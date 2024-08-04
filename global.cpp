#include "global.h"
#include <Qdebug>
#include <QTimer>
#include <QElapsedTimer>
//#include "ballvalve.h"



//using namespace inputWidg;
//using namespace inputAct;
//using namespace inputSens;

Global::Global() {
    appSwVers = "vers: 0.1   ";
    zoomKoef = zoomKoefPf1 = zoomKoefPf2 = 1.0;
    UIXsize = UIXsizePf1 = UIXsizePf2 = 1000;
    UIYsize = UIYsizePf1 = UIYsizePf2 = 1000;
    UIXresizeSize = UIXresizeSizePf1 = UIXresizeSizePf2 = 1000;
    UIYresizeSize = UIYresizeSizePf1 = UIYresizeSizePf2 = 1000;

    dev1 = "";
    dev2 = "";
    dev3 = "";
    dev4 = "";
    dev1ConnectStatus = false;   // rs232 for temperature sensor and level meter
    dev2ConnectStatus = false;   // rs232 for scale
    dev3ConnectStatus = false;
    dev4ConnectStatus = false;

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

    for (int iter = 0; iter <= MAX_AN_INPUT4_20 + 1; iter++) {// +1 for voltage inputs

        io.name = QString::number(iter);
        io.name.append(nam);
        ANinput4_20.append(io);
    }
    nam = " Din";
    for (int iter = 0; iter < MAX_DIinput; iter++) {
        io.name = QString::number(iter);
        io.name.append(nam);
        DIinput.append(io);
    }
    nam = " Dout";
    for (int iter = 0; iter < MAX_DIoutput; iter++) {
        io.name = QString::number(iter);
        io.name.append(nam);
        DIoutput.append(io);
    }


    for (int i = 0; i < 64;i++) {    // 255= max sensor, max activator
        sensList.append(sdata);
        //    actList.append(sact);
    }
    qDebug() << sensList.size() << actList.size();


    creatWidgList();

    creatActList();
    qDebug() << "!!! test act name ";
    creatSensList();
    qDebug() << "!!! test sensor name ";

    //foreach(sens item,  sensList){
    //    qDebug() << item.name << item.type ;
    //}
    disableRS485 = false;   // for testing
    create_IN_OUT_list();
    createPressSensList();
    tick = 0;
    waitTx = 0;
    createBallValve();

    tickTimer.start();

}

void Global::createPressSensList()
{
    press_sens psl;

    for (int i = 0; i < 8; i++){       // 8 readings average
        psl.buf.append(i);
    }

    for (int i = 0; i < 8; i++){       // 8 readings average
        press_sensList.append(psl);
    }
    qDebug() <<"press_sensList"<< press_sensList.size();


    press_sensList[0].name = "1. tvertnes līmenis";
    press_sensList[1].name = "2. tvertnes līmenis";
    press_sensList[2].name = "3. tvertnes līmenis";

}

//QList<bool>DIinput;
//QList<bool>DIoutput;
//QList<int>ANinput4_20;   mA  // value/100 = x,xx(A)

int Global::getANval(int addres) {
    int val = 0;
    int addr = addres - 200;
    if (addr >= 0 && addr < MAX_AN_INPUT4_20) {
        val = sensList[addr].analog;
    }
    return val;
}

