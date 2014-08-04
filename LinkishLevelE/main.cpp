#include "LevelEditor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LevelEditor w;
    w.initialize();
    w.showMaximized();

    return a.exec();
}
