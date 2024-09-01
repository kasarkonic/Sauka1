#include "runprocess.h"
#include "ui_runprocess.h"

/*!
 * \brief Runprocess::Runprocess
 * \param global
 * \param parent
 */
Runprocess::Runprocess(Global& global, QWidget* parent)
    : QWidget(parent, Qt::Window)
    , ui(new Ui::Runprocess)
    , global(global) {
    ui->setupUi(this);
    init();
}

Runprocess::~Runprocess() {
    delete ui;
}
/*!
 * \brief Runprocess::start
 * \param state
 * execute  changeState(state)
 */
void Runprocess::start(int state)
{
    pauseProc = false;
    currentTabVal = 0;
    changeState(state);
}
/*!
 * \brief Runprocess::stop
 *  go to StateIdle
 */

void Runprocess::stop()
{
    pauseProc = false;
    changeState(StateIdle);
}
/*!
 * \brief Runprocess::pause
 * \param val
 * ??????????????????????????????????????
 */
void Runprocess::pause(bool val)
{
    pauseProc = val;
}

void Runprocess::timerEvent(QTimerEvent* event) {
    // qDebug() << "timerEvent " << event->timerId() << " -> " << taskTimer << global.getTick();
    if(!pauseProc){
        if (event->timerId() == taskTimer) {
            //qDebug() << "timerEvent " ;

            if(!pauseProc){
                runTaskCycle();
            }
        }
    }
    else{
        //qDebug() << "!!! Pause !!! " ;

    }
}

void Runprocess::stateIdle() {
    // changeState(StateReset);
}

void Runprocess::stateReset() {
    switch (getState()) {
    case StateReset:
        tempInt++;

        if (tempInt > 32) {
            tempInt = 0;
        }
        //global.DIoutput[tempInt].value = 1;
        DIOUT(tempInt, 1)
        qDebug() << " DIoutput[" << tempInt << "] = 1" << global.getTick() << "\n";
        emit diOutputChangeSi(tempInt, global.DIoutput[tempInt].value);

        changeState(StateReset0, 400);
        break;

    case StateReset0:
        if (isTimerTimeout()) {
            //global.DIoutput[tempInt].value = 0;
            DIOUT(tempInt, 0)
            qDebug() << " DIoutput[" << tempInt << "] = 0" << global.getTick();
            emit diOutputChangeSi(tempInt, global.DIoutput[tempInt].value);
            changeState(StateReset1, 100);
        }
        break;

    case StateReset1:
        if (isTimerTimeout()) {
            changeState(StateReset);
        }
        break;
    }
}

void Runprocess::stateInit() {
    switch (getState()) {
    case StateInit:
        qDebug() << "StateInit " << global.getTick();
        changeState(StateIdle);

        int start = false;
        if(start){
            currentTabVal = 0;
            changeState(StateRun);
        }
        break;
    }
}


/*
    struct  tVal {
        int npk = 0; //QLabel *label_npk;
        int cmbGroupItem = 0; //QComboBox *cmbGroup = nullptr;
        int cmbObjectItem = 0;// QComboBox *cmbObject = nullptr;
        int  val = 0;      //QLineEdit *linEditVal = nullptr;
        QString  notes = ""; //    QLineEdit *linEditNote = nullptr;
    };
    QList<tVal>tabVal;
 */

