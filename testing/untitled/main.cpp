#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include "DraggableWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow mainWindow;

    QWidget *centralWidget = new QWidget(&mainWindow);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QString imagePath = ":/img/wk.png";
    DraggableWidget *draggableWidget = new DraggableWidget(imagePath, centralWidget);

    layout->addWidget(draggableWidget);

    mainWindow.setCentralWidget(centralWidget);

    mainWindow.resize(800, 600);
    mainWindow.show();

    return a.exec();
}
