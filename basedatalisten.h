#ifndef BASEDATALISTEN_H
#define BASEDATALISTEN_H
#include "commondata.h"
#include "rcvframe.h"

class baseDataListen
{
public:
    baseDataListen();
    virtual ~baseDataListen(){}

    virtual bool notifyRcvRawDataFrame(RawDataFrame &dataFrame);
    virtual bool nodifyrcvframe(RcvFrame &rcvF);
};

#endif // BASEDATALISTEN_H
