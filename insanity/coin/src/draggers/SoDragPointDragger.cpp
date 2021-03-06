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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif // HAVE_CONFIG_H

#ifdef HAVE_DRAGGERS

/*!
  \class SoDragPointDragger SoDragPointDragger.h Inventor/draggers/SoDragPointDragger.h
  \brief The SoDragPointDragger class provides mechanisms for moving a point in 3D.
  \ingroup draggers

  \DRAGGER_DEFAULT_SCREENSHOT

  <center>
  <img src="http://doc.coin3d.org/images/Coin/draggers/dragpoint.png">
  </center>

  This dragger is convenient to use when it is desirable that the
  end-user should interact with points by positioning them freely in
  3D space.

  The dragger consists of a part for 2D motion in a plane (like the
  SoTranslate2Dragger) and another part on the axis normal to the
  plane.

  While the dragger is inactive (ie the user is not currently grabbing
  and / or dragging it's parts), the CTRL keys on the keyboard can be
  used to switch the orientation of the 2D-plane part and the
  normal-axis part so the normal-axis part points along one of the
  other principal axes.  This is done by position the mouse pointer
  over the dragger geometry and pressing and releasing a CTRL key.
*/
// FIXME: Should include an URL-link to the default geometry-file?
// Plus a small usage example.  20010909 mortene.

#include <Inventor/draggers/SoDragPointDragger.h>

#include <cstring>

#include <Inventor/SbRotation.h>
#include <Inventor/SbVec3f.h>
#include <Inventor/draggers/SoTranslate1Dragger.h>
#include <Inventor/draggers/SoTranslate2Dragger.h>
#include <Inventor/events/SoKeyboardEvent.h>
#include <Inventor/nodes/SoRotation.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoTranslation.h>
#include <Inventor/sensors/SoFieldSensor.h>

#include <data/draggerDefaults/dragPointDragger.h>

#include "nodekits/SoSubKitP.h"
#include "SbBasicP.h"

/*!
  \var SoSFVec3f SoDragPointDragger::translation

  Continuously updated to contain the current translation from the
  dragger's local origo position.

  The application programmer applying this dragger in his code should
  connect the relevant node fields in the scene to this field to make
  it follow the dragger.
*/

/*!
  \var SoFieldSensor * SoDragPointDragger::fieldSensor
  \COININTERNAL
*/

class SoDragPointDraggerP {
public:
};

SO_KIT_SOURCE(SoDragPointDragger);

// Doc in superclass.
void
SoDragPointDragger::initClass(void)
{
  SO_KIT_INTERNAL_INIT_CLASS(SoDragPointDragger, SO_FROM_INVENTOR_1);
}

