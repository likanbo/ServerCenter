#ifndef COMMONDATA_H
#define COMMONDATA_H
#include <QString>


class RawDataFrame
{
public:
    RawDataFrame();
    RawDataFrame(const RawDataFrame &frame);
    RawDataFrame(QByteArray dataArr,QString desc);

    QByteArray m_Buffer;//数据帧源码
    QString m_dataDesc;//数据源 描述 IP后者端口
};



class CommonData
{
public:
    CommonData();
    static CommonData* GetInstance();


    void SetDataDir(QString dataDir)
    {
        m_dataDir = dataDir;
    }
    QString GetDataDir(){
        return  m_dataDir;
    }

    void SetRcvDir(QString datarcv)
    {
        m_rcvDir = datarcv;
    }
    QString GetRcvDir(){
        return  m_rcvDir;
    }

    void SetSndDir(QString datasnd)
    {
        m_sndDir = datasnd;
    }
    QString GetSndDir(){
        return  m_sndDir;
    }

private:
    static CommonData* m_pInstance;
    QString m_dataDir;
    QString m_rcvDir;
    QString m_sndDir;
};

#endif // COMMONDATA_H
