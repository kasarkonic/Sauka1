#include "widgetservice.h"
#include "ui_widgetservice.h"
#include<QMouseEvent>
#include <QSettings>
//#include "widgetdiagramelement.h"


WidgetService::WidgetService(WidgetDiagramElement *widgetElement, QWidget *parent)

    : QWidget(parent)
    , ui(new Ui::WidgetService)
    , widgetElement(widgetElement)
{
    currentWid =  widgetElement->settings.name;
    widgetElement->global.widHash[currentWid].ptrCurrWidgetService = this;

    qDebug() << "currentWid name " << currentWid << widgetElement->global.widHash[currentWid].ptrCurrWidgetService ;
    ui->setupUi(this);
    //qDebug() << "???" << widgetElement->global.widHash[currentWid].startX << widgetElement->global.widHash[currentWid].startY  ;
    updateFormData();
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

void WidgetService::updateFormData()
{
    //geometry data
    ui->labelName->setText(widgetElement->global.widHash[currentWid].name);
    ui->lineEdit_Xpos->setText(QString::number(widgetElement->global.widHash[currentWid].startX));
    ui->lineEdit_Ypos->setText(QString::number(widgetElement->global.widHash[currentWid].startY));
    ui->lineEdit_startSize->setText(QString::number(widgetElement->global.widHash[currentWid].startSize));
    ui->lineEdit_options->setText(QString::number(widgetElement->global.widHash[currentWid].options));

    // sensor data
    addresAct = widgetElement->global.widHash[currentWid].actAddres;
    addresAN1 = widgetElement->global.widHash[currentWid].sensAddres1;
    addresAN2 = widgetElement->global.widHash[currentWid].sensAddres2;
    actValue = widgetElement->global.sensList[addresAct].digital;
    an1Value = widgetElement->global.sensList[addresAN1].analog;
    an2Value = widgetElement->global.sensList[addresAN2].analog;

    ui->label_AddressDI->setText(QString::number(addresAct));
    ui->label_AddressAI1->setText(QString::number(addresAN1));
    ui->label_AddresAI2->setText(QString::number(addresAN2));

    ui->lineEdit_AddresDI->setText(QString::number(actValue));
    //ui->lineEdit_AddresAN1->setText(QString::number(an1Value));
    ui->lineEdit_AddresAN2->setText(QString::number(an2Value));


    updateSensorVal();





    widgetElement->updateSettings();

}

void WidgetService::updateSensorVal()
{
    QColor col;
    QString qss1;
    QString qss2;

    if(actValue >= 2){
        col = QColor(Qt::yellow);
        qss1 = QString("background-color: %1").arg(col.name());
        ui->pushButton_ON->setStyleSheet(qss1);
        ui->pushButton_OFF->setStyleSheet(qss1);
        actValue = 2;

    }
    if(actValue == 1){
        col = QColor(Qt::green);
        qss1 = QString("background-color: %1").arg(col.name());
        ui->pushButton_ON->setStyleSheet(qss1);
        col = QColor(Qt::gray);
        qss2 = QString("background-color: %1").arg(col.name());
        ui->pushButton_OFF->setStyleSheet(qss2);

    }

    if(actValue == 0){
        col = QColor(Qt::gray);
        qss1 = QString("background-color: %1").arg(col.name());
        ui->pushButton_ON->setStyleSheet(qss1);
        col = QColor(Qt::red);
        qss2 = QString("background-color: %1").arg(col.name());
        ui->pushButton_OFF->setStyleSheet(qss2);
    }
    ui->lineEdit_AddresAN1->setText(QString::number(an1Value));
     widgetElement->global.sensList[addresAct].digital;
     ui->lineEdit_AddresDI->setText(QString::number(actValue));
     ui->label_Notes->setText("Darbībā prblēmas nav novērotas");
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
    updateFormData();
}


void WidgetService::on_pushButton_OFF_clicked()
{
    actValue = 0;
    widgetElement->global.sensList[addresAct].digital = actValue;
    updateSensorVal();
}


void WidgetService::on_pushButton_ON_clicked()
{
actValue = 1;
widgetElement->global.sensList[addresAct].digital = actValue;
updateSensorVal();
}


void WidgetService::on_horizontalSlider_valueChanged(int value)
{
    qDebug() << "slider value: " << value;
    an1Value = value;
    widgetElement->global.sensList[addresAN1].analog = an1Value;
    updateSensorVal();
}

