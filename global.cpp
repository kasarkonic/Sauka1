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
    //          WidgetType::widgT ty,       name,    page,       X,    Y,  size, options,  actAdr1, sensAdr1,  sensAdr2)

    addWidgList(WidgetType::Mix,        "Mix",     1,        20,   30, 100,     0,        MIXSPEED, MIXONOFF,  0);
    addWidgList(WidgetType::Dyno,       "Dyno1",   1,         200,   30, 100,   0,        DINOSPEED, DINONOFF,  0);
    addWidgList(WidgetType::Tvertne,    "Tvertne 1",1,       380,   30, 100,    0,        0, TVERTNE1LEVEL, TVERTNE1FULL);
    addWidgList(WidgetType::Pump,       "Pump1",    1,        560,    30, 100,  0,        PUMP1SPEED, PUMP1NOFF,  0);

    addWidgList(WidgetType::Valve,      "Valve 1",  1,       500,   500, 100,  0,       0, 0,  0);

    addWidgList(WidgetType::Pipe,        "Pipe 1",  1,        720,    30,  100,  0,      0, 0,  0);

    addWidgList(WidgetType::ScalesBase,    "Scales Base", 1,   772,  142,    100,  0,     0,   0, 0);
    addWidgList(WidgetType::ScalesMass,    "Scales Mass",1,    770,  30,   100, 0,    0,   SCALESMASS, 0);


    /*


    addWidgList(WidgetType::Mix,        "Mix",     424,        468,   96, 0, 0,        0,  0,0,0,0);
    addWidgList(WidgetType::Dyno,       "Dyno1",   161,         8,   70, 0,  0,        0,  0,0,0,0);
    addWidgList(WidgetType::Tvertne,     "Tvertne 1",  225,     50,   50, 0,  0,        0,  1,201,2,0);
    addWidgList(WidgetType::Tvertne,     "Tvertne 2",  375,     50,   50, 0,  0,        0,  3,202,4,0);
    addWidgList(WidgetType::Tvertne,     "Tvertne 3",  525,     50,   50, 0,  0,        0,  0,5,6,0);
    addWidgList(WidgetType::Tvertne,     "Tvertne 4",  650,     50,   50, 0,  0,        0,  0,7,8,0);

    addWidgList(WidgetType::Pump,       "Pump1",  235,        255,    35, 0,  0,        0,  305,0,0,0);
    addWidgList(WidgetType::Pump,       "Pump2",  378,        255,    35, 0,  0,        0,  306,0,0,0);
    addWidgList(WidgetType::Pump,       "Pump3",  526,        255,    35, 0,  0,        0,  307,0,0,0);
    addWidgList(WidgetType::Pump,       "Pump4",  652,        255,    35, 0,  0,        0,  308,0,0,0);

    addWidgList(WidgetType::Valve,      "Valve 1",  231,       165,   25, 0,  45,       0,  301,31,32,0);
    addWidgList(WidgetType::Valve,      "Valve 2",  386,       165,   25, 10, 45,       0,  302,0,0,0);
    addWidgList(WidgetType::Valve,      "Valve 3",  534,       165,   25, 0,  45,       0,  303,0,0,0);
    addWidgList(WidgetType::Valve,      "Valve 4",  658,       165,   25, 10, 45,       0,  304,0,0,0);

    addWidgList(WidgetType::Pipe,     "Pipe 1",   240,        105,    60,  10,  0,      0,  0,0,0,0);
    addWidgList(WidgetType::Pipe,    "Pipe 2",    392,        105,    60,  10,  0,      0,  0,0,0,0);
    addWidgList(WidgetType::Pipe,     "Pipe 3",   540,        105,    60,  10,  0,      0,  0,0,0,0);
    addWidgList(WidgetType::Pipe,    "Pipe 4",    665,        105,    60,  10,  0,      0,  0,0,0,0);

    addWidgList(WidgetType::Pipe,     "Pipe 5",    240,        190,    60,  10, 0,      0,  0,0,0,0);
    addWidgList(WidgetType::Pipe,    "Pipe 6",    392,        190,    60,  10,  0,      0,  0,0,0,0);
    addWidgList(WidgetType::Pipe,     "Pipe 7",    540,        190,    60,  10, 0,      0,  0,0,0,0);
    addWidgList(WidgetType::Pipe,    "Pipe 8",    665,        190,    60,  10,  0,      0,  0,0,0,0);

    addWidgList(WidgetType::Pipe,     "Pipe 9",    269,        297,    176,  10, 40,    0,  0,0,0,0);
    addWidgList(WidgetType::Pipe,    "Pipe 10",    391,        298,    137,  10, 21,    0,  0,0,0,0);
    addWidgList(WidgetType::Pipe,     "Pipe 11",    492,        295,    133,  10,160,   0,  0,0,0,0);
    addWidgList(WidgetType::Pipe,    "Pipe 12",    526,        295,    189,  10, 135,   0,  0,0,0,0);
    addWidgList(WidgetType::Pipe,    "Pipe 13",    457,       567,     115,   10,  0,   0,  0,0,0,0);

    addWidgList(WidgetType::ScalesBase,    "Scales Base",    413,        545,    250,   15, 0,   0,  0,0,0,0);
    addWidgList(WidgetType::ScalesMass,    "Scales Mass",    584,       485,     62,   0,  0,   0,  0,11,0,0);


*/










    // page Dyno
    // WidgetType::widgT ty, QString na,int X, int Y, int size, int sizeW, int options, int page, int actAdr, int sensAdr1, int sensAdr2
    /*
    addWidgList(WidgetType::Dyno,       "Dyno 51",   200,         50,   70, 0,  0,      1, 0,0,2,0);

    addWidgList(WidgetType::Pump,       "Pump 51",  235,        255,    35, 0,  0,      1, 0,0,0,0);
    addWidgList(WidgetType::Pump,       "Pump 52",  378,        255,    35, 0,  0,       1, 0,0,0,0);

    addWidgList(WidgetType::Valve,      "Valve 51",  231,       165,   25, 0,  45,       1, 0,0,0,0);
    addWidgList(WidgetType::Valve,      "Valve 52",  386,      165,   25,  10,  45,     1, 0,0,0,0);
    addWidgList(WidgetType::Valve,      "Valve 53",  534,       165,   25, 0,  45,       1, 0,0,0,0);
    addWidgList(WidgetType::Valve,      "Valve 54",  658,      165,   25,  10,  45,     1, 0,0,0,0);

    addWidgList(WidgetType::Valve,      "Valve 55",  231,       165,   25, 0,  45,      1, 0,0,0,0);
    addWidgList(WidgetType::Valve,      "Valve 56",  386,      165,   25,  10,  45,     1, 0,0,0,0);
    addWidgList(WidgetType::Valve,      "Valve 57",  534,       165,   25, 0,  45,      1, 0,0,0,0);
    addWidgList(WidgetType::Valve,      "Valve 58",  658,      165,   25,  10,  45,     1, 0,0,0,0);

    addWidgList(WidgetType::Pipe,     "Pipe 51",   240,        105,    60,  10,  0,     1, 0,0,0,0);
    addWidgList(WidgetType::Pipe,    "Pipe 52",    392,        105,    60,  10,  0,     1, 0,0,0,0);
    addWidgList(WidgetType::Pipe,     "Pipe 53",   540,        105,    60,  10,  0,     1, 0,0,0,0);
    addWidgList(WidgetType::Pipe,    "Pipe 54",    665,        105,    60,  10,  0,     1, 0,0,0,0);

    addWidgList(WidgetType::Pipe,     "Pipe 55",    240,        190,    60,  10,  0,    1, 0,0,0,0);
    addWidgList(WidgetType::Pipe,    "Pipe 56",    392,        190,    60,  10,  0,     1, 0,0,0,0);
    addWidgList(WidgetType::Pipe,     "Pipe 57",    540,        190,    60,  10,  0,    1, 0,0,0,0);
    addWidgList(WidgetType::Pipe,    "Pipe 58",    665,        190,    60,  10,  0,     1, 0,0,0,0);

    addWidgList(WidgetType::Pipe,     "Pipe 59",   240,        305,    60,  10,  0,     1, 0,0,0,0);
    addWidgList(WidgetType::Pipe,    "Pipe 60",    392,        305,    60,  10,  0,     1, 0,0,0,0);
    addWidgList(WidgetType::Pipe,     "Pipe 61",   540,        305,    60,  10,  0,     1, 0,0,0,0);
    addWidgList(WidgetType::Pipe,    "Pipe 62",    665,        305,    60,  10,  0,     1, 0,0,0,0);

    addWidgList(WidgetType::Pipe,     "Pipe 63",    240,        390,    60,  10,  0,    1, 0,0,0,0);
    addWidgList(WidgetType::Pipe,    "Pipe 64",    392,        390,    60,  10,  0,     1, 0,0,0,0);
    addWidgList(WidgetType::Pipe,     "Pipe 65",    540,        390,    60,  10,  0,    1, 0,0,0,0);
    addWidgList(WidgetType::Pipe,    "Pipe 66",    665,        390,    60,  10,  0,     1, 0,0,0,0);
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
