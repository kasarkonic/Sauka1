#ifndef HWPORTS_H
#define HWPORTS_H

#include <QMainWindow>
#include "global.h"
#include <QLabel>
#include <QComboBox>

namespace Ui {
class HwPorts;
}

class HwPorts : public QMainWindow
{
    Q_OBJECT

public:
    explicit HwPorts(Global&  global, QWidget *parent = nullptr);
    ~HwPorts();

private slots:

    void on_pushButton_Save_clicked();

    void on_pushButton_Update_clicked();

private:
    Global &global;
    Ui::HwPorts *ui;
    void initUI();

     enum { NumGridCol = 8,
           NumGridRows = 3};

     QLabel* labels[NumGridRows][NumGridCol];
     QComboBox* comboBox[NumGridRows];

     struct  ComInfo{
         QString port = "";
         QString location = "";
         QString description = "";
         QString manufacturer = "";
         QString serialNumber = "";
         QString vendorIdentifier = "";
         QString productIdentifier = "";
     };
      QMap<QString,ComInfo> comPortMap;
     void scanPortsInfo();
      void clearDisplay();

};

#endif // HWPORTS_H
