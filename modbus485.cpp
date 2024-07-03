#include "modbus485.h"
#include <QSerialPort>
#include <QLoggingCategory>





Modbus485::Modbus485(Global& global, QWidget* parent)
//: QMainWindow(parent)
    : QThread(parent)
    , global(global)

{

    // qt.modbus: (RTU client) Received ADU:


    //  QLoggingCategory::setFilterRules("qt.modbus* = true");
    // QLoggingCategory::setFilterRul
    modbusDevice = new QModbusRtuSerialClient(this);
    // QElapsedTimer timer;
    // timerReadIn = new QTimer(this);
    // timerWriteOut = new QTimer(this);
    // connect(timerReadIn, SIGNAL(timeout()),
    //         this, SLOT(timerReadSlot()));
    //connect(timerWriteOut, SIGNAL(timeout()),
    //         this, SLOT(timerWriteSlot()));
    // timerReadIn->start(3000);
    //   timerWriteOut->start(250);

    intervalTimer = new QElapsedTimer();
    intervalTimer->start();

    task_state = State_rd23IOD32_0;
    taskTimer = new QTimer(this);
    taskTimer->start(10);//---------------------------------------------------------------------------------------------
    connect(taskTimer, SIGNAL(timeout()),
            this, SLOT(runTaskCycle()));

    changeState(State_rd23IOD32_0);
    qDebug() << "Modbus485 set name ";
    name = "Modbus485";
    RS485Ready = true;

}
/*
void Modbus485::run()
{
    qDebug() << "Modbus485 Run ";
    timerReadIn->start(500);
    timerWriteOut->start(250);
}
*/


bool Modbus485::init() {
    qDebug() << "init() Modbus485" << global.dev3;
    //QModbusRtuSerialClient* modbusDevice();

    connect(modbusDevice, &QModbusClient::errorOccurred, this, &Modbus485::errorHandler);

    modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter, global.dev3);

    modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::EvenParity); //NoParity
    modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud38400); //Baud115200
    modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);

    modbusDevice->setTimeout(500);
    modbusDevice->setNumberOfRetries(3);
    RS485Ready = true;


    if (!modbusDevice->connectDevice()) {
        qDebug() << global.dev3 << "Connect failed:" << modbusDevice->errorString();
        global.dev3ConnectStatus = false;
        return false;
        //statusBar()->showMessage(tr("Connect failed: %1").arg(modbusDevice->errorString()), 5000);
    } else {
        qDebug() << "modbusDevice connect OK";
        global.dev3ConnectStatus = true;

        return true;
    }
}

void Modbus485::test(int address, int value) {
    Q_UNUSED(address);
    Q_UNUSED(value);
    //onReadReady();

    //readData();
    // writeDat();
    // wr23IOD32(7,0x70, 0xff);

}

bool Modbus485::wr23IOD32(int boardAdr, int regAdr, quint16 value)  // 7, 0x70, 0xffff
{
    qDebug() << "Modbus485::wr23IOD32 " << boardAdr << regAdr << Qt::hex << value << Qt::dec <<global.getTick();
    const auto table = QModbusDataUnit::HoldingRegisters;   // cmd 06
    int startAddress = regAdr;
    Q_ASSERT(startAddress >= 0 && startAddress < 200);

    quint16 numberOfEntries = 2;
    //return QModbusDataUnit(table, startAddress, numberOfEntries);



    //! [write_data_0]
    //QModbusDataUnit writeUnit = writeRequest();
    QModbusDataUnit writeUnit = QModbusDataUnit(table, startAddress, numberOfEntries);


    //for (qsizetype i = 0, total = 1 /*writeUnit.valueCount()*/; i < total; ++i) {
    //    const auto addr = i + 0x70; //writeUnit.startAddress();
    //}

    writeUnit.setValue(0, value); // writeModel->m_coils[addr]);

    // qDebug() << "writeUnit1? " << writeUnit.isValid() << writeUnit.registerType() << writeUnit.startAddress() << writeUnit.values();

    writeDat(writeUnit, boardAdr);
    return true;
}

