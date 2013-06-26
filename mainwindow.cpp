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

#include "abuleduapplicationv1.h"
#include "tete.h"
#include "mainwindow.h"
#include "abuleduaproposv0.h"
#include "abuleduexercicev0.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QInputDialog>
//#include <QLocale>

//bool isIn(int i, QList<int> s);
int rechercherVide(QList<AbulEduFlatBoutonV1 *> s);

MainWindow::MainWindow(QWidget *parent) :
    AbulEduExerciceV0(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    AbulEduAproposV0 *monAide=new AbulEduAproposV0(this);

    fontBIG.setPointSize(50);
    fontMEDIUM.setPointSize(18);
    fontMINUS.setPointSize(10);

     FIXE = 5;
     DEBUTANT = 0;
     JOKER = 1;
     SURCOMPTAGE = 2;
     CALCUL = 3;
     MAXTETES = 4;

//    QRegExp nomNbreRegExp("btnNbre");
    nomBtnNbre = ui->frmAireDeJeu->findChildren <AbulEduFlatBoutonV1 *> (/*nomNbreRegExp*/);
    qDebug() << nomBtnNbre.size();

//    QRegExp nomRepRegExp("btnRep");
    nomBtnRep = ui->frmAnswers->findChildren <AbulEduFlatBoutonV1 *> (/*nomRepRegExp*/);
    foreach(AbulEduFlatBoutonV1* btn,nomBtnRep)
    {
        int nbFleches = btn->objectName().remove("btnRep").toInt() + 1;
        btn->setIconeNormale(":/cibler/backgrounds/target"+QString::number(nbFleches));
        btn->setCouleurFondPressed(QColor(255,255,255,50));
        btn->setCouleursTexte(QColor(0,108,192,255),QColor(0,0,255,255),QColor(0,0,255,255),QColor(0,0,255,255));
    }

//    for (int i = 0; i < MAXTETES; i++) {
//        Tete * tete = new Tete(ui->centralWidget, 15+50*i, 295);
//        tete->affiche();
//        lstTetes.append(tete);
//    }

    niveau = DEBUTANT;
    nExercice = 0;
    nErreurs = 0;
    cumulErreurs = 0;
    nbreCible =-1;
    setAbeExerciceName("Nombre Cible");
    setAbeSkill(trUtf8("stratégie d'anticipation"));

    ui->menuBar->hide();

    setWindowFlags(Qt::CustomizeWindowHint);

    QList<AbulEduFlatBoutonV1 *> btns = ui->frmIcones->findChildren<AbulEduFlatBoutonV1 *>();
    for(int i = 0; i < btns.count(); i++)
    {
        QString composant = btns.at(i)->whatsThis();
        btns.at(i)->setIconeNormale(QString(":/cibler/buttons/%1").arg(composant));

#ifdef __ABULEDUTABLETTEV1__MODE__
        btns.at(i)->setIconePressed(QString(":/cibler/buttons/%1Hover").arg(composant));
#else
        btns.at(i)->setIconeSurvol(QString(":/cibler/buttons/%1Hover").arg(composant));
#endif
        btns.at(i)->setIconeDisabled(QString(":/cibler/buttons/%1Disabled").arg(composant));
        btns.at(i)->setTexteAlignement(Qt::AlignLeft);
    }

#ifdef __ABULEDUTABLETTEV1__MODE__
    /// 15/01/2012 Icham -> mode tablette, pas de tooltips (pas de survol en mode tactile, et puis ça faisait des trucs bizarres parfois)
    /// 15/01/2013 iCHAM -> icones survol = icones normales
    // on cherche tous les enfants, et on leur met une chaine vide en tooltips (= desactivation)
    foreach (QWidget *obj, findChildren<QWidget*>()) {
        obj->setToolTip("");
//        if(dynamic_cast<AbulEduFlatBoutonV1*>(obj)){
//            dynamic_cast<AbulEduFlatBoutonV1*>(obj)->setIconeSurvol(dynamic_cast<AbulEduFlatBoutonV1*>(obj)->getIconeNormale());
//        }
    }
#endif
    foreach(AbulEduFlatBoutonV1* enfant,btns)
    {
        enfant->setCouleurFondPressed(QColor(255,255,255,50));
        enfant->setCouleurTexteSurvol(Qt::red);
        enfant->setCouleurTexteNormale(Qt::white);
        enfant->setStyleSheet(enfant->styleSheet().replace("border-image","text-align: bottom;background-image"));
        enfant->setStyleSheet(enfant->styleSheet().replace("image-position: center","background-position: center top"));
    }

    ui->vl_widgetContainer->removeWidget(ui->frmButtons);
    ui->frmButtons->move(0,40);
    ui->frmButtons->setVisible(false);
    ui->frmButtons->adjustSize();
    ui->btnFullScreen->setEnabled(false);
    ui->btnMinimized->setEnabled(false);
    ui->btnVerifier->setEnabled(false);

    /* Positionnement en dur puisque la hauteur de fenêtre "utile" est fixe */
    ui->frmChoixNombres->move(775,314);
    ui->frmChoixNombres->setVisible(false);
    ui->frmNiveau->move(800,24);
    ui->frmNiveau->setVisible(false);

    QDesktopWidget *widget = QApplication::desktop();
    int desktop_width = widget->width();
    int desktop_height = widget->height();
    this->move((desktop_width-this->width())/2, (desktop_height-this->height())/2);

    initNbreCible();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    foreach(AbulEduFlatBoutonV1* enfant,ui->frmButtons->findChildren<AbulEduFlatBoutonV1 *>())
    {
        enfant->setCouleurTexteSurvol(Qt::red);
        enfant->setStyleSheet(enfant->styleSheet().replace("border-image","text-align: bottom;background-image"));
        enfant->setStyleSheet(enfant->styleSheet().replace("image-position: center","background-position: center top"));
    }
    ui->btnFeuille->setStyleSheet("QPushButton > *{color:red;}QPushButton{border: none; color:rgba(0,0,0,255);background-repeat: no-repeat;background-color:transparent;border-image:url(':/cibler/buttons/leaf');image-position: center;}");
}

