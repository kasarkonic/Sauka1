#ifndef CONVEYOR_H
#define CONVEYOR_H

#include "widgetdiagramelement.h"


class Conveyor : public WidgetDiagramElement {
    Q_OBJECT
public:
    Conveyor(Global& global, QString name, QWidget* parent = nullptr);
protected:
    void    paintEvent(QPaintEvent* event) override;
    void    timerEvent(QTimerEvent* event) override;
    void    updateSettings() override;
    //   void    mousePressEvent(QMouseEvent *event) override;
    //   void    mouseMoveEvent (QMouseEvent *event) override;
    //    void    mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    QImage* imgBackground;

};



#endif // CONVEYOR_H
