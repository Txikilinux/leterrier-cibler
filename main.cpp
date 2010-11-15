#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qApp->setApplicationName("NombreCible");
    qApp->setApplicationVersion("10.11");
    qApp->setOrganizationDomain("http://www.abuledu.org/leterrier/cible");

    MainWindow w;
    w.setFixedSize(600, 400);
    w.show();
    return a.exec();
}
