#ifndef RS232_H
#define RS232_H

#include <QMainWindow>
#include "global.h"
#include <QSettings>

#include <QSerialPort>
#include <QSplineSeries>
#include <QChartView>
#include <QValueAxis>
#include <QTime>

#define START_MSG       '$'
#define END_MSG         ';'

#define WAIT_START      1
#define IN_MESSAGE      2
#define UNDEFINED       3

namespace Ui {
    class Rs232;
}

class Rs232 : public QMainWindow //,public QThread
{
    Q_OBJECT

public:
    explicit Rs232(Global& global, QWidget* parent = nullptr);
    QSerialPort* m_serial;
    void readSerial();
    ~Rs232();

private slots:
    // void readyRead();


    void on_pushButtonStart_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButton_1s_clicked();

    void on_pushButton_10s_clicked();

    void on_pushButton_60s_clicked();

    void on_pushButton_Save_clicked();

    void newDataUpdateCh(QStringList);
    void on_pushButton_set_S0_clicked();

    void on_pushButton_set_S1_clicked();

    void on_pushButton_set_empty_s0_clicked();

    void on_pushButton_set_empty_s1_clicked();

    void on_lineEdit_empty_S0_editingFinished();

    void on_lineEdit_empty_S1_editingFinished();

    void on_lineEdit_full_S1_editingFinished();

    void on_lineEdit_full_S0_editingFinished();

    void on_pushButton_save_S0_clicked();

    void on_pushButton_save_S1_clicked();

signals:
    void newData(QStringList data);

protected:
    void    timerEvent(QTimerEvent* event) override;
    void    closeEvent(QCloseEvent* event) override;
    void    mouseDoubleClickEvent(QMouseEvent* event) override;

private:

    Global& global;
    Ui::Rs232* ui;

    struct  ComInfo {
        QString port = "";
        QString location = "";
        QString description = "";
        QString manufacturer = "";
        QString serialNumber = "";
        QString vendorIdentifier = "";
        QString productIdentifier = "";
    };

    struct chart1Data {
        QPointF chartT1;
        QPointF chartT2;
    };

    QList<chart1Data> chartDataList;
    QMap<QString, ComInfo> comPortMap;
    bool initPort();
    QString str;
    QString corectPort;
    void sendData(QString send);
    void initUI();
    bool recordStatus = false;
    int timeMark = 60;

    QByteArray currserdata;
    QString receivedData;

    QColor col;
    QString qssGreen;
    QString qssRed;
    QString qssGray;
    QString qssCyan;


    QChart* chart1;
    QSplineSeries* sp_seriesT1;
    QSplineSeries* sp_seriesT2;
    QSplineSeries* sp_seriesMin;
    QSplineSeries* sp_seriesMax;

    QValueAxis* myAxisX;
    QValueAxis* myAxisY;
    QChartView* chartView1;
    QPointF  spser;
    QString myAxisYtitle;

    void drawTchart();
    bool createMessageBox(QString text);
    int  timerIdUpd = 0;
    int timerInit = 0;
    int timer1sId = 0;
    int  att = 0;
    QString currentTime;
    QTime startTime;
    // void newDataUpdateCh(QStringList currSdata);
    int receiveDataRequest = false;
    void addPointToChart(int val1, int val2);

    int STATE;
    int addPressSensList(int sensorNr, int val);    // ret fill %
    int  calcPressSensList(int sensorNr);
    bool ok;

    QString settingsFile;


};


#endif // RS232_H
