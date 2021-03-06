#ifndef COIN_SBVEC3US_H
#define COIN_SBVEC3US_H

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

#include <cstdio>
#include <Inventor/SbBasic.h>
#include <Inventor/system/inttypes.h>
#include <Inventor/SbByteBuffer.h>
#include <Inventor/SbString.h>

#ifndef NDEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // !NDEBUG

class SbVec3s;
class SbVec3ub;
class SbVec3ui32;

class COIN_DLL_API SbVec3us {
public:
  SbVec3us(void) { }
  SbVec3us(const unsigned short v[3]) { vec[0] = v[0]; vec[1] = v[1]; vec[2] = v[2]; }
  SbVec3us(unsigned short x, unsigned short y, unsigned short z) { vec[0] = x; vec[1] = y; vec[2] = z; }
  explicit SbVec3us(const SbVec3s & v) { setValue(v); }
  explicit SbVec3us(const SbVec3ub & v) { setValue(v); }
  explicit SbVec3us(const SbVec3ui32 & v) { setValue(v); }

  SbVec3us & setValue(const unsigned short v[3]) { vec[0] = v[0]; vec[1] = v[1]; vec[2] = v[2]; return *this; }
  SbVec3us & setValue(unsigned short x, unsigned short y, unsigned short z) { vec[0] = x; vec[1] = y; vec[2] = z; return *this; }
  SbVec3us & setValue(const SbVec3s & v);
  SbVec3us & setValue(const SbVec3ub & v);
  SbVec3us & setValue(const SbVec3ui32 & v);

  const unsigned short * getValue(void) const { return vec; }
  void getValue(unsigned short & x, unsigned short & y, unsigned short & z) const { x = vec[0]; y = vec[1]; z = vec[2]; }

  unsigned short & operator[](int i) { return vec[i]; }
  const unsigned short & operator[](int i) const { return vec[i]; }

  int32_t dot(const SbVec3us & v) const { return vec[0] * v[0] + vec[1] * v[1] + vec[2] * v[2]; }
  void negate(void);

  SbVec3us & operator*=(int d) { vec[0] *= d; vec[1] *= d; vec[2] *= d; return *this; }
  SbVec3us & operator*=(double d);
  SbVec3us & operator/=(int d) { SbDividerChk("SbVec3us::operator/=(int)", d); vec[0] /= d; vec[1] /= d; vec[2] /= d; return *this; }
  SbVec3us & operator/=(double d) { SbDividerChk("SbVec3us::operator/=(double)", d); return operator*=(1.0 / d); }
  SbVec3us & operator+=(const SbVec3us & v) { vec[0] += v[0]; vec[1] += v[1]; vec[2] += v[2]; return *this; }
  SbVec3us & operator-=(const SbVec3us & v) { vec[0] -= v[0]; vec[1] -= v[1]; vec[2] -= v[2]; return *this; }
  SbVec3us operator-(void) const { SbVec3us v(*this); v.negate(); return v; }

protected:
  unsigned short vec[3];

}; // SbVec3us

inline SbVec3us operator*(const SbVec3us & v, int d) {
  SbVec3us val(v); val *= d; return val;
}

inline SbVec3us operator*(const SbVec3us & v, double d) {
  SbVec3us val(v); val *= d; return val;
}

inline SbVec3us operator*(int d, const SbVec3us & v) {
  SbVec3us val(v); val *= d; return val;
}

inline SbVec3us operator*(double d, const SbVec3us & v) {
  SbVec3us val(v); val *= d; return val;
}

inline SbVec3us operator/(const SbVec3us & v, int d) {
  SbDividerChk("operator/(SbVec3us,int)", d);
  SbVec3us val(v); val /= d; return val;
}

inline SbVec3us operator/(const SbVec3us & v, double d) {
  SbDividerChk("operator/(SbVec3us,double)", d);
  SbVec3us val(v); val /= d; return val;
}

inline SbVec3us operator+(const SbVec3us & v1, const SbVec3us & v2) {
  SbVec3us v(v1); v += v2; return v;
}

inline SbVec3us operator-(const SbVec3us & v1, const SbVec3us & v2) {
  SbVec3us v(v1); v -= v2; return v;
}

inline bool operator==(const SbVec3us & v1, const SbVec3us & v2) {
  return ((v1[0] == v2[0]) && (v1[1] == v2[1]) && (v1[2] == v2[2]));
}

inline bool operator!=(const SbVec3us & v1, const SbVec3us & v2) {
  return !(v1 == v2);
}

#endif // !COIN_SBVEC3US_H
