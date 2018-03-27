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
#include <QModelIndex>
#include <QTimer>
#include <QLabel>

#include "toolbar.h"
#include "slidebar.h"
#include "tableview.h"
#include "aria2rpc.h"
#include "global.h"
#include "tablemodel.h"
#include "trayicon.h"

DWIDGET_USE_NAMESPACE

class MainWindow : public DMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *);

private:
    void startAria2c();

private slots:
    void activeWindow();
    void setStatusText(const int &total, const int &processing);
    void onNewTaskBtnClicked();
    void onStartBtnClicked();
    void onPauseBtnClicked();
    void onDeleteBtnClicked();
    void handleDialogAddTask(const QString &url);
    void handleAddedTask(const QString &gid);
    void handleUpdateStatus(const QString &fileName, const QString &gid, const int &status, const QString &totalLength,
                            const QString &completedLenth, const QString &speed, const int &percent);
    void updateToolBarStatus(const QModelIndex &index);
    void refreshEvent();

private:
    ToolBar *m_toolBar;
    SlideBar *m_slideBar;
    TableView *m_tableView;
    Aria2RPC *m_aria2RPC;
    TrayIcon *m_trayIcon;
    QLabel *m_statusLabel;
    QTimer *m_refreshTimer;
};

#endif
