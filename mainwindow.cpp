#include "mainwindow.h"
#include "hwports.h"
#include "qforeach.h"
#include "ui_mainwindow.h"
#include <Qdebug>

#include <QFile>

//#include "rs232.h"
#include "parmani.h"
#include "componentcard.h"
#include "recipet.h"

#include <QMouseEvent>
#include "global.h"
#include <QDateTime>
#include <QRandomGenerator>
#include "modbus485.h"
#include "runprocess.h"




MainWindow::MainWindow(Global& global, QWidget* parent)
    : QMainWindow(parent)
    , scale(global, this)
    , global(global)
    , ui(new Ui::MainWindow)
    , procUI1(global, this)
    , procUI2(global, this)
    , modbus485(global, this)
    , runprocess(global, this)
    , rs232 (global, this)
    , hwService(global,rs232, this)
    , procesSteps(global, this)


{
    // modbus485.start();  in thread
    //modbus485.run();

    ui->setupUi(this);
    procUI2.show();
    procUI1.show();
    procesSteps.show();

    //global.scalePtr = *scale;

    QString settingsFile = QApplication::applicationDirPath() + "/settings.ini";
    global.settingsFileName = settingsFile;

    QSettings settings(settingsFile, QSettings::IniFormat);
    qDebug() << "settingsFile" << settingsFile << global.settingsFileName;




    //IntegerSetting = settings.value("SettingName", default).toInt();
    // BooleanSetting = settings.value("SettingName", default).toBool();


    //areaY = size().height();
    //areaX = size().width();
    global.UIXsize = size().width();
    global.UIYsize = size().height();
    qDebug() << "UI size" << global.UIXsize << ":" << global.UIYsize;

    initUI();
    // drawWidgets();


    qDebug() << "Autosettings  Com ports";
    HwPorts* hwPorts = new HwPorts(global, this);
    if (!hwPorts->autoScanComPorts()) {
        qDebug() << "ERROR!!! Com port nof found !!";
        ui->textEdit_Field->setText("Kļūda sistērmā!\n Nevar automātiski atrast Com. portus! Veiciet to manuāli!");
    } else {
        ui->textEdit_Field->setText("Komunikācija ar perifēriju izveidota!");
    }

    initTimer = true;
    timerIdUpd = startTimer(500);
    // timerTick = startTimer(1);
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

    connect(&modbus485, &Modbus485::valChangeAn,
            &hwService, &HWService::updateDataAn);

    connect(&modbus485, &Modbus485::valChangeDi,
            &hwService, &HWService::updateDataDi);

    connect(&modbus485, &Modbus485::valChangeDi,
            this, &MainWindow::changeInputVal);


    connect(&hwService, &HWService::factoryReset,
            &modbus485, &Modbus485::factoryReset);

    //connect (&hwService, &HWService::outputChange,
    //         &modbus485,&Modbus485::wr23IOD32);

    connect(&runprocess, &Runprocess::diOutputChangeSi,
            &modbus485, &Modbus485::diOutputChangeSl);

    connect(&hwService, &HWService::diOutputChangeSi,
            &modbus485, &Modbus485::diOutputChangeSl);


    connect(&runprocess, &Runprocess::diOutputChangeSi,
            &hwService, &HWService::updateDataDi);

    connect(&runprocess, &Runprocess::stateChange,
            &procesSteps, &ProcesSteps::setTabValRecord);

    connect(&procesSteps, &ProcesSteps::startR,
            this, &MainWindow::on_pushButton_start_clicked);

    connect(&procesSteps, &ProcesSteps::stopR,
            this, &MainWindow::on_pushButton_stop_clicked);

    connect(&procesSteps, &ProcesSteps::pauseR,
            this, &MainWindow::on_pushButton_pause_clicked);

    connect(&procesSteps, &ProcesSteps::nextR,
            this, &MainWindow::processtepsPrwsNext);


    connect(&runprocess, &Runprocess::printInfo,
             &procesSteps, &ProcesSteps::printInfo);

  //  connect(&runprocess, &Runprocess::stateChange,
  //          &procesSteps, &ProcesSteps::setTabValRecord);
    connect (&runprocess,&Runprocess::resetScales,
            &scale,&Scale::resetScales);

    currentTime = "currentTime";
    ui->label_2->setText(currentTime);
    qDebug() << "-------------------modbus485.init()";
    modbus485.init();
    att = 1;

    qDebug() << "global.ballvalveTest->close();" << global.getTick();
    global.ballvalveTest0->close();
    loadSettings();
    // only for testing:
    Scale* scale = new Scale(global, this);
    ui->pushButton_pause->setCheckable(true);
    //  scale->show();
    // processStepsWindow.show();

}

