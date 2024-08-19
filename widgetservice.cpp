#include "widgetservice.h"
#include "ui_widgetservice.h"
#include<QMouseEvent>
#include <QSettings>
//#include "global.h"
//#include "widgetdiagramelement.h"


WidgetService::WidgetService(Global& global, WidgetDiagramElement* widgetElement, QWidget* parent)

    : QWidget(parent)
    , global(global)
    , ui(new Ui::WidgetService)
    , widgetElement(widgetElement) {
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, global.backgroundColor); //QColor(255, 0, 0, 127)
    //pal.setColor(QPalette::Window, QColor(242, 219, 238, 0.251));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    currentWid = widgetElement->settings.name;
    currentWidnpk = widgetElement->settings.npk;
    widgetElement->global.widHash[currentWid].ptrCurrWidgetService = this;

    qDebug() << "currentWid name " << currentWid << widgetElement->global.widHash[currentWid].ptrCurrWidgetService;
    ui->setupUi(this);
    //qDebug() << "???" << widgetElement->global.widHash[currentWid].startX << widgetElement->global.widHash[currentWid].startY  ;
    setWindowTitle(currentWid);
    // addresAct = widgetElement->global.widHash[currentWid].act_Addres1;
    //addresSens1 = widgetElement->global.widHash[currentWid].sensAddres1;
    // addresSens2 = widgetElement->global.widHash[currentWid].sensAddres2;
    //qDebug() << "addresAct,sens1,sens2" << addresAct << addresSens1 << addresSens2;

    ui->label_0_1->setText("Ieejas/izejas nosaukums");
    ui->label_0_2->setText("Adrese");
    ui->label_0_3->setText("Vērtība");
    ui->horizontalSlider_speed->setRange(-100,100);
    ui->horizontalSlider_speed->setValue(50);

    updateFormData();   // data from global. ...
    timerId = startTimer(100);
}
void WidgetService::openWidgetServiceForm() {
    qDebug() << "WidgetSrv Open service pipe ??? : ";

    this->show();
}

WidgetService::~WidgetService() {
    widgetElement->global.widHash[currentWid].ptrCurrWidgetService = nullptr;
    qDebug() << "WidgetService::~WidgetService()";
    delete ui;
}


