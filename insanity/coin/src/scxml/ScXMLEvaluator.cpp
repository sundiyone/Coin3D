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

#include <Inventor/scxml/ScXMLEvaluator.h>

/*!
  \class ScXMLEvaluator ScXMLEvaluator.h Inventor/scxml/ScXMLEvaluator.h
  \brief defines an interface for profile-dependent evaluators.

  \ingroup scxml
  \since Coin 3.1
*/

#include <cassert>
#include <cstring>
#include <cstdio>
#include <memory>

#include <Inventor/SbString.h>
#include <Inventor/scxml/ScXMLEvent.h>
#include <Inventor/scxml/ScXMLDocument.h>
#include <Inventor/scxml/ScXMLStateMachine.h>
#include <Inventor/scxml/ScXMLDataElt.h>
#include "base/coinString.h"
#include "scxml/SbStringConvert.h"

// *************************************************************************

using std::strlen;
using std::strcpy;
using std::strcmp;

class ScXMLEvaluator::PImpl {
public:
};

SCXML_OBJECT_ABSTRACT_SOURCE(ScXMLEvaluator);

void
ScXMLEvaluator::initClass(void)
{
  SCXML_OBJECT_INIT_ABSTRACT_CLASS(ScXMLEvaluator, ScXMLObject, "ScXMLObject");

  // init all dataobjs
  ScXMLDataObj::initClass();
  ScXMLConstantDataObj::initClass();
  ScXMLStringDataObj::initClass();
  ScXMLRealDataObj::initClass();
  ScXMLBoolDataObj::initClass();
  ScXMLSbDataObj::initClass();
  ScXMLXMLDataObj::initClass();
  ScXMLExprDataObj::initClass();
  ScXMLReferenceDataObj::initClass();
  ScXMLAndOpExprDataObj::initClass();
  ScXMLOrOpExprDataObj::initClass();
  ScXMLNotOpExprDataObj::initClass();
  ScXMLEqualsOpExprDataObj::initClass();
  ScXMLAddOpExprDataObj::initClass();
  ScXMLSubtractOpExprDataObj::initClass();
  ScXMLMultiplyOpExprDataObj::initClass();
  ScXMLDivideOpExprDataObj::initClass();
  ScXMLNegateOpExprDataObj::initClass();
}

void
ScXMLEvaluator::cleanClass(void)
{
  // clean out all dataobjs
  ScXMLNegateOpExprDataObj::cleanClass();
  ScXMLDivideOpExprDataObj::cleanClass();
  ScXMLMultiplyOpExprDataObj::cleanClass();
  ScXMLSubtractOpExprDataObj::cleanClass();
  ScXMLAddOpExprDataObj::cleanClass();
  ScXMLEqualsOpExprDataObj::cleanClass();
  ScXMLNotOpExprDataObj::cleanClass();
  ScXMLOrOpExprDataObj::cleanClass();
  ScXMLAndOpExprDataObj::cleanClass();
  ScXMLReferenceDataObj::cleanClass();
  ScXMLExprDataObj::cleanClass();
  ScXMLXMLDataObj::cleanClass();
  ScXMLSbDataObj::cleanClass();
  ScXMLBoolDataObj::cleanClass();
  ScXMLRealDataObj::cleanClass();
  ScXMLStringDataObj::cleanClass();
  ScXMLConstantDataObj::cleanClass();
  ScXMLDataObj::cleanClass();

  ScXMLEvaluator::classTypeId = SoType::badType();
}

ScXMLEvaluator::ScXMLEvaluator(void)
: statemachine(nullptr)
{
}

ScXMLEvaluator::~ScXMLEvaluator(void)
{
}

/*!
  Override to perform actions when installed on a state machine.
*/
void
ScXMLEvaluator::setStateMachine(ScXMLStateMachine * sm)
{
  this->statemachine = sm;
}


/*!
  \fn ScXMLDataObj * ScXMLEvaluator::evaluate(const char * expression, ScXMLStateMachine * sm) const
*/

/*!
  \fn ScXMLDataObj * ScXMLEvaluator::locate(const char * location, ScXMLStateMachine * sm) const
*/

/*!
  Does nothing - overridden in derived classes.

  The intention of this function is to clear out temporary variables that
  has the scope of only one event being processed by the scxml state machine.
*/
void
ScXMLEvaluator::clearTemporaryVariables(void)
{
}

// *************************************************************************

/*!
  \class ScXMLDataObj ScXMLEvaluator.h Inventor/scxml/ScXMLEvaluator.h
  \brief base class for evaluator data objects in the SCXML data module

  \ingroup scxml
  \since Coin 3.1
*/

SCXML_OBJECT_ABSTRACT_SOURCE(ScXMLDataObj);

void
ScXMLDataObj::initClass(void)
{
  SCXML_OBJECT_INIT_ABSTRACT_CLASS(ScXMLDataObj, ScXMLObject, "ScXMLObject");
}

void
ScXMLDataObj::setContainer(ScXMLObject * container) {
  if (this->container) {
    delete container;
  }
  this->container = container;
}

void
ScXMLDataObj::cleanClass(void)
{
  ScXMLDataObj::classTypeId = SoType::badType();
}

ScXMLDataObj::ScXMLDataObj(void)
: container(nullptr)
{
}

ScXMLDataObj::~ScXMLDataObj(void)
{
}

// *************************************************************************

/*!
  \class ScXMLConstantDataObj ScXMLEvaluator.h Inventor/scxmlScXMLEvaluator.h
  \brief base class for immediate data values

  \ingroup scxml
  \since Coin 3.1
*/

SCXML_OBJECT_ABSTRACT_SOURCE(ScXMLConstantDataObj);

void
ScXMLConstantDataObj::initClass(void)
{
  SCXML_OBJECT_INIT_ABSTRACT_CLASS(ScXMLConstantDataObj, ScXMLDataObj, "ScXMLDataObj");
}

void
ScXMLConstantDataObj::cleanClass(void)
{
  ScXMLConstantDataObj::classTypeId = SoType::badType();
}

// *************************************************************************

SCXML_OBJECT_SOURCE(ScXMLStringDataObj);

void
ScXMLStringDataObj::initClass(void)
{
  SCXML_OBJECT_INIT_CLASS(ScXMLStringDataObj, ScXMLConstantDataObj, "ScXMLConstantDataObj");
}

void
ScXMLStringDataObj::cleanClass(void)
{
  ScXMLStringDataObj::classTypeId = SoType::badType();
}

ScXMLDataObj *
ScXMLStringDataObj::createFor(const char * strval)
{
  assert(strval && strval[0] == '\'');
  std::unique_ptr<char[]> buf(new char [strlen(strval) + 1]);
  int res = sscanf(strval, "'%[^']'", buf.get());
  if (res == 1) {
    return new ScXMLStringDataObj(buf.get());
  } else {
    // This code path is illegal, but the assert is disabled because the
    // problem should be easy enough to identify by the downstream error, and
    // that error would most likely be handled robustly by the parser.
    // assert(0);
    // An alternative approach would be to construct the StringDataObj
    // on the empty string instead of the faulty one.
    return new ScXMLStringDataObj(strval);
  }
}

