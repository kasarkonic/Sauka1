#include "componentcard.h"
#include "ui_componentcard.h"
#include <QSettings>
#include <QApplication>
#include <QDir>
#include <QMessageBox>
//#include <QComboBox>

ComponentCard::ComponentCard(Global &global,QWidget *parent)
    //: QMainWindow(parent)
    : QWidget(parent, Qt::Window)
    , ui(new Ui::ComponentCard)
    , global(global)

{
    //QPalette pal = QPalette();
    //pal.setColor(QPalette::Window,global.backgroundColor); //QColor(255, 0, 0, 127)
    //pal.setColor(QPalette::Window, QColor(242, 219, 238, 0.251));
   // this->setAutoFillBackground(true);
   // this->setPalette(pal);





    ui->setupUi(this);

    ui->lineEdit_moisture->setReadOnly(true);
    ui->lineEdit_dray->setReadOnly(true);
    ui->lineEdit_organic->setReadOnly(true);
    ui->lineEdit_humin->setReadOnly(true);
    ui->lineEdit_sarms->setReadOnly(true);
    ui->lineEdit_KO->setReadOnly(true);




    updateCardFileName();
    //cmbList = global.cardFileName;
    //cmbList << "Iestatijumi" << "Receptes" << "Atskaites" << "Serviss"  << "Par_mani";
   // ui->comboBox_loadCard->addItems(cmbList);
    ui->comboBox_loadCard->setCurrentIndex(0);


}

ComponentCard::~ComponentCard()
{
    delete ui;
}

void ComponentCard::on_lineEdit_comp_name_editingFinished()
{
cardName = ui->lineEdit_comp_name->text();
}



void ComponentCard::on_pushButton_edit_clicked()
{

}


void ComponentCard::on_pushButton_save_clicked()
{

    if(cardName.length() > 0){
        readAllUIFields();

        QDateTime date = QDateTime::currentDateTime();

        QString currentTime = "Kartiņa izveidota ";
        currentTime.append(date.toString("dd.MM.yyyy hh:mm:ss"));
        currentTime.append("\n");

        notesTXT = currentTime.append(notesTXT);

        settingsFile = itemTofileName(cardName);
       // settingsFile = QApplication::applicationDirPath() + "/receptes/kartinas/k_" + cardName + ".ini";
        qDebug() << "settingsFile" << settingsFile;
        QSettings settings(settingsFile, QSettings::IniFormat);

        settings.setValue("Komponentes_nosaukums", cardName);

        settings.setValue("Mitrums", QString::number(moistureVal));
        settings.setValue("Sausne", QString::number(drayVal));
        settings.setValue("Organiskas_vielas", QString::number(organicVal));
        settings.setValue("Humini", QString::number(huminVal));
        settings.setValue("Sarms", QString::number(sarmsVal));
        settings.setValue("K2O", QString::number(KOVal));

        settings.setValue("param_7", param7);
        settings.setValue("parametrs_7", QString::number(param7Val));

        settings.setValue("param_8", param8);
        settings.setValue("parametrs_8", QString::number(param8Val));

        settings.setValue("param_9", param9);
        settings.setValue("parametrs_9", QString::number(param9Val));

        settings.setValue("param_10", param10);
        settings.setValue("parametrs_10", QString::number(param10Val));

        settings.setValue("Piezimes", notesTXT);
        settings.sync();
        QString str = "Kartiņa saglabāta failā:  " + settingsFile;

        ui->label_info->setText(str);
        updateCardFileName();
    }
    else{
        ui->label_info->setText("Lūdzu ievadiet komponentes nosaukumu !");
    }
}


