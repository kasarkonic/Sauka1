#include "recipet.h"
#include "ui_recipet.h"
#include <QDir>
#include <QMessageBox>
#include <QSettings>

Recipet::Recipet(Global &global,QWidget *parent)
   : QWidget(parent, Qt::Window)
   , ui(new Ui::Recipet)
   , global(global)
{
    ui->setupUi(this);

    cmbList.clear();
    cmbList << "Process no 1." << "Process no 2." << "Process no 3." ;
    ui->comboBox_8_ingr->addItems(cmbList);
    ui->comboBox_9_ingr->addItems(cmbList);
    ui->comboBox_10_ingr->addItems(cmbList);
   updateCardFileName();
}

Recipet::~Recipet()
{
    delete ui;
}

void Recipet::on_pushButton_delet_clicked()
{

}


void Recipet::on_pushButton_clear_clicked(bool checked)
{

}


void Recipet::on_pushButton_save_clicked()
{

    recName = ui->lineEdit_Rec_name->text();
    if(ui->lineEdit_Rec_name){

        QDateTime date = QDateTime::currentDateTime();
        QString currentTime = "Recepte izveidota ";
        currentTime.append(date.toString("dd.MM.yyyy hh:mm:ss"));
        currentTime.append("\n");

        QString notesTXT = ui->textEdit_notes->toPlainText();
        notesTXT = currentTime.append(notesTXT);

        QString settingsFile = itemTofileNameR(recName);
        qDebug() << "settingsFile" << settingsFile;
        QSettings settings(settingsFile, QSettings::IniFormat);

        settings.setValue("Receptes_nosaukums", recName);

        settings.setValue("1.komponente", ui->comboBox_1_ingr->currentText());
 ////////       int ui->lineEdit_1_ingr_val->text()
 ///////       settings.setValue("1.komponente_val", QString::number(ui->lineEdit_1_ingr_val->text()));



    }
    else{
        ui->label_notes->setText("Lūdzu ievadiet Receptes nosaukumu !");
    }
}


void Recipet::on_pushButton_exit_clicked()
{

}


void Recipet::on_comboBox_reciep_highlighted(int index)
{

}


void Recipet::on_comboBox_reciep_currentIndexChanged(int index)
{

}

QString Recipet::fileNameToItem(QString fname)
{
    int len = fname.length();
   // QString str = "";

    if(len > 5){
        fname.resize(len - 4);
    }
    if(fname.length() > 3){
        fname.remove(0,2);
    }
    qDebug() << "fileNameToItem:  " << fname;
    return fname;
}

QString Recipet::itemTofileName(QString item)
{
    QString fName = QApplication::applicationDirPath() + "/receptes/kartinas/k_";
    fName.append(item);
    fName.append(".ini");
    qDebug() << "fName: " << fName;
    return fName;
}

QString Recipet::fileNameToItemR(QString fname)
{
    int len = fname.length();
   // QString str = "";

    if(len > 5){
        fname.resize(len - 4);
    }
    if(fname.length() > 3){
        fname.remove(0,2);
    }
    qDebug() << "RfileNameToItem:  " << fname;
    return fname;
}

QString Recipet::itemTofileNameR(QString item)
{
    QString fName = QApplication::applicationDirPath() + "/receptes/kartinas/r_";
    fName.append(item);
    fName.append(".ini");
    qDebug() << "RfName: " << fName;
    return fName;
}

void Recipet::updateCardFileName()
{

    qDebug() << "updateCardFileName " ;
    QString strDir =  QApplication::applicationDirPath() + "/receptes/kartinas";
    QDir directory(strDir);

    cardFileName = directory.entryList(QStringList() << "*.ini",QDir::Files);

    qDebug() << "files :: "   << cardFileName;

    ui->comboBox_1_ingr->clear();
    ui->comboBox_2_ingr->clear();
    ui->comboBox_3_ingr->clear();
    ui->comboBox_4_ingr->clear();
    ui->comboBox_5_ingr->clear();
    ui->comboBox_6_ingr->clear();
    ui->comboBox_7_ingr->clear();

    cmbList.clear();

    qDebug() << "-----------------------";
    int i = 0;
    foreach(QString filename, cardFileName) {

        //qDebug()<< "filename.resize(2) == " << filename[0] << filename[1];
      if(filename[0] == 'k' && filename[1] == '_' ){
        cmbList.append(fileNameToItem(filename));
        qDebug() << "filename " << filename << cmbList[i];
        i++;
      }

    }

    qDebug()<< "cmbList len = "<<  cmbList.length() << "   " << cmbList;
    if(cmbList.length()){
        ui->comboBox_1_ingr->addItems(cmbList);
        ui->comboBox_2_ingr->addItems(cmbList);
        ui->comboBox_3_ingr->addItems(cmbList);
        ui->comboBox_4_ingr->addItems(cmbList);
        ui->comboBox_5_ingr->addItems(cmbList);
        ui->comboBox_6_ingr->addItems(cmbList);
        ui->comboBox_7_ingr->addItems(cmbList);

    }

}

