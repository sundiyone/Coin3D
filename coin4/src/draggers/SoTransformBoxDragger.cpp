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
  \class SoTransformBoxDragger SoTransformBoxDragger.h Inventor/draggers/SoTransformBoxDragger.h
  \brief The SoTransformBoxDragger provides a box which can be translated, scaled and rotated.
  \ingroup draggers

  \DRAGGER_DEFAULT_SCREENSHOT

  <center>
  <img src="http://doc.coin3d.org/images/Coin/draggers/transformbox.png">
  </center>

  Translate the dragger by clicking and dragging any of the
  (invisible) sides. Scaling is done by dragging the corner
  cubes. Only uniform scaling is supported. Rotation is done by
  dragging any of the 12 beams connecting the corner cubes.

  This dragger consists of a rigid framework for doing all the usual
  interaction operations on scene geometry. The "user interface" of
  the dragger is very simple, providing little room for the end-user
  to make mistakes.

  For the application programmer's convenience, the Coin library also
  provides a manipulator class called SoTransformBoxManip, which wraps
  the SoTransformBoxDragger into the necessary mechanisms for making
  direct insertion of this dragger into a scenegraph possible with
  very little effort.

  \sa SoTransformBoxManip
*/

#include <Inventor/draggers/SoTransformBoxDragger.h>

#include <cstring>

#include <Inventor/draggers/SoRotateCylindricalDragger.h>
#include <Inventor/draggers/SoScaleUniformDragger.h>
#include <Inventor/draggers/SoTranslate2Dragger.h>
#include <Inventor/nodes/SoAntiSquish.h>
#include <Inventor/nodes/SoRotation.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSurroundScale.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/errors/SoDebugError.h>

#include <data/draggerDefaults/transformBoxDragger.h>

#include "nodekits/SoSubKitP.h"
#include "SbBasicP.h"

/*!
  \var SoSFRotation SoTransformBoxDragger::rotation

  This field is continuously updated to contain the rotation of the
  dragger's box.
*/
/*!
  \var SoSFVec3f SoTransformBoxDragger::translation

  The dragger's offset position from the local origo.
*/
/*!
  \var SoSFVec3f SoTransformBoxDragger::scaleFactor

  Continuously updated to contain the current vector of scaling along
  the X, Y and Z axes. The three components will always be equal, as
  this dragger only supports uniform scale operations.
*/

/*!
  \var SoFieldSensor * SoTransformBoxDragger::rotFieldSensor
  \COININTERNAL
*/
/*!
  \var SoFieldSensor * SoTransformBoxDragger::translFieldSensor
  \COININTERNAL
*/
/*!
  \var SoFieldSensor * SoTransformBoxDragger::scaleFieldSensor
  \COININTERNAL
*/

#define THISP(d) static_cast<SoTransformBoxDragger *>(d)

class SoTransformBoxDraggerP {
public:
};

SO_KIT_SOURCE(SoTransformBoxDragger);


// doc in superclass
void
SoTransformBoxDragger::initClass(void)
{
  SO_KIT_INTERNAL_INIT_CLASS(SoTransformBoxDragger, SO_FROM_INVENTOR_1);
}

