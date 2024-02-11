#include "rs232.h"
#include "ui_rs232.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QSerialPort>
//#include <QPointF>


#define TMIN 60
#define TMAX 70
Rs232::Rs232(Global &global,QWidget *parent)
    : QMainWindow(parent)
    , global(global)
    , ui(new Ui::Rs232)
{
    ui->setupUi(this);

    m_serial = new QSerialPort(this);
    if (!initPort()){
        qDebug() << "start timemark 1000";
        timerInit = startTimer(1000, Qt::CoarseTimer);

    }




    connect(m_serial, &QSerialPort::readyRead,   //readyRead
            this, &readSerial);
    initUI();

    sp_seriesT1 = new QSplineSeries();
    //////////////////////////////////////////////////////////////

    QPointF  spser;
    for(int i = 0; i<5;i++){
        spser.setX (i);
        spser.setY ((int)i/10 ); // for testing
        sp_seriesT1->append(spser);
    }

    /////////////////////////////////////////////////////////////
    sp_seriesT2 = new QSplineSeries();
    sp_seriesMin = new QSplineSeries();
    sp_seriesMax = new QSplineSeries();

    // m_serial = new QSerialPort(this);
    drawTchart();
}

Rs232::~Rs232()
{
    delete ui;
}

bool Rs232::initPort()
{
    qDebug() << "\ninitPort()";

    QTextStream out(stdout);
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    //qDebug() << "\n";
    out << QObject::tr("Total number of ports available: ") << serialPortInfos.count() << "\n";

    const QString blankString = QObject::tr("N/A");
    QString description;
    QString manufacturer;
    QString serialNumber;

    str = "Available com port: \n";
    ui->textEditInfo->append(str);

    for (const QSerialPortInfo &serialPortInfo : serialPortInfos) {
        description = serialPortInfo.description();
        manufacturer = serialPortInfo.manufacturer();
        serialNumber = serialPortInfo.serialNumber();
        qDebug() <<serialNumber <<description << manufacturer << "\n"; // << endl

        ComInfo  comInfo;
        comInfo.port = serialPortInfo.portName();
        comInfo.location = serialPortInfo.systemLocation();
        comInfo.description = !description.isEmpty() ? description : blankString;
        comInfo.manufacturer = !manufacturer.isEmpty() ? manufacturer : blankString;
        comInfo.serialNumber = !serialNumber.isEmpty() ? serialNumber : blankString;
        comInfo.vendorIdentifier = serialPortInfo.hasVendorIdentifier() ? QByteArray::number(serialPortInfo.vendorIdentifier(), 16) : blankString;
        comInfo.productIdentifier = serialPortInfo.hasProductIdentifier() ? QByteArray::number(serialPortInfo.productIdentifier(), 16) : blankString;


        comPortMap.insert(serialPortInfo.portName(),comInfo);
        str = "";
        str.append(QObject::tr("Port: ") + serialPortInfo.portName() + "\n");
        str.append(QObject::tr("Location: ") + serialPortInfo.systemLocation() + "\n");
        str.append(QObject::tr("Description: ") + (!description.isEmpty() ? description : blankString) + "\n");
        str.append(QObject::tr("Manufacturer: ") + (!manufacturer.isEmpty() ? manufacturer : blankString) + "\n");
        str.append(QObject::tr("Serial number: ") + (!serialNumber.isEmpty() ? serialNumber : blankString) + "\n");
        str.append(QObject::tr("Vendor Identifier: ") + (serialPortInfo.hasVendorIdentifier() ? QByteArray::number(serialPortInfo.vendorIdentifier(), 16) : blankString) + "\n");
        str.append(QObject::tr("Product Identifier: ") + (serialPortInfo.hasProductIdentifier() ? QByteArray::number(serialPortInfo.productIdentifier(), 16) : blankString) + "\n\n");

        qDebug() << str;
        ui->textEditInfo->append(str);


    }
    qDebug() << "Open port:";
    //  m_serial = new QSerialPort(this);

    corectPort = nullptr;
    foreach (ComInfo cInfo, comPortMap){

        // "403"  FDI RS232
        // "2341" Arduino MEGA
        if(cInfo.vendorIdentifier == "2341"){
            corectPort = cInfo.port;
        }
    }

    if(corectPort != nullptr){
        m_serial->setPortName(corectPort);
        m_serial->setBaudRate(115200);
        m_serial->setDataBits(QSerialPort::Data8);
        m_serial->setParity(QSerialPort::NoParity);
        m_serial->setStopBits(QSerialPort::OneStop);
        m_serial->setFlowControl(QSerialPort::NoFlowControl);

        str = "Selected port: ";
        str.append(corectPort);
        str.append("\n");
        str.append(comPortMap[corectPort].manufacturer);
        str.append(", ");
        str.append(comPortMap[corectPort].serialNumber);
        str.append("\n");
        ui->textEditInfo->append(str);

        str = corectPort;
        if(m_serial->open(QIODevice::ReadWrite)){
            str.append(" open successful!\n");
            ui->textEditInfo->append(str);
            if(timerInit > 0){
                killTimer(timerInit);
            }
            return true;
        }
        else{
            str.append(" open error!");
            ui->textEditInfo->append(str);
            return false;
        }
    }
    else{
        str = "Available com port nof fond \n search Vendor Id ";
        str.append("2341");
        ui->textEditInfo->append(str);
        return false;
    }

}

