#include "scalesmass.h"
#include "ui_scalesmass.h"

ScalesMass::ScalesMass(Global &global, QString name, QWidget *parent)
    : WidgetDiagramElement(global,name,parent)
{
    settings.startX = global.widHash[settings.name].startX;
    settings.startY = global.widHash[settings.name].startY;
    settings.startSize = global.widHash[settings.name].startSize;
    timerId = startTimer(200, Qt::CoarseTimer);
}

void ScalesMass::updateSettings()
{
    WidgetDiagramElement::updateSettings(); // base class

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
    imgBackground->load(":/pictures/icons-scales-weightl.png");

    *imgBackground = imgBackground->scaled(settings.currSize, settings.currSize, Qt::KeepAspectRatio);
    painter.drawImage(QPoint(), *imgBackground);

    QFont font("times", settings.currSize/6);
    painter.setFont(font);
    painter.drawText(QRect(0, 0, settings.currSize, settings.currSize), Qt::AlignCenter, "123,4 kg");
}

void ScalesMass::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)
    if(timerId){
        update();
    }
}
