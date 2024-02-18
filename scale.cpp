#include "scale.h"
#include "ui_scale.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QDateTime>


Scale::Scale(Global &global, QWidget *parent) :
    QMainWindow(parent)
  , global(global)
  , ui(new Ui::Scale)
{
    timer1sId  = startTimer(1000, Qt::CoarseTimer);
    ui->setupUi(this);
    sc_serial = new QSerialPort(this);
    if (!initPort()){
        qDebug() << "start timemark 1000";
        timerInit = startTimer(1000, Qt::CoarseTimer);
    }
    connect(sc_serial, &QSerialPort::readyRead,this, &Scale::readSerial);   //readyRead
    connect (this, SIGNAL(newData(QStringList)), this, SLOT(newDataUpdate(QStringList)));
    // initUI();
}

Scale::~Scale()
{
    delete ui;
}
void Scale::initUI()
{
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, global.backgroundColor); //QColor(255, 0, 0, 127)
    //pal.setColor(QPalette::Window, QColor(242, 219, 238, 0.251));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

bool Scale::initPort()
{
    qDebug() << "\ninitPort()";
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
            qDebug() << str;
            if(timerInit > 0){
                killTimer(timerInit);
            }
            return true;
        }
        else{
            str.append(" open error!");
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
    qDebug() << "sendData" << send << utf8Data ;
    Q_UNUSED(written);
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
            QString receivedData = QString(data);
            QStringList incomingData = receivedData.split(',');
            qDebug() <<"1 receivedData" <<incomingData;
            qDebug() <<"2 incomingData" <<incomingData;

            emit newData(incomingData);
            ui->label_Receive->setText(receivedData);
        }
    }
    /*
        qDebug() <<"readSerial()" <<data ;//<< m_serial->waitForReadyRead();

        if(!data.isEmpty()) {
            char *temp = data.data();
            // Get a '\0'-terminated char* to the data


            for(int i = 0; temp[i] != '\0'; i++) {
                switch(STATE) {
                case WAIT_START:
                    if(temp[i] == START_MSG) {
                        STATE = IN_MESSAGE;
                        receivedData.clear();
                        break;
                    }
                    break;
                case IN_MESSAGE:
                    if(temp[i] == END_MSG) {
                        STATE = WAIT_START;
                        QStringList incomingData = receivedData.split(',');
                        // Emit signal for data received with the list
                        emit newData(incomingData);
                        ui->label_Receive->setText(temp);
                        //qDebug() <<"emit" <<incomingData;
                        break;
                    }
                    else if (isdigit (temp[i]) || isspace (temp[i]) || temp[i] =='-' || temp[i] =='.')
                    {
                        // If examined char is a digit, and not '$' or ';', append it to temporary string
                        receivedData.append(temp[i]);
                    }
                    break;
                default: break;
                }
            }
        } //if(!data.isEmpty())

    }

*/
}



void Scale::timerEvent(QTimerEvent *event)
{

    if(event->timerId() == timer1sId){
        currentTime = QTime::currentTime().toString("hh:mm:ss");
        setWindowTitle(currentTime);
        // qDebug() <<startTime << currentTime;

        /*
       // if(!startTime.isNull()){
        if(startTime != QTime(0,0)){

            QTime finishTime = QTime::currentTime();

            int sec = startTime.secsTo(finishTime);
            QTime t = QTime(0,0).addSecs(sec);
              QString durat = QString("%1h. %2min. %3sek.")
                .arg(t.hour()).arg(t.minute()).arg(t.second());

            QString str = "  Ieraksts sākts ";
            str.append(startTime.toString("hh:mm:ss"));
            str.append(",  ieraksta ilgums ");
            str.append(durat);     //.toString("hh:mm:ss")
            str.append(", laika iedaļas vērtība ");
            str.append(QString::number(timeMark,10));
            str.append("s.");
            ui->label_chart_info->setText(str);
        }
        */
    }


    if(event->timerId() == timerId){
        // qDebug()<< "Event Id";
        att++;

    }

    if(event->timerId() == timerInit){
        qDebug()<< "Event Init";
        initPort();
    }


}

void Scale::on_lineEdit_Send_editingFinished()
{

    QString val = ui->lineEdit_Send->text();
    sendData(val);
}


void Scale::on_pushButton_clicked()
{
    sendData("READ");
    readSerial();
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

void Scale::newDataUpdate(QStringList currSdata)
{

    bool ok;
    float t1 = 0.0;


    qDebug() << "currSdata" <<currSdata.size() << currSdata;


    foreach (QString str, currSdata) {
        qDebug() << str;
    }

    if(currSdata.size() == 4){

        ui->label_Stat1->setText(currSdata[0]);
        ui->label_Stat2->setText(currSdata[1]);

        t1 = currSdata[2].toFloat(&ok);
        if(!ok){
              // ui->textEditInfo->append(QString("Uztverti kļūdaini dati !!!"));
            t1 = 0;
        }

       // t1 = currSdata[2].toFloat(&ok);

        ui->label_Value->setText(QString::number(t1));




    }



}