// FIXME: document which parts need to be present in the geometry
// scenegraph, and what role they play in the dragger. 20010913 mortene.
/*!
  \DRAGGER_CONSTRUCTOR

  \NODEKIT_PRE_DIAGRAM

  \verbatim
  CLASS SoDragPointDragger
  -->"this"
        "callbackList"
        "topSeparator"
           "motionMatrix"
  -->      "noRotSep"
  -->         "xTranslatorSwitch"
  -->            "xTranslator"
  -->         "xyTranslatorSwitch"
  -->            "xyTranslator"
  -->      "rotXSep"
  -->         "rotX"
  -->         "xzTranslatorSwitch"
  -->            "xzTranslator"
  -->      "rotYSep"
  -->         "rotY"
  -->         "zTranslatorSwitch"
  -->            "zTranslator"
  -->         "yzTranslatorSwitch"
  -->            "yzTranslator"
  -->      "rotZSep"
  -->         "rotZ"
  -->         "yTranslatorSwitch"
  -->            "yTranslator"
  -->      "xFeedbackSwitch"
  -->         "xFeedbackSep"
  -->            "xFeedbackTranslation"
  -->            "xFeedback"
  -->      "yFeedbackSwitch"
  -->         "yFeedbackSep"
  -->            "yFeedbackTranslation"
  -->            "yFeedback"
  -->      "zFeedbackSwitch"
  -->         "zFeedbackSep"
  -->            "zFeedbackTranslation"
  -->            "zFeedback"
  -->      "planeFeedbackSep"
  -->         "planeFeedbackTranslation"
  -->         "planeFeedbackSwitch"
  -->            "yzFeedback"
  -->            "xzFeedback"
  -->            "xyFeedback"
           "geomSeparator"
  \endverbatim

  \NODEKIT_POST_DIAGRAM


  \NODEKIT_PRE_TABLE

  \verbatim
  CLASS SoDragPointDragger
  PVT   "this",  SoDragPointDragger  --- 
        "callbackList",  SoNodeKitListPart [ SoCallback, SoEventCallback ] 
  PVT   "topSeparator",  SoSeparator  --- 
  PVT   "motionMatrix",  SoMatrixTransform  --- 
  PVT   "noRotSep",  SoSeparator  --- 
  PVT   "xTranslatorSwitch",  SoSwitch  --- 
        "xTranslator",  SoTranslate1Dragger  --- 
  PVT   "xyTranslatorSwitch",  SoSwitch  --- 
        "xyTranslator",  SoTranslate2Dragger  --- 
  PVT   "rotXSep",  SoSeparator  --- 
  PVT   "rotX",  SoRotation  --- 
  PVT   "xzTranslatorSwitch",  SoSwitch  --- 
        "xzTranslator",  SoTranslate2Dragger  --- 
  PVT   "rotYSep",  SoSeparator  --- 
  PVT   "rotY",  SoRotation  --- 
  PVT   "zTranslatorSwitch",  SoSwitch  --- 
        "zTranslator",  SoTranslate1Dragger  --- 
  PVT   "yzTranslatorSwitch",  SoSwitch  --- 
        "yzTranslator",  SoTranslate2Dragger  --- 
  PVT   "rotZSep",  SoSeparator  --- 
  PVT   "rotZ",  SoRotation  --- 
  PVT   "yTranslatorSwitch",  SoSwitch  --- 
        "yTranslator",  SoTranslate1Dragger  --- 
  PVT   "xFeedbackSwitch",  SoSwitch  --- 
  PVT   "xFeedbackSep",  SoSeparator  --- 
  PVT   "xFeedbackTranslation",  SoTranslation  --- 
        "xFeedback",  SoSeparator  --- 
  PVT   "yFeedbackSwitch",  SoSwitch  --- 
  PVT   "yFeedbackSep",  SoSeparator  --- 
  PVT   "yFeedbackTranslation",  SoTranslation  --- 
        "yFeedback",  SoSeparator  --- 
  PVT   "zFeedbackSwitch",  SoSwitch  --- 
  PVT   "zFeedbackSep",  SoSeparator  --- 
  PVT   "zFeedbackTranslation",  SoTranslation  --- 
        "zFeedback",  SoSeparator  --- 
  PVT   "planeFeedbackSep",  SoSeparator  --- 
  PVT   "planeFeedbackTranslation",  SoTranslation  --- 
  PVT   "planeFeedbackSwitch",  SoSwitch  --- 
        "yzFeedback",  SoSeparator  --- 
        "xzFeedback",  SoSeparator  --- 
        "xyFeedback",  SoSeparator  --- 
  PVT   "geomSeparator",  SoSeparator  --- 
  \endverbatim

  \NODEKIT_POST_TABLE
*/
SoDragPointDragger::SoDragPointDragger(void)
{
  SO_KIT_INTERNAL_CONSTRUCTOR(SoDragPointDragger);

  SO_KIT_ADD_CATALOG_ENTRY(noRotSep, SoSeparator, false, topSeparator, rotXSep, false);
  SO_KIT_ADD_CATALOG_ENTRY(planeFeedbackSep, SoSeparator, false, topSeparator, geomSeparator, false);
  SO_KIT_ADD_CATALOG_ENTRY(planeFeedbackSwitch, SoSwitch, false, planeFeedbackSep, "", false);
  SO_KIT_ADD_CATALOG_ENTRY(planeFeedbackTranslation, SoTranslation, false, planeFeedbackSep, planeFeedbackSwitch, false);
  SO_KIT_ADD_CATALOG_ENTRY(rotX, SoRotation, true, rotXSep, xzTranslatorSwitch, false);
  SO_KIT_ADD_CATALOG_ENTRY(rotXSep, SoSeparator, false, topSeparator, rotYSep, false);
  SO_KIT_ADD_CATALOG_ENTRY(rotY, SoRotation, true, rotYSep, zTranslatorSwitch, false);
  SO_KIT_ADD_CATALOG_ENTRY(rotYSep, SoSeparator, false, topSeparator, rotZSep, false);
  SO_KIT_ADD_CATALOG_ENTRY(rotZ, SoRotation, true, rotZSep, yTranslatorSwitch, false);
  SO_KIT_ADD_CATALOG_ENTRY(rotZSep, SoSeparator, false, topSeparator, xFeedbackSwitch, false);
  SO_KIT_ADD_CATALOG_ENTRY(xFeedback, SoSeparator, true, xFeedbackSep, "", true);
  SO_KIT_ADD_CATALOG_ENTRY(xFeedbackSep, SoSeparator, false, xFeedbackSwitch, "", false);
  SO_KIT_ADD_CATALOG_ENTRY(xFeedbackSwitch, SoSwitch, false, topSeparator, yFeedbackSwitch, false);
  SO_KIT_ADD_CATALOG_ENTRY(xFeedbackTranslation, SoTranslation, false, xFeedbackSep, xFeedback, false);
  SO_KIT_ADD_CATALOG_ENTRY(xTranslator, SoTranslate1Dragger, true, xTranslatorSwitch, "", true);
  SO_KIT_ADD_CATALOG_ENTRY(xTranslatorSwitch, SoSwitch, false, noRotSep, xyTranslatorSwitch, false);
  SO_KIT_ADD_CATALOG_ENTRY(xyFeedback, SoSeparator, true, planeFeedbackSwitch, "", true);
  SO_KIT_ADD_CATALOG_ENTRY(xyTranslator, SoTranslate2Dragger, true, xyTranslatorSwitch, "", true);
  SO_KIT_ADD_CATALOG_ENTRY(xyTranslatorSwitch, SoSwitch, false, noRotSep, "", false);
  SO_KIT_ADD_CATALOG_ENTRY(xzFeedback, SoSeparator, true, planeFeedbackSwitch, xyFeedback, true);
  SO_KIT_ADD_CATALOG_ENTRY(xzTranslator, SoTranslate2Dragger, true, xzTranslatorSwitch, "", true);
  SO_KIT_ADD_CATALOG_ENTRY(xzTranslatorSwitch, SoSwitch, false, rotXSep, "", false);
  SO_KIT_ADD_CATALOG_ENTRY(yFeedback, SoSeparator, true, yFeedbackSep, "", true);
  SO_KIT_ADD_CATALOG_ENTRY(yFeedbackSep, SoSeparator, false, yFeedbackSwitch, "", false);
  SO_KIT_ADD_CATALOG_ENTRY(yFeedbackSwitch, SoSwitch, false, topSeparator, zFeedbackSwitch, false);
  SO_KIT_ADD_CATALOG_ENTRY(yFeedbackTranslation, SoTranslation, false, yFeedbackSep, yFeedback, false);
  SO_KIT_ADD_CATALOG_ENTRY(yTranslator, SoTranslate1Dragger, true, yTranslatorSwitch, "", true);
  SO_KIT_ADD_CATALOG_ENTRY(yTranslatorSwitch, SoSwitch, false, rotZSep, "", false);
  SO_KIT_ADD_CATALOG_ENTRY(yzFeedback, SoSeparator, true, planeFeedbackSwitch, xzFeedback, true);
  SO_KIT_ADD_CATALOG_ENTRY(yzTranslator, SoTranslate2Dragger, true, yzTranslatorSwitch, "", true);
  SO_KIT_ADD_CATALOG_ENTRY(yzTranslatorSwitch, SoSwitch, false, rotYSep, "", false);
  SO_KIT_ADD_CATALOG_ENTRY(zFeedback, SoSeparator, true, zFeedbackSep, "", true);
  SO_KIT_ADD_CATALOG_ENTRY(zFeedbackSep, SoSeparator, false, zFeedbackSwitch, "", false);
  SO_KIT_ADD_CATALOG_ENTRY(zFeedbackSwitch, SoSwitch, false, topSeparator, planeFeedbackSep, false);
  SO_KIT_ADD_CATALOG_ENTRY(zFeedbackTranslation, SoTranslation, false, zFeedbackSep, zFeedback, false);
  SO_KIT_ADD_CATALOG_ENTRY(zTranslator, SoTranslate1Dragger, true, zTranslatorSwitch, "", true);
  SO_KIT_ADD_CATALOG_ENTRY(zTranslatorSwitch, SoSwitch, false, rotYSep, yzTranslatorSwitch, false);

  if (SO_KIT_IS_FIRST_INSTANCE()) {
    SoInteractionKit::readDefaultParts("dragPointDragger.iv",
                                       DRAGPOINTDRAGGER_draggergeometry,
                                       static_cast<int>(strlen(DRAGPOINTDRAGGER_draggergeometry)));
  }

  SO_KIT_ADD_FIELD(translation, (0.0f, 0.0f, 0.0f));
  SO_KIT_INIT_INSTANCE();

  this->jumpLimit = 0.1f;

  // initialize default parts not contained in simple draggers
  this->setPartAsDefault("xFeedback", "dragPointXFeedback");
  this->setPartAsDefault("yFeedback", "dragPointYFeedback");
  this->setPartAsDefault("zFeedback", "dragPointZFeedback");
  this->setPartAsDefault("xyFeedback", "dragPointXYFeedback");
  this->setPartAsDefault("xzFeedback", "dragPointXZFeedback");
  this->setPartAsDefault("yzFeedback", "dragPointYZFeedback");

  // create simple draggers that compromise this dragger
  (void)SO_GET_ANY_PART(this, "xTranslator", SoTranslate1Dragger);
  (void)SO_GET_ANY_PART(this, "yTranslator", SoTranslate1Dragger);
  (void)SO_GET_ANY_PART(this, "zTranslator", SoTranslate1Dragger);
  (void)SO_GET_ANY_PART(this, "xyTranslator", SoTranslate2Dragger);
  (void)SO_GET_ANY_PART(this, "xzTranslator", SoTranslate2Dragger);
  (void)SO_GET_ANY_PART(this, "yzTranslator", SoTranslate2Dragger);

  // set rotations to align draggers to their respective axis/planes
  SoRotation *xrot = new SoRotation;
  xrot->rotation.setValue(SbRotation(SbVec3f(1.0f, 0.0f, 0.0f), (static_cast<float>(M_PI))*0.5f));
  this->setAnyPartAsDefault("rotX", xrot);
  SoRotation *yrot = new SoRotation;
  yrot->rotation.setValue(SbRotation(SbVec3f(0.0f, 1.0f, 0.0f), (static_cast<float>(M_PI))*0.5f));
  this->setAnyPartAsDefault("rotY", yrot);
  SoRotation *zrot = new SoRotation;
  zrot->rotation.setValue(SbRotation(SbVec3f(0.0f, 0.0f, 1.0f), (static_cast<float>(M_PI))*0.5f));
  this->setAnyPartAsDefault("rotZ", zrot);

  // initialize switch nodes
  SoSwitch *sw;
  sw = SO_GET_ANY_PART(this, "planeFeedbackSwitch", SoSwitch);
  SoInteractionKit::setSwitchValue(sw, SO_SWITCH_NONE);
  sw = SO_GET_ANY_PART(this, "xFeedbackSwitch", SoSwitch);
  SoInteractionKit::setSwitchValue(sw, SO_SWITCH_NONE);
  sw = SO_GET_ANY_PART(this, "yFeedbackSwitch", SoSwitch);
  SoInteractionKit::setSwitchValue(sw, SO_SWITCH_NONE);
  sw = SO_GET_ANY_PART(this, "zFeedbackSwitch", SoSwitch);
  SoInteractionKit::setSwitchValue(sw, SO_SWITCH_NONE);

  this->currAxis = 1;
  this->updateSwitchNodes();

  this->addStartCallback(SoDragPointDragger::startCB, this);
  this->addMotionCallback(SoDragPointDragger::motionCB, this);
  this->addFinishCallback(SoDragPointDragger::finishCB, this);
  this->addOtherEventCallback(SoDragPointDragger::metaKeyChangeCB, this);

  this->addValueChangedCallback(SoDragPointDragger::valueChangedCB);
  this->fieldSensor = new SoFieldSensor(SoDragPointDragger::fieldSensorCB, this);
  this->fieldSensor->setPriority(0);

  this->setUpConnections(true, true);
}

