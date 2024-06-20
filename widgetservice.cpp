#include "widgetservice.h"
#include "ui_widgetservice.h"
#include<QMouseEvent>
#include <QSettings>
//#include "global.h"
//#include "widgetdiagramelement.h"


WidgetService::WidgetService(Global &global,WidgetDiagramElement *widgetElement, QWidget *parent)

    : QWidget(parent)
    , global(global)
    , ui(new Ui::WidgetService)
    , widgetElement(widgetElement)
{
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, global.backgroundColor); //QColor(255, 0, 0, 127)
    //pal.setColor(QPalette::Window, QColor(242, 219, 238, 0.251));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    currentWid =  widgetElement->settings.name;
    widgetElement->global.widHash[currentWid].ptrCurrWidgetService = this;

    qDebug() << "currentWid name " << currentWid << widgetElement->global.widHash[currentWid].ptrCurrWidgetService ;
    ui->setupUi(this);
    //qDebug() << "???" << widgetElement->global.widHash[currentWid].startX << widgetElement->global.widHash[currentWid].startY  ;

    addresAct = widgetElement->global.widHash[currentWid].act_Addres1;
    addresSens1 = widgetElement->global.widHash[currentWid].sensAddres1;
    addresSens2 = widgetElement->global.widHash[currentWid].sensAddres2;
    qDebug() << "addresAct,sens1,sens2" << addresAct << addresSens1 << addresSens2;


    updateFormData();   // data from global. ...
}
void WidgetService::openWidgetServiceForm()
{
    qDebug() << "WidgetSrv Open service pipe ??? : " ;

    this->show();
}

//  qDebug() << "Open service pipe ??? : " ;
//  WidgetService *widgetService = new WidgetService (this,global,sender());
//  Pipe* pipe = qobject_cast<Pipe*>(sender());
//  qDebug() << "Open service : " << pipe->settings.name ;
//  widgetService->show();





WidgetService::~WidgetService()
{
    widgetElement->global.widHash[currentWid].ptrCurrWidgetService = nullptr;
    qDebug() << "WidgetService::~WidgetService()" ;
    delete ui;
}

void WidgetService::updateUIvalue()
{

}

