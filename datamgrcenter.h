#ifndef DATAMGRCENTER_H
#define DATAMGRCENTER_H

#include <QMap>
#include "rcvframe.h"
#include "sendframe.h"
#include "globals.h"
#include <QObject>
#include <QMutexLocker>
#include "globals.h"
#include "commondata.h"
#include <QUdpSocket>
#include <thread>
#include <chrono>
#include <QDateTime>
#include "ServerTcp.h"
#include <QMessageBox>
#include <QList>
#include "basedatalisten.h"

class ServerTcp;
class DataMgrCenter : QObject
{
    Q_OBJECT
public:
    DataMgrCenter();
    ~DataMgrCenter();

    static DataMgrCenter*GetInstance();

    QMap<unsigned int,RcvFrame> m_rcvFrameMap;

    QMap<unsigned int,RcvFrame> GetFrameMap()
    {
        return  m_rcvFrameMap;
    }

    void add2FrameMap(RcvFrame rcvF);
    bool ParserRcvFrame(QString remote,QByteArray arrBuffer);
    bool AssembleSndFrame(QByteArray &arrBuffer);


    bool addBaseDataListen(baseDataListen *listener);
    void muticastDataListen(RcvFrame rcvF);

    //启动 TCP服务器
    bool startTcpServer(int port);
private:
    static DataMgrCenter *m_pInstance;
    QUdpSocket *socket;

    ServerTcp *m_TcpSer;//TCP服务器

    QList<baseDataListen *> m_baseListenList;

    std::thread m_thread;
    void thread_func();//线程函数定时触发
};

#endif // DATAMGRCENTER_H
