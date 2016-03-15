#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QSystemTrayIcon>
#include <QMenu>

class SystemTray : public QSystemTrayIcon
{
    Q_OBJECT

public:
    explicit SystemTray(QObject *parent = 0);
    void initMenu();

signals:
    void sigExit();

private:
    QMenu m_menu;
};

#endif // SYSTEMTRAY_H
