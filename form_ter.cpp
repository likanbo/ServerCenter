#include "form_ter.h"
#include "ui_form_ter.h"

Form_Ter::Form_Ter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_Ter)
{
    ui->setupUi(this);
}

Form_Ter::~Form_Ter()
{
    delete ui;
}

void Form_Ter::updatedata(QString ipdesc, int devID, RawDistance &rawDis)
{
    ui->label_ip->setText(ipdesc);
    ui->label_dev_id->setText(QString::number(devID));
}
