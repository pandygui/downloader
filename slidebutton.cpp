/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     rekols <rekols@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "slidebutton.h"
#include "dsvgrenderer.h"
#include "dhidpihelper.h"

#include <QPainter>
#include <QDebug>

DWIDGET_USE_NAMESPACE

SlideButton::SlideButton(QWidget *parent)
    : QPushButton(parent)
{
    const qreal ratio = devicePixelRatioF();
    setIconSize(QSize(15, 15) * ratio);

    connect(this, &QPushButton::toggled, this, &SlideButton::handleChanged);
}

SlideButton::~SlideButton()
{
}

void SlideButton::setNormalPic(const QString &fileName)
{
    const qreal ratio = devicePixelRatioF();

    m_normalPic = DSvgRenderer::render(fileName, QSize(15, 15) * ratio);
    m_normalPic.setDevicePixelRatio(ratio);
    setIcon(m_normalPic);
}

void SlideButton::setActivePic(const QString &fileName)
{
    const qreal ratio = devicePixelRatioF();

    m_activePic = DSvgRenderer::render(fileName, QSize(15, 15) * ratio);
    m_activePic.setDevicePixelRatio(ratio);
}

void SlideButton::handleChanged(bool checked)
{
    if (checked) {
        setIcon(m_activePic);
    } else {
        setIcon(m_normalPic);
    }
}

void SlideButton::paintEvent(QPaintEvent *e)
{
    QPushButton::paintEvent(e);

    if (!isChecked())
        return;

    QRect r = rect();
    r.setLeft(r.right() - 2);

    QPainter painter(this);
    painter.fillRect(r, QColor(44, 167, 248));
}
