#include "procui1.h"
#include "ui_procui1.h"



ProcUI1::ProcUI1(Global& global, QWidget* parent) :
    QMainWindow(parent)
    , global(global)
    , ui(new Ui::ProcUI1) {

    ui->setupUi(this);

    initUI();
    drawWidgets();
}

ProcUI1::~ProcUI1() {
    delete ui;
}

void ProcUI1::initUI() {
    this->move(100, 50);
    this->resize(1820, 980);

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

    pal.setColor(QPalette::Base, Qt::yellow);
    ui->textEdit_Info->setPalette(pal);

    ui->statusbar->showMessage("Process flow 1");

}

void ProcUI1::resizeEvent(QResizeEvent* event) {
    Q_UNUSED(event);

    float koefx = 1.0;
    float koefy = 1.0;
    float koef = 1.0;
    qDebug() << "ProcUI1::resizeEvent" << size().height() << size().width();
    global.UIXresizeSizePf1 = size().width();
    global.UIYresizeSizePf1 = size().height();

    if (size().width() > 0 && size().height() > 0) {
        koefx = (float)global.UIXsizePf1 / global.UIXresizeSizePf1;
        koefy = (float)global.UIYsizePf1 / global.UIYresizeSizePf1;
    }

    if (koefx >= koefy) {
        koef = koefx;
    } else {
        koef = koefy;
    }

    if (koef == 0) {
        koef = 1;
    }
    //qDebug() << "resizeEvent UIsize 1" << global.UIXsizePf1 << global.UIYsizePf1 << size().width() << size().height() << koefx << koefy << koef;
    global.zoomKoefPf1 = koef;


}



void ProcUI1::timerEvent(QTimerEvent* event) {
    Q_UNUSED(event)
}
void ProcUI1::drawWidgets() {
    qDebug() << "widData draw  " << global.widHash.size() << "elements";

    foreach(Global::wdataStruct widData, global.widHash) {

        if (widData.page == 1) {    // all pages
            // qDebug() << "drawWidgets Draw: " << widData.type << widData.name << "page" <<widData.page ;
            switch (widData.type) {
            case WidgetType::widgT::Dyno:
            {
                new Dyno(global, widData.name, ui->desktop);
                // ui->horizontalLayout_Process->addWidget(dynoA);

            }
            break;

            case WidgetType::widgT::Mix:
            {
                new Mix(global, widData.name, ui->desktop);
                //ui->horizontalLayout_Process->addWidget(mixA);
            }
            break;

            case WidgetType::widgT::Pipe:
            {
                new Pipe(global, widData.name, ui->desktop);
                // ui->horizontalLayout_Process->addWidget(pipeA);
            }
            break;

            case WidgetType::Pump:
            {
                new Pump(global, widData.name, ui->desktop);
                // ui->horizontalLayout_Process->addWidget(pumpA);

            }
            break;

            case WidgetType::Tvertne:
            {
                new Tvertne(global, widData.name, ui->desktop);
                //ui->horizontalLayout_Process->addWidget(tvertneA);

            }
            break;

            case WidgetType::Valve:
            {
                new Valve(global, widData.name, ui->desktop);
                //ui->horizontalLayout_Process->addWidget(valveA);

            }
            break;

            case WidgetType::ScalesBase:
            {
                new ScalesBase(global, widData.name, ui->desktop);
                // ui->horizontalLayout_Process->addWidget(scalesBase);

            }
            break;

            case WidgetType::ScalesMass:
            {
                new ScalesMass(global, widData.name, ui->desktop);
                //ui->horizontalLayout_Process->addWidget(scalesMass);

            }
            break;
            case WidgetType::Dispax:
            {
                new Dispax(global, widData.name, ui->desktop);
                //ui->horizontalLayout_Process->addWidget(scalesMass);
            }
            break;
            case WidgetType::Label:
            {
                new Label(global, widData.name, ui->desktop);
                //ui->horizontalLayout_Process->addWidget(scalesMass);
            }
            break;

            default:
                qDebug() << "Wrong widget type !!! " << widData.type;
                break;
            }
        }
    }

}

void ProcUI1::on_pushButton_Stop_clicked() {

}

