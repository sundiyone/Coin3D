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

#ifdef HAVE_NODEKITS

/*!
  \class SoSeparatorKit SoSeparatorKit.h Inventor/nodekits/SoSeparatorKit.h
  \brief The SoSeparatorKit class provides a typical set of nodes to influence a shape subgraph.
  \ingroup nodekits

  \NODEKIT_PRE_DIAGRAM

  \verbatim
  CLASS SoSeparatorKit
  -->"this"
        "callbackList"
  -->   "topSeparator"
  -->      "pickStyle"
  -->      "appearance"
  -->      "units"
  -->      "transform"
  -->      "texture2Transform"
  -->      "childList"
  \endverbatim

  \NODEKIT_POST_DIAGRAM


  \NODEKIT_PRE_TABLE

  \verbatim
  CLASS SoSeparatorKit
  PVT   "this",  SoSeparatorKit  --- 
        "callbackList",  SoNodeKitListPart [ SoCallback, SoEventCallback ] 
  PVT   "topSeparator",  SoSeparator  --- 
        "pickStyle",  SoPickStyle  --- 
        "appearance",  SoAppearanceKit  --- 
        "units",  SoUnits  --- 
        "transform",  SoTransform  --- 
        "texture2Transform",  SoTexture2Transform  --- 
        "childList",  SoNodeKitListPart [ SoShapeKit, SoSeparatorKit ] 
  \endverbatim

  \NODEKIT_POST_TABLE
*/

#include <Inventor/nodekits/SoSeparatorKit.h>

#include <Inventor/nodekits/SoShapeKit.h>
#include <Inventor/nodekits/SoAppearanceKit.h>
#include <Inventor/nodekits/SoNodeKitListPart.h>
#include <Inventor/nodes/SoPickStyle.h>
#include <Inventor/nodes/SoUnits.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoTexture2Transform.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/sensors/SoFieldSensor.h>

#include "nodekits/SoSubKitP.h"

#ifndef DOXYGEN_SKIP_THIS

class SoSeparatorKitP {
public:
  SoSeparatorKitP(SoSeparatorKit * kit) : kit(kit) {}

  SoSeparatorKit * kit;
  SoFieldSensor * fieldsensor;
  SoSeparator * connectedseparator;

  void connectFields(const bool onoff);
  void attachSensor(const bool onoff);

  static void sensorCB(void *, SoSensor *);

};

#endif // DOXYGEN_SKIP_THIS

/*!
  \enum SoSeparatorKit::CacheEnabled

  Contains the same values with the same semantics as in the enum with
  the same name in SoSeparator. See documentation of
  SoSeparator::CacheEnabled.
*/

/*!
  \var SoSFEnum SoSeparatorKit::renderCaching

  See documentation for SoSeparator::renderCaching.
*/
/*!
  \var SoSFEnum SoSeparatorKit::boundingBoxCaching

  See documentation for SoSeparator::boundingBoxCaching.
*/
/*!
  \var SoSFEnum SoSeparatorKit::renderCulling

  See documentation for SoSeparator::renderCulling.
*/
/*!
  \var SoSFEnum SoSeparatorKit::pickCulling

  See documentation for SoSeparator::pickCulling.
*/


SO_KIT_SOURCE(SoSeparatorKit);

#define PRIVATE(obj) ((obj)->pimpl)

/*!
  Constructor.
*/
SoSeparatorKit::SoSeparatorKit(void)
{
  PRIVATE(this) = new SoSeparatorKitP(this);
  SO_KIT_INTERNAL_CONSTRUCTOR(SoSeparatorKit);

  SO_KIT_ADD_FIELD(renderCaching, (SoSeparatorKit::AUTO));
  SO_KIT_ADD_FIELD(boundingBoxCaching, (SoSeparatorKit::AUTO));
  SO_KIT_ADD_FIELD(renderCulling, (SoSeparatorKit::AUTO));
  SO_KIT_ADD_FIELD(pickCulling, (SoSeparatorKit::AUTO));

  SO_KIT_DEFINE_ENUM_VALUE(CacheEnabled, ON);
  SO_KIT_DEFINE_ENUM_VALUE(CacheEnabled, OFF);
  SO_KIT_DEFINE_ENUM_VALUE(CacheEnabled, AUTO);

  SO_KIT_SET_SF_ENUM_TYPE(renderCaching, CacheEnabled);
  SO_KIT_SET_SF_ENUM_TYPE(boundingBoxCaching, CacheEnabled);
  SO_KIT_SET_SF_ENUM_TYPE(renderCulling, CacheEnabled);
  SO_KIT_SET_SF_ENUM_TYPE(pickCulling, CacheEnabled);

  // Note: we must use "" instead of , , to humour MS VisualC++ 6.

  SO_KIT_ADD_CATALOG_ENTRY(topSeparator, SoSeparator, true, this, "", false);
  SO_KIT_ADD_CATALOG_ENTRY(pickStyle, SoPickStyle, true, topSeparator, appearance, true);
  SO_KIT_ADD_CATALOG_ENTRY(appearance, SoAppearanceKit, true, topSeparator, units, true);
  SO_KIT_ADD_CATALOG_ENTRY(units, SoUnits, true, topSeparator, transform, true);
  SO_KIT_ADD_CATALOG_ENTRY(transform, SoTransform, true, topSeparator, texture2Transform, true);
  SO_KIT_ADD_CATALOG_ENTRY(texture2Transform, SoTexture2Transform, true, topSeparator, childList, true);
  SO_KIT_ADD_CATALOG_LIST_ENTRY(childList, SoSeparator, true, topSeparator, "", SoShapeKit, true);
  SO_KIT_ADD_LIST_ITEM_TYPE(childList, SoSeparatorKit);

  PRIVATE(this)->connectedseparator = nullptr;
  PRIVATE(this)->fieldsensor = new SoFieldSensor(SoSeparatorKitP::sensorCB, PRIVATE(this));
  PRIVATE(this)->fieldsensor->setPriority(0);

  SO_KIT_INIT_INSTANCE();

  this->setUpConnections(true, true);
}

