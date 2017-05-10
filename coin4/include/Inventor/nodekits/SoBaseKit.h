#ifndef COIN_SOBASEKIT_H
#define COIN_SOBASEKIT_H

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

#include <Inventor/nodekits/SoSubKit.h>
#include <Inventor/nodes/SoNode.h>
#ifdef COIN_INTERNAL
class SoNodeKitPath;
#else // !COIN_INTERNAL
// Include these header files for better Open Inventor compatibility.
#include <Inventor/SoNodeKitPath.h>
#include <Inventor/misc/SoChildList.h>
#endif // !COIN_INTERNAL

class SoGroup;
class SoNodekitParts;
class SoNodekitCatalog;
class SoPath;

// Convenience macros. FIXME: document. 20000113 mortene.

#define SO_GET_PART(_kit_, _name_, _classname_) \
 ((_classname_ *)_kit_->getPart(_name_, true))

#define SO_CHECK_PART(_kit_, _name_, _classname_) \
 (static_cast<_classname_ *>(_kit_->getPart(_name_, false)))

#define SO_GET_ANY_PART(_kit_, _name_, _classname_) \
 (static_cast<_classname_ *>(_kit_->getAnyPart(_name_, true, false, false)))

#define SO_CHECK_ANY_PART(_kit_, _name_, _classname_) \
 (static_cast<_classname_ *>(_kit_->getAnyPart(_name_, false, false, false)))


class COIN_DLL_API SoBaseKit : public SoNode {
  typedef SoNode inherited;

  SO_NODE_HEADER(SoBaseKit);

  SO_KIT_CATALOG_ENTRY_HEADER(callbackList);

public:
  static void initClass(void);
  SoBaseKit(void);

  static const SoNodekitCatalog * getClassNodekitCatalog(void);
  virtual const SoNodekitCatalog * getNodekitCatalog(void) const;

  virtual SoNode * getPart(const SbName & partname, bool makeifneeded);
  SbString getPartString(const SoBase * part);
  virtual SoNodeKitPath * createPathToPart(const SbName & partname,
                                           bool makeifneeded,
                                           const SoPath * pathtoextend = NULL);
  virtual bool setPart(const SbName & partname, SoNode * from);
  bool set(const char * namevaluepairliststring);
  bool set(const char * partnamestring, const char * parameterstring);

  virtual void doAction(SoAction * action);
  virtual void callback(SoCallbackAction * action);
  virtual void GLRender(SoGLRenderAction * action);
  virtual void getBoundingBox(SoGetBoundingBoxAction * action);
  virtual void getMatrix(SoGetMatrixAction * action);
  virtual void handleEvent(SoHandleEventAction * action);
  virtual void rayPick(SoRayPickAction * action);
  virtual void search(SoSearchAction * action);
  virtual void write(SoWriteAction * action);
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction * action);

  virtual SoChildList * getChildren(void) const;

  void printDiagram(void);
  void printSubDiagram(const SbName & rootname, int level);
  void printTable(void);

  virtual void addWriteReference(SoOutput * out, bool isfromfield = false);
  bool forceChildDrivenWriteRefs(SoOutput * out);

  static bool isSearchingChildren(void);
  static void setSearchingChildren(const bool newval);

protected:
  virtual ~SoBaseKit();

  static const SoNodekitCatalog ** getClassNodekitCatalogPtr(void);

  virtual SoNode * addToCopyDict(void) const;
  virtual void copyContents(const SoFieldContainer * fromfc,
                            bool copyconnections);

  SoGroup * getContainerNode(const SbName & listname,
                             bool makeifneeded = true);
  virtual SoNode * getAnyPart(const SbName & partname, bool makeifneeded,
                              bool leafcheck = false,
                              bool publiccheck = false);
  virtual SoNodeKitPath * createPathToAnyPart(const SbName & partname,
                                              bool makeifneeded,
                                              bool leafcheck = false,
                                              bool publiccheck = false,
                                              const SoPath * pathtoextend = NULL);
  virtual bool setAnyPart(const SbName & partname, SoNode * from,
                            bool anypart = true);
  void createNodekitPartsList(void); // not part of Coin
  void createFieldList(void); // replaces above method
  virtual void createDefaultParts(void);
  const SoNodekitParts * getNodekitPartsList(void) const; // not part of Coin
  const SbList<SoSFNode*> & getCatalogInstances(void) const; // replaces above method

  void catalogError(void);
  virtual bool setUpConnections(bool onoff, bool doitalways = false);
  virtual bool readInstance(SoInput * in, unsigned short flags);
  virtual void setDefaultOnNonWritingFields(void);
  void countMyFields(SoOutput * out);

  virtual bool setPart(const int partNum, SoNode * node);

  SoChildList * children;
  bool connectionsSetUp;

private:
  friend class SoInteractionKit;
  static bool findPart(const SbString & partname, SoBaseKit *& kit,
                         int & partnum, bool & islist, int & listidx,
                         const bool makeifneeded, SoPath * path = NULL,
                         const bool recsearch = false);
  static void atexit_cleanupkit(void);

  bool makePart(const int partnum);
  int getRightSiblingIndex(const int partnum);
  int findNodeInThisKit(SoNode *node, const int parentnum = -1) const;

  static SoNodekitCatalog * classcatalog;
  static const SoNodekitCatalog ** parentcatalogptr;
  static bool searchchildren;

  class SoBaseKitP * pimpl;
  friend class SoBaseKitP;
};

#endif // !COIN_SOBASEKIT_H
