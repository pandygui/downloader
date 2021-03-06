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

    enum DataRole {
        FileName = 0, Size, Speed, Time, Status, GID, Percent, TotalLength
    };

    enum Mode {
        AllTasks = 0, Downloading, Paused, Finished
    };

    TableModel(QObject *parent = nullptr);
    ~TableModel();

    void append(DataItem *data);
    void removeItem(DataItem *data);
    void removeItems();
    void switchAllTasksMode();
    void switchDownloadingMode();
    void switchPausedMode();
    void switchFinishedMode();
    DataItem *find(const QString &gid);
    const QList<DataItem *> dataList() { return m_dataList; };
    const QList<DataItem *> renderList() { return m_renderList; }

protected:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    QList<DataItem *> m_dataList;
    QList<DataItem *> m_renderList;
    QMap<QString, DataItem *> m_map;
    Mode m_mode;
};

#endif