void Runprocess::stateRun() {
    switch (getState()) {
    case StateRun:
        qDebug() << currentTabVal
                 <<"StateRun_procesGroupItems "
                 << global.tabVal[currentTabVal].cmbGroupItem
                 <<  global.tabVal[currentTabVal].cmbObjectItem
                 <<  global.tabVal[currentTabVal].val
                 <<  global.tabVal[currentTabVal].notes;
        //      QStringList procesGroupItems  = { "Valve", "Pump", "DRIVES", "Pause","Test","Pipe","Command" };
        switch (global.tabVal[currentTabVal].cmbGroupItem) {
        case Global::Valve: // valve
            stateValve();
            break;
        case Global::Pump: // pump
            changeState(StatePump);
            break;
        case Global::DRIVES: // DRIVES
            changeState(StateDrives);
            break;

        case Global::IsValveFinish: //  IsValveFinish?
            changeState(StateIfValveFinish);
            //stateIfValveFinish();
            break;

        case Global::Scales: // Scales:
            changeState(StateScalesTest);
            break;
        case Global::Tank: //  Tank
            changeState(StateTankTest);
            break;
        case Global::Command: // Command
            changeState(StateCmd);
            break;
        case Global::Pipe: // Pipe
            statePipe();
            break;


        default:
            changeState(StateIdle);
            break;
        }

        break;

    case StateRun1:
        break;

    case StatePump:
        statePump();
        break;

    case StatePause:
        break;


    case StatePipe:
        statePipe();
        break;

    case StateDrives:
        stateDrives();
        break;

    case StateCmd:
        stateCmd();
        break;

    case StateIfValveFinish:
        stateIfValveFinish();
        break;
    case StateScalesTest:
        stateScalesTest();
        break;
    case StateTankTest:
        stateTankTest();
        break;

    case StateNext:
        stateNext();
        break;

    default:
        break;


    }
}

void Runprocess::stateValve()
{
    int out = global.tabVal[currentTabVal].cmbObjectItem;
    int val = global.tabVal[currentTabVal].val > 0;

    out = out + Y1_1_atvērt;        // start real pin addres
    if(out < MAX_DIoutput){
        global.DIoutput[out].value = val;
    }
    qDebug() << "valve addres " << out << "val = " << val;

    if(out == Y2_1_atvērt){global.DIoutput[Y2_1_aizv].value = 0;}
    if(out == Y2_2_atvērt){global.DIoutput[Y2_2_aizv].value = 0;}
    if(out == Y2_3_atvērt){global.DIoutput[Y2_3_aizv].value = 0;}
    if(out == Y2_4_atvērt){global.DIoutput[Y2_4_aizv].value = 0;}
    if(out == Y3_1_atvērt){global.DIoutput[Y3_1_aizv].value = 0;}
    if(out == Y3_2_atvērt){global.DIoutput[Y3_2_aizv].value = 0;}
    if(out == Y3_3_atvērt){global.DIoutput[Y3_3_aizv].value = 0;}
    if(out == Y3_4_atvērt){global.DIoutput[Y3_4_aizv].value = 0;}
    if(out == Y4_1_atvērt){global.DIoutput[Y4_1_aizv].value = 0;}
    if(out == Y4_2_atvērt){global.DIoutput[Y4_2_aizv].value = 0;}
    if(out == Y4_3_atvērt){global.DIoutput[Y4_3_aizv].value = 0;}
    if(out == Y4_4_atvērt){global.DIoutput[Y4_4_aizv].value = 0;}
    if(out == Y5_1_atvērt){global.DIoutput[Y5_1_aizv].value = 0;}
    if(out == Y5_2_atvērt){global.DIoutput[Y5_2_aizv].value = 0;}
    if(out == Y5_3_atvērt){global.DIoutput[Y5_3_aizv].value = 0;}
    if(out == Y5_4_atvērt){global.DIoutput[Y5_4_aizv].value = 0;}
    if(out == Y6_1_atvērt){global.DIoutput[Y6_1_aizv].value = 0;}
    if(out == Y6_2_atvērt){global.DIoutput[Y6_2_aizv].value = 0;}

    if(out == Y2_1_aizv){global.DIoutput[Y2_1_atvērt].value = 0;}
    if(out == Y2_2_aizv){global.DIoutput[Y2_2_atvērt].value = 0;}
    if(out == Y2_3_aizv){global.DIoutput[Y2_3_atvērt].value = 0;}
    if(out == Y2_4_aizv){global.DIoutput[Y2_4_atvērt].value = 0;}
    if(out == Y3_1_aizv){global.DIoutput[Y3_1_atvērt].value = 0;}
    if(out == Y3_2_aizv){global.DIoutput[Y3_2_atvērt].value = 0;}
    if(out == Y3_3_aizv){global.DIoutput[Y3_3_atvērt].value = 0;}
    if(out == Y3_4_aizv){global.DIoutput[Y3_4_atvērt].value = 0;}
    if(out == Y4_1_aizv){global.DIoutput[Y4_1_atvērt].value = 0;}
    if(out == Y4_2_aizv){global.DIoutput[Y4_2_atvērt].value = 0;}
    if(out == Y4_3_aizv){global.DIoutput[Y4_3_atvērt].value = 0;}
    if(out == Y4_4_aizv){global.DIoutput[Y4_4_atvērt].value = 0;}
    if(out == Y5_1_aizv){global.DIoutput[Y5_1_atvērt].value = 0;}
    if(out == Y5_2_aizv){global.DIoutput[Y5_2_atvērt].value = 0;}
    if(out == Y5_3_aizv){global.DIoutput[Y5_3_atvērt].value = 0;}
    if(out == Y5_4_aizv){global.DIoutput[Y5_4_atvērt].value = 0;}
    if(out == Y6_1_aizv){global.DIoutput[Y6_1_atvērt].value = 0;}
    if(out == Y6_2_aizv){global.DIoutput[Y6_2_atvērt].value = 0;}

    global.DIoutput[0].update = true;   // update all outputs
    global.DIoutput[32].update = true;
    changeState(StateNext);
}

