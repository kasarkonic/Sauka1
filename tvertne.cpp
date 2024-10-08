#include "tvertne.h"
#include <QSettings>


Tvertne::Tvertne(Global& global, QString name, QWidget* parent)
    : WidgetDiagramElement(global, name, parent)

{
    global.widHash[settings.name].ptrCurrWidget = this;

#ifdef ENABLE_WIDGET_SIZE
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::lightGray); //QColor(255, 0, 0, 127)
    pal.setColor(QPalette::Window, QColor(0, 0, 0, 20));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
#endif

    timerIdUpd = startTimer(100, Qt::CoarseTimer);  // only for widgetervice position addjust

    fill = 0;
    full = false;
  //  loadSettings();

}

void Tvertne::updateSettings()

{

    /////////////////////////////////////// only for testing
    /*

    testtim++;

    if(testtim  == 10 && settings.name == "1. Tvertne"){
        testtim = 0;
        test1++;
//--------------
        global.DIinput[TVERTNE1LEVEL].value = test1 * 10 + 20000;
        global.DIinput[TVERTNE1LEVEL].update += global.DIinput[TVERTNE1LEVEL].value;
        global.DIinput[TVERTNE1LEVEL].count ++;

        global.DIinput[TVERTNE1LEVEL].avr =  global.DIinput[TVERTNE1LEVEL].update / global.DIinput[TVERTNE1LEVEL].count;

        if(global.DIinput[TVERTNE1LEVEL].count > 9){
            global.DIinput[TVERTNE1LEVEL].count = 9;
           global.DIinput[TVERTNE1LEVEL].update -= global.DIinput[TVERTNE1LEVEL].avr;
        }

        if(global.DIinput[TVERTNE1KALIBFULL].value <= global.DIinput[TVERTNE1KALIBEMPTY].value){
            global.DIinput[TVERTNE1KALIBFULL].value = global.DIinput[TVERTNE1KALIBEMPTY].value + 1;
            qDebug() <<    " kalib value error !!!!!!!!!!!!! " ;
        }

        int range = global.DIinput[TVERTNE1KALIBFULL].value - global.DIinput[TVERTNE1KALIBEMPTY].value;
        float res = 100.0 * ( global.DIinput[TVERTNE1LEVEL].avr - global.DIinput[TVERTNE1KALIBEMPTY].value)/range;
        if(res > 110){
            res = 110.0;
        }
        global.DIinput[TVERTNE1LEVELPROC].value = (int)res;
//-------------




    qDebug()  << settings.name  <<  " Calibration error more 100% !!!! ";


    //qDebug() <<  "avr" << global.DIinput[TVERTNE1LEVEL].avr << " | " << global.DIinput[TVERTNE1KALIBEMPTY].value <<  " | " << global.DIinput[TVERTNE1KALIBFULL].value ;

        ////
        if(test1 > 10){
            test1 = 0;
        }
    }

*/
    /////////////////////////////////////


    // qDebug() << "Tvertne::updateSettings()" ;
    WidgetDiagramElement::updateSettings();

    int fval = global.DIinput[settings.var1].value; // fill value in %


    // fill = 10 * qRound(24*100.0/fval);
    if (fill > 100)
        fill = 100;
    fill = 100 - fval;
    //qDebug() << "fill"  << fval << settings.sensAddres1 << (24*100.0/fval);

    full = global.DIinput[settings.var2].value < 600;
    //qDebug() << "Tvertne::updateSettings()" <<fill<< "="  <<global.DIinput[settings.sensAddres1].value << full<<"=" <<global.DIinput[settings.sensAddres2].value;

    update();
}