bool Modbus485::rd23IOD32(int boardAdr, int regAdr) {

    //qDebug() << "rd23IOD32" <<boardAdr << global.getTick();

    if (!modbusDevice) {
        qDebug() << "readDat RET";
        return false;
    }

    const auto table = QModbusDataUnit::HoldingRegisters;
    int startAddress = regAdr;
    Q_ASSERT(startAddress >= 0 && startAddress < 200);

    quint16 numberOfEntries = 2;
    QModbusDataUnit dataUnit = QModbusDataUnit(table, startAddress, numberOfEntries);



    //! [read_data_1]
    if (auto* reply = modbusDevice->sendReadRequest(dataUnit, boardAdr)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, &Modbus485::onReadReady);
            QModbusDataUnit writeUnit = dataUnit;
            //qDebug()<<"rd23IOD32"<< readRequest().registerType() << readRequest().values() << readRequest().valueCount() <<
            //   readRequest().startAddress() << readRequest().value(0)<< readRequest().value(1);
        } else
            delete reply; // broadcast replies return immediately
        // qDebug() << "T=" << global.getTick() - starttemp << " OK res: " ;  // ok digital input

        return true;
    } else {
        // statusBar()->showMessage(tr("Read error: %1").arg(modbusDevice->errorString()), 5000);
        qDebug() << "Read error:" << modbusDevice->errorString();
        //qDebug()  << "T=" << global.getTick() - starttemp ;
        return false;
    }
}

bool Modbus485::rd24DIB32(int boardAdr, int regAdr) {
    //qDebug() << "rd24DIB32" <<boardAdr << global.getTick();
    if (!modbusDevice) {
        qDebug() << "readDat RET";
        return false;
    }

    const auto table = QModbusDataUnit::HoldingRegisters;
    int startAddress = regAdr;
    Q_ASSERT(startAddress >= 0 && startAddress < 200);

    quint16 numberOfEntries = 2;
    QModbusDataUnit dataUnit = QModbusDataUnit(table, startAddress, numberOfEntries);


    //! [read_data_1]
    if (auto* reply = modbusDevice->sendReadRequest(dataUnit, boardAdr)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, &Modbus485::onReadReady);
            QModbusDataUnit writeUnit = dataUnit;
            qDebug() << readRequest().registerType() << readRequest().values() << readRequest().valueCount() <<
                        readRequest().startAddress() << readRequest().value(0) << readRequest().value(1);
        } else
            delete reply; // broadcast replies return immediately


        return true;
    } else {
        // statusBar()->showMessage(tr("Read error: %1").arg(modbusDevice->errorString()), 5000);
        qDebug() << "Read error:" << modbusDevice->errorString();
        return false;
    }
}

bool Modbus485::rdN4AIB16(int boardAdr, int regAdr, int len) {
    //  qDebug() << "rdN4AIB16" <<boardAdr << global.getTick();

    // processTimeStart = QTime::msecsSinceStartOfDay();
    // timer.start();
    //01,04,00,00,00,10,crc
    if (!modbusDevice) {
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
    QModbusDataUnit dataUnit = QModbusDataUnit(table, startAddress, numberOfEntries);



    //! [read_data_1]
    if (auto* reply = modbusDevice->sendReadRequest(dataUnit, boardAdr)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, &Modbus485::onReadReady);
            QModbusDataUnit writeUnit = dataUnit;
            qDebug() << readRequest().registerType() << readRequest().values() << readRequest().valueCount() <<
                        readRequest().startAddress() << readRequest().value(0) << readRequest().value(1);
        } else
            delete reply; // broadcast replies return immediately
        return true;
    } else {
        // statusBar()->showMessage(tr("Read error: %1").arg(modbusDevice->errorString()), 5000);
        qDebug() << "Read error:" << modbusDevice->errorString();
        return false;
    }
}

