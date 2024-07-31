#include "modbus485.h"
#include "qcoreevent.h"
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

    task_state = 0; // start
    taskTimer = new QTimer(this);
    taskTimer->start(10);//---------------------------------------------------------------------------------------------
    qDebug() <<" taskTimer->start(10);//----------------";
    connect(taskTimer, SIGNAL(timeout()),
            this, SLOT(runTaskCycle()));

    //    changeState(State_rd23IOD32_0);  for testing only
    //changeState(0);

    qDebug() << "Modbus485 set name ";
    name = "Modbus485";
    RS485Ready = true;
    driveStatusTimer = startTimer(3000);

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
        qDebug() << global.dev3 << "Connect failed:"<< global.dev3 << modbusDevice->errorString();
        global.dev3ConnectStatus = false;
        return false;
        //statusBar()->showMessage(tr("Connect failed: %1").arg(modbusDevice->errorString()), 5000);
    } else {
        qDebug() << "modbusDevice connect OK" << global.dev3;
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
    Q_ASSERT(startAddress >= 0 && startAddress < 0xffff);


    //quint16 numberOfEntries = 1;
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

bool Modbus485::wr23IOD32m(int boardAdr, int regAdr, quint16 value1, quint16 value2)
{
    qDebug() << "Modbus485::wr23IOD32m " << boardAdr << regAdr << Qt::hex << value1 << value2 << Qt::dec <<global.getTick();
    const auto table = QModbusDataUnit::HoldingRegisters;   // cmd 06
    int startAddress = regAdr;
    //Q_ASSERT(startAddress >= 0 && startAddress < 200);

    quint16 numberOfEntries = 2;
    //return QModbusDataUnit(table, startAddress, numberOfEntries);



    //! [write_data_0]
    //QModbusDataUnit writeUnit = writeRequest();
    QModbusDataUnit writeUnit = QModbusDataUnit(table, startAddress, numberOfEntries);


    //for (qsizetype i = 0, total = 1 /*writeUnit.valueCount()*/; i < total; ++i) {
    //    const auto addr = i + 0x70; //writeUnit.startAddress();
    //}

    writeUnit.setValue(0, value1); // writeModel->m_coils[addr]);
    writeUnit.setValue(1, value2); // writeModel->m_coils[addr]);
    // qDebug() << "writeUnit1? " << writeUnit.isValid() << writeUnit.registerType() << writeUnit.startAddress() << writeUnit.values();

    writeDat(writeUnit, boardAdr);
    return true;

}




bool Modbus485::rd23IOD32(int boardAdr, int regAdr, int len) {

    qDebug() << "rd23IOD32" <<boardAdr << regAdr << len << global.getTick();

    if (!modbusDevice) {
        qDebug() << "readDat RET";
        return false;
    }

    const auto table = QModbusDataUnit::HoldingRegisters;            //cmd 3
    int startAddress = regAdr;
    //Q_ASSERT(startAddress >= 0 && startAddress < 200);

    quint16 numberOfEntries = len;
    QModbusDataUnit dataUnit = QModbusDataUnit(table, startAddress, numberOfEntries);



    //! [read_data_1]
    if (auto* reply = modbusDevice->sendReadRequest(dataUnit, boardAdr)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, &Modbus485::onReadReady);
            QModbusDataUnit writeUnit = dataUnit;
            qDebug()<<"rd23IOD32"<< readRequest().registerType() << readRequest().values() << readRequest().valueCount() <<
                readRequest().startAddress() << readRequest().value(0)<< readRequest().value(1);
        } else
            delete reply; // broadcast replies return immediately

        qDebug() << "T=" << global.getTick() - starttemp << " OK res: " ;  // ok digital input

        return true;
    } else {
        // statusBar()->showMessage(tr("Read error: %1").arg(modbusDevice->errorString()), 5000);
        qDebug() << "Read error:" << modbusDevice->errorString();
        //qDebug()  << "T=" << global.getTick() - starttemp ;
        return false;
    }
}

