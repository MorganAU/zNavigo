#include "FenPrincipal.h"

FenPrincipal::FenPrincipal()
{
    //Génération des widgets de la fenêtre principale
    creerActions();
    creerMenus();
    creerBarreDOutils();
    creerBarreEtat();

    //Génération des onglets et chargement de la page d'accueil
    m_listeOnglets = new QTabWidget;
    m_listeOnglets->addTab(creerOngletPageWeb(tr("http://www.google.fr")), tr("(Nouvelle page)"));
    connect(m_listeOnglets, SIGNAL(currentChanged(int)), this, SLOT(changementOnglet(int)));
    setCentralWidget(m_listeOnglets);

    //Options
    chargerOptions();

    //Définition de quelques propriétés de la fenêtre
    setMinimumSize(500, 350);
    setWindowIcon(QIcon("Icones/bateau.png"));
    setWindowTitle("zNavigo");    
}

void FenPrincipal::creerActions()
{
    m_ouvrir = new QAction(QIcon("Icones/new.png"),tr("Ouvrir un &nouvel onglet"), this);
    m_ouvrir->setShortcut(tr("Ctrl+T"));
    connect(m_ouvrir, SIGNAL(triggered()), this, SLOT(nouvelOnglet()));

    m_fermer = new QAction(QIcon("Icones/delete.png"),tr("&Fermer l'onglet"), this);
    m_fermer->setShortcut(tr("Ctrl+W"));
    connect(m_fermer, SIGNAL(triggered()), this, SLOT(fermerOnglet()));

    m_quitter = new QAction(QIcon("Icones/quitter.png"), tr("&Quitter ZNavigo"), this);
    m_quitter->setShortcut(tr("Ctrl+Q"));
    connect(m_quitter, SIGNAL(triggered()), qApp, SLOT(quit()));


    m_pagePrecedente = new QAction(QIcon("Icones/prec.png"), tr("Page &précédente"), this);
    m_pagePrecedente->setShortcut(QKeySequence::Back);
    connect(m_pagePrecedente, SIGNAL(triggered()), this, SLOT(precedente()));

    m_pageSuivante = new QAction(QIcon("Icones/suiv.png"), tr("Page &suivante"), this);
    m_pageSuivante->setShortcut(QKeySequence::Forward);
    connect(m_pageSuivante, SIGNAL(triggered()), this, SLOT(suivante()));

    m_stopLoad = new QAction(QIcon("Icones/stop.png"), "Ar&rêter le chargement", this);
    connect(m_stopLoad, SIGNAL(triggered()), this, SLOT(stop()));

    m_actualiserPage = new QAction(QIcon("Icones/actu.png"), tr("&Actualiser la page"), this);
    m_actualiserPage->setShortcut(QKeySequence::Refresh);
    connect(m_actualiserPage, SIGNAL(triggered()), this, SLOT(actualiser()));

    m_pageAccueil = new QAction(QIcon("Icones/home.png"), tr("Page d'a&ccueil"), this);
    connect(m_pageAccueil, SIGNAL(triggered()), this, SLOT(accueil()));

    m_rechercher = new QAction(QIcon("Icones/Rechercher.png"), tr("Rechercher"), this);
    m_rechercher->setShortcut(tr("Ctrl+F"));
    connect(m_rechercher, SIGNAL(triggered()), this, SLOT(menuRechercher()));

    m_actionFermerRecherche = new QAction(QIcon("Icones/fermerRecherche.png"), "", this);
    connect(m_actionFermerRecherche, SIGNAL(triggered()), this, SLOT(fermerRecherche()));

    m_go = new QAction(QIcon("Icones/go.png"), tr("A&ller à"), this);
    connect(m_go, SIGNAL(triggered()), this, SLOT(chargerPage()));


    m_taillePoliceDefaut = new QAction(QIcon("Icones/taillePolice.png"), tr("Changer la taille police"), this);
    connect(m_taillePoliceDefaut, SIGNAL(triggered()), this, SLOT(optionTaille()));

    m_urlAccueilDefaut = new QAction(QIcon("Icones/optionUrl.png"), tr("Changer la paged'accueil"), this);
    connect(m_urlAccueilDefaut, SIGNAL(triggered()), this, SLOT(optionUrl()));


    m_aPropos = new QAction(tr("À pr&opos..."), this);
    m_aPropos->setShortcut(QKeySequence::HelpContents);
    connect(m_aPropos, SIGNAL(triggered()), this, SLOT(aPropos()));

    m_aProposQt = new QAction(tr("À propos de Q&t..."), this);
    connect(m_aProposQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void FenPrincipal::creerMenus()
{
    QMenu *menuFichier = menuBar()->addMenu(tr("F&ichier"));

    menuFichier->addAction(m_ouvrir);
    menuFichier->addAction(m_fermer);
    menuFichier->addSeparator();
    menuFichier->addAction(m_quitter);

    QMenu *menuNavigation = menuBar()->addMenu(tr("Na&vigation"));

    menuNavigation->addAction(m_pagePrecedente);
    menuNavigation->addAction(m_pageSuivante);
    menuNavigation->addAction(m_stopLoad);
    menuNavigation->addAction(m_actualiserPage);
    menuNavigation->addAction(m_pageAccueil);
    menuNavigation->addSeparator();
    menuNavigation->addAction(m_rechercher);

    m_menuHistorique = menuBar()->addMenu(tr("Historiq&ue"));
    connect(m_menuHistorique, SIGNAL(aboutToShow()), this, SLOT(creerHistorique()));
    connect(m_menuHistorique, SIGNAL(triggered(QAction*)), this, SLOT(afficherHistorique(QAction*)));

    QMenu *menuOptions = menuBar()->addMenu(tr("Options"));

    menuOptions->addAction(m_taillePoliceDefaut);
    menuOptions->addAction(m_urlAccueilDefaut);

    QMenu *menuAide = menuBar()->addMenu(tr("&?"));

    menuAide->addAction(m_aPropos);
    menuAide->addAction(m_aProposQt);

}

void FenPrincipal::creerBarreDOutils()
{
    m_barreAdresse = new QLineEdit;
    connect(m_barreAdresse, SIGNAL(returnPressed()), this, SLOT(chargerPage()));
    m_barreRecherche = new QLineEdit;
    connect(m_barreRecherche, SIGNAL(returnPressed()), this, SLOT(lancerRecherche()));
    m_choixTaille = new QComboBox;

    QList<QString> items;
    for ( int i = 6; i <= 32; ++i )
    {
        QString a;
        a.setNum(i);

        items.append(a);
    }
    m_choixTaille->addItems(items);
    connect(m_choixTaille, SIGNAL(currentIndexChanged(int)), this, SLOT(tailleChoisi()));

    m_choixUrl = new QLineEdit;


    QToolBar *toolBarNavigation = addToolBar(tr("Navigation"));

    toolBarNavigation->addAction(m_pagePrecedente);
    toolBarNavigation->addAction(m_pageSuivante);
    toolBarNavigation->addAction(m_stopLoad);
    toolBarNavigation->addAction(m_actualiserPage);
    toolBarNavigation->addAction(m_pageAccueil);
    toolBarNavigation->addWidget(m_barreAdresse);
    toolBarNavigation->addAction(m_go);
    toolBarNavigation->addAction(m_rechercher);


    m_cacherRecherche = new QAction(this);
    m_cacherRecherche = toolBarNavigation->addWidget(m_barreRecherche);
    m_cacherRecherche->setVisible(false);

    toolBarNavigation->addAction(m_actionFermerRecherche);
    m_actionFermerRecherche->setVisible(false);

    m_cacherChoixTaille = new QAction(this);
    m_cacherChoixTaille = toolBarNavigation->addWidget(m_choixTaille);
    m_cacherChoixTaille->setVisible(false);

    m_cacherUrlHome = new QAction(this);
    m_cacherUrlHome = toolBarNavigation->addWidget(m_choixUrl);
    m_cacherUrlHome->setVisible(false);
}

void FenPrincipal::creerBarreEtat()
{
    m_progLoading = new QProgressBar(this);
    m_progLoading->setVisible(false);
    m_progLoading->setMaximumHeight(14);
    statusBar()->addWidget(m_progLoading, 1);
}




//Autres méthodes


QWidget *FenPrincipal::creerOngletPageWeb(QString url)
{
    QWidget *pageOnglet = new QWidget;
    QWebView *pageWeb = new QWebView;

    pageWeb->settings()->setAttribute(QWebSettings::PluginsEnabled,true);
    pageWeb->settings()->setAttribute(QWebSettings::JavascriptEnabled,true);
    pageWeb->settings()->setAttribute(QWebSettings::JavaEnabled,true);
    pageWeb->settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows,true);
    pageWeb->settings()->setFontSize(QWebSettings::MinimumFontSize, m_choixTaille->currentText().toInt());


    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(pageWeb);
    pageOnglet->setLayout(layout);

    if(url.isEmpty())
    {
        pageWeb->load(QUrl(tr("html/page_blanche.html")));
    }
    else
    {
        if(url.left(7) != "http://")
        {
            url = "http://" + url;
        }
        pageWeb->load(QUrl(url));
    }

    //Gestion des signaux envoyés par la page web
    connect(pageWeb, SIGNAL(titleChanged(QString)), this, SLOT(changementTitre(QString)));
    connect(pageWeb, SIGNAL(urlChanged(QUrl)), this, SLOT(changementUrl(QUrl)));
    connect(pageWeb, SIGNAL(loadStarted()), this, SLOT(chargementDebut()));
    connect(pageWeb, SIGNAL(loadProgress(int)), this, SLOT(chargementEnCours(int)));
    connect(pageWeb, SIGNAL(loadFinished(bool)), this, SLOT(chargementTermine(bool)));

    return pageOnglet;
}

QWebView *FenPrincipal::pageActuelle()
{
    return m_listeOnglets->currentWidget()->findChild<QWebView *>();
}

QWebHistory *FenPrincipal::historique()
{
    return pageActuelle()->page()->history();
}

void FenPrincipal::closeEvent(QCloseEvent *event)
{
    QSettings settings("Options.ini", QSettings::IniFormat);
    settings.setValue("Police", m_choixTaille->currentIndex());

    event->accept();
}

void FenPrincipal::chargerOptions()
{ 
    QSettings settings("Options.ini", QSettings::IniFormat);
    m_choixTaille->setCurrentIndex(settings.value("Police", 6).toInt());
}

//Slots


void FenPrincipal::precedente()
{
    pageActuelle()->back();
}

void FenPrincipal::suivante()
{
    pageActuelle()->forward();
}

void FenPrincipal::accueil()
{
    pageActuelle()->load(QUrl(tr("http://www.google.fr")));
}

void FenPrincipal::stop()
{
    pageActuelle()->stop();
}

void FenPrincipal::actualiser()
{
    pageActuelle()->reload();
}

void FenPrincipal::aPropos()
{
    QMessageBox::information(this, tr("À propos..."), tr("zNavigo est un projet réalisé pour illustrer les tutoriels C++ du <a href=\"http://www.siteduzero.com\">Site du Zéro</a>.<br />Les images de ce programme ont été créées par <a href=\"http://www.everaldo.com\">Everaldo Coelho</a>"));
}

void FenPrincipal::nouvelOnglet()
{
    int indexNouvelOnglet = m_listeOnglets->addTab(creerOngletPageWeb(tr("http://google.fr")), tr("Nouvelle page"));
    m_listeOnglets->setCurrentIndex(indexNouvelOnglet);

    m_barreAdresse->setText("");
    m_barreAdresse->setFocus(Qt::OtherFocusReason);
}

void FenPrincipal::fermerOnglet()
{
    //On ne doit pas fermer le dernier onglet
    if(m_listeOnglets->count() > 1)
    {
        m_listeOnglets->removeTab(m_listeOnglets->currentIndex());
    }
    else
    {
        QMessageBox::critical(this, tr("Erreur"), tr("Il faut au moins un onglet !"));
    }
}

void FenPrincipal::chargerPage()
{
    QString url = m_barreAdresse->text();

    //On rajoute le "http://" s'il n'est pas déjà dans l'adresse
    if(url.left(7) != "http://")
    {
        url = "http://" + url;
        m_barreAdresse->setText(url);
    }
    pageActuelle()->load(QUrl(url));
}

void FenPrincipal::changementOnglet(int index)
{
    changementTitre(pageActuelle()->title());
    changementUrl(pageActuelle()->url());
}

void FenPrincipal::changementTitre(const QString &titreComplet)
{
    QString titreCourt = titreComplet;

    //On tronque le titre pour éviter des onglets trop large
    if(titreComplet.size() > 40)
    {
        titreCourt = titreComplet.left(40) + "...";
    }

    setWindowTitle(titreCourt + " - " + tr("ZNavigo"));
    m_listeOnglets->setTabText(m_listeOnglets->currentIndex(), titreCourt);
}

void FenPrincipal::changementUrl(const QUrl &url)
{
    if(url.toString() != tr("html/page_blanche.html"))
    {
        m_barreAdresse->setText(url.toString());
    }
}

void FenPrincipal::chargementDebut()
{
    m_progLoading->setVisible(true);
}

void FenPrincipal::chargementEnCours(int pourcentage)
{
    m_progLoading->setValue(pourcentage);
}

void FenPrincipal::chargementTermine(bool ok)
{
    m_progLoading->setVisible(false);
    statusBar()->showMessage(tr("Prêt"), 2000);
}

void FenPrincipal::menuRechercher()
{
    m_cacherRecherche->setVisible(true);
    m_actionFermerRecherche->setVisible(true);
}

void FenPrincipal::lancerRecherche()
{
    pageActuelle()->findText(m_barreRecherche->text());
}

void FenPrincipal::fermerRecherche()
{
        m_cacherRecherche->setVisible(false);
        m_actionFermerRecherche->setVisible(false);
}

void FenPrincipal::optionTaille()
{
    m_cacherChoixTaille->setVisible(true);
}

void FenPrincipal::tailleChoisi()
{
    for ( int i = 0 ; i < m_listeOnglets->count() ; i++ )
    {
        m_listeOnglets->widget(i)->findChild<QWebView *>()->settings()->setFontSize(QWebSettings::MinimumFontSize, m_choixTaille->currentText().toInt());
    }
    m_cacherChoixTaille->setVisible(false);
}

void FenPrincipal::optionUrl()
{
    m_cacherUrlHome->setVisible(true);
}

void FenPrincipal::urlChoisi()
{

}

void FenPrincipal::creerHistorique()
{
    //On efface le contenu précédent du menu
    m_menuHistorique->clear();
    //On récupère la liste complète
    QList<QWebHistoryItem> liste = historique()->items();
    //Et la position actuelle dans la liste
    int indexActuel = historique()->currentItemIndex();

    //On limite les éléments affichés de l'historique
    int debut = qMax(indexActuel - 10, 0);
    int fin = qMin(indexActuel + 5, liste.size());
    for(int i = debut ; i < fin ; ++i)
    {
        QWebHistoryItem item = liste[i];
        QString titre = item.title();
        if(titre.isEmpty())
        {
            titre = item.url().toString();
        }

        //

        QAction *action = m_menuHistorique->addAction(titre);
        action->setData(i);

        if(i == indexActuel)
        {
            QFont font = action->font();
            font.setBold(true);
            action->setFont(font);
        }
    }
}

void FenPrincipal::afficherHistorique(QAction *action)
{
    QWebHistory *history = historique();

    bool ok = false;
    int index = action->data().toInt(&ok);
    if(ok)
    {
        history->goToItem(history->itemAt(index));
    }
}