void WidgetService::updateFormData()        // read data from global and display in to UI
{
    //geometry data
    ui->labelName->setText(widgetElement->global.widHash[currentWid].name);
    ui->lineEdit_Xpos->setText(QString::number(widgetElement->global.widHash[currentWid].startX));
    ui->lineEdit_Ypos->setText(QString::number(widgetElement->global.widHash[currentWid].startY));
    ui->lineEdit_startSize->setText(QString::number(widgetElement->global.widHash[currentWid].startSize));
    // ui->lineEdit_options->setText(QString::number(widgetElement->global.widHash[currentWid].options));

    widgetElement->updateSettings();


    QString str;
    QString strDeg = QChar(0x00b0);

    switch (widgetElement->global.widHash[currentWid].type) {

    case WidgetType::widgT::Tvertne:

        /*
         * Widget Tvertne
         *
         * avārijas līmeņa sensors sensList[sensor address].digital.
         * līmeņa sensors sensList[sensor address].analog.
         *
         */
        {
            currentWidnpk = widgetElement->settings.npk;
            int level = widgetElement->settings.var1;
            int full = widgetElement->settings.var2;

            int levelv = global.DIinput[level].value;
            int fullv =  global.DIinput[full].value;

            str = "Izvēlēts elements \"TVERTNE \"\n";
            str.append("IN1 tvertnes līmenis\n");

            str.append(QString::number(currentWidnpk));
            str.append("\nIN2 drošības līmeņa devējs\n");

            ui->label1_1->setText("Līmenis tvertnē %");
            ui->label2_1->setText("Pilnas Tv. devējs");
            ui->label3_1->setText("Temperatūra C" + strDeg);

            ui->label4_1->setText("Sensoru kalibrēšana");
            ui->label5_1->setText("Kalibrēt pilnu Tv.");
            ui->label6_1->setText("Kalibrēt tukšu Tv");

            ui->label1_2->setText(QString::number(level));
            ui->label2_2->setText(QString::number(full));

            ui->label3_2->setText("-");
            ui->label4_2->setText("Kalibrēšanas vērtība");
            //ui->lineEdit_5_2->hide();
            //ui->lineEdit_6_2->hide();

            ui->label1_3->setText(QString::number(levelv));
            ui->label2_3->setText(QString::number(fullv));


            switch (currentWidnpk) {
            case 0:
                ui->label3_3->setText(QString::number(global.DIinput[TVERTNE1TEMP].value));
                ui->label4_2->setText(QString::number(global.DIinput[TVERTNE1LEVEL].value));

                break;
            case 1:
                ui->label3_3->setText(QString::number(global.DIinput[TVERTNE2TEMP].value));
                ui->label4_2->setText(QString::number(global.DIinput[TVERTNE2LEVEL].value));
                break;
            case 2:
                ui->label3_3->setText(QString::number(global.DIinput[TVERTNE3TEMP].value));
                ui->label4_2->setText(QString::number(global.DIinput[TVERTNE3LEVEL].value));
                break;
            case 3:
                ui->label3_3->setText(QString::number(global.DIinput[TVERTNE4TEMP].value));
                ui->label4_2->setText(QString::number(global.DIinput[TVERTNE4LEVEL].value));
                break;
            case 4:
                ui->label3_3->setText(QString::number(global.DIinput[TVERTNE5TEMP].value));
                ui->label4_2->setText(QString::number(global.DIinput[TVERTNE1LEVEL].value));
                break;
            default:
                break;
            }


            ui->label4_3->setText("Saglabāt");
            ui->pushButton_5_3->setText("Pilna Tv.");
            ui->pushButton_6_3->setText("Tukša Tv.");

        }


        break;

    case WidgetType::widgT::Valve:  //??????????????????????????



        {
            int outOpen = global.ballValveList[currentWidnpk].bValvePtr->outOpen;    // output address
            int outClose = global.ballValveList[currentWidnpk].bValvePtr->outClose;
            int inOpen = global.ballValveList[currentWidnpk].bValvePtr->inOpen;
            int inClose = global.ballValveList[currentWidnpk].bValvePtr->inClose;

            int outOpenv = global.DIoutput[outOpen].value;    // output address
            int outClosev = global.DIoutput[outClose].value;
            int inOpenv = global.DIinput[inOpen].value;
            int inClosev = global.DIinput[inClose].value;

            int openTime = global.ballValveList[currentWidnpk].bValvePtr->getOpenTime();
            int closeTime = global.ballValveList[currentWidnpk].bValvePtr->getCloseTime();


            ui->label1_2->setText(QString::number(inOpen));
            ui->label2_2->setText(QString::number(inClose));
            ui->label3_2->setText(QString::number(outOpen));
            ui->label4_2->setText(QString::number(outClose));

            ui->label1_3->setText(QString::number(inOpenv));
            ui->label2_3->setText(QString::number(inClosev));
            ui->label3_3->setText(QString::number(outOpenv));
            ui->label4_3->setText(QString::number(outClosev));



            QString str1 = QString::number((closeTime/10));
            str1.append(".");
            str1.append(QString::number((int)closeTime%10));
            str1.append(" s");
            ui->lineEdit_5_2->setText(str1);

            str1 = QString::number((openTime/10));
            str1.append(".");
            str1.append(QString::number((int)openTime%10));
            str1.append(" s");
            ui->lineEdit_6_2->setText(str1);

            ui->pushButton_5_3->setText(" Aizvērt vārstu");
            ui->pushButton_6_3->setText("Atvērt vārstu");

            str = "Izvēlēts elements \"Valve \"\n";
            str.append("ON OFF islēdz/ atslēdz vārstu motoru\n");
            str.append("DI1 atvērta vārsta gala slēdzis.\n");
            str.append("DI2 aizvērta vārsta gala slēdzis.\n");
            str.append("Options iestāda vārsta leņķi 0-90\u00B0.\n");
            str.append("0\u00B0 horizontāls, 90\u00B0n vertilāls\n");
            str.append(str1);

            //str.append(strDeg);
            //str.append(" .\n");

            ui->label1_1->setText("In vārsts vaļā");
            ui->label2_1->setText("In vārsts ciet");
            ui->label3_1->setText("Out atvērt vārstu");
            ui->label4_1->setText("Out aizvērt vārstu");
            ui->label5_1->setText("Aizvēršanās laiks");
            ui->label6_1->setText("Atvēršanās laiks");

        }

        break;

    case WidgetType::widgT::Pump:

        /*
         * Widget Pump
         * var1  - on/off  forvard
         * var2   - on/off   revers
         */

        str = "Izvēlēts sūknis \"Pump \"\n";
        str.append("Aktuators maina motora griežšanās ātrumu un virzienu\n");
        str.append("IN1 = 0 izslēdz, IN1 > 0 ieslēdz motoru\n");
        ui->label1_1->setText("Ieslēgts turp");
        ui->label2_1->setText("Ieslēgts atpakaļ");
        ui->label3_1->setText("");
        ui->label4_1->setText("");
        if( currentWidnpk == 0){
            ui->label5_1->setText("Ieslēgt/Izslēgt Turp");
            ui->label6_1->setText("Ieslēgt/Izslēgt Atpakaļ");

            ui->pushButton_5_3->setText("Turp");
            ui->pushButton_6_3->setText("Atpakaļ");


        }

        else if ( currentWidnpk == 1){       // pump 2.2
            actualMotorNode = M4;
            gearrate = 10;
            ui->label1_1->setText("Ātrums");
            ui->label2_1->setText("Statuss");
            ui->label3_1->setText("Kļūda");
            ui->label4_1->setText("MODBUS node");
            ui->label5_1->setText("Ieslēgt ");
            ui->label6_1->setText("Izslēgt ");

            ui->label1_2->setText(QString::number(On_Pump_2_speed));
            ui->label2_2->setText(QString::number(0));
            ui->label3_2->setText(QString::number(0));
            ui->label4_2->setText(QString::number(actualMotorNode));
            ui->lineEdit_5_2->hide();
            ui->lineEdit_6_2->hide();

            ui->label1_3->setText(QString::number(13));
            ui->label2_3->setText(QString::number(23));
            ui->label3_3->setText(QString::number(33));
            ui->label4_3->setText("");
            ui->pushButton_5_3->setText("Ieslēgt");
            ui->pushButton_6_3->setText("Izslēgt");

            ui->line_14->hide();
            ui->line_15->hide();
            ui->line_16->hide();
            ui->line_17->hide();
            ui->line_18->hide();
            ui->line_19->hide();
            ui->line_20->hide();
            ui->line_21->hide();

        }

        else{
            ui->label5_1->setText("Ieslēgt sūkni");
            ui->label6_1->setText("Izslēgt sūkni");
            ui->pushButton_5_3->setText("Ieslēgt");
            ui->pushButton_6_3->setText("Izslēgt");
        }

        // ui->pushButton_5_3->setText("Ieslēgt Turp");
        // ui->pushButton_6_3->setText("Izslēgt Atpakaļ");

        ui->label1_2->setText(QString::number(widgetElement->settings.var1));
        ui->label2_2->setText(QString::number(widgetElement->settings.var2));
        ui->label3_2->setText("");
        //ui->label4_2->setText("");
        ui->lineEdit_5_2->hide();
        ui->lineEdit_6_2->hide();

        ui->label1_3->setText(QString::number(global.DIoutput[widgetElement->settings.var1].value));
        ui->label2_3->setText(QString::number(global.DIoutput[widgetElement->settings.var2].value));
        ui->label3_3->setText("");
        ui->label4_3->setText("");
        // ui->pushButton_5_3->setText("Ieslēgt");
        // ui->pushButton_6_3->setText("Izslēgt");

        ui->line_14->hide();
        ui->line_15->hide();
        ui->line_16->hide();
        ui->line_17->hide();
        ui->line_18->hide();
        ui->line_19->hide();
        ui->line_20->hide();
        ui->line_21->hide();

        break;

    case WidgetType::widgT::Dispax:


        //set_dispax_speed


        str = "Izvēlēts sūknis \"DISPAX 3D\"\n";
        //str.append("Ieslēdz / Izslēdz\n");
        str.append("IN1 = 0 ieslēgt / izslēgt motoru");
        ui->label1_1->setText("IN1  ");
        ui->label2_1->setText("");
        ui->label3_1->setText("");
        ui->label4_1->setText("");
        if( currentWidnpk == 0){
            ui->label5_1->setText("Ieslēgt");
            ui->label6_1->setText("Izslēgt");

            ui->label2_2->setText("");
            ui->label3_2->setText("");
            ui->label4_2->setText("");

            ui->label2_3->setText("");
            ui->label3_3->setText("");
            ui->label4_3->setText("");

            ui->pushButton_5_3->setText("ieslēgt");
            ui->pushButton_6_3->setText("izslēgt");
            ui->lineEdit_5_2->setText("");
            ui->lineEdit_6_2->setText("");
            ui->lineEdit_5_2->setDisabled(true);
            ui->lineEdit_6_2->setDisabled(true);
            ui->horizontalSlider_speed->setDisabled(true);









        }


        break;


    case WidgetType::widgT::Mix:
    case WidgetType::widgT::Dyno:
    case WidgetType::widgT::Conveyor:

        /*
         * Widget Mix
         *
         * mikseris act[actList address1].digital.
         * griežšanās ātrums act[actList address1].analog.
         *
         */


        switch (widgetElement->global.widHash[currentWid].type)  {
        case WidgetType::widgT::Mix:
            actualMotorNode = M9;
            gearrate = 9;
            str = "Izvēlēts maisītājs\n";
            break;

        case WidgetType::widgT::Conveyor:
            actualMotorNode = M8;
            gearrate = -28;
            str = "Izvēlēts transportieris\n";

            break;
        default:
            break;
        }


        //str = "Izvēlēts maisītājs \"Mix \"\n";
        // str.append("Aktuators maina motora griežšanās ātrumu\n");
        // str.append("IN1 = 0 izslēdz, IN1 > 0 ieslēdz motoru\n");
        ui->label1_1->setText("Ātrums");
        ui->label2_1->setText("Statuss");
        ui->label3_1->setText("Kļūda");
        ui->label4_1->setText("MODBUS node");
        ui->label5_1->setText("Ieslēgt ");
        ui->label6_1->setText("Izslēgt ");

        ui->label1_2->setText(QString::number(12));
        ui->label2_2->setText(QString::number(22));
        ui->label3_2->setText(QString::number(32));
        ui->label4_2->setText(QString::number(actualMotorNode));
        ui->lineEdit_5_2->hide();
        ui->lineEdit_6_2->hide();

        ui->label1_3->setText(QString::number(13));
        ui->label2_3->setText(QString::number(23));
        ui->label3_3->setText(QString::number(33));
        ui->label4_3->setText("");
        ui->pushButton_5_3->setText("Ieslēgt");
        ui->pushButton_6_3->setText("Izslēgt");

        ui->line_14->hide();
        ui->line_15->hide();
        ui->line_16->hide();
        ui->line_17->hide();
        ui->line_18->hide();
        ui->line_19->hide();
        ui->line_20->hide();
        ui->line_21->hide();

        break;





    case WidgetType::widgT::Pipe:
        str = "Izvēlēta savienojošā caurule \"Pipe \"\n";
        str.append("Options = 0 vertikala, \n");
        str.append("Options = 90 horizontāla, \n");
        //  ui->horizontalSlider->setEnabled(false);
        //  ui->horizontalSlider_1->setEnabled(false);
        //  ui->horizontalSlider_2->setEnabled(false);
        break;
    case WidgetType::widgT::ScalesBase:
        str = "Izvēlēta svaru pamatne \"ScalesBase \"\n";
        //  ui->horizontalSlider->setEnabled(false);
        //  ui->horizontalSlider_1->setEnabled(false);
        // ui->horizontalSlider_2->setEnabled(false);
        break;
    case WidgetType::widgT::ScalesMass:
        str = "Izvēlēta svaru atsvars \"ScalesMass \"\n";
        str.append("IN1 masas lielums, \n");
        // ui->horizontalSlider->setEnabled(false);
        //  ui->horizontalSlider_2->setEnabled(false);
        break;
    case WidgetType::widgT::Label:


        ui->label_0_1->setText("Teksta lauks");
        ui->label_0_2->setText("Nekādas manipulācijas nav paredzētas.");
        ui->label_0_3->setText("");


        str = "teksta Lauks\n";

        ui->label1_1->setText("");
        ui->label2_1->setText("");
        ui->label3_1->setText("");
        ui->label4_1->setText("");
        ui->label5_1->setText("");
        ui->label6_1->setText("");

        ui->label1_2->setText("");
        ui->label2_2->setText("");
        ui->label3_2->setText("");
        ui->label4_2->setText("");
        ui->lineEdit_5_2->hide();
        ui->lineEdit_6_2->hide();

        ui->label1_3->setText("");
        ui->label2_3->setText("");
        ui->label3_3->setText("");
        ui->label4_3->setText("");
        ui->pushButton_5_3->hide();
        ui->pushButton_6_3->hide();
        ui->line_14->hide();
        ui->line_15->hide();
        ui->line_16->hide();
        ui->line_17->hide();
        ui->line_18->hide();
        ui->line_19->hide();
        ui->line_20->hide();
        ui->line_21->hide();

        break;




    default:
        break;
    }
    ui->label_Notes->setText(str);

}

