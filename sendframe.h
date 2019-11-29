#ifndef SENDFRAME_H
#define SENDFRAME_H
#include <QException>
#include <QString>

#define TER_CNT 100

class cnoclass{
public:
    cnoclass(){};
    cnoclass(char _sat,int _cno)
    {
        sat = _sat;
        cno = _cno;
    }
    cnoclass(const cnoclass& cnocla){
        sat = cnocla.sat;
        cno = cnocla.cno;
    }
public:
    char sat;
    int cno;
};
class SendFrame
{
public:
    SendFrame();

    char header[3];
    unsigned int sour;
    unsigned int dest;
    char infotype;
    unsigned int infolenth;
    unsigned int datatype;
    unsigned int datalenth;

    int tercnt;

    QList<double> PositionXGPS;
    QList<double> PositionYGPS;
    QList<double> PositionZGPS;
    QList<QList<cnoclass>> cnogps;//干扰前载噪比


    QList<QList<cnoclass>> cnoglonass;
    QList<double> PositionXGlonass;
    QList<double> PositionYGlonass;
    QList<double> PositionZGlonass;

    QList<int> R_type;
    int starnumGPS;
    int starnumGlonass;

    char tail;

    bool toBuffer(char *buffer,int &len);
};

#endif // SENDFRAME_H
