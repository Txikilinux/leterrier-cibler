#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QDesktopWidget>
#include <tete.h>
#include "abuleduaproposv0.h"
 #include "abuleduexercicev0.h"
#include "abuleduflatboutonv1.h"

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
    void paintEvent(QPaintEvent *);
#ifndef __ABULEDUTABLETTEV1__MODE__
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
#endif

private:
    Ui::MainWindow *ui;

    QTranslator qtTranslator;
    QTranslator myappTranslator;

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

    QList <AbulEduFlatBoutonV1 *> nomBtnNbre;
    QList <AbulEduFlatBoutonV1 *> nomBtnRep;
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

    /** Position de la souris pour gerer le deplacement de la fenetre */
    QPoint m_dragPosition;
    bool   m_isWindowMoving;

    /** Booléen qui détermine si on est dans la demande de solution */
    bool m_isCanceled;

    QString m_messageAide;

    QPropertyAnimation          *m_displayMotion;

private slots:
    void on_btnQuitter_clicked();
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
    void on_btnFeuille_clicked();
    void on_btnSortie_clicked();
    void on_btnNiveaux_clicked();
    void on_btnNombres_clicked();
    void on_btnNiveauAnnuler_clicked();
    void on_btnNombresFermer_clicked();
    void on_btnNiveauJaune_clicked();
    void on_btnNiveauOrange_clicked();
    void on_btnNiveauMarron_clicked();
    void on_btnNiveauNoire_clicked();
    void on_lineEditOrigine_returnPressed();

    void slotHideFrames();
    void donneReponse();
    void on_btnAbandonner_clicked();
    void slotEndSolution();

    void slotSendJoker();

    void on_btnLanguages_clicked();
    void on_btnFr_clicked();
    void on_btnEn_clicked();
    void on_btnEs_clicked();
    void on_btnIt_clicked();
    void on_btnDe_clicked();
    void on_btnOc_clicked();
    void on_btnLangueAnnuler_clicked();
    void slotChangeLangue();

    void on_btnMinimized_clicked();
    void on_btnFullScreen_clicked();
    void on_btnJoker_clicked();
    /** Permet d'un seul appel de rendre tous les boutons de l'interface actifs ou inactifs */
    void setAllButtonsEnabled(bool trueFalse);
    void on_btnDebut_clicked();
    void on_btnInformation_clicked();
    void on_btnAideFeuille_clicked();
};

#endif // MAINWINDOW_H
