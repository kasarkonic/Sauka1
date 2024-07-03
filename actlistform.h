#ifndef ACTLISTFORM_H
#define ACTLISTFORM_H

//#include "global.h"
#include <QMainWindow>
#include "acttablemodel.h"
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
    class ActListForm;
}

class ActListForm : public QMainWindow {
    Q_OBJECT

public:
    explicit ActListForm(Global& global, QWidget* parent = nullptr);

    ~ActListForm();
    void updateData(int row);

signals:
     void updateDIoutput(int row, int val);
    void updateDataTable();
private slots:
    void handleButton();
    void handleEditFinish();


private:
    Global& global;
    Ui::ActListForm* ui;
    ActTableModel* acttablemodel;
    QPushButton* butt;
    QPushButton* buttA;
    QLineEdit* lineEditAn;
};

#endif // ACTLISTFORM_H
