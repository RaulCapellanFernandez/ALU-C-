#include "interfacealu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InterfaceALU w;
    w.show();

    return a.exec();
}