// FIXME: document which parts need to be present in the geometry
// scenegraph, and what role they play in the dragger. 20010913 mortene.
/*!
  \DRAGGER_CONSTRUCTOR

  \NODEKIT_PRE_DIAGRAM

  \verbatim
  CLASS SoTransformBoxDragger
  -->"this"
        "callbackList"
        "topSeparator"
           "motionMatrix"
  -->      "surroundScale"
  -->      "antiSquish"
  -->      "scaler"
  -->      "rotator1Sep"
  -->         "rotator1Rot"
  -->         "rotator1"
  -->      "rotator2Sep"
  -->         "rotator2Rot"
  -->         "rotator2"
  -->      "rotator3Sep"
  -->         "rotator3Rot"
  -->         "rotator3"
  -->      "translator1Sep"
  -->         "translator1Rot"
  -->         "translator1"
  -->      "translator2Sep"
  -->         "translator2Rot"
  -->         "translator2"
  -->      "translator3Sep"
  -->         "translator3Rot"
  -->         "translator3"
  -->      "translator4Sep"
  -->         "translator4Rot"
  -->         "translator4"
  -->      "translator5Sep"
  -->         "translator5Rot"
  -->         "translator5"
  -->      "translator6Sep"
  -->         "translator6Rot"
  -->         "translator6"
           "geomSeparator"
  \endverbatim

  \NODEKIT_POST_DIAGRAM


  \NODEKIT_PRE_TABLE

  \verbatim
  CLASS SoTransformBoxDragger
  PVT   "this",  SoTransformBoxDragger  ---
        "callbackList",  SoNodeKitListPart [ SoCallback, SoEventCallback ]
  PVT   "topSeparator",  SoSeparator  ---
  PVT   "motionMatrix",  SoMatrixTransform  ---
        "surroundScale",  SoSurroundScale  ---
        "antiSquish",  SoAntiSquish  ---
        "scaler",  SoScaleUniformDragger  ---
  PVT   "rotator1Sep",  SoSeparator  ---
  PVT   "rotator1Rot",  SoRotation  ---
        "rotator1",  SoRotateCylindricalDragger  ---
  PVT   "rotator2Sep",  SoSeparator  ---
  PVT   "rotator2Rot",  SoRotation  ---
        "rotator2",  SoRotateCylindricalDragger  ---
  PVT   "rotator3Sep",  SoSeparator  ---
  PVT   "rotator3Rot",  SoRotation  ---
        "rotator3",  SoRotateCylindricalDragger  ---
  PVT   "translator1Sep",  SoSeparator  ---
  PVT   "translator1Rot",  SoRotation  ---
        "translator1",  SoTranslate2Dragger  ---
  PVT   "translator2Sep",  SoSeparator  ---
  PVT   "translator2Rot",  SoRotation  ---
        "translator2",  SoTranslate2Dragger  ---
  PVT   "translator3Sep",  SoSeparator  ---
  PVT   "translator3Rot",  SoRotation  ---
        "translator3",  SoTranslate2Dragger  ---
  PVT   "translator4Sep",  SoSeparator  ---
  PVT   "translator4Rot",  SoRotation  ---
        "translator4",  SoTranslate2Dragger  ---
  PVT   "translator5Sep",  SoSeparator  ---
  PVT   "translator5Rot",  SoRotation  ---
        "translator5",  SoTranslate2Dragger  ---
  PVT   "translator6Sep",  SoSeparator  ---
  PVT   "translator6Rot",  SoRotation  ---
        "translator6",  SoTranslate2Dragger  ---
  PVT   "geomSeparator",  SoSeparator  ---
  \endverbatim

  \NODEKIT_POST_TABLE
*/
SoTransformBoxDragger::SoTransformBoxDragger(void)
{
  SO_KIT_INTERNAL_CONSTRUCTOR(SoTransformBoxDragger);

  SO_KIT_ADD_CATALOG_ENTRY(surroundScale, SoSurroundScale, true, topSeparator, antiSquish, true);
  SO_KIT_ADD_CATALOG_ENTRY(antiSquish, SoAntiSquish, false, topSeparator, scaler, true);
  SO_KIT_ADD_CATALOG_ENTRY(scaler, SoScaleUniformDragger, true, topSeparator, rotator1Sep, true);
  SO_KIT_ADD_CATALOG_ENTRY(rotator1Sep, SoSeparator, false, topSeparator, rotator2Sep, false);
  SO_KIT_ADD_CATALOG_ENTRY(rotator1Rot, SoRotation, true, rotator1Sep, rotator1, false);
  SO_KIT_ADD_CATALOG_ENTRY(rotator1, SoRotateCylindricalDragger, true, rotator1Sep, "", true);
  SO_KIT_ADD_CATALOG_ENTRY(rotator2Sep, SoSeparator, false, topSeparator, rotator3Sep, false);
  SO_KIT_ADD_CATALOG_ENTRY(rotator2Rot, SoRotation, true, rotator2Sep, rotator2, false);
  SO_KIT_ADD_CATALOG_ENTRY(rotator2, SoRotateCylindricalDragger, true, rotator2Sep, "", true);
  SO_KIT_ADD_CATALOG_ENTRY(rotator3Sep, SoSeparator, false, topSeparator, translator1Sep, false);
  SO_KIT_ADD_CATALOG_ENTRY(rotator3Rot, SoRotation, true, rotator3Sep, rotator3, false);
  SO_KIT_ADD_CATALOG_ENTRY(rotator3, SoRotateCylindricalDragger, true, rotator3Sep, "", true);
  SO_KIT_ADD_CATALOG_ENTRY(translator1Sep, SoSeparator, false, topSeparator, translator2Sep, false);
  SO_KIT_ADD_CATALOG_ENTRY(translator1Rot, SoRotation, true, translator1Sep, translator1, false);
  SO_KIT_ADD_CATALOG_ENTRY(translator1, SoTranslate2Dragger, true, translator1Sep, "", true);
  SO_KIT_ADD_CATALOG_ENTRY(translator2Sep, SoSeparator, false, topSeparator, translator3Sep, false);
  SO_KIT_ADD_CATALOG_ENTRY(translator2Rot, SoRotation, true, translator2Sep, translator2, false);
  SO_KIT_ADD_CATALOG_ENTRY(translator2, SoTranslate2Dragger, true, translator2Sep, "", true);
  SO_KIT_ADD_CATALOG_ENTRY(translator3Sep, SoSeparator, false, topSeparator, translator4Sep, false);
  SO_KIT_ADD_CATALOG_ENTRY(translator3Rot, SoRotation, true, translator3Sep, translator3, false);
  SO_KIT_ADD_CATALOG_ENTRY(translator3, SoTranslate2Dragger, true, translator3Sep, "", true);
  SO_KIT_ADD_CATALOG_ENTRY(translator4Sep, SoSeparator, false, topSeparator, translator5Sep, false);
  SO_KIT_ADD_CATALOG_ENTRY(translator4Rot, SoRotation, true, translator4Sep, translator4, false);
  SO_KIT_ADD_CATALOG_ENTRY(translator4, SoTranslate2Dragger, true, translator4Sep, "", true);
  SO_KIT_ADD_CATALOG_ENTRY(translator5Sep, SoSeparator, false, topSeparator, translator6Sep, false);
  SO_KIT_ADD_CATALOG_ENTRY(translator5Rot, SoRotation, true, translator5Sep, translator5, false);
  SO_KIT_ADD_CATALOG_ENTRY(translator5, SoTranslate2Dragger, true, translator5Sep, "", true);
  SO_KIT_ADD_CATALOG_ENTRY(translator6Sep, SoSeparator, false, topSeparator, geomSeparator, false);
  SO_KIT_ADD_CATALOG_ENTRY(translator6Rot, SoRotation, true, translator6Sep, translator6, false);
  SO_KIT_ADD_CATALOG_ENTRY(translator6, SoTranslate2Dragger, true, translator6Sep, "", true);

  if (SO_KIT_IS_FIRST_INSTANCE()) {
    SoInteractionKit::readDefaultParts("transformBoxDragger.iv",
                                       TRANSFORMBOXDRAGGER_draggergeometry,
                                       static_cast<int>(strlen(TRANSFORMBOXDRAGGER_draggergeometry)));
  }

  SO_KIT_ADD_FIELD(rotation, (SbRotation(SbVec3f(0.0f, 0.0f, 1.0f), 0.0f)));
  SO_KIT_ADD_FIELD(translation, (0.0f, 0.0f, 0.0f));
  SO_KIT_ADD_FIELD(scaleFactor, (1.0f, 1.0f, 1.0f));

  SO_KIT_INIT_INSTANCE();

  SO_GET_ANY_PART(this, "scaler", SoScaleUniformDragger);
  SO_GET_ANY_PART(this, "rotator1", SoRotateCylindricalDragger);
  SO_GET_ANY_PART(this, "rotator2", SoRotateCylindricalDragger);
  SO_GET_ANY_PART(this, "rotator3", SoRotateCylindricalDragger);
  SO_GET_ANY_PART(this, "translator1", SoTranslate2Dragger);
  SO_GET_ANY_PART(this, "translator2", SoTranslate2Dragger);
  SO_GET_ANY_PART(this, "translator3", SoTranslate2Dragger);
  SO_GET_ANY_PART(this, "translator4", SoTranslate2Dragger);
  SO_GET_ANY_PART(this, "translator5", SoTranslate2Dragger);
  SO_GET_ANY_PART(this, "translator6", SoTranslate2Dragger);

  SoRotation *rot;
  rot = SO_GET_ANY_PART(this, "rotator1Rot", SoRotation);
  rot->rotation = SbRotation(SbVec3f(0.0f, 0.0f, 1.0f), static_cast<float>(M_PI)/2.0f);
  this->rotator1Rot.setDefault(true);
  rot = SO_GET_ANY_PART(this, "rotator2Rot", SoRotation);
  rot->rotation = SbRotation(SbVec3f(1.0f, 0.0f, 0.0f), static_cast<float>(M_PI)/2.0f);
  this->rotator2Rot.setDefault(true);
  rot = SO_GET_ANY_PART(this, "rotator3Rot", SoRotation);
  rot->rotation = SbRotation(SbVec3f(0.0f, 0.0f, 1.0f), 0.0f);
  this->rotator3Rot.setDefault(true);

  rot = SO_GET_ANY_PART(this, "translator1Rot", SoRotation);
  rot->rotation = SbRotation(SbVec3f(0.0f, 1.0f, 0.0f), static_cast<float>(M_PI)/2.0f);
  this->translator1Rot.setDefault(true);
  rot = SO_GET_ANY_PART(this, "translator2Rot", SoRotation);
  rot->rotation = SbRotation(SbVec3f(0.0f, 1.0f, 0.0f), -static_cast<float>(M_PI)/2.0f);
  this->translator2Rot.setDefault(true);

  rot = SO_GET_ANY_PART(this, "translator3Rot", SoRotation);
  rot->rotation = SbRotation(SbVec3f(1.0f, 0.0f, 0.0f), static_cast<float>(M_PI)/2.0f);
  this->translator3Rot.setDefault(true);
  rot = SO_GET_ANY_PART(this, "translator4Rot", SoRotation);
  rot->rotation = SbRotation(SbVec3f(1.0f, 0.0f, 0.0f), -static_cast<float>(M_PI)/2.0f);
  this->translator4Rot.setDefault(true);

  rot = SO_GET_ANY_PART(this, "translator5Rot", SoRotation);
  rot->rotation = SbRotation(SbVec3f(1.0f, 0.0f, 0.0f), static_cast<float>(M_PI));
  this->translator5Rot.setDefault(true);

  rot = SO_GET_ANY_PART(this, "translator6Rot", SoRotation);
  rot->rotation = SbRotation(SbVec3f(1.0f, 0.0f, 0.0f), 0.0f);
  this->translator6Rot.setDefault(true);

  SoAntiSquish *squish = SO_GET_ANY_PART(this, "antiSquish", SoAntiSquish);
  squish->sizing = SoAntiSquish::BIGGEST_DIMENSION;
  squish->sizing.setDefault(true);
  squish->recalcAlways = false;
  squish->recalcAlways.setDefault(true);

  this->addValueChangedCallback(SoTransformBoxDragger::valueChangedCB);
  this->rotFieldSensor = new SoFieldSensor(SoTransformBoxDragger::fieldSensorCB, this);
  this->rotFieldSensor->setPriority(0);
  this->translFieldSensor = new SoFieldSensor(SoTransformBoxDragger::fieldSensorCB, this);
  this->translFieldSensor->setPriority(0);
  this->scaleFieldSensor = new SoFieldSensor(SoTransformBoxDragger::fieldSensorCB, this);
  this->scaleFieldSensor->setPriority(0);
  this->setUpConnections(true, true);

  this->scaler.setDefault(true);
}

