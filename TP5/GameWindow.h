#ifndef GameWindow_H
#define GameWindow_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QTimer>
#include <QSharedPointer>

#include <vector>
using namespace std;

#include "GamePiece.h"

QT_BEGIN_NAMESPACE
class QLineEdit;
class QLabel;
QT_END_NAMESPACE

class GamePiece;

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    GameWindow(QWidget *parent = 0);

private slots:
	void gridClicked();
	void newGameClicked();
	void quitClicked();
	void restartClicked();
	void helpClicked();
    void updateTempsRestant();

private:
    bool player1Turn_;
    bool isGamePlaying_;
    vector<vector<QSharedPointer<GamePiece> > > buttons_;
    QPushButton* restart_;

    QLabel * player1name_;
    QLabel * player2name_;
    QLabel * timeLeft_;
    QTimer * timer_;
    int maxGameTime_;
    int currentTime_;

    Player playerWon_;

    // Mine
    QVBoxLayout * buttonLayout_;
    QVBoxLayout * mainLayout_;
    QGridLayout * gridLayout_;

    bool moveIsValid(int column) const;
    int countPiecesInColumn(int column) const;
    void createPieceInColumn(int column);
    Player checkWin() const;
    bool checkDraw() const;
    void reinitialisation();
    void messageRecommencer();
};


#endif // GameWindow_H