void Rs232::sendData(QString send)
{
    QByteArray utf8Data = send.toUtf8();
    const qint64 written = m_serial->write(utf8Data);
    Q_UNUSED(written);
}

void Rs232::initUI()
{
    col = QColor(Qt::green);
    qssGreen = QString("background-color: %1").arg(col.name());

    col = QColor(Qt::red);
    qssRed = QString("background-color: %1").arg(col.name());

    col = QColor(Qt::gray);
    qssGray = QString("background-color: %1").arg(col.name());



}

void Rs232::readSerial()
{
    const QByteArray data = m_serial->readAll();
    // qDebug()<< "data" << data;
    QString str = QString(data);
    //ui->textEditInfo->append("Receive " + str);
    currserdata = data;
}

void Rs232::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == timerId){
        att++;
        bool ok;
        int t1 = 0;
        int t2 = 0;
        auto str= QString(currserdata);
        QStringList elements = str.split(',');

        qDebug() << "elemrnt" <<elements.size();
        if(elements.size() > 3){
            qDebug() << elements[0]<< elements[1] << elements[2] << elements[3];

            t1 = elements[1].toInt(&ok);
            if(!ok){
                t1 = 0;
            }
            t2 = elements[3].toInt(&ok);
            if(!ok){
                t2 = 0;
            }
        }

        QPointF  spser;
        spser.setX (att);
        spser.setY (t1);
        sp_seriesT1->append(spser);

        chart1Data chdat;
        chdat.chart1 = spser;

        spser.setY (t2);
        sp_seriesT2->append(spser);
        chdat.chart2 = spser;

        chartDataList.append(chdat);

        qDebug() << "add" << spser.x() << spser.y();


        sp_seriesMin->append(att,TMIN);
        sp_seriesMax->append(att,TMAX);

        //chart1->axes(Qt::Horizontal).first()->setRange(0, 200);


        // chartView1->update();
        //  chartView1->repaint();
        //chart1->removeAllSeries();
        chart1->removeSeries(sp_seriesT1);
        chart1->removeSeries(sp_seriesT2);
        chart1->removeSeries(sp_seriesMin);
        chart1->removeSeries(sp_seriesMax);

        chart1->addSeries(sp_seriesT1);
        chart1->addSeries(sp_seriesT2);
        chart1->addSeries(sp_seriesMin);
        chart1->addSeries(sp_seriesMax);



        ui->textEditInfo->append(QString(currserdata));
        //ui->verticalLayout_chart->addWidget(chart1);
    }

    if(event->timerId() == timerInit){
        initPort();
    }

}


void Rs232::on_pushButtonStart_clicked()
{
    recordStatus = true;
    ui->pushButtonStart->setStyleSheet(qssGreen);
    ui->pushButton_Stop->setStyleSheet(qssGray);
    ui->label_statuss->setText("Notiek ieraksts");
    if(timerId > 0){
        killTimer(timerId);
    }
    timerId = startTimer(timeMark * 100, Qt::CoarseTimer); //1000 for testing
}


