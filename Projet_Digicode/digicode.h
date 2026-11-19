#ifndef DIGICODE_H
#define DIGICODE_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QMessageBox>
#include <QTimer>
#include "porte.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Digicode;
}
QT_END_NAMESPACE

class Digicode : public QMainWindow
{
    Q_OBJECT

public:
    explicit Digicode(QWidget *parent = nullptr);
    ~Digicode() override;

private slots:
    void onQPushButtonClicked();
    void onTimerTempoGache_timeout();

private:
    Ui::Digicode *ui;
    int NB_TOUCHES;
    QPushButton **touches;
    QLineEdit *afficheur;
    QGridLayout *grille;
    Porte *laPorte;
    QTimer *tempoGache;

};
#endif // DIGICODE_H
