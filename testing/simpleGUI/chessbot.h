#ifndef CHESSBOT_H
#define CHESSBOT_H

#include <QObject>
#include <QProcess>

class ChessBot : public QObject
{
    Q_OBJECT
public:
    explicit ChessBot(QObject *parent = nullptr);
    virtual ~ChessBot();

    void startEngine(const QString &enginePath);
    void sendCommand(const QString &command);
    void stopEngine();
signals:
    void outputReceived(const QString &output);
private slots:
    void readEngineOutput();
private:
    QProcess *process;
};

#endif // CHESSBOT_H
