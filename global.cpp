#include "global.h"
#include <Qdebug>


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


    for(int i = 0; i < MAX_DIinput; i++){
        sen.name = (QString::number(i));
        sen.name.append(". DI in");
        sen.address = i;
        //DIinput.append(io);
        sensList.append(sen);
    }

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

    sen.name = (QString::number(MAX_AN_INPUT4_20-1));
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
    //addWidgList(WidgetType::widgT ty, QString na,int X, int Y, int size, int sizeW, int options, int page, int actAdr1, int actAdr2, int sensAdr1, int sensAdr2)

    // page  Mix
    // WidgetType::widgT ty, QString na,int X, int Y, int size, int sizeW, int options, int page,   int actAdr1, int actAdr2, int sensAdr1, int sensAdr2
    addWidgList(WidgetType::Mix,        "Mix",     240,        24,   96, 0, 0,        0, 0,  0,0,0);
    addWidgList(WidgetType::Dyno,       "Dyno1",   161,         8,   70, 0,  0,        0, 0,  0,0,0);
    addWidgList(WidgetType::Dyno,       "Dyno",   161,         600,   70, 0,  0,       0,  0,  0,0,0);

    addWidgList(WidgetType::Tvertne,     "Tvertne 2",  650,     50,   50, 0,  0,       0,  0,  0,0,0);
    addWidgList(WidgetType::Tvertne,     "Tvertne 3",  248,     420,   50, 0,  0,       0,  0,  3,202,4);
    addWidgList(WidgetType::Tvertne,     "Tvertne 4",  450,     420,   50, 0,  0,       0,  0,  0,5,6);
    addWidgList(WidgetType::Tvertne,     "Tvertne 5",  635,     420,   50, 0,  0,       0,  0,  0,7,8);

    addWidgList(WidgetType::Pump,       "Pump1",  440,        196,    35, 0,  0,        0, 0,  305,0,0);
    //addWidgList(WidgetType::Pump,       "Pump2",  378,        255,    35, 0,  0,        0, 0,  306,0,0);
   //addWidgList(WidgetType::Pump,       "Pump3",  526,        255,    35, 0,  0,        0, 0,  307,0,0);
   // addWidgList(WidgetType::Pump,       "Pump4",  652,        255,    35, 0,  0,        0, 0,  308,0,0);

    addWidgList(WidgetType::Valve,      "Valve 1",  240,       145,   30, 0,  90,       0, 0,  301,31,32);
    addWidgList(WidgetType::Valve,      "Valve 2",  270,       145,   30, 10, 90,       0, 0,  302,0,0);
    addWidgList(WidgetType::Valve,      "Valve 3",  656,       237,   30, 0,  90,       0, 0,  303,0,0);
    addWidgList(WidgetType::Valve,      "Valve 4",  657,       141,   30, 10, 90,       0, 0,  304,0,0);

    addWidgList(WidgetType::Valve,      "Valve 5",  631,       355,   30, 0,  90,       0, 0,  301,31,32);
    addWidgList(WidgetType::Valve,      "Valve 6",  656,       355,   30, 10, 90,      0,  0,  302,0,0);
    addWidgList(WidgetType::Valve,      "Valve 7",  245,       515,   30, 0,  90,       0, 0,  303,0,0);
    addWidgList(WidgetType::Valve,      "Valve 8",  270,       515,   30, 10, 90,       0, 0,  304,0,0);

    addWidgList(WidgetType::Valve,      "Valve 9",  447,       515,   30, 0,  90,       0, 0,  301,31,32);
    addWidgList(WidgetType::Valve,      "Valve 10",  472,       515,   30, 10, 90,       0, 0,  302,0,0);
    addWidgList(WidgetType::Valve,      "Valve 11",  631,       515,   30, 0,  90,       0, 0,  303,0,0);
    addWidgList(WidgetType::Valve,      "Valve 12",  656,       515,   30, 10, 90,       0, 0,  304,0,0);

    addWidgList(WidgetType::Valve,      "Valve 13",  245,       355,   30, 0,  90,      0,  0,  303,0,0);
    addWidgList(WidgetType::Valve,      "Valve 14",  270,       355,   30, 10, 90,       0, 0,  304,0,0);
    addWidgList(WidgetType::Valve,      "Valve 15",  447,       355,   30, 0,  90,       0, 0,  301,31,32);
    addWidgList(WidgetType::Valve,      "Valve 16",  472,       355,   30, 10, 90,       0, 0,  302,0,0);

    addWidgList(WidgetType::Valve,      "Valve 17",  150,       355,   30, 0,  90,       0, 0,  303,0,0);
    addWidgList(WidgetType::Valve,      "Valve 18",  125,       355,   30, 10, 90,       0, 0,  304,0,0);


    addWidgList(WidgetType::Pipe,     "Pipe 1",   250,        110,    35,  10,  0,      0, 0,  0,0,0);
    addWidgList(WidgetType::Pipe,    "Pipe 2",    280,        110,    35,  10,  0,      0, 0,  0,0,0);
    addWidgList(WidgetType::Pipe,     "Pipe 3",   665,        105,    30,  10,  0,      0, 0,  0,0,0);
    addWidgList(WidgetType::Pipe,    "Pipe 4",    489,        208,    170,  10,  90,      0, 0,  0,0,0);

    addWidgList(WidgetType::Pipe,     "Pipe 5",    250,        175,    30,  10, 0,      0, 0,  0,0,0);
    addWidgList(WidgetType::Pipe,    "Pipe 6",    280,        175,    30,  10,  0,      0, 0,  0,0,0);
    addWidgList(WidgetType::Pipe,     "Pipe 7",    250,        208,    170,  10, 90,      0, 0,  0,0,0);
    addWidgList(WidgetType::Pipe,    "Pipe 8",    665,        177,    60,  10,  0,      0, 0,  0,0,0);

    addWidgList(WidgetType::Pipe,     "Pipe 9",    665,        477,    30,  10, 0,    0, 0,  0,0,0);
    addWidgList(WidgetType::Pipe,    "Pipe 10",    336,        304,    35,  10,90,    0, 0,  0,0,0);
    addWidgList(WidgetType::Pipe,     "Pipe 11",    245,        336,    45,  10,90,   0, 0,  0,0,0);
    addWidgList(WidgetType::Pipe,    "Pipe 12",    668,        389,    30,  10, 0,   0, 0,  0,0,0);

    addWidgList(WidgetType::Pipe,    "Pipe 13",    463,       389,     30,   10,  0,   0, 0,  0,0,0);
    addWidgList(WidgetType::Pipe,     "Pipe 14",    250,        389,    30,  10, 0,      0, 0,  0,0,0);
    addWidgList(WidgetType::Pipe,    "Pipe 15",    280,        477,    30,  10,  0,      0, 0,  0,0,0);
    addWidgList(WidgetType::Pipe,     "Pipe 16",    457,        477,    30,  10, 0,      0, 0,  0,0,0);

    addWidgList(WidgetType::Pipe,    "Pipe 17",    482,        477,    30,  10,  0,      0, 0,  0,0,0);
    addWidgList(WidgetType::Pipe,     "Pipe 18",    643,        477,    30,  10, 0,    0, 0,  0,0,0);
    addWidgList(WidgetType::Pipe,    "Pipe 19",    280,        389,    30,  10,0,    0, 0,  0,0,0);
    addWidgList(WidgetType::Pipe,     "Pipe 20",    482,        389,    30,  10,0,   0, 0,  0,0,0);

    addWidgList(WidgetType::Pipe,    "Pipe 21",    125,        389,    30,  10,  0,      0, 0,  0,0,0);
    addWidgList(WidgetType::Pipe,     "Pipe 22",    150,        389,    30,  10, 0,    0, 0,  0,0,0);
    addWidgList(WidgetType::Pipe,    "Pipe 23",    643,        389,    30,  10,0,    0, 0,  0,0,0);
    addWidgList(WidgetType::Pipe,     "Pipe 24",    255,        477,    30,  10,0,   0, 0,  0,0,0);

    addWidgList(WidgetType::Pipe,     "Pipe 25",    665,        550,    30,  10, 0,    0, 0,  0,0,0);
    addWidgList(WidgetType::Pipe,    "Pipe 26",    280,        550,    30,  10,  0,      0, 0,  0,0,0);
    addWidgList(WidgetType::Pipe,     "Pipe 27",    457,        550,    30,  10, 0,      0, 0,  0,0,0);
    addWidgList(WidgetType::Pipe,    "Pipe 28",    482,        550,    30,  10,  0,      0, 0,  0,0,0);

    addWidgList(WidgetType::Pipe,     "Pipe 29",    643,        550,    30,  10, 0,    0, 0,  0,0,0);
    addWidgList(WidgetType::Pipe,     "Pipe 30",    255,        550,    30,  10,0,   0, 0,  0,0,0);
    addWidgList(WidgetType::Pipe,    "Pipe 31",    336,        595,    35,  10,90,    0, 0,  0,0,0);
    addWidgList(WidgetType::Pipe,     "Pipe32",    245,        595,    45,  10,90,   0, 0,  0,0,0);


    addWidgList(WidgetType::ScalesBase,    "Scales Base",    235,        100,    250,   15, 0,   0, 0,  0,0,0);
    addWidgList(WidgetType::ScalesMass,    "Scales Mass",    431,       40,     62,   0,  0,   0, 0,  0,11,0);


    // page Dyno
    // WidgetType::widgT ty, QString na,int X, int Y, int size, int sizeW, int options, int page, int actAdr, int sensAdr1, int sensAdr2

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


    qDebug() << "create " << widHash.size() << "widgets";
}

void Global::addWidgList(WidgetType::widgT ty, QString na,int X, int Y, int size, int sizeW, int options, int page, int actAdr1, int actAdr2, int sensAdr1, int sensAdr2)
{
    wdataStruct data;
    data.type = ty;
    data.name = na;
    data.startX = X;
    data.startY = Y;
    data.startSize = size;
    data.startSizeWi = sizeW;
    data.options = options;
    data.page = page;
    data.act_Addres1 = actAdr1; // mainly di
    data.act_Addres2 = actAdr2; // mainly an
    data.sensAddres1 = sensAdr1;
    data.sensAddres2 = sensAdr2;
    widHash.insert(na, data);
}
