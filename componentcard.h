#ifndef COMPONENTCARD_H
#define COMPONENTCARD_H

#include <QMainWindow>
#include"global.h"

namespace Ui {
class ComponentCard;
}

class ComponentCard : public QWidget
{
    Q_OBJECT

public:

    explicit ComponentCard(Global &global, QWidget *parent = nullptr);
   // Ui::ComponentCard *ui;
    ~ComponentCard();

private slots:
    void on_lineEdit_comp_name_editingFinished();







    void on_pushButton_edit_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_del_clicked();

    void on_lineEdit_moisture_editingFinished();

    void on_lineEdit_moistureVol_editingFinished();

    void on_lineEdit_dray_editingFinished();

    void on_lineEdit_drayVol_editingFinished();

    void on_lineEdit_organic_editingFinished();

    void on_lineEdit_organicVol_editingFinished();

    void on_lineEdit_humin_editingFinished();

    void on_lineEdit_huminVol_editingFinished();

    void on_lineEdit_sarms_editingFinished();

    void on_lineEdit_sarmsVol_editingFinished();

    void on_lineEdit_KO_editingFinished();

    void on_lineEdit_KOVol_editingFinished();

    void on_lineEdit_param7_editingFinished();



    void on_lineEdit_param8_editingFinished();



    void on_lineEdit_param9_editingFinished();


    void on_lineEdit_param10_editingFinished();

    void on_lineEdit_param10Vol_editingFinished();

    void on_textEdit_notes_textChanged();

    void on_lineEdit_param7_Vol_editingFinished();

    void on_lineEdit_param8_Vol_editingFinished();



    void on_lineEdit_param9_Vol_editingFinished();

    void on_pushButton_exit_clicked();

    void on_comboBox_loadCard_currentIndexChanged(int index);



    void on_comboBox_loadCard_highlighted(int index);

private:
    Ui::ComponentCard *ui;
    Global &global;
    void updateUI();

    QString settingsFile;
    bool ok;

    QString cardName;
    QString moisture;
    int moistureVal;
    QString dray;
    int drayVal;
    QString organic;
    int organicVal;
    QString humin;
    int huminVal;
    QString sarms;
    int sarmsVal;
    QString KO;
    int KOVal;
    QString param7;
    int param7Val;
    QString param8;
    int param8Val;
    QString param9;
    int param9Val;
    QString param10;
    int param10Val;
    QString notesTXT;
    QString info;

    QStringList cmbList;
    int cmbListIndex;
    void updateCardFileName();
    QString fileNameToItem(QString fname);
    QString itemTofileName(QString item);
    void updateCardData(QString fname);
    void readAllUIFields();
};

#endif // COMPONENTCARD_H
