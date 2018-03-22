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

#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include "dimagebutton.h"
#include "dsearchedit.h"

DWIDGET_USE_NAMESPACE

class ToolBar : public QWidget
{
    Q_OBJECT

public:
    ToolBar(QWidget *parent = nullptr);
    ~ToolBar();

signals:
    void newTaskBtnClicked();

private slots:
    void showToolsButton();
    void showSearchEdit();

private:
    DImageButton *m_taskAddBtn;
    DImageButton *m_taskStartBtn;
    DImageButton *m_taskPauseBtn;
    DImageButton *m_taskDeleteBtn;
    DImageButton *m_searchBtn;
    DSearchEdit *m_searchEdit;
};

#endif
