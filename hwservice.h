#ifndef HWSERVICE_H
#define HWSERVICE_H

#include <QWidget>
//#include "global.h"
//#include "senslistsform.h"
#include <QMainWindow>
#include "actlistform.h"
#include "senslistsform.h"
#include <QElapsedTimer>

namespace Ui {
    class HWService;
}

class HWService : public QMainWindow {
    Q_OBJECT

public:
    explicit HWService(Global& global, QWidget* parent = nullptr);

    Ui::HWService* ui;
    ActListForm actListForm;
    SensListsForm sensListsForm;
    ~HWService();

signals:
    void setBaudrate(int address);
    bool factoryReset(int address);
    void outputChange(int id, int address, int data);
    void diOutputChangeSi(int i, int value);

public slots:
    void updateDataAn(int row, int val);
    void updateDataDi(int row, bool val);
    void updateDIoutput(int row, int val);

protected:
    void    timerEvent(QTimerEvent* event) override;


private slots:
    void on_pushButton_actuator_clicked();

    void on_pushButton_sensor_clicked();

    void on_pushButton_Scales_clicked();

    void on_pushButton_Com_Ports_clicked();

    void on_pushButton_ReadBaudR_clicked();

    void on_lineEdit_Input_address_editingFinished();

    void on_pushButton_ChangeAddress_clicked();

    void on_pushButton_FactoryReset_clicked();

    void on_pushButton_Disable_clicked();

    void on_pushButton_Out_write_clicked();

    void on_lineEdit_Out_address_editingFinished();

    void on_lineEdit_Out_value_editingFinished();

private:

    Global& global;
    int modbusAddress = 0;
    int timerId;
    bool ok;
    int out_address;
    int out_value;
    // QElapsedTimer *updateTimer;



};

#endif // HWSERVICE_H
