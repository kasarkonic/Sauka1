#ifndef GLOBAL_H
#define GLOBAL_H



#include "qlineedit.h"
#include "qpushbutton.h"
#include <QObject>
#include <QHash>
#include <QList>
//#include <QTimer>


class WidgetService;
class WidgetDiagramElement;
namespace ActuatorType
{
enum actT{
    Invertor,
    Relay,
};
}
namespace SensorType
{
enum sensT{
    Digital,
    Analog,
};
}


namespace WidgetType
{
enum widgT{
    Dyno,
    Mix,
    Pipe,
    Pump,
    Tvertne,
    Valve,
    ScalesBase,
    ScalesMass
};
}

class Global
{

public:
    Global();

    //QTimer *timer;

    struct  act{
        ActuatorType::actT type = ActuatorType::actT::Relay;  // Dyno
        QString name = "Dyno";
        int address = 0;
        int digital = 0;
        int analog = 0;
        QPushButton * ptrLineEditDI = nullptr;
        QLineEdit * ptrLineEditAN = nullptr;
    } ;

    struct  sens{
        SensorType::sensT type = SensorType::sensT::Digital;  //
        QString name = "Sens";
        int address = 0;
        int digital = 2; //VALUE
        int analog = 7; //VALUE
        QLineEdit * ptrLineEditDI = nullptr;
        QLineEdit * ptrLineEditAN = nullptr;
    };

    struct wdataStruct {
        WidgetType::widgT type;
        QString name ;
        int startX = 100;
        int startY = 100;
        int startSize = 50;
        int startSizeWi = 10;
        int options = 0;   //valve |- and pipe angle      
        int windowNr = 0;
        bool formExist = false;
        WidgetDiagramElement * ptrCurrWidget = nullptr;
        WidgetService * ptrCurrWidgetService = nullptr;
        int page = 0;
        int act_sensAddres = 0;
        int sensAddres1 = 0;
        int sensAddres2 = 0;

    };

    QList<act> actList;
    QList<sens> sensList;
    QHash<QString,wdataStruct> widHash;

    QString settingsFileName;
    QString appSwVers;
    float zoomKoef;
    int UIXsize;
    int UIYsize;
    int UIXresizeSize;
    int UIYresizeSize;


    // attach Com. port
    QString dev1;
    QString dev2;
    QString dev3;
    QString dev4;
    QString dev1_VendorId;
    QString dev2_VendorId;
    QString dev3_VendorId;
    QString dev4_VendorId;
    QString dev1_description;
    QString dev2_description;
    QString dev3_description;
    QString dev4_description;


    QColor  backgroundColor = QColor(250, 250, 250, 175);   // 255 transparent

private:

    void creatWidgList();
    void addWidgList(WidgetType::widgT ty, QString na,int X, int Y, int size, int sizeW, int options, int page, int actAdr, int sensAdr1, int sensAdr2);

    void creatActList();
    void addActList(QString name, ActuatorType::actT tp, int addres);

    void creatSensList();
    void addSensList(QString name, SensorType::sensT tp, int addres);


};

#endif // GLOBAL_H
