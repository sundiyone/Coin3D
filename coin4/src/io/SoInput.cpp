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

/*!
  \class SoInput SoInput.h Inventor/SoInput.h
  \brief The SoInput class is an abstraction of file import functionality.
  \ingroup general

  This class takes care of most of the chores of doing data import in Coin.
  It puts a layer of abstraction over the read operations to make it
  transparent for the rest of the Coin code whether or not we're reading
  from a file, from a memory buffer or from stdin.

  SoInput also takes care of checking file validity, aswell as handling
  information about features in the various file formats which are
  supported.

  Example usage:
  \code
  int
  main(void)
  {
    SoDB::init();

    SoInput in;
    if (in.openFile("fab_model.iv")) {
      SoSeparator * root = SoDB::readAll(&in);
      if (root) {
        // Do stuff with the imported scene graph here
        // ...
        return 0;
      }
    }

    return 1;
  }
  \endcode


  Important note: there are several public and protected methods which
  makes it possible to pass in or get returned FILE* structures in
  this class. Do \e not use these methods when the Coin library has
  been compiled as an MSWindows DLL, as passing FILE* instances back
  or forth to DLLs is dangerous and will most likely cause a
  crash. This is an intrinsic limitation for MSWindows DLLs.


  This class supports one environment variable called
  COIN_SOINPUT_SEARCH_GLOBAL_DICT.  When set to "1", the global
  dictionary is searched after the current file dictionary when
  resolving USE keywords. This makes it possible to reference nodes in
  other files. The reason for introducing this feature is that the
  SoFile node rereads the file whenever the name field changes.  The
  first time the file is read, it's possible to reference nodes in the
  parent file, using the USE keyword. But, when the file is reread
  this is no longer possible, since the reading now starts at the
  SoFile node, with an empty dictionary.

  \sa SoOutput, SoDB
*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif // HAVE_UNISTD_H
#ifdef HAVE_SYS_TYPES_H
/* According to Coin user Ralf Corsepius, at least SunOS4 needs to
   include sys/types.h before netinet/in.h. There have also been a
   problem report for FreeBSD which seems to indicate that the same
   dependency exists on that platform aswell. */
#include <sys/types.h>
#endif // HAVE_SYS_TYPES_H
#include <ctype.h>

#include <Inventor/SoInput.h>

#include <Inventor/C/tidbits.h>
#include <Inventor/SbName.h>
#include <Inventor/SoDB.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/errors/SoReadError.h>
#include <Inventor/fields/SoField.h>
#include <Inventor/lists/SbStringList.h>
#include <Inventor/misc/SoProto.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/threads/SbStorage.h>

#include "misc/SbHash.h"
#include "tidbitsp.h"
#include "glue/zlib.h"
#include "coindefs.h" // COIN_STUB(), COIN_OBSOLETED()
#include "io/SoInputP.h"
#include "io/SoInput_FileInfo.h"

// This (POSIX-compliant) macro is missing from the Win32 API header
// files for MSVC++ 6.0.
#ifndef S_ISDIR
 // The _S_IFDIR bitpattern is not in the POSIX standard, but MSVC++
 // header files has it.
 #ifdef _S_IFDIR
 #define S_ISDIR(s) (s & _S_IFDIR)
 #else // Ai.
 #error Can neither find nor make an S_ISDIR macro to test stat structures.
 #endif // !_S_IFDIR
#endif // !S_ISDIR

// *************************************************************************

SbStringList * SoInput::dirsearchlist = nullptr;

static SbStorage * soinput_tls = nullptr;

struct soinput_tls_data {
  SbStringList * searchlist;
  int instancecount;
};

static void
soinput_construct_tls_data(void * closure)
{
  soinput_tls_data * data = (soinput_tls_data*) closure;
  data->searchlist = new SbStringList;
  data->instancecount = 0;
}

static void
soinput_destruct_tls_data(void * closure)
{
  soinput_tls_data * data = (soinput_tls_data*) closure;

  int n = data->searchlist->getLength();
  for (int i = 0; i < n; i++) {
    delete (*data->searchlist)[i];
  }
  delete data->searchlist;
}

// *************************************************************************

bool
SoInputP::debug(void)
{
  static int dbg = -1;
  if (dbg == -1) {
    const char * env = coin_getenv("COIN_DEBUG_IMPORT");
    dbg = (env && (atoi(env) > 0)) ? 1 : 0;
  }
  return dbg;
}

bool
SoInputP::debugBinary(void)
{
  static int debug = -1;
  if (debug == -1) {
    const char * env = coin_getenv("COIN_DEBUG_BINARY_INPUT");
    debug = (env && (atoi(env) > 0)) ? 1 : 0;
  }
  return debug ? true : false;
}

// *************************************************************************
/*
  Important note: Up until Coin 3.1.1 we used to have a bug in SoInput
  when reading files from other files (SoFile/SoVRMLInline++). The SoInput
  dictionary was global for all files pushed onto the SoInput filestack,
  and DEFs in extra files could therefore overwrite DEFs in the original
  file. This minimal case reproduces this bug:

  #Inventor V2.1 ascii

  Switch {
    whichChild -1
    DEF cube Cube {}
  }

  File { name "minimal_ref.iv" }
  USE cube

  minimal_ref.iv looks something like this:

  #Inventor V2.1 ascii
  DEF cube Info {}

  In older versions of Coin you'll not see the Cube when loading the first
  file.

 */
// *************************************************************************


// Helper function that pops the stack when the current file is at
// EOF.  Then it returns the file at the top of the stack.
SoInput_FileInfo *
SoInputP::getTopOfStackPopOnEOF(void)
{
  SoInput_FileInfo * fi = owner->getTopOfStack();
  assert(fi); // Should always have a top of stack, because the last
              // element on the stack is never removed until the
              // SoInput is closed

  // Pop the stack if end of current file
  if (fi->isEndOfFile()) {
    (void) owner->popFile(); // Only pops if more than one file is on
                             // the stack.
    fi = owner->getTopOfStack();
    assert(fi);
  }

  return fi;
}

// Helperfunctions to handle different filetypes (Inventor, VRML 1.0
// and VRML 2.0).
//
// VRML 1.0 identifiers are defined as:
//
//  VRML 1.0 Node names must not begin with a digit, and must
//  not contain spaces or control characters, single or double
//  quote characters, backslashes, curly braces, the sharp (#)
//  character, the plus (+) character or the period character.
//
//  Field names start with lower case letters, Node types start
//  with upper case. The remainder of the characters may be any
//  printable ascii (21H-7EH) except curly braces {}, square
//  brackets [], single ' or double " quotes, sharp #, backslash
//  \\ plus +, period . or ampersand &.
//
//  In addition to this, we found ',' to be an invalid character in
//  VRML 1.0 names. This was made apparent when reading the following
//  fields on an unknown node:
//
//   fields [SFString test, SFFloat length]
//
//  If ',' is to be a valid character in a name, then the name
//  of the first field would become 'test,', and not just 'test'
//
// The grammar for VRML2 identifiers is:
//
//  nodeNameId ::= Id ;
//  nodeTypeId ::= Id ;
//  fieldId ::= Id ;
//
//  Id ::= IdFirstChar | IdFirstChar IdRestChars ;
//
//  IdFirstChar ::= Any ISO-10646 character encoded using UTF-8
//  except: 0x30-0x39, 0x0-0x20, 0x22, 0x23, 0x27, 0x2b, 0x2c,
//  0x2d, 0x2e, 0x5b, 0x5c, 0x5d, 0x7b, 0x7d, 0x7f ;
//
//  IdRestChars ::= Any number of ISO-10646 characters except:
//  0x0-0x20, 0x22, 0x23, 0x27, 0x2c, 0x2e, 0x5b, 0x5c, 0x5d,
//  0x7b, 0x7d, 0x7f ;

bool
SoInputP::isNameStartChar(unsigned char c, bool validIdent)
{
  if (validIdent) return SbName::isIdentStartChar(c);
  return (c > 0x20); // Not control characters
}

bool
SoInputP::isNameStartCharVRML1(unsigned char c, bool validIdent)
{
  static unsigned char invalid_vrml1_table[256];
  static unsigned char valid_ident_invalid_vrml1_table[256];

  static int isNameStartCharVRML1Initialized = false;
  if (!isNameStartCharVRML1Initialized) {
    const unsigned char invalid_vrml1[] = {
      0x22, 0x23, 0x27, 0x2b, 0x2c, 0x2e, 0x5c, 0x7b, 0x7d, 0x00 }; // 0x7d = 125
    //'"',  '#',  ''',  '+',  ',',  '.',  '\',  '{',  '}'

    // Differences from invalid_vrml1: '&' , '[', and ']' are now invalid
    const unsigned char valid_ident_invalid_vrml1[] = {
      0x22, 0x23, 0x26, 0x27, 0x2b, 0x2c, 0x2e, 0x5b, 0x5c, 0x5d, 0x7b, 0x7d, 0x00 }; // 0x7d = 125
    //'"',  '#',   '&', ''',  '+',  ',',  '.',  '[',  '\',   ']',  '{',  '}'

    for (int c = 0; c < 256; ++c) {
      invalid_vrml1_table[c] = 0;
      valid_ident_invalid_vrml1_table[c] = 0;
    }

    const unsigned char * ptr = invalid_vrml1;
    while (*ptr) { invalid_vrml1_table[*ptr] = 1; ++ptr; }
    ptr = valid_ident_invalid_vrml1;
    while (*ptr) { valid_ident_invalid_vrml1_table[*ptr] = 1; ++ptr; }

    isNameStartCharVRML1Initialized = true;
  }

  if (c <= 0x20) return false; // Control characters
  if (c >= 0x30 && c <= 0x39) return false; // Digits

  if (validIdent) return (valid_ident_invalid_vrml1_table[c] == 0);
  return (invalid_vrml1_table[c] == 0);
}

