#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>


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

    void on_WhiteButton_clicked();

    void on_RandomButton_clicked();

    void on_BlackButton_clicked();

    void on_BackToChooseUIButton_clicked();

    void on_ResignButton_clicked();

    void on_BackFromPuzzlesButton_clicked();

    void on_diff_1_clicked();

    void on_diff_2_clicked();

    void on_diff_3_clicked();

    void on_diff_4_clicked();

    void on_diff_5_clicked();

    void on_diff_6_clicked();

    void on_diff_7_clicked();

    void on_saveGameButton_clicked();

    void on_cancelResignButton_clicked();

    void on_FENButton_clicked();

    void on_PGNButton_clicked();

private:

    Ui::MainWindow *ui;
    void setStyleOnbutton();
    void apply_shadow(QWidget *widget);
    QString baseColorButton;
    QString buttonStyle;
    QString text_align_style;

    QString clickedDiffButton;
    QString buttonDiffStyle;
    QString buttonDiffStyleClicked;
    QString textColor;
    QString hoverColor;


    int game_diff;
    QPushButton *lastClickedButton;
    bool confirmResign=false;
};
#endif // MAINWINDOW_H
