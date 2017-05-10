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

#include <Inventor/navigation/SoScXMLRotateTarget.h>

/*!
  \class SoScXMLRotateTarget SoScXMLRotateTarget.h Inventor/scxml/SoScXMLRotateTarget.h
  \brief Navigation system event target for rotating operations.

  \ingroup navigation
*/

#
#include <cassert>
#include <cmath>
#include <cfloat>

#include <boost/scoped_ptr.hpp>
#include <boost/intrusive_ptr.hpp>

#include <Inventor/SbViewVolume.h>
#include <Inventor/SbRotation.h>
#include <Inventor/SbPlane.h>
#include <Inventor/SbLine.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/nodes/SoOrthographicCamera.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/fields/SoSFVec3d.h>
#include <Inventor/SbTime.h>
#include <Inventor/SbVec2f.h>
#include <Inventor/SbViewVolume.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/projectors/SbSphereSheetProjector.h>
#include <Inventor/nodes/SoCamera.h>
#include <Inventor/scxml/ScXMLEvent.h>
#include <Inventor/scxml/SoScXMLStateMachine.h>
#include <Inventor/C/tidbits.h>
#include <Inventor/navigation/SoScXMLNavigation.h>
#include <Inventor/navigation/SoScXMLFlightControlTarget.h>
#include <Inventor/navigation/SoScXMLDollyTarget.h>

#include "scxml/SbStringConvert.h"
#include "SbBasicP.h"
#include "coindefs.h"
#include "base/coinString.h"

namespace {

class RotateData : public SoScXMLNavigationTarget::Data {
// sendspinstart
// should be persistent over rotations, but individually settable per session
// or better; per event origin point
public:
  RotateData(void) {
    this->projector.reset(new SbSphereSheetProjector);
    SbViewVolume volume;
    volume.ortho(-1, 1, -1, 1, -1, 1);
    this->projector->setViewVolume(volume);
    this->logsize = 0;
  }

  SbVec2f downposn;
  boost::intrusive_ptr<SoCamera> cameraclone;
  boost::scoped_ptr<SbSphereSheetProjector> projector;

  struct log {
    SbVec2f posn;
    SbTime time;
  } mouselog[3];
  int logsize;
};

static SoScXMLNavigationTarget::Data * NewRotateData(void) { return new RotateData; }

} // namespace

class SoScXMLRotateTarget::PImpl {
public:
  // received
  static SbName BEGIN;
  static SbName UPDATE;
  static SbName END;
  static SbName SET_FOCAL_POINT;
  // sent
  static SbName TRIGGER_SPIN;
};

SbName SoScXMLRotateTarget::PImpl::BEGIN;
SbName SoScXMLRotateTarget::PImpl::UPDATE;
SbName SoScXMLRotateTarget::PImpl::END;
SbName SoScXMLRotateTarget::PImpl::SET_FOCAL_POINT;
SbName SoScXMLRotateTarget::PImpl::TRIGGER_SPIN;

// *************************************************************************

#define PRIVATE

SCXML_OBJECT_SOURCE(SoScXMLRotateTarget);

void
SoScXMLRotateTarget::initClass(void)
{
  SCXML_OBJECT_INIT_CLASS(SoScXMLRotateTarget, SoScXMLNavigationTarget, "SoScXMLNavigationTarget");

#define EVENT_PREFIX COIN_NAVIGATION_ROTATE_TARGET_EVENT_PREFIX
  PImpl::BEGIN            = SbName(EVENT_PREFIX ".BEGIN");
  PImpl::UPDATE           = SbName(EVENT_PREFIX ".UPDATE");
  PImpl::END              = SbName(EVENT_PREFIX ".END");
  PImpl::SET_FOCAL_POINT  = SbName(EVENT_PREFIX ".SET_FOCAL_POINT");
  PImpl::TRIGGER_SPIN     = SbName(EVENT_PREFIX ".TRIGGER_SPIN");
#undef EVENT_PREFIX
}

void
SoScXMLRotateTarget::cleanClass(void)
{
  SoScXMLRotateTarget::classTypeId = SoType::badType();
}

SoScXMLRotateTarget * SoScXMLRotateTarget::theSingleton = nullptr;

SoScXMLRotateTarget *
SoScXMLRotateTarget::constructSingleton(void)
{
  assert(SoScXMLRotateTarget::theSingleton == nullptr);
  SoScXMLRotateTarget::theSingleton =
    static_cast<SoScXMLRotateTarget *>(SoScXMLRotateTarget::classTypeId.createInstance());
  return SoScXMLRotateTarget::theSingleton;
}

void
SoScXMLRotateTarget::destructSingleton(void)
{
  assert(SoScXMLRotateTarget::theSingleton != nullptr);
  delete SoScXMLRotateTarget::theSingleton;
  SoScXMLRotateTarget::theSingleton = nullptr;
}

