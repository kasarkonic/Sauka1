#ifndef WIDGETDIAGRAMELEMENT_H
#define WIDGETDIAGRAMELEMENT_H

#include <QWidget>
#include"global.h"
#include<QMouseEvent>

#include <QPainter>
#include <QPixmap>

class WidgetDiagramElement : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetDiagramElement( Global &global, QString name, QWidget *parent = nullptr);
    virtual void updateSettings();
    Global &global;

    struct  widDataStruct{
        int type = 4; // Dyno
        QString name = "";

        int startX = 100;
        int startY = 100;
        int startSize = 100;
        int startSizeWi = 10;

        //valve |- angle
        // pipe angle
        int options = 0;

        // līmenis, ātrums
        int value = 0;

        // tvertne gala slēdzis
        //pārējie on/off/??
        int status = 0;

        int currX = 0;
        int currY = 0;
        int currSize = 0;
        int currSizeWi = 0;

    } settings;

protected:
   // void    mousePressEvent(QMouseEvent *event) override;
    //void    mouseMoveEvent (QMouseEvent *event) override;
    void    mouseDoubleClickEvent(QMouseEvent *event) override;
    void    timerEvent(QTimerEvent *event) override;
    void    resizeEvent(QResizeEvent* event) override ;
   // Global &global;
    void setNewPosition(float koef);
   //virtual void updateSettings();
    QString widName;

    int addresAct1;
    int addresAct2;

    int timerIdUpd = 0;

private:
   // Global &global;
    int timerId = 0;
    int att = 100;
    float zoomKoefPf1old = 0;
    float zoomKoefPf2old = 0;

};




#endif // WIDGETDIAGRAMELEMENT_H
