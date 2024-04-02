#include "modbus485.h"
#include <QSerialPort>
#include <QLoggingCategory>




Modbus485::Modbus485(Global &global, QWidget *parent)
    : QMainWindow(parent)
    , global(global)

{

    // qt.modbus: (RTU client) Received ADU:


    //  QLoggingCategory::setFilterRules("qt.modbus* = true");
    // QLoggingCategory::setFilterRules("qt* = true");
    modbusDevice = new QModbusRtuSerialClient(this);
    // QElapsedTimer timer;
    timerTest = startTimer(1000, Qt::CoarseTimer);
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
    modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,QSerialPort::Baud115200);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,QSerialPort::Data8);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,QSerialPort::OneStop);

    modbusDevice->setTimeout(1000);
    modbusDevice->setNumberOfRetries(3);



    if (!modbusDevice->connectDevice()) {
        qDebug() << global.dev3 <<"Connect failed:" << modbusDevice->errorString();
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

    readData();
    // writeDat();
    // wr23IOD32(7,0x70, 0xff);

}

bool Modbus485::wr23IOD32(int boardAdr, int regAdr, quint16 value)  // 7, 0x70, 0xffff
{

    const auto table = QModbusDataUnit::HoldingRegisters;   // cmd 06
    int startAddress = regAdr;
    Q_ASSERT(startAddress >= 0 && startAddress < 200);

    quint16 numberOfEntries =2;
    //return QModbusDataUnit(table, startAddress, numberOfEntries);



    //! [write_data_0]
    //QModbusDataUnit writeUnit = writeRequest();
    QModbusDataUnit writeUnit = QModbusDataUnit(table, startAddress, numberOfEntries);


    //for (qsizetype i = 0, total = 1 /*writeUnit.valueCount()*/; i < total; ++i) {
    //    const auto addr = i + 0x70; //writeUnit.startAddress();
    //}

    writeUnit.setValue(0, value ); // writeModel->m_coils[addr]);

    qDebug() << "writeUnit1? " << writeUnit.isValid() << writeUnit.registerType() << writeUnit.startAddress() << writeUnit.values();

    writeDat(writeUnit,boardAdr);

}

bool Modbus485::rd23IOD32(int boardAdr, int regAdr)
{

    if (!modbusDevice){
        qDebug() << "readDat RET";
        return false;
    }

    const auto table = QModbusDataUnit::HoldingRegisters;
    int startAddress = regAdr;
    Q_ASSERT(startAddress >= 0 && startAddress < 200);

    quint16 numberOfEntries = 2;
    QModbusDataUnit dataUnit =  QModbusDataUnit(table, startAddress, numberOfEntries);



    //! [read_data_1]
    if (auto *reply = modbusDevice->sendReadRequest(dataUnit, boardAdr)) {
        if (!reply->isFinished()){
            connect(reply, &QModbusReply::finished, this, &Modbus485::onReadReady);
            QModbusDataUnit writeUnit = dataUnit;
            qDebug()<< readRequest().registerType() << readRequest().values() << readRequest().valueCount() <<
                readRequest().startAddress() << readRequest().value(0)<< readRequest().value(1);
        }
        else
            delete reply; // broadcast replies return immediately
        return true;
    } else {
        // statusBar()->showMessage(tr("Read error: %1").arg(modbusDevice->errorString()), 5000);
        qDebug() << "Read error:" << modbusDevice->errorString();
        return false;
    }
}

