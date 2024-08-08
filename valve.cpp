#include "valve.h"

//#include <QSettings>
//#include <QPainter>



Valve::Valve(Global& global, QString name, QWidget* parent)
    : WidgetDiagramElement(global, name, parent)

{

    global.widHash[settings.name].ptrCurrWidget = this;
    //*
#ifdef ENABLE_WIDGET_SIZE
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, QColor(0, 0, 0, 20));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
#endif

    currentAngle = 45;
    timerIdUpd = startTimer(200, Qt::CoarseTimer);
}

void Valve::updateSettings() {
    // qDebug() << "Valve updateSettings" << settings.var1;
    WidgetDiagramElement::updateSettings();

    killTimer(timerIdUpd);
    if (motorOn) {
        timerIdUpd = startTimer(50, Qt::CoarseTimer);
    } else {
        timerIdUpd = startTimer(200, Qt::CoarseTimer); // not rotate
        att = 0;
        changeDirections = 0;
    }
    int openPos = settings.var1;//  0 vai 90

    motorOn = global.ballValveList[settings.npk].bValvePtr->getStatus() == 2 ; //valveStatus::Unknow = 2

   // in/out pin:
   // int outOpen = global.ballValveList[settings.npk].bValvePtr->outOpen;    // output address
   // int outClose = global.ballValveList[settings.npk].bValvePtr->outClose;
    int inOpen = global.ballValveList[settings.npk].bValvePtr->inOpen;
    int inClose = global.ballValveList[settings.npk].bValvePtr->inClose;


    swOpen = (bool)(global.DIinput[inOpen].value > 0);
    swClose = (bool)(global.DIinput[inClose].value > 0);



    if (swClose == 1 && swOpen == 0) {  //close
        currentAngle = openPos + 90;    // close
        changeDirections = -1;
    }
    if (swClose == 0 && swOpen == 1) {  //open
        currentAngle = openPos;    // open

        changeDirections = 1;
    }
    if (swClose == 0 && swOpen == 0 && motorOn) {  //process
        changeDirections = 0;
    }
    if (swClose == 0 && swOpen == 0 && !motorOn) {  //process
        currentAngle = 45;   // process
        changeDirections = 0;
    }

    if (swClose == 1 && swOpen == 1) {  //error
        currentAngle = 45;    // error
        att = 0;
        changeDirections = 0;
    }


    // qDebug() << "Valve sensors" << motorOn << swOpen << swClose << currentAngle << changeDirections << att;



     /*
     if(motorOn){  //motorOn
         currentAngle = 45 + att ;

         if(swClose == 1 && openPos >=45) changeDirections = -1;
         if(swClose == 1 && openPos <45) changeDirections = 1;
         if(swOpen == 1 && openPos >=45) changeDirections = -1;
         if(swOpen == 1 && openPos <45) changeDirections = 1;
     }
     else{
         changeDirections = 0;
     }
     */
     //qDebug() << settings.name<<" stat,Om,Off" << currentAngle << settings.var1 << swOpen <<swClose << att <<changeDirections;

    update();
}

void Valve::calcPoints(int angle) {
    float an = M_PI / 180 * (35 + angle);
    float an1 = M_PI / 180 * (180 - 35 + angle);
    float size = settings.currSize;

    points[0] = QPoint(size / 2 + size / 2 * cos(an), size / 2 - size / 2 * sin(an));//0
    points[1] = QPoint(size / 2 - size / 2 * cos(an), size / 2 + size / 2 * sin(an));//3
    points[2] = QPoint(size / 2 + size / 2 * cos(an1), size / 2 - size / 2 * sin(an1));//1
    points[3] = QPoint(size / 2 - size / 2 * cos(an1), size / 2 + size / 2 * sin(an1));//2
}
/*
void Valve::updateWidget()
{
    move(settings.currX,settings.currY);
    resize(settings.currSize,settings.currSize);
}

void Valve::setNewPosition(float koef)
{
    settings.currX = int(settings.startX /koef);
    settings.currY = int(settings.startY / koef);
    settings.currSize = int (settings.startSize/koef);
    qDebug() << "Valve::setNewPosition" << koef;

    move(settings.currX,settings.currY);
    resize(settings.currSize,settings.currSize);
}

*/
void Valve::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    //qDebug() << "Valve::paintEvent" <<settings.status <<settings.var1 ;
    // qDebug() << "Valve paintEvent"<<settings.name <<settings.currX << settings.currY << settings.currSize<<"\n" ;


    calcPoints(currentAngle + att);

    QPainter painter(this);
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::black);

    QColor  color = Qt::yellow;

    if (swClose == 1 && swOpen == 0) {
        color = Qt::red;
    } else if (swClose == 0 && swOpen == 1) {
        color = Qt::green;
    } else {
        color = Qt::yellow;
    }

    painter.setBrush(color);
    painter.setPen(pen);
    painter.drawPolygon(points, 4, Qt::WindingFill);

    resize(settings.currSize, settings.currSize);

}


void Valve::timerEvent(QTimerEvent* event) {
    Q_UNUSED(event);

    if (event->timerId() == timerIdUpd) {
        att = att + changeDirections;
        if (att > 3600) {
            att = 0;
        }
        if (att < 0) {
            att = 3600;
        }
        //qDebug() << att<<" timerIdUpd";
        //update();
        updateSettings();
    }
}
