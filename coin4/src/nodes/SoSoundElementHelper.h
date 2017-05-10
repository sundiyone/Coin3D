#ifndef COIN_SOSOUNDELEMENTHELPER_H
#define COIN_SOSOUNDELEMENTHELPER_H

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
