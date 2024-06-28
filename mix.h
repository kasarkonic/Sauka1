#ifndef MIX_H
#define MIX_H

#include "widgetdiagramelement.h"


class Mix : public WidgetDiagramElement {
    Q_OBJECT
public:
    Mix(Global& global, QString name, QWidget* parent = nullptr);


protected:
    void    paintEvent(QPaintEvent* event) override;
    void    timerEvent(QTimerEvent* event) override;
    void updateSettings() override;
    // void    mousePressEvent(QMouseEvent *event) override;
    // void    mouseMoveEvent (QMouseEvent *event) override;
    //  void    mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    QImage* imgBackground;
    int att = 360;
    int speed = 0;
    // int timerIdUpd = 0;
    QColor  triangColor = Qt::blue;
};

#endif // MIX_H