void Runprocess::stateIfValveFinish()
{

    int out = global.tabVal[currentTabVal].cmbObjectItem;
    int val = global.tabVal[currentTabVal].val;
    out = out + Y1_1_atvērt; // real address

    if(global.DIinput[out].value == val){
        changeState(StateNext);
    }

    int maxTime = global.tabVal[currentTabVal].notes.toInt(&ok);
    qDebug() << "maxTime ???" << maxTime << (intervalTimer->elapsed())/1000;
    if (ok) {
        if((intervalTimer->elapsed() - stateStartTime)/1000 > maxTime){ // compare s
            qDebug() << "ERROR !!!" <<out <<"Valve not finish process in  time: " << maxTime<<"s";
            changeState(StateError);
        }
    }

    qDebug() << "stateIfValveFinish"
             << maxTime
             << (intervalTimer->elapsed() - stateStartTime)/1000;

}

void Runprocess::statePump()
{
    int out = global.tabVal[currentTabVal].cmbObjectItem; //pump nr
    int val = global.tabVal[currentTabVal].val > 0;
    int pumpAddress = 0;

    //    QStringList procesObjestItemsPump  = { "Sapropelis 2.2", "Mohno 5.5", "Dispax 11Kw", "Pump H2o","Pump B","Pump Na","Pump Sifons" };

    switch (out) {
    case 0:
        pumpAddress = set_pump2_2_On_Off;
        break;
    case 1:
        pumpAddress = 0;   //??????????????????????  MOHNO DRIVER
        if(val == 0){     // stop
            stopDrive(M4) ;
        }
        if(val > 0){     // stop
            runDrive(M4,val) ;
        }
        break;
    case 2:
        pumpAddress = set_dispax_11Kw_On_;
        break;
    case 3:
        pumpAddress = H2o_pilda_On;
        break;
    case 4:
        pumpAddress = B_pilda_On;
        break;
    case 5:
        pumpAddress = N_pilda_On;
        break;
    case 6:
        pumpAddress = TermoSifons_On;
        break;
    default:
        break;
    }


    if(pumpAddress < MAX_DIoutput){
        global.DIoutput[pumpAddress].value = val;
    }
    //  qDebug() << "pump addres " << out << "val = " << val;
    else{
        qDebug() << "ERROR !!!" <<out <<"Pump address out of range " << pumpAddress;
    }

    changeState(StateNext);



}
/*!
 * \brief Runprocess::stateCmd
 * QStringList procesObjestItemsComand  = {"Pause",  "Goto", "Stop", "GOtoStart" };
 */

void Runprocess::stateCmd()
{
    switch (global.tabVal[currentTabVal].cmbObjectItem) {
    case 0: // pause
        changeState(StateNext,global.tabVal[currentTabVal].val * 1000);   // s
        break;
    case 1: //Goto
        changeState(StateIdle); // ???????????????????????????????????
        break;
    case 2: //Stop
        changeState(StateIdle);
        break;
    case 3: //GOtoStart
        currentTabVal = 0;
        changeState(StateRun);
        break;
    default:
        break;
    }
}


