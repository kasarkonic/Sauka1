#include "mainwindow.h"
#include "dyno.h"
#include "hwports.h"
#include "qforeach.h"
#include "ui_mainwindow.h"
#include <Qdebug>

#include <QFile>

#include "rs232.h"
#include "parmani.h"
#include "componentcard.h"
#include "recipet.h"

#include <QMouseEvent>
#include "global.h"
#include <QDateTime>
#include <QRandomGenerator>
#include "modbus485.h"
#include "runprocess.h"



MainWindow::MainWindow(Global &global,  QWidget *parent)
    : QMainWindow(parent)
    //, global(global)
    , scale(global,this)
    , global(global)
    , ui(new Ui::MainWindow)
    , procUI1(global,this)
    , procUI2(global,this)
    , modbus485(global,this)
    , runprocess(global,this)
    , hwService(global,this)


{


    modbus485.start();
    //modbus485.run();

    ui->setupUi(this);
    procUI2.show();
    procUI1.show();
    //global.scalePtr = *scale;

    QString settingsFile = QApplication::applicationDirPath() + "/settings.ini";
    global.settingsFileName =  settingsFile;

    QSettings settings(settingsFile, QSettings::IniFormat);
    qDebug() << "settingsFile" << settingsFile << global.settingsFileName;

    //IntegerSetting = settings.value("SettingName", default).toInt();
    // BooleanSetting = settings.value("SettingName", default).toBool();


    //areaY = size().height();
    //areaX = size().width();
    global.UIXsize = size().width();
    global.UIYsize = size().height();
    qDebug() << "UI size" << global.UIXsize <<":" << global.UIYsize;

    initUI();
    // drawWidgets();


    qDebug() << "Autosettings  Com ports";
    HwPorts *hwPorts = new HwPorts(global,this);
    if(!hwPorts->autoScanComPorts()){
        qDebug()<< "ERROR!!! Com port nof found !!";
        ui->textEdit_Field->setText("Kļūda sistērmā!\n Nevar automātiski atrast Com. portus! Veiciet to manuāli!");
    }
    else{
        ui->textEdit_Field->setText("Komunikācija ar perifēriju izveidota!");
    }

    initTimer = true;
    timerIdUpd = startTimer(500);
    timerTick = startTimer(1);
    timerUpdateOutput = startTimer(200);

    // connect(&valve,SIGNAL(openService()),this,SLOT(openServiceFormValve()));  old style
    //    connect(
    //               &valve, &Valve::openServiceValve,
    //               this, &MainWindow::openServiceFormValve
    //               );
    //   connect(
    //                &pump, &Pump::openServicePump,
    //                this, &MainWindow::openServiceFormPump
    //                );

    connect(&modbus485,&Modbus485::valChangeAn,
            &hwService, &HWService::updateDataAn);

    connect(&modbus485,&Modbus485::valChangeDi,
            &hwService, &HWService::updateDataDi);

    connect(&modbus485,&Modbus485::valChangeDi,
            this, &MainWindow::changeInputVal);


    connect (&hwService, &HWService::factoryReset,
             &modbus485, &Modbus485::factoryReset);

    //connect (&hwService, &HWService::outputChange,
    //         &modbus485,&Modbus485::wr23IOD32);

    connect (&runprocess,&Runprocess::diOutputChangeSi,
                &modbus485,&Modbus485::diOutputChangeSl);

    connect (&hwService,&HWService::diOutputChangeSi,
            &modbus485,&Modbus485::diOutputChangeSl);


    connect(&runprocess,&Runprocess::diOutputChangeSi,
            &hwService, &HWService::updateDataDi);


    // sender, &Sender::valueChanged,
    //     receiver, &Receiver::updateValue;
    currentTime = "currentTime";
    ui->label_2->setText(currentTime);
    qDebug() <<  "-------------------modbus485.init()";
    modbus485.init();
    att = 1;
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

void MainWindow::changeInputVal(int row, int val)
{
    Q_UNUSED(val);

    foreach (Global::wdataStruct widData, global.widHash){


        if( (widData.act_Addres1 == row) |
           // (widData.act_Addres2 == row) |
            (widData.sensAddres1 == row) |
            (widData.sensAddres2 == row)){
            qDebug() << "hange inputs, update "  << widData.name;
            widData.ptrCurrWidget->updateSettings();
        }
    }
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED (event);

    float koefx = 1.0;
    float koefy = 1.0;
    float koef = 1.0;

    qDebug() << "MainWindow::resizeEvent"  << size().height() << size().width();
    global.UIXresizeSize = size().width();
    global.UIYresizeSize = size().height() ;

    if(size().width() > 0 && size().height() > 0){
        koefx =  (float)global.UIXsize/global.UIXresizeSize;
        koefy = (float)global.UIYsize/global.UIYresizeSize;
    }

    if(koefx >= koefy){
        koef = koefx;
    }
    else{
        koef = koefy;
    }

    if(koef == 0){
        koef = 1;
    }
     qDebug() << "resizeEvent UIsize Main"  << global.UIXsize << global.UIYsize <<size().width()<<size().height()<<koefx <<koefy<<koef;
    global.zoomKoef = koef;

}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        qDebug() << "Main mousePressEvent MainWind" ;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();

    // get the cursor position of this event
    const QPoint& pos = event->pos();

    int dx =pos.x();
    int dy = pos.y();

    qDebug() << " Main mouseMoveEventdx:dy"<< dx <<dy ;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
   // Q_UNUSED(event)

    if(event->timerId() == timerIdUpd){
        currentTime = QTime::currentTime().toString("hh:mm:ss");
        setWindowTitle(currentTime);
        ui->statusbar->showMessage (statusStr + currentTime);

       // qDebug() <<  "-------------------";
        //modbus485.readData();
        // modbus485.rd24DIB32(4,0xc0);
        // modbus485.rd23IOD32(4,0xc0);
        // digital output
        /*  if (att < 0xffff)
        modbus485.wr23IOD32(4,0x70,att);  // wr23IOD32(7,0x70, 0xff);
    else
        modbus485.wr23IOD32(4,0x71,att>>16);  // wr23IOD32(7,0x70, 0xff);
 */



       // if(!global.disableRS485){

        // analog input, next DI input, next update DI output
       // modbus485.rdN4AIB16(2, 0,15);   // ok analog input
       // modbus485.rd23IOD32(4,0xc0);  // ok digital input
       //  }
       }


    if(event->timerId() == timerTick){
        global.addTick();
    }
}

