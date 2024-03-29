#ifndef HWSERVICE_H
#define HWSERVICE_H

#include <QWidget>
#include "global.h"
//#include "senslistsform.h"
#include <QMainWindow>
#include "actlistform.h"
#include "senslistsform.h"

namespace Ui {
class HWService;
}

class HWService  : public QMainWindow
{
    Q_OBJECT

public:
    explicit HWService(Global &global, QWidget *parent = nullptr );

    Global &global;
    Ui::HWService *ui;

    ~HWService();
    SensListsForm sensListsForm;
    ActListForm actListForm;

signals:
     void setBaudrate(int address);
     bool factoryReset(int address);
public slots:
    void updateDataAn(int row, int val);
    void updateDataDi(int row, bool val);

protected:
         void    timerEvent(QTimerEvent *event) override;


private slots:
    void on_pushButton_actuator_clicked();

    void on_pushButton_sensor_clicked();

    void on_pushButton_Scales_clicked();

    void on_pushButton_Com_Ports_clicked();

    void on_pushButton_ReadBaudR_clicked();

    void on_lineEdit_Input_address_editingFinished();

    void on_pushButton_ChangeAddress_clicked();

    void on_pushButton_FactoryReset_clicked();

private:


    int modbusAddress = 0;
    int timerId;


};

#endif // HWSERVICE_H
