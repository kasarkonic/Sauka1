#include "hwports.h"
#include "ui_hwports.h"
#include <QtSerialPort/QSerialPortInfo>


HwPorts::HwPorts(Global &global, QWidget *parent)
    : QMainWindow(parent)
    , global(global)
    , ui(new Ui::HwPorts)
{
    ui->setupUi(this);

    scanPortsInfo();
    comPortMap.size()
     initUI();
}

HwPorts::~HwPorts()
{
    delete ui;
}



// QList<QLabel> labelList;




void HwPorts::initUI()
{

    for (int row = 0 ; row < NumGridRows; row++){

        for (int col = 0 ; col < NumGridCol ; col++){
            labels[row][col] = new QLabel(tr("Line %1:").arg(row + 1));
            ui->gridLayout_Tabel->addWidget(labels[row][col], row + 1, col);
        }
    }

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


}

void HwPorts::scanPortsInfo()
{
   const auto serialPortInfos = QSerialPortInfo::availablePorts();
    const QString blankString = QObject::tr("N/A");
    QString description;
    QString manufacturer;
    QString serialNumber;

    QString str = "Available com port: \n";
    ui->textEditInfo->append(str);

    int row = 1;
    int col = 1;

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

        labels[row][0]->setText("Device name") ;
        labels[row][1]->setText(serialPortInfo.portName()) ;
        labels[row][2]->setText(!description.isEmpty() ? description : blankString) ;            //("Name");
        labels[row][3]->setText (!manufacturer.isEmpty() ? manufacturer : blankString);            //("Vendor");
        labels[row][4]->setText(!serialNumber.isEmpty() ? serialNumber : blankString) ;            //("Vendor id");
        labels[row][5]->setText (serialPortInfo.hasVendorIdentifier() ? QByteArray::number(serialPortInfo.vendorIdentifier(), 16) : blankString) ;           //("Com no");
        labels[row][6]->setText  (serialPortInfo.hasProductIdentifier() ? QByteArray::number(serialPortInfo.productIdentifier(), 16) : blankString);           //("Note");
        labels[row][7]->setText("Status??");
        row++;


        qDebug() << str;
        ui->textEditInfo->append(str);


    }



}

void HwPorts::clearDisplay()
{
    for (int row = 0+1 ; row < NumGridRows; row++){

        for (int col = 0 ; col < NumGridCol ; col++){
            labels[row][col]->setText("");
        }
    }
    for (int i = 0 ; i < NumGridRows; i++){
        comboBox[i]->removeItem(1);

    }

}


void HwPorts::on_pushButton_Save_clicked()
{

}


void HwPorts::on_pushButton_Update_clicked()
{

    clearDisplay();
     scanPortsInfo();
}

