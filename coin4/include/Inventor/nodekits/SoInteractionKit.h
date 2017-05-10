#ifndef COIN_SOINTERACTIONKIT_H
#define COIN_SOINTERACTIONKIT_H

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

#include <Inventor/nodekits/SoSubKit.h>
#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/fields/SoSFEnum.h>

#ifdef COIN_INTERNAL
class SoFieldSensor;
#else // !COIN_INTERNAL
// Include this header file for better Open Inventor compatibility.
#include <Inventor/sensors/SoFieldSensor.h>
#endif // !COIN_INTERNAL

class SoSensor;
class SoSeparator;

class COIN_DLL_API SoInteractionKit : public SoBaseKit {
  typedef SoBaseKit inherited;

  SO_KIT_HEADER(SoInteractionKit);

  SO_KIT_CATALOG_ENTRY_HEADER(geomSeparator);
  SO_KIT_CATALOG_ENTRY_HEADER(topSeparator);

public:
  SoSFEnum renderCaching;
  SoSFEnum boundingBoxCaching;
  SoSFEnum renderCulling;
  SoSFEnum pickCulling;

public:
  SoInteractionKit(void);
  static void initClass(void);

  enum CacheEnabled { OFF, ON, AUTO };

  virtual bool setPartAsPath(const SbName &partname,
                               SoPath *path);
  virtual bool setPartAsDefault(const SbName &partname,
                                  SoNode *node,
                                  bool onlyifdefault = true);
  virtual bool setPartAsDefault(const SbName &partname,
                                  const SbName &nodename,
                                  bool onlyifdefault = true);
  bool isPathSurrogateInMySubgraph(const SoPath *path,
                                     SoPath *&pathToOwner,
                                     SbName  &surrogatename,
                                     SoPath *&surrogatepath,
                                     bool fillargs = true);
  bool isPathSurrogateInMySubgraph(const SoPath *path);
  static void setSwitchValue(SoNode *node, const int newVal);
  virtual bool setPart(const SbName & partname, SoNode * from);

protected:
  virtual ~SoInteractionKit();
  virtual void copyContents(const SoFieldContainer *fromFC,
                            bool copyConnections);

  virtual bool setPart(const int partNum, SoNode *node);
  virtual bool readInstance(SoInput *in, unsigned short flags);
  static void readDefaultParts(const char *fileName,
                               const char defaultBuffer[],
                               int defBufSize);
  virtual bool setAnyPartAsDefault(const SbName &partname,
                                     SoNode *node,
                                     bool anypart = true,
                                     bool onlyifdefault = true);
  virtual bool setAnyPartAsDefault(const SbName &partname,
                                     const SbName &nodename,
                                     bool anypart = true,
                                     bool onlyifdefault = true);
  bool setAnySurrogatePath(const SbName &name,
                             SoPath *path,
                             bool leafcheck = false,
                             bool publiccheck = false);
  virtual bool setUpConnections(bool onoff, bool doitalways = false);
  virtual void setDefaultOnNonWritingFields();

  SoFieldSensor *fieldSensor;
  static void fieldSensorCB(void *, SoSensor *);
  SoSeparator *oldTopSep;

  void connectSeparatorFields( SoSeparator *dest, bool onOff );

private:
  class SoInteractionKitP * pimpl;
  friend class SoInteractionKitP;
};

#endif // !COIN_SOINTERACTIONKIT_H
