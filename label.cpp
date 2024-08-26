#include "label.h"

Label::Label(Global& global, QString name, QWidget* parent)
    : WidgetDiagramElement(global, name, parent) {
    global.widHash[settings.name].ptrCurrWidget = this;
    //*
#ifdef ENABLE_WIDGET_SIZE
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, QColor(0, 0, 0, 50));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
#endif

    timerIdUpd = startTimer(200, Qt::CoarseTimer);  // only for widgetervice position addjust

}

void Label::updateSettings() {
    WidgetDiagramElement::updateSettings(); // base class
    // qDebug() << "Mix updateSettings" << settings.currX << settings.currY << settings.act_Addres1<< global.getTick();

    killTimer(timerIdUpd);
    timerIdUpd = startTimer(200, Qt::CoarseTimer); // not rotate

    update();
}

void Label::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    //qDebug() << "MIX paintEvent"<<settings.name <<settings.currX << settings.currY << settings.currSize<<"\n" ;

    QPainter painter(this);
    QPen pen;
    pen.setWidth(4);    //draw mix
    pen.setColor(Qt::red);
    painter.setBrush(Qt::red);
    painter.setPen(pen);

    QFont bold("Verdana", 16);
    bold.setBold(false);
    painter.setFont(bold);

    width = 0;
    height = 0;
    dest = QRect(0, 0, width, height);
    str = "l";



    switch (settings.npk) {
    case 0:
        width = 100;
        height = 45;
        dest = QRect(0, 0, width, height);
        str = "Uz dinamill";
        break;
    case 1:
        width = 150;
        height = 20;
        dest = QRect(0, 0, width, height);
        str = "Iztukšošana";
        break;
    case 2:
        width = 150;
        height = 20;
        dest = QRect(0, 0, width, height);
        str = "Komponentes";
        break;

    case 3:
        width = 100;
        height = 45;
        dest = QRect(0, 0, width, height);
        str = "Uz dinamill";
        break;
    case 4:
        width = 150;
        height = 20;
        dest = QRect(0, 0, width, height);
        str = "H2o";
        break;
    case 5:
        width = 150;
        height = 20;
        dest = QRect(0, 0, width, height);
        str = "B";
        break;
    case 6:
        width = 150;
        height = 20;
        dest = QRect(0, 0, width, height);
        str = "Na";
        break;
    case 7:
        width = 150;
        height = 30;
        dest = QRect(0, 0, width, height);
        str = "Mazgāšana";
        break;
    case 8:
        width = 150;
        height = 20;
        dest = QRect(0, 0, width, height);
        str = "Dozēšana";
        break;
    case 9:
        width = 150;
        height = 50;
        dest = QRect(0, 0, width, height);
        str = "Sausās komponentes";
        break;
    case 10:
        width = 150;
        height = 25;
        dest = QRect(0, 0, width, height);
        str = "Sapropelis";
        break;
    case 11:
        width = 150;
        height = 20;
        dest = QRect(0, 0, width, height);
        str = "Uz reaktoru";
        break;



    default:
        break;
    }



    painter.drawText(dest, Qt::TextWordWrap | Qt::AlignCenter, str);

    resize(width, height);
}

void Label::timerEvent(QTimerEvent* event) {
    Q_UNUSED(event)
        if (event->timerId() == timerIdUpd) {
            updateSettings();
        }
}

/*
void Label::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
       // qDebug() << "Mix mousePressEvent" ;
       //  updateSettings();
    }
}
void Label::mouseMoveEvent(QMouseEvent *event)
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

void Label::mouseDoubleClickEvent(QMouseEvent *event)
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

