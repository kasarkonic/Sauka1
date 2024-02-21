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


    QPoint points[4];

    points[0] = QPoint(0 + settings.currX,0 + settings.currY);
    points[1] = QPoint(settings.currSize + settings.currX,0 + settings.currY);
    points[2] = QPoint(settings.currSize + settings.currX,settings.currSize + settings.currY);
    points[3] = QPoint(0 + settings.currX,settings.currSize + settings.currY);

    painter.drawPolygon(points,4);

    int rad = settings.currSize - 4;// minus pen
    rad = (int)settings.currSize/5 ;

    float an = att * M_PI /180;

    points[0] = QPoint(rad * cos(an) + rad, rad * sin(an) + rad);
    points[1] = QPoint(rad * cos(an + 2*M_PI/3) + rad, rad * sin(an + 2*M_PI/3) + rad);
    points[2] = QPoint(rad * cos(an + 4*M_PI/3) + rad, rad * sin(an + 4*M_PI/3) + rad);

    pen.setWidth(2);
    pen.setColor(Qt::blue);
    painter.setBrush(triangColor);
    painter.setPen(pen);
    painter.drawPolygon(points,3);







    //  imgBackground= new QImage();
    //  imgBackground->load(":/pictures/mixeris3.png");

    //  *imgBackground = imgBackground->scaled(settings.currSize, settings.currSize, Qt::KeepAspectRatio);
    //  painter.drawImage(QPoint(), *imgBackground);


}

void ScalesMass::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)
    if(timerId){
        update();
    }
}
