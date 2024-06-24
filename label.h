#ifndef LABEL_H
#define LABEL_H

#include "widgetdiagramelement.h"
class Label : public WidgetDiagramElement
{
    Q_OBJECT
public:
    Label(Global &global,QString name, QWidget *parent = nullptr);


protected:
    void    paintEvent(QPaintEvent *event) override;
    void    timerEvent(QTimerEvent *event) override;
    void updateSettings() override;
    // void    mousePressEvent(QMouseEvent *event) override;
    // void    mouseMoveEvent (QMouseEvent *event) override;
    //  void    mouseDoubleClickEvent(QMouseEvent *event) override;

private:
 QString str;
 int width;
 int height;
 QRect dest;
};
#endif // LABEL_H
