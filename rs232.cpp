#include "rs232.h"
#include "ui_rs232.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QSerialPort>


Rs232::Rs232(Global &global,QWidget *parent)
    : QMainWindow(parent)
    , global(global)
    , ui(new Ui::Rs232)
{
    ui->setupUi(this);
  /////////////////////////


   // connect(m_serial, &QSerialPort::readyRead,   //readyRead
   //         this, &Rs232::readDats);

    //connect(m_serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    //   connect(
    //                &pump, &Pump::openServicePump,
    //                this, &MainWindow::openServiceFormPump
    //                );



    // sender, &Sender::valueChanged,
    //     receiver, &Receiver::updateValue;



    ////////////////////////////
    // m_serial(new QSerialPort(this))
    initPort();

}

Rs232::~Rs232()
{
    delete ui;
}

void Rs232::initPort()
{


    QTextStream out(stdout);
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    qDebug() << "\n\n\n";
    out << QObject::tr("Total number of ports available: \n\n\n") << serialPortInfos.count() ;

    const QString blankString = QObject::tr("N/A");
    QString description;
    QString manufacturer;
    QString serialNumber;

    str = "Available com port: \n";
    ui->textEditInfo->append(str);

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
        ui->textEditInfo->append(str);


    }
    qDebug() << "Open port:";
    m_serial = new QSerialPort(this);

    corectPort = nullptr;
    foreach (ComInfo cInfo, comPortMap){

       // "403"  FDI RS232
       // "2341" Arduino MEGA
        if(cInfo.vendorIdentifier == "2341"){
            corectPort = cInfo.port;
        }
    }

    if(corectPort != nullptr){
        m_serial->setPortName(corectPort);
        m_serial->setBaudRate(115200);
        m_serial->setDataBits(QSerialPort::Data8);
        m_serial->setParity(QSerialPort::NoParity);
        m_serial->setStopBits(QSerialPort::OneStop);
        m_serial->setFlowControl(QSerialPort::NoFlowControl);

        str = "Selected port: ";
        str.append(corectPort);
        str.append("\n");
        str.append(comPortMap[corectPort].manufacturer);
        str.append(", ");
        str.append(comPortMap[corectPort].serialNumber);
        str.append("\n");
        ui->textEditInfo->append(str);

        str = corectPort;
        if(m_serial->open(QIODevice::ReadWrite)){
            str.append(" open successful!\n");
        }
        else{
            str.append(" open error!");
        }
        ui->textEditInfo->append(str);

    }
    else{
        str = "Available com port nof fond \n search Vendor Id ";
        str.append("2341");
        ui->textEditInfo->append(str);
    }

}

void Rs232::sendData(QString send)
{
    QByteArray utf8Data = send.toUtf8();
    const qint64 written = m_serial->write(utf8Data);
    Q_UNUSED(written);
}

void Rs232::readDats()
{
 const QByteArray data = m_serial->readAll();
 qDebug()<< "data" << data;
 ui->textEditInfo->append(QString(data));

}