#ifndef __ABULEDUTABLETTEV1__MODE__
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isWindowMoving) {
        move(event->globalPos() - m_dragPosition);
        event->accept();
    }

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && ui->lblTitre->rect().contains(event->pos())) {
        m_dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
        m_isWindowMoving = true;
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_isWindowMoving = false;
}

#endif

void MainWindow::initNbreCible() {

    // effacer l'affichage
    ui->lblAffiche->clear();
    ui->btnNouveau->setDisabled(true);
    nErreurs = 0;

    // afficher les btnNbre (je conserve 0 par commodité)
    for (int i = 0; i < 10; i++) {
//        nomBtnNbre[i]->setStyleSheet("color :yellow");
        nomBtnNbre[i]->setIconeNormale(":/cibler/backgrounds/arrow");
        nomBtnNbre[i]->setCouleurFondPressed(QColor(255,255,255,50));
        nomBtnNbre[i]->setCouleursTexte(QColor(0,108,192,255),QColor(0,0,255,255),QColor(0,0,255,255),QColor(0,0,255,255));
        nomBtnNbre[i]->setFont(fontBIG);
        nomBtnNbre[i]->setEnabled(true);
        nomBtnNbre[i]->setProperty("text", QString::number(i));
    }
    nomBtnNbre[0]->hide();
    // joker
    if (niveau == DEBUTANT || niveau == FIXE)
        ui->cboxJoker->hide();
    else {
        ui->cboxJoker->setCurrentIndex(0);
        ui->cboxJoker->setVisible(true);
        ui->cboxJoker->setDisabled(true);
    }
    // effacer les btnRep
    for (int i = 0; i < 3; i++) {

        nomBtnRep[i]->setText("");
    }

    // tirer le nombre cible (pas le même tout de suite)
    int nbreCibleSave = nbreCible;
    nbreDonne = -1;
    if (niveau == FIXE) {
//        qDebug() << "fixe = " << nbreCible;
    }
    else if (niveau == DEBUTANT) {
        while (nbreCibleSave ==  nbreCible) nbreCible = (rand() % 5) + 8;
    } else if (niveau == JOKER) {
        while (nbreCibleSave ==  nbreCible) nbreCible = (rand() % 14) + 11;
    } else {
        if (niveau == SURCOMPTAGE) {
            nbreDonne = 7 + rand() % 3;
            while (nbreCibleSave ==  nbreCible) nbreCible = nbreDonne + 2 + (rand() % 5);
        } else {
            nbreDonne = 1 + rand() % 3;
            while (nbreCibleSave ==  nbreCible) nbreCible = nbreDonne + 9 + 4 + (rand() % 6);
        }
        nomBtnRep[0]->setText(QString::number(nbreDonne));
        nomBtnRep[0]->setDisabled(true);
        nomBtnNbre[nbreDonne]->setDisabled(true);
        nomBtnNbre[nbreDonne]->setFont(fontMEDIUM);
    }
    ui->lblCible->setText(QString::number(nbreCible));

    setAbeLevel(trUtf8("niveau %1").arg(QString::number(niveau)));
    //setAbeLineLog(trUtf8("Atteindre la cible en 3 coups"),"",-1,0,"a");

} // fin initNombreCible