bool Global::getDIval(int addres) {
    bool val = 0;

    if (addres >= 0 && addres < MAX_DIinput) {
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
void Global::create_IN_OUT_list() {
    act actuat;
    actuat.analog = 0;
    actuat.digital = false;


    sens sen;

    sen.type = SensorType::sensT::Digital;  // digital 0 -> MAX_DIinput  tad analog MAX_DIinput ->MAX_DIinput + MAX_AN_VIRUAL_INPUT
    //sen.name = "DI in";
    //int address = 0;
    sen.digital = 0; //VALUE
    sen.analog = 0; //VALUE
    sen.ptrLineEditDI = nullptr;
    sen.ptrLineEditAN = nullptr;


    for (int i = 0; i < MAX_ACTUATOR; i++) {
        actuat.name = (QString::number(i));
        actuat.name.append(". Act. output");
        actList.append(actuat);
    }

    // io.An = 0.0;
    //io.Di = false;
    sen.type = SensorType::sensT::Analog;  // digital 0 -> MAX_DIinput  tad analog MAX_DIinput ->MAX_DIinput + MAX_AN_VIRUAL_INPUT


    for (int i = 0; i < MAX_AN_INPUT4_20; i++) {
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


void Global::creatActList() {

    act  sact;

    for (int i = 0; i < 64;i++) {    // 255= max sensor, max activator
        actList.append(sact);
    }

    addActList("Valve 1", ActuatorType::Relay, 1);
    addActList("Valve 2", ActuatorType::Relay, 2);
    addActList("Valve 3", ActuatorType::Relay, 3);
    addActList("Valve 4", ActuatorType::Relay, 4);
    addActList("Pump 1", ActuatorType::Relay, 5);
    addActList("Pump 2", ActuatorType::Relay, 6);
    addActList("Pump 3", ActuatorType::Relay, 7);
    addActList("Pump 4", ActuatorType::Relay, 8);

    addActList("Mix invertor 1", ActuatorType::Invertor, 15);

    qDebug() << "create " << actList.size() << "actuators";
}

void Global::addActList(QString name, ActuatorType::actT tp, int addres) {
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
void Global::creatSensList() {
    addSensList("Tvertne 1 sensors DI", SensorType::Digital, 1);
    addSensList("Tvertne 1 sensors AN", SensorType::Analog, 2);

    addSensList("Tvertne 2 sensors DI", SensorType::Digital, 3);
    addSensList("Tvertne 2 sensors AN", SensorType::Analog, 5);

    addSensList("Tvertne 3 sensors DI", SensorType::Digital, 4);
    addSensList("Tvertne 3 sensors AN", SensorType::Analog, 5);

    addSensList("Tvertne 4 sensors DI", SensorType::Digital, 6);
    addSensList("Tvertne 4 sensors AN", SensorType::Analog, 7);
    addSensList("Scale AN", SensorType::Analog, 11);



    addSensList("Pump1 1 sensors AN", SensorType::Digital, 32);
    addSensList("Tvertne 2 sensors AN", SensorType::Digital, 33);


    qDebug() << "create " << sensList.size() << "sensors";
}

void Global::addSensList(QString name, SensorType::sensT tp, int addres) {
    sens data;

    data.type = tp;  //
    data.name = name;
    // data.analog = 0; VALUE
    // data.digital = 0; VALUE
    sensList.append(data);
    sensList[addres] = data;
}

void Global::createBallValve()
{
   BallValve* ballvalveTest = new BallValve(this,0,1,0,1);
    ballvalveTest->close();

}

void Global::needUpdateDIoutputs(int row, int val) {
    updateDataIn.need = true;
    updateDataIn.row = row;
    updateDataIn.val = val;
}

void Global::needUpdateSensorIn(int row, int val) {
    updateDataOut.need = true;
    updateDataOut.row = row;
    updateDataOut.val = val;
}

int Global::getTick() {
    return tickTimer.elapsed();
}

int Global::getnTick()
{
    return tickTimer.nsecsElapsed();
}

//void Global::addTick() {
//    tick++;
//}

int Global::getwaitTx() {
    return waitTx;
}

void Global::setwaitTx(int val) {
    waitTx = val;
}

QString Global::getDriveErrorTxt(int errCode)
{
    QString res = "Error code: ";
    res.append(QString::number(errCode));

    for(int i = 0; i < driveErrorCodes.size(); i++)
    {
        if (driveErrorCodes[i].code == errCode) {
            res.append(driveErrorCodes[i].name);
            //res.append("/n");
        }
    }
    // qDebug() << errCode << res;
    return res;
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

void Global::creatWidgList() {
    //      WidgetType::widgT ty,    name,       page, X,       Y,  size, options,  actAdr1, sensAdr1,  sensAdr2)

    addWidgList(WidgetType::Mix, "MIX", 1, 496, 27, 120, 0, set_mix_speed, set_mix_On_Off, 0);
    addWidgList(WidgetType::ScalesBase,    "Scales Base", 1,   393,  123,   172,  0, 0, 0, 0);
    addWidgList(WidgetType::ScalesMass,    "Scales Mass",1,    389,  48,   77, 0,0,scales_mass, 0);

    addWidgList(WidgetType::Dispax, "DISPAX", 1, 400, 330, 120, 0, set_dino_speed, set_dino_On_Off, 0);
    addWidgList(WidgetType::Label, "LABEL1", 1, 1644, 230, 250, 0, 0, 0, 0);
    addWidgList(WidgetType::Label, "LABEL2", 1, 233, 251, 250, 0, 0, 0, 0);
    addWidgList(WidgetType::Label, "LABEL3", 1, 243, 1, 250, 0, 0, 0, 0);

    addWidgList(WidgetType::Tvertne, "T2", 1, 1598, 1, 120, 0, 0, TVERTNE2LEVEL, TVERTNE2FULL);
    addWidgList(WidgetType::Tvertne, "T3", 1, 700, 310, 120, 0, 0, TVERTNE3LEVEL, TVERTNE3FULL);
    addWidgList(WidgetType::Tvertne, "T4", 1, 1000, 310, 120, 0, 0, TVERTNE4LEVEL, TVERTNE4FULL);
    addWidgList(WidgetType::Tvertne, "T5", 1, 1300, 310, 120, 0, 0, TVERTNE5LEVEL, TVERTNE5FULL);

    addWidgList(WidgetType::Pump, "PUMP S4", 1, 433, 483, 50, 0, set_pump1_speed, set_pump1_On_Off, 0);
    addWidgList(WidgetType::Pump, "PUMP S5", 1, 744, 61, 50, 0, set_pump1_speed, set_pump1_On_Off, 0);


    addWidgList(WidgetType::Valve, "Valve 2.1", 1, 608, 7, 25, 0, VALVE1ACT, Y2_1_open, Y2_1_close);
    addWidgList(WidgetType::Valve, "Valve 2.2", 1, 608, 147, 25, 0, VALVE1ACT, Y2_2_open, Y2_2_close);
    addWidgList(WidgetType::Valve, "Valve 2.3", 1, 1524, 124, 25, 0, VALVE1ACT, Y2_3_open, Y2_3_close);
    addWidgList(WidgetType::Valve, "Valve 2.4", 1, 1452, 124, 25, 0, VALVE1ACT, Y2_4_open, Y2_4_close);

    addWidgList(WidgetType::Valve, "Valve 3.1", 1, 709, 273, 25, 0, VALVE1ACT, Y3_1_open, Y3_1_close);
    addWidgList(WidgetType::Valve, "Valve 3.2", 1, 782, 275, 25, 0, VALVE1ACT, Y3_2_open, Y3_2_close);
    addWidgList(WidgetType::Valve, "Valve 3.3", 1, 710, 458, 25, 0, VALVE1ACT, Y3_3_open, Y3_3_close);
    addWidgList(WidgetType::Valve, "Valve 3.4", 1, 781, 458, 25, 0, VALVE1ACT, Y3_4_open, Y3_4_close);

    addWidgList(WidgetType::Valve, "Valve 4.1", 1, 1009, 225, 25, 0, VALVE1ACT, Y4_1_open, Y4_1_close);
    addWidgList(WidgetType::Valve, "Valve 4.2", 1, 1080, 224, 25, 0, VALVE1ACT, Y4_2_open, Y4_2_close);
    addWidgList(WidgetType::Valve, "Valve 4.3", 1, 1382, 563, 25, 0, VALVE1ACT, Y4_3_open, Y4_3_close);
    addWidgList(WidgetType::Valve, "Valve 4.4", 1, 1310, 563, 25, 0, VALVE1ACT, Y4_4_open, Y4_4_close);

    addWidgList(WidgetType::Valve, "Valve 5.1", 1, 1307, 174, 25, 0, VALVE1ACT, Y5_1_open, Y5_1_close);
    addWidgList(WidgetType::Valve, "Valve 5.2", 1, 1379, 173, 25, 0, VALVE1ACT, Y5_2_open, Y5_2_close);
    addWidgList(WidgetType::Valve, "Valve 5.3", 1, 1010, 514, 25, 0, VALVE1ACT, Y5_3_open, Y5_3_close);
    addWidgList(WidgetType::Valve, "Valve 5.4", 1, 1081, 513, 25, 0, VALVE1ACT, Y5_4_open, Y5_4_close);


    addWidgList(WidgetType::Valve, "Valve 6.2", 1, 468, 273, 25, 0, VALVE1ACT, VALVE1SWOPEN, VALVE1SWCLOSE);
    addWidgList(WidgetType::Valve, "Valve 6.3", 1, 408, 273, 25, 0, VALVE1ACT, VALVE1SWOPEN, VALVE1SWCLOSE);


    // PIPE

    addWidgList(WidgetType::Pipe, "Pipe 1", 1, 1480, 130, 41, 90, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 2", 1, 662, 80, 75, 90, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 3", 1, 650, 13, 153, 0, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 4", 1, 800, 80, 694, 90, 0, 0, 0);

    addWidgList(WidgetType::Pipe, "Pipe 5", 1, 570, 133, 27,  0, 0,0,0);
    addWidgList(WidgetType::Pipe, "Pipe 6", 1, 750, 282, 36, 0, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 7", 1, 736, 280, 41, 90, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 8", 1, 1335, 180, 41, 90, 0, 0, 0);

    addWidgList(WidgetType::Pipe, "Pipe 9", 1, 1150, 138, 37, 0, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 10", 1, 1551, 130, 90, 90, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 11", 1, 1050, 230, 88, 0, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 12", 1, 635, 13, 23, 90, 0, 0, 0);

    addWidgList(WidgetType::Pipe, "Pipe 13", 1, 1493, 80, 56, 0, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 14", 1, 495, 280, 211, 90, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 15", 1, 1036, 230, 41, 90, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 16", 1, 246,  32, 243,  90, 0,0,0);

    addWidgList(WidgetType::Pipe, "Pipe 17", 1, 1108, 230, 57, 90, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 18", 1, 1037, 520, 41, 90, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 19", 1, 450, 570, 856, 90, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 20", 1, 854, 620, 799, 90, 0, 0, 0);


    addWidgList(WidgetType::Pipe, "Pipe 21", 1, 450, 288, 38, 0, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 22", 1, 570, 13, 35, 90, 0, 0, 0);

    addWidgList(WidgetType::Pipe, "Pipe 23", 1, 650, 180, 100, 0, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 24", 1, 660, 230, 344, 90, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 25", 1, 1350, 428, 148, 0, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 26", 1, 810, 281, 46, 90, 0, 0, 0);

    addWidgList(WidgetType::Pipe, "Pipe 27", 1, 1050, 428, 97, 0, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 28", 1, 736, 464, 41, 90, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 29", 1, 1337, 570, 41, 90, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 30", 1, 750, 428, 44, 0, 0, 0, 0);

    addWidgList(WidgetType::Pipe, "Pipe 31", 1, 660, 180, 643, 90, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 32", 1, 435, 280, 30, 90, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 33", 1, 246, 280, 156, 90, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 34", 1, 808, 464, 57, 90, 0, 0, 0);

    addWidgList(WidgetType::Pipe, "Pipe 35", 1, 450, 427, 50, 0, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 36", 1, 623, 475, 103, 0, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 37", 1, 850, 536, 29, 0, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 38", 1, 623, 464, 84, 90, 0, 0, 0);

    addWidgList(WidgetType::Pipe, "Pipe 39", 1, 850, 470, 45, 0, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 40", 1, 624, 520, 383, 90, 0, 0, 0);

    addWidgList(WidgetType::Pipe, "Pipe 41", 1, 570, 18, 27, 0, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 42", 1, 850, 246, 46, 0, 0, 0, 0);

    addWidgList(WidgetType::Pipe, "Pipe 43", 1, 850, 587, 44, 0, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 44", 1, 1410, 568, 22, 90, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 45", 1, 1150, 527, 38, 0, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 46", 1, 1151, 586, 40, 0, 0, 0, 0);

    addWidgList(WidgetType::Pipe, "Pipe 47", 1, 850, 130, 598, 90, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 48", 1, 570, 154, 35, 90, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 49", 1, 1109, 520, 56, 90, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 50", 1, 1650, 287, 344, 0, 0, 0, 0);

    addWidgList(WidgetType::Pipe, "Pipe 51", 1, 1627, 116, 17, 0, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 52", 1, 850, 196, 29, 0, 0, 0, 0);

    addWidgList(WidgetType::Pipe, "Pipe 53", 1, 850, 130, 48, 0, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 54", 1, 1407, 180, 22, 90, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 55", 1, 1150, 196, 45, 0, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 56", 1, 1418, 130, 61, 0, 0, 0, 0);

    addWidgList(WidgetType::Pipe, "Pipe 57", 1, 1350, 180, 138, 0, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 58", 1, 1651, 280, 104, 90, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 59", 1, 1418, 575, 55, 0, 0, 0, 0);
    addWidgList(WidgetType::Pipe, "Pipe 60", 1, 450, 539, 42, 0, 0, 0, 0);

    addWidgList(WidgetType::Pipe, "Pipe 61", 1, 635, 154, 23, 90, 0, 0, 0);






    // addWidgList(WidgetType::ScalesBase,    "Scales Base", 1,   772,  142,    100,  0,     0,   0, 0);
    // addWidgList(WidgetType::ScalesMass,    "Scales Mass",1,    770,  30,   100, 0,    0,   scales_mass, 0);


    /*

     addWidgList(WidgetType::ScalesBase,    "Scales Base",    413,        545,    250,   15, 0,   0,  0,0,0,0);
     addWidgList(WidgetType::ScalesMass,    "Scales Mass",    584,       485,     62,   0,  0,   0,  0,11,0,0);

 */


    qDebug() << "create " << widHash.size() << "widgets";
}



void Global::addWidgList(WidgetType::widgT ty, QString name, int page, int X, int Y, int size, int options, int actAdr1, int sensAdr1, int sensAdr2) {
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
