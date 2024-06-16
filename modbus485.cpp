#include "modbus485.h"
#include <QSerialPort>
#include <QLoggingCategory>





Modbus485::Modbus485(Global &global, QWidget *parent)
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
    taskTimer->start(10);
    connect(taskTimer, SIGNAL(timeout()),
            this, SLOT(runTaskCycle()));

    changeState(State_rd23IOD32_0);
    qDebug() << "Modbus485 set name ";
    name = "Modbus485";

}
/*
void Modbus485::run()
{
    qDebug() << "Modbus485 Run ";
    timerReadIn->start(500);
    timerWriteOut->start(250);
}
*/


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
    Q_UNUSED (address);
    Q_UNUSED ( value);
    //onReadReady();

    //readData();
    // writeDat();
    // wr23IOD32(7,0x70, 0xff);

}

bool Modbus485::wr23IOD32(int boardAdr, int regAdr, quint16 value)  // 7, 0x70, 0xffff
{
    qDebug() << "Modbus485::wr23IOD32 " << boardAdr<< regAdr << Qt::hex << value;
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

    // qDebug() << "writeUnit1? " << writeUnit.isValid() << writeUnit.registerType() << writeUnit.startAddress() << writeUnit.values();

    writeDat(writeUnit,boardAdr);
    return true;
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
            //qDebug()<<"rd23IOD32"<< readRequest().registerType() << readRequest().values() << readRequest().valueCount() <<
            //   readRequest().startAddress() << readRequest().value(0)<< readRequest().value(1);
        }
        else
            delete reply; // broadcast replies return immediately
        qDebug() << "T=" << global.getTick() - starttemp << " OK res: " ;  // ok digital input

        return true;
    } else {
        // statusBar()->showMessage(tr("Read error: %1").arg(modbusDevice->errorString()), 5000);
        qDebug() << "Read error:" << modbusDevice->errorString() ;
        //qDebug()  << "T=" << global.getTick() - starttemp ;
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
    // timer.start();
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
    int res = 0;
    res =  updateDIOut(0);
    res =+ updateDIOut(16);
    res =+ updateDIOut(32);
    res =+ updateDIOut(48);
    /*
            int tmpTime = global.getTick();
            //qDebug() << "Modbus485::updateDIOut()" << tmpTime ;

            int res;
            quint16 val1,val2,val3,val4;
            val1 = val2 = val3 = val4 = 0;
            for(int i = 15; i >= 0;i--){
                val1 <<= 1;
                val1 += (global.DIoutput[i].value & 1);
                val2 <<= 1;
                val2 += (global.DIoutput[i+16].value & 1);
                val3 <<= 1;
                val3 += (global.DIoutput[i+32].value & 1);
                val4 <<= 1;
                val4 += (global.DIoutput[i+48].value & 1);
            }
            // qDebug() << "wr23IOD32 = " << (void *)val1 << (void *)val2 << (void *)val3 << (void *)val4;
            qDebug() << "wr23IOD32 = " << Qt::hex<<val1 << val2 << val3 << val4;
            res =  wr23IOD32(4,0x70,val1);  // wr23IOD32(7,0x70, 0xff);
            res +=  wr23IOD32(4,0x71,val2);  // wr23IOD32(7,0x70, 0xff)
            res +=  wr23IOD32(5,0x70,val3);  // wr23IOD32(7,0x70, 0xff);
            res +=  wr23IOD32(5,0x71,val4);  // wr23IOD32(7,0x70, 0xff)
            qDebug() << "Modbus485::update finish " << global.getTick() << global.getTick() - tmpTime ;
            return (res == 4);
          */
    return (res == 4);
}

bool Modbus485::updateDIOut(int i)
{
    int res = 0;
    quint16 val1,val2,val3,val4;
    val1 = val2 = val3 = val4 = 0;


    for(int k = 15; k >= 0;k--){
        val1 <<= 1;
        val1 += (global.DIoutput[k].value & 1);
        val2 <<= 1;
        val2 += (global.DIoutput[k+16].value & 1);
        val3 <<= 1;
        val3 += (global.DIoutput[k+32].value & 1);
        val4 <<= 1;
        val4 += (global.DIoutput[k+48].value & 1);
    }
    // qDebug() << "wr23IOD32 = " << (void *)val1 << (void *)val2 << (void *)val3 << (void *)val4;
    qDebug() << "wr23IOD32 = " << i << global.DIoutput[i].value << Qt::hex<<val1 << val2 << val3 << val4;


    if(i >= 0 && i < 16){
        res =  wr23IOD32(4,0x70,val1);  // wr23IOD32(7,0x70, 0xff);
    }
    if(i >= 16 && i < 32){
        res +=  wr23IOD32(4,0x71,val2);  // wr23IOD32(7,0x70, 0xff)
    }
    if(i >= 32 && i < 48){
        res +=  wr23IOD32(5,0x70,val3);  // wr23IOD32(7,0x70, 0xff);
    }
    if(i >= 48 && i < 64){
        res +=  wr23IOD32(5,0x71,val4);  // wr23IOD32(7,0x70, 0xff)
    }
    qDebug() << "updateDIOut" << i << res << global.getTick();
    return (res == 4);
}



