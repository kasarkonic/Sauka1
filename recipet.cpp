#include "recipet.h"
#include "ui_recipet.h"
#include <QDir>
#include <QMessageBox>
#include <QSettings>
#include "componentcard.h"
#include <QMessageBox>

Recipet::Recipet(Global &global,QWidget *parent)
   : QWidget(parent, Qt::Window)
   , ui(new Ui::Recipet)
   , global(global)
{
    ui->setupUi(this);

    pcmbList.clear();
    pcmbList << "Process no 1." << "Process no 2." << "Process no 3." ;
    ui->comboBox_8_ingr->addItems(pcmbList);
    ui->comboBox_9_ingr->addItems(pcmbList);
    ui->comboBox_10_ingr->addItems(pcmbList);
    updateCardFileName();
    updateRecFileName();
   // clearFilds();
    calculateSumm();

}

Recipet::~Recipet()
{
    delete ui;
}
/*
bool Recipet::event(QEvent *e)
{
    Q_UNUSED(e)
    qDebug() <<  "-------Recipet::event-------------" << e->type();
    if(e->type() == QEvent::Leave){
    }
}
*/
void Recipet::on_pushButton_delet_clicked()
{
    QString text = "  Vai tiešām vēlaties\nneatgriezeniski dzēst\n        recepti ?";
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, " ", text, QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes){
        qDebug() << " del file: " << recName;

        QString str = "Nodzēsta recepte " + recName;
        ui->label_notes->setText(str);

        QString settingsFile = itemTofileNameR(recName);
        qDebug() << "settingsFile" << settingsFile;

        QDir dir(settingsFile);
        dir.remove(settingsFile);

        // ui->comboBox_loadCard->removeItem(cmbListIndex);

        updateRecFileName();
    }
}


void Recipet::on_pushButton_clear_clicked(bool checked)
{
    clearFilds();
    updateRecdData();
}


