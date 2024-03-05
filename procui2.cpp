#include "procui2.h"
#include "ui_procui2.h"


ProcUI2::ProcUI2(Global &global,QWidget *parent) :
    QMainWindow(parent)
   , global(global)
   , ui(new Ui::ProcUI2)
{

    ui->setupUi(this);
    drawWidgets();
    initUI();
}

ProcUI2::~ProcUI2()
{
    delete ui;
}

void ProcUI2::initUI()
{
    this->move(50,25);
    this->resize(1000,900);
QPixmap pixmap(":/pictures/logo2.png");
ui->label_Logo->setPixmap(pixmap);
ui->label_Logo->setMask(pixmap.mask());

QPalette pal = QPalette();

pal.setColor(QPalette::Window, global.backgroundColor); //QColor(255, 0, 0, 127)
//pal.setColor(QPalette::Window, QColor(242, 219, 238, 0.251));
this->setAutoFillBackground(true);
this->setPalette(pal);

QColor col = QColor(Qt::green);
QString qss = QString("background-color: %1").arg(col.name());
ui->pushButton_Stop->setStyleSheet(qss);

pal.setColor(QPalette::Base,Qt::yellow);
ui->textEdit_Info->setPalette(pal);

}

void ProcUI2::drawWidgets()
{
    qDebug() << "widData draw  " << global.widHash.size() << "elements";

    foreach (Global::wdataStruct widData, global.widHash){

        if( widData.page == 1 || widData.page == 3 ){    // all pages
            // qDebug() << "drawWidgets Draw: " << widData.type << widData.name << "page" <<widData.page ;
            switch (widData.type) {
            case WidgetType::widgT::Dyno:
            {
                Dyno *dynoA = new Dyno(global,widData.name,this);
                ui->horizontalLayout_Process->addWidget(dynoA);
            }
                break;

            case WidgetType::widgT::Mix:
            {
                Mix *mixA = new Mix(global,widData.name,this);
                ui->horizontalLayout_Process->addWidget(mixA);
            }
                break;

            case WidgetType::widgT::Pipe:
            {
                Pipe *pipeA = new Pipe(global,widData.name,this);
                ui->horizontalLayout_Process->addWidget(pipeA);
            }
                break;

            case WidgetType::Pump:
            {
                Pump *pumpA = new Pump(global,widData.name,this);
                ui->horizontalLayout_Process->addWidget(pumpA);

            }
                break;

            case WidgetType::Tvertne:
            {
                Tvertne *tvertneA = new Tvertne(global,widData.name,this);
                ui->horizontalLayout_Process->addWidget(tvertneA);

            }
                break;

            case WidgetType::Valve:
            {
                Valve *valveA = new Valve(global,widData.name,this);
                ui->horizontalLayout_Process->addWidget(valveA);

            }
                break;

            case WidgetType::ScalesBase:
            {
                ScalesBase *scalesBase = new ScalesBase(global,widData.name,this);
                ui->horizontalLayout_Process->addWidget(scalesBase);

            }
                break;

            case WidgetType::ScalesMass:
            {
                ScalesMass *scalesMass = new ScalesMass(global,widData.name,this);
                ui->horizontalLayout_Process->addWidget(scalesMass);

            }
                break;


            default:
                qDebug() << "Wrong widget type !!! "  <<widData.type;
                break;
            }
        }
    }
}

void ProcUI2::on_pushButton_Stop_clicked()
{

}