void MainWindow::on_btnNbre1_clicked() { _btnNbre(1); }
void MainWindow::on_btnNbre2_clicked() { _btnNbre(2); }
void MainWindow::on_btnNbre3_clicked() { _btnNbre(3); }
void MainWindow::on_btnNbre4_clicked() { _btnNbre(4); }
void MainWindow::on_btnNbre5_clicked() { _btnNbre(5); }
void MainWindow::on_btnNbre6_clicked() { _btnNbre(6); }
void MainWindow::on_btnNbre7_clicked() { _btnNbre(7); }
void MainWindow::on_btnNbre8_clicked() { _btnNbre(8); }
void MainWindow::on_btnNbre9_clicked() { _btnNbre(9); }

void MainWindow::_btnNbre(int n) {

    nbreChoisi = n;
    // construire la liste actuelle des nombres choisis
    nbresChoisis.clear();
    for (int i = 0; i < 3; i++)
        if (nomBtnRep[i]->text() != "") nbresChoisis << nomBtnRep[i]->text().toInt();
    if (nbresChoisis.length() < 3 ) { // ya encore de la place !
        nbresChoisis << nbreChoisi;
        // désélectionner un btnRep
        int i = rechercherVide(nomBtnRep); // indice d'un btnReponse vide
        nomBtnRep[i]->setText(QString::number(nbreChoisi));
        // modifier le bntNbre
        nomBtnNbre[nbreChoisi]->setDisabled(true);
        nomBtnNbre[nbreChoisi]->setFont(fontMEDIUM);
    }
    gererJoker();
    if (nbresChoisis.length() >=3 ) {
        int s = 0; // somme des nombres choisis
        for (int i = 0; i < 3; i++) s += nbresChoisis[i];
        verifier(s);
    }
} // fin _btnNbre

int rechercherVide(QList <AbulEduFlatBoutonV1 *> s) {
    for (int i = 0; i < 3; i++) {
        if (s[i]->text() == "") return i;
    }
    return -1;
}

QString MainWindow::abeEvaluation() {
    if (nErreurs == 0)
       return "a";
    else if (nErreurs == 1)
       return "b";
    return "c";
}

void MainWindow::verifier(int somme) {
    if (somme == nbreCible) {
        ui->lblAffiche->setText(trUtf8("Bien,\n  Tu peux maintenant\n  prendre une nouvelle cible."));
        setAbeLineLog(trUtf8("Atteindre la cible en 3 coups"),"",-1,0, abeEvaluation());
        pushAbulEduLogs();
        ui->btnNouveau->setDisabled(false);
        if (nExercice < MAXTETES) {
//            if (nErreurs == 0)
//                lstTetes[nExercice]->affiche(0);
//            else if (nErreurs < 3)
//                lstTetes[nExercice]->affiche(1);
//            else
//                lstTetes[nExercice]->affiche(2);
        }
    } else {
        ui->lblAffiche->setText(trUtf8("Erreur, \n  Je te demande\n  de corriger..."));        
        nErreurs++;     
        cumulErreurs++;
        setAbeLineLog(trUtf8("Atteindre la cible en 3 coups"),"",-1,0, "d", QString::number(nbreCible), "", "", QString::number(somme));
    }
}

void MainWindow::on_btnRep0_clicked() { _btnRep(0); }
void MainWindow::on_btnRep1_clicked() { _btnRep(1); }
void MainWindow::on_btnRep2_clicked() { _btnRep(2); }

void MainWindow::_btnRep(int n) {
    // valeur du btnRep
    int v = nomBtnRep[n]->text().toInt();
    // effacer le btnRep
    nomBtnRep[n]->setText("");
    // restaurer le btnNbre
    nomBtnNbre[v]->setDisabled(false);
    nomBtnNbre[v]->setFont(fontBIG);
    gererJoker();
}

void MainWindow::on_btnNouveau_clicked()
{
    nExercice++;
    if (nExercice >= MAXTETES && niveau < CALCUL)
        if (cumulErreurs < 4)
           _niveau(niveau+1);
        else {
            setAbeLineLog(trUtf8("Atteindre la cible en 3 coups"),"",-1,0, "d", "", "", trUtf8("Pas de changement de niveau"));
           _niveau(niveau);
       }
    else
        initNbreCible();
}

void MainWindow::on_actionProposerCible_triggered() {
    niveau = FIXE;
    bool ok;
    int n = QInputDialog::getInteger(this, trUtf8("Choisis une cible"), trUtf8("Nombre entier\n  entre 9 et 28"), 13, 9, 28, 1, &ok);
    if (ok)
        nbreCible = n;
    else {
        niveau = DEBUTANT;
    }
    initNbreCible();
}

void MainWindow::on_actionDebutant_triggered() { _niveau(DEBUTANT); }
void MainWindow::on_actionJoker_triggered() { _niveau(JOKER); }
void MainWindow::on_actionSurcomptage_triggered() { _niveau(SURCOMPTAGE); }
void MainWindow::on_actionCalcul_triggered() { _niveau(CALCUL); }

