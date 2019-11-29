#include "form_termonitor.h"
#include "ui_form_termonitor.h"

Form_TerMonitor::Form_TerMonitor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_TerMonitor)
{
    ui->setupUi(this);
    m_devFrm.clear();

    //ui->tableWidget->setTextElideMode(QAbstractItemView::NoEditTriggers);
    //ui->tableWidget->setRowCount(100);
    //ui->tableWidget->setColumnCount(4);
}

Form_TerMonitor::~Form_TerMonitor()
{
    delete ui;
}

bool Form_TerMonitor::nodifyrcvframe(RcvFrame &rcvF)
{
    qDebug() << rcvF.remote;



    try
    {
        if(m_devList.contains(rcvF.devID))//if(m_devFrm.contains(rcvF.devID))
        {
            for (int i=0;i<ui->tableWidget->rowCount();i++)
            {
                QTableWidgetItem *item = ui->tableWidget->item(i,1);//设备ID
                if(item->text() == QString::number(rcvF.devID))
                {
                     int colIndex = 0;

                    item = ui->tableWidget->item(i,colIndex++);//IP地址
                    item->setText(rcvF.remote);

                    item = ui->tableWidget->item(i,colIndex++);//设备ID
                    item->setText(QString::number(rcvF.devID));

                    item = ui->tableWidget->item(i,colIndex++);//接收卫星数
                    item->setText(QString::number(rcvF.gpsRaw.numMeas));

                    item = ui->tableWidget->item(i,colIndex++);//接收卫星数
                    item->setText(QString::number(rcvF.glonassRaw.numMeas));


                    item = ui->tableWidget->item(i,colIndex++);//GPS定位状态
                    item->setText(rcvF.gpsGGA.GetPosState());

                    item = ui->tableWidget->item(i,colIndex++);//GPS定位状态
                    item->setText(rcvF.glonassGGA.GetPosState());

                }
            }
        }
        else
        {
            ui->tableWidget->insertRow(0);
            int cols = ui->tableWidget->columnCount();
            int rows = 0;
            int colIndex = 0;

            QTableWidgetItem *newItem = new QTableWidgetItem(rcvF.remote);
            ui->tableWidget->setItem(rows,colIndex++,newItem);//IP地址

            newItem = new QTableWidgetItem(QString::number(rcvF.devID));
            ui->tableWidget->setItem(rows,colIndex++,newItem);//设备ID

            newItem = new QTableWidgetItem(QString::number(rcvF.gpsRaw.numMeas));
            ui->tableWidget->setItem(rows,colIndex++,newItem);//接收卫星数

            newItem = new QTableWidgetItem(QString::number(rcvF.glonassRaw.numMeas));
            ui->tableWidget->setItem(rows,colIndex++,newItem);//接收卫星数


            newItem = new QTableWidgetItem(rcvF.gpsGGA.GetPosState());
            ui->tableWidget->setItem(rows,colIndex++,newItem);//GPS定位状态

            newItem = new QTableWidgetItem(rcvF.glonassGGA.GetPosState());
            ui->tableWidget->setItem(rows,colIndex++,newItem);//Glonass定位状态

            m_devList << rcvF.devID;
        }

    } catch (QException ex) {

    }

    return  true;
}
