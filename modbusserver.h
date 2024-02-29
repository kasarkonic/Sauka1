#ifndef MODBUSSERVER_H
#define MODBUSSERVER_H

#include "QtSerialBus/qmodbuspdu.h"
#include <QObject>
#include "global.h"
#include <QModbusRtuSerialServer>

class ModbusServer :public  QModbusRtuSerialServer
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ModbusServer)
public:
   explicit ModbusServer(Global &global, QObject *parent = nullptr);
   Global &global;
   bool init();

  public Q_SLOTS:
   void coilChanged(int id, bool value);

private Q_SLOTS:
      void onStateChanged(int state);
      void updateWidgets(QModbusDataUnit::RegisterType table, int address, int size);
      void handleDeviceError(QModbusDevice::Error newError);
     // void coilChanged(int id, bool value);
      void discreteInputChanged(int id, bool value);
      void bitChanged(int id, QModbusDataUnit::RegisterType table, bool value);

private:
    QModbusServer *modbusDevice = nullptr;

};


#endif // MODBUSSERVER_H