ScXMLStringDataObj::ScXMLStringDataObj(void)
: value(nullptr)
{
}

ScXMLStringDataObj::ScXMLStringDataObj(const char * strval)
: value(nullptr)
{
  this->setString(strval);
}

ScXMLStringDataObj::~ScXMLStringDataObj(void)
{
  this->setString(nullptr);
}

void
ScXMLStringDataObj::setString(const char * strptr)
{
  if (this->value) {
    delete [] this->value;
    this->value = nullptr;
  }
  if (strptr) {
    this->value = new char [strlen(strptr) + 1];
    strcpy(this->value, strptr);
  }
}

ScXMLDataObj *
ScXMLStringDataObj::clone(void) const
{
  ScXMLStringDataObj * copy = new ScXMLStringDataObj;
  copy->setString(this->getString());
  return copy;
}

void
ScXMLStringDataObj::convertToString(SbString & str) const
{
  if (!this->value) {
    str = "''";
  } else {
    // FIXME: quote special characters (')
    str.sprintf("'%s'", this->value);
  }
}

// *************************************************************************

SCXML_OBJECT_SOURCE(ScXMLRealDataObj);

void
ScXMLRealDataObj::initClass(void)
{
  SCXML_OBJECT_INIT_CLASS(ScXMLRealDataObj, ScXMLConstantDataObj, "ScXMLConstantDataObj");
}

void
ScXMLRealDataObj::cleanClass(void)
{
  ScXMLRealDataObj::classTypeId = SoType::badType();
}

ScXMLDataObj *
ScXMLRealDataObj::createFor(double value)
{
  return new ScXMLRealDataObj(value);
}

ScXMLRealDataObj::ScXMLRealDataObj(void)
: value(0.0f)
{
}

ScXMLRealDataObj::ScXMLRealDataObj(double realval)
: value(realval)
{
}

ScXMLRealDataObj::~ScXMLRealDataObj(void)
{
}

void
ScXMLRealDataObj::setReal(double real)
{
  this->value = real;
}

ScXMLDataObj *
ScXMLRealDataObj::clone(void) const
{
  ScXMLRealDataObj * copy = new ScXMLRealDataObj;
  copy->setReal(this->getReal());
  return copy;
}

void
ScXMLRealDataObj::convertToString(SbString & str) const
{
  str = SbStringConvert::toString(this->value);
}

// *************************************************************************

SCXML_OBJECT_SOURCE(ScXMLBoolDataObj);

void
ScXMLBoolDataObj::initClass(void)
{
  SCXML_OBJECT_INIT_CLASS(ScXMLBoolDataObj, ScXMLConstantDataObj, "ScXMLConstantDataObj");
}

void
ScXMLBoolDataObj::cleanClass(void)
{
  ScXMLBoolDataObj::classTypeId = SoType::badType();
}

ScXMLDataObj *
ScXMLBoolDataObj::createFor(bool boolval)
{
  return new ScXMLBoolDataObj(boolval);
}

ScXMLBoolDataObj::ScXMLBoolDataObj(void)
: value(false)
{
}

ScXMLBoolDataObj::ScXMLBoolDataObj(bool boolval)
: value(boolval)
{
}

ScXMLBoolDataObj::~ScXMLBoolDataObj(void)
{
}

void
ScXMLBoolDataObj::setBool(bool val)
{
  this->value = val;
}

ScXMLDataObj *
ScXMLBoolDataObj::clone(void) const
{
  ScXMLBoolDataObj * copy = new ScXMLBoolDataObj;
  copy->setBool(this->getBool());
  return copy;
}

void
ScXMLBoolDataObj::convertToString(SbString & str) const
{
  if (this->value) {
    str = "TRUE";
  }
  else {
    str = "FALSE";
  }
}

// *************************************************************************

SCXML_OBJECT_SOURCE(ScXMLSbDataObj);

void
ScXMLSbDataObj::initClass(void)
{
  SCXML_OBJECT_INIT_CLASS(ScXMLSbDataObj, ScXMLConstantDataObj, "ScXMLConstantDataObj");
}

void
ScXMLSbDataObj::cleanClass(void)
{
  ScXMLSbDataObj::classTypeId = SoType::badType();
}

ScXMLDataObj *
ScXMLSbDataObj::createFor(const char * sbvalue)
{
  return new ScXMLSbDataObj(sbvalue);
}

ScXMLSbDataObj::ScXMLSbDataObj(void)
: value(nullptr)
{
}

ScXMLSbDataObj::ScXMLSbDataObj(const char * sbvalue)
: value(nullptr)
{
  this->setSbValue(sbvalue);
}

ScXMLSbDataObj::~ScXMLSbDataObj(void)
{
  this->setSbValue(nullptr);
}

void
ScXMLSbDataObj::setSbValue(const char * sbvalue)
{
  if (this->value) {
    delete [] this->value;
    this->value = nullptr;
  }
  if (sbvalue) {
    this->value = new char [ strlen(sbvalue) + 1 ];
    strcpy(this->value, sbvalue);
  }
}

ScXMLDataObj *
ScXMLSbDataObj::clone(void) const
{
  ScXMLSbDataObj * copy = new ScXMLSbDataObj;
  copy->setSbValue(this->getSbValue());
  return copy;
}

void
ScXMLSbDataObj::convertToString(SbString & str) const
{
  if (!this->value) {
    str = "";
  } else {
    str = this->value;
  }
}

// *************************************************************************

SCXML_OBJECT_SOURCE(ScXMLXMLDataObj);

void
ScXMLXMLDataObj::initClass(void)
{
  SCXML_OBJECT_INIT_CLASS(ScXMLXMLDataObj, ScXMLDataObj, "ScXMLDataObj");
}

void
ScXMLXMLDataObj::cleanClass(void)
{
  ScXMLXMLDataObj::classTypeId = SoType::badType();
}

ScXMLXMLDataObj::ScXMLXMLDataObj(void)
{
}

ScXMLXMLDataObj::~ScXMLXMLDataObj(void)
{
}

ScXMLDataObj *
ScXMLXMLDataObj::clone(void) const
{
  ScXMLXMLDataObj * copy = new ScXMLXMLDataObj;
  // FIXME:
  return copy;
}

// *************************************************************************

SCXML_OBJECT_ABSTRACT_SOURCE(ScXMLExprDataObj);

void
ScXMLExprDataObj::initClass(void)
{
  SCXML_OBJECT_INIT_ABSTRACT_CLASS(ScXMLExprDataObj, ScXMLDataObj, "ScXMLDataObj");
}

void
ScXMLExprDataObj::cleanClass(void)
{
  ScXMLExprDataObj::classTypeId = SoType::badType();
}

ScXMLExprDataObj::ScXMLExprDataObj(void)
: result(nullptr)
{
}

ScXMLExprDataObj::~ScXMLExprDataObj(void)
{
  if (this->result) {
    delete this->result;
    this->result = nullptr;
  }
}

