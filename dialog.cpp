#include "dialog.h"
#include "ui_dialog.h"
#include "articleitemwidget.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    m_articleNet = new ArticleNet(this);
    connect(m_articleNet, &ArticleNet::sigResponse, this, &Dialog::slotUpdateArticleList);
    m_articleNet->request(10, QStringLiteral(""));
    ui->stackedWidget->setCurrentIndex(0);

    connect(ui->pbReturn, &QPushButton::clicked, this, &Dialog::slotReturn);
    connect(ui->listWidget, &QListWidget::itemClicked, this, &Dialog::slotListWidgetItemClicked);

    ui->pbReturn->setVisible(false);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::slotReturn()
{
    ui->pbReturn->setVisible(false);
    ui->stackedWidget->setCurrentIndex(0);
}

void Dialog::slotUpdateArticleList(const ArticleResult &data)
{
    ui->listWidget->clear();

    for (int i=0, count=data.newslist.size(); i<count; i++) {
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        item->setSizeHint(QSize(this->width(), 60));
        ArticleItemWidget *widget = new ArticleItemWidget(ui->listWidget);
        widget->setData(data.newslist.at(i));
        qDebug() << data.newslist.at(i).title;
        ui->listWidget->setItemWidget(item, widget);
    }
}

void Dialog::slotListWidgetItemClicked(QListWidgetItem *item)
{
    ArticleItemWidget *itemWidget = static_cast<ArticleItemWidget*>(ui->listWidget->itemWidget(item));
    if (!itemWidget) {
        return;
    }

    ui->pbReturn->setVisible(true);

    ui->labelTitle->setText(itemWidget->getData().description);
    QUrl url(itemWidget->getData().url);
    if (ui->webView->url() != url) {
        ui->webView->load(url);
    }
    ui->stackedWidget->setCurrentIndex(1);
}
