#ifndef PROCUI2_H
#define PROCUI2_H

#include <QMainWindow>
#include "global.h"
#include "recipeform.h"

namespace Ui {
    class ProcUI2;
}

class ProcUI2 : public QMainWindow {
    Q_OBJECT

public:
    explicit ProcUI2(Global& global, QWidget* parent = nullptr);
    ~ProcUI2();
        void maximizeWindow();

protected:
    void    resizeEvent(QResizeEvent* event) override;
    void    timerEvent(QTimerEvent* event) override;


private slots:
    void on_pushButton_Stop_clicked();

private:
   //Conveyor* conveyorA;
   // Dyno* dynoA;
   // Mix* mixA;
   // Tvertne* tvertneA;
   // Pump* pumpA;
   // Dispax* dispax;
   // Label* label;
   // Pipe* pipeA;
   // Valve* valveA;
   // ScalesBase* scalesBase;
   // ScalesMass* scalesMass;

    Global& global;
    Ui::ProcUI2* ui;
    RecipeForm* recipeForm;
    void initUI();
    void drawWidgets();
};

#endif // PROCUI2_H
