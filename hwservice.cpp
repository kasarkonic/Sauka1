#include "hwservice.h"
#include "ui_hwservice.h"
#include <Qdebug>
//#include "global.h"
//#include "senslistsform.h"
//#include "actlistform.h"
#include "scale.h"
#include "hwports.h"
#include "rs232.h"


HWService::HWService(Global& global, Rs232&  rs232, QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::HWService)
    , actListForm(global, this)
    , sensListsForm(global, this)
    , global(global)
    , rs232(rs232)


{
    qDebug() << "HWService::HWService";
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, global.backgroundColor); //QColor(255, 0, 0, 127)
    //pal.setColor(QPalette::Window, QColor(242, 219, 238, 0.251));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->move(50, 50);
    ui->setupUi(this);
    timerId = startTimer(1000, Qt::CoarseTimer);
    QString str = "Addres: 0-";
    str.append(QString::number(MAX_DIoutput));
    ui->label_6->setText(str);

    ui->comboBox_use_motor->addItem("M8");
    ui->comboBox_use_motor->addItem("M9");
    ui->comboBox_use_motor->addItem("M4");
    ui->horizontalSlider->setRange(-100,100);
    //updateTimer = new QElapsedTimer();
    //updateTimer->start();

}

HWService::~HWService() {
    delete ui;
}



void HWService::updateDataAn(int row, int val) {
    qDebug() << " REC HWService::updateDataAn(int row) " << row << val;
    sensListsForm.updateData(row);
    actListForm.updateData(row);

    QString str = "An in 0-16   ";

    for (int i = 0;i < 8; i++) {
        str.append(QString::number(global.ANinput4_20[i].value));
        str.append(", ");
    }
    str.append("  ");

    for (int i = 8;i < 16; i++) {
        str.append(QString::number(global.ANinput4_20[i].value));
        str.append(", ");
    }

    ui->label_row7->setText(str);
    //ui->label_row8->setText(str1);

}
void HWService::updateDataDi(int row, bool val) {
    Q_UNUSED(row)
    Q_UNUSED(val)
    // qDebug() << " REC HWService::updateDataDi(int row) " << row << val;
    //sensListsForm.updateData(row);
    //actListForm.updateData(row);

    QString str1 = "Di out 0-31   ";
    QString str2 = "Di out 32-63  ";
    QString str3 = "Di out 64-95  ";
    QString str4 = "Di in 0-31    ";
    QString str5 = "Di in 32-63   ";
    QString str6 = "Di in 64-95   ";

    for (int i = 0; i < 8; i++) {
        str1.append(QString::number(global.DIoutput[i].value)); //global.DIoutput[i].update(); ????   DIOUT(adr,val)
        str2.append(QString::number(global.DIoutput[i + 32].value));
        str3.append(QString::number(global.DIoutput[i + 64].value));
        str4.append(QString::number(global.DIinput[i].value));
        str5.append(QString::number(global.DIinput[i + 32].value));
        str6.append(QString::number(global.DIinput[i + 64].value));

        str1.append(", ");
        str2.append(", ");
        str3.append(", ");
        str4.append(", ");
        str5.append(", ");
        str6.append(", ");
    }

    str1.append("  ");
    str2.append("  ");
    str3.append("  ");
    str4.append("  ");
    str5.append("  ");
    str6.append("  ");

    for (int i = 9; i < 16; i++) {
        str1.append(QString::number(global.DIoutput[i].value));
        str2.append(QString::number(global.DIoutput[i + 32].value));
        str3.append(QString::number(global.DIoutput[i + 64].value));
        str4.append(QString::number(global.DIinput[i].value));
        str5.append(QString::number(global.DIinput[i + 32].value));
        str6.append(QString::number(global.DIinput[i + 64].value));

        str1.append(", ");
        str2.append(", ");
        str3.append(", ");
        str4.append(", ");
        str5.append(", ");
        str6.append(", ");
    }

    str1.append("  ");
    str2.append("  ");
    str3.append("  ");
    str4.append("  ");
    str5.append("  ");
    str6.append("  ");

    for (int i = 16;i < 24; i++) {
        str1.append(QString::number(global.DIoutput[i].value));
        str2.append(QString::number(global.DIoutput[i + 32].value));
        str3.append(QString::number(global.DIoutput[i + 64].value));
        str4.append(QString::number(global.DIinput[i].value));
        str5.append(QString::number(global.DIinput[i + 32].value));
        str6.append(QString::number(global.DIinput[i + 64].value));

        str1.append(", ");
        str2.append(", ");
        str3.append(", ");
        str4.append(", ");
        str5.append(", ");
        str6.append(", ");
    }

    str1.append("  ");
    str2.append("  ");
    str3.append("  ");
    str4.append("  ");
    str5.append("  ");
    str6.append("  ");

    for (int i = 24;i < 32; i++) {
        str1.append(QString::number(global.DIoutput[i].value));
        str2.append(QString::number(global.DIoutput[i + 32].value));
        str3.append(QString::number(global.DIoutput[i + 64].value));
        str4.append(QString::number(global.DIinput[i].value));
        str5.append(QString::number(global.DIinput[i + 32].value));
        str6.append(QString::number(global.DIinput[i + 64].value));

        str1.append(", ");
        str2.append(", ");
        str3.append(", ");
        str4.append(", ");
        str5.append(", ");
        str6.append(", ");
    }



    ui->label_row1->setText(str1);
    ui->label_row2->setText(str2);
    ui->label_row3->setText(str3);
    ui->label_row4->setText(str4);
    ui->label_row5->setText(str5);
    ui->label_row6->setText(str6);

    QString str = "M8 ETA: ";
    str.append(QString::number(global.DIoutput[drive_M8_status].value,16));    // hex
    ui->label_ETA->setText(str);

}

