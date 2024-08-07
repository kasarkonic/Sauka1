#ifndef GLOBAL_H
#define GLOBAL_H



#include "qlineedit.h"
#include "qpushbutton.h"
#include <QObject>
#include <QHash>
#include <QList>
#include "def.h"
#include <QMessageBox>
#include <QElapsedTimer>
#include "ballvalve.h"


/*
#define DI_IN_START_ADDRESS 0   // MODBUSS ADDRESS 4  DIinput
#define DI_OUT_START_ADDRESS 0   // MODBUSS ADDRESS 4  DIoutput
#define AN_IN_START_ADDRESS DI_IN_START_ADDRESS + MAX_DIinput // modbuss address 2  ANinput 1-15
#define AN_VIRTUAL_IN_START_ADDRESS AN_IN_START_ADDRESS + MAX_AN_INPUT4_20 // modbuss address 2  ANinput 1-15

#define VIRUAL_PORTS 16 // Virtual input copy invertor ON/OFF
#define MAX_DIinput     32*3 + VIRUAL_PORTS       // addres [0 , MAX_DIinp] 32*3
#define MAX_DIoutput     32*3 + VIRUAL_PORTS      // addres [0 , MAX_DIinp] + MAX_AN_VIRUAL_INPUT invertor speed, on/off...
#define MAX_ACTUATOR    64  // addres [0 , MAX_DIoutput]
#define MAX_AN_INPUT4_20 16    // addres [200 , MAX_AN_VIRUAL_INPUT + 200]   200+MAX_AN_VIRUAL_INPUT  a/d input  0-30V

*/
class WidgetService;
class WidgetDiagramElement;
class BallValve;

namespace ActuatorType {
enum actT {
    Invertor,
    Relay,
};
}
namespace SensorType {
enum sensT {
    Digital,
    Analog,
};
}


namespace WidgetType {
enum widgT {
    Dyno,
    Mix,
    Pipe,
    Pump,
    Tvertne,
    Valve,
    ScalesBase,
    ScalesMass,
    Dispax,
    Label,
};
}



class Global {

public:
    Global();

    struct  act {
        ActuatorType::actT type = ActuatorType::actT::Relay;  // Dyno
        QString name = "Dyno";
        int address = 0;
        int digital = 0;
        int analog = 0;
        QPushButton* ptrButton = nullptr;
        QLineEdit* ptrLineEdit = nullptr;
    };

    struct  sens {
        SensorType::sensT type = SensorType::sensT::Digital;  // digital 0 -> MAX_DIinput  tad analog MAX_DIinput ->MAX_DIinput + MAX_AN_VIRUAL_INPUT
        QString name = "Sens";
        int address = 0;
        int digital = 2; //VALUE
        int analog = 7; //VALUE
        QLineEdit* ptrLineEditDI = nullptr;
        QLineEdit* ptrLineEditAN = nullptr;
    };
    struct  press_sens {        // pressure sensors
        //int number = 0;     // number 0,1,2,3,...
        int current_val = 0; // current VALUE
        int average_val = 0; //VALUE
        int full_val = 0;
        int empty_val = 0;
        int fill = 0;       // fill %
        QList<int> buf;      // circular buller
        int curr_iter = 0;  // current bufer iterator
        QString name = "";
    };
    QList<press_sens>press_sensList;

    struct  bvalve {
        int npk = 0;
        BallValve* bValvePtr = nullptr;

    };
    QList<bvalve>ballValveList;

    QList <int>tvertneTemp;     // temperatura tvertnēs !!!!!!!!!!!!!!!!!!!


    void createPressSensList();

    struct wdataStruct {
        WidgetType::widgT type;
        QString name = "";
        int npk;
        int page = 0;
        int startX = 100;   // left upp corner
        int startY = 100;   // left upp corner
        int startSize = 50; // dimensions
        // int startSizeWi = 10; // pipe len
        int var1 = 0;   //valve |- and pipe angle
        int var2 = 0;
       // int windowNr = 0;
        bool formExist = false;
        WidgetDiagramElement* ptrCurrWidget = nullptr;
        WidgetService* ptrCurrWidgetService = nullptr;
    };

    struct  updateData {
        bool need = false;  // need uptate
        int row = 0;
        int val = 0;    // data value
    };

