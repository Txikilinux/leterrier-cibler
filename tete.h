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


#ifndef TETE_H
#define TETE_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>

class Tete : public QWidget
{
    Q_OBJECT
public:
    explicit Tete(QWidget *parent = 0, int x = 0, int y = 0);
    ~Tete();
    void affiche(int apparence = -1);
    void cache();
private:
    /**
      le label contient l'image
      */
    QLabel lblTete;
    /**
      les différentes images
      */
    QPixmap teteNeutre;
    QPixmap teteBien;
    QPixmap tetePassable;
    QPixmap teteMal;

    QPoint m_position;
    QSize m_taille;
    /**
      apparence de la tête
      neutre < 0, bien = 0, passable = 1 ou 2, mal > 2 (nombre d'erreur(s)
      */
    int apparence;

signals:

public slots:

};


#endif // TETE_H