bool Modbus485::rd24DIB32(int boardAdr, int regAdr)
{

    if (!modbusDevice){
        qDebug() << "readDat RET";
        return false;
    }

    const auto table = QModbusDataUnit::HoldingRegisters;
    int startAddress = regAdr;
    Q_ASSERT(startAddress >= 0 && startAddress < 200);

    quint16 numberOfEntries = 2;
    QModbusDataUnit dataUnit =  QModbusDataUnit(table, startAddress, numberOfEntries);



    //! [read_data_1]
    if (auto *reply = modbusDevice->sendReadRequest(dataUnit, boardAdr)) {
        if (!reply->isFinished()){
            connect(reply, &QModbusReply::finished, this, &Modbus485::onReadReady);
            QModbusDataUnit writeUnit = dataUnit;
            qDebug()<< readRequest().registerType() << readRequest().values() << readRequest().valueCount() <<
                readRequest().startAddress() << readRequest().value(0)<< readRequest().value(1);
        }
        else
            delete reply; // broadcast replies return immediately
        return true;
    } else {
        // statusBar()->showMessage(tr("Read error: %1").arg(modbusDevice->errorString()), 5000);
        qDebug() << "Read error:" << modbusDevice->errorString();
        return false;
    }
}

bool Modbus485::rdN4AIB16(int boardAdr, int regAdr, int len)
{
    // processTimeStart = QTime::msecsSinceStartOfDay();
    timer.start();
    //01,04,00,00,00,10,crc
    if (!modbusDevice){
        qDebug() << "readDat RET";
        return false;
    }

    //const auto table = QModbusDataUnit::HoldingRegisters;   // tr 03
    //const auto table = QModbusDataUnit::Coils;   // tr 01
    // const auto table = QModbusDataUnit::DiscreteInputs; // tr 02

    const auto table = QModbusDataUnit::InputRegisters;  // tr 4
    int startAddress = regAdr;
    Q_ASSERT(startAddress >= 0 && startAddress < 200);

    quint16 numberOfEntries = len;
    QModbusDataUnit dataUnit =  QModbusDataUnit(table, startAddress, numberOfEntries);



    //! [read_data_1]
    if (auto *reply = modbusDevice->sendReadRequest(dataUnit, boardAdr)) {
        if (!reply->isFinished()){
            connect(reply, &QModbusReply::finished, this, &Modbus485::onReadReady);
            QModbusDataUnit writeUnit = dataUnit;
            qDebug()<< readRequest().registerType() << readRequest().values() << readRequest().valueCount() <<
                readRequest().startAddress() << readRequest().value(0)<< readRequest().value(1);
        }
        else
            delete reply; // broadcast replies return immediately
        return true;
    } else {
        // statusBar()->showMessage(tr("Read error: %1").arg(modbusDevice->errorString()), 5000);
        qDebug() << "Read error:" << modbusDevice->errorString();
        return false;
    }
}

bool Modbus485::updateDIOut()
{
    quint16 val1 = 0;
    quint16 val2 = 0;
    for(int i = 15; i >= 0;i--){
        val1 <<= 1;
        val1 += (global.DIoutput[i].Di & 1);
        val2 <<= 1;
        val2 += (global.DIoutput[i+16].Di & 1);
    }
    // qDebug() << "wr23IOD32 = " << (void *)val1 << (void *)val2;
    wr23IOD32(4,0x70,val1);  // wr23IOD32(7,0x70, 0xff);
    wr23IOD32(4,0x71,val2);  // wr23IOD32(7,0x70, 0xff)
}

void Modbus485::timerEvent(QTimerEvent *event)
{
    Q_UNUSED (event);

 /*   int i = 1;    // only for testing level meter
    global.ANinput4_20[i].An += 10;

    if(global.ANinput4_20[i].An > 110)
        global.ANinput4_20[i].An = 0;

    qDebug() << "emit valChangeAn(i)" << i << global.ANinput4_20[i].An; // level meter
    emit valChangeAn(i + MAX_DIinput, global.ANinput4_20[i].An);
    */

}

void Modbus485::errorHandler(QModbusDevice::Error error)
{
    qDebug() << "ERROR !!!" << error;
}

bool Modbus485::setBaudrate(int address)
{
    //reset address 0x01;
    // FF 06 00 FB 00 00 ED E5
    return true;
}

