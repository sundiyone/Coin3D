#ifndef COIN_SOFOREIGNFILEKIT_H
#define COIN_SOFOREIGNFILEKIT_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) by Kongsberg Oil & Gas Technologies.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Kongsberg Oil & Gas Technologies
 *  about acquiring a Coin Professional Edition License.
 *
 *  See http://www.coin3d.org/ for more information.
 *
 *  Kongsberg Oil & Gas Technologies, Bygdoy Alle 5, 0257 Oslo, NORWAY.
 *  http://www.sim.no/  sales@sim.no  coin-support@coin3d.org
 *
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
