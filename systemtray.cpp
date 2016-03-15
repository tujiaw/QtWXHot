#include "systemtray.h"
#include <QMenu>

SystemTray::SystemTray(QObject *parent)
    : QSystemTrayIcon(parent)
{
    this->setIcon(QIcon(":/tray"));
    initMenu();
}

void SystemTray::initMenu()
{
    this->setContextMenu(&m_menu);
    QAction *acExit = new QAction("Exit", &m_menu);
    connect(acExit, SIGNAL(triggered()), this, SIGNAL(sigExit()));
    m_menu.addAction(acExit);
}
