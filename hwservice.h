#ifndef HWSERVICE_H
#define HWSERVICE_H

#include <QWidget>
#include "global.h"
#include "hwlistsform.h"
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
    // HWListsForm hwListForm;

private slots:
    void on_pushButton_actuator_clicked();

    void on_pushButton_sensor_clicked();

    void on_pushButton_invertor_clicked();

private:
  //HWListsForm hwListForm;
};

#endif // HWSERVICE_H
