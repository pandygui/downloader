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
#include "tablemodel.h"
#include "utils.h"

#include <QApplication>
#include <QCloseEvent>
#include <QPushButton>
#include <QLineEdit>
#include <QProcess>
#include <QDebug>
#include <QLabel>
#include <QDateTime>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent),
      m_toolBar(new ToolBar),
      m_slideBar(new SlideBar),
      m_tableView(new TableView),
      m_aria2RPC(new Aria2RPC),
      m_trayIcon(new TrayIcon(this)),
      m_refreshTimer(new QTimer(this)),
      m_statusLabel(new QLabel)
{
    QWidget *centralWidget = new QWidget;
    QHBoxLayout *centralLayout = new QHBoxLayout(centralWidget);
    QVBoxLayout *taskLayout = new QVBoxLayout;

    titlebar()->setCustomWidget(m_toolBar, Qt::AlignVCenter, false);
    titlebar()->setSeparatorVisible(true);
    titlebar()->setFixedHeight(45);

    // init toolbar attribute.
    m_toolBar->setStartButtonEnabled(false);
    m_toolBar->setPauseButtonEnabled(false);
    m_toolBar->setDeleteButtonEnabled(false);

    // init bottom label attribute.
    m_statusLabel->setStyleSheet("QLabel { color: #797979; font-size: 15px; }");
    setStatusText(0, 0);

    // m_trayIcon->show();
    m_refreshTimer->setInterval(500);

    taskLayout->addWidget(m_tableView);
    taskLayout->addSpacing(5);
    taskLayout->addWidget(m_statusLabel, 0, Qt::AlignHCenter);
    taskLayout->addSpacing(5);

    centralLayout->addWidget(m_slideBar);
    centralLayout->addLayout(taskLayout);
    centralLayout->setSpacing(0);
    centralLayout->setMargin(0);

    setCentralWidget(centralWidget);
    setWindowIcon(QIcon(":/images/deepin-downloader.svg"));

    startAria2c();
    setMinimumSize(940, 590);
    resize(940, 590);

    setStyleSheet(Utils::getQssContent(":/qss/style.qss"));
    setFocusPolicy(Qt::ClickFocus);

    connect(m_toolBar, &ToolBar::newTaskBtnClicked, this, &MainWindow::onNewTaskBtnClicked);
    connect(m_toolBar, &ToolBar::startBtnClicked, this, &MainWindow::onStartBtnClicked);
    connect(m_toolBar, &ToolBar::pauseBtnClicked, this, &MainWindow::onPauseBtnClicked);
    connect(m_toolBar, &ToolBar::deleteBtnClicked, this, &MainWindow::onDeleteBtnClicked);

    connect(m_aria2RPC, &Aria2RPC::addedTask, this, &MainWindow::handleAddedTask);
    connect(m_aria2RPC, &Aria2RPC::updateStatus, this, &MainWindow::handleUpdateStatus);
    connect(m_refreshTimer, &QTimer::timeout, this, &MainWindow::refreshEvent);

    connect(m_tableView, &QTableView::clicked, this, &MainWindow::updateToolBarStatus);

    connect(m_trayIcon, &TrayIcon::openActionTriggered, this, &MainWindow::activeWindow);
    connect(m_trayIcon, &TrayIcon::exitActionTriggered, qApp, &QApplication::quit);

    // test for tableview.
    // for (int i = 1; i < 10; ++i) {
    //     GlobalStruct *data = new GlobalStruct;
    //     data->gid = QString("r%1").arg(i);
    //     data->status = Global::Status::Active;
    //     m_tableView->tableModel()->append(data);
    // }
}

MainWindow::~MainWindow()
{
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    if (!m_trayIcon->isVisible()) {
        // sometimes aria2c not quit.
        QProcess::startDetached("killall aria2c");
        e->accept();
    } else {
        setVisible(false);
        e->ignore();
    }
}