bool Modbus485::updateDIOut(int i) {
    //qDebug() << "updateDIOut----------------------" << global.getTick();
    int res = 0;
    quint16 val1, val2, val3, val4;
    bool val1ch, val2ch, val3ch, val4ch;
    val1 = val2 = val3 = val4 = 0;
    val1ch = val2ch = val3ch = val4ch = false;
    //printDIoutput();

    if (0 >= i && i < 16) {
        for (int k = 15; k >= 0;k--) {
            val1 <<= 1;
            val1 += (global.DIoutput[k].value > 0);
            val1ch |= global.DIoutput[k].update;
            global.DIoutput[k].update = false;
        }
        // if (val1ch) {
        res = wr23IOD32(4, 0x70, val1);  // wr23IOD32(7,0x70, 0xff)
        // }
        // else{
        //     RS485Ready = true;
        // }
    }

    if (16 >= i && i < 32) {
        for (int k = 31; k >= 16;k--) {
            val2 <<= 1;
            val2 += (global.DIoutput[k].value > 0);
            val2ch |= global.DIoutput[k].update;
            global.DIoutput[k].update = false;
        }
        // if (val2ch) {
        res += wr23IOD32(4, 0x71, val2);  // wr23IOD32(7,0x70, 0xff)
        // }
        // else{
        //     RS485Ready = true;
        // }
    }

    if (32 >= i && i < 48) {
        for (int k = 47; k >= 32;k--) {
            val3 <<= 1;
            val3 += (global.DIoutput[k].value > 0);
            val3ch |= global.DIoutput[k].update;
            global.DIoutput[k].update = false;
        }
        if (val3ch) {
            // res += wr23IOD32(5, 0x70, val3);  // wr23IOD32(7,0x70, 0xff) ----------------------------------------------------------------------
            RS485Ready = true;
        }
        else{
            RS485Ready = true;
        }
    }

    if (48 >= i && i < 64) {
        for (int k = 63; k >= 48;k--) {
            val4 <<= 1;
            val4 += (global.DIoutput[k].value > 0);
            val4ch |= global.DIoutput[k].update;
            global.DIoutput[k].update = false;
        }
        if (val4ch) {
            // res += wr23IOD32(5, 0x71, val4);  // wr23IOD32(7,0x70, 0xff) ----------------------------------------------------------------------
            RS485Ready = true;
        }
        else{
            RS485Ready = true;
        }
    }

    // qDebug() << "wr23IOD32 = " << (void *)val1 << (void *)val2 << (void *)val3 << (void *)val4;
    // qDebug() << "wr23IOD32 = " << i << global.DIoutput[i].value << "HEX ->"
    //<< Qt::hex<<val1 << val2 << val3 << val4
    //<<val1ch << val2ch << val3ch << val4ch << global.getTick();

    return (res == 4);
}



void Modbus485::timerEvent(QTimerEvent* event) {
    Q_UNUSED(event)
    //if(event->timerId() == taskTimer){
    //     runTaskCycle();
    // }
}
/*
void Modbus485::timerReadSlot() {
    if (!global.disableRS485 && global.dev3ConnectStatus) {
        qDebug() << "Read An Di Inputs";
        //analog input, next DI input, next update DI output
        rdN4AIB16(2, 0, 16);   // ok analog input!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        rd23IOD32(4, 0xc0);  // ok digital input
        rd23IOD32(5, 0xc0);  // ok digital input
        //updateDIOut();

    }
}
*/
void Modbus485::timerWriteSlot() {
    qDebug() << "Change  Outputs" << global.disableRS485 << global.updateDataOut.need;
    // if(!global.disableRS485){
    // if(global.updateDataOut.need){
    //    global.updateDataOut.need = false;
    //updateDIOut();
    // }

    // }
}

