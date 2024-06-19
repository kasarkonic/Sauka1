#include "widgetdiagramelement.h"
#include<QMouseEvent>
#include "widgetservice.h"
//#include "global.h"

WidgetDiagramElement::WidgetDiagramElement(Global &global,QString name, QWidget *parent)
    : QWidget{parent}
    , global(global)

{
    settings.name = name;
    settings.type = global.widHash[name].type;

    updateSettings();

}
/*
void WidgetDiagramElement::setNewPosition(float koef)
{
 //    qDebug() << "WidgetDiagramElement 1::setNewPosition()" <<settings.name << global.zoomKoef<<settings.startX<<settings.startY<<
//    settings.currX<<settings.currY << koef ;
//    settings.currX = global.widHash[settings.name].startX/koef;
 //   settings.currY = global.widHash[settings.name].startY/koef;
 //   settings.currSize = global.widHash[settings.name].startSize/koef;
 //   settings.options = global.widHash[settings.name].options;
 //   qDebug() << "WidgetDiagramElement 2::setNewPosition()" <<settings.name << global.zoomKoef<<settings.startX<<settings.startY<<
 //   settings.currX<<settings.currY << koef ;

    move(settings.currX,settings.currY);
    //repaint();
    //resize(settings.currSize,settings.currSize);

  //  updateSettings();

}
*/
void WidgetDiagramElement::updateSettings()
{
   // qDebug() << "WidgetDiagramElement::updateSettings()";

    float koef = global.zoomKoefPf1;

    settings.startX = global.widHash[settings.name].startX;
    settings.startY = global.widHash[settings.name].startY;
    settings.startSize = global.widHash[settings.name].startSize;
    settings.options = global.widHash[settings.name].options;
    settings.act_Addres1 = global.widHash[settings.name].act_Addres1;
    settings.sensAddres1 = global.widHash[settings.name].sensAddres1;
    settings.sensAddres2 = global.widHash[settings.name].sensAddres2;
    settings.currSize = settings.startSize;        //Hi
    settings.currSizeWi = settings.startSizeWi;

    settings.currX = global.widHash[settings.name].startX/koef;
    settings.currY = global.widHash[settings.name].startY/koef;
    settings.currSize = global.widHash[settings.name].startSize/koef;

     // setNewPosition(koef);
    move(settings.currX,settings.currY);
}

void WidgetDiagramElement::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED (event)
    qDebug() << "WidgetDiagramElement::mouseDoubleClickEvent ws:" << settings.name << settings.type ;


    if(!global.widHash[settings.name].ptrCurrWidgetService){
        //global.widHash[settings.name].formExist = true;
        WidgetService *serviceForm = new WidgetService(global, this );
        serviceForm->show();
    }
    else{
        qDebug() << "UI form " << settings.name << " exist";

        global.widHash[settings.name].ptrCurrWidgetService->raise();
        global.widHash[settings.name].ptrCurrWidgetService->activateWindow();
    }
}

void WidgetDiagramElement::timerEvent(QTimerEvent *event)
{
    Q_UNUSED (event);
    //qDebug() << "WidgetDiagramElement::timerEvent";
}



void WidgetDiagramElement::resizeEvent(QResizeEvent *event)
{
    qDebug() << "WidgetDiagramElement::resizeEvent" << global.getTick();
    Q_UNUSED (event);


    if(global.widHash[settings.name].page == 1){
        qDebug() << "setNewPosition 1 " << global.widHash[settings.name].name << zoomKoefPf1old <<global.zoomKoefPf1;
       if( (int)(1000 * zoomKoefPf1old ) != (int)(1000 * global.zoomKoefPf1) ){
            //setNewPosition(global.zoomKoefPf1);
            move(settings.currX,settings.currY);
            zoomKoefPf1old = global.zoomKoefPf1;
    }

    }
    if(global.widHash[settings.name].page == 2){
        qDebug() << "setNewPosition 2 " << global.widHash[settings.name].name << global.zoomKoefPf2;
        if( (int)(1000 * zoomKoefPf2old) != (int)(1000 * global.zoomKoefPf2)){
           // setNewPosition(global.zoomKoefPf2);
            move(settings.currX,settings.currY);
            zoomKoefPf2old = global.zoomKoefPf2;
        }
    }
}


