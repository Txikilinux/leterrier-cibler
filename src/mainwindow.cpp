/**
  * Cibler (le Terrier d'AbulÉdu)
  *
  * @warning aucun traitement d'erreur n'est pour l'instant implémenté
  * @see https://redmine.ryxeo.com/projects/leterrier-cibler
  * @author 2010-2011 André Connes <andre.connes@wanadoo.fr>
  * @author 2011 Jean-Louis Frucot <frucot.jeanlouis@free.fr>
  * @author 2011-2013 Eric Seigne <eric.seigne@ryxeo.com>
  * @author 2012-2013 Philippe Cadaugade <philippe.cadaugade@ryxeo.com>
  * @author 2013 Icham Sirat <icham.sirat@ryxeo.com>
  * @see The GNU Public License (GPL)
  *
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
    ui->frmIcones->raise();

    //    AbulEduAproposV0 *monAide=new AbulEduAproposV0(this);

    fontBIG.setPointSize(50);
    fontMEDIUM.setPointSize(18);
    MAXTETES = 4;
    m_isCanceled = false;

    nomBtnNbre.clear();
    for(int i = 0;i<10;i++)
    {
        foreach(AbulEduFlatBoutonV1* btn,ui->frmAireDeJeu->findChildren <AbulEduFlatBoutonV1 *>())
        {
            if(btn->objectName().endsWith(QString::number(i)))
            {
                nomBtnNbre << btn;
            }
        }
    }
    nomBtnRep.clear();
    for(int i = 0;i<10;i++)
    {
        foreach(AbulEduFlatBoutonV1* btn,ui->frmAnswers->findChildren <AbulEduFlatBoutonV1 *>())
        {
            if(btn->objectName().endsWith(QString::number(i)))
            {
                nomBtnRep << btn;
            }
        }
    }
    foreach(AbulEduFlatBoutonV1* btn,nomBtnRep)
    {
        int nbFleches = btn->objectName().remove("btnRep").toInt() + 1;
        btn->setIconeNormale(":/cibler/backgrounds/target"+QString::number(nbFleches));
        btn->setCouleurFondPressed(QColor(255,255,255,50));
        btn->setCouleursTexte(QColor(154,68,45,255),QColor(93,23,15,255),QColor(93,23,15,255),QColor(93,23,15,255));
    }

    niveau = DEBUTANT;
    nExercice = 0;
    nErreurs = 0;
    cumulErreurs = 0;
    nbreCible =-1;
    m_messageAide = trUtf8("Choisis dans la grille des nombres pour compléter correctement l'addition. A tout moment, tu peux reprendre un nombre de l'addition en cliquant dessus.");
    m_messageEnd = QString();
    setAbeExerciceName("Cibler");
    setAbeSkill(trUtf8("stratégie d'anticipation"));


    setWindowFlags(Qt::CustomizeWindowHint);
    connect(ui->frmMenuFeuille, SIGNAL(signalAbeMenuFeuilleChangeLanguage(QString)),this,SLOT(slotChangeLangue(QString)),Qt::UniqueConnection);


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

    ui->btnVerifier->setEnabled(false);

    /* Positionnement en dur puisque la hauteur de fenêtre "utile" est fixe */
    ui->frmChoixNombres->move(780,164);
    ui->frmNiveau->move(802,107);

    ui->frmFondJoker->setVisible(false);
    ui->frmFondJoker->move(270,300);
    foreach(AbulEduFlatBoutonV1* btn, ui->frmNbresJoker->findChildren<AbulEduFlatBoutonV1*>())
    {
        connect(btn, SIGNAL(clicked()),SLOT(slotSendJoker()),Qt::UniqueConnection);
    }
    ui->btnJoker->setIcones(":/data/images/boutonJoker",":/data/images/boutonJokerHover",":/data/images/boutonJokerHover","");
    ui->btnJoker->setVisible(false);

#if !defined(Q_OS_ANDROID)
    /* Centrage fenetre avec gestion multi-ecrans */
    QDesktopWidget *widget = QApplication::desktop();
    /* C'est ici qu'on récupère le uméro d'écran de l'appli ->screenNumber(this) */
    int desktop_width  = widget->screen(widget->screenNumber(this))->width();
    int desktop_height = widget->screen(widget->screenNumber(this))->height();
    this->move((desktop_width-this->width())/2, (desktop_height-this->height())/2);