bool Modbus485::factoryReset(int address)
{
    qDebug() << "Rese--------------------------------------" << address ;
    if (!modbusDevice){
        qDebug() << "readDat RET";
        return false;
    }
    /*
    //const auto table = QModbusDataUnit::HoldingRegisters;   // tr 03
    //const auto table = QModbusDataUnit::Coils;   // tr 01
    // const auto table = QModbusDataUnit::DiscreteInputs; // tr 02

    const auto table = QModbusDataUnit::HoldingRegisters;  // tr 4
    int startAddress = 251;

    quint16 numberOfEntries = 0;
    QModbusDataUnit dataUnit =  QModbusDataUnit(table, startAddress, numberOfEntries);
    int boardAdr = 0xff;


    //! [read_data_1]
    if (auto *reply = modbusDevice->sendReadRequest(dataUnit, boardAdr)) {
        if (!reply->isFinished()){
            connect(reply, &QModbusReply::finished, this, &Modbus485::onReadReady);
            QModbusDataUnit writeUnit = dataUnit;
            qDebug()<< readRequest().registerType() << readRequest().values() << readRequest().valueCount() <<
                readRequest().startAddress() << readRequest().value(0)<< readRequest().value(1);
        }
        else
            delete reply; // broadcast replies return immediately
        return true;
    } else {
        // statusBar()->showMessage(tr("Read error: %1").arg(modbusDevice->errorString()), 5000);
        qDebug() << "Read error:" << modbusDevice->errorString();
        return false;
    }
    */
    return true;
}


