#include "dialog.h"
#include "ui_dialog.h"
#include "articleitemwidget.h"
#include "systemtray.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    DropWidget(parent),
    ui(new Ui::Dialog),
    m_fromIndex(0)
{
    ui->setupUi(this);
    m_articleNet = new ArticleNet(this);
    connect(m_articleNet, &ArticleNet::sigResponse, this, &Dialog::slotUpdateArticleList);
    ui->stackedWidget->setCurrentIndex(0);

    connect(ui->pbReturn, &QPushButton::clicked, this, &Dialog::slotReturn);
    connect(ui->pbSetting, &QPushButton::clicked, this, &Dialog::slotSetting);
    connect(ui->listWidget, &QListWidget::itemClicked, this, &Dialog::slotListWidgetItemClicked);
    connect(ui->stackedWidget, &QStackedWidget::currentChanged, this, &Dialog::slotStackedCurrentChanged);
    connect(ui->settingWidget, &SettingWidget::sigBackgroundLoad, this, &Dialog::slotBackgroundLoad);
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
    ui->pbReturn->setIcon(QIcon(":/return.png"));
    ui->pbSetting->setIcon(QIcon(":/setting.png"));

    this->installEventFilter(this);

    QImage background(ui->settingWidget->getBackgroundPath());
    if (background.isNull()) {
        background.load(":/background.png");
    }
    this->setBackground(background);
    m_articleNet->request(ui->settingWidget->getCount(), ui->settingWidget->getKeyword());
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::slotReturn()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Dialog::slotSetting()
{
    ui->stackedWidget->setCurrentIndex(2);
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
    ui->stackedWidget->setCurrentIndex(1);
}

void Dialog::slotStackedCurrentChanged(int index)
{
    qDebug() << "index:" << index;
    QString keyword = ui->settingWidget->getKeyword();
    if (2 == m_fromIndex) {
        m_articleNet->request(ui->settingWidget->getCount(), keyword);
    }

    if (0 == index) {
        ui->pbReturn->hide();
        ui->labelTitle->setText(keyword.isEmpty() ? tr("weixin article") : keyword);
    } else if (1 == index) {
        ui->pbReturn->show();
        QListWidgetItem *item = ui->listWidget->currentItem();
        ArticleItemWidget *itemWidget = static_cast<ArticleItemWidget*>(ui->listWidget->itemWidget(item));
        if (itemWidget) {
            ui->labelTitle->setText(itemWidget->getData().description);
            QUrl url(itemWidget->getData().url);
            if (ui->webView->url() != url) {
                ui->webView->load(url);
            }
        }
    } else if (2 == index) {
        ui->pbReturn->show();
        ui->labelTitle->setText(tr("setting"));
    }

    m_fromIndex = index;
}

void Dialog::slotBackgroundLoad(const QString &path)
{
    QImage image(path);
    if (!image.isNull()) {
        this->setBackground(image);
    }
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
