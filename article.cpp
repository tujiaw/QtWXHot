#include "article.h"
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include "json.h"

static const QByteArray APIKEY = "7de1f6e062332074a6e0fd03379714cd";
static const QString BASE_URL = "http://apis.baidu.com/txapi/weixin/wxhot";

ArticleNet::ArticleNet(QObject *parent)
    : QObject(parent)
{
    m_net = new QNetworkAccessManager(this);
}

void ArticleNet::request(const ArticleRequest &data)
{
    QUrl url(getUrl(data));
    QNetworkRequest request(url);
    request.setRawHeader("apikey", APIKEY);
    QNetworkReply *reply = m_net->get(request);
    connect(reply, &QNetworkReply::finished, [reply, this] {
       if (reply->error() == QNetworkReply::NoError) {
           QByteArray allData = reply->readAll();
           QVariantMap vm = json::toMap(allData);

           ArticleResult result;
           result.code = vm["code"].toInt();
           result.msg = vm["msg"].toString();
           QList<ArticleItem> newsList;
           QList<QVariant> newsValue = vm["newslist"].toList();
           for (int i=0; i<newsValue.size(); i++) {
               vm = newsValue[i].toMap();
               ArticleItem item;
               item.description = vm["description"].toString();
               item.picUrl = vm["picUrl"].toString();
               item.title = vm["title"].toString();
               item.url = vm["url"].toString();
               newsList.append(item);
           }
           result.newslist = newsList;
           emit sigResponse(result);
       }
    });
}

void ArticleNet::request(int num, const QString &word, int rand, int page)
{
    ArticleRequest arg;
    arg.apikey = APIKEY;
    arg.num = num;
    arg.page = page;
    arg.rand = rand;
    QByteArray arr = word.toLocal8Bit();
    arg.word = QString(arr.toPercentEncoding());
    qDebug() << "word:" << arg.word;
    request(arg);
}

QString ArticleNet::getUrl(const ArticleRequest &data)
{
    QString result;
    result += BASE_URL + "?";
    result += QString("num=%1").arg(data.num) + "&";
    result += QString("rand=%1").arg(data.rand) + "&";
    if (!data.word.isEmpty()) {
        result += QString("word=%1").arg(data.word) + "&";
    }
    result += QString("page=%1").arg(data.page);
    qDebug() << "url:" << result;
    return result;
}
