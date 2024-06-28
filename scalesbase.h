#ifndef SCALESBASE_H
#define SCALESBASE_H

#include "widgetdiagramelement.h"



class ScalesBase : public WidgetDiagramElement {
    Q_OBJECT

public:
    explicit ScalesBase(Global& global, QString name, QWidget* parent = nullptr);

    void updateSettings() override;
    // void setNewPosition(float koef);

protected:
    void    paintEvent(QPaintEvent* event) override;
    void    timerEvent(QTimerEvent* event) override;

private:
    QImage* imgBackground;
    int att = 360;
    //int timerIdUpd = 0;
    QColor  triangColor = Qt::blue;
};

#endif // SCALESBASE_H