SoScXMLRotateTarget *
SoScXMLRotateTarget::singleton(void)
{
  assert(SoScXMLRotateTarget::theSingleton != nullptr);
  return SoScXMLRotateTarget::theSingleton;
}

const SbName &
SoScXMLRotateTarget::BEGIN(void)
{
  return PImpl::BEGIN;
}

const SbName &
SoScXMLRotateTarget::UPDATE(void)
{
  return PImpl::UPDATE;
}

const SbName &
SoScXMLRotateTarget::END(void)
{
  return PImpl::END;
}

const SbName &
SoScXMLRotateTarget::SET_FOCAL_POINT(void)
{
  return PImpl::SET_FOCAL_POINT;
}

const SbName &
SoScXMLRotateTarget::TRIGGER_SPIN(void)
{
  return PImpl::TRIGGER_SPIN;
}

SoScXMLRotateTarget::SoScXMLRotateTarget(void)
{
  this->setEventTargetType(SOSCXML_NAVIGATION_TARGETTYPE);
  this->setEventTargetName("Rotate");
}

SoScXMLRotateTarget::~SoScXMLRotateTarget(void)
{
}


bool
SoScXMLRotateTarget::processOneEvent(const ScXMLEvent * event)
{
  assert(event);

  SbName sessionid = this->getSessionId(event);
  if (sessionid == SbName::empty()) { return false; }

  const SbName & eventname = event->getEventName();

  if (eventname == BEGIN()) {
    RotateData * data =
      static_cast<RotateData *>(this->getSessionData(sessionid, NewRotateData));
    assert(data);

    SoScXMLStateMachine * statemachine = inherited::getSoStateMachine(event, sessionid);
    if (!statemachine) { return false; }

    if (!inherited::getEventSbVec2f(event, "mouseposition", data->downposn)) {
      return false;
    }

    data->mouselog[0].posn = data->downposn;
    data->mouselog[0].time = SbTime::getTimeOfDay();
    data->logsize = 1;

    SoCamera * camera = inherited::getActiveCamera(event, sessionid);
    if unlikely (!camera) { return false; }

    // store current camera position
    data->cameraclone = static_cast<SoCamera *>(camera->copy());

    return true;
  }

  else if (eventname == UPDATE()) {
    RotateData * data = static_cast<RotateData *>(this->getSessionData(sessionid, NewRotateData));
    assert(data);

    SoScXMLStateMachine * statemachine = inherited::getSoStateMachine(event, sessionid);
    if (!statemachine) { return false; }

    SoCamera * camera = statemachine->getActiveCamera();
    if unlikely (!camera) {
      SoDebugError::post("SoScXMLRotateTarget::processOneEvent",
                         "while processing %s: no current camera",
                         eventname.getString());
      return false;
    }

    assert(data->cameraclone.get());
    if unlikely (camera->getTypeId() != data->cameraclone->getTypeId()) {
      SoDebugError::post("SoScXMLRotateTarget::processOneEvent",
                         "while processing %s: camera type was changed",
                         eventname.getString());
      return false;
    }

    // get mouse position
    SbVec2f currentpos;
    if (!inherited::getEventSbVec2f(event, "mouseposition", currentpos)) {
      return false;
    }

    // update mouse log
    data->mouselog[2].time = data->mouselog[1].time;
    data->mouselog[2].posn = data->mouselog[1].posn;
    data->mouselog[1].time = data->mouselog[0].time;
    data->mouselog[1].posn = data->mouselog[0].posn;
    data->mouselog[0].posn = currentpos;
    data->mouselog[0].time = SbTime::getTimeOfDay();
    data->logsize += 1;

    // find rotation
    data->projector->project(data->downposn);
    SbRotation rot;
    data->projector->projectAndGetRotation(currentpos, rot);
    rot.invert();

    // restore camera to original position and do full reorientation
    camera->copyFieldValues(data->cameraclone.get());
    reorientCamera(camera, rot);

    return true;
  }

  else if (eventname == END()) {
    bool triggerspincheck = false; // default if not set
    inherited::getEventbool(event, "triggerspin", triggerspincheck, false);

    if (triggerspincheck) {
      RotateData * data = static_cast<RotateData *>(this->getSessionData(sessionid, NewRotateData));
      assert(data);

      bool triggerspin = false;
      SbRotation spinrotation;

      if (data->logsize > 2) {
        SbTime stoptime = (SbTime::getTimeOfDay() - data->mouselog[0].time);
        if (stoptime.getValue() < 0.100) {
          SbVec3f from = data->projector->project(data->mouselog[2].posn);
          SbVec3f to = data->projector->project(data->mouselog[0].posn);
          spinrotation = data->projector->getRotation(from, to);

          SbTime delta = data->mouselog[0].time - data->mouselog[2].time;
          double deltatime = delta.getValue();
          spinrotation.invert();
          spinrotation.scaleAngle(float(0.200 / deltatime));

          SbVec3f axis;
          float radians;
          spinrotation.getValue(axis, radians);
          if ((radians > 0.01f) && (deltatime < 0.300)) {
            triggerspin = true;
          }
        }
      }

      if (triggerspin) {
        SoScXMLStateMachine * statemachine = inherited::getSoStateMachine(event, sessionid);
        if (!statemachine) { return false; }
        SbString rotationstr;
        rotationstr = SbStringConvert::toString(spinrotation);

        SbString updatetimestr;
        double fromtime = SbTime::getTimeOfDay().getValue();
        updatetimestr = SbStringConvert::toString(fromtime);

        ScXMLEvent event;
        event.setEventName(TRIGGER_SPIN());
        event.setAssociation("rotation", rotationstr.getString());
        event.setAssociation("from", updatetimestr.getString());
        statemachine->queueEvent(&event);
      }
    }

    this->freeSessionData(sessionid);
    return true;
  }

  else if (eventname == SET_FOCAL_POINT()) {
    // _sessionid
    // worldspace {SbVec3f}
    // [upvector] {SbVec3f}
    // [focaldistance] {double}

    SoScXMLStateMachine * statemachine = inherited::getSoStateMachine(event, sessionid);
    if (!statemachine) { return false; }

    SoCamera * camera = inherited::getActiveCamera(event, sessionid);
    if unlikely (!camera) { return false; }

    SbVec3f worldspace(0.0f, 0.0f, 0.0f);
    if (event->getAssociation("worldspace")) {
      SbString valuestr = event->getAssociation("worldspace");
      if (SbStringConvert::typeOf(valuestr) == SbStringConvert::SBVEC3F) {
        if (!inherited::getEventSbVec3f(event, "worldspace", worldspace)) {
          return false;
        }
      } else {
        return false;
      }
    }

    SbVec3f upvector(0.0f, 0.0f, 0.0f);
    bool useupvector = inherited::getEventSbVec3f(event, "upvector", upvector, false);

    double focaldistance = 0.0f;
    bool usefocaldistance = inherited::getEventDouble(event, "focaldistance", focaldistance, false);

    if (!useupvector) {
      // camera->pointAt() will turn the model away from its current up vector, so we
      // try to preserve the existing up vector here instead of calling the up-vector-less
      // version.
      camera->orientation.getValue().multVec(SbVec3f(0.0f, 1.0f, 0.0f), upvector);
      useupvector = true;
    }

    if (!useupvector) {
      SoScXMLRotateTarget::setFocalPoint(camera, worldspace);
    } else {
      SoScXMLRotateTarget::setFocalPoint(camera, worldspace, upvector);
    }
    if (usefocaldistance) {
      SoScXMLDollyTarget::jump(camera, float(focaldistance));
    }

    return true;
  }

  else {
    SoDebugError::post("SoScXMLRotateTarget::processOneEvent",
                       "processing %s: unknown event",
                       eventname.getString());
    return false;
  }

  return true;
}

