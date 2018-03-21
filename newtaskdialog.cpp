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

#include "newtaskdialog.h"
#include <QHBoxLayout>
#include <QPushButton>

NewTaskDialog::NewTaskDialog(QWidget *parent)
    : DDialog(parent)
{
    // setTitle(tr("New task"));

    QWidget *centralWidget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    m_textEdit = new QPlainTextEdit;
    m_textEdit->setStyleSheet("QPlainTextEdit { border: 1px solid #f3f3f3; }");
    m_textEdit->setFixedHeight(155);

    QPushButton *openFileBtn = new QPushButton(QIcon(":/images/torrent.svg"),
                                               tr("Open torrent file"));

    layout->addSpacing(15);
    layout->addWidget(m_textEdit);
    layout->addWidget(openFileBtn);
    layout->addStretch();
    layout->setMargin(0);

    addContent(centralWidget);
    addButton(tr("Cancel"));
    addButton(tr("Downlload"));
    setContentLayoutContentsMargins(QMargins(10, 10, 10, 10));
}

NewTaskDialog::~NewTaskDialog()
{
}
