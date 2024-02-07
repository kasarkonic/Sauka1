#include "parmani.h"
#include "ui_parmani.h"
#include "global.h"

ParMani::ParMani(Global &global, QWidget *parent)
    : QMainWindow(parent)
    , global(global)
    , ui(new Ui::ParMani)
{
    ui->setupUi(this);
    ui->label->setText("Es vēl mācos");
    Dyno *dynoA = new Dyno(global,"",this);
    ui->verticalLayout->addWidget(dynoA);
    timerId = startTimer(200, Qt::CoarseTimer);
     qDebug() << "parmani::att "<< att ;
}

ParMani::~ParMani()
{
    delete ui;
}

void ParMani::on_pushButtonExit_clicked()
{
    close();
}

void ParMani::timerEvent(QTimerEvent *event)
{
    Q_UNUSED (event);
     qDebug() << "Pipe::att "<< att ;

    int step = 1;
    att = att + step;


    int attX;
    int attY;
   // dynoA->move(currX,currY);

    qDebug() << "Pipe::att "<< att ;

}

