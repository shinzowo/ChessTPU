#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setStyleSheet("background-color: #282B5B;");
    w.resize(1000, 700);
    w.show();
    return a.exec();
}


