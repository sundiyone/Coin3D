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

/*
 * Press mouse button in viewer canvas to trigger assert deep in Coin for
 * checking that debug symbols are available in the libraries.
 *
 * Jotted down 2002-01-11 by Lars J. Aas <larsa@sim.no>
 */

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>

#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoCallback.h>
#include <Inventor/nodes/SoSeparator.h>

#include <Inventor/actions/SoHandleEventAction.h>
#include <Inventor/events/SoMouseButtonEvent.h>

#include <stdlib.h>
#include <stdio.h>

void
callback(void * closure, SoAction * action)
{
  if ( action->isOfType(SoHandleEventAction::getClassTypeId()) ) {
    SoHandleEventAction * heaction =
      (SoHandleEventAction *) action;
    if ( heaction->getEvent()->isOfType(SoMouseButtonEvent::getClassTypeId()) ) {
      SoSeparator * sep = (SoSeparator *) closure;
      sep->addChild(NULL); // trigger assert inside Coin
    }
  }
}

int
main(int argc, char ** argv)
{
  QWidget * win = SoQt::init("Debug Test");
  SoQtExaminerViewer * viewer = new SoQtExaminerViewer(win);
  viewer->show();
  SoQt::show(win);
  SoSeparator * sep = new SoSeparator;
  SoCallback * cb = new SoCallback;
  cb->setCallback(callback, sep);
  sep->addChild(cb);
  sep->addChild(new SoCube);
  viewer->setSceneGraph(sep);
  viewer->setViewing(FALSE);
  SoQt::mainLoop();
  viewer->hide();
  // delete viewer;
  return 0;
}
