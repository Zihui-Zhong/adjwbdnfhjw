#ifndef GamePiece_H
#define GamePiece_H

#include <QPushButton>

enum Player {
    NONE,
    PLAYER_1,
    PLAYER_2
};

class GamePiece : public QPushButton
{
    Q_OBJECT
public:
    GamePiece(int posX, int posY, Player player=NONE, QWidget *parent = 0);
    virtual ~GamePiece() {}
    GamePiece(const GamePiece& src) : x_(src.y_), y_(src.x_), player_(src.player_) {}

    int getXposition() const { return x_; }
    int getYposition() const { return y_; }
    Player getPlayer() const { return player_; }
private :
    int x_;
    int y_;

    Player player_;
};

#endif // GamePiece_H