    struct inOut {
        int value = 0;
        QString name;
        int update = true;
        int count = 0;
    };

    struct rs485WrPar {
        int boardAdr;
        int cmd;    // 6 write single reg.   3 reead holding reg.
        int regAdr;
        quint16 value;
        int len;
    };

    struct drError_code{
        int code;
        const char *name;
    };


    QList<drError_code>  driveErrorCodes {
        {0x0000,	"[No fault] (NOF)	No fault saved"},
        {0x1000,	"[Precharge] (CRF1)	Precharge"},
        {0x1000,	"[Motor overload] (OLF)	Motor overload fault"},
        {0x1000,	"[Overspeed] (SOF)	Motor overspeed fault"},
        {0x1000,	"[IGBT desaturation] (HDF)	IGBT desaturation"},
        {0x1000,	"[internal- CPU ] (INFE)	internal- CPU"},
        {0x1000,	"[Ch.sw. fault] (CSF)	Channel switching fault"},
        {0x1000,	"[Angle error] (ASF)	Angle error"},

        {0x2230,	"[IGBT short circuit] (SCF4)	IGBT short circuit fault"},
        {0x2310,	"[Overcurrent] (OCF)	Overcurrent fault"},
        {0x2311,	"[Proc.Overload Flt] (OLC)	Process Overload Fault"},
        {0x2320,	"[Motor short circuit] (SCF1)	Motor short circuit"},
        {0x2320,	"[Motor short circuit] (SCF5)	motor short circuit"},
        {0x2330,     "[Ground short circuit] (SCF3)	Ground short circuit"},
        {0x3110,	"[Mains overvoltage] (OSF)	Supply overvoltage fault"},
        {0x3120,	"[Undervoltage] (USF)	Supply undervolt fault"},
        {0x3130,	"[Input phase loss] (PHF)	Supply phase loss fault"},
        {0x3310,	"[Overbraking] (OBF)	DC bus overvoltage fault"},
        {0x3310,	"[1 output phase loss] (OPF1)	1 motor phase loss fault"},
        {0x3310,	"[3out ph loss] (OPF2)	3 motor phase loss fault"},
        {0x4210,	"[Drive overheat] (OHF)	Drive overheating fault"},
        {0x4210,     "[IGBT overheat] (TJF)	IGBT overheat fault"},
        {0x4310,     "[PTC fault] (OTFL)	LI6=PTC overheat fault"},
        {0x5000,	"[Out. contact. stuck] (FCF1)	Output cont close fault"},
        {0x5000,	"[Out. contact. open.] (FCF2)	Output cont open fault"},
        {0x5000,	"[input contactor] (LCF)	input contactor"},
        {0x5210,	"[Internal- I measure] (INF9)	Internal I measure fault"},
        {0x5210,     "[Internal-mains circuit] (INFA)	Internal i/p volt circuit flt"},
        {0x5210,	"[Internal- th. sensor] (INFB)	Internal temperature fault"},
        {0x5530,	"[Control Eeprom] (EEF1)	EEprom control fault"},
        {0x5530,	"[Power Eeprom] (EEF2)	EEprom power fault"},
        {0x6100,	"[Rating error] (INF1)	Rating error"},
        {0x6100,	"[PWR Calib.] (INF2)	Incompatible control card"},
        {0x6100,	"[Int.serial link] (INF3)	Internal coms link fault"},
        {0x6100,	"[Int.Mfg area] (INF4)	Internal manu zone fault"},
        {0x6100,	"[Cards pairing] (HCF)	Cards pairing"},
        {0x6300,	"[Incorrect config.] (CFF)	Incorrect configuration"},
        {0x6300,	"[Invalid config.] (CFI)	Invalid config parameters"},
        {0x6300,	"[Bad conf] (CFI2)	Interrupted config."},
        {0x7000,	"[Internal-option] (INF6)	Internal option fault"},
        {0x7110,	"[Brake feedback] (BRF)	Brake feedback fault"},
        {0x7300,	"[Load slipping] (ANF)	Output speed <> ref"},
        {0x7300,	"[LI6=PTC probe] (PTFL)	LI6=PTC failed"},
        {0x7300,	"[AI3 4-20mA loss] (LFF3)	AI3 4-20mA loss"},
        {0x7310,	"[Speed fdback loss] (SPF)	Speed feedback loss"},
        {0x7400,	"[FB fault] (FBE)	FB fault"},
        {0x7400,	"[FB stop flt.] (FBES)	FB stop fault"},
        {0x7510,	"[Modbus com.] (SLF1)	Modbus coms fault"},
        {0x7510,	"[HMI com.] (SLF3)	HMI coms fault"},
        {0x7520,	"[int. com.link] (ILF)	Com Internal link fault"},
        {0x7520,	"[Com. network] (CNF)	Network fault"},
        {0x7530,	"[PC com.] (SLF2)	PC coms fault"},
        {0x8100,	"[CAN com.] (COF)	Comms fault CANopen"},
        {0x9000,	"[External flt-LI/Bit] (EPF1)	External fault logic input"},
        {0x9000,	"[External fault com.] (EPF2)	External fault comms"},
        {0xFF00,	"[Auto-tuning ] (TNF)	Auto-tuning fault"},
        {0xFF01,	"[Brake control] (BLF)	Brake control fault"},
        {0xFF02,	"[Torque/current lim] (SSF)	Torque/current limit fault"},
        {0xFF03,	"[Pr.Underload.Flt] (ULF)	Process Underlaod Fault"},
        {0xFF03,	"[Safety fault] (SAFF)	Safety fault"},
        {0xFF80,	"[Load fault] (DLF)	Dynamic load fault"}




    };