void Modbus485::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)
    //if(event->timerId() == taskTimer){
    //     runTaskCycle();
    // }
}

void Modbus485::timerReadSlot()
{
    if(!global.disableRS485){
        qDebug() << "Read An Di Inputs";
        //analog input, next DI input, next update DI output
        rdN4AIB16(2, 0,16);   // ok analog input!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        rd23IOD32(4,0xc0);  // ok digital input
        rd23IOD32(5,0xc0);  // ok digital input
        //updateDIOut();

    }
}
void Modbus485::timerWriteSlot()
{
    qDebug() << "Change  Outputs" << global.disableRS485 << global.updateDataOut.need;
    // if(!global.disableRS485){
    // if(global.updateDataOut.need){
    //    global.updateDataOut.need = false;
    updateDIOut();
    // }

    // }
}

void Modbus485::diOutputChangeSl(int i, int value)
{
    qDebug() << "Modbus485::diOutputChangeSl !!!!!!!!!!!!!!!!" << i << value <<global.getTick();
    if(i<16){
        global.setwaitTx(0x1);
    }
    if(1 > 15 && i<31){
        global.setwaitTx(0x2);
    }
    if(1 > 30 && i< 48){
        global.setwaitTx(0x4);
    }
    if(i<47 && i < 54){
        global.setwaitTx(0x8);
    }





   // updateDIOut(i);   // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

}

void Modbus485::errorHandler(QModbusDevice::Error error)
{
    qDebug() << "ERROR !!!" << error;
}