void WidgetService::updateFormData()        // read data from global and display in to UI
{
    //geometry data
    ui->labelName->setText(widgetElement->global.widHash[currentWid].name);
    ui->lineEdit_Xpos->setText(QString::number(widgetElement->global.widHash[currentWid].startX));
    ui->lineEdit_Ypos->setText(QString::number(widgetElement->global.widHash[currentWid].startY));
    ui->lineEdit_startSize->setText(QString::number(widgetElement->global.widHash[currentWid].startSize));
    ui->lineEdit_options->setText(QString::number(widgetElement->global.widHash[currentWid].options));

    // sensor data

    // addresAct = widgetElement->global.widHash[currentWid].act_Addres1;
    // addresSens1 = widgetElement->global.widHash[currentWid].sensAddres1;
    // addresSens2 = widgetElement->global.widHash[currentWid].sensAddres2;

    //qDebug() << "addresAct,sens1,sens2" << addresAct << addresSens1 << addresSens2;
    bool isValve = widgetElement->global.widHash[currentWid].type == WidgetType::widgT::Valve;



    ui->label_AddressDI->setText("" + QString::number(addresAct));
    ui->label_AddressAI1->setText("" + QString::number(addresSens1));
    ui->label_AddressAI2->setText("" + QString::number(addresSens2));

    ui->lineEdit_AddresDI->setText(QString::number(global.DIoutput[addresAct].value));

    switch (widgetElement->global.widHash[currentWid].type) {
    case WidgetType::widgT::Dyno:
    case WidgetType::widgT::Pump:
    case WidgetType::widgT::Mix:
        ui->lineEdit_AddresAN1->setText(QString::number(global.DIoutput[addresSens1].value));
        break;
    case WidgetType::widgT::Tvertne:
    case WidgetType::widgT::Valve:
        ui->lineEdit_AddresAN1->setText(QString::number(global.DIinput[addresSens1].value));
        break;

    case WidgetType::widgT::ScalesMass:
        ui->lineEdit_AddresAN1->setText(QString::number(global.DIinput[addresSens1].value));
        break;

    default:
        break;
    }

    //ui->lineEdit_AddresAN1->setText(QString::number(global.DIoutput[addresSens1].value));
    ui->lineEdit_AddresAN2->setText(QString::number(global.DIinput[addresSens2].value));

    //      ui->horizontalSlider_2->hide();
    //      ui->label_AN2->hide();
    //      ui->lineEdit_AddresAN2->hide();
    //      ui->label_AddressAI2->hide();


    //actValueDi = global.actList[addresAct].digital;
    //actValueAn1 = global.actList[addresAct].analog;
    //actValueAn2;

    // }


    // updateSensorVal();

    widgetElement->updateSettings();


    QString str;
    QString strDeg = QChar(0x00b0);

    switch (widgetElement->global.widHash[currentWid].type) {
    case WidgetType::widgT::Dyno:
        str = "Izvēlēts elements \"Dynamill\"\n";
        str.append("Aktuators maina motora griežšanās ātrumu\n");
        str.append("IN1 = 0 izslēdz, IN1 > 0 ieslēdz motoru\n");
        ui->horizontalSlider_2->setEnabled(false);
        break;

    case WidgetType::widgT::Tvertne:

        /*
         * Widget Tvertne
         *
         * avārijas līmeņa sensors sensList[sensor address].digital.
         * līmeņa sensors sensList[sensor address].analog.
         *
         */

        str = "Izvēlēts elements \"TVERTNE \"\n";
        str.append("IN1 tvertnes līmenis\n");
        str.append("IN2 drošības līmeņa devējs\n");
        ui->horizontalSlider->setEnabled(false);

        // ui->horizontalSlider->setDisabled(false);

        //  ui->label_Di->setText("DI addr."+QString::number(addresAct));
        //  ui->label_AN1->setText("AN1 addr."+QString::number(addresAN1));
        //  ui->label_AN2->setText("AN2 addr."+QString::number(addresAN2));
        break;
    case WidgetType::widgT::Valve:  //??????????????????????????

        /*
         * Widget Valve
         *
         * vārsta gala slēdži sensList[sensor address1].digital.
         * vārsta gala slēdži sensList[sensor address1].digital.
         *
         */

        str = "Izvēlēts elements \"Valve \"\n";
        str.append("ON OFF islēdz/ atslēdz vārstu motoru\n");
        str.append("DI1 atvērta vārsta gala slēdzis.\n");
        str.append("DI2 aizvērta vārsta gala slēdzis.\n");
        str.append("Options iestāda atvērta vārsta leņķi 0-90\u00B0.\n");
        //str.append(strDeg);
        //str.append(" .\n");
        break;

    case WidgetType::widgT::Pump:

        /*
         * Widget Pump
         *
         * sūknis act[actList address1].digital.
         * griežšanās ātrums act[actList address1].analog.
         *
         */
        str = "Izvēlēts sūknis \"Pump \"\n";
        str.append("Aktuators maina motora griežšanās ātrumu un virzienu\n");
        str.append("IN1 = 0 izslēdz, IN1 > 0 ieslēdz motoru\n");
        ui->horizontalSlider_2->setEnabled(false);
        ui->horizontalSlider->setMaximum(100);
        ui->horizontalSlider->setMinimum(-100);

        break;

    case WidgetType::widgT::Mix:

        /*
         * Widget Mix
         *
         * mikseris act[actList address1].digital.
         * griežšanās ātrums act[actList address1].analog.
         *
         */
        str = "Izvēlēts maisītājs \"Mix \"\n";
        str.append("Aktuators maina motora griežšanās ātrumu\n");
        str.append("IN1 = 0 izslēdz, IN1 > 0 ieslēdz motoru\n");
        ui->horizontalSlider_2->setEnabled(false);

        break;
    case WidgetType::widgT::Pipe:
        str = "Izvēlēta savienojošā caurule \"Pipe \"\n";
        str.append("Options = 0 vertikala, \n");
        str.append("Options = 90 horizontāla, \n");
        ui->horizontalSlider->setEnabled(false);
        ui->horizontalSlider_1->setEnabled(false);
        ui->horizontalSlider_2->setEnabled(false);
        break;
    case WidgetType::widgT::ScalesBase:
        str = "Izvēlēta svaru pamatne \"ScalesBase \"\n";
        ui->horizontalSlider->setEnabled(false);
        ui->horizontalSlider_1->setEnabled(false);
        ui->horizontalSlider_2->setEnabled(false);
        break;
    case WidgetType::widgT::ScalesMass:
        str = "Izvēlēta svaru atsvars \"ScalesMass \"\n";
        str.append("IN1 masas lielums, \n");
        ui->horizontalSlider->setEnabled(false);
        ui->horizontalSlider_2->setEnabled(false);
        break;

    default:
        break;
    }
    ui->label_Notes->setText(str);

}

