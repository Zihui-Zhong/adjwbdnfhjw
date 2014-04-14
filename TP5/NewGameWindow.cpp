#include "NewGameWindow.h"
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QMessageBox>
#include <QFormLayout>

NewGameWindow::NewGameWindow(QWidget *parent) : QDialog(parent)
{


    QLabel * joueur1Tag = new QLabel("Joueur 1: ", parent);
    QLabel * joueur2Tag = new QLabel("Joueur 2: ", parent);
    QLabel * tempsMaxTag = new QLabel("Temps max (min): ", parent);

    QLineEdit * joueur1LE = new QLineEdit(parent);
    QLineEdit * joueur2LE = new QLineEdit(parent);

    QSpinBox * tempsMaxSB = new QSpinBox(parent);
    tempsMaxSB->setMaximum(20);
    tempsMaxSB->setMinimum(1);

    QPushButton * debuterPartieBtn = new QPushButton("Débuter la partie", parent);
    QPushButton * annulerBtn = new QPushButton("Annuler", parent);


    QFormLayout * layout = new QFormLayout;
    layout->addRow(joueur1Tag, joueur1LE);
    layout->addRow(joueur2Tag, joueur2LE);
    layout->addRow(tempsMaxTag, tempsMaxSB);
    layout->addRow(debuterPartieBtn, annulerBtn);

    setLayout(layout);

    show();
    setWindowTitle(tr("Nouvelle Partie"));
}

