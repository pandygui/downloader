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

#ifndef SLIDEBAR_H
#define SLIDEBAR_H

#include <QFrame>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QMap>

#include "slidebutton.h"

class SlideBar : public QFrame
{
    Q_OBJECT

public:
    SlideBar(QWidget *parent = nullptr);
    ~SlideBar();

    void initButton();
    int index() { return m_currentIndex; }

signals:
    void buttonClicked(const int index);

private:
    QVBoxLayout *m_layout;
    QButtonGroup *m_buttonGroup;
    QStringList m_buttonsKey;
    QMap<QString, QString> m_buttonList;

    int m_currentIndex = 0;
};

#endif
