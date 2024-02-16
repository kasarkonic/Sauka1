#include "rs232.h"
#include "ui_rs232.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QDateTime>
#include <QFile>
#include <QMessageBox>




#define TMIN 56
#define TMAX 70


Rs232::Rs232(Global &global,QWidget *parent)
    : QMainWindow(parent)
    , global(global)
    , ui(new Ui::Rs232)
{
    timer1sId  = startTimer(100, Qt::CoarseTimer);
    ui->setupUi(this);

    m_serial = new QSerialPort(this);
    if (!initPort()){
        qDebug() <<"start timemark 1000";
        timerInit = startTimer(1000, Qt::CoarseTimer);
    }

    STATE = WAIT_START;
    startTime = QTime(0,0);
    connect(m_serial, &QSerialPort::readyRead,this, &Rs232::readSerial);   //readyRead
    connect (this, SIGNAL(newData(QStringList)), this, SLOT(newDataUpdateCh(QStringList)));
    initUI();
    /*
    sp_seriesT1 = new QSplineSeries();
    sp_seriesT2 = new QSplineSeries();
    sp_seriesMin = new QSplineSeries();
    sp_seriesMax = new QSplineSeries();
*/
    drawTchart();
}

Rs232::~Rs232()
{
    m_serial->close();
    delete ui;
}

