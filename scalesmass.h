#ifndef SCALESMASS_H
#define SCALESMASS_H

#include "widgetdiagramelement.h"

class ScalesMass : public WidgetDiagramElement {
    Q_OBJECT

public:
    explicit ScalesMass(Global& global, QString name, QWidget* parent = nullptr);
    void updateSettings() override;

protected:
    void    paintEvent(QPaintEvent* event) override;
    void    timerEvent(QTimerEvent* event)override;

private:
    QImage* imgBackground;
    int att = 360;
    //int timerIdUpd = 0;
    QColor  triangColor = Qt::blue;
    float massValue = 0;
};

#endif // SCALESMASS_H
