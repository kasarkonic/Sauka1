#ifndef MODBUS485_H
#define MODBUS485_H

#include "global.h"
#include <QMainWindow>
#    include <QModbusRtuSerialClient>
#    include <QSerialPortInfo>


class Modbus485  : public QMainWindow
{
    Q_OBJECT
public:
    explicit Modbus485(Global &global, QWidget *parent = nullptr);

    Global &global;
    bool init();
    void test(int address, int value);

public slots:
    void errorHandler(QModbusDevice::Error error);


private slots:
    void onReadReady();
private:
    QModbusRtuSerialClient*  modbusDevice;
    QModbusDataUnit readRequest() const;
    QModbusDataUnit writeRequest() const;
    void readData();
    void writeDat();

};

#endif // MODBUS485_H