void ComponentCard::on_pushButton_clear_clicked()
{
    ok = false;
    //cardName = "";
    moisture = "Mitrums";
    moistureVal = 0;
    dray = "Sausna";
    drayVal = 0;
    organic = "Organiska viela";
    organicVal = 0;
    humin = "Humīnskābes";
    huminVal = 0;
    sarms = "Sārms";
    sarmsVal = 0;
    KO = "Kālija Oksīds";
    KOVal = 0;
    param7 = "7. parametrs";
    param7Val = 0;
    param8 = "8. parametrs";
    param8Val = 0;
    param9 = "9. parametrs";
    param9Val = 0;
    param10 = "10. parametrs";
    param10Val = 0;
    notesTXT = "";
    info = "";
    updateUI();
}


void ComponentCard::on_pushButton_del_clicked()
{
QString text = "  Vai tiešām vēlaties\nneatgriezeniski dzēst\n        kartiņu ?";
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, " ", text, QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes){
        qDebug() << " del file: " << settingsFile;

        QString str = "Nodzēsta kartiņa " + cardName;
        ui->label_info->setText(str);

        QDir dir(settingsFile);
        dir.remove(settingsFile);

       // ui->comboBox_loadCard->removeItem(cmbListIndex);

        updateCardFileName();
    }

}


void ComponentCard::on_lineEdit_moisture_editingFinished()
{
    moisture = ui->lineEdit_moisture->text();
    qDebug() << "moisture: " << moisture;
}


void ComponentCard::on_lineEdit_moistureVol_editingFinished()
{
    int val = ui->lineEdit_moistureVol->text().toInt(&ok);
        if(ok){
            moistureVal = val;
        }
        else{
            ui->lineEdit_moistureVol->setText("moistureVol");
        }
        qDebug() << "moistureVal: " << moistureVal;
}


void ComponentCard::on_lineEdit_dray_editingFinished()
{
    dray = ui->lineEdit_dray->text();
    qDebug() << "dray: " << dray;
}


void ComponentCard::on_lineEdit_drayVol_editingFinished()
{
    int val = ui->lineEdit_drayVol->text().toInt(&ok);
        if(ok){
            drayVal = val;
        }
        else{
            ui->lineEdit_drayVol->setText("drayVol");
        }
}


void ComponentCard::on_lineEdit_organic_editingFinished()
{
    organic = ui->lineEdit_organic->text();
    qDebug() << "organic: " << organic;
}


void ComponentCard::on_lineEdit_organicVol_editingFinished()
{
    int val = ui->lineEdit_organicVol->text().toInt(&ok);
        if(ok){
            organicVal = val;
        }
        else{
            ui->lineEdit_organicVol->setText("organicVol");
        }
}


void ComponentCard::on_lineEdit_humin_editingFinished()
{
    humin = ui->lineEdit_humin->text();
    qDebug() << "humin: " << humin;
}


void ComponentCard::on_lineEdit_huminVol_editingFinished()
{
    int val = ui->lineEdit_huminVol->text().toInt(&ok);
        if(ok){
            huminVal = val;
        }
        else{
            ui->lineEdit_huminVol->setText("huminVol");
        }
}


void ComponentCard::on_lineEdit_sarms_editingFinished()
{
    sarms = ui->lineEdit_sarms->text();
    qDebug() << "sarms: " << sarms;
}


void ComponentCard::on_lineEdit_sarmsVol_editingFinished()
{
    int val = ui->lineEdit_sarmsVol->text().toInt(&ok);
        if(ok){
            sarmsVal = val;
        }
        else{
            ui->lineEdit_sarmsVol->setText("sarmsVol");
        }
}


void ComponentCard::on_lineEdit_KO_editingFinished()
{
    KO = ui->lineEdit_KO->text();
    qDebug() << "KO: " << KO;
}


void ComponentCard::on_lineEdit_KOVol_editingFinished()
{
    int val = ui->lineEdit_KOVol->text().toInt(&ok);
        if(ok){
            KOVal = val;
        }
        else{
            ui->lineEdit_KOVol->setText("KOVal");
        }
}


