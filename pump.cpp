#include "pump.h"

Pump::Pump(Global &global,QString name, QWidget *parent)
    : WidgetDiagramElement(global, name,parent)
{
    global.widHash[settings.name].ptrCurrWidget = this;
    //*
#ifdef ENABLE_WIDGET_SIZE
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::lightGray); //QColor(255, 0, 0, 127)
    pal.setColor(QPalette::Window, QColor(0, 0, 0, 20));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
#endif
    timerIdUpd = startTimer(100, Qt::CoarseTimer);  // only for widgetervice position addjust

}

void Pump::updateSettings()
{

    WidgetDiagramElement::updateSettings(); // base class
    //qDebug() << "Pump updateSettings" << settings.options;

    speed = (int)global.DIoutput[settings.act_Addres1].value;
    step = (int)(speed)/10;
    if(global.DIoutput[settings.sensAddres1].value == 0){
        step = 0;
    }


    //int dSensAdr = global.widHash[settings.name].sensAddres1;
    //speed = (int)global.sensList[dSensAdr].analog /3;
    killTimer(timerIdUpd);

    if(speed & 0x7fff){
        timerIdUpd = startTimer(50, Qt::CoarseTimer);
    }
    else{
        timerIdUpd = startTimer(200, Qt::CoarseTimer);
    }
    update();
}

void Pump::paintEvent(QPaintEvent *event)
{

    Q_UNUSED (event);
    // qDebug() << "Pump::paintEvent" << settings.currX << settings.currY << settings.currSize;
    QPainter painter(this);
    QPen pen;
    pen.setWidth(4);    //draw pipe
    pen.setColor(Qt::green);
    //painter.setBrush(settings.triangColor);// (pipeColour);
    painter.setPen(pen);

    int rad = settings.currSize - 4;// minus pen
    painter.drawEllipse(2, 2, rad, rad);

    rad = (int)settings.currSize/2 ;

    float an = att * M_PI /180;
    QPoint points[3];
    points[0] = QPoint(rad * cos(an) + rad, rad * sin(an) + rad);
    points[1] = QPoint(rad * cos(an + 2*M_PI/3) + rad, rad * sin(an + 2*M_PI/3) + rad);
    points[2] = QPoint(rad * cos(an + 4*M_PI/3) + rad, rad * sin(an + 4*M_PI/3) + rad);

    pen.setWidth(2);
    pen.setColor(Qt::blue);
    painter.setBrush(triangColor);
    painter.setPen(pen);
    painter.drawPolygon(points,3);

    resize(settings.currSize,settings.currSize);
    //  move(settings.currX,settings.currY);
}

void Pump::timerEvent(QTimerEvent *event)
{
    Q_UNUSED (event);
    if(event->timerId() == timerIdUpd){
        att+= step;

        if (att < 0)
            att = 360;

        if (att > 360)
            att = 0;

        //qDebug() << "Pump::att " << att << Qt::hex << speed << (speed & 0x8000) ;
        //update();
        updateSettings();
    }
}
/*
void Pump::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();

    // get the cursor position of this event
    const QPoint& pos = event->pos();

    int pointX = pos.x();
    int pointY = pos.y();

    settings.startX += pointX;
    settings.startY += pointY;
    //?   updateSettings();
    emit updateServiceUI();
    qDebug() << "Pump mouseMoveEvent dx:dy" << pointX - mouseStartPointX << pointY - mouseStartPointY ;


}

void Pump::mousePressEvent(QMouseEvent *event)
{
    const QPoint& pos = event->pos();
    mouseStartPointX = pos.x();
    mouseStartPointY = pos.y();
    qDebug() << " Pump mousePressEvent dx:dy" <<pos.x() << pos.y();
}

void Pump::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        qDebug() << "Pump mouseDoubleClickEvent" ;
        //emit openServicePump();
      //  WidgetService *serviceForm = new WidgetService();
      //  serviceForm->show();
    }
}

*/
