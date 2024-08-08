/********************************************************************************
** Form generated from reading UI file 'hwservice.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HWSERVICE_H
#define UI_HWSERVICE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HWService
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_Sauka;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QFrame *line;
    QFrame *line_3;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_actuator;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_sensor;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_Scales;
    QFrame *line_5;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pushButton_Com_Ports;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *pushButton_measure;
    QSpacerItem *horizontalSpacer_6;
    QFrame *line_6;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_ETA;
    QComboBox *comboBox_use_motor;
    QPushButton *pushButton_Motor_on;
    QPushButton *pushButton_Motor_off;
    QSlider *horizontalSlider;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButton_slider_minus;
    QLabel *label_slider_center;
    QPushButton *pushButton_slider_plus;
    QPushButton *pushButton_Reset;
    QPushButton *pushButton_get_error_code;
    QHBoxLayout *horizontalLayout_10;
    QLineEdit *lineEdit_enter_reg;
    QPushButton *pushButton_readReg;
    QFrame *line_7;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_row1;
    QLabel *label_row2;
    QLabel *label_row3;
    QFrame *line_10;
    QLabel *label_row4;
    QLabel *label_row5;
    QLabel *label_row6;
    QFrame *line_9;
    QLabel *label_row7;
    QLabel *label_row8;
    QFrame *line_8;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_6;
    QLineEdit *lineEdit_Out_address;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_7;
    QLineEdit *lineEdit_Out_value;
    QHBoxLayout *horizontalLayout_11;
    QPushButton *pushButton_Out_write;
    QPushButton *pushButton_Out_1;
    QPushButton *pushButton_Out_0;
    QLabel *label_5;
    QSpacerItem *verticalSpacer;
    QFrame *line_4;
    QHBoxLayout *horizontalLayout_5;
    QTextEdit *textEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *HWService)
    {
        if (HWService->objectName().isEmpty())
            HWService->setObjectName("HWService");
        HWService->resize(1214, 780);
        centralwidget = new QWidget(HWService);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_Sauka = new QLabel(centralwidget);
        label_Sauka->setObjectName("label_Sauka");

        horizontalLayout->addWidget(label_Sauka);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        horizontalLayout->addWidget(label_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_2->addWidget(line);

        line_3 = new QFrame(centralwidget);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::Shape::HLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_2->addWidget(line_3);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_2->addWidget(line_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        pushButton_actuator = new QPushButton(centralwidget);
        pushButton_actuator->setObjectName("pushButton_actuator");

        horizontalLayout_3->addWidget(pushButton_actuator);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        pushButton_sensor = new QPushButton(centralwidget);
        pushButton_sensor->setObjectName("pushButton_sensor");

        horizontalLayout_3->addWidget(pushButton_sensor);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");

        horizontalLayout_3->addWidget(pushButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        pushButton_Scales = new QPushButton(centralwidget);
        pushButton_Scales->setObjectName("pushButton_Scales");

        horizontalLayout_3->addWidget(pushButton_Scales);


        verticalLayout_2->addLayout(horizontalLayout_3);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

        line_5 = new QFrame(centralwidget);
        line_5->setObjectName("line_5");
        line_5->setFrameShape(QFrame::Shape::HLine);
        line_5->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_3->addWidget(line_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);

        pushButton_Com_Ports = new QPushButton(centralwidget);
        pushButton_Com_Ports->setObjectName("pushButton_Com_Ports");

        horizontalLayout_4->addWidget(pushButton_Com_Ports);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        pushButton_measure = new QPushButton(centralwidget);
        pushButton_measure->setObjectName("pushButton_measure");

        horizontalLayout_4->addWidget(pushButton_measure);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);


        verticalLayout_3->addLayout(horizontalLayout_4);

        line_6 = new QFrame(centralwidget);
        line_6->setObjectName("line_6");
        line_6->setFrameShape(QFrame::Shape::HLine);
        line_6->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_3->addWidget(line_6);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_ETA = new QLabel(centralwidget);
        label_ETA->setObjectName("label_ETA");
        label_ETA->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_ETA);

        comboBox_use_motor = new QComboBox(centralwidget);
        comboBox_use_motor->setObjectName("comboBox_use_motor");

        verticalLayout_5->addWidget(comboBox_use_motor);

        pushButton_Motor_on = new QPushButton(centralwidget);
        pushButton_Motor_on->setObjectName("pushButton_Motor_on");

        verticalLayout_5->addWidget(pushButton_Motor_on);

        pushButton_Motor_off = new QPushButton(centralwidget);
        pushButton_Motor_off->setObjectName("pushButton_Motor_off");

        verticalLayout_5->addWidget(pushButton_Motor_off);

        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName("horizontalSlider");
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout_5->addWidget(horizontalSlider);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        pushButton_slider_minus = new QPushButton(centralwidget);
        pushButton_slider_minus->setObjectName("pushButton_slider_minus");
        pushButton_slider_minus->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_9->addWidget(pushButton_slider_minus);

        label_slider_center = new QLabel(centralwidget);
        label_slider_center->setObjectName("label_slider_center");
        QFont font;
        font.setPointSize(9);
        label_slider_center->setFont(font);
        label_slider_center->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(label_slider_center);

        pushButton_slider_plus = new QPushButton(centralwidget);
        pushButton_slider_plus->setObjectName("pushButton_slider_plus");
        pushButton_slider_plus->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_9->addWidget(pushButton_slider_plus);


        verticalLayout_5->addLayout(horizontalLayout_9);

        pushButton_Reset = new QPushButton(centralwidget);
        pushButton_Reset->setObjectName("pushButton_Reset");

        verticalLayout_5->addWidget(pushButton_Reset);

        pushButton_get_error_code = new QPushButton(centralwidget);
        pushButton_get_error_code->setObjectName("pushButton_get_error_code");

        verticalLayout_5->addWidget(pushButton_get_error_code);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        lineEdit_enter_reg = new QLineEdit(centralwidget);
        lineEdit_enter_reg->setObjectName("lineEdit_enter_reg");

        horizontalLayout_10->addWidget(lineEdit_enter_reg);

        pushButton_readReg = new QPushButton(centralwidget);
        pushButton_readReg->setObjectName("pushButton_readReg");

        horizontalLayout_10->addWidget(pushButton_readReg);


        verticalLayout_5->addLayout(horizontalLayout_10);


        horizontalLayout_6->addLayout(verticalLayout_5);

        line_7 = new QFrame(centralwidget);
        line_7->setObjectName("line_7");
        line_7->setFrameShape(QFrame::Shape::VLine);
        line_7->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_6->addWidget(line_7);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_row1 = new QLabel(centralwidget);
        label_row1->setObjectName("label_row1");

        verticalLayout_4->addWidget(label_row1);

        label_row2 = new QLabel(centralwidget);
        label_row2->setObjectName("label_row2");

        verticalLayout_4->addWidget(label_row2);

        label_row3 = new QLabel(centralwidget);
        label_row3->setObjectName("label_row3");

        verticalLayout_4->addWidget(label_row3);

        line_10 = new QFrame(centralwidget);
        line_10->setObjectName("line_10");
        line_10->setFrameShape(QFrame::Shape::HLine);
        line_10->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_4->addWidget(line_10);

        label_row4 = new QLabel(centralwidget);
        label_row4->setObjectName("label_row4");

        verticalLayout_4->addWidget(label_row4);

        label_row5 = new QLabel(centralwidget);
        label_row5->setObjectName("label_row5");

        verticalLayout_4->addWidget(label_row5);

        label_row6 = new QLabel(centralwidget);
        label_row6->setObjectName("label_row6");

        verticalLayout_4->addWidget(label_row6);

        line_9 = new QFrame(centralwidget);
        line_9->setObjectName("line_9");
        line_9->setFrameShape(QFrame::Shape::HLine);
        line_9->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_4->addWidget(line_9);

        label_row7 = new QLabel(centralwidget);
        label_row7->setObjectName("label_row7");

        verticalLayout_4->addWidget(label_row7);

        label_row8 = new QLabel(centralwidget);
        label_row8->setObjectName("label_row8");

        verticalLayout_4->addWidget(label_row8);


        horizontalLayout_6->addLayout(verticalLayout_4);

        line_8 = new QFrame(centralwidget);
        line_8->setObjectName("line_8");
        line_8->setFrameShape(QFrame::Shape::VLine);
        line_8->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_6->addWidget(line_8);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        verticalLayout->addWidget(label_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");

        horizontalLayout_7->addWidget(label_6);

        lineEdit_Out_address = new QLineEdit(centralwidget);
        lineEdit_Out_address->setObjectName("lineEdit_Out_address");

        horizontalLayout_7->addWidget(lineEdit_Out_address);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");

        horizontalLayout_8->addWidget(label_7);

        lineEdit_Out_value = new QLineEdit(centralwidget);
        lineEdit_Out_value->setObjectName("lineEdit_Out_value");

        horizontalLayout_8->addWidget(lineEdit_Out_value);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        pushButton_Out_write = new QPushButton(centralwidget);
        pushButton_Out_write->setObjectName("pushButton_Out_write");

        horizontalLayout_11->addWidget(pushButton_Out_write);

        pushButton_Out_1 = new QPushButton(centralwidget);
        pushButton_Out_1->setObjectName("pushButton_Out_1");

        horizontalLayout_11->addWidget(pushButton_Out_1);

        pushButton_Out_0 = new QPushButton(centralwidget);
        pushButton_Out_0->setObjectName("pushButton_Out_0");

        horizontalLayout_11->addWidget(pushButton_Out_0);


        verticalLayout->addLayout(horizontalLayout_11);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");

        verticalLayout->addWidget(label_5);


        horizontalLayout_6->addLayout(verticalLayout);

        horizontalLayout_6->setStretch(0, 5);
        horizontalLayout_6->setStretch(2, 15);
        horizontalLayout_6->setStretch(4, 15);

        verticalLayout_3->addLayout(horizontalLayout_6);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        line_4 = new QFrame(centralwidget);
        line_4->setObjectName("line_4");
        line_4->setFrameShape(QFrame::Shape::HLine);
        line_4->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_3->addWidget(line_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");

        horizontalLayout_5->addWidget(textEdit);


        verticalLayout_3->addLayout(horizontalLayout_5);

        verticalLayout_3->setStretch(0, 5);
        verticalLayout_3->setStretch(1, 5);
        verticalLayout_3->setStretch(2, 5);
        verticalLayout_3->setStretch(3, 5);
        verticalLayout_3->setStretch(4, 5);
        verticalLayout_3->setStretch(5, 5);
        verticalLayout_3->setStretch(6, 5);
        verticalLayout_3->setStretch(7, 1);
        verticalLayout_3->setStretch(8, 50);
        HWService->setCentralWidget(centralwidget);
        menubar = new QMenuBar(HWService);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1214, 21));
        HWService->setMenuBar(menubar);
        statusbar = new QStatusBar(HWService);
        statusbar->setObjectName("statusbar");
        HWService->setStatusBar(statusbar);

        retranslateUi(HWService);

        QMetaObject::connectSlotsByName(HWService);
    } // setupUi

    void retranslateUi(QMainWindow *HWService)
    {
        HWService->setWindowTitle(QCoreApplication::translate("HWService", "MainWindow", nullptr));
        label_Sauka->setText(QCoreApplication::translate("HWService", "TextLabel", nullptr));
        label_3->setText(QCoreApplication::translate("HWService", "Servisa lapa", nullptr));
        label_2->setText(QCoreApplication::translate("HWService", "TextLabel", nullptr));
        pushButton_actuator->setText(QCoreApplication::translate("HWService", "Aktu\304\201tori", nullptr));
        pushButton_sensor->setText(QCoreApplication::translate("HWService", "Dev\304\223ji", nullptr));
        pushButton->setText(QCoreApplication::translate("HWService", "Testi", nullptr));
        pushButton_Scales->setText(QCoreApplication::translate("HWService", "Svari", nullptr));
        pushButton_Com_Ports->setText(QCoreApplication::translate("HWService", "Com Ports", nullptr));
        pushButton_measure->setText(QCoreApplication::translate("HWService", "M\304\223r\304\253jumi", nullptr));
        label_ETA->setText(QCoreApplication::translate("HWService", "Motoru komandas", nullptr));
        pushButton_Motor_on->setText(QCoreApplication::translate("HWService", "Motor Start", nullptr));
        pushButton_Motor_off->setText(QCoreApplication::translate("HWService", "Motor Stop", nullptr));
        pushButton_slider_minus->setText(QCoreApplication::translate("HWService", "-", nullptr));
        label_slider_center->setText(QCoreApplication::translate("HWService", "0", nullptr));
        pushButton_slider_plus->setText(QCoreApplication::translate("HWService", "+", nullptr));
        pushButton_Reset->setText(QCoreApplication::translate("HWService", "Reset", nullptr));
        pushButton_get_error_code->setText(QCoreApplication::translate("HWService", "Get ERROR code", nullptr));
        lineEdit_enter_reg->setText(QCoreApplication::translate("HWService", "Enter reg", nullptr));
        pushButton_readReg->setText(QCoreApplication::translate("HWService", "Read", nullptr));
        label_row1->setText(QCoreApplication::translate("HWService", "A1 out 0-31", nullptr));
        label_row2->setText(QCoreApplication::translate("HWService", "A2 out 32-63", nullptr));
        label_row3->setText(QCoreApplication::translate("HWService", "A3 out 64-95", nullptr));
        label_row4->setText(QCoreApplication::translate("HWService", "A1 in 1-31", nullptr));
        label_row5->setText(QCoreApplication::translate("HWService", "A2 in 32-63", nullptr));
        label_row6->setText(QCoreApplication::translate("HWService", "A3 in 64-95", nullptr));
        label_row7->setText(QCoreApplication::translate("HWService", "An in 0-15", nullptr));
        label_row8->setText(QCoreApplication::translate("HWService", "Virtual in 0-32", nullptr));
        label_4->setText(QCoreApplication::translate("HWService", "Iestat\304\253t izejas", nullptr));
        label_6->setText(QCoreApplication::translate("HWService", "Address:  0-32", nullptr));
        label_7->setText(QCoreApplication::translate("HWService", "Value:  0,   >0 ", nullptr));
        pushButton_Out_write->setText(QCoreApplication::translate("HWService", "S\305\253t\304\253t", nullptr));
        pushButton_Out_1->setText(QCoreApplication::translate("HWService", "S\305\253t\304\253t 1", nullptr));
        pushButton_Out_0->setText(QCoreApplication::translate("HWService", "S\305\253t\304\253t 0", nullptr));
        label_5->setText(QCoreApplication::translate("HWService", "Tekst", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HWService: public Ui_HWService {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HWSERVICE_H