ScXMLDataObj *
ScXMLExprDataObj::evaluate(ScXMLStateMachine * sm)
{
  if (this->result) {
    delete this->result;
    this->result = nullptr;
  }
  bool ok = this->evaluateNow(sm, this->result);
  if (!ok) return nullptr;
  return this->result;
}

// *************************************************************************
/*!
  \class ScXMLReferenceDataObj ScXMLEvaluator.h Inventor/scxml/ScXMLEvaluator.h
  \brief A data object representing a reference to another object in the data model.

  \ingroup scxml
*/

SCXML_OBJECT_SOURCE(ScXMLReferenceDataObj);

void
ScXMLReferenceDataObj::initClass(void)
{
  SCXML_OBJECT_INIT_CLASS(ScXMLReferenceDataObj, ScXMLExprDataObj, "ScXMLExprDataObj");
}

void
ScXMLReferenceDataObj::cleanClass(void)
{
  ScXMLReferenceDataObj::classTypeId = SoType::badType();
}

ScXMLDataObj *
ScXMLReferenceDataObj::createFor(const char * reference)
{
  return new ScXMLReferenceDataObj(reference);
}

ScXMLReferenceDataObj::ScXMLReferenceDataObj(void)
: reference(nullptr)
{
}

ScXMLReferenceDataObj::ScXMLReferenceDataObj(const char * referencestr)
: reference(nullptr)
{
  this->setReference(referencestr);
}

ScXMLReferenceDataObj::~ScXMLReferenceDataObj(void)
{
  this->setReference(nullptr);
}

void
ScXMLReferenceDataObj::setReference(const char * referencestr)
{
  if (this->reference) {
    delete [] this->reference;
    this->reference = nullptr;
  }
  if (referencestr) {
    this->reference = new char [ strlen(referencestr) + 1 ];
    strcpy(this->reference, referencestr);
  }
}

bool
ScXMLReferenceDataObj::evaluateNow(ScXMLStateMachine * sm, ScXMLDataObj *& pointer) const
{
  assert(this->reference);

  ScXMLEvaluator * evaluator = sm->getEvaluator();
  assert(evaluator);

  ScXMLDataObj * obj = evaluator->locate(this->reference);
  if (!obj) {
    return false;
  }

  ScXMLConstantDataObj * valueobj = nullptr;
  if (obj->isOfType(ScXMLExprDataObj::getClassTypeId())) {
    ScXMLExprDataObj * exprobj = static_cast<ScXMLExprDataObj *>(obj);
    ScXMLDataObj * dataobj = exprobj->evaluate(sm);
    if (!dataobj) {
      return false;
    }
    if (!dataobj->isOfType(ScXMLConstantDataObj::getClassTypeId())) {
      return false;
    }
    valueobj = static_cast<ScXMLConstantDataObj *>(dataobj);
  } else {
    // assuming const-obj
    if (!obj->isOfType(ScXMLConstantDataObj::getClassTypeId())) {
      return false;
    }
    valueobj = static_cast<ScXMLConstantDataObj *>(obj);
  }
  pointer = valueobj->clone();
  return true;
}

// *************************************************************************
// logical operators

/*!
  \class ScXMLAndOpExprDataObj ScXMLEvaluator.h Inventor/scxml/ScXMLEvaluator.h
  \brief Implements the logical AND operator.

  \ingroup scxml
*/
SCXML_OBJECT_SOURCE(ScXMLAndOpExprDataObj);

void
ScXMLAndOpExprDataObj::initClass(void)
{
  SCXML_OBJECT_INIT_CLASS(ScXMLAndOpExprDataObj, ScXMLExprDataObj, "ScXMLExprDataObj");
}

void
ScXMLAndOpExprDataObj::cleanClass(void)
{
  ScXMLAndOpExprDataObj::classTypeId = SoType::badType();
}

ScXMLDataObj *
ScXMLAndOpExprDataObj::createFor(ScXMLDataObj * lhs, ScXMLDataObj * rhs)
{
  assert(lhs && rhs);
  if (lhs->isOfType(ScXMLBoolDataObj::getClassTypeId())) {
    ScXMLBoolDataObj * lhsbool = static_cast<ScXMLBoolDataObj *>(lhs);
    if (lhsbool->getBool()) {
      delete lhs;
      return rhs;
    } else {
      delete rhs;
      return lhs;
    }
  }
  if (rhs->isOfType(ScXMLBoolDataObj::getClassTypeId())) {
    ScXMLBoolDataObj * rhsbool = static_cast<ScXMLBoolDataObj *>(rhs);
    if (rhsbool->getBool()) {
      delete rhs;
      return lhs;
    } else {
      delete lhs;
      return rhs;
    }
  }
  return new ScXMLAndOpExprDataObj(lhs, rhs);
}

ScXMLAndOpExprDataObj::ScXMLAndOpExprDataObj(void)
: lhs(nullptr), rhs(nullptr)
{
}

ScXMLAndOpExprDataObj::ScXMLAndOpExprDataObj(ScXMLDataObj * lhsptr, ScXMLDataObj * rhsptr)
: lhs(lhsptr), rhs(rhsptr)
{
}

ScXMLAndOpExprDataObj::~ScXMLAndOpExprDataObj(void)
{
  if (this->lhs) {
    delete this->lhs;
    this->lhs = nullptr;
  }
  if (this->rhs) {
    delete this->rhs;
    this->rhs = nullptr;
  }
}

void
ScXMLAndOpExprDataObj::setLHS(ScXMLDataObj * lhsptr)
{
  this->lhs = lhsptr;
}

void
ScXMLAndOpExprDataObj::setRHS(ScXMLDataObj * rhsptr)
{
  this->rhs = rhsptr;
}

bool
ScXMLAndOpExprDataObj::evaluateNow(ScXMLStateMachine * sm, ScXMLDataObj *& pointer) const
{
  assert(this->lhs && this->rhs);
  ScXMLBoolDataObj * lhsbool = nullptr, * rhsbool = nullptr;

  if (this->lhs->isOfType(ScXMLExprDataObj::getClassTypeId())) {
    ScXMLExprDataObj * lhsexpr = static_cast<ScXMLExprDataObj *>(this->lhs);
    ScXMLDataObj * evaled = lhsexpr->evaluate(sm);
    if (!evaled) {
      return false;
    }
    if (!evaled->isOfType(ScXMLBoolDataObj::getClassTypeId())) {
      sm->queueInternalEvent("error.eval.minimum.AndOperator.INVALID_LHS");
      return false;
    }
    lhsbool = static_cast<ScXMLBoolDataObj *>(evaled);
  }
  else if (this->lhs->isOfType(ScXMLBoolDataObj::getClassTypeId())) {
    lhsbool = static_cast<ScXMLBoolDataObj *>(this->lhs);
  }
  else {
    sm->queueInternalEvent("error.eval.minimum.AndOperator.INVALID_LHS");
    return false;
  }

  if (!lhsbool->getBool()) {
    // lhs is false, rhs is irrelevant, result is false
    pointer = new ScXMLBoolDataObj(false);
    return true;
  }

  if (this->rhs->isOfType(ScXMLExprDataObj::getClassTypeId())) {
    ScXMLExprDataObj * rhsexpr = static_cast<ScXMLExprDataObj *>(this->rhs);
    ScXMLDataObj * evaled = rhsexpr->evaluate(sm);
    if (!evaled) {
      return false;
    }
    if (!evaled->isOfType(ScXMLBoolDataObj::getClassTypeId())) {
      sm->queueInternalEvent("error.eval.minimum.AndOperator.INVALID_RHS");
      return false;
    }
    rhsbool = static_cast<ScXMLBoolDataObj *>(evaled);
  }
  else if (this->rhs->isOfType(ScXMLBoolDataObj::getClassTypeId())) {
    rhsbool = static_cast<ScXMLBoolDataObj *>(this->rhs);
  }
  else {
    sm->queueInternalEvent("error.eval.minimum.AndOperator.INVALID_RHS");
    return false;
  }

  if (!rhsbool->getBool()) {
    // rhs is false, result is false
    pointer = new ScXMLBoolDataObj(false);
    return true;
  }

  pointer = new ScXMLBoolDataObj(true);
  return true;
}

