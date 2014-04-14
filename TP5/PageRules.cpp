#include "PageRules.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>


PageRules::PageRules(QWidget *parent) : QWidget(parent)
{

    QLabel * lbl = new QLabel("Règlement:\n\n"
                             "Le jeu de Puissance 4 est simple,\n"
                             "il se joue à 2 joueurs sur une grille 7\n"
                             "colonnes par 6 rangées. À chaque tour,\n"
                             "un joueur vient placer un pion dans une\n"
                             "des 7 colonnes et celui-ci vient tomber\n"
                             "tout en bas. Le but du jeu est de faire\n"
                             "une suite de 4 pions, soit à l'horizontale,\n"
                             "à la verticale ou dans l'une des deux\n"
                             "diagonale. Le premier qui arrive à faire\n"
                             "une suite gagne la partie.", parent);


    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(lbl);

    setLayout(layout);


}
