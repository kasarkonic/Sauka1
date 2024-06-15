#ifndef MODBUS485_H
#define MODBUS485_H

#include "global.h"
#include <QMainWindow>
#    include <QModbusRtuSerialClient>
#    include <QSerialPortInfo>
#include <QElapsedTimer>
#include <QThread>
#include <QTimer>
#include <QElapsedTimer>


class Modbus485  :  public QThread //  public QMainWindow
{
    Q_OBJECT
public:
    explicit Modbus485(Global &global, QWidget *parent = nullptr);

    // overriding the QThread's run() method
    // void run() override;

    //QTimer *timerReadIn;
    //QTimer *timerWriteOut;

    bool init();
    void test(int address, int value);
    bool wr23IOD32(int boardAdr,int regAdr, quint16 value);
    bool rd23IOD32(int boardAdr,int regAdr);
    bool rd24DIB32(int boardAdr,int regAdr);
    bool rdN4AIB16(int boardAdr,int regAdr,int len);
    bool updateDIOut();
    bool updateDIOut(int i);

protected:
    void    timerEvent(QTimerEvent *event) override;

public slots:
    void errorHandler(QModbusDevice::Error error);
    bool setBaudrate(int address);
    bool factoryReset(int address);
    void timerReadSlot();
    void timerWriteSlot();
    void diOutputChangeSl(int i, int value);


signals:
    void valChangeAn(int sensAddr, int val);
    void valChangeDi(int sensAddr, bool val);

private slots:
    void onReadReady();
    void runTaskCycle();

private:
    Global &global;
    QModbusRtuSerialClient*  modbusDevice;
    QModbusDataUnit readRequest() const;
    QModbusDataUnit writeRequest() const;
    void readData();
    void writeDat(QModbusDataUnit writeUnit, int boardAdr);
    void writeDat();
    //QElapsedTimer timer;
    int timerTest;
    QElapsedTimer *intervalTimer;
    QString name;

    quint16 val1,val2,val3,val4;
    quint16 val1old,val2old,val3old,val4old;
    void printDIinput();
    void printDIinput1(int start, int finish);


    enum States
    {

        State_rd23IOD32_0 ,
        State_rd23IOD32_1 ,
        State_rd24DIB32 ,
        State_rdN4AIB16 ,

        State_wd23IOD32_0 ,
        State_wd23IOD32_1 ,
        State_inverter1 ,
        State_inverter2 ,
        State_inverter3

    };

   // void runTaskCycle();
    void changeState(int newState, int timeout = -1);
    int task_state;
    int stateStartTime;
    QTimer *taskTimer;
    bool isTimerTimeout();
    int stateTimerInterval = 0;
   // bool stateTimerTimeout = false;

};

#endif // MODBUS485_H
