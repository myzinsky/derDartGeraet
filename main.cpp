#include "darts.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Darts w;
    w.show();

    return a.exec();
}
