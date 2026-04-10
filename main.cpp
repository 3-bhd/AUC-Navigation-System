#include "mapping.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mapping m;
    m.show();
    return a.exec();
}