void HWService::updateDIoutput(int row, int val) {
    Q_UNUSED(row)
    Q_UNUSED(val)
    //qDebug() << " REC HWService::updateDIoutput(int row) " << row << val;
    //  actListForm.updateDIoutput(row,val);
    //modbuss
}

void HWService::timerEvent(QTimerEvent* event) {
    Q_UNUSED(event)
    // float volt24 = global.ANinput4_20 [15].value * 0.020797;//  voltage input   BBBBBBBB   wrong addres
    // float volt24 = SUPLAY_24V/100.0;//  power supplay input
    //     qDebug() << " HWService::timerEven " << global.getTick();
    int volt24 = global.ANinput4_20[SUPLAY_24V].value;
    QString v24 = QString::number(volt24 / 100.0, 'g', 4);

    QString str = "24V Barošanas bloka spriegums = ";

    ui->textEdit->clear();
    str.append(v24);
    str.append(" V");
    ui->textEdit->setText(str);

    QString noteTxt = "bit0  = 1: Ready to switch on, awaiting power section line supply\n";
    noteTxt.append("bit1  = 1: Switched on, ready\n");
    noteTxt.append("bit2  = 1: Operation enabled, running\n");
    noteTxt.append("bit3  = 1: Fault detection\n");
    noteTxt.append("bit4  Voltage enabled  0: not conn,  1: connected\n");
    noteTxt.append("bit5  = 0 quick stop\n");
    noteTxt.append("bit6  =  switched on disable\n");
    noteTxt.append("bit7  = 0: not warning  1: warning\n\n");
    noteTxt.append("bit8  = 0 reserved\n");
    noteTxt.append("bit9  = 0 cmd from LCD  1: cmd from fieldbus\n");
    noteTxt.append("bit10  = 0: reference not reach target   1: reach target\n");
    noteTxt.append("bit11  = 0: reference in internal limits  1: out of limits\n");
    noteTxt.append("bit12  = 0 reserved\n");
    noteTxt.append("bit13  = 0 reserved\n");
    noteTxt.append("bit14  = 0: Stop key not active  1: StopKey active\n");
    noteTxt.append("bit15  = 0: forvard direction 1: revers direction\n");

    ui->textEdit->append(noteTxt);














    if(global.dev3ConnectStatus){
        updateDataDi(0, 0);
        updateDataAn(0, 0);
    }

}

void HWService::on_pushButton_actuator_clicked() {
    qDebug() << "on_pushButton_actuator_clicked";
    //ActListForm *actListForm = new ActListForm(global,this);
    actListForm.show();
}


void HWService::on_pushButton_sensor_clicked() {
    qDebug() << "on_pushButton_sensor_clicked";
    // SensListsForm *sensListsForm = new SensListsForm(global,this);
    sensListsForm.show();
}

void HWService::on_pushButton_Scales_clicked() {
    qDebug() << "on_pushButton_scale_clicked";
    Scale* scale = new Scale(global, this);
    scale->show();
}


void HWService::on_pushButton_Com_Ports_clicked() {
    qDebug() << "on_pushButton_Com_Ports_clicked";
    HwPorts* hwPorts = new HwPorts(global, this);
    hwPorts->show();
    hwPorts->updateUI();
}

void HWService::on_pushButton_measure_clicked()
{
    // Rs232* rs232 = new Rs232(global, this);
    rs232.show();

}


