#ifndef FORM_TERMONITOR_H
#define FORM_TERMONITOR_H

#include <QWidget>
#include "form_ter.h"
#include "basedatalisten.h"

namespace Ui {
class Form_TerMonitor;
}

class Form_TerMonitor : public QWidget,public baseDataListen
{
    Q_OBJECT

public:
    explicit Form_TerMonitor(QWidget *parent = nullptr);
    ~Form_TerMonitor();

    virtual bool nodifyrcvframe(RcvFrame &rcvF);

    QMap<int,Form_Ter*> m_devFrm;
    QList<int> m_devList;
private:
    Ui::Form_TerMonitor *ui;
};

#endif // FORM_TERMONITOR_H
