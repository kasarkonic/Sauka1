#include "widgetdiagramelement.h"
#include<QMouseEvent>
#include "widgetservice.h"
#include "global.h"

WidgetDiagramElement::WidgetDiagramElement(Global &global,QString name, QWidget *parent)
    : QWidget{parent}
    , global(global)

{
    settings.name = name;
 //   global.widHash[settings.name].ptrCurrWidget = this;
}

void WidgetDiagramElement::setNewPosition(float koef)
{
    // qDebug() << "WidgetDiagramElement 1::setNewPosition()" <<settings.name << global.zoomKoef<<settings.startX<<settings.startY<<
    // settings.currX<<settings.currY  ;
    settings.currX = int((float)settings.startX /koef);
    settings.currY = int((float)settings.startY / koef);
    settings.currSize = int ((float)settings.startSize/koef);
    settings.options = global.widHash[settings.name].options;
    qDebug() << "WidgetDiagramElement 2::setNewPosition()" <<settings.name << global.zoomKoef<<settings.startX<<settings.startY<<
        settings.currX<<settings.currY << koef ;
    move(settings.currX,settings.currY);
  //  resize(settings.currSize,settings.currSize);

  //  updateSettings();
}

void WidgetDiagramElement::updateSettings()
{

    float koef = global.zoomKoef;
    addresAct1 = global.widHash[settings.name].act_Addres1;
    if(addresAct1 >= 300){
        addresAct1 -= 300;
    }
    addresAct2 = global.widHash[settings.name].act_Addres2;
    if(addresAct2 >= 300){
        addresAct2 -= 300;
    }
   // int addresAN1 = global.widHash[settings.name].sensAddres1;
   // int addresAN2 = global.widHash[settings.name].sensAddres2;
   // int actValueDi = global.actList[addresAct].digital;
    //int an1Value = global.sensList[addresAN1].analog;
    //int an2Value = global.sensList[addresAN2].analog;

    //qDebug() <<settings.name << ":updateSettings()" <<global.widHash[settings.name].startX << global.widHash[settings.name].startY ;
   // qDebug() <<settings.name << ":" <<addresAct << actValueDi;
   // qDebug() <<settings.name << ":" <<addresAN1 << global.sensList[addresAN1].analog  << ":" <<addresAN2 << global.sensList[addresAN2].analog << "\n";

    settings.currX = global.widHash[settings.name].startX/koef;
    settings.currY = global.widHash[settings.name].startY/koef;
    settings.currSize = global.widHash[settings.name].startSize/koef;
    settings.options = global.widHash[settings.name].options;

    //move(settings.currX,settings.currY);
    //resize(settings.currSize,settings.currSize);
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
    qDebug() << "WidgetDiagramElement::timerEvent";
}

void WidgetDiagramElement::resizeEvent(QResizeEvent *event)
{
     qDebug() << "WidgetDiagramElement::resizeEvent";
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
        qDebug() << "setNewPosition 1 " << global.widHash[settings.name].name <<global.zoomKoefPf1;
       setNewPosition(global.zoomKoefPf1);

    }
    if(global.widHash[settings.name].page == 1){
        qDebug() << "setNewPosition 2 " << global.widHash[settings.name].name << global.zoomKoefPf2;
       setNewPosition(global.zoomKoefPf2);
    }

}


