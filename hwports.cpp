#include "hwports.h"
#include "ui_hwports.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QSettings>


HwPorts::HwPorts(Global &global, QWidget *parent)
    : QMainWindow(parent)
    , global(global)
    , ui(new Ui::HwPorts)
{

    ui->setupUi(this);
    initUI();
    scanPortsInfo();
    loadSettings();
}

HwPorts::~HwPorts()
{
    delete ui;
}



// QList<QLabel> labelList;




void HwPorts::initUI()
{
    /*
    for (int row = 0 ; row < NumGridRows; row++){

        for (int col = 0 ; col < NumGridCol ; col++){
            labels[row][col] = new QLabel(tr("Line %1:").arg(row + 1));
            ui->gridLayout_Tabel->addWidget(labels[row][col], row + 1, col);
            ui->gridLayout_Tabel->setColumnStretch(col,1);
        }
    }
ui->gridLayout_Tabel->setColumnStretch(NumGridCol,1);

    labels[0][0]->setText("Device Name");
    labels[0][1]->setText("Port Name");
    labels[0][2]->setText("Description");
    labels[0][3]->setText("Manufacturer");
    labels[0][4]->setText("Serial number");
    labels[0][5]->setText("Vendor Id");
    labels[0][6]->setText("Product Id");
    labels[0][7]->setText("Status");


     for (int row = 0+1 ; row < NumGridRows; row++){
         comboBox[row] = new QComboBox();
         ui->gridLayout_Tabel->addWidget(comboBox[row], row + 1, NumGridCol);
     }

     QFrame *linea1 = new QFrame(this);
     linea1->setLineWidth(2);
     linea1->setMidLineWidth(1);
     linea1->setFrameShape(QFrame::HLine);
     linea1->setFrameShadow(QFrame::Raised);

     ui->gridLayout_Tabel->addWidget(linea1, 3, 4, 0, 4);


*/

}

void HwPorts::scanPortsInfo()
{
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    const QString blankString = QObject::tr("N/A");
    QString description;
    QString manufacturer;
    QString serialNumber;
    comPortMap.clear();

    QString str = "Available com port: \n";
    ui->textEditInfo->append(str);
    int portCnt = 0;

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

        comPortMap.insert(QString::number(portCnt),comInfo);
        portCnt++;

        str = "";
        str.append(QObject::tr("Port: ") + serialPortInfo.portName() + "\n");
        str.append(QObject::tr("Location: ") + serialPortInfo.systemLocation() + "\n");
        str.append(QObject::tr("Description: ") + (!description.isEmpty() ? description : blankString) + "\n");
        str.append(QObject::tr("Manufacturer: ") + (!manufacturer.isEmpty() ? manufacturer : blankString) + "\n");
        str.append(QObject::tr("Serial number: ") + (!serialNumber.isEmpty() ? serialNumber : blankString) + "\n");
        str.append(QObject::tr("Vendor Identifier: ") + (serialPortInfo.hasVendorIdentifier() ? QByteArray::number(serialPortInfo.vendorIdentifier(), 16) : blankString) + "\n");
        str.append(QObject::tr("Product Identifier: ") + (serialPortInfo.hasProductIdentifier() ? QByteArray::number(serialPortInfo.productIdentifier(), 16) : blankString) + "\n\n");

        cmbList << str;

        ui->comboBox_R1->clear();
        ui->comboBox_R2->clear();
        ui->comboBox_R3->clear();
        ui->comboBox_R4->clear();

        ui->comboBox_R1->addItems(cmbList);
        ui->comboBox_R2->addItems(cmbList);
        ui->comboBox_R3->addItems(cmbList);
        ui->comboBox_R4->addItems(cmbList);

        qDebug() << str;
        ui->textEditInfo->append(str);
    }  
}

void HwPorts::clearDisplay()
{

}

