#ifndef SENSLISTSFORM_H
#define SENSLISTSFORM_H

#include <QMainWindow>
#include <QDialog>
#include <QTableView>
#include <QItemDelegate>
#include <QStandardItemModel>
#include "global.h"
#include "sensortablemodel.h"

namespace Ui {
class SensListsForm;
}

class SensListsForm : public QMainWindow//, public QDialog
{
    Q_OBJECT

public:
    explicit SensListsForm(Global &global, QWidget *parent = nullptr);

    ~SensListsForm();

    void updateData(int row);

private slots:
    void handleButton();
    void handleEditFinish();

private:
    Global &global;
    Ui::SensListsForm *ui;
    void initUI();


    SensorTableModel *sensorTableModel;

    //QLineEdit *lineEdit ;
    //QPushButton *butt;
    QLineEdit *lineEdit ;
    QLineEdit *lineEditDi ;
    QLineEdit *lineEditAn ;

};

#endif // SENSLISTSFORM_H
