#ifndef COIN_SOJAVASCRIPTENGINE_H
#define COIN_SOJAVASCRIPTENGINE_H

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
  
#include <Inventor/misc/SoScriptEngine.h>
#include <Inventor/C/glue/spidermonkey.h>
#include <Inventor/lists/SbList.h>

// *************************************************************************

#define COIN_JAVASCRIPT_RUNTIME_MAXBYTES 4194304

// *************************************************************************

typedef void SoJSfield2jsvalFunc(JSContext *, const SoField *, jsval *);
typedef bool SoJSjsval2field2Func(JSContext *, const jsval, SoField *);
typedef JSObject * SoJSWrapperInitFunc(JSContext *, JSObject * obj);

// *************************************************************************

class COIN_DLL_API SoJavaScriptEngine : public SoScriptEngine {

public:
  SoJavaScriptEngine();
  virtual ~SoJavaScriptEngine();

  virtual bool executeScript(const SbName & name, 
                               const SbString & script) const;
  virtual bool executeFile(const SbName & filename) const;
  virtual bool executeFunction(const SbName &name, int argc, 
                                 const SoField * argv, 
                                 SoField * rval = NULL) const;

  virtual bool setScriptField(const SbName & name, const SoField * f) const;
  virtual bool unsetScriptField(const SbName & name) const;
  virtual bool getScriptField(const SbName & name, SoField * f) const;
  virtual bool hasScriptField(const SbName & name) const;

  // Everything under here is javascript specific

  static SoJavaScriptEngine *getEngine(JSContext * cx);

  bool field2jsval(const SoField * f, jsval * v) const;
  bool jsval2field(const jsval v, SoField * f) const;
  void enableAutoNodeUnref(bool onoff);
  bool getAutoNodeUnrefState(void) const;

  static bool init(uint32_t maxbytes = COIN_JAVASCRIPT_RUNTIME_MAXBYTES);
  static void shutdown(void);
  static bool debug(void);

  static JSRuntime * getRuntime(void);
  JSContext * getContext(void) const;
  JSObject * getGlobal(void) const;

  void addHandler(const SoType & type, SoJSWrapperInitFunc * init, 
                  SoJSfield2jsvalFunc * field2jsval, 
                  SoJSjsval2field2Func * jsval2field);

protected:
  static void setRuntime(JSRuntime * runtime);
  void setContext(JSContext * context);
  void setGlobal(JSObject * global);

private:
  class SoJavaScriptEngineP * pimpl; 
  friend class SoJavaScriptEngineP; 
};

#endif // !COIN_SOJAVASCRIPTENGINE_H