void Rs232::on_pushButton_Stop_clicked()
{
    recordStatus = false;
    ui->pushButtonStart->setStyleSheet(qssGray);
    ui->pushButton_Stop->setStyleSheet(qssRed);
    ui->label_statuss->setText("Ieraksts izslēgts");
    if(timerId > 0){
        killTimer(timerId);
    }
}


void Rs232::on_pushButton_1s_clicked()
{
    timeMark = 1;
    ui->pushButton_1s->setStyleSheet(qssGreen);
    ui->pushButton_10s->setStyleSheet(qssGray);
    ui->pushButton_60s->setStyleSheet(qssGray);
}


void Rs232::on_pushButton_10s_clicked()
{
    timeMark = 10;
    ui->pushButton_1s->setStyleSheet(qssGray);
    ui->pushButton_10s->setStyleSheet(qssGreen);
    ui->pushButton_60s->setStyleSheet(qssGray);
}


void Rs232::on_pushButton_60s_clicked()
{
    timeMark = 60;
    ui->pushButton_1s->setStyleSheet(qssGray);
    ui->pushButton_10s->setStyleSheet(qssGray);
    ui->pushButton_60s->setStyleSheet(qssGreen);
}


void Rs232::drawTchart()
{
    qDebug() <<"drawTchart ";

    chart1 = new QChart();
    sp_seriesT1->setName("T1");
    sp_seriesT2->setName("T2");
    sp_seriesMin->setName("Min");
    sp_seriesMax->setName("Max");

    chart1->addSeries(sp_seriesT1);
    // chart1->addSeries(sp_seriesT2);
    // chart1->addSeries(sp_seriesMin);
    // chart1->addSeries(sp_seriesMax);



    //QValueAxis *axisX = new QValueAxis;
    //QValueAxis *axisY = new QValueAxis;

    axisX = new QValueAxis;
    axisY = new QValueAxis;

    axisX->setLabelFormat("%i");
    axisX->setTitleText("time");
    axisX->setRange(0, 650);
    //axisX->setLabelFormat("%.2f");
    axisX->setTickCount(14);


    axisY->setLabelFormat("%i");
    axisY->setTitleText("Temperature");
    axisY->setRange(0, 100);
    // axisY->setLabelFormat("%.2f");
    axisY->setTickCount(7);


    // sp_series1->attachAxis(axisX);
    //sp_series1->attachAxis(axisY);


    chart1->setTitle("Temperatūra pēc Dino");



    chart1->addAxis(axisX, Qt::AlignBottom);
    chart1->addAxis(axisY, Qt::AlignLeft);



    chart1->axes(Qt::Vertical).first()->setRange(0,100);
    chart1->axes(Qt::Horizontal).first()->setRange(0, 500);
    chart1->legend()->setVisible(true);
    chart1->legend()->setAlignment(Qt::AlignBottom);

    // Customize the title font
    QFont font;
    font.setPixelSize(18);
    chart1->setTitleFont(font);
    chart1->setTitleBrush(QBrush(Qt::black));
    //chart1->setTitle("Name1");

    // Change the line color and weight
    QPen pen(QRgb(0x00CED1));
    pen.setWidth(1);

    sp_seriesT1->setPen(pen);
    sp_seriesT2->setPen(pen);

    QPen pen1(Qt::red);
    pen1.setWidth(1);

    sp_seriesMax->setPen(pen1);
    sp_seriesMin->setPen(pen1);



    chart1->setAnimationOptions(QChart::NoAnimation);

    // QChartView *chartView1 = new QChartView(chart1);
    chartView1 = new QChartView(chart1);
    chartView1->setRenderHint(QPainter::Antialiasing);

    QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window,QRgb(0xffffff));
    pal.setColor(QPalette::WindowText,QRgb(0x404040));
    qApp->setPalette(pal);
    ui->verticalLayout_chart->addWidget(chartView1);//       for testing
}