/*!
  Protected destructor.

  (Dragger classes are derived from SoBase, so they are reference
  counted and automatically destroyed when their reference count goes
  to 0.)
 */
SoTransformBoxDragger::~SoTransformBoxDragger()
{
  delete this->rotFieldSensor;
  delete this->translFieldSensor;
  delete this->scaleFieldSensor;
}

// Doc in super.
bool
SoTransformBoxDragger::setUpConnections(bool onoff, bool doitalways)
{
  if (!doitalways && this->connectionsSetUp == onoff) return onoff;

  if (onoff) {
    int i;
    SbString str;
    inherited::setUpConnections(onoff, doitalways);
    SoDragger *child = coin_assert_cast<SoDragger *>(this->getAnyPart("scaler", false));
    child->setPartAsDefault("scaler", "transformBoxScalerScaler");
    child->setPartAsDefault("scalerActive", "transformBoxScalerScalerActive");
    child->setPartAsDefault("feedback", "transformBoxScalerFeedback");
    child->setPartAsDefault("feedbackActive", "transformBoxScalerFeedbackActive");
    this->addChildDragger(child);

    for (i = 1; i <= 3; i++) {
      str.sprintf("rotator%d", i);
      child = coin_assert_cast<SoDragger *>(this->getAnyPart(str.getString(), false));
      child->setPartAsDefault("rotator", "transformBoxRotatorRotator");
      child->setPartAsDefault("rotatorActive", "transformBoxRotatorRotatorActive");
      child->setPartAsDefault("feedback", "transformBoxRotatorFeedback");
      child->setPartAsDefault("feedbackActive", "transformBoxRotatorFeedbackActive");
      this->addChildDragger(child);
    }

    for (i = 1; i <= 6; i++) {
      str.sprintf("translator%d", i);
      child = coin_assert_cast<SoDragger *>(this->getAnyPart(str.getString(), false));
      child->setPartAsDefault("translator", "transformBoxTranslatorTranslator");
      child->setPartAsDefault("translatorActive", "transformBoxTranslatorTranslatorActive");
      child->setPartAsDefault("xAxisFeedback", "transformBoxTranslatorXAxisFeedback");
      child->setPartAsDefault("yAxisFeedback", "transformBoxTranslatorYAxisFeedback");
      this->addChildDragger(child);
    }
    if (this->translFieldSensor->getAttachedField() != &this->translation) {
      this->translFieldSensor->attach(&this->translation);
    }
    if (this->rotFieldSensor->getAttachedField() != &this->rotation) {
      this->rotFieldSensor->attach(&this->rotation);
    }
    if (this->scaleFieldSensor->getAttachedField() != &this->scaleFactor) {
      this->scaleFieldSensor->attach(&this->scaleFactor);
    }
  }
  else {
    this->removeChildDragger(coin_assert_cast<SoDragger *>(this->getAnyPart("scaler", false)));
    this->removeChildDragger(coin_assert_cast<SoDragger *>(this->getAnyPart("rotator1", false)));
    this->removeChildDragger(coin_assert_cast<SoDragger *>(this->getAnyPart("rotator2", false)));
    this->removeChildDragger(coin_assert_cast<SoDragger *>(this->getAnyPart("rotator3", false)));
    this->removeChildDragger(coin_assert_cast<SoDragger *>(this->getAnyPart("translator1", false)));
    this->removeChildDragger(coin_assert_cast<SoDragger *>(this->getAnyPart("translator2", false)));
    this->removeChildDragger(coin_assert_cast<SoDragger *>(this->getAnyPart("translator3", false)));
    this->removeChildDragger(coin_assert_cast<SoDragger *>(this->getAnyPart("translator4", false)));
    this->removeChildDragger(coin_assert_cast<SoDragger *>(this->getAnyPart("translator5", false)));
    this->removeChildDragger(coin_assert_cast<SoDragger *>(this->getAnyPart("translator6", false)));

    if (this->translFieldSensor->getAttachedField() != nullptr) {
      this->translFieldSensor->detach();
    }
    if (this->rotFieldSensor->getAttachedField() != nullptr) {
      this->rotFieldSensor->detach();
    }
    if (this->scaleFieldSensor->getAttachedField() != nullptr) {
      this->scaleFieldSensor->detach();
    }
    inherited::setUpConnections(onoff, doitalways);
  }
  return !(this->connectionsSetUp = onoff);
}

