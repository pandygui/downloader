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

#include "tableview.h"
#include <QHeaderView>
#include <QStandardItem>

TableView::TableView(QWidget *parent)
    : QTableView(parent),
      m_itemModel(new QStandardItemModel)
{
    setModel(m_itemModel);

    QStringList headerTitles;
    headerTitles << tr("File name") << tr("Size") << tr("Speed")
                 << tr("Remaining time") << tr("Status");

    m_itemModel->setHorizontalHeaderLabels(headerTitles);

    setShowGrid(false);
    setAlternatingRowColors(true);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

    QHeaderView *headerView = horizontalHeader();
    headerView->setSectionResizeMode(1, QHeaderView::Stretch);
    headerView->setSectionResizeMode(2, QHeaderView::Stretch);
    headerView->setSectionResizeMode(3, QHeaderView::Fixed);
    headerView->setSectionResizeMode(4, QHeaderView::Stretch);
    headerView->setHighlightSections(false);

    setColumnWidth(0, 300);
    setColumnWidth(1, 100);
    setColumnWidth(2, 100);
    setColumnWidth(3, 160);
    setColumnWidth(4, 100);

    for (int i = 0; i < 100; ++i) {
        appendItem("hhhhh" + QString::number(i));
    }
}

TableView::~TableView()
{
}

void TableView::appendItem(const QString &name)
{
    int row = m_itemModel->rowCount();
    m_itemModel->insertRow(row);

    QStandardItem *listItem = new QStandardItem(name);
    m_itemModel->setItem(row, 0, listItem);
    setRowHeight(row, 45);
}
