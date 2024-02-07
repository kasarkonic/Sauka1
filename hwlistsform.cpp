#include "hwlistsform.h"
//#include "qlineedit.h"

#include "ui_hwlistsform.h"
#include <QFormLayout>
#include <QLabel>
#include <QGroupBox>

#include <QLineEdit>
#include <QPushButton>


HWListsForm::HWListsForm(Global &global, QWidget *parent)
    : QMainWindow(parent)
    , global(global)
    , ui(new Ui::HWListsForm)

{

    ui->setupUi(this);

    sensorTableModel = new SensorTableModel(global,this);

    sensorTableModel->setHeaderData(0,Qt::Horizontal," Adrese",Qt::DisplayRole);
    sensorTableModel->setHeaderData(1,Qt::Horizontal," Nosaukums",Qt::DisplayRole);
    sensorTableModel->setHeaderData(2,Qt::Horizontal," Vērtība DI",Qt::DisplayRole);
    sensorTableModel->setHeaderData(3,Qt::Horizontal," Vērtība AI",Qt::DisplayRole);
    sensorTableModel->setHeaderData(4,Qt::Horizontal," Mainīt DI",Qt::DisplayRole);
    sensorTableModel->setHeaderData(5,Qt::Horizontal," Mainīt AI",Qt::DisplayRole);

    ui->tableView->setModel(sensorTableModel);



    int maxRow = global.sensList.size();

    for(int row = 0; row < maxRow; row++)
    {
        lineEditDi = new QLineEdit();
        lineEditAn = new QLineEdit();

        global.sensList[row].ptrLineEditDI = lineEditDi;
        global.sensList[row].ptrLineEditAN = lineEditAn;

        ui->tableView->setIndexWidget(sensorTableModel->index(row,4),lineEditDi);
        ui->tableView->setIndexWidget(sensorTableModel->index(row,5),lineEditAn);

        connect(lineEditDi, &QLineEdit::editingFinished, this, &HWListsForm::handleEditFinish);
        connect(lineEditAn, &QLineEdit::editingFinished, this, &HWListsForm::handleEditFinish);
    }

    initUI();
}

HWListsForm::~HWListsForm()
{
    delete ui;
}


void HWListsForm::handleButton()
{
    qDebug() << "HWListsForm::handleButton ";
}

void HWListsForm::handleEditFinish()

{
    qDebug() << "handleEditFinish()";
    QObject* obj = sender();

    QLineEdit* lEdit = qobject_cast<QLineEdit*>(sender());

    int maxRow = global.sensList.size();
    bool ok = true;
    int val;
    for(int row = 0; row < maxRow; row++)
    {

        if(global.sensList[row].ptrLineEditDI == obj){
            val = lEdit->text().toInt(&ok);
            qDebug() <<"DI " <<row<< val << ok;
            if(ok){
                global.sensList[row].digital = val;
            }

        }
        if(global.sensList[row].ptrLineEditAN == obj){
            val = lEdit->text().toInt();
            qDebug() <<"AN " <<row<< val << ok;
            if(ok){
                global.sensList[row].analog = val;
            }
        }
    }
    // qDebug() << "lEdit " << lEdit->text() ;
}


void HWListsForm::initUI()
{


}