// *************************************************************************

SCXML_OBJECT_SOURCE(ScXMLOrOpExprDataObj);

void
ScXMLOrOpExprDataObj::initClass(void)
{
  SCXML_OBJECT_INIT_CLASS(ScXMLOrOpExprDataObj, ScXMLExprDataObj, "ScXMLExprDataObj");
}

void
ScXMLOrOpExprDataObj::cleanClass(void)
{
  ScXMLOrOpExprDataObj::classTypeId = SoType::badType();
}

ScXMLDataObj *
ScXMLOrOpExprDataObj::createFor(ScXMLDataObj * lhs, ScXMLDataObj * rhs)
{
  assert(lhs && rhs);
  if (lhs->isOfType(ScXMLBoolDataObj::getClassTypeId())) {
    ScXMLBoolDataObj * lhsbool = static_cast<ScXMLBoolDataObj *>(lhs);
    if (lhsbool->getBool()) {
      delete rhs;
      return lhs;
    } else {
      delete lhs;
      return rhs;
    }
  }
  if (rhs->isOfType(ScXMLBoolDataObj::getClassTypeId())) {
    ScXMLBoolDataObj * rhsbool = static_cast<ScXMLBoolDataObj *>(rhs);
    if (rhsbool->getBool()) {
      delete lhs;
      return rhs;
    } else {
      delete rhs;
      return lhs;
    }
  }
  return new ScXMLOrOpExprDataObj(lhs, rhs);
}

ScXMLOrOpExprDataObj::ScXMLOrOpExprDataObj(void)
: lhs(nullptr), rhs(nullptr)
{
}

ScXMLOrOpExprDataObj::ScXMLOrOpExprDataObj(ScXMLDataObj * lhsptr, ScXMLDataObj * rhsptr)
: lhs(lhsptr), rhs(rhsptr)
{
}

ScXMLOrOpExprDataObj::~ScXMLOrOpExprDataObj(void)
{
  if (this->lhs) {
    delete this->lhs;
    this->lhs = nullptr;
  }
  if (this->rhs) {
    delete this->rhs;
    this->rhs = nullptr;
  }
}

void
ScXMLOrOpExprDataObj::setLHS(ScXMLDataObj * lhsptr)
{
  this->lhs = lhsptr;
}

void
ScXMLOrOpExprDataObj::setRHS(ScXMLDataObj * rhsptr)
{
  this->rhs = rhsptr;
}

bool
ScXMLOrOpExprDataObj::evaluateNow(ScXMLStateMachine * sm, ScXMLDataObj *& pointer) const
{
  assert(this->lhs && this->rhs);
  ScXMLBoolDataObj * lhsbool = nullptr, * rhsbool = nullptr;

  if (this->lhs->isOfType(ScXMLExprDataObj::getClassTypeId())) {
    ScXMLExprDataObj * lhsexpr = static_cast<ScXMLExprDataObj *>(lhs);
    ScXMLDataObj * evaled = lhsexpr->evaluate(sm);
    if (!evaled) {
      return false;
    }
    if (!evaled->isOfType(ScXMLBoolDataObj::getClassTypeId())) {
      sm->queueInternalEvent("error.eval.minimum.OrOperator.INVALID_LHS");
      return false;
    }
    lhsbool = static_cast<ScXMLBoolDataObj *>(evaled);
  }
  else if (this->lhs->isOfType(ScXMLBoolDataObj::getClassTypeId())) {
    lhsbool = static_cast<ScXMLBoolDataObj *>(this->lhs);
  }
  else {
    sm->queueInternalEvent("error.eval.minimum.OrOperator.INVALID_LHS");
    return false;
  }

  if (lhsbool->getBool()) {
    // lhs is true, rhs is irrelevant, result is true
    pointer = new ScXMLBoolDataObj(true);
    return true;
  }

  if (this->rhs->isOfType(ScXMLExprDataObj::getClassTypeId())) {
    ScXMLExprDataObj * rhsexpr = static_cast<ScXMLExprDataObj *>(rhs);
    ScXMLDataObj * evaled = rhsexpr->evaluate(sm);
    if (!evaled) {
      return false;
    }
    if (!evaled->isOfType(ScXMLBoolDataObj::getClassTypeId())) {
      sm->queueInternalEvent("error.eval.minimum.OrOperator.INVALID_RHS");
      return false;
    }
    rhsbool = static_cast<ScXMLBoolDataObj *>(evaled);
  }
  else if (this->rhs->isOfType(ScXMLBoolDataObj::getClassTypeId())) {
    rhsbool = static_cast<ScXMLBoolDataObj *>(this->rhs);
  }
  else {
    sm->queueInternalEvent("error.eval.minimum.OrOperator.INVALID_RHS");
    return false;
  }

  if (rhsbool->getBool()) {
    // rhs is true, result is true
    pointer = new ScXMLBoolDataObj(true);
    return true;
  }

  // neither lhs or rhs were true
  pointer = new ScXMLBoolDataObj(false);
  return true;
}

// *************************************************************************

SCXML_OBJECT_SOURCE(ScXMLNotOpExprDataObj);

void
ScXMLNotOpExprDataObj::initClass(void)
{
  SCXML_OBJECT_INIT_CLASS(ScXMLNotOpExprDataObj, ScXMLExprDataObj, "ScXMLExprDataObj");
}

void
ScXMLNotOpExprDataObj::cleanClass(void)
{
  ScXMLNotOpExprDataObj::classTypeId = SoType::badType();
}

ScXMLDataObj *
ScXMLNotOpExprDataObj::createFor(ScXMLDataObj * rhs)
{
  if (rhs->getTypeId() == ScXMLBoolDataObj::getClassTypeId()) {
    ScXMLBoolDataObj * boolrhs = static_cast<ScXMLBoolDataObj *>(rhs);
    boolrhs->setBool(boolrhs->getBool() ? false : true);
    return boolrhs;
  }
  return new ScXMLNotOpExprDataObj(rhs);
}

ScXMLNotOpExprDataObj::ScXMLNotOpExprDataObj(void)
: rhs(nullptr)
{
}

