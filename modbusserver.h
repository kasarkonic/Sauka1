#ifndef MODBUSSERVER_H
#define MODBUSSERVER_H

#include "QtSerialBus/qmodbuspdu.h"
#include <QObject>
#include <QModbusRtuSerialServer>
#include "global.h"

class ModbusServer :public  QModbusRtuSerialServer
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ModbusServer)
public:
    ModbusServer(Global &global, QObject *parent = nullptr);
    Global &global;
    ~ModbusServer();

    void bitChanged(int id, QModbusDataUnit::RegisterType table, bool value);
    void setRegister(const QString &value);

private:
    QModbusResponse processPrivateRequest(const QModbusPdu &request) ;
    QModbusRtuSerialServer *modbusDevice ;
    void updateWidgets(QModbusDataUnit::RegisterType table, int address, int size);
    QModbusDataUnitMap reg;
};


#endif // MODBUSSERVER_H