void WidgetService::updateSensorVal()  // take data from UI and update global. ....
{
    QColor col;
    QString qss1;
    QString qss2;


    updateFormData() ;

}

void WidgetService::updateSettings()
{
    qDebug() << "WidgetService::updateSettings()";
}

void WidgetService::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    widgetElement->global.widHash[currentWid].ptrCurrWidgetService = nullptr;
    qDebug() << "WidgetService::closeEvent" ;
}
void WidgetService::mousePressEvent(QMouseEvent *event)
{
    const QPoint& pos = event->pos();
    mouseStartPointX = pos.x();
    mouseStartPointY = pos.y();
    qDebug() << " WidgetService mousePressEvent dx:dy" <<pos.x() << pos.y();
}
void WidgetService::mouseMoveEvent(QMouseEvent *event)
{
    // event->accept();

    // get the cursor position of this event
    const QPoint& pos = event->pos();

    int pointX = (mouseStartPointX - pos.x())/-100;
    int pointY = (mouseStartPointY - pos.y())/-100;
    qDebug() << " WidgetService mouseMoveEvent dx:dy" << pointX<< pointY;
    widgetElement->global.widHash[currentWid].startX += pointX;
    widgetElement->global.widHash[currentWid].startY += pointY;
    updateFormData();
}

void WidgetService::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    // qDebug() << "WidgetService::mouseDoubleClickEvent" ;

}

void WidgetService::on_pushButton_Xplus_clicked()
{
    widgetElement->global.widHash[currentWid].startX +=1;
    // updateSettings();
    // updateFormData();
    updateFormData();
}


void WidgetService::on_pushButton_Xminus_clicked()
{
    if(widgetElement->global.widHash[currentWid].startX > 1)
        widgetElement->global.widHash[currentWid].startX -=1;
    updateFormData();
}


void WidgetService::on_pushButton_Yplus_clicked()
{
    widgetElement->global.widHash[currentWid].startY +=1;
    updateFormData();
}


void WidgetService::on_pushButton_Yminus_clicked()
{
    if(widgetElement->global.widHash[currentWid].startY > 1)
        widgetElement->global.widHash[currentWid].startY -=1;
    updateFormData();
}


void WidgetService::on_pushButton_sizeplus_clicked()
{
    widgetElement->global.widHash[currentWid].startSize +=1;
    updateFormData();
}


void WidgetService::on_pushButton_sizeMinus_clicked()
{
    if(widgetElement->global.widHash[currentWid].startSize > 1)
        widgetElement->global.widHash[currentWid].startSize -=1;
    updateFormData();
}


void WidgetService::on_pushButton_OptionsMinus_clicked()
{
    if(widgetElement->global.widHash[currentWid].options > 0)
        widgetElement->global.widHash[currentWid].options -=1;
    updateFormData();
}