ScXMLNotOpExprDataObj::ScXMLNotOpExprDataObj(ScXMLDataObj * rhsptr)
: rhs(rhsptr)
{
}

ScXMLNotOpExprDataObj::~ScXMLNotOpExprDataObj(void)
{
  if (this->rhs) {
    delete this->rhs;
    this->rhs = nullptr;
  }
}

void
ScXMLNotOpExprDataObj::setRHS(ScXMLDataObj * rhsptr)
{
  this->rhs = rhsptr;
}

bool
ScXMLNotOpExprDataObj::evaluateNow(ScXMLStateMachine * sm, ScXMLDataObj *& pointer) const
{
  assert(this->rhs);
  ScXMLBoolDataObj * rhsbool = nullptr;
  if (this->rhs->isOfType(ScXMLExprDataObj::getClassTypeId())) {
    ScXMLExprDataObj * rhsexpr = static_cast<ScXMLExprDataObj *>(rhs);
    ScXMLDataObj * evaled = rhsexpr->evaluate(sm);
    if (!evaled) {
      return false;
    }
    if (!evaled->isOfType(ScXMLBoolDataObj::getClassTypeId())) {
      sm->queueInternalEvent("error.eval.minimum.NotOperator.INVALID_RHS");
      return false;
    }
    rhsbool = static_cast<ScXMLBoolDataObj *>(evaled);
  }
  else if (this->rhs->isOfType(ScXMLBoolDataObj::getClassTypeId())) {
    rhsbool = static_cast<ScXMLBoolDataObj *>(this->rhs);
  }
  else {
    sm->queueInternalEvent("error.eval.minimum.NotOperator.INVALID_RHS");
    return false;
  }

  pointer = new ScXMLBoolDataObj(rhsbool->getBool() ? false : true);
  return true;
}

// *************************************************************************

SCXML_OBJECT_SOURCE(ScXMLEqualsOpExprDataObj);

void
ScXMLEqualsOpExprDataObj::initClass(void)
{
  SCXML_OBJECT_INIT_CLASS(ScXMLEqualsOpExprDataObj, ScXMLExprDataObj, "ScXMLExprDataObj");
}

void
ScXMLEqualsOpExprDataObj::cleanClass(void)
{
  ScXMLEqualsOpExprDataObj::classTypeId = SoType::badType();
}

ScXMLDataObj *
ScXMLEqualsOpExprDataObj::createFor(ScXMLDataObj * lhs, ScXMLDataObj * rhs)
{
  if (lhs->getTypeId() == ScXMLRealDataObj::getClassTypeId() &&
      rhs->getTypeId() == ScXMLRealDataObj::getClassTypeId()) {
    ScXMLRealDataObj * reallhs = static_cast<ScXMLRealDataObj *>(lhs);
    ScXMLRealDataObj * realrhs = static_cast<ScXMLRealDataObj *>(rhs);
    ScXMLBoolDataObj * folded =
      new ScXMLBoolDataObj(reallhs->getReal() == realrhs->getReal() ? true : false);
    delete lhs;
    delete rhs;
    return folded;
  }
  if (lhs->getTypeId() == ScXMLBoolDataObj::getClassTypeId() &&
      rhs->getTypeId() == ScXMLBoolDataObj::getClassTypeId()) {
    ScXMLBoolDataObj * boollhs = static_cast<ScXMLBoolDataObj *>(lhs);
    ScXMLBoolDataObj * boolrhs = static_cast<ScXMLBoolDataObj *>(rhs);
    ScXMLBoolDataObj * folded =
      new ScXMLBoolDataObj(boollhs->getBool() == boolrhs->getBool() ? true : false);
    delete lhs;
    delete rhs;
    return folded;
  }
  if (lhs->getTypeId() == ScXMLStringDataObj::getClassTypeId() &&
      rhs->getTypeId() == ScXMLStringDataObj::getClassTypeId()) {
    ScXMLStringDataObj * stringlhs = static_cast<ScXMLStringDataObj *>(lhs);
    ScXMLStringDataObj * stringrhs = static_cast<ScXMLStringDataObj *>(rhs);
    ScXMLBoolDataObj * folded =
      new ScXMLBoolDataObj(strcmp(stringlhs->getString(), stringrhs->getString()) == 0 ? true : false);
    delete lhs;
    delete rhs;
    return folded;
  }
  return new ScXMLEqualsOpExprDataObj(lhs, rhs);
}

ScXMLEqualsOpExprDataObj::ScXMLEqualsOpExprDataObj(void)
: lhs(nullptr), rhs(nullptr)
{
}

ScXMLEqualsOpExprDataObj::ScXMLEqualsOpExprDataObj(ScXMLDataObj * lhsptr, ScXMLDataObj * rhsptr)
: lhs(lhsptr), rhs(rhsptr)
{
}

ScXMLEqualsOpExprDataObj::~ScXMLEqualsOpExprDataObj(void)
{
  if (this->lhs) {
    delete this->lhs;
    this->lhs = nullptr;
  }
  if (this->rhs) {
    delete this->rhs;
    this->rhs = nullptr;
  }
}

void
ScXMLEqualsOpExprDataObj::setLHS(ScXMLDataObj * lhsptr)
{
  this->lhs = lhsptr;
}

void
ScXMLEqualsOpExprDataObj::setRHS(ScXMLDataObj * rhsptr)
{
  this->rhs = rhsptr;
}

bool
ScXMLEqualsOpExprDataObj::evaluateNow(ScXMLStateMachine * sm, ScXMLDataObj *& pointer) const
{
  assert(this->lhs && this->rhs);
  ScXMLDataObj * lhsevaled = nullptr, * rhsevaled = nullptr;

  if (this->lhs->isOfType(ScXMLExprDataObj::getClassTypeId())) {
    ScXMLExprDataObj * lhsexpr = static_cast<ScXMLExprDataObj *>(this->lhs);
    ScXMLDataObj * evaled = lhsexpr->evaluate(sm);
    if (!evaled) {
      return false;
    }
    lhsevaled = evaled;
  }
  else {
    lhsevaled = this->lhs;
  }

  if (this->rhs->isOfType(ScXMLExprDataObj::getClassTypeId())) {
    ScXMLExprDataObj * rhsexpr = static_cast<ScXMLExprDataObj *>(this->rhs);
    ScXMLDataObj * evaled = rhsexpr->evaluate(sm);
    if (!evaled) { return false; }
    rhsevaled = evaled;
  }
  else {
    rhsevaled = this->rhs;
  }

  if (lhsevaled->getTypeId() == rhsevaled->getTypeId()) {
    if (lhsevaled->getTypeId() == ScXMLBoolDataObj::getClassTypeId()) {
      ScXMLBoolDataObj * boollhs = static_cast<ScXMLBoolDataObj *>(lhsevaled);
      ScXMLBoolDataObj * boolrhs = static_cast<ScXMLBoolDataObj *>(rhsevaled);
      if (boollhs->getBool() == boolrhs->getBool()) {
        pointer = new ScXMLBoolDataObj(true);
        return true;
      }
    }
    else if (lhsevaled->getTypeId() == ScXMLRealDataObj::getClassTypeId()) {
      ScXMLRealDataObj * reallhs = static_cast<ScXMLRealDataObj *>(lhsevaled);
      ScXMLRealDataObj * realrhs = static_cast<ScXMLRealDataObj *>(rhsevaled);
      // FIXME: use epsilon comparison?
      if (reallhs->getReal() == realrhs->getReal()) {
        pointer = new ScXMLBoolDataObj(true);
        return true;
      }
    }
    else if (lhsevaled->getTypeId() == ScXMLStringDataObj::getClassTypeId()) {
      ScXMLStringDataObj * stringlhs = static_cast<ScXMLStringDataObj *>(lhsevaled);
      ScXMLStringDataObj * stringrhs = static_cast<ScXMLStringDataObj *>(rhsevaled);
      if (strcmp(stringlhs->getString(), stringrhs->getString()) == 0) {
        pointer = new ScXMLBoolDataObj(true);
        return true;
      }
    }
  }

  pointer = new ScXMLBoolDataObj(false);
  return true;
}