void MainWindow::_niveau(int n) {
    niveau = n;
    nExercice = 0;
    cumulErreurs = 0;
    for (int i = 0; i < MAXTETES; i++)
//        lstTetes[i]->affiche(-1);
    initNbreCible();
}

void MainWindow::on_cboxJoker_activated(int index)
{
    if (index > 0 && index <10) _btnNbre(index);
    else if (index == 10) _btnNbre(0);
}

void MainWindow::gererJoker() {
    nbresChoisis.clear();
    for (int i = 0; i < 3; i++)
        if (nomBtnRep[i]->text() != "") nbresChoisis << nomBtnRep[i]->text().toInt();
    if (nbresChoisis.length() == 2)
        ui->cboxJoker->setDisabled(false);
    else
        ui->cboxJoker->setDisabled(true);
}

void MainWindow::on_btnQuitter_clicked()
{
    close();
}

void MainWindow::on_action_Journal_de_mes_activit_s_triggered()
{
    abeApp->getAbeIdentite()->abeGetMyLogsAsPDF();
}

void MainWindow::on_action_Changer_d_utilisateur_triggered()
{
    abeApp->getAbeNetworkAccessManager()->abeSSOLogout();
    abeApp->getAbeNetworkAccessManager()->abeSSOLogin();
}

void MainWindow::on_btnFeuille_clicked()
{
    if (ui->frmButtons->isVisible())
    {
        ui->frmButtons->setVisible(false);
    }
    else
    {
        ui->frmButtons->setVisible(true);
        ui->frmButtons->raise();
    }
    on_btnNombresFermer_clicked();
    on_btnNiveauAnnuler_clicked();
}

void MainWindow::on_btnSortie_clicked()
{
    close();
}

void MainWindow::on_btnNiveaux_clicked()
{
    ui->frmNiveau->setVisible(true);
    ui->frmNiveau->raise();
    ui->btnNiveaux->setStyleSheet(ui->btnNiveaux->styleSheet().replace("background-color:rgba(0,0,0,0);","border-radius:5px;background-color:#ffffff;"));
    on_btnNombresFermer_clicked();
    if (ui->frmButtons->isVisible())
    {
        ui->frmButtons->setVisible(false);
    }
}

void MainWindow::on_btnNombres_clicked()
{
    ui->lineEditOrigine->clear();
    ui->lineEditOrigine->setFocus();
    ui->frmChoixNombres->setVisible(true);
    ui->frmChoixNombres->raise();
    ui->btnNombres->setStyleSheet(ui->btnNombres->styleSheet().replace("background-color:rgba(0,0,0,0);","border-radius:5px;background-color:#ffffff;"));
    on_btnNiveauAnnuler_clicked();
    if (ui->frmButtons->isVisible())
    {
        ui->frmButtons->setVisible(false);
    }
}

void MainWindow::on_btnNiveauAnnuler_clicked()
{
    ui->frmNiveau->setVisible(false);
    ui->btnNiveaux->setStyleSheet(ui->btnNiveaux->styleSheet().replace("border-radius:5px;background-color:#ffffff;","background-color:rgba(0,0,0,0);"));
}

void MainWindow::on_btnNombresFermer_clicked()
{
    ui->frmChoixNombres->setVisible(false);
    ui->btnNombres->setStyleSheet(ui->btnNombres->styleSheet().replace("border-radius:5px;background-color:#ffffff;","background-color:rgba(0,0,0,0);"));
}

void MainWindow::on_btnNiveauJaune_clicked()
{
    _niveau(DEBUTANT);
}

void MainWindow::on_btnNiveauOrange_clicked()
{
    _niveau(JOKER);
}

void MainWindow::on_btnNiveauMarron_clicked()
{
    _niveau(SURCOMPTAGE);
}

void MainWindow::on_btnNiveauNoire_clicked()
{
    _niveau(CALCUL);
}

void MainWindow::on_lineEditOrigine_returnPressed()
{
    niveau = FIXE;
    bool ok;
    int n = ui->lineEditOrigine->text().toInt(&ok);
    if (ok)
    {
        if(n >= 9 && n <= 28)
        {
            nbreCible = n;
            initNbreCible();
            on_btnNombresFermer_clicked();
        }
        else
        {
            AbulEduMessageBoxV1* msg = new AbulEduMessageBoxV1(trUtf8("Problème"),trUtf8("Le nombre doit être compris entre 9 et 28"));
            msg->show();
        }
    }
    else {
        AbulEduMessageBoxV1* msg = new AbulEduMessageBoxV1(trUtf8("Problème"),trUtf8("C'est un nombre, %1 ?!").arg(ui->lineEditOrigine->text()));
        msg->show();
    }
}
