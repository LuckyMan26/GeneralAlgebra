#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QFont V("Verdana",16);
    QApplication::setFont(V);
    w.show();
    return a.exec();
}
