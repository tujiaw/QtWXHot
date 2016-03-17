#include "settingwidget.h"
#include "ui_settingwidget.h"
#include <QFileDialog>

SettingWidget::SettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWidget),
    m_setting("tujiaw", "WXHot")
{
    ui->setupUi(this);
    ui->sbCount->setValue(10);
    ui->sbCount->setRange(10, 50);
    ui->sbCount->setSingleStep(5);
    ui->leKeyword->setText("");
    ui->pbBackgroundLoad->setText(tr("load"));

    QPixmap exitPixmap(":/exit");
    exitPixmap = exitPixmap.scaled(ui->pbExit->size());
    ui->pbExit->setIcon(exitPixmap);

    connect(ui->pbBackgroundLoad, &QPushButton::clicked, this, &SettingWidget::slotBackgroundLoad);
    connect(ui->pbExit, &QPushButton::clicked, [this] { qApp->quit(); });

    initData();
}

SettingWidget::~SettingWidget()
{
    delete ui;
}

void SettingWidget::initData()
{
    int count = m_setting.value("ArticleCount").toInt();
    QString keyword = m_setting.value("ArticleKeyword").toString();
    QString path = m_setting.value("BackgroundPath").toString();

    ui->sbCount->setValue(count);
    ui->leKeyword->setText(keyword);

    QFontMetrics fm = ui->pbBackgroundLoad->fontMetrics();
    QString elidedText = fm.elidedText(path, Qt::ElideMiddle, ui->pbBackgroundLoad->width()-30);
    ui->pbBackgroundLoad->setText(elidedText);
}

int SettingWidget::getCount()
{
    int count = ui->sbCount->value();
    m_setting.setValue("ArticleCount", count);
    return count;
}

QString SettingWidget::getKeyword()
{
    QString keyword = ui->leKeyword->text().trimmed();
    m_setting.setValue("ArticleKeyword", keyword);
    return keyword;
}

QString SettingWidget::getBackgroundPath()
{
    return m_setting.value("BackgroundPath").toString();
}

void SettingWidget::slotBackgroundLoad()
{
    QString path = QFileDialog::getOpenFileName(this, "", "", "Images (*.png *.jpg)");
    if (!path.isEmpty()) {
        QFontMetrics fm = ui->pbBackgroundLoad->fontMetrics();
        QString elidedText = fm.elidedText(path, Qt::ElideMiddle, ui->pbBackgroundLoad->width());
        ui->pbBackgroundLoad->setText(elidedText);
        m_setting.setValue("BackgroundPath", path);
        emit sigBackgroundLoad(path);
    }
}
