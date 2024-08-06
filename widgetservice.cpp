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
    ui->horizontalSlider_speed->setValue(50);

    updateFormData();   // data from global. ...
    timerId = startTimer(100);
}
void WidgetService::openWidgetServiceForm() {
    qDebug() << "WidgetSrv Open service pipe ??? : ";

    this->show();
}

//  qDebug() << "Open service pipe ??? : " ;
//  WidgetService *widgetService = new WidgetService (this,global,sender());
//  Pipe* pipe = qobject_cast<Pipe*>(sender());
//  qDebug() << "Open service : " << pipe->settings.name ;
//  widgetService->show();





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

    // sensor data





    // ui->lineEdit_AddresDI->setText(QString::number(global.DIoutput[addresAct].value));
    /*
    switch (widgetElement->global.widHash[currentWid].type) {

    case WidgetType::widgT::Valve:
        //    ui->lineEdit_AddresAN1->setText(QString::number(global.DIinput[addresSens1].value));

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

        ui->lineEdit_5_2->setText(" ");
        ui->lineEdit_6_2->setText(" ");
        ui->pushButton_5_3->setText(QString::number(openTime));
        ui->pushButton_6_3->setText(QString::number(closeTime));


        }


        break;

    case WidgetType::widgT::ScalesMass:
        //    ui->lineEdit_AddresAN1->setText(QString::number(global.DIinput[addresSens1].value));
        break;

    default:
        break;
    }

   */


    // ui->lineEdit_AddresAN2->setText(QString::number(global.DIinput[addresSens2].value));


    widgetElement->updateSettings();


    QString str;
    QString strDeg = QChar(0x00b0);

    switch (widgetElement->global.widHash[currentWid].type) {

    case WidgetType::widgT::Dyno:

        str = "Izvēlēts elements \"Dynamill\"\n";
        str.append("Aktuators maina motora griežšanās ātrumu\n");
        str.append("IN1 = 0 izslēdz, IN1 > 0 ieslēdz motoru\n");

        ui->label1_1->setText("Ātrums");
        ui->label2_1->setText("Statuss");
        ui->label3_1->setText("Kļūda");
        ui->label4_1->setText("-");
        ui->label5_1->setText("Ieslēgt mikseri");
        ui->label6_1->setText("Izslēgt mikseri");

        ui->label1_2->setText(QString::number(12));
        ui->label2_2->setText(QString::number(22));
        ui->label3_2->setText(QString::number(32));
        ui->label4_2->setText("");
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
            str.append("IN2 drošības līmeņa devējs\n");

            ui->label1_1->setText("Līmenis tvertnē %");
            ui->label2_1->setText("Pilnas Tv. devējs");
            ui->label3_1->setText("Temperatūra");
            ui->label4_1->setText("Sensoru kalibrēšana");
            ui->label5_1->setText("Kalibrēt pilnu Tv.");
            ui->label6_1->setText("Kalibrēt tukšu Tv");

            ui->label1_2->setText(QString::number(level));
            ui->label2_2->setText(QString::number(full));

            ui->label3_2->setText("-");
            ui->label4_2->setText("Pašreizējā vērtība");
            //ui->lineEdit_5_2->hide();
            //ui->lineEdit_6_2->hide();

            ui->label1_3->setText(QString::number(levelv));
            ui->label2_3->setText(QString::number(fullv));
            ui->label3_3->setText(QString::number(global.tvertneTemp[currentWidnpk]));
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

            ui->lineEdit_5_2->setText(QString::number(openTime));
            ui->lineEdit_6_2->setText(QString::number(openTime));
            ui->pushButton_5_3->setText(" Aizvērt vārstu");
            ui->pushButton_6_3->setText("Atvērt vārstu");


        }

        str = "Izvēlēts elements \"Valve \"\n";
        str.append("ON OFF islēdz/ atslēdz vārstu motoru\n");
        str.append("DI1 atvērta vārsta gala slēdzis.\n");
        str.append("DI2 aizvērta vārsta gala slēdzis.\n");
        str.append("Options iestāda vārsta leņķi 0-90\u00B0.\n");
        str.append("0\u00B0 horizontāls, 90\u00B0n vertilāls\n");
        //str.append(strDeg);
        //str.append(" .\n");

        ui->label1_1->setText("In vārsts vaļā");
        ui->label2_1->setText("In vārsts ciet");
        ui->label3_1->setText("Out atvērt vārstu");
        ui->label4_1->setText("Out aizvērt vārstu");
        ui->label5_1->setText("Aizvēršanās laiks");
        ui->label6_1->setText("Atvēršanās laiks");



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
        ui->label1_1->setText("Ātrums");
        ui->label2_1->setText("Statuss");
        ui->label3_1->setText("Kļūda");
        ui->label4_1->setText("-");
        ui->label5_1->setText("Ieslēgt mikseri");
        ui->label6_1->setText("Izslēgt mikseri");

        ui->label1_2->setText(QString::number(12));
        ui->label2_2->setText(QString::number(22));
        ui->label3_2->setText(QString::number(32));
        ui->label4_2->setText("");
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
        ui->label1_1->setText("Ātrums");
        ui->label2_1->setText("Statuss");
        ui->label3_1->setText("Kļūda");
        ui->label4_1->setText("-");
        ui->label5_1->setText("Ieslēgt mikseri");
        ui->label6_1->setText("Izslēgt mikseri");

        ui->label1_2->setText(QString::number(12));
        ui->label2_2->setText(QString::number(22));
        ui->label3_2->setText(QString::number(32));
        ui->label4_2->setText("");
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
    if(widgetElement->global.widHash[currentWid].type == WidgetType::widgT::Valve) {
        // open valve
        global.ballValveList[currentWidnpk].bValvePtr->close();
    }

            if(widgetElement->global.widHash[currentWid].type == WidgetType::widgT::Tvertne) {
                // save calibration full

            }

}


void WidgetService::on_pushButton_6_3_clicked()
{
    if(widgetElement->global.widHash[currentWid].type == WidgetType::widgT::Valve) {
        // close valve
        global.ballValveList[currentWidnpk].bValvePtr->open();
    }
    if(widgetElement->global.widHash[currentWid].type == WidgetType::widgT::Tvertne) {
        // save calibration empty

    }

}


void WidgetService::on_lineEdit_5_2_editingFinished()
{
    if(widgetElement->global.widHash[currentWid].type == WidgetType::widgT::Tvertne) {

    }
}


void WidgetService::on_lineEdit_6_2_editingFinished()
{
    if(widgetElement->global.widHash[currentWid].type == WidgetType::widgT::Tvertne) {


    }
}

void WidgetService::timerEvent(QTimerEvent *event)
{
 Q_UNUSED (event)
    updateFormData();

}

