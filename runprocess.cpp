#include "runprocess.h"
#include "ui_runprocess.h"

Runprocess::Runprocess(Global &global,QWidget *parent)
    : QWidget(parent, Qt::Window)
    , ui(new Ui::Runprocess)
    , global(global)
{
    ui->setupUi(this);
    init();
}

Runprocess::~Runprocess()
{
    delete ui;
}

void Runprocess::timerEvent(QTimerEvent *event)
{
   // qDebug() << "timerEvent " << event->timerId() << " -> " << taskTimer << global.getTick();
    if(event->timerId() == taskTimer){
       // qDebug() << "timerEvent " ;
        runTaskCycle();
    }
}

void Runprocess::stateIdle()
{
changeState(StateReset);
}

void Runprocess::stateReset()
{
    switch (getState())
    {
    case StateReset:
        changeState(StateReset0,500);
  break;

    case StateReset0:
        if (isTimerTimeout())
        {
            changeState(StateReset1,500);
        }
        break;

    case StateReset1:
        if (isTimerTimeout())
        {
            changeState(StateReset);
        }
        break;
    }
}

void Runprocess::stateInit()
{
    switch (getState())
    {
    case StateInit:
        qDebug() << "StateInit " << global.getTick();
        changeState(StateIdle);
        break;
    }
}

void Runprocess::stateRunning()
{
    switch (getState())
    {
    case StateRunning:
        qDebug() << "StateRunning " << global.getTick();
        changeState(StateIdle);
        break;
    }
}

void Runprocess::stateError()
{
    switch (getState())
    {
    case StateError:
        qDebug() << "StateError " << global.getTick();
        changeState(StateIdle);
        break;
    }
}

void Runprocess::init()
{
    task_state = 0;
    taskTimer = startTimer(100);

}

void Runprocess::runTaskCycle()
{
    //qDebug() << " runTaskCycle()  "<< Qt::hex << getState() << Qt::dec << global.getTick();
    // Goto master state in state machine (state groups)
    // Read about state groups here: http://172.16.16.15/docs/paf/tasks_and_state.html
    //
    switch (getMasterState())
    {
    case StateInit:
        stateInit();
        break;
    case StateReset:
         stateReset();
        break;
    case StateRunning:
        stateRunning();
        break;
    case StateError:
        stateError();
        break;

    default:
        // check for the single states that not grouped together
        switch (getState())
        {
        case StateIdle:
            stateIdle();
            break;
        }
        break;
    }
}

int Runprocess::getMasterState()
{
    return task_state & 0xf00;
}

int Runprocess::getState()
{
    return task_state;
}

void Runprocess::changeState(int newState, int timeout)
{
 //   qDebug() << "TCS:" << Qt::hex << getState() << " -> " << Qt::hex << newState<< Qt::dec <<"Tick:"<< global.getTick();
    task_state = newState;
    stateStartTime = global.getTick();
    stateTimerInterval = timeout;
    if (timeout > -1) {
        stateTimerInterval = timeout;
    }
}


bool Runprocess::isTimerTimeout()
{
    return((global.getTick() - stateStartTime) > stateTimerInterval);
}

int Runprocess::getStateRunTime()
{
    return (global.getTick() - stateStartTime);
}
