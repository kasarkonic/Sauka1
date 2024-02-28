#ifndef MODBUSSERVER_H
#define MODBUSSERVER_H

#include "QtSerialBus/qmodbuspdu.h"
#include <QObject>
#include <QModbusRtuSerialServer>

class ModbusServer :public  QModbusRtuSerialServer
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ModbusServer)
public:
    ModbusServer(QObject *parent = nullptr);
private:
    QModbusResponse processPrivateRequest(const QModbusPdu &request) ;
};


#endif // MODBUSSERVER_H
