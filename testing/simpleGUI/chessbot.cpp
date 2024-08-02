#include "chessbot.h"
#include <QDebug>
ChessBot::ChessBot(QObject *parent)
    : QObject{parent},
      process(new QProcess(this))
{
    connect(process, &QProcess::readyReadStandardOutput, this, &ChessBot::readEngineOutput);
}

ChessBot::~ChessBot()
{
    stopEngine();
}

void ChessBot::startEngine(const QString &enginePath){
    process->start(enginePath);
        if (!process->waitForStarted()) {
            qDebug() << "Failed to start engine!";
        }
}
void ChessBot::sendCommand(const QString &command)
{
    if (process->state() == QProcess::Running) {
        process->write(command.toUtf8() + '\n');
    }
}

void ChessBot::stopEngine()
{
    if (process->state() == QProcess::Running) {
        process->kill();
        process->waitForFinished();
    }
}

void ChessBot::readEngineOutput()
{
    QByteArray output = process->readAllStandardOutput();
    emit outputReceived(QString::fromUtf8(output));
}