void Recipet::on_pushButton_save_clicked()
{

    recName = ui->lineEdit_Rec_name->text();
    if(recName.length() >0){

        QDateTime date = QDateTime::currentDateTime();
        QString currentTime = "Recepte izveidota ";
        currentTime.append(date.toString("dd.MM.yyyy hh:mm:ss"));
        currentTime.append("\n");

        notesTXT = ui->textEdit_notes->toPlainText();
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
    close();
}


void Recipet::on_comboBox_reciep_highlighted(int index)
{
    on_comboBox_reciep_currentIndexChanged(index);
}


void Recipet::on_comboBox_reciep_currentIndexChanged(int index)
{
     qDebug() << "updateRecdData(rcardFileName[index])" << index ;
    if(index >=0 ){


   QString str;
   QStringList strlist;

   QString rName = rcmbList[index];

   QString kfName = itemTofileNameR(rName);

   bool ok ;

   qDebug() << "kfName: " << rName << kfName;

   //qDebug() << "update settingsFile" << fname;
   QSettings settings(kfName, QSettings::IniFormat);

   recName = settings.value("Receptes_nosaukums", "???").toString();
   qDebug() << "recName:" << recName;

   ui->lineEdit_Rec_name->setText(recName);
//
   ingr1 = settings.value("1.komponente","").toString();
   ingr1_vol = settings.value("1.komponente_vol","").toInt(&ok);
    if(!ok){
       str = QString("Kļūda 1. ingradientam daudzumam: \" %1 \" nav komponentes kartiņas !!!").arg(ingr1_vol);
       ui->label_notes->setText(str);
       ingr1_vol = 0;
    }
    //
    ingr2 = settings.value("2.komponente","").toString();
    ingr2_vol = settings.value("2.komponente_vol","").toInt(&ok);
    if(!ok){
        str = QString("Kļūda 2. ingradientam daudzumam: \" %1 \" nav komponentes kartiņas !!!").arg(ingr2_vol);
        ui->label_notes->setText(str);
        ingr2_vol = 0;
    }

    //
    ingr3 = settings.value("3.komponente","").toString();
    ingr3_vol = settings.value("3.komponente_vol","").toInt(&ok);
    if(!ok){
        str = QString("Kļūda 3. ingradientam daudzumam: \" %1 \" nav komponentes kartiņas !!!").arg(ingr3_vol);
        ui->label_notes->setText(str);
        ingr3_vol = 0;
    }

    //
    ingr4 = settings.value("4.komponente","").toString();
    ingr4_vol = settings.value("4.komponente_vol","").toInt(&ok);
    if(!ok){
        str = QString("Kļūda 4. ingradientam daudzumam: \" %1 \" nav komponentes kartiņas !!!").arg(ingr4_vol);
        ui->label_notes->setText(str);
        ingr4_vol = 0;
    }

    //
    ingr5 = settings.value("5.komponente","").toString();
    ingr5_vol = settings.value("5.komponente_vol","").toInt(&ok);
    if(!ok){
        str = QString("Kļūda 5. ingradientam daudzumam: \" %1 \" nav komponentes kartiņas !!!").arg(ingr5_vol);
        ui->label_notes->setText(str);
        ingr5_vol = 0;
    }

    //
    ingr6 = settings.value("6.komponente","").toString();
    ingr6_vol = settings.value("6.komponente_vol","").toInt(&ok);
    if(!ok){
        str = QString("Kļūda 6. ingradientam daudzumam: \" %1 \" nav komponentes kartiņas !!!").arg(ingr6_vol);
        ui->label_notes->setText(str);
        ingr6_vol = 0;
    }

    //
    ingr7 = settings.value("7.komponente","").toString();
    ingr7_vol = settings.value("7.komponente_vol","").toInt(&ok);
    if(!ok){
        str = QString("Kļūda 7. ingradientam daudzumam: \" %1 \" nav komponentes kartiņas !!!").arg(ingr7_vol);
        ui->label_notes->setText(str);
        ingr7_vol = 0;
    }

    //
    process1 = settings.value("1.process","").toString();
    process1_vol = settings.value("1.process_vol","").toInt(&ok);
    if(!ok){
        str = QString("Kļūda 8. procesa parametrā: \" %1 \" nav komponentes kartiņas !!!").arg(process1_vol);
        ui->label_notes->setText(str);
        process1_vol = 0;
    }

    //
    process2 = settings.value("2.process","").toString();
    process2_vol = settings.value("1.process_vol","").toInt(&ok);
    if(!ok){
        str = QString("Kļūda 1. procesa parametrā: \" %1 \" nav komponentes kartiņas !!!").arg(process2_vol);
        ui->label_notes->setText(str);
        process2_vol = 0;
    }

    //
    process3 = settings.value("3.process","").toString();
    process3_vol = settings.value("1.process_vol","").toInt(&ok);
    if(!ok){
        str = QString("Kļūda 1. procesa parametrā: \" %1 \" nav komponentes kartiņas !!!").arg(process3_vol);
        ui->label_notes->setText(str);
        process3_vol = 0;
    }

   notesTXT = settings.value("3.process","").toString();

   updateRecdData();


    }


}

QString Recipet::fileNameToItem(QString fname)
{
    int len = fname.length();

    if(len > 5){
        fname.resize(len - 4);
    }
    if(fname.length() >= 3){
        fname.remove(0,2);
    }
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
    if(len > 5){
        fname.resize(len - 4);
    }
    if(fname.length() >= 3){
       fname.remove(0,2);
    }

    qDebug() << "RfileNameToItem: res  " << fname << fname.length();
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

        qDebug()<< "filename " << i <<filename;
        if(filename.length() >= 7){
           if(filename[0] == 'r' && filename[1] == '_' ){
                QString str  = fileNameToItemR(filename);
                rcmbList.append({str});
                qDebug() << "rfilename " << rcmbList.length() << filename << rcmbList[i];
                i++;
            }
        }
    }

    qDebug()<< "rcmbList len = "<<  rcmbList.length() << "   " << rcmbList;
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
    notesTXT.clear();
    recName = rcmbList[0];

    ingr1 = cmbList[0];
    ingr2 = cmbList[0];
    ingr3 = cmbList[0];
    ingr4 = cmbList[0];
    ingr5 = cmbList[0];
    ingr6 = cmbList[0];
    ingr7 = cmbList[0];
    process1 = pcmbList[0];
    process2 = pcmbList[0];
    process3 = pcmbList[0];
    calculateSumm();

}