void MainWindow::loadSettings()
{

    // QString settingsFile = global.settingsFileName;
    //  QSettings settings(settingsFile, QSettings::IniFormat);
    // QString sText = settings.value("last_save", "").toString();
    //  qDebug() << "last_save " << sText ;

    // valve.loadSettings();
    // pump.loadSettings();

}

void MainWindow::saveSettings()
{

    QString settingsFile = global.settingsFileName;
    QSettings settings(settingsFile, QSettings::IniFormat);
    QString sText = settingsFile;

    settings.beginGroup("mainwindow");
    settings.setValue("settingsFile", global.appSwVers);
    settings.setValue("settingsFile", sText);

    QDateTime date = QDateTime::currentDateTime();
    sText = date.toString("dd.MM.yyyy hh:mm:ss");


    // sText = QTime::currentTime().toString("YY:MM:DD:hh:mm:ss");
    qDebug() << "QTime::currentTime:" << sText ;
    settings.setValue("last_save", sText);


    settings.setValue("UI_width", size().width());
    settings.setValue("UI_height", size().height());
    settings.endGroup();


}




void MainWindow::initUI()
{
    qDebug() << "start UI settings";
    this->move(1000,1000);


    QPalette pal = QPalette();

    pal.setColor(QPalette::Window, global.backgroundColor); //QColor(255, 0, 0, 127)
    //pal.setColor(QPalette::Window, QColor(242, 219, 238, 0.251));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    QColor col = QColor(Qt::green);
    QString qss = QString("background-color: %1").arg(col.name());
    ui->pushButton_Stop->setStyleSheet(qss);

    pal.setColor(QPalette::Base,Qt::yellow);
    ui->textEdit_Field->setPalette(pal);

    // strādā   ui->label_logo->setStyleSheet("background-image: url(:/pictures/logo2.png)");
    QPixmap pixmap(":/pictures/logo2.png");
    ui->label_logo->setPixmap(pixmap);
    ui->label_logo->setMask(pixmap.mask());

    QString str = "Šaja laukā tiek attēloti tekošie notikumi un avārias situāciju apraksti.\n Piemēram:\n\n\n";
    str.append("10.01:23 Sistēma ieslēgta\n");
    str.append("10.02:25 ieslēdzās sapropeļa padeves vārsts V1\n");
    str.append("10.05:33 ieslēdzās sapropeļa padeves motors\n");
    str.append("10.07:43 ERROR ! vārsts V2 nav aizvēries\n");
    str.append("10.11:53 BRĪDINĀJUMS ! vārsta V4 aizversanas laiks 20s morma 12s\n");
    ui->textEdit_Field->setText(str);

    cmbList << "Iestatijumi" << "Receptes" <<"Kartiņa" << "Atskaites" << "Serviss"  << "Ražošana"<< "Par_mani";
    ui->comboBox->addItems(cmbList);
    ui->comboBox->setCurrentIndex(0);






    // default settings.

    global.DIoutput[MIXSPEED].value = 50;

}






