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

#include "tablemodel.h"

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

TableModel::~TableModel()
{
}

DataItem * TableModel::find(const QString &gid)
{
    if (m_map.contains(gid)) {
        return m_map.value(gid);
    }

    return nullptr;
}

void TableModel::append(DataItem *data)
{
    int row = m_dataList.size();

    beginInsertRows(QModelIndex(), row, row);
    m_dataList.append(data);
    m_map.insert(data->gid, data);
    endInsertRows();
}

void TableModel::removeItem(DataItem *data)
{
    if (m_map.contains(data->gid)) {
        beginRemoveRows(QModelIndex(), m_dataList.indexOf(data), m_dataList.indexOf(data));
        m_map.remove(data->gid);
        m_dataList.removeOne(data);
        delete data;
        endRemoveRows();
    }
}

void TableModel::removeItems()
{
    beginRemoveRows(QModelIndex(), 0, m_dataList.size());
    qDeleteAll(m_dataList.begin(), m_dataList.end());
    m_dataList.clear();
    m_map.clear();
    endRemoveRows();
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_dataList.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 5;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    const DataItem *data = m_dataList.at(row);
    const QChar sizeSepChar = (!data->totalLength.isEmpty()) ? '/' : ' ';

    switch (role) {
    case TableModel::FileName:
        return data->fileName;
    case TableModel::Size:
        return QString("%1%2%3  %4").arg(data->completedLength).arg(sizeSepChar).arg(data->totalLength).arg(data->percent);
    case TableModel::Speed:
        return (data->status != Global::Status::Paused) ? data->speed : "";
    case TableModel::Time:
        return data->time;
    case TableModel::Status:
        return data->status;
    case TableModel::GID:
        return data->gid;
    case TableModel::Percent:
        return data->percent;
    case TableModel::TotalLength:
        return data->total;
    }

    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation != Qt::Horizontal) {
        return QVariant();
    }

    switch (section) {
    case 0:
        return tr("File name");
    case 1:
        return tr("Size and progress");
    case 2:
        return tr("Speed");
    case 3:
        return tr("Remaining time");
    case 4:
        return tr("Status");
    }

    return QVariant();
}
