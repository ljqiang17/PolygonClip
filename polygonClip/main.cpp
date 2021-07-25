#include "polygonclip.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    polygonClip w;
    w.show();

    return a.exec();
}
