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

#include "toolbar.h"
#include "utils.h"
#include "dimagebutton.h"
#include "newtaskdialog.h"

#include <QHBoxLayout>
#include <QTimer>
#include <QLabel>

DWIDGET_USE_NAMESPACE

ToolBar::ToolBar(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    QLabel *iconLabel = new QLabel;
    QPixmap iconPixmap = Utils::renderSVG(":/images/deepin-downloader.svg", QSize(22, 22));

    iconLabel->setPixmap(iconPixmap);

    m_taskAddBtn = new DImageButton(":/images/task_new_normal.svg",
                                    ":/images/task_new_hover.svg",
                                    ":/images/task_new_press.svg");
    m_taskStartBtn = new DImageButton(":/images/task_start_normal.svg",
                                      ":/images/task_start_hover.svg",
                                      ":/images/task_start_press.svg");
    m_taskPauseBtn = new DImageButton(":/images/task_pause_normal.svg",
                                      ":/images/task_pause_hover.svg",
                                      ":/images/task_pause_press.svg");
    m_taskDeleteBtn = new DImageButton(":/images/task_delete_normal.svg",
                                       ":/images/task_delete_hover.svg",
                                       ":/images/task_delete_press.svg");
    m_searchBtn = new DImageButton(":/images/search_normal.svg",
                                   ":/images/search_hover.svg",
                                   ":/images/search_press.svg");
    m_searchEdit = new DSearchEdit;

    m_taskStartBtn->setDisabledPic(":/images/task_start_insensitive.svg");
    m_taskPauseBtn->setDisabledPic(":/images/task_pause_insensitive.svg");
    m_taskDeleteBtn->setDisabledPic(":/images/task_delete_insensitive.svg");

    m_taskAddBtn->setFixedSize(24, 24);
    m_taskStartBtn->setFixedSize(24, 24);
    m_taskPauseBtn->setFixedSize(24, 24);
    m_taskDeleteBtn->setFixedSize(24, 24);
    m_searchBtn->setFixedSize(24, 24);

    m_taskAddBtn->setFocusPolicy(Qt::NoFocus);
    m_taskStartBtn->setFocusPolicy(Qt::NoFocus);
    m_taskPauseBtn->setFocusPolicy(Qt::NoFocus);
    m_taskDeleteBtn->setFocusPolicy(Qt::NoFocus);
    m_searchBtn->setFocusPolicy(Qt::NoFocus);

    m_searchEdit->setVisible(false);
    m_searchEdit->setFixedWidth(300);

    layout->setMargin(0);
    layout->setSpacing(28);

    layout->addSpacing(5);
    layout->addWidget(iconLabel);
    layout->addStretch();
    layout->addWidget(m_taskAddBtn);
    layout->addWidget(m_taskStartBtn);
    layout->addWidget(m_taskPauseBtn);
    layout->addWidget(m_taskDeleteBtn);
    layout->addWidget(m_searchBtn);
    layout->addWidget(m_searchEdit);
    layout->addStretch();

    setFocusPolicy(Qt::ClickFocus);

    connect(m_taskAddBtn, &DImageButton::clicked, this, &ToolBar::newTaskBtnClicked);
    connect(m_taskStartBtn, &DImageButton::clicked, this, &ToolBar::startBtnClicked);
    connect(m_taskPauseBtn, &DImageButton::clicked, this, &ToolBar::pauseBtnClicked);
    connect(m_taskDeleteBtn, &DImageButton::clicked, this, &ToolBar::deleteBtnClicked);
    connect(m_searchBtn, &DImageButton::clicked, this, &ToolBar::showSearchEdit);
    connect(m_searchEdit, &DSearchEdit::focusOut, this, [=] { QTimer::singleShot(300, this, &ToolBar::showToolsButton); });
}

ToolBar::~ToolBar()
{
}

void ToolBar::setStartButtonEnabled(bool enabled)
{
    m_taskStartBtn->setEnabled(enabled);
}

void ToolBar::setPauseButtonEnabled(bool enabled)
{
    m_taskPauseBtn->setEnabled(enabled);
}

void ToolBar::setDeleteButtonEnabled(bool enabled)
{
    m_taskDeleteBtn->setEnabled(enabled);
}

void ToolBar::showToolsButton()
{
    m_taskAddBtn->setVisible(true);
    m_taskStartBtn->setVisible(true);
    m_taskPauseBtn->setVisible(true);
    m_taskDeleteBtn->setVisible(true);
    m_searchBtn->setVisible(true);
    m_searchEdit->setVisible(false);
}

void ToolBar::showSearchEdit()
{
    m_taskAddBtn->setVisible(false);
    m_taskStartBtn->setVisible(false);
    m_taskPauseBtn->setVisible(false);
    m_taskDeleteBtn->setVisible(false);
    m_searchBtn->setVisible(false);
    m_searchEdit->setVisible(true);
    m_searchEdit->setFocus();
}