void Modbus485::diOutputChangeSl(int i, int value) {
    //qDebug() << "Modbus485::diOutputChangeSl !!!!!!!!!!!!!!!!" << i << value << global.getTick();
    if (i < 16) {
        global.setwaitTx(0x1);
    }
    if (i > 15 && i < 32) {
        global.setwaitTx(0x2);
    }
    if (i > 31 && i < 48) {
        global.setwaitTx(0x4);
    }
    if (i > 47 && i < 54) {
        global.setwaitTx(0x8);
    }

    //updateDIOut(i);   //

}

void Modbus485::errorHandler(QModbusDevice::Error error) {
    qDebug() << "ERROR !!!" << error;
}

bool Modbus485::setBaudrate(int address) {
    Q_UNUSED(address);
    //reset address 0x01;
    // FF 06 00 FB 00 00 ED E5
    return true;
}

bool Modbus485::factoryReset(int address) {
    qDebug() << "Rese--------------------------------------" << address;
    if (!modbusDevice) {
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


void Modbus485::onReadReady() {

    QByteArray replayDataArray;
    int datalen;
    auto reply = qobject_cast<QModbusReply*>(sender());

    if (!reply)
        return;


    //dataChangeDi = -1;  //if change 1 input    dataChangeDi = input number
    // dataChangeAn = -1;  //if change more inputs  dataChangeDi = 0xffff

    qDebug() << "onReadReady from addres" << reply->serverAddress() << global.getTick();
    if (reply->error() == QModbusDevice::NoError) {
        const QModbusDataUnit unit = reply->result();

        datalen = reply->rawResult().data().length();
        replayDataArray = reply->rawResult().data();
        //qDebug() << "datalen , reg Type,address" << reply->serverAddress() << replayDataArray.length() << datalen << unit.registerType();

        switch (reply->serverAddress()) {
        case 2:     // rdN4AIB16
            if (unit.registerType() == 3 && replayDataArray.length() == datalen) {
                // qDebug() << "rdN4AIB16" << reply->serverAddress() << datalen  << reply->result().values();
                for (int i = 0; i <= 15; i++) {    // in0 - in14 0-20mA input  in15 30v input
                    if (global.ANinput4_20[i].value != reply->result().value(i)) {
                        //  qDebug() << "emit valChangeAn(i)"<< i  << global.ANinput4_20[i].value << reply->result().value(i);
                        global.ANinput4_20[i].value = reply->result().value(i);
                        global.ANinput4_20[i].update = true;
                        emit valChangeAn(i, global.ANinput4_20[i].value);// for testing
                    }
                }
            }

            else {
                qDebug() << "error";
            }

            //qDebug() << "imodbus Free " <<reply->serverAddress() <<"t:" <<global.getTick() - starttemp;
            break;



        case 4:     // rd23IOD32 read data address 4
            if (unit.registerType() == 4 && replayDataArray.length() == datalen) {
                //qDebug() << "Din rd23IOD32 address:" << reply->serverAddress()
                //        << QString::number(reply->result().value(0), 16)
                //        << QString::number(reply->result().value(1), 16);


                for (int i = 0; i < 16; i++) {
                    if ((bool)global.DIinput[i].value != (bool)(reply->result().value(0) & (1 << i))) {
                        global.DIinput[i].value = (bool)(reply->result().value(0) & (1 << i));
                        global.DIinput[i].update = true;
                        qDebug() << "emit valChangeDi(" << i << ")" << global.DIinput[i].value;
                        emit valChangeDi(i, (bool)global.DIinput[i].value);
                    }
                }
                for (int i = 0; i < 16; i++) {
                    if ((bool)global.DIinput[i + 16].value != (bool)(reply->result().value(1) & (1 << i))) {
                        global.DIinput[i + 16].value = (bool)(reply->result().value(1) & (1 << i));
                        global.DIinput[i + 16].update = true;
                        qDebug() << "emit valChangeDi(" << i << ")" << global.DIinput[i + 16].value;
                        emit valChangeDi(i + 16, (bool)global.DIinput[i + 16].value);
                    }
                }
                // printDIinput();

            } else {
                qDebug() << "error";
            }

            //qDebug() << "imodbus Free " <<reply->serverAddress() <<"t:" <<global.getTick() - starttemp;
            break;


        case 5:     // rd23IOD32 read data address5
            if (unit.registerType() == 4 && replayDataArray.length() == datalen) {
                //qDebug() << "Din rd23IOD32 address:" << reply->serverAddress()
                //        << QString::number(reply->result().value(0), 16)
                //        << QString::number(reply->result().value(1), 16);

                for (int i = 0; i < 16; i++) {
                    if ((bool)global.DIinput[i + 32].value != (bool)(reply->result().value(0) & (1 << i))) {
                        global.DIinput[i + 32].value = (bool)(reply->result().value(0) & (1 << i));
                        global.DIinput[i + 32].update = true;
                        qDebug() << "emit valChangeDi(" << i + 32 << ")" << global.DIinput[i + 32].value;
                        emit valChangeDi(i + 32, (bool)global.DIinput[i + 32].value);
                    }
                }
                for (int i = 0; i < 16; i++) {
                    if ((bool)global.DIinput[i + 32 + 16].value != (bool)(reply->result().value(1) & (1 << i))) {
                        global.DIinput[i + 32 + 16].value = (bool)(reply->result().value(1) & (1 << i));
                        global.DIinput[i + 32 + 16].update = true;
                        qDebug() << "emit valChangeDi(" << i + 32 + 16 << ")" << global.DIinput[i + 32 + 16].value;
                        emit valChangeDi(i + 32 + 16, (bool)global.DIinput[i + 32 + 16].value);
                    }
                }


                //  printDIinput();
            } else {
                qDebug() << "error";
            }

            //qDebug() << "imodbus Free " <<reply->serverAddress() <<"t:" <<global.getTick() - starttemp;
            break;

        case 8:     // 24DIB32  DIinput[64-95]
            if (unit.registerType() == 4 && replayDataArray.length() == datalen) {
                //qDebug() << "Din 24DIB32 address:" << reply->serverAddress()
                //        << QString::number(reply->result().value(0), 16)
                //        << QString::number(reply->result().value(1), 16);

                for (int i = 0; i < 16; i++) {
                    if ((bool)global.DIinput[i + 64].value != (bool)(reply->result().value(0) & (1 << i))) {
                        global.DIinput[i + 64].value = (bool)(reply->result().value(0) & (1 << i));
                        global.DIinput[i + 64].update = true;
                        qDebug() << "emit valChangeDi(" << i + 64 << ")" << global.DIinput[i + 64].value;
                        emit valChangeDi(i + 64, (bool)global.DIinput[i + 64].value);
                    }
                }
                for (int i = 0; i < 16; i++) {
                    if ((bool)global.DIinput[i + 64 + 16].value != (bool)(reply->result().value(1) & (1 << i))) {
                        global.DIinput[i + 64 + 16].value = (bool)(reply->result().value(1) & (1 << i));
                        global.DIinput[i + 64 + 16].update = true;
                        qDebug() << "emit valChangeDi(" << i + 64 + 16 << ")" << global.DIinput[i + 64 + 16].value;
                        emit valChangeDi(i + 64 + 16, (bool)global.DIinput[i + 64 + 16].value);
                    }
                }
                // printDIinput();
            }

            break;

        default:
            qDebug() << "Receive Msg from uncnown Modbus addres !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
            break;

            //qDebug() << "imodbus Free " <<reply->serverAddress() <<"t:" <<global.getTick() - starttemp;


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

    //dataChangeDi >= 0 ;  emit signal !!!!!!!!!!!!!!!!!!!!
    //dataChangeAn >= 0
    RS485Ready = true;
}



//      read data  addres 7 reg addres 0xc0 and 0xc1  QModbusDataUnit::HoldingRegisters
QModbusDataUnit Modbus485::readRequest() const {
    // const auto table = ui->writeTable->currentData().value<QModbusDataUnit::RegisterType>();
    //QModbusDataUnit(RegisterType type, int newStartAddress, quint16 newValueCount)
    // QModbusDataUnit::Coils
    //QModbusDataUnit *table = new QModbusDataUnit(QModbusDataUnit::Coils,0x70,7);

    const auto table = QModbusDataUnit::HoldingRegisters;

    int startAddress = 0xc0;
    Q_ASSERT(startAddress >= 0 && startAddress < 200);

    // do not go beyond 10 entries
    quint16 numberOfEntries = 2;
    return QModbusDataUnit(table, startAddress, numberOfEntries);

}

QModbusDataUnit Modbus485::writeRequest() const {
    //const auto table = ui->writeTable->currentData().value<QModbusDataUnit::RegisterType>();
    //  //DiscreteInputs,Coils,InputRegisters, HoldingRegisters,
    const auto table = QModbusDataUnit::HoldingRegisters;  // coils->0f   HoldingRegisters -> 10 InputRegisters -> invalid request
    int startAddress = 0x70;
    Q_ASSERT(startAddress >= 0 && startAddress < 200);

    // do not go beyond 10 entries
    quint16 numberOfEntries = 3;
    return QModbusDataUnit(table, startAddress, numberOfEntries);
}



void Modbus485::readData() {
    if (!modbusDevice) {
        qDebug() << "readDat RET";
        return;
    }

    //! [read_data_1]
    if (auto* reply = modbusDevice->sendReadRequest(readRequest(), 7)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, &Modbus485::onReadReady);
            //QModbusDataUnit writeUnit = readRequest();
            // qDebug()<< readRequest().values() << readRequest().valueCount() <<
            // readRequest().startAddress() << readRequest().value(0)<< readRequest().value(1);
        } else
            delete reply; // broadcast replies return immediately
    } else {
        // statusBar()->showMessage(tr("Read error: %1").arg(modbusDevice->errorString()), 5000);
        qDebug() << "Read error:" << modbusDevice->errorString();
    }
}

void Modbus485::writeDat(QModbusDataUnit writeUnit, int boardAdr) {
    if (!modbusDevice) {
        qDebug() << "writeDat RET";
        return;
    }
    if (!global.dev3ConnectStatus) {
        qDebug() << "ConnectStatus error";
        return;
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
    // qDebug() << "writeUnit2? " << writeUnit.isValid() << writeUnit.registerType() << writeUnit.startAddress() << writeUnit.values();


    if (auto* reply = modbusDevice->sendWriteRequest(writeUnit, boardAdr)) {
        if (!reply->isFinished()) {
            //if error
            //qDebug() << "error boards address:" << boardAdr ;
            connect(reply, &QModbusReply::finished, this, [this, reply]() {
                const auto error = reply->error();
                //qDebug() << "error:" << error ;
                if (error == QModbusDevice::ProtocolError) {
                    //  statusBar()->showMessage(tr("Write response error: %1 (Modbus exception: 0x%2)")
                    //      .arg(reply->errorString()).arg(reply->rawResult().exceptionCode(), -1, 16),
                    //       5000);
                    qDebug() << "Write response error::  (code:)" << reply->errorString() << reply->rawResult().exceptionCode();

                } else if (error != QModbusDevice::NoError) {
                    // statusBar()->showMessage(tr("Write response error: %1 (code: 0x%2)").
                    //   arg(reply->errorString()).arg(error, -1, 16), 5000);
                    qDebug() << "Write response error:  (code:)" << reply->errorString() << reply->rawResult().exceptionCode();

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
/*
void Modbus485::writeDat() {
    if (!modbusDevice) {
        qDebug() << "writeDat RET";
        return;
    }
    if (!global.dev3ConnectStatus) {
        qDebug() << "ConnectStatus error";
        return;
    }
    qDebug() << "global.dev3ConnectStatus" << global.dev3ConnectStatus;

    //! [write_data_0]
    QModbusDataUnit writeUnit = writeRequest();

    qDebug() << "writeUnit? " << writeUnit.isValid() << writeUnit.registerType() << writeUnit.startAddress() << writeUnit.values();

    // QModbusDataUnit::RegisterType table = QModbusDataUnit::HoldingRegisters;
    for (qsizetype i = 0, total = 1; i < total; ++i) {
        // const auto addr = i + 0x70; //writeUnit.startAddress();
        writeUnit.setValue(i, 0xcc); // writeModel->m_coils[addr]);
    }


    qDebug() << "writeUnit2? " << writeUnit.isValid() << writeUnit.registerType() << writeUnit.startAddress() << writeUnit.values();




    if (auto* reply = modbusDevice->sendWriteRequest(writeUnit, 7)) {
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
                    qDebug() << "Write response error:  (code:)" << reply->errorString() << reply->rawResult().exceptionCode();

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
*/

void Modbus485::printDIinput1(int start, int finish) {
    QDebug debug = qDebug();

    for (int i = start; i <= finish; i++) {
        debug << global.DIinput[i].value;
    }
}

void Modbus485::printDIoutput1(int start, int finish) {
    QDebug debug = qDebug();

    for (int i = start; i <= finish; i++) {
        debug << global.DIoutput[i].value;
    }
    for (int i = start; i <= finish; i++) {
        debug << global.DIoutput[i].update;
    }
}

void Modbus485::runTaskCycle() {
    int interval = 100;  // 25 arI strādā
    //qDebug() << "runTaskCycle()" << task_state << global.getTick();
    switch (task_state) {
    case State_rd23IOD32_0:
        // qDebug() << "32_0RS485Ready" << RS485Ready << global.getTick();
        if (isTimerTimeout() ) {

            if(global.dev3ConnectStatus){

                if(!RS485Ready){qDebug() << "RS485Ready:" << RS485Ready << task_state;}

                qDebug() << "starttemp"  << global.getTick() - starttemp << global.dev3ConnectStatus;
                starttemp = global.getTick();
                RS485Ready = false;
                qDebug() << "rrd23IOD32(4, 0xc0" << RS485Ready << global.getTick();
                rd23IOD32(4, 0xc0);  // ok digital input
                // RS485Ready = false;
                // if (global.getwaitTx()) {
                //    changeState(State_wd23IOD32_1, interval);
                // } else {
                changeState(State_rd23IOD32_1, interval);
                // }
            }
        }
        break;
    case State_rd23IOD32_1:
        qDebug() << "rd 5 RS485Ready" << RS485Ready << global.getTick();
        if ( isTimerTimeout()) {
            if(!RS485Ready){qDebug() << "RS485Ready:" << RS485Ready << task_state;}

            qDebug() << "rd 5a RS485Ready" << RS485Ready << global.getTick();
             RS485Ready = false;
            // rd23IOD32(5,0xc0);  // ok digital input  no board? !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            //if (global.getwaitTx()) {
            //   changeState(State_wd23IOD32_1, interval);
            //} else {
            changeState(State_rd24DIB32, interval);
            //}
        }
        break;
    case State_rd24DIB32:
        qDebug() << "rd24DIB32(8, 0xc0);" << RS485Ready << global.getTick();
        if (isTimerTimeout()) {
             if(!RS485Ready){qDebug() << "RS485Ready:" << RS485Ready << task_state;}
            RS485Ready = false;
            rd24DIB32(8, 0xc0);
            if (global.getwaitTx()) {
                changeState(State_wd23IOD32_1, interval);
            } else {
                changeState(State_rdN4AIB16, interval);
           }
        }
        break;
    case State_rdN4AIB16:
        if (isTimerTimeout() || RS485Ready) {
            RS485Ready = false;
            rdN4AIB16(2, 0, 16);

            changeState(State_wd23IOD32_1, interval);
            /*
            if (global.getwaitTx()) {
                changeState(State_wd23IOD32_1, interval);
            } else {
                global.setwaitTx(0x0f);
                changeState(State_wd23IOD32_1, interval);
            }
            */
        }
        break;
    case State_wd23IOD32_1:
        global.setwaitTx(0x0f);  // for testing
        if (!(global.getwaitTx() & 0x01)) {
            changeState(State_wd23IOD32_2, 1);
        }
        qDebug() << "8 RS485Ready" << RS485Ready << global.getTick();
        if (isTimerTimeout()) {
            RS485Ready = false;
            updateDIOut(0);
            int tx = global.getwaitTx() & ~0x1;  // remove d0
            global.setwaitTx(tx);
            changeState(State_wd23IOD32_2, interval);
        }


        break;
    case State_wd23IOD32_2:
        qDebug() << "16 RS485Ready" << RS485Ready << global.getTick();
        if (!(global.getwaitTx() & 0x02)) {
            changeState(State_wd23IOD32_4, interval);
        }

        if (isTimerTimeout()) {
            RS485Ready = false;
            updateDIOut(16);
            int tx = global.getwaitTx() & ~0x2;  // remove d0
            global.setwaitTx(tx);
            changeState(State_wd23IOD32_4, interval);
        }
        break;

    case State_wd23IOD32_4:
        if (!(global.getwaitTx() & 0x04)) {
            changeState(State_wd23IOD32_8, interval);
        }
        qDebug() << "32 RS485Ready" << RS485Ready << global.getTick();
        if (isTimerTimeout()) {
            RS485Ready = false;
            updateDIOut(32);
            int tx = global.getwaitTx() & ~0x4;  // remove d0
            global.setwaitTx(tx);
            changeState(State_wd23IOD32_8, interval);
        }
        break;

    case State_wd23IOD32_8:
        if (!(global.getwaitTx() & 0x08)) {
            changeState(State_inverter1, interval);
        }
        qDebug() << "48 RS485Ready" << RS485Ready << global.getTick();
        if (isTimerTimeout()) {
            RS485Ready = false;
            updateDIOut(48);
            int tx = global.getwaitTx() & ~0x8;  // remove d0
            global.setwaitTx(tx);
            changeState(State_inverter1, 1);
        }
        break;





    case State_inverter1:
        changeState(State_inverter2, 1);
        break;
    case State_inverter2:
        changeState(State_inverter3, 1);
        break;
    case State_inverter3:
        changeState(State_rd23IOD32_0, interval);
        break;

    default:
        break;
    }
}


void Modbus485::changeState(int newState, int timeout) {
    qDebug() << "485: " << Qt::hex << task_state<< "->" << Qt::hex << newState<< Qt::dec <<"Tick:"<< global.getTick() << "tick-old state" << global.getTick() - oldstateStartTime;
    task_state = newState;
    stateStartTime = intervalTimer->elapsed();//  global.getTick();
    oldstateStartTime = global.getTick();

    stateTimerInterval = 0;
    if (timeout > -1) {
        stateTimerInterval = timeout;
    }
    // qDebug() << "Star: " << stateStartTime<< "Interval: " << stateTimerInterval ;

}

bool Modbus485::isTimerTimeout() {
    // qDebug() << "Star: " << stateStartTime<< "Interval: " << stateTimerInterval  << "elaps - start: " << intervalTimer->elapsed() - stateStartTime ;
    return((intervalTimer->elapsed() - stateStartTime) > stateTimerInterval);
}


void Modbus485::printDIinput() {
    // printDIinput1(0,15);
    // printDIinput1(16,31);
    // printDIinput1(32,47);
    // printDIinput1(48,63);
    // printDIinput1(64,79);
    // printDIinput1(80,95);

    printDIinput1(0, 31);
    printDIinput1(32, 63);
    printDIinput1(64, 95);
}
void Modbus485::printDIoutput() {
    printDIoutput1(0, 31);
    //printDIioutput1(32,63);
    //printDIioutput1(64,95);
}
