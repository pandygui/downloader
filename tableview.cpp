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

TableView::TableView(QWidget *parent)
    : QTableView(parent),
      m_model(new TableModel)
{
    setModel(m_model);
    setItemDelegate(new ItemDelegate);

    QHeaderView *headerView = horizontalHeader();
    verticalHeader()->setDefaultSectionSize(50);
    headerView->setSectionResizeMode(0, QHeaderView::Stretch);
    headerView->setSectionResizeMode(1, QHeaderView::Fixed);
    headerView->setSectionResizeMode(2, QHeaderView::Fixed);
    headerView->setSectionResizeMode(3, QHeaderView::Stretch);
    headerView->setHighlightSections(false);

    setColumnWidth(0, 300);
    setColumnWidth(1, 100);
    setColumnWidth(2, 100);
    setColumnWidth(3, 160);
    setColumnWidth(4, 100);

    setShowGrid(false);
    setAlternatingRowColors(true);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
}

TableView::~TableView()
{
}