// Convenience method used to call setDefault on similar fields.
//
// Note: keep the function name prefix to avoid name clashes with
// other dragger .cpp files for "--enable-compact" builds.
//
// FIXME: should collect these methods in a common method visible to
// all draggers implementing the exact same functionality. 20010826 mortene.
static void
SoTransformBoxDragger_set_default(SoDragger * dragger, const char * fmt,
                                  int minval, int maxval)
{
  SbString str;
  for (int i = minval; i <= maxval; i++) {
    str.sprintf(fmt, i);
    SoField * f = dragger->getField(str.getString());
    assert(f);
    f->setDefault(true);
  }
}

// Doc in superclass.
void
SoTransformBoxDragger::setDefaultOnNonWritingFields(void)
{
  this->surroundScale.setDefault(true);

  SoTransformBoxDragger_set_default(this, "rotator%d", 1, 3);
  SoTransformBoxDragger_set_default(this, "translator%d", 1, 6);

  inherited::setDefaultOnNonWritingFields();
}

/*! \COININTERNAL */
void
SoTransformBoxDragger::fieldSensorCB(void * d, SoSensor *)
{
  SoTransformBoxDragger * thisp = THISP(d);
  SbMatrix matrix = thisp->getMotionMatrix();
  thisp->workFieldsIntoTransform(matrix);
  thisp->setMotionMatrix(matrix);
}

