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

#include "aria2rpc.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>
#include <QDebug>

Aria2RPC::Aria2RPC(QObject *parent)
    : QObject(parent)
{

}

void Aria2RPC::addUri(const QString &uri, const QString &id)
{
    QJsonArray array;
    QJsonArray item;

    item.append(uri);
    array.append(item);

    sendMessage("aria2.addUri", id, array);
}

void Aria2RPC::remove(const QString &gid)
{
    qDebug() << "remove: " << gid;

    QJsonArray params;

    if (gid != "0") {
        params.append(gid);
    }

    params.append(gid);
    sendMessage("aria2.remove", gid, params);
}

void Aria2RPC::pause(const QString &gid)
{
    QJsonArray params;
    params.append(gid);
    sendMessage("aria2.pause", gid, params);
}

void Aria2RPC::tellStatus(const QString &gid)
{
    QJsonArray params;
    params.append(gid);
    sendMessage("aria2.tellStatus", gid, params);
}

void Aria2RPC::sendMessage(const QString &method, const QString &id, QJsonArray params)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager;

    QJsonObject object;
    object.insert("jsonrpc", "2.0");
    object.insert("id", id);
    object.insert("method", method);

    if (!params.isEmpty()) {
        object.insert("params", params);
    }

    QNetworkRequest *request = new QNetworkRequest;
    request->setUrl(QUrl("http://localhost:7200/jsonrpc"));
    request->setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->post(*request, QJsonDocument(object).toJson());

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray buffer = reply->readAll();
        qDebug() << "success: " << buffer;
    } else {
        qDebug() << "error: " << reply->errorString();
    }

    manager->deleteLater();
}
