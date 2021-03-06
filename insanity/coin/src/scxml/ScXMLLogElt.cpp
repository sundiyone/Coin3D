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

#include <Inventor/scxml/ScXMLLogElt.h>

/*!
  \class ScXMLLogElt ScXMLLogElt.h Inventor/scxml/ScXMLLogElt.h
  \brief implements the &lt;log&gt; SCXML element.

  \ingroup scxml
*/

#include <cassert>
#include <cstring>

#include <Inventor/errors/SoDebugError.h>
#include <Inventor/C/XML/element.h>
#include <Inventor/scxml/ScXMLEvent.h>
#include <Inventor/scxml/ScXMLStateMachine.h>
#include <Inventor/scxml/ScXMLCoinEvaluator.h>

#include "scxml/ScXMLCommonP.h"
#include "SbBasicP.h"

// *************************************************************************

class ScXMLLogEltReader : public ScXMLEltReader {
public:
  ScXMLLogEltReader(void);
  virtual ScXMLElt * read(ScXMLElt * container, cc_xml_elt * xmlelt, ScXMLDocument * doc, ScXMLStateMachine * sm);
};

ScXMLLogEltReader::ScXMLLogEltReader(void)
: ScXMLEltReader("log")
{
}

ScXMLElt *
ScXMLLogEltReader::read(ScXMLElt * container, cc_xml_elt * xmlelt, ScXMLDocument * COIN_UNUSED_ARG(doc), ScXMLStateMachine * COIN_UNUSED_ARG(sm))
{
  assert(container && xmlelt);
  ScXMLLogElt * log = new ScXMLLogElt;
  log->setContainer(container);
  this->setXMLAttributes(log, xmlelt);

  // handle XML attributes
  if (unlikely(!log->handleXMLAttributes())) {
    delete log;
    return nullptr;
  }

  const int numchildren = cc_xml_elt_get_num_children(xmlelt);
  for (int c = 0; c < numchildren; ++c) {
    cc_xml_elt * element = cc_xml_elt_get_child(xmlelt, c);
    const char * elementtype = cc_xml_elt_get_type(element);

    if (std::strcmp(elementtype, COIN_XML_CDATA_TYPE) == 0) {
      // ignore CDATA
      continue;
    }

    SoDebugError::post("ScXMLElseEltReader::read",
                       "<log> contains unexpected <%s> element", elementtype);
    delete log;
    return nullptr;
  }

  return log;
}

// *************************************************************************

class ScXMLLogElt::PImpl {
};

#define PRIVATE

SCXML_ELEMENT_SOURCE(ScXMLLogElt);

void
ScXMLLogElt::initClass(void)
{
  SCXML_OBJECT_INIT_CLASS(ScXMLLogElt, ScXMLExecutableElt, "ScXMLExecutableElt");
  SCXML_ELEMENT_REGISTER_READER(ScXMLLogElt, "log", ScXMLLogEltReader);
}

void
ScXMLLogElt::cleanClass(void)
{
  SCXML_ELEMENT_UNREGISTER_READER(ScXMLLogElt);
  ScXMLLogElt::classTypeId = SoType::badType();
}

ScXMLLogElt::ScXMLLogElt(void)
: label(nullptr),
  expr(nullptr),
  level(nullptr)
{
}

ScXMLLogElt::~ScXMLLogElt(void)
{
  this->setLabelAttribute(nullptr);
  this->setExprAttribute(nullptr);
  this->setLevelAttribute(nullptr);
}

void
ScXMLLogElt::setLabelAttribute(const char * labelstr)
{
  SCXML__SET_ATTRIBUTE_VALUE(this->label, "label", labelstr);
}

// const char * getLabelAttribute(void) const { return this->label; }

void
ScXMLLogElt::setExprAttribute(const char * exprstr)
{
  SCXML__SET_ATTRIBUTE_VALUE(this->expr, "expr", exprstr);
}

// const char * getExprAttribute(void) const { return this->expr; }

void
ScXMLLogElt::setLevelAttribute(const char * levelstr)
{
  SCXML__SET_ATTRIBUTE_VALUE(this->level, "level", levelstr);
}

// const char * getLevelAttribute(void) const { return this->level; }

bool
ScXMLLogElt::handleXMLAttributes(void)
{
  if (!inherited::handleXMLAttributes()) {
    return false;
  }

  this->setLabelAttribute(this->getXMLAttribute("label"));
  this->setExprAttribute(this->getXMLAttribute("expr"));
  this->setLevelAttribute(this->getXMLAttribute("level"));

  return true;
}

void
ScXMLLogElt::copyContents(const ScXMLElt * rhs)
{
  inherited::copyContents(rhs);
  const ScXMLLogElt * orig = coin_assert_cast<const ScXMLLogElt *>(rhs);
  this->setLabelAttribute(orig->getLabelAttribute());
  this->setExprAttribute(orig->getExprAttribute());
  this->setLevelAttribute(orig->getLevelAttribute());
}

const ScXMLElt *
ScXMLLogElt::search(const char * attrname, const char * attrvalue) const
{
  const ScXMLElt * hit = inherited::search(attrname, attrvalue);
  if (hit) {
    return hit;
  }
  if (std::strcmp(attrname, "label") == 0) {
    if (this->label && std::strcmp(attrvalue, this->label) == 0) {
      return this;
    }
  }
  else if (std::strcmp(attrname, "expr") == 0) {
    if (this->expr && std::strcmp(attrvalue, this->expr) == 0) {
      return this;
    }
  }
  else if (std::strcmp(attrname, "level") == 0) {
    if (this->level && std::strcmp(attrvalue, this->level) == 0) {
      return this;
    }
  }
  return nullptr;
}

void
ScXMLLogElt::execute(ScXMLStateMachine * statemachine) const
{
  inherited::execute(statemachine);

  int elementloglevel = 1;
  if (this->level) {
    elementloglevel = atoi(this->level);
  }
  if (elementloglevel < statemachine->getLogLevel()) {
    return;
  }

  // FIXME: log through another mechanism than printf()

  printf("SCXML (%s): %s\n", this->label ? this->label : "Log", this->expr ? this->expr : "<no message>");
  const ScXMLEvent * event = statemachine->getCurrentEvent();
  printf("> EVENT '%s'\n", event ? event->getEventName().getString() : "<no event>");
  if (event->getNumAssociations() > 0) {
    SbList<const char *> keylist;
    size_t numkeys = event->getAssociationKeys(keylist);
    for (size_t i = 0; i < numkeys; ++i) {
      const char * value = event->getAssociation(keylist[i]);
      printf("> - key '%s' carries value '%s'\n", keylist[i], value);
    }
  }
  for (int i = 0; i < statemachine->getNumActiveStates(); ++i) {
    const ScXMLElt * state = statemachine->getActiveState(i);
    const char * id = state->getXMLAttribute("id");
    printf("> SCXML active state: '%s' (type '%s')\n", id ? id : "<no id>",
      state->getTypeId().getName().getString());
  }
  ScXMLEvaluator * evaluator = statemachine->getEvaluator();
  if (evaluator && evaluator->isOfType(ScXMLCoinEvaluator::getClassTypeId())) {
    ScXMLCoinEvaluator * coinev = static_cast<ScXMLCoinEvaluator *>(evaluator);
    coinev->dumpTemporaries();
  }
}

#undef PRIVATE
