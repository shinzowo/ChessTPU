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

    void on_FalseResignButton_clicked();

    void on_TrueResignButton_clicked();

    void on_BackFromPuzzlesButton_clicked();

private:

    Ui::MainWindow *ui;
    void setStyleOnbutton();
    void apply_shadow(QWidget *widget);
    QString baseColorButton;
    QString buttonStyle;
    QString textColor;
    QString hoverColor;
};
#endif // MAINWINDOW_H
