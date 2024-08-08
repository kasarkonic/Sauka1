/********************************************************************************
** Form generated from reading UI file 'scale.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCALE_H
#define UI_SCALE_H

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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Scale
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_11;
    QLabel *label;
    QLineEdit *lineEdit_Send;
    QSpacerItem *horizontalSpacer_12;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_14;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_20;
    QLabel *label_Receive;
    QSpacerItem *horizontalSpacer_13;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_15;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_19;
    QLabel *label_Value;
    QSpacerItem *horizontalSpacer_16;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer_17;
    QLabel *label_Stat1;
    QSpacerItem *horizontalSpacer_18;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_21;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_Stat2;
    QSpacerItem *horizontalSpacer_22;
    QFrame *line;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Read;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_Tare;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *pushButton_Zero;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton_cont_reading;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_14;
    QFrame *line_3;
    QVBoxLayout *verticalLayout_3;
    QSlider *verticalSlider;
    QFrame *line_2;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Scale)
    {
        if (Scale->objectName().isEmpty())
            Scale->setObjectName("Scale");
        Scale->resize(800, 600);
        centralwidget = new QWidget(Scale);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_4 = new QVBoxLayout(centralwidget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_11);

        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout_10->addWidget(label);

        lineEdit_Send = new QLineEdit(centralwidget);
        lineEdit_Send->setObjectName("lineEdit_Send");

        horizontalLayout_10->addWidget(lineEdit_Send);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_12);


        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_14);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        horizontalLayout_9->addWidget(label_4);

        horizontalSpacer_20 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_20);

        label_Receive = new QLabel(centralwidget);
        label_Receive->setObjectName("label_Receive");

        horizontalLayout_9->addWidget(label_Receive);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_13);


        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_15);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        horizontalLayout_8->addWidget(label_3);

        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_19);

        label_Value = new QLabel(centralwidget);
        label_Value->setObjectName("label_Value");

        horizontalLayout_8->addWidget(label_Value);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_16);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_7);

        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");

        horizontalLayout_12->addWidget(label_8);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_17);

        label_Stat1 = new QLabel(centralwidget);
        label_Stat1->setObjectName("label_Stat1");

        horizontalLayout_12->addWidget(label_Stat1);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_18);


        verticalLayout->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        horizontalSpacer_21 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_21);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");

        horizontalLayout_13->addWidget(label_6);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_8);

        label_Stat2 = new QLabel(centralwidget);
        label_Stat2->setObjectName("label_Stat2");

        horizontalLayout_13->addWidget(label_Stat2);

        horizontalSpacer_22 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_22);


        verticalLayout->addLayout(horizontalLayout_13);

        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line);

        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(3, 1);
        verticalLayout->setStretch(4, 1);

        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        pushButton_Read = new QPushButton(centralwidget);
        pushButton_Read->setObjectName("pushButton_Read");

        horizontalLayout_6->addWidget(pushButton_Read);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        pushButton_Tare = new QPushButton(centralwidget);
        pushButton_Tare->setObjectName("pushButton_Tare");

        horizontalLayout_5->addWidget(pushButton_Tare);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_10);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_9);

        pushButton_Zero = new QPushButton(centralwidget);
        pushButton_Zero->setObjectName("pushButton_Zero");

        horizontalLayout_4->addWidget(pushButton_Zero);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        pushButton_cont_reading = new QPushButton(centralwidget);
        pushButton_cont_reading->setObjectName("pushButton_cont_reading");

        horizontalLayout_3->addWidget(pushButton_cont_reading);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName("horizontalLayout_14");

        verticalLayout_2->addLayout(horizontalLayout_14);

        line_3 = new QFrame(centralwidget);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::Shape::HLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_2->addWidget(line_3);

        verticalLayout_2->setStretch(1, 1);
        verticalLayout_2->setStretch(2, 1);
        verticalLayout_2->setStretch(3, 1);
        verticalLayout_2->setStretch(4, 1);

        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalSlider = new QSlider(centralwidget);
        verticalSlider->setObjectName("verticalSlider");
        verticalSlider->setOrientation(Qt::Vertical);

        verticalLayout_3->addWidget(verticalSlider);


        horizontalLayout->addLayout(verticalLayout_3);

        horizontalLayout->setStretch(0, 10);
        horizontalLayout->setStretch(1, 10);
        horizontalLayout->setStretch(2, 2);

        verticalLayout_4->addLayout(horizontalLayout);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_4->addWidget(line_2);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");

        verticalLayout_5->addWidget(label_5);


        verticalLayout_4->addLayout(verticalLayout_5);

        verticalLayout_4->setStretch(0, 2);
        verticalLayout_4->setStretch(1, 1);
        verticalLayout_4->setStretch(2, 5);
        Scale->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Scale);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        Scale->setMenuBar(menubar);
        statusbar = new QStatusBar(Scale);
        statusbar->setObjectName("statusbar");
        Scale->setStatusBar(statusbar);

        retranslateUi(Scale);

        QMetaObject::connectSlotsByName(Scale);
    } // setupUi

    void retranslateUi(QMainWindow *Scale)
    {
        Scale->setWindowTitle(QCoreApplication::translate("Scale", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("Scale", "Send", nullptr));
        label_4->setText(QCoreApplication::translate("Scale", "Receive strings:", nullptr));
        label_Receive->setText(QCoreApplication::translate("Scale", "TextLabel", nullptr));
        label_3->setText(QCoreApplication::translate("Scale", "Value", nullptr));
        label_Value->setText(QCoreApplication::translate("Scale", "Value", nullptr));
        label_8->setText(QCoreApplication::translate("Scale", "Status", nullptr));
        label_Stat1->setText(QCoreApplication::translate("Scale", "-", nullptr));
        label_6->setText(QCoreApplication::translate("Scale", "Status", nullptr));
        label_Stat2->setText(QCoreApplication::translate("Scale", "-", nullptr));
        pushButton_Read->setText(QCoreApplication::translate("Scale", "READ", nullptr));
        pushButton_Tare->setText(QCoreApplication::translate("Scale", "TARE", nullptr));
        pushButton_Zero->setText(QCoreApplication::translate("Scale", "ZERO", nullptr));
        pushButton_cont_reading->setText(QCoreApplication::translate("Scale", "Repeat reading", nullptr));
        label_5->setText(QCoreApplication::translate("Scale", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Scale: public Ui_Scale {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCALE_H
