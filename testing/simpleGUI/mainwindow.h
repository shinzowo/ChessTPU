#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QListWidgetItem>
#include <QDir>
#include "game.h"
//#include "ChessBot.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_ClassicGameButton_clicked();

    void on_FischerChessButton_clicked();

    void on_ThreeCheckButton_clicked();

    void on_PuzzleButton_clicked();

    void on_QuitButton_clicked();

    void on_TwoPlayersButton_clicked();

    void on_BotButton_clicked();

    void on_BackButton_clicked();

    void on_BotGameStart_clicked();

    void on_BackToChooseUIButton_clicked();

    void on_ResignButton_clicked();

    void on_EditPuzzleButton_clicked();

    void on_BackFromPuzzlesButton_clicked();

    void on_diffButton_clicked();

    void on_saveGameButton_clicked();

    void on_cancelResignButton_clicked();

    void on_FENButton_clicked();

    void on_PGNButton_clicked();

    void on_SavePositionButton_clicked();

    void on_BackFromEditButton_clicked();

    void onItemClicked(QListWidgetItem *item);

    void on_LoadPositionButton_clicked();

    void on_DeletePositionButton_clicked();
    void on_tool_button_clicked();

    //void onEngineOutputReceived(const QString &output);


    void on_toMainMenuButton_clicked();

    void onAboutToQuit();

private:

    Ui::MainWindow *ui;
    game *chessGame;
    //ChessBot *chessBot;

    void adjustGraphicsViewSize();
    void setupBaseParametres();
    void setStyleOnbutton();
    void apply_shadow(QWidget *widget);
    void saveFEN();
    void continueGame();

    QString buttonStyle;

    QString buttonDiffStyle;
    QString buttonDiffStyleClicked;

    QString fileName;
    QDir Dir;

    QString game_mode;
    bool isBotWith=false;
    int player_side;
    int game_diff;


    QPushButton *lastClickedDiffButton;
    QPushButton *lastClickedToolButton;
    bool confirmResign=false;

    QString openFileDialog();
    QString botPath;

protected:
    void resizeEvent(QResizeEvent *event) override;
};
#endif // MAINWINDOW_H