bool
SoInputP::isNameStartCharVRML2(unsigned char c, bool validIdent)
{
  static unsigned char invalid_vrml2_table[256];
  static unsigned char valid_ident_invalid_vrml2_table[256];

  static int isNameStartCharVRML2Initialized = false;
  if (!isNameStartCharVRML2Initialized) {
    const unsigned char invalid_vrml2[] = {
      0x22, 0x23, 0x27, 0x2b, 0x2c, 0x2d, 0x2e, 0x5b, 0x5c, 0x5d, 0x7b, 0x7d, 0x7f, 0x00 }; // 0x7f = 127
    //'"',  '#',  ''',  '+',  ',',  '-',  '.',  '[',  '\',  ']',  '{',  '}',  ''

    const unsigned char * valid_ident_invalid_vrml2 = invalid_vrml2;

    for (int c = 0; c < 256; ++c) {
      invalid_vrml2_table[c] = 0;
      valid_ident_invalid_vrml2_table[c] = 0;
    }

    const unsigned char * ptr = invalid_vrml2;
    while (*ptr) { invalid_vrml2_table[*ptr] = 1; ++ptr; }
    ptr = valid_ident_invalid_vrml2;
    while (*ptr) { valid_ident_invalid_vrml2_table[*ptr] = 1; ++ptr; }

    isNameStartCharVRML2Initialized = true;
  }

  if (c <= 0x20) return false; // Control characters
  if (c >= 0x30 && c <= 0x39) return false; // Digits

  if (validIdent) return (valid_ident_invalid_vrml2_table[c] == 0);

  // For Coin to be able to load VRML97 (invalid) files that have
  // been generated with illegal names, '+' is considered a valid
  // startcharacter.
  static int non_strict = -1;
  if (non_strict == -1) {
    const char * env = coin_getenv("COIN_NOT_STRICT_VRML97");
    non_strict = env && (atoi(env) > 0);
  }

  if (c == '+' && non_strict) // '+' is considered valid
    return true;

  return (invalid_vrml2_table[c] == 0);
}

// Helperfunction to handle different filetypes (Inventor, VRML 1.0
// and VRML 2.0).
//
// See SoInputP::isIdentStartChar for more information
bool
SoInputP::isNameChar(unsigned char c, bool validIdent)
{
  if (validIdent) return SbName::isIdentChar(c);
  return (c > 0x20); // Not control characters
}

bool
SoInputP::isNameCharVRML1(unsigned char c, bool validIdent)
{
  static unsigned char invalid_vrml1_table[256];
  static unsigned char valid_ident_invalid_vrml1_table[256];

  static int isNameCharVRML1Initialized = false;
  if (!isNameCharVRML1Initialized) {
    const unsigned char invalid_vrml1[] = {
      0x22, 0x23, 0x27, 0x2b, 0x2c, 0x2e, 0x5c, 0x7b, 0x7d, 0x00 }; // 0x7d = 125
    //'"',  '#',  ''',  '+',  ',',  '.',  '\',  '{',  '}'

    // Differences from invalid_vrml1: '&' , '[', and ']' are now invalid
    const unsigned char valid_ident_invalid_vrml1[] = {
      0x22, 0x23, 0x26, 0x27, 0x2b, 0x2c, 0x2e, 0x5b, 0x5c, 0x5d, 0x7b, 0x7d, 0x00 }; // 0x7d = 125
    //'"',  '#',   '&', ''',  '+',  ',',  '.',  '[',  '\',   ']',  '{',  '}'

    for (int c = 0; c < 256; ++c) {
      invalid_vrml1_table[c] = 0;
      valid_ident_invalid_vrml1_table[c] = 0;
    }

    const unsigned char * ptr = invalid_vrml1;
    while (*ptr) { invalid_vrml1_table[*ptr] = 1; ++ptr; }
    ptr = valid_ident_invalid_vrml1;
    while (*ptr) { valid_ident_invalid_vrml1_table[*ptr] = 1; ++ptr; }

    isNameCharVRML1Initialized = true;
  }

  if (c <= 0x20) return false; // Control characters

  if (validIdent) return (valid_ident_invalid_vrml1_table[c] == 0);
  return (invalid_vrml1_table[c] == 0);
}

bool
SoInputP::isNameCharVRML2(unsigned char c, bool validIdent)
{
  static unsigned char invalid_vrml2_table[256];
  static unsigned char valid_ident_invalid_vrml2_table[256];

  static int isNameCharVRML2Initialized = false;
  if (!isNameCharVRML2Initialized) {
    // Compared to isIdentStartChar, '+' and '-' have now become valid characters.
    const unsigned char invalid_vrml2[] = {
      0x22, 0x23, 0x27, 0x2c, 0x2e, 0x5b, 0x5c, 0x5d, 0x7b, 0x7d, 0x7f, 0x00 }; // 0x7f = 127
    //'"',  '#',  ''',  ',',  '.',  '[',  '\',  ']',  '{',  '}',  ''

    const unsigned char * valid_ident_invalid_vrml2 = invalid_vrml2;

    for (int c = 0; c < 256; ++c) {
      invalid_vrml2_table[c] = 0;
      valid_ident_invalid_vrml2_table[c] = 0;
    }

    const unsigned char * ptr = invalid_vrml2;
    while (*ptr) { invalid_vrml2_table[*ptr] = 1; ++ptr; }
    ptr = valid_ident_invalid_vrml2;
    while (*ptr) { valid_ident_invalid_vrml2_table[*ptr] = 1; ++ptr; }

    isNameCharVRML2Initialized = true;
  }

  if (c <= 0x20) return false; // Control characters

  if (validIdent) return (valid_ident_invalid_vrml2_table[c] == 0);
  return (invalid_vrml2_table[c] == 0);
}

// *************************************************************************

#define PRIVATE(obj) (obj->pimpl)

// *************************************************************************

/*!
  Constructor. If no filepointer is set, input will be read from stdin.
 */
SoInput::SoInput(void)
{
  this->constructorsCommon();
}

/*!
  A constructor which copies the reference mappings from \a dictIn upon
  initialization.
 */
SoInput::SoInput(SoInput * dictIn)
{
  if (dictIn && dictIn->filestack.getLength()) {
    PRIVATE(this)->copied_references = dictIn->getTopOfStack()->getReferences();
  }
  this->constructorsCommon();
}

/*!
  \COININTERNAL
  Do common tasks for the constructors.
*/
void
SoInput::constructorsCommon(void)
{
  // In general, we force app programmers to call SoDB::init(),
  // directly or indirectly, before using any other part of the Coin
  // API. We grant slack in one particular spot, though: it should be
  // possible to construct an SoInput before SoDB::init() has been
  // invoked from app code, as it is common to just have an SoInput on
  // the stack of the main() function.
  //
  // But since SoInput uses threads, which needs to be initialized, we
  // need to check for SoDB::init() here, and invoke it if it was not
  // yet called.
  if (!SoDB::isInitialized()) { SoDB::init(); }

  PRIVATE(this) = new SoInputP(this);

  /* It is not possible to "pass" C library data from the application
     to a MSWin .DLL, so this is necessary to get hold of the stderr
     FILE*. Just using fprintf(stderr, ...) or fprintf(stdout, ...)
     directly might result in a crash when Coin has been compiled as a
     .DLL. */
  this->setFilePointer(coin_get_stdin());

  soinput_tls_data * data = (soinput_tls_data *)soinput_tls->get();
  if (data->instancecount == 0) {
    const SbStringList & dir = *SoInput::dirsearchlist;
    for (int i = 0; i < dir.getLength(); i++) {
      data->searchlist->append(new SbString(dir[i]->getString()));
    }
  }
  data->instancecount++;
}

/*!
  Destructor. Runs SoInput::closeFile() to close any open files.
*/
SoInput::~SoInput(void)
{
  this->closeFile();

  // FIXME: this causes a crash if SoDB::cleanup() was already called,
  // as the atexit-function destructed soinput_tls. This can
  // e.g. happen for the following, common main() structure:
  //
  // int main(void) {
  //   SoDB::init();
  //   [...]
  //   SoInput in;
  //   [...]
  //   SoDB::cleanup();
  //   return 0;
  // }
  //
  // 20041022 mortene.
  soinput_tls_data * data = (soinput_tls_data *)soinput_tls->get();

  data->instancecount--;
  if (data->instancecount == 0) {
    for (int i = 0; i < data->searchlist->getLength(); i++) {
      delete (*data->searchlist)[i];
    }
    data->searchlist->truncate(0);
  }

  delete PRIVATE(this);
}

/*!
  Adds a ROUTE from /a fromnode's \fromfield, to \a tonode's
  tofield. This makes it possible to defines ROUTEs in files
  before the \a fromnode or \a tonode is parsed.

  \COIN_FUNCTION_EXTENSION

  \since Coin 2.0
*/
void
SoInput::addRoute(const SbName & fromnode, const SbName & fromfield,
                  const SbName & tonode, const SbName & tofield)
{
  SoInput_FileInfo * info = this->getTopOfStack();
  assert(info);

  info->addRoute(fromnode, fromfield,
                   tonode, tofield);
}

/*!
  Searches for PROTO named \a name. This function will only return
  PROTOs that have been read by the current SoInput instance.

  \since Coin 2.3
*/
SoProto *
SoInput::findProto(const SbName & name)
{
  SoInput_FileInfo * info = this->getTopOfStack();
  if (info) {
    return info->findProto(name);
  }
  return nullptr;
}

/*!
  Adds a Proto which should be active in the current scope.

  \COIN_FUNCTION_EXTENSION

  \since Coin 2.0
*/
void
SoInput::addProto(SoProto * proto)
{
  SoInput_FileInfo * info = this->getTopOfStack();
  assert(info);
  proto->ref(); // the PROTO is unref'ed when the file is popped
  info->addProto(proto);
}

/*!
  Pushed a Proto onto the Proto stack. The Proto stack is used during
  VRML2 file parsing.

  \COIN_FUNCTION_EXTENSION

  \sa popProto()
  \since Coin 2.0
*/
void
SoInput::pushProto(SoProto * proto)
{
  SoInput_FileInfo * info = this->getTopOfStack();
  assert(info);
  info->pushProto(proto);
}

/*!
  Pops a Proto off the Proto stack.

  \COIN_FUNCTION_EXTENSION

  \sa pushProto()
  \since Coin 2.0
*/
void
SoInput::popProto(void)
{
  SoInput_FileInfo * info = this->getTopOfStack();
  assert(info);
  info->popProto();
}

/*!
  Returns the Proto at the top of the Proto stack.

  \COIN_FUNCTION_EXTENSION

  \sa pushProto()
  \since Coin 2.0
*/
SoProto *
SoInput::getCurrentProto(void) const
{
  SoInput_FileInfo * info = this->getTopOfStack();
  assert(info);
  return info->getCurrentProto();
}

