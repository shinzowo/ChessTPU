#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGraphicsDropShadowEffect>

enum{base_ui, choose_ui, side_ui, game_ui, puzzle_ui};
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setStyleOnbutton();
    ui->widget_2->setVisible(false);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setStyleOnbutton(){
    baseColorButton="#3D4E59";
    textColor="#ffffff";
    hoverColor="#232E35";
    buttonStyle=QString("QPushButton{background-color: %1; color: %2; border-style:outset; border-radius:5px;"
                        "}"
                        "QPushButton:hover{background-color: %3}").arg(baseColorButton).arg(textColor).arg(hoverColor);
    ui->chess_title->setStyleSheet("QLabel{color:#ffffff;}");
    ui->chess_title_2->setStyleSheet("QLabel{color:#ffffff;}");
    ui->chess_title_3->setStyleSheet("QLabel{color:#ffffff;}");
    ui->chess_title_4->setStyleSheet("QLabel{color:#ffffff;}");
    ui->ClassicGameButton->setStyleSheet(buttonStyle);
    apply_shadow(ui->ClassicGameButton);

    ui->FischerChessButton->setStyleSheet(buttonStyle);
    apply_shadow(ui->FischerChessButton);

    ui->ThreeCheckButton->setStyleSheet(buttonStyle);
    apply_shadow(ui->ThreeCheckButton);

    ui->PuzzleButton->setStyleSheet(buttonStyle);
    apply_shadow(ui->PuzzleButton);

    ui->QuitButton->setStyleSheet(buttonStyle);
    apply_shadow(ui->QuitButton);

    ui->BotButton->setStyleSheet(buttonStyle);
    apply_shadow(ui->BotButton);

    ui->TwoPlayersButton->setStyleSheet(buttonStyle);
    apply_shadow(ui->TwoPlayersButton);

    ui->BackButton->setStyleSheet(buttonStyle);
    apply_shadow(ui->BackButton);

    ui->WhiteButton->setStyleSheet(buttonStyle);
    apply_shadow(ui->WhiteButton);

    ui->RandomButton->setStyleSheet(buttonStyle);
    apply_shadow(ui->RandomButton);

    ui->BlackButton->setStyleSheet(buttonStyle);
    apply_shadow(ui->BlackButton);

    ui->BackToChooseUIButton->setStyleSheet(buttonStyle);
    apply_shadow(ui->BackToChooseUIButton);

    ui->ResignButton->setStyleSheet(buttonStyle);
    apply_shadow(ui->ResignButton);

    ui->TrueResignButton->setStyleSheet(buttonStyle);
    apply_shadow(ui->TrueResignButton);

    ui->FalseResignButton->setStyleSheet(buttonStyle);
    apply_shadow(ui->FalseResignButton);

    ui->BackFromPuzzlesButton->setStyleSheet(buttonStyle);
}
void MainWindow::apply_shadow(QWidget *widget){
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(widget);
    shadowEffect->setBlurRadius(5);
    shadowEffect->setOffset(1, 1);
    shadowEffect->setColor(Qt::black);
    widget->setGraphicsEffect(shadowEffect);
}
void MainWindow::on_ClassicGameButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(choose_ui);
}


void MainWindow::on_FischerChessButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(choose_ui);
}


void MainWindow::on_ThreeCheckButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(choose_ui);
}


void MainWindow::on_PuzzleButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(puzzle_ui);
}


void MainWindow::on_QuitButton_clicked()
{
    this->close();
}


void MainWindow::on_TwoPlayersButton_clicked()
{

}


void MainWindow::on_BotButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(side_ui);
}


void MainWindow::on_BackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(base_ui);
}


void MainWindow::on_WhiteButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(game_ui);
}


void MainWindow::on_RandomButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(game_ui);
}


void MainWindow::on_BlackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(game_ui);
}


void MainWindow::on_BackToChooseUIButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(choose_ui);
}


void MainWindow::on_ResignButton_clicked()
{
    ui->widget_2->setVisible(true);
}

void MainWindow::on_TrueResignButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(base_ui);
     ui->widget_2->setVisible(false);
}

void MainWindow::on_FalseResignButton_clicked()
{
    ui->widget_2->setVisible(false);
}





void MainWindow::on_BackFromPuzzlesButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(base_ui);
}

