#ifndef RUNPROCESS_H
#define RUNPROCESS_H

#include <QWidget>
#include"global.h"
#include <QElapsedTimer>

namespace Ui {
class Runprocess;
}

class Runprocess : public QWidget {
    Q_OBJECT

public:
    explicit Runprocess(Global& global, QWidget* parent = nullptr);
    ~Runprocess();
    void start(int state);
    void stop();
    void pause(bool val);
protected:
    void    timerEvent(QTimerEvent* event) override;

private:

    // Typedefs & Enums
    enum States {

        StateIdle,
        StateReset = 0x100,//100
        StateReset0,
        StateReset1,
        StateInit = 0x200,  // 0x200
        StateRun = 0x300,   // 0x300

        StateRun1,   // 0x301

        StateValve,
        StatePump, // 0x302
        StatePause, // 0x303

        StatePipe, // 0x304
        StateCmd, // 0x305

        StateIsValveFinish,// 0x306
        StateScalesTest,
        StateTankTest,
        StateDrives, // 0x302

        StateNext, // 0x307
        StateError = 0x900, // 0x600`

    };

    void stateIdle(void);
    void stateReset(void);
    void stateInit(void);
    void stateRun(void);
    void stateValve(void);
    void stateIsValveFinish(void);
    void statePump(void);
    void stateCmd(void);
    void stateScalesTest(void);
    void stateTankTest(void);
    void stateCmdOutTXT(void);
    void stateNext(void);
    void statePipe(void);
    void stateDrives(void);

    void stateError(void);


    Ui::Runprocess* ui;
    Global& global;

    QElapsedTimer* intervalTimer;
    Global::rs485WrPar param;

    void init();
    void runTaskCycle();
    int getMasterState();
    int getState();
    void changeState(int newState, int timeout = -1);
    bool isTimerTimeout();
    int getStateRunTime();

    int task_state;
    int stateStartTime;
    int  taskTimer = 0;

    int stateTimerInterval = 0;
    bool stateTimerTimeout = false;
    int tempInt = 0;

    int currentTabVal;
   // Global::rs485WrPar paramr;
    bool pauseProc;
    bool ok;
    int actualMotorNode;
    void runDrive( int address, int speed);
    void stopDrive(int address);

signals:
    void diOutputChangeSi(int i, int value);
    void stateChange(int step);

};

#endif // RUNPROCESS_H
