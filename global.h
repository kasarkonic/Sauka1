#ifndef GLOBAL_H
#define GLOBAL_H



#include "qlineedit.h"
#include "qpushbutton.h"
#include <QObject>
#include <QHash>
#include <QList>
#include "def.h"


#define DI_IN_START_ADDRESS 0   // MODBUSS ADDRESS 4  DIinput
#define DI_OUT_START_ADDRESS 0   // MODBUSS ADDRESS 4  DIoutput
#define AN_IN_START_ADDRESS DI_IN_START_ADDRESS + MAX_DIinput // modbuss address 2  ANinput 1-15
#define AN_VIRTUAL_IN_START_ADDRESS AN_IN_START_ADDRESS + MAX_AN_INPUT4_20 // modbuss address 2  ANinput 1-15

#define MAX_AN_VIRUAL_INPUT 16 // Virtual input copy invertor ON/OFF
#define MAX_DIinput     32*3       // addres [0 , MAX_DIinp] 32*3
#define MAX_DIoutput     32*3 + MAX_AN_VIRUAL_INPUT      // addres [0 , MAX_DIinp] + MAX_AN_VIRUAL_INPUT invertor speed, on/off...
#define MAX_ACTUATOR    64  // addres [0 , MAX_DIoutput]
#define MAX_AN_INPUT4_20 16    // addres [200 , MAX_AN_VIRUAL_INPUT + 200]   200+MAX_AN_VIRUAL_INPUT  a/d input  0-30V


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
        QPushButton * ptrButton = nullptr;
        QLineEdit * ptrLineEdit = nullptr;
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
        int page = 0;
        int startX = 100;   // left upp corner
        int startY = 100;   // left upp corner
        int startSize = 50; // dimensions
       // int startSizeWi = 10; // pipe len
        int options = 0;   //valve |- and pipe angle
        int windowNr = 0;
        bool formExist = false;
        WidgetDiagramElement * ptrCurrWidget = nullptr;
        WidgetService * ptrCurrWidgetService = nullptr;

        int act_Addres1 = 0;
       // int act_Addres2 = 0;
        int sensAddres1 = 0;
        int sensAddres2 = 0;

    };

    struct  updateData{
        bool need = false;  // need uptate
        int row = 0;
        int val = 0;    // data value
    } ;
    struct inOut{
      int value;
      QString name;
      bool update;
    };
    updateData updateDataIn;
    updateData updateDataOut;

    QList<act> actList;
    QList<sens> sensList;
    QHash<QString,wdataStruct> widHash;

    //board input output;
    QList<inOut>DIinput;
    QList<inOut>DIoutput;

    /*[0-14] 4-20ma input N4AIB16 board
    [15] voltage value/100 = x,xx(mA) input N4AIB16 board
    [16-48] 4-20ma input N4AIB16 board input 24DIB32 board
    */

    QList<inOut>ANinput4_20; // value/100 = x,xx(mA) [0-14] 4-20ma input N4AIB16 board
    int scaleVal;

    bool disableRS485; // for testing
    int getANval(int addres);
    bool getDIval(int addres);

   // void setDIval(int addres, bool val);

    QString settingsFileName;
    QString appSwVers;
    float zoomKoef;
    int UIXsize;
    int UIYsize;
    int UIXresizeSize;
    int UIYresizeSize;

    float zoomKoefPf1;
    float zoomKoefPf2;
    int UIXsizePf1;
    int UIYsizePf1;
    int UIXresizeSizePf1;
    int UIYresizeSizePf1;


    int UIXsizePf2;
    int UIYsizePf2;
    int UIXresizeSizePf2;
    int UIYresizeSizePf2;



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
    QStringList cardFileName;

    void needUpdateDIoutputs(int row, int val);
    void needUpdateSensorIn(int row, int val);
    int getTick();
    void addTick();
    int getwaitTx();
    void setwaitTx(int val);


private:

    int tick;
    void create_IN_OUT_list();
    void creatWidgList();
    void addWidgList(WidgetType::widgT ty, QString name, int page,int X, int Y, int size,int options, int actAdr1, int sensAdr1, int sensAdr2);
    void creatActList();
    void addActList(QString name, ActuatorType::actT tp, int addres);

    void creatSensList();
    void addSensList(QString name, SensorType::sensT tp, int addres);

    // 0 bit 23DI 0 board address 4 , data adress 0-31
    // 1 bit 23DI 1 board address 5 , data adress 32-63
    int waitTx;

};

#endif // GLOBAL_H