/*!
  Protected destructor.

  (Dragger classes are derived from SoBase, so they are reference
  counted and automatically destroyed when their reference count goes
  to 0.)
 */
SoDragPointDragger::~SoDragPointDragger()
{
  delete this->fieldSensor;
}

// Doc in superclass.
bool
SoDragPointDragger::setUpConnections(bool onoff, bool doitalways)
{
  if (!doitalways && this->connectionsSetUp == onoff) return onoff;

  if (onoff) {
    inherited::setUpConnections(onoff, doitalways);

    SoDragger * xdragger = coin_assert_cast<SoDragger *>(this->getAnyPart("xTranslator", false));
    xdragger->setPartAsDefault("translator", "dragPointXTranslatorTranslator");
    xdragger->setPartAsDefault("translatorActive", "dragPointXTranslatorTranslatorActive");
    this->registerDragger(xdragger);

    SoDragger * ydragger = coin_assert_cast<SoDragger *>(this->getAnyPart("yTranslator", false));
    ydragger->setPartAsDefault("translator", "dragPointYTranslatorTranslator");
    ydragger->setPartAsDefault("translatorActive", "dragPointYTranslatorTranslatorActive");
    this->registerDragger(ydragger);

    SoDragger * zdragger = coin_assert_cast<SoDragger *>(this->getAnyPart("zTranslator", false));
    zdragger->setPartAsDefault("translator", "dragPointZTranslatorTranslator");
    zdragger->setPartAsDefault("translatorActive", "dragPointZTranslatorTranslatorActive");
    this->registerDragger(zdragger);

    SoDragger * xydragger = coin_assert_cast<SoDragger *>(this->getAnyPart("xyTranslator", false));
    xydragger->setPartAsDefault("translator", "dragPointXYTranslatorTranslator");
    xydragger->setPartAsDefault("translatorActive", "dragPointXYTranslatorTranslatorActive");
    this->registerDragger(xydragger);

    SoDragger * xzdragger = coin_assert_cast<SoDragger *>(this->getAnyPart("xzTranslator", false));
    xzdragger->setPartAsDefault("translator", "dragPointXZTranslatorTranslator");
    xzdragger->setPartAsDefault("translatorActive", "dragPointXZTranslatorTranslatorActive");
    this->registerDragger(xzdragger);

    SoDragger * yzdragger = coin_assert_cast<SoDragger *>(this->getAnyPart("yzTranslator", false));
    yzdragger->setPartAsDefault("translator", "dragPointYZTranslatorTranslator");
    yzdragger->setPartAsDefault("translatorActive", "dragPointYZTranslatorTranslatorActive");
    this->registerDragger(yzdragger);

    SoDragPointDragger::fieldSensorCB(this, nullptr);
    if (this->fieldSensor->getAttachedField() != &this->translation) {
      this->fieldSensor->attach(&this->translation);
    }
  }
  else {
    this->unregisterDragger("xTranslator");
    this->unregisterDragger("yTranslator");
    this->unregisterDragger("zTranslator");
    this->unregisterDragger("xyTranslator");
    this->unregisterDragger("xzTranslator");
    this->unregisterDragger("yzTranslator");
    if (this->fieldSensor->getAttachedField() != nullptr) {
      this->fieldSensor->detach();
    }

    inherited::setUpConnections(onoff, doitalways);
  }
  return !(this->connectionsSetUp = onoff);
}

