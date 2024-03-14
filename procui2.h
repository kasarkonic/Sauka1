#ifndef PROCUI2_H
#define PROCUI2_H

#include <QMainWindow>
#include "global.h"
#include "dyno.h"
#include "mix.h"
#include "pipe.h"
#include "pump.h"
#include "tvertne.h"
#include "global.h"
#include "valve.h"
#include "scalesbase.h"
#include "scalesmass.h"

namespace Ui {
class ProcUI2;
}

class ProcUI2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProcUI2(Global &global, QWidget *parent = nullptr);
    ~ProcUI2();

private slots:
    void on_pushButton_Stop_clicked();

private:
    Dyno *dynoA;
    Mix *mixA;
    Tvertne *tvertneA;
    Pump *pumpA;
    Pipe *pipeA;
    Valve *valveA;
    ScalesBase *scalesBase;
    ScalesMass *scalesMass;

    Global &global;
    Ui::ProcUI2 *ui;
    void initUI();
    void drawWidgets();
};

#endif // PROCUI2_H
