#include "digicode.h"
#include "ui_digicode.h"

Digicode::Digicode(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Digicode)
    , NB_TOUCHES(12)
{
    ui->setupUi(this);
    int colonne=0, ligne=0;
    grille = new QGridLayout(this);
    afficheur = new QLineEdit(this);
    afficheur->setReadOnly(true);
    afficheur->setAlignment(Qt::AlignRight);
    afficheur->setEchoMode(QLineEdit::Password);
    afficheur->setMinimumHeight(80);
    grille->addWidget(afficheur,ligne,colonne,1,3);
    // Création du clavier
    const QString TableDesSymboles[4][3] = {{"7","8","9"},{"4","5","6"},
                                            {"1","2","3"},{"On","0","Ok"}};

    int i = 0;

    for (ligne = 0; ligne < 4; ++ligne) {
        for (colonne = 0; colonne < 3; ++colonne) {
            touches[i] = new QPushButton(this);
            touches[i]->setText(TableDesSymboles[ligne][colonne]);
            touches[i]->setMinimumHeight(80);
            touches[i]->setMinimumWidth(80);
            touches[i]->setMaximumHeight(80);
            touches[i]->setMaximumWidth(80);
            grille->addWidget(touches[i], ligne + 1, colonne);
            i++;
        }

    }

    this->setLayout(grille);

    QList<QPushButton*> allButtons = this->findChildren<QPushButton*>();
    foreach(QPushButton* button, allButtons) {
        connect(button, &QPushButton::clicked, this, &Digicode::onQPushButtonClicked);
    }

    tempoGache = new QTimer(this);
    tempoGache->setSingleShot(true);
    connect(tempoGache, &QTimer::timeout, this, &Digicode::onTimerTempoGache_timeout);

    codeSecret = "1234";

    laPorte = new Porte(this);
    laPorte->show();

}

Digicode::~Digicode()
{
    delete ui;
}

void Digicode::onQPushButtonClicked()
{
    QPushButton *touche;
    touche=qobject_cast<QPushButton*>(sender());

    /**
     * @brief expression
     * recupere le texte de l'afficheur
     */
    QString expression = afficheur->text();

    QString texteTouche;
    texteTouche = touche->text();

    if (texteTouche != "Ok" && texteTouche != "On") {
        afficheur->setText(expression + texteTouche);
        code = code + texteTouche;
    }

    if (texteTouche == "Ok") {
        if (code == codeSecret) {
            QMessageBox::information(this, "Digicode", "la porte est déverrouillee");
            laPorte->Deverrouiller();
            tempoGache->start(3000);
        } else {
            QMessageBox::information(this, "Digicode", "code Faux");
        }
    }

    if (texteTouche == "On") {
        code.clear();
        afficheur->clear();
    }


}

void Digicode::onTimerTempoGache_timeout()
{
    laPorte->Verrouiller();
}
