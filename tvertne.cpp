#include "tvertne.h"


Tvertne::Tvertne(Global &global, QString name, QWidget *parent)
    : WidgetDiagramElement(global,name,parent)

{
    global.widHash[settings.name].ptrCurrWidget = this;
    widName = name;
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::lightGray); //QColor(255, 0, 0, 127)
    // pal.setColor(QPalette::Window, QColor(100, 100, 100, 255));
    pal.setColor(QPalette::Window, QColor(Qt::red));
    this->setAutoFillBackground(true);

    settings.startX = global.widHash[settings.name].startX;
    settings.startY = global.widHash[settings.name].startY;
    settings.startSize = global.widHash[settings.name].startSize;
    qDebug() << "TVERTNE Name: "<<settings.name <<settings.currX << settings.currY << settings.currSize ;

   // timerIdUpd = startTimer(200, Qt::CoarseTimer);

    fill = 0;
    full = 0;

}

void Tvertne::updateSettings()

{
    //qDebug() << "Tvertne::updateSettings()" << ;
    WidgetDiagramElement::updateSettings();
    int dSensAdr = global.widHash[widName].act_sensAddres;
    if(dSensAdr >= 300){
        dSensAdr -= 300;
    }
    int an1SensAdr = global.widHash[widName].sensAddres1;
    //int an2SensAdr = global.widHash[widName].sensAddres2;

    //fill = (int)global.sensList[an1SensAdr].analog;
    //fill = global.getANval(an1SensAdr);
    //qDebug() << "fill"  << fill << an1SensAdr;

    //int res;
    float fval = global.getANval(an1SensAdr);
    if(fval > 100){
    fill = 10 * qRound(24*100.0/fval);
    qDebug() << "fill"  << fval << an1SensAdr << (24*100.0/fval);
    //fill = res;
    }




    //full = global.sensList[dSensAdr].digital;
    full = global.getDIval(dSensAdr);
    //qDebug() << "Tvertne::updateSettings()" <<widName<<dSensAdr << full<< "----" <<an1SensAdr <<fill << "---" <<an2SensAdr;

    update();
}

void Tvertne::timerEvent(QTimerEvent *event)
{
    Q_UNUSED (event);
    qDebug() << "Tvertne::timerEvent";
    updateSettings();
}


/*
void Tvertne::setNewPosition(float koef)
{
    settings.currX = int(settings.startX /koef);
    settings.currY = int(settings.startY / koef);
    settings.currSize = int (settings.startSize/koef);

    move(settings.currX,settings.currY);
    resize(settings.currSize,settings.currSize);
}

*/
void Tvertne::paintEvent(QPaintEvent *event)
{
    Q_UNUSED (event);

    //qDebug() << "Tvertne paintEvent"<<settings.name <<settings.currX << settings.currY << settings.currSize<<"\n" ;

    QPainter painter(this);
    QPen pen;
    pen.setWidth(5);    //draw pipe
    pen.setColor(Qt::red);
    painter.setBrush(Qt::red);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);

    int b = (int)settings.currSize /10;

    QPoint points[4];

    imgBackground= new QImage();
    imgBackground->load(":/pictures/fxup1.png");

    *imgBackground = imgBackground->scaled(settings.currSize, settings.currSize, Qt::KeepAspectRatio);
    painter.drawImage(QPoint(), *imgBackground);

    // qDebug()<<"full:fill" <<full<<":" << fill;
    if (full){
        painter.drawLine(QPoint(b,b),QPoint(settings.currSize - b, b));
    }



    pen.setWidth(3);
    pen.setColor(Qt::black);
    painter.setPen(pen);

    points[0] = QPoint(b,b);
    points[1] = QPoint(settings.currSize - b, b);
    points[2] = QPoint(settings.currSize - b ,settings.currSize - b);
    points[3] = QPoint(b,settings.currSize -b);

    painter.drawLine(points[1],points[2]);
    painter.drawLine(points[2],points[3]);
    painter.drawLine(points[3],points[0]);

    pen.setWidth(1);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.setBrush(QColor(0, 32, 255, 50));

    int tf = fill * (settings.currSize - 2*b)/100;

    points[0] = QPoint(b,b + tf);
    points[1] = QPoint(settings.currSize - b, b + tf);
    points[2] = QPoint(settings.currSize - b ,settings.currSize - 2*b);
    points[3] = QPoint(b,settings.currSize - 2*b);

    painter.drawPolygon(points,4);


}

/*
void Tvertne::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
       // qDebug() << "Tvertne mousePressEvent" ;
        // updateSettings();
    }
}
void Tvertne::mouseMoveEvent(QMouseEvent *event)
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

void Tvertne::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        qDebug() << "Tvertne mouseDoubleClickEvent" ;
        // emit openServicePump();
        //emit openServicePipe();

     //   WidgetService *serviceForm = new WidgetService();
      //  serviceForm->show();

    }

}
*/
