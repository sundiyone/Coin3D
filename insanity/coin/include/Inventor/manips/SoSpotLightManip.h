#ifndef COIN_SOSPOTLIGHTMANIP_H
#define COIN_SOSPOTLIGHTMANIP_H

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

#include <Inventor/nodes/SoSpotLight.h>
#include <Inventor/tools/SbLazyPimplPtr.h>

#ifndef COIN_INTERNAL
#include <Inventor/draggers/SoDragger.h>
#endif

class SoChildList;
class SoDragger;
class SoFieldSensor;
class SoPath;
class SoSensor;
class SoSpotLightManipP;

class COIN_DLL_API SoSpotLightManip : public SoSpotLight {
  typedef SoSpotLight inherited;

  SO_NODE_HEADER(SoSpotLightManip);

public:
  static void initClass(void);
  SoSpotLightManip(void);

  SoDragger * getDragger(void);
  bool replaceNode(SoPath * p);
  bool replaceManip(SoPath * p, SoSpotLight * newone) const;

  virtual void doAction(SoAction * action);
  virtual void callback(SoCallbackAction * action);
  virtual void GLRender(SoGLRenderAction * action);
  virtual void getBoundingBox(SoGetBoundingBoxAction * action);
  virtual void getMatrix(SoGetMatrixAction * action);
  virtual void handleEvent(SoHandleEventAction * action);
  virtual void pick(SoPickAction * action);
  virtual void search(SoSearchAction * action);

  virtual SoChildList * getChildren(void) const;

protected:
  virtual ~SoSpotLightManip(void);

  void setDragger(SoDragger * newdragger);

  virtual void copyContents(const SoFieldContainer * fromfc,
                            bool copyconnections);

  static void transferFieldValues(const SoSpotLight * from, SoSpotLight * to);
  static void valueChangedCB(void * f, SoDragger * d);
  static void fieldSensorCB(void * f, SoSensor * d);

  SoFieldSensor * locationFieldSensor;
  SoFieldSensor * directionFieldSensor;
  SoFieldSensor * angleFieldSensor;
  SoFieldSensor * colorFieldSensor;
  SoChildList * children;

private:
  void attachSensors(const bool onoff);

private:
  SbLazyPimplPtr<SoSpotLightManipP> pimpl;

  SoSpotLightManip(const SoSpotLightManip & rhs);
  SoSpotLightManip & operator = (const SoSpotLightManip & rhs);
}; // SoSpotLightManip

#endif // !COIN_SOSPOTLIGHTMANIP_H
