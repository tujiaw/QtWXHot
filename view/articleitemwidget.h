#ifndef ARTICLEITEMWIDGET_H
#define ARTICLEITEMWIDGET_H

#include <QWidget>
#include "article.h"

class QLabel;
class HttpImageLabel;
class ArticleItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ArticleItemWidget(QWidget *parent = 0);
    void setData(const ArticleItem &item);
    const ArticleItem& getData() const;

private:
    HttpImageLabel *m_image;
    QLabel *m_desc;
    QLabel *m_title;
    ArticleItem m_data;
};

#endif // ARTICLEITEMWIDGET_H
