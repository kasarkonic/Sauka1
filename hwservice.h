#ifndef HWSERVICE_H
#define HWSERVICE_H

#include <QWidget>
//#include "global.h"
//#include "senslistsform.h"
#include <QMainWindow>
#include "actlistform.h"
#include "senslistsform.h"
#include <QElapsedTimer>
#include "rs232.h"

namespace Ui {
    class HWService;
}

class HWService : public QMainWindow {
    Q_OBJECT

public:
    explicit HWService(Global& global, Rs232& rs232, QWidget* parent = nullptr);

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

    void on_pushButton_Out_write_clicked();

    void on_lineEdit_Out_address_editingFinished();

    void on_lineEdit_Out_value_editingFinished();

    void on_pushButton_measure_clicked();

    void on_comboBox_use_motor_currentIndexChanged(int index);

    void on_pushButton_Motor_off_clicked(bool checked);

    void on_pushButton_Reset_clicked();

    void on_pushButton_Motor_on_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_pushButton_slider_minus_clicked(bool checked);

    void on_pushButton_slider_plus_clicked();

    void on_pushButton_get_error_code_clicked();

    void on_pushButton_readReg_clicked();

    void on_lineEdit_enter_reg_editingFinished();

private:

    Global& global;
    Rs232& rs232;
    Global::rs485WrPar param;
    int modbusAddress = 0;
    int timerId;
    bool ok;
    int out_address;
    int out_value;
    int testMotorAddres = 18; // M8
    int rpm;
    int readRegTest;
    // QElapsedTimer *updateTimer;



};

#endif // HWSERVICE_H
