#ifndef WIDGETSERVICE_H
#define WIDGETSERVICE_H

#include <QWidget>

//#include"global.h"

#include "widgetDiagramElement.h"
#include <QMainWindow>



namespace Ui {
class WidgetService;
}

class WidgetService :  public  QWidget
{
    Q_OBJECT
public:
    explicit WidgetService(WidgetDiagramElement *widgetElement, QWidget *parent = nullptr);

    ~WidgetService();
    void openWidgetServiceForm();
    Ui::WidgetService *ui;
    void updateSettings();

protected:
    void    closeEvent (QCloseEvent *event) override;
    void    mousePressEvent(QMouseEvent *event) override;
    void    mouseMoveEvent (QMouseEvent *event) override;
    void    mouseDoubleClickEvent(QMouseEvent *event) override;
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

private:
         // WidgetDiagramElement::widDataStruct &wsettings;
    WidgetDiagramElement *widgetElement;
    // Global &global;
    QObject obj;
    //Ui::WidgetService *ui;
    // Pipe pipe;

    void updateUIvalue();
    int mouseStartPointX;
    int mouseStartPointY;
    //void updateSettings();
    void updateFormData();
    QString currentWid;

};



#endif // WIDGETSERVICE_H