void WidgetService::updateSensorVal()  // take data from UI and update global. ....
{
    //  QColor col;
    QString qss1;
    QString qss2;


    updateFormData();

}


void WidgetService::updateSettings() {
    qDebug() << "WidgetService::updateSettings()";
}

void WidgetService::closeEvent(QCloseEvent* event) {
    Q_UNUSED(event);
    widgetElement->global.widHash[currentWid].ptrCurrWidgetService = nullptr;
    qDebug() << "WidgetService::closeEvent";
}
void WidgetService::mousePressEvent(QMouseEvent* event) {
    const QPoint& pos = event->pos();
    mouseStartPointX = pos.x();
    mouseStartPointY = pos.y();
    qDebug() << " WidgetService mousePressEvent dx:dy" << pos.x() << pos.y();
}
void WidgetService::mouseMoveEvent(QMouseEvent* event) {
    Q_UNUSED(event);
    // event->accept();

    // get the cursor position of this event
    // const QPoint& pos = event->pos();

    // int pointX = (mouseStartPointX - pos.x()) / -100;
    // int pointY = (mouseStartPointY - pos.y()) / -100;
    //qDebug() << " WidgetService mouseMoveEvent dx:dy" << pointX << pointY;
    //  widgetElement->global.widHash[currentWid].startX += pointX;
    //  widgetElement->global.widHash[currentWid].startY += pointY;
    //   updateFormData();
}

