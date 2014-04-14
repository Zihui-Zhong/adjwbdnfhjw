#include <QtGui>
#include <QApplication>

#include <QLabel>
#include <QSpinBox>
#include <QMessageBox>

#include <math.h>

#include "GamePiece.h"
#include "GameWindow.h"
#include "NewGameWindow.h"

GameWindow::GameWindow(QWidget *parent): QWidget(parent), player1Turn_(true), isGamePlaying_(false)
{
    // Grid Layout
    gridLayout_ = new QGridLayout(parent);
    gridLayout_->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    gridLayout_->setHorizontalSpacing(0);
    gridLayout_->setVerticalSpacing(0);

    // Remplir la grille de boutons
    for (int i = 0; i < 7; i ++) {
        buttons_.push_back(vector<QSharedPointer<GamePiece> >());

        for (int j = 0; j < 6; j++) {
            QSharedPointer<GamePiece> button(new GamePiece(i, j));
            connect(&(*button), SIGNAL(clicked()), this, SLOT(gridClicked()));
            gridLayout_->addWidget(&(*button), j, i);
            buttons_[i].push_back(button);
        }
    }

    // Boutons
    buttonLayout_ = new QVBoxLayout(parent);
    buttonLayout_->setAlignment(Qt::AlignBottom);

    QPushButton* newGame = new QPushButton("Nouvelle Partie", parent);

    restart_ = new QPushButton("Recommencer", parent);
    restart_->setEnabled(false);

    QPushButton* help = new QPushButton("Aide", parent);

    QPushButton* quit = new QPushButton("Quitter", parent);

    buttonLayout_->addWidget(newGame);
    buttonLayout_->addWidget(restart_);
    buttonLayout_->addWidget(help);
    buttonLayout_->addWidget(quit);

    // Connections des boutons - À FAIRE

    connect(quit, SIGNAL(clicked()),this, SLOT(quitClicked()) ) ;
    connect(newGame,SIGNAL(clicked()),this,SLOT(newGameClicked()));
    connect(restart_,SIGNAL(clicked()),this,SLOT(restartClicked()));
    maxGameTime_=1000;

    // Info Layout
    QHBoxLayout * infoLayout = new QHBoxLayout(parent);
    buttonLayout_->setAlignment(Qt::AlignLeft);

    QLabel * player1Tag = new QLabel("Joueur 1 : ", parent);
    player1name_ = new QLabel("joueur1",parent);

    QLabel * player2Tag = new QLabel("Joueur 2 : ", parent);
    player2name_ = new QLabel("joueur2",parent);

    QLabel * timerLabel = new QLabel("Temps restant : ", parent);
    timeLeft_ = new QLabel("", parent);

    timer_ = new QTimer(parent);
    timer_->setInterval(1000);
    connect(timer_, SIGNAL(timeout()), this, SLOT(updateTempsRestant()));

    infoLayout->addWidget(player1Tag);
    infoLayout->addWidget(player1name_);
    infoLayout->addWidget(player2Tag);
    infoLayout->addWidget(player2name_);
    infoLayout->addWidget(timerLabel);
    infoLayout->addWidget(timeLeft_);

    // Widget Layout
    QHBoxLayout * widgetLayout = new QHBoxLayout(parent);

    widgetLayout->addLayout(gridLayout_);
    widgetLayout->addLayout(buttonLayout_);

    // Main Layout
    mainLayout_ = new QVBoxLayout(parent);
    mainLayout_->addLayout(infoLayout);
    mainLayout_->addLayout(widgetLayout);

    // Ajout du layout à la fenetre principale
    setLayout(mainLayout_);
    // Ajout du titre de la  fenetre
    setWindowTitle(tr("Puissance 4"));
}

void GameWindow::gridClicked()
{

    if (!isGamePlaying_) {
        return;
    }

    GamePiece *clickedGamePiece = qobject_cast<GamePiece* >(sender());
    int column = clickedGamePiece->getXposition();

    // Est-ce que le prochain coup est valide?
    if (moveIsValid(column)) {
        createPieceInColumn(column);
    }

    // Logique lorsqu'on veut vérifier quel joueur a gagné - À FAIRE
    // Indice: regarder l'enum Player dans le fichier GamePiece.h et utiliser l'attribut playerWon_


    if(checkWin()){
        isGamePlaying_=false;
        timer_->stop();

        if(player1Turn_){
            QMessageBox::warning(this, "Victoire", "Bravo "+player1name_->text()+"! Tu as GAGNE!");
        }else{
            QMessageBox::warning(this, "Victoire", "Bravo "+player2name_->text()+"! Tu as GAGNE!");

        }

        messageRecommencer();
       return;
    }
    if (checkDraw()) {
        isGamePlaying_=false;
        timer_->stop();
        timer_->stop();


        QMessageBox::warning(this, "Partie nulle", "C'est une partie nulle! ");

        messageRecommencer();

    }


}

void GameWindow::newGameClicked()
{
    player1name_->setText("Alice");
    player2name_->setText("Bob");
    currentTime_=maxGameTime_;
    reinitialisation();
    isGamePlaying_=true;
    restart_->setEnabled(true);
    timer_->start();

    // Logique lorsqu'on appuie sur le bouton nouvelle partie - À FAIRE
    // ...
}

void GameWindow::quitClicked()
{
    timer_->stop();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Quitter?", "Quitter?",QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QCoreApplication::quit();
    } else {
        timer_->start();
    }

}

