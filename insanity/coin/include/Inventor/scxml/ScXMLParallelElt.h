#ifndef COIN_SCXMLPARALLELELT_H
#define COIN_SCXMLPARALLELELT_H

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

#include <Inventor/scxml/ScXMLAbstractStateElt.h>
#include <Inventor/tools/SbPimplPtr.h>

class ScXMLEvent;
class ScXMLStateMachine;
class ScXMLOnEntryElt;
class ScXMLOnExitElt;
class ScXMLTransitionElt;
class ScXMLStateElt;
class ScXMLInitialElt;
class ScXMLFinalElt;
class ScXMLHistoryElt;
class ScXMLAnchorElt;
class ScXMLDataModelElt;

class COIN_DLL_API ScXMLParallelElt : public ScXMLAbstractStateElt {
  typedef ScXMLAbstractStateElt inherited;
  SCXML_ELEMENT_HEADER(ScXMLElt)

public:
  static void initClass(void);
  static void cleanClass(void);

  ScXMLParallelElt(void);
  virtual ~ScXMLParallelElt(void);

  // XML attributes
  virtual void setSrcAttribute(const char * src);
  const char * getSrcAttribute(void) const { return this->src; }

  virtual bool handleXMLAttributes(void);

  virtual void copyContents(const ScXMLElt * rhs);

  virtual const ScXMLElt * search(const char * attrname, const char * attrvalue) const;

  // children...
  virtual void setOnEntry(ScXMLOnEntryElt * onentry);
  virtual ScXMLOnEntryElt * getOnEntry(void) const;

  virtual void setOnExit(ScXMLOnExitElt * onexit);
  virtual ScXMLOnExitElt * getOnExit(void) const;

  virtual int getNumTransitions(void) const;
  virtual ScXMLTransitionElt * getTransition(int idx) const;
  virtual void addTransition(ScXMLTransitionElt * transition);
  virtual void removeTransition(ScXMLTransitionElt * transition);
  virtual void clearAllTransitions(void);

  virtual void setInitial(ScXMLInitialElt * initial);
  virtual ScXMLInitialElt * getInitial(void) const;

  virtual int getNumStates(void) const;
  virtual ScXMLStateElt * getState(int idx) const;
  virtual void addState(ScXMLStateElt * state);
  virtual void removeState(ScXMLStateElt * state);
  virtual void clearAllStates(void);

  virtual int getNumParallels(void) const;
  virtual ScXMLParallelElt * getParallel(int idx) const;
  virtual void addParallel(ScXMLParallelElt * state);
  virtual void removeParallel(ScXMLParallelElt * state);
  virtual void clearAllParallels(void);

  virtual int getNumFinals(void) const;
  virtual ScXMLFinalElt * getFinal(int idx) const;
  virtual void addFinal(ScXMLFinalElt * state);
  virtual void removeFinal(ScXMLFinalElt * state);
  virtual void clearAllFinals(void);

  virtual int getNumHistories(void) const;
  virtual ScXMLHistoryElt * getHistory(int idx) const;
  virtual void addHistory(ScXMLHistoryElt * history);
  virtual void removeHistory(ScXMLHistoryElt * history);
  virtual void clearAllHistories(void);

  virtual int getNumAnchors(void) const;
  virtual ScXMLAnchorElt * getAnchor(int idx) const;
  virtual void addAnchor(ScXMLAnchorElt * anchor);
  virtual void removeAnchor(ScXMLAnchorElt * anchor);
  virtual void clearAllAnchors(void);

  virtual void setDataModel(ScXMLDataModelElt * datamodel);
  virtual ScXMLDataModelElt * getDataModel(void) const;

  bool isAtomicState(void) const;

protected:
  char * src;

private:
  ScXMLParallelElt(const ScXMLParallelElt & rhs); // N/A
  ScXMLParallelElt & operator = (const ScXMLParallelElt & rhs); // N/A

  class PImpl;
  SbPimplPtr<PImpl> pimpl;

}; // ScXMLParallelElt

#endif // !COIN_SCXMLPARALLELELT_H
