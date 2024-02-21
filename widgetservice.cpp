#include "widgetservice.h"
#include "ui_widgetservice.h"
#include<QMouseEvent>
#include <QSettings>
#include "global.h"
//#include "widgetdiagramelement.h"


WidgetService::WidgetService(Global &global,WidgetDiagramElement *widgetElement, QWidget *parent)

    : QWidget(parent)
    , ui(new Ui::WidgetService)
    , global(global)
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

    addresAct = widgetElement->global.widHash[currentWid].act_sensAddres;
    bool isValve = widgetElement->global.widHash[currentWid].type == WidgetType::widgT::Valve;

    if(addresAct >= 300 && !isValve){   // actuator

        ui->label_AddressDI->setText("act DI " + QString::number(addresAct));
        ui->label_AddressAI1->setText("act AN " + QString::number(addresAct));

        ui->lineEdit_AddresDI->setText(QString::number(global.actList[addresAct-300].digital));
        ui->lineEdit_AddresAN1->setText(QString::number(global.actList[addresAct-300].analog));

        ui->horizontalSlider_2->hide();
        ui->label_AN2->hide();
        ui->lineEdit_AddresAN2->hide();
        ui->label_AddressAI2->hide();


        actValueDi = global.actList[addresAct-300].digital;
        actValueAn1 = global.actList[addresAct-300].analog;
        //actValueAn2;

    }

    if( addresAct < 300 && !isValve ){       // sensor

        addresSens1 = widgetElement->global.widHash[currentWid].sensAddres1;

        ui->label_AddressDI->setText("sens DI " + QString::number(addresSens1));
        ui->label_AddressAI1->setText("sens AN " + QString::number(addresSens1));

        ui->lineEdit_AddresDI->setText(QString::number(global.sensList[addresSens1].digital));
        ui->lineEdit_AddresAN1->setText(QString::number(global.sensList[addresSens1].analog));

        ui->horizontalSlider_2->hide();
        ui->label_AN2->hide();
        ui->lineEdit_AddresAN2->hide();
        ui->label_AddressAI2->hide();

        actValueDi = global.sensList[addresSens1].digital;
        actValueAn1 = global.sensList[addresSens1].analog;
        //actValueAn2;

    }


    if(isValve){


        addresAct = widgetElement->global.widHash[currentWid].act_sensAddres;
        ui->label_AddressDI->setText("act DI " + QString::number(addresAct));
        ui->lineEdit_AddresDI->setText(QString::number(global.actList[addresAct-300].digital));


        addresSens1 = widgetElement->global.widHash[currentWid].sensAddres1;
        ui->label_AddressAI1->setText("sens DI " + QString::number(addresSens1));
        ui->lineEdit_AddresAN1->setText(QString::number(global.sensList[addresSens1].digital));

        addresSens2 = widgetElement->global.widHash[currentWid].sensAddres2;
        ui->label_AddressAI2->setText("sens DI " + QString::number(addresSens2));
        ui->lineEdit_AddresAN2->setText(QString::number(global.sensList[addresSens2].digital));

        ui->horizontalSlider_2->show();
        ui->label_AN2->show();
        ui->lineEdit_AddresAN2->show();
        ui->label_AddressAI2->show();

        actValueDi = global.actList[addresAct-300].digital;
        actValueAn1 = global.sensList[addresSens1].digital;
        actValueAn2 = global.sensList[addresSens2].digital;
    }






    // updateSensorVal();

     widgetElement->updateSettings();

    /*
      *enum widgT{
    Dyno,
    Mix,
    Pipe,
    Pump,
    Tvertne,
    Valve,
      */


    QString str;
    switch (widgetElement->global.widHash[currentWid].type) {
    case WidgetType::widgT::Dyno:

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
        str.append("ON OFF maina drošības devēja \"0\" vērtību\n");
        str.append("\"SLIDER\" maina tvertnes piepildījums sensora \"1\" vērtību. \n");
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
        str.append("ON OFF islēdz/ atslēdz vārstu\n");
        str.append("DI1 un DI2 vārsta gala slēdži.\n");
        //   ui->horizontalSlider->setDisabled(true);

        //  ui->label_Di->setText("DI1 sens. addr. "+QString::number(addresAct));
        // ui->label_AN1->setText("DI1 Sens. addr. "+QString::number(addresAN1));
        //  ui->label_AN1->setText("-");
        //  ui->label_AN2->setText("DI2 sens. addr. . "+QString::number(addresAN2));

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
        str.append("ON OFF ieslēdz/ atslēdz sūkni\n");
        str.append("AN1 sūkņa griežšanās ātrums\n");
        //  ui->horizontalSlider->setDisabled(false);

        //  ui->label_Di->setText("DI addr."+QString::number(addresAct));
        //  ui->label_AN1->setText("AN1 addr."+QString::number(addresAN1));

        //  ui->label_AN2->setText("-");

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
        str.append("ON OFF ieslēdz/ atslēdz maisītāju\n");
        str.append("AN1 sūkņa griežšanās ātrums\n");
        //  ui->horizontalSlider->setDisabled(false);

        // ui->label_Di->setText("DI addr."+QString::number(addresAct));
        // ui->label_AN1->setText("AN1 addr."+QString::number(addresAN1));

        // ui->label_AN2->setText("-");

        break;
         case WidgetType::widgT::ScalesBase:
        str = "Izvēlēta svaru pamatne \"ScalesBase \"\n";
        break;
         case WidgetType::widgT::ScalesMass:
         str = "Izvēlēta svaru atsvars \"ScalesMass \"\n";
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



    if(actValueDi > 0){
        col = QColor(Qt::red);
        qss1 = QString("background-color: %1").arg(col.name());
        ui->pushButton_ON->setStyleSheet(qss1);
        ui->pushButton_ON->setText("OFF");
    }

    if(actValueDi == 0){
        col = QColor(Qt::green);
        qss1 = QString("background-color: %1").arg(col.name());
        ui->pushButton_ON->setStyleSheet(qss1);
        ui->pushButton_ON->setText("ON");
    }



    addresAct = widgetElement->global.widHash[currentWid].act_sensAddres;

    bool isValve = widgetElement->global.widHash[currentWid].type == WidgetType::widgT::Valve;
    if(addresAct >= 300 && !isValve){   // actuator

        qDebug() << "updateSensorVal " << addresAct << actValueDi <<  actValueAn1;

        global.actList[addresAct-300].digital = actValueDi;
        global.actList[addresAct-300].analog = actValueAn1;
    }


    if( addresAct < 300  && !isValve ){

    qDebug() << "updateSensorVal " << addresAct << actValueDi <<  actValueAn1;
    addresSens1 = widgetElement->global.widHash[currentWid].sensAddres1;

    global.sensList[addresSens1].digital = actValueDi;
    global.sensList[addresSens1].analog = actValueAn1;

    }

    if(isValve){

        qDebug() << "Valve updateSensorVal " << addresAct << actValueDi <<  actValueAn1 <<  actValueAn2;

        global.actList[addresAct-300].digital = actValueDi;

        addresSens1 = widgetElement->global.widHash[currentWid].sensAddres1;
        global.sensList[addresSens1].digital = actValueAn1;

        addresSens2 = widgetElement->global.widHash[currentWid].sensAddres2;
        global.sensList[addresSens2].digital = actValueAn2;



    }




    //widgetElement->updateSettings();

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

    int pointX = pos.x();
    int pointY = pos.y();
    qDebug() << " WidgetService mouseMoveEvent dx:dy" << pointX<< pointY;
    widgetElement->global.widHash[currentWid].startX = pointX;
    widgetElement->global.widHash[currentWid].startY = pointY;
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


void WidgetService::on_horizontalSlider_valueChanged(int value)
{
    qDebug() << "slider value: " << value;
    //if(widgetElement->global.widHash[currentWid].type == WidgetType::widgT::Valve)
    // {
    //    an1Value = 0;
    //    if(value > 50) {
    //         an1Value = 1;
    //     }
    // }
    // else{
    //     an1Value = value;
    // }

    actValueAn1 = value;
    // widgetElement->global.sensList[addresAN1].analog = an1Value;
    qDebug() << "on_horizontalSlider_valueChanged " << actValueAn1;
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


void WidgetService::on_horizontalSlider_2_valueChanged(int value)
{
    actValueAn2 = value;
    qDebug() << "on_horizontalSlider_2_valueChanged " << actValueAn2;
    updateSensorVal();
}

