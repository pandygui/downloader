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

#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>
#include <QItemSelection>
#include <QStandardItemModel>

#include "tablemodel.h"
#include "global.h"

class TableView : public QTableView
{
    Q_OBJECT

public:
    TableView(QWidget *parent = nullptr);
    ~TableView();

    TableModel *tableModel() { return m_model; };

protected:
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

private:
    TableModel *m_model;
};

#endif
