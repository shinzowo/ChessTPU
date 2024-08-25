#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <vector>
#include <QGraphicsDropShadowEffect>
#include <QLabel>
#include <QMessageBox>
#include <QInputDialog>
#include <QList>





enum{base_ui, choose_ui, side_ui, game_ui, puzzle_ui, edit_ui};
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)/*,
      chessBot(new ChessBot(this))*/
{
    ui->setupUi(this);
    setupBaseParametres();
    chessGame=new game(ui->graphicsView, this);






}
void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    if (ui->graphicsView && ui->graphicsView->scene()) {
        QRectF sceneRect=ui->graphicsView->scene()->sceneRect();
        ui->graphicsView->setSceneRect(sceneRect);
        ui->graphicsView->fitInView(ui->graphicsView->scene()->sceneRect(), Qt::KeepAspectRatio);
    }
}
void MainWindow :: adjustGraphicsViewSize(){
    if (ui->graphicsView && ui->graphicsView->scene()) {
        ui->graphicsView->fitInView(ui->graphicsView->scene()->sceneRect(), Qt::KeepAspectRatio);
    }
}
MainWindow::~MainWindow()
{
    //chessBot->stopEngine();
    delete ui;
}

/*
void MainWindow::onEngineOutputReceived(const QString &output)
{
    qDebug() << "Engine output:" << output;
    // Обработка вывода движка
}*/

