#include "hwservice.h"
#include "ui_hwservice.h"
#include <Qdebug>
#include "global.h"
#include "senslistsform.h"
#include "actlistform.h"
#include "scale.h"
#include "hwports.h"


HWService::HWService(Global &global, QWidget *parent)
    : QMainWindow(parent)
    , global(global)
    , ui(new Ui::HWService)


{
   qDebug() << "HWService::HWService";

   ui->setupUi(this);

}

HWService::~HWService()
{
    delete ui;
}

void HWService::on_pushButton_actuator_clicked()
{
    qDebug() << "on_pushButton_actuator_clicked";
    ActListForm *actListForm = new ActListForm(global,this);
    actListForm->show();
}


void HWService::on_pushButton_sensor_clicked()
{
 qDebug() << "on_pushButton_sensor_clicked";
    SensListsForm *sensListsForm = new SensListsForm(global,this);
    sensListsForm->show();
}

void HWService::on_pushButton_Scales_clicked()
{
    qDebug() << "on_pushButton_scale_clicked";
       Scale *scale = new Scale(global,this);
       scale->show();
}


void HWService::on_pushButton_Com_Ports_clicked()
{
    qDebug() << "on_pushButton_Com_Ports_clicked";
    HwPorts *hwPorts = new HwPorts(global,this);
    hwPorts->show();
}

