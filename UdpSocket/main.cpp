#include "mainudp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainUdp w;
    w.show();
    return a.exec();
}
