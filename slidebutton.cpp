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

#include <QPainter>
#include <QDebug>

DWIDGET_USE_NAMESPACE

SlideButton::SlideButton(QWidget *parent)
    : QPushButton(parent)
{
}

SlideButton::~SlideButton()
{
}

void SlideButton::setNormalPic(const QString &fileName)
{
    const qreal ratio = devicePixelRatioF();

    m_normalPic = DSvgRenderer::render(fileName, QSize(16, 16) * ratio);
    m_normalPic.setDevicePixelRatio(ratio);

    update();
}

void SlideButton::setActivePic(const QString &fileName)
{
    const qreal ratio = devicePixelRatioF();

    m_activePic = DSvgRenderer::render(fileName, QSize(16, 16) * ratio);
    m_activePic.setDevicePixelRatio(ratio);
}

void SlideButton::setTextStr(const QString &text)
{
    m_text = text;

    update();
}

void SlideButton::paintEvent(QPaintEvent *e)
{
    QPushButton::paintEvent(e);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

    const QPixmap iconPixmap = isChecked() ? m_activePic : m_normalPic;
    const int padding = 15;
    const QRect r = rect();

    QFont font;
    font.setPointSize(11);
    painter.setFont(font);

    // draw icon.
    const int iconY = (r.height() - iconPixmap.height() / iconPixmap.devicePixelRatio()) / 2;
    const int iconWidth = iconPixmap.width() / iconPixmap.devicePixelRatio();
    const int iconHeight = iconPixmap.height() / iconPixmap.devicePixelRatio();
    painter.drawPixmap(QRect(padding, iconY, iconWidth, iconHeight), iconPixmap);

    // draw text.
    painter.setPen(isChecked() ? QColor("#2CA7F8") : QColor("#000000"));
    painter.drawText(QRect(iconWidth + padding + 5, 0, r.width(), r.height()), Qt::AlignVCenter | Qt::AlignLeft, m_text);

    if (!isChecked())
        return;

    // draw right separator line.
    QRect rightRect = r;
    rightRect.setLeft(r.right() - 2);
    painter.fillRect(rightRect, QColor(44, 167, 248));
}
