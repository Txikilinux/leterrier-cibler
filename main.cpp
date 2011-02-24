/**
  * NombreCible (le terrier d'AbulEdu)
  *
  * @warning aucun traitement d'erreur n'est pour l'instant implémenté
  * @see https://redmine.ryxeo.com/projects/
  * @author 2009-2010 Andre Connes <andre dot connes at wanadoo dot fr>
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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qApp->setApplicationName("leterrier-cibler");
    qApp->setApplicationVersion("1.0.2");
    qApp->setOrganizationDomain("abuledu.org");
    qApp->setOrganizationName("leterrier");

    MainWindow w;
    w.setFixedSize(600, 400);
    w.show();
    return a.exec();
}
