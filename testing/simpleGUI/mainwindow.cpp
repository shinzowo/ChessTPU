#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGraphicsDropShadowEffect>
#include <QLabel>
#include "DraggableWidget.h"
#include <vector>


bool flag = false;
std::vector<DraggableWidget*> pie;
enum{base_ui, choose_ui, side_ui, game_ui, puzzle_ui};
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setStyleOnbutton();

    this->resize(800, 630);

    //Установка базовых параметром для компонентов меню
    game_diff=4;
    lastClickedButton=ui->diff_4;


    ui->cancelResignButton->setVisible(false);
    ui->widget->setContentsMargins(40, 10, 40, 10);
    ui->widget_save->hide();


    // auto board = new QLabel(ui->square);
    // auto pixmap = new QPixmap(":/img/board.png");
    // board->setPixmap(*pixmap);
    // board->setAlignment(Qt::AlignCenter);

    // QVBoxLayout *layout = new QVBoxLayout(ui->square);
    // layout->addWidget(board);
    // layout->setContentsMargins(0, 0, 0, 0);
    // ui->square->setLayout(layout);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setStyleOnbutton(){
    baseColorButton="#3D4E59";
    textColor="#ffffff";
    hoverColor="#232E35";
    clickedDiffButton="#6ACF68";

    buttonStyle=QString("QPushButton{background-color: %1; color: %2; border-style:outset; border-radius:5px;"
                        "}"
                        "QPushButton:hover{background-color: %3}").arg(baseColorButton).arg(textColor).arg(hoverColor);
    QString text_align_style=QString("QPushButton{text-align:Left; padding-left: %1 px;}").arg(15);

    ui->chess_title->setStyleSheet("QLabel{color:#ffffff;}");
    ui->chess_title_2->setStyleSheet("QLabel{color:#ffffff;}");
    ui->chess_title_3->setStyleSheet("QLabel{color:#ffffff;}");
    ui->chess_title_4->setStyleSheet("QLabel{color:#ffffff;}");
    ui->ClassicGameButton->setStyleSheet(buttonStyle+text_align_style);
    apply_shadow(ui->ClassicGameButton);

    ui->FischerChessButton->setStyleSheet(buttonStyle+text_align_style);
    apply_shadow(ui->FischerChessButton);

    ui->ThreeCheckButton->setStyleSheet(buttonStyle+text_align_style);
    apply_shadow(ui->ThreeCheckButton);

    ui->PuzzleButton->setStyleSheet(buttonStyle+text_align_style);
    apply_shadow(ui->PuzzleButton);

    ui->QuitButton->setStyleSheet(buttonStyle+text_align_style);
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

    ui->ResignButton->setStyleSheet(buttonStyle+"QPushButton{text-align:Left; padding-left: 15 px;}");
    apply_shadow(ui->ResignButton);

    ui->saveGameButton->setStyleSheet(buttonStyle);
    apply_shadow(ui->saveGameButton);

    ui->cancelResignButton->setStyleSheet(buttonStyle);

    ui->BackFromPuzzlesButton->setStyleSheet(buttonStyle);

    ui->PGNButton->setStyleSheet(buttonStyle);
    apply_shadow(ui->PGNButton);

    ui->FENButton->setStyleSheet(buttonStyle);
    apply_shadow(ui->FENButton);

    //кнопки уровня сложности
    ui->diff_label->setStyleSheet("QLabel{color:#ffffff;}");
    buttonDiffStyle=QString("QPushButton{background-color: %1; color: %2; border-style:outset; border-radius:1px;"
                        "}"
                        "QPushButton:hover{background-color: %3}").arg(baseColorButton).arg(textColor).arg(hoverColor);
    buttonDiffStyleClicked=QString("QPushButton{background-color: %1; color: %2; border-style:outset; border-radius:1px;"
                        "}").arg(clickedDiffButton).arg(textColor);

    ui->diff_1->setStyleSheet(buttonDiffStyle);
    apply_shadow(ui->diff_1);

    ui->diff_2->setStyleSheet(buttonDiffStyle);
    apply_shadow(ui->diff_2);

    ui->diff_3->setStyleSheet(buttonDiffStyle);
    apply_shadow(ui->diff_3);

    ui->diff_4->setStyleSheet(buttonDiffStyleClicked);
    apply_shadow(ui->diff_4);

    ui->diff_5->setStyleSheet(buttonDiffStyle);
    apply_shadow(ui->diff_5);

    ui->diff_6->setStyleSheet(buttonDiffStyle);
    apply_shadow(ui->diff_6);

    ui->diff_7->setStyleSheet(buttonDiffStyle);
    apply_shadow(ui->diff_7);
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

    if(flag) return;
    flag = true;
    ui->stackedWidget->setCurrentIndex(puzzle_ui);
    int cell_size = 50;
    std::vector<DraggableWidget*> pieces;
    pieces.push_back(new DraggableWidget(":/img/pieces600/wr.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/wn.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/wb.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/wq.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/wk.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/wp.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/br.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/bn.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/bb.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/bq.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/bp.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/bk.png", this));
    for(int i=0;i<12;i++){
        pieces[i]->setGeometry(ui->Pieces->pos().x()+cell_size*i, ui->Pieces->pos().y(), cell_size, cell_size);

        pieces[i]->setAttribute(Qt::WA_TranslucentBackground, true);
        pieces[i]->setAttribute(Qt::WA_OpaquePaintEvent, true);
        pieces[i]->setStyleSheet("background: transparent;");
        pieces[i]->show();
        pie.push_back(pieces[i]);
    }
    pieces.clear();
}

