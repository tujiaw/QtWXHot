#include "articleitemwidget.h"
#include "httpimagelabel.h"
#include <QtWidgets>

ArticleItemWidget::ArticleItemWidget(QWidget *parent) : QWidget(parent)
{
    m_image = new HttpImageLabel(this);
    m_image->setFixedSize(50, 50);
    m_desc = new QLabel(this);
    m_title = new QLabel(this);

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);
    vLayout->addWidget(m_desc);
    vLayout->addWidget(m_title);

    QHBoxLayout *mLayout = new QHBoxLayout(this);
    mLayout->setContentsMargins(0, 0, 0, 0);
    mLayout->setSpacing(10);
    mLayout->addWidget(m_image);
    mLayout->addLayout(vLayout);
}

void ArticleItemWidget::setData(const ArticleItem &item)
{
    m_data = item;
    m_image->setHttpImage(item.picUrl);
    m_desc->setText(item.description);
    m_title->setText(item.title);
}

const ArticleItem& ArticleItemWidget::getData() const
{
    return m_data;
}
