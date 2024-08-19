#ifndef TVERTNE_H
#define TVERTNE_H

#include "widgetdiagramelement.h"

class Tvertne : public WidgetDiagramElement {
    Q_OBJECT
public:
    Tvertne(Global& global, QString name, QWidget* parent = nullptr);



protected:
    void    paintEvent(QPaintEvent* event) override;
    void    timerEvent(QTimerEvent* event) override;
    void updateSettings() override;
    //   void    mousePressEvent(QMouseEvent *event) override;
    //   void    mouseMoveEvent (QMouseEvent *event) override;
    //    void    mouseDoubleClickEvent(QMouseEvent *event) override;
    //     void setNewPosition(float koef) ;
private:
    QImage* imgBackground;

    int fill;
    bool full;

    int testtim = 0;
    int test1 = 0;


};

#endif // TVERTNE_H