void WidgetService::mouseDoubleClickEvent(QMouseEvent* event) {
    Q_UNUSED(event);
    // qDebug() << "WidgetService::mouseDoubleClickEvent" ;

}

void WidgetService::on_pushButton_Xplus_clicked() {
    widgetElement->global.widHash[currentWid].startX += 1;
    // updateSettings();
    // updateFormData();
    updateFormData();
}


void WidgetService::on_pushButton_Xminus_clicked() {
    if (widgetElement->global.widHash[currentWid].startX > 1)
        widgetElement->global.widHash[currentWid].startX -= 1;
    updateFormData();
}


void WidgetService::on_pushButton_Yplus_clicked() {
    widgetElement->global.widHash[currentWid].startY += 1;
    updateFormData();
}


void WidgetService::on_pushButton_Yminus_clicked() {
    if (widgetElement->global.widHash[currentWid].startY > 1)
        widgetElement->global.widHash[currentWid].startY -= 1;
    updateFormData();
}


void WidgetService::on_pushButton_sizeplus_clicked() {
    widgetElement->global.widHash[currentWid].startSize += 1;
    updateFormData();
}


void WidgetService::on_pushButton_sizeMinus_clicked() {
    if (widgetElement->global.widHash[currentWid].startSize > 1)
        widgetElement->global.widHash[currentWid].startSize -= 1;
    updateFormData();
}