// doc in super
void
SoDragPointDragger::setDefaultOnNonWritingFields(void)
{
  this->xTranslator.setDefault(true);
  this->yTranslator.setDefault(true);
  this->zTranslator.setDefault(true);

  this->xyTranslator.setDefault(true);
  this->xzTranslator.setDefault(true);
  this->yzTranslator.setDefault(true);

  this->planeFeedbackTranslation.setDefault(true);
  this->xFeedbackTranslation.setDefault(true);
  this->yFeedbackTranslation.setDefault(true);
  this->zFeedbackTranslation.setDefault(true);

  inherited::setDefaultOnNonWritingFields();
}

/*! \COININTERNAL */
void
SoDragPointDragger::fieldSensorCB(void * d, SoSensor *)
{
  SoDragPointDragger * thisp = static_cast<SoDragPointDragger *>(d);
  SbMatrix matrix = thisp->getMotionMatrix();
  thisp->workFieldsIntoTransform(matrix);
  thisp->setMotionMatrix(matrix);
}

/*! \COININTERNAL */
void
SoDragPointDragger::valueChangedCB(void *, SoDragger * d)
{
  SoDragPointDragger * thisp = static_cast<SoDragPointDragger *>(d);

  SbMatrix matrix = thisp->getMotionMatrix();
  SbVec3f t;
  t[0] = matrix[3][0];
  t[1] = matrix[3][1];
  t[2] = matrix[3][2];

  thisp->fieldSensor->detach();
  if (thisp->translation.getValue() != t) {
    thisp->translation = t;
  }
  thisp->fieldSensor->attach(&thisp->translation);
}