bool HwPorts::autoScanComPorts()
{
    int result = 0;
    qDebug()<< "Vendor Id:"<< global.dev1_VendorId<< global.dev2_VendorId<< global.dev3_VendorId<< global.dev4_VendorId;

    foreach (ComInfo cmap, comPortMap) {
        qDebug()<< cmap.vendorIdentifier ;
        }

    foreach (ComInfo cmap, comPortMap) {
        if(cmap.vendorIdentifier == global.dev1_VendorId){
            global.dev1 = cmap.port;
            result |= 0x01;
        }

        if(cmap.vendorIdentifier == global.dev2_VendorId){
            global.dev2 = cmap.port;
            result |= 0x02;
        }

        if(cmap.vendorIdentifier == global.dev3_VendorId){
            global.dev3 = cmap.port;
            result |= 0x04;
        }

        if(cmap.vendorIdentifier == global.dev4_VendorId){
            global.dev4 = cmap.port;
            result |= 0x08;
        }
    }

    return(result == 0x0F);
}

void HwPorts::updateUI()
{

    if(!global.dev1.isNull()){
       ui->label_R1_port->setText(global.dev1);
       ui->label_R1_vend->setText(global.dev1_VendorId);
    }

    if(!global.dev2.isNull()){
        ui->label_R2_port->setText(global.dev2);
        ui->label_R2_vend->setText(global.dev2_VendorId);
    }
    if(!global.dev3.isNull()){
        ui->label_R3_port->setText(global.dev3);
        ui->label_R3_vend->setText(global.dev3_VendorId);
    }

    if(!global.dev4.isNull()){
        ui->label_R4_port->setText(global.dev4);
        ui->label_R4_vend->setText(global.dev4_VendorId);
    }

}