/*!
  Checks if the next bytes in \a in is the IS keyword. Returns \c true
  if the IS keyword was found, \a readok will be set to \c false if
  some error occured while searching for the IS keyword.

  \COIN_FUNCTION_EXTENSION

  \since Coin 2.0
*/
bool
SoInput::checkISReference(SoFieldContainer * container,
                          const SbName & fieldname, bool & readok)
{
  readok = true;
  SoProto * proto = this->getCurrentProto();
  bool foundis = false;
  if (proto) {
    // The reason for this specific parsing code is that we need
    // to put back whitespace when the IS keyword isn't found.
    // SoInput::read(SbName) skips whitespace automatically...
    // pederb, 2001-10-26
    SbString putback;
    const int STATE_WAIT_I = 0;
    const int STATE_EXPECT_S = 1;
    const int STATE_EXPECT_SPACE = 2;
    const int STATE_FOUND = 3;
    const int STATE_NOTFOUND = 4;
    int state = STATE_WAIT_I;
    do {
      char c;
      readok = this->read(c, false);
      putback += c;
      if (readok) {
        switch (state) {
        case STATE_WAIT_I:
          if (c == 'I') state = STATE_EXPECT_S;
          else if (!coin_isspace(c)) state = STATE_NOTFOUND;
          break;
        case STATE_EXPECT_S:
          if (c == 'S') state = STATE_EXPECT_SPACE;
          else state = STATE_NOTFOUND;
          break;
        case STATE_EXPECT_SPACE:
          if (coin_isspace(c)) state = STATE_FOUND;
          else state = STATE_NOTFOUND;
          break;
        default:
          assert(0 && "should not happen");
          break;
        }
      }
    } while (readok && state != STATE_FOUND && state != STATE_NOTFOUND);

    if (state == STATE_FOUND) {
      foundis = true;
      SbName iname;
      readok = this->read(iname, true);
      if (readok) {
        assert(container->isOfType(SoNode::getClassTypeId()));
        proto->addISReference((SoNode*) container, fieldname, iname);
      }
    }
    else {
      assert(state == STATE_NOTFOUND);
      this->putBack(putback.getString());
      foundis = false;
    }
  }
  return foundis;
}

/*!
  Uses the given file pointer as the input file. The input stack of
  files will be emptied first. Closing a file passed in by it's file
  pointer is the library user's responsibility.

  Important note: do \e not use this method when the Coin library has
  been compiled as an MSWindows DLL, as passing FILE* instances back
  or forth to DLLs is dangerous and will most likely cause a
  crash. This is an intrinsic limitation for MSWindows DLLs.

  Note that it is not allowed to pass a FILE* to a gzip-compressed
  file under Mac OS X.

  \sa openFile(), closeFile()
*/
void
SoInput::setFilePointer(FILE * newFP)
{
  this->closeFile();

  const char * name = (newFP == coin_get_stdin()) ? "<stdin>" : "";
  SoInput_Reader * reader = nullptr;

  // delay creating the reader if we're reading from
  // stdin. SoInput_FileInfo will create it when we know that we're
  // actually going to read from stdin
  if (newFP != coin_get_stdin()) {
    reader = SoInput_Reader::createReader(newFP, SbString(name));
  }
  SoInput_FileInfo * newfile =
    new SoInput_FileInfo(reader, PRIVATE(this)->copied_references);
  if (newfile) this->filestack.insert(newfile, 0);
}

/*!
  Open the given file, and make it the only one in the file stack. If
  \a okIfNotFound is \c false, show a warning message if the file could
  not be opened.

  Returns \c true if file could be opened for reading, \c false
  otherwise.

  Note: even if your attempt at opening a file is unsuccessful,
  the SoInput instance will \e not default to reading from stdin after
  a call has been made to this method.

  \sa setFilePointer(), pushFile(), closeFile()
*/
bool
SoInput::openFile(const char * fileName, bool okIfNotFound)
{
  this->closeFile();

  SbString fullname;
  FILE * fp = this->findFile(fileName, fullname);
  if (fp) {
    SoInput_Reader * reader = SoInput_Reader::createReader(fp, fullname);
    assert(reader);
    SoInput_FileInfo * newfile =
      new SoInput_FileInfo(reader, PRIVATE(this)->copied_references);
    this->filestack.insert(newfile, 0);

    SoInput::addDirectoryFirst(SoInput::getPathname(fullname).getString());
    return true;
  }

  if (!okIfNotFound) { SoReadError::post(this, fullname.getString()); }

  return false;
}

/*!
  Push a new file on top of the stack. Further read operations will take
  place with the new file until it reaches end-of-file, upon when the
  file will be popped of the stack and we'll continue with the next file
  in the stack.

  Returns \c true if the file could be opened for reading, \c false
  otherwise.

  \sa openFile()
*/
bool
SoInput::pushFile(const char * filename)
{
  // Get rid of default stdin filepointer if it has not yet been read
  // from. The reason for this is that <stdin> is put on the stack as
  // the default reader by the constructor.  If pushFile is called
  // before <stdin> is read from, it should not be used for reading,
  // so we remove it.  This case happens e.g. when running the code:
  //
  // SoFile * f = new SoFile;
  // f->name = "nonexistant.iv";
  //
  // The name-field has a callback function that calls
  // File::readNamedFile, which calls pushFile. No other files than
  // the pushed file should end up on the stack.
  if (this->filestack.getLength() == 1 &&
      this->filestack[0]->ivFilePointer() == coin_get_stdin() &&
      !PRIVATE(this)->usingstdin) {

    this->closeFile();
  }

  SbString fullname;
  FILE * fp = this->findFile(filename, fullname);
  if (fp) {
    SoInput_Reader * reader = SoInput_Reader::createReader(fp, fullname);
    SoInput_FileInfo * newfile =
      new SoInput_FileInfo(reader, PRIVATE(this)->copied_references);
    this->filestack.insert(newfile, 0);

    SoInput::addDirectoryFirst(SoInput::getPathname(fullname).getString());
    return true;
  }

  SoReadError::post(this, fullname.getString());

  return false;
}

/*!
  Removes all files from the internal stack. Any files opened by
  openFile() or pushFile() will also be closed, but not the files
  coming from setFilePointer() -- which are the responsibility of the
  caller.

  You usually don't need to call this method explicitly, as it will
  automatically be triggered by the SoInput destructor to close any
  open files when the SoInput instance goes out of scope.

  \sa setFilePointer(), openFile(), pushFile()
*/
void
SoInput::closeFile(void)
{
  // Remove all entries, including the default <stdin>.
  while (this->filestack.getLength() > 0) {
    if (!this->fromBuffer() && (this->getCurFile() != coin_get_stdin())) {
      SbString s = SoInput::getPathname(this->getTopOfStack()->ivFilename());
      if (s.getLength()) SoInput::removeDirectory(s.getString());
    }
    delete this->getTopOfStack();
    this->filestack.remove(0);
  }
}

/*!
  Checks to see if the current file is a valid file which can be read
  by the Coin library.

  When reading files through e.g. SoDB::readAll(), this is
  automatically checked for you, so application code should usually
  not need to use this method.
*/
bool
SoInput::isValidFile(void)
{
  if (this->getTopOfStack() == nullptr) return false;

  // Abstract away the stupidity of providing both isValidFile() and
  // isValidBuffer().
  if (this->getTopOfStack()->isMemBuffer()) return this->isValidBuffer();

  float ver = this->getIVVersion();
  if (ver != 0.0f) return true;
  return false;
}

/*!
  Returns \c true if the current text buffer represents a valid
  iv-file which can be read by the Coin library.

  When reading files through e.g. SoDB::readAll(), this is
  automatically checked for you, so application code should usually
  not need to use this method.
*/
bool
SoInput::isValidBuffer(void)
{
  if (this->getTopOfStack() == nullptr) return false;

  // Abstract away the stupidity of providing both isValidFile() and
  // isValidBuffer().
  if (!this->getTopOfStack()->isMemBuffer()) return this->isValidFile();

  // Set "validate header" argument to false, as memory buffers should
  // be possible to read even with no header.
  return this->checkHeader(false);
}

/*!
  Returns file pointer of the file on top of the input stack. If the
  "file" is actually a memory buffer, returns \c nullptr.

  Important note: do \e not use this method when the Coin library has
  been compiled as an MSWindows DLL, as passing FILE* instances back
  or forth to DLLs is dangerous and will most likely cause a
  crash. This is an intrinsic limitation for MSWindows DLLs.

  \sa getCurFileName()
*/
FILE *
SoInput::getCurFile(void) const
{
  SoInput_FileInfo * fi = this->getTopOfStack();
  assert(fi);
  return fi->isMemBuffer() ? nullptr : fi->ivFilePointer();
}

/*!
  Returns the name of the file on top of the input stack. \c nullptr will
  be returned if the toplevel "file" is a memory buffer.

  \sa getCurFile()
*/
const char *
SoInput::getCurFileName(void) const
{
  SoInput_FileInfo * fi = this->getTopOfStack();
  assert(fi);
  return fi->isMemBuffer() ? nullptr : fi->ivFilename().getString();
}

/*!
  Sets up the input stream for reading from the strings pointed to by a
  nullptr-terminated array of string pointers.  It is intended for reading
  memory-inlined scene graphs.

  The rationale for this function is that there is a compiler portability
  problem with compiling large, static string buffers.  Some compilers
  have fixed max-lengths on this feature, just over 1KB, which obviously
  becomes a problem real fast.  This method lets you specify the buffer
  as an array of smaller string buffers, typically one string for each
  line in the Inventor file.

  \code
  SoNode *
  makeSceneGraph(void) {
    static const char * inlinescenegraph[] = {
      "#Inventor V2.1 ascii\n",
      "\n",
      "Separator {\n",
      "  Cube {\n",
      "  }\n",
      "}\n",
      nullptr
    };
    SoInput in;
    if ( !in.setStringArray(inlinescenegraph) ) return nullptr;
    return SoDB::readAll(&in);
  }
  \endcode

  \sa setBuffer()

  \COIN_FUNCTION_EXTENSION

  \since Coin 2.1
*/
void
SoInput::setStringArray(const char * strings[])
{
  size_t bufsize = 0;
  size_t i;
  for (i = bufsize = 0; strings[i] != nullptr; i++ )
    bufsize += strlen(strings[i]);
  char * buf = new char [bufsize + 1];
  for (i = bufsize = 0; strings[i] != nullptr; i++ ) {
    const size_t len = strlen(strings[i]);
    memcpy(buf+bufsize, strings[i], len);
    bufsize += len;
  }
  this->setBuffer(buf, bufsize);
  SoInput_FileInfo * info = this->getTopOfStack();
  assert(info);
  info->setDeleteBuffer(buf);
}