/*!
  The dragger plane jump limit is ignored in Coin, as we use a
  continuous moving plane.

  This method still included for API compatibility with the original
  SGI Inventor API.
 */
void
SoDragPointDragger::setJumpLimit(const float limit)
{
  // FIXME: should we use it? I'm a bit partial to the visual
  // appearance of the SGI strategy myself, so... 20011024 mortene.
  this->jumpLimit = limit;
}

/*!
  The dragger plane jump limit is ignored in Coin, as we use a
  continuous moving plane.

  This method still included for API compatibility with the original
  SGI Inventor API.
 */
float
SoDragPointDragger::getJumpLimit(void) const
{
  // FIXME: should we use it? I'm a bit partial to the visual
  // appearance of the SGI strategy myself, so... 20011024 mortene.
  return this->jumpLimit;
}

/*!
  Circulate the dragger's three different sets of geometry, to
  circulate the orientation of the translation axis and translation
  plane through the three principal axes.

  This function is triggered when the user taps the \c CTRL key.
 */
void
SoDragPointDragger::showNextDraggerSet(void)
{
  this->currAxis = (this->currAxis + 1) % 3;
  this->updateSwitchNodes();
}

/*! \COININTERNAL
  Called when dragger is selected (picked) by the user.
*/
void
SoDragPointDragger::dragStart(void)
{
  SoDragger * activechild = this->getActiveChildDragger();

  assert(activechild != nullptr);

  SoSwitch * sw;
  if (activechild->isOfType(SoTranslate2Dragger::getClassTypeId())) {
    sw = SO_GET_ANY_PART(this, "planeFeedbackSwitch", SoSwitch);
    SoInteractionKit::setSwitchValue(sw, this->currAxis);
  }
  else {
    switch (this->currAxis) {
    case 0:
      sw = SO_GET_ANY_PART(this, "xFeedbackSwitch", SoSwitch);
      break;
    case 1:
      sw = SO_GET_ANY_PART(this, "yFeedbackSwitch", SoSwitch);
      break;
    case 2:
      sw = SO_GET_ANY_PART(this, "zFeedbackSwitch", SoSwitch);
      break;
    default:
      assert(0); sw = nullptr; // Dummy assignment to avoid compiler warning.
      break;
    }
    SoInteractionKit::setSwitchValue(sw, 0);
  }
}

