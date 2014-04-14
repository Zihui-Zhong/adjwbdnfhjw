#include <QApplication>
#include <QLabel>
#include "GameWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    GameWindow window;

#if defined(Q_OS_SYMBIAN)
    window.showMaximized();
#else
    window.show();
#endif


    return app.exec();
}


