#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QFrame>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_playButton_clicked()
{

    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_puzzleButton_clicked()
{

}

void MainWindow::on_exitButton_clicked()
{
    close();
}

void MainWindow::on_BackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_ClassicButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_backClassicButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

