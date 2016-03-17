#include "dialog.h"
#include <QApplication>
#include <QFile>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);

    QFile qss(":/style.css");
    if (qss.open(QIODevice::ReadOnly | QIODevice::Text)) {
        a.setStyleSheet(qss.readAll());
    }

    QTranslator trans;
    trans.load(":/chinese.qm");
    a.installTranslator(&trans);

    Dialog w;
    w.show();

    return a.exec();
}
