/********************************************************************************
** Form generated from reading UI file 'rs232.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RS232_H
#define UI_RS232_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
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

class Ui_Rs232
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_chart;
    QHBoxLayout *horizontalLayout;
    QLabel *label_chart_info;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_statuss;
    QPushButton *pushButtonStart;
    QPushButton *pushButton_Stop;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_3;
    QPushButton *pushButton_1s;
    QPushButton *pushButton_10s;
    QPushButton *pushButton_60s;
    QPushButton *pushButton_Save;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QTextEdit *textEditInfo;
    QFrame *line;
    QVBoxLayout *verticalLayout_sens_1;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QLabel *label_current_S0;
    QLabel *label_2;
    QLabel *label_average_S0;
    QFrame *line_4;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *lineEdit_full_S0;
    QLabel *label_full_S0;
    QPushButton *pushButton_set_S0;
    QHBoxLayout *horizontalLayout_7;
    QSlider *verticalSlider_S0;
    QHBoxLayout *horizontalLayout_8;
    QLineEdit *lineEdit_empty_S0;
    QLabel *label_empty_S0;
    QPushButton *pushButton_set_empty_s0;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButton_save_S0;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_name_S0;
    QFrame *line_2;
    QFrame *line_3;
    QVBoxLayout *verticalLayout_sens_2;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_3;
    QLabel *label_current_S1;
    QLabel *label_4;
    QLabel *label_average_S1;
    QFrame *line_5;
    QHBoxLayout *horizontalLayout_15;
    QLineEdit *lineEdit_full_S1;
    QLabel *label_full_S1;
    QPushButton *pushButton_set_S1;
    QHBoxLayout *horizontalLayout_14;
    QSlider *verticalSlider_S1;
    QHBoxLayout *horizontalLayout_13;
    QLineEdit *lineEdit_empty_S1;
    QLabel *label_empty_S1;
    QPushButton *pushButton_set_empty_s1;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *pushButton_save_S1;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_name_S1;
    QFrame *line_7;
    QFrame *line_8;
    QVBoxLayout *verticalLayout_sens_3;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_5;
    QLabel *label_current_S2;
    QLabel *label_6;
    QLabel *label_average_S2;
    QFrame *line_6;
    QHBoxLayout *horizontalLayout_22;
    QLineEdit *lineEdit_full_S2;
    QLabel *label_full_S2;
    QPushButton *pushButton_set_S2;
    QHBoxLayout *horizontalLayout_21;
    QSlider *verticalSlider_S2;
    QHBoxLayout *horizontalLayout_20;
    QLineEdit *lineEdit_empty_S2;
    QLabel *label_empty_S2;
    QPushButton *pushButton_set_empty_s2;
    QPushButton *pushButton_save_S2;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_name_S2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Rs232)
    {
        if (Rs232->objectName().isEmpty())
            Rs232->setObjectName("Rs232");
        Rs232->resize(1413, 600);
        centralwidget = new QWidget(Rs232);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_4 = new QHBoxLayout(centralwidget);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout_chart = new QVBoxLayout();
        verticalLayout_chart->setObjectName("verticalLayout_chart");

        verticalLayout->addLayout(verticalLayout_chart);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_chart_info = new QLabel(centralwidget);
        label_chart_info->setObjectName("label_chart_info");
        QFont font;
        font.setPointSize(13);
        label_chart_info->setFont(font);

        horizontalLayout->addWidget(label_chart_info);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_statuss = new QLabel(centralwidget);
        label_statuss->setObjectName("label_statuss");

        horizontalLayout_3->addWidget(label_statuss);

        pushButtonStart = new QPushButton(centralwidget);
        pushButtonStart->setObjectName("pushButtonStart");

        horizontalLayout_3->addWidget(pushButtonStart);

        pushButton_Stop = new QPushButton(centralwidget);
        pushButton_Stop->setObjectName("pushButton_Stop");

        horizontalLayout_3->addWidget(pushButton_Stop);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");

        horizontalLayout_3->addWidget(pushButton_3);

        pushButton_1s = new QPushButton(centralwidget);
        pushButton_1s->setObjectName("pushButton_1s");

        horizontalLayout_3->addWidget(pushButton_1s);

        pushButton_10s = new QPushButton(centralwidget);
        pushButton_10s->setObjectName("pushButton_10s");

        horizontalLayout_3->addWidget(pushButton_10s);

        pushButton_60s = new QPushButton(centralwidget);
        pushButton_60s->setObjectName("pushButton_60s");

        horizontalLayout_3->addWidget(pushButton_60s);

        pushButton_Save = new QPushButton(centralwidget);
        pushButton_Save->setObjectName("pushButton_Save");

        horizontalLayout_3->addWidget(pushButton_Save);

        horizontalLayout_3->setStretch(0, 7);
        horizontalLayout_3->setStretch(1, 10);
        horizontalLayout_3->setStretch(2, 10);
        horizontalLayout_3->setStretch(3, 10);
        horizontalLayout_3->setStretch(4, 10);
        horizontalLayout_3->setStretch(5, 10);
        horizontalLayout_3->setStretch(6, 10);
        horizontalLayout_3->setStretch(7, 10);

        verticalLayout->addLayout(horizontalLayout_3);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        textEditInfo = new QTextEdit(centralwidget);
        textEditInfo->setObjectName("textEditInfo");

        horizontalLayout_2->addWidget(textEditInfo);


        verticalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout->addLayout(verticalLayout_3);

        verticalLayout->setStretch(0, 20);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(3, 1);

        horizontalLayout_4->addLayout(verticalLayout);

        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_4->addWidget(line);

        verticalLayout_sens_1 = new QVBoxLayout();
        verticalLayout_sens_1->setObjectName("verticalLayout_sens_1");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout_5->addWidget(label);

        label_current_S0 = new QLabel(centralwidget);
        label_current_S0->setObjectName("label_current_S0");

        horizontalLayout_5->addWidget(label_current_S0);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        horizontalLayout_5->addWidget(label_2);

        label_average_S0 = new QLabel(centralwidget);
        label_average_S0->setObjectName("label_average_S0");

        horizontalLayout_5->addWidget(label_average_S0);


        verticalLayout_sens_1->addLayout(horizontalLayout_5);

        line_4 = new QFrame(centralwidget);
        line_4->setObjectName("line_4");
        line_4->setFrameShape(QFrame::Shape::HLine);
        line_4->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_sens_1->addWidget(line_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        lineEdit_full_S0 = new QLineEdit(centralwidget);
        lineEdit_full_S0->setObjectName("lineEdit_full_S0");

        horizontalLayout_6->addWidget(lineEdit_full_S0);

        label_full_S0 = new QLabel(centralwidget);
        label_full_S0->setObjectName("label_full_S0");

        horizontalLayout_6->addWidget(label_full_S0);

        pushButton_set_S0 = new QPushButton(centralwidget);
        pushButton_set_S0->setObjectName("pushButton_set_S0");

        horizontalLayout_6->addWidget(pushButton_set_S0);


        verticalLayout_sens_1->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        verticalSlider_S0 = new QSlider(centralwidget);
        verticalSlider_S0->setObjectName("verticalSlider_S0");
        verticalSlider_S0->setMinimumSize(QSize(100, 0));
        verticalSlider_S0->setOrientation(Qt::Vertical);

        horizontalLayout_7->addWidget(verticalSlider_S0);


        verticalLayout_sens_1->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        lineEdit_empty_S0 = new QLineEdit(centralwidget);
        lineEdit_empty_S0->setObjectName("lineEdit_empty_S0");

        horizontalLayout_8->addWidget(lineEdit_empty_S0);

        label_empty_S0 = new QLabel(centralwidget);
        label_empty_S0->setObjectName("label_empty_S0");

        horizontalLayout_8->addWidget(label_empty_S0);

        pushButton_set_empty_s0 = new QPushButton(centralwidget);
        pushButton_set_empty_s0->setObjectName("pushButton_set_empty_s0");

        horizontalLayout_8->addWidget(pushButton_set_empty_s0);


        verticalLayout_sens_1->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        pushButton_save_S0 = new QPushButton(centralwidget);
        pushButton_save_S0->setObjectName("pushButton_save_S0");

        horizontalLayout_9->addWidget(pushButton_save_S0);


        verticalLayout_sens_1->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        label_name_S0 = new QLabel(centralwidget);
        label_name_S0->setObjectName("label_name_S0");

        horizontalLayout_10->addWidget(label_name_S0);


        verticalLayout_sens_1->addLayout(horizontalLayout_10);


        horizontalLayout_4->addLayout(verticalLayout_sens_1);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_4->addWidget(line_2);

        line_3 = new QFrame(centralwidget);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::Shape::VLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_4->addWidget(line_3);

        verticalLayout_sens_2 = new QVBoxLayout();
        verticalLayout_sens_2->setObjectName("verticalLayout_sens_2");
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName("horizontalLayout_16");
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        horizontalLayout_16->addWidget(label_3);

        label_current_S1 = new QLabel(centralwidget);
        label_current_S1->setObjectName("label_current_S1");

        horizontalLayout_16->addWidget(label_current_S1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        horizontalLayout_16->addWidget(label_4);

        label_average_S1 = new QLabel(centralwidget);
        label_average_S1->setObjectName("label_average_S1");

        horizontalLayout_16->addWidget(label_average_S1);


        verticalLayout_sens_2->addLayout(horizontalLayout_16);

        line_5 = new QFrame(centralwidget);
        line_5->setObjectName("line_5");
        line_5->setFrameShape(QFrame::Shape::HLine);
        line_5->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_sens_2->addWidget(line_5);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName("horizontalLayout_15");
        lineEdit_full_S1 = new QLineEdit(centralwidget);
        lineEdit_full_S1->setObjectName("lineEdit_full_S1");

        horizontalLayout_15->addWidget(lineEdit_full_S1);

        label_full_S1 = new QLabel(centralwidget);
        label_full_S1->setObjectName("label_full_S1");

        horizontalLayout_15->addWidget(label_full_S1);

        pushButton_set_S1 = new QPushButton(centralwidget);
        pushButton_set_S1->setObjectName("pushButton_set_S1");

        horizontalLayout_15->addWidget(pushButton_set_S1);


        verticalLayout_sens_2->addLayout(horizontalLayout_15);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName("horizontalLayout_14");
        verticalSlider_S1 = new QSlider(centralwidget);
        verticalSlider_S1->setObjectName("verticalSlider_S1");
        verticalSlider_S1->setMinimumSize(QSize(100, 0));
        verticalSlider_S1->setOrientation(Qt::Vertical);

        horizontalLayout_14->addWidget(verticalSlider_S1);


        verticalLayout_sens_2->addLayout(horizontalLayout_14);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        lineEdit_empty_S1 = new QLineEdit(centralwidget);
        lineEdit_empty_S1->setObjectName("lineEdit_empty_S1");

        horizontalLayout_13->addWidget(lineEdit_empty_S1);

        label_empty_S1 = new QLabel(centralwidget);
        label_empty_S1->setObjectName("label_empty_S1");

        horizontalLayout_13->addWidget(label_empty_S1);

        pushButton_set_empty_s1 = new QPushButton(centralwidget);
        pushButton_set_empty_s1->setObjectName("pushButton_set_empty_s1");

        horizontalLayout_13->addWidget(pushButton_set_empty_s1);


        verticalLayout_sens_2->addLayout(horizontalLayout_13);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        pushButton_save_S1 = new QPushButton(centralwidget);
        pushButton_save_S1->setObjectName("pushButton_save_S1");

        horizontalLayout_12->addWidget(pushButton_save_S1);


        verticalLayout_sens_2->addLayout(horizontalLayout_12);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        label_name_S1 = new QLabel(centralwidget);
        label_name_S1->setObjectName("label_name_S1");

        horizontalLayout_11->addWidget(label_name_S1);


        verticalLayout_sens_2->addLayout(horizontalLayout_11);


        horizontalLayout_4->addLayout(verticalLayout_sens_2);

        line_7 = new QFrame(centralwidget);
        line_7->setObjectName("line_7");
        line_7->setFrameShape(QFrame::Shape::VLine);
        line_7->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_4->addWidget(line_7);

        line_8 = new QFrame(centralwidget);
        line_8->setObjectName("line_8");
        line_8->setFrameShape(QFrame::Shape::VLine);
        line_8->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_4->addWidget(line_8);

        verticalLayout_sens_3 = new QVBoxLayout();
        verticalLayout_sens_3->setObjectName("verticalLayout_sens_3");
        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName("horizontalLayout_23");
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");

        horizontalLayout_23->addWidget(label_5);

        label_current_S2 = new QLabel(centralwidget);
        label_current_S2->setObjectName("label_current_S2");

        horizontalLayout_23->addWidget(label_current_S2);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");

        horizontalLayout_23->addWidget(label_6);

        label_average_S2 = new QLabel(centralwidget);
        label_average_S2->setObjectName("label_average_S2");

        horizontalLayout_23->addWidget(label_average_S2);


        verticalLayout_sens_3->addLayout(horizontalLayout_23);

        line_6 = new QFrame(centralwidget);
        line_6->setObjectName("line_6");
        line_6->setFrameShape(QFrame::Shape::HLine);
        line_6->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_sens_3->addWidget(line_6);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setObjectName("horizontalLayout_22");
        lineEdit_full_S2 = new QLineEdit(centralwidget);
        lineEdit_full_S2->setObjectName("lineEdit_full_S2");

        horizontalLayout_22->addWidget(lineEdit_full_S2);

        label_full_S2 = new QLabel(centralwidget);
        label_full_S2->setObjectName("label_full_S2");

        horizontalLayout_22->addWidget(label_full_S2);

        pushButton_set_S2 = new QPushButton(centralwidget);
        pushButton_set_S2->setObjectName("pushButton_set_S2");

        horizontalLayout_22->addWidget(pushButton_set_S2);


        verticalLayout_sens_3->addLayout(horizontalLayout_22);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName("horizontalLayout_21");
        verticalSlider_S2 = new QSlider(centralwidget);
        verticalSlider_S2->setObjectName("verticalSlider_S2");
        verticalSlider_S2->setMinimumSize(QSize(100, 0));
        verticalSlider_S2->setOrientation(Qt::Vertical);

        horizontalLayout_21->addWidget(verticalSlider_S2);


        verticalLayout_sens_3->addLayout(horizontalLayout_21);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName("horizontalLayout_20");
        lineEdit_empty_S2 = new QLineEdit(centralwidget);
        lineEdit_empty_S2->setObjectName("lineEdit_empty_S2");

        horizontalLayout_20->addWidget(lineEdit_empty_S2);

        label_empty_S2 = new QLabel(centralwidget);
        label_empty_S2->setObjectName("label_empty_S2");

        horizontalLayout_20->addWidget(label_empty_S2);

        pushButton_set_empty_s2 = new QPushButton(centralwidget);
        pushButton_set_empty_s2->setObjectName("pushButton_set_empty_s2");

        horizontalLayout_20->addWidget(pushButton_set_empty_s2);


        verticalLayout_sens_3->addLayout(horizontalLayout_20);

        pushButton_save_S2 = new QPushButton(centralwidget);
        pushButton_save_S2->setObjectName("pushButton_save_S2");

        verticalLayout_sens_3->addWidget(pushButton_save_S2);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName("horizontalLayout_18");
        label_name_S2 = new QLabel(centralwidget);
        label_name_S2->setObjectName("label_name_S2");

        horizontalLayout_18->addWidget(label_name_S2);


        verticalLayout_sens_3->addLayout(horizontalLayout_18);


        horizontalLayout_4->addLayout(verticalLayout_sens_3);

        Rs232->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Rs232);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1413, 25));
        Rs232->setMenuBar(menubar);
        statusbar = new QStatusBar(Rs232);
        statusbar->setObjectName("statusbar");
        Rs232->setStatusBar(statusbar);

        retranslateUi(Rs232);

        QMetaObject::connectSlotsByName(Rs232);
    } // setupUi

    void retranslateUi(QMainWindow *Rs232)
    {
        Rs232->setWindowTitle(QCoreApplication::translate("Rs232", "MainWindow", nullptr));
        label_chart_info->setText(QCoreApplication::translate("Rs232", "TextLabel", nullptr));
        label_statuss->setText(QCoreApplication::translate("Rs232", "Ierakstu", nullptr));
        pushButtonStart->setText(QCoreApplication::translate("Rs232", "S\304\201kt", nullptr));
        pushButton_Stop->setText(QCoreApplication::translate("Rs232", "Beigt", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Rs232", "Laika ieda\304\274as v\304\223rt\304\253ba", nullptr));
        pushButton_1s->setText(QCoreApplication::translate("Rs232", "1 s", nullptr));
        pushButton_10s->setText(QCoreApplication::translate("Rs232", "10 s", nullptr));
        pushButton_60s->setText(QCoreApplication::translate("Rs232", "60 s", nullptr));
        pushButton_Save->setText(QCoreApplication::translate("Rs232", "Izveidot failu", nullptr));
        label->setText(QCoreApplication::translate("Rs232", "v\304\223rt\304\253ba", nullptr));
        label_current_S0->setText(QString());
        label_2->setText(QCoreApplication::translate("Rs232", "Vid\304\223j\304\201", nullptr));
        label_average_S0->setText(QString());
        label_full_S0->setText(QCoreApplication::translate("Rs232", "Full", nullptr));
        pushButton_set_S0->setText(QCoreApplication::translate("Rs232", "Iestat\304\253t", nullptr));
        label_empty_S0->setText(QCoreApplication::translate("Rs232", "Empty", nullptr));
        pushButton_set_empty_s0->setText(QCoreApplication::translate("Rs232", "Iestat\304\253t", nullptr));
        pushButton_save_S0->setText(QCoreApplication::translate("Rs232", "Saglab\304\201t", nullptr));
        label_name_S0->setText(QCoreApplication::translate("Rs232", "Sensor Name", nullptr));
        label_3->setText(QCoreApplication::translate("Rs232", "v\304\223rt\304\253ba", nullptr));
        label_current_S1->setText(QString());
        label_4->setText(QCoreApplication::translate("Rs232", "Vid\304\223j\304\201", nullptr));
        label_average_S1->setText(QString());
        label_full_S1->setText(QCoreApplication::translate("Rs232", "Full", nullptr));
        pushButton_set_S1->setText(QCoreApplication::translate("Rs232", "Iestat\304\253t", nullptr));
        label_empty_S1->setText(QCoreApplication::translate("Rs232", "Empty", nullptr));
        pushButton_set_empty_s1->setText(QCoreApplication::translate("Rs232", "Iestat\304\253t", nullptr));
        pushButton_save_S1->setText(QCoreApplication::translate("Rs232", "Saglab\304\201t", nullptr));
        label_name_S1->setText(QCoreApplication::translate("Rs232", "Sensor Name", nullptr));
        label_5->setText(QCoreApplication::translate("Rs232", "v\304\223rt\304\253ba", nullptr));
        label_current_S2->setText(QString());
        label_6->setText(QCoreApplication::translate("Rs232", "Vid\304\223j\304\201", nullptr));
        label_average_S2->setText(QString());
        label_full_S2->setText(QCoreApplication::translate("Rs232", "Full", nullptr));
        pushButton_set_S2->setText(QCoreApplication::translate("Rs232", "Iestat\304\253t", nullptr));
        label_empty_S2->setText(QCoreApplication::translate("Rs232", "Empty", nullptr));
        pushButton_set_empty_s2->setText(QCoreApplication::translate("Rs232", "Iestat\304\253t", nullptr));
        pushButton_save_S2->setText(QCoreApplication::translate("Rs232", "Saglab\304\201t", nullptr));
        label_name_S2->setText(QCoreApplication::translate("Rs232", "Sensor Name", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Rs232: public Ui_Rs232 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RS232_H
