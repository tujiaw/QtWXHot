#include "settingwidget.h"
#include "ui_settingwidget.h"
#include <QFileDialog>

SettingWidget::SettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);
    ui->sbCount->setValue(10);
    ui->sbCount->setRange(10, 50);
    ui->sbCount->setSingleStep(5);
    ui->leKeyword->setText("");
    ui->leBackgroundPath->setText("");

    connect(ui->pbBackgroundLoad, &QPushButton::clicked, this, &SettingWidget::slotBackgroundLoad);
    connect(ui->pbExit, &QPushButton::clicked, [this] { qApp->quit(); });
}

SettingWidget::~SettingWidget()
{
    delete ui;
}

int SettingWidget::getCount() const
{
    return ui->sbCount->value();
}

QString SettingWidget::getKeyword() const
{
    return ui->leKeyword->text().trimmed();
}

void SettingWidget::slotBackgroundLoad()
{
    QString path = QFileDialog::getOpenFileName(this, "", "", "Images (*.png *.jpg)");
    if (!path.isEmpty()) {
        emit sigBackgroundLoad(path);
    }
}
