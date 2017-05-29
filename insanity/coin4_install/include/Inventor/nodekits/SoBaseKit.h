#ifndef COIN_SOBASEKIT_H
#define COIN_SOBASEKIT_H

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
                                           const SoPath * pathtoextend = nullptr);
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
                                              const SoPath * pathtoextend = nullptr);
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
                         const bool makeifneeded, SoPath * path = nullptr,
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
