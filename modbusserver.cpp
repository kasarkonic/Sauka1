#include "modbusserver.h"
#include "QtSerialBus/qmodbusdataunit.h"
#include <QModbusDevice>
#include <QSerialPort>

// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause


// The request must contain the start address (quint16) and the number of
// registers to read (quint16).
static constexpr int ReadRequestSize {4};

// The request must contain the start address (quint16), the number of
// registers to write (quint16), the byte count (quint8) and at least one
// register value (quint16).
static constexpr int WriteHeaderSize {5};
static constexpr int MinimumWriteRequestSize {WriteHeaderSize + 2}; // 2 payload bytes

ModbusServer::ModbusServer(Global &global, QObject *parent)
    : QModbusRtuSerialServer(parent)
    , global(global)
{
   //global.dev1    port Nr

    modbusDevice = new QModbusRtuSerialServer(this);


    QModbusDataUnitMap reg;
    reg.insert(QModbusDataUnit::Coils, { QModbusDataUnit::Coils, 0, 10 });
    reg.insert(QModbusDataUnit::DiscreteInputs, { QModbusDataUnit::DiscreteInputs, 0, 10 });
    reg.insert(QModbusDataUnit::InputRegisters, { QModbusDataUnit::InputRegisters, 0, 10 });
    reg.insert(QModbusDataUnit::HoldingRegisters, { QModbusDataUnit::HoldingRegisters, 0, 10 });

    modbusDevice->setMap(reg);




    modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter, global.dev1);

    modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,QSerialPort::NoParity);

    modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,QSerialPort::Baud9600);

    modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,QSerialPort::Data8);

    modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);


    QModbusServer::connectDevice() ;


    //setMap({{QModbusDataUnit::HoldingRegisters, {QModbusDataUnit::HoldingRegisters, 0, 10}}});


}

ModbusServer::~ModbusServer()
{
    // close port ???
}

void ModbusServer::bitChanged(int id, QModbusDataUnit::RegisterType table, bool value)
{
    if (!modbusDevice)
        return;

    if (!modbusDevice->setData(table, quint16(id), value))
        qDebug()<< "Could not set data: " + modbusDevice->errorString();
}

void ModbusServer::setRegister(const QString &value)
{
    if (!modbusDevice)
        return;

    const QString objectName = QObject::sender()->objectName();
  //  if (registers.contains(objectName)) {
        bool ok = true;
        const quint16 id = quint16(QObject::sender()->property("ID").toUInt());
        if (objectName.startsWith(QStringLiteral("inReg"))) {
            const auto uval = value.toUShort(&ok, 16);
            if (ok)
                ok = modbusDevice->setData(QModbusDataUnit::InputRegisters, id, uval);
        } else if (objectName.startsWith(QStringLiteral("holdReg"))) {
            const auto uval = value.toUShort(&ok, 16);
            if (ok)
                ok = modbusDevice->setData(QModbusDataUnit::HoldingRegisters, id, uval);
        }

        if (!ok)
        qDebug()<< "Could not set register: " + modbusDevice->errorString();
  //  }
}


void ModbusServer::updateWidgets(QModbusDataUnit::RegisterType table, int address, int size)
{
    for (int i = 0; i < size; ++i) {
        quint16 value;
        QString text;
        switch (table) {
        case QModbusDataUnit::Coils:
            modbusDevice->data(QModbusDataUnit::Coils, quint16(address + i), &value);
            // coilButtons.button(address + i)->setChecked(value);
            qDebug() <<"coil:"<< address + i << value;
            break;
        case QModbusDataUnit::HoldingRegisters:
            modbusDevice->data(QModbusDataUnit::HoldingRegisters, quint16(address + i), &value);
            //registers.value(QStringLiteral("holdReg_%1").arg(address + i))->setText(text.setNum(value, 16));
            qDebug() << "registers:" << QStringLiteral("holdReg_%1").arg(address + i) << value;

            break;
        default:
            break;
        }
    }
}