MainWindow::~MainWindow() {
    saveSettings();
    delete ui;
}

void MainWindow::changeInputVal(int row, int val) {
    Q_UNUSED(val);
    Q_UNUSED(row);
/*
    foreach(Global::wdataStruct widData, global.widHash) {


        if ((widData.var1 == row) |
            (widData.var2 == row) ) {
            qDebug() << "hange inputs, update " << widData.name;
            widData.ptrCurrWidget->updateSettings();
        }
    }
    */
}


void MainWindow::resizeEvent(QResizeEvent* event) {
    Q_UNUSED(event);

    float koefx = 1.0;
    float koefy = 1.0;
    float koef = 1.0;

    //qDebug() << "MainWindow::resizeEvent" << size().height() << size().width();
    global.UIXresizeSize = size().width();
    global.UIYresizeSize = size().height();

    if (size().width() > 0 && size().height() > 0) {
        koefx = (float)global.UIXsize / global.UIXresizeSize;
        koefy = (float)global.UIYsize / global.UIYresizeSize;
    }

    if (koefx >= koefy) {
        koef = koefx;
    } else {
        koef = koefy;
    }

    if (koef == 0) {
        koef = 1;
    }
    //qDebug() << "resizeEvent UIsize Main" << global.UIXsize << global.UIYsize << size().width() << size().height() << koefx << koefy << koef;
    global.zoomKoef = koef;

}

void MainWindow::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        qDebug() << "Main mousePressEvent MainWind";
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event) {
    event->accept();

    // get the cursor position of this event
    //const QPoint& pos = event->pos();

    //int dx = pos.x();
    //int dy = pos.y();

    // qDebug() << " Main mouseMoveEventdx:dy" << dx << dy;
}

void MainWindow::timerEvent(QTimerEvent* event) {
    // Q_UNUSED(event)

    if (event->timerId() == timerIdUpd) {
        currentTime = QTime::currentTime().toString("hh:mm:ss");
        setWindowTitle(currentTime);
        ui->statusbar->showMessage(statusStr + currentTime);




    }


    // if (event->timerId() == timerTick) {
    //  global.addTick();
    // }
}

