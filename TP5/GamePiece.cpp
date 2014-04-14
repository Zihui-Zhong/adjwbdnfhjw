#include <QtGui>

#include"GamePiece.h"

GamePiece::GamePiece(int posX, int posY, Player player, QWidget *parent)
    : QPushButton(parent)
    , x_(posX)
    , y_(posY)
    , player_(player)
{
    setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));

    if (player_ == PLAYER_1) {
        setStyleSheet("background-color: red");
    } else if (player_ == PLAYER_2){
        setStyleSheet("background-color: yellow");
    }
}