/*! \COININTERNAL
  Called when user drags the mouse after picking the dragger.
*/
void
SoDragPointDragger::drag(void)
{
  // FIXME: update feedback information, pederb 20000202
}

/*! \COININTERNAL
  Called when mouse button is released after picking and interacting
  with the dragger.
*/
void
SoDragPointDragger::dragFinish(void)
{
  SoSwitch *sw;
  sw = SO_GET_ANY_PART(this, "planeFeedbackSwitch", SoSwitch);
  SoInteractionKit::setSwitchValue(sw, SO_SWITCH_NONE);
  sw = SO_GET_ANY_PART(this, "xFeedbackSwitch", SoSwitch);
  SoInteractionKit::setSwitchValue(sw, SO_SWITCH_NONE);
  sw = SO_GET_ANY_PART(this, "yFeedbackSwitch", SoSwitch);
  SoInteractionKit::setSwitchValue(sw, SO_SWITCH_NONE);
  sw = SO_GET_ANY_PART(this, "zFeedbackSwitch", SoSwitch);
  SoInteractionKit::setSwitchValue(sw, SO_SWITCH_NONE);
}

/*! \COININTERNAL */
void
SoDragPointDragger::startCB(void *d, SoDragger *)
{
  SoDragPointDragger * thisp = static_cast<SoDragPointDragger *>(d);
  thisp->dragStart();
}

