 #include "senslistsform.h"


#include "ui_senslistsform.h"
//#include <QFormLayout>
//#include <QLabel>
//#include <QGroupBox>

//#include <QLineEdit>
//#include <QPushButton>


SensListsForm::SensListsForm(Global &global, QWidget *parent)
    : QMainWindow(parent)
    , global(global)
    , ui(new Ui::SensListsForm)

{

    ui->setupUi(this);

    sensorTableModel = new SensorTableModel(global,this);
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

        connect(lineEditDi, &QLineEdit::editingFinished, this, &SensListsForm::handleEditFinish);
        connect(lineEditAn, &QLineEdit::editingFinished, this, &SensListsForm::handleEditFinish);
    }

    initUI();
}

SensListsForm::~SensListsForm()
{
    delete ui;
}


void SensListsForm::handleButton()
{
    qDebug() << "SensListsForm::handleButton ";
}

void SensListsForm::handleEditFinish()

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


void SensListsForm::initUI()
{


}
