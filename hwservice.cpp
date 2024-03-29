#include "hwservice.h"
#include "ui_hwservice.h"
#include <Qdebug>
//#include "global.h"
//#include "senslistsform.h"
//#include "actlistform.h"
#include "scale.h"
#include "hwports.h"


HWService::HWService(Global &global, QWidget *parent)
    : QMainWindow(parent)
    , global(global)
    , ui(new Ui::HWService)
    , actListForm(global,this)
    , sensListsForm(global,this)


{
   qDebug() << "HWService::HWService";
   QPalette pal = QPalette();
   pal.setColor(QPalette::Window,global.backgroundColor); //QColor(255, 0, 0, 127)
   //pal.setColor(QPalette::Window, QColor(242, 219, 238, 0.251));
   this->setAutoFillBackground(true);
   this->setPalette(pal);
   ui->setupUi(this);
   ui->lineEdit_Input_address->setText("0");
   timerId = startTimer(1000, Qt::CoarseTimer);

}

HWService::~HWService()
{
    delete ui;
}

void HWService::updateDataAn(int row, int val)
{
    qDebug() << " REC HWService::updateDataAn(int row) " << row << val;
    sensListsForm.updateData(row);
    actListForm.updateData(row);
}
void HWService::updateDataDi(int row, bool val)
{
    qDebug() << " REC HWService::updateDataDi(int row) " << row << val;
    sensListsForm.updateData(row);
    actListForm.updateData(row);
}

void HWService::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)
    float volt24 = global.ANinput4_20[15].An * 0.020797;//  voltage input
    qDebug() << "HWService::timerEvent " << volt24;
    QString str = "24V Barošanas bloka spriegums = ";
    str.append(QString::number(volt24));
    str.append("V");
    ui->textEdit->setText(str);
}

void HWService::on_pushButton_actuator_clicked()
{
    qDebug() << "on_pushButton_actuator_clicked";
    //ActListForm *actListForm = new ActListForm(global,this);
    actListForm.show();
}


void HWService::on_pushButton_sensor_clicked()
{
 qDebug() << "on_pushButton_sensor_clicked";
   // SensListsForm *sensListsForm = new SensListsForm(global,this);
    sensListsForm.show();
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
    hwPorts->updateUI();
}


void HWService::on_pushButton_ReadBaudR_clicked()
{
    emit setBaudrate(modbusAddress);

/*
 *
 *
 *
 *
 * For example 1, Change the baud rate to 4800bps:
Send data(address 1):01 06 00 FE 00 02 69 FB
Return data :01 06 00 FE 00 02 69 FB
Baud rate corresponds to the number: 0:1200 1:2400 2:4800 3:9600
4:19200 5:38400 6:57600 7: 115200 8: Factory reset
Note: 1 The baud rate will be updated only when the module


*/
}


void HWService::on_lineEdit_Input_address_editingFinished()
{
    bool ok = true;

    int val = ui->lineEdit_Input_address->text().toInt(&ok);
    if(!ok){
        val = 0;;
    }
    modbusAddress = val;
    qDebug() << "input address" <<modbusAddress;

}


void HWService::on_pushButton_ChangeAddress_clicked()
{

    emit factoryReset(modbusAddress);
    emit setBaudrate(modbusAddress);
    /*
     * Send data(address is 1): 01 06 00 FD 00 02 99 FB
Return data : 01 06 00 FD 00 02 99 FB
Send data(don't know the address): FF 06 00 FD 00 02 8C 25
Return data : FF 06 00 FD 00 02 8C 25
*/

}


void HWService::on_pushButton_FactoryReset_clicked()
{
     emit factoryReset(modbusAddress);

  /*  Modbus Address(PLC)：40252
        RS485 address : 0x01~0x3F
        Function code:Write 0x06;
    Register address:0x00FB(251)
        Send data(address 1):FF 06 00 FB 00 00 ED E5
            Return data :FF 06 00 FB 00 00 ED E5
*/
}