void Tvertne::loadSettings() // move tomainwindows.cpp
{
    int val;
    bool ok;
    QString str;


    QString settingsFile = global.settingsFileName;
    QSettings settings(settingsFile, QSettings::IniFormat);
    settings.beginGroup("Tvertne_calibrate_level_sensor");

    //11111111111
    val = settings.value("TVERTNE1KALIBEMPTY", "").toInt(&ok);


    qDebug() << "settings.value(TVERTNE1KALIBEMPTY)" << val;

    if (!ok) {
        str = QString("Kļūda Init failā TVERTNE1KALIBEMPTY !!!").arg(val);
        qDebug() << str;
        val = 0;
    }
    global.DIinput[TVERTNE1KALIBEMPTY].value = val;

    val = settings.value("TVERTNE1KALIBFULL", "").toInt(&ok);
    if (!ok) {
        str = QString("Kļūda Init failā TVERTNE1KALIBFULL !!!").arg(val);
        qDebug() << str;
        val = 0;
    }
    global.DIinput[TVERTNE1KALIBFULL].value = val;
        //222222222
    val = settings.value("TVERTNE2KALIBEMPTY", "").toInt(&ok);
    if (!ok) {
        str = QString("Kļūda Init failā TVERTNE2KALIBEMPTY !!!").arg(val);
        qDebug() << str;
        val = 0;
    }
    global.DIinput[TVERTNE2KALIBEMPTY].value = val;

    val = settings.value("TVERTNE2KALIBFULL", "").toInt(&ok);
    if (!ok) {
        str = QString("Kļūda Init failā TVERTNE2KALIBFULL !!!").arg(val);
        qDebug() << str;
        val = 0;
    }
    global.DIinput[TVERTNE2KALIBFULL].value = val;

    //33333333
    val = settings.value("TVERTNE3KALIBEMPTY", "").toInt(&ok);
    if (!ok) {
        str = QString("Kļūda Init failā TVERTNE3KALIBEMPTY !!!").arg(val);
        qDebug() << str;
        val = 0;
    }
    global.DIinput[TVERTNE3KALIBEMPTY].value = val;

    val = settings.value("TVERTNE3KALIBFULL", "").toInt(&ok);
    if (!ok) {
        str = QString("Kļūda Init failā TVERTNE3KALIBFULL !!!").arg(val);
        qDebug() << str;
        val = 0;
    }
    global.DIinput[TVERTNE3KALIBFULL].value = val;


    //44444444
    val = settings.value("TVERTNE4KALIBEMPTY", "").toInt(&ok);
    if (!ok) {
        str = QString("Kļūda Init failā TVERTNE4KALIBEMPTY !!!").arg(val);
        qDebug() << str;
        val = 0;
    }
    global.DIinput[TVERTNE4KALIBEMPTY].value = val;

    val = settings.value("TVERTNE4KALIBFULL", "").toInt(&ok);
    if (!ok) {
        str = QString("Kļūda Init failā TVERTNE4KALIBFULL !!!").arg(val);
        qDebug() << str;
        val = 0;
    }
    global.DIinput[TVERTNE4KALIBFULL].value = val;
    //55555555
    val = settings.value("TVERTNE5KALIBEMPTY", "").toInt(&ok);
    if (!ok) {
        str = QString("Kļūda Init failā TVERTNE5KALIBEMPTY !!!").arg(val);
        qDebug() << str;
        val = 0;
    }
    global.DIinput[TVERTNE5KALIBEMPTY].value = val;

    val = settings.value("TVERTNE5KALIBFULL", "").toInt(&ok);
    if (!ok) {
        str = QString("Kļūda Init failā TVERTNE5KALIBFULL !!!").arg(val);
        qDebug() << str;
        val = 0;
    }
    global.DIinput[TVERTNE5KALIBFULL].value = val;
    settings.endGroup();

    qDebug() << "loadSettings() TVERTNE kalib,"
             << global.DIinput[TVERTNE1KALIBEMPTY].value
             << global.DIinput[TVERTNE1KALIBFULL].value
             << global.DIinput[TVERTNE2KALIBEMPTY].value
             << global.DIinput[TVERTNE2KALIBFULL].value
             << global.DIinput[TVERTNE3KALIBEMPTY].value
             << global.DIinput[TVERTNE3KALIBFULL].value
             << global.DIinput[TVERTNE4KALIBEMPTY].value
             << global.DIinput[TVERTNE4KALIBFULL].value
             << global.DIinput[TVERTNE5KALIBEMPTY].value
             << global.DIinput[TVERTNE5KALIBFULL].value
        ;

}

void Tvertne::timerEvent(QTimerEvent* event) {
    Q_UNUSED(event);
    // qDebug() << "Tvertne::timerEvent";
    updateSettings();
}


void Tvertne::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    //qDebug() << "Tvertne paintEvent"<<settings.name <<settings.currX << settings.currY << settings.currSize<<"\n" ;

    QPainter painter(this);
    QPen pen;
    pen.setWidth(5);    //draw pipe
    pen.setColor(Qt::red);
    painter.setBrush(Qt::red);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);

    int b = (int)settings.currSize / 10;

    QPoint points[4];

    imgBackground = new QImage();
    imgBackground->load(":/pictures/fxup1.png");

    *imgBackground = imgBackground->scaled(settings.currSize, settings.currSize, Qt::KeepAspectRatio);
    painter.drawImage(QPoint(), *imgBackground);

    // qDebug()<<"full:fill" <<full<<":" << fill;
    if (full) {
        painter.drawLine(QPoint(b, b), QPoint(settings.currSize - b, b));
    }

    pen.setWidth(3);
    pen.setColor(Qt::black);
    painter.setPen(pen);

    points[0] = QPoint(b, b);
    points[1] = QPoint(settings.currSize - b, b);
    points[2] = QPoint(settings.currSize - b, settings.currSize - b);
    points[3] = QPoint(b, settings.currSize - b);

    painter.drawLine(points[1], points[2]);
    painter.drawLine(points[2], points[3]);
    painter.drawLine(points[3], points[0]);

    pen.setWidth(1);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.setBrush(QColor(0, 32, 255, 50));

    int tf = fill * (settings.currSize - 2 * b) / 100;

    points[0] = QPoint(b, b + tf);
    points[1] = QPoint(settings.currSize - b, b + tf);
    points[2] = QPoint(settings.currSize - b, settings.currSize - 2 * b);
    points[3] = QPoint(b, settings.currSize - 2 * b);

    painter.drawPolygon(points, 4);

    resize(settings.currSize, settings.currSize);
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
