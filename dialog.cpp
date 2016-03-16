#include "dialog.h"
#include "ui_dialog.h"
#include "articleitemwidget.h"
#include "systemtray.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    DropWidget(parent),
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
    ui->labelTitle->setProperty("qssname", "article_title");

    m_tray = new SystemTray(this);
    connect(m_tray, &SystemTray::activated, [this] (QSystemTrayIcon::ActivationReason reason) {
        if (QSystemTrayIcon::Trigger == reason) {
            if (this->isVisible()) {
                hide();
            } else {
                show();
            }
        }
    });
    connect(m_tray, &SystemTray::sigShow, [this] { show(); });
    connect(m_tray, &SystemTray::sigExit, [this] { qApp->quit(); });
    m_tray->show();

    ui->labelTitle->setText(tr("weixin article"));
    ui->pbReturn->setIcon(QIcon(":/return"));
    ui->pbSetting->setIcon(QIcon(":/setting"));

    this->setBackground(QImage(":/background"));
    this->installEventFilter(this);
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

bool Dialog::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyRelease) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Escape) {
            this->hide();
        }
    }
    return false;
}
