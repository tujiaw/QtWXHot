#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>

namespace Ui {
class SettingWidget;
}

class SettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWidget(QWidget *parent = 0);
    ~SettingWidget();

    int getCount() const;
    QString getKeyword() const;

signals:
    void sigBackgroundLoad(const QString &path);

private slots:
    void slotBackgroundLoad();

private:
    Ui::SettingWidget *ui;
};

#endif // SETTINGWIDGET_H
