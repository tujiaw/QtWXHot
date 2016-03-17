#include "systemtray.h"
#include <QMenu>

SystemTray::SystemTray(QObject *parent)
    : QSystemTrayIcon(parent)
{
    this->setIcon(QPixmap(":/tray.png").scaled(50, 50));
    initMenu();
}

void SystemTray::initMenu()
{
    this->setContextMenu(&m_menu);
    QAction *acShow = new QAction(tr("show"), &m_menu);
    QAction *acExit = new QAction(tr("exit"), &m_menu);

    connect(acShow, SIGNAL(triggered()), this, SIGNAL(sigShow()));
    connect(acExit, SIGNAL(triggered()), this, SIGNAL(sigExit()));

    m_menu.addAction(acShow);
    m_menu.addAction(acExit);
}
