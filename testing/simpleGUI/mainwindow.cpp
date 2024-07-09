#include "mainwindow.h"
#include "./ui_mainwindow.h"

enum{base_ui, choose_ui, side_ui};
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    baseColorButton="#3D4E59";
    textColor="#ffffff";
    hoverColor="#232E35";
    buttonStyle=QString("QPushButton{background-color: %1; color: %2; border-style:outset;"
                        "}"
                        "QPushButton:hover{background-color: %3}").arg(baseColorButton).arg(textColor).arg(hoverColor);

}

MainWindow::~MainWindow()
{
    delete ui;
}


// void MainWindow::on_ClassicGameButton_clicked()
// {
//     ui->stackedWidget->setCurrentIndex(choose_ui);
// }


// void MainWindow::on_FischerChessButton_clicked()
// {
//     ui->stackedWidget->setCurrentIndex(choose_ui);
// }


// void MainWindow::on_ThreeCheckButton_clicked()
// {
//     ui->stackedWidget->setCurrentIndex(choose_ui);
// }


// void MainWindow::on_PuzzleButton_clicked()
// {

// }


// void MainWindow::on_QuitButton_clicked()
// {
//     this->close();
// }


// void MainWindow::on_TwoPlayersButton_clicked()
// {

// }


// void MainWindow::on_BotButton_clicked()
// {
//     ui->stackedWidget->setCurrentIndex(side_ui);
// }


// void MainWindow::on_BackButton_clicked()
// {
//     ui->stackedWidget->setCurrentIndex(base_ui);
// }


// void MainWindow::on_WhiteButton_clicked()
// {

// }


// void MainWindow::on_RandomButton_clicked()
// {

// }


// void MainWindow::on_BlackButton_clicked()
// {

// }


// void MainWindow::on_BackToChooseUIButton_clicked()
// {
//      ui->stackedWidget->setCurrentIndex(choose_ui);
// }