void ComponentCard::on_lineEdit_param7_editingFinished()
{
    param7 = ui->lineEdit_param7->text();
    qDebug() << "7: " << param7;
}
void ComponentCard::on_lineEdit_param7_Vol_editingFinished()
{
    int val = ui->lineEdit_param7_Vol->text().toInt(&ok);
        if(ok){
            param7Val = val;
        }
        else{
            ui->lineEdit_param7_Vol->setText("vol 7");
        }
}



void ComponentCard::on_lineEdit_param8_editingFinished()
{
    param8 = ui->lineEdit_param8->text();
    qDebug() << "8: " << param8;
}
void ComponentCard::on_lineEdit_param8_Vol_editingFinished()
{
    int val = ui->lineEdit_param8_Vol->text().toInt(&ok);
        if(ok){
            param8Val = val;
        }
        else{
            ui->lineEdit_param8_Vol->setText("vol 8");
        }
}




void ComponentCard::on_lineEdit_param9_editingFinished()
{
    param9 = ui->lineEdit_param9->text();
    qDebug() << "9: " << param9;
}

void ComponentCard::on_lineEdit_param9_Vol_editingFinished()
{
    int val = ui->lineEdit_param9_Vol->text().toInt(&ok);
        if(ok){
            param9Val = val;
        }
        else{
            ui->lineEdit_param9_Vol->setText("vol 9");
        }
}



void ComponentCard::on_lineEdit_param10_editingFinished()
{
    param10 = ui->lineEdit_param10->text();
    qDebug() << "10: " << param10;
}


void ComponentCard::on_lineEdit_param10Vol_editingFinished()
{
int val = ui->lineEdit_param10Vol->text().toInt(&ok);
    if(ok){
        param10Val = val;
    }
    else{
        ui->lineEdit_param10Vol->setText("vol 10");
    }
}


void ComponentCard::on_textEdit_notes_textChanged()
{
   notesTXT = ui->textEdit_notes->toPlainText();
   qDebug() << notesTXT;
}


void ComponentCard::on_pushButton_exit_clicked()
{
   // updateCardFileName();   // for testing
}

void ComponentCard::updateUI()
{
ui->lineEdit_comp_name->setText(cardName);
ui->lineEdit_moistureVol->setText(QString::number(moistureVal));
ui->lineEdit_drayVol->setText(QString::number(drayVal));
ui->lineEdit_organicVol->setText(QString::number(organicVal));
ui->lineEdit_huminVol->setText(QString::number(huminVal));
ui->lineEdit_sarmsVol->setText(QString::number(sarmsVal));
ui->lineEdit_KOVol->setText(QString::number(KOVal));
ui->lineEdit_param7->setText(param7);
ui->lineEdit_param7_Vol->setText(QString::number(param7Val));
ui->lineEdit_param8->setText(param8);
ui->lineEdit_param8_Vol->setText(QString::number(param8Val));
ui->lineEdit_param9->setText(param9);
ui->lineEdit_param9_Vol->setText(QString::number(param9Val));
ui->lineEdit_param10->setText(param10);
ui->lineEdit_param10Vol->setText(QString::number(param10Val));
ui->textEdit_notes->setText(notesTXT);
ui->label_info->setText(info);


}

void ComponentCard::updateCardFileName()
{
    QString strDir =  QApplication::applicationDirPath() + "/receptes/kartinas";
    QDir directory(strDir);

    global.cardFileName = directory.entryList(QStringList() << "*.ini",QDir::Files);
   // qDebug() << "directory: " << strDir;
    qDebug() << "files : "  << global.cardFileName;
    ui->comboBox_loadCard->clear();
    cmbList.clear();

    qDebug() << "-----------------------";
    int i = 0;
    foreach(QString filename, global.cardFileName) {

        qDebug()<< "filename.resize(2) == " << filename[0] << filename[1];
      if(filename[0] == 'k' && filename[1] == '_' ){
        cmbList.append(fileNameToItem(filename));
        qDebug() << "filename " << filename << cmbList[i];
        i++;
      }
    }

    qDebug()<< "cmbList len = "<<  cmbList.length() << "   " << cmbList;
   // on_comboBox_loadCard_currentIndexChanged(0);
    if(cmbList.length()){
        ui->comboBox_loadCard->addItems(cmbList);
    }
    //cmbList = global.cardFileName;
    //updateUI();
}