void Recipet::calculateSumm()
{
    int sum = ingr1_vol + ingr2_vol + ingr3_vol + ingr4_vol + ingr5_vol + ingr6_vol + ingr7_vol;
    ui->label_sum->setText(QString::number(sum) + "    kg/T");
    if(sum > 1000){
        ui->label_sum->setStyleSheet("QLabel { background-color : red; color : black; }");
    }
    else{
         ui->label_sum->setStyleSheet("QLabel { background-color : white; color : black; }");
    }
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
    calculateSumm();
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
    calculateSumm();
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
    calculateSumm();
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
    calculateSumm();
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
    calculateSumm();
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
    calculateSumm();
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
    calculateSumm();
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



        ui->lineEdit_Rec_name->setText(recName);

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

void Recipet::updateRecdData()
{
    QString str;
    int index;
    ui->lineEdit_Rec_name->setText(recName);
//
    index = cmbList.indexOf(ingr1);
    if(index >= 0){
        ui->comboBox_1_ingr->setCurrentIndex(index);
    }
    else{
        str = QString("1 ingradientam: \" %1 \" nav komponentes kartiņas !!!").arg(ingr1);
        ui->label_notes->setText(str);
    }
    ui->lineEdit_1_ingr_val->setText(QString::number(ingr1_vol));
 //
    index = cmbList.indexOf(ingr2);
    if(index >= 0){
        ui->comboBox_2_ingr->setCurrentIndex(index);
    }
    else{
        str = QString("2 ingradientam: \" %1 \" nav komponentes kartiņas !!!").arg(ingr2);
        ui->label_notes->setText(str);
    }
    ui->lineEdit_2_ingr_val->setText(QString::number(ingr2_vol));
//
    index = cmbList.indexOf(ingr3);
    if(index >= 0){
        ui->comboBox_3_ingr->setCurrentIndex(index);
    }
    else{
        str = QString("3 ingradientam: \" %1 \" nav komponentes kartiņas !!!").arg(ingr3);
        ui->label_notes->setText(str);
    }
    ui->lineEdit_3_ingr_val->setText(QString::number(ingr3_vol));
    //
    index = cmbList.indexOf(ingr4);
    if(index >= 0){
        ui->comboBox_4_ingr->setCurrentIndex(index);
    }
    else{
        str = QString("4 ingradientam: \" %1 \" nav komponentes kartiņas !!!").arg(ingr4);
        ui->label_notes->setText(str);
    }
    ui->lineEdit_4_ingr_val->setText(QString::number(ingr4_vol));
    //
    index = cmbList.indexOf(ingr5);
    if(index >= 0){
        ui->comboBox_5_ingr->setCurrentIndex(index);
    }
    else{
        str = QString("5 ingradientam: \" %1 \" nav komponentes kartiņas !!!").arg(ingr5);
        ui->label_notes->setText(str);
    }
    ui->lineEdit_5_ingr_val->setText(QString::number(ingr5_vol));
    //
    index = cmbList.indexOf(ingr6);
    if(index >= 0){
        ui->comboBox_6_ingr->setCurrentIndex(index);
    }
    else{
        str = QString("6 ingradientam: \" %1 \" nav komponentes kartiņas !!!").arg(ingr6);
        ui->label_notes->setText(str);
    }
    ui->lineEdit_6_ingr_val->setText(QString::number(ingr7_vol));
    //
    index = cmbList.indexOf(ingr7);
    if(index >= 0){
        ui->comboBox_7_ingr->setCurrentIndex(index);
    }
    else{
        str = QString("7 ingradientam: \" %1 \" nav komponentes kartiņas !!!").arg(ingr7);
        ui->label_notes->setText(str);
    }
    ui->lineEdit_7_ingr_val->setText(QString::number(ingr7_vol));
    //
    index = pcmbList.indexOf(process1);
    if(index >= 0){
        ui->comboBox_8_ingr->setCurrentIndex(index);
    }
    else{
        str = QString("1 procesam: \" %1 \" nav komponentes kartiņas !!!").arg(process1);
        ui->label_notes->setText(str);
    }
    ui->lineEdit_8_ingr_val->setText(QString::number(process1_vol));

    //
    index = pcmbList.indexOf(process2);
    if(index >= 0){
        ui->comboBox_9_ingr->setCurrentIndex(index);
    }
    else{
        str = QString("2 procesam: \" %1 \" nav komponentes kartiņas !!!").arg(process2);
        ui->label_notes->setText(str);
    }
    ui->lineEdit_9_ingr_val->setText(QString::number(process2_vol));

    //
    index = pcmbList.indexOf(process3);
    if(index >= 0){
        ui->comboBox_10_ingr->setCurrentIndex(index);
    }
    else{
        str = QString("3 procesam: \" %1 \" nav komponentes kartiņas !!!").arg(process3);
        ui->label_notes->setText(str);
    }
    ui->lineEdit_10_ingr_val->setText(QString::number(process3_vol));

    ui->textEdit_notes->setText(notesTXT);
    calculateSumm();
}


void Recipet::on_pushButton_components_Card_clicked(bool checked)
{
    ComponentCard *componentCard = new ComponentCard(global,this);
    componentCard->show();
}

