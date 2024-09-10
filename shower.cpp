#include "shower.h"


Shower::Shower(Global& global, QString name, QWidget* parent)
 : WidgetDiagramElement(global, name, parent)
{
}


void Shower::updateSettings() {
    WidgetDiagramElement::updateSettings(); // base class
    // qDebug() << "Shower updateSettings" << settings.currX << settings.currY << settings.act_Addres1<< global.getTick();

    speed = (int)global.DIoutput[settings.var1].value;
    killTimer(timerIdUpd);
    if (speed) {
        timerIdUpd = startTimer(50, Qt::CoarseTimer); //rotate
    } else {
        timerIdUpd = startTimer(200, Qt::CoarseTimer); // not rotate
    }
    update();
}
\


void Shower::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    //qDebug() << "Shower paintEvent"<<settings.name <<settings.currX << settings.currY << settings.currSize<<"\n" ;

    QPainter painter(this);
    QPen pen;
    //  pen.setWidth(4);    //draw Shower
    //  pen.setColor(Qt::red);
    //  painter.setBrush(Qt::red);
    //  painter.setPen(pen);

    imgBackground = new QImage();
    imgBackground->load(":/pictures/shower.png");

    *imgBackground = imgBackground->scaled(settings.currSize, settings.currSize, Qt::KeepAspectRatio);
    painter.drawImage(QPoint(), *imgBackground);


    QPoint points[4];
    /*
    points[0] = QPoint(0 + settings.currX,0 + settings.currY);
    points[1] = QPoint(settings.currSize + settings.currX,0 + settings.currY);
    points[2] = QPoint(settings.currSize + settings.currX,settings.currSize + settings.currY);
    points[3] = QPoint(0 + settings.currX,settings.currSize + settings.currY);

   // painter.drawPolygon(points,4);/  nezinu kas parsarkanu kluci ????
*/
    int rad = settings.currSize - 4;// minus pen
    rad = (int)settings.currSize / 7;

    float an = att * M_PI / 180;

    points[0] = QPoint(rad * cos(an) + rad, rad * sin(an) + rad);
    points[1] = QPoint(rad * cos(an + 2 * M_PI / 3) + rad, rad * sin(an + 2 * M_PI / 3) + rad);
    points[2] = QPoint(rad * cos(an + 4 * M_PI / 3) + rad, rad * sin(an + 4 * M_PI / 3) + rad);

    pen.setWidth(2);
    pen.setColor(Qt::black);
    painter.setBrush(triangColor);
    painter.setPen(pen);
    painter.drawPolygon(points, 3);




    resize(settings.currSize, settings.currSize);
}

void Shower::timerEvent(QTimerEvent* event) {
    Q_UNUSED(event)
    if (event->timerId() == timerIdUpd) {
        int step = speed;
        att += step;
        if (att > 360) {
            att = 0;
        }
        updateSettings();
    }
}

/*
void Shower::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
       // qDebug() << "Mix mousePressEvent" ;
       //  updateSettings();
    }
}
void Shower::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();

    // get the cursor position of this event
    const QPoint& pos = event->pos();

    int pointX = pos.x();
    int pointY = pos.y();

    settings.startX += pointX;
    settings.startY += pointY;
    //?   updateSettings();
    // updateServiceUI();
    //() << "Pump mouseMoveEvent dx:dy" << pointX - mouseStartPointX << pointY - mouseStartPointY ;
}

void Shower::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        qDebug() << "Mix mouseDoubleClickEvent" ;
        // emit openServicePump();
        //emit openServicePipe();

    //    WidgetService *serviceForm = new WidgetService();
    //    serviceForm->show();

    }

}
*/