    QList<rs485WrPar> rs485WrList;

    updateData updateDataIn;
    updateData updateDataOut;

    QList<act> actList;
    QList<sens> sensList;
    QHash<QString, wdataStruct> widHash;

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
    QString dev1;   // rs232 for temperature sensor and level meter
    QString dev2;   // rs232 for scale
    QString dev3;   // for RS485 Modbus DI DO An input
    QString dev4;
    bool dev1ConnectStatus;   // rs232 for temperature sensor and level meter
    bool dev2ConnectStatus;   // rs232 for scale
    bool dev3ConnectStatus;   // for RS485 Modbus DI DO An input
    bool dev4ConnectStatus;
    QString dev1_VendorId;
    QString dev2_VendorId;
    QString dev3_VendorId;
    QString dev4_VendorId;
    QString dev1_description;
    QString dev2_description;
    QString dev3_description;
    QString dev4_description;
    //QString level_description;


    QColor  backgroundColor = QColor(250, 250, 250, 175);   // 255 transparent
    QStringList cardFileName;

    void needUpdateDIoutputs(int row, int val);
    void needUpdateSensorIn(int row, int val);
    int getTick();
    int getnTick();
    //void addTick();
    int getwaitTx();
    void setwaitTx(int val);
    QString    getDriveErrorTxt(int errCode);


    BallValve* ballvalveTest0;
    BallValve* ballvalveTest1;
    BallValve* ballvalveTest2;
    BallValve* ballvalveTest3;
    BallValve* ballvalveTest4;
    BallValve* ballvalveTest5;
    BallValve* ballvalveTest6;
    BallValve* ballvalveTest7;
    BallValve* ballvalveTest8;
    BallValve* ballvalveTest9;
    BallValve* ballvalveTest10;
    BallValve* ballvalveTest11;
    BallValve* ballvalveTest12;
    BallValve* ballvalveTest13;
    BallValve* ballvalveTest14;
    BallValve* ballvalveTest15;
    BallValve* ballvalveTest16;
    BallValve* ballvalveTest17;


private:

    QElapsedTimer tickTimer;
    int tick;
    void create_IN_OUT_list();
    void creatWidgList();
    void addWidgList(WidgetType::widgT ty, int npk, int page, int X, int Y, int size, int var1, int var2);
    void creatActList();
    void addActList(QString name, ActuatorType::actT tp, int addres);

    void creatSensList();
    void addSensList(QString name, SensorType::sensT tp, int addres);

    // 0 bit 23DI 0 board address 4 , data adress 0-31
    // 1 bit 23DI 1 board address 5 , data adress 32-63
    int waitTx;
    void createBallValve();

};

#endif // GLOBAL_H