void WidgetService::on_pushButton_OptionsMinus_clicked() {
    //  if (widgetElement->global.widHash[currentWid].options > 0)
    //      widgetElement->global.widHash[currentWid].options -= 1;
    //  updateFormData();
}


void WidgetService::on_pushButton_OptionsPlus_clicked() {
    widgetElement->global.widHash[currentWid].var1 += 1;
    updateFormData();
}


void WidgetService::on_lineEdit_Xpos_editingFinished() {
    int val = ui->lineEdit_Xpos->text().toInt();
    widgetElement->global.widHash[currentWid].startX = val;
    updateFormData();
}


void WidgetService::on_lineEdit_Ypos_editingFinished() {
    int val = ui->lineEdit_Ypos->text().toInt();
    widgetElement->global.widHash[currentWid].startY = val;
    updateFormData();
}


void WidgetService::on_lineEdit_startSize_editingFinished() {
    int val = ui->lineEdit_startSize->text().toInt();
    widgetElement->global.widHash[currentWid].startSize = val;
    updateFormData();
}


void WidgetService::on_lineEdit_options_editingFinished() {
    int val = ui->lineEdit_options->text().toInt();
    widgetElement->global.widHash[currentWid].var1 = val;
    updateSensorVal();
}




void WidgetService::on_pushButton_5_3_clicked()
{
    switch (widgetElement->global.widHash[currentWid].type) {
    case WidgetType::widgT::Valve:
        // close valve
        global.ballValveList[currentWidnpk].bValvePtr->close();

        break;
    case WidgetType::widgT::Tvertne:
        // save calibration full
        break;

    case WidgetType::widgT::Dispax:
        // off
        global.DIoutput[widgetElement->settings.var1].value = 1;
        break;
    case WidgetType::widgT::Mix:
    case WidgetType::widgT::Dyno:
    case WidgetType::widgT::Conveyor:
        // motor On
        param.boardAdr = actualMotorNode;
        param.value = 128;
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

        param.regAdr = LFRD_REG;
        param.value = rpm;
        param.len = 1;
        param.cmd = WR_REG;
        global.rs485WrList.append(param);
        break;

    case WidgetType::widgT::Pump:
        // save calibration full
        if(currentWidnpk == 1){ // pump 2.2
            // motor On
            actualMotorNode = M4;
            param.boardAdr = actualMotorNode;
            param.value = 128;
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

            param.regAdr = LFRD_REG;
            param.value = rpm;
            param.len = 1;
            param.cmd = WR_REG;
            global.rs485WrList.append(param);

        }
        else {
            if( global.DIoutput[widgetElement->settings.var1].value == 1){ //pump work Fw/
                global.DIoutput[widgetElement->settings.var1].value = 0;
                global.DIoutput[widgetElement->settings.var2].value = 0;
            }
            else{
                global.DIoutput[widgetElement->settings.var1].value = 1;
                global.DIoutput[widgetElement->settings.var2].value = 0;
            }
        }
        break;
    default:
        break;
    }
}

