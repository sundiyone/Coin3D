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

/*!
  \class SoSFVec2f SoSFVec2f.h Inventor/fields/SoSFVec2f.h
  \brief The SoSFVec2f class is a container for an SbVec2f vector.
  \ingroup fields

  This field is used where nodes, engines or other field containers
  needs to store a single vector with two elements.

  \sa SoMFVec2f
*/

// *************************************************************************

#include <Inventor/fields/SoSFVec2f.h>

#include <Inventor/SoInput.h>
#include <Inventor/SoOutput.h>
#include <Inventor/errors/SoDebugError.h>

#include "fields/SoSubFieldP.h"
#include "fields/shared.h"

// *************************************************************************

SO_SFIELD_SOURCE(SoSFVec2f, SbVec2f, const SbVec2f &);

// *************************************************************************

// Override from parent class.
void
SoSFVec2f::initClass(void)
{
  SO_SFIELD_INTERNAL_INIT_CLASS(SoSFVec2f);
}

// *************************************************************************

// No need to document readValue() and writeValue() here, as the
// necessary information is provided by the documentation of the
// parent classes.
#ifndef DOXYGEN_SKIP_THIS

bool
SoSFVec2f::readValue(SoInput * in)
{
  return
    in->read(this->value[0]) &&
    in->read(this->value[1]);
}

void
SoSFVec2f::writeValue(SoOutput * out) const
{
  sosfvec2f_write_value(out, this->getValue());
}

#endif // DOXYGEN_SKIP_THIS

// *************************************************************************

/*!
  Set value of vector.
*/
void
SoSFVec2f::setValue(float x, float y)
{
  this->setValue(SbVec2f(x, y));
}

/*!
  Set value of vector.
*/
void
SoSFVec2f::setValue(const float xy[2])
{
  this->setValue(SbVec2f(xy));
}

// *************************************************************************

#ifdef COIN_TEST_SUITE

BOOST_AUTO_TEST_CASE(initialized)
{
  SoSFVec2f field;
  BOOST_CHECK_MESSAGE(SoSFVec2f::getClassTypeId() != SoType::badType(),
                      "SoSFVec2f class not initialized");
  BOOST_CHECK_MESSAGE(field.getTypeId() != SoType::badType(),
                      "missing class initialization");
}

#endif // COIN_TEST_SUITE