void MainWindow::loadSettings() {

    //settings from file settings.ini
    int val;
    bool ok;
    QString str;


    QString settingsFile = global.settingsFileName;
    QSettings settings(settingsFile, QSettings::IniFormat);
    settings.beginGroup("Tvertne_calibrate_level_sensor");

    //11111111111
    val = settings.value("TVERTNE1KALIBEMPTY", "").toInt(&ok);
    if (!ok) {
        str = QString("Kļūda Init failā TVERTNE1KALIBEMPTY !!!").arg(val);
        qDebug() << str;
        val = 0;
    }
    global.DIinput[TVERTNE1KALIBEMPTY].value = val;

    val = settings.value("TVERTNE1KALIBFULL", "").toInt(&ok);
    if (!ok) {
        str = QString("Kļūda Init failā TVERTNE1KALIBFULL !!!").arg(val);
        qDebug() << str;
        val = 0;
    }
    global.DIinput[TVERTNE1KALIBFULL].value = val;
        //222222222
    val = settings.value("TVERTNE2KALIBEMPTY", "").toInt(&ok);
    if (!ok) {
        str = QString("Kļūda Init failā TVERTNE2KALIBEMPTY !!!").arg(val);
        qDebug() << str;
        val = 0;
    }
    global.DIinput[TVERTNE2KALIBEMPTY].value = val;

    val = settings.value("TVERTNE2KALIBFULL", "").toInt(&ok);
    if (!ok) {
        str = QString("Kļūda Init failā TVERTNE2KALIBFULL !!!").arg(val);
        qDebug() << str;
        val = 0;
    }
    global.DIinput[TVERTNE2KALIBFULL].value = val;

    //33333333
    val = settings.value("TVERTNE3KALIBEMPTY", "").toInt(&ok);
    if (!ok) {
        str = QString("Kļūda Init failā TVERTNE3KALIBEMPTY !!!").arg(val);
        qDebug() << str;
        val = 0;
    }
    global.DIinput[TVERTNE3KALIBEMPTY].value = val;

    val = settings.value("TVERTNE3KALIBFULL", "").toInt(&ok);
    if (!ok) {
        str = QString("Kļūda Init failā TVERTNE3KALIBFULL !!!").arg(val);
        qDebug() << str;
        val = 0;
    }
    global.DIinput[TVERTNE3KALIBFULL].value = val;


    //44444444
    val = settings.value("TVERTNE4KALIBEMPTY", "").toInt(&ok);
    if (!ok) {
        str = QString("Kļūda Init failā TVERTNE4KALIBEMPTY !!!").arg(val);
        qDebug() << str;
        val = 0;
    }
    global.DIinput[TVERTNE4KALIBEMPTY].value = val;

    val = settings.value("TVERTNE4KALIBFULL", "").toInt(&ok);
    if (!ok) {
        str = QString("Kļūda Init failā TVERTNE4KALIBFULL !!!").arg(val);
        qDebug() << str;
        val = 0;
    }
    global.DIinput[TVERTNE4KALIBFULL].value = val;
    //55555555
    val = settings.value("TVERTNE5KALIBEMPTY", "").toInt(&ok);
    if (!ok) {
        str = QString("Kļūda Init failā TVERTNE5KALIBEMPTY !!!").arg(val);
        qDebug() << str;
        val = 0;
    }
    global.DIinput[TVERTNE5KALIBEMPTY].value = val;

    val = settings.value("TVERTNE5KALIBFULL", "").toInt(&ok);
    if (!ok) {
        str = QString("Kļūda Init failā TVERTNE5KALIBFULL !!!").arg(val);
        qDebug() << str;
        val = 0;
    }
    global.DIinput[TVERTNE5KALIBFULL].value = val;
    settings.endGroup();

    qDebug() << "loadSettings() TVERTNE kalib,"
             << global.DIinput[TVERTNE1KALIBEMPTY].value
             << global.DIinput[TVERTNE1KALIBFULL].value
             << global.DIinput[TVERTNE2KALIBEMPTY].value
             << global.DIinput[TVERTNE2KALIBFULL].value
             << global.DIinput[TVERTNE3KALIBEMPTY].value
             << global.DIinput[TVERTNE3KALIBFULL].value
             << global.DIinput[TVERTNE4KALIBEMPTY].value
             << global.DIinput[TVERTNE4KALIBFULL].value
             << global.DIinput[TVERTNE5KALIBEMPTY].value
             << global.DIinput[TVERTNE5KALIBFULL].value
        ;

}

void MainWindow::saveSettings() {

    QString settingsFile = global.settingsFileName;
    QSettings settings(settingsFile, QSettings::IniFormat);
    QString sText = settingsFile;

    settings.beginGroup("mainwindow");
    settings.setValue("Description", "Global information");
    settings.setValue("settingsFile", sText);

    QDateTime date = QDateTime::currentDateTime();
    sText = date.toString("dd.MM.yyyy hh:mm:ss");


    // sText = QTime::currentTime().toString("YY:MM:DD:hh:mm:ss");
    qDebug() << "QTime::currentTime:" << sText;
    QString str = global.appSwVers;
    str.append(sText) ;
    settings.setValue("SwVers", str);
    settings.setValue("last_save", sText);
    settings.setValue("UI_width", size().width());
    settings.setValue("UI_height", size().height());
    settings.endGroup();


}




void MainWindow::initUI() {
    qDebug() << "start UI settings";
    this->move(1000, 1000);


    QPalette pal = QPalette();

    pal.setColor(QPalette::Window, global.backgroundColor); //QColor(255, 0, 0, 127)
    //pal.setColor(QPalette::Window, QColor(242, 219, 238, 0.251));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    QColor col = QColor(Qt::green);
    QString qss = QString("background-color: %1").arg(col.name());
    ui->pushButton_Stop->setStyleSheet(qss);

    pal.setColor(QPalette::Base, Qt::yellow);
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

    /*
    enum mCombo{
        Iestatijumi,
        Receptes,
        Kartiņa,
        Mērījumi,
        Serviss,
        Ražošana,
        Procesu_programmēšana,
        Par_mani,
    };

    QStringList menuComboxList  = {
            "Iestatijumi"
            ,"Receptes"
            ,"Kartiņa"
            ,"Mērījumi"
            ,"Serviss"
            ,"Ražošana"
            ,"Procesu programmēšana"
            ,"Par_mani"
        };
*/
    ui->comboBox->addItems(menuComboxList);
    ui->comboBox->setCurrentIndex(0);


    // default settings.

    //global.DIoutput[MIXSPEED].value = 20;
    DIOUT(MIXSPEED, 20)

    statusStr = "\u00A9 2024.  vers: 0.0, build: ";
    statusStr.append(__DATE__);
    statusStr.append(",   tel. 29222201,   current time: ");

    QString datetime = QStringLiteral(__DATE__) + QStringLiteral(" ") + QStringLiteral(__TIME__);
    qDebug()  << datetime;
}



