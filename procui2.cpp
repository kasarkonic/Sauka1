#include "procui2.h"
#include "ui_procui2.h"

#include "dyno.h"
#include "conveyor.h"
#include "mix.h"
#include "pipe.h"
#include "pump.h"
#include "dispax.h"
#include "label.h"
#include "tvertne.h"
#include "valve.h"
#include "scalesbase.h"
#include "scalesmass.h"
#include "recipeform.h"


ProcUI2::ProcUI2(Global& global, QWidget* parent) :
    QMainWindow(parent)
    , global(global)
    , ui(new Ui::ProcUI2) {

    ui->setupUi(this);
    drawWidgets();
    initUI();
}

ProcUI2::~ProcUI2() {
    delete ui;
}

void ProcUI2::initUI() {
    this->move(50, 25);
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
    ui->statusbar->showMessage("Process flow 2");
    //RecipeForm new recipetForm
    new RecipeForm(ui->widget_Table);
    //new Conveyor(global, widData.name, ui->desktop);

}

void ProcUI2::resizeEvent(QResizeEvent* event) {
    Q_UNUSED(event);
    float koefx = 1.0;
    float koefy = 1.0;
    float koef = 1.0;
    qDebug() << "ProcUI1::resizeEvent" << size().height() << size().width();
    global.UIXresizeSizePf2 = size().width();
    global.UIYresizeSizePf2 = size().height();

    if (size().width() > 0 && size().height() > 0) {
        koefx = (float)global.UIXsizePf2 / global.UIXresizeSizePf2;
        koefy = (float)global.UIYsizePf2 / global.UIYresizeSizePf2;
    }

    if (koefx >= koefy) {
        koef = koefx;
    } else {
        koef = koefy;
    }

    if (koef == 0) {
        koef = 1;
    }
    //qDebug() << "resizeEvent UIsize 2" << global.UIXsizePf2 << global.UIYsizePf2 << size().width() << size().height() << koefx << koefy << koef;
    global.zoomKoefPf2 = koef;

}

void ProcUI2::timerEvent(QTimerEvent* event) {
    Q_UNUSED(event)
}

void ProcUI2::drawWidgets() {
    qDebug() << "widData draw  " << global.widHash.size() << "elements";


    foreach(Global::wdataStruct widData, global.widHash) {

        if (widData.page == 2) {    // all pages
            // qDebug() << "drawWidgets Draw: " << widData.type << widData.name << "page" <<widData.page ;
            switch (widData.type) {
            case WidgetType::widgT::Conveyor:
            {
                new Conveyor(global, widData.name, ui->desktop_2);
                // ui->horizontalLayout_Process->addWidget(ConveyorA);
            }
                break;
            case WidgetType::widgT::Dyno:
            {
                new Dyno(global, widData.name, ui->desktop_2);
                // ui->horizontalLayout_Process->addWidget(dynoA);
            }
            break;

            case WidgetType::widgT::Mix:
            {
                new Mix(global, widData.name, ui->desktop_2);
                //ui->horizontalLayout_Process->addWidget(mixA);
            }
            break;

            case WidgetType::widgT::Pipe:
            {
                new Pipe(global, widData.name, ui->desktop_2);
                //ui->horizontalLayout_Process->addWidget(pipeA);
            }
            break;

            case WidgetType::Pump:
            {
                new Pump(global, widData.name, ui->desktop_2);
                //ui->horizontalLayout_Process->addWidget(pumpA);

            }
            break;

            case WidgetType::Tvertne:
            {
                new Tvertne(global, widData.name, ui->desktop_2);
                //ui->horizontalLayout_Process->addWidget(tvertneA);

            }
            break;

            case WidgetType::Valve:
            {
                new Valve(global, widData.name, ui->desktop_2);
                //ui->horizontalLayout_Process->addWidget(valveA);

            }
            break;

            case WidgetType::ScalesBase:
            {
                new ScalesBase(global, widData.name, ui->desktop_2);
                //ui->horizontalLayout_Process->addWidget(scalesBase);

            }
            break;

            case WidgetType::ScalesMass:
            {
                new ScalesMass(global, widData.name, ui->desktop_2);
                //ui->horizontalLayout_Process->addWidget(scalesMass);

            }
            break;

            case WidgetType::Dispax:
            {
                new Dispax(global, widData.name, ui->desktop_2);
                //ui->horizontalLayout_Process->addWidget(scalesMass);
            }
            break;
            case WidgetType::Label:
            {
                new Label(global, widData.name, ui->desktop_2);
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

void ProcUI2::on_pushButton_Stop_clicked() {

}

