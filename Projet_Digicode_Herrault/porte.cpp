#include "porte.h"
#include "ui_porte.h"

Porte::Porte(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Porte)
{
    ui->setupUi(this);
    Verrouiller();
}

Porte::~Porte()
{
    delete ui;
}

void Porte::Deverrouiller()
{
    ui->labelEtat->setText("La porte est déverrouillée");
    ui->labelImage->setPixmap(QPixmap(":/img/images/porte_ouverte.png"));
}

void Porte::Verrouiller()
{
    ui->labelEtat->setText("La porte est verroulliée");
    ui->labelImage->setPixmap(QPixmap(":/img/images/porte_fermee.png"));
}