bool Modbus485::rd24DIB32(int boardAdr, int regAdr) {
    qDebug() << "rd24DIB32" <<boardAdr<< regAdr << global.getTick();
    if (!modbusDevice) {
        qDebug() << "readDat RET";
        return false;
    }
    /*
    enum RegisterType {
        Invalid,                 nesūta neko
        DiscreteInputs,         2
        Coils,                  1
        InputRegisters,         4
        HoldingRegisters        3
    };  5                       compile error
 */
    const auto table = QModbusDataUnit::HoldingRegisters;   //3

    int startAddress = regAdr;
    //Q_ASSERT(startAddress >= 0 && startAddress < 200);

    quint16 numberOfEntries = 1;    // 2 ??????????????????????????????????????????????????????????????
    QModbusDataUnit dataUnit = QModbusDataUnit(table, startAddress, numberOfEntries);


    //! [read_data_1]
    if (auto* reply = modbusDevice->sendReadRequest(dataUnit, boardAdr)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, &Modbus485::onReadReady);
            QModbusDataUnit writeUnit = dataUnit;
            // qDebug() << readRequest().registerType() << readRequest().values() << readRequest().valueCount() <<
            //             readRequest().startAddress() << readRequest().value(0) << readRequest().value(1);
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
    qDebug() << "rdN4AIB16" <<boardAdr << "reg:" << regAdr << "len" << len << global.getTick();

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

    const auto table = QModbusDataUnit::InputRegisters;  // transmit 4 ????? !!!!

    int startAddress = regAdr;
    Q_ASSERT(startAddress >= 0 && startAddress < 0xffff);

    quint16 numberOfEntries = len;
    QModbusDataUnit dataUnit = QModbusDataUnit(table, startAddress, numberOfEntries);

    qDebug() << "dataUnit.isValid ?"<< dataUnit.isValid();

    //! [read_data_1]
    if (auto* reply = modbusDevice->sendReadRequest(dataUnit, boardAdr)) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, &Modbus485::onReadReady);
            QModbusDataUnit writeUnit = dataUnit;
            // qDebug() << readRequest().registerType() << readRequest().values() << readRequest().valueCount() <<
            //             readRequest().startAddress() << readRequest().value(0) << readRequest().value(1);
        } else{
            qDebug() << "replies return immediately" <<  readRequest().startAddress() << reply->rawResult().data();
            delete reply; // broadcast replies return immediately
        }
        return true;


    } else {
        // statusBar()->showMessage(tr("Read error: %1").arg(modbusDevice->errorString()), 5000);
        qDebug() << "Read error:" << modbusDevice->errorString();
        return false;
    }
}

bool Modbus485::wrDrive(int boardAdr, int regAdr, quint16 value)
{
    return wr23IOD32(boardAdr, regAdr, value);
}

bool Modbus485::wrDrivem(int boardAdr, int regAdr, quint16 value1, quint16 value2)
{
    return wr23IOD32m(boardAdr, regAdr, value1,value2);
}

bool Modbus485::rdDrivem(int boardAdr, int regAdr, int len)
{
    //return  rdN4AIB16(boardAdr, regAdr, len); // send cmd = 3 mut be 3 ???!!!
    return  rd23IOD32(boardAdr, regAdr, len);
}


quint16 Modbus485::updateDIOut(int i) {
    //qDebug() << "updateDIOut----------------------" << global.getTick();
    //int res = 0;
    quint16 val1, val2, val3, val4;
    bool val1ch, val2ch, val3ch, val4ch;
    val1 = val2 = val3 = val4 = 0;
    val1ch = val2ch = val3ch = val4ch = false;

    // printDIoutput();



    if ((0 <= i) && (i < 16)) {
        for (int k = 15; k >= 0;k--) {
            val1 <<= 1;
            val1 += (global.DIoutput[k].value > 0);
            // val1ch |= global.DIoutput[k].update;
            //  qDebug() << k << i << val1 << val1ch << (global.DIoutput[k].value > 0);
            global.DIoutput[k].update = false;
        }
        retval = val1;
        // qDebug() << "retval0" << i << retval;
    }
    //qDebug() << "retval1" << i << retval;

    if ((16 <= i) && (i < 32)) {
        for (int k = 31; k >= 16;k--) {
            val2 <<= 1;
            val2 += (global.DIoutput[k].value > 0);
            //val2ch |= global.DIoutput[k].update;
            //  qDebug()<< k << i << val2 << val1ch << (global.DIoutput[k].value > 0);
            global.DIoutput[k].update = false;
        }
        retval = val2;
    }



    if ((32 <= i) && (i < 48)) {
        for (int k = 47; k >= 32;k--) {
            val3 <<= 1;
            val3 += (global.DIoutput[k].value > 0);
            // val3ch |= global.DIoutput[k].update;
            //  qDebug()<< k << i << val3 << val1ch << (global.DIoutput[k].value > 0);
            global.DIoutput[k].update = false;
        }
        retval = val3;
    }


    if ((48 <= i) && (i < 64)) {
        for (int k = 63; k >= 48;k--) {
            val4 <<= 1;
            val4 += (global.DIoutput[k].value > 0);
            //val4ch |= global.DIoutput[k].update;
            //  qDebug()<< k << i << val4 << val1ch << (global.DIoutput[k].value > 0);
            global.DIoutput[k].update = false;
        }
        retval = val4;
    }


    //  qDebug() << "retval2" << i << Qt::hex << retval;
    return retval;
}



