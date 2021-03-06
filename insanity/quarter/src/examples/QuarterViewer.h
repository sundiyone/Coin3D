#ifndef QUARTER_QUARTERVIEWER_H
#define QUARTER_QUARTERVIEWER_H

/**************************************************************************\
 *
 *  This file is part of the SIM Quarter extension library for Coin.
 *  Copyright (C) 1998-2009 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License ("GPL") version 2
 *  as published by the Free Software Foundation.  See the file COPYING
 *  at the root directory of this source distribution for additional
 *  information about the GNU GPL.
 *
 *  For using SIM Quarter with software that can not be combined with
 *  the GNU GPL, and for taking advantage of the additional benefits of
 *  our support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org/> for more information.
 *
 *  Systems in Motion AS, Bygd�y all� 5, N-0257 Oslo, NORWAY. (www.sim.no)
 *
\**************************************************************************/

#include "ui_QuarterViewer.h"

QT_BEGIN_NAMESPACE

class QuarterViewer : public QWidget {
public:
  QuarterViewer(QWidget * parent = 0);
  ~QuarterViewer();

private:
  Ui::QuarterViewer ui;
  class SoSeparator * root;
};

QT_END_NAMESPACE

#endif // QUARTER_QUARTERVIEWER_H
