#ifndef ARTICLE_H
#define ARTICLE_H

#include <QString>
#include <QObject>

struct ArticleRequest {
    QString apikey;
    int num;
    int rand;
    QString word;
    int page;
};

struct ArticleItem {
    QString title;
    QString description;
    QString picUrl;
    QString url;
};

struct ArticleResult {
    int code;
    QString msg;
    QList<ArticleItem> newslist;
};

Q_DECLARE_OPAQUE_POINTER(ArticleResult)

class QNetworkAccessManager;
class ArticleNet : public QObject
{
    Q_OBJECT
public:
    ArticleNet(QObject *parent = 0);

    void request(const ArticleRequest &data);
    void request(int num, const QString &word, int rand = 1, int page = 1);
    static QString getUrl(const ArticleRequest &data);

signals:
    void sigResponse(const ArticleResult &data);

private:
    QNetworkAccessManager *m_net;
};

#endif // ARTICLE_H
