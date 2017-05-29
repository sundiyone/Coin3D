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

// FIXME: not in use yet. 19990620 mortene.

#include <stdio.h>

#include <qslider.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qframe.h>

#include <soqtdefs.h>
#include <Inventor/Qt/QColorSelection.h>


QColorSelection::QColorSelection(QWidget *parent, const char *name, QColor *col) : QWidget(parent, name)
{
  if (col == NULL) {
    QColor tempcol(0, 0, 0);
    col = &tempcol;
  }

  QGridLayout* grid = new QGridLayout(this, 4, 2);

  red   = new QSlider(0, 255, 1, col->red(),   QSlider::Horizontal, this);
  green = new QSlider(0, 255, 1, col->green(), QSlider::Horizontal, this);
  blue  = new QSlider(0, 255, 1, col->blue(),  QSlider::Horizontal, this);

  QFrame* frame = new QFrame(this);
  color = new QWidget(frame);

  QLabel* rgblabels[3];
  rgblabels[0] = new QLabel("R:", this);
  rgblabels[1] = new QLabel("G:", this);
  rgblabels[2] = new QLabel("B:", this);
  rgblabels[0]->setMinimumSize(rgblabels[0]->sizeHint());
  rgblabels[1]->setMinimumSize(rgblabels[1]->sizeHint());
  rgblabels[2]->setMinimumSize(rgblabels[2]->sizeHint());
  rgblabels[0]->setAlignment(AlignRight);
  rgblabels[1]->setAlignment(AlignRight);
  rgblabels[2]->setAlignment(AlignRight);

  grid->addMultiCellWidget(frame, 0, 0, 0, 1);
  grid->addMultiCellWidget(color, 0, 0, 0, 1);

  grid->addWidget(rgblabels[0], 1, 0);
  grid->addWidget(rgblabels[1], 2, 0);
  grid->addWidget(rgblabels[2], 3, 0);

  grid->addWidget(red,   1, 1);
  grid->addWidget(green, 2, 1);
  grid->addWidget(blue,  3, 1);

  grid->setColStretch(0, 1);
  grid->setColStretch(1, 10);

  valueChanged();

  QObject::connect(red, SIGNAL(valueChanged(int)), this, SLOT(valueChanged()));
  QObject::connect(green, SIGNAL(valueChanged(int)), this, SLOT(valueChanged()));
  QObject::connect(blue, SIGNAL(valueChanged(int)), this, SLOT(valueChanged()));


}

void QColorSelection::valueChanged()
{
  QColor col(red->value(), green->value(), blue->value());
  color->setBackgroundColor(col);
  emit colorChanged(col);
}

void QColorSelection::setType(const char *typeString)
{
#ifdef linux
  snprintf(titleString, MAX_TITLE, "%sColorEditor", typeString);
#else
  sprintf(titleString, "%sColorEditor", typeString);
#endif
  this->setCaption(titleString);
}

void QColorSelection::setColor(QColor col)
{
  printf("Setting color %i, %i, %i\n", col.red(), col.green(), col.blue());
  red->setValue(col.red());
  green->setValue(col.green());
  blue->setValue(col.blue());
}

void QColorSelection::closeEvent(QCloseEvent *e)
{
  e->accept();
  emit closed();
}
