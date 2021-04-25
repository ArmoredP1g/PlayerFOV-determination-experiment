#include "Qt_CQB_Game.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Qt_CQB_Game * w = new Qt_CQB_Game;
    w->show();
    return a.exec();
}