bool Modbus485::setBaudrate(int address)
{
    Q_UNUSED (address);
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

    //qDebug() << "onReadReady from addres" << reply->serverAddress();
    if (reply->error() == QModbusDevice::NoError) {
        const QModbusDataUnit unit = reply->result();

        datalen = reply->rawResult().data().length();
        replayDataArray = reply->rawResult().data();
        //qDebug() << "datalen , reg Type,address" << reply->serverAddress() << replayDataArray.length() << datalen << unit.registerType();

        switch (reply->serverAddress()) {
        case 2:     // rdN4AIB16
            if(unit.registerType() == 3 && replayDataArray.length() == datalen){
                qDebug() << "rdN4AIB16" << reply->serverAddress() << datalen  << reply->result().values();
                for(int i = 0; i <=15; i++){    // in0 - in14 0-20mA input  in15 30v input
                    if(global.ANinput4_20[i].value != reply->result().value(i)){
                        qDebug() << "emit valChangeAn(i)"<< i  << global.ANinput4_20[i].value << reply->result().value(i);
                        global.ANinput4_20[i].value = reply->result().value(i);
                        global.ANinput4_20[i].update = true;
                        emit valChangeAn(i, global.ANinput4_20[i].value);// for testing
                    }
                }
            }

            else{
                qDebug() << "error";
            }
            ismodbusFree = true;
            qDebug() << "imodbus Free " <<reply->serverAddress() <<"t:" <<global.getTick() - starttemp;
            break;



        case 4:     // rd23IOD32 read data address 4
            if(unit.registerType() == 4 && replayDataArray.length() == datalen){
                qDebug() << "Din rd23IOD32 address:" << reply->serverAddress()
                         <<  QString::number(reply->result().value(0), 16)
                          << QString::number(reply->result().value(1), 16);


                for(int i = 0; i < MAX_DIinput/2; i++){
                    if((bool)global.DIinput[i].value != (bool)(reply->result().value(0) & (1 << i))){
                        global.DIinput[i].value = (bool)(reply->result().value(0) & (1 << i));
                        global.DIinput[i].update = true;
                        qDebug() << "emit valChangeDi(" << i << ")" << global.DIinput[i].value;
                        emit valChangeDi(i,(bool)global.DIinput[i].value);
                    }
                }
                for(int i = 0; i < MAX_DIinput/2; i++){
                    if((bool)global.DIinput[i + MAX_DIinput/2].value != (bool)(reply->result().value(1) & (1 << i))){
                        global.DIinput[i + MAX_DIinput/2].value = (bool)(reply->result().value(1) & (1 << i));
                        global.DIinput[i + MAX_DIinput/2].update = true;
                        qDebug() << "emit valChangeDi(" << i << ")" << global.DIinput[i + MAX_DIinput/2].value;
                        emit valChangeDi(i+MAX_DIinput/2, (bool)global.DIinput[i+MAX_DIinput/2].value);
                    }
                }
                // printDIinput();

            }
            else{
                qDebug() << "error";
            }

            ismodbusFree = true;
            qDebug() << "imodbus Free " <<reply->serverAddress() <<"t:" <<global.getTick() - starttemp;
            break;


        case 5:     // rd23IOD32 read data address5
            if(unit.registerType() == 4 && replayDataArray.length() == datalen){
                qDebug() << "Din rd23IOD32 address:" << reply->serverAddress()
                         <<  QString::number(reply->result().value(0), 16)
                          << QString::number(reply->result().value(1), 16);

                for(int i = 0; i < 16; i++){
                    if((bool)global.DIinput[i + 32].value != (bool)(reply->result().value(0) & (1 << i))){
                        global.DIinput[i + 32].value = (bool)(reply->result().value(0) & (1 << i));
                        global.DIinput[i + 32].update = true;
                        qDebug() << "emit valChangeDi(" << i + 32 << ")" << global.DIinput[i + 32].value;
                        emit valChangeDi(i + MAX_DIinput/2,(bool)global.DIinput[i + MAX_DIinput/2].value);
                    }
                }
                for(int i = 0; i < 16; i++){
                    if((bool)global.DIinput[i + 32 + 16].value != (bool)(reply->result().value(1) & (1 << i))){
                        global.DIinput[i + 32 + 16].value = (bool)(reply->result().value(1) & (1 << i));
                        global.DIinput[i + 32 + 16].update = true;
                        qDebug() << "emit valChangeDi(" << i + 32 + 16  << ")" << global.DIinput[i + 32 + 16].value;
                        emit valChangeDi(i+MAX_DIinput/2, (bool)global.DIinput[i+MAX_DIinput/2].value);
                    }
                }


                //  printDIinput();
            }
            else{
                qDebug() << "error";
            }

            ismodbusFree = true;
            qDebug() << "imodbus Free " <<reply->serverAddress() <<"t:" <<global.getTick() - starttemp;
            break;

        case 8:     // 24DIB32  DIinput[64-95]
            if(unit.registerType() == 4 && replayDataArray.length() == datalen){
                qDebug() << "Din 24DIB32 address:" << reply->serverAddress()
                         <<  QString::number(reply->result().value(0), 16)
                          << QString::number(reply->result().value(1), 16);

                for(int i = 0; i < 16; i++){
                    if((bool)global.DIinput[i + 64].value != (bool)(reply->result().value(0) & (1 << i))){
                        global.DIinput[i + 64].value = (bool)(reply->result().value(0) & (1 << i));
                        global.DIinput[i + 64].update = true;
                        qDebug() << "emit valChangeDi(" << i + 64 << ")" << global.DIinput[i + 64].value;
                        emit valChangeDi(i + 64,(bool)global.DIinput[i + 64].value);
                    }
                }
                for(int i = 0; i < 16; i++){
                    if((bool)global.DIinput[i + 64 + 16].value != (bool)(reply->result().value(1) & (1 << i))){
                        global.DIinput[i + 64 + 16].value = (bool)(reply->result().value(1) & (1 << i));
                        global.DIinput[i + 64 + 16].update = true;
                        qDebug() << "emit valChangeDi(" << i + 64 + 16  << ")" << global.DIinput[i + 64 + 16].value;
                        emit valChangeDi(i+ 64 + 16, (bool)global.DIinput[i+64+16].value);
                    }
                }
                ismodbusFree = true;
                printDIinput();
            }

            break;

            ismodbusFree = true;
            qDebug() << "imodbus Free " <<reply->serverAddress() <<"t:" <<global.getTick() - starttemp;


        default:
            qDebug() << "Receive Msg from uncnown Modbus addres !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
            break;
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
    // qDebug() << "writeUnit2? " << writeUnit.isValid() << writeUnit.registerType() << writeUnit.startAddress() << writeUnit.values();


    if (auto *reply = modbusDevice->sendWriteRequest(writeUnit, boardAdr)) {
        if (!reply->isFinished()) {
            //if error
            connect(reply, &QModbusReply::finished, this, [this, reply]() {
                const auto error = reply->error();

                if (error == QModbusDevice::ProtocolError) {
                    //  statusBar()->showMessage(tr("Write response error: %1 (Modbus exception: 0x%2)")
                    //      .arg(reply->errorString()).arg(reply->rawResult().exceptionCode(), -1, 16),
                    //       5000);
                    qDebug() << "Write response error::  (code:)"<< reply->errorString()<<reply->rawResult().exceptionCode();

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

    // QModbusDataUnit::RegisterType table = QModbusDataUnit::HoldingRegisters;
    for (qsizetype i = 0, total = 1 ; i < total; ++i) {
        // const auto addr = i + 0x70; //writeUnit.startAddress();
        writeUnit.setValue(i, 0xcc ); // writeModel->m_coils[addr]);
    }


    qDebug() << "writeUnit2? " << writeUnit.isValid() << writeUnit.registerType() << writeUnit.startAddress() << writeUnit.values();




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


void Modbus485::printDIinput1(int start, int finish){
    QDebug debug = qDebug();

    for(int i = start; i<= finish; i++){
        debug << global.DIinput[i].value;
    }
}

void Modbus485::runTaskCycle()
{
    int interval = 50;  // 25 arI strādā
    //qDebug() << "runTaskCycle()" << task_state;
    switch (task_state)
    {
    case State_rd23IOD32_0:
        if (isTimerTimeout())
        {
            //qDebug() << "starttemp" << ismodbusFree << global.getTick() - starttemp ;
            starttemp =  global.getTick();
            rd23IOD32(4,0xc0);  // ok digital input

            ismodbusFree = false;

                        if( global.getwaitTx()){
                            changeState(State_wd23IOD32_0,interval);
                        }
                        else {
                            changeState(State_rd23IOD32_1,interval);
                        }

        }
        break;
    case State_rd23IOD32_1:
        if (isTimerTimeout())
        {
         //   rd23IOD32(5,0xc0);  // ok digital input  no board !!!!
            if( global.getwaitTx()){
                changeState(State_wd23IOD32_0,interval);
            }
            else {
                changeState(State_rd24DIB32,1);
            }
        }
        break;
    case State_rd24DIB32:
        if (isTimerTimeout())
        {
            rd24DIB32(8,0xc0);
            if( global.getwaitTx()){
                changeState(State_wd23IOD32_0,interval);
            }
            else {
                changeState(State_rdN4AIB16);
            }
        }
        break;
    case State_rdN4AIB16:
        if (isTimerTimeout())
        {
            rdN4AIB16(2, 0,16);

             if( global.getwaitTx()){
                 changeState(State_wd23IOD32_0,interval);
             }
             else {
            changeState(State_wd23IOD32_0,interval);
             }
        }
        break;

    case State_wd23IOD32_0:
        qDebug() << "getwaitTx" << global.getwaitTx() ;
        if( !(global.getwaitTx() & 0x03)){
            changeState(State_wd23IOD32_1,1);
        }

        if (isTimerTimeout())
        {
          if(global.getwaitTx() & 0x01){
            updateDIOut(0);
            int tx = global.getwaitTx() & ~0x1 ;  // remove d0
            global.setwaitTx(tx);
             }
          if(global.getwaitTx() & 0x02){
            updateDIOut(16);
            int tx = global.getwaitTx() & ~0x2 ;  // remove d0
            global.setwaitTx(tx);
             }
            changeState(State_wd23IOD32_1,interval);
          }


        break;
    case State_wd23IOD32_1:
            qDebug() << "getwaitTx" << global.getwaitTx() ;
        if( !(global.getwaitTx() & 0x0c)){
            changeState(State_rd23IOD32_0,interval);
        }

        if (isTimerTimeout())
        {

            if(global.getwaitTx() & 0x04){
             // updateDIOut(32);    // no board -----------------------------------------------
              int tx = global.getwaitTx() & ~0x4 ;  // remove d0
              global.setwaitTx(tx);
               }
            if(global.getwaitTx() & 0x08){
            //  updateDIOut(48); // no board -----------------------------------------------
              int tx = global.getwaitTx() & ~0x8 ;  // remove d0
              global.setwaitTx(tx);
               }

            changeState(State_rd23IOD32_0,interval);
        }
        break;
    case State_inverter1:

        break;
    case State_inverter2:

        break;

    case State_inverter3:

        break;

    default:
        break;
    }
}


void Modbus485::changeState(int newState, int timeout)
{
    qDebug() << "485: " << Qt::hex << task_state<< "->" << Qt::hex << newState<< Qt::dec <<"Tick:"<< global.getTick() << global.getTick() - oldstateStartTime;
    task_state = newState;
    stateStartTime = intervalTimer->elapsed();//  global.getTick();
    oldstateStartTime = global.getTick();

    stateTimerInterval = 0;
    if (timeout > -1) {
        stateTimerInterval = timeout;
    }
    qDebug() << "Star: " << stateStartTime<< "Interval: " << stateTimerInterval ;

}

bool Modbus485::isTimerTimeout()
{
    // qDebug() << "Star: " << stateStartTime<< "Interval: " << stateTimerInterval  << "elaps - start: " << intervalTimer->elapsed() - stateStartTime ;
    return((intervalTimer->elapsed() - stateStartTime) > stateTimerInterval);
}


void Modbus485::printDIinput()
{
   // printDIinput1(0,15);
   // printDIinput1(16,31);
   // printDIinput1(32,47);
   // printDIinput1(48,63);
   printDIinput1(64,79);
    printDIinput1(80,95);
}

