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
    clearFilds();
    updateCardFileName();
    updateRecFileName();

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
    if(recName.length() >0){

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
        settings.setValue("1.komponente_vol", QString::number(ingr1_vol));

        settings.setValue("2.komponente", ui->comboBox_2_ingr->currentText());
        settings.setValue("2.komponente_vol", QString::number(ingr2_vol));

        settings.setValue("3.komponente", ui->comboBox_3_ingr->currentText());
        settings.setValue("3.komponente_vol", QString::number(ingr3_vol));

        settings.setValue("4.komponente", ui->comboBox_4_ingr->currentText());
        settings.setValue("4.komponente_vol", QString::number(ingr4_vol));

        settings.setValue("5.komponente", ui->comboBox_5_ingr->currentText());
        settings.setValue("5.komponente_vol", QString::number(ingr5_vol));

        settings.setValue("6.komponente", ui->comboBox_6_ingr->currentText());
        settings.setValue("6.komponente_vol", QString::number(ingr6_vol));

        settings.setValue("7.komponente", ui->comboBox_7_ingr->currentText());
        settings.setValue("7.komponente_vol", QString::number(ingr7_vol));

        settings.setValue("1.process", ui->comboBox_8_ingr->currentText());
        settings.setValue("1.process_vol", QString::number(process1_vol));

        settings.setValue("2.process", ui->comboBox_9_ingr->currentText());
        settings.setValue("2.process_vol", QString::number(process2_vol));

        settings.setValue("3.process", ui->comboBox_10_ingr->currentText());
        settings.setValue("3.process_vol", QString::number(process3_vol));

        settings.setValue("Piezimes", notesTXT);
        settings.sync();

        QString str = "Recepte saglabāta failā:  " + settingsFile;
        ui->label_notes->setText(str);
        updateRecFileName();


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
    //updateRecdData(rcardFileName[index]);
}


void Recipet::on_comboBox_reciep_currentIndexChanged(int index)
{

    qDebug() << "updateRecdData(rcardFileName[index])" << index << rcardFileName[index];
     //       updateRecdData(rcardFileName[index]);


}

