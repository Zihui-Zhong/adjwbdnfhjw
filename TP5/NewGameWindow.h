#ifndef NEW_GAME_WINDOW
#define NEW_GAME_WINDOW

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QString>
#include <string>
class NewGameWindow : public QDialog
{
	Q_OBJECT
public:
	NewGameWindow(QWidget *parent = 0);
signals:
    void debut(QString nom1,QString nom2, int nbMinutes);


private slots:
    void quitClicked();
    void debuterClicked();

private:
    QLineEdit * joueur1LE;
    QLineEdit * joueur2LE;
    QSpinBox * tempsMaxSB;

};

#endif //FENETRE_NOUVELLE_PARTIE_
