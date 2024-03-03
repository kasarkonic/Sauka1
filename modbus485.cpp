#include "modbus485.h"
#include <QSerialPort>
#include <QLoggingCategory>



Modbus485::Modbus485(Global &global, QWidget *parent)
    : QMainWindow(parent)
    , global(global)

{

// qt.modbus: (RTU client) Received ADU:


    QLoggingCategory::setFilterRules("qt.modbus* = true");
    modbusDevice = new QModbusRtuSerialClient(this);

}

bool Modbus485::init()
{
    //QModbusRtuSerialClient* modbusDevice();
    //ScalesMass *scalesMass = new ScalesMass(global,widData.name,this);
    //QModbusRtuSerialClient *modbusDevice = new QModbusRtuSerialClient(this);
    //modbusDevice = new QModbusRtuSerialClient(this);

    connect(modbusDevice, &QModbusClient::errorOccurred,this, &Modbus485::errorHandler);

    modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,global.dev3);

    modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,QSerialPort::NoParity);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,QSerialPort::Baud9600);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,QSerialPort::Data8);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,QSerialPort::OneStop);

    modbusDevice->setTimeout(1000);
    modbusDevice->setNumberOfRetries(3);



    if (!modbusDevice->connectDevice()) {
        qDebug() << "Connect failed:" << modbusDevice->errorString();
        return false;
        //statusBar()->showMessage(tr("Connect failed: %1").arg(modbusDevice->errorString()), 5000);
    } else {
        qDebug() << "modbusDevice connect OK";

        return true;
    }

}

void Modbus485::test(int address, int value)
{

    //onReadReady();

     //readData();
    writeDat();

}

void Modbus485::errorHandler(QModbusDevice::Error error)
{
    qDebug() << "ERROR !!!" << error;
}

void Modbus485::onReadReady()
{
    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError) {
        const QModbusDataUnit unit = reply->result();
        for (qsizetype i = 0, total = unit.valueCount(); i < total; ++i) {
            const QString entry = tr("Address: %1, Value: %2").arg(unit.startAddress() + i)
                    .arg(QString::number(unit.value(i),
                                         unit.registerType() <= QModbusDataUnit::Coils ? 10 : 16));
            qDebug() << "entry" << entry;

        }
    } else if (reply->error() == QModbusDevice::ProtocolError) {
        //statusBar()->showMessage(tr("Read response error: %1 (Modbus exception: 0x%2)").
        //                             arg(reply->errorString()).
        //                              arg(reply->rawResult().exceptionCode(), -1, 16), 5000);
        qDebug() << "Read response error: Modbus exception:)" << reply->errorString() << reply->rawResult().exceptionCode();


    } else {
        //statusBar()->showMessage(tr("Read response error: %1 (code: 0x%2)").
        //                            arg(reply->errorString()).
        //                            arg(reply->error(), -1, 16), 5000);

        qDebug() << "Read response error: %1 (code: 0x%2)" << reply->errorString() << reply->error();
    }

    reply->deleteLater();
}



//      read data  addres 7 reg addres 0xc0 and 0xc1  QModbusDataUnit::HoldingRegisters
QModbusDataUnit Modbus485::readRequest() const
{
    // const auto table = ui->writeTable->currentData().value<QModbusDataUnit::RegisterType>();
    //QModbusDataUnit(RegisterType type, int newStartAddress, quint16 newValueCount)
    // QModbusDataUnit::Coils
    //QModbusDataUnit *table = new QModbusDataUnit(QModbusDataUnit::Coils,0x70,7);

    const auto table = QModbusDataUnit::HoldingRegisters;

    int startAddress = 0xc0;
    Q_ASSERT(startAddress >= 0 && startAddress < 200);

    // do not go beyond 10 entries
    quint16 numberOfEntries =2;
    return QModbusDataUnit(table, startAddress, numberOfEntries);

}

QModbusDataUnit Modbus485::writeRequest() const
{
    //const auto table = ui->writeTable->currentData().value<QModbusDataUnit::RegisterType>();
    const auto table = QModbusDataUnit::HoldingRegisters;
    int startAddress = 0x70;
    Q_ASSERT(startAddress >= 0 && startAddress < 200);

    // do not go beyond 10 entries
    quint16 numberOfEntries = 3;
    return QModbusDataUnit(table, startAddress, numberOfEntries);
}



void Modbus485::readData()
{
    if (!modbusDevice){
        qDebug() << "readDat RET";
        return;
    }

    //! [read_data_1]
    if (auto *reply = modbusDevice->sendReadRequest(readRequest(), 7)) {
        if (!reply->isFinished()){
            connect(reply, &QModbusReply::finished, this, &Modbus485::onReadReady);
            //QModbusDataUnit writeUnit = readRequest();
           // qDebug()<< readRequest().values() << readRequest().valueCount() <<
                      // readRequest().startAddress() << readRequest().value(0)<< readRequest().value(1);
        }
        else
            delete reply; // broadcast replies return immediately
    } else {
        // statusBar()->showMessage(tr("Read error: %1").arg(modbusDevice->errorString()), 5000);
        qDebug() << "Read error:" << modbusDevice->errorString();
    }
}

void Modbus485::writeDat()
{
    if (!modbusDevice){
        qDebug() << "writeDat RET";
        return;
    }

    //! [write_data_0]
    QModbusDataUnit writeUnit = writeRequest();
    QModbusDataUnit::RegisterType table = QModbusDataUnit::HoldingRegisters;
    for (qsizetype i = 112; i <= 113; ++i) {

            int value = 1;
            writeUnit.setValue(i, value);
    }


    qDebug()<< writeUnit.values();


    if (auto *reply = modbusDevice->sendWriteRequest(writeUnit, 7)) {
        if (!reply->isFinished()) {
            //if error
            connect(reply, &QModbusReply::finished, this, [this, reply]() {
                const auto error = reply->error();

                if (error == QModbusDevice::ProtocolError) {
                    //  statusBar()->showMessage(tr("Write response error: %1 (Modbus exception: 0x%2)")
                    //      .arg(reply->errorString()).arg(reply->rawResult().exceptionCode(), -1, 16),
                    //       5000);


                } else if (error != QModbusDevice::NoError) {
                    // statusBar()->showMessage(tr("Write response error: %1 (code: 0x%2)").
                    //   arg(reply->errorString()).arg(error, -1, 16), 5000);
                    qDebug() << "Write response error:  (code:)"<< reply->errorString()<<reply->rawResult().exceptionCode();

                }
                reply->deleteLater();
            });


        } else {
            // broadcast replies return immediately
            reply->deleteLater();
        }
    } else {
        //statusBar()->showMessage(tr("Write error: %1").arg(modbusDevice->errorString()), 5000);
        qDebug() << "Write error:" << modbusDevice->errorString();
    }
}
