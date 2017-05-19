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

// Important note: this sourcefile was in full generated by the
// Coin/scripts/templant script from the code in SFNodeEnginePath.tpl
// (except the test suite cases at the end).

///////////////////////////////////////////////////////////////////////////


//$ BEGIN TEMPLATE SFNodeEnginePath(NODE, Node, node)

/*!
  \class SoSFNode SoSFNode.h Inventor/fields/SoSFNode.h
  \brief The SoSFNode class is a container for a single node.
  \ingroup fields

  This field container stores a pointer to a Coin node. It takes care
  of the necessary functionality for handling copy, import and export
  operations.

  Note that the node pointer stored in a field instance of this type
  may be a \c nullptr pointer.

  \sa SoNode, SoMFNode

*/

// Type-specific define to be able to do #ifdef tests on type.  (Note:
// used to check the header file wrapper define, but that doesn't work
// with --enable-compact build.)
#define COIN_INTERNAL_SOSFNODE

#include <Inventor/fields/SoSFNode.h>

#include "SbBasicP.h"

#include <Inventor/SoInput.h>
#include <Inventor/SoOutput.h>
#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/errors/SoReadError.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/engines/SoEngine.h>
#include <Inventor/SoOutput.h>
#if COIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // COIN_DEBUG

#include "fields/SoSubFieldP.h"

// Can't use SO_SFIELD_SOURCE() because we need to modify setValue()
// to ref and unref the passed node.
SO_SFIELD_REQUIRED_SOURCE(SoSFNode);


// Override from parent class.
void
SoSFNode::initClass(void)
{
  SO_SFIELD_INTERNAL_INIT_CLASS(SoSFNode);
}

// (Declarations hidden in SO_[S|M]FIELD_HEADER macro in header file,
// so don't use Doxygen commenting.)
#ifndef DOXYGEN_SKIP_THIS

/* Constructor, sets initial node pointer to a \c nullptr pointer. */
SoSFNode::SoSFNode(void)
{
  this->value = nullptr;
#ifdef COIN_INTERNAL_SOSFPATH
  this->head = nullptr;
#endif // COIN_INTERNAL_SOSFPATH
}

/* Destructor, dereferences the current node pointer if necessary. */
SoSFNode::~SoSFNode(void)
{
  this->enableNotify(false);
  this->setValue(nullptr);
}

#endif // DOXYGEN_SKIP_THIS


// No need to document readValue() and writeValue() here, as the
// necessary information is provided by the documentation of the
// parent classes.
#ifndef DOXYGEN_SKIP_THIS

// Store the \a newval node pointer in this field. If \a newval is not
// \c nullptr, will add 1 to the reference count of the node.
void
SoSFNode::setValue(SoNode * newval)
{
  // Don't use getValue() to find oldptr, since this might trigger a
  // recursive evaluation call if the field is connected.
  SoNode * oldptr = this->value;
  if (oldptr == newval) return;

  if (oldptr) {
#ifdef COIN_INTERNAL_SOSFPATH
    SoNode * h = oldptr->getHead();
    // The path should be audited by us at all times. So don't use
    // SoSFPath to wrap SoTempPath or SoLightPath, for instance.
    assert(h==this->head && "Path head changed without notification!");
    if (h) {
      h->removeAuditor(this, SoNotRec::FIELD);
      h->unref();
    }
#endif // COIN_INTERNAL_SOSFPATH
    oldptr->removeAuditor(this, SoNotRec::FIELD);
    oldptr->unref();
  }

  if (newval) {
    newval->addAuditor(this, SoNotRec::FIELD);
    newval->ref();
#ifdef COIN_INTERNAL_SOSFPATH
    this->head = newval->getHead();
    if (this->head) {
      this->head->addAuditor(this, SoNotRec::FIELD);
      this->head->ref();
    }
#endif // COIN_INTERNAL_SOSFPATH
  }

  this->value = newval;
  this->valueChanged();
}

// Compares to see if the \a field points to the same node as this
// field does, and returns \c true if this is the case.
//
// Be aware that this method does \e not check for node/subgraph
// equality if the pointers are not the same, so \c false is returned
// even though the contents of the node/subgraph are equal.
bool
SoSFNode::operator==(const SoSFNode & field) const
{
  return (this->getValue() == field.getValue());
}

// Import node.
bool
SoSFNode::readValue(SoInput * in)
{
  SoBase * baseptr;
  bool isVRMLspecialCase = false;

  // Note: do *not* simply check for baseptr==nullptr here, as that is a
  // valid condition for VRML97 files, where nodes can indeed be
  // explicitly given as a nullptr value. See the 'vrml97nullchild' test
  // case near the end of this file for a valid case that would fail.
  if(in->isFileVRML1() || in->isFileVRML2()) {
    SbName name;
    in->read(name, true);
    if (name == "NULL") {
      baseptr = nullptr;
      isVRMLspecialCase = true;
    }
    else {
      in->putBack(name.getString());
    }
  }

  if (!isVRMLspecialCase) {
    if (!SoBase::read(in, baseptr, SoNode::getClassTypeId())) return false;
    if (baseptr == nullptr) {
      SoReadError::post(in, "Invalid node specification");
      return false;
    }
  }

  if (in->eof()) {
    SoReadError::post(in, "Premature end of file");
    return false;
  }

  if (baseptr != nullptr) {
    this->setValue(coin_safe_cast<SoNode *>(baseptr));
  }
  return true;
}

