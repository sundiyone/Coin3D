#ifndef COIN_SOSOUNDELEMENTHELPER_H
#define COIN_SOSOUNDELEMENTHELPER_H

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

#ifndef COIN_INTERNAL
#error this is a private header file
#endif /* !COIN_INTERNAL */

/*
  This is an inelegant class that contains code for handling
  SoSoundElements. It is used by SoSwitch, SoVRMLSwitch, SoLOD,
  SoVRMLLOD and SoLevelOfDetail.

  2003-02-04 thammer.  */

// *************************************************************************

#include <Inventor/actions/SoAudioRenderAction.h>
#include <Inventor/elements/SoSoundElement.h>
#include <Inventor/misc/SoChildList.h>

// *************************************************************************

class SoSoundElementHelper {
public:
  SoSoundElementHelper() {
    this->hassoundchild = SoSoundElementHelper::MAYBE;
    this->soundchildplaying = false;
    this->shoulddosoundtraversal = true;
  }
  
  void notifyCalled() {
    this->hassoundchild = SoSoundElementHelper::MAYBE;
    this->soundchildplaying = false;
    this->shoulddosoundtraversal = true;
  }

  void enableTraversingOfInactiveChildren() {
    this->shoulddosoundtraversal = true;
  }

  void traverseInactiveChildren(SoNode *node, SoAction *action, int idx, 
                                SoAction::PathCode pathcode,
                                int numchildren,
                                SoChildList *children) {
    if (this->shouldDoSoundTraversal(action, idx, pathcode)) {
      // Note: If there is a playing SoVRMLSound node somewhere among
      // the non-active children sub-graphs, it must be informed that
      // it shouldn't be playing anymore. So we traverse all inactive
      // children. This could be optimized, as we only need to visit
      // the old active (now inactive) child. 2003-02-04 thammer.

      SoState * state = action->getState();
      int n = numchildren;
      for (int i=0; i<n; i++) {
        if (i != idx) {
          action->getState()->push();
          SoSoundElement::setIsPartOfActiveSceneGraph(state, node, false);
          children->traverse(action, i);
          action->getState()->pop();
        }
      }
      this->shoulddosoundtraversal = false;
    }
  }

  void preAudioRender(SoNode *node, SoAction *action) {
    this->lookforsoundnode = false;
    this->oldhassound = false;
    this->oldisplaying = false;

    int numindices;
    const int * indices;
    SoState * state = action->getState();
    if ((action->getPathCode(numindices, indices) != SoAction::IN_PATH) &&
        (this->hassoundchild != SoSoundElementHelper::NO) ) {
      this->lookforsoundnode = true;
      this->oldhassound = SoSoundElement::setSceneGraphHasSoundNode(state, 
                                                            node, false);
      this->oldisplaying = SoSoundElement::setSoundNodeIsPlaying(state, 
                                                         node, false);
    }
  }

  void postAudioRender(SoNode *node, SoAction *action) {
    if (this->lookforsoundnode) {
      SoState * state = action->getState();
      bool soundnodefound = SoSoundElement::sceneGraphHasSoundNode(state);
      this->soundchildplaying = SoSoundElement::soundNodeIsPlaying(state);
      SoSoundElement::setSceneGraphHasSoundNode(state, node, this->oldhassound
                                                || soundnodefound);
      SoSoundElement::setSoundNodeIsPlaying(state, node, this->oldisplaying 
                                            || this->soundchildplaying);
      this->hassoundchild = soundnodefound ? SoSoundElementHelper::YES :
      SoSoundElementHelper::NO;
    }
  }

private:
  bool shouldDoSoundTraversal(SoAction *action, int idx, 
                              SoAction::PathCode pathcode) {
    return action->isOfType(SoAudioRenderAction::getClassTypeId()) &&
      (this->hassoundchild != SoSoundElementHelper::NO) &&
      (! ( (idx >= 0) && (pathcode == SoAction::IN_PATH) ) ) &&
      this->shoulddosoundtraversal;
  }  

  enum Alternatives { YES, NO, MAYBE };

  SoSoundElementHelper::Alternatives hassoundchild;
  bool soundchildplaying;
  bool shoulddosoundtraversal;

  bool lookforsoundnode;
  bool oldhassound;
  bool oldisplaying;

};

#endif // !COIN_SOSOUNDELEMENTHELPER_H
