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

void Runprocess::timerEvent(QTimerEvent* event) {
    // qDebug() << "timerEvent " << event->timerId() << " -> " << taskTimer << global.getTick();
    if (event->timerId() == taskTimer) {
        //qDebug() << "timerEvent " ;
        runTaskCycle();
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
            //         changeState(StateRun);
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


        switch (global.tabVal[currentTabVal].cmbGroupItem) {
        case 0: // valve
            changeState(StateValve);
            break;
        case 1: // pump
            changeState(StatePump);
            break;
        default:
            break;
        }


        changeState(StateRun1,1000);
        break;

    case StateRun1:
        if(isTimerTimeout()){


            //qDebug() << "StateRun1 " << global.getTick();
            changeState(StateRun);
        }
        break;




    }
}

void Runprocess::stateValve()
{
    int out = global.tabVal[currentTabVal].cmbObjectItem;
    int val = global.tabVal[currentTabVal].val > 0;

    out = out + Y1_1_atvērt;        // start real pin addres
    global.DIoutput[out].value = val;
    global.DIoutput[out].update = true;


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

void Runprocess::stateCmdOut()
{
    switch (getState()) {
    case 0:

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
    if(global.tabVal.length() > currentTabVal){
        currentTabVal ++;
    changeState(StateRun);
    }
    else{
     changeState(StateIdle);
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
    case StateInit:
        stateInit();
        break;
    case StateReset:
        stateReset();
        break;
    case StateRun:
        stateRun();
        break;
    case StateCmdOut:
        stateCmdOut();
        break;
    case StateTest:
        stateTest();
        break;
    case StateCmdOutTXT:
        stateCmdOutTXT();
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
    return((intervalTimer->elapsed() - stateStartTime) > stateTimerInterval);
}

int Runprocess::getStateRunTime() {
    return (intervalTimer->elapsed() - stateStartTime);
}
