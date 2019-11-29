#include "basedatalisten.h"

baseDataListen::baseDataListen()
{

}

bool baseDataListen::notifyRcvRawDataFrame(RawDataFrame &dataFrame)
{
    return  false;
}

bool baseDataListen::nodifyrcvframe(RcvFrame &rcvF)
{
    return false;
}
