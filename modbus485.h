#ifndef MODBUS485_H
#define MODBUS485_H

#include "global.h"
#include <QMainWindow>
#    include <QModbusRtuSerialClient>
#    include <QSerialPortInfo>
#include <QElapsedTimer>
#include <QThread>
#include <QTimer>


class Modbus485  :  public QThread //  public QMainWindow
{
    Q_OBJECT
public:
    explicit Modbus485(Global &global, QWidget *parent = nullptr);

    // overriding the QThread's run() method
    void run() override;

    Global &global;
    QTimer *timer;
    bool init();
    void test(int address, int value);
    bool wr23IOD32(int boardAdr,int regAdr, quint16 value);
    bool rd23IOD32(int boardAdr,int regAdr);
    bool rd24DIB32(int boardAdr,int regAdr);
    bool rdN4AIB16(int boardAdr,int regAdr,int len);
    bool updateDIOut();

protected:
  //  void    timerEvent(QTimerEvent *event) override;

public slots:
    void errorHandler(QModbusDevice::Error error);
    bool setBaudrate(int address);
    bool factoryReset(int address);
    void MyTimerSlot();

signals:
    void valChangeAn(int sensAddr, int val);
    void valChangeDi(int sensAddr, bool val);

private slots:
    void onReadReady();
private:
    QModbusRtuSerialClient*  modbusDevice;
    QModbusDataUnit readRequest() const;
    QModbusDataUnit writeRequest() const;
    void readData();
    void writeDat(QModbusDataUnit writeUnit, int boardAdr);
    void writeDat();
    //QElapsedTimer timer;
    int timerTest;
    QString name;
    int timerReadIn;
    int timerWriteOut;

};

#endif // MODBUS485_H