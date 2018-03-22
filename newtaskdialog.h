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

#ifndef NEWTASKDIALOG_H
#define NEWTASKDIALOG_H

#include "ddialog.h"
#include <QPlainTextEdit>
#include <QComboBox>

DWIDGET_USE_NAMESPACE

class NewTaskDialog : public DDialog
{
    Q_OBJECT

public:
    NewTaskDialog(QWidget *parent = nullptr);
    ~NewTaskDialog();

private slots:
    void handleButtonClicked(const int &index, const QString &text);

private:
    QPlainTextEdit *m_textEdit;
    QComboBox *m_comboBox;
};

#endif
