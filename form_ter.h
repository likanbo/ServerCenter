#ifndef FORM_TER_H
#define FORM_TER_H

#include <QWidget>
#include "rcvframe.h"

namespace Ui {
class Form_Ter;
}

class Form_Ter : public QWidget
{
    Q_OBJECT

public:
    explicit Form_Ter(QWidget *parent = nullptr);
    ~Form_Ter();

    void updatedata(QString ipdesc,int devID, RawDistance &rawDis);

private:
    Ui::Form_Ter *ui;
};

#endif // FORM_TER_H