void Rs232::initUI()
{
    col = QColor(Qt::green);
    qssGreen = QString("background-color: %1").arg(col.name());

    col = QColor(Qt::red);
    qssRed = QString("background-color: %1").arg(col.name());

    col = QColor(Qt::gray);
    qssGray = QString("background-color: %1").arg(col.name());

    col = QColor(Qt::cyan);
    qssCyan = QString("background-color: %1").arg(col.name());

    ui->pushButton_Save->setStyleSheet(qssCyan);

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
        m_serial->setBaudRate(QSerialPort::Baud115200);
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

void Rs232::readSerial()
{
    if(m_serial->bytesAvailable()) {

        if(!m_serial->canReadLine()){
          qDebug() <<"line not receive all";
            return;
        }

        // If any bytes are available
        QByteArray data = m_serial->readLine(25);// readAll();  //readData()  readLineData()


        qDebug() <<"readSerial()" <<data ;//<< m_serial->waitForReadyRead();

        if(!data.isEmpty()) {                                                             // If the byte array is not empty
            char *temp = data.data();
            // Get a '\0'-terminated char* to the data

            for(int i = 0; temp[i] != '\0'; i++) {                                        // Iterate over the char*
                switch(STATE) {                                                           // Switch the current state of the message
                case WAIT_START:                                                          // If waiting for start [$], examine each char
                    if(temp[i] == START_MSG) {                                            // If the char is $, change STATE to IN_MESSAGE
                        STATE = IN_MESSAGE;
                        receivedData.clear();                                             // Clear temporary QString that holds the message
                        break;                                                            // Break out of the switch
                    }
                    break;
                case IN_MESSAGE:                                                          // If state is IN_MESSAGE
                    if(temp[i] == END_MSG) {                                              // If char examined is ;, switch state to END_MSG
                        STATE = WAIT_START;
                        QStringList incomingData = receivedData.split(' ');               // Split string received from port and put it into list
                        //emit newData(incomingData);                                       // Emit signal for data received with the list

                        if(receiveDataRequest){
                            emit newData(incomingData);
                            //qDebug() <<"emit" <<incomingData;
                            receiveDataRequest = false;
                        }
                        break;
                    }
                    else if (isdigit (temp[i]) || isspace (temp[i]) || temp[i] =='-' || temp[i] =='.')
                    {
                        /* If examined char is a digit, and not '$' or ';', append it to temporary string */
                        receivedData.append(temp[i]);
                    }
                    break;
                default: break;
                }
            }
        }
    }

}

void Rs232::timerEvent(QTimerEvent *event)
{


    if(event->timerId() == timer1sId){
        currentTime = QTime::currentTime().toString("hh:mm:ss");
        setWindowTitle(currentTime);
       // qDebug() <<startTime << currentTime;

       // if(!startTime.isNull()){
        if(startTime != QTime(0,0)){

            QTime finishTime = QTime::currentTime();

            int sec = startTime.secsTo(finishTime);
            QTime t = QTime(0,0).addSecs(sec);
              QString durat = QString("%1h. %2min. %3sek.")
                .arg(t.hour()).arg(t.minute()).arg(t.second());

            QString str = tr("  Ieraksts sākts ");
            str.append(startTime.toString("hh:mm:ss"));
            str.append(tr(",  ieraksta ilgums "));
            str.append(durat);     //.toString("hh:mm:ss")
            str.append(tr(", laika iedaļas vērtība "));
            str.append(QString::number(timeMark,10));
            str.append(tr("s."));
            ui->label_chart_info->setText(str);
        }
    }


    if(event->timerId() == timerId){
        // qDebug()<< "Event Id";
        att++;
        receiveDataRequest = true;

        if(att > 100){
            int range = att * 1.1;
            chart1->axes(Qt::Horizontal).first()->setRange(0, range);
        }
    }

    if(event->timerId() == timerInit){
        qDebug()<< "Event Init";
        initPort();
    }

}

void Rs232::closeEvent(QCloseEvent *event)
{
    m_serial->close();
    delete ui;
}

void Rs232::mouseDoubleClickEvent(QMouseEvent *event)
{

}


void Rs232::on_pushButtonStart_clicked()
{
    recordStatus = true;
    ui->pushButtonStart->setStyleSheet(qssGreen);
    ui->pushButton_Stop->setStyleSheet(qssGray);
    ui->label_statuss->setText(tr("Notiek ieraksts"));
    if(timerId > 0){
        killTimer(timerId);
    }
    timerId = startTimer(timeMark * 100, Qt::CoarseTimer); //1000 for testing
    sp_seriesT1->clear();
    sp_seriesT2->clear();
    sp_seriesMin->clear();
    sp_seriesMax->clear();
    att = 0;
    startTime = QTime::currentTime();
    chart1->axes(Qt::Horizontal).first()->setRange(0, 110);
}


void Rs232::on_pushButton_Stop_clicked()
{
    if(!createMessageBox(tr("Vai vēlaties pārtraut ierakstu?"))){
        return;
    }
    recordStatus = false;
    ui->pushButtonStart->setStyleSheet(qssGray);
    ui->pushButton_Stop->setStyleSheet(qssRed);
    ui->label_statuss->setText(tr("Ieraksts pārtraukts"));
    if(timerId > 0){
        killTimer(timerId);
    }
    startTime = QTime(0,0);
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

    sp_seriesT1 = new QSplineSeries();
    sp_seriesT2 = new QSplineSeries();
    sp_seriesMin = new QSplineSeries();
    sp_seriesMax = new QSplineSeries();

    chart1 = new QChart();
    sp_seriesT1->setName("T1");
    sp_seriesT2->setName("T2");
    sp_seriesMin->setName("Min");
    sp_seriesMax->setName("Max");

    chart1->addSeries(sp_seriesT1);
    chart1->addSeries(sp_seriesT2);
    chart1->addSeries(sp_seriesMin);
    chart1->addSeries(sp_seriesMax);


    QString str = tr("Dino temperatūra        ");
    str.append(currentTime)  ;
    chart1->setTitle(str);

    chart1->createDefaultAxes();
    chart1->axes(Qt::Vertical).first()->setRange(0,100);
    chart1->axes(Qt::Horizontal).first()->setRange(0, 110);
    chart1->legend()->setVisible(true);
    chart1->legend()->setAlignment(Qt::AlignBottom);

    // Customize the title font
    QFont font;
    font.setPixelSize(18);
    chart1->setTitleFont(font);
    chart1->setTitleBrush(QBrush(Qt::black));
    //chart1->setTitle("Name1");

    // Change the line color and weight
    //QPen pen(QRgb(0xff7700));
    QPen pen(Qt::blue);
    pen.setWidth(1);

    sp_seriesT1->setPen(pen);

    //QPen pen1(QRgb(0x05fe01));
    QPen pen1(Qt::green);
    pen1.setWidth(1);
    sp_seriesT2->setPen(pen1);

    QPen pen2(Qt::red);
    pen2.setWidth(1);

    sp_seriesMax->setPen(pen2);
    sp_seriesMin->setPen(pen2);



    chart1->setAnimationOptions(QChart::NoAnimation);

    // QChartView *chartView1 = new QChartView(chart1);
    chartView1 = new QChartView(chart1);
    chartView1->setRenderHint(QPainter::Antialiasing);

    QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window,QRgb(0xffffff));
    pal.setColor(QPalette::WindowText,QRgb(0x404040));
    qApp->setPalette(pal);
    ui->verticalLayout_chart->addWidget(chartView1);
}