/*!
  Sets up the input stream for reading from a memory buffer. Closes all
  open files in the file stack first.

  In the original SGI Inventor API this method was designed as "char * bufpointer",
  Coin followed this until Coin 3, but changed the signature to const from Coin 4.0.
*/
void
SoInput::setBuffer(const void * bufpointer, size_t bufsize)
{
  this->closeFile();
  SoInput_Reader * reader = nullptr;

  unsigned char * header = (unsigned char*) bufpointer;
  if ((bufsize >= 2) && (header[0] == 0x1f) && (header[1] == 0x8b)) {
    if (cc_zlibglue_available()) {
      reader = new SoInput_GZMemBufferReader(bufpointer, bufsize);
    }
    else {
      SoDebugError::postWarning("SoInput::setBuffer",
                                "Buffer seems to be in gzip format, but zlib support is "
                                "not available.");
    }
  }
  if (reader == nullptr) {
    reader = new SoInput_MemBufferReader(bufpointer, bufsize);
  }
  SoInput_FileInfo * newfile =
    new SoInput_FileInfo(reader, PRIVATE(this)->copied_references);
  this->filestack.insert(newfile, 0);
}

/*!
  Returns number of bytes read so far from the current file or memory
  buffer.
  You can only use this method while you're reading the file.
  When the reading has finished, the current file is popped off the
  file stack, and a more or less random number is returned. You
  should use the stat() system call to find the size of a file (or
  fseek() and ftell()).
*/
size_t
SoInput::getNumBytesRead(void) const
{
  SoInput_FileInfo * fi = this->getTopOfStack();
  assert(fi);
  return fi->getNumBytesParsedSoFar();
}

/*!
  Returns header of current file.
*/
SbString
SoInput::getHeader(void)
{
  (void) this->checkHeader();
  SoInput_FileInfo * fi = this->getTopOfStack();

  return fi ? fi->ivHeader() : SbString("");
}

/*!
  Returns the library version needed to read a file with the given header.
  If the header of the current file is not valid, this method returns
  \a 0.0f.
*/
float
SoInput::getIVVersion(void)
{
  if ( (this->filestack.getLength()==0) || !this->checkHeader()) { return 0.0f; }
  return this->getTopOfStack()->ivVersion();
}

/*!
  Returns \c true if the current file is in binary format.
*/
bool
SoInput::isBinary(void)
{
  (void) this->checkHeader(); // Make sure the file header has been
                              // read. checkHeader calls
                              // SoInput_FileInfo::readHeader

  SoInput_FileInfo * fi = this->getTopOfStack();
  assert(fi);
  return fi->isBinary();
}

/*!
  Get next character in current stream. Returns \c false on end of file.

  \sa read()
*/
bool
SoInput::get(char & c)
{
  // It is essential that this method pops on EOF, because this
  // feature is used in e.g SoFile::readNamedFile
  SoInput_FileInfo * fi = PRIVATE(this)->getTopOfStackPopOnEOF();
  return (this->checkHeader() && // Strip off file header, if any.
          fi->get(c));
}

/*!
  Returns next character in current stream. Don't use this method -- SoInput
  is supposed to \e hide whether or not you are reading from file or memory.
  It is only included for compatibility reasons.
*/
bool
SoInput::getASCIIBuffer(char & c)
{
  return this->get(c);
}

/*!
  Returns next character in current stream. Don't use this method -- SoInput
  is supposed to \e hide whether or not you are reading from file or memory.
  It is only included for compatibility reasons.
*/
bool
SoInput::getASCIIFile(char & c)
{
  return this->get(c);
}

/*!
  Reads an  unsigned integer in hexidecimal format from the current stream.
  Note that no error checking is done to see if it actually is a hex
  format value.

  A number in hexadecimal format must have the "0x" prefix.

  Returns \c false if end of file is encountered.
*/
bool
SoInput::readHex(uint32_t & l)
{
  assert(!this->isBinary());

  // FIXME: this is a tremendously stupid function. Should obsolete it.

  // FIXME: no checking for array overwriting. Dangerous. 19990625 mortene.
  char buffer[1024];
  char * bufptr = buffer;

  if (this->readChar(bufptr, '0')) {
    if (this->readChar(bufptr + 1, 'x')) {
      bufptr += 2 + this->readHexDigits(bufptr + 2);
    }
  }

  *bufptr = '\0';
  sscanf(buffer, "%x", &l);
  return true;
}

/*!
  Skips whitespace and reads next character in input stream.
  Returns \c false if encountering end of file.
*/
bool
SoInput::read(char & c)
{
  SoInput_FileInfo * fi = PRIVATE(this)->getTopOfStackPopOnEOF();

  if (!this->checkHeader()) return false;

  return (fi->skipWhiteSpace() && fi->get(c));
}

/*!
  Reads next character in input stream, returns \c false if encountering
  end of file. If \a skip is \c true, skips whitespace before reading a
  character.
*/
bool
SoInput::read(char & c, bool skip)
{
  SoInput_FileInfo * fi = PRIVATE(this)->getTopOfStackPopOnEOF();

  if (!this->checkHeader()) return false;

  bool ok = true;
  if (skip) ok = fi->skipWhiteSpace();
  return (ok && fi->get(c));
}


/*!
  Skips whitespace and extracts string. A string can be placed
  within quotes, in which case we will return all characters between
  the quotes (including spaces, tabs, newlines, etc). A quote character
  (i.e. ``"'') can also be part of the string, but must then be preceded
  by a ``\'' character.

  A string not contained in quotes is terminated by the first following
  whitespace character.

  Returns \c false upon encountering end of file (EOF) before the
  string is fully parsed, or any other error. Note: This function does
  not return \c false when encountering all EOFs. When multiple files
  are on the stack and a string is being parsed (the parser has found
  one or more valid characters) and EOF is encountered, the parsing
  stops and the read string along with \c true is returned. The next
  time the read method is called, the stack is popped and a read
  string from the next file is returned - not always returning \c
  false between the files (though it might on certain
  circumstances). The solution to this is to test for end of file
  after each successive read operation.
*/
bool
SoInput::read(SbString & s)
{
  SoInput_FileInfo * fi = PRIVATE(this)->getTopOfStackPopOnEOF();

  if (!this->checkHeader()) return false;

  ////////////////////
  // Binary read
  ////////////////////

  if (fi->isBinary()) { // Checkheader has already been called
    // This is just a guess at a sensible limit, to help detect
    // corrupted files and to avoid those leading to attempts at
    // allocating gigabytes of memory.
    const unsigned int MAXSTRLEN = 10 * 1024;

    unsigned int slen;
    if (!this->read(slen)) { return false; }
    if (slen == 0) { s = ""; return true; }

    // Inventor V1.0 binary files seems to have 0xffffffff as some
    // sort of end-of-file tag, so handle that case.
    if (slen == 0xffffffff) {
      char c;
      (void)fi->get(c); // sets the EOF flag as a side-effect
      if (fi->isEndOfFile()) { return false; }
      fi->putBack(c);
    }

    // Sanity check
    if (slen > MAXSTRLEN) {
      SoReadError::post(this, "String too long (%u characters) -- "
                        "file probably corrupt.", slen);
      return false;
    }

    char buffer[MAXSTRLEN+4+1];
    if (!fi->getChunkOfBytes((unsigned char *)buffer, ((slen+3)/4)*4)) { return false; }
    buffer[slen] = '\0';
    s = buffer;
    return true;
  }


  ////////////////////
  // ASCII read
  ////////////////////

  if (!fi->skipWhiteSpace()) return false;

  s.makeEmpty();

  char c;
  if (!fi->get(c)) return false;

  bool quoted = (c == '\"');
  if (!quoted) fi->putBack(c);

  // FIXME: the following code could have been much cleaner if we'd
  // used SbString::operator+=(char) for each char instead of going
  // through the tmp buffer. SbString::operator+=(char) uses strlen()
  // for each invocation, though, so that'd give us rather nasty
  // algorithm-time on the SoInput::read(SbString) operations. The
  // correct fix is to first avoid the strlen() invocations in
  // SbString, then simplify this code. 20020506 mortene.

  char bufStore[256];
  int bytesLeft;
  unsigned int totallen = 0;
  do {
    char * buf = bufStore;
    bytesLeft = sizeof(bufStore) - 1;

    while (bytesLeft > 0) {
      if (!fi->get(*buf)) {
        if ((totallen == 0) || quoted) {
          if (quoted) {
            SoReadError::post(this, "Missing terminating quote-character (\")");
          }
          return false;
        }
        // This method does not return false on all EOFs. When having
        // started reading the last String, and encountering EOF at
        // the end of this, it simply stops reading and returns
        // true. The next time, it just pops the stack and starts
        // reading on the next file. Not returning false.
        break;
      }

      if (quoted) {
        if (*buf == '\"') break;

        if (*buf == '\\') {
          if (!fi->get(c)) return false;
          if (c == '\"') {
            // VRML 2.0 allows for strings to contain literal
            // newlines, Inventor/VRML V1.0 doesn't.  This also checks
            // for a special case in Inventor/VRML 1.0 files where the
            // last two characters of a line containing a quoted
            // string is \". In this case, the backslash should be
            // considered literal and the quote should terminate the
            // string.
            if (!this->isFileVRML2() && fi->get(c)) {
              fi->putBack(c);
              if (c == '\n') fi->putBack('\"');
              else *buf = '\"';
            }
            else {
              *buf = c;
            }
          }
          // In VRML V2.0, backslashes must be quoted.
          else if (c != '\\' || !this->isFileVRML2()) {
            fi->putBack(c);
          }
        }
      }
      // Unquoted strings end on first encountered whitespace
      else if (fi->isSpace(*buf)) {
        fi->putBack(*buf);
        break;
      }

      buf++; totallen++;
      bytesLeft--;
    }

    *buf = '\0';
    s += bufStore;

  } while (bytesLeft == 0);

  return true;
}

