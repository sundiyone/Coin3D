#ifndef COIN_SOINPUT_H
#define COIN_SOINPUT_H

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

#include <Inventor/system/inttypes.h>
#include <Inventor/SbBasic.h>
#include <Inventor/lists/SbList.h>
#include <stdio.h> // FILE
#ifndef COIN_INTERNAL
 // For Open Inventor compatibility.
 #include <Inventor/SoDB.h>
#endif // COIN_INTERNAL

// *************************************************************************

class SbDict;
class SoBase;
class SbString;
class SbTime;
class SbName;
class SbStringList;
class SoInput_FileInfo;
class SoProto;
class SoField;
class SoFieldContainer;
class SoInputP;

// *************************************************************************

class COIN_DLL_API SoInput {
public:
  SoInput(void);
  SoInput(SoInput * dictIn);

  SoProto * findProto(const SbName & name);
  void addProto(SoProto * proto);
  void pushProto(SoProto * proto);
  SoProto * getCurrentProto(void) const;
  void popProto(void);

  void addRoute(const SbName & fromnode, const SbName & fromfield,
                const SbName & tonode, const SbName & tofield);
  bool checkISReference(SoFieldContainer * container, const SbName & fieldname,
                          bool & readok);

  virtual ~SoInput(void);

  virtual void setFilePointer(FILE * newFP);
  virtual bool openFile(const char * fileName, bool okIfNotFound = false);
  virtual bool pushFile(const char * fileName);
  virtual void closeFile(void);
  virtual bool isValidFile(void);
  virtual bool isValidBuffer(void);
  virtual FILE * getCurFile(void) const;
  virtual const char * getCurFileName(void) const;
  virtual void setBuffer(const void * bufpointer, size_t bufsize);
          void setStringArray(const char * strings[]);
  virtual size_t getNumBytesRead(void) const;
  virtual SbString getHeader(void);
  virtual float getIVVersion(void);
  virtual bool isBinary(void);

  virtual bool get(char & c);
  virtual bool getASCIIBuffer(char & c);
  virtual bool getASCIIFile(char & c);
  virtual bool readHex(uint32_t & l);
  virtual bool read(bool & b);
  virtual bool read(char & c);
  virtual bool read(char & c, bool skip);
  virtual bool read(SbString & s);
  virtual bool read(SbName & n, bool validIdent = false);
  virtual bool read(int & i);
  virtual bool read(unsigned int & i);
  virtual bool read(short & s);
  virtual bool read(unsigned short & s);
  virtual bool read(float & f);
  virtual bool read(double & d);
  virtual bool readByte(int8_t & b);
  virtual bool readByte(uint8_t & b);
#ifdef __CYGWIN__
  //These function are not virtual as they are meant to be only wrappers to the real function calls, due to limitations in Cygwin g++ type demangling.
  bool read(long int & i);
  bool read(long unsigned int & i);
#endif //__CYGWIN__
  virtual bool readBinaryArray(unsigned char * c, int length);
  virtual bool readBinaryArray(int32_t * l, int length);
  virtual bool readBinaryArray(float * f, int length);
  virtual bool readBinaryArray(double * d, int length);
  virtual bool eof(void) const;

  bool isFileVRML1(void);
  bool isFileVRML2(void);
  virtual void resetFilePointer(FILE * fptr);

  virtual void getLocationString(SbString & string) const;
  virtual void putBack(const char c);
  virtual void putBack(const char * str);
  virtual void addReference(const SbName & name, SoBase * base,
                            bool addToGlobalDict = true);
  virtual void removeReference(const SbName & name);
  virtual SoBase * findReference(const SbName & name) const;

  static void addDirectoryFirst(const char * dirName);
  static void addDirectoryLast(const char * dirName);
  static void addEnvDirectoriesFirst(const char * envVarName,
                                     const char * separator = ":\t ");
  static void addEnvDirectoriesLast(const char * envVarName,
                                    const char * separator = ":\t ");
  static void removeDirectory(const char * dirName);
  static void clearDirectories(void);
  static const SbStringList & getDirectories(void);

  static void init(void);

  static SbString getPathname(const char * const filename);
  static SbString getPathname(const SbString & s);
  static SbString getBasename(const char * const filename);
  static SbString getBasename(const SbString & s);

  static SbString searchForFile(const SbString & basename,
                                const SbStringList & directories,
                                const SbStringList & subdirectories);


protected:
  virtual bool popFile(void);
  void setIVVersion(float version);
  FILE * findFile(const char * fileName, SbString & fullName);
  void initFile(FILE * newFP, const char * fileName, SbString * fullName,
                bool openedHere, SbDict * refDict = nullptr);
  bool checkHeader(bool bValidateBufferHeader = false);
  bool fromBuffer(void) const;
  bool skipWhiteSpace(void);
  size_t freeBytesInBuf(void) const;
  bool readInteger(int32_t & l);
  bool readUnsignedInteger(uint32_t & l);
  bool readReal(double & d);
  bool readUnsignedIntegerString(char * str);
  int readDigits(char * str);
  int readHexDigits(char * str);
  int readChar(char * str, char charToRead);

  bool makeRoomInBuf(size_t nBytes);
  void convertShort(char * from, short * s);
  void convertInt32(char * from, int32_t * l);
  void convertFloat(char * from, float * f);
  void convertDouble(char * from, double * d);
  void convertShortArray(char * from, short * to, int len);
  void convertInt32Array(char * from, int32_t * to, int len);
  void convertFloatArray(char * from, float * to, int len);
  void convertDoubleArray(char * from, double * to, int len);
  bool isFileURL(const char * url);
  char * URLToFile(char * out_buf, const char * in_buf);
  bool IsURL(const char * c_strng);

  static void setDirectories(SbStringList * dirs);

private:
  friend class SoDB;
  friend class SoInputP;

  static void clean(void);
  void constructorsCommon(void);

  static void addDirectoryIdx(const int idx, const char * dirName);
  static void addEnvDirectoriesIdx(int startidx, const char * envVarName,
                                   const char * separator);
  static SbStringList * dirsearchlist;

  SbList<SoInput_FileInfo *> filestack;
  SoInput_FileInfo * getTopOfStack(void) const {
    return this->filestack[0];
  }

  SoInputP * pimpl;
};

#endif // !COIN_SOINPUT_H