/*! \COININTERNAL */
void
SoTransformBoxDragger::valueChangedCB(void *, SoDragger * d)
{
  SoTransformBoxDragger * thisp = THISP(d);
  SbMatrix matrix = thisp->getMotionMatrix();

  SbVec3f trans, scale;
  SbRotation rot, scaleOrient;
  matrix.getTransform(trans, rot, scale, scaleOrient);

  thisp->translFieldSensor->detach();
  if (thisp->translation.getValue() != trans)
    thisp->translation = trans;
  thisp->translFieldSensor->attach(&thisp->translation);

  thisp->rotFieldSensor->detach();
  if (thisp->rotation.getValue() != rot)
    thisp->rotation = rot;
  thisp->rotFieldSensor->attach(&thisp->rotation);

  thisp->scaleFieldSensor->detach();
  if (thisp->scaleFactor.getValue() != scale)
    thisp->scaleFactor = scale;
  thisp->scaleFieldSensor->attach(&thisp->scaleFactor);
}

// private
void
SoTransformBoxDragger::addChildDragger(SoDragger * child)
{
  child->addStartCallback(invalidateSurroundScaleCB, this);
  child->addFinishCallback(invalidateSurroundScaleCB, this);
  this->registerChildDragger(child);
}

// private
void
SoTransformBoxDragger::removeChildDragger(SoDragger * child)
{
  child->removeStartCallback(invalidateSurroundScaleCB, this);
  child->removeFinishCallback(invalidateSurroundScaleCB, this);
  this->unregisterChildDragger(child);
}

/*! \COININTERNAL */
void
SoTransformBoxDragger::invalidateSurroundScaleCB(void *, SoDragger * d)
{
  SoTransformBoxDragger * thisp = THISP(d);
  SoSurroundScale * surround = SO_CHECK_PART(thisp, "surroundScale", SoSurroundScale);
  if (surround) surround->invalidate();

  SoAntiSquish * squish = SO_CHECK_ANY_PART(thisp, "antiSquish", SoAntiSquish);
  if (squish) squish->recalc();
}

#undef THISP
#endif // HAVE_DRAGGERS
