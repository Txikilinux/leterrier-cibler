#include <QtGui/QApplication>
#include "mainwindow.h"
#include "abuleduaproposv0.h"

//-------------------Nom visible de l'application---------------------
//
extern const QString abeApplicationLongName="Leterrier d'AbulEdu - Nombre Cible";
//
//--------------------------------------------------------------------

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qApp->setApplicationName("leterrier-cibler");
    qApp->setApplicationVersion("1.0.1");
    qApp->setOrganizationDomain("abuledu.org");
    qApp->setOrganizationName("leterrier");

    MainWindow w;
    w.setFixedSize(600, 400);
    w.show();
    return a.exec();
}