void MainWindow::on_QuitButton_clicked()
{
    this->close();
}

void MainWindow::on_TwoPlayersButton_clicked()
{
    if(flag) return;
    flag = true;
    //QVBoxLayout *layout = new QVBoxLayout(ui->square);
    QSize size =  ui->board->size();
    int cell_size = size.height() / 8;
    std::vector<DraggableWidget*> pieces;
    pieces.push_back(new DraggableWidget(":/img/pieces600/br.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/bn.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/bb.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/bq.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/bk.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/bb.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/bn.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/br.png", this));



    for (int i = 0; i < 8; ++i){
        pieces[i]->makeGrid(ui->empty_widget->pos().x(), ui->empty_widget->pos().y(), cell_size, cell_size, 8, 8);
        pieces[i]->setGeometry(ui->empty_widget->pos().x() + cell_size * i, ui->empty_widget->pos().y(), cell_size, cell_size);
        pieces[i]->setAttribute(Qt::WA_TranslucentBackground, true);
        pieces[i]->setAttribute(Qt::WA_OpaquePaintEvent, true);
        pieces[i]->setStyleSheet("background: transparent;");
        pieces[i]->show();
        pie.push_back(pieces[i]);
    }

    pieces.clear();
    pieces.push_back(new DraggableWidget(":/img/pieces600/wr.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/wn.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/wb.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/wq.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/wk.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/wb.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/wn.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/wr.png", this));

    for (int i = 0; i < 8; ++i){
        pieces[i]->makeGrid(ui->empty_widget->pos().x(), ui->empty_widget->pos().y(), cell_size, cell_size, 8, 8);
        pieces[i]->setGeometry(ui->empty_widget->pos().x() + cell_size * i, ui->empty_widget->pos().y() + 7 * cell_size, cell_size, cell_size);
        pieces[i]->setAttribute(Qt::WA_TranslucentBackground, true);
        pieces[i]->setAttribute(Qt::WA_OpaquePaintEvent, true);
        pieces[i]->setStyleSheet("background: transparent;");
        pieces[i]->show();
        pie.push_back(pieces[i]);
    }

    pieces.clear();
    pieces.push_back(new DraggableWidget(":/img/pieces600/wp.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/wp.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/wp.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/wp.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/wp.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/wp.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/wp.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/wp.png", this));

    for (int i = 0; i < 8; ++i){
        pieces[i]->makeGrid(ui->empty_widget->pos().x(), ui->empty_widget->pos().y(), cell_size, cell_size, 8, 8);
        pieces[i]->setGeometry(ui->empty_widget->pos().x() + cell_size * i, ui->empty_widget->pos().y() + 6 * cell_size, cell_size, cell_size);
        pieces[i]->setAttribute(Qt::WA_TranslucentBackground, true);
        pieces[i]->setAttribute(Qt::WA_OpaquePaintEvent, true);
        pieces[i]->setStyleSheet("background: transparent;");
        pieces[i]->show();
        pie.push_back(pieces[i]);
    }

    pieces.clear();
    pieces.push_back(new DraggableWidget(":/img/pieces600/bp.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/bp.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/bp.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/bp.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/bp.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/bp.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/bp.png", this));
    pieces.push_back(new DraggableWidget(":/img/pieces600/bp.png", this));

    for (int i = 0; i < 8; ++i){
        pieces[i]->makeGrid(ui->empty_widget->pos().x(), ui->empty_widget->pos().y(), cell_size, cell_size, 8, 8);
        pieces[i]->setGeometry(ui->empty_widget->pos().x() + cell_size * i, ui->empty_widget->pos().y() + 1 * cell_size, cell_size, cell_size);
        pieces[i]->setAttribute(Qt::WA_TranslucentBackground, true);
        pieces[i]->setAttribute(Qt::WA_OpaquePaintEvent, true);
        pieces[i]->setStyleSheet("background: transparent;");
        pieces[i]->show();
        pie.push_back(pieces[i]);
    }


}

