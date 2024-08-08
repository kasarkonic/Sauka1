/********************************************************************************
** Form generated from reading UI file 'hwports.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HWPORTS_H
#define UI_HWPORTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HwPorts
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Update;
    QPushButton *pushButton_Save;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_3;
    QGridLayout *gridLayout;
    QLabel *label_23;
    QLabel *label_6;
    QComboBox *comboBox_R3;
    QLabel *label_R4_pr_nr;
    QLabel *label_22;
    QLabel *label_R3_pr_nr;
    QLabel *label_R2_vend;
    QLabel *label_R1_desc;
    QLabel *label_R1_port;
    QLabel *label_R1_vend;
    QLabel *label_18;
    QLabel *label_R4_ser;
    QLabel *label_R2_pr_nr;
    QLabel *label_R2_stat;
    QLabel *label_4;
    QLabel *label_R3_ser;
    QLabel *label_8;
    QLabel *label_R2_desc;
    QLabel *label_R2_ser;
    QLabel *label_30;
    QLabel *label_5;
    QLabel *label;
    QLabel *label_R1_man;
    QLabel *label_R4_stat;
    QLabel *label_R3_desc;
    QLabel *label_R2_port;
    QComboBox *comboBox_R2;
    QFrame *line_4;
    QLabel *label_R4_man;
    QLabel *label_R2_man;
    QComboBox *comboBox_R1;
    QLabel *label_R3_vend;
    QLabel *label_R1_pr_nr;
    QLabel *label_7;
    QLabel *label_R3_port;
    QLabel *label_R3_man;
    QLabel *label_R4_vend;
    QLabel *label_R4_port;
    QLabel *label_R3_stat;
    QLabel *label_R1_ser;
    QLabel *label_29;
    QLabel *label_11;
    QLabel *label_35;
    QComboBox *comboBox_R4;
    QLabel *label_R1_stat;
    QLabel *label_R4_desc;
    QFrame *line;
    QFrame *line_3;
    QFrame *line_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *textEditInfo;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *HwPorts)
    {
        if (HwPorts->objectName().isEmpty())
            HwPorts->setObjectName("HwPorts");
        HwPorts->resize(816, 583);
        centralwidget = new QWidget(HwPorts);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_4 = new QVBoxLayout(centralwidget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton_Update = new QPushButton(centralwidget);
        pushButton_Update->setObjectName("pushButton_Update");

        horizontalLayout_2->addWidget(pushButton_Update);

        pushButton_Save = new QPushButton(centralwidget);
        pushButton_Save->setObjectName("pushButton_Save");

        horizontalLayout_2->addWidget(pushButton_Save);


        verticalLayout_4->addLayout(horizontalLayout_2);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");

        verticalLayout_5->addWidget(label_9);


        verticalLayout_4->addLayout(verticalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label_23 = new QLabel(centralwidget);
        label_23->setObjectName("label_23");

        gridLayout->addWidget(label_23, 0, 6, 1, 1);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 0, 0, 1, 1);

        comboBox_R3 = new QComboBox(centralwidget);
        comboBox_R3->setObjectName("comboBox_R3");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(5);
        sizePolicy.setVerticalStretch(5);
        sizePolicy.setHeightForWidth(comboBox_R3->sizePolicy().hasHeightForWidth());
        comboBox_R3->setSizePolicy(sizePolicy);
        comboBox_R3->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(comboBox_R3, 4, 8, 1, 1);

        label_R4_pr_nr = new QLabel(centralwidget);
        label_R4_pr_nr->setObjectName("label_R4_pr_nr");

        gridLayout->addWidget(label_R4_pr_nr, 5, 6, 1, 1);

        label_22 = new QLabel(centralwidget);
        label_22->setObjectName("label_22");

        gridLayout->addWidget(label_22, 0, 3, 1, 1);

        label_R3_pr_nr = new QLabel(centralwidget);
        label_R3_pr_nr->setObjectName("label_R3_pr_nr");

        gridLayout->addWidget(label_R3_pr_nr, 4, 6, 1, 1);

        label_R2_vend = new QLabel(centralwidget);
        label_R2_vend->setObjectName("label_R2_vend");

        gridLayout->addWidget(label_R2_vend, 3, 5, 1, 1);

        label_R1_desc = new QLabel(centralwidget);
        label_R1_desc->setObjectName("label_R1_desc");

        gridLayout->addWidget(label_R1_desc, 2, 2, 1, 1);

        label_R1_port = new QLabel(centralwidget);
        label_R1_port->setObjectName("label_R1_port");

        gridLayout->addWidget(label_R1_port, 2, 1, 1, 1);

        label_R1_vend = new QLabel(centralwidget);
        label_R1_vend->setObjectName("label_R1_vend");

        gridLayout->addWidget(label_R1_vend, 2, 5, 1, 1);

        label_18 = new QLabel(centralwidget);
        label_18->setObjectName("label_18");

        gridLayout->addWidget(label_18, 0, 2, 1, 1);

        label_R4_ser = new QLabel(centralwidget);
        label_R4_ser->setObjectName("label_R4_ser");

        gridLayout->addWidget(label_R4_ser, 5, 4, 1, 1);

        label_R2_pr_nr = new QLabel(centralwidget);
        label_R2_pr_nr->setObjectName("label_R2_pr_nr");

        gridLayout->addWidget(label_R2_pr_nr, 3, 6, 1, 1);

        label_R2_stat = new QLabel(centralwidget);
        label_R2_stat->setObjectName("label_R2_stat");

        gridLayout->addWidget(label_R2_stat, 3, 7, 1, 1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        label_R3_ser = new QLabel(centralwidget);
        label_R3_ser->setObjectName("label_R3_ser");

        gridLayout->addWidget(label_R3_ser, 4, 4, 1, 1);

        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_8, 0, 8, 1, 1);

        label_R2_desc = new QLabel(centralwidget);
        label_R2_desc->setObjectName("label_R2_desc");

        gridLayout->addWidget(label_R2_desc, 3, 2, 1, 1);

        label_R2_ser = new QLabel(centralwidget);
        label_R2_ser->setObjectName("label_R2_ser");

        gridLayout->addWidget(label_R2_ser, 3, 4, 1, 1);

        label_30 = new QLabel(centralwidget);
        label_30->setObjectName("label_30");

        gridLayout->addWidget(label_30, 0, 5, 1, 1);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName("label");

        gridLayout->addWidget(label, 5, 0, 1, 1);

        label_R1_man = new QLabel(centralwidget);
        label_R1_man->setObjectName("label_R1_man");

        gridLayout->addWidget(label_R1_man, 2, 3, 1, 1);

        label_R4_stat = new QLabel(centralwidget);
        label_R4_stat->setObjectName("label_R4_stat");

        gridLayout->addWidget(label_R4_stat, 5, 7, 1, 1);

        label_R3_desc = new QLabel(centralwidget);
        label_R3_desc->setObjectName("label_R3_desc");

        gridLayout->addWidget(label_R3_desc, 4, 2, 1, 1);

        label_R2_port = new QLabel(centralwidget);
        label_R2_port->setObjectName("label_R2_port");

        gridLayout->addWidget(label_R2_port, 3, 1, 1, 1);

        comboBox_R2 = new QComboBox(centralwidget);
        comboBox_R2->setObjectName("comboBox_R2");
        sizePolicy.setHeightForWidth(comboBox_R2->sizePolicy().hasHeightForWidth());
        comboBox_R2->setSizePolicy(sizePolicy);
        comboBox_R2->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(comboBox_R2, 3, 8, 1, 1);

        line_4 = new QFrame(centralwidget);
        line_4->setObjectName("line_4");
        line_4->setFrameShape(QFrame::Shape::HLine);
        line_4->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout->addWidget(line_4, 1, 0, 1, 9);

        label_R4_man = new QLabel(centralwidget);
        label_R4_man->setObjectName("label_R4_man");

        gridLayout->addWidget(label_R4_man, 5, 3, 1, 1);

        label_R2_man = new QLabel(centralwidget);
        label_R2_man->setObjectName("label_R2_man");

        gridLayout->addWidget(label_R2_man, 3, 3, 1, 1);

        comboBox_R1 = new QComboBox(centralwidget);
        comboBox_R1->setObjectName("comboBox_R1");
        sizePolicy.setHeightForWidth(comboBox_R1->sizePolicy().hasHeightForWidth());
        comboBox_R1->setSizePolicy(sizePolicy);
        comboBox_R1->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(comboBox_R1, 2, 8, 1, 1);

        label_R3_vend = new QLabel(centralwidget);
        label_R3_vend->setObjectName("label_R3_vend");

        gridLayout->addWidget(label_R3_vend, 4, 5, 1, 1);

        label_R1_pr_nr = new QLabel(centralwidget);
        label_R1_pr_nr->setObjectName("label_R1_pr_nr");

        gridLayout->addWidget(label_R1_pr_nr, 2, 6, 1, 1);

        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");

        gridLayout->addWidget(label_7, 0, 7, 1, 1);

        label_R3_port = new QLabel(centralwidget);
        label_R3_port->setObjectName("label_R3_port");

        gridLayout->addWidget(label_R3_port, 4, 1, 1, 1);

        label_R3_man = new QLabel(centralwidget);
        label_R3_man->setObjectName("label_R3_man");

        gridLayout->addWidget(label_R3_man, 4, 3, 1, 1);

        label_R4_vend = new QLabel(centralwidget);
        label_R4_vend->setObjectName("label_R4_vend");

        gridLayout->addWidget(label_R4_vend, 5, 5, 1, 1);

        label_R4_port = new QLabel(centralwidget);
        label_R4_port->setObjectName("label_R4_port");

        gridLayout->addWidget(label_R4_port, 5, 1, 1, 1);

        label_R3_stat = new QLabel(centralwidget);
        label_R3_stat->setObjectName("label_R3_stat");

        gridLayout->addWidget(label_R3_stat, 4, 7, 1, 1);

        label_R1_ser = new QLabel(centralwidget);
        label_R1_ser->setObjectName("label_R1_ser");

        gridLayout->addWidget(label_R1_ser, 2, 4, 1, 1);

        label_29 = new QLabel(centralwidget);
        label_29->setObjectName("label_29");

        gridLayout->addWidget(label_29, 0, 4, 1, 1);

        label_11 = new QLabel(centralwidget);
        label_11->setObjectName("label_11");

        gridLayout->addWidget(label_11, 0, 1, 1, 1);

        label_35 = new QLabel(centralwidget);
        label_35->setObjectName("label_35");

        gridLayout->addWidget(label_35, 2, 0, 1, 1);

        comboBox_R4 = new QComboBox(centralwidget);
        comboBox_R4->setObjectName("comboBox_R4");
        sizePolicy.setHeightForWidth(comboBox_R4->sizePolicy().hasHeightForWidth());
        comboBox_R4->setSizePolicy(sizePolicy);
        comboBox_R4->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(comboBox_R4, 5, 8, 1, 1);

        label_R1_stat = new QLabel(centralwidget);
        label_R1_stat->setObjectName("label_R1_stat");

        gridLayout->addWidget(label_R1_stat, 2, 7, 1, 1);

        label_R4_desc = new QLabel(centralwidget);
        label_R4_desc->setObjectName("label_R4_desc");

        gridLayout->addWidget(label_R4_desc, 5, 2, 1, 1);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setColumnStretch(0, 5);

        horizontalLayout_3->addLayout(gridLayout);

        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_3->addWidget(line);

        line_3 = new QFrame(centralwidget);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::Shape::VLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_3->addWidget(line_3);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_3->addWidget(line_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_3->addLayout(verticalLayout);


        verticalLayout_4->addLayout(horizontalLayout_3);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        textEditInfo = new QTextEdit(centralwidget);
        textEditInfo->setObjectName("textEditInfo");

        verticalLayout_3->addWidget(textEditInfo);


        verticalLayout_4->addLayout(verticalLayout_3);

        verticalLayout_4->setStretch(0, 1);
        verticalLayout_4->setStretch(2, 10);
        verticalLayout_4->setStretch(3, 5);
        HwPorts->setCentralWidget(centralwidget);
        menubar = new QMenuBar(HwPorts);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 816, 21));
        HwPorts->setMenuBar(menubar);
        statusbar = new QStatusBar(HwPorts);
        statusbar->setObjectName("statusbar");
        HwPorts->setStatusBar(statusbar);

        retranslateUi(HwPorts);

        QMetaObject::connectSlotsByName(HwPorts);
    } // setupUi

    void retranslateUi(QMainWindow *HwPorts)
    {
        HwPorts->setWindowTitle(QCoreApplication::translate("HwPorts", "MainWindow", nullptr));
        label_2->setText(QCoreApplication::translate("HwPorts", "Com port manager", nullptr));
        pushButton_Update->setText(QCoreApplication::translate("HwPorts", "Update", nullptr));
        pushButton_Save->setText(QCoreApplication::translate("HwPorts", "Save", nullptr));
        label_9->setText(QCoreApplication::translate("HwPorts", "For uto select port : use vendor id", nullptr));
        label_23->setText(QCoreApplication::translate("HwPorts", "Product nr.", nullptr));
        label_6->setText(QCoreApplication::translate("HwPorts", "Device Name", nullptr));
        label_R4_pr_nr->setText(QString());
        label_22->setText(QCoreApplication::translate("HwPorts", "Manufacturer", nullptr));
        label_R3_pr_nr->setText(QString());
        label_R2_vend->setText(QString());
        label_R1_desc->setText(QString());
        label_R1_port->setText(QString());
        label_R1_vend->setText(QString());
        label_18->setText(QCoreApplication::translate("HwPorts", "Description", nullptr));
        label_R4_ser->setText(QString());
        label_R2_pr_nr->setText(QString());
        label_R2_stat->setText(QString());
        label_4->setText(QCoreApplication::translate("HwPorts", "RS485   boards.", nullptr));
        label_R3_ser->setText(QString());
        label_8->setText(QCoreApplication::translate("HwPorts", "Select", nullptr));
        label_R2_desc->setText(QString());
        label_R2_ser->setText(QString());
        label_30->setText(QCoreApplication::translate("HwPorts", "Vendor Id", nullptr));
        label_5->setText(QCoreApplication::translate("HwPorts", "Scales", nullptr));
        label->setText(QCoreApplication::translate("HwPorts", "Motors", nullptr));
        label_R1_man->setText(QString());
        label_R4_stat->setText(QString());
        label_R3_desc->setText(QString());
        label_R2_port->setText(QString());
        label_R4_man->setText(QString());
        label_R2_man->setText(QString());
        label_R3_vend->setText(QString());
        label_R1_pr_nr->setText(QString());
        label_7->setText(QCoreApplication::translate("HwPorts", "Status", nullptr));
        label_R3_port->setText(QString());
        label_R3_man->setText(QString());
        label_R4_vend->setText(QString());
        label_R4_port->setText(QString());
        label_R3_stat->setText(QString());
        label_R1_ser->setText(QString());
        label_29->setText(QCoreApplication::translate("HwPorts", "Serial nr.", nullptr));
        label_11->setText(QCoreApplication::translate("HwPorts", "Port Nr", nullptr));
        label_35->setText(QCoreApplication::translate("HwPorts", "Temperature, level sensors", nullptr));
        label_R1_stat->setText(QString());
        label_R4_desc->setText(QString());
        label_3->setText(QCoreApplication::translate("HwPorts", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HwPorts: public Ui_HwPorts {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HWPORTS_H
