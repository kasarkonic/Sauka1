#include "widgetservice.h"
#include "ui_widgetservice.h"
#include<QMouseEvent>
#include <QSettings>
#include "global.h"
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
    if(addresAct >= 300){   // actuator

        addresactDi = global.actList[addresAct-300].digital;
        addresactAn = global.actList[addresAct-300].digital;

        ui->label_AddressDI->setText("act DI " + QString::number(addresAct));
        ui->label_AddressAI1->setText("act AN " + QString::number(addresAct));

        ui->lineEdit_AddresDI->setText(QString::number(global.actList[addresAct-300].digital));
        ui->lineEdit_AddresAN1->setText(QString::number(global.actList[addresAct-300].analog));
    }
    if( widgetElement->global.widHash[currentWid].sensAddres1 > 0 ){       // sensor
        addresAN1 =  widgetElement->global.widHash[currentWid].sensAddres1;
        actValueDi1 = widgetElement->global.sensList[addresAN1].digital;
        actValueAn1 = widgetElement->global.sensList[addresAN1].analog;

        addresAN2 =  widgetElement->global.widHash[currentWid].sensAddres2;
        actValueDi2 = widgetElement->global.sensList[addresAN2].digital;
        actValueAn2 = widgetElement->global.sensList[addresAN2].analog;

        ui->label_AddressDI->setText("sens DI " + QString::number(addresAN1));
        ui->label_AddressAI1->setText("sens AN " + QString::number(addresAN1));

        ui->lineEdit_AddresDI->setText(QString::number(global.sensList[addresSens].digital));
        ui->lineEdit_AddresAN1->setText(QString::number(global.sensList[addresSens].analog));


        if(widgetElement->global.widHash[currentWid].type == WidgetType::widgT::Valve){
            ui->label_AddressAI2->setText("sens2 DI " + QString::number(addresAN2));
            ui->lineEdit_AddresAN2->setText(QString::number(global.sensList[addresSens2].digital));
        }

    }

    if(addresAct >= 300 && widgetElement->global.widHash[currentWid].sensAddres1 > 0 ){// valve  addresAN1 >0


}



    updateSensorVal();

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
        ui->horizontalSlider->setDisabled(false);

        ui->label_Di->setText("DI addr."+QString::number(addresAct));
        ui->label_AN1->setText("AN1 addr."+QString::number(addresAN1));
        ui->label_AN2->setText("AN2 addr."+QString::number(addresAN2));
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
        ui->horizontalSlider->setDisabled(true);

        ui->label_Di->setText("DI1 sens. addr. "+QString::number(addresAct));
        // ui->label_AN1->setText("DI1 Sens. addr. "+QString::number(addresAN1));
        ui->label_AN1->setText("-");
        ui->label_AN2->setText("DI2 sens. addr. . "+QString::number(addresAN2));

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
        ui->horizontalSlider->setDisabled(false);

        ui->label_Di->setText("DI addr."+QString::number(addresAct));
        ui->label_AN1->setText("AN1 addr."+QString::number(addresAN1));

        ui->label_AN2->setText("-");

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
        ui->horizontalSlider->setDisabled(false);

        ui->label_Di->setText("DI addr."+QString::number(addresAct));
        ui->label_AN1->setText("AN1 addr."+QString::number(addresAN1));

        ui->label_AN2->setText("-");

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

    /*   if(actValueDi >= 2){
        col = QColor(Qt::yellow);
        qss1 = QString("background-color: %1").arg(col.name());
        ui->pushButton_ON->setStyleSheet(qss1);
     //   ui->pushButton_OFF->setStyleSheet(qss1);
        actValueDi = 2;}
*/

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


    int adr = widgetElement->global.widHash[currentWid].act_sensAddres;
    if (adr > 300){ // actuator
        widgetElement->global.actList[adr - 300].digital = actValueDi;
     //   widgetElement->global.actList[adr - 300].analog = actValueAn;
    }
    else{    // sensors


        addresSens =  widgetElement->global.widHash[currentWid].sensAddres1;
        widgetElement->global.sensList[addresSens].digital = actValueDi;
     //   widgetElement->global.sensList[addresSens].analog = actValueAn;

        addresSens2 =  widgetElement->global.widHash[currentWid].sensAddres2;
    //    widgetElement->global.sensList[addresSens2].digital = ;
    //    widgetElement->global.sensList[addresSens2].analog = ;

    }








    // widgetElement->global.sensList[addresAN1].analog = an1Value;
    // ui->lineEdit_AddresAN1->setText(QString::number(an1Value));
    // widgetElement->global.sensList[addresAct].digital = actValueDi;
    // ui->lineEdit_AddresDI->setText(QString::number(actValueDi));

    widgetElement->updateSettings();

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
    if(actValueDi){
        actValueDi = 0;
    }
    else{
        actValueDi = 1;}

    updateSensorVal();

}


void WidgetService::on_horizontalSlider_valueChanged(int value)
{
    qDebug() << "slider value: " << value;
    if(widgetElement->global.widHash[currentWid].type == WidgetType::widgT::Valve)
    {
        an1Value = 0;
        if(value > 50) {
            an1Value = 1;
        }
    }
    else{
        an1Value = value;
    }

    actValueAn = value;
    // widgetElement->global.sensList[addresAN1].analog = an1Value;
    updateSensorVal();
}

void WidgetService::on_lineEdit_AddresAN1_editingFinished()
{
    actValueAn = ui->lineEdit_AddresAN1->text().toInt();
    updateSensorVal();
}

void WidgetService::on_lineEdit_AddresAN2_editingFinished()
{
    int val = ui->lineEdit_AddresAN2->text().toInt();
    addresSens2 =  widgetElement->global.widHash[currentWid].sensAddres2;
    widgetElement->global.sensList[addresSens2].digital = val;
    updateSensorVal();
    // qDebug() << "lineEdit_AddresAN2 " << val;
}


void WidgetService::on_pushButton_Reset_clicked()
{

}


void WidgetService::on_lineEdit_AddresDI_editingFinished()
{
    actValueDi = ui->lineEdit_AddresDI->text().toInt();
}

