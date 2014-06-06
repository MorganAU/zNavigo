#ifndef FENPRINCIPAL_H
#define FENPRINCIPAL_H

#include <QtWidgets>


class FenPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    FenPrincipal();
    void creerActions();
    void creerMenus();
    void creerBarreDOutils();

private:
    QMenu *m_menuPages;
    QAction *m_pagePrecedente;
};

#endif // FENPRINCIPAL_H