// *************************************************************************
// arithmetic operators

SCXML_OBJECT_SOURCE(ScXMLAddOpExprDataObj);

void
ScXMLAddOpExprDataObj::initClass(void)
{
  SCXML_OBJECT_INIT_CLASS(ScXMLAddOpExprDataObj, ScXMLExprDataObj, "ScXMLExprDataObj");
}

void
ScXMLAddOpExprDataObj::cleanClass(void)
{
  ScXMLAddOpExprDataObj::classTypeId = SoType::badType();
}

ScXMLDataObj *
ScXMLAddOpExprDataObj::createFor(ScXMLDataObj * lhs, ScXMLDataObj * rhs)
{
  if (lhs->isOfType(ScXMLRealDataObj::getClassTypeId()) &&
      rhs->isOfType(ScXMLRealDataObj::getClassTypeId())) {
    ScXMLRealDataObj * reallhs = static_cast<ScXMLRealDataObj *>(lhs);
    ScXMLRealDataObj * realrhs = static_cast<ScXMLRealDataObj *>(rhs);
    ScXMLRealDataObj * folded = new ScXMLRealDataObj(reallhs->getReal() + realrhs->getReal());
    delete lhs;
    delete rhs;
    return folded;
  }
  return new ScXMLAddOpExprDataObj(lhs, rhs);
}

ScXMLAddOpExprDataObj::ScXMLAddOpExprDataObj(void)
: lhs(nullptr), rhs(nullptr)
{
}

ScXMLAddOpExprDataObj::ScXMLAddOpExprDataObj(ScXMLDataObj * lhsptr, ScXMLDataObj * rhsptr)
: lhs(lhsptr), rhs(rhsptr)
{
}

ScXMLAddOpExprDataObj::~ScXMLAddOpExprDataObj(void)
{
  if (this->lhs) {
    delete this->lhs;
    this->lhs = nullptr;
  }
  if (this->rhs) {
    delete this->rhs;
    this->rhs = nullptr;
  }
}

void
ScXMLAddOpExprDataObj::setLHS(ScXMLDataObj * lhsptr)
{
  this->lhs = lhsptr;
}

void
ScXMLAddOpExprDataObj::setRHS(ScXMLDataObj * rhsptr)
{
  this->rhs = rhsptr;
}

bool
ScXMLAddOpExprDataObj::evaluateNow(ScXMLStateMachine * sm, ScXMLDataObj *& pointer) const
{
  assert(this->lhs && this->rhs);
  ScXMLRealDataObj * lhsreal = nullptr, * rhsreal = nullptr;

  if (this->lhs->isOfType(ScXMLExprDataObj::getClassTypeId())) {
    ScXMLExprDataObj * lhsexpr = static_cast<ScXMLExprDataObj *>(this->lhs);
    ScXMLDataObj * evaled = lhsexpr->evaluate(sm);
    if (!evaled) { return false; }
    assert(evaled->isOfType(ScXMLRealDataObj::getClassTypeId()));
    lhsreal = static_cast<ScXMLRealDataObj *>(evaled);
  }
  else if (this->lhs->isOfType(ScXMLRealDataObj::getClassTypeId())) {
    lhsreal = static_cast<ScXMLRealDataObj *>(this->lhs);
  }
  else {
    sm->queueInternalEvent("error.eval.minimum.AddOperator.INVALID_LHS");
    return false;
  }

  if (this->rhs->isOfType(ScXMLExprDataObj::getClassTypeId())) {
    ScXMLExprDataObj * rhsexpr = static_cast<ScXMLExprDataObj *>(this->rhs);
    ScXMLDataObj * evaled = rhsexpr->evaluate(sm);
    if (!evaled) {
      return false;
    }
    assert(evaled->isOfType(ScXMLRealDataObj::getClassTypeId()));
    rhsreal = static_cast<ScXMLRealDataObj *>(evaled);
  }
  else if (this->rhs->isOfType(ScXMLRealDataObj::getClassTypeId())) {
    rhsreal = static_cast<ScXMLRealDataObj *>(this->rhs);
  }
  else {
    sm->queueInternalEvent("error.eval.minimum.AddOperator.INVALID_RHS");
    return false;
  }

  pointer = new ScXMLRealDataObj(lhsreal->getReal() + rhsreal->getReal());
  return true;
}

// *************************************************************************

SCXML_OBJECT_SOURCE(ScXMLSubtractOpExprDataObj);

void
ScXMLSubtractOpExprDataObj::initClass(void)
{
  SCXML_OBJECT_INIT_CLASS(ScXMLSubtractOpExprDataObj, ScXMLExprDataObj, "ScXMLExprDataObj");
}

void
ScXMLSubtractOpExprDataObj::cleanClass(void)
{
  ScXMLSubtractOpExprDataObj::classTypeId = SoType::badType();
}

ScXMLDataObj *
ScXMLSubtractOpExprDataObj::createFor(ScXMLDataObj * lhs, ScXMLDataObj * rhs)
{
  if (lhs->isOfType(ScXMLRealDataObj::getClassTypeId()) &&
      rhs->isOfType(ScXMLRealDataObj::getClassTypeId())) {
    ScXMLRealDataObj * reallhs = static_cast<ScXMLRealDataObj *>(lhs);
    ScXMLRealDataObj * realrhs = static_cast<ScXMLRealDataObj *>(rhs);
    ScXMLRealDataObj * folded = new ScXMLRealDataObj(reallhs->getReal() - realrhs->getReal());
    delete lhs;
    delete rhs;
    return folded;
  }
  return new ScXMLSubtractOpExprDataObj(lhs, rhs);
}

ScXMLSubtractOpExprDataObj::ScXMLSubtractOpExprDataObj(void)
: lhs(nullptr), rhs(nullptr)
{
}

ScXMLSubtractOpExprDataObj::ScXMLSubtractOpExprDataObj(ScXMLDataObj * lhsptr, ScXMLDataObj * rhsptr)
: lhs(lhsptr), rhs(rhsptr)
{
}

