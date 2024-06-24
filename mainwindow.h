#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QSettings>
#include <QMainWindow>
#include <QStringList>
#include "dyno.h"
#include "mix.h"
#include "pipe.h"
#include "pump.h"
#include "dispax.h"
#include "label.h"
#include "tvertne.h"
#include "global.h"
#include "valve.h"
#include "scalesbase.h"
#include "scalesmass.h"
#include "hwservice.h"
#include "procui1.h"
#include "procui2.h"
#include "modbus485.h"
#include "scale.h"
#include "runprocess.h"

//#include "componentcard.h"
//#include "recipet.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Global &global, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void changeInputVal(int row, int val);

private slots:

    // void openServiceForm();

    void on_pushButton_Stop_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_Dyno_clicked();

    void on_pushButton_Mix_clicked();

    void on_pushButton_Recipes_clicked();

    void on_pushButton_Service_clicked();

protected:
    Scale scale;

    void    resizeEvent(QResizeEvent* event) override;
    void    mousePressEvent(QMouseEvent *event) override;
    void    mouseMoveEvent (QMouseEvent *event) override;
    void    timerEvent(QTimerEvent *event) override;



private:

    Global &global;

    Ui::MainWindow *ui;

    // WidgetData widgetData;

    Dyno *dynoA;
    Mix *mixA;
    Tvertne *tvertneA;
    Pump *pumpA;
    Dispax *dispax;
    Label *label;
    Pipe *pipeA;
    Valve *valveA;
    ScalesBase *scalesBase;
    ScalesMass *scalesMass;
    ProcUI1 procUI1;
    ProcUI2 procUI2;
    Modbus485 modbus485;
    Runprocess runprocess;
   // Scale scale;

    HWService hwService;
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

    void initUI();
    int  timerIdUpd = 0;
    int  timerTest = 0;
    int  timerTick = 0;
    int timerUpdateOutput = 0;
    int att = 0;
    int att1 = 0;

    QString currentTime; // HH:mm:ss

    void appendInfo(QString str, QColor col);

    QStringList  cmbList;
    //void drawWidgets();
    bool initTimer;
    void delAllWid();

QString statusStr = "\u00A9 2023. vers. 0.0  tel. 29222201   02.02.2024  ";

};


#endif // MAINWINDOW_H