// Rotate camera around its focal point.
void
SoScXMLRotateTarget::reorientCamera(SoCamera * camera, const SbRotation & rot)
{
  if (camera == nullptr) return;

  // Find global coordinates of focal point.
  SbVec3f direction;
  camera->orientation.getValue().multVec(SbVec3f(0, 0, -1), direction);
  SbVec3f focalpoint = camera->position.getValue() +
    camera->focalDistance.getValue() * direction;

  // Set new orientation value by accumulating the new rotation.
  camera->orientation = rot * camera->orientation.getValue();

  // Reposition camera so we are still pointing at the same old focal point.
  camera->orientation.getValue().multVec(SbVec3f(0, 0, -1), direction);
  camera->position = focalpoint - camera->focalDistance.getValue() * direction;

  // some custom code to support UTMCamera cameras
  static const SoType utmcamtype(SoType::fromName("UTMCamera"));
  if (utmcamtype != SoType::badType() && camera->isOfType(utmcamtype)) {
    SbVec3d offset;
    offset.setValue(camera->position.getValue());
    SoSFVec3d * utmpositionfield = coin_assert_cast<SoSFVec3d *>(camera->getField("utmposition"));
    utmpositionfield->setValue(utmpositionfield->getValue()+offset);
    camera->position.setValue(0.0f, 0.0f, 0.0f);
  }
}

void
SoScXMLRotateTarget::setFocalPoint(SoCamera * camera, const SbVec3f & worldspace)
{
  camera->pointAt(worldspace);
}

void
SoScXMLRotateTarget::setFocalPoint(SoCamera * camera, const SbVec3f & worldspace, const SbVec3f & upvector)
{
  camera->pointAt(worldspace, upvector);
  SoScXMLFlightControlTarget::resetRoll(camera, upvector);
}

#undef PRIVATE