#endif
    connect(ui->pageAbout, SIGNAL(signalAbeAproposBtnCloseClicked()), this, SLOT(slotMainWindowShowMainPage()),Qt::UniqueConnection);
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

void MainWindow::initNbreCible()
{
    ui->btnAbandonner->setEnabled(true);
    foreach(AbulEduMessageBoxV1* mbox,ui->pagePrincipale->findChildren<AbulEduMessageBoxV1*>()){
        mbox->close();
    }
    // effacer l'affichage
    nErreurs = 0;
    m_isCanceled = false;

    /* Gestion du joker */
    if (niveau == DEBUTANT || niveau == FIXE || niveau == CALCULEXPERT )
    {
        ui->btnJoker->setVisible(false);
    }
    else {
        ui->btnJoker->setVisible(true);
        ui->btnJoker->setEnabled(true);
    }
    if(ui->btnJoker->isVisible()){
        m_messageAide = trUtf8("Le bouton dragon est le joker. Il te donne la possibilité d'utiliser n'importe quel nombre entre 0 et 9");
    }
    else {
        m_messageAide = trUtf8("Choisis dans la grille des nombres pour compléter correctement l'addition. A tout moment, tu peux reprendre un nombre de l'addition en cliquant dessus.");
    }
    /* Vider les btnRep */
    for (int i = 0; i < 3; i++) {

        nomBtnRep[i]->setText("");
    }
    int graine = 1;
//    if(nive)
    /* afficher les btnNbre (je conserve 0 par commodité) <- ? */
    nomBtnNbre[0]->hide();
    int nbreCibleSave = nbreCible;

    if(niveau == CALCULEXPERT){
        nbreCible = 0;
        nbreDonne = 1+rand()%10;
        do {
            graine = 9 + rand()%((38-nbreDonne)/2);
            m_second = graine+rand()%9;
            do{
                m_third = graine+rand()%9;
            }
            while(m_third == m_second);
            nbreCible = m_second + m_third + nbreDonne;
            nomBtnRep[0]->setText(QString::number(nbreDonne));
            nomBtnRep[0]->setEnabled(false);
            ui->lblCible->setText(QString::number(nbreCible));

        }
        while(nbreCible == nbreCibleSave || nbreCible < 35);
    }
    else {
        /* Tirer le nombre cible (différent du précédent) */
        nbreDonne = -1;
        if (niveau == FIXE) {
        }
        else if (niveau == DEBUTANT) {
            while (nbreCibleSave ==  nbreCible) nbreCible = (rand() % 5) + 8;
            nomBtnRep[0]->setEnabled(true);
        }
        else if (niveau == JOKER) {
            while (nbreCibleSave ==  nbreCible) nbreCible = (rand() % 14) + 11;
            nomBtnRep[0]->setEnabled(true);
        }
        else {
            if (niveau == SURCOMPTAGE) {
                nbreDonne = 7 + rand() % 3;
                while (nbreCibleSave ==  nbreCible) nbreCible = nbreDonne + 2 + (rand() % 5);
            } else {
                nbreDonne = 1 + rand() % 3;
                while (nbreCibleSave ==  nbreCible) nbreCible = nbreDonne + 9 + 4 + (rand() % 6);
            }
            nomBtnRep[0]->setText(QString::number(nbreDonne));
            nomBtnRep[0]->setEnabled(false);
            nomBtnNbre[nbreDonne]->setEnabled(false);
            nomBtnNbre[nbreDonne]->setFont(fontMEDIUM);
        }
        ui->lblCible->setText(QString::number(nbreCible));
    }
    setAbeLevel(trUtf8("niveau %1").arg(QString::number(niveau)));
    //setAbeLineLog(trUtf8("Atteindre la cible en 3 coups"),"",-1,0,"a");
    slotHideFrames();
    for (int i = 1; i < 10; i++) {
        nomBtnNbre[i]->setIconeNormale(":/cibler/backgrounds/arrow");
        nomBtnNbre[i]->setCouleurFondPressed(QColor(255,255,255,50));
        nomBtnNbre[i]->setCouleursTexte(QColor(154,68,45,255),QColor(93,23,15,255),QColor(93,23,15,255),QColor(93,23,15,255));
        nomBtnNbre[i]->setFont(fontBIG);
        nomBtnNbre[i]->setEnabled(true);
        nomBtnNbre[i]->setProperty("text", QString::number(i-1+graine));
        connect(nomBtnNbre[i],SIGNAL(clicked()),SLOT(slotHideFrames()),Qt::UniqueConnection);
        if(niveau == SURCOMPTAGE || niveau == CALCUL || niveau == CALCULEXPERT){
            if(i-1+graine == nbreDonne){
                nomBtnNbre[i]->setDisabled(true);
                nomBtnNbre[i]->setFont(fontMEDIUM);
            }
        }
    }

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

void MainWindow::_btnNbre(int n)
{
    nbreChoisi = nomBtnNbre[n]->text().toInt();
    /* construire la liste actuelle des nombres choisis */
    nbresChoisis.clear();
    for (int i = 0; i < 3; i++)
        if (nomBtnRep[i]->text() != "") nbresChoisis << nomBtnRep[i]->text().toInt();
    if (nbresChoisis.length() < 3 ) { // ya encore de la place !
        nbresChoisis << nbreChoisi;
        /* désélectionner un btnRep */
        int i = rechercherVide(nomBtnRep); // indice d'un btnReponse vide
        nomBtnRep[i]->setText(QString::number(nbreChoisi));
        /* modifier le bntNbre */
        nomBtnNbre[n]->setDisabled(true);
        nomBtnNbre[n]->setFont(fontMEDIUM);
    }
    /*    gererJoker(); */
    if (nbresChoisis.length() >=3 ) {
        int s = 0; /* somme des nombres choisis */
        for (int i = 0; i < 3; i++) s += nbresChoisis[i];
        verifier(s);
    }
}

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

void MainWindow::verifier(int somme)
{
    if(!m_isCanceled)
    {
        foreach(AbulEduMessageBoxV1* mbox,ui->pagePrincipale->findChildren<AbulEduMessageBoxV1*>()){
            mbox->close();
        }
        if (somme == nbreCible) {
            AbulEduMessageBoxV1* msg = new AbulEduMessageBoxV1(trUtf8("Félicitations !!"),trUtf8("Tu peux maintenant\n  prendre une nouvelle cible."),true, ui->pagePrincipale);
            msg->setWink();
            msg->show();
            setAbeLineLog(trUtf8("Atteindre la cible en 3 coups"),"",-1,0, abeEvaluation());
            pushAbulEduLogs();
            if (nExercice < MAXTETES) {
                //            if (nErreurs == 0)
                //                lstTetes[nExercice]->affiche(0);
                //            else if (nErreurs < 3)
                //                lstTetes[nExercice]->affiche(1);
                //            else
                //                lstTetes[nExercice]->affiche(2);
            }
            ui->btnAbandonner->setEnabled(false);
        }
        else {
            AbulEduMessageBoxV1* msg = new AbulEduMessageBoxV1(trUtf8("Erreur !!"),trUtf8("Je te demande\n  de corriger..."),true, ui->pagePrincipale);
            msg->show();
            nErreurs++;
            cumulErreurs++;
            setAbeLineLog(trUtf8("Atteindre la cible en 3 coups"),"",-1,0, "d", QString::number(nbreCible), "", "", QString::number(somme));
        }
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
    bool found = false;
    QListIterator<AbulEduFlatBoutonV1*> it(nomBtnNbre);
    while(it.hasNext() && !found){
        AbulEduFlatBoutonV1* btn = it.next();
        if(btn->text().toInt() == v){
            btn->setDisabled(false);
            btn->setFont(fontBIG);
            found = true;
        }
    }
    gererJoker();
}

void MainWindow::on_abeMenuFeuilleBtnNew_clicked()
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
    int n = QInputDialog::getInt(this, trUtf8("Choisis une cible"), trUtf8("Nombre entier\n  entre 9 et 24"), 13, 9, 24, 1, &ok);
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
    //    for (int i = 0; i < MAXTETES; i++)
    ////        lstTetes[i]->affiche(-1);

    ui->lblLevel->setPixmap(QPixmap(":/data/belts/belt"+QString::number(n)));
    initNbreCible();
}

void MainWindow::slotSendJoker()
{
    AbulEduFlatBoutonV1* btn = static_cast<AbulEduFlatBoutonV1*>(sender());
    int ind = btn->objectName().remove("btn").toInt();
    _btnNbre(ind);
    ui->frmFondJoker->setVisible(false);
    ui->btnJoker->setEnabled(false);
    setAllButtonsEnabled(true);
}

void MainWindow::gererJoker() {
    nbresChoisis.clear();
    for (int i = 0; i < 3; i++) {
        if (nomBtnRep[i]->text() != "") nbresChoisis << nomBtnRep[i]->text().toInt();
    }
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

void MainWindow::on_abeMenuFeuilleBtnQuit_clicked()
{
    close();
}

void MainWindow::on_btnNiveaux_clicked()
{
    ui->frmNiveau->setVisible(true);
    ui->frmNiveau->raise();
    ui->btnNiveaux->setStyleSheet(ui->btnNiveaux->styleSheet().replace("background-color:rgba(0,0,0,0);","border-radius:5px;background-color:#ffffff;"));
    on_btnNombresFermer_clicked();
}

void MainWindow::on_btnNombres_clicked()
{
    ui->lineEditOrigine->clear();
    ui->lineEditOrigine->setFocus();
    ui->frmChoixNombres->setVisible(true);
    ui->frmChoixNombres->raise();
    ui->btnNombres->setStyleSheet(ui->btnNombres->styleSheet().replace("background-color:rgba(0,0,0,0);","border-radius:5px;background-color:#ffffff;"));
    on_btnNiveauAnnuler_clicked();
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

void MainWindow::on_btnLevelVeryEasy_clicked()
{
    _niveau(DEBUTANT);
}

void MainWindow::on_btnLevelEasy_clicked()
{
    _niveau(JOKER);
}

void MainWindow::on_btnLevelMedium_clicked()
{
    _niveau(SURCOMPTAGE);
}

void MainWindow::on_btnLevelDifficult_clicked()
{
    _niveau(CALCUL);
}

void MainWindow::on_btnLevelVeryDifficult_clicked()
{
    _niveau(CALCULEXPERT);
}

void MainWindow::on_lineEditOrigine_returnPressed()
{
    foreach(AbulEduMessageBoxV1* mbox,ui->pagePrincipale->findChildren<AbulEduMessageBoxV1*>()){
        mbox->close();
    }
    niveau = FIXE;
    ui->lblLevel->setPixmap(QPixmap(":/data/belts/belt"+QString::number(niveau)));

    bool ok;
    int n = ui->lineEditOrigine->text().toInt(&ok);
    if (ok)
    {
        if(n >= 9 && n <= 24)
        {
            nbreCible = n;
            initNbreCible();
            on_btnNombresFermer_clicked();
        }
        else
        {
            AbulEduMessageBoxV1* msg = new AbulEduMessageBoxV1(trUtf8("Problème"),trUtf8("Le nombre doit être compris entre 9 et 24"),true, ui->pagePrincipale);
            msg->show();
        }
    }
    else {
        AbulEduMessageBoxV1* msg = new AbulEduMessageBoxV1(trUtf8("Problème"),trUtf8("C'est un nombre, %1 ?!").arg(ui->lineEditOrigine->text()),true, ui->pagePrincipale);
        msg->show();
    }
}

void MainWindow::slotHideFrames()
{
    on_btnNombresFermer_clicked();
    on_btnNiveauAnnuler_clicked();
}

void MainWindow::donneReponse()
{
    foreach(AbulEduMessageBoxV1* mbox,ui->pagePrincipale->findChildren<AbulEduMessageBoxV1*>()){
        mbox->close();
    }
    ui->btnRep2->click();
    ui->btnRep1->click();
    if(niveau < 2){
        ui->btnRep0->click();
    }
    bool useAgain = false;
    if(niveau == CALCULEXPERT){
        m_first = nbreDonne;
        /* les attributs m_second et m_third ont déjà une valeur */
        QTimer::singleShot(2000, this, SLOT(writeSecondInBtnRep()));
        QTimer::singleShot(3000, this, SLOT(writeThirdInBtnRep()));
        QTimer::singleShot(5000, this, SLOT(slotEndSolution()));
    }
    else {
        m_first = -1;
        m_second = -1;
        m_third = -1;
        if(nbreDonne == -1)
        {

            nbresChoisis.clear();
            for(int i=0;i<100;i++){
                m_first = -1;
                m_second = -1;
                m_third = -1;
                while(m_first + m_second + m_third != nbreCible)
                {
                    m_first = rand()%9+1;
                    while(m_second == m_first || m_second==-1){
                        m_second = rand()%9+1;
                    }
                    while(m_third == m_first || m_third == m_second || m_third==-1) {
                        m_third = rand()%9+1;
                    }
                }
            }
        }
        else if(nbreDonne == nbreCible-2){
            m_first = nbreDonne;
            m_second = 1;
            m_third = 1;
            useAgain = true;
        }
        else
        {
            m_first = nbreDonne;
            int but = nbreCible - nbreDonne;
            if (but == 18){
                m_second = 9;
                m_third = 9;
                useAgain = true;
            }
            else {
                while(m_second + m_third != but)
                {
                    m_second = rand()%9+1;
                    while(m_second == nbreDonne || m_second==-1){
                        m_second = rand()%9+1;
                    }
                    QList<int> used;
                    used << m_first << m_second;
                    while((m_third == nbreDonne || m_third == m_second || m_third==-1) && !useAgain) {
                        m_third = rand()%9+1;
                        if(!used.contains(m_third)){
                            used << m_third;
                            /* Si on a essayé tous les chiffres */
                            if(used.size() > 9){
                                useAgain = true;
                                while(m_third == nbreDonne || m_third==-1)
                                {
                                    m_third = rand()%9+1;
                                }
                            }
                        }
                    }
                }
            }
        }
        if(m_first != nbreDonne) {
            QTimer::singleShot(1000, nomBtnNbre[m_first], SLOT(click()));
        }
        QTimer::singleShot(2000, nomBtnNbre[m_second], SLOT(click()));
        if(m_third == m_second){
            QTimer::singleShot(3000, this, SLOT(writeThirdInBtnRep()));
        }
        else {
            QTimer::singleShot(3000, nomBtnNbre[m_third], SLOT(click()));
        }
        if(useAgain){
            QTimer::singleShot(5000, this, SLOT(slotEndSolutionJoker()));
        }
        else {
            QTimer::singleShot(5000, this, SLOT(slotEndSolution()));
        }
    }
}

void MainWindow::writeSecondInBtnRep()
{
    nomBtnRep[1]->setText(QString::number(m_second));
}

void MainWindow::writeThirdInBtnRep()
{
    nomBtnRep[2]->setText(QString::number(m_third));
}

void MainWindow::on_btnAbandonner_clicked()
{
    m_isCanceled = true;
    foreach(AbulEduFlatBoutonV1* enfant,ui->frmIcones->findChildren<AbulEduFlatBoutonV1 *>())
    {
        enfant->setEnabled(false);
    }
    donneReponse();
}

void MainWindow::slotEndSolution()
{
    m_messageEnd = trUtf8("Voici un corrigé ! \n\nTu peux choisir une nouvelle grille en cliquant sur la feuille de cerisier ou sur la cible, ou en changeant de niveau...");
    showEndSolution();
}

void MainWindow::slotEndSolutionJoker()
{
    m_messageEnd = trUtf8("Voici une solution possible. Il fallait utiliser le joker... Tu peux rejouer...");
    showEndSolution();
}

void MainWindow::showEndSolution()
{
    foreach(AbulEduMessageBoxV1* mbox,ui->pagePrincipale->findChildren<AbulEduMessageBoxV1*>()){
        mbox->close();
    }
    foreach(AbulEduFlatBoutonV1* enfant,ui->frmIcones->findChildren<AbulEduFlatBoutonV1 *>())
    {
        if(enfant->whatsThis() != "verification") {
            enfant->setEnabled(true);
        }
    }
    AbulEduMessageBoxV1* msg = new AbulEduMessageBoxV1(trUtf8("Pas trouvé ?"),m_messageEnd,true, ui->pagePrincipale);
    msg->show();
    m_isCanceled = false;
}

void MainWindow::slotChangeLangue(QString lang)
{
    qApp->removeTranslator(&qtTranslator);
    qApp->removeTranslator(&myappTranslator);

    //Un 1er qtranslator pour prendre les traductions QT Systeme
    //c'est d'ailleur grace a ca qu'on est en RTL
    qtTranslator.load("qt_" + lang, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    qApp->installTranslator(&qtTranslator);

    //foreach (QWidget *widget, QApplication::allWidgets()) widget->setLayoutDirection(Qt::RightToLeft);
    //Et un second qtranslator pour les traductions specifiques du
    //logiciel
    myappTranslator.load("leterrier-cibler_" + lang, "lang");
    qApp->installTranslator(&myappTranslator);
    ui->retranslateUi(this);
}

void MainWindow::on_btnJoker_clicked()
{
    ui->frmFondJoker->setVisible(true);
    ui->frmFondJoker->raise();
    setAllButtonsEnabled(false);
}

void MainWindow::setAllButtonsEnabled(bool trueFalse)
{
    foreach(AbulEduFlatBoutonV1* enfant,ui->frmIcones->findChildren<AbulEduFlatBoutonV1 *>())
    {
        if(enfant->whatsThis() != "verification")
            enfant->setEnabled(trueFalse);
    }
    foreach(AbulEduFlatBoutonV1* enfant,ui->frmAnswers->findChildren<AbulEduFlatBoutonV1 *>())
    {
        enfant->setEnabled(trueFalse);
    }
    foreach(AbulEduFlatBoutonV1* enfant,ui->frmAireDeJeu->findChildren<AbulEduFlatBoutonV1 *>())
    {
        enfant->setEnabled(trueFalse);
    }
}

void MainWindow::on_btnDebut_clicked()
{
    foreach(AbulEduMessageBoxV1* mbox,ui->pagePrincipale->findChildren<AbulEduMessageBoxV1*>()){
        mbox->close();
    }
    int prems = 0;
    if(niveau == CALCULEXPERT){
        ui->btnRep1->setText("");
        ui->btnRep2->setText("");
        foreach(AbulEduFlatBoutonV1* btn,ui->frmAireDeJeu->findChildren<AbulEduFlatBoutonV1*>()){
            btn->setEnabled(true);
            btn->setFont(fontBIG);
        }
    }
    else {
        if(nomBtnRep.size() > 0 && (niveau == SURCOMPTAGE || niveau == CALCUL)){
            prems = 1;
        }
        for(int i = prems;i < nomBtnRep.size();i++)
        {
            if(!nomBtnRep[i]->text().isEmpty())
            {
                int v = nomBtnRep[i]->text().toInt();
                nomBtnRep[i]->setText(QString());
                nomBtnNbre[v]->setEnabled(true);
                nomBtnNbre[v]->setFont(fontBIG);
            }
        }
    }
}

void MainWindow::on_btnAide_clicked()
{
    foreach(AbulEduMessageBoxV1* mbox,ui->pagePrincipale->findChildren<AbulEduMessageBoxV1*>()){
        mbox->close();
    }
    AbulEduMessageBoxV1* msg = new AbulEduMessageBoxV1(trUtf8("Coup de pouce !"),m_messageAide,true, ui->pagePrincipale);
    msg->setWink();
    msg->show();
}

void MainWindow::on_abeMenuFeuilleBtnHelp_clicked()
{
    ui->stackedWidget->abeStackedWidgetSlideInWidget(ui->pageAbout);
}

void MainWindow::slotMainWindowShowMainPage()
{
    ui->stackedWidget->abeStackedWidgetSlideInWidget(ui->pagePrincipale);
}

void MainWindow::on_btnTarget_clicked()
{
    on_abeMenuFeuilleBtnNew_clicked();
}
