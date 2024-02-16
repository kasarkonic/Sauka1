#ifndef SCALE_H
#define SCALE_H

#include "global.h"
#include <QMainWindow>
#include <QSerialPort>

#define START_MSG       '$'
#define END_MSG         ';'

#define WAIT_START      1
#define IN_MESSAGE      2
#define UNDEFINED       3

namespace Ui {
class Scale;
}

class Scale : public QMainWindow
{
    Q_OBJECT

public:
    explicit Scale(Global &global, QWidget *parent = nullptr);
    QSerialPort *sc_serial;
    ~Scale();


protected:
    void    timerEvent(QTimerEvent *event) override;
signals:
    void newData(QStringList data);
private slots:
    void on_lineEdit_Send_editingFinished();

    void on_pushButton_clicked();

private:
    Global &global;
    Ui::Scale *ui;
    void initUI();
    bool initPort();
    void sendData(QString send);
    void readSerial();
    QString corectPort;
    QString receivedData;
    bool receiveDataRequest = false;



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

    int  timerId = 0;
    int timerInit = 0;
    int timer1sId = 0;
    int att;
    QString currentTime;
    int STATE;
};

#endif // SCALE_H