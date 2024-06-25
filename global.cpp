#include "global.h"
#include <Qdebug>
#include <QTimer>



//using namespace inputWidg;
//using namespace inputAct;
//using namespace inputSens;

Global::Global()
{
    appSwVers = "0.1 08.02.2024";
    zoomKoef = zoomKoefPf1 = zoomKoefPf2 = 1.0;
    UIXsize = UIXsizePf1 = UIXsizePf2 = 1000;
    UIYsize = UIYsizePf1 = UIYsizePf2 = 1000;
    UIXresizeSize = UIXresizeSizePf1 = UIXresizeSizePf2 = 1000;
    UIYresizeSize = UIYresizeSizePf1 = UIYresizeSizePf2 = 1000;

    dev1 = "";
    dev2 = "";
    dev3 = "";
    dev4 = "";
    // dev1_VendorId = "";
    // dev2_VendorId = "";
    // dev3_VendorId = "";
    // dev4_VendorId = "";


    sens sdata;
    act  sact;


    //#define MAX_DIinput     32      // addres [0 , MAX_DIinp]
    //#define MAX_ACTUATOR    64  // addres [100 , MAX_DIoutput + 100]
    //#define MAX_AN_INPUT4_20 16    // addres [200 , MAX_AN_VIRUAL_INPUT + 200]   200+MAX_AN_VIRUAL_INPUT  a/d input  0-30V
    //#define MAX_AN_VIRUAL_INPUT 16    // Virtual input copy actuator motor value

    inOut io;
    io.value = 0;
    io.update = false;
    QString nam = " Ain";

    for(int iter = 0; iter <= MAX_AN_INPUT4_20+1; iter++){// +1 for voltage inputs

        io.name = QString::number(iter);
        io.name.append(nam);
        ANinput4_20.append(io);
    }
    nam = " Din";
    for(int iter = 0; iter < MAX_DIinput; iter++){
        io.name = QString::number(iter);
        io.name.append(nam);
        DIinput.append(io);
    }
    nam = " Dout";
    for(int iter = 0; iter < MAX_DIoutput; iter++){
        io.name = QString::number(iter);
        io.name.append(nam);
        DIoutput.append(io);
    }


    for(int i=0 ; i<64;i++){    // 255= max sensor, max activator
        sensList.append(sdata);
        //    actList.append(sact);
    }
    qDebug()  << sensList.size()<<actList.size();


    creatWidgList();

    creatActList();
    qDebug()  << "!!! test act name ";
    creatSensList();
    qDebug()  << "!!! test sensor name ";

    //foreach(sens item,  sensList){
    //    qDebug() << item.name << item.type ;
    //}
    disableRS485 = false;   // for testing
    create_IN_OUT_list();

    tick = 0;
    waitTx = 0;
}

//QList<bool>DIinput;
//QList<bool>DIoutput;
//QList<int>ANinput4_20;   mA  // value/100 = x,xx(A)

int Global::getANval(int addres)
{
    int val = 0;
    int addr = addres - 200;
    if(addr >= 0 && addr < MAX_AN_INPUT4_20 ){
        val = sensList[addr].analog;
    }
    return val;
}

bool Global::getDIval(int addres)
{
    bool val = 0;

    if (addres >= 0  && addres < MAX_DIinput){
        //val = DIinput[addres].Di;
        val = sensList[addres].digital;
    }
    return val;
}

