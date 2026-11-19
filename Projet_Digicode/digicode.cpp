#include "digicode.h"
#include "ui_digicode.h"

Digicode::Digicode(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Digicode)
    , NB_TOUCHES(16)
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

    for (int i = 0; i < NB_TOUCHES; ++i) {
        touches[i] = new QPushButton(this);
        touches[i]->setText(TableDesSymboles[i][i]);
        touches[i]->setMinimumHeight(80);
        touches[i]->setMinimumWidth(80);
        touches[i]->setMaximumHeight(80);
        touches[i]->setMaximumWidth(80);
        layout()->addWidget(touches[i]);
    }

    this->setLayout(grille);

    QList<QPushButton*> allButtons = this->findChildren<QPushButton*>();
    foreach(QPushButton* button, allButtons) {
        connect(button, &QPushButton::clicked, this, &Digicode::onQPushButtonClicked);
    }

    connect(tempoGache, &QTimer::timeout, this, &Digicode::onTimerTempoGache_timeout);
    tempoGache->setSingleShot(true);



}

Digicode::~Digicode()
{
    delete ui;
}

void Digicode::onQPushButtonClicked()
{
    QPushButton *touche;
    touche=qobject_cast<QPushButton*>(sender());

    QString code;
    QString codeSecret;

    QString texteTouche;
    texteTouche = touche->text();

    if (texteTouche != "OK" && texteTouche != "On") {
        code = code + texteTouche;
    }

    if (texteTouche == "OK") {
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
    }


}

void Digicode::onTimerTempoGache_timeout()
{
    laPorte->Verrouiller();
}
