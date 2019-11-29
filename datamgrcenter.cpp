#include "datamgrcenter.h"

DataMgrCenter* DataMgrCenter::m_pInstance = nullptr;

DataMgrCenter::DataMgrCenter()
{
    m_rcvFrameMap.clear();
    m_rcvFrameMap.size();

    m_thread = std::thread(&DataMgrCenter::thread_func,this);

    startTcpServer(8080);
}

DataMgrCenter::~DataMgrCenter()
{

}

DataMgrCenter *DataMgrCenter::GetInstance()
{

    if(m_pInstance == nullptr){
        m_pInstance = new DataMgrCenter();
        m_pInstance->m_rcvFrameMap.clear();
    }

    return  m_pInstance;
}

void DataMgrCenter::add2FrameMap(RcvFrame rcvF)
{
    if(rcvF.devID == 0){
        return;
    }
    if(m_rcvFrameMap.size() > 0){
        unsigned int devID = rcvF.devID;
        if(m_rcvFrameMap.contains(devID)){
            m_rcvFrameMap[rcvF.devID] = rcvF;
        }
        else
        {
            m_rcvFrameMap.insert(rcvF.devID,rcvF);
        }
    }
    else
    {
        m_rcvFrameMap.insert(rcvF.devID,rcvF);
    }
}

bool DataMgrCenter::ParserRcvFrame(QString remote,QByteArray arrBuffer)
{
    QMutexLocker locker(&mutex);

    if(!(arrBuffer.size() > 0)){
        return  false;
    }

    try {

        RcvFrame rcv;
        rcv.remote = remote;
        if(rcv.ParserFrame(arrBuffer.data(),arrBuffer.size())){
            add2FrameMap(rcv);

            muticastDataListen(rcv);
        }


        return true;
    } catch (QException ex) {

    }

}

bool DataMgrCenter::AssembleSndFrame(QByteArray &arrBuffer)
{

    try {


        SendFrame snd;
        QMap<unsigned int,RcvFrame>::iterator iter = m_rcvFrameMap.begin();

        snd.tercnt = m_rcvFrameMap.size();
        while (iter != m_rcvFrameMap.end()) {

            //GPS
            snd.PositionXGPS << iter.value().gpsGGA.longtitude;
            snd.PositionYGPS << iter.value().gpsGGA.latitude;
            snd.PositionZGPS << iter.value().gpsGGA.height;
            snd.starnumGPS = iter.value().gpsRaw.numMeas;
            //每个接收卫星对应一个 载噪比值
            QList<cnoclass> cnoListGPS;
            for(auto rawdis:iter.value().gpsRaw.blockList){
                cnoclass cno(rawdis.svID,rawdis.cno);
                cnoListGPS<< cno;
            }
            snd.cnogps << cnoListGPS;

            //GLONASS

            snd.PositionXGlonass << iter.value().glonassGGA.longtitude;
            snd.PositionYGlonass << iter.value().glonassGGA.latitude;
            snd.PositionZGlonass << iter.value().glonassGGA.height;
            snd.starnumGlonass = iter.value().glonassRaw.numMeas;
            //每个接收卫星对应一个 载噪比值
            QList<cnoclass> cnoListGlonass;
            for(auto rawdis:iter.value().glonassRaw.blockList){
                cnoclass cno(rawdis.svID,rawdis.cno);
                cnoListGlonass << cno;
            }
            snd.cnoglonass << cnoListGlonass;

            iter++;
        }
        char framebuffer[65535];
        int len;
        snd.toBuffer(framebuffer,len);

        if(len > 0){
            int sok = socket->writeDatagram(framebuffer,len, QHostAddress("10.19.2.15"), 8888);
            qDebug() << sok;
        }

        QString fileName = CommonData::GetInstance()->GetRcvDir() + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text |QIODevice::Append))
        {
            return false;
        }
        QTextStream textStream(&file);

        textStream << QByteArray(framebuffer,len).toHex();

        file.close();


        return true;
    } catch (QException ex) {

    }
}

bool DataMgrCenter::addBaseDataListen(baseDataListen *listener)
{
    m_baseListenList << listener;
}

void DataMgrCenter::muticastDataListen(RcvFrame rcvF)
{
    for(auto lis:m_baseListenList)
    {
        lis->nodifyrcvframe(rcvF);
    }
}

bool DataMgrCenter::startTcpServer(int port)
{
    m_TcpSer = new ServerTcp(this);


    if (!m_TcpSer->listen(QHostAddress::Any, port)) {
        QMessageBox::critical(nullptr, tr("Threaded Fortune Server"),
                              tr("Unable to start the server: %1.")
                              .arg(m_TcpSer->errorString()));
        //close();
        return false;
    }

}

void DataMgrCenter::thread_func()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        QMutexLocker locker(&mutex);

        QByteArray arrBytes;
        //AssembleSndFrame(arrBytes);

//        if(arrBytes.length() > 0){
//            socket->writeDatagram(arrBytes, QHostAddress::LocalHost, 8888);
//        }
    }
}
