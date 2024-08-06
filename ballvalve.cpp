#include "ballvalve.h"
#include "global.h"


BallValve::BallValve(Global* global,QString name, int outOpen, int outClose, int inOpen, int inClose, QObject* parent )
    : QObject(parent)
    , global(global)
    , name(name)
    , outOpen (outOpen)
    , outClose (outClose)
    , inOpen (inOpen)
    , inClose (inClose)


{
    qDebug() <<"App sw vers:"<<  global->appSwVers<< global->getTick();
}

void BallValve::open()
{
    qDebug() <<"open valve";
    global->DIoutput[outOpen].value = 1;
    global->DIoutput[outOpen].update = true;
    startOpenTime = global->getTick();
    startTim();
    status = valveStatus::Unknow;

}

void BallValve::close()
{
    qDebug() <<"close valve";
    global->DIoutput[outClose].value = 1;
    global->DIoutput[outClose].update = true;
    StartCloseTime = global->getTick();
    startTim();
    status = valveStatus::Unknow;

}

bool BallValve::isOpen()
{
    return status == valveStatus::Open;
}

bool BallValve::isClose()
{
    return status == valveStatus::Close;
}

QString BallValve::getName()
{
    return name;
}

int BallValve::getOpenTime()
{
    return openTime;
}

int BallValve::getCloseTime()
{
    return closeTime;
}

int BallValve::initbattValve(bool stat)  // close if unknow status,
{
    if((global->DIinput[inOpen].value > 0) && (global->DIinput[inClose].value > 0)) {
        status = valveStatus::Unknow;
        close();
    }
    else if(global->DIinput[inOpen].value > 0) {
        status = valveStatus::Open;
        close();
    }
    else {
            status = valveStatus::Close;
        }
    return status;
}

int BallValve::getStatus()
{
    return status;
}

void BallValve::timerEvent(QTimerEvent *event)
{
    Q_UNUSED (event)
    //qDebug() << " BallValve TimerEvent" << global->getTick();

    if(startOpenTime){
        openTime =  (global->getTick() - startOpenTime)/100;
        if(global->DIinput[inOpen].value > 0){ 
            global->DIoutput[outOpen].value = 0;
            global->DIoutput[outOpen].update = true;
            //openTime =  global->getTick() - startOpenTime;
            startOpenTime = 0;
            status = valveStatus::Open;
            killTimer(timerId);
        }
        if((global->getTick() - startOpenTime) > 10000){ // 12s.  ERROR!!!
            global->DIoutput[outOpen].value = 0;
            global->DIoutput[outOpen].update = true;
            qDebug() << "ERROR!!! not open in 10s " ;
            status = valveStatus::Unknow;
            qDebug() << "ERROR!!! not open in 10s " ;
            killTimer(timerId);
        }
    }
    if(StartCloseTime){
        closeTime =  (global->getTick() - StartCloseTime)/100;
        if(global->DIinput[inClose].value > 0){
            global->DIoutput[outClose].value = 0;
            global->DIoutput[outClose].update = true;
            //closeTime =  global->getTick() - StartCloseTime;
            StartCloseTime = 0;
            status = valveStatus::Close;
            killTimer(timerId);
        }
        if((global->getTick() - StartCloseTime) > 12000){ // 12s.  ERROR!!!
            global->DIoutput[outClose].value = 0;
            global->DIoutput[outClose].update = true;
            status = valveStatus::Unknow;
            qDebug() << "ERROR!!! not close in 12s " ;
            killTimer(timerId);
        }
    }
}

void BallValve::startTim(int t)
{
   // qDebug() <<"startTim" << t;   //<< global->getTick();
    if(timerId != -1){
        killTimer(timerId);
    }
    timerId = startTimer(100);
}



