#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qApp->setApplicationName("NombreCible");
    qApp->setApplicationVersion("v1");
    qApp->setOrganizationDomain("http://entraide.abuledu-fr.org/rss/topic/nombre-cible");

    MainWindow w;
    w.setFixedSize(600, 400);
    w.show();
    return a.exec();
}