ScXMLSubtractOpExprDataObj::~ScXMLSubtractOpExprDataObj(void)
{
  if (this->lhs) {
    delete this->lhs;
    this->lhs = nullptr;
  }
  if (this->rhs) {
    delete this->rhs;
    this->rhs = nullptr;
  }
}

void
ScXMLSubtractOpExprDataObj::setLHS(ScXMLDataObj * lhsptr)
{
  this->lhs = lhsptr;
}

void
ScXMLSubtractOpExprDataObj::setRHS(ScXMLDataObj * rhsptr)
{
  this->rhs = rhsptr;
}

bool
ScXMLSubtractOpExprDataObj::evaluateNow(ScXMLStateMachine * sm, ScXMLDataObj *& pointer) const
{
  assert(this->lhs && this->rhs);
  ScXMLRealDataObj * lhsreal = nullptr, * rhsreal = nullptr;

  if (this->lhs->isOfType(ScXMLExprDataObj::getClassTypeId())) {
    ScXMLExprDataObj * lhsexpr = static_cast<ScXMLExprDataObj *>(this->lhs);
    ScXMLDataObj * evaled = lhsexpr->evaluate(sm);
    if (!evaled) {
      return false;
    }
    assert(evaled->isOfType(ScXMLRealDataObj::getClassTypeId()));
    lhsreal = static_cast<ScXMLRealDataObj *>(evaled);
  }
  else if (this->lhs->isOfType(ScXMLRealDataObj::getClassTypeId())) {
    lhsreal = static_cast<ScXMLRealDataObj *>(this->lhs);
  }
  else {
    sm->queueInternalEvent("error.eval.minimum.SubtractOperator.INVALID_LHS");
    return false;
  }

  if (this->rhs->isOfType(ScXMLExprDataObj::getClassTypeId())) {
    ScXMLExprDataObj * rhsexpr = static_cast<ScXMLExprDataObj *>(this->rhs);
    ScXMLDataObj * evaled = rhsexpr->evaluate(sm);
    if (!evaled) {
      return false;
    }
    assert(evaled->isOfType(ScXMLRealDataObj::getClassTypeId()));
    rhsreal = static_cast<ScXMLRealDataObj *>(evaled);
  }
  else if (this->rhs->isOfType(ScXMLRealDataObj::getClassTypeId())) {
    rhsreal = static_cast<ScXMLRealDataObj *>(this->rhs);
  }
  else {
    sm->queueInternalEvent("error.eval.minimum.SubtractOperator.INVALID_RHS");
    return false;
  }

  pointer = new ScXMLRealDataObj(lhsreal->getReal() - rhsreal->getReal());
  return true;
}

// *************************************************************************

SCXML_OBJECT_SOURCE(ScXMLMultiplyOpExprDataObj);

void
ScXMLMultiplyOpExprDataObj::initClass(void)
{
  SCXML_OBJECT_INIT_CLASS(ScXMLMultiplyOpExprDataObj, ScXMLExprDataObj, "ScXMLExprDataObj");
}

void
ScXMLMultiplyOpExprDataObj::cleanClass(void)
{
  ScXMLMultiplyOpExprDataObj::classTypeId = SoType::badType();
}

ScXMLDataObj *
ScXMLMultiplyOpExprDataObj::createFor(ScXMLDataObj * lhs, ScXMLDataObj * rhs)
{
  if (lhs->isOfType(ScXMLRealDataObj::getClassTypeId()) &&
      rhs->isOfType(ScXMLRealDataObj::getClassTypeId())) {
    ScXMLRealDataObj * reallhs = static_cast<ScXMLRealDataObj *>(lhs);
    ScXMLRealDataObj * realrhs = static_cast<ScXMLRealDataObj *>(rhs);
    ScXMLRealDataObj * folded = new ScXMLRealDataObj(reallhs->getReal() * realrhs->getReal());
    delete lhs;
    delete rhs;
    return folded;
  }
  return new ScXMLMultiplyOpExprDataObj(lhs, rhs);
}

ScXMLMultiplyOpExprDataObj::ScXMLMultiplyOpExprDataObj(void)
: lhs(nullptr), rhs(nullptr)
{
}

ScXMLMultiplyOpExprDataObj::ScXMLMultiplyOpExprDataObj(ScXMLDataObj * lhsptr, ScXMLDataObj * rhsptr)
: lhs(lhsptr), rhs(rhsptr)
{
}

ScXMLMultiplyOpExprDataObj::~ScXMLMultiplyOpExprDataObj(void)
{
  if (this->lhs) {
    delete this->lhs;
    this->lhs = nullptr;
  }
  if (this->rhs) {
    delete this->rhs;
    this->rhs = nullptr;
  }
}

void
ScXMLMultiplyOpExprDataObj::setLHS(ScXMLDataObj * lhsptr)
{
  this->lhs = lhsptr;
}

void
ScXMLMultiplyOpExprDataObj::setRHS(ScXMLDataObj * rhsptr)
{
  this->rhs = rhsptr;
}

bool
ScXMLMultiplyOpExprDataObj::evaluateNow(ScXMLStateMachine * sm, ScXMLDataObj *& pointer) const
{
  assert(this->lhs && this->rhs);
  ScXMLRealDataObj * lhsreal = nullptr, * rhsreal = nullptr;

  if (this->lhs->isOfType(ScXMLExprDataObj::getClassTypeId())) {
    ScXMLExprDataObj * lhsexpr = static_cast<ScXMLExprDataObj *>(this->lhs);
    ScXMLDataObj * evaled = lhsexpr->evaluate(sm);
    if (!evaled) {
      return false;
    }
    assert(evaled->isOfType(ScXMLRealDataObj::getClassTypeId()));
    lhsreal = static_cast<ScXMLRealDataObj *>(evaled);
  }
  else if (this->lhs->isOfType(ScXMLRealDataObj::getClassTypeId())) {
    lhsreal = static_cast<ScXMLRealDataObj *>(this->lhs);
  }
  else {
    sm->queueInternalEvent("error.eval.minimum.MultiplyOperator.INVALID_LHS");
    return false;
  }

  if (this->rhs->isOfType(ScXMLExprDataObj::getClassTypeId())) {
    ScXMLExprDataObj * rhsexpr = static_cast<ScXMLExprDataObj *>(this->rhs);
    ScXMLDataObj * evaled = rhsexpr->evaluate(sm);
    if (!evaled) {
      return false;
    }
    assert(evaled->isOfType(ScXMLRealDataObj::getClassTypeId()));
    rhsreal = static_cast<ScXMLRealDataObj *>(evaled);
  }
  else if (this->rhs->isOfType(ScXMLRealDataObj::getClassTypeId())) {
    rhsreal = static_cast<ScXMLRealDataObj *>(this->rhs);
  }
  else {
    sm->queueInternalEvent("error.eval.minimum.MultiplyOperator.INVALID_RHS");
    return false;
  }

  pointer = new ScXMLRealDataObj(lhsreal->getReal() * rhsreal->getReal());
  return true;
}

// *************************************************************************

SCXML_OBJECT_SOURCE(ScXMLDivideOpExprDataObj);

