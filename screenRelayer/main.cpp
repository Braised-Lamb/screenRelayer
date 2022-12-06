#include "screenRelayer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    screenRelayer w;
    w.setWindowIcon(QIcon(":/screenRelayer/icons/logo.png"));
    w.show();
    return a.exec();
}
