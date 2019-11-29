#ifndef TCPSERVERTHREAD_H
#define TCPSERVERTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <iostream>
#include "datamgrcenter.h"
#include "commondata.h"

class TcpServerThread : public QThread
{
    Q_OBJECT

public:
    TcpServerThread(int socketDescriptor, QObject *parent);

    void run() override;

public:
    int socketDescriptor;
};

class Worker : public QObject
{
    Q_OBJECT
public:
    Worker(QTcpSocket *s)
        : socket(s)
    {

    }

public slots:
    void doWork();

public:
    QTcpSocket *socket;
};

#endif
