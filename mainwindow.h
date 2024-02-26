#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QSettings>
#include <QMainWindow>
#include <QStringList>
#include "dyno.h"
#include "mix.h"
#include "pipe.h"
#include "pump.h"
#include "tvertne.h"
#include "global.h"
#include "valve.h"
#include "scalesbase.h"
#include "scalesmass.h"
#include "hwservice.h"
#include "rs232.h"
#include "parmani.h"
#include "procui1.h"
#include "procui2.h"




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Global &global, QWidget *parent = nullptr);
    ~MainWindow();

    Global &global;

private slots:


    // void openServiceForm();

    void on_pushButton_Stop_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_Dyno_clicked();

    void on_pushButton_Mix_clicked();

protected:
    void    resizeEvent(QResizeEvent* event) override;
    void    mousePressEvent(QMouseEvent *event) override;
    void    mouseMoveEvent (QMouseEvent *event) override;
    void    timerEvent(QTimerEvent *event) override;

private:

    //Global &global;

    Ui::MainWindow *ui;

    // WidgetData widgetData;


    Dyno *dynoA;
    Mix *mixA;
    Tvertne *tvertneA;
    Pump *pumpA;
    Pipe *pipeA;
    Valve *valveA;
    ScalesBase *scalesBase;
    ScalesMass *scalesMass;
    ProcUI1 procUI1;
    ProcUI2 procUI2;

    //HWService *hwService;
   // Rs232 *rs232;
   // ParMani *parmani;


    int valveStyleAngle;
    int minWidgSize;
    int valveStatus;
    //int areaY;
    //int areaX;

    void loadSettings();
    void saveSettings();
    QString settingsFile;

    void resizeAllKoef(float koef);
    void updateSettingForAll();
    void initUI();
    int  timerIdUpd = 0;
    int att = 0;

    QString currentTime; // HH:mm:ss

    void appendInfo(QString str, QColor col);

    QStringList  cmbList;
    void drawWidgets();
    bool initTimer;
    void delAllWid();

QString statusStr = "\u00A9 2023. vers. 0.0  tel. 29222201   02.02.2024  ";

};


#endif // MAINWINDOW_H
