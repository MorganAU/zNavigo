#include <QApplication>
#include <QtWidgets>
#include "FenPrincipal.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    FenPrincipal fenetre;
    fenetre.show();

    return app.exec();

}
