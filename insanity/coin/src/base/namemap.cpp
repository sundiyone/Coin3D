/**************************************************************************\
 * Copyright (c) Kongsberg Oil & Gas Technologies AS
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
\**************************************************************************/

#include "base/namemap.h"

#include <cstdlib>
#include <cassert>
#include <cstring>

#include "threads/threadsutilp.h"
#include "tidbitsp.h"
#include "coindefs.h"

/* ************************************************************************* */

/*
  Implementation note: we can not use the cc_dict ADT to simplify this
  implementation, as cc_dict requires all keys in the hash to be
  unique. That is not necessarily true for a set of strings, as two
  strings can map to the same key (even though the probability is low
  (with a good hash routine)).

  So it is indeed necessary to use our own string hash, where equality
  is tested for with first hash value and then string compare.

  mortene.
*/

/* ************************************************************************* */

#define CHUNK_SIZE (65536-32)
static const unsigned int NAME_TABLE_SIZE = 1999;

struct NamemapMemChunk {
  char mem[CHUNK_SIZE];
  char * curbyte;
  size_t bytesleft;
  struct NamemapMemChunk * next;
};

struct NamemapBucketEntry {
  unsigned long hashvalue;
  const char * str;
  struct NamemapBucketEntry * next;
};

static void * access_mutex = nullptr;
static struct NamemapBucketEntry ** nametable = nullptr;
static struct NamemapMemChunk * headchunk = nullptr;

/* ************************************************************************* */

extern "C" {

/* Deallocates static process resources. */
static void
namemap_cleanup(void)
{
  unsigned int i;

  struct NamemapMemChunk * chunkptr = headchunk;
  while (chunkptr) {
    struct NamemapMemChunk * next = chunkptr->next;
    std::free(chunkptr);
    chunkptr = next;
  }
  
  for (i = 0; i < NAME_TABLE_SIZE; i++) {
    struct NamemapBucketEntry * entry = nametable[i];
    while (entry) {
      struct NamemapBucketEntry * next = entry->next;
      std::free(entry);
      entry = next;
    }
  }
  std::free(nametable);
  nametable = static_cast<struct NamemapBucketEntry **>(nullptr);

  CC_MUTEX_DESTRUCT(access_mutex);
}

} // extern "C"

/* Initializes static data. */
static void
namemap_init(void)
{
  unsigned int i;

  nametable = static_cast<struct NamemapBucketEntry **>(
    std::malloc(sizeof(struct NamemapBucketEntry *) * NAME_TABLE_SIZE));
  for (i = 0; i < NAME_TABLE_SIZE; i++) { nametable[i] = nullptr; }

  headchunk = nullptr;

  coin_atexit(static_cast<coin_atexit_f *>(namemap_cleanup), CC_ATEXIT_SBNAME);
}

static const char *
find_string_address(const char * s)
{
  size_t len = std::strlen(s) + 1;

  /* FIXME: this is an unacceptable limitation. 20030608 mortene. */
  assert(len < CHUNK_SIZE);

  if (headchunk == nullptr || headchunk->bytesleft < len) {
    struct NamemapMemChunk * newchunk = static_cast<struct NamemapMemChunk *>(
      std::malloc(sizeof(struct NamemapMemChunk))
      );

    newchunk->curbyte = newchunk->mem;
    newchunk->bytesleft = CHUNK_SIZE;
    newchunk->next = headchunk;

    headchunk = newchunk;
  }

  (void)std::strcpy(headchunk->curbyte, s);
  s = headchunk->curbyte;

  headchunk->curbyte += len;
  headchunk->bytesleft -= len;

  return s;
}

static const char *
namemap_find_or_add_string(const char * str, bool addifnotfound)
{
  unsigned long h, i;
  struct NamemapBucketEntry * entry;

  if (access_mutex == nullptr) { CC_MUTEX_CONSTRUCT(access_mutex); }
  CC_MUTEX_LOCK(access_mutex);

  if (nametable == nullptr) { namemap_init(); }
  assert(nametable != static_cast<struct NamemapBucketEntry **>(nullptr) && "name hash dead");

  h = cc_string_hash_text(str);
  i = h % NAME_TABLE_SIZE;
  entry = nametable[i];

  while (entry != nullptr) {
    if (entry->hashvalue == h && std::strcmp(entry->str, str) == 0) { break; }
    entry = entry->next;
  }

  if ((entry == nullptr) && addifnotfound) {
    entry = static_cast<struct NamemapBucketEntry *>(std::malloc(sizeof(struct NamemapBucketEntry)));
    entry->str = find_string_address(str);
    entry->hashvalue = h;
    entry->next = nametable[i];

    nametable[i] = entry;
  }

  CC_MUTEX_UNLOCK(access_mutex);
  return entry ? entry->str : nullptr;
}

/* ************************************************************************* */

/*!
  Adds a string to the name hash and returns it's permanent memory
  address pointer. If the string is already present in the name hash,
  just returns the address pointer.
*/
const char *
cc_namemap_get_address(const char * str)
{
  return namemap_find_or_add_string(str, true);
}

/*!
  Returns address pointer of a given string.

  String will not be added if it doesn't exist in name hash (and \c
  nullptr will be returned).
*/
const char *
cc_namemap_peek_string(const char * str)
{
  return namemap_find_or_add_string(str, false);
}

#undef CHUNK_SIZE