void Modbus485::timerEvent(QTimerEvent* event) {
    Q_UNUSED(event)




    if ( true &&(event->timerId() == driveStatusTimer )) {

        param.boardAdr = M8;
        param.regAdr = ETA_REG;
        param.value = 0;
        param.cmd = RD_REG;
        param.len = 1;
        //  global.rs485WrList.append(param);

        param.boardAdr = M9;
        //   global.rs485WrList.append(param);

        param.boardAdr = M4;
        //   global.rs485WrList.append(param);


        param.boardAdr = M8;
        param.regAdr = RFRD_REG;    //  for testing ERRD;
        param.value = 0;
        param.len = 1;  // for testing 1;
        param.cmd = RD_REG;
        global.rs485WrList.append(param);


        param.boardAdr = M9;
        //    global.rs485WrList.append(param);

        param.boardAdr = M4;
        //    global.rs485WrList.append(param);



        param.boardAdr = M8;
        param.regAdr = RFRD_REG;    //  for testing ERRD;
        param.value = 0;
        param.len = 1;  // for testing 1;
        param.cmd = RD_REG;
        global.rs485WrList.append(param);


        param.boardAdr = 20;    // read pressure level sensor
        param.regAdr = 0;    //  for testing ERRD;
        param.len = 12;  // for testing 1;
        param.cmd = RD_IN_REG;          // ta tomer md 3
        global.rs485WrList.append(param);



    }


}

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
    Q_UNUSED(value)
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


