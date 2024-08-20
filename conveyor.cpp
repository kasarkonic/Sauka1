#include "conveyor.h"


Conveyor::Conveyor(Global& global, QString name, QWidget* parent)
    : WidgetDiagramElement(global, name, parent) {
    global.widHash[settings.name].ptrCurrWidget = this;
    ///*
#ifdef ENABLE_WIDGET_SIZE
    QPalette pal = QPalette();
    //pal.setColor(QPalette::Window, Qt::lightGray); //QColor(255, 0, 0, 127)
    pal.setColor(QPalette::Window, QColor(0, 0, 0, 50));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
#endif

    timerIdUpd = startTimer(100, Qt::CoarseTimer);  // only for widgetervice position addjust

}

void Conveyor::updateSettings() {
    WidgetDiagramElement::updateSettings(); // base class
    // qDebug() << "Conveyor updateSettings" << settings.currX << settings.currY << settings.act_Addres1<< global.getTick();

    killTimer(timerIdUpd);
    if (global.DIoutput[settings.var1].value) {
        timerIdUpd = startTimer(50, Qt::CoarseTimer); //rotate
    } else {
        timerIdUpd = startTimer(100, Qt::CoarseTimer); // not rotate
    }
    //repaint();
    update();
}

void Conveyor::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    //qDebug() << "Conveyor paintEvent"<<settings.name <<settings.currX << settings.currY << settings.currSize<<"\n" ;
    //   qDebug() << "Conveyor::paintEvent";
    QPainter painter(this);
 /*   QPen pen;
    pen.setWidth(4);    //draw pipe
    pen.setColor(Qt::red);
    painter.setBrush(Qt::red);
    painter.setPen(pen);

    QPoint points[4];

    points[0] = QPoint(0 + settings.currX, 0 + settings.currY);
    points[1] = QPoint(settings.currSize + settings.currX, 0 + settings.currY);
    points[2] = QPoint(settings.currSize + settings.currX, settings.currSize + settings.currY);
    points[3] = QPoint(0 + settings.currX, settings.currSize + settings.currY);

    painter.drawPolygon(points, 4);
*/
    imgBackground = new QImage();
    imgBackground->load(":/pictures/conveyor1.png");

    *imgBackground = imgBackground->scaled(settings.currSize, settings.currSize, Qt::KeepAspectRatio);
    painter.drawImage(QPoint(), *imgBackground);

    resize(settings.currSize, settings.currSize);
}
void Conveyor::timerEvent(QTimerEvent* event) {
    Q_UNUSED(event)
        if (event->timerId() == timerIdUpd) {
            updateSettings();
        }
}

/*
void Conveyor::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        // qDebug() << "Conveyor mousePressEvent" ;
        // updateSettings();
    }
}
void Conveyor::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();

    // get the cursor position of this event
    const QPoint& pos = event->pos();

    int pointX = pos.x();
    int pointY = pos.y();

    settings.startX += pointX;
    settings.startY += pointY;
    //?   updateSettings();
   // emit updateServiceUI();
//qDebug() << "Pump mouseMoveEvent dx:dy" << pointX - mouseStartPointX << pointY - mouseStartPointY ;
}

void Conveyor::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        qDebug() << "Conveyor mouseDoubleClickEvent" ;
        // emit openServicePump();
        //emit openServicePipe();

        WidgetService *serviceForm = new WidgetService();
       // serviceForm->ui.
        serviceForm->show();

    }

}
*/