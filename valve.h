#ifndef VALVE_H
#define VALVE_H

//#include <QObject>
//#include <QWidget>
#include "widgetdiagramelement.h"


namespace ValveStatus
{
enum{
    Close,  // 0
    OpenBA,
    OpenBC,
    OpenAC,
    Open_BA,
    Open_BC,
    Open_BB,
    OpenABC_B,
    OPENABC,
    Unknown,
};
}


class Valve : public WidgetDiagramElement
{
    Q_OBJECT
public:
    Valve(Global &global,QString name, QWidget *parent = nullptr);
    // void saveSettings();
    // void loadSettings();

    // void setStartParam(QPoint dimA, QPoint dimC,QPoint pos);



    //void setNewPosition(float koef);
    void updateSettings() override;

signals:
    // void openServiceValve();

protected:
    void    paintEvent(QPaintEvent *event) override;
    void    timerEvent(QTimerEvent *event) override;
    void    updateWidget();

private:
    int angle;

    void updateStatus();
    //int  timerIdUpd = 0;
    int att = 0;

    QPoint points[4];
    void calcPoints(int angle);
    // QColor color = Qt::yellow;;

};

#endif // VALVE_H
