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
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>

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

    QFormLayout *posLayout = new QFormLayout;
    QLabel *tipsLabel = new QLabel(tr("Save to:"));
    tipsLabel->setStyleSheet("QLabel { color: #202020; }");

    m_comboBox = new QComboBox;
    m_comboBox->addItem(QIcon(":/images/folder-downloads.svg"),
                        tr("Download"), "");
    m_comboBox->addItem(QIcon(":/images/folder-desktop.svg"),
                        tr("Desktop"), "");
    m_comboBox->setFixedHeight(25);

    posLayout->addRow(tipsLabel, m_comboBox);
    posLayout->setHorizontalSpacing(10);

    layout->addSpacing(15);
    layout->addWidget(m_textEdit);
    layout->addSpacing(10);
    layout->addWidget(openFileBtn);
    layout->addSpacing(20);
    layout->addLayout(posLayout);
    layout->addSpacing(15);
    layout->addStretch();
    layout->setMargin(0);

    centralWidget->setFixedWidth(440);

    addContent(centralWidget);
    addButton(tr("Cancel"));
    addButton(tr("Downlload"));
    setContentLayoutContentsMargins(QMargins(20, 10, 20, 10));
}

NewTaskDialog::~NewTaskDialog()
{
}
