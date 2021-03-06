#ifndef COIN_SBVEC4D_H
#define COIN_SBVEC4D_H

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

#include <stdio.h>

#include <Inventor/SbBasic.h>
#ifndef NDEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // !NDEBUG

class SbVec4f;
class SbVec4b;
class SbVec4s;
class SbVec4i32;
class SbVec3d;

class COIN_DLL_API SbVec4d {
public:
  SbVec4d(void) { }
  SbVec4d(const double v[4]) { vec[0] = v[0]; vec[1] = v[1]; vec[2] = v[2]; vec[3] = v[3]; }
  SbVec4d(double x, double y, double z, double w) { vec[0] = x; vec[1] = y; vec[2] = z; vec[3] = w; }
  explicit SbVec4d(const SbVec4f & v) { setValue(v); }
  explicit SbVec4d(const SbVec4b & v) { setValue(v); }
  explicit SbVec4d(const SbVec4s & v) { setValue(v); }
  explicit SbVec4d(const SbVec4i32 & v) { setValue(v); }

  SbVec4d & setValue(const double v[4]) { vec[0] = v[0]; vec[1] = v[1]; vec[2] = v[2]; vec[3] = v[3]; return *this; }
  SbVec4d & setValue(double x, double y, double z, double w) { vec[0] = x; vec[1] = y; vec[2] = z; vec[3] = w; return *this; }
  SbVec4d & setValue(const SbVec4f & v);
  SbVec4d & setValue(const SbVec4b & v);
  SbVec4d & setValue(const SbVec4s & v);
  SbVec4d & setValue(const SbVec4i32 & v);

  const double * getValue(void) const { return vec; }
  void getValue(double & x, double & y, double & z, double & w) const { x = vec[0]; y = vec[1]; z = vec[2]; w = vec[3]; }

  double & operator[](int i) { return vec[i]; }
  const double & operator[](int i) const { return vec[i]; }

  double dot(const SbVec4d & v) const { return vec[0] * v[0] + vec[1] * v[1] + vec[2] * v[2] + vec[3] * v[3]; }
  bool equals(const SbVec4d & v, double tolerance) const;
  void getReal(SbVec3d & v) const;
  double length(void) const;
  double sqrLength(void) const { return vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2] + vec[3] * vec[3]; }
  void negate(void) { vec[0] = -vec[0]; vec[1] = -vec[1]; vec[2] = -vec[2]; vec[3] = -vec[3]; }
  double normalize(void);

  SbVec4d & operator*=(double d) { vec[0] *= d; vec[1] *= d; vec[2] *= d; vec[3] *= d; return *this; }
  SbVec4d & operator/=(double d) { SbDividerChk("SbVec4d::operator/=(double)", d); return operator*=(1.0 / d); }
  SbVec4d & operator+=(const SbVec4d & v) { vec[0] += v[0]; vec[1] += v[1]; vec[2] += v[2]; vec[3] += v[3]; return *this; }
  SbVec4d & operator-=(const SbVec4d & v) { vec[0] -= v[0]; vec[1] -= v[1]; vec[2] -= v[2]; vec[3] -= v[3]; return *this; }
  SbVec4d operator-(void) const { return SbVec4d(-vec[0], -vec[1], -vec[2], -vec[3]); }

  void print(FILE * fp) const;

protected:
  double vec[4];

}; // SbVec4d

inline SbVec4d operator*(const SbVec4d & v, double d) {
  SbVec4d val(v); val *= d; return val;
}

inline SbVec4d operator*(double d, const SbVec4d & v) {
  SbVec4d val(v); val *= d; return val;
}

inline SbVec4d operator/(const SbVec4d & v, double d) {
  SbDividerChk("operator/(SbVec4d,double)", d);
  SbVec4d val(v); val /= d; return val;
}

inline SbVec4d operator+(const SbVec4d & v1, const SbVec4d & v2) {
  SbVec4d v(v1); v += v2; return v;
}

inline SbVec4d operator-(const SbVec4d & v1, const SbVec4d & v2) {
  SbVec4d v(v1); v -= v2; return v;
}

inline bool operator==(const SbVec4d & v1, const SbVec4d & v2) {
  return ((v1[0] == v2[0]) && (v1[1] == v2[1]) && (v1[2] == v2[2]) && (v1[3] == v2[3]));
}

inline bool operator!=(const SbVec4d & v1, const SbVec4d & v2) {
  return !(v1 == v2);
}

#endif // !COIN_SBVEC4D_H
