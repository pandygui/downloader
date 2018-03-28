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
#include <QStyleOptionViewItem>
#include <QStyleOptionProgressBar>
#include <QProgressBar>
#include <QApplication>
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
    const bool isSelected = option.state & QStyle::State_Selected;

    QFont font;
    font.setPointSize(11);
    painter->setFont(font);

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QColor("#303030"));

    // painting selection item background.
    if (isSelected) {
        painter->fillRect(rect, QColor("#D5EDFE"));
    }

    const QRect textRect = rect.marginsRemoved(QMargins(10, 0, 0, 0));

    // painting each column item.
    if (column == 0) {

        const QString name = painter->fontMetrics().elidedText(index.data(TableModel::FileName).toString(), Qt::ElideLeft, textRect.width() - 10);
        painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, name);

    } else if (column == 1) {
        
        if (index.data(TableModel::TotalLength) == 0) {
            return;
        }

        QRect sizeRect = textRect;
        sizeRect.setHeight(sizeRect.height() / 1.8);

        QRect barRect = sizeRect;
        barRect.setTop(sizeRect.bottom() + 7);
        barRect.setWidth(barRect.width() - 10);
        barRect.setHeight(6);

        QStyleOptionViewItem viewOption(option);
        initStyleOption(&viewOption, index);

        QStyleOptionProgressBar *optionBar = new QStyleOptionProgressBar;
        optionBar->initFrom(option.widget);
        optionBar->rect = barRect;
        optionBar->minimum = 0;
        optionBar->maximum = 100;
        optionBar->progress = index.data(TableModel::Percent).toInt();

        QProgressBar *progressbar = new QProgressBar;
        progressbar->setStyleSheet("background-color: rgba(0, 0, 0, 0.05);");
        QApplication::style()->drawControl(QStyle::CE_ProgressBarContents, optionBar, painter, progressbar);

        const QString sizeText = painter->fontMetrics().elidedText(index.data(TableModel::Size).toString() + "%", Qt::ElideRight, textRect.width() - 10);
        painter->drawText(sizeRect, Qt::AlignBottom | Qt::AlignLeft, sizeText);

    } else if (column == 2) {

        const QString speed = index.data(TableModel::Speed).toString();
        painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, speed);

    } else if (column == TableModel::Time) {

        const QString time = index.data(TableModel::Time).toString();
        painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, time);

    } else if (column == 3) {

        QString statusText = "";
        switch (index.data(TableModel::Status).toInt()) {
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
    Q_UNUSED(option);
    Q_UNUSED(index);

    // don't work here.
    return QSize(-1, 50);
}
