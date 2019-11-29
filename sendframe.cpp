#include "sendframe.h"

SendFrame::SendFrame()
{
    tercnt = 0;
    memset(header,0,sizeof (header));
    sour = 0;
    dest = 0;
    infotype = 0;
    infolenth = 0;
    datatype = 0;
    datalenth = 0;

    PositionXGPS.clear();
    PositionYGPS.clear();
    PositionZGPS.clear();
    cnogps.clear();
    R_type.clear();
    starnumGPS = 0;

    tail = 0;
}

bool SendFrame::toBuffer(char *buffer,int &len)
{
    int index = 0;
    buffer[index++] = 0x7B;
    buffer[index++] = 0x7B;
    buffer[index++] = 0x7B;

    buffer[index++] = 0x00;
    buffer[index++] = 0xB2;

    buffer[index++] = 0x00;
    buffer[index++] = 0xB1;

    buffer[index++] = 0xA1;//信息类型

    datalenth = tercnt * (26+cnogps.size()*2 + 26+cnoglonass.size()*2);

    infolenth = datalenth + 4;
    memcpy(buffer+index,&infolenth,2);

    datatype = 0x0041;
    memcpy(buffer+index,&datatype,2);

    memcpy(buffer+index,&datalenth,2);//数据长度

    buffer[index++] = tercnt;

    //数据内容
    for (int i=0;i<tercnt;i++) {

        buffer[index++] = 1;//系统 GPS

        if(PositionXGPS.size() == PositionYGPS.size()&& PositionXGPS.size() == PositionZGPS.size())
        {
            memcpy(buffer+index,&(PositionXGPS.at(i)),8);
            index += 8;

            memcpy(buffer+index,&(PositionYGPS.at(i)),8);
            index += 8;

            memcpy(buffer+index,&(PositionZGPS.at(i)),8);
            index += 8;
        }

        buffer[index++] = starnumGPS;

        QList<cnoclass> cnoList = cnogps.at(i);
        for(auto cnoValue:cnoList)
        {
            buffer[index++] = cnoValue.sat;
            buffer[index++] = cnoValue.cno;
        }


        buffer[index++] = 4;//系统 Glonass

        if(PositionXGlonass.size() == PositionYGlonass.size()&& PositionXGlonass.size() == PositionZGlonass.size())
        {
            memcpy(buffer+index,&(PositionXGlonass.at(i)),8);
            index += 8;

            memcpy(buffer+index,&(PositionYGlonass.at(i)),8);
            index += 8;

            memcpy(buffer+index,&(PositionZGlonass.at(i)),8);
            index += 8;
        }

        buffer[index++] = starnumGlonass;

        QList<cnoclass> cnoListGlonass = cnoglonass.at(i);
        for(auto cnoValue:cnoListGlonass)
        {
            buffer[index++] = cnoValue.sat;
            buffer[index++] = cnoValue.cno;
        }
    }


    buffer[index++] = tail;

    len = index;
    return buffer;
}
