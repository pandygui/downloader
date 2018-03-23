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

#include "itemdelegate.h"
#include "tablemodel.h"
#include "tableview.h"
#include <QStandardItemModel>
#include <QPainter>
#include <QDebug>

ItemDelegate::ItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

ItemDelegate::~ItemDelegate()
{
}

void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::black);

    const QRect rect = option.rect;

    if (option.state & QStyle::State_Selected) {
        painter->setPen(Qt::black);
        painter->fillRect(rect, QColor("#D5EDFE"));
    }

    switch (index.column()) {
    case TableModel::FileName:
        painter->drawText(QRect(rect).marginsRemoved(QMargins(10, 0, 0, 0)), Qt::AlignVCenter | Qt::AlignLeft, index.data(TableModel::FileName).toString());
        break;
    case TableModel::Size:
        painter->drawText(rect, Qt::AlignCenter, index.data(TableModel::Size).toString());
        break;
    case TableModel::Speed:
        painter->drawText(rect, Qt::AlignCenter, index.data(TableModel::Speed).toString());
        break;
    case TableModel::Percent:
        painter->drawText(rect, Qt::AlignCenter, QString("%1%").arg(index.data(TableModel::Percent).toInt()));
        break;
    case TableModel::Status:
        painter->drawText(QRect(rect).marginsRemoved(QMargins(0, 0, 10, 0)), Qt::AlignCenter, index.data(TableModel::Status).toString());
        break;
    }
}

QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(-1, 50);
}