/*!
  Read a name from the current stream and place it in \a n.

  This method should not be used specifically to read all instances of
  SbName. The semantics of the interface is such that it is designed
  to handle identifier tokens from the Inventor / VRML file
  formats. I.e. cases where node names, node types and field names are
  to be read. If your goal is to read the value of a SbName field that
  is not any of the above, and at least when the string might be
  quoted, then you should most likely use SoInput::read(SbString &)
  instead.

  If \a validIdent is \c true the name needs to be a valid identifier
  (no reserved characters etc), while \a validIdent equal to \c false
  means we'll just read characters for the next word until we hit
  whitespace or one of the "{"/"}" delimiters.

  Returns \c false on encountering end of file before a full name has
  been read -- if \a validIdent is also \c false. If \a validIdent is
  passed as \c true, the return value will be \c false if no valid name
  was found, but \e not necessarily on end of file.
*/
bool
SoInput::read(SbName & n, bool validIdent)
{
  SoInput_FileInfo * fi = PRIVATE(this)->getTopOfStackPopOnEOF();
  if (!this->checkHeader()) return false;

  const enum CodePath { INVENTOR, VRML1, VRML2 } codepath =
    fi->isFileVRML2() ? VRML2 : (fi->isFileVRML1() ? VRML1 : INVENTOR);

  // Binary format.
  if (fi->isBinary()) { // Checkheader has already been called
    SbString s;
    if (!this->read(s)) return false;

    n = s;
    const int strlength = s.getLength();

    switch (codepath) {
    case INVENTOR:
      if (validIdent && strlength > 0) {
        if (!SoInputP::isNameStartChar(s[0], validIdent)) return false;
        for (int i = 1; i < strlength; i++)
          if (!SoInputP::isNameChar(s[i], validIdent)) return false;
      }
      break;
    case VRML1:
      if (validIdent && strlength > 0) {
        if (!SoInputP::isNameStartCharVRML1(s[0], validIdent)) return false;
        for (int i = 1; i < strlength; i++)
          if (!SoInputP::isNameCharVRML1(s[i], validIdent)) return false;
      }
    case VRML2:
      if (validIdent && strlength > 0) {
        if (!SoInputP::isNameStartCharVRML2(s[0], validIdent)) return false;
        for (int i = 1; i < strlength; i++)
          if (!SoInputP::isNameCharVRML2(s[i], validIdent)) return false;
      }
    default:
      assert(!"invalid code path");
      break;
    }

    return true;
  }
  // ASCII format.
  else {
    if (!fi->skipWhiteSpace()) return false;

    SbString s;
    char buf[256];
    char * b = buf;
    char c;
    bool gotchar = false;

    switch (codepath) {
    case INVENTOR:
      if ((gotchar = fi->get(c)) && SoInputP::isNameStartChar(c, validIdent)) {
        *b++ = c;
        while ((gotchar = fi->get(c)) && SoInputP::isNameChar(c, validIdent)) {
          *b++ = c;
          if (b - buf == 255) {
            *b = '\0';
            s += buf;
            b = buf;
          }
        }
      }
      break;
    case VRML1:
      if ((gotchar = fi->get(c)) && SoInputP::isNameStartCharVRML1(c, validIdent)) {
        *b++ = c;
        while ((gotchar = fi->get(c)) && SoInputP::isNameCharVRML1(c, validIdent)) {
          *b++ = c;
          if (b - buf == 255) {
            *b = '\0';
            s += buf;
            b = buf;
          }
        }
      }
      break;
    case VRML2:
      if ((gotchar = fi->get(c)) && SoInputP::isNameStartCharVRML2(c, validIdent)) {
        *b++ = c;
        while ((gotchar = fi->get(c)) && SoInputP::isNameCharVRML2(c, validIdent)) {
          *b++ = c;
          if (b - buf == 255) {
            *b = '\0';
            s += buf;
            b = buf;
          }
        }
      }
      break;
    default:
      assert(!"invalid code path");
      break;
    }
    // This behavior is pretty silly, but this is how it is supposed
    // to work, apparently -- _not_ returning false upon end-of-file.
    if (gotchar) fi->putBack(c);

    *b = '\0';
    s += buf;
    n = SbName(s);

#if 0 // debug
    SoDebugError::postInfo("SoInput::read",
                           "string read: ``%s''", s.getString());
#endif // debug

    if (s.getLength() == 0) return false;
  }

  return true;
}

// FIXME: should we maybe do bounds-testing on the read-in data
// to warn if the data doesn't fit in the storage type?
// std::numeric_limits<type>::max() ought to be all the information
// needed.  20070520 larsa
#define READ_NUM(reader, readType, num, type) \
  SoInput_FileInfo * fi = this->getTopOfStack(); \
  assert(fi); \
  if (!fi->skipWhiteSpace()) return false; \
  readType _tmp; \
  if (!fi->reader(_tmp)) return false; \
  num = (type) _tmp;

#define READ_INTEGER(num, type) \
READ_NUM(readInteger, int32_t, num, type)

#define READ_UNSIGNED_INTEGER(num, type) \
READ_NUM(readUnsignedInteger, uint32_t, num, type)

#define READ_REAL(num, type) \
READ_NUM(readReal, double, num, type)

/*!
  Read integer from current file or buffer position and place it in \a i.
  Returns \c false if we hit end of file prematurely.
 */
bool
SoInput::read(int & i)
{
  SoInput_FileInfo * fi = this->getTopOfStack();
  assert(fi);

  if (fi->isBinary()) { // Assume checkheader has been called
    int32_t tmp;
    if (!this->readBinaryArray(&tmp, 1)) return false;
    i = tmp;
    return true;
  }
  else {
    READ_INTEGER(i, int);
  }
  return true;
}

/*!
  Read unsigned integer from current file or buffer position and place
  it in \a i. Returns \c false if we hit end of file prematurely.
 */
bool
SoInput::read(unsigned int & i)
{
  SoInput_FileInfo * fi = this->getTopOfStack();
  assert(fi);

  if (fi->isBinary()) { // Assume checkheader has been called
    int32_t tmp;
    if (!this->readBinaryArray(&tmp, 1)) return false;
    i = tmp;
    return true;
  }
  else {
    READ_UNSIGNED_INTEGER(i, unsigned int);
  }
  return true;
}

/*!
  Read short integer from current file or buffer position and place
  it in \a s. Returns \c false if we hit end of file prematurely.
 */
bool
SoInput::read(short & s)
{
  SoInput_FileInfo * fi = this->getTopOfStack();
  assert(fi);

  if (fi->isBinary()) { // Assume checkheader has been called
    int32_t tmp;
    if (!this->readBinaryArray(&tmp, 1)) return false;
    s = (short) tmp;
    return true;
  }
  else {
    READ_INTEGER(s, short);
  }
  return true;
}

/*!
  Read unsigned short integer from current file or buffer position and place
  it in \a s. Returns \c false if we hit end of file prematurely.
 */
bool
SoInput::read(unsigned short & s)
{
  SoInput_FileInfo * fi = this->getTopOfStack();
  assert(fi);

  if (fi->isBinary()) { // Assume checkheader has been called
    int32_t tmp;
    if (!this->readBinaryArray(&tmp, 1)) return false;
    s = (unsigned short) tmp;
    return true;
  }
  else {
    READ_UNSIGNED_INTEGER(s, unsigned short);
  }
  return true;
}

/*!
  Read signed byte integer from current file or buffer position and place
  it in \a b. Returns \c false if we hit end of file prematurely.
 */
bool
SoInput::readByte(int8_t & b)
{
  SoInput_FileInfo * fi = this->getTopOfStack();
  assert(fi);

  if (fi->isBinary()) { // Assume checkheader has been called
    int32_t tmp;
    if (!this->readBinaryArray(&tmp, 1)) return false;
    b = (int8_t) tmp;
    return true;
  }
  else {
    READ_INTEGER(b, int8_t);
  }
  return true;
}

/*!
  Read unsigned byte integer from current file or buffer position and place
  it in \a b. Returns \c false if we hit end of file prematurely.
 */
bool
SoInput::readByte(uint8_t & b)
{
  SoInput_FileInfo * fi = this->getTopOfStack();
  assert(fi);

  if (fi->isBinary()) { // Assume checkheader has been called
    int32_t tmp;
    if (!this->readBinaryArray(&tmp, 1)) return false;
    b = (uint8_t) tmp;
    return true;
  }
  else {
    READ_UNSIGNED_INTEGER(b, uint8_t);
  }
  return true;
}

/*!
  Read float value from current file or buffer position and place
  it in \a f. Returns \c false if we hit end of file prematurely.
 */
bool
SoInput::read(float & f)
{
  SoInput_FileInfo * fi = this->getTopOfStack();
  assert(fi);

  if (fi->isBinary()) { // Assume checkheader has been called
    if (!this->readBinaryArray(&f, 1)) { return false; }
  }
  else {
    READ_REAL(f, float);
  }
  if (!coin_finite((double)f)) {
    SoReadError::post(this,
                      "Detected non-valid floating point number, replacing "
                      "with 0.0f");
    f = 0.0f;
    // We don't return false, thereby allowing the read process to
    // continue, as a convenience for the application programmer.
  }
  return true;
}

/*!
  Read double value from current file or buffer position and place
  it in \a d. Returns \c false if we hit end of file prematurely.
 */
bool
SoInput::read(double & d)
{
  SoInput_FileInfo * fi = this->getTopOfStack();
  assert(fi);

  if (fi->isBinary()) { // Assume checkheader has been called
    if (!this->readBinaryArray(&d, 1)) { return false; }
  }
  else {
    READ_REAL(d, double);
  }
  if (!coin_finite(d)) {
    SoReadError::post(this,
                      "Detected non-valid floating point number, replacing "
                      "with 0.0");
    d = 0.0;
    // We don't return false, thereby allowing the read process to
    // continue, as a convenience for the application programmer.
  }
  return true;
}

#ifdef __CYGWIN__

bool
SoInput::read(long int & i)
{
  static_assert(sizeof(long int) == sizeof(int));
  return read(reinterpret_cast<int &>(i));
}

bool
SoInput::read(unsigned long int & i)
{
  static_assert(sizeof(unsigned long int) == sizeof(unsigned int));
  return read(reinterpret_cast<unsigned int &>(i));
}
#endif //__CYGWIN

/*!
  Reads \a length characters from the current stream into \a c. Returns
  \c false if end of file is encountered before the given number of bytes
  could be read.
 */
bool
SoInput::readBinaryArray(unsigned char * c, int length)
{
  return (this->checkHeader() &&
          this->getTopOfStack()->getChunkOfBytes(c, length));
}

/*!
  Reads \a length 32-bit integers from the current stream into \a l. Returns
  \c false if end of file is encountered before the given number of integers
  could be read.
 */
bool
SoInput::readBinaryArray(int32_t * l, int length)
{
  assert(length > 0);
  if (!this->checkHeader() ||
      !this->getTopOfStack()->getChunkOfBytes((unsigned char *)l,
                                              length * sizeof(int32_t)))
    return false;

  this->convertInt32Array((char *)l, l, length);
  return true;
}

