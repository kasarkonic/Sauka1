#include "runprocess.h"
#include "ui_runprocess.h"

Runprocess::Runprocess(Global &global,QWidget *parent)
    : QWidget(parent, Qt::Window)
    , ui(new Ui::Runprocess)
    , global(global)
{
    ui->setupUi(this);
}

Runprocess::~Runprocess()
{
    delete ui;
}
/*



///
/// \brief Task runner function. Called by framework
///
void MachineController::runTaskCycle(void)
{
    if (receivedInternalMess())
        onInternalMessage();

    // Goto master state in state machine (state groups)
    // Read about state groups here: http://172.16.16.15/docs/paf/tasks_and_state.html
    //
    switch (getMasterState())
    {
    case StateRunning:
        stateRunning();
        break;
    case StateCycleup:
        stateCycleup();
        break;
    case StateCycledown:
        stateCycledown();
        break;
    case StateReset:
        stateReset();
        break;
    case StatePurge:
        statePurge();
        break;
    case StateInit:
        stateInit();
        break;
    case StateError:
        stateError();
        break;
    default:
        // check for the single states that not grouped together
        switch (getState())
        {
        case StatePowerOn:
            statePowerOn();
            break;
        case StateIdle:
            stateIdle();
            break;
        }
        break;
    }
}





void MachineController::stateCycledown()
{
    switch (getState())
    {
    case StateCycledown:
        // Cycle down has been received. Wait until there are no more active sets in machine before cycling down
        sdebug("--- MACHINE CYCLEDOWN ---MC\n");
        DynamicParams::setCycleUpStatus(0);

        pendingCycleUp = 0;

        Controller::command(AppCommands::CmdCycleDown, DynamicParams::getCycleDownStatus());

        // int tmp = DynamicParams::getCycleDownStatus(); //??????????????????????
        backjoggerCntrl->command(AppCommands::CmdCycleDown, pendingCycledown);
        paperTransportCntrl->command(AppCommands::CmdCycleDown, pendingCycledown);
        staplerCtrl->command(AppCommands::CmdCycleDown, pendingCycledown);
        pendingCycledown = 0;
        changeState(StateCycledown_CheckError, 1000); // must be 1000  only for testing !!!
        break;

    case StateCycledown_CheckError:

        if (isTimerTimeout())
        {

            data.value32 = 2;
            signal.emitSignal(AppSignals::CycleDownDownstream, &data);
            sdebug("MS send CycleDown 2 to down\n");

            if (!isPaperPathFree())
            {
                PafMachineStatus::clearStatusBits(PafMachineStatus::ControlDisabled | PafMachineStatus::Running);
                PafMachineStatus::setStatusBits(PafMachineStatus::PaperError);
                PafMachineStatus::sendStatus(25);
                sdebug("UpCanCom::Closed 1\n");
                upstream->currentInputState(UpCanCom::Closed);
            }
            {
                PafMachineStatus::clearStatusBits(PafMachineStatus::Running);
                PafMachineStatus::sendStatus(26);
                changeState(StateIdle);
            }
        }
        break;
    }
}








void PafTask::changeState(uint16_t newState, int timeout)
{
    if (bPrintTaskChange) {
        const char* str;
        sdebug("TCS: ");
        sdebug_mode_normal();
        sdebug(taskName);
        sdebug(" ");
        #ifdef INCLUDE_PRINT_FROM_TASK
        sdebug(getStateName(task_state,&str) ? str : "s%X",task_state);
        sdebug(" -> ");
        #endif
        sdebug(getStateName(newState,&str) ? str : "s%X",newState);
        //getStateName(newState,&str);
        //sdebug(str);
        sdebug("\n");
        sdebug_mode_restore();
    }
    task_state = newState;
    stateChangeTimeMark = PafTimer::getTick32();
    if (timeout > -1) {
        int_timer.start(timeout);
    }
}




bool PafTask::getStateName(int state, const char **str)
{
    const StateNameMapItem* pTaskNames = getStateNameMap();
    *str = "undef";
    if (pTaskNames == 0)
        return false;
    int stateInList = pTaskNames->state;
    while (stateInList != -1) {
        if (state == stateInList) {
            *str = pTaskNames->name;
            return true;
        }
        pTaskNames++;
        stateInList = pTaskNames->state;
    }
    return false;
}



uint32_t PafTask::getCurrentTick(void)
{
    return PafTimer::getTick32();
}



uint32_t PafTask::getStateRunTime()
{
    return PafTimer::getTick32() - stateChangeTimeMark;
}


void PafTask::setPeriodTimeout(int period)
{
    lastPeriodTimeMark = PafTimer::getTick32();
    periodTimeout = (period < 1) ? 0 : (uint32_t)period;
}


.h




private:
    // Typedefs & Enums
    enum States
    {
        StatePowerOn = 0,
        StateIdle,
        StateReset = 0x100,//100
        StateResetWaitpaperpathClearPause1,//101
        StateResetWaitpaperpathClear, // 102
        StateResetWaitpaperpathClearPause2,//103
        StateWaitOnReset,   //0x104
        StatePurge = 0x200,
        StatePurge_WaitOnReadyToPurge,
        StatePurge_Purging,
        StateInit = 0x400,  // 0x400
        StateInit_WaitOnInitDone,  // 0x401

        StateCycleup = 0x500,
        StateCycleupWait,

        StateRunning = 0x600,                // 0x600
        StateWaitRearEdge,                   // 0x601
        StateWaitSideBackJogFinished,        // 0x602
        StateWaitSideBackJogStaple,          // 0x603

        StateWaitStaplerFinished,            // 0x604

        StateWaitStaplerAngleMoveToPurgePos, // 0x605
        StateWaitStaplerMoveToPurgePos,      // 0x606
        StateRestoreStaplerposition,              // 0x607
        StateCheckPaperPathClear,              // 0x608
        StateWaitOpenBJAfterPurge,          // 0x609
        StateWaitStaplerToPosAfterPurge,      // 0x610

        StateCycledown = 0x700,              // 0x700
        StateCycledown_CheckError,  // 0x701
        StateError = 0x900, // 0x900`

    };


    void statePowerOn(void);
    void stateIdle(void);
    void stateReset(void);
    void statePurge(void);
    void stateInit(void);

 */
