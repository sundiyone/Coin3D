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

#ifndef SOQT_QTNATIVEPOPUPMENU_H
#define SOQT_QTNATIVEPOPUPMENU_H

#include <qobject.h>
#include <Inventor/Qt/SoQtBasic.h>
#include <Inventor/Qt/widgets/SoQtPopupMenu.h>

// *************************************************************************

struct MenuRecord;
struct ItemRecord;
class QAction;

class QtNativePopupMenu : public QObject, public SoQtPopupMenu
{
  typedef SoQtPopupMenu inherited;
  Q_OBJECT

public:
  QtNativePopupMenu(void);
  virtual ~QtNativePopupMenu();

  virtual int newMenu(const char * name, int menuid = -1);
  virtual int getMenu(const char * name);
  virtual void setMenuTitle(int id, const char * title);
  virtual const char * getMenuTitle(int id);

  virtual int newMenuItem(const char * name, int itemid = -1);
  virtual int getMenuItem(const char * name);
  virtual void setMenuItemTitle(int itemid, const char * title);
  virtual const char * getMenuItemTitle(int itemid);
  virtual void setMenuItemEnabled(int itemid, SbBool enabled);
  virtual SbBool getMenuItemEnabled(int itemid);
  virtual SbBool getMenuItemMarked(int itemid);

  virtual void addMenu(int menuid, int submenuid, int pos = -1);
  virtual void addMenuItem(int menuid, int itemid, int pos = -1);
  virtual void addSeparator(int menuid, int pos = -1);
  virtual void removeMenu(int menuid);
  virtual void removeMenuItem(int itemid);

  virtual void popUp(QWidget * inside, int x, int y);

protected:
  virtual void _setMenuItemMarked(int itemid, SbBool marked);

  MenuRecord * getMenuRecord(int menuid);
  ItemRecord * getItemRecord(int itemid);
  ItemRecord * getItemRecordFromAction(QAction * action);
  MenuRecord * createMenuRecord(const char * name);
  ItemRecord * createItemRecord(const char * name);

private slots:
  void itemActivation(QAction *);
  void itemActivation(int itemid);

private:
  SbPList * menus;
  SbPList * items;

};  // class QtNativePopupMenu

// *************************************************************************

#endif // ! SOQT_QTNATIVEPOPUPMENU_H
