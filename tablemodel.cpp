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
    m_dataList = new QList<GlobalStruct *>;
}

TableModel::~TableModel()
{
    qDeleteAll(m_dataList->begin(), m_dataList->end());
}

GlobalStruct * TableModel::find(const QString &gid)
{
    if (m_map.contains(gid)) {
        return m_map[gid];
    }

    return nullptr;
}

void TableModel::append(GlobalStruct *data)
{
    int row = m_dataList->count();
    beginInsertRows(QModelIndex(), row, row);
    m_dataList->append(data);
    m_map.insert(data->gid, data);
    endInsertRows();
}

void TableModel::removeItem(GlobalStruct *data)
{
    if (m_map.contains(data->gid)) {
        m_map.remove(data->gid);
        m_dataList->removeOne(data);
        delete data;
    }
}

void TableModel::removeItems()
{
    qDeleteAll(m_dataList->begin(), m_dataList->end());
    m_dataList->clear();
    m_map.clear();
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return m_dataList->count();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return Column::Status + 1;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    const int row = index.row();

    switch (role) {
    case TableModel::FileName:
        return QVariant(m_dataList->at(row)->gid);
    case TableModel::Size:
            return QVariant(m_dataList->at(row)->totalLength);
    case TableModel::Speed:
        return QVariant(m_dataList->at(row)->speed);
    case TableModel::Percent:
        return QVariant(m_dataList->at(row)->percent);
    case TableModel::Status:
        return QVariant(m_dataList->at(row)->status);
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
        return tr("Size");
    case 2:
        return tr("Speed");
    case 3:
        return tr("Percent");
    case 4:
        return tr("Status");
    }

    return QVariant();
}