/*
void Global::setDIval(int addres, bool val)
{
    bool value = val;
    if (addres >= 100  && addres < 100 + MAX_DIinput){
       value = 0;
    }
    DIoutput[addres - 100].Di = value;
}
*/
void Global::create_IN_OUT_list()
{
    act actuat;
    actuat.analog = 0;
    actuat.digital = false;


    sens sen;

    sen.type = SensorType::sensT::Digital;  // digital 0 -> MAX_DIinput  tad analog MAX_DIinput ->MAX_DIinput + MAX_AN_VIRUAL_INPUT
    //sen.name = "DI in";
    //int address = 0;
    sen.digital =0; //VALUE
    sen.analog = 0; //VALUE
    sen.ptrLineEditDI = nullptr;
    sen.ptrLineEditAN = nullptr;


    for(int i = 0; i < MAX_ACTUATOR; i++){
        actuat.name = (QString::number(i));
        actuat.name.append(". Act. output");
        actList.append(actuat);
    }

    // io.An = 0.0;
    //io.Di = false;
    sen.type = SensorType::sensT::Analog;  // digital 0 -> MAX_DIinput  tad analog MAX_DIinput ->MAX_DIinput + MAX_AN_VIRUAL_INPUT


    for(int i = 0; i < MAX_AN_INPUT4_20; i++){
        //io.name = (QString::number(i));
        //io.name.append(". An input");
        //ANinput4_20.append(io);
        sen.name = (QString::number(i));
        sen.name.append(". An output");
        sensList.append(sen);
    }

    sen.name = (QString::number(MAX_AN_INPUT4_20));// -1   ???
    sen.name.append(". 24V barošana");
    sensList.append(sen);


    scaleVal = 0;
    // for testing only
    // actList[0].digital = 1;
    // actList[1].digital = 1;
    //actList[2].digital = 1;
    // actList[29].digital = 1;
    // actList[30].digital = 1;
    // actList[31].digital = 1;
}


void Global::creatActList()
{

    act  sact;

    for(int i=0 ; i<64;i++){    // 255= max sensor, max activator
        actList.append(sact);
    }

    addActList("Valve 1",ActuatorType::Relay,1);
    addActList("Valve 2",ActuatorType::Relay,2);
    addActList("Valve 3",ActuatorType::Relay,3);
    addActList("Valve 4",ActuatorType::Relay,4);
    addActList("Pump 1",ActuatorType::Relay,5);
    addActList("Pump 2",ActuatorType::Relay,6);
    addActList("Pump 3",ActuatorType::Relay,7);
    addActList("Pump 4",ActuatorType::Relay,8);

    addActList("Mix invertor 1",ActuatorType::Invertor,15);

    qDebug() << "create " << actList.size() << "actuators";
}

void Global::addActList(QString name, ActuatorType::actT tp, int addres)
{
    // Act adreses apzīmē adr + 300;
    act data;
    data.type = tp;
    data.address = addres;
    data.name = name;
    // data.analog = 0; VALUE
    // data.digital = 0; VALUE
    //actList.append(data);
    actList[addres] = (data);
}


//addSensList(QString name, SensorType::sensT tp, int addres)
void Global::creatSensList()
{
    addSensList("Tvertne 1 sensors DI", SensorType::Digital, 1);
    addSensList("Tvertne 1 sensors AN", SensorType::Analog,  2);

    addSensList("Tvertne 2 sensors DI", SensorType::Digital, 3);
    addSensList("Tvertne 2 sensors AN", SensorType::Analog,  5);

    addSensList("Tvertne 3 sensors DI", SensorType::Digital, 4);
    addSensList("Tvertne 3 sensors AN", SensorType::Analog,  5);

    addSensList("Tvertne 4 sensors DI", SensorType::Digital, 6);
    addSensList("Tvertne 4 sensors AN", SensorType::Analog,  7);
    addSensList("Scale AN", SensorType::Analog,  11);



    addSensList("Pump1 1 sensors AN", SensorType::Digital,  32);
    addSensList("Tvertne 2 sensors AN", SensorType::Digital,  33);


    qDebug() << "create " << sensList.size() << "sensors";
}

void Global::addSensList(QString name, SensorType::sensT tp, int addres)
{
    sens data;

    data.type = tp;  //
    data.name = name;
    // data.analog = 0; VALUE
    // data.digital = 0; VALUE
    sensList.append(data);
    sensList[addres] = data;
}

void Global::needUpdateDIoutputs(int row, int val)
{
    updateDataIn.need = true;
    updateDataIn.row = row;
    updateDataIn.val = val;
}

void Global::needUpdateSensorIn(int row, int val)
{
    updateDataOut.need = true;
    updateDataOut.row = row;
    updateDataOut.val = val;
}

int Global::getTick()
{
    return tick;
}

void Global::addTick()
{
    tick++;
}

int Global::getwaitTx()
{
    return waitTx;
}

void Global::setwaitTx(int val)
{
    waitTx = val;
}

//*************************************************************
//in out number:

//QList<bool>DIinput;           + 0
//QList<bool>DIoutput;          + 100
//QList<int>ANinput4_20; // value/100 = x,xx(mA)   + 200