void GameWindow::restartClicked()
{
    timer_->stop();



    timer_->stop();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Recommencer?", "Recommencer?",QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        isGamePlaying_=true;
        reinitialisation();
    }
    timer_->start();

    bool recommencer = true;
    if (recommencer) {
        timer_->start();
    }
}

void GameWindow::helpClicked()
{
    // Logique lorsqu'on appuie sur le bouton aide - À FAIRE
    // ...
}

void GameWindow::updateTempsRestant() {
    // Mise à jour et affichage du temps
    char buffer[16];
    sprintf(buffer, "%d:%d", currentTime_ / 60, currentTime_ % 60);
    timeLeft_->setText(tr(buffer));
    currentTime_ -= 1;

    if (currentTime_ <= 0) {
        restartClicked();
    }
}

bool GameWindow::moveIsValid(int column) const {
    return (countPiecesInColumn(column) != 6);
}

int GameWindow::countPiecesInColumn(int column) const {
    // On compte le nombre de jetons dans une colonne
    vector<QSharedPointer<GamePiece> > buttons = buttons_[column];
    int count = 0;

    for (size_t i = 0; i < buttons.size(); i++) {
        if (buttons[i]->getPlayer() != NONE) {
            count += 1;
        }
    }

    return count;
}

void GameWindow::createPieceInColumn(int column) {
    // Création d'un jeton. On doit le faire descendre le plus bas possible
    int row = 5 - countPiecesInColumn(column);

    // Création du nouveau jeton dans la grille - À FAIRE
    // Indices: Il faut utiliser la classe QSharedPointer et l'attribut buttons_. Allez voir
    // dans le constructeur de la classe GameWindow pour vous aider
    Player current;
    if(player1Turn_)
        current=PLAYER_1;
    else
        current=PLAYER_2;

    QSharedPointer<GamePiece> button(new GamePiece(column,row,current));

    gridLayout_->addWidget(&(*button), row,column);
    buttons_[column][row]= button;




    connect(&(*buttons_[column][row]), SIGNAL(clicked()), this, SLOT(gridClicked()));
    gridLayout_->addWidget(&(*buttons_[column][row]), row, column);
    player1Turn_ = !player1Turn_;
}

Player GameWindow::checkWin() const {
    // Vérification si le joueur qui vient juste de jouer a gagné
    Player player = (!player1Turn_) ? PLAYER_1 : PLAYER_2;

    // Verticale
    for (size_t j = 0; j < 6; j++) {
        // Indices are inverted for the y axis
        size_t idx = 5 - j;

        for (size_t i = 0; i < 4; i++) {
            if (buttons_[i    ][idx]->getPlayer() == player &&
                buttons_[i + 1][idx]->getPlayer() == player &&
                buttons_[i + 2][idx]->getPlayer() == player &&
                buttons_[i + 3][idx]->getPlayer() == player)
            {
                return player;
            }
        }
    }

    // Horizontale
    for (size_t i = 0; i < 7; i++) {
        vector<QSharedPointer<GamePiece> > buttons = buttons_[i];

        for (size_t j = 0; j < 3; j++) {
            // Indices are inverted for the y axis
            size_t idx = 5 - j;

            if (buttons[idx    ]->getPlayer() == player &&
                buttons[idx - 1]->getPlayer() == player &&
                buttons[idx - 2]->getPlayer() == player &&
                buttons[idx - 3]->getPlayer() == player)
            {
                return player;
            }
        }
    }

    // Diagonale droite-bas
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 3; j++) {
            if (buttons_[i    ][j    ]->getPlayer() == player &&
                buttons_[i + 1][j + 1]->getPlayer() == player &&
                buttons_[i + 2][j + 2]->getPlayer() == player &&
                buttons_[i + 3][j + 3]->getPlayer() == player)
            {
                return player;
            }
        }
    }

    // Diagonale droite-haut
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 3; j++) {
            size_t idx = 5 - j;

            if (buttons_[i    ][idx    ]->getPlayer() == player &&
                buttons_[i + 1][idx - 1]->getPlayer() == player &&
                buttons_[i + 2][idx - 2]->getPlayer() == player &&
                buttons_[i + 3][idx - 3]->getPlayer() == player)
            {
                return player;
            }
        }
    }

    return NONE;
}

bool GameWindow::checkDraw() const {
    int count = 0;
    for (int i = 0; i < 7; i++) {
        count += countPiecesInColumn(i);
    }

    return count == 42;
}

void GameWindow::reinitialisation() {

    currentTime_=maxGameTime_;
    for (int i = 0; i < 7; i ++) {
        for (int j = 0; j < 6; j++) {
           buttons_[i][j].clear();
        }
        buttons_[i].clear();
    }

    buttons_.clear();

    for (int i = 0; i < 7; i ++) {
        buttons_.push_back(vector<QSharedPointer<GamePiece> >());

        for (int j = 0; j < 6; j++) {
            QSharedPointer<GamePiece> button(new GamePiece(i, j));
            connect(&(*button), SIGNAL(clicked()), this, SLOT(gridClicked()));
            gridLayout_->addWidget(&(*button), j, i);
            buttons_[i].push_back(button);
        }
    }


}

void GameWindow::messageRecommencer(){
    timer_->stop();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Recommencer?", "Recommencer?",QMessageBox::Yes|QMessageBox::No);
    reinitialisation();
    if (reply == QMessageBox::Yes) {
        isGamePlaying_=true;
        timer_->start();
    } else {
        timeLeft_->setText("");
    }

}
