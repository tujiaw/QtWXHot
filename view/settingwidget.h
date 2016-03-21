#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include <QSettings>

namespace Ui {
class SettingWidget;
}

class SettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWidget(QWidget *parent = 0);
    ~SettingWidget();

    void initData();
    int getCount();
    QString getKeyword();
    QString getBackgroundPath();

    void setBackgroundPath(const QString &path);

signals:
    void sigBackgroundLoad(const QString &path);

private slots:
    void slotBackgroundLoad();

private:
    Ui::SettingWidget *ui;
    QSettings m_setting;
};

#endif // SETTINGWIDGET_H
