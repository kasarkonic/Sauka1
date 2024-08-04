#ifndef BALLVALVE_H
#define BALLVALVE_H

#include <QMainWindow>
#include <QTimer>
#include "global.h"
//#include <QElapsedTimer>
#include <QBasicTimer>

class Global;
class BallValve :  public QObject
{
    Q_OBJECT
public:
    explicit BallValve(Global* global, int outOpern, int outClose, int inOpen, int inClose);


    void open();
    void close();
    bool isOpen();
    bool isClose();
    int getOpenTime();
    int getCloseTime();
    int initbattValve( bool stat ); // close/oprn if unknow status 0 close,  1 open.
    QTimer* runTimer;

public slots:
    void timerEvent();

protected:
    // void startTim(int t = 100);
    void timerEvent(QTimerEvent* event) ;

private slots:
    //void timerEvent();

private:

    enum valveStatus {
        Open,
        Close,
        Unknow,
    };

    //QTimer* runTimer;
     QElapsedTimer etimer;
     QBasicTimer btimer;
    Global* global;
    void startTim(int t = 1000);
    int outOpern = 0;
    int outClose = 0;
    int inOpen = 0;
    int inClose = 0;

    int openTime = 0;
    int closeTime = 0;
    //int startTime;

    valveStatus status = valveStatus::Unknow;



};

#endif // BALLVALVE_H
