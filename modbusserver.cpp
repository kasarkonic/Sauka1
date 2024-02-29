#include "modbusserver.h"
#include "QtSerialBus/qmodbusdataunit.h"
#include <QSerialPort>
//#include <QModbusRtuSerialServer>
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

    connect(modbusDevice, &QModbusServer::dataWritten,
            this, &ModbusServer::updateWidgets);

    connect(modbusDevice, &QModbusServer::stateChanged,
            this, &ModbusServer::onStateChanged);

    connect(modbusDevice, &QModbusServer::errorOccurred,
            this, &ModbusServer::handleDeviceError);



}

bool ModbusServer::init()
{
    modbusDevice = new QModbusRtuSerialServer(this);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter, global.dev3);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
    modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);


    modbusDevice->setServerAddress(7);          // !!!! address

    QModbusDataUnitMap reg;
    reg.insert(QModbusDataUnit::Coils, { QModbusDataUnit::Coils, 0, 32 });
    reg.insert(QModbusDataUnit::DiscreteInputs, { QModbusDataUnit::DiscreteInputs, 0, 32 });
    reg.insert(QModbusDataUnit::InputRegisters, { QModbusDataUnit::InputRegisters, 0, 32 });
    reg.insert(QModbusDataUnit::HoldingRegisters, { QModbusDataUnit::HoldingRegisters, 0, 32 });

    modbusDevice->setMap(reg);
}

void ModbusServer::onStateChanged(int state)
{
    if (state == QModbusDevice::UnconnectedState)
        qDebug() << "Modbus disconected !!!!";
}
void ModbusServer::coilChanged(int id, bool value)
{

    bitChanged(id, QModbusDataUnit::Coils, value);
    qDebug() << "coilChanged" <<QModbusDataUnit::DiscreteInputs << id << value;
}

void ModbusServer::discreteInputChanged(int id, bool value)
{

    bitChanged(id, QModbusDataUnit::DiscreteInputs, value);
     qDebug() << "bitChanged" <<QModbusDataUnit::DiscreteInputs << id << value;
}

void ModbusServer::bitChanged(int id, QModbusDataUnit::RegisterType table, bool value)
{
    if (!modbusDevice)
        return;

    if (!modbusDevice->setData(table, quint16(id), value))
        qDebug() << "bitChanged" <<"Could not set data: " + modbusDevice->errorString() << id << value;

}

void ModbusServer::updateWidgets(QModbusDataUnit::RegisterType table, int address, int size)
{
    for (int i = 0; i < size; ++i) {
        quint16 value;
        QString text;
        switch (table) {
        case QModbusDataUnit::Coils:
            modbusDevice->data(QModbusDataUnit::Coils, quint16(address + i), &value);
            qDebug() << " rec. Coils" << value;
            break;
        case QModbusDataUnit::HoldingRegisters:
            modbusDevice->data(QModbusDataUnit::HoldingRegisters, quint16(address + i), &value);
            qDebug() << " rec. HoldingRegisters" << value;
            break;
        default:
            break;
        }
    }
}

void ModbusServer::handleDeviceError(Error newError)
{
    if (newError == QModbusDevice::NoError || !modbusDevice)
        return;
    qDebug() << " Error " << modbusDevice->errorString();
}