void HwPorts::loadSettings()
{

    QString settingsFile = global.settingsFileName;
    QSettings settings(settingsFile, QSettings::IniFormat);
/*
    global.dev1_VendorId = settings.value("Port_Settings/device_1_Id", "na").toString();
    global.dev2_VendorId = settings.value("Port_Settings/device_2_Id", "na").toString();
    global.dev3_VendorId = settings.value("Port_Settings/device_3_Id", "na").toString();
    global.dev4_VendorId = settings.value("Port_Settings/device_4_Id", "na").toString();
   */

    global.dev1_VendorId = settings.value("Device_1/Vendor_Id", "na").toString();
    global.dev2_VendorId = settings.value("Device_2/Vendor_Id", "na").toString();
    global.dev3_VendorId = settings.value("Device_3/Vendor_Id", "na").toString();
    global.dev4_VendorId = settings.value("Device_4/Vendor_Id", "na").toString();


    qDebug()<< "loadSettings() Vendor Id:"<< global.dev1_VendorId<< global.dev2_VendorId<< global.dev3_VendorId<< global.dev4_VendorId;
}

    void HwPorts::on_pushButton_Save_clicked()
    {
        QString settingsFile = global.settingsFileName;
        QSettings settings(settingsFile, QSettings::IniFormat);
        QString sText = settingsFile;

        settings.beginGroup("Device_1");
        settings.setValue("port_Nr", global.dev1);
        settings.setValue("Vendor_Id", global.dev1_VendorId);
        settings.endGroup();


        settings.beginGroup("Device_2");
        settings.setValue("port_Nr", global.dev2);
        settings.setValue("Vendor_Id", global.dev2_VendorId);
        settings.endGroup();

        settings.beginGroup("Device_3");
        settings.setValue("port_Nr", global.dev3);
        settings.setValue("Vendor_Id", global.dev3_VendorId);
        settings.endGroup();

        settings.beginGroup("Device_4");
        settings.setValue("port_Nr", global.dev4);
        settings.setValue("Vendor_Id", global.dev4_VendorId);
        settings.endGroup();


/*
        settings.beginGroup("Port_Settings");
        settings.setValue("device_1", global.dev1);
        settings.setValue("device_2", global.dev2);
        settings.setValue("device_3", global.dev3);
        settings.setValue("device_4", global.dev4);

        settings.setValue("device_1_Id", global.dev1_VendorId);
        settings.setValue("device_2_Id", global.dev2_VendorId);
        settings.setValue("device_3_Id", global.dev3_VendorId);
        settings.setValue("device_4_Id", global.dev4_VendorId);

        settings.endGroup();

*/
        ui->textEditInfo->append(tr("Com. portu iestatījumi saglabāti failā: %1").arg(settingsFile));
    }


    void HwPorts::on_pushButton_Update_clicked()
    {
        clearDisplay();
        scanPortsInfo();
    }


    void HwPorts::on_comboBox_R1_activated(int index)
    {
        qDebug() << "\nR1 index "<< index;
        QString ind = QString::number(index);

        ui->label_R1_port->setText(comPortMap[ind].port);
        ui->label_R1_desc->setText(comPortMap[ind].description);
        ui->label_R1_man->setText(comPortMap[ind].manufacturer);

        ui->label_R1_ser->setText(comPortMap[ind].serialNumber);
        ui->label_R1_vend->setText(comPortMap[ind].vendorIdentifier);
        ui->label_R1_pr_nr->setText(comPortMap[ind].productIdentifier);
        ui->label_R1_stat->setText("");
        global.dev1 = comPortMap[ind].port;
        global.dev1_VendorId = comPortMap[ind].vendorIdentifier;
    }


    void HwPorts::on_comboBox_R2_activated(int index)
    {
        qDebug() << "\nR2 index "<< index;
        QString ind = QString::number(index);

        ui->label_R2_port->setText(comPortMap[ind].port);
        ui->label_R2_desc->setText(comPortMap[ind].description);
        ui->label_R2_man->setText(comPortMap[ind].manufacturer);

        ui->label_R2_ser->setText(comPortMap[ind].serialNumber);
        ui->label_R2_vend->setText(comPortMap[ind].vendorIdentifier);
        ui->label_R2_pr_nr->setText(comPortMap[ind].productIdentifier);
        ui->label_R2_stat->setText("");
        global.dev2 = comPortMap[ind].port;
        global.dev2_VendorId = comPortMap[ind].vendorIdentifier;
    }


    void HwPorts::on_comboBox_R3_activated(int index)
    {
        qDebug() << "\nR3 index "<< index;
        QString ind = QString::number(index);

        ui->label_R3_port->setText(comPortMap[ind].port);
        ui->label_R3_desc->setText(comPortMap[ind].description);
        ui->label_R3_man->setText(comPortMap[ind].manufacturer);

        ui->label_R3_ser->setText(comPortMap[ind].serialNumber);
        ui->label_R3_vend->setText(comPortMap[ind].vendorIdentifier);
        ui->label_R3_pr_nr->setText(comPortMap[ind].productIdentifier);
        ui->label_R3_stat->setText("");
        global.dev3 = comPortMap[ind].port;
        global.dev3_VendorId = comPortMap[ind].vendorIdentifier;
    }


    void HwPorts::on_comboBox_R4_activated(int index)
    {
        qDebug() << "\nR2 index "<< index;
        QString ind = QString::number(index);

        ui->label_R4_port->setText(comPortMap[ind].port);
        ui->label_R4_desc->setText(comPortMap[ind].description);
        ui->label_R4_man->setText(comPortMap[ind].manufacturer);

        ui->label_R4_ser->setText(comPortMap[ind].serialNumber);
        ui->label_R4_vend->setText(comPortMap[ind].vendorIdentifier);
        ui->label_R4_pr_nr->setText(comPortMap[ind].productIdentifier);
        ui->label_R4_stat->setText("");
        global.dev4 = comPortMap[ind].port;
        global.dev4_VendorId = comPortMap[ind].vendorIdentifier;
    }

