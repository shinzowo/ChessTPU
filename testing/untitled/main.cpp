#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include "DraggableWidget.h"

const int cell_size = 75;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow mainWindow;

    QVBoxLayout *layout = new QVBoxLayout(&mainWindow);

    auto board = QLabel(&mainWindow);

    QPixmap image(":/img/board.png");

    image = image.scaled(cell_size*8, cell_size*8, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    board.setPixmap(image);
    board.resize(image.size());
    board.move(140, 140);

    QString imagePath = ":/img/wk75.png";
    DraggableWidget *draggableWidget = new DraggableWidget(imagePath, &mainWindow);

    draggableWidget->makeGrid(board.pos().x(), board.pos().y(), cell_size, cell_size, 8, 8);
    draggableWidget->move(board.pos());

    layout->addWidget(draggableWidget);


    mainWindow.resize(800, 800);
    mainWindow.show();

    return a.exec();
}