QString Recipet::fileNameToItem(QString fname)
{
    int len = fname.length();
   // QString str = "";

    if(len > 5){
        fname.resize(len - 4);
    }
    if(fname.length() >= 3){
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
    if(fname.length() >= 3){
        fname.remove(0,2);
    }
    qDebug() << "RfileNameToItem:  " << fname << fname.length();
    return fname;
}

QString Recipet::itemTofileNameR(QString item)
{
    QString fName = QApplication::applicationDirPath() + "/receptes/r_";
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

    qDebug() << "-----------------------" << cardFileName;
    int i = 0;

    foreach(QString filename, cardFileName) {

        //qDebug()<< "filename.resize(2) == " << filename[0] << filename[1];
      if(filename[0] == 'k' && filename[1] == '_' ){
        cmbList.append(fileNameToItem(filename));
        qDebug() << "filename " << cmbList.length() << filename << cmbList[i];
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

void Recipet::updateRecFileName()
{

    qDebug() << "updateRecFileName " ;
    QString strDir =  QApplication::applicationDirPath() + "/receptes";
    QDir directory(strDir);

    rcardFileName = directory.entryList(QStringList() << "*.ini",QDir::Files);


    ui->comboBox_reciep->clear();
    rcmbList.clear();

    qDebug() << "-----------------------" << rcardFileName;
    int i = 0;

    foreach(QString filename, rcardFileName) {

        //qDebug()<< "filename.resize(2) == " << filename[0] << filename[1];
        qDebug() << "rfilename " << rcmbList.length() << filename << rcmbList[i];
        if(filename[0] == 'r' && filename[1] == '_' ){
            rcmbList.append(fileNameToItemR(filename));
            i++;
        }
    }

    qDebug()<< "cmbList len = "<<  rcmbList.length() << "   " << rcmbList;
    if(rcmbList.length()){
        ui->comboBox_reciep->addItems(rcmbList);
    }


}

void Recipet::clearFilds()
{
    ingr1_vol = 0;
    ingr2_vol = 0;
    ingr3_vol = 0;
    ingr4_vol = 0;
    ingr5_vol = 0;
    ingr6_vol = 0;
    ingr7_vol = 0;
    process1_vol = 0;
    process2_vol = 0;
    process3_vol = 0;
}


void Recipet::on_lineEdit_1_ingr_val_editingFinished()
{
    int val = ui->lineEdit_1_ingr_val->text().toInt(&ok);
    if(ok){
        ingr1_vol = val;
    }
    else{
        ui->lineEdit_1_ingr_val->setText("kļūda ievadot");
    }
    qDebug() << "ingr1_vol: " << ingr1_vol;
}


void Recipet::on_lineEdit_2_ingr_val_editingFinished()
{
    int val = ui->lineEdit_2_ingr_val->text().toInt(&ok);
    if(ok){
        ingr2_vol = val;
    }
    else{
        ui->lineEdit_2_ingr_val->setText("kļūda ievadot");
    }
    qDebug() << "ingr2_vol: " << ingr2_vol;
}


void Recipet::on_lineEdit_3_ingr_val_editingFinished()
{
    int val = ui->lineEdit_3_ingr_val->text().toInt(&ok);
    if(ok){
        ingr3_vol = val;
    }
    else{
        ui->lineEdit_3_ingr_val->setText("kļūda ievadot");
    }
    qDebug() << "ingr3_vol: " << ingr3_vol;
}


void Recipet::on_lineEdit_4_ingr_val_editingFinished()
{
    int val = ui->lineEdit_4_ingr_val->text().toInt(&ok);
    if(ok){
        ingr4_vol = val;
    }
    else{
        ui->lineEdit_4_ingr_val->setText("kļūda ievadot");
    }
    qDebug() << "ingr4_vol: " << ingr4_vol;
}


void Recipet::on_lineEdit_5_ingr_val_editingFinished()
{
    int val = ui->lineEdit_5_ingr_val->text().toInt(&ok);
    if(ok){
        ingr5_vol = val;
    }
    else{
        ui->lineEdit_5_ingr_val->setText("kļūda ievadot");
    }
    qDebug() << "ingr5_vol: " << ingr5_vol;
}


void Recipet::on_lineEdit_6_ingr_val_editingFinished()
{
    int val = ui->lineEdit_6_ingr_val->text().toInt(&ok);
    if(ok){
        ingr6_vol = val;
    }
    else{
        ui->lineEdit_6_ingr_val->setText("kļūda ievadot");
    }
    qDebug() << "ingr6_vol: " << ingr6_vol;
}


void Recipet::on_lineEdit_7_ingr_val_editingFinished()
{
    int val = ui->lineEdit_7_ingr_val->text().toInt(&ok);
    if(ok){
        ingr7_vol = val;
    }
    else{
        ui->lineEdit_7_ingr_val->setText("kļūda ievadot");
    }
    qDebug() << "ingr7_vol: " << ingr7_vol;
}


void Recipet::on_lineEdit_8_ingr_val_editingFinished()
{
    int val = ui->lineEdit_8_ingr_val->text().toInt(&ok);
    if(ok){
        process1_vol = val;
    }
    else{
        ui->lineEdit_8_ingr_val->setText("kļūda ievadot");
    }
    qDebug() << "process1_vol: " << process1_vol;
}


void Recipet::on_lineEdit_9_ingr_val_editingFinished()
{
    int val = ui->lineEdit_9_ingr_val->text().toInt(&ok);
    if(ok){
        process2_vol = val;
    }
    else{
        ui->lineEdit_9_ingr_val->setText("kļūda ievadot");
    }
    qDebug() << "process2_vol: " << process2_vol;
}


void Recipet::on_lineEdit_10_ingr_val_editingFinished()
{
    int val = ui->lineEdit_10_ingr_val->text().toInt(&ok);
    if(ok){
        process3_vol = val;
    }
    else{
        ui->lineEdit_10_ingr_val->setText("kļūda ievadot");
    }
    qDebug() << "process3_vol: " << process3_vol;
}

void Recipet::updateUI()
{

    /*




        QString notesTXT = ui->textEdit_notes->toPlainText();
        notesTXT = currentTime.append(notesTXT);

        QString settingsFile = itemTofileNameR(recName);
        qDebug() << "settingsFile" << settingsFile;
        QSettings settings(settingsFile, QSettings::IniFormat);



        settings.setValue("1.komponente", ui->comboBox_1_ingr->currentText());
        settings.setValue("1.komponente_vol", QString::number(ingr1_vol));

        settings.setValue("2.komponente", ui->comboBox_2_ingr->currentText());
        settings.setValue("2.komponente_vol", QString::number(ingr2_vol));

        settings.setValue("3.komponente", ui->comboBox_3_ingr->currentText());
        settings.setValue("3.komponente_vol", QString::number(ingr3_vol));

        settings.setValue("4.komponente", ui->comboBox_4_ingr->currentText());
        settings.setValue("4.komponente_vol", QString::number(ingr4_vol));

        settings.setValue("5.komponente", ui->comboBox_5_ingr->currentText());
        settings.setValue("5.komponente_vol", QString::number(ingr5_vol));

        settings.setValue("6.komponente", ui->comboBox_6_ingr->currentText());
        settings.setValue("6.komponente_vol", QString::number(ingr6_vol));

        settings.setValue("7.komponente", ui->comboBox_7_ingr->currentText());
        settings.setValue("7.komponente_vol", QString::number(ingr7_vol));

        settings.setValue("1.process", ui->comboBox_8_ingr->currentText());
        settings.setValue("1.process_vol", QString::number(process1_vol));

        settings.setValue("2.process", ui->comboBox_9_ingr->currentText());
        settings.setValue("2.process_vol", QString::number(process2_vol));

        settings.setValue("3.process", ui->comboBox_10_ingr->currentText());
        settings.setValue("3.process_vol", QString::number(process3_vol));

        settings.setValue("Piezimes", notesTXT);
        settings.sync();

    */
}

void Recipet::updateRecdData(QString fname)
{
    QString str;
    QStringList strlist;
    qDebug() << "update settingsFile" << fname;
    QSettings settings(fname, QSettings::IniFormat);

    recName = settings.value("Komponentes_nosaukums", "").toString();
    ui->lineEdit_Rec_name->setText(recName);

    str = settings.value("1.komponente","").toString();

    int index = rcardFileName.indexOf(str);
    qDebug() << "index" << index << str << "<|||||||>" << rcardFileName;
    if (index >= 0){

      //  ui->comboBox_1_ingr->setCurrentIndex(index);
    }

    else{

       // ui->comboBox_1_ingr->clear();
       // ui->comboBox_1_ingr->addItem("Ingradienta kartiņa nav atrasta !");
    }


  //  strlist = ui->comboBox_1_ingr->get

 //ui->comboBox_1_ingr->



    //settings.setValue("1.komponente", ui->comboBox_1_ingr->currentText());
   // settings.setValue("1.komponente_vol", QString::number(ingr1_vol));




}