void MainWindow::startAria2c()
{
    QProcess *process = new QProcess(this);

    // first killed aria2c.
    process->start("killall aria2c");
    process->waitForFinished(-1);

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

void MainWindow::setStatusText(const int &total, const int &processing)
{
    QString text;
    text.append(QString("total %1 task(s)").arg(total));
    text.append(" , ");
    text.append(QString("%1 task is processing").arg(processing));

    m_statusLabel->setText(text);
}

void MainWindow::activeWindow()
{
    setVisible(!isVisible());

    if (isVisible()) {
        activateWindow();
    }
}

void MainWindow::onNewTaskBtnClicked()
{
    NewTaskDialog *dlg = new NewTaskDialog;
    connect(dlg, &NewTaskDialog::startDownload, this, &MainWindow::handleDialogAddTask);
    dlg->exec();
}

void MainWindow::onStartBtnClicked()
{
    const QModelIndexList selected = m_tableView->selectionModel()->selectedRows();

    for (const QModelIndex &index : selected) {
        const QString gid = index.data(TableModel::GID).toString();
        const int status = index.data(TableModel::Status).toInt();

        if (status != Global::Status::Active) {
            m_aria2RPC->unpause(gid);
        }
    }
}

void MainWindow::onPauseBtnClicked()
{
    const QModelIndexList selected = m_tableView->selectionModel()->selectedRows();

    for (const QModelIndex &index : selected) {
        const QString gid = index.data(TableModel::GID).toString();
        const int status = index.data(TableModel::Status).toInt();

        if (status != Global::Status::Paused) {
            m_aria2RPC->pause(gid);
        }
    }
}

void MainWindow::onDeleteBtnClicked()
{
    const QModelIndexList selected = m_tableView->selectionModel()->selectedRows();
    QList<GlobalStruct *> deleteList;

    for (const QModelIndex &index : selected) {
        const QString gid = index.data(TableModel::GID).toString();
        const int status = index.data(TableModel::Status).toInt();

        if (status != Global::Status::Removed) {
            GlobalStruct *data = m_tableView->tableModel()->find(gid);
            deleteList << data;
        }
    }

    for (int i = 0; i < deleteList.size(); ++i) {
        GlobalStruct *data = deleteList.at(i);
        m_aria2RPC->remove(data->gid);
        m_tableView->tableModel()->removeItem(data);
    }
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

    m_tableView->tableModel()->append(data);
}

void MainWindow::handleUpdateStatus(const QString &fileName, const QString &gid, const int &status, const long long &totalLength,
                                    const long long &completedLength, const long long &speed, const int &percent)
{
    GlobalStruct *data = m_tableView->tableModel()->find(gid);

    if (data == nullptr) return;

    data->totalLength = Utils::formatUnit(totalLength);
    data->completedLength = Utils::formatUnit(completedLength);
    data->speed = (speed != 0) ? Utils::formatSpeed(speed) : "";
    data->fileName = fileName;
    data->status = status;
    data->percent = percent;    

    if (totalLength == completedLength || totalLength == 0 || data->status == Global::Status::Paused) {
        data->time = "";
    } else {
        QTime t(0, 0, 0);
        t = t.addSecs((totalLength - completedLength) / speed);
        data->time = t.toString("mm:ss");
    }

    m_tableView->update();
}

void MainWindow::updateToolBarStatus(const QModelIndex &index)
{
    const int status = index.data(TableModel::Status).toInt();

    switch (status) {
    case Status::Active:
        m_toolBar->setStartButtonEnabled(false);
        m_toolBar->setPauseButtonEnabled(true);
        m_toolBar->setDeleteButtonEnabled(true);
        break;
    case Status::Waiting:
        m_toolBar->setStartButtonEnabled(true);
        m_toolBar->setPauseButtonEnabled(false);
        m_toolBar->setDeleteButtonEnabled(true);
        break;
    case Status::Paused:
        m_toolBar->setStartButtonEnabled(true);
        m_toolBar->setPauseButtonEnabled(false);
        m_toolBar->setDeleteButtonEnabled(true);
        break;
    case Status::Error:
        m_toolBar->setStartButtonEnabled(true);
        m_toolBar->setPauseButtonEnabled(false);
        m_toolBar->setDeleteButtonEnabled(true);
        break;
    case Status::Complete:
        m_toolBar->setStartButtonEnabled(false);
        m_toolBar->setPauseButtonEnabled(false);
        m_toolBar->setDeleteButtonEnabled(true);
        break;
    case Status::Removed:
        m_toolBar->setStartButtonEnabled(false);
        m_toolBar->setPauseButtonEnabled(false);
        m_toolBar->setDeleteButtonEnabled(false);
        break;
    }
}

void MainWindow::refreshEvent()
{
    QList<GlobalStruct *> *dataList = m_tableView->tableModel()->dataList();
    int active = 0;

    for (auto *item : *dataList) {
        m_aria2RPC->tellStatus(item->gid);

        if (item->status == Global::Status::Active) {
            ++active;
        }
    }

    if (dataList->isEmpty()) {
        m_refreshTimer->stop();
    }

    setStatusText(dataList->count(), active);
}
