#include "screenRelayer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); 
    QDesktopWidget* desktop = QApplication::desktop();
    auto N = desktop->screenCount();
    qDebug() << N;
    screenRelayer w;
    w.setGeometry(desktop->screenGeometry(N - 1));
    w.setWindowIcon(QIcon(":/screenRelayer/icons/logo.png"));
    w.show();
    return a.exec();
}
