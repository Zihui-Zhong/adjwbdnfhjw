#include "NewGameWindow.h"
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QMessageBox>
#include <QFormLayout>
#include <QCoreApplication>

NewGameWindow::NewGameWindow(QWidget *parent) : QDialog(parent)
{


    QLabel * joueur1Tag = new QLabel("Joueur 1: ", parent);
    QLabel * joueur2Tag = new QLabel("Joueur 2: ", parent);
    QLabel * tempsMaxTag = new QLabel("Temps max (min): ", parent);

    joueur1LE = new QLineEdit(parent);
    joueur2LE = new QLineEdit(parent);

    tempsMaxSB = new QSpinBox(parent);
    tempsMaxSB->setMaximum(20);
    tempsMaxSB->setMinimum(1);

    QPushButton * debuterPartieBtn = new QPushButton("Débuter la partie", parent);
    QPushButton * annulerBtn = new QPushButton("Annuler", parent);

    connect(annulerBtn, SIGNAL(clicked()),this, SLOT(quitClicked()));
    connect(debuterPartieBtn, SIGNAL(clicked()),this, SLOT(debuterClicked()));

    QFormLayout * layout = new QFormLayout;
    layout->addRow(joueur1Tag, joueur1LE);
    layout->addRow(joueur2Tag, joueur2LE);
    layout->addRow(tempsMaxTag, tempsMaxSB);
    layout->addRow(debuterPartieBtn, annulerBtn);

    setLayout(layout);

    show();
    setWindowTitle(tr("Nouvelle Partie"));
}

void NewGameWindow::quitClicked()
{
    this->close();
}

void NewGameWindow::debuterClicked()
{
    emit debut(joueur1LE->text(),joueur2LE->text(),tempsMaxSB->value());

    this->close();
}
