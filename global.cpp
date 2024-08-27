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

    for (int iter = pipe_dir0; iter <= pipe_dir70; iter++) {

        io.name = "pipe_direction";
        DIoutput[iter].name = "pipe_direction";
        DIoutput[iter].value = 0;// iter %3;//0;
        DIoutput[iter].update = false;
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
    createComboxlist();
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



/*
 *  QString name    valve name
 * int outOpen      Output valve actuator OPEN
 * int outClose     Output valve actuator CLOSE
 * int inOpen       Input valve Open sensor
 * int inClose      Input valve Close sensor
 * bv.npk = 0;      valve No
 * bv.bValvePtr     ptr to valve object
 *
 */
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


    ballvalveTest4 = new BallValve(this,"Y4.1",Y4_1_atvērt_4KY1,Y4_1_aizv_4KY2,Y4_1_open,Y4_1_close);
    bv.npk = 4;
    bv.bValvePtr = ballvalveTest4;
    ballValveList.append(bv);

    ballvalveTest5 = new BallValve(this,"Y4.2",Y4_2_atvērt_4KY3,Y4_2_aizv_4KY4,Y4_2_open,Y4_2_close);
    bv.npk = 5;
    bv.bValvePtr = ballvalveTest5;
    ballValveList.append(bv);

    ballvalveTest6 = new BallValve(this,"Y4.3",Y4_3_atvērt_4KY5,Y4_3_aizv_4KY6,Y4_3_open,Y4_3_close);
    bv.npk = 6;
    bv.bValvePtr = ballvalveTest6;
    ballValveList.append(bv);

    ballvalveTest7 = new BallValve(this,"Y4.4",Y4_4_atvērt_4KY7,Y4_4_aizv_4KY8,Y4_4_open,Y4_4_close);
    bv.npk = 7;
    bv.bValvePtr = ballvalveTest7;
    ballValveList.append(bv);


    ballvalveTest8 = new BallValve(this,"Y3.1",Y3_1_atvērt,Y3_1_aizv,Y3_1_open,Y3_1_close);
    bv.npk = 8;
    bv.bValvePtr = ballvalveTest8;
    ballValveList.append(bv);

    ballvalveTest9 = new BallValve(this,"Y3.2",Y3_2_atvērt,Y3_2_aizv,Y3_2_open,Y3_2_close);
    bv.npk = 9;
    bv.bValvePtr = ballvalveTest9;
    ballValveList.append(bv);

    ballvalveTest10 = new BallValve(this,"Y2.4",Y2_4_atvērt,Y2_4_aizv,Y2_4_open,Y2_4_close);
    bv.npk = 10;
    bv.bValvePtr = ballvalveTest10;
    ballValveList.append(bv);

    ballvalveTest11 = new BallValve(this,"Y2.3",Y2_3_atvērt,Y2_3_aizv,Y2_3_open,Y2_3_close);
    bv.npk = 11;
    bv.bValvePtr = ballvalveTest11;
    ballValveList.append(bv);

    ballvalveTest12 = new BallValve(this,"Y2.1",Y2_1_atvērt,Y2_1_aizv,Y2_1_open,Y2_1_close);
    bv.npk = 12;
    bv.bValvePtr = ballvalveTest12;
    ballValveList.append(bv);

    ballvalveTest13 = new BallValve(this,"Y2.2",Y2_2_atvērt,Y2_2_aizv,Y2_2_open,Y2_2_close);
    bv.npk = 13;
    bv.bValvePtr = ballvalveTest13;
    ballValveList.append(bv);

    ballvalveTest14 = new BallValve(this,"Y3.3",Y3_3_atvērt,Y3_3_aizv,Y3_3_open,Y3_3_close);
    bv.npk = 14;
    bv.bValvePtr = ballvalveTest14;
    ballValveList.append(bv);

    ballvalveTest15 = new BallValve(this,"3.4",Y3_4_atvērt,Y3_4_aizv,Y3_4_open,Y3_4_close);
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


    ballvalveTest18 = new BallValve(this,"ballvalveTest18",0,0,0,0);
    bv.npk = 18;
    bv.bValvePtr = ballvalveTest18;
    ballValveList.append(bv);

    ballvalveTest19 = new BallValve(this,"ballvalveTest19",0,0,0,0);
    bv.npk = 19;
    bv.bValvePtr = ballvalveTest19;
    ballValveList.append(bv);

    ballvalveTest20 = new BallValve(this,"ballvalveTest20",0,0,0,0);
    bv.npk = 20;
    bv.bValvePtr = ballvalveTest20;
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

WidgetType::widgT ty Widget type
QString name  Widget name
int npk       Widget number
int page      display in page 1 or 2

Left upper corner coordinates:
int Y
int size        start size



for DIZPAX:
act_sensAddres act  address
    var1   - speed	// cik ātri
    var2 -

for MIX:
    var1   - speed	// invertor drive
    var2 -  1=On, 0=Off

for DINO:
act_sensAddres act  address
    var1   - speed	// cik ātri
    var2 -


for  Pipe :
int size        start len
var1 = Angle > 0 fron vertical CCW  options
    Angle = 0  horisontal
    Angle = 90  vertical
var2  flow direction 0=>No flow,   1=>right,down    2=>left,up



for  Valve :
options Angle fron vertical CCW  options mean close  open = option + 90
Hight startSize
Width  startSizeWi
    var1  - ope 0 or 90deg


for pump:

    var1  - on/off  forvard  if relay switch
    var2   - on/off   revers if available

    var1   - speed	// if invertor drive
    var2 -  1=On, 0=Off


for Conveyor
    var1   - speed	// invertor drive
    var2 -  1=On, 0=Off

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

    addWidgList(WidgetType::Dyno, "Dinamill", 0, 1, 1743, 253, 70, set_dino0_speed, set_dino0_On_Off);
    addWidgList(WidgetType::Conveyor, "Šneka konveijer", 0, 1, 385, 1, 146, set_dino0_speed, set_dino0_On_Off);


    addWidgList(WidgetType::Mix,"Mixeris", 0, 1, 519, 73, 120, set_mix_speed, set_mix_On_Off);
    addWidgList(WidgetType::ScalesBase,"Svaru pamatne ",  0, 1,   234,  166,   312,  0, 0);
    addWidgList(WidgetType::ScalesMass,"Svars", 0,1,    218,  77,   77, scales_mass,scales_mass);

    addWidgList(WidgetType::Dispax,"Dispax 3D", 0, 1, 400, 330, 120, set_dispax_On_Off, set_dispax_On_Off);
    addWidgList(WidgetType::Label,"Uzraksts 1", 0, 1, 1644, 230, 250, 0, 0);
    addWidgList(WidgetType::Label,"Uzraksts 2", 1, 1, 233, 251, 250, 0, 0);
    addWidgList(WidgetType::Label,"Uzraksts 3", 2, 1, 243, 1, 250, 0, 0);

    addWidgList(WidgetType::Tvertne,"4. Tvertne",0, 1, 1598, 1, 120, TVERTNE4LEVELPROC, TVERTNE4FULL);
    addWidgList(WidgetType::Tvertne,"3. Tvertne",1, 1, 700, 370, 120, TVERTNE3LEVELPROC, TVERTNE3FULL);
    addWidgList(WidgetType::Tvertne,"2. Tvertne",2, 1, 1000, 370, 120, TVERTNE2LEVELPROC, TVERTNE2FULL);
    addWidgList(WidgetType::Tvertne,"1. Tvertne",3, 1, 1300, 370, 120, TVERTNE1LEVELPROC, TVERTNE1FULL);

    addWidgList(WidgetType::Pump,"Sūknis Sapropela 2.2",0, 1, 1128, 10, 50, set_pump2_2_On_Off_FW, set_pump2_2_On_Off_RW);
    addWidgList(WidgetType::Pump,"Sūknis MOHNO 5.5",1, 1, 433, 483, 50, On_Pump_2_speed, On_Pump_2_ONOFF);
    addWidgList(WidgetType::Pump,"Sūknis Dinamill",2, 1, 1324, 10, 50, set_pump2_2_On_Off_FW, set_pump2_2_On_Off_RW);


    addWidgList(WidgetType::Valve,"ballvalveTest0", 0, 1, 705, 67, 30, 0, 0);
    addWidgList(WidgetType::Valve,"ballvalveTest1", 1, 1, 782, 67, 30, 0, 0);
    addWidgList(WidgetType::Valve,"ballvalveTest2", 2, 1, 1524, 160, 30, 0, 0);
    addWidgList(WidgetType::Valve,"ballvalveTest3", 3, 1, 1452, 160, 30, 0, 0);

    addWidgList(WidgetType::Valve,"Y4.1", 4, 1, 705, 320, 30, 0, 0);
    addWidgList(WidgetType::Valve,"Y4.2", 5, 1, 782, 320, 30, 0, 0);
    addWidgList(WidgetType::Valve,"Y4.3", 6, 1, 710, 529, 30, 0, 0);
    addWidgList(WidgetType::Valve,"Y4.4", 7, 1, 781, 529, 30, 0, 0);

    addWidgList(WidgetType::Valve,"Y3.1", 8, 1, 1009, 320, 30, 0, 0);
    addWidgList(WidgetType::Valve,"Y3.2", 9, 1, 1080, 320, 30, 0, 0);
    addWidgList(WidgetType::Valve,"Y3.3", 14, 1, 1010, 529, 30, 0, 0);
    addWidgList(WidgetType::Valve,"Y3.4", 15, 1, 1081, 529 , 30, 0, 0);

    addWidgList(WidgetType::Valve,"Y2.1", 12, 1, 1307, 320, 30, 0, 0);
    addWidgList(WidgetType::Valve,"Y2.2", 13, 1, 1379, 320, 30, 0, 0);
    addWidgList(WidgetType::Valve,"Y2.3", 11, 1, 1303, 529, 30, 0, 0);
    addWidgList(WidgetType::Valve,"Y2.4", 10, 1, 1382, 529, 30, 0, 0);

    addWidgList(WidgetType::Valve,"ballvalveTest16", 16, 1, 487, 283, 30, 0, 0);
    addWidgList(WidgetType::Valve,"ballvalveTest17", 17, 1, 408, 283, 30, 0, 0);


    // PIPE

    addWidgList(WidgetType::Pipe,"Caurule", 0, 1, 750, 28, 369, 90, pipe_dir0);
    addWidgList(WidgetType::Pipe,"Caurule", 1, 1, 737, 70, 41, 90, pipe_dir1);
    addWidgList(WidgetType::Pipe,"Caurule", 2, 1, 751, 30, 40, 0, pipe_dir2);
    addWidgList(WidgetType::Pipe,"Caurule", 3, 1, 1381, 28, 123, 90, pipe_dir3);

    addWidgList(WidgetType::Pipe,"Caurule", 4, 1, 553, 162, 20,  0, pipe_dir4);
    addWidgList(WidgetType::Pipe,"Caurule", 5, 1, 750, 341, 27, 0, pipe_dir5);
    addWidgList(WidgetType::Pipe,"Caurule", 6, 1, 736, 330, 41, 90, pipe_dir6);
    addWidgList(WidgetType::Pipe,"Caurule", 7, 1, 1335, 330, 41, 90, pipe_dir7);

    addWidgList(WidgetType::Pipe,"Caurule", 8, 1, 1252, 291, 43, 0, pipe_dir8);
    addWidgList(WidgetType::Pipe,"Caurule", 9, 1, 1561, 170, 90, 90, pipe_dir9);
    addWidgList(WidgetType::Pipe,"Caurule", 10, 1, 1050, 331, 42, 0, pipe_dir10);
    addWidgList(WidgetType::Pipe,"Caurule", 11, 1, 571, 70, 127, 90, pipe_dir11);

    addWidgList(WidgetType::Pipe,"Caurule", 12, 1, 1493, 28, 143, 0, pipe_dir12);
    addWidgList(WidgetType::Pipe,"Caurule", 13, 1, 525, 290, 740, 90, pipe_dir13);
    addWidgList(WidgetType::Pipe,"Caurule", 14, 1, 1037, 330, 41, 90, pipe_dir14);
    addWidgList(WidgetType::Pipe,"Caurule", 15, 1, 565,  170, 280,  90, pipe_dir15);

    addWidgList(WidgetType::Pipe,"Caurule", 16, 1, 1108, 330, 57, 90, pipe_dir16);
    addWidgList(WidgetType::Pipe,"Caurule", 17, 1, 1037, 535, 41, 90, pipe_dir17);
    addWidgList(WidgetType::Pipe,"Caurule", 18, 1, 450, 595, 815, 90, pipe_dir18);
    addWidgList(WidgetType::Pipe,"Caurule", 19, 1, 854, 655, 799, 90, pipe_dir29);

    addWidgList(WidgetType::Pipe,"Caurule", 20, 1, 450, 290, 35, 0, pipe_dir20);
    addWidgList(WidgetType::Pipe,"Caurule", 21, 1, 870, 170, 577, 90, pipe_dir21);
    addWidgList(WidgetType::Pipe,"Caurule", 22, 1, 650, 290, 52, 0, pipe_dir22);
    addWidgList(WidgetType::Pipe,"Caurule", 23, 1, 660, 290, 344, 90, pipe_dir23);

    addWidgList(WidgetType::Pipe,"Caurule", 24, 1, 1350, 490, 52, 0, pipe_dir24);
    addWidgList(WidgetType::Pipe,"Caurule", 25, 1, 810, 330, 46, 90, pipe_dir25);
    addWidgList(WidgetType::Pipe,"Caurule", 26, 1, 1050, 490, 52, 0, pipe_dir26);
    addWidgList(WidgetType::Pipe,"Caurule", 27, 1, 736, 535, 41, 90, pipe_dir27);

    addWidgList(WidgetType::Pipe,"Caurule", 28, 1, 1337, 535, 41, 90, pipe_dir28);
    addWidgList(WidgetType::Pipe,"Caurule", 29, 1, 750, 490, 45, 0, pipe_dir29);
    addWidgList(WidgetType::Pipe,"Caurule", 30, 1, 960, 330, 41, 90, pipe_dir30);
    addWidgList(WidgetType::Pipe,"Caurule", 31, 1, 435, 290, 46, 90, pipe_dir31);

    addWidgList(WidgetType::Pipe,"Caurule", 32, 1, 246, 290, 156, 90, pipe_dir32);
    addWidgList(WidgetType::Pipe,"Caurule", 33, 1, 808, 535, 57, 90, pipe_dir33);
    addWidgList(WidgetType::Pipe,"Caurule", 34, 1, 450, 427, 50, 0, pipe_dir34);
    addWidgList(WidgetType::Pipe,"Caurule", 35, 1, 650, 535, 68, 0, pipe_dir35);

    addWidgList(WidgetType::Pipe,"Caurule", 36, 1, 1252, 535, 65, 0, pipe_dir36);
    addWidgList(WidgetType::Pipe,"Caurule", 37, 1, 650, 535, 56, 90, pipe_dir37);
    addWidgList(WidgetType::Pipe,"Caurule", 38, 1, 850, 535, 56, 0, pipe_dir38);
    addWidgList(WidgetType::Pipe,"Caurule", 39, 1, 960, 535, 44, 90, pipe_dir39);

    addWidgList(WidgetType::Pipe,"Caurule", 40, 1, 570, 73, 18, 0, pipe_dir40);
    addWidgList(WidgetType::Pipe,"Caurule", 41, 1, 850, 307, 35, 0, pipe_dir41);
    addWidgList(WidgetType::Pipe,"Caurule", 42, 1, 850, 612, 55, 0, pipe_dir42);
    addWidgList(WidgetType::Pipe,"Caurule", 43, 1, 1417, 535, 83, 90, pipe_dir43);

    addWidgList(WidgetType::Pipe,"Caurule", 44, 1, 1150, 535, 56, 0, pipe_dir44);
    addWidgList(WidgetType::Pipe,"Caurule", 45, 1, 1151, 612, 46, 0, pipe_dir45);
    addWidgList(WidgetType::Pipe,"Caurule", 46, 1, 850, 230, 653, 90, pipe_dir46);
    addWidgList(WidgetType::Pipe,"Caurule", 47, 1, 1485, 170, 35, 90, pipe_dir47);

    addWidgList(WidgetType::Pipe,"Caurule", 48, 1, 1109, 535, 44, 90, pipe_dir48);
    addWidgList(WidgetType::Pipe,"Caurule", 49, 1, 1650, 287, 379, 0, pipe_dir49);
    addWidgList(WidgetType::Pipe,"Caurule", 50, 1, 1644, 126, 56, 0, pipe_dir50);
    addWidgList(WidgetType::Pipe,"Caurule", 51, 1, 956, 299, 42, 0, pipe_dir51);

    addWidgList(WidgetType::Pipe,"Caurule", 52, 1, 851, 77, 209, 0, pipe_dir52);
    addWidgList(WidgetType::Pipe,"Caurule", 53, 1, 1407, 330, 96, 90, pipe_dir53);
    addWidgList(WidgetType::Pipe,"Caurule", 54, 1, 1150, 307, 33, 0, pipe_dir54);
    addWidgList(WidgetType::Pipe,"Caurule", 55, 1, 1350, 335, 38, 0, pipe_dir55);

    addWidgList(WidgetType::Pipe,"Caurule", 56, 1, 1493, 231, 111, 0, pipe_dir56);
    addWidgList(WidgetType::Pipe,"Caurule", 57, 1, 1651, 280, 50, 90, pipe_dir57);
    addWidgList(WidgetType::Pipe,"Caurule", 58, 1, 1493, 535, 123, 0, pipe_dir58);
    addWidgList(WidgetType::Pipe,"Caurule", 59, 1, 450, 539, 68, 0, pipe_dir59);

    addWidgList(WidgetType::Pipe,"Caurule", 60, 1, 818, 70, 45, 90, pipe_dir60);
    addWidgList(WidgetType::Pipe,"Caurule", 61, 1, 661, 330, 41, 90, pipe_dir61);
    addWidgList(WidgetType::Pipe,"Caurule", 62, 1, 1186, 28, 129, 90, pipe_dir62);
    addWidgList(WidgetType::Pipe,"Caurule", 63, 1, 533, 50, 40, 0, pipe_dir63);
    addWidgList(WidgetType::Pipe,"Caurule", 64, 1, 959, 537, 64, 0, pipe_dir64);
    addWidgList(WidgetType::Pipe,"Caurule", 65, 1, 1255, 535, 44, 90, pipe_dir65);
    addWidgList(WidgetType::Pipe,"Caurule", 66, 1, 1150, 233, 53, 0, pipe_dir66);
    addWidgList(WidgetType::Pipe,"Caurule", 67, 1, 1252, 330, 49, 90, pipe_dir67);

  // 2 lapa

    addWidgList(WidgetType::Conveyor, "Šneka konveijer 1", 1, 2, 406, 368, 204, set_dino0_speed, set_dino0_On_Off);
    addWidgList(WidgetType::Mix,"Mixeris 1", 1, 2, 600, 439, 163, set_mix_speed, set_mix_On_Off);

    addWidgList(WidgetType::ScalesBase,"Svaru pamatne ",    1,2,   665,  577,   312,  0, 0);
    addWidgList(WidgetType::ScalesMass,"Svars", 1,2,    895,  500,  77, scales_mass,scales_mass);

    addWidgList(WidgetType::Label,"Uzraksts 4", 4, 2, 272, 20, 250, 0, 0);
    addWidgList(WidgetType::Label,"Uzraksts 5", 5, 2, 572, 20, 250, 0, 0);
    addWidgList(WidgetType::Label,"Uzraksts 6", 6, 2, 872, 20, 250, 0, 0);
    addWidgList(WidgetType::Label,"Uzraksts 7", 7, 2, 136, 250, 250, 0, 0);
    addWidgList(WidgetType::Label,"Uzraksts 8", 8, 2, 136, 300, 250, 0, 0);
    addWidgList(WidgetType::Label,"Uzraksts 9", 9, 2, 330, 387, 250, 0, 0);
    addWidgList(WidgetType::Label,"Uzraksts 10", 10, 2, 1055, 376, 250, 0, 0);
    addWidgList(WidgetType::Label,"Uzraksts 11", 11, 2, 570, 624, 250, 0, 0);

    addWidgList(WidgetType::Tvertne,"H2o Tvertne",5, 2, 300, 50, 120, TVERTNE1LEVELPROC, TVERTNE1FULL);
    addWidgList(WidgetType::Tvertne,"B Tvertne",6, 2, 600, 50, 120, TVERTNE2LEVELPROC, TVERTNE2FULL);
    addWidgList(WidgetType::Tvertne,"Na Tvertne",7, 2, 900, 50, 120, TVERTNE3LEVELPROC, TVERTNE3FULL);

    addWidgList(WidgetType::Pump,"Sūknis H2o",3, 2, 330, 200, 50, On_pilda_H2o, On_pilda_H2o);
    addWidgList(WidgetType::Pump,"Sūknis B",4, 2, 630, 200, 50, On_pilda_B, On_pilda_B);
    addWidgList(WidgetType::Pump,"Sūknis Na",5, 2, 930, 200, 50, On_pilda_Na, On_pilda_Na);
    addWidgList(WidgetType::Pump,"Sūknis Sapropela 2.2 2",6, 2, 930, 391, 50, set_pump2_2_On_Off_FW, set_pump2_2_On_Off_RW);

    addWidgList(WidgetType::Valve,"18 valve", 18, 2, 344, 310, 30, 0, 0);
    addWidgList(WidgetType::Valve,"19 valve", 19, 2, 644, 310, 30, 0, 0);
    addWidgList(WidgetType::Valve,"20 valve", 20, 2, 944, 310, 30, 0, 0);

    addWidgList(WidgetType::Pipe,"Caurule", 68, 2, 610, 441, 28, 0, pipe_dir60);
    addWidgList(WidgetType::Pipe,"Caurule", 69, 2, 630, 368, 102, 0, pipe_dir61);
    addWidgList(WidgetType::Pipe,"Caurule", 70, 2, 650, 347, 122, 0, pipe_dir62);
    addWidgList(WidgetType::Pipe,"Caurule", 71, 2, 670, 368, 102, 0, pipe_dir63);
    addWidgList(WidgetType::Pipe,"Caurule", 72, 2, 690, 410, 60, 0, pipe_dir64);

    addWidgList(WidgetType::Pipe,"Caurule", 73, 2, 350, 168, 27, 0, pipe_dir65);
    addWidgList(WidgetType::Pipe,"Caurule", 74, 2, 650, 168, 27, 0, pipe_dir66);
    addWidgList(WidgetType::Pipe,"Caurule", 75, 2, 950, 168, 27, 0, pipe_dir67);

    addWidgList(WidgetType::Pipe,"Caurule", 76, 2, 350, 257, 50, 0, pipe_dir65);
    addWidgList(WidgetType::Pipe,"Caurule", 77, 2, 650, 257, 50, 0, pipe_dir66);
    addWidgList(WidgetType::Pipe,"Caurule", 78, 2, 950, 257, 50, 0, pipe_dir67);

    addWidgList(WidgetType::Pipe,"Caurule", 79, 2, 350, 368, 282, 90, pipe_dir65);
    addWidgList(WidgetType::Pipe,"Caurule", 80, 2, 673, 368, 290, 90, pipe_dir66);
    addWidgList(WidgetType::Pipe,"Caurule", 81, 2, 690, 409, 233, 90, pipe_dir67);

    addWidgList(WidgetType::Pipe,"Caurule", 82, 2, 644, 555, 69, 0, pipe_dir67);

    addWidgList(WidgetType::Pipe,"Caurule", 83, 2, 350, 345, 32, 0, pipe_dir65);
    addWidgList(WidgetType::Pipe,"Caurule", 84, 2, 950, 345, 32, 0, pipe_dir67);

    addWidgList(WidgetType::Pipe,"Caurule", 85, 2, 990, 409, 300, 90, pipe_dir66);
    addWidgList(WidgetType::Pipe,"Caurule", 86, 2, 154, 283, 200, 90, pipe_dir65);

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
void Global::createComboxlist()
{
        pipeItems
        << "pipe_dir0"
        << "pipe_dir1"
        << "pipe_dir2"
        << "pipe_dir3"
        << "pipe_dir4"
        << "pipe_dir5"
        << "pipe_dir6"
        << "pipe_dir7"
        << "pipe_dir8"
        << "pipe_dir9"
        << "pipe_dir10"
        << "pipe_dir11"
        << "pipe_dir12"
        << "pipe_dir13"
        << "pipe_dir14"
        << "pipe_dir15"
        << "pipe_dir16"
        << "pipe_dir17"
        << "pipe_dir18"
        << "pipe_dir19"
        << "pipe_dir20"
        << "pipe_dir21"
        << "pipe_dir22"
        << "pipe_dir23"
        << "pipe_dir24"
        << "pipe_dir25"
        << "pipe_dir26"
        << "pipe_dir27"
        << "pipe_dir28"
        << "pipe_dir30"
        << "pipe_dir31"
        << "pipe_dir32"
        << "pipe_dir33"
        << "pipe_dir34"
        << "pipe_dir35"
        << "pipe_dir36"
        << "pipe_dir37"
        << "pipe_dir38"
        << "pipe_dir39"
        << "pipe_dir40"
        << "pipe_dir41"
        << "pipe_dir42"
        << "pipe_dir43"
        << "pipe_dir44"
        << "pipe_dir45"
        << "pipe_dir46"
        << "pipe_dir47"
        << "pipe_dir48"
        << "pipe_dir49"
        << "pipe_dir50"
        << "pipe_dir51"
        << "pipe_dir52"
        << "pipe_dir53"
        << "pipe_dir54"
        << "pipe_dir55"
        << "pipe_dir56"
        << "pipe_dir57"
        << "pipe_dir58"
        << "pipe_dir59"
        << "pipe_dir60"
        << "pipe_dir61"
        << "pipe_dir62"
        << "pipe_dir63"
        << "pipe_dir64"
        << "pipe_dir65"
        << "pipe_dir66"
        << "pipe_dir67"
        << "pipe_dir68"
        << "pipe_dir69"
        << "pipe_dir70"
        << "pipe_dir70"
        << "pipe_dir71"
        << "pipe_dir72"
        << "pipe_dir73"
        << "pipe_dir74"
        << "pipe_dir75"
        << "pipe_dir76"
        << "pipe_dir77"
        << "pipe_dir78"
        << "pipe_dir79"
        << "pipe_dir80"
        << "pipe_dir81"
        << "pipe_dir82"
        << "pipe_dir83"
        << "pipe_dir84"
        << "pipe_dir85"
        << "pipe_dir86";




}