// Export node.
void
SoSFNode::writeValue(SoOutput * out) const
{
  // NB: This code is common for SoSFNode, SoSFPath and SoSFEngine.
  // That's why we check the base type before writing.
  SoBase * base = this->getValue();
  if (base) {
    if (base->isOfType(SoNode::getClassTypeId())) {
      coin_assert_cast<SoNode *>(base)->writeInstance(out);
    }
    else if (base->isOfType(SoPath::getClassTypeId())) {
      SoWriteAction wa(out);
      wa.continueToApply(coin_assert_cast<SoPath *>(base));
    }
    else if (base->isOfType(SoEngine::getClassTypeId())) {
      coin_assert_cast<SoEngine *>(base)->writeInstance(out);
    }
    else {
      assert(0 && "strange internal error");
    }
  }
  else {
    // This actually works for both ASCII and binary formats.
    out->write("NULL");
  }
}

#endif // DOXYGEN_SKIP_THIS


// Overridden from parent to propagate write reference counting to
// node.
void
SoSFNode::countWriteRefs(SoOutput * out) const
{
  inherited::countWriteRefs(out);

  SoBase * base = this->getValue();
  if (base == NULL) return;

  // NB: This code is common for SoSFNode, SoSFPath and SoSFEngine.
  // That's why we check the base type before writing/counting

  if (base->isOfType(SoNode::getClassTypeId())) {
    coin_assert_cast<SoNode *>(base)->writeInstance(out);
  }
  else if (base->isOfType(SoEngine::getClassTypeId())) {
    coin_assert_cast<SoEngine *>(base)->addWriteReference(out);
  }
  else if (base->isOfType(SoPath::getClassTypeId())) {
    SoWriteAction wa(out);
    wa.continueToApply(coin_assert_cast<SoPath *>(base));
  }
}

// Override from parent to update our node pointer
// reference. This is necessary so we do the Right Thing with regard
// to the copyconnections flag.
//
// Note that we have to unplug auditing and the reference counter
// addition we made during the copy process.
//
// For reference for future debugging sessions, copying of this field
// goes like this:
//
//    - copyFrom() is called (typically from SoFieldData::overlay())
//    - copyFrom() calls operator=()
//    - operator=() calls setValue()
//    - we have a local copy (ie not from SoSubField.h) of setValue()
//      that sets up auditing and references the item
//
// <mortene@sim.no>
void
SoSFNode::fixCopy(bool copyconnections)
{
  SoNode * n = this->getValue();
  if (!n) return;

#if COIN_DEBUG
  n->assertAlive();
#endif // COIN_DEBUG

  // The setValue() call below will automatically de-audit and un-ref
  // the old pointer-value reference we have, *before* re-inserting a
  // copy.

#if defined(COIN_INTERNAL_SOSFNODE) || defined(COIN_INTERNAL_SOSFENGINE)
  SoFieldContainer * fc = SoFieldContainer::findCopy(n, copyconnections);
#if COIN_DEBUG
  if (fc) fc->assertAlive();
#endif // COIN_DEBUG
  if (fc) this->setValue(coin_assert_cast<SoNode *>(fc));
#endif // COIN_INTERNAL_SOSFNODE || COIN_INTERNAL_SOSFENGINE

#ifdef COIN_INTERNAL_SOSFPATH
  this->setValue(n->copy());
#endif // COIN_INTERNAL_SOSFPATH
}

// Override from SoField to check node pointer.
bool
SoSFNode::referencesCopy(void) const
{
  if (inherited::referencesCopy()) return true;

  SoBase * n = this->getValue();
  if (!n) return false;

  if (n->isOfType(SoNode::getClassTypeId()) ||
      n->isOfType(SoEngine::getClassTypeId())) {
    if (SoFieldContainer::checkCopy(coin_assert_cast<SoFieldContainer *>(n))) return true;
  }
  else if (n->isOfType(SoPath::getClassTypeId())) {
    SoPath * p = coin_assert_cast<SoPath *>(n);
    if (p->getHead() == NULL) return false;
    if (SoFieldContainer::checkCopy(p->getHead())) return true;
  }
  else {
    assert(0 && "strange internal error");
  }

  return false;
}

// Kill the type-specific define.
#undef COIN_INTERNAL_SOSFNODE
//$ END TEMPLATE SFNodeEnginePath

#ifdef COIN_TEST_SUITE

#include <cstring>
#include <Inventor/nodes/SoNode.h>

BOOST_AUTO_TEST_CASE(initialized)
{
  SoSFNode field;
  BOOST_CHECK_MESSAGE(SoSFNode::getClassTypeId() != SoType::badType(),
                      "SoSFNode class not initialized");
  BOOST_CHECK_MESSAGE(field.getTypeId() != SoType::badType(),
                      "missing class initialization");
}

BOOST_AUTO_TEST_CASE(vrml97nullchild)
{
  // NULL values for children must be allowed, or we break VRML97
  // support.  -mortene.
  char scene[] = "#VRML V2.0 utf8\n\nAppearance { material NULL }";

  SoInput * in = new SoInput;
  in->setBuffer(reinterpret_cast<const void*>(scene), strlen(scene));
  SoNode * g = NULL;
  const bool readok = SoDB::read(in, g);
  delete in;

  BOOST_CHECK_MESSAGE(readok,
                      "failed to read VRML97 with NULL child in graph");
  if (g) {
    g->ref();
    g->unref();
  }
}

#endif // COIN_TEST_SUITE