/*! \COININTERNAL */
void
SoDragPointDragger::motionCB(void *d, SoDragger *)
{
  SoDragPointDragger * thisp = static_cast<SoDragPointDragger *>(d);
  thisp->drag();
}

/*! \COININTERNAL */
void
SoDragPointDragger::finishCB(void *d, SoDragger *)
{
  SoDragPointDragger * thisp = static_cast<SoDragPointDragger *>(d);
  thisp->dragFinish();
}

/*! \COININTERNAL */
void
SoDragPointDragger::metaKeyChangeCB(void * d, SoDragger *)
{
  SoDragPointDragger * thisp = static_cast<SoDragPointDragger *>(d);
  // we're only interested if dragger is _not_ active
  if (thisp->getActiveChildDragger()) return;
  const SoEvent *event = thisp->getEvent();
  if (SO_KEY_PRESS_EVENT(event, LEFT_CONTROL) ||
      SO_KEY_PRESS_EVENT(event, RIGHT_CONTROL)) {
    thisp->showNextDraggerSet();
  }
}

void
SoDragPointDragger::registerDragger(SoDragger *dragger)
{
  this->registerChildDragger(dragger);
}

void
SoDragPointDragger::unregisterDragger(const char *name)
{
  SoDragger * dragger = coin_assert_cast<SoDragger *>(this->getAnyPart(name, false));
  this->unregisterChildDragger(dragger);
}

void
SoDragPointDragger::updateSwitchNodes()
{
  SoSwitch *sw;
  sw = SO_GET_ANY_PART(this, "xTranslatorSwitch", SoSwitch);
  SoInteractionKit::setSwitchValue(sw, this->currAxis == 0 ? 0 : SO_SWITCH_NONE);
  sw = SO_GET_ANY_PART(this, "yTranslatorSwitch", SoSwitch);
  SoInteractionKit::setSwitchValue(sw, this->currAxis == 1 ? 0 : SO_SWITCH_NONE);
  sw = SO_GET_ANY_PART(this, "zTranslatorSwitch", SoSwitch);
  SoInteractionKit::setSwitchValue(sw, this->currAxis == 2 ? 0 : SO_SWITCH_NONE);

  sw = SO_GET_ANY_PART(this, "xyTranslatorSwitch", SoSwitch);
  SoInteractionKit::setSwitchValue(sw, this->currAxis == 2 ? 0 : SO_SWITCH_NONE);
  sw = SO_GET_ANY_PART(this, "xzTranslatorSwitch", SoSwitch);
  SoInteractionKit::setSwitchValue(sw, this->currAxis == 1 ? 0 : SO_SWITCH_NONE);
  sw = SO_GET_ANY_PART(this, "yzTranslatorSwitch", SoSwitch);
  SoInteractionKit::setSwitchValue(sw, this->currAxis == 0 ? 0 : SO_SWITCH_NONE);
}

#endif // HAVE_DRAGGERS
