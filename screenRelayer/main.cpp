#include "screenRelayer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QDesktopWidget* desktop = QApplication::desktop();
    int N = desktop->screenCount();
    QApplication a(argc, argv);
    screenRelayer w;
    w.setWindowIcon(QIcon(":/screenRelayer/icons/logo.png"));
    if (N >= 1) w.setGeometry(desktop->screenGeometry(1));
    w.show();
    return a.exec();
}
