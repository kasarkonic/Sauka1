#include "actlistform.h"
#include "ui_actlistform.h"

ActListForm::ActListForm(Global &global, QWidget *parent)
    : QMainWindow(parent)
    , global(global)
    , ui(new Ui::ActListForm)
{
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, global.backgroundColor); //QColor(255, 0, 0, 127)
    //pal.setColor(QPalette::Window, QColor(242, 219, 238, 0.251));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    ui->setupUi(this);
    ui->label_head->setText("Piedziņas elementi");
    acttablemodel = new ActTableModel(global,this);
    ui->tableView->setModel(acttablemodel);
    int maxRow = global.actList.size();

    for(int row = 0; row < maxRow; row++)
    {
        butt = new QPushButton();
        lineEditAn = new QLineEdit();

        global.actList[row].ptrButton = butt;
        global.actList[row].ptrLineEdit = lineEditAn;

        ui->tableView->setIndexWidget(acttablemodel->index(row,4),butt);
        ui->tableView->setIndexWidget(acttablemodel->index(row,5),lineEditAn);

        connect(butt, &QPushButton::clicked, this, &ActListForm::handleButton);
        connect(lineEditAn, &QLineEdit::editingFinished, this, &ActListForm::handleEditFinish);
    }

}


void ActListForm::handleButton()
{
   // qDebug() << "actListsForm::handleButton ";
    QObject* obj = sender();
    QPushButton* buttA = qobject_cast<QPushButton*>(sender());
    int maxRow = global.actList.size();
    //bool ok = true;
    int val;
    qDebug() << "actListsForm::handleButton " <<maxRow ;
    for(int row = 0; row < maxRow; row++)
    {
        //qDebug() << row << global.actList[row].ptrButton <<obj ;
        if(global.actList[row].ptrButton == obj){

            if(global.actList[row].digital){
                val = 0;
                buttA->setText("OFF");
            }
            else {
                val = 1;
                buttA->setText("ON");
            }
            qDebug() << row << val << buttA->text();
            global.actList[row].digital = val;
            acttablemodel->updateData(row);
            global.needUpdateDIoutputs(row,val);
        }
    }
}

void ActListForm::handleEditFinish()

{
    qDebug() << "handleEditFinish()";
    QObject* obj = sender();

    QLineEdit* lEdit = qobject_cast<QLineEdit*>(sender());

    int maxRow = global.actList.size();
    bool ok = true;
    int val;
    for(int row = 0; row < maxRow; row++)
    {
   // qDebug() << row << global.actList[row].ptrLineEdit <<obj ;
  /*      if(global.actList[row].ptrLineEdit == obj){
            val = lEdit->text().toInt(&ok);
            qDebug() <<"DI " <<row<< val << ok;
            if(ok){
                global.actList[row].digital = val;
            }

        }
*/
        if(global.actList[row].ptrLineEdit == obj){
            val = lEdit->text().toInt(&ok);
            qDebug() <<"AN " <<row<< val << ok;
            if(ok){
                global.actList[row].analog = val;
                acttablemodel->updateData(row);
                global.needUpdateDIoutputs(row,val);
            }
        }
    }
    // qDebug() << "lEdit " << lEdit->text() ;
}

void ActListForm::updateData(int row)
{
    acttablemodel->updateData(row);
    //qDebug() << "ActListForm::updateRow(int row) " << row ;

}


ActListForm::~ActListForm()
{
    delete ui;
}
