#ifndef FENOPTION_H
#define FENOPTION_H

#include <QtWidgets>
#include <QDialog>
#include <QSettings>
#include <QWebSettings>

class FenOption : public QDialog
{
    Q_OBJECT

public:
    FenOption(int size, QString url, QWidget *parent);

private slots:
    void on_appliquer_clicked();
    void enregistrerOptions();
    void on_defaut_clicked();

signals:
    void tailleChoisi(QString);
    void urlChoisi(QString);

private:
    QFormLayout *m_listeOptions;

    QComboBox *m_choixTaille;
    QLineEdit *m_choixUrl;
    QAction *m_cacherChoixTaille;
    QAction *m_taillePoliceDefaut;
    QPushButton *m_appliquer;

};

#endif // FENOPTION_H
