/**
  * Chemin (le terrier d'AbulEdu)
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

#include<QtCore>
#include "tete.h"

Tete::Tete(QWidget *parent, int x, int y) :
    QWidget(parent)
{

    teteNeutre = QPixmap(QString::fromUtf8(":/img/data/images/teteNeutre.png"));
    teteBien = QPixmap(QString::fromUtf8(":/img/data/images/teteBien.png"));
    tetePassable = QPixmap(QString::fromUtf8(":/img/data/images/tetePassable.png"));
    teteMal = QPixmap(QString::fromUtf8(":/img/data/images/teteMal.png"));

    m_taille = QSize(51, 51);
    m_position = QPoint(x, y);
    this->lblTete.move(m_position);
    this->lblTete.resize(m_taille);
    this->lblTete.setScaledContents(true);
    this->lblTete.setParent(parent);
    this->lblTete.show();
}
Tete::~Tete()
{
}
void Tete::affiche(int apparence) {
    this->lblTete.show();
    if (apparence < 0)
        lblTete.setPixmap(teteNeutre);
    else if (apparence == 0)
        lblTete.setPixmap(teteBien);
    else if (apparence ==1)
        lblTete.setPixmap(tetePassable);
    else
        lblTete.setPixmap(teteMal);
}

void Tete::cache() {
    this->lblTete.hide();
}
