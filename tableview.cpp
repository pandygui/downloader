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
#include "itemdelegate.h"

#include <QHeaderView>
#include <QStandardItem>
#include <QScrollBar>
#include <QDebug>

TableView::TableView(QWidget *parent)
    : QTableView(parent),
      m_model(new TableModel)
{
    setModel(m_model);
    setItemDelegate(new ItemDelegate);

    QHeaderView *headerView = horizontalHeader();
    verticalHeader()->setDefaultSectionSize(50);
    headerView->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    headerView->setSectionResizeMode(0, QHeaderView::Stretch);
    headerView->setSectionResizeMode(1, QHeaderView::Fixed);
    headerView->setSectionResizeMode(2, QHeaderView::Fixed);
    headerView->setSectionResizeMode(3, QHeaderView::Fixed);
    headerView->setSectionResizeMode(4, QHeaderView::Fixed);
    headerView->setHighlightSections(false);

    // set row height.
    QHeaderView *vheaderView = verticalHeader();
    vheaderView->setDefaultSectionSize(65);

    setColumnWidth(0, 300);
    setColumnWidth(1, 170);
    setColumnWidth(2, 120);
    setColumnWidth(3, 100);
    setColumnWidth(4, 130);

    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    setAlternatingRowColors(true);
    setSortingEnabled(true);
    setShowGrid(false);

    resizeColumnsToContents();
}

TableView::~TableView()
{
}

void TableView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    QTableView::selectionChanged(selected, deselected);

    if (!model())
        return;

    Q_EMIT selectionItemChanged();
}