void MainWindow::appendInfo(QString str, QColor col) {
    ui->textEdit_Field->setTextColor(col);
    ui->textEdit_Field->append(str);
    ui->textEdit_Field->setTextColor(Qt::black);

    QTextCursor cursor = ui->textEdit_Field->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit_Field->setTextCursor(cursor);

}

void MainWindow::delAllWid() {
    foreach(Global::wdataStruct widData, global.widHash) {
        // qDebug() << widData.name<< " exist ? " <<widData.ptrCurrWidget;
        if (widData.ptrCurrWidget) {
            widData.ptrCurrWidget->close();
            //  qDebug() << widData.name<< " close() ";
        }
    }
}

void MainWindow::processtepsPrwsNext()
{
    runprocess.next();
}



void MainWindow::on_pushButton_Stop_clicked() {
    qDebug() << "pushButton_EMERG_STOP_clicked() ????????????????????????????????????";
    QColor col = QColor(Qt::red);
    QString qss = QString("background-color: %1").arg(col.name());
    ui->pushButton_Stop->setStyleSheet(qss);


    qss = currentTime;
    qss.append("  PUSH EMERGENCY STOP !!!");
    appendInfo(qss, Qt::red);

}


/*
    enum mCombo{
        Iestatijumi,
        Receptes,
        Kartina,
        Mērījumi,
        Serviss,
        Ražošana,
        Procesu_programmēšana,
        Par_mani,
    };
      */
void MainWindow::on_comboBox_currentIndexChanged(int index) {

    switch (index) {
    case mCombo::Iestatijumi:
        // rs232.show();
        break;

    case mCombo::Receptes:
    {
        Recipet* recipet = new Recipet(global, this);
        recipet->show();

        break;
    }
    case mCombo::Kartina:
    {
        ComponentCard* componentCard = new ComponentCard(global, this);
        componentCard->show();

        break;
    }
    case mCombo::Serviss :
    {
        //HWService *hwService = new HWService(global,this);
        //hwService = new HWService(global,this);
        hwService.show();
        break;
    }
    case mCombo::Razosana:
    {
        //  Runprocess *runprocess = new Runprocess(global.this);
        runprocess.show();

        break;
    }
    case mCombo::Procesu_programmesana:
    {
       // procUI1.maximizeWindow();
        procesSteps.show();
       procesSteps.maximizeWindow();
        break;
    }
    case mCombo::Par_mani:
    {
        ParMani* parmani = new ParMani(global, this);
        //parmani = new ParMani(global,this);
        parmani->show();
        break;
    }

    default:
        break;
    }

    ui->comboBox->setCurrentIndex(0);
    qDebug() << " Combo box index Finish" << index << menuComboxList;
}


void MainWindow::on_pushButton_Dyno_clicked() {
    procUI2.maximizeWindow();
    procUI2.show();
    procUI2.raise();
}

void MainWindow::on_pushButton_Mix_clicked() {
    procUI1.maximizeWindow();
    procUI1.show();
    procUI1.raise();
}

void MainWindow::on_pushButton_Recipes_clicked() {
    // ComponentCard *componentCard = new ComponentCard(global,this);
    // componentCard->show();
    Recipet* recipet = new Recipet(global, this);
    recipet->show();

}


void MainWindow::on_pushButton_Service_clicked() {
    hwService.show();
}


void MainWindow::on_pushButton_start_clicked()
{
    runprocess.start(0x300);
}

void MainWindow::on_pushButton_stop_clicked()
{
    runprocess.stop();
}

void MainWindow::on_pushButton_pause_clicked()
{
    pause = !pause;
    runprocess.pause(pause);
    ui->pushButton_pause->setChecked(pause);
}

