#ifndef COIN_SOREORGANIZEACTION_H
#define COIN_SOREORGANIZEACTION_H

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

#include <Inventor/actions/SoSimplifyAction.h>

class SoSimplifier;
class SoSeparator;
class SoReorganizeActionP;

class COIN_DLL_API SoReorganizeAction : public SoSimplifyAction {
  typedef SoSimplifyAction inherited;

  SO_ACTION_HEADER(SoReorganizeAction);

public: 
  static void initClass(void);

  SoReorganizeAction(SoSimplifier * simplifier = nullptr);
  virtual ~SoReorganizeAction(void);

  SoSeparator * getSimplifiedSceneGraph(void) const;
  void generateNormals(bool onoff);
  bool areNormalGenerated(void) const;
  void generateTriangleStrips(bool onoff);
  bool areTriangleStripGenerated(void) const;
  void generateTexCoords(bool onoff);
  bool areTexCoordsGenerated(void) const;
  void generateVPNodes(bool onoff); 
  bool areVPNodesGenerated(void); 
  void matchIndexArrays(bool onoff);
  bool areIndexArraysMatched(void) const;
  SoSimplifier * getSimplifier(void) const;

  virtual void apply(SoNode * root);
  virtual void apply(SoPath * path);
  virtual void apply(const SoPathList & pathlist, bool obeysrules = false);

  static void startReport(const char * msg);
  static void finishReport(void);

protected:
  virtual void beginTraversal(SoNode * node);

private:
  SbPimplPtr<SoReorganizeActionP> pimpl;

  // NOT IMPLEMENTED:
  SoReorganizeAction(const SoReorganizeAction & rhs);
  SoReorganizeAction & operator = (const SoReorganizeAction & rhs);
}; // SoReorganizeAction

#endif // !COIN_SOREORGANIZEACTION_H