bool Rs232::createMessageBox(QString text)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, " ", text, QMessageBox::Yes|QMessageBox::No);
    return (reply == QMessageBox::Yes);
}

void Rs232::newDataUpdateCh(QStringList currSdata)
{

    bool ok;
    int t1 = 0;
    int t2 = 0;


    // QStringList elements = QString(currSdata).split(',');

    qDebug() << "currSdata" <<currSdata.size() << currSdata;

    if(currSdata.size() == 4){
        qDebug() << currSdata[0] <<"," << currSdata[1] <<"," << currSdata[2];

        t1 = currSdata[1].toFloat(&ok);
        if(!ok){
            ui->textEditInfo->append(QString("Uztverti kļūdaini dati !!!"));
            t1 = 0;
        }
        t2 = currSdata[2].toFloat(&ok);
        if(!ok){
            ui->textEditInfo->append(QString("Uztverti kļūdaini dati !!!"));
            t2 = 0;
        }

        chart1Data chdat;
        // QPointF  spser;
        spser.setX (att);
        spser.setY (t1);

        sp_seriesT1->append(spser);
        chdat.chartT1 = spser;

        spser.setY (t2);
        sp_seriesT2->append(spser);
        chdat.chartT2 = spser;

        chartDataList.append(chdat);


        //qDebug() << "add T2: " << spser.x() << spser.y();

        sp_seriesMin->append(att,TMIN);
        sp_seriesMax->append(att,TMAX);

    }
    else{
        qDebug() << currSdata;
    }

    // QString strn = "Dino temperatūra        ";
    // strn.append(currentTime)  ;
    // chart1->setTitle(strn);

    if(att > 100){
        int range = att * 1.1;
        chart1->axes(Qt::Horizontal).first()->setRange(0, range);
    }

}



void Rs232::on_pushButton_Save_clicked()
{
    QString newstr = currentTime.replace(":","_");

    qDebug() << currentTime << newstr;

    QString filename = "Dino_T_";


    filename.append (currentTime);
    filename.append(".png");
    chartView1->grab().save(filename) ;

    ui->textEditInfo->append(QString("Izveidots fails: ") + filename);


    filename = "Dino_T_";
    filename.append (currentTime);
    filename.append(".txt");

    QFile file(filename);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);

        stream<< "\t" <<filename<< "\n\n\n";

         for(int i = 0; i < chartDataList.size();i++){

            stream<< QString::number(i) << ",\t";
            stream<< QString::number(chartDataList[i].chartT1.x());
            stream<<  ", ";
            stream<< QString::number(chartDataList[i].chartT1.y());
            stream<<  ",\t";
            stream<< QString::number(chartDataList[i].chartT2.x());
            stream<<  ", ";
            stream<< QString::number(chartDataList[i].chartT2.y());
            stream<< "\n";
         }
    }
          //      foreach (chart1Data, chartDataList) {
        //stream << "something" << endl;
            file.close();
   // filename = "Dino_T_";
   // filename.append (currentTime);
   // filename.append(".txt");
   // chartView1->grab().save(filename) ;

    ui->textEditInfo->append(QString("Izveidots fails: ") + filename);
   // }


}