void Modbus485::onReadReady() {     // RS485 handler

    QByteArray replayDataArray;
    int datalen;
    auto reply = qobject_cast<QModbusReply*>(sender());

    if (!reply){
        qDebug() << "onReadReady not rep" << reply->serverAddress() << global.getTick();
        return;
    }

    //dataChangeDi = -1;  //if change 1 input    dataChangeDi = input number
    // dataChangeAn = -1;  //if change more inputs  dataChangeDi = 0xffff

    qDebug() << "";
    qDebug() << "onReadReady from addres" << reply->serverAddress()<< "type"<< reply->result().registerType() << reply->error() <<  global.getTick()
        <<  Qt::hex <<reply->rawResult().data() ;    // 0 => no error

    //  qDebug() << QString::number(reply->result().registerType(),16)   // 4
    //           << QString::number(reply->result().startAddress())      //192 if address -1 Error
    //           << QString::number(reply->result().valueCount());   // 4
    //
    if (reply->error() == QModbusDevice::NoError) {
        const QModbusDataUnit unit = reply->result();

        datalen = reply->rawResult().data().length();
        replayDataArray = reply->rawResult().data();
        qDebug() << "len: "  << datalen  << "Data:" << replayDataArray;
    }



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

            //---------------
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



            //------------
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


        case 18:     // Drive Motor M8


            qDebug() << "M8: "<< QString::number(replayDataArray.length())   // 4
                     << QString::number(reply->result().registerType(),16)   // 4
                     << QString::number(reply->result().startAddress()) ;     //192


            qDebug() << "Adr Id: "
                     <<  reply->serverAddress()
                     << "reg:"
                     <<  reply->result().startAddress()
                     << "data" ;
            for(int i = 0; i < replayDataArray.length(); i++){  // 0,1,2
                qDebug() << reply->result().value(i);
            }
            qDebug() << " -------------------";



            switch (reply->result().startAddress()) {
            case SAF1:      // 14 reg  Safety fault register SAF1,SAF2,SF00-SF11

                qDebug() << "SAF1 : ";
                for(int i = 0; i < replayDataArray.length(); i++){
                    qDebug() << reply->result().value(i);
                }
                break;
            case STOS:       // STO status
                qDebug() << "STOS : ";
                for(int i = 0; i < replayDataArray.length(); i++){
                    qDebug() << reply->result().value(i);
                }

                break;
            case ERRD:      // reg ERRD 8606 is CiA402 fault code
                qDebug() << "ERRD : ";
                for(int i = 0; i < replayDataArray.length(); i++){
                    qDebug() << reply->result().value(i);
                }

                qDebug() << reply->result().value(0);   // tas ir rezults ERRD
                break;
            case RFRD_REG:      // RFRD_REG 8605   1 rpm
                qDebug() << "RFRD_REG : ";
                for(int i = 0; i < replayDataArray.length(); i++){
                    qDebug() << reply->result().value(i);
                }

                qDebug() << reply->result().value(0) << " ---------------------------------------- rpm" ;   // tas ir rezults RFRD_REG
                break;
            default:
                break;
            }





            // reg ERRD 8606 is CiA402 fault code

            global.DIinput[drive_M8_status].value = (reply->result().value(0));
            global.DIinput[drive_M8_speed].value = (reply->result().value(1));
            // emit valChangeDi(drive_M8_status, global.DIinput[drive_M8_status].value);
            // emit valChangeDi(drive_M8_speed, global.DIinput[drive_M8_speed].value);

            break;

        case 20:     // collect sensors from external box

            /*



16 bitu dati!!!!


onReadReady from addres 20 type 4 QModbusDevice::NoError 23591 "\x18\xE0\xD2\xDD\xE6\xC2\x01\xFF\xFF\x03\xF9\x00\x10\x00\x0F\x03\xFB\x05\xF9\x07\xEE\x07\xEE\xA1v"
len:  25 Data: "\x18\xE0\xD2\xDD\xE6\xC2\x01\xFF\xFF\x03\xF9\x00\x10\x00\x0F\x03\xFB\x05\xF9\x07\xEE\x07\xEE\xA1v"
 Modbus Id:20 lenght error 25




                */
            //16

          //  if(datalen != 12){
         //       qDebug() << " Modbus Id:20 lenght error" << datalen;
          //  }
          //  else{
                global.DIinput[TVERTNE1LEVEL].value = reply->result().value(0);
                global.DIinput[TVERTNE2LEVEL].value = reply->result().value(1);
                global.DIinput[TVERTNE3LEVEL].value = reply->result().value(2);
                global.DIinput[TVERTNE4LEVEL].value = reply->result().value(3);
                global.DIinput[TVERTNE1FULL].value = reply->result().value(4);
                global.DIinput[TVERTNE2FULL].value = reply->result().value(5);
                global.DIinput[TVERTNE3FULL].value = reply->result().value(6);
                global.DIinput[TVERTNE4FULL].value = reply->result().value(7);
                global.DIinput[TVERTNE1TEMP].value = reply->result().value(8);
                global.DIinput[TVERTNE2TEMP].value = reply->result().value(9);
                global.DIinput[TVERTNE3TEMP].value = reply->result().value(10);
                global.DIinput[TVERTNE4TEMP].value = reply->result().value(11);

                qDebug() << " Modbus Id:20 Data"
                         << global.DIinput[TVERTNE1LEVEL].value
                         << global.DIinput[TVERTNE2LEVEL].value
                         << global.DIinput[TVERTNE3LEVEL].value
                         << global.DIinput[TVERTNE4LEVEL].value
                         << global.DIinput[TVERTNE1FULL].value
                         << global.DIinput[TVERTNE2FULL].value
                         << global.DIinput[TVERTNE3FULL].value
                         << global.DIinput[TVERTNE4FULL].value
                         << global.DIinput[TVERTNE1TEMP].value
                         << global.DIinput[TVERTNE2TEMP].value
                         << global.DIinput[TVERTNE3TEMP].value
                         << global.DIinput[TVERTNE4TEMP].value ;
          //  }

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
        qDebug() << "Read response error: Modbus exception:)" << reply->errorString() << reply->rawResult().exceptionCode()
                 << reply->rawResult().data() << ";;;;;;;;;";


    } else {
        //statusBar()->showMessage(tr("Read response error: %1 (code: 0x%2)").
        //                            arg(reply->errorString()).
        //                            arg(reply->error(), -1, 16), 5000);

        qDebug() << "Read response error: %1 (code: 0x%2)" << reply->errorString() << reply->error();
    }

    reply->deleteLater();

    //dataChangeDi >= 0 ;  emit signal !!!!!!!!!!!!!!!!!!!!
    //dataChangeAn >= 0
    qDebug() << "RS485Ready = 1" << reply->serverAddress() << global.getTick();
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
    //Q_ASSERT(startAddress >= 0 && startAddress < 200);

    // do not go beyond 10 entries
    quint16 numberOfEntries = 2;
    return QModbusDataUnit(table, startAddress, numberOfEntries);

}