/*!
  Reads \a length floats from the current stream into \a f. Returns
  \c false if end of file is encountered before the given number of
  binary float values could be read.
 */
bool
SoInput::readBinaryArray(float * f, int length)
{
  assert(length > 0);
  if (!this->checkHeader() ||
      !this->getTopOfStack()->getChunkOfBytes((unsigned char *)f,
                                              length * sizeof(float)))
    return false;

  this->convertFloatArray((char *)f, f, length);

  return true;
}

/*!
  Reads \a length double floats from the current stream into \a d.
  Returns \c false if end of file is encountered before the given number of
  binary double float values could be read.
 */
bool
SoInput::readBinaryArray(double * d, int length)
{
  assert(length > 0);
  if (!this->checkHeader() ||
      !this->getTopOfStack()->getChunkOfBytes((unsigned char *)d,
                                              length * sizeof(double)))
    return false;

  this->convertDoubleArray((char *)d, d, length);
  return true;
}

/*!
  Returns \c true if we are at the end of the current stream, otherwise
  \c false.
 */
bool
SoInput::eof(void) const
{
  SoInput_FileInfo * fi = this->getTopOfStack();
  if (!fi) return true;
  return fi->isEndOfFile();
}

/*!
  Places the current line number location and file name in a string
  which is to be used in the output upon read errors.
 */
void
SoInput::getLocationString(SbString & str) const
{
  if (this->filestack.getLength() == 0) {
    str = "";
    return;
  }

  const char * filename = this->getCurFileName();

  // FIXME: hack to cast away constness. Ugly. 19990713 mortene.
  if (((SoInput *)this)->isBinary()) {
    str.sprintf("\tOccurred at position %lu in binary file %s",
                (unsigned long int) this->getTopOfStack()->getNumBytesParsedSoFar(),
                filename ? filename : "<memory>");
  }
  else {
    str.sprintf("\tOccurred at line %3d in %s",
                this->getTopOfStack()->lineNr(),
                filename ? filename : "<memory>");
  }
}

/*!
  Insert character \a c in stream at the current position.
 */
void
SoInput::putBack(const char c)
{
  SoInput_FileInfo * fi = this->getTopOfStack();
  assert(fi);
  fi->putBack(c);
}

/*!
  Insert string \a str in stream at the current position.
 */
void
SoInput::putBack(const char * str)
{
  SoInput_FileInfo * fi = this->getTopOfStack();
  assert(fi);
  fi->putBack(str);
}

/*!
  Adds a name<->SoBase mapping to our dictionary.

  \sa findReference(), removeReference()
 */
void
SoInput::addReference(const SbName & name, SoBase * base,
                      bool addToGlobalDict)
{
  SoProto * proto = this->getCurrentProto();
  if (proto) {
    proto->addReference(name, base);
  }
  else {
    this->getTopOfStack()->addReference(name, base, addToGlobalDict);
  }
}

/*!
  Removes a name<->SoBase mapping from our dictionary.

  \sa findReference(), addReference()
 */
void
SoInput::removeReference(const SbName & name)
{
  SoProto * proto = this->getCurrentProto();
  if (proto) {
    proto->removeReference(name);
  }
  else {
    this->getTopOfStack()->removeReference(name);
  }
}

/*!
  Finds an SoBase derived object which has been mapped to \a name earlier
  during the import process.

  The Coin library will by default only search through the previously
  loaded nodes from the \e same file. By setting the environment
  variable \c COIN_SOINPUT_SEARCH_GLOBAL_DICT to "1", you can force
  the import process to search for USE-references through \e all nodes
  that has been loaded or otherwise instantiated.

  \sa addReference(), removeReference()
 */
SoBase *
SoInput::findReference(const SbName & name) const
{
  SoProto * proto = this->getCurrentProto();
  if (proto) {
    return proto->findReference(name);
  }
  else {
    SoBase * base = this->getTopOfStack()->findReference(name);
    if (base) return base;

    static int COIN_SOINPUT_SEARCH_GLOBAL_DICT = -1;
    if (COIN_SOINPUT_SEARCH_GLOBAL_DICT < 0) {
      const char * env = coin_getenv("COIN_SOINPUT_SEARCH_GLOBAL_DICT");
      if (env) COIN_SOINPUT_SEARCH_GLOBAL_DICT = atoi(env);
      else COIN_SOINPUT_SEARCH_GLOBAL_DICT = 0;
    }

    if (COIN_SOINPUT_SEARCH_GLOBAL_DICT) {
      return SoBase::getNamedBase(name, SoNode::getClassTypeId());
    }
  }
  return nullptr;
}

/*!
  Add a directory to the search list. The added directory will be searched
  before any of the other directories in the list.

  \sa addDirectoryLast(), addEnvDirectoriesFirst(), addEnvDirectoriesLast()
  \sa removeDirectory(), clearDirectories()
 */
void
SoInput::addDirectoryFirst(const char * dirName)
{
  SoInput::addDirectoryIdx(0, dirName);
}

/*!
  Add a directory to the search list. The added directory will be searched
  after any of the other directories in the list.

  \sa addDirectoryFirst(), addEnvDirectoriesFirst(), addEnvDirectoriesLast()
  \sa removeDirectory(), clearDirectories()
 */
void
SoInput::addDirectoryLast(const char * dirName)
{
  SoInput::addDirectoryIdx(-1, dirName);
}

/*!
  \COININTERNAL

  Add a directory to the search list at the specified index value. An index
  of -1 means append.
 */
void
SoInput::addDirectoryIdx(const int idx, const char * dirName)
{
  assert(idx > -2);
  if (strlen(dirName) == 0) return; // Don't add empty dirs
  SbStringList * dirs = SoInput::dirsearchlist;

  if (soinput_tls) {
    soinput_tls_data * data = (soinput_tls_data *)soinput_tls->get();
    if (data->instancecount) { dirs = data->searchlist; }
  }

  assert(idx <= dirs->getLength());
  // NB: note that it _should_ be possible to append/insert the same
  // directory name multiple times, as this is an easy way of
  // "stacking" names when doing recursive SoDB::readAll() calls or
  // using SoInput::pushFile(). So don't try to "fix" or change this
  // aspect of adding entries to the directory search list. --mortene

  SbString * ns = new SbString(dirName);
  if (idx == -1) dirs->append(ns);
  else if (idx != -1) dirs->insert(ns, idx);
}

/*!
  Add in front of the list all directories in the environment
  variable \a envVarName. The \a separator string should contain all
  characters to be interpreted as separators in the environment variable
  string list. The default separators are ':', tab and space.

  \sa addDirectoryFirst(), addDirectoryLast()
  \sa addEnvDirectoriesLast()
  \sa removeDirectory(), clearDirectories()
 */
void
SoInput::addEnvDirectoriesFirst(const char * envVarName,
                                const char * separator)
{
  SoInput::addEnvDirectoriesIdx(0, envVarName, separator);
}

/*!
  Add at the end of the list all directories in the environment
  variable \a envVarName. The \a separator string should contain all
  characters to be interpreted as separators in the environment variable
  string list. The default separators are ':', tab and space.

  \sa addDirectoryFirst(), addDirectoryLast()
  \sa addEnvDirectoriesFirst()
  \sa removeDirectory(), clearDirectories()
 */
void
SoInput::addEnvDirectoriesLast(const char * envVarName,
                               const char * separator)
{
  SoInput::addEnvDirectoriesIdx(SoInput::dirsearchlist->getLength(),
                                envVarName,
                                separator);
}

/*!
  \COININTERNAL

  Add environment variable directory list, starting at index \a startidx.
 */
void
SoInput::addEnvDirectoriesIdx(int startidx,
                              const char * envVarName,
                              const char * separator)
{
  const char * p = coin_getenv(envVarName);
  if (!p) {
#if COIN_DEBUG
    SoDebugError::postWarning("SoInput::addEnvDirectoriesFirst",
                              "Tried to add directories from nonexistent "
                              "environment variable '%s'.",
                              envVarName);
#endif // COIN_DEBUG
    return;
  }

  // FIXME: the following "tokenizer" code could perhaps be factored
  // out and moved to e.g. SbStringList? 20030820 mortene.

  if (separator == nullptr) {
    // use default separators if nullptr
    separator = ":\t ";
  }
  const char * end = p + strlen(p);

  while (p < end) {
    const char * hit = strpbrk(p, separator);

    if (hit && hit != p) {
      const ptrdiff_t offset = hit - p;
      SbString add = SbString(p).getSubString(0, (int)(offset - 1));
      SoInput::addDirectoryIdx(startidx++, add.getString());
      p = hit+1;
    }
    else if (hit) { // more than one separator in a row
      p++;
    }
    else { // last entry
      SoInput::addDirectoryIdx(startidx, p);
      p = end;
    }
  }
}

/*!
  Remove the given directory from the directory search list.

  The search list is scanned from last to first for the directory name,
  so directories can easily be "stacked" by pushing with addDirectoryLast()
  and then removed with this method.

  \sa addDirectoryFirst(), addDirectoryLast()
  \sa addEnvDirectoriesFirst(), addEnvDirectoriesLast()
  \sa clearDirectories()
 */
void
SoInput::removeDirectory(const char * dirName)
{
  SbStringList * dirs = SoInput::dirsearchlist;

  if (soinput_tls) {
    soinput_tls_data * data = (soinput_tls_data *)soinput_tls->get();
    if (data->instancecount) { dirs = data->searchlist; }
  }

  // dirsearchlist might be null if user called SoDB::cleanup()
  if (dirs) {
    int idx = dirs->getLength() - 1;
    for (; idx >= 0; idx--) {
      if (*((*dirs)[idx]) == dirName) break;
    }

    if (idx >=0) {
      delete (*dirs)[idx]; // Dealloc SbString object
      dirs->remove(idx);
    }
#if COIN_DEBUG
    else {
      SoDebugError::postWarning("SoInput::removeDirectory",
                                "Tried to remove nonexistent directory '%s'"
                                " in directory search list.", dirName);
    }
#endif // COIN_DEBUG
  }
}

/*!
  Remove all entries from the directory search list.

  \sa addDirectoryFirst(), addDirectoryLast()
  \sa addEnvDirectoriesFirst(), addEnvDirectoriesLast()
  \sa removeDirectory()
 */
void
SoInput::clearDirectories(void)
{
  while (SoInput::dirsearchlist->getLength() > 0) {
    delete (*SoInput::dirsearchlist)[0];
    SoInput::dirsearchlist->remove(0);
  }
}

