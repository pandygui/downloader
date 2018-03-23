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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
#include <QHBoxLayout>
#include <QTimer>
#include "toolbar.h"
#include "slidebar.h"
#include "tableview.h"
#include "aria2rpc.h"
#include "globalstruct.h"

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void startAria2c();

private slots:
    void onNewTaskBtnClicked();
    void handleDialogAddTask(const QString &url);
    void handleAddedTask(const QString &gid);
    void handleUpdateStatus(const QString &gid, const QString &status, const QString &totalLength, const QString &completedLenth, const QString &speed);
    void refreshEvent();

private:
    ToolBar *m_toolBar;
    SlideBar *m_slideBar;
    TableView *m_tableView;
    Aria2RPC *m_aria2RPC;
    QTimer *m_refreshTimer;

    QList<GlobalStruct *> m_dataList;
    QMap<QString, GlobalStruct *> m_map;
};

#endif
