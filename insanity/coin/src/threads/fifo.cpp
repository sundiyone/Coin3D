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

#include <Inventor/C/threads/fifo.h>

#include <stdlib.h>
#include <assert.h>

#include <Inventor/C/threads/mutex.h>
#include <Inventor/C/threads/condvar.h>
#include <Inventor/C/errors/debugerror.h>

#include "threads/fifop.h"
#include "threads/mutexp.h"
#include "threads/condvarp.h"

/*
  The cc_fifo is a C datatype for managing a pointer first-in,
  first-out queue.
*/

/* ********************************************************************** */

static cc_fifo_item * cc_fifo_item_new(void);
static void cc_fifo_item_delete(cc_fifo_item * item);

static cc_fifo_item * i_get_free_item(cc_fifo * fifo);
static void i_append(cc_fifo * fifo, cc_fifo_item * item);
static cc_fifo_item * i_unlink_head(cc_fifo * fifo);

/* ********************************************************************** */

void
cc_fifo_struct_init(cc_fifo * fifo)
{
  assert(fifo != nullptr);
  cc_mutex_struct_init(&fifo->access);
  fifo->head = nullptr;
  fifo->tail = nullptr;
  fifo->free = nullptr;
  fifo->elements = 0;
  cc_condvar_struct_init(&fifo->sleep);
}

void
cc_fifo_struct_clean(cc_fifo * fifo)
{
  cc_fifo_item * item, * next;
  assert(fifo != nullptr);
  cc_mutex_struct_clean(&fifo->access);
  /* free fifo list */
  item = fifo->head;
  while ( item != nullptr ) {
    next = item->next;
    cc_fifo_item_delete(item);
    item = next;
  }
  /* free free list */
  item = fifo->free;
  while ( item != nullptr ) {
    next = item->next;
    cc_fifo_item_delete(item);
    item = next;
  }
  cc_condvar_struct_clean(&fifo->sleep);
}

/* ********************************************************************** */

cc_fifo *
cc_fifo_new(void)
{
  cc_fifo * fifo;
  fifo = (cc_fifo*) malloc(sizeof(cc_fifo));
  cc_fifo_struct_init(fifo);
  return fifo;
}

void
cc_fifo_delete(cc_fifo * fifo)
{
  cc_fifo_struct_clean(fifo);
  free(fifo);
}

/* ********************************************************************** */

void
cc_fifo_assign(cc_fifo * fifo, void * ptr, uint32_t type)
{
  cc_fifo_item * item;
  assert(fifo != nullptr);
  cc_mutex_lock(&fifo->access);
  item = i_get_free_item(fifo);
  item->item = ptr;
  item->type = type;
  i_append(fifo, item);
  cc_condvar_wake_one(&fifo->sleep);
  cc_mutex_unlock(&fifo->access);
}

void
cc_fifo_retrieve(cc_fifo * fifo, void ** ptr, uint32_t * type)
{
  cc_fifo_item * item;
  assert(fifo != nullptr && ptr != nullptr);
  cc_mutex_lock(&fifo->access);
  while ( true ) {
    if ( fifo->elements == 0 ) {
      cc_condvar_wait(&fifo->sleep, &fifo->access);
    } else {
      item = i_unlink_head(fifo);
      *ptr = item->item;
      if ( type != nullptr ) *type = item->type;
      item->next = fifo->free;
      fifo->free = item;
      cc_mutex_unlock(&fifo->access);
      cc_condvar_wake_one(&fifo->sleep);
      return;
    }
  }
}

bool
cc_fifo_try_retrieve(cc_fifo * fifo, void ** ptr, uint32_t * type)
{
  cc_fifo_item * item;
  assert(fifo != nullptr && ptr != nullptr);
  /* FIXME: consider cc_mutex_try_lock()? to escape even a failed lock */
  if ( ! cc_mutex_try_lock(&fifo->access) ) {
    return false;
  }
  if ( fifo->elements == 0 ) {
    cc_mutex_unlock(&fifo->access);
    return false;
  }
  item = i_unlink_head(fifo);
  *ptr = item->item;
  if ( type != nullptr ) *type = item->type;
  cc_fifo_item_delete(item);
  cc_mutex_unlock(&fifo->access);
  cc_condvar_wake_one(&fifo->sleep);
  return true;
}

/* ********************************************************************** */

unsigned int
cc_fifo_size(cc_fifo * fifo)
{
  assert(fifo != nullptr);
  return fifo->elements;
}

/* ********************************************************************** */

cc_fifo_item *
cc_fifo_item_new(void) /* static */
{
  cc_fifo_item * item;
  item = (cc_fifo_item*) malloc(sizeof(cc_fifo_item));
  assert(item != nullptr);
  item->next = nullptr;
  item->item = nullptr;
  item->type = 0;
  return item;
}

void
cc_fifo_item_delete(cc_fifo_item * item) /* static */
{
  assert(item != nullptr);
  free(item);
}

/* ********************************************************************** */

