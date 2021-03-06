#ifndef COIN_SOHANDLEEVENTACTION_H
#define COIN_SOHANDLEEVENTACTION_H

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

#include <Inventor/actions/SoAction.h>
#include <Inventor/actions/SoSubAction.h>

class SbViewportRegion;
class SoEvent;
class SoPickedPoint;
class SoPickedPointList;

class SoHandleEventActionP;

class COIN_DLL_API SoHandleEventAction : public SoAction {
  typedef SoAction inherited;

  SO_ACTION_HEADER(SoHandleEventAction);

public:
  static void initClass(void);

  SoHandleEventAction(const SbViewportRegion & viewportregion);
  virtual ~SoHandleEventAction(void);

  void setViewportRegion(const SbViewportRegion & newregion);
  const SbViewportRegion & getViewportRegion(void) const;
  void setEvent(const SoEvent * ev);
  const SoEvent * getEvent(void) const;
  void setHandled(void);
  bool isHandled(void) const;
  void setGrabber(SoNode * node);
  void releaseGrabber(void);
  SoNode * getGrabber(void) const;
  void setPickRoot(SoNode * node);
  SoNode * getPickRoot(void) const;
  void setPickRadius(const float radiusinpixels);
  const SoPickedPoint * getPickedPoint(void);
  const SoPickedPointList & getPickedPointList(void);

protected:
  virtual void beginTraversal(SoNode * node);

private:
  SbPimplPtr<SoHandleEventActionP> pimpl;

  // NOT IMPLEMENTED:
  SoHandleEventAction(const SoHandleEventAction & rhs);
  SoHandleEventAction & operator = (const SoHandleEventAction & rhs);
}; // SoHandleEventAction

#ifndef COIN_INTERNAL
// For SGI / TGS Open Inventor compile-time compatibility.
#include <Inventor/actions/SoRayPickAction.h>
#endif // COIN_INTERNAL

#endif // !COIN_SOHANDLEEVENTACTION_H
