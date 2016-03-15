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
        if (reply->error() == QNetworkReply::NoError) {
            QImage image;
            image.loadFromData(reply->readAll());
            if (!image.isNull()) {
                this->setPixmap(QPixmap::fromImage(image).scaled(this->size()));
            } else {
                qDebug() << "is null, url:" << url;
            }
        } else {
            qDebug() << "error:" << reply->error() << ", url:" << url;
        }
        reply->deleteLater();
        net->deleteLater();
    });
}
