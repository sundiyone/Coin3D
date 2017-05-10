#ifndef COIN_SOGLNURBS_H
#define COIN_SOGLNURBS_H

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

#ifndef COIN_INTERNAL
#error this is a private header file
#endif /* !COIN_INTERNAL */

#include <Inventor/SbBasic.h>

class SoAction;
class SoShape;

bool sogl_calculate_nurbs_normals();

void
sogl_render_nurbs_surface(SoAction * action, SoShape * shape,
                          void * nurbsrenderer,
                          const int numuctrlpts, const int numvctrlpts,
                          const float * uknotvec, const float * vknotvec,
                          const int numuknot, const int numvknot,
                          const int numsctrlpts, const int numtctrlpts,
                          const float * sknotvec, const float * tknotvec,
                          const int numsknot, const int numtknot,
                          const bool glrender,
                          const int numcoordindex = 0, const int32_t * coordindex = nullptr,
                          const int numtexcoordindex = 0, const int32_t * texcoordindex = nullptr);

void sogl_render_nurbs_curve(SoAction * action, SoShape * shape,
                             void * nurbsrenderer,
                             const int numctrlpts,
                             const float * knotvec,
                             const int numknots,
                             const bool glrender,
                             const bool drawaspoints = false,
                             const int numcoordindex = 0, const int32_t * coordindex = nullptr);



#endif // COIN_SOGLNURBS_H
