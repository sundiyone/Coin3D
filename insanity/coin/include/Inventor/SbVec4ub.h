#ifndef COIN_SBVEC4UB_H
#define COIN_SBVEC4UB_H

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

#include <Inventor/SbBasic.h>
#include <Inventor/system/inttypes.h>
#ifndef NDEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // !NDEBUG

class SbVec4b;
class SbVec4us;
class SbVec4ui32;

class COIN_DLL_API SbVec4ub {
public:
  SbVec4ub(void) { }
  SbVec4ub(const uint8_t v[4]) { vec[0] = v[0]; vec[1] = v[1]; vec[2] = v[2]; vec[3] = v[3]; }
  SbVec4ub(uint8_t x, uint8_t y, uint8_t z, uint8_t w) { vec[0] = x; vec[1] = y; vec[2] = z; vec[3] = w; }
  explicit SbVec4ub(const SbVec4b & v) { setValue(v); }
  explicit SbVec4ub(const SbVec4us & v) { setValue(v); }
  explicit SbVec4ub(const SbVec4ui32 & v) { setValue(v); }

  SbVec4ub & setValue(const uint8_t v[4]) { vec[0] = v[0]; vec[1] = v[1]; vec[2] = v[2]; vec[3] = v[3]; return *this; } 
  SbVec4ub & setValue(uint8_t x, uint8_t y, uint8_t z, uint8_t w) { vec[0] = x; vec[1] = y; vec[2] = z; vec[3] = w; return *this; } 
  SbVec4ub & setValue(const SbVec4b & v);
  SbVec4ub & setValue(const SbVec4us & v);
  SbVec4ub & setValue(const SbVec4ui32 & v);

  const uint8_t * getValue(void) const { return vec; }
  void getValue(uint8_t & x, uint8_t & y, uint8_t & z, uint8_t & w) const { x = vec[0]; y = vec[1]; z = vec[2]; w = vec[3]; }

  uint8_t & operator[](int i) { return vec[i]; }
  const uint8_t & operator[](int i) const { return vec[i]; }

  int32_t dot(SbVec4ub v) const { return vec[0] * v[0] + vec[1] * v[1] + vec[2] * v[2] + vec[3] * v[3]; }
  void negate(void);

  SbVec4ub & operator*=(int d) { vec[0] *= d; vec[1] *= d; vec[2] *= d; vec[3] *= d; return *this; }
  SbVec4ub & operator*=(double d);
  SbVec4ub & operator/=(int d) { SbDividerChk("SbVec4ub::operator/=(int)", d); vec[0] /= d; vec[1] /= d; vec[2] /= d; vec[3] /= d; return *this; }
  SbVec4ub & operator/=(double d) { SbDividerChk("SbVec4ub::operator/=(double)", d); return operator*=(1.0 / d); }
  SbVec4ub & operator+=(SbVec4ub v) { vec[0] += v[0]; vec[1] += v[1]; vec[2] += v[2]; vec[3] += v[3]; return *this; }
  SbVec4ub & operator-=(SbVec4ub v) { vec[0] -= v[0]; vec[1] -= v[1]; vec[2] -= v[2]; vec[3] -= v[3]; return *this; }
  SbVec4ub operator-(void) const { SbVec4ub v(*this); v.negate(); return v; }

protected:
  uint8_t vec[4];

}; // SbVec4ub

inline SbVec4ub operator*(SbVec4ub v, int d) {
  SbVec4ub val(v); val *= d; return val;
}

inline SbVec4ub operator*(SbVec4ub v, double d) {
  SbVec4ub val(v); val *= d; return val;
}

inline SbVec4ub operator*(int d, SbVec4ub v) {
  SbVec4ub val(v); val *= d; return val;
}

inline SbVec4ub operator*(double d, SbVec4ub v) {
  SbVec4ub val(v); val *= d; return val;
}

inline SbVec4ub operator/(SbVec4ub v, int d) {
  SbDividerChk("operator/(SbVec4ub,int)", d);
  SbVec4ub val(v); val /= d; return val;
}

inline SbVec4ub operator/(SbVec4ub v, double d) {
  SbDividerChk("operator/(SbVec4ub,double)", d);
  SbVec4ub val(v); val /= d; return val;
}

inline SbVec4ub operator+(SbVec4ub v1, SbVec4ub v2) {
  SbVec4ub v(v1); v += v2; return v;
}

inline SbVec4ub operator-(SbVec4ub v1, SbVec4ub v2) {
  SbVec4ub v(v1); v -= v2; return v;
}

inline bool operator==(SbVec4ub v1, SbVec4ub v2) {
  return ((v1[0] == v2[0]) && (v1[1] == v2[1]) && (v1[2] == v2[2]) && (v1[3] == v2[3]));
}

inline bool operator!=(SbVec4ub v1, SbVec4ub v2) {
  return !(v1 == v2);
}

#endif // !COIN_SBVEC4UB_H