/*!
  Returns the list of directories which'll be searched upon loading
  Coin and VRML format files. Directory searches will be done whenever
  any external references appears in a file, for instance to texture images.
 */
const SbStringList &
SoInput::getDirectories(void)
{
  if (soinput_tls) {
    soinput_tls_data * data = (soinput_tls_data *)soinput_tls->get();
    if (data->instancecount) { return *data->searchlist; }
  }

  return *SoInput::dirsearchlist;
}

/*!
  Initialize static variables in class. Called from SoDB::init().
*/
void
SoInput::init(void)
{
  coin_atexit((coin_atexit_f *)SoInput::clean, CC_ATEXIT_NORMAL);

  // This will catch multiple initClass() calls (unless there's a
  // removeDirectories() in between them, which is unlikely to happen
  // inadvertently).
  assert(SoInput::dirsearchlist == nullptr);

  SoInput::dirsearchlist = new SbStringList;
  SoInput::addDirectoryFirst(".");

  soinput_tls = new SbStorage(sizeof(soinput_tls_data),
                              soinput_construct_tls_data,
                              soinput_destruct_tls_data);
}

// Clean out static variables in class (to aid in searching for memory
// leaks).
void
SoInput::clean(void)
{
  SoInput::clearDirectories();
  delete SoInput::dirsearchlist;
  SoInput::dirsearchlist = nullptr;

  delete soinput_tls; soinput_tls = nullptr;
}

/*!
  Finds and returns the part of the given filename which is the
  directory path name.
 */
SbString
SoInput::getPathname(const char * const filename)
{
  // FIXME: this method would be a prime candidate for the planned
  // SbFile class of filesystem abstractions to hide system
  // differences. 20011021 mortene.

#ifdef HAVE__SPLITPATH

  char drive[_MAX_DRIVE];
  char dir[_MAX_DIR];

  _splitpath(filename, drive, dir, nullptr, nullptr);

  SbString s(drive);
  s += dir;
  return s;

#else // HAVE__SPLITPATH

  const char * ptr = strrchr(filename, '/');
  if (ptr == nullptr) return SbString("");

  SbString s = filename;
  return s.getSubString(0, ptr-filename);

#endif // !HAVE__SPLITPATH
}

/*!
  Finds and returns the part of the given filename which is the
  directory path name.
 */
SbString
SoInput::getPathname(const SbString & s)
{
  return SoInput::getPathname(s.getString());
}

/*!
  Finds and returns the part of the given filename which is the base name
  (i.e. the filename without the leading directory path).
 */
SbString
SoInput::getBasename(const char * const filename)
{
  // FIXME: this method would be a prime candidate for the planned
  // SbFile class of filesystem abstractions to hide system
  // differences. 20011021 mortene.

#ifdef HAVE__SPLITPATH

  char fname[_MAX_FNAME];
  char ext[_MAX_EXT];

  _splitpath(filename, nullptr, nullptr, fname, ext);

  SbString s(fname);
  s += ext;
  return s;

#else // UNIX systems

  const char * ptr = strrchr(filename, '/');
  if (ptr == nullptr) return SbString(filename);

  SbString s = filename;
  return s.getSubString(ptr - filename + 1, -1);

#endif // UNIX
}

/*!
  Finds and returns the part of the given filename which is the base name
  (i.e. the filename without the leading directory path).
 */
SbString
SoInput::getBasename(const SbString & s)
{
  return SoInput::getBasename(s.getString());
}

// internal method used for testing if a file exists
static bool
test_filename(const SbString & filename)
{
  FILE * fp = fopen(filename.getString(), "rb");
#if COIN_DEBUG && 0 // flip 1<->0 to turn texture search trace on or off
  SoDebugError::postInfo("test_filename", "file search: %s (%s)\n",
                         filename.getString(), fp ? "hit" : "miss");
#endif // !COIN_DEBUG

  if (fp != nullptr) {
    fclose(fp);
    return true;
  }
  return false;
}

/*!
  Given a \a basename for a file and an array of \a directories to
  search, returns the full name of the file found.

  In addition to looking at the root of each directory in \a
  directories, all \a subdirectories is also searched for each item in
  \a directories.

  If no file matching \a basename could be found in any of the
  directories, returns an empty string.

  This method is a Coin extension, not part of the original Inventor
  API.
*/
SbString
SoInput::searchForFile(const SbString & basename,
                       const SbStringList & directories,
                       const SbStringList & subdirectories)
{
  int i;

  if (test_filename(basename)) return basename;

  SbString fullname = basename;

  bool trypath = true;
  const char * strptr = basename.getString();
  const char * lastunixdelim = strrchr(strptr, '/');
  const char * lastdosdelim = strrchr(strptr, '\\');
  if (!lastdosdelim) {
    lastdosdelim = strrchr(strptr, ':');
    if (lastdosdelim) trypath = false;
  }
  const char * lastdelim = SbMax(lastunixdelim, lastdosdelim);

  if (lastdelim && trypath) {
    SbString tmpstring;
    for (i = 0; i < directories.getLength(); i++) {
      SbString dirname(directories[i]->getString());
      int dirlen = dirname.getLength();

      if (dirlen > 0 &&
          dirname[dirlen-1] != '/' &&
          dirname[dirlen-1] != '\\' &&
          dirname[dirlen-1] != ':') {
        dirname += "/";
      }

      tmpstring.sprintf("%s%s", dirname.getString(),
                        fullname.getString());
      if (test_filename(tmpstring)) return tmpstring;
    }
  }

  const ptrdiff_t offset = lastdelim - strptr;
  SbString base = lastdelim ?
    basename.getSubString((int)(offset + 1), -1) :
    basename;

  for (i = 0; i < directories.getLength(); i++) {
    SbString dirname(directories[i]->getString());
    int dirlen = dirname.getLength();

    if (dirlen > 0 &&
        dirname[dirlen-1] != '/' &&
        dirname[dirlen-1] != '\\' &&
        dirname[dirlen-1] != ':') {
      dirname += "/";
    }
    fullname.sprintf("%s%s", dirname.getString(),
                     base.getString());
    if (test_filename(fullname)) return fullname;
    for (int j = 0; j < subdirectories.getLength(); j++) {
      fullname.sprintf("%s%s/%s", dirname.getString(),
                       subdirectories[j]->getString(),
                       base.getString());
      if (test_filename(fullname)) return fullname;
    }
  }
  // none found
  return SbString("");
}


/*!
  Changes the file format version number for the stream at the top of the
  stack.
 */
void
SoInput::setIVVersion(float version)
{
  SoInput_FileInfo * fi = this->getTopOfStack();
  assert(fi);
  fi->setIvVersion(version);
}

/*!
  This function has been obsoleted in Coin.
*/
void
SoInput::initFile(FILE * /* newFP */, const char * /* fileName */,
                  SbString * /* fullName */,
                  bool /* openedHere */, SbDict * /* refDict */)
{
  COIN_OBSOLETED();
}

/*!
  Returns \c true if the current stream has had it's header parsed.
  If it hasn't, this method will attempt to read the header and returns
  \c true if it could be done.

  If \a bValidateBufferHeader is \c true, the returned flag will also
  be \c false if the file stream header was not of a supported file
  format type.
*/
bool
SoInput::checkHeader(bool bValidateBufferHeader)
{
  SoInput_FileInfo * fi = this->getTopOfStack();
  if (!fi) {
    SoDebugError::post("SoInput::checkHeader", "no files on the stack");
    return false;
  }

  // Make a note if reading is attempted on <stdin>. By marking if
  // <stdin> is being read from or not, we have a pretty good way of
  // telling if the user want to use <stdin> to read from or not when
  // a new file is pushed on the stack.
  if (this->filestack.getLength() == 1 &&
      fi->ivFilePointer() == coin_get_stdin() &&
      !PRIVATE(this)->usingstdin) {

    PRIVATE(this)->usingstdin = true;
  }

  return fi->readHeader(this) && (!bValidateBufferHeader || fi->ivVersion() != 0.0f);
}

/*!
  Returns \c true if the current input stream is fetching data from a
  memory buffer, or \c false if the input is from a file.
*/
bool
SoInput::fromBuffer(void) const
{
  SoInput_FileInfo * fi = this->getTopOfStack();
  assert(fi);
  return fi->isMemBuffer() ? true : false;
}

/*!
  Move file pointer past whitespace in the current file or buffer.
  Returns \c false if end of file is encountered.
 */
bool
SoInput::skipWhiteSpace(void)
{
  // FIXME: pop file on EOF? don't think so, but please let me
  // know if I'm wrong. jornskaa 20040702
  return (this->checkHeader() && this->getTopOfStack()->skipWhiteSpace());
}

/*!
  Pop the topmost file off the stack. Returns \c false if there was no
  files on the stack to pop. A file is only popped when there is more
  than one file on the stack.

  \sa pushFile(), openFile(), closeFile()
 */
bool
SoInput::popFile(void)
{
  if (this->filestack.getLength() == 0) return false;

  SoInput_FileInfo * topofstack = this->getTopOfStack();

  // connect routes before applying post callbacks
  topofstack->connectRoutes(this);

  // unreference Proto definitions
  topofstack->unrefProtos();

  // apply post callback, even if we're not going to pop
  topofstack->applyPostCallback(this);
  // If only one file is on the stack, don't pop it
  if (this->filestack.getLength() == 1) return false;

  if (topofstack->ivFilePointer()) {
    const char * filename = topofstack->ivFilename().getString();
    SbString path = SoInput::getPathname(filename);
    if (path.getLength()) SoInput::removeDirectory(path.getString());
  }
  delete topofstack;
  this->filestack.remove(0);
  return true;
}

/*!
  This function has been obsoleted in Coin.
 */
size_t
SoInput::freeBytesInBuf(void) const
{
  COIN_OBSOLETED();
  return 0;
}

/*!
  Reads 32-bit signed integer value from the current stream. Returns
  \c false if we hit end of file prematurely.
 */
bool
SoInput::readInteger(int32_t & l)
{
  SoInput_FileInfo * fi = PRIVATE(this)->getTopOfStackPopOnEOF();
  if (!fi) return false;
  return fi->readInteger(l);
}

/*!
  Reads 32-bit unsigned integer value from the current stream. Returns
  \c false if we hit end of file prematurely.
 */
bool
SoInput::readUnsignedInteger(uint32_t & l)
{
  SoInput_FileInfo * fi = PRIVATE(this)->getTopOfStackPopOnEOF();
  if (!fi) return false;
  return fi->readUnsignedInteger(l);
}

