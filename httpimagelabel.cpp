#include "httpimagelabel.h"
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>

HttpImageLabel::HttpImageLabel(QWidget *parent) : QLabel(parent)
{
}

void HttpImageLabel::setHttpImage(const QString &url)
{
    QNetworkAccessManager *net = new QNetworkAccessManager();
    QNetworkReply *reply = net->get(QNetworkRequest(QUrl(url)));
    connect(reply, &QNetworkReply::finished, [reply, net, this] {
        if (reply->error() == QNetworkReply::NoError) {
            QImage image;
            image.loadFromData(reply->readAll());
            if (!image.isNull()) {
                this->setPixmap(QPixmap::fromImage(image).scaled(this->size()));
            }
        }
        reply->deleteLater();
        net->deleteLater();
    });
}
