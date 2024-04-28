#include "scalesbase.h"

ScalesBase::ScalesBase(Global &global, QString name, QWidget *parent)
    : WidgetDiagramElement(global,name,parent)
{

    global.widHash[settings.name].ptrCurrWidget = this;
    /*
    settings.startX = global.widHash[settings.name].startX;
    settings.startY = global.widHash[settings.name].startY;
    settings.startSize = global.widHash[settings.name].startSize;
    settings.startSizeWi = global.widHash[settings.name].startSizeWi;
    settings.currSize = settings.startSize;        //Hi
    settings.currSizeWi = settings.startSizeWi;
    */

//*
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::lightGray); //QColor(255, 0, 0, 127)
    pal.setColor(QPalette::Window, QColor(0, 0, 0, 20));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
//*/
    widName = name;
    timerIdUpd = startTimer(500, Qt::CoarseTimer);  // only for widgetervice position addjust

}

void ScalesBase::updateSettings()
{
    WidgetDiagramElement::updateSettings(); // base class
    //repaint();
    update();
}
/*
void ScalesBase::setNewPosition(float koef)
{
    WidgetDiagramElement::setNewPosition(koef); // call base class
    settings.currSize = int(settings.startSize /koef);        //Hi
    settings.currSizeWi = int(settings.startSizeWi /koef);
    //   qDebug() << "Pipe::setNewPosition";
}
*/
void ScalesBase::paintEvent(QPaintEvent *event)
{
    Q_UNUSED (event);

    // qDebug() << "ScalesBase"<<settings.name <<settings.currX << settings.currY << settings.currSize<<"\n" ;

    QPainter painter(this);
    QPen pen;
    pen.setWidth(2);    //draw pipe
    pen.setColor(Qt::black);
    painter.setBrush(Qt::cyan);
    painter.setPen(pen);


    QPoint points[4];


    int stX = 0;
    int stY = 0;

    int hi = settings.currSize;        //Hi
    int wi = settings.currSizeWi;

   //qDebug() << stX << stY << hi << wi;

    points[0] = QPoint(stX, stY);
    points[1] = QPoint(stX + hi, stY);
    points[2] = QPoint(stX + hi, stY + wi/2);
    points[3] = QPoint(stX, stY + wi/2);

    painter.drawPolygon(points,4);


    points[0] = QPoint(stX + hi/2, stY + wi/2);
    points[1] = QPoint(stX + hi/2 + wi, stY + wi + wi);
    points[2] = QPoint(stX + hi/2 - wi, stY + wi + wi);

    pen.setWidth(2);
    pen.setColor(Qt::black);
    painter.setBrush(Qt::cyan);
    painter.setPen(pen);
    painter.drawPolygon(points,3);



/*
    //QPainter painter(this);
    QPen pen1;
    pen1.setWidth(4);    //draw pipe
    pen1.setColor(Qt::red);
    painter.setBrush(Qt::red);
    painter.setPen(pen);

    imgBackground= new QImage();
    imgBackground->load(":/pictures/icons-scales-weightl.png");

    *imgBackground = imgBackground->scaled(settings.currSize, settings.currSize, Qt::KeepAspectRatio);
    painter.drawImage(QPoint(), *imgBackground);
*/
resize(settings.currSize,3 * wi);
}

void ScalesBase::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event)
   // qDebug() << "ScalesBase::timerEvent";
   // if(event->timerId() == timerIdUpd){
    //    update();
    //}
  //  WidgetDiagramElement::updateSettings();
        updateSettings();
}
