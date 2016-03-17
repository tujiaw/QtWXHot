#include "httpimagelabel.h"
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>

HttpImageLabel::HttpImageLabel(QWidget *parent) : QLabel(parent)
{
}

void HttpImageLabel::setHttpImage(const QString &url)
{
    QNetworkAccessManager *net = new QNetworkAccessManager();
    QNetworkReply *reply = net->get(QNetworkRequest(QUrl(url)));
    connect(reply, &QNetworkReply::finished, [reply, net, url, this] {
        bool useDefault = false;
        if (reply->error() == QNetworkReply::NoError) {
            QImage image;
            image.loadFromData(reply->readAll());
            if (!image.isNull()) {
                this->setPixmap(QPixmap::fromImage(image).scaled(this->size()));
            } else {
                useDefault = true;
                qDebug() << "is null, url:" << url;
            }
        } else {
            useDefault = true;
            qDebug() << "error:" << reply->error() << ", url:" << url;
        }

        if (useDefault) {
            this->setPixmap(QPixmap(":/default_item").scaled(this->size()));
        }
        reply->deleteLater();
        net->deleteLater();
    });
}
