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
    painter->setPen(QColor("#303030"));

    const QRect rect = option.rect;
    const int column = index.column();
    const QString text = index.data(column).toString();

    // painting selection item background.
    if (option.state & QStyle::State_Selected) {
        painter->fillRect(rect, QColor("#D5EDFE"));
    }

    // painting each column item.
    if (column == TableModel::FileName) {
        const QRect nameRect = QRect(rect).marginsRemoved(QMargins(10, 0, 0, 0));
        const QString name = painter->fontMetrics().elidedText(text, Qt::ElideLeft, rect.width() - 10);
        painter->drawText(nameRect, Qt::AlignVCenter | Qt::AlignLeft, name);
    } else if (column == TableModel::Size) {
        painter->drawText(rect, Qt::AlignVCenter | Qt::AlignLeft, text);
    } else if (column == TableModel::Speed) {
        painter->drawText(rect, Qt::AlignVCenter | Qt::AlignLeft, text);
    } else if (column == TableModel::Time) {
        painter->drawText(rect, Qt::AlignVCenter | Qt::AlignLeft, text);
    } else if (column == TableModel::Status) {
        QRect statusRect = QRect(rect).marginsRemoved(QMargins(0, 0, 10, 0));
        painter->drawText(statusRect, Qt::AlignVCenter | Qt::AlignLeft, text);
    }
}

QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // don't work here.
    return QSize(-1, 50);
}
