#include "commondata.h"

CommonData* CommonData::m_pInstance = nullptr;

CommonData::CommonData()
{

}

CommonData *CommonData::GetInstance()
{
   if(m_pInstance == nullptr){
       m_pInstance = new CommonData();
   }

   return m_pInstance;
}

RawDataFrame::RawDataFrame()
{

}

RawDataFrame::RawDataFrame(const RawDataFrame &frame)
{
    m_dataDesc = frame.m_dataDesc;
    m_Buffer = frame.m_Buffer;
}

RawDataFrame::RawDataFrame(QByteArray dataArr, QString desc)
{
    m_Buffer = dataArr;
    m_dataDesc = desc;
}