void Runprocess::stateScalesTest()
{

    int val = global.tabVal[currentTabVal].val;

    int maxTime = global.tabVal[currentTabVal].notes.toInt(&ok);
    qDebug() << "maxTime ???" << maxTime << (intervalTimer->elapsed())/1000;
    if (!ok) {
        if((intervalTimer->elapsed() - stateStartTime)/1000 > maxTime){ // compare s
            qDebug() << "Varning !!!" "maxTime not defined " ;
        }
        else if((intervalTimer->elapsed() - stateStartTime)/1000 > maxTime){ // compare s
            qDebug() << "ERROR !!!" << val  <<"Scales not change value in  time: " << maxTime<<"s";
            changeState(StateError);
        }

        //    QStringList procesObjestItemsScales  = { "More_then","Less_then" };
        switch (global.tabVal[currentTabVal].cmbObjectItem) {
        case 0: // "More_then"
            if(global.DIinput[scales_mass].value >= val){
                changeState(StateNext);
            }
            break;
        case 1: //"Less_then"
            if(global.DIinput[scales_mass].value <= val){
                changeState(StateNext);
            }
            break;
        default:
            break;
        }
    }
    qDebug() << "stateScalesTest"
             << "current:"
             << global.DIinput[scales_mass].value
             << "Destin. :" << val
             << maxTime
             << (intervalTimer->elapsed() - stateStartTime)/1000;

}
void Runprocess::stateTankTest()
{
    int val = global.tabVal[currentTabVal].val;
    int in = global.tabVal[currentTabVal].cmbObjectItem;
    in += TVERTNE1LEVEL;    // offset
    int maxTime = global.tabVal[currentTabVal].notes.toInt(&ok);
    qDebug() << "maxTime ???" << maxTime << (intervalTimer->elapsed())/1000;
    if (!ok) {
        if((intervalTimer->elapsed() - stateStartTime)/1000 > maxTime){ // compare s
            qDebug() << "Varning !!!" "maxTime not defined " ;
        }
        else if((intervalTimer->elapsed() - stateStartTime)/1000 > maxTime){ // compare s
            qDebug() << "ERROR !!!" << val  <<"Tank not change value in  time: " << maxTime<<"s";
            changeState(StateError);
        }

        /*
    QStringList procesObjestItemsTank  = {
        "TVERTNE1FULL"
        ,"TVERTNE2FULL"
        ,"TVERTNE3FULL"
        ,"TVERTNE4FULL"
        ,"TVERTNE5FULL"

        ,"TVERTNE1LEVELPROC"
        ,"TVERTNE2LEVELPROC"
        ,"TVERTNE3LEVELPROC"
        ,"TVERTNE4LEVELPROC"
        ,"TVERTNE5LEVELPROC"
    };
             */

        if (in > MAX_DIinput){
            qDebug() << "ERROR !!!" <<"Incorrect sensor address " << in;
            return;
        }
        if( global.DIinput[in].value >= val){
            changeState(StateNext);
        }
    }
    qDebug() << "stateTankTest"
             << "current:"
             << global.DIinput[in].value
             << "Destin. :" << val
             << maxTime
             << (intervalTimer->elapsed() - stateStartTime)/1000;
}

void Runprocess::stateCmdOutTXT()
{
    switch (getState()) {
    case 0:
        break;
    default:
        break;
    }
}

void Runprocess::stateNext()
{
    if(isTimerTimeout()){
        if(global.tabVal.length() - 1 > currentTabVal){
            currentTabVal ++;
            emit stateChange(currentTabVal);
            changeState(StateRun);
        }
        else{
            changeState(StateIdle);
        }
    }
}

/*!
 * \brief Runprocess::statePipe
 * var2  flow direction 0=>No flow, 1=>right,down  2=>left,up
 */

void Runprocess::statePipe()
{
    int pipe = global.tabVal[currentTabVal].cmbObjectItem;
    int val = global.tabVal[currentTabVal].val;
    if(pipe < MAX_DIoutput){
        pipe = pipe + pipe_dir0;        // start real pin addres
        global.DIoutput[pipe].value = val;
        global.DIoutput[pipe].update = true;
    }
    qDebug() <<"global.DIoutput[" << pipe << "] =" << val;
    changeState(StateNext);

}

