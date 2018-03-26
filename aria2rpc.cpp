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
#include "global.h"
#include "utils.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
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

void Aria2RPC::tellActive()
{
    QJsonArray params;
    params.append(0);
    params.append(100);
    sendMessage("aria2.tellActive", 0, params);
}

void Aria2RPC::tellWaiting()
{
    QJsonArray params;
    params.append(0);
    params.append(100);
    sendMessage("aria2.tellWaiting", 0, params);
}

void Aria2RPC::tellStopped()
{
    QJsonArray params;
    params.append(0);
    params.append(100);
    sendMessage("aria2.tellStopped", 0, params);
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
    manager->post(*request, QJsonDocument(object).toJson());

    connect(manager, &QNetworkAccessManager::finished, this,
            [=] (QNetworkReply *reply) {
                handleNetworkReply(reply, method);
                manager->deleteLater();
                manager->destroyed();
            });
}

void Aria2RPC::handleNetworkReply(QNetworkReply *reply, const QString &method)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray buffer = reply->readAll();
        QJsonDocument document = QJsonDocument::fromJson(buffer);
        QJsonObject object = document.object();

        if (!object.isEmpty()) {
            if (method == "aria2.tellStatus") {
                handleTellStatus(object);
            } else {
                Q_EMIT addedTask(object.value("result").toString());
            }
        }
    } else {
        qDebug() << "error: " << reply->errorString();
    }
}

void Aria2RPC::handleTellStatus(const QJsonObject &object)
{
    QJsonObject result = object.value("result").toObject();
    QJsonArray files = result.value("files").toArray();

    for (int i = 0; i < files.size(); ++i) {
        QJsonObject file = files[i].toObject();
    }

    // qDebug() << "gid" << result.value("gid").toString();
    // qDebug() << "speed: " << result.value("downloadSpeed").toString();
    // qDebug() << "status: " << result.value("status").toString();
    // qDebug() << "total length: " << result.value("totalLength").toString();
    // qDebug() << "completed length: " << result.value("completedLength").toString();
    // qDebug() << result.value("completedLength").toString().toLong() * 100 / result.value("totalLength").toString().toLong();
    // qDebug() << "\n";

    const long speedSize = result.value("downloadSpeed").toString().toLong();

    const QString gid = result.value("gid").toString();
    const QString statusStr = result.value("status").toString();
    const QString totalLength = result.value("totalLength").toString();
    const QString completedLength = result.value("completedLength").toString();
    const QString percent = QString::number(completedLength.toLong() * 100 / totalLength.toLong()) + "%";

    QString speed = "";
    int status = 0;

    if (speedSize != 0) {
        speed = Utils::formatSpeed(speedSize);
    }

    if (statusStr == "active") {
        status = Global::Status::Active;
    } else if (statusStr == "waiting") {
        status = Global::Status::Waiting;
    } else if (statusStr == "paused") {
        status = Global::Status::Paused;
    } else if (statusStr == "error") {
        status = Global::Status::Error;
    } else if (statusStr == "complete") {
        status = Global::Status::Complete;
    } else if (statusStr == "removed") {
        status = Global::Status::Removed;
    }

    Q_EMIT updateStatus(gid, status, Utils::formatUnit(totalLength.toLong()), Utils::formatUnit(completedLength.toLong()), speed, percent);
}