void MainWindow::appendInfo(QString str, QColor col)
{
    ui->textEdit_Field->setTextColor(col);
    ui->textEdit_Field->append(str);
    ui->textEdit_Field->setTextColor(Qt::black);

    QTextCursor cursor = ui->textEdit_Field->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit_Field->setTextCursor(cursor);


}
/*
void MainWindow::drawWidgets()
{
    qDebug() << "widData draw  " << global.widHash.size() << "elements";

    foreach (Global::wdataStruct widData, global.widHash){

        if( widData.page == 0 || widData.page == 3 ){    // all pages
            // qDebug() << "drawWidgets Draw: " << widData.type << widData.name << "page" <<widData.page ;
            switch (widData.type) {
            case WidgetType::widgT::Dyno:
            {
                Dyno *dynoA = new Dyno(global,widData.name,this);
                ui->horizontalLayout_ProcessFlow->addWidget(dynoA);
            }
                break;

            case WidgetType::widgT::Mix:
            {
                Mix *mixA = new Mix(global,widData.name,this);
                ui->horizontalLayout_ProcessFlow->addWidget(mixA);
            }
                break;

            case WidgetType::widgT::Pipe:
            {
                Pipe *pipeA = new Pipe(global,widData.name,this);
                ui->horizontalLayout_ProcessFlow->addWidget(pipeA);
            }
                break;

            case WidgetType::Pump:
            {
                Pump *pumpA = new Pump(global,widData.name,this);
                ui->horizontalLayout_ProcessFlow->addWidget(pumpA);

            }
                break;

            case WidgetType::Tvertne:
            {
                Tvertne *tvertneA = new Tvertne(global,widData.name,this);
                ui->horizontalLayout_ProcessFlow->addWidget(tvertneA);

            }
                break;

            case WidgetType::Valve:
            {
                Valve *valveA = new Valve(global,widData.name,this);
                ui->horizontalLayout_ProcessFlow->addWidget(valveA);

            }
                break;

            case WidgetType::ScalesBase:
            {
                ScalesBase *scalesBase = new ScalesBase(global,widData.name,this);
                ui->horizontalLayout_ProcessFlow->addWidget(scalesBase);

            }
                break;

            case WidgetType::ScalesMass:
            {
                ScalesMass *scalesMass = new ScalesMass(global,widData.name,this);
                ui->horizontalLayout_ProcessFlow->addWidget(scalesMass);

            }
                break;


            default:
                qDebug() << "Wrong widget type !!! "  <<widData.type;
                break;
            }
        }
    }
}
*/
void MainWindow::delAllWid()
{
    foreach (Global::wdataStruct widData, global.widHash){
        // qDebug() << widData.name<< " exist ? " <<widData.ptrCurrWidget;
        if(widData.ptrCurrWidget){
            widData.ptrCurrWidget->close();
            //  qDebug() << widData.name<< " close() ";
        }
    }
}



void MainWindow::on_pushButton_Stop_clicked()
{
    qDebug() << "pushButton_EMERG_STOP_clicked() ????????????????????????????????????";
    QColor col = QColor(Qt::red);
    QString qss = QString("background-color: %1").arg(col.name());
    ui->pushButton_Stop->setStyleSheet(qss);


    qss = currentTime;
    qss.append("  PUSH EMERGENCY STOP !!!");
    appendInfo(qss,Qt::red);

}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    qDebug() << " Combo box index" << index << cmbList[index];
    // cmbList << "Iestatijumi" << "Receptes" <<"Kartiņa" << "Atskaites" << "Serviss"  << "Ražošana"<< "Par_mani";

    switch (index) {
    case 0:
        break;

    case 1:
    {
        Recipet *recipet = new Recipet(global,this);
        recipet->show();

        break;
    }
    case 2:
    {
        ComponentCard *componentCard = new ComponentCard(global,this);
        componentCard->show();

        break;
    }
    case 3:
    {
        Rs232 *rs232 = new Rs232(global,this);
        //rs232 = new Rs232(global,this);
        rs232->show();
        break;
    }
    case 4:
    {
        //HWService *hwService = new HWService(global,this);
        //hwService = new HWService(global,this);
        hwService.show();
        break;
    }
        case 5:
    {
      //  Runprocess *runprocess = new Runprocess(global.this);
            runprocess.show();

       // ParMani *parmani = new ParMani(global,this);
        //parmani = new ParMani(global,this);
       // parmani->show();
        break;
    }

    case 6:
    {
        ParMani *parmani = new ParMani(global,this);
        //parmani = new ParMani(global,this);
        parmani->show();
        break;
    }

    default:
        break;
    }

    ui->comboBox->setCurrentIndex(0);
    qDebug() << " Combo box index Finish" << index << cmbList[index];
}


void MainWindow::on_pushButton_Dyno_clicked()
{
    procUI2.show();
    procUI2.raise();
}

void MainWindow::on_pushButton_Mix_clicked()
{
    procUI1.show();
    procUI1.raise();
}

void MainWindow::on_pushButton_Recipes_clicked()
{
   // ComponentCard *componentCard = new ComponentCard(global,this);
   // componentCard->show();
    Recipet *recipet = new Recipet(global,this);
    recipet->show();

}


void MainWindow::on_pushButton_Service_clicked()
{
    hwService.show();
}

