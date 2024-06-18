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
 ui->statusbar->showMessage("Process flow 2");
}

void ProcUI2::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED (event);
    float koefx = 1.0;
    float koefy = 1.0;
    float koef = 1.0;
    qDebug() << "ProcUI1::resizeEvent"  << size().height() << size().width();
    global.UIXresizeSizePf2 = size().width();
    global.UIYresizeSizePf2 = size().height();

    if(size().width() > 0 && size().height() > 0){
        koefx =  (float)global.UIXsizePf2/global.UIXresizeSizePf2;
        koefy = (float)global.UIYsizePf2/global.UIYresizeSizePf2;
    }

    if(koefx >= koefy){
        koef = koefx;
    }
    else{
        koef = koefy;
    }

    if(koef == 0){
        koef = 1;
    }
     qDebug() << "resizeEvent UIsize 2"  << global.UIXsizePf2 << global.UIYsizePf2 <<size().width()<<size().height()<<koefx <<koefy<<koef;
    global.zoomKoefPf2 = koef;

}

void ProcUI2::timerEvent(QTimerEvent *event)
{
   // Q_UNUSED(event)
}

void ProcUI2::drawWidgets()
{
    qDebug() << "widData draw  " << global.widHash.size() << "elements";

    foreach (Global::wdataStruct widData, global.widHash){

        if( widData.page == 2){    // all pages
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

