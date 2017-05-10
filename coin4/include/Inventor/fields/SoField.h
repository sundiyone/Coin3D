#ifndef COIN_SOFIELD_H
#define COIN_SOFIELD_H

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

#include <Inventor/SoType.h>
#include <Inventor/misc/SoNotification.h>

class SbString;
class SoEngineOutput;
class SoFieldContainer;
class SoFieldConverter;
class SoFieldList;
class SoInput;
class SoOutput;

class COIN_DLL_API SoField {

public:
  virtual ~SoField();

  static void initClass(void);
  static void initClasses(void);
  static void cleanupClass(void);

  void setIgnored(bool ignore);
  bool isIgnored(void) const;

  void setDefault(bool defaultVal);
  bool isDefault(void) const;

  virtual SoType getTypeId(void) const = 0;

  static SoType getClassTypeId(void);
  bool isOfType(const SoType type) const;

  void enableConnection(bool flag);
  bool isConnectionEnabled(void) const;

  // Field<-Engine connection stuff.
  bool connectFrom(SoEngineOutput * master,
                     bool notnotify = false, bool append = false);
  bool appendConnection(SoEngineOutput * master, bool notnotify = false);
  void disconnect(SoEngineOutput * engineoutput);
  bool isConnectedFromEngine(void) const;
  bool getConnectedEngine(SoEngineOutput *& master) const;

  // Field<->Field connection stuff.
  bool connectFrom(SoField * master,
                     bool notnotify = false, bool append = false);
  bool appendConnection(SoField * master, bool notnotify = false);
  void disconnect(SoField * field);
  bool isConnectedFromField(void) const;
  bool getConnectedField(SoField *& master) const;
  int getNumConnections(void) const;
  int getForwardConnections(SoFieldList & slavelist) const;
  int getConnections(SoFieldList & masterlist) const;

  void disconnect(void);
  bool isConnected(void) const;

  void setContainer(SoFieldContainer * cont);
  SoFieldContainer * getContainer(void) const;

  bool set(const char * valuestring);
  void get(SbString & valuestring);

  bool shouldWrite(void) const;

  virtual void touch(void);
  virtual void startNotify(void);
  virtual void notify(SoNotList * nlist);
  bool enableNotify(bool on);
  bool isNotifyEnabled(void) const;

  void addAuditor(void * f, SoNotRec::Type type);
  void removeAuditor(void * f, SoNotRec::Type type);

  bool operator==(const SoField & f) const;
  bool operator!=(const SoField & f) const;

  virtual void connectionStatusChanged(int numconnections);
  bool isReadOnly(void) const;
  virtual bool isSame(const SoField & f) const = 0;
  virtual void copyFrom(const SoField & f) = 0;

  virtual void fixCopy(bool copyconnections);
  virtual bool referencesCopy(void) const;
  void copyConnection(const SoField * fromfield);

  virtual bool read(SoInput * input, const SbName & name);
  virtual void write(SoOutput * out, const SbName & name) const;

  virtual void countWriteRefs(SoOutput * out) const;

  // enums for setFieldType()/getFieldType()
  enum FieldType {
    NORMAL_FIELD = 0,
    EVENTIN_FIELD,
    EVENTOUT_FIELD,
    EXPOSED_FIELD
  };

  void setFieldType(int type);
  int getFieldType(void) const;

  bool getDirty(void) const;
  void setDirty(bool dirty);

  void evaluate(void) const {
    if ((this->statusbits & (FLAG_EXTSTORAGE|FLAG_NEEDEVALUATION)) ==
        (FLAG_EXTSTORAGE|FLAG_NEEDEVALUATION)) this->evaluateField();
  }

protected:
  SoField(void);

  void valueChanged(bool resetdefault = true);
  virtual void evaluateConnection(void) const;
  virtual bool readValue(SoInput * in) = 0;
  virtual void writeValue(SoOutput * out) const = 0;
  virtual bool readConnection(SoInput * in);
  virtual void writeConnection(SoOutput * out) const;

  bool isDestructing(void) const;

  virtual SoNotRec createNotRec(SoBase * cont);

private:

  enum FieldFlags {
    FLAG_TYPEMASK = 0x0007,  // need 3 bits for values [0-5]
    FLAG_ISDEFAULT = 0x0008,
    FLAG_IGNORE = 0x0010,
    FLAG_EXTSTORAGE = 0x0020,
    FLAG_ENABLECONNECTS = 0x0040,
    FLAG_NEEDEVALUATION = 0x0080,
    FLAG_READONLY = 0x0100,
    FLAG_DONOTIFY = 0x0200,
    FLAG_ISDESTRUCTING = 0x0400,
    FLAG_ISEVALUATING = 0x0800,
    FLAG_ISNOTIFIED = 0x1000
  };

  void evaluateField(void) const;
  void extendStorageIfNecessary(void);
  SoFieldConverter * createConverter(SoType from) const;
  SoFieldContainer * resolveWriteConnection(SbName & mastername) const;

  void notifyAuditors(SoNotList * l);

  static SoType classTypeId;

  // These are bit flags.
  enum FileFormatFlags {
    IGNORED = 0x01,
    CONNECTED = 0x02,
    DEFAULT = 0x04,
    ALLFILEFLAGS = IGNORED|CONNECTED|DEFAULT
  };

  bool changeStatusBits(const unsigned int bits, const bool onoff);
  void clearStatusBits(const unsigned int bits);
  void setStatusBits(const unsigned int bits);
  bool getStatus(const unsigned int bits) const;
  unsigned int statusbits;
  union {
    SoFieldContainer * container;
    class SoConnectStorage * storage;
  };

  bool hasExtendedStorage(void) const;
};


#ifndef COIN_INTERNAL
// Added to be Inventor compliant.
#include <Inventor/fields/SoSField.h>
#include <Inventor/fields/SoMField.h>
#endif // !COIN_INTERNAL

#endif // !COIN_SOFIELD_H
