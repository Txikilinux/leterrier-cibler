#include "tete.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
//#include <QLocale>

//bool isIn(int i, QList<int> s);
int rechercherVide(QList <QPushButton *> s);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fontBIG.setPointSize(50);
    fontMEDIUM.setPointSize(18);
    fontMINUS.setPointSize(10);

     DEBUTANT = 0;
     JOKER = 1;
     SURCOMPTAGE = 2;
     CALCUL = 3;
     MAXTETES = 3;

    QRegExp nomNbreRegExp("btnNbre");
    nomBtnNbre = ui->centralWidget->findChildren <QPushButton *> (nomNbreRegExp);
    //qDebug() << nomBtnNbre;

    QRegExp nomRepRegExp("btnRep");
    nomBtnRep = ui->centralWidget->findChildren <QPushButton *> (nomRepRegExp);
    //qDebug() << nomBtnRep;

    for (int i = 0; i < MAXTETES; i++) {
        Tete * tete = new Tete(ui->centralWidget, 15+65*i, 295);
        tete->affiche();
        lstTetes.append(tete);
    }

    niveau = DEBUTANT;
    reussite = 0;
    nbreCible =-1;
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

void MainWindow::initNbreCible() {

    // effacer l'affichage
    ui->lblAffiche->clear();

    // afficher les btnNbre (je conserve 0 par commodité)
    for (int i = 0; i < 10; i++) {
        nomBtnNbre[i]->setStyleSheet("color :yellow");
        nomBtnNbre[i]->setFont(fontBIG);
        nomBtnNbre[i]->setDisabled(false);
        nomBtnNbre[i]->setProperty("text", QString::number(i));
    }
    // joker
    nomBtnNbre[0]->hide();
    if (niveau == DEBUTANT)
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
    if (niveau == DEBUTANT) {
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
}

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
}

int rechercherVide(QList <QPushButton *> s) {
    for (int i = 0; i < 3; i++) {
        if (s[i]->text() == "") return i;
    }
    return -1;
}

void MainWindow::verifier(int somme) {
    if (somme == nbreCible) {
        ui->lblAffiche->setText(trUtf8("Bravo,\n  Tu peux maintenant\n  prendre une nouvelle cible."));
        if (reussite < MAXTETES) lstTetes[reussite]->affiche(0);
    } else {
        ui->lblAffiche->setText(trUtf8("Erreur, \n  Je te demande\n  de corriger..."));
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
    reussite++;
    if (reussite >= MAXTETES && niveau < CALCUL)
       _niveau(niveau+1);
    else
        initNbreCible();
}

void MainWindow::on_actionDebutant_triggered() { _niveau(DEBUTANT); }
void MainWindow::on_actionJoker_triggered() { _niveau(JOKER); }
void MainWindow::on_actionSurcomptage_triggered() { _niveau(SURCOMPTAGE); }
void MainWindow::on_actionCalcul_triggered() { _niveau(CALCUL); }

void MainWindow::_niveau(int n) {
    niveau = n;
    reussite = 0;
    for (int i = 0; i < MAXTETES; i++)
        lstTetes[i]->affiche(-1);
    initNbreCible();
}

void MainWindow::on_cboxJoker_activated(int index)
{
    if (index > 0) _btnNbre(index);
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
