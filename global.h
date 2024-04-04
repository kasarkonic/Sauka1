#ifndef GLOBAL_H
#define GLOBAL_H



#include "qlineedit.h"
#include "qpushbutton.h"
#include <QObject>
#include <QHash>
#include <QList>



//#include <QTimer>
#define DI_IN_START_ADDRESS 0   // MODBUSS ADDRESS 4  DIinput
#define DI_OUT_START_ADDRESS 0   // MODBUSS ADDRESS 4  DIoutput
#define AN_IN_START_ADDRESS DI_IN_START_ADDRESS + MAX_DIinput // modbuss address 2  ANinput 1-15
#define AN_VIRTUAL_IN_START_ADDRESS AN_IN_START_ADDRESS + MAX_AN_INPUT4_20 // modbuss address 2  ANinput 1-15

#define MAX_DIinput     32      // addres [0 , MAX_DIinp]
#define MAX_DIoutput    32  // addres [100 , MAX_DIoutput + 100]
#define MAX_AN_INPUT4_20 16    // addres [200 , MAX_AN_VIRUAL_INPUT + 200]   200+MAX_AN_VIRUAL_INPUT  a/d input  0-30V
#define MAX_AN_VIRUAL_INPUT 16    // Virtual input copy actuator motor value

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
        SensorType::sensT type = SensorType::sensT::Digital;  // digital 0 -> MAX_DIinput  tad analog MAX_DIinput ->MAX_DIinput + MAX_AN_VIRUAL_INPUT
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

    struct  inOut{
        bool Di = false;
        int An = 0.0;
        QString name = "IN/OUT";
    } ;

    QList<act> actList;
    QList<sens> sensList;
    QHash<QString,wdataStruct> widHash;

    //board input output;
   // QList<inOut>DIinput;
    QList<inOut>DIoutput;
    QList<inOut>ANinput4_20; // value/100 = x,xx(mA)
    int scaleVal;

    bool disableRS485; // for testing
    int getANval(int addres);
    bool getDIval(int addres);
    void setDIval(int addres, bool val);

    QString settingsFileName;
    QString appSwVers;
    float zoomKoef;
    int UIXsize;
    int UIYsize;
    int UIXresizeSize;
    int UIYresizeSize;


    // attach Com. port
    QString dev1;   // rs232 for temperature sensor
    QString dev2;   // rs232 for scale
    QString dev3;   // for RS485 Modbus DI DO An input
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

    void create_IN_OUT_list();
    void creatWidgList();
    void addWidgList(WidgetType::widgT ty, QString na,int X, int Y, int size, int sizeW, int options, int page, int actAdr, int sensAdr1, int sensAdr2);

    void creatActList();
    void addActList(QString name, ActuatorType::actT tp, int addres);

    void creatSensList();
    void addSensList(QString name, SensorType::sensT tp, int addres);


};

#endif // GLOBAL_H