void
ScXMLDivideOpExprDataObj::initClass(void)
{
  SCXML_OBJECT_INIT_CLASS(ScXMLDivideOpExprDataObj, ScXMLExprDataObj, "ScXMLExprDataObj");
}

void
ScXMLDivideOpExprDataObj::cleanClass(void)
{
  ScXMLDivideOpExprDataObj::classTypeId = SoType::badType();
}

ScXMLDataObj *
ScXMLDivideOpExprDataObj::createFor(ScXMLDataObj * lhs, ScXMLDataObj * rhs)
{
  if (lhs->isOfType(ScXMLRealDataObj::getClassTypeId()) &&
      rhs->isOfType(ScXMLRealDataObj::getClassTypeId())) {
    ScXMLRealDataObj * reallhs = static_cast<ScXMLRealDataObj *>(lhs);
    ScXMLRealDataObj * realrhs = static_cast<ScXMLRealDataObj *>(rhs);
    ScXMLRealDataObj * folded = new ScXMLRealDataObj(reallhs->getReal() / realrhs->getReal());
    delete lhs;
    delete rhs;
    return folded;
  }
  return new ScXMLDivideOpExprDataObj(lhs, rhs);
}

ScXMLDivideOpExprDataObj::ScXMLDivideOpExprDataObj(void)
: lhs(nullptr), rhs(nullptr)
{
}

ScXMLDivideOpExprDataObj::ScXMLDivideOpExprDataObj(ScXMLDataObj * lhsptr, ScXMLDataObj * rhsptr)
: lhs(lhsptr), rhs(rhsptr)
{
}

ScXMLDivideOpExprDataObj::~ScXMLDivideOpExprDataObj(void)
{
  if (this->lhs) {
    delete this->lhs;
    this->lhs = nullptr;
  }
  if (this->rhs) {
    delete this->rhs;
    this->rhs = nullptr;
  }
}

void
ScXMLDivideOpExprDataObj::setLHS(ScXMLDataObj * lhsptr)
{
  this->lhs = lhsptr;
}

void
ScXMLDivideOpExprDataObj::setRHS(ScXMLDataObj * rhsptr)
{
  this->rhs = rhsptr;
}

bool
ScXMLDivideOpExprDataObj::evaluateNow(ScXMLStateMachine * sm, ScXMLDataObj *& pointer) const
{
  assert(this->lhs && this->rhs);
  ScXMLRealDataObj * lhsreal = nullptr, * rhsreal = nullptr;

  if (this->lhs->isOfType(ScXMLExprDataObj::getClassTypeId())) {
    ScXMLExprDataObj * lhsexpr = static_cast<ScXMLExprDataObj *>(this->lhs);
    ScXMLDataObj * evaled = lhsexpr->evaluate(sm);
    if (!evaled) {
      return false;
    }
    assert(evaled->isOfType(ScXMLRealDataObj::getClassTypeId()));
    lhsreal = static_cast<ScXMLRealDataObj *>(evaled);
  }
  else if (this->lhs->isOfType(ScXMLRealDataObj::getClassTypeId())) {
    lhsreal = static_cast<ScXMLRealDataObj *>(this->lhs);
  }
  else {
    sm->queueInternalEvent("error.eval.minimum.DivideOperator.INVALID_LHS");
    return false;
  }

  if (this->rhs->isOfType(ScXMLExprDataObj::getClassTypeId())) {
    ScXMLExprDataObj * rhsexpr = static_cast<ScXMLExprDataObj *>(this->rhs);
    ScXMLDataObj * evaled = rhsexpr->evaluate(sm);
    if (!evaled) {
      return false;
    }
    assert(evaled->isOfType(ScXMLRealDataObj::getClassTypeId()));
    rhsreal = static_cast<ScXMLRealDataObj *>(evaled);
  }
  else if (this->rhs->isOfType(ScXMLRealDataObj::getClassTypeId())) {
    rhsreal = static_cast<ScXMLRealDataObj *>(this->rhs);
  }
  else {
    sm->queueInternalEvent("error.eval.minimum.DivideOperator.INVALID_RHS");
    return false;
  }

  if (rhsreal->getReal() == 0.0) {
    sm->queueInternalEvent("error.eval.minimum.DivideOperator.DIVIDE_BY_ZERO");
    pointer = new ScXMLRealDataObj(0.0f);
    return true;
  }

  pointer = new ScXMLRealDataObj(lhsreal->getReal() / rhsreal->getReal());
  return true;
}

// *************************************************************************

SCXML_OBJECT_SOURCE(ScXMLNegateOpExprDataObj);

void
ScXMLNegateOpExprDataObj::initClass(void)
{
  SCXML_OBJECT_INIT_CLASS(ScXMLNegateOpExprDataObj, ScXMLExprDataObj, "ScXMLExprDataObj");
}

void
ScXMLNegateOpExprDataObj::cleanClass(void)
{
  ScXMLNegateOpExprDataObj::classTypeId = SoType::badType();
}

ScXMLDataObj *
ScXMLNegateOpExprDataObj::createFor(ScXMLDataObj * rhs)
{
  if (rhs->isOfType(ScXMLRealDataObj::getClassTypeId())) {
    ScXMLRealDataObj * rhsreal = static_cast<ScXMLRealDataObj *>(rhs);
    rhsreal->setReal(-(rhsreal->getReal()));
    return rhsreal;
  }
  return new ScXMLNegateOpExprDataObj(rhs);
}

ScXMLNegateOpExprDataObj::ScXMLNegateOpExprDataObj(void)
: rhs(nullptr)
{
}

ScXMLNegateOpExprDataObj::ScXMLNegateOpExprDataObj(ScXMLDataObj * rhsptr)
: rhs(rhsptr)
{
}

ScXMLNegateOpExprDataObj::~ScXMLNegateOpExprDataObj(void)
{
  if (this->rhs) {
    delete this->rhs;
    this->rhs = nullptr;
  }
}

void
ScXMLNegateOpExprDataObj::setRHS(ScXMLDataObj * rhsptr)
{
  this->rhs = rhsptr;
}

bool
ScXMLNegateOpExprDataObj::evaluateNow(ScXMLStateMachine * sm, ScXMLDataObj *& pointer) const
{
  assert(this->rhs);
  ScXMLRealDataObj * rhsevaled = nullptr;
  if (this->rhs->isOfType(ScXMLExprDataObj::getClassTypeId())) {
    ScXMLExprDataObj * rhsexpr = static_cast<ScXMLExprDataObj *>(this->rhs);
    ScXMLDataObj * evaled = rhsexpr->evaluate(sm);
    if (!evaled) {
      return false;
    }
    rhsevaled = static_cast<ScXMLRealDataObj *>(evaled);
  }
  else if (this->rhs->isOfType(ScXMLRealDataObj::getClassTypeId())) {
    rhsevaled = static_cast<ScXMLRealDataObj *>(this->rhs);
  }
  else {
    sm->queueInternalEvent("error.eval.minimum.Negate.INVALID_RHS");
    return false;
  }

  pointer = new ScXMLRealDataObj(-(rhsevaled->getReal()));
  return true;
}
