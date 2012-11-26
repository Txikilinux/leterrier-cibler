#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QPushButton>
#include <tete.h>
#include "abuleduaproposv0.h"
 #include "abuleduexercicev0.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public AbulEduExerciceV0 {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

    /**
      fontes utilisées
    */
    QFont fontBIG; // 50
    QFont fontMEDIUM; // 25
    QFont fontMINUS; //10

    /**
      débutant : nombres de 8 à 13
      avec joker : idem
      surcomptage : nombres de 6 à 24, un grand nombre donné
      calcul : nombres de 6 à 24, un petit nombre est donné
    */
    int niveau;
    int FIXE, DEBUTANT , JOKER, SURCOMPTAGE, CALCUL;
    /**
      nombre de têtes = nombre d'exercices par niveau
      */
    int MAXTETES; // 3 àu 4 têtes
    /**
      nombre d'erreurs
        pour un exercice
        cumulées sur un niveau
      */
    int nErreurs;
    int cumulErreurs;
    /**
      nombre d'exercices réalisés sur un niveau
      permet de changer de niveau si > MAXTETES
      */
    int nExercice;

    QList <QPushButton *> nomBtnNbre;
    QList <QPushButton *> nomBtnRep;
    int nbreCible, nbreDonne; // la cible et le nombre donné si niveau = SURCOMPTAGE ou CALCUL
    int nbreChoisi;

    QList <int> nbresChoisis;
    QList <Tete *> lstTetes;

    void initNbreCible();
    void _joker();
    void _btnNbre(int n);
    void _btnRep(int n);
    void verifier(int somme);
    /**
      gerer l'affichage du joker
      */
    void gererJoker();
    QString abeEvaluation(); // renvoie a,b,c,d ou z en fonction du niveau, #erreurs, etc.

private slots:
    void on_btnQuitter_clicked();
    void on_cboxJoker_activated(int index);
    void on_actionProposerCible_triggered();
    void on_actionDebutant_triggered();
    void on_actionJoker_triggered();
    void on_actionSurcomptage_triggered();
    void on_actionCalcul_triggered();
    void _niveau(int n);

    void on_btnNouveau_clicked();
    void on_btnRep0_clicked();
    void on_btnRep1_clicked();
    void on_btnRep2_clicked();

    void on_btnNbre1_clicked();
    void on_btnNbre2_clicked();
    void on_btnNbre3_clicked();
    void on_btnNbre4_clicked();
    void on_btnNbre5_clicked();
    void on_btnNbre6_clicked();
    void on_btnNbre7_clicked();
    void on_btnNbre8_clicked();
    void on_btnNbre9_clicked();

    void on_action_Journal_de_mes_activit_s_triggered();
    void on_action_Changer_d_utilisateur_triggered();
};

#endif // MAINWINDOW_H
