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
    connect (this, SIGNAL(newData(QStringList)), this, SLOT(newDataUpdateCh(QStringList)));
    initUI();
}

Scale::~Scale()
{
    delete ui;
}
void Scale::initUI()
{

}

bool Scale::initPort()
{
    qDebug() << "\ninitPort()";

    QTextStream out(stdout);
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    //qDebug() << "\n";
    out << QObject::tr("Total number of ports available: ") << serialPortInfos.count() << "\n";

    const QString blankString = QObject::tr("N/A");
    QString description;
    QString manufacturer;
    QString serialNumber;

    QString str = "Available com port: \n";
    //ui->textEditInfo->append(str);

    for (const QSerialPortInfo &serialPortInfo : serialPortInfos) {
        description = serialPortInfo.description();
        manufacturer = serialPortInfo.manufacturer();
        serialNumber = serialPortInfo.serialNumber();
        qDebug() <<serialNumber <<description << manufacturer << "\n"; // << endl

        ComInfo  comInfo;
        comInfo.port = serialPortInfo.portName();
        comInfo.location = serialPortInfo.systemLocation();
        comInfo.description = !description.isEmpty() ? description : blankString;
        comInfo.manufacturer = !manufacturer.isEmpty() ? manufacturer : blankString;
        comInfo.serialNumber = !serialNumber.isEmpty() ? serialNumber : blankString;
        comInfo.vendorIdentifier = serialPortInfo.hasVendorIdentifier() ? QByteArray::number(serialPortInfo.vendorIdentifier(), 16) : blankString;
        comInfo.productIdentifier = serialPortInfo.hasProductIdentifier() ? QByteArray::number(serialPortInfo.productIdentifier(), 16) : blankString;


        comPortMap.insert(serialPortInfo.portName(),comInfo);
        str = "";
        str.append(QObject::tr("Port: ") + serialPortInfo.portName() + "\n");
        str.append(QObject::tr("Location: ") + serialPortInfo.systemLocation() + "\n");
        str.append(QObject::tr("Description: ") + (!description.isEmpty() ? description : blankString) + "\n");
        str.append(QObject::tr("Manufacturer: ") + (!manufacturer.isEmpty() ? manufacturer : blankString) + "\n");
        str.append(QObject::tr("Serial number: ") + (!serialNumber.isEmpty() ? serialNumber : blankString) + "\n");
        str.append(QObject::tr("Vendor Identifier: ") + (serialPortInfo.hasVendorIdentifier() ? QByteArray::number(serialPortInfo.vendorIdentifier(), 16) : blankString) + "\n");
        str.append(QObject::tr("Product Identifier: ") + (serialPortInfo.hasProductIdentifier() ? QByteArray::number(serialPortInfo.productIdentifier(), 16) : blankString) + "\n\n");

        qDebug() << str;
        //ui->textEditInfo->append(str);
        qDebug() << str;

    }
    qDebug() << "Open port:";
    //  m_serial = new QSerialPort(this);

    corectPort = nullptr;
    foreach (ComInfo cInfo, comPortMap){

        // "403"  FDI RS232
        // "2341" Arduino MEGA
        if(cInfo.vendorIdentifier == "403"){
            corectPort = cInfo.port;
        }
    }

    if(corectPort != nullptr){
        sc_serial->setPortName(corectPort);
        sc_serial->setBaudRate(QSerialPort::Baud115200);
        sc_serial->setDataBits(QSerialPort::Data8);
        sc_serial->setParity(QSerialPort::NoParity);
        sc_serial->setStopBits(QSerialPort::OneStop);
        sc_serial->setFlowControl(QSerialPort::NoFlowControl);

        str = "Selected port: ";
        str.append(corectPort);
        str.append("\n");
        str.append(comPortMap[corectPort].manufacturer);
        str.append(", ");
        str.append(comPortMap[corectPort].serialNumber);
        str.append("\n");
        //ui->textEditInfo->append(str);
        qDebug() << str;

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
        str.append("403");
        qDebug() << str;
        return false;
    }

}

void Scale::sendData(QString send)
{
    QString str = "01";
    str.append(send);
    QByteArray utf8Data = str.toUtf8();
    const qint64 written = sc_serial->write(utf8Data);
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


        qDebug() <<"readSerial()" <<data ;//<< m_serial->waitForReadyRead();

        if(!data.isEmpty()) {                                                             // If the byte array is not empty
            char *temp = data.data();
            // Get a '\0'-terminated char* to the data

            for(int i = 0; temp[i] != '\0'; i++) {                                        // Iterate over the char*
                switch(STATE) {                                                           // Switch the current state of the message
                case WAIT_START:                                                          // If waiting for start [$], examine each char
                    if(temp[i] == START_MSG) {                                            // If the char is $, change STATE to IN_MESSAGE
                        STATE = IN_MESSAGE;
                        receivedData.clear();                                             // Clear temporary QString that holds the message
                        break;                                                            // Break out of the switch
                    }
                    break;
                case IN_MESSAGE:                                                          // If state is IN_MESSAGE
                    if(temp[i] == END_MSG) {                                              // If char examined is ;, switch state to END_MSG
                        STATE = WAIT_START;
                        QStringList incomingData = receivedData.split(' ');               // Split string received from port and put it into list
                        //emit newData(incomingData);                                       // Emit signal for data received with the list

                        if(receiveDataRequest){
                            emit newData(incomingData);
                            //qDebug() <<"emit" <<incomingData;
                            receiveDataRequest = false;
                        }
                        break;
                    }
                    else if (isdigit (temp[i]) || isspace (temp[i]) || temp[i] =='-' || temp[i] =='.')
                    {
                        /* If examined char is a digit, and not '$' or ';', append it to temporary string */
                        receivedData.append(temp[i]);
                    }
                    break;
                default: break;
                }
            }
        }
    }

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
        receiveDataRequest = true;

        //if(att > 100){
        //    int range = att * 1.1;
        //    chart1->axes(Qt::Horizontal).first()->setRange(0, range);
        //}
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
}

