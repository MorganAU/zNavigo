#include "FenPrincipal.h"

FenPrincipal::FenPrincipal()
{
    QWebView *pageWeb = new QWebView(this);
    pageWeb->load(QUrl("http://www.google.fr/"));
    setCentralWidget(pageWeb);
    showMaximized();

    creerActions();
    creerMenus();
    creerBarreDOutils();

}
 void FenPrincipal::creerMenus()
 {
     m_fichier = new QMenu;
     m_fichier = menuBar()->addMenu("F&ichier");
     m_fichier->addAction(m_enregistrer);
     m_fichier->addAction(m_rechercher);
     m_fichier->addAction(m_imprimer);

     m_navigation = new QMenu;
     m_navigation = menuBar()->addMenu("&Navigation");
     m_navigation->addAction(m_pageAccueil);
     m_navigation->addAction(m_pagePrecedente);
     m_navigation->addAction(m_pageSuivante);
     m_navigation->addAction(m_actualiserPage);
     m_navigation->addAction(m_stopLoad);

 }

 void FenPrincipal::creerActions()
 {
     m_enregistrer = new QAction(QIcon("Icones/save.png"),"Enregistrer la page sous...", this);
     m_rechercher = new QAction(QIcon("Icones/search.png"),"Rechercher...", this);
     m_imprimer = new QAction(QIcon("Icones/impr.png"), "Imprimer", this);

     m_pagePrecedente = new QAction(QIcon("Icones/prec.png"), "Page pré&cédente", this);
     m_pageSuivante = new QAction(QIcon("Icones/suiv.png"), "Page &suivante", this);
     m_actualiserPage = new QAction(QIcon("Icones/actu.png"),"&Actualiser la page", this);
     m_pageAccueil = new QAction(QIcon("Icones/home.png"),"&Page d'accueil", this);
     m_stopLoad = new QAction(QIcon("Icones/stop.png"), "Arrêter le chargement", this);
 }

 void FenPrincipal::creerBarreDOutils()
 {
    m_toolBarFichier = new QToolBar;
    m_toolBarFichier = addToolBar("Fichier");
    m_toolBarFichier->addAction(m_enregistrer);
    m_toolBarFichier->addAction(m_rechercher);
    m_toolBarFichier->addAction(m_imprimer);
    m_toolBarFichier->addAction(m_pagePrecedente);
    m_toolBarFichier->addAction(m_pageSuivante);
    m_toolBarFichier->addAction(m_actualiserPage);
    m_toolBarFichier->addAction(m_pageAccueil);
    m_toolBarFichier->addAction(m_stopLoad);

 }
