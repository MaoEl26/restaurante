#include "controladora.h"
#include <QApplication>

Controladora* controladora;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    controladora= new Controladora();

    return a.exec();
}