/*

Left upper corner coordinates:
startX
startY

Widget size
startSize



for MIX:
act_sensAddres act  address
    digital  - on/off	// griežas
    analog   - speed	// cik ātri
sensAddres   - no
sensAddres2  - no



for  Pipe :
Hight startSize
Width  startSizeWi
Angle > 0 fron vertical CCW  options
Angle = 0  horisontal
Angle = 90  vertical
act_sensAddres act  address
    digital  - no
    analog   - no


for  Valve :
options Angle fron vertical CCW  options mean close  open = option + 90
Hight startSize
Width  startSizeWi
Angle > 0 fron vertical CCW  options
act_sensAddres act  address
    digital  - on/off
    analog   - speed
act_sensAddres sensor1 address
    digital - stop switch1
act_sensAddres sensor2 address
     digital - stop switch2



for pump:
act_sensAddres act  address
    digital  - on/off
    analog   - speed

for tvertne:

    digital  - max level
    analog   - level



page = 0   draw on "Mix" page
page = 1   draw on "Dyno" page
page = 3   draw on all pages

    */

void Global::creatWidgList()
{
    //      WidgetType::widgT ty,    name,       page, X,       Y,  size, options,  actAdr1, sensAdr1,  sensAdr2)

    addWidgList(WidgetType::Mix,        "MIX",     1,   530,    30,  100,     0,        MIXSPEED, MIXONOFF,  0);

    addWidgList(WidgetType::Dispax,     "DISPAX",  1,   400,    352, 100,       0,        DINOSPEED, DINONOFF,  0);
    addWidgList(WidgetType::Label,      "LABEL1",  1,   1644,   230, 250,       0,        0,0,0);
    addWidgList(WidgetType::Label,      "LABEL2",  1,   243,    230, 250,       0,        0,0,0);


    addWidgList(WidgetType::Tvertne,    "T2",      1,   1598,    16,  80,    0,        0, TVERTNE1LEVEL, TVERTNE1FULL);
    addWidgList(WidgetType::Tvertne,    "T3",      1,   700,    350,  80,    0,        0, TVERTNE1LEVEL, TVERTNE1FULL);
    addWidgList(WidgetType::Tvertne,    "T4",      1,   1000,    350, 80,    0,        0, TVERTNE1LEVEL, TVERTNE1FULL);
    addWidgList(WidgetType::Tvertne,    "T5",      1,   1300,    350, 80,    0,        0, TVERTNE1LEVEL, TVERTNE1FULL);

    addWidgList(WidgetType::Pump,       "PUMP S4",  1,  425,    485, 50,     0,        PUMP1SPEED, PUMP1NOFF,  0);
    addWidgList(WidgetType::Pump,       "PUMP S5",  1,  746,    50,  50,     0,        PUMP1SPEED, PUMP1NOFF,  0);


    addWidgList(WidgetType::Valve,      "Valve 2.1",  1,    660,   33, 25,  0,       VALVE1ACT, VALVE1SWOPEN,  VALVE1SWCLOSE);
    addWidgList(WidgetType::Valve,      "Valve 2.2",  1,    660,   90, 25,  0,       VALVE1ACT, VALVE1SWOPEN,  VALVE1SWCLOSE);
    addWidgList(WidgetType::Valve,      "Valve 2.3",  1,    1524,  122, 25,  0,       VALVE1ACT, VALVE1SWOPEN,  VALVE1SWCLOSE);
    addWidgList(WidgetType::Valve,      "Valve 2.4",  1,    1449,  122, 25,  0,       VALVE1ACT, VALVE1SWOPEN,  VALVE1SWCLOSE);

    addWidgList(WidgetType::Valve,      "Valve 3.1",  1,    699,   273, 25,  0,       VALVE1ACT, VALVE1SWOPEN,  VALVE1SWCLOSE);
    addWidgList(WidgetType::Valve,      "Valve 3.2",  1,    759,   273, 25,  0,       VALVE1ACT, VALVE1SWOPEN,  VALVE1SWCLOSE);
    addWidgList(WidgetType::Valve,      "Valve 3.3",  1,    699,   463, 25,  0,       VALVE1ACT, VALVE1SWOPEN,  VALVE1SWCLOSE);
    addWidgList(WidgetType::Valve,      "Valve 3.4",  1,    757,   461, 25,  0,       VALVE1ACT, VALVE1SWOPEN,  VALVE1SWCLOSE);

    addWidgList(WidgetType::Valve,      "Valve 4.1",  1,    1003,   221, 25,  0,       VALVE1ACT, VALVE1SWOPEN,  VALVE1SWCLOSE);
    addWidgList(WidgetType::Valve,      "Valve 4.2",  1,    1058,   221, 25,  0,       VALVE1ACT, VALVE1SWOPEN,  VALVE1SWCLOSE);
    addWidgList(WidgetType::Valve,      "Valve 4.3",  1,    1301,   583, 25,  0,       VALVE1ACT, VALVE1SWOPEN,  VALVE1SWCLOSE);
    addWidgList(WidgetType::Valve,      "Valve 4.4",  1,    1359,   582, 25,  0,       VALVE1ACT, VALVE1SWOPEN,  VALVE1SWCLOSE);

    addWidgList(WidgetType::Valve,      "Valve 5.1",  1,    1300,   171, 25,  0,       VALVE1ACT, VALVE1SWOPEN,  VALVE1SWCLOSE);
    addWidgList(WidgetType::Valve,      "Valve 5.2",  1,    1360,   171, 25,  0,       VALVE1ACT, VALVE1SWOPEN,  VALVE1SWCLOSE);
    addWidgList(WidgetType::Valve,      "Valve 5.3",  1,    1000,   522, 25,  0,       VALVE1ACT, VALVE1SWOPEN,  VALVE1SWCLOSE);
    addWidgList(WidgetType::Valve,      "Valve 5.4",  1,    1058,  521, 25,  0,       VALVE1ACT, VALVE1SWOPEN,  VALVE1SWCLOSE);


    addWidgList(WidgetType::Valve,      "Valve 6.2",  1,    468,   273, 25,  0,       VALVE1ACT, VALVE1SWOPEN,  VALVE1SWCLOSE);
    addWidgList(WidgetType::Valve,      "Valve 6.3",  1,    408,   273, 25,  0,       VALVE1ACT, VALVE1SWOPEN,  VALVE1SWCLOSE);


// PIPE

    addWidgList(WidgetType::Pipe,       "Pipe 1",     1,   1477,    131,   45,  90,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 2",     1,    680,    70,    61,  90,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 3",     1,    670,    60,    27,  0,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 4",     1,    800,    70,    694,  90,      0,0,0);

   // addWidgList(WidgetType::Pipe,       "Pipe 5",     1,    857,    10,    17,  0,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 6",     1,    737,    291,    65,  0,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 7",     1,    728,    282,    30,  90,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 8",     1,    1326,   180,    30,  90,      0,0,0);

    addWidgList(WidgetType::Pipe,       "Pipe 9",     1,    1106,    138,    39,  0,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 10",    1,    1551,    131,    90,  90,      0, 0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 11",     1,    1036,   238,    118,  0,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 12",     1,    670,    7,      23,  0,      0,0,0);

    addWidgList(WidgetType::Pipe,       "Pipe 13",     1,    1493,    70,     62,  0,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 14",     1,    495,    280,    202,  90,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 15",     1,    1028,    230,    30,  90,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 16",     1,    445,    590,    169,  90,      0,0,0);

    addWidgList(WidgetType::Pipe,       "Pipe 17",     1,    1086,    230,    20,  90,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 18",     1,    1027,    530,    30,  90,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 19",     1,    624,    590,    673,  90,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 20",     1,    808,    650,    840,  90,      0,0,0);


    addWidgList(WidgetType::Pipe,       "Pipe 21",     1,    445,    288,    61,  0,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 22",     1,    570,    7,    100,  90,      0,0,0);

    addWidgList(WidgetType::Pipe,       "Pipe 23",     1,    674,    180,    100,  0,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 24",     1,    684,    230,    319,  90,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 25",     1,    1335,   428,    164,  0,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 26",     1,    786,    281,    20,  90,      0,0,0);

    addWidgList(WidgetType::Pipe,       "Pipe 27",     1,    1037,   427,    104,   0,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 28",     1,    725,   470,    30,  90,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 29",     1,    1325,   591,    30,  90,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 30",     1,    736,   426,    44,   0,      0,0,0);

    addWidgList(WidgetType::Pipe,       "Pipe 31",     1,    679,   180,    617,   90,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 32",     1,    435,   280,    30,   90,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 33",     1,    246,   280,    156,  90,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 34",     1,    784,   470,    25,   90,      0,0,0);

    addWidgList(WidgetType::Pipe,       "Pipe 35",     1,    445,   428,    49,   0,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 36",     1,    614,   470,   129,   0,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 37",     1,    808,   541,    46,   0,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 38",     1,    623,   470,    75,  90,      0,0,0);

    addWidgList(WidgetType::Pipe,       "Pipe 39",     1,    809,   469,    60,  0,       0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 40",     1,    624,   530,    370,   90,    0,0,0);

 //   addWidgList(WidgetType::Pipe,       "Pipe 41",     1,    867,    10,    60,  90,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 42",     1,    795,    240,    41,  0,      0,0,0);

    addWidgList(WidgetType::Pipe,       "Pipe 43",     1,    808,    603,    48,  0,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 44",     1,   1386,    591,    22,  90,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 45",     1,    1108,    531,    60,   0,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 46",     1,   1408,    591,    60,  0,      0,0,0);

    addWidgList(WidgetType::Pipe,       "Pipe 47",     1,    806,    130,    603,  90,      0,0,0);
   // addWidgList(WidgetType::Pipe,       "Pipe 48",     1,    1646,   200,    30,  90,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 49",     1,    1085,   531,    23,  90,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 50",     1,    1647,   287,    372,   0,      0,0,0);

    addWidgList(WidgetType::Pipe,       "Pipe 51",     1,    1637,    95,    44,  0,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 52",     1,    795,    192,    36,  0,      0,0,0);

    addWidgList(WidgetType::Pipe,       "Pipe 53",     1,    795,    130,    48,  0,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 54",     1,   1386,    181,    22,  90,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 55",     1,    1106,    191,    47,   0,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 56",     1,    1408,    130,    60,  0,      0,0,0);

    addWidgList(WidgetType::Pipe,       "Pipe 57",     1,    1335,   188,    169,   0,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 58",     1,    1647,   287,    104,   90,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 59",     1,    1418,    130,    30,   90,      0,0,0);
   // addWidgList(WidgetType::Pipe,       "Pipe 60",     1,    1637,   200,    370,   0,      0,0,0);

    addWidgList(WidgetType::Pipe,       "Pipe 61",     1,    570,    123,    20,  0,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 62",     1,    670,    120,    23,  0,      0,0,0);

    addWidgList(WidgetType::Pipe,       "Pipe 63",     1,    445,    539,    53,  0,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 64",     1,   570,    142,    111,  90,      0,0,0);
    addWidgList(WidgetType::Pipe,       "Pipe 65",     1,    570,    11,    20,   0,      0,0,0);



   // addWidgList(WidgetType::ScalesBase,    "Scales Base", 1,   772,  142,    100,  0,     0,   0, 0);
   // addWidgList(WidgetType::ScalesMass,    "Scales Mass",1,    770,  30,   100, 0,    0,   SCALESMASS, 0);


    /*

    addWidgList(WidgetType::ScalesBase,    "Scales Base",    413,        545,    250,   15, 0,   0,  0,0,0,0);
    addWidgList(WidgetType::ScalesMass,    "Scales Mass",    584,       485,     62,   0,  0,   0,  0,11,0,0);

*/


    qDebug() << "create " << widHash.size() << "widgets";
}



void Global::addWidgList(WidgetType::widgT ty, QString name, int page,int X, int Y, int size,int options, int actAdr1, int sensAdr1, int sensAdr2)
{
    wdataStruct data;
    data.type = ty;     // widget type
    data.name = name;   // neme
    data.page = page;   // page Nr procUI1 = 1 procUI2 = 2

    data.startX = X;    // coordinate X
    data.startY = Y;    // coordinate Y
    data.startSize = size;  // size zoom
    data.options = options; // valve angle, pipe angle
    data.act_Addres1 = actAdr1; // actuator address
    data.sensAddres1 = sensAdr1; // sensor address1, for pipe angle, for valve angle / on off/
    data.sensAddres2 = sensAdr2; // sensor address2
    widHash.insert(name, data);
}