void Modbus485::onReadReady()
{
    QByteArray replayDataArray;
    int datalen;
    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;

    //dataChangeDi = -1;  //if change 1 input    dataChangeDi = input number
   // dataChangeAn = -1;  //if change more inputs  dataChangeDi = 0xffff

    qDebug() << "onReadReady from addres" << reply->serverAddress();
    if (reply->error() == QModbusDevice::NoError) {
        const QModbusDataUnit unit = reply->result();

        datalen = reply->rawResult().data().length();
        replayDataArray = reply->rawResult().data();
        qDebug() << "datalen , reg Type" << replayDataArray.length() << datalen << unit.registerType();

        switch (reply->serverAddress()) {
        case 2:     // rdN4AIB16
            if(unit.registerType() == 3 && replayDataArray.length() == datalen){
                qDebug() << reply->result().values();

                for(int i = 0; i < (datalen)/2; i++){
                    if(global.ANinput4_20[i].An != reply->result().value(i)){
                        global.ANinput4_20[i].An = reply->result().value(i);
                        qDebug() << "emit valChangeAn(i)" << i << global.ANinput4_20[i].An;
                        emit valChangeAn(i+ MAX_DIinput, global.ANinput4_20[i].An);
                    }
                }
            }


            else{
                qDebug() << "error";
            }

            //qDebug() << "processTime " << timer.elapsed();
            for(int i = 0; i < MAX_ANinput4_20; i++){
                //     qDebug() << i << global.ANinput4_20[i].An/100.0 ;  //     BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
            }

            rd23IOD32(4,0xc0);  // 2
            break;

        case 4:     // rd23IOD32
            if(unit.registerType() == 4 && replayDataArray.length() == datalen){
                qDebug() << reply->result().values();
                //int hex = replayDataArray.toInt(&ok, 16);


                //   reply->result().value(0)    // biti [in1:in16] => [d0:d15]
                //   reply->result().value(1)    // biti [in17:in32] => [d0:d15]

                qDebug() << QString::number(reply->result().value(0), 16);
                qDebug() << QString::number(reply->result().value(1), 16);

                for(int i = 0; i < MAX_DIinput/2; i++){
                    if(global.DIinput[i].Di != (bool)(reply->result().value(0) & (1 << i))){
                        global.DIinput[i].Di = (bool)(reply->result().value(0) & (1 << i));
                        qDebug() << "emit valChangeDi(i)" << i << global.DIinput[i].Di;
                        emit valChangeDi(i,(bool)global.DIinput[i].Di);
                    }
                }
                for(int i = MAX_DIinput/2; i < MAX_DIinput; i++){
                    if(global.DIinput[i].Di != (bool)(reply->result().value(1) & (1 << i))){
                        global.DIinput[i].Di = (bool)(reply->result().value(1) & (1 << i));
                        qDebug() << "emit valChangeDi(i)" << i << global.DIinput[i].Di;
                        emit valChangeDi(i, global.DIinput[i].Di);
                    }
                }







                //for(int i = 0; i < 32 ; i++){
                //    qDebug() << i << global.getDIval(i) ;  //
                //}
            }
            else{
                qDebug() << "error";
            }

            //***     updateDIOut();  // 3
            qDebug() << "processTime " << timer.elapsed();

            break;


        default:
            break;
        }





        //(int)*





        // qDebug() << "reply->serverAddress()is: " << reply->serverAddress();//QModbusDataUnit::
        // qDebug() << "unit.registerType()is: " << unit.registerType();// int
        // qDebug() << "reply->rawResult().data() " << reply->rawResult().data() ;
        // qDebug() << "reply->rawResult().data().length() " << reply->rawResult().data().length() ;
        //qDebug() << "reply->rawResult().data().length() " << reply->rawResult().data();
        // qDebug() << "reply->result().registerType() " << reply->result().registerType() ;
        /*
        for (qsizetype i = 0, total = unit.valueCount(); i < total; ++i) {


            const QString entry = tr("Address: %1, Value: %2").arg(unit.startAddress() + i)
                    .arg(QString::number(unit.value(i),
                                         unit.registerType() <= QModbusDataUnit::Coils ? 10 : 16));
            qDebug() << "entry" <<unit.value(i) << entry;

        }

*/

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

    //dataChangeDi >= 0 ;  emit signal !!!!!!!!!!!!!!!!!!!!
    //dataChangeAn >= 0
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
    //  //DiscreteInputs,Coils,InputRegisters, HoldingRegisters,
    const auto table = QModbusDataUnit::HoldingRegisters;  // coils->0f   HoldingRegisters -> 10 InputRegisters -> invalid request
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

void Modbus485::writeDat(QModbusDataUnit writeUnit, int boardAdr)
{
    if (!modbusDevice){
        qDebug() << "writeDat RET";
        return ;

    }
    /*
    //! [write_data_0]
    QModbusDataUnit writeUnit = writeRequest();

    qDebug() << "writeUnit? " << writeUnit.isValid() << writeUnit.registerType() << writeUnit.startAddress() << writeUnit.values();

    QModbusDataUnit::RegisterType table = QModbusDataUnit::HoldingRegisters;
    for (qsizetype i = 0, total = 1 ; i < total; ++i) {
        const auto addr = i + 0x70; //writeUnit.startAddress();
            writeUnit.setValue(i, 0x0f ); // writeModel->m_coils[addr]);
    }


    qDebug() << "writeUnit1? " << writeUnit.isValid() << writeUnit.registerType() << writeUnit.startAddress() << writeUnit.values();



*/
    qDebug() << "writeUnit2? " << writeUnit.isValid() << writeUnit.registerType() << writeUnit.startAddress() << writeUnit.values();


    if (auto *reply = modbusDevice->sendWriteRequest(writeUnit, boardAdr)) {
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

void Modbus485::writeDat()
{
    if (!modbusDevice){
        qDebug() << "writeDat RET";
        return ;

    }

    //! [write_data_0]
    QModbusDataUnit writeUnit = writeRequest();

    qDebug() << "writeUnit? " << writeUnit.isValid() << writeUnit.registerType() << writeUnit.startAddress() << writeUnit.values();

    QModbusDataUnit::RegisterType table = QModbusDataUnit::HoldingRegisters;
    for (qsizetype i = 0, total = 1 ; i < total; ++i) {
        const auto addr = i + 0x70; //writeUnit.startAddress();
        writeUnit.setValue(i, 0xcc ); // writeModel->m_coils[addr]);
    }


    qDebug() << "writeUnit1? " << writeUnit.isValid() << writeUnit.registerType() << writeUnit.startAddress() << writeUnit.values();




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

