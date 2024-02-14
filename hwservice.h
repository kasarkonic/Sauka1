#ifndef HWSERVICE_H
#define HWSERVICE_H

#include <QWidget>
#include "global.h"
//#include "senslistsform.h"
#include <QMainWindow>

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


private slots:
    void on_pushButton_actuator_clicked();

    void on_pushButton_sensor_clicked();

    void on_pushButton_Scales_clicked();

    void on_pushButton_Com_Ports_clicked();

private:

};

#endif // HWSERVICE_H
