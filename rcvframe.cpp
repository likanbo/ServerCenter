#include "rcvframe.h"

RcvFrame::RcvFrame()
{


    header = 0;
    devID = 0;
    frameNum1 = 0;
    frameNum2 = 0;


    pow = 0;

    tail[0] = 0;
    tail[1] = 0;
}

RcvFrame::RcvFrame(const RcvFrame &rcv)
{
    remote = rcv.remote;

    devID = rcv.devID;

    gpsRaw = rcv.gpsRaw;
    gpsRMC = rcv.gpsRMC;

    glonassRaw = rcv.glonassRaw;
    glonassRMC = rcv.glonassRMC;
}

bool RcvFrame::ParserFrame(const char *pbuffer, int len)
{
    if(pbuffer == nullptr || len < 1024)
    {
        return  false;
    }

    try
    {
        int index = 0;

        memcpy(&header,pbuffer+index,2);
        index += 2;

        memcpy(&devID,pbuffer+index,2);
        index += 2;

        memcpy(&frameNum1,pbuffer+index,4);
        index += 4;

        memcpy(&frameNum2,pbuffer+index,4);
        index += 4;


        //BLOX1
        char blox1[500];
        memcpy(blox1,pbuffer+index,500);
        index += 500;
        ParserUblox(blox1,500,gpsRaw,gpsRMC,gpsGGA);


        QString strPow = QString::fromLocal8Bit(pbuffer+index,6);
        index += 6;
        pow = strPow.toDouble();//dBm

        //BLOX2
        char blox2[500];
        memcpy(blox2,pbuffer+index,500);
        index += 500;
        ParserUblox(blox2,500,glonassRaw,glonassRMC,glonassGGA);

        index += 4;

        tail[0] = pbuffer[index++];
        tail[1] = pbuffer[index++];

        return  true;
    } catch (QException ex) {

    }
}

bool RcvFrame::ParserUblox(const char *pbuffer, int len, RawDistance &rawdis,RMC &rm,GGA &ga)
{
    if(pbuffer == nullptr || len < 500)
    {
        return  false;
    }

    try
    {
        int index = 0;

        int header = 0;
        memcpy(&header,pbuffer+index,2);
        index += 2;

        char cla = pbuffer[index++];

        char id =  pbuffer[index++];

        int lenMeas = 0;
        memcpy(&lenMeas,pbuffer+index,2);
        index += 2;

        memcpy(&rawdis.rcvTow,pbuffer+index,8);
        index += 8;

        memcpy(&rawdis.weeks,pbuffer+index,2);
        index += 2;

        memcpy(&rawdis.leapS,pbuffer+index,1);
        index += 1;

        rawdis.numMeas  = pbuffer[index++];
        rawdis.recStat = pbuffer[index++];

        if(rawdis.numMeas > 64){
            return  false;
        }

        index += 3;

        RepeatedBlock reblk;
        for(int i=0;i<rawdis.numMeas;i++)
        {
            memcpy(&reblk.preMes,pbuffer+index,8);
            index += 8;

            memcpy(&reblk.cpMes,pbuffer+index,8);
            index += 8;

            memcpy(&reblk.doMes,pbuffer+index,4);
            index += 4;

            reblk.gnssID = pbuffer[index++];
            reblk.svID = pbuffer[index++];
            reblk.reserved = pbuffer[index++];
            reblk.freqId = pbuffer[index++];

            memcpy(&reblk.locktime,pbuffer+index,2);
            index += 2;

            reblk.cno = pbuffer[index++];

//            reblk.prStdev = pbuffer[index++];

//            reblk.cpStDev = pbuffer[index++] * 0.004;

//            reblk.doStDev = pbuffer[index++];

//            reblk.trkStat = pbuffer[index++];

            index++;

            rawdis.blockList.append(reblk);
        }

        //chk
        index += 2;

        //RMC
//        QStringList rmcSplit;
//        int dd = 0;
//        int p = index;
//        for(dd = 0;dd<len-index;dd++){
//            if(pbuffer[index+dd] == 0x0D && pbuffer[index+dd+1] == 0x0A){
//                QString rmc = QString::fromLocal8Bit(pbuffer+p,index+dd+2-p);
//                rmcSplit << rmc;

//                p = index+dd+2;
//            }
//        }
        QString rmc = (pbuffer+index);
        qDebug() << rmc;

        QStringList rmcSplit = rmc.split('$');


        for(auto rmcItem :rmcSplit){            
            if(rmcItem.contains("RMC")){//GLRMC
//                QStringList rmcList = rmcItem.split(',');
//                int rmcIndex = 0;
//                rm.xxRMC = rmcList.at(rmcIndex++);
//                rm.time = rmcList.at(rmcIndex++);
//                rm.status = rmcList.at(rmcIndex++);
//                rm.latitude = rmcList.at(rmcIndex++).toDouble();
//                rm.NS = rmcList.at(rmcIndex++);
//                rm.longtitude = rmcList.at(rmcIndex++).toDouble();
//                rm.EW = rmcList.at(rmcIndex++);
//                rm.spd = rmcList.at(rmcIndex++).toDouble();
//                rm.cog = rmcList.at(rmcIndex++).toDouble();
//                rm.date = rmcList.at(rmcIndex++);
            }
            else
            {
                if(rmcItem.contains("GGA")){
                    QStringList rmcList = rmcItem.split(',');
                    int rmcIndex = 0;
                    ga.gga = rmcList.at(rmcIndex++);
                    ga.utctime = rmcList.at(rmcIndex++);
                    ga.latitude = rmcList.at(rmcIndex++).toDouble();//纬度
                    ga.NS = rmcList.at(rmcIndex++);
                    ga.longtitude = rmcList.at(rmcIndex++).toDouble();//经度
                    ga.WE = rmcList.at(rmcIndex++);
                    ga.gpsStatus = rmcList.at(rmcIndex++).toInt();
                    ga.satnum = rmcList.at(rmcIndex++).toInt();
                    ga.hdop = rmcList.at(rmcIndex++).toDouble();
                    ga.height = rmcList.at(rmcIndex++).toDouble();

                }
            }
        }



        char tail[2];
        mempcpy(tail,pbuffer+index,2);

        return  true;
    } catch (QException ex) {

    }
}
