#ifndef FENPRINCIPAL_H
#define FENPRINCIPAL_H

#include <QtWidgets>
#include <QWebView>
#include <QtGui>
#include <QtWebKit>



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

private:
    QTabWidget *m_listeOnglets;

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
    QAction *m_go;

    QLineEdit *m_barreAdresse;
    QProgressBar *m_progLoading;
};

#endif // FENPRINCIPAL_H
