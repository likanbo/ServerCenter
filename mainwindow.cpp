#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_frmTerMonitor = new Form_TerMonitor();

    DataMgrCenter::GetInstance()->addBaseDataListen(m_frmTerMonitor);

    m_frmTerMonitor->showNormal();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
    m_frmTerMonitor->showNormal();
}
