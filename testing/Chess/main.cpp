#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("Chess");
    w.setStyleSheet("background-color: lightgreen;");
    w.show();
    return a.exec();
}
