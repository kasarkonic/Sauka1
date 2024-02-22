#include "parmani.h"
#include "ui_parmani.h"
#include "global.h"

ParMani::ParMani(Global &global, QWidget *parent)
    : QMainWindow(parent)
    , global(global)
    , ui(new Ui::ParMani)
{
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, global.backgroundColor); //QColor(255, 0, 0, 127)
    //pal.setColor(QPalette::Window, QColor(242, 219, 238, 0.251));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    ui->setupUi(this);
    ui->label->setText("Es vēl augu");
    //Dyno *dynoA = new Dyno(global,"",this);
   // ui->verticalLayout->addWidget(dynoA);
    //timerId = startTimer(200, Qt::CoarseTimer);
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

    qDebug() << "Mani::att "<< att ;

}

