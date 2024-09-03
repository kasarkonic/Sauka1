#ifndef PROCESSTEPS_H
#define PROCESSTEPS_H

#include <QMainWindow>
#include <QWidget>
#include "global.h"
#include "qcombobox.h"
#include <QSignalMapper>

namespace Ui {
class ProcesSteps;
}

class ProcesSteps : public QMainWindow
{
    Q_OBJECT

public:
    ProcesSteps(const ProcesSteps &) = default;
    ProcesSteps(ProcesSteps &&) = delete;
    ProcesSteps &operator=(const ProcesSteps &) = default;
    ProcesSteps &operator=(ProcesSteps &&) = delete;
    explicit ProcesSteps(Global &global, QWidget *parent = nullptr);
    ~ProcesSteps();
    void maximizeWindow();

protected:

    void wheelEvent(QWheelEvent * event) override;
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void clicked(int npk);
    void currentIndexChanged(int item);
    void editingFinished();
    void startR();
    void stopR();
    void pauseR();




public slots:
    void setTabValRecord(int recNr);

private slots:
   // void on_pushButton_Up_clicked();

   // void on_pushButton_Down_clicked();

    void on_pushButton_Load_clicked();

    void on_pushButton_clicked();

    void on_textEdit_Notes_textChanged();

    void onClickIns();
    void onClickDel();
    void groupIndexChange(int index);
    void objectIndexChange(int index);
    void linValFinish();
    void linNoteFinish();


    void on_pushButton_SlUp_clicked();

    void on_pushButton_SlDown_clicked();

    void on_verticalSlider_valueChanged(int value);

    void on_pushButton_Start_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButton_Pause_clicked();

private:
    Global& global;
    Ui::ProcesSteps *ui;
    QSignalMapper *signalMapper;
    void drawWidgets();

    struct  tPtr {
        QLabel *label_npk;
        QPushButton *button_ins = nullptr;
        QPushButton *button_del = nullptr;
        QComboBox *cmbGroup = nullptr;
        QComboBox *cmbObject = nullptr;
        QLineEdit *linEditVal = nullptr;
        QLineEdit *linEditNote = nullptr;
        QLabel *labelhelp  = nullptr;
    };
    QList<tPtr>tabPtr;
    /*
 * move to global
    struct  tVal {
        int npk = 0; //QLabel *label_npk;
        int cmbGroupItem = 0; //QComboBox *cmbGroup = nullptr;
        int cmbObjectItem = 0;// QComboBox *cmbObject = nullptr;
        int  val = 0;      //QLineEdit *linEditVal = nullptr;
        QString  notes = ""; //    QLineEdit *linEditNote = nullptr;
    };
    QList<tVal>tabVal;
*/
    bool ok;
    bool ok1;
    int activeRow = 0;
    int firstLineIndex = 0;

    void UpdateTable();

    QList<QString>saveProcesList;
    QList<QString>loadProcesList;

};

#endif // PROCESSTEPS_H
