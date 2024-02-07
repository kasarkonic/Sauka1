#ifndef HWLISTSFORM_H
#define HWLISTSFORM_H

#include <QMainWindow>
#include <QDialog>
#include <QTableView>
#include <QItemDelegate>
#include <QStandardItemModel>
#include "global.h"
#include "sensortablemodel.h"

namespace Ui {
class HWListsForm;
}

class HWListsForm : public QMainWindow//, public QDialog
{
    Q_OBJECT

public:
    explicit HWListsForm(Global &global, QWidget *parent = nullptr);

    Global &global;
    ~HWListsForm();
private slots:
    void handleButton();
    void handleEditFinish();

private:
    Ui::HWListsForm *ui;
    void initUI();
    //QStandardItemModel *sensorTabModel;
    SensorTableModel *sensorTableModel;

    //QLineEdit *lineEdit ;
    //QPushButton *butt;
    QLineEdit *lineEdit ;
    QLineEdit *lineEditDi ;
    QLineEdit *lineEditAn ;

};

#endif // HWLISTSFORM_H
