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

#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include "global.h"

using namespace Global;

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:

    enum Column {
        FileName = 0, Size, Speed, Time, Status
    };

    TableModel(QObject *parent = nullptr);
    ~TableModel();

    void append(GlobalStruct *data);
    void removeItem(GlobalStruct *data);
    void removeItems();
    GlobalStruct *find(const QString &gid);
    QList<GlobalStruct *> *dataList() { return m_dataList; };

protected:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    QList<GlobalStruct *> *m_dataList;
    QMap<QString, GlobalStruct *> m_map;
};

#endif
