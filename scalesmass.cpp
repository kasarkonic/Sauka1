#include "scalesmass.h"
#include "ui_scalesmass.h"

ScalesMass::ScalesMass(Global& global, QString name, QWidget* parent)
    : WidgetDiagramElement(global, name, parent) {
    global.widHash[settings.name].ptrCurrWidget = this;

#ifdef ENABLE_WIDGET_SIZE
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::lightGray); //QColor(255, 0, 0, 127)
    pal.setColor(QPalette::Window, QColor(0, 0, 0, 20));
    this->setAutoFillBackground(true);
    this->setPalette(pal);
#endif

    timerIdUpd = startTimer(100, Qt::CoarseTimer);  // only for widgetervice position addjust
}

void ScalesMass::updateSettings() {
    WidgetDiagramElement::updateSettings(); // base class
    massValue = global.DIinput[settings.var1].value;
    killTimer(timerIdUpd);update();
    timerIdUpd = startTimer(100, Qt::CoarseTimer); // not rotate
    update();
}

void ScalesMass::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    // qDebug() << "MIX paintEvent"<<settings.name <<settings.currX << settings.currY << settings.currSize<<"\n" ;

    QPainter painter(this);
    QPen pen;
    pen.setWidth(4);    //draw pipe
    pen.setColor(Qt::red);
    painter.setBrush(Qt::red);
    painter.setPen(pen);

    imgBackground = new QImage();
    imgBackground->load(":/pictures/kettlebell1.png");

    *imgBackground = imgBackground->scaled(settings.currSize, settings.currSize, Qt::KeepAspectRatio);
    painter.drawImage(QPoint(), *imgBackground);

    QString str = QString::number(massValue);
    // qDebug() << massValue << str;

    QFont font("times", settings.currSize / 6);
    painter.setFont(font);
    // qDebug() << "scalesM = " << settings.name <<settings.currSize << settings.startX << settings.currX << settings.startY << settings.currY;
    painter.drawText(QRect(0, settings.currSize / 6, settings.currSize, settings.currSize), Qt::AlignCenter, str);
    resize(settings.currSize, settings.currSize);
}

void ScalesMass::timerEvent(QTimerEvent* event) {
    Q_UNUSED(event)
        if (event->timerId() == timerIdUpd) {

            updateSettings();
        }
}
