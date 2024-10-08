#ifndef RECIPET_H
#define RECIPET_H

#include <QMainWindow>
#include"global.h"
namespace Ui {
    class Recipet;
}

class Recipet : public QWidget {
    Q_OBJECT

public:
    explicit Recipet(Global& global, QWidget* parent = nullptr);
    ~Recipet();

    //  void setUpdateUI(const void &newUpdateUI);

protected:
    //   bool event(QEvent *e) override;


private slots:
    void on_pushButton_delet_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_exit_clicked();

    void on_comboBox_reciep_highlighted(int index);

    void on_comboBox_reciep_currentIndexChanged(int index);

    void on_lineEdit_1_ingr_val_editingFinished();

    void on_lineEdit_2_ingr_val_editingFinished();

    void on_lineEdit_3_ingr_val_editingFinished();

    void on_lineEdit_4_ingr_val_editingFinished();

    void on_lineEdit_5_ingr_val_editingFinished();

    void on_lineEdit_6_ingr_val_editingFinished();

    void on_lineEdit_7_ingr_val_editingFinished();

    void on_lineEdit_8_ingr_val_editingFinished();

    void on_lineEdit_9_ingr_val_editingFinished();

    void on_lineEdit_10_ingr_val_editingFinished();

    void on_pushButton_components_Card_clicked();

    void on_pushButton_clear_clicked();

private:
    Ui::Recipet* ui;
    Global& global;
    QStringList cmbList;
    QStringList cardFileName;
    QStringList rcmbList;
    QStringList rcardFileName;
    QStringList pcmbList;
    void updateUI();
    void updateRecdData();
    QString fileNameToItem(QString fname);
    QString itemTofileName(QString item);

    QString fileNameToItemR(QString fname);
    QString itemTofileNameR(QString item);
    void updateCardFileName();
    void updateRecFileName();
    void clearFilds();
    bool ok;
    void calculateSumm();

    QString notesTXT;

    QString ingr1;
    QString ingr2;
    QString ingr3;
    QString ingr4;
    QString ingr5;
    QString ingr6;
    QString ingr7;
    QString process1;
    QString process2;
    QString process3;

    int ingr1_vol;
    int ingr2_vol;
    int ingr3_vol;
    int ingr4_vol;
    int ingr5_vol;
    int ingr6_vol;
    int ingr7_vol;
    int process1_vol;
    int process2_vol;
    int process3_vol;

    QString recName;
};

#endif // RECIPET_H
