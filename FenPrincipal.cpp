#include "FenPrincipal.h"

FenPrincipal::FenPrincipal()
{
    creerMenus();
    creerActions();
}
 void FenPrincipal::creerMenus()
 {
     m_menuPages = new QMenu;
     m_menuPages = menuBar()->addMenu("&Page");
 }

 void FenPrincipal::creerActions()
 {
     m_pagePrecedente = new QAction("Page pré&cédente", this);
     m_menuPages->addAction(m_pagePrecedente);
 }
