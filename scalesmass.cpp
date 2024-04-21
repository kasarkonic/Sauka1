#include "scalesmass.h"
#include "ui_scalesmass.h"

ScalesMass::ScalesMass(Global &global, QString name, QWidget *parent)
    : WidgetDiagramElement(global,name,parent)
{
    global.widHash[settings.name].ptrCurrWidget = this;
    widName = name;
    settings.startX = global.widHash[settings.name].startX;
    settings.startY = global.widHash[settings.name].startY;
    settings.startSize = global.widHash[settings.name].startSize;
    timerIdUpd = startTimer(200, Qt::CoarseTimer);
}

void ScalesMass::updateSettings()
{
    WidgetDiagramElement::updateSettings(); // base class
    int an1SensAdr = global.widHash[widName].sensAddres1;
    massValue = global.sensList[an1SensAdr].analog /10.0;
    //qDebug() << "scales val = " << widName <<an1SensAdr << massValue;
     update();
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
    painter.drawText(QRect(0, settings.currSize/6, settings.currSize, settings.currSize), Qt::AlignCenter, str);
resize(settings.currSize,settings.currSize);
}

void ScalesMass::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)
    //qDebug() << "ScalesMass::timerEvent";
    if(event->timerId() == timerIdUpd){
        updateSettings();
    }
}
