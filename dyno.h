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

 //   void    mousePressEvent(QMouseEvent *event) override;
 //   void    mouseMoveEvent (QMouseEvent *event) override;
//    void    mouseDoubleClickEvent(QMouseEvent *event) override;

 // void setNewPosition(float koef) ;
  //    void updateSettings() override;

private:
    QImage *imgBackground;
   // Global &global;


};

#endif // DYNO_H