/*!
  Destructor.
*/
SoSeparatorKit::~SoSeparatorKit()
{
  PRIVATE(this)->connectFields(false);
  delete PRIVATE(this)->fieldsensor;
  delete PRIVATE(this);
}

/*!
  Does initialization common for all objects of the
  SoSeparatorKit class. This includes setting up the
  type system, among other things.
*/
void
SoSeparatorKit::initClass(void)
{
  SO_KIT_INTERNAL_INIT_CLASS(SoSeparatorKit, SO_FROM_INVENTOR_1);
}

void
SoSeparatorKit::setDefaultOnNonWritingFields(void)
{
  this->topSeparator.setDefault(true);
  inherited::setDefaultOnNonWritingFields();
}

bool
SoSeparatorKit::setUpConnections(bool onoff, bool doitalways)
{
  if (onoff == this->connectionsSetUp && !doitalways)
    return onoff;

  if (onoff) {
    inherited::setUpConnections(onoff, false);
    PRIVATE(this)->connectFields(true);
    PRIVATE(this)->attachSensor(true);
  }
  else {
    PRIVATE(this)->attachSensor(false);
    PRIVATE(this)->connectFields(false);
    inherited::setUpConnections(onoff, false);
  }
  return !(this->connectionsSetUp = onoff);
}

#undef PRIVATE

/****** methods for SoSeparatorKitP are below ************************/

#ifndef DOXYGEN_SKIP_THIS

//
// connect fields in topSeparator to the fields in this node.
//
void
SoSeparatorKitP::connectFields(const bool onoff)
{
  if (this->connectedseparator) { // always disconnect
    this->connectedseparator->renderCaching.disconnect();
    this->connectedseparator->boundingBoxCaching.disconnect();
    this->connectedseparator->renderCulling.disconnect();
    this->connectedseparator->pickCulling.disconnect();
    this->connectedseparator->unref();
    this->connectedseparator = nullptr;
  }
  if (onoff) {
    SoSeparator * sep = (SoSeparator*) this->kit->topSeparator.getValue();
    if (sep) {
      this->connectedseparator = sep;
      this->connectedseparator->ref(); // ref to make sure pointer is legal
      sep->renderCaching.connectFrom(&this->kit->renderCaching);
      sep->boundingBoxCaching.connectFrom(&this->kit->boundingBoxCaching);
      sep->renderCulling.connectFrom(&this->kit->renderCulling);
      sep->pickCulling.connectFrom(&this->kit->pickCulling);
    }
  }
}

//
// attach sensor to topSeparator if onoff, detach otherwise
//
void
SoSeparatorKitP::attachSensor(const bool onoff)
{
  if (onoff) {
    if (this->fieldsensor->getAttachedField() != &this->kit->topSeparator) {
      this->fieldsensor->attach(&this->kit->topSeparator);
    }
  }
  else {
    if (this->fieldsensor->getAttachedField()) this->fieldsensor->detach();
  }
}

//
// callback from field sensor connected to topSeparator
//
void
SoSeparatorKitP::sensorCB(void * data, SoSensor *)
{
  SoSeparatorKitP * thisp = (SoSeparatorKitP*) data;
  if (thisp->connectedseparator != thisp->kit->topSeparator.getValue()) {
    thisp->connectFields(true);
  }
}

#endif // DOXYGEN_SKIP_THIS
#endif // HAVE_NODEKITS