void WidgetService::on_pushButton_OptionsPlus_clicked()
{
    widgetElement->global.widHash[currentWid].options +=1;
    updateFormData();
}


void WidgetService::on_lineEdit_Xpos_editingFinished()
{
    int val = ui->lineEdit_Xpos->text().toInt();
    widgetElement->global.widHash[currentWid].startX = val;
    updateFormData();
}


void WidgetService::on_lineEdit_Ypos_editingFinished()
{
    int val = ui->lineEdit_Ypos->text().toInt();
    widgetElement->global.widHash[currentWid].startY = val;
    updateFormData();
}


void WidgetService::on_lineEdit_startSize_editingFinished()
{
    int val = ui->lineEdit_startSize->text().toInt();
    widgetElement->global.widHash[currentWid].startSize = val;
    updateFormData();
}


void WidgetService::on_lineEdit_options_editingFinished()
{
    int val = ui->lineEdit_options->text().toInt();
    widgetElement->global.widHash[currentWid].options = val;
    updateSensorVal();
}


/*
void WidgetService::on_pushButton_ON_clicked()
{
    bool ok = true;
    actValueDi = ui->lineEdit_AddresDI->text().toInt(&ok,10);
    if(!ok){
        actValueDi = 0;
    }


    if(actValueDi){
        actValueDi = 0;
    }
    else{
        actValueDi = 1;}

    qDebug() << "on_pushButton_ON_clicked " << actValueDi;


    updateSensorVal();

}

*/
void WidgetService::on_horizontalSlider_valueChanged(int value)
{
    qDebug() << "on_horizontalSlider_valueChanged " << value;
    global.DIoutput[addresAct].value = value;
    updateSensorVal();
}


void WidgetService::on_horizontalSlider_1_valueChanged(int value)
{
    qDebug() << "on_horizontalSlider_1_valueChanged " << value;

    switch (widgetElement->global.widHash[currentWid].type) {
    case WidgetType::widgT::Dyno:
    case WidgetType::widgT::Pump:
    case WidgetType::widgT::Mix:
        global.DIoutput[addresSens1].value = value;
        break;
    case WidgetType::widgT::Tvertne:
    case WidgetType::widgT::Valve:
        global.DIinput[addresSens1].value = value;
        break;

    case WidgetType::widgT::ScalesMass:
        global.DIinput[addresSens1].value = value;
        break;

    default:
        break;
    }

    updateSensorVal();

}


void WidgetService::on_horizontalSlider_2_valueChanged(int value)
{
    //actValueAn2 = value;
    qDebug() << "on_horizontalSlider_2_valueChanged " << value;
    global.DIinput[addresSens2].value = value;
    updateSensorVal();
}







void WidgetService::on_lineEdit_AddresAN1_editingFinished()
{   
    bool ok = true;
    actValueAn1 = ui->lineEdit_AddresAN1->text().toInt(&ok,10);
    if(!ok){
        actValueAn1 = 0;
    }
    qDebug() << "on_lineEdit_AddresAN1_editingFinished " << actValueAn1;

    updateSensorVal();
}

void WidgetService::on_lineEdit_AddresAN2_editingFinished()
{
    bool ok = true;
    actValueAn2 = ui->lineEdit_AddresAN1->text().toInt(&ok,10);
    if(!ok){
        actValueAn2 = 0;
    }
    qDebug() << "on_lineEdit_AddresAN1_editingFinished " << actValueAn2;

    updateSensorVal();
}

void WidgetService::on_lineEdit_AddresDI_editingFinished()
{
    bool ok = true;
    actValueDi = ui->lineEdit_AddresDI->text().toInt(&ok,10);
    if(!ok){
        actValueDi = 0;
    }
    qDebug() << "on_lineEdit_AddresDI_editingFinished " << actValueDi;
    updateSensorVal();
}
