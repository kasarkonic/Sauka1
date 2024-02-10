#ifndef RS232_H
#define RS232_H

#include <QMainWindow>
#include "global.h"
#include <QThread>
#include <QSerialPort>

namespace Ui {
class Rs232;
}

class Rs232 : public QMainWindow //,public QThread
{
    Q_OBJECT

public:
    explicit Rs232(Global &global, QWidget *parent = nullptr);
    QSerialPort *m_serial;
   // void readDats();
    ~Rs232();

private slots:
   // void readyRead();


private:
    Global &global;
    Ui::Rs232 *ui;

    //QSerialPort *m_serial;

    struct  ComInfo{
        QString port = "";
        QString location = "";
        QString description = "";
        QString manufacturer = "";
        QString serialNumber = "";
        QString vendorIdentifier = "";
        QString productIdentifier = "";
    };

    QMap<QString,ComInfo> comPortMap;
    void initPort();
    QString str ;
    QString corectPort;
    void sendData(QString send);
    void readDats();
};

#endif // RS232_H