/*!
  Reads a double-precision floating point value from the current stream.
  Returns \c false if we hit end of file prematurely or if no valid string
  representing a value could be read.
 */
bool
SoInput::readReal(double & d)
{
  SoInput_FileInfo * fi = PRIVATE(this)->getTopOfStackPopOnEOF();
  if (!fi) return false;
  return fi->readReal(d);
}

/*!
  Reads a set of bytes from the stream making up an unsigned integer and
  puts them at \a str.

  Returns \c false if no string representing an unsigned integer could be
  read.
 */
bool
SoInput::readUnsignedIntegerString(char * str)
{
  SoInput_FileInfo * fi = PRIVATE(this)->getTopOfStackPopOnEOF();
  if (!fi) return false;
  return fi->readUnsignedIntegerString(str);
}

/*!
  Read decimal base digits from the current input stream into \a str and
  returns the number of characters read.
 */
int
SoInput::readDigits(char * str)
{
  SoInput_FileInfo * fi = PRIVATE(this)->getTopOfStackPopOnEOF();
  if (!fi) return false;
  return fi->readDigits(str);
}

/*!
  Read hexadecimal base digits from the current input stream into \a str and
  returns the number of characters read.
 */
int
SoInput::readHexDigits(char * str)
{
  SoInput_FileInfo * fi = PRIVATE(this)->getTopOfStackPopOnEOF();
  if (!fi) return false;
  return fi->readHexDigits(str);
}

/*!
  Reads the next character in stream and compares it to \a charToRead.
  Returns \c 1 on success, \c 0 on failure. Failure may come from either
  end of file, or from the next character in the stream being different
  than \a charToRead.
 */
int
SoInput::readChar(char * s, char charToRead)
{
  SoInput_FileInfo * fi = PRIVATE(this)->getTopOfStackPopOnEOF();
  if (!fi) return false;
  return fi->readChar(s, charToRead);
}

/*!
  This function has been obsoleted in Coin.
 */
bool
SoInput::makeRoomInBuf(size_t /* nBytes */)
{
  COIN_OBSOLETED();
  return false;
}

/*!
  Convert the bytes at \a from (which must be a short integer in network
  format (i.e. most significant byte first)) to a short integer in native
  format which is put at the \a s pointer.
 */
void
SoInput::convertShort(char * from, short * s)
{
  *s = (short) (coin_ntoh_uint16(*((uint16_t*)from)));
}

/*!
  Convert the bytes at \a from (which must be a 32-bit integer in network
  format (i.e. most significant byte first)) to a 32-bit integer in native
  format which is put at the \a l pointer.
 */
void
SoInput::convertInt32(char * from, int32_t * l)
{
  *l = (int32_t) (coin_ntoh_uint32(*((uint32_t*)from)));
}

/*!
  Convert the bytes at \a from (which must be a single-precision floating
  point number in network format) to a single-precision floating point
  number in native format which is put at the \a f pointer.
 */
void
SoInput::convertFloat(char * from, float * f)
{
  *f = coin_ntoh_float_bytes(from);
}

/*!
  Convert the bytes at \a from (which must be a double-precision floating
  point number in network format) to a double-precision floating point
  number in native format which is put at the \a d pointer.
 */
void
SoInput::convertDouble(char * from, double * d)
{
  *d = coin_ntoh_double_bytes(from);
}

/*!
  Convert a block of short numbers in network format to native format.

  \sa convertShort()
 */
void
SoInput::convertShortArray(char * from, short * to, int len)
{
  for (int i=0; i < len; i++) {
    this->convertShort(from, to);
    from += sizeof(short);
    to++;
  }
}

/*!
  Convert a block of 32-bit integer numbers in network format to native format.

  \sa convertInt32()
 */
void
SoInput::convertInt32Array(char * from, int32_t * to, int len)
{
  for (int i=0; i < len; i++) {
    this->convertInt32(from, to);
    from += sizeof(int32_t);
    to++;
  }
}

/*!
  Convert a block of single-precision floating point numbers in
  network format to native format.

  \sa convertFloat()
 */
void
SoInput::convertFloatArray(char * from, float * to, int len)
{
  for (int i=0; i < len; i++) {
    this->convertFloat(from, to);
    from += sizeof(float);
    to++;
  }
}

/*!
  Convert a block of double-precision floating point numbers in
  network format to native format.

  \sa convertDouble()
 */
void
SoInput::convertDoubleArray(char * from, double * to, int len)
{
  for (int i=0; i < len; i++) {
    this->convertDouble(from, to);
    from += sizeof(double);
    to++;
  }
}

/*!
  Returns \c true if current file is a VRML V1.0 file.

  \COIN_FUNCTION_EXTENSION
*/
bool
SoInput::isFileVRML1(void)
{
  (void) this->checkHeader();
  SoInput_FileInfo * fi = this->getTopOfStack();
  if (fi) return fi->isFileVRML1();
  return false;
}

/*!
  Returns \c true if current file is a VRML 2 / VRML97 file.

  \COIN_FUNCTION_EXTENSION
*/
bool
SoInput::isFileVRML2(void)
{
  (void) this->checkHeader();
  SoInput_FileInfo * fi = this->getTopOfStack();
  if (fi) return fi->isFileVRML2();
  return false;
}

/*!
  This function has been obsoleted in Coin.
*/
void
SoInput::resetFilePointer(FILE * /* fptr */)
{
  COIN_OBSOLETED();
}

/*!
  This function is part of the TGS Inventor API, but is not
  implemented in Coin.
*/
bool
SoInput::isFileURL(const char * /* url */)
{
  COIN_STUB();
  return false;
}

/*!
  This function is part of the TGS Inventor API, but is not
  implemented in Coin.
*/
char *
SoInput::URLToFile(char * /* out_buf */, const char * /* in_buf */)
{
  COIN_STUB();
  return nullptr;
}

/*!
  This function is part of the TGS Inventor API, but is not
  implemented in Coin.
*/
bool
SoInput::IsURL(const char * /* c_strng */)
{
  COIN_STUB();
  return false;
}

/*!
  Set up the directory search path directly with the list of directories
  in \a dirs. Note that "." should be part of the directory list if you
  want to handle files specified by a relative path.
 */
void
SoInput::setDirectories(SbStringList * dirs)
{
  // Dealloc SbString objects
  for (int i=0; i < SoInput::dirsearchlist->getLength(); i++)
    delete (*SoInput::dirsearchlist)[i];

  (*SoInput::dirsearchlist) = *dirs;
}

/*!
  \COININTERNAL

  Return the currently active stream.
*/
#if 0
SoInput_FileInfo *
SoInput::getTopOfStack(void) const
{
  if (this->filestack.getLength() == 0) {
    SoDebugError::post("SoInput::getTopOfStack", "no files in stack");
    return nullptr;
  }
  return this->filestack[0];
}
#endif

/*!
  Scan through the include directories in order and try to find a file
  with the given name in any one of them. If file is found, put the
  full name with complete path from current directory of process into
  \a fullname, open the file and return the file pointer.

  If the file could either not be found or not opened for reading,
  return \c nullptr.

  Important note: do \e not use this method when the Coin library has
  been compiled as an MSWindows DLL, as passing FILE* instances back
  or forth to DLLs is dangerous and will most likely cause a
  crash. This is an intrinsic limitation for MSWindows DLLs.
 */
FILE *
SoInput::findFile(const char * basename, SbString & fullname)
{
  // This function has an undocumented feature in Coin: upon error, an
  // error message with the reason why it could not be opened will be
  // placed in the \a fullname argument. Keep this undocumented, to
  // avoid incompatibility problems with SGI/TGS Inventor for app
  // programmers.  -mortene.

  fullname = "";

  if (strlen(basename) < 1) {
    SoDebugError::post("SoInput::findFile", "Was asked to find a file with no name!");
    return nullptr;
  }

  const char * env = coin_getenv("COIN_DEBUG_SOINPUT_FINDFILE");
  const bool DEBUG_FILE_SEARCHING = env && (atoi(env) > 0);
  if (DEBUG_FILE_SEARCHING) {
    cc_string str;
    cc_string_construct(&str);
    bool ok = coin_getcwd(&str);
    if (!ok) {
      SoDebugError::post("SoInput::findFile",
                         "Couldn't get current working directory: %s",
                         cc_string_get_text(&str));
    }
    else {
      SoDebugError::postInfo("SoInput::findFile",
                             "Current working directory: '%s'",
                             cc_string_get_text(&str));
    }
    cc_string_clean(&str);
  }

  SbStringList sl = SoInput::getDirectories();

  // Make sure we try from cwd first.
  SbString relativepath("");
  sl.insert(&relativepath, 0);

  FILE * fp = nullptr;
  for (int diridx = 0; diridx < sl.getLength(); diridx++) {
    SbString n = * sl[diridx];
    const int namelen = n.getLength();
    if ((namelen && n[namelen - 1] != '/' && n[namelen - 1] != '\\') &&
        (basename[0] != '/' && basename[0] != '\\')) {
      n += "/";
    }
    n += basename;

    struct stat buf;
    if ((stat(n.getString(), &buf) == 0) && !S_ISDIR(buf.st_mode)) {
      fp = fopen(n.getString(), "rb");
      if (fp != nullptr) {
        if (DEBUG_FILE_SEARCHING) {
          SoDebugError::postInfo("SoInput::findFile", "successfully fopened '%s'", n.getString());
        }
        fullname = n;
        return fp;
      }
      else {
        const bool same = strcmp(basename, n.getString()) == 0;
        SbString s;
        if (!same) { s.sprintf(" as '%s'", n.getString()); }

        fullname.sprintf("Found '%s'%s, but was unable to open it: '%s'",
                         basename, s.getString(), strerror(errno));
      }
    }
  }

  // If file was not found, list all directories where we looked for
  // it.
  bool foundbutcouldntopen = fullname.getLength() > 0;
  if (!foundbutcouldntopen) {
    cc_string str;
    cc_string_construct(&str);
    bool ok = coin_getcwd(&str);
    fullname.sprintf("Could not find '%s' in any of the "
                     "following directories (from cwd '%s'):",
                     basename, ok ? cc_string_get_text(&str) : "<unknown>");
    cc_string_clean(&str);

    for (int diridx = 0; diridx < sl.getLength(); diridx++) {
      fullname += "\n\t'";
      fullname += * sl[diridx];
      fullname += "'";
    }
  }

  return nullptr;
}

#undef READ_NUM
#undef READ_INTEGER
#undef READ_UNSIGNED_INTEGER
#undef READ_REAL
#undef PRIVATE
