#include "ServerTcp.h"
#include <stdlib.h>


ServerTcp::ServerTcp(QObject *parent)
    : QTcpServer(parent)
{

}


void ServerTcp::incomingConnection(qintptr socketDescriptor)
{
    TcpServerThread *thread = new TcpServerThread(socketDescriptor, this);

    connect(thread, &QThread::finished, thread, &QObject::deleteLater);

    thread->start();

    m_TcpThreadList.append(thread);
}