void WidgetService::on_pushButton_6_3_clicked()
{

    switch (widgetElement->global.widHash[currentWid].type) {
    case WidgetType::widgT::Valve:
        // open valve
        global.ballValveList[currentWidnpk].bValvePtr->open();
        break;
    case WidgetType::widgT::Tvertne:
        // save calibration empty
        break;
    case WidgetType::widgT::Dispax:
        // off
        global.DIoutput[widgetElement->settings.var1].value = 0;
        break;
    case WidgetType::widgT::Mix:

    case WidgetType::widgT::Dyno:
    case WidgetType::widgT::Conveyor:
        // motor Off

        param.boardAdr = actualMotorNode;
        param.regAdr = CMD_REG;
        param.value = 7;
        param.cmd = WR_REG;
        global.rs485WrList.append(param);


        break;
    case WidgetType::widgT::Pump:
        // motor off

        if ( currentWidnpk == 1){       // pump 2.2
            actualMotorNode = M4;
            param.boardAdr = actualMotorNode;
            param.regAdr = CMD_REG;
            param.value = 7;
            param.cmd = WR_REG;
            global.rs485WrList.append(param);
        }
        else{

            if( global.DIoutput[widgetElement->settings.var2].value == 1){ //pump work RW/
                global.DIoutput[widgetElement->settings.var1].value = 0;
                global.DIoutput[widgetElement->settings.var2].value = 0;
            }
            else{
                global.DIoutput[widgetElement->settings.var1].value =0;
                global.DIoutput[widgetElement->settings.var2].value = 1;
            }
        }
        break;

    default:
        break;
    }

}



