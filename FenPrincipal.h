#ifndef FENPRINCIPAL_H
#define FENPRINCIPAL_H

#include <QtWidgets>
#include <QWebView>
#include <QtGui>
#include <QtWebKit>
#include <QSettings>
#include "FenOption.h"



class FenPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    FenPrincipal();


private:
    void creerActions();
    void creerMenus();
    void creerBarreDOutils();
    void creerBarreEtat();
    QWidget *creerOngletPageWeb(QString url);
    QWebView *pageActuelle();
    QWebHistory *historique();
    void chargerOptions();

private slots:
    void precedente();
    void suivante();
    void accueil();
    void stop();
    void actualiser();

    void aPropos();
    void nouvelOnglet();
    void fermerOnglet();
    void chargerPage();
    void changementOnglet(int index);

    void changementTitre(const QString & titreComplet);
    void changementUrl(const QUrl & url);
    void chargementDebut();
    void chargementEnCours(int pourcentage);
    void chargementTermine(bool ok);

    void menuRechercher();
    void lancerRecherche();
    void fermerRecherche();

    void ouvrirFenOption();
    void appliquerTaille(QString tailleFinal);

    void creerHistorique();
    void afficherHistorique(QAction*action);

private:
    QTabWidget *m_listeOnglets;
    QMenu *m_menuHistorique;

    FenOption *m_fenOption;

    QAction *m_ouvrir;
    QAction *m_fermer;
    QAction *m_quitter;
    QAction *m_aPropos;
    QAction *m_aProposQt;
    QAction *m_pagePrecedente;
    QAction *m_pageSuivante;
    QAction *m_stopLoad;
    QAction *m_actualiserPage;
    QAction *m_pageAccueil;
    QAction *m_rechercher;
    QAction *m_go;

    QAction *m_parametres;
    QString m_urlParDefaut;

    QLineEdit *m_barreAdresse;

    QLineEdit *m_barreRecherche;
    QAction *m_cacherRecherche;
    QAction *m_actionFermerRecherche;

    QProgressBar *m_progLoading;
};

#endif // FENPRINCIPAL_H
