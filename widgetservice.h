#ifndef WIDGETSERVICE_H
#define WIDGETSERVICE_H

#include <QWidget>

#include"global.h"
#include "widgetDiagramElement.h"
#include <QMainWindow>



namespace Ui {
    class WidgetService;
}

class WidgetService : public  QWidget {
    Q_OBJECT
public:
    Global& global;
    Ui::WidgetService* ui;
    explicit WidgetService(Global& global, WidgetDiagramElement* widgetElement, QWidget* parent = nullptr);
    void openWidgetServiceForm();
    void updateSettings();
    ~WidgetService();

protected:
    void    closeEvent(QCloseEvent* event) override;
    void    mousePressEvent(QMouseEvent* event) override;
    void    mouseMoveEvent(QMouseEvent* event) override;
    void    mouseDoubleClickEvent(QMouseEvent* event) override;
private slots:
    void on_pushButton_Xplus_clicked();

    void on_pushButton_Xminus_clicked();

    void on_pushButton_Yplus_clicked();

    void on_pushButton_Yminus_clicked();

    void on_pushButton_sizeplus_clicked();

    void on_pushButton_sizeMinus_clicked();

    void on_pushButton_OptionsMinus_clicked();

    void on_pushButton_OptionsPlus_clicked();

    void on_lineEdit_Xpos_editingFinished();

    void on_lineEdit_Ypos_editingFinished();

    void on_lineEdit_startSize_editingFinished();

    void on_lineEdit_options_editingFinished();

    // void on_pushButton_ON_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_lineEdit_AddresAN2_editingFinished();

    void on_lineEdit_AddresAN1_editingFinished();

    void on_lineEdit_AddresDI_editingFinished();

    void on_horizontalSlider_2_valueChanged(int value);

    void on_horizontalSlider_1_valueChanged(int value);

private:
    // WidgetDiagramElement::widDataStruct &wsettings;
    WidgetDiagramElement* widgetElement;
    //Global &global;
    QObject obj;
    //Ui::WidgetService *ui;
    // Pipe pipe;

    void updateUIvalue();
    int mouseStartPointX;
    int mouseStartPointY;
    //void updateSettings();
    void updateFormData();
    void updateSensorVal();
    QString currentWid;

    int addresAct;  // global.widHash[].act_sensAddres  ok
    int addresSens1;  // global.widHash[].act_sensAddres  ok
    int addresSens2;  // global.widHash[].act_sensAddres  ok

    //int addresAN1;  // global.widHash[].sensAddres1
   // int addresAN2;  // global.widHash[].sensAddres2

    int actValueDi; // push button value == lineedit DI value
    int actValueAn1;
    int actValueAn2;
    //int an1Value;
    //int an2Value;
};



#endif // WIDGETSERVICE_H
