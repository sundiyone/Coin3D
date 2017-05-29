#ifndef COIN_SOOVERRIDEELEMENT_H
#define COIN_SOOVERRIDEELEMENT_H

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

#include <Inventor/elements/SoSubElement.h>
#include <Inventor/system/inttypes.h>

class SoType; // lame doxygen "fix"

class COIN_DLL_API SoOverrideElement : public SoElement {
  typedef SoElement inherited;

  SO_ELEMENT_HEADER(SoOverrideElement);
public:
  static void initClass(void);
protected:
  virtual ~SoOverrideElement();

public:
  enum FlagBits {
    AMBIENT_COLOR     = 0x00000001,
    COLOR_INDEX       = 0x00000002,
    COMPLEXITY        = 0x00000004,
    COMPLEXITY_TYPE   = 0x00000008,
    CREASE_ANGLE      = 0x00000010,
    DIFFUSE_COLOR     = 0x00000020,
    DRAW_STYLE        = 0x00000040,
    EMISSIVE_COLOR    = 0x00000080,
    FONT_NAME         = 0x00000100,
    FONT_SIZE         = 0x00000200,
    LIGHT_MODEL       = 0x00000400,
    LINE_PATTERN      = 0x00000800,
    LINE_WIDTH        = 0x00001000,
    MATERIAL_BINDING  = 0x00002000,
    POINT_SIZE        = 0x00004000,
    PICK_STYLE        = 0x00008000,
    SHAPE_HINTS       = 0x00010000,
    SHININESS         = 0x00020000,
    SPECULAR_COLOR    = 0x00040000,
    POLYGON_OFFSET    = 0x00080000,
    TRANSPARENCY      = 0x00100000,
    TRANSPARENCY_TYPE = 0x00200000, 
    NORMAL_VECTOR     = 0x00400000,
    NORMAL_BINDING    = 0x00800000
  };
  
  virtual void init(SoState * state);

  virtual void push(SoState * state);

  virtual bool matches(const SoElement * element) const;
  virtual SoElement * copyMatchInfo(void) const;

  static uint32_t getFlags(SoState * const state) {
    return (static_cast<const SoOverrideElement*>(getConstElement(state, classStackIndex)))->flags;
  }

  static bool getAmbientColorOverride(SoState * const state);
  static bool getColorIndexOverride(SoState * const state);
  static bool getComplexityOverride(SoState * const state);
  static bool getComplexityTypeOverride(SoState * const state);
  static bool getCreaseAngleOverride(SoState * const state);
  static bool getDiffuseColorOverride(SoState * const state);
  static bool getDrawStyleOverride(SoState * const state);
  static bool getEmissiveColorOverride(SoState * const state);
  static bool getFontNameOverride(SoState * const state);
  static bool getFontSizeOverride(SoState * const state);
  static bool getLightModelOverride(SoState * const state);
  static bool getLinePatternOverride(SoState * const state);
  static bool getLineWidthOverride(SoState * const state);
  static bool getMaterialBindingOverride(SoState * const state);
  static bool getPickStyleOverride(SoState * const state);
  static bool getPointSizeOverride(SoState * const state);
  static bool getPolygonOffsetOverride(SoState * const state);
  static bool getShapeHintsOverride(SoState * const state);
  static bool getShininessOverride(SoState * const state);
  static bool getSpecularColorOverride(SoState * const state);
  static bool getTransparencyOverride(SoState * const state);
  static bool getTransparencyTypeOverride(SoState * const state);
  static bool getNormalVectorOverride(SoState * const state);
  static bool getNormalBindingOverride(SoState * const state);

  static void setAmbientColorOverride(SoState * const state,
                                      SoNode * const node,
                                      const bool override);
  static void setColorIndexOverride(SoState * const state,
                                    SoNode * const node,
                                    const bool override);
  static void setComplexityOverride(SoState * const state,
                                    SoNode * const node,
                                    const bool override);
  static void setComplexityTypeOverride(SoState * const state,
                                        SoNode * const node,
                                        const bool override);
  static void setCreaseAngleOverride(SoState * const state,
                                     SoNode * const node,
                                     const bool override);
  static void setDiffuseColorOverride(SoState * const state,
                                      SoNode * const node,
                                      const bool override);
  static void setDrawStyleOverride(SoState * const state,
                                   SoNode * const node,
                                   const bool override);
  static void setEmissiveColorOverride(SoState * const state,
                                       SoNode * const node,
                                       const bool override);
  static void setFontNameOverride(SoState * const state,
                                  SoNode * const node,
                                  const bool override);
  static void setFontSizeOverride(SoState * const state,
                                  SoNode * const node,
                                  const bool override);
  static void setLightModelOverride(SoState * const state,
                                    SoNode * const node,
                                    const bool override);
  static void setLinePatternOverride(SoState * const state,
                                     SoNode * const node,
                                     const bool override);
  static void setLineWidthOverride(SoState * const state,
                                   SoNode * const node,
                                   const bool override);
  static void setMaterialBindingOverride(SoState * const state,
                                         SoNode * const node,
                                         const bool override);
  static void setPickStyleOverride(SoState * const state,
                                   SoNode * const node,
                                   const bool override);
  static void setPointSizeOverride(SoState * const state,
                                   SoNode * const node,
                                   const bool override);
  static void setPolygonOffsetOverride(SoState * const state,
                                       SoNode * const node,
                                       const bool override);
  static void setShapeHintsOverride(SoState * const state,
                                    SoNode * const node,
                                    const bool override);
  static void setShininessOverride(SoState * const state,
                                   SoNode * const node,
                                   const bool override);
  static void setSpecularColorOverride(SoState * const state,
                                       SoNode * const node,
                                       const bool override);
  static void setTransparencyOverride(SoState * const state,
                                      SoNode * const node,
                                      const bool override);
  static void setTransparencyTypeOverride(SoState * const state,
                                          SoNode * const node,
                                          const bool override);
  static void setNormalVectorOverride(SoState * const state,
                                      SoNode * const node,
                                      const bool override);
  static void setNormalBindingOverride(SoState * const state,
                                       SoNode * const node,
                                       const bool override);

  virtual void print(FILE * file) const;

private:

  uint32_t flags;
};

#endif // !COIN_SOOVERRIDEELEMENT_H
