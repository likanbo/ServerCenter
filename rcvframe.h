#ifndef RCVFRAME_H
#define RCVFRAME_H

#include <QException>
#include <QString>
#include <QDebug>

const int MAX_LEN = 65535;


class RMC
{
public:
    RMC()
    {
        latitude = 0;
        longtitude = 0;
        spd = 0;
        cog = 0;
        mv = 0;
    }
    RMC(const RMC &rmc)
    {
        xxRMC = rmc.xxRMC;
        time = rmc.time;
        status = rmc.status;
        latitude = rmc.latitude;
        NS = rmc.NS;
        longtitude = rmc.longtitude;
        EW = rmc.EW;
        spd = rmc.spd;
        cog = rmc.cog;
        date = rmc.date;
        mv = rmc.mv;
        mvEW = rmc.mvEW;
        posMode = rmc.posMode;
        navStatus = rmc.navStatus;
        cs = rmc.cs;
    }

public:
    QString xxRMC;
    QString time;
    QString status;
    double latitude;
    QString NS;
    double longtitude;
    QString EW;
    double spd;
    double cog;
    QString date;
    double mv;
    QString mvEW;
    QString posMode;
    QString navStatus;

    unsigned char cs;

};

class GGA
{
public:
    GGA()
    {
        latitude = 0;
        longtitude = 0;

        gpsStatus = 0;
        satnum = 0;

        hdop = 0;
        height = 0;
        horiH = 0;
        diffTime = 0;
        diffID = 0;
        chk = 0;
    }
    GGA(const GGA &ggaT)
    {
        gga = ggaT.gga;
        utctime = ggaT.utctime;

        latitude = ggaT.latitude;
        NS = ggaT.NS;
        longtitude = ggaT.longtitude;
        WE = ggaT.WE;

        gpsStatus = ggaT.gpsStatus;

        satnum = ggaT.satnum;

        hdop = ggaT.hdop;
        height = ggaT.height;
        horiH = ggaT.horiH;
        diffTime = ggaT.diffTime;
        diffID = ggaT.diffID;
        chk = ggaT.chk;
    }
public:
    QString gga;
    QString utctime;

    double latitude;
    QString NS;
    double longtitude;
    QString WE;

    //0:未定位 1：非差分定位 2：差分定位 3：无效GPS 6：正在估算
    char gpsStatus;
    QString GetPosState()
    {
        QString desc;
        switch (gpsStatus)
        {
        case 0:
            desc = QString::fromUtf8("未定位");
            break;
        case 1:
            desc = QString::fromUtf8("非差分定位");
            break;
        case 2:
            desc = QString::fromUtf8("差分定位");
            break;
        case 3:
            desc = QString::fromUtf8("无效");
            break;
        case 6:
            desc = QString::fromUtf8("正在估算");
            break;
        default:
            desc = QString::fromUtf8("未定位");
            break;
        }

        return desc;
    }

    char satnum;

    double hdop;
    double height;
    double horiH;
    double diffTime;
    int diffID;
    char chk;
};

class RepeatedBlock
{
public:
    RepeatedBlock()
    {
        preMes = 0;//Pseudorante measurement
        cpMes = 0;//Carrier phase
        doMes = 0;//Doppler measurement
        gnssID = 0;
        svID = 0;
        reserved = 0;
        freqId = 0;
        locktime = 0;
        cno = 0;
        prStdev = 0;
        cpStDev = 0;
        doStDev = 0;
        trkStat = 0;
        res = 0;
    }
    RepeatedBlock(const RepeatedBlock &blk)
    {
        preMes = blk.preMes;//Pseudorante measurement
        cpMes = blk.cpMes;//Carrier phase
        doMes = blk.doMes;//Doppler measurement
        gnssID = blk.gnssID;
        svID = blk.svID;
        reserved = blk.reserved;
        freqId = blk.freqId;
        locktime = blk.locktime;
        cno = blk.cno;
        prStdev = blk.prStdev;
        cpStDev = blk.cpStDev;
        doStDev = blk.doStDev;
        trkStat = blk.trkStat;
        res = blk.res;
    }

    double preMes;//Pseudorante measurement
    double cpMes;//Carrier phase
    double doMes;//Doppler measurement
    unsigned char gnssID;
    unsigned char svID;
    unsigned char reserved;
    unsigned int freqId;
    unsigned int locktime;
    unsigned char cno;
    double prStdev;
    double cpStDev;
    double doStDev;
    double trkStat;
    unsigned char res;

};
class RawDistance
{
public:
    RawDistance()
    {

        rcvTow = 0;
        weeks = 0;
        leapS = 0;
        numMeas = 0;
        recStat = 0;
        blockList.clear();
    }
    RawDistance(const RawDistance &raw)
    {
        rcvTow = raw.rcvTow;
        weeks = raw.weeks;
        leapS = raw.leapS;
        numMeas = raw.numMeas;
        recStat = raw.recStat;
        blockList.clear();
        blockList.append(raw.blockList);
    }

    unsigned long long int rcvTow;
    unsigned int weeks;
    unsigned int leapS;
    unsigned int numMeas;
    unsigned int recStat;

    QList<RepeatedBlock> blockList;

};

class RcvFrame
{
public:
    RcvFrame();
    RcvFrame(const RcvFrame & rcv);

    bool ParserFrame(const char *pbuffer,int len);
    bool ParserUblox(const char *pbuffer,int len,RawDistance &rawdis,RMC &rm,GGA &ga);

    QString remote;

    unsigned int header;
    unsigned int devID;
    unsigned int frameNum1;
    unsigned int frameNum2;

    RawDistance gpsRaw;
    RMC gpsRMC;
    GGA gpsGGA;

    RawDistance glonassRaw;
    RMC glonassRMC;
    GGA glonassGGA;

    double pow;

    unsigned char reserve[4];
    unsigned char tail[2];
};

#endif // RCVFRAME_H
