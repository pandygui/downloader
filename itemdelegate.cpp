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
    const QRect rect(option.rect);
    const int column(index.column());
    const QString text(index.data(column).toString());
    const bool isSelected = option.state & QStyle::State_Selected;

    QFont font;
    font.setPointSize(11);
    painter->setFont(font);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QColor("#303030"));

    // painting selection item background.
    if (isSelected) {
        painter->setPen(Qt::white);
        painter->fillRect(rect, QColor("#2CA7F8"));
    }

    const QRect textRect = rect.marginsRemoved(QMargins(10, 0, 0, 0));

    // painting each column item.
    if (column == TableModel::FileName) {
        const QString name = painter->fontMetrics().elidedText(text, Qt::ElideLeft, textRect.width() - 10);
        painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, name);
    } else if (column == TableModel::Size) {
        painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, text);
    } else if (column == TableModel::Speed) {
        painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, text);
    } else if (column == TableModel::Time) {
        painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, text);
    } else if (column == TableModel::Status) {
        if (!isSelected) {
            painter->setPen(QColor("#95CF52"));
        }
        
        painter->drawText(rect.marginsRemoved(QMargins(10, 0, 10, 0)), Qt::AlignVCenter | Qt::AlignLeft, text);
    }
}

QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // don't work here.
    return QSize(-1, 50);
}
