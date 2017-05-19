#ifndef COIN_SOFOREIGNFILEKIT_H
#define COIN_SOFOREIGNFILEKIT_H

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

#include <Inventor/SbBasic.h>

#include <Inventor/nodekits/SoSubKit.h>
#include <Inventor/nodekits/SoBaseKit.h>

typedef bool SoForeignFileIdentifyFunc(const char *);

class SoForeignFileKitP;

class COIN_DLL_API SoForeignFileKit : public SoBaseKit {
  typedef SoBaseKit inherited;

  SO_KIT_ABSTRACT_HEADER(SoForeignFileKit);
  SO_KIT_CATALOG_ENTRY_HEADER(topSeparator);

public:
  static void initClass(void);

  static bool isFileSupported(SoInput * in, bool exhaust = false);
  static bool isFileSupported(const char * filename, bool exhaust = false);

  static SoForeignFileKit * createForeignFileKit(SoInput * in, bool exhaust = false);
  static SoForeignFileKit * createForeignFileKit(const char * filename, bool exhaust = false);

  // foreign read support
  virtual bool canReadFile(const char * filename = nullptr) const;
  virtual bool readFile(const char * filename);
  // foreign write support
  virtual bool canWriteFile(const char * filename = nullptr) const;
  virtual bool writeFile(const char * filename);

  /*!
    Converts (if necessary) the internal representation of the foreign file to a pure Coin scenegraph.
    Returns the root node with a refcount of 0.
  */
  virtual class SoSeparator *convert() = 0;

protected:
  static void initClasses(void);

  SoForeignFileKit(void);
  virtual ~SoForeignFileKit(void);

  static bool registerFileExtension(SoType handler, SbName extension, SoForeignFileIdentifyFunc * identify);

private:
  SoForeignFileKitP * pimpl;

}; // SoForeignFileKit

#endif // !COIN_SOFOREIGNFILEKIT_H
