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
#include "global.h"

#include <QStandardItemModel>
#include <QPainter>
#include <QDebug>

using namespace Global;

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
    const QVariant data(index.data(column));
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
        const QString name = painter->fontMetrics().elidedText(data.toString(), Qt::ElideLeft, textRect.width() - 10);
        painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, name);
    } else if (column == TableModel::Size) {
        painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, data.toString());
    } else if (column == TableModel::Speed) {
        painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, data.toString());
    } else if (column == TableModel::Time) {
        painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, data.toString());
    } else if (column == TableModel::Status) {
        QString statusText = "";
        switch (data.toInt()) {
        case Global::Status::Active:
            statusText = Global::ACTIVE;
            break;
        case Global::Status::Waiting:
            statusText = Global::WAITING;
            break;
        case Global::Status::Paused:
            statusText = Global::PAUSED;
            break;
        case Global::Status::Error:
            statusText = Global::ERROR;
            break;
        case Global::Status::Complete:
            statusText = Global::COMPLETE;
            break;
        case Global::Status::Removed:
            statusText = Global::REMOVED;
            break;
        }

        statusText = painter->fontMetrics().elidedText(statusText, Qt::ElideRight, textRect.width() - 10);

        // if (!isSelected) {
        //     painter->setPen(QColor("#95CF52"));
        // }

        painter->drawText(rect.marginsRemoved(QMargins(10, 0, 10, 0)), Qt::AlignVCenter | Qt::AlignLeft, statusText);
    }
}

QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // don't work here.
    return QSize(-1, 50);
}
