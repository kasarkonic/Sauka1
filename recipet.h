#ifndef RECIPET_H
#define RECIPET_H

#include <QMainWindow>
#include"global.h"
namespace Ui {
class Recipet;
}

class Recipet : public QWidget
{
    Q_OBJECT

public:
    explicit Recipet(Global &global, QWidget *parent = nullptr);
    ~Recipet();

private slots:
    void on_pushButton_delet_clicked();

    void on_pushButton_clear_clicked(bool checked);

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

private:
    Ui::Recipet *ui;
    Global &global;
    QStringList cmbList;
    QStringList cardFileName;
    QString recName;
    QString fileNameToItem(QString fname);
    QString itemTofileName(QString item);

    QString fileNameToItemR(QString fname);
    QString itemTofileNameR(QString item);
    void updateCardFileName();
    void clearFilds();
    bool ok;
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
};

#endif // RECIPET_H
