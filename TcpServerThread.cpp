#include "TcpServerThread.h"

#include <QtNetwork>
#include <QMutex>
#include <QString>
#include <QFile>
#include <QTextStream>
#include "globals.h"

TcpServerThread::TcpServerThread(int socketDescriptor, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor)
{
}



void TcpServerThread::run()
{
    QTcpSocket *socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    Worker *worker = new Worker(socket);
    connect(worker->socket, &QTcpSocket::readyRead, worker, &Worker::doWork);

    exec();
}

//$ 0x24 36

void Worker::doWork()
{
    QString fileName;
    QString remoteAddr;
    if (socket->peerAddress().protocol() == QAbstractSocket::IPv4Protocol)
    {
        fileName = socket->peerAddress().toString();
    }
    else if (socket->peerAddress().protocol() == QAbstractSocket::IPv6Protocol)
    {
        fileName = socket->peerAddress().toString();
        fileName.remove('f');
        fileName.remove(':');
    }
    //qDebug() << fileName;
    remoteAddr = fileName;

    fileName = CommonData::GetInstance()->GetRcvDir() + fileName;
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text |QIODevice::Append))
    {
        std::cout << "Open file failed, file name is: " << fileName.toStdString() << std::endl;
        return;
    }

    QByteArray buff = socket->readAll();

    if (buff == "Start to Receive Navigation Data")
        return;
    QTextStream out(&file);
    out << buff.toHex(' ') << "\n";
    file.close();

    DataMgrCenter::GetInstance()->ParserRcvFrame(remoteAddr,buff);
}
