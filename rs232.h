#ifndef RS232_H
#define RS232_H

#include <QMainWindow>
#include "global.h"
#include <QThread>
#include <QSerialPort>
#include <QSplineSeries>
#include <QChartView>
#include <QValueAxis>


namespace Ui {
class Rs232;
}

class Rs232 : public QMainWindow //,public QThread
{
    Q_OBJECT

public:
    explicit Rs232(Global &global, QWidget *parent = nullptr);
    QSerialPort *m_serial;
    void readSerial();
    ~Rs232();

private slots:
    // void readyRead();


    void on_pushButtonStart_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButton_1s_clicked();

    void on_pushButton_10s_clicked();

    void on_pushButton_60s_clicked();

protected:
    void    timerEvent(QTimerEvent *event) override;

private:
    Global &global;
    Ui::Rs232 *ui;

    struct  ComInfo{
        QString port = "";
        QString location = "";
        QString description = "";
        QString manufacturer = "";
        QString serialNumber = "";
        QString vendorIdentifier = "";
        QString productIdentifier = "";
    };

    struct chart1Data{
        QPointF chart1;
        QPointF chart2;
    };

    QList<chart1Data> chartDataList;

    QMap<QString,ComInfo> comPortMap;
    bool initPort();
    QString str ;
    QString corectPort;
    void sendData(QString send);
    void initUI();
    bool recordStatus = false;
    int timeMark = 60;

    QByteArray currserdata;

    QColor col;
    QString qssGreen;
    QString qssRed;
    QString qssGray;

    QChart *chart1;
    QSplineSeries *sp_seriesT1;
    QSplineSeries *sp_seriesT2;
    QSplineSeries *sp_seriesMin;
    QSplineSeries *sp_seriesMax;

    QValueAxis *axisX;
    QValueAxis *axisY;
    QChartView *chartView1;



    void drawTchart();
    int  timerId = 0;
    int timerInit = 0;
    int  att = 0;



};

#endif // RS232_H
