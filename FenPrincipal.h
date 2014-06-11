#ifndef FENPRINCIPAL_H
#define FENPRINCIPAL_H

#include <QtWidgets>
#include <QWebView>



class FenPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    FenPrincipal();
    void creerActions();
    void creerMenus();
    void creerBarreDOutils();

private:
    QMenu *m_fichier;
    QAction *m_enregistrer;
    QAction *m_rechercher;
    QAction *m_imprimer;

    QMenu *m_navigation;
    QAction *m_pagePrecedente;
    QAction *m_pageSuivante;
    QAction *m_actualiserPage;
    QAction *m_pageAccueil;
    QAction *m_stopLoad;

    QToolBar *m_toolBarFichier;
};

#endif // FENPRINCIPAL_H