QString ComponentCard::fileNameToItem(QString fname)
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

QString ComponentCard::itemTofileName(QString item)
{
    QString fName = QApplication::applicationDirPath() + "/receptes/kartinas/k_";
    fName.append(item);
    fName.append(".ini");
    qDebug() << "fName: " << fName;
    return fName;
}

void ComponentCard::updateCardData(QString fname)
{

    qDebug() << "update settingsFile" << fname;
    QSettings settings(fname, QSettings::IniFormat);

    cardName = settings.value("Komponentes_nosaukums", "").toString();

    moistureVal = settings.value("Mitrums", "").toInt();
    drayVal = settings.value("Sausne",  "").toInt();
    organicVal = settings.value("Organiskas_vielas",  "").toInt();
    huminVal = settings.value("Humini",  "").toInt();
    sarmsVal = settings.value("Sarms",  "").toInt();
    KOVal = settings.value("K2O",  "").toInt();;

    param7 = settings.value("param_7",  "").toString();
    param7Val = settings.value("parametrs_7", "").toInt();

    param8 = settings.value("param_8",  "").toString();
    param8Val = settings.value("parametrs_8", "").toInt();

    param9 = settings.value("param_9",  "").toString();
    param9Val = settings.value("parametrs_9", "").toInt();

    param10 = settings.value("param_10",  "").toString();
    param10Val = settings.value("parametrs_10", "").toInt();

    notesTXT = settings.value("Piezimes", "").toString();
    QString str = "Nolasīts kartiņas fails:  " + settingsFile;
    ui->label_info->setText(str);
    updateUI();
}

void ComponentCard::readAllUIFields()
{
    on_lineEdit_moisture_editingFinished();
    on_lineEdit_moistureVol_editingFinished();
    on_lineEdit_dray_editingFinished();
    on_lineEdit_drayVol_editingFinished();
    on_lineEdit_organic_editingFinished();
    on_lineEdit_organicVol_editingFinished();
    on_lineEdit_humin_editingFinished();
    on_lineEdit_huminVol_editingFinished();
    on_lineEdit_sarms_editingFinished();
    on_lineEdit_sarmsVol_editingFinished();
    on_lineEdit_KO_editingFinished();
    on_lineEdit_KOVol_editingFinished();
    on_lineEdit_param7_editingFinished();
    on_lineEdit_param7_Vol_editingFinished();
    on_lineEdit_param8_editingFinished();
    on_lineEdit_param8_Vol_editingFinished();
    on_lineEdit_param9_editingFinished();
    on_lineEdit_param9_Vol_editingFinished();
    on_lineEdit_param10_editingFinished();
    on_lineEdit_param10Vol_editingFinished();
    on_textEdit_notes_textChanged();
}


void ComponentCard::on_comboBox_loadCard_currentIndexChanged(int index)
{
     qDebug() << " ComponentCard::on_comboBox_loadCard_currentIndexChanged" << index ;
    if(index < 0){
        index = 0;
    }

        cmbListIndex = index;
        settingsFile = "";
        if(cmbList.length() >= index){
            settingsFile = itemTofileName(cmbList[index]);
        }
  else{
      cardName = " ????????????????";
  }
  qDebug() << " Actual card name: " << cmbList[index] << "  index: "<< cmbListIndex<<"  file:  " <<settingsFile;
  updateCardData(settingsFile);
  updateUI();

}


void ComponentCard::on_comboBox_loadCard_highlighted(int index)
{
    qDebug() <<  "  on_comboBox_loadCard_highlighted   " << index ;
    on_comboBox_loadCard_currentIndexChanged(index);
}

