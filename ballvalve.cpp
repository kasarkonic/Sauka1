#include "ballvalve.h"
//#include "global.h"
//#include "inout.h"
#include <QTimer>

BallValve::BallValve(Global* global, int outOpern, int outClose, int inOpen, int inClose)
    //: QMainWindow(parent)
    : global(global)
    , outOpern (outOpern)
    , outClose (outClose)
    , inOpen (inOpen)
    , inClose (inClose)


{

    qDebug() <<"App sw vers:"<<  global->appSwVers;

    runTimer = new QTimer();
    //etimer.start();
    btimer.start(1000,this);
   connect(runTimer, SIGNAL(timeout()),this, SLOT(timerEvent()));

   // runTimer->start(1000);
}

void BallValve::open()
{
qDebug() <<"close alve";
    global->DIoutput[outOpern].value = 1;
    global->DIoutput[outOpern].update = true;
   // startTime = global->getTick();
    startTim();



    /*
    1. ieslēdz out
            2 paņem laiku
            sagaida rezultātu
            izslēdz out
            izrēkina laiku.
            */

}

void BallValve::close()
{
    qDebug() <<"close alve";
    startTim();

}

bool BallValve::isOpen()
{
    return status == valveStatus::Open;
}

bool BallValve::isClose()
{
    return status == valveStatus::Close;
}

int BallValve::getOpenTime()
{
    return openTime;
}

int BallValve::getCloseTime()
{
    return closeTime;
}

int BallValve::initbattValve(bool stat)  // close/oprn if unknow status 0 close,  1 open.
{
    if((global->DIinput[inOpen].value > 0) && (global->DIinput[inClose].value > 0)){
        status = valveStatus::Unknow;
        if(stat){
            open();
        }
        else{
            close();
        }
    }
    else if((global->DIinput[inOpen].value > 0)){
        status = valveStatus::Open;
    }
    else if((global->DIinput[inClose].value > 0)){
        status = valveStatus::Close;
    }
    return status;



}

void BallValve::startTim(int t)
{
    qDebug() <<"startTim" << t;
   // runTimer->start(1000);
//runTimer->start(t);
//connect(runTimer, SIGNAL(timeout()),
 //       this, SLOT(runTimer()));
}

void BallValve::timerEvent(QTimerEvent *event)
{
    qDebug() << " BallValve timer event" << global->getTick();
//runTimer->start(1000);
}

void BallValve::timerEvent()
{
     qDebug() << " BallValve timerEvent" << global->getTick();
//runTimer->start(1000);
}

