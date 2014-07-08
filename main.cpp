#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include "FenPrincipal.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Traduction des chaînes prédéfinies par Qt dans notre langue
    QString locale = QLocale::system().name();
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);

    // Ouverture de la fenêtre principale du navigateur
    FenPrincipal fenetre;
    fenetre.show();


    return app.exec();

}
