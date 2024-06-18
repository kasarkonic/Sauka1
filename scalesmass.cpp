#include "scalesmass.h"
#include "ui_scalesmass.h"

ScalesMass::ScalesMass(Global &global, QString name, QWidget *parent)
    : WidgetDiagramElement(global,name,parent)
{
    global.widHash[settings.name].ptrCurrWidget = this;
    //widName = name;
    //settings.startX = global.widHash[settings.name].startX;
    //settings.startY = global.widHash[settings.name].startY;
    //settings.startSize = global.widHash[settings.name].startSize;
   // timerIdUpd = startTimer(200, Qt::CoarseTimer);

    //*
        QPalette pal = QPalette();
        pal.setColor(QPalette::Window, Qt::lightGray); //QColor(255, 0, 0, 127)
        pal.setColor(QPalette::Window, QColor(0, 0, 0, 20));
        this->setAutoFillBackground(true);
        this->setPalette(pal);
    //*/

    timerIdUpd = startTimer(500, Qt::CoarseTimer);  // only for widgetervice position addjust
}

void ScalesMass::updateSettings()
{
    WidgetDiagramElement::updateSettings(); // base class
    int an1SensAdr = global.widHash[settings.name].sensAddres1;
    massValue = global.sensList[an1SensAdr].analog /10.0;
    qDebug() << "scales val = " << settings.name <<an1SensAdr << massValue;
    update();
      //repaint();
}

void ScalesMass::paintEvent(QPaintEvent *event)
{
    Q_UNUSED (event);

    // qDebug() << "MIX paintEvent"<<settings.name <<settings.currX << settings.currY << settings.currSize<<"\n" ;

    QPainter painter(this);
    QPen pen;
    pen.setWidth(4);    //draw pipe
    pen.setColor(Qt::red);
    painter.setBrush(Qt::red);
    painter.setPen(pen);

    imgBackground= new QImage();
    imgBackground->load(":/pictures/kettlebell1.png");

    *imgBackground = imgBackground->scaled(settings.currSize, settings.currSize, Qt::KeepAspectRatio);
    painter.drawImage(QPoint(), *imgBackground);

    QString str = QString::number(massValue);
   // qDebug() << massValue << str;

    QFont font("times", settings.currSize/6);
    painter.setFont(font);
    qDebug() << "scalesM = " << settings.name <<settings.currSize << settings.startX << settings.currX << settings.startY << settings.currY;
    painter.drawText(QRect(0, settings.currSize/6, settings.currSize, settings.currSize), Qt::AlignCenter, str);
    resize(settings.currSize,settings.currSize);
}

void ScalesMass::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)
   // WidgetDiagramElement::updateSettings();
    //qDebug() << "ScalesMass::timerEvent";
    //if(event->timerId() == timerIdUpd){
        updateSettings();
   // }
}
