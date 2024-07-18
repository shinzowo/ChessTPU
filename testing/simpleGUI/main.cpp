#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setStyleSheet("background-color: #282B5B;");
    w.resize(800, 630);
    w.show();
    return a.exec();
}