void WidgetService::on_lineEdit_5_2_editingFinished()
{
    if(widgetElement->global.widHash[currentWid].type == WidgetType::widgT::Tvertne) {

        int val = ui->lineEdit_5_2->text().toInt(&ok);
        if (!ok) {
            ui->lineEdit_5_2->setText("Kļūda!");
            val = 0;
        }
        else{
            switch (currentWidnpk) {
            case 0:
                global.DIoutput[TVERTNE1KALIBEMPTY].value = val;
                break;
            case 1:
                global.DIoutput[TVERTNE2KALIBEMPTY].value = val;
                break;
            case 2:
                global.DIoutput[TVERTNE3KALIBEMPTY].value = val;
                break;
            case 3:
                global.DIoutput[TVERTNE4KALIBEMPTY].value = val;
                break;
            case 4:
                global.DIoutput[TVERTNE5KALIBEMPTY].value = val;
                break;
            default:
                break;
            }

        }

    }
}


void WidgetService::on_lineEdit_6_2_editingFinished()
{
    if(widgetElement->global.widHash[currentWid].type == WidgetType::widgT::Tvertne) {
        int val = ui->lineEdit_6_2->text().toInt(&ok);
        if (!ok) {
            ui->lineEdit_6_2->setText("Kļūda!");
            val = 0;
        }
        else{
            switch (currentWidnpk) {
            case 0:
                global.DIoutput[TVERTNE1KALIBFULL].value = val;
                break;
            case 1:
                global.DIoutput[TVERTNE2KALIBFULL].value = val;
                break;
            case 2:
                global.DIoutput[TVERTNE3KALIBFULL].value = val;
                break;
            case 3:
                global.DIoutput[TVERTNE4KALIBFULL].value = val;
                break;
            case 4:
                global.DIoutput[TVERTNE5KALIBFULL].value = val;
                break;
            default:
                break;
            }

        }

    }
}

void WidgetService::timerEvent(QTimerEvent *event)
{
    Q_UNUSED (event)
    updateFormData();

}


void WidgetService::on_horizontalSlider_speed_valueChanged(int value)
{
    switch (widgetElement->global.widHash[currentWid].type) {

    case WidgetType::widgT::Mix:
    case WidgetType::widgT::Dispax:
    case WidgetType::widgT::Dyno:
    case WidgetType::widgT::Conveyor:


        rpm = value * gearrate;
        // speed change
        param.boardAdr = actualMotorNode;
        param.value = rpm;
        param.len = 1;
        param.cmd = WR_REG;
        param.regAdr = LFRD_REG;
        global.rs485WrList.append(param);

        break;

    case WidgetType::widgT::Pump:
        if ( currentWidnpk == 1){       // pump 2.2
            actualMotorNode = M4;

            rpm = value * gearrate;
            // speed change
            param.boardAdr = actualMotorNode;
            param.value = rpm;
            param.len = 1;
            param.cmd = WR_REG;
            param.regAdr = LFRD_REG;
            global.rs485WrList.append(param);
        }
        break;




    default:
        break;
    }

    ui->_slider_val->setText(QString::number(value));
    qDebug() << "horizontalSlider_speed_valueChanged, node:" << actualMotorNode << rpm ;
}