void MainWindow::setupBaseParametres(){
    setStyleOnbutton();
    //Установка базовых параметром для компонентов меню
    game_diff=4;
    lastClickedDiffButton=ui->diff_4;
    lastClickedToolButton=ui->moveButton;

    ui->cancelResignButton->setVisible(false);
    ui->LoadPositionButton->setVisible(false);
    ui->DeletePositionButton->setVisible(false);

    ui->PiecePanel1->setVisible(false);
    ui->PiecePanel1_2->setVisible(false);



    connect(ui->savesProblemWidget, &QListWidget::itemClicked,
                this, &MainWindow::onItemClicked);


    ui->widget->setContentsMargins(40, 10, 40, 10);
    ui->widget_save->hide();
    //Коннект кнопок общей функции для выбора сложности
    connect(ui->diff_1, &QPushButton::clicked, this, &MainWindow::on_diffButton_clicked);
    connect(ui->diff_2, &QPushButton::clicked, this, &MainWindow::on_diffButton_clicked);
    connect(ui->diff_3, &QPushButton::clicked, this, &MainWindow::on_diffButton_clicked);
    connect(ui->diff_4, &QPushButton::clicked, this, &MainWindow::on_diffButton_clicked);
    connect(ui->diff_5, &QPushButton::clicked, this, &MainWindow::on_diffButton_clicked);
    connect(ui->diff_6, &QPushButton::clicked, this, &MainWindow::on_diffButton_clicked);
    connect(ui->diff_7, &QPushButton::clicked, this, &MainWindow::on_diffButton_clicked);

    //Коннект кнопок общей функции для редактора

    connect(ui->moveButton, &QPushButton::clicked, this, &MainWindow::on_tool_button_clicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &MainWindow::on_tool_button_clicked);
    connect(ui->wkButton, &QPushButton::clicked, this, &MainWindow::on_tool_button_clicked);
    connect(ui->wqButton, &QPushButton::clicked, this, &MainWindow::on_tool_button_clicked);
    connect(ui->wrButton, &QPushButton::clicked, this, &MainWindow::on_tool_button_clicked);
    connect(ui->wbButton, &QPushButton::clicked, this, &MainWindow::on_tool_button_clicked);
    connect(ui->wnButton, &QPushButton::clicked, this, &MainWindow::on_tool_button_clicked);
    connect(ui->wpButton, &QPushButton::clicked, this, &MainWindow::on_tool_button_clicked);

    connect(ui->bkButton, &QPushButton::clicked, this, &MainWindow::on_tool_button_clicked);
    connect(ui->bqButton, &QPushButton::clicked, this, &MainWindow::on_tool_button_clicked);
    connect(ui->brButton, &QPushButton::clicked, this, &MainWindow::on_tool_button_clicked);
    connect(ui->bbButton, &QPushButton::clicked, this, &MainWindow::on_tool_button_clicked);
    connect(ui->bnButton, &QPushButton::clicked, this, &MainWindow::on_tool_button_clicked);
    connect(ui->bpButton, &QPushButton::clicked, this, &MainWindow::on_tool_button_clicked);

    /*/Бот
    connect(chessBot, &ChessBot::outputReceived, this, &MainWindow::onEngineOutputReceived);
    chessBot->startEngine("D:/projects/Fairy-stockfish/Fairy-Stockfish/src/stockfish.exe");
    chessBot->sendCommand("uci");
    chessBot->sendCommand("ucinewgame");
    chessBot->sendCommand("position startpos moves e2e4 e7e5");
    chessBot->sendCommand("go movetime 1000");*/
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

    //Кнопка выбора вернуться в главное меню
    ui->toMainMenuButton->setStyleSheet("QPushButton{background:transparent; color:\"#ffffff\";} QPushButton:hover{color:\"#808080\"}");

    ui->ResignButton->setStyleSheet(buttonStyle+"QPushButton{text-align:Left; padding-left: 15 px;}");
    apply_shadow(ui->ResignButton);

    ui->saveGameButton->setStyleSheet(buttonStyle);
    apply_shadow(ui->saveGameButton);

    ui->cancelResignButton->setStyleSheet(buttonStyle);

    ui->EditPuzzleButton->setStyleSheet(buttonStyle);
    ui->BackFromPuzzlesButton->setStyleSheet(buttonStyle);

    ui->SavePositionButton->setStyleSheet(buttonStyle);
    ui->BackFromEditButton->setStyleSheet(buttonStyle);
    ui->LoadPositionButton->setStyleSheet(buttonStyle);
    ui->DeletePositionButton->setStyleSheet(buttonStyle);


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

    //Кнопки выбора фигур
    QList<QPushButton*> toolsButtons=ui->PiecePanel1->findChildren<QPushButton*>();
    for(QPushButton *toolBut: toolsButtons){
        toolBut->setStyleSheet(buttonDiffStyle);
    }
    toolsButtons=ui->PiecePanel1_2->findChildren<QPushButton*>();
    for(QPushButton *toolBut: toolsButtons){
        toolBut->setStyleSheet(buttonDiffStyle);
    }


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
    ui->stackedWidget->setCurrentIndex(game_ui);
    chessGame->startGame();
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

void MainWindow::on_toMainMenuButton_clicked()
{
    chessGame->resetGame();
    ui->stackedWidget->setCurrentIndex(base_ui);
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
        ui->stackedWidget->setCurrentIndex(choose_ui);
        chessGame->resetGame();

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

void MainWindow::on_EditPuzzleButton_clicked()
{
   chessGame->setAllowEdit(true);
   ui->stackedWidget->setCurrentIndex(edit_ui);
   ui->PiecePanel1->setVisible(true);
   ui->PiecePanel1_2->setVisible(true);
   adjustGraphicsViewSize();

}

void MainWindow::on_BackFromPuzzlesButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(base_ui);
}

void MainWindow::on_SavePositionButton_clicked()
{
    bool ok;
    fileName = QInputDialog::getText(nullptr, "Save As", "Enter file name:", QLineEdit::Normal, "", &ok);
    if (ok && !fileName.isEmpty()) {
            QMessageBox::information(nullptr, "File Name", "You entered: " + fileName);
            // Здесь добавить код для сохранения файла с указанным именем
    } else {
            QMessageBox::warning(nullptr, "Input Error", "File name cannot be empty.");
    }
    ui->savesProblemWidget->addItem(fileName);
}

void MainWindow::on_BackFromEditButton_clicked()
{
    if(ui->LoadPositionButton->isVisible()==false){
        chessGame->setAllowEdit(false);
        ui->stackedWidget->setCurrentIndex(puzzle_ui);
        ui->PiecePanel1->setVisible(false);
        ui->PiecePanel1_2->setVisible(false);

    }
    else{
        ui->LoadPositionButton->setVisible(false);
        ui->DeletePositionButton->setVisible(false);
        ui->SavePositionButton->setVisible(true);
    }
}

void MainWindow::on_LoadPositionButton_clicked()
{

}

void MainWindow::on_DeletePositionButton_clicked()
{
     QListWidgetItem *selectedItem = ui->savesProblemWidget->currentItem();
     if(selectedItem){
         delete selectedItem;
     }
}

void MainWindow::on_diffButton_clicked(){
    QPushButton *clickedDiffButton=qobject_cast<QPushButton*>(sender());
    if(!clickedDiffButton){
        return;
    }
    QString buttonName = clickedDiffButton->objectName();
    if(lastClickedDiffButton){
        lastClickedDiffButton->setStyleSheet(buttonDiffStyle);
    }
    clickedDiffButton->setStyleSheet(buttonDiffStyleClicked);
    lastClickedDiffButton=clickedDiffButton;
}

void MainWindow::on_FENButton_clicked()
{
    ui->widget_save->hide();
}

void MainWindow::on_PGNButton_clicked()
{
    ui->widget_save->hide();
}

void MainWindow::on_tool_button_clicked(){

    QPushButton *clickedToolButton = qobject_cast<QPushButton*>(sender());
    if(!clickedToolButton){
        return;
    }

    if(lastClickedToolButton){
        lastClickedToolButton->setStyleSheet(buttonDiffStyle);
    }
    clickedToolButton->setStyleSheet(buttonDiffStyleClicked);
    lastClickedToolButton=clickedToolButton;

    QString name_ToolButton=lastClickedToolButton->objectName();
    chessGame->updateToolButtonName(name_ToolButton);
}

void MainWindow::onItemClicked(QListWidgetItem *item) {
    // Обработка события клика на элемент
    qDebug() << "Item clicked:" << item->text();
    ui->LoadPositionButton->setVisible(true);
    ui->DeletePositionButton->setVisible(true);
    ui->SavePositionButton->setVisible(false);
}

