void
cc_fifo_lock(cc_fifo * fifo)
{
  assert(fifo != nullptr);
  cc_mutex_lock(&fifo->access);
}

bool
cc_fifo_try_lock(cc_fifo * fifo)
{
  assert(fifo != nullptr);
  return cc_mutex_try_lock(&fifo->access);
}

void
cc_fifo_unlock(cc_fifo * fifo)
{
  assert(fifo != nullptr);
  cc_mutex_unlock(&fifo->access);
}

/* ********************************************************************** */

bool
cc_fifo_peek(cc_fifo * fifo, void ** item, uint32_t * type)
{
  assert(fifo != nullptr);
  if ( fifo->head == nullptr ) return false;
  *item = fifo->head->item;
  if ( type != nullptr ) *type = fifo->head->type;
  return true;
}

bool
cc_fifo_contains(cc_fifo * fifo, void * itemptr)
{
  cc_fifo_item * item;
  assert(fifo != nullptr);
  item = fifo->head;
  while ( item != nullptr ) {
    if ( item->item == itemptr ) return true;
    item = item->next;
  }
  return false;
}

bool
cc_fifo_reclaim(cc_fifo * fifo, void * itemptr)
{
  cc_fifo_item * item, * prev;
  assert(fifo != nullptr);
  item = fifo->head;
  prev = nullptr;
  while ( item != nullptr ) {
    if ( item->item == itemptr ) {
      if ( prev == nullptr ) fifo->head = item->next;
      else prev->next = item->next;
      if ( fifo->tail == item ) fifo->tail = prev;
      /* and reset/store the container */
      item->item = nullptr;
      item->type = 0;
      item->next = fifo->free;
      fifo->free = item;
      return true;
    }
    prev = item;
    item = item->next;
  }
  return false;
}

/* ********************************************************************** */

/*
  get item from free list or construct a new one
*/

cc_fifo_item *
i_get_free_item(cc_fifo * fifo) /* static */
{
  cc_fifo_item * item;
  if ( fifo->free != nullptr ) {
    item = fifo->free;
    fifo->free = item->next;
    item->next = nullptr;
  } else {
    item = cc_fifo_item_new();
  }
  return item;
}

/*
  append item to fifo.  make sure both ::head and ::tail are correct
  after.
*/

void
i_append(cc_fifo * fifo, cc_fifo_item * item) /* static */
{
  if ( fifo->tail == nullptr ) {
    fifo->head = item;
    fifo->tail = item;
  } else {
    fifo->tail->next = item;
    fifo->tail = item;
  }
  fifo->elements += 1;
}

/*
  unlink first item from fifo.  make sure both ::head and ::tail are
  correct after.
*/

cc_fifo_item *
i_unlink_head(cc_fifo * fifo) /* static */
{
  cc_fifo_item * item;
  item = fifo->head;
  fifo->head = item->next;
  if ( fifo->head == nullptr )
    fifo->tail = nullptr;
  fifo->elements -= 1;
  return item;
}

/* ********************************************************************** */

/*!
  \class SbFifo Inventor/threads/SbFifo.h
  \brief A class for managing a pointer first-in, first-out queue.
  \ingroup threads
*/

/*!
  \fn void SbFifo::assign(void * ptr, uint32_t type)

  Puts pointer \a ptr of type \a type into the fifo.

  The \a type argument is just meant as a user data tag, and a 0 value
  can be given as the \a type argument if type data is uninteresting.
*/

/*!
  \fn void SbFifo::retrieve(void *& ptr, uint32_t &type)

  Reads a pointer from the queue. Blocks until a pointer is available
  for reading.
*/

/*!
  \fn bool SbFifo::tryRetrieve(void *& ptr, uint32_t & type)

  Tries to read a pointer from the queue. If no data can be read, \c
  false is returned, and \c true otherwise. The function does not
  block.
*/

/*!
  \fn unsigned int SbFifo::size(void) const

  Returns number of pointers currently in the queue.
*/

/*!
  \fn void SbFifo::lock(void) const

  Blocks until the queue can be locked.
*/

/*!
  \fn void SbFifo::unlock(void) const

  Unlocks the queue.
*/

/*!
  \fn bool SbFifo::peek(void *& item, uint32_t & type) const

  Peeks at the head item of the queue without removing it.  In the
  case where the fifo is empty, \c false is returned.

  The queue must be locked with SbFifo::lock() before using this
  function, then unlocked.
*/

/*!
  \fn bool SbFifo::contains(void * item) const

  Returns \c true or \c false depending on whether the item is in the
  queue.

  The queue must be locked with SbFifo::lock() before using this
  function, then unlocked.
*/

/*!
  \fn bool SbFifo::reclaim(void * item)

  This function removes the given \a item from the queue.  Returns \c
  true or \c false depending on whether the item was in the queue in
  the first place.

  The queue must be locked with SbFifo::lock() before using this
  function, then unlocked.
*/

/* ********************************************************************** */
