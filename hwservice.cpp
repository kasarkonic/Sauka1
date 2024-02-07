#include "hwservice.h"
#include "ui_hwservice.h"
#include <Qdebug>
#include "global.h"
#include "hwlistsform.h"


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
    HWListsForm *hwListForm = new HWListsForm(global,this);
    hwListForm->show();
}


void HWService::on_pushButton_sensor_clicked()
{
 qDebug() << "on_pushButton_sensor_clicked";
}


void HWService::on_pushButton_invertor_clicked()
{
 qDebug() << "on_pushButton_invertor_clicked";
}

