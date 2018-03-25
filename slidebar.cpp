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

#include "slidebar.h"

#define BUTTON_HEIGHT 35

SlideBar::SlideBar(QWidget *parent)
    : QFrame(parent),
      m_layout(new QVBoxLayout(this)),
      m_buttonGroup(new QButtonGroup)
{
    m_layout->setMargin(0);
    m_layout->setSpacing(0);

    m_buttonList.insert("nav_alltask", tr("All tasks"));
    m_buttonList.insert("nav_downloading", tr("Downloading"));
    m_buttonList.insert("nav_paused", tr("Paused"));
    m_buttonList.insert("nav_done", tr("Finished"));
    m_buttonList.insert("nav_trash", tr("Trash"));

    setObjectName("SlideBar");
    setFixedWidth(200);
    initButton();
}

SlideBar::~SlideBar()
{
}

void SlideBar::initButton()
{
    int count = 0;

    for (const auto &key : m_buttonList.keys()) {
        SlideButton *btn = new SlideButton;
        btn->setText(" " + m_buttonList[key]);
        btn->setFixedHeight(BUTTON_HEIGHT);
        btn->setCheckable(true);
        btn->setNormalPic(QString(":/images/%1_normal.svg").arg(key));
        btn->setActivePic(QString(":/images/%1_active.svg").arg(key));

        m_layout->addWidget(btn);
        m_buttonGroup->addButton(btn);

        if (count == 0) {
            btn->setChecked(true);
        }

        connect(btn, &SlideButton::clicked, this, [=] { Q_EMIT buttonClicked(count); });

        ++count;
    }

    m_layout->addStretch();
}
