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
    , ui(new Ui::HWService)
    , actListForm(global,this)
    , sensListsForm(global,this)
    , global(global)


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

    QString str;
    QString str1;
    for(int i = 0;i < 8; i++){
       str.append(QString::number(global.sensList[i].analog));
       str1.append(QString::number(global.sensList[i + 8 ].analog));

       str.append(", ");
       str1.append(", ");
    }
    ui->label_row5->setText(str);
    ui->label_row6->setText(str1);



}
void HWService::updateDataDi(int row, bool val)
{
    qDebug() << " REC HWService::updateDataDi(int row) " << row << val;
    sensListsForm.updateData(row);
    //actListForm.updateData(row);

    QString str;
    QString str1;
    QString str2;
    QString str3;

    for(int i = 0;i < 16; i++){
       str.append(QString::number(global.sensList[i].digital));
       str1.append(QString::number(global.sensList[i + 16 ].digital));
       str2.append(QString::number(global.sensList[i + 32].digital));
       str3.append(QString::number(global.sensList[i + 48 ].digital));
       str.append(", ");
       str1.append(", ");
       str2.append(", ");
       str3.append(", ");
    }
    ui->label_row1->setText(str);
    ui->label_row2->setText(str1);
    ui->label_row3->setText(str2);
    ui->label_row4->setText(str3);




}

void HWService::updateDIoutput(int row, int val)
{
      qDebug() << " REC HWService::updateDIoutput(int row) " << row << val;
  //  actListForm.updateDIoutput(row,val);
    //modbuss
}

void HWService::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)
  // float volt24 = global.ANinput4_20 [15].value * 0.020797;//  voltage input   BBBBBBBB   wrong addres
  // float volt24 = SUPLAY_24V/100.0;//  power supplay input

    int volt24 =  SUPLAY_24V ;
    QString v24 = QString::number(volt24/100.0, 'g', 4);

    QString str = "24V Barošanas bloka spriegums = ";

    str.append(v24);
    str.append(" V");
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


void HWService::on_pushButton_Disable_clicked()
{
    global.disableRS485 = !global.disableRS485;
    QString str = "Eable RS485";
    if(global.disableRS485){
        str = "Disable RS485";
    }
    ui->pushButton_Disable->setText(str);
}


void HWService::on_pushButton_Out_write_clicked()
{
    int id = 4;
    if(out_value >= 1){
        out_value = 1;
    }
    if(out_address >= MAX_DIinput){
        ui->lineEdit_Out_address->setText("ERROR!");
        out_address = 63;//
    }


     global.actList[out_address].digital= (bool)out_value;
     global.updateDataOut.need = true;

    qDebug() << "---------------------------------emit 1outputChange " << id << out_address << out_value;
    //emit outputChange(id, out_address,out_value);   // function code 06, out_value  on = 100,  off 200    out_address  0-32



    global.DIoutput[out_address].value = out_value;
    //qDebug() << " DIoutput[" << tempInt << "] = 1" << global.getTick() << "\n";
    emit diOutputChangeSi(out_address,global.DIoutput[out_address].value);


}


void HWService::on_lineEdit_Out_address_editingFinished()
{

    out_address = ui->lineEdit_Out_address->text().toInt(&ok);
    qDebug() << "out_address " << out_address << ok;
    if(!ok){
        ui->lineEdit_Out_address->setText("ERROR!");
        out_address = 0;
    }
}


void HWService::on_lineEdit_Out_value_editingFinished()
{
    out_value = ui->lineEdit_Out_value->text().toInt(&ok);
    qDebug() << "out_value " << out_value << ok;
    if(!ok){
        ui->lineEdit_Out_value->setText("ERROR!");
        out_value = 0;
    }
}

