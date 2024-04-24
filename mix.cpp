#include "mix.h"



Mix::Mix(Global &global, QString name, QWidget *parent)
    : WidgetDiagramElement(global,name,parent)


{
    global.widHash[settings.name].ptrCurrWidget = this;
    /*
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, QColor(0, 0, 0, 50));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
 */
        widName = name;
    //settings.startX = global.widHash[settings.name].startX;
    //settings.startY = global.widHash[settings.name].startY;
    //settings.startSize = global.widHash[settings.name].startSize;
        timerIdUpd = startTimer(500, Qt::CoarseTimer);  // only for widgetervice position addjust

}

void Mix::updateSettings()
{
    WidgetDiagramElement::updateSettings(); // base class
    //qDebug() << "Mix updateSettings" << settings.options;

    int dSensAdr = global.widHash[widName].sensAddres1;
    speed = (int)global.sensList[dSensAdr].analog /3;

    killTimer(timerIdUpd);
    if(global.sensList[dSensAdr].digital){
        //killTimer(timerIdUpd);
         timerIdUpd = startTimer(150, Qt::CoarseTimer); //rotate
    }
    else{
        //killTimer(timerIdUpd);
        timerIdUpd = startTimer(500, Qt::CoarseTimer);
    }
     repaint();
}
/*
void Mix::setNewPosition(float koef)
{ 
    settings.currX = int((float)settings.startX /koef);
    settings.currY = int((float)settings.startY / koef);
    settings.currSize = int ((float)settings.startSize/koef);
}

*/
void Mix::paintEvent(QPaintEvent *event)
{
    Q_UNUSED (event);

   // qDebug() << "MIX paintEvent"<<settings.name <<settings.currX << settings.currY << settings.currSize<<"\n" ;

    QPainter painter(this);
    QPen pen;
    pen.setWidth(4);    //draw mix
    pen.setColor(Qt::red);
    painter.setBrush(Qt::red);
    painter.setPen(pen);

      imgBackground= new QImage();
      imgBackground->load(":/pictures/mixeris31.png");

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

resize(settings.currSize,settings.currSize);
}

void Mix::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)
     //qDebug() << "Mix::timerEvent";
    if(timerIdUpd){
        int step = (int)speed/10;
        step = speed;
        att += step;
        if (att > 360){
            att = 0;
        }
       // qDebug() << att;
        //update();
      //  updateSettings();
    }
}

/*
void Mix::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
       // qDebug() << "Mix mousePressEvent" ;
       //  updateSettings();
    }
}
void Mix::mouseMoveEvent(QMouseEvent *event)
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

void Mix::mouseDoubleClickEvent(QMouseEvent *event)
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
