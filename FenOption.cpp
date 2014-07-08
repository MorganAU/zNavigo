#include "FenOption.h"
#include "FenPrincipal.h"

FenOption::FenOption(int size, QString url, QWidget *parent = 0) : QDialog(parent)
{
    //Paramètres de la fenêtre
    setFixedSize(800, 800);
    //Taille de la police
    QString tailleActuelle;
    tailleActuelle.setNum(size);
    m_choixTaille = new QComboBox;
    QList<QString> items;
    for(int i = 12; i<= 32; i++)
    {
        QString a;
        a.setNum(i);
        items.append(a);
    }
    m_choixTaille->addItems(items);
    m_choixTaille->setCurrentText(tailleActuelle);

    //Page d'accueil
    m_choixUrl = new QLineEdit(url);


    //Boutons
    QPushButton *m_appliquer = new QPushButton("Appliquer");
    m_appliquer->setObjectName("appliquer");
    QPushButton *enregistrer = new QPushButton("Enregistrer");
    QPushButton *defaut = new QPushButton("Défaut");
    defaut->setObjectName("defaut");

    //Dispositionnement des options
    m_listeOptions = new QFormLayout;
    m_listeOptions->addRow("Taille de la police", m_choixTaille);
    m_listeOptions->addRow("Page d'accueil (nécessite de redémarrer)", m_choixUrl);

    //Différents layouts
    QHBoxLayout *layoutBoutons = new QHBoxLayout;
    layoutBoutons->addWidget(m_appliquer);
    layoutBoutons->addWidget(enregistrer);
    layoutBoutons->addWidget(defaut);

    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->addLayout(m_listeOptions);
    layoutPrincipal->addLayout(layoutBoutons);

    //Connections
    QMetaObject::connectSlotsByName(this);
    connect(enregistrer, SIGNAL(clicked()), this, SLOT(enregistrerOptions()));

}



    //Slots
void FenOption::on_appliquer_clicked()
{
    emit tailleChoisi(m_choixTaille->currentText());
    if(m_choixUrl->text().left(7) != "http://")
    {
        m_choixUrl->setText("http://" + m_choixUrl->text());
    }
    emit urlChoisi(m_choixUrl->text());
}

void FenOption::on_defaut_clicked()
{
    m_choixTaille->setCurrentText("12");
    m_choixUrl->setText("http://www.google.fr");
    emit tailleChoisi(m_choixTaille->currentText());
    emit urlChoisi(m_choixUrl->text());
}

void FenOption::enregistrerOptions()
{
    QSettings settings("Options.ini", QSettings::IniFormat);
    settings.setValue("Police", m_choixTaille->currentText());
    settings.setValue("Accueil", m_choixUrl->text());

    bool ok = false;
    QMessageBox::information(this, "Sauvegarde", "Vos options ont été sauvegardées avec succés.");
    if(ok = true)
    {
        close();
    }
}



