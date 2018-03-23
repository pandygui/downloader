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

#include "mainwindow.h"
#include "dtitlebar.h"
#include "newtaskdialog.h"
#include "utils.h"

#include <QPushButton>
#include <QLineEdit>
#include <QProcess>
#include <QDebug>
#include <QLabel>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent),
      m_toolBar(new ToolBar),
      m_slideBar(new SlideBar),
      m_tableView(new TableView),
      m_aria2RPC(new Aria2RPC),
      m_refreshTimer(new QTimer(this))
{
    titlebar()->setCustomWidget(m_toolBar, Qt::AlignVCenter, false);
    titlebar()->setSeparatorVisible(true);
    titlebar()->setFixedHeight(45);

    QWidget *centralWidget = new QWidget;
    QHBoxLayout *centralLayout = new QHBoxLayout(centralWidget);
    QVBoxLayout *taskLayout = new QVBoxLayout;

    taskLayout->addWidget(m_tableView);

    m_refreshTimer->setInterval(1000);

    centralLayout->addWidget(m_slideBar);
    centralLayout->addLayout(taskLayout);
    centralLayout->setSpacing(0);
    centralLayout->setMargin(0);

    setCentralWidget(centralWidget);
    setWindowIcon(QIcon(":/images/deepin-downloader.svg"));

    startAria2c();
    setMinimumSize(900, 588);
    resize(900, 588);

    setStyleSheet(Utils::getQssContent(":/qss/style.qss"));
    setFocusPolicy(Qt::ClickFocus);

    connect(m_toolBar, &ToolBar::newTaskBtnClicked, this, &MainWindow::onNewTaskBtnClicked);
    connect(m_aria2RPC, &Aria2RPC::addedTask, this, &MainWindow::handleAddedTask);
    connect(m_aria2RPC, &Aria2RPC::updateStatus, this, &MainWindow::handleUpdateStatus);
    connect(m_refreshTimer, &QTimer::timeout, this, &MainWindow::refreshEvent);
}

MainWindow::~MainWindow()
{
}

void MainWindow::startAria2c()
{
    QProcess *process = new QProcess(this);

    QStringList args;
    args << QString("--dir=%1/Desktop").arg(QDir::homePath());
    args << "--enable-rpc=true";
    args << "--rpc-listen-port=7200";
    args << "--rpc-allow-origin-all=true";
    args << "--rpc-save-upload-metadata=true";
    args << "--check-certificate=false";
    args << "--disable-ipv6";

    process->start("/usr/bin/aria2c", args);
}

void MainWindow::onNewTaskBtnClicked()
{
    NewTaskDialog *dlg = new NewTaskDialog;
    connect(dlg, &NewTaskDialog::startDownload, this, &MainWindow::handleDialogAddTask);
    dlg->exec();
}

void MainWindow::handleDialogAddTask(const QString &url)
{
    m_aria2RPC->addUri(url, "");
    m_refreshTimer->start();
}

void MainWindow::handleAddedTask(const QString &gid)
{
    GlobalStruct *data = new GlobalStruct;
    data->gid = gid;

    m_tableView->model()->append(data);
}

void MainWindow::handleUpdateStatus(const QString &gid, const QString &status, const QString &totalLength,
                                     const QString &completedLenth, const QString &speed, const int &percent)
{
    GlobalStruct *data = m_tableView->model()->find(gid);

    if (!data) return;

    data->gid = gid;
    data->status = status;
    data->totalLength = totalLength;
    data->completedLenth = completedLenth;
    data->percent = percent;
    data->speed = speed;

    m_tableView->update();
}

void MainWindow::refreshEvent()
{
    auto *list = m_tableView->model()->dataList();

    for (int i = 0; i < list->size(); ++i) {
        m_aria2RPC->tellStatus(list->at(i)->gid);
    }
}
