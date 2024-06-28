#ifndef PROCUI1_H
#define PROCUI1_H

#include <QMainWindow>
#include "global.h"
#include "dyno.h"
#include "mix.h"
#include "pipe.h"
#include "pump.h"
#include "dispax.h"
#include "label.h"
#include "tvertne.h"
#include "global.h"
#include "valve.h"
#include "scalesbase.h"
#include "scalesmass.h"

namespace Ui {
    class ProcUI1;
}

class ProcUI1 : public QMainWindow {
    Q_OBJECT

public:
    explicit ProcUI1(Global& global, QWidget* parent = nullptr);
    ~ProcUI1();

protected:

    void    resizeEvent(QResizeEvent* event) override;
    void    timerEvent(QTimerEvent* event) override;


private slots:
    void on_pushButton_Stop_clicked();

private:
    Dyno* dynoA;
    Mix* mixA;
    Tvertne* tvertneA;
    Pump* pumpA;
    Dispax* dispax;
    Label* label;
    Pipe* pipeA;
    Valve* valveA;
    ScalesBase* scalesBase;
    ScalesMass* scalesMass;

    Global& global;
    Ui::ProcUI1* ui;
    void initUI();
    void drawWidgets();

};

#endif // PROCUI1_H