void HWService::on_pushButton_Out_write_clicked() {
    //int id = 4;
    if (out_value >= 1 && out_address < 96) { // 96,97.. inverter
        out_value = 1;
    }
    if (out_address >= MAX_DIoutput) {
        ui->lineEdit_Out_address->setText("ERROR!");
        out_address = 63;//
    }


    global.actList[out_address].digital = (bool)out_value;
    global.updateDataOut.need = true;

    qDebug() << "---------------------------------emit 1outputChange "  << out_address << out_value;
    //emit outputChange(id, out_address,out_value);   // function code 06, out_value  on = 100,  off 200    out_address  0-32



    global.DIoutput[out_address].value = out_value;
    global.DIoutput[out_address].update = true;
    //qDebug() << " DIoutput[" << tempInt << "] = 1" << global.getTick() << "\n";
    emit diOutputChangeSi(out_address, global.DIoutput[out_address].value);


}


void HWService::on_lineEdit_Out_address_editingFinished() {

    out_address = ui->lineEdit_Out_address->text().toInt(&ok);
    qDebug() << "out_address " << out_address << ok;
    if (!ok) {
        ui->lineEdit_Out_address->setText("ERROR!");
        out_address = 0;
    }
}


void HWService::on_lineEdit_Out_value_editingFinished() {
    out_value = ui->lineEdit_Out_value->text().toInt(&ok);
    qDebug() << "out_value " << out_value << ok;
    if (!ok) {
        ui->lineEdit_Out_value->setText("ERROR!");
        out_value = 0;
    }
}


void HWService::on_comboBox_use_motor_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        testMotorAddres = M8;
        break;
    default:
    case 1:
        testMotorAddres = M9;
        break;
    case 2:
        testMotorAddres = M4;
        break;
        testMotorAddres = 0;
    }

    qDebug() << "Motor test address" << index << testMotorAddres;


}

/*
#define CMD_REG  8501
#define LFR_REG  8502
#define LFRD_REG 8602
#define HMIS_REG 3240
*/
void HWService::on_pushButton_Motor_off_clicked(bool checked)
{
    Q_UNUSED(checked)
    param.boardAdr = testMotorAddres;
    param.regAdr = CMD_REG;
    param.value = 7;
    param.cmd = WR_REG;
    global.rs485WrList.append(param);

    //QString str = "Motor On";
    //ui->pushButton_Motor_on->setText(str);
}


void HWService::on_pushButton_Reset_clicked()
{
    param.boardAdr = testMotorAddres;

    param.regAdr = CMD_REG;
    param.value = 128;
    param.len = 1;
    param.cmd = WR_REG;
    global.rs485WrList.append(param);
}


void HWService::on_pushButton_Motor_on_clicked()
{

    param.boardAdr = testMotorAddres;
    param.value = 128;          // ??????????????? reset
    param.regAdr = CMD_REG;
    param.len = 1;
    param.cmd = WR_REG;
    global.rs485WrList.append(param);

    param.value = 6;
    global.rs485WrList.append(param);

    param.value = 7;
    global.rs485WrList.append(param);

    param.value = 15;
    global.rs485WrList.append(param);

    QString str;// = "Atrums: ";
    str.append(QString::number(rpm)) ;
    str.append(" rpm");

    ui->label_slider_center->setText(str);
}


void HWService::on_horizontalSlider_valueChanged(int value)
{
    int koef = 10;
    rpm = value * koef;    // koef for diferrent motors?
    qDebug() << "Motor speed rpm" << value;
    param.boardAdr = testMotorAddres;

    param.regAdr = LFRD_REG;
    param.value = rpm;
    param.len = 1;
    param.cmd = WR_REG;
    global.rs485WrList.append(param);

    QString str;// = "Atrums: ";
    str.append(QString::number(rpm)) ;
    str.append(" rpm");
    ui->label_slider_center->setText(str);
}


void HWService::on_pushButton_slider_minus_clicked(bool checked)
{
    Q_UNUSED(checked)
    int val =  ui->horizontalSlider->value();
    if(val > - 100){
        val--;
        ui->horizontalSlider->setValue(val);
        on_horizontalSlider_valueChanged(val);
    }
}


void HWService::on_pushButton_slider_plus_clicked()
{
    int val =  ui->horizontalSlider->value();
    if(val < 100){
        val++;
        ui->horizontalSlider->setValue(val);
        on_horizontalSlider_valueChanged(val);
    }
}


void HWService::on_pushButton_get_error_code_clicked()
{
    param.boardAdr = testMotorAddres;

    param.regAdr = ERRD;
   // param.value = 0;
    param.len = 1;
    param.cmd = RD_REG;
    global.rs485WrList.append(param);


    param.regAdr = SAF1;
    //param.value = 0;
    param.len = 14;
    param.cmd = RD_REG;
    global.rs485WrList.append(param);

}