void Runprocess::stateDrives()
{
    int items = global.tabVal[currentTabVal].cmbObjectItem;
    int speed = global.tabVal[currentTabVal].val;

    switch (items) {
    case 0: // mix
        if(speed == 0){   // item =  0  off
            stopDrive(M9) ;
        }
        if(speed >0){   // item > 0 speed
            runDrive( M9,speed);
        }
        break;
    case 1: // coveyor
        if(speed == 0){   // item =  0  off
            stopDrive(M8) ;
        }
        if(speed >0){   // item > 0 speed
            runDrive( M8,speed);
        }
        break;

    default:
        break;
    }
}


void Runprocess::stateError() {
    switch (getState()) {
    case StateError:
        qDebug() << "StateError " << global.getTick();
        changeState(StateIdle);
        break;
    }
}
/*!
 * \brief Runprocess::init
 * start statemachine process
 * next iteration every 10ms
 */
void Runprocess::init() {
    task_state = 0;
    taskTimer = startTimer(100);
    tempInt = 0;
    pauseProc = true;
    intervalTimer = new QElapsedTimer();
    intervalTimer->start();
    task_state = StateInit;
}

/*!
 * \brief Runprocess::runTaskCycle
 *  run iteration
 */

void Runprocess::runTaskCycle() {
    // qDebug() << " runTaskCycle()  "<< Qt::hex << getState() << Qt::dec << global.getTick();
    // Goto master state in state machine (state groups)

    switch (getMasterState()) {
    case StateIdle:
        stateIdle();
        break;
    case StateReset:
        stateReset();
        break;
    case StateInit:
        stateInit();
        break;
    case StateRun:
        stateRun();
        break;
    case StateError:
        stateError();
        break;

    default:
        // check for the single states that not grouped together
        switch (getState()) {
        case StateIdle:
            stateIdle();
            break;
        }
        break;
    }
}

int Runprocess::getMasterState() {
    return task_state & 0xf00;
}

int Runprocess::getState() {
    return task_state;
}
/*!
 * \brief Runprocess::changeState
 * \param newState
 * \param timeout default -1
 */
void Runprocess::changeState(int newState, int timeout) {
    qDebug() << "TCS:" << Qt::hex << getState() << " -> " << Qt::hex << newState<< Qt::dec <<"Tick:"<< global.getTick();
    task_state = newState;
    intervalTimer->start();
    stateStartTime = intervalTimer->elapsed();//  global.getTick();

    //qDebug() << "TCS:" << Qt::hex << getState() << " -> " << Qt::hex << newState<< Qt::dec <<"Tick:"<< global.getTick() << stateStartTime;
    stateTimerInterval = 0;
    if (timeout > -1) {
        stateTimerInterval = timeout;
    }
}

/*!
 * \brief Runprocess::isTimerTimeout
 * \return true, if timeout > elapsed time from changeState(State,timeout)
 */
bool Runprocess::isTimerTimeout() {

    if(stateTimerInterval == 0){    // no timeout
        return 1;
    }
    else{
        return((intervalTimer->elapsed() - stateStartTime) > stateTimerInterval);
    }
}

int Runprocess::getStateRunTime() {
    return (intervalTimer->elapsed() - stateStartTime);
}

/*!
 * \brief ProcesSteps::runDrive
 * \param address   M4,M8,M9
 * \param speed     +- 0.1Hz
 */
void Runprocess::runDrive(int address, int speed)
{
    // motor On
    Global::rs485WrPar param;

    param.boardAdr = address;
    param.value = 128;      // reset
    param.regAdr = CMD_REG;
    param.len = 1;
    param.cmd = WR_REG;
    global.rs485WrList.append(param);

    param.value = 6;
    global.rs485WrList.append(param);

    param.value = 7;
    global.rs485WrList.append(param);

    param.value = 15;
    global.rs485WrList.append(param);

    param.regAdr = LFRD_REG;
    param.value = speed;
    param.len = 1;
    param.cmd = WR_REG;
    global.rs485WrList.append(param);


}

void Runprocess::stopDrive(int address)
{
    // motor Off
    Global::rs485WrPar param;
    param.boardAdr = address;
    param.regAdr = CMD_REG;
    param.value = 7;
    param.cmd = WR_REG;
    global.rs485WrList.append(param);
}
