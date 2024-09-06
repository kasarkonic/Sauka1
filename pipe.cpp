#include "pipe.h"


Pipe::Pipe(Global& global, QString name, QWidget* parent)
    : WidgetDiagramElement(global, name, parent)

{
    global.widHash[settings.name].ptrCurrWidget = this;
    /**/
   // qDebug() << "Pipe::Pipe";
#ifdef ENABLE_WIDGET_SIZE
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::lightGray);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
#endif
    angle = settings.var1;

    timerIdUpd = startTimer(500, Qt::CoarseTimer);  // only for widgetervice position addjust

}

void Pipe::get(int* pnt) {
    int po = 123;
    *pnt = po;
}


void Pipe::updateSettings() {
    // qDebug() << "Pipe updateSettings" << settings.name << settings.npk <<  global.getTick();
    WidgetDiagramElement::updateSettings();
    killTimer(timerIdUpd);

   // qDebug() << "Pipe" << settings.name << global.DIoutput[settings.var2].value;
    if(global.DIoutput[settings.var2].value == 0){ // not move arrow
        timerIdUpd = startTimer(250, Qt::CoarseTimer); // not rotate
    }
    if(global.DIoutput[settings.var2].value == 1){ // arrow move right
        timerIdUpd = startTimer(100, Qt::CoarseTimer); // not rotate
        att +=2;
        if (att > settings.currSize - 10){
            att = -10;
        }
    }

    if(global.DIoutput[settings.var2].value == 2){ // arrow move left
        timerIdUpd = startTimer(100, Qt::CoarseTimer); // not rotate
        att -=2;
        if (att <  - 10){
            att = settings.currSize + 10;
        }
    }
    update();
}


void Pipe::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    //QString currentTime = QTime::currentTime().toString("ms");
   // qDebug() << "Pipe::paintEvent" << settings.name <<settings.var1 << settings.var2 << global.DIoutput[settings.var2].value;
    QPainter painter(this);
    QPen pen;
    pen.setWidth(2);    //draw pipe
    pen.setColor(pipeColorFront);       //(Qt::black);
    //  if(settings.options == 1){
    //      painter.setBrush(pipeColorRear);// (pipeColour);
    //      settings.options = 0;
     // }
     // else{
    painter.setBrush(pipeColorFront);
    // }

    painter.setPen(pen);

    //  pen.setWidth(2);    //draw pipe
    //  pen.setColor(Qt::red);
    //  painter.setRenderHint(QPainter::Antialiasing);
    //  painter.setPen(pen);

     // updateSettings();
      // arrow points

    int stX = 0;
    int stY = 0;

    int hi = settings.currSize;        //Hi
    int wi = settings.currSizeWi;



    settings.var1 %= 360;
    float an = settings.var1 * M_PI / 180;
    float SinAN = sin(an);
    float CosAN = cos(an);

    if (settings.var1 >= 0 && settings.var1 <= 90) {
        stY = wi * SinAN;
        stX = 0;
        // resize(wi * cos(an) + hi * sin(an),hi * cos(an)  + wi * sin(an));
    }
    if (settings.var1 > 90 && settings.var1 <= 180) {
        stX = wi * sin(an - M_PI / 2);
        stY = hi * cos(M_PI - an) + wi * cos(an - M_PI / 2);
        // resize(wi * sin(an-M_PI/2) + hi * cos(an-M_PI/2),stY);
    }
    if (settings.var1 > 180 && settings.var1 <= 270) {
        stX = hi * sin(an - M_PI) + wi * cos(an - M_PI);
        stY = settings.startY = hi * cos(an - M_PI);
        // resize(stX ,hi * cos(an - M_PI) + wi * sin(an-M_PI));
    }
    if (settings.var1 > 270 && settings.var1 <= 360) {
        stX = hi * cos(an - 3 * M_PI / 2);
        stY = 0;
        // resize(stX +  wi * sin( an - 3*M_PI/2) , diog * cos( 2* M_PI - (an + diogAngle) ));
    }

    pipePoints[0].setX(stX);        //left upper corner
    pipePoints[0].setY(stY);

    pipePoints[1].setX(stX + wi * CosAN); // right upper corner
    pipePoints[1].setY(stY - wi * SinAN);

    pipePoints[2].setX(stX + hi * SinAN + wi * CosAN);
    pipePoints[2].setY(stY + hi * CosAN - wi * SinAN);//  max size Y

    pipePoints[3].setX(stX + hi * SinAN);
    pipePoints[3].setY(stY + hi * CosAN);


    painter.drawPolygon(pipePoints, 4, Qt::WindingFill);


        //pipe virtual middle line

        pipemiddle[0].setX(stX + wi * CosAN/2);
        pipemiddle[0].setY(stY - wi * SinAN/2);

        pipemiddle[1].setX(stX + hi * SinAN + wi * CosAN/2 );
        pipemiddle[1].setY(stY + hi * CosAN - wi * SinAN/2 );

        pen.setWidth(1);    //draw pipe
        pen.setColor(pipeColorFront); //(Qt::black);
        painter.setPen(pen);
        painter.drawLines(pipemiddle,1);


            if(global.DIoutput[settings.var2].value != 0)
            {
                //draw arrow

                pipemiddle[0].setX(stX + wi * CosAN/2);
                pipemiddle[0].setY(stY - wi * SinAN/2);


                arrowPoints[0].setX(pipePoints[0].x() + att * SinAN  );
                arrowPoints[0].setY(pipePoints[0].y() + att * CosAN  );

                arrowPoints[1].setX(pipemiddle[0].x() + (att + arrTop) * SinAN  );
                arrowPoints[1].setY(pipemiddle[0].y() + (att + arrTop) * CosAN  );

                arrowPoints[2] = arrowPoints[1];
                arrowPoints[2] = arrowPoints[1];

                arrowPoints[3].setX(pipePoints[1].x() + att * SinAN  );
                arrowPoints[3].setY(pipePoints[1].y() + att * CosAN  );


                pen.setWidth(20);    //draw arrow
                pen.setColor(Qt::black);
                pen.setCapStyle(Qt::RoundCap);  //Qt::FlatCap   Qt::RoundCap
                painter.setPen(pen);
                painter.drawLines(arrowPoints,2);


            }


    resize(wi + settings.currSize * sin(an), stY + hi * cos(an));

}
void Pipe::timerEvent(QTimerEvent* event) {

    Q_UNUSED(event);

    updateSettings();
}

