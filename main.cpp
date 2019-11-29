#include "mainwindow.h"

#include <QApplication>
#include <QDir>
#include "commondata.h"
#include "datamgrcenter.h"
#include "ServerTcp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString dataDir = QDir::currentPath()+"/data/";

    QDir dirData(dataDir);
    if(!dirData.exists()){
        dirData.mkdir(dataDir);
    }
    CommonData::GetInstance()->SetDataDir(dataDir);


    QString rcvDir = dataDir + "rcv/";
    QDir dirrcv(rcvDir);
    if(!dirrcv.exists()){
        dirrcv.mkdir(rcvDir);
    }
    CommonData::GetInstance()->SetRcvDir(rcvDir);

    QString sndDir = dataDir + "snd/";
    QDir dirsnd(sndDir);
    if(!dirsnd.exists()){
        dirsnd.mkdir(sndDir);
    }
    CommonData::GetInstance()->SetSndDir(sndDir);

    DataMgrCenter::GetInstance();


    MainWindow w;
    w.show();
    return a.exec();
}
