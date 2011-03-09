/**
  * NombreCible (le terrier d'AbulEdu)
  *
  * @warning aucun traitement d'erreur n'est pour l'instant implémenté
  * @see https://redmine.ryxeo.com/projects/
  * @author 2009-2010 Andre Connes <andre dot connes at wanadoo dot fr>
  * @author 2011 Eric Seigne <eric.seigne@ryxeo.com>
  * @see The GNU Public License (GPL)
  */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include <QtGui/QApplication>
#include "mainwindow.h"
#include "abuleduaproposv0.h"

//-------------------Nom visible de l'application---------------------
//
extern const QString abeApplicationLongName="Leterrier d'AbulEdu - Nombre Cible";
//
//--------------------------------------------------------------------

//Capteur de debug
void debugOutput(QtMsgType type, const char *msg)
{
  switch (type) {
  case QtDebugMsg:
#ifdef QT_NO_DEBUG_OUTPUT
    fprintf(stderr, "Debug: %s\n", msg);
#endif
    break;
  case QtWarningMsg:
#ifdef QT_NO_WARNING_OUTPUT
    fprintf(stderr, "Warning: %s\n", msg);
#endif
    break;
  case QtCriticalMsg:
    fprintf(stderr, "Critical: %s\n", msg);
    break;
  case QtFatalMsg:
    fprintf(stderr, "Fatal: %s\n", msg);
    abort();
  }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //a mettre en commentaire pour avoir les qdebug ... et a activer
    //quand on release l'application
    qInstallMsgHandler(debugOutput);

    qApp->setApplicationName("leterrier-cibler");
    qApp->setApplicationVersion("1.0.3");
    qApp->setOrganizationDomain("abuledu.org");
    qApp->setOrganizationName("leterrier");

    MainWindow w;
    w.setFixedSize(600, 400);
    w.show();
    return a.exec();
}
