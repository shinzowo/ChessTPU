#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setStyleSheet("background-color: #9A3838;");
    w.resize(800, 630);
    w.show();
    return a.exec();
}


