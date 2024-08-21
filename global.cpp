#include "global.h"
#include <Qdebug>
#include <QTimer>
#include <QElapsedTimer>
//#include "def.h"
//#include "ballvalve.h"



//using namespace inputWidg;
//using namespace inputAct;
//using namespace inputSens;

Global::Global() {
    tickTimer.start();
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
    for (int i = 0; i < 10; i++) {    // 10 = max nr of Tvertne
        tvertneTemp.append(i);
    }

    qDebug() << sensList.size() << actList.size();

    createBallValve();
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


    for (int i = 0; i < MAX_DIinput + VIRUAL_PORTS ; i++) {
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
    /*
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
*/
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
    bvalve bv;
    //BallValve(Global* global,QString name, int outOpen, int outClose, int inOpen, int inClose, QObject* parent = nullptr);

    ballvalveTest0 = new BallValve(this,"ballvalveTest0",0,0,0,0);
    bv.npk = 0;
    bv.bValvePtr = ballvalveTest0;
    ballValveList.append(bv);

    ballvalveTest1 = new BallValve(this,"ballvalveTest1",0,0,0,0);
    bv.npk = 1;
    bv.bValvePtr = ballvalveTest1;
    ballValveList.append(bv);

    ballvalveTest2 = new BallValve(this,"ballvalveTest2",0,0,0,0);
    bv.npk = 2;
    bv.bValvePtr = ballvalveTest2;
    ballValveList.append(bv);

    ballvalveTest3 = new BallValve(this,"ballvalveTest3",0,0,0,0);
    bv.npk = 3;
    bv.bValvePtr = ballvalveTest3;
    ballValveList.append(bv);


    ballvalveTest4 = new BallValve(this,"Y4.1",32,33,49,48);
    bv.npk = 4;
    bv.bValvePtr = ballvalveTest4;
    ballValveList.append(bv);

    ballvalveTest5 = new BallValve(this,"Y4.2",34,35,51,50);
    bv.npk = 5;
    bv.bValvePtr = ballvalveTest5;
    ballValveList.append(bv);

    ballvalveTest6 = new BallValve(this,"Y4.3",36,37,53,52);
    bv.npk = 6;
    bv.bValvePtr = ballvalveTest6;
    ballValveList.append(bv);

    ballvalveTest7 = new BallValve(this,"Y4.4",38,39,55,54);
    bv.npk = 7;
    bv.bValvePtr = ballvalveTest7;
    ballValveList.append(bv);


    ballvalveTest8 = new BallValve(this,"Y3.1",24,25,41,40);
    bv.npk = 8;
    bv.bValvePtr = ballvalveTest8;
    ballValveList.append(bv);

    ballvalveTest9 = new BallValve(this,"Y3.2",26,27,43,42);
    bv.npk = 9;
    bv.bValvePtr = ballvalveTest9;
    ballValveList.append(bv);

    ballvalveTest10 = new BallValve(this,"Y2.4",22,23,39,38);
    bv.npk = 10;
    bv.bValvePtr = ballvalveTest10;
    ballValveList.append(bv);

    ballvalveTest11 = new BallValve(this,"Y2.3",20,21,37,36);
    bv.npk = 11;
    bv.bValvePtr = ballvalveTest11;
    ballValveList.append(bv);

    ballvalveTest12 = new BallValve(this,"Y2.1",16,17,33,32);
    bv.npk = 12;
    bv.bValvePtr = ballvalveTest12;
    ballValveList.append(bv);

    ballvalveTest13 = new BallValve(this,"Y2.2",18,19,35,34);
    bv.npk = 13;
    bv.bValvePtr = ballvalveTest13;
    ballValveList.append(bv);

    ballvalveTest14 = new BallValve(this,"Y3.3",28,29,45,44);
    bv.npk = 14;
    bv.bValvePtr = ballvalveTest14;
    ballValveList.append(bv);

    ballvalveTest15 = new BallValve(this,"3.4",30,31,47,46);
    bv.npk = 15;
    bv.bValvePtr = ballvalveTest15;
    ballValveList.append(bv);


    ballvalveTest16 = new BallValve(this,"ballvalveTest16",0,0,0,0);
    bv.npk = 16;
    bv.bValvePtr = ballvalveTest16;
    ballValveList.append(bv);

    ballvalveTest17 = new BallValve(this,"ballvalveTest17",0,0,0,0);
    bv.npk = 17;
    bv.bValvePtr = ballvalveTest17;
    ballValveList.append(bv);


    qDebug() << "ballValveList[0].name" << ballValveList[0].bValvePtr->name << ballValveList[1].bValvePtr->name;

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

for DIZPAX:
act_sensAddres act  address
    var1   - speed	// cik ātri
    var2 -

for MIX:
act_sensAddres act  address
    var1   - speed	// cik ātri
    var2 -

for DINO:
act_sensAddres act  address
    var1   - speed	// cik ātri
    var2 -


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
    var1  - ope 0 or 90deg


for pump:
act_sensAddres act  address
    var1  - on/off  forvard
    var2   - on/off   revers



for ScalesMass:
act_sensAddres act  address
    var1   - massValue	// cik ātri
    var2 -

for Tvertne:
act_sensAddres act  address
    var1   - fill value in %
    var2 -  full

page = 0   draw on "Mix" page
page = 1   draw on "Dyno" page
page = 3   draw on all pages

    */

void Global::creatWidgList() {
    //addWidgList(WidgetType::widgT ty,QString name, int npk, int page, int X, int Y, int size, int var1, int var2) {

    // addWidgList(WidgetType::Dyno, 0, 1, 176, 1, 74, set_dino0_speed, set_dino0_On_Off);
    addWidgList(WidgetType::Conveyor, "Šneka konveijer", 0, 1, 75, 1, 153, set_dino0_speed, set_dino0_On_Off);


    addWidgList(WidgetType::Mix,"Mixeris", 0, 1, 496, 27, 120, set_mix_speed, set_mix_On_Off);
    addWidgList(WidgetType::ScalesBase,"Svaru pamatne ",    0, 1,   393,  123,   172,  0, 0);
    addWidgList(WidgetType::ScalesMass,"Svars", 0,1,    389,  48,   77, scales_mass,scales_mass);

    addWidgList(WidgetType::Dispax,"Dispax 3D", 0, 1, 400, 330, 120, set_dispax_On_Off, set_dispax_On_Off);
    addWidgList(WidgetType::Label,"Uzraksts 1", 0, 1, 1644, 230, 250, 0, 0);
    addWidgList(WidgetType::Label,"Uzraksts 2", 1, 1, 233, 251, 250, 0, 0);
    addWidgList(WidgetType::Label,"Uzraksts 3", 2, 1, 243, 1, 250, 0, 0);

    addWidgList(WidgetType::Tvertne,"4. Tvertne",0, 1, 1598, 1, 120, TVERTNE4LEVELPROC, TVERTNE4FULL);
    addWidgList(WidgetType::Tvertne,"3. Tvertne",1, 1, 700, 310, 120, TVERTNE3LEVELPROC, TVERTNE3FULL);
    addWidgList(WidgetType::Tvertne,"2. Tvertne",2, 1, 1000, 310, 120, TVERTNE2LEVELPROC, TVERTNE2FULL);
    addWidgList(WidgetType::Tvertne,"1. Tvertne",3, 1, 1300, 310, 120, TVERTNE1LEVELPROC, TVERTNE1FULL);

    addWidgList(WidgetType::Pump,"Sūknis Sapropela 2.2",0, 1, 744, 61, 50, set_pump2_2_On_Off_FW, set_pump2_2_On_Off_RW);
    addWidgList(WidgetType::Pump,"Sūknis MOHNO 5.5",1, 1, 433, 483, 50, On_Pump_2_speed, On_Pump_2_ONOFF);



    addWidgList(WidgetType::Valve,"ballvalveTest0", 0, 1, 608, 7, 25, 0, 0);
    addWidgList(WidgetType::Valve,"ballvalveTest1", 1, 1, 608, 147, 25, 0, 0);
    addWidgList(WidgetType::Valve,"ballvalveTest2", 2, 1, 1524, 124, 25, 0, 0);
    addWidgList(WidgetType::Valve,"ballvalveTest3", 3, 1, 1452, 124, 25, 0, 0);

    addWidgList(WidgetType::Valve,"Y4.1", 4, 1, 709, 273, 25, 0, 0);
    addWidgList(WidgetType::Valve,"Y4.2", 5, 1, 782, 275, 25, 0, 0);
    addWidgList(WidgetType::Valve,"Y4.3", 6, 1, 710, 458, 25, 0, 0);
    addWidgList(WidgetType::Valve,"Y4.4", 7, 1, 781, 458, 25, 0, 0);

    addWidgList(WidgetType::Valve,"Y3.1", 8, 1, 1009, 225, 25, 0, 0);
    addWidgList(WidgetType::Valve,"Y3.2", 9, 1, 1080, 224, 25, 0, 0);
    addWidgList(WidgetType::Valve,"Y2.4", 10, 1, 1382, 563, 25, 0, 0);
    addWidgList(WidgetType::Valve,"Y2.3", 11, 1, 1310, 563, 25, 0, 0);

    addWidgList(WidgetType::Valve,"Y2.1", 12, 1, 1307, 174, 25, 0, 0);
    addWidgList(WidgetType::Valve,"Y2.2", 13, 1, 1379, 173, 25, 0, 0);
    addWidgList(WidgetType::Valve,"Y3.3", 14, 1, 1010, 514, 25, 0, 0);
    addWidgList(WidgetType::Valve,"3.4", 15, 1, 1081, 513, 25, 0, 0);


    addWidgList(WidgetType::Valve,"ballvalveTest16", 16, 1, 468, 273, 25, 0, 0);
    addWidgList(WidgetType::Valve,"ballvalveTest17", 17, 1, 408, 273, 25, 0, 0);


    // PIPE

    addWidgList(WidgetType::Pipe,"Caurule", 0, 1, 1480, 130, 41, 90, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 1, 1, 662, 80, 75, 90, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 2, 1, 650, 13, 153, 0, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 3, 1, 800, 80, 694, 90, 0);

    addWidgList(WidgetType::Pipe,"Caurule", 4, 1, 570, 133, 27,  0, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 5, 1, 750, 282, 36, 0, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 6, 1, 736, 280, 41, 90, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 7, 1, 1335, 180, 41, 90, 0);

    addWidgList(WidgetType::Pipe,"Caurule", 8, 1, 1150, 138, 37, 0, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 9, 1, 1551, 130, 90, 90, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 10, 1, 1050, 230, 88, 0, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 11, 1, 635, 13, 23, 90, 0);

    addWidgList(WidgetType::Pipe,"Caurule", 12, 1, 1493, 80, 56, 0, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 13, 1, 495, 280, 211, 90, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 14, 1, 1036, 230, 41, 90, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 15, 1, 246,  32, 243,  90, 0);

    addWidgList(WidgetType::Pipe,"Caurule", 16, 1, 1108, 230, 57, 90, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 17, 1, 1037, 520, 41, 90, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 18, 1, 450, 570, 856, 90, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 19, 1, 854, 620, 799, 90, 0);

    addWidgList(WidgetType::Pipe,"Caurule", 20, 1, 450, 288, 38, 0, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 21, 1, 570, 13, 35, 90, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 22, 1, 650, 180, 100, 0, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 23, 1, 660, 230, 344, 90, 0);

    addWidgList(WidgetType::Pipe,"Caurule", 24, 1, 1350, 428, 148, 0, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 25, 1, 810, 281, 46, 90, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 26, 1, 1050, 428, 97, 0, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 27, 1, 736, 464, 41, 90, 0);

    addWidgList(WidgetType::Pipe,"Caurule", 28, 1, 1337, 570, 41, 90, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 29, 1, 750, 428, 44, 0, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 30, 1, 660, 180, 643, 90, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 31, 1, 435, 280, 30, 90, 0);

    addWidgList(WidgetType::Pipe,"Caurule", 32, 1, 246, 280, 156, 90, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 33, 1, 808, 464, 57, 90, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 34, 1, 450, 427, 50, 0, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 35, 1, 623, 475, 103, 0, 0);

    addWidgList(WidgetType::Pipe,"Caurule", 36, 1, 850, 536, 29, 0, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 37, 1, 623, 464, 84, 90, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 38, 1, 850, 470, 45, 0, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 39, 1, 624, 520, 383, 90, 0);

    addWidgList(WidgetType::Pipe,"Caurule", 40, 1, 570, 18, 27, 0, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 41, 1, 850, 246, 46, 0, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 42, 1, 850, 587, 44, 0, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 43, 1, 1410, 568, 22, 90, 0);

    addWidgList(WidgetType::Pipe,"Caurule", 44, 1, 1150, 527, 38, 0, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 45, 1, 1151, 586, 40, 0, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 46, 1, 850, 130, 598, 90, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 47, 1, 570, 154, 35, 90, 0);

    addWidgList(WidgetType::Pipe,"Caurule", 48, 1, 1109, 520, 56, 90, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 49, 1, 1650, 287, 344, 0, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 50, 1, 1627, 116, 17, 0, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 51, 1, 850, 196, 29, 0, 0);

    addWidgList(WidgetType::Pipe,"Caurule", 52, 1, 850, 130, 48, 0, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 53, 1, 1407, 180, 22, 90, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 54, 1, 1150, 196, 45, 0, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 55, 1, 1418, 130, 61, 0, 0);

    addWidgList(WidgetType::Pipe,"Caurule", 56, 1, 1350, 180, 138, 0, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 57, 1, 1651, 280, 104, 90, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 58, 1, 1418, 575, 55, 0, 0);
    addWidgList(WidgetType::Pipe,"Caurule", 59, 1, 450, 539, 42, 0, 0);

    addWidgList(WidgetType::Pipe,"Caurule", 60, 1, 635, 154, 23, 90, 0);


    qDebug() << "create " << widHash.size() << "widgets";
}



void Global::addWidgList(WidgetType::widgT ty, QString name, int npk, int page, int X, int Y, int size, int var1, int var2) {
    wdataStruct data;
    data.type = ty;     // widget type
    data.npk = npk;   // neme
    data.page = page;   // page Nr procUI1 = 1 procUI2 = 2

    data.startX = X;    // coordinate X
    data.startY = Y;    // coordinate Y
    data.startSize = size;  // size zoom
    data.var1 = var1; // valve angle, pipe angle
    data.var2 = var2; // actuator address
    //   data.name = name;


    if (ty == WidgetType::Pipe){
        name.append(" ");
        name.append(QString::number(npk));
    }

    if (ty == WidgetType::Valve){
        name = ballValveList[npk].bValvePtr->name;
    }

    /*
    if (ty == WidgetType::Conveyor){
      name.append("Conveyor ");
      name.append(QString::number(npk));
    }
    if (ty == WidgetType::Dyno){
        name.append("Dyno ");
        name.append(QString::number(npk));
    }

    if (ty == WidgetType::Mix){
        name.append("Mikseris ");
        name.append(QString::number(npk));
    }


    if (ty == WidgetType::Pump){
        name.append("Sūknis ");
        name.append(QString::number(npk));
    }


    if (ty == WidgetType::Tvertne){
        switch (npk) {
        case 0:
            name.append("4. Tvertne");
            break;
        case 1:
            name.append("3. Tvertne");
            break;
        case 2:
            name.append("2. Tvertne");
            break;
        case 3:
            name.append("1. Tvertne");
            break;
        default:
            break;
        }

        //name.append(QString::number(npk));
    }
    if (ty == WidgetType::ScalesBase){
        name.append("ScalesBase ");
        name.append(QString::number(npk));
    }
    if (ty == WidgetType::ScalesMass){
        name.append("ScalesMass ");
        name.append(QString::number(npk));
    }
    if (ty == WidgetType::Dispax){
        name.append("Dispax ");
        name.append(QString::number(npk));
    }
    if (ty == WidgetType::Label){
        name.append("Label ");
        name.append(QString::number(npk));
    }

    */

    data.name = name;
    widHash.insert(name, data);
}
