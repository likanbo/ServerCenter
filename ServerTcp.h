#ifndef SERVERTCP_H
#define SERVERTCP_H

#include <QTcpServer>
#include "TcpServerThread.h"
#include <QList>

class TcpServerThread;

class ServerTcp : public QTcpServer
{
    Q_OBJECT

public:
    ServerTcp(QObject *parent = 0);

    QList<TcpServerThread*> m_TcpThreadList;
protected:
    void incomingConnection(qintptr socketDescriptor) override;

};

#endif