void MainWindow::on_BotButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(side_ui);
}

void MainWindow::on_BackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(base_ui);
    flag = false;
    for (auto p : pie) {
        p->close();
    }
    pie.clear();
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
    if(ui->widget_save->isVisible()){
        ui->widget_save->hide();
    }
    if(confirmResign==true){
        ui->cancelResignButton->hide();

        ui->widget->setContentsMargins(40, 10, 10+30, 10);
        ui->ResignButton->setStyleSheet(buttonStyle);
        confirmResign=false;
        ui->stackedWidget->setCurrentIndex(side_ui);

    }
    else{
        ui->cancelResignButton->show();
        ui->widget->setContentsMargins(40, 10, 10, 10);
        ui->ResignButton->setStyleSheet("background-color:#ED591A; border-radius:5px");
        confirmResign=true;
    }
}

void MainWindow::on_cancelResignButton_clicked()
{
    ui->cancelResignButton->hide();
    ui->widget->setContentsMargins(40, 10, 10+30, 10);
    ui->ResignButton->setStyleSheet(buttonStyle);
    confirmResign=false;
}

void MainWindow::on_saveGameButton_clicked()
{
    if(ui->widget_save->isVisible()!=true){
        ui->widget_save->show();
    }
    else{
        ui->widget_save->hide();
    }

}

void MainWindow::on_BackFromPuzzlesButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(base_ui);
    flag=false;
    for (auto p : pie) {
        p->close();
    }
    pie.clear();
}




void MainWindow::on_diff_1_clicked()
{
    lastClickedButton->setStyleSheet(buttonDiffStyle);
    ui->diff_1->setStyleSheet(buttonDiffStyleClicked);
    lastClickedButton=ui->diff_1;
    game_diff=1;

}


void MainWindow::on_diff_2_clicked()
{
    lastClickedButton->setStyleSheet(buttonDiffStyle);
    ui->diff_2->setStyleSheet(buttonDiffStyleClicked);
    lastClickedButton=ui->diff_2;
    game_diff=2;
}

void MainWindow::on_diff_3_clicked()
{
    lastClickedButton->setStyleSheet(buttonDiffStyle);
    ui->diff_3->setStyleSheet(buttonDiffStyleClicked);
    lastClickedButton=ui->diff_3;
    game_diff=3;
}

void MainWindow::on_diff_4_clicked()
{
    lastClickedButton->setStyleSheet(buttonDiffStyle);
    ui->diff_4->setStyleSheet(buttonDiffStyleClicked);
    lastClickedButton=ui->diff_4;
    game_diff=4;
}

void MainWindow::on_diff_5_clicked()
{
    lastClickedButton->setStyleSheet(buttonDiffStyle);
    ui->diff_5->setStyleSheet(buttonDiffStyleClicked);
    lastClickedButton=ui->diff_5;
    game_diff=5;
}

void MainWindow::on_diff_6_clicked()
{
    lastClickedButton->setStyleSheet(buttonDiffStyle);
    ui->diff_6->setStyleSheet(buttonDiffStyleClicked);
    lastClickedButton=ui->diff_6;
    game_diff=6;
}

void MainWindow::on_diff_7_clicked()
{
    lastClickedButton->setStyleSheet(buttonDiffStyle);
    ui->diff_7->setStyleSheet(buttonDiffStyleClicked);
    lastClickedButton=ui->diff_7;
    game_diff=7;
}







void MainWindow::on_FENButton_clicked()
{
    ui->widget_save->hide();
}


void MainWindow::on_PGNButton_clicked()
{
    ui->widget_save->hide();
}

