#ifndef COIN_SONORMALCACHE_H
#define COIN_SONORMALCACHE_H

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

#include <Inventor/SbVec3f.h>
#include <Inventor/caches/SoCache.h>
#include <Inventor/system/inttypes.h>

class SoNormalGenerator;
class SoNormalCacheP;

class COIN_DLL_API SoNormalCache : public SoCache {
  typedef SoCache inherited;

public:
  SoNormalCache(SoState * const state);
  virtual ~SoNormalCache();

  void set(const int num, const SbVec3f * const normals);
  void set(SoNormalGenerator *generator);

  int getNum(void) const;
  const SbVec3f *getNormals(void) const;

  int getNumIndices(void) const;
  const int32_t *getIndices(void) const;

  void generatePerVertex(const SbVec3f * const coords,
                         const unsigned int numcoords,
                         const int32_t *coordindices,
                         const int numcoordindices,
                         const float crease_angle,
                         const SbVec3f *facenormals = nullptr,
                         const int numfacenormals = -1,
                         const bool ccw = true,
                         const bool tristrip = false);


  void generatePerFace(const SbVec3f * const coords,
                       const unsigned int numcoords,
                       const int32_t *coordindices,
                       const int numcoorindices,
                       const bool ccw);

  void generatePerFaceStrip(const SbVec3f * const coords,
                            const unsigned int numcoords,
                            const int32_t *coordindices,
                            const int numcoorindices,
                            const bool ccw);

  void generatePerStrip(const SbVec3f * const coords,
                        const unsigned int numcoords,
                        const int32_t *coordindices,
                        const int numcoorindices,
                        const bool ccw);

  void generatePerVertexQuad(const SbVec3f * const coords,
                             const unsigned int numcoords,
                             const int vPerRow,
                             const int vPerColumn,
                             const bool ccw);

  void generatePerFaceQuad(const SbVec3f * const coords,
                           const unsigned int numcoords,
                           const int vPerRow,
                           const int vPerColumn,
                           const bool ccw);

  void generatePerRowQuad(const SbVec3f * const coords,
                          const unsigned int numcoords,
                          const int vPerRow,
                          const int vPerColumn,
                          const bool ccw);

private:
  SoNormalCacheP * pimpl;
  void clearGenerator(void);
};

#endif // !COIN_SONORMALCACHE_H
