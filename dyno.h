#ifndef DYNO_H
#define DYNO_H

#include "widgetdiagramelement.h"


class Dyno : public WidgetDiagramElement
{
    Q_OBJECT
public:
    Dyno(Global &global,QString name, QWidget *parent = nullptr);
protected:
    void    paintEvent(QPaintEvent *event) override;
    void    timerEvent(QTimerEvent *event) override;
    void    updateSettings() override;
    //   void    mousePressEvent(QMouseEvent *event) override;
    //   void    mouseMoveEvent (QMouseEvent *event) override;
    //    void    mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    QImage *imgBackground;

};

#endif // DYNO_H
