#ifndef COIN_SOANTISQUISH_H
#define COIN_SOANTISQUISH_H

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

#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/nodes/SoTransformation.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/SbMatrix.h>

class COIN_DLL_API SoAntiSquish : public SoTransformation {
  typedef SoTransformation inherited;

  SO_NODE_HEADER(SoAntiSquish);

public:
  static void initClass(void);
  SoAntiSquish(void);

  enum Sizing {
    X, Y, Z, AVERAGE_DIMENSION, BIGGEST_DIMENSION, SMALLEST_DIMENSION,
    LONGEST_DIAGONAL
  };

  SoSFEnum sizing;
  SoSFBool recalcAlways;

  void recalc(void);
  virtual void doAction(SoAction * action);

protected:
  virtual ~SoAntiSquish();

  virtual void callback(SoCallbackAction * action);
  virtual void GLRender(SoGLRenderAction * action);
  virtual void getBoundingBox(SoGetBoundingBoxAction * action);
  virtual void getMatrix(SoGetMatrixAction * action);
  virtual void pick(SoPickAction * action);

  SbMatrix getUnsquishingMatrix(const SbMatrix & squishedmatrix,
                                const bool calcinverse,
                                SbMatrix & getinverse);
private:
  SbMatrix unsquishedmatrix, inversematrix;
  bool matrixvalid, inversevalid;
};

#endif // !COIN_SOANTISQUISH_H
