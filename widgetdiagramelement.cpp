#include "widgetdiagramelement.h"
#include<QMouseEvent>
#include "widgetservice.h"
#include "global.h"

WidgetDiagramElement::WidgetDiagramElement(Global &global,QString name, QWidget *parent)
    : QWidget{parent}
    , global(global)

{
    settings.name = name;
    settings.type = global.widHash[name].type;

    updateSettings();

}

void WidgetDiagramElement::setNewPosition(float koef)
{
     qDebug() << "WidgetDiagramElement 1::setNewPosition()" <<settings.name << global.zoomKoef<<settings.startX<<settings.startY<<
     settings.currX<<settings.currY  ;
    settings.currX = global.widHash[settings.name].startX/koef;
    settings.currY = global.widHash[settings.name].startY/koef;
    settings.currSize = global.widHash[settings.name].startSize/koef;
    settings.options = global.widHash[settings.name].options;
    qDebug() << "WidgetDiagramElement 2::setNewPosition()" <<settings.name << global.zoomKoef<<settings.startX<<settings.startY<<
    settings.currX<<settings.currY << koef ;

    move(settings.currX,settings.currY);
    //repaint();
    //resize(settings.currSize,settings.currSize);

  //  updateSettings();

}

void WidgetDiagramElement::updateSettings()
{

    float koef = global.zoomKoef;

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

/*
    float koefx = 1.0;
    float koefy = 1.0;
    float koef = 1.0;

    if(size().width() > 0 && size().height() > 0){
        koefx =  (float)global.UIXsize/global.UIXresizeSize;
        koefy = (float)global.UIYsize/global.UIYresizeSize;
    }

    if(koefx >= koefy){
        koef = koefx;
    }
    else{
        koef = koefy;
    }

    if(koef == 0){
        koef = 1;
    }
     qDebug() << "resizeEvent UIsize"  << global.UIXsize << global.UIYsize <<size().width()<<size().height()<<koefx <<koefy<<koef;
    global.zoomKoef = koef;
    */


    if(global.widHash[settings.name].page == 0){
        qDebug() << "setNewPosition 1 " << global.widHash[settings.name].name << zoomKoefPf1old <<global.zoomKoefPf1;
       if( (int)(1000 * zoomKoefPf1old ) != (int)(1000 * global.zoomKoefPf1) ){
            setNewPosition(global.zoomKoefPf1);
            zoomKoefPf1old = global.zoomKoefPf1;
    }

    }
    if(global.widHash[settings.name].page == 1){
        qDebug() << "setNewPosition 2 " << global.widHash[settings.name].name << global.zoomKoefPf2;
        if( (int)(1000 * zoomKoefPf2old) != (int)(1000 * global.zoomKoefPf2)){
            setNewPosition(global.zoomKoefPf2);
            zoomKoefPf2old = global.zoomKoefPf2;
        }
    }
}


