#include "scale.h"
#include "ui_scale.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QDateTime>


Scale::Scale(Global &global, QWidget *parent) :
    QMainWindow(parent)
  , global(global)
  , ui(new Ui::Scale)
{

#ifdef ENABLE_WIDGET_SIZE
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::lightGray); //QColor(255, 0, 0, 127)
    pal.setColor(QPalette::Window, QColor(0, 0, 0, 20));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
#endif

    timerRead = startTimer(500, Qt::CoarseTimer);
    timer1sId  = startTimer(1000, Qt::CoarseTimer);
    ui->setupUi(this);
    sc_serial = new QSerialPort(this);
    if (!initPort()){
        qDebug() << "start timemark 1000";
        timerInit = startTimer(1000, Qt::CoarseTimer);
    }
    connect(sc_serial, &QSerialPort::readyRead,this, &Scale::readSerial);   //readyRead
    connect (this, SIGNAL(newData(QStringList)), this, SLOT(newDataUpdate(QStringList)));
    initUI();
}

Scale::~Scale()
{
    sc_serial->close();
    delete ui;
}
void Scale::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    sc_serial->close();
    qDebug() <<"Scale::closeEvent";
}
void Scale::initUI()
{
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, global.backgroundColor); //QColor(255, 0, 0, 127)
    //pal.setColor(QPalette::Window, QColor(242, 219, 238, 0.251));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    ui->verticalSlider->setMaximum(10);
}

bool Scale::initPort()
{
    qDebug() << "\ninitPort() scale" << global.dev1;
    QString str;

    corectPort = global.dev1;
    if(corectPort != nullptr){
        sc_serial->setPortName(corectPort);
        sc_serial->setBaudRate(QSerialPort::Baud115200);
        sc_serial->setDataBits(QSerialPort::Data8);
        sc_serial->setParity(QSerialPort::NoParity);
        sc_serial->setStopBits(QSerialPort::OneStop);
        sc_serial->setFlowControl(QSerialPort::NoFlowControl);


        str = corectPort;
        if(sc_serial->open(QIODevice::ReadWrite)){
            str.append(" open successful!\n");
            ui->label_5->setText(str);
            qDebug() << str;
            if(timerInit > 0){
                killTimer(timerInit);
            }
            return true;
        }
        else{
            str.append(" open error!");
            ui->label_5->setText(str);
            qDebug() << str;
            return false;
        }
    }
    else{
        str = "Available com port nof fond \n search Vendor Id ";
        str.append("403  ????????????????????");
        qDebug() << str;
        return false;
    }

    return false;
}

void Scale::sendData(QString send)
{
    QString str = "";
    str.append(send);
    QByteArray utf8Data = str.toUtf8();
    const qint64 written = sc_serial->write(utf8Data);
    //qDebug() << "sendData" << send << utf8Data ;
    Q_UNUSED(written);
    ui->lineEdit_Send->setText(send);
}

void Scale::readSerial()
{
    if(sc_serial->bytesAvailable()) {
        if(!sc_serial->canReadLine()){
            qDebug() <<"line not receive all";
            return;
        }

        // If any bytes are available
        QByteArray data = sc_serial->readLine(25);// readAll();  //readData()  readLineData()

        if(!data.isEmpty()) {
            bool ok;
            QString receivedData = QString(data);
            QStringList incomingData = receivedData.split(',');
            qDebug() <<"scale receivedData" <<incomingData;


            emit newData(incomingData);
            ui->label_Receive->setText(receivedData);
            global.scaleVal = receivedData.toInt(&ok);
            if(!ok){
               global.scaleVal = 0;
            }
        }
    }

}



void Scale::timerEvent(QTimerEvent *event)
{

    if(event->timerId() == timerTime){
        currentTime = QTime::currentTime().toString("hh:mm:ss");
        setWindowTitle(currentTime);
    }


    if(event->timerId() == timerRead){
        // qDebug()<< "Event Id";
        att++;
        sendData("READ\r\n");
    }

    if(event->timerId() == timerInit){
        //qDebug()<< "Event Init";
        initPort();
    }

}

void Scale::on_lineEdit_Send_editingFinished()
{

    QString val = ui->lineEdit_Send->text();
    sendData(val);
}

void Scale::on_pushButton_Zero_clicked()
{
    sendData("ZERO\r\n");
}


void Scale::on_pushButton_Tare_clicked()
{
    sendData("TARE\r\n");
}


void Scale::on_pushButton_Read_clicked()
{
    sendData("READ\r\n");
}

void Scale:: newDataUpdate(QStringList currSdata)
{

    bool ok;
    float t1 = 0.0;
   // qDebug() << "currSdata" <<currSdata.size() << currSdata;
   // foreach (QString str, currSdata) {
        //qDebug() << str;
   // }

    if(currSdata.size() == 4){
        qDebug() << currSdata[2];
        ui->label_Stat1->setText(currSdata[0]);
        ui->label_Stat2->setText(currSdata[1]);

        t1 = currSdata[2].toFloat(&ok);
        if(!ok){
              // ui->textEditInfo->append(QString("Uztverti kļūdaini dati !!!"));
            t1 = 0;
        }

       // t1 = currSdata[2].toFloat(&ok);
    t1 = 10.0 * t1;
        ui->label_Value->setText(QString::number(t1));

        global.sensList[11].analog = (int)t1;
        qDebug() << "save data sensor 11 AN" <<(int)t1;
    }
}


void Scale::on_pushButton_cont_reading_clicked()
{
    if(timerRead){
        killTimer(timerRead);
        QString str = QString("Start reading F=%1").arg(repeatePeriod);
        ui->pushButton_cont_reading->setText(str);
    }
    else{
        timerRead = startTimer(repeatePeriod, Qt::CoarseTimer);
        ui->pushButton_cont_reading->setText("Stop reading.");
    }
    qDebug() << "on_verticalSlider_valueChanged" << timerInit << repeatePeriod;
}


void Scale::on_verticalSlider_valueChanged(int value)
{
    qDebug() << "on_verticalSlider_valueChanged" << value << repeatePeriod;
    repeatePeriod = (1000 - 10 * value);
    if(timerRead){
        killTimer(timerRead);
        timerRead   = startTimer(repeatePeriod, Qt::CoarseTimer);
        ui->pushButton_cont_reading->setText("Start reading %1.");
    }
     qDebug() << "on_verticalSlider_valueChanged" << value << repeatePeriod;

}

