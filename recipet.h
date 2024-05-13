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
};

#endif // RECIPET_H
