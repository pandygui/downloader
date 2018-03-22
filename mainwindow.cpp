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
      m_taskManager(new TaskManager),
      m_aria2RPC(new Aria2RPC)
{
    titlebar()->setCustomWidget(m_toolBar, Qt::AlignVCenter, false);
    titlebar()->setSeparatorVisible(true);
    titlebar()->setFixedHeight(45);

    QWidget *centralWidget = new QWidget;
    QHBoxLayout *centralLayout = new QHBoxLayout(centralWidget);

    centralLayout->addWidget(m_slideBar);
    centralLayout->addWidget(m_taskManager);
    centralLayout->setSpacing(0);
    centralLayout->setMargin(0);

    setCentralWidget(centralWidget);
    setWindowIcon(QIcon(":/images/deepin-downloader.svg"));

    initAria2c();
    setMinimumSize(900, 588);
    resize(900, 588);

    setStyleSheet(Utils::getQssContent(":/qss/style.qss"));
    setFocusPolicy(Qt::ClickFocus);

    connect(m_toolBar, &ToolBar::newTaskBtnClicked, this, &MainWindow::onNewTaskBtnClicked);
}

MainWindow::~MainWindow()
{
}

void MainWindow::initAria2c()
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
    connect(dlg, &NewTaskDialog::startDownload, this, &MainWindow::handleAddNewTask);
    dlg->exec();
}

void MainWindow::handleAddNewTask(const QString &url)
{
    m_aria2RPC->addUri(url, "test");
}
