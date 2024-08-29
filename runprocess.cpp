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
        runTaskCycle();
    }
    }
    else{
        qDebug() << "!!! Pause !!! " ;

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

        int start = true;
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
                 <<"StateRun procesGroupItems "
                 << global.tabVal[currentTabVal].cmbGroupItem
                 <<  global.tabVal[currentTabVal].cmbObjectItem
                 <<  global.tabVal[currentTabVal].val
                 <<  global.tabVal[currentTabVal].notes;
        //      QStringList procesGroupItems  = { "Valve", "Pump", "Mix", "Pause","Test","Pipe","Command" };
        switch (global.tabVal[currentTabVal].cmbGroupItem) {
        case 0: // valve
            stateValve();
            break;
        case 1: // pump
            //changeState(StatePump);
            break;
        case 2: // Mix
            //changeState(StatePump);
            break;
        case 3: // pause???????????????????????????????
            changeState(StateNext,global.tabVal[currentTabVal].val);
            break;
        case 4: //  Test
           // changeState(StateTest);
            break;
        case 5: // Pipe
            statePipe();
            break;
        case 6: // Command
            stateCmd();
            break;


        default:
            changeState(StateIdle);
            break;
        }
        break;

    case StateRun1:
        if(isTimerTimeout()){


            //qDebug() << "StateRun1 " << global.getTick();
            changeState(StateRun);
        }
        break;




    case StatePump:
        break;

    case StatePause:
        break;

    case StateTest:
        break;

    case StatePipe:
        statePipe();
        break;

    case StateCmd:
        stateCmd();
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
    global.DIoutput[out].value = val;

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

void Runprocess::statePump()
{

}
/*!
 * \brief Runprocess::stateCmd
 * QStringList procesObjestItemsComand  = {"Pause",  "Goto", "Stop", "GOtoStart" };
 */

void Runprocess::stateCmd()
{
    switch (global.tabVal[currentTabVal].cmbObjectItem) {
    case 0: // pause
        changeState(StateNext,global.tabVal[currentTabVal].val);
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



void Runprocess::stateTest()
{
    switch (getState()) {
    case 0:

        break;
    default:
        break;
    }
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
    int val = global.tabVal[currentTabVal].val > 0;

    pipe = pipe + pipe_dir0;        // start real pin addres
    global.DIoutput[pipe].value = val;
    global.DIoutput[pipe].update = true;
    qDebug() <<"global.DIoutput[" << pipe << "] =" << val;
    changeState(StateNext);

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
    stateStartTime = intervalTimer->elapsed();//  global.getTick();
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