QModbusDataUnit Modbus485::writeRequest() const {
    //const auto table = ui->writeTable->currentData().value<QModbusDataUnit::RegisterType>();
    //  //DiscreteInputs,Coils,InputRegisters, HoldingRegisters,
    const auto table = QModbusDataUnit::HoldingRegisters;  // coils->0f   HoldingRegisters -> 10 InputRegisters -> invalid request
    int startAddress = 0x70;
    //Q_ASSERT(startAddress >= 0 && startAddress < 200);

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

    stateStartTime = global.getTick();
    if(oldtask_state != task_state){
        // qDebug() << "runTaskCycle()" << task_state << stateStartTime;
    }
    oldtask_state = task_state;
    int interval = 25;  // 25 arI strādā
    quint16 dat1;
    quint16 dat2;

    switch (task_state) {



    case STDIN1:
        RS485Ready = false;
        rd23IOD32(4, 0xc0, 2);  // ok digital input
        changeState(STDIN2,interval);
        // changeState(STDOUTLIST,interval);   // only for testing !!!!!!!!!!!!!!!!!!!!!!!
        break;

    case STDIN2:
        if(RS485Ready){
            RS485Ready = false;
            rd23IOD32(5, 0xc0, 2);  // ok digital input
            changeState(STIAN3,1);
        }
        break;

    case STIAN3:
        if(RS485Ready){
            // qDebug() << "rd23IOD32(5, 0xc0) response time:" << global.getTick() - starttemp;
            RS485Ready = false;
            rd24DIB32(8, 0xc0); // analog input
            changeState(STIAN4,interval);
        }
        break;


    case STIAN4:

        if(RS485Ready){
            //qDebug() << "rd24DIB32(8, 0xc0) response time:" << global.getTick() - starttemp;
            RS485Ready = false;
            rdN4AIB16(2, 0, 16); // analog input
            changeState(STOUT5,interval);
        }
        break;

    case STOUT5:

        if(RS485Ready){
            //qDebug() << "rdN4AIB16(2, 0, 16) response time:" << global.getTick() - starttemp;

            dat1 = updateDIOut(0);
            dat2 = updateDIOut(16);
            wr23IOD32m(4,0x70,dat1,dat2);
            // RS485Ready = false;
            changeState(STOUT6,interval);//50

        }
        break;

    case STOUT6:

        // if(RS485Ready){
        dat1 = updateDIOut(32);
        dat2 = updateDIOut(48);
        wr23IOD32m(5,0x70,dat1,dat2);

        RS485Ready = false;
        changeState(STDOUTLIST,interval);//50

        // }
        break;



    case STDOUTLIST:

        if(global.rs485WrList.size() > 0){
            // qDebug() << "STDOUTLIST rs485WrList" << global.rs485WrList.length();

            qDebug() << "STDOUTLIST: len="<<global.rs485WrList.length()
                     << "Adr:"
                     <<global.rs485WrList[0].boardAdr
                     << "node:"
                     <<global.rs485WrList[0].regAdr
                     << "val:"
                     <<global.rs485WrList[0].value
                     << "CMD:"
                     <<global.rs485WrList[0].cmd
                     << "len:"
                     <<global.rs485WrList[0].len
                     << "tick:"
                     << global.getTick();

            switch (global.rs485WrList[0].cmd) {
            case WR_REG:
                wr23IOD32(global.rs485WrList[0].boardAdr, global.rs485WrList[0].regAdr, global.rs485WrList[0].value);
                break;
            case RD_REG:
                RS485Ready = false;
                rdDrivem(global.rs485WrList[0].boardAdr, global.rs485WrList[0].regAdr, global.rs485WrList[0].len);
                // rdDrivem(18, 3201, 2);
                //rdDrivem(2, 0, 4);
                break;
            case RD_IN_REG:
                rdDrivem(global.rs485WrList[0].boardAdr, global.rs485WrList[0].regAdr, global.rs485WrList[0].len);
                break;
            default:
                break;
            }

            global.rs485WrList.removeFirst();
            changeState(STOUT7,interval);
        }
        else{
            changeState(STOUT7,1);
        }
        break;


    case STOUT7:

        if(global.rs485WrList.size() > 0){

            changeState(STDOUTLIST,1);
        }
        else{
            changeState(IDLE,1);
        }
        break;

    case IDLE:
        //qDebug() << "------------------------------" << global.getTick();
        RS485Ready = true;
        changeState(STDIN1, interval);
        break;


    default:
        break;
    }
    if(oldtask_state == task_state){
        //qDebug() << "the same state -> 10ms"  << global.getnTick();
        changeState(task_state,10); // min state interval
    }

}


void Modbus485::changeState(int newState, int timeout) {
    if(task_state != newState){
        // qDebug() << "485: " << Qt::hex << task_state<< "->" << Qt::hex << newState<< Qt::dec <<"Tick:"<< global.getTick(); -------------------------------------
        task_state = newState;
    }

    if(timeout > 0){
        //taskTimer->setInterval(timeout);
        taskTimer->start(timeout);
    }
    else{
        taskTimer->stop();
        //runTaskCycle();
        taskTimer->start(1);   // 1 mSec min timeout
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
