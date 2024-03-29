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
   // myAxisX = new QValueAxis();
   // myAxisY = new QValueAxis();
    myAxisYtitle = "Laiks 1 iedaļa 1s";
    timer1sId  = startTimer(1000, Qt::CoarseTimer);
    ui->setupUi(this);



    m_serial = new QSerialPort(this);

    if (!initPort()){
        qDebug() <<"start timemark 1000" << m_serial->openMode();
        timerInit = startTimer(1000, Qt::CoarseTimer);
    }

    STATE = WAIT_START;
    startTime = QTime(0,0);
    connect(m_serial, &QSerialPort::readyRead,this, &Rs232::readSerial);   //readyRead
    connect (this, SIGNAL(newData(QStringList)), this, SLOT(newDataUpdateCh(QStringList)));
    initUI();

    drawTchart();

}

Rs232::~Rs232()
{
    qDebug() <<"Rs232::~Rs232()";
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

    corectPort = global.dev1;

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
        str = corectPort;
        str.append(" Not fond \n Vendor Id: ");
        str.append(global.dev1_VendorId);
        str.append("\n");
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


    if(event->timerId() == timerIdUpd){
        // qDebug()<< "Event Id";
        att++;
        receiveDataRequest = true;

        if(att > 100){
            int range = att * 1.1;
            //chart1->axes(Qt::Horizontal).first()->setRange(0, range);
            myAxisX->setRange(0, range);
        }
    }

    if(event->timerId() == timerInit){
        qDebug()<< "Event Init";
        initPort();
    }

}

void Rs232::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    m_serial->close();
    qDebug() <<"Rs232::closeEvent";
}

void Rs232::mouseDoubleClickEvent(QMouseEvent *event)
{
Q_UNUSED(event);
}


void Rs232::on_pushButtonStart_clicked()
{
    recordStatus = true;
    ui->pushButtonStart->setStyleSheet(qssGreen);
    ui->pushButton_Stop->setStyleSheet(qssGray);
    ui->label_statuss->setText(tr("Notiek ieraksts"));
    if(timerIdUpd > 0){
        killTimer(timerIdUpd);
    }
    timerIdUpd = startTimer(timeMark * 1000, Qt::CoarseTimer); //1000 for testing
    sp_seriesT1->clear();
    sp_seriesT2->clear();
    sp_seriesMin->clear();
    sp_seriesMax->clear();
    att = 0;
    startTime = QTime::currentTime();
    //chart1->axes(Qt::Horizontal).first()->setRange(0, 110);
    myAxisX->setRange(0, 110);
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
    if(timerIdUpd > 0){
        killTimer(timerIdUpd);
    }
    startTime = QTime(0,0);
}


void Rs232::on_pushButton_1s_clicked()
{
    timeMark = 1;
    ui->pushButton_1s->setStyleSheet(qssGreen);
    ui->pushButton_10s->setStyleSheet(qssGray);
    ui->pushButton_60s->setStyleSheet(qssGray);
    //myAxisX->setTitleText("Laiks 1iedaļa 1s");
    myAxisYtitle = "Laiks 1 iedaļa 1s";
}


void Rs232::on_pushButton_10s_clicked()
{
    timeMark = 10;
    ui->pushButton_1s->setStyleSheet(qssGray);
    ui->pushButton_10s->setStyleSheet(qssGreen);
    ui->pushButton_60s->setStyleSheet(qssGray);
    //myAxisX->setTitleText("Laiks 1iedaļa 10s");
    myAxisYtitle = "Laiks 1 iedaļa 10s";
}


void Rs232::on_pushButton_60s_clicked()
{
    timeMark = 60;
    ui->pushButton_1s->setStyleSheet(qssGray);
    ui->pushButton_10s->setStyleSheet(qssGray);
    ui->pushButton_60s->setStyleSheet(qssGreen);
   // myAxisX->setTitleText("Laiks 1iedaļa 60s");
    myAxisYtitle = "Laiks 1 iedaļa 60s";
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



  //  chart1->createDefaultAxes();
   // chart1->axes(Qt::Vertical).first()->setRange(0,100);
   // chart1->axes(Qt::Horizontal).first()->setRange(0, 110);

   // chart1->axes(Qt::Horizontal).first()->setTitleText(myAxisYtitle);



    myAxisX = new QValueAxis();
    myAxisY = new QValueAxis();
    myAxisX->setLabelFormat("%i");
  //  myAxisX->setTitleText(myAxisYtitle);
    myAxisX->setRange(0, 110);
    myAxisX->setTickCount(5);
    chart1->addAxis(myAxisX, Qt::AlignBottom);


    myAxisY = new QValueAxis();
    myAxisY->setLabelFormat("%i");
   //myAxisY->setTitleText("Temperatūra"); //u8"\u00B0"
    myAxisY->setRange(0, 100);
    myAxisY->setTitleText("Temperatūra \u2103"); //u8"\u00B0"
    myAxisY->setTickCount(6);
    chart1->addAxis(myAxisY, Qt::AlignLeft);


    sp_seriesT1->attachAxis(myAxisX);
    sp_seriesT1->attachAxis(myAxisY);
    sp_seriesT2->attachAxis(myAxisX);
    sp_seriesT2->attachAxis(myAxisY);
    sp_seriesMin->attachAxis(myAxisX);
    sp_seriesMin->attachAxis(myAxisY);
    sp_seriesMax->attachAxis(myAxisX);
    sp_seriesMax->attachAxis(myAxisY);

/*
     chart1 = new QChart();
     chart1->addSeries(sp_seriesT1);
     chart1->addSeries(sp_seriesT2);
     chart1->addSeries(sp_seriesMin);
     chart1->addSeries(sp_seriesMax);

     chart1->setTitle(str);
      chart1->addAxis(myAxisX, Qt::AlignBottom);
     chart1->addAxis(myAxisY, Qt::AlignLeft);
*/



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
       // qDebug() << currSdata[0] <<"," << currSdata[1] <<"," << currSdata[2];

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
        //chart1->axes(Qt::Horizontal).first()->setRange(0, range);
        myAxisX->setRange(0, range);
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
        stream<< "N.P.K.\t\t" <<"Time\t\t"<< "T1\t\t" << "T2";
         for(int i = 0; i < chartDataList.size();i++){

            stream<< QString::number(i) << ",\t\t";
            stream<< QString::number(chartDataList[i].chartT1.x());
            stream<<  ",\t\t";
            stream<< QString::number(chartDataList[i].chartT1.y());
            stream<<  ",\t\t";
 //           stream<< QString::number(chartDataList[i].chartT2.x());
 //           stream<<  ", ";
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

