/********************************************************************************
** Form generated from reading UI file 'widgetservice.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETSERVICE_H
#define UI_WIDGETSERVICE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetService
{
public:
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *labelName;
    QPushButton *pushButton;
    QFrame *line_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_0_1;
    QFrame *line_8;
    QFrame *line_10;
    QLabel *label_0_2;
    QFrame *line_11;
    QFrame *line_9;
    QLabel *label_0_3;
    QFrame *line_13;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_12;
    QLabel *label1_1;
    QLabel *label2_1;
    QLabel *label3_1;
    QLabel *label4_1;
    QFrame *line_6;
    QFrame *line;
    QVBoxLayout *verticalLayout_2;
    QLabel *label1_2;
    QLabel *label2_2;
    QLabel *label3_2;
    QLabel *label4_2;
    QFrame *line_2;
    QFrame *line_7;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_16;
    QLabel *label1_3;
    QLabel *label2_3;
    QLabel *label3_3;
    QLabel *label4_3;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label5_1;
    QFrame *line_15;
    QFrame *line_14;
    QLineEdit *lineEdit_5_2;
    QFrame *line_16;
    QFrame *line_17;
    QPushButton *pushButton_5_3;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label6_1;
    QFrame *line_18;
    QFrame *line_19;
    QLineEdit *lineEdit_6_2;
    QFrame *line_20;
    QFrame *line_21;
    QPushButton *pushButton_6_3;
    QSlider *horizontalSlider_speed;
    QFrame *line_4;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_Notes;
    QFrame *line_12;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_3;
    QFrame *line_3;
    QLineEdit *lineEdit_Xpos;
    QPushButton *pushButton_Xplus;
    QPushButton *pushButton_Xminus;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_4;
    QLineEdit *lineEdit_Ypos;
    QPushButton *pushButton_Yplus;
    QPushButton *pushButton_Yminus;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_5;
    QLineEdit *lineEdit_startSize;
    QPushButton *pushButton_sizeplus;
    QPushButton *pushButton_sizeMinus;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_7;
    QLineEdit *lineEdit_options;
    QPushButton *pushButton_OptionsPlus;
    QPushButton *pushButton_OptionsMinus;
    QHBoxLayout *horizontalLayout_8;

    void setupUi(QWidget *WidgetService)
    {
        if (WidgetService->objectName().isEmpty())
            WidgetService->setObjectName("WidgetService");
        WidgetService->resize(375, 533);
        verticalLayout_4 = new QVBoxLayout(WidgetService);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        labelName = new QLabel(WidgetService);
        labelName->setObjectName("labelName");

        horizontalLayout->addWidget(labelName);

        pushButton = new QPushButton(WidgetService);
        pushButton->setObjectName("pushButton");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setIconSize(QSize(16, 28));

        horizontalLayout->addWidget(pushButton);


        verticalLayout_3->addLayout(horizontalLayout);


        verticalLayout_4->addLayout(verticalLayout_3);

        line_5 = new QFrame(WidgetService);
        line_5->setObjectName("line_5");
        line_5->setFrameShape(QFrame::Shape::HLine);
        line_5->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_4->addWidget(line_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_0_1 = new QLabel(WidgetService);
        label_0_1->setObjectName("label_0_1");

        horizontalLayout_4->addWidget(label_0_1);

        line_8 = new QFrame(WidgetService);
        line_8->setObjectName("line_8");
        line_8->setFrameShape(QFrame::Shape::VLine);
        line_8->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_4->addWidget(line_8);

        line_10 = new QFrame(WidgetService);
        line_10->setObjectName("line_10");
        line_10->setFrameShape(QFrame::Shape::VLine);
        line_10->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_4->addWidget(line_10);

        label_0_2 = new QLabel(WidgetService);
        label_0_2->setObjectName("label_0_2");

        horizontalLayout_4->addWidget(label_0_2);

        line_11 = new QFrame(WidgetService);
        line_11->setObjectName("line_11");
        line_11->setFrameShape(QFrame::Shape::VLine);
        line_11->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_4->addWidget(line_11);

        line_9 = new QFrame(WidgetService);
        line_9->setObjectName("line_9");
        line_9->setFrameShape(QFrame::Shape::VLine);
        line_9->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_4->addWidget(line_9);

        label_0_3 = new QLabel(WidgetService);
        label_0_3->setObjectName("label_0_3");

        horizontalLayout_4->addWidget(label_0_3);


        verticalLayout_4->addLayout(horizontalLayout_4);

        line_13 = new QFrame(WidgetService);
        line_13->setObjectName("line_13");
        line_13->setFrameShape(QFrame::Shape::HLine);
        line_13->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_4->addWidget(line_13);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName("verticalLayout_12");
        label1_1 = new QLabel(WidgetService);
        label1_1->setObjectName("label1_1");

        verticalLayout_12->addWidget(label1_1);

        label2_1 = new QLabel(WidgetService);
        label2_1->setObjectName("label2_1");

        verticalLayout_12->addWidget(label2_1);

        label3_1 = new QLabel(WidgetService);
        label3_1->setObjectName("label3_1");

        verticalLayout_12->addWidget(label3_1);

        label4_1 = new QLabel(WidgetService);
        label4_1->setObjectName("label4_1");

        verticalLayout_12->addWidget(label4_1);


        horizontalLayout_5->addLayout(verticalLayout_12);


        horizontalLayout_2->addLayout(horizontalLayout_5);

        line_6 = new QFrame(WidgetService);
        line_6->setObjectName("line_6");
        line_6->setFrameShape(QFrame::Shape::VLine);
        line_6->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_2->addWidget(line_6);

        line = new QFrame(WidgetService);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_2->addWidget(line);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label1_2 = new QLabel(WidgetService);
        label1_2->setObjectName("label1_2");

        verticalLayout_2->addWidget(label1_2);

        label2_2 = new QLabel(WidgetService);
        label2_2->setObjectName("label2_2");

        verticalLayout_2->addWidget(label2_2);

        label3_2 = new QLabel(WidgetService);
        label3_2->setObjectName("label3_2");

        verticalLayout_2->addWidget(label3_2);

        label4_2 = new QLabel(WidgetService);
        label4_2->setObjectName("label4_2");

        verticalLayout_2->addWidget(label4_2);


        horizontalLayout_2->addLayout(verticalLayout_2);

        line_2 = new QFrame(WidgetService);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_2->addWidget(line_2);

        line_7 = new QFrame(WidgetService);
        line_7->setObjectName("line_7");
        line_7->setFrameShape(QFrame::Shape::VLine);
        line_7->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_2->addWidget(line_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setObjectName("verticalLayout_16");
        label1_3 = new QLabel(WidgetService);
        label1_3->setObjectName("label1_3");

        verticalLayout_16->addWidget(label1_3);

        label2_3 = new QLabel(WidgetService);
        label2_3->setObjectName("label2_3");

        verticalLayout_16->addWidget(label2_3);

        label3_3 = new QLabel(WidgetService);
        label3_3->setObjectName("label3_3");

        verticalLayout_16->addWidget(label3_3);

        label4_3 = new QLabel(WidgetService);
        label4_3->setObjectName("label4_3");

        verticalLayout_16->addWidget(label4_3);


        horizontalLayout_6->addLayout(verticalLayout_16);


        horizontalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_2->setStretch(0, 5);
        horizontalLayout_2->setStretch(3, 5);
        horizontalLayout_2->setStretch(6, 5);

        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_4->addLayout(verticalLayout);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        label5_1 = new QLabel(WidgetService);
        label5_1->setObjectName("label5_1");

        horizontalLayout_11->addWidget(label5_1);

        line_15 = new QFrame(WidgetService);
        line_15->setObjectName("line_15");
        line_15->setFrameShape(QFrame::Shape::VLine);
        line_15->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_11->addWidget(line_15);

        line_14 = new QFrame(WidgetService);
        line_14->setObjectName("line_14");
        line_14->setFrameShape(QFrame::Shape::VLine);
        line_14->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_11->addWidget(line_14);

        lineEdit_5_2 = new QLineEdit(WidgetService);
        lineEdit_5_2->setObjectName("lineEdit_5_2");

        horizontalLayout_11->addWidget(lineEdit_5_2);

        line_16 = new QFrame(WidgetService);
        line_16->setObjectName("line_16");
        line_16->setFrameShape(QFrame::Shape::VLine);
        line_16->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_11->addWidget(line_16);

        line_17 = new QFrame(WidgetService);
        line_17->setObjectName("line_17");
        line_17->setFrameShape(QFrame::Shape::VLine);
        line_17->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_11->addWidget(line_17);

        pushButton_5_3 = new QPushButton(WidgetService);
        pushButton_5_3->setObjectName("pushButton_5_3");

        horizontalLayout_11->addWidget(pushButton_5_3);

        horizontalLayout_11->setStretch(0, 5);
        horizontalLayout_11->setStretch(3, 5);
        horizontalLayout_11->setStretch(6, 5);

        verticalLayout_4->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        label6_1 = new QLabel(WidgetService);
        label6_1->setObjectName("label6_1");

        horizontalLayout_12->addWidget(label6_1);

        line_18 = new QFrame(WidgetService);
        line_18->setObjectName("line_18");
        line_18->setFrameShape(QFrame::Shape::VLine);
        line_18->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_12->addWidget(line_18);

        line_19 = new QFrame(WidgetService);
        line_19->setObjectName("line_19");
        line_19->setFrameShape(QFrame::Shape::VLine);
        line_19->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_12->addWidget(line_19);

        lineEdit_6_2 = new QLineEdit(WidgetService);
        lineEdit_6_2->setObjectName("lineEdit_6_2");

        horizontalLayout_12->addWidget(lineEdit_6_2);

        line_20 = new QFrame(WidgetService);
        line_20->setObjectName("line_20");
        line_20->setFrameShape(QFrame::Shape::VLine);
        line_20->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_12->addWidget(line_20);

        line_21 = new QFrame(WidgetService);
        line_21->setObjectName("line_21");
        line_21->setFrameShape(QFrame::Shape::VLine);
        line_21->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_12->addWidget(line_21);

        pushButton_6_3 = new QPushButton(WidgetService);
        pushButton_6_3->setObjectName("pushButton_6_3");

        horizontalLayout_12->addWidget(pushButton_6_3);

        horizontalLayout_12->setStretch(0, 5);
        horizontalLayout_12->setStretch(3, 5);
        horizontalLayout_12->setStretch(6, 5);

        verticalLayout_4->addLayout(horizontalLayout_12);

        horizontalSlider_speed = new QSlider(WidgetService);
        horizontalSlider_speed->setObjectName("horizontalSlider_speed");
        horizontalSlider_speed->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(horizontalSlider_speed);

        line_4 = new QFrame(WidgetService);
        line_4->setObjectName("line_4");
        line_4->setFrameShape(QFrame::Shape::HLine);
        line_4->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_4->addWidget(line_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_Notes = new QLabel(WidgetService);
        label_Notes->setObjectName("label_Notes");
        label_Notes->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout_5->addWidget(label_Notes);


        verticalLayout_4->addLayout(verticalLayout_5);

        line_12 = new QFrame(WidgetService);
        line_12->setObjectName("line_12");
        line_12->setFrameShape(QFrame::Shape::HLine);
        line_12->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_4->addWidget(line_12);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName("verticalLayout_10");
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_3 = new QLabel(WidgetService);
        label_3->setObjectName("label_3");

        horizontalLayout_7->addWidget(label_3);

        line_3 = new QFrame(WidgetService);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::Shape::HLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_7->addWidget(line_3);

        lineEdit_Xpos = new QLineEdit(WidgetService);
        lineEdit_Xpos->setObjectName("lineEdit_Xpos");

        horizontalLayout_7->addWidget(lineEdit_Xpos);

        pushButton_Xplus = new QPushButton(WidgetService);
        pushButton_Xplus->setObjectName("pushButton_Xplus");
        pushButton_Xplus->setAutoRepeat(true);
        pushButton_Xplus->setAutoRepeatInterval(10);

        horizontalLayout_7->addWidget(pushButton_Xplus);

        pushButton_Xminus = new QPushButton(WidgetService);
        pushButton_Xminus->setObjectName("pushButton_Xminus");
        pushButton_Xminus->setAutoRepeat(true);
        pushButton_Xminus->setAutoRepeatInterval(10);

        horizontalLayout_7->addWidget(pushButton_Xminus);

        horizontalLayout_7->setStretch(0, 5);
        horizontalLayout_7->setStretch(2, 2);
        horizontalLayout_7->setStretch(3, 2);
        horizontalLayout_7->setStretch(4, 2);

        verticalLayout_10->addLayout(horizontalLayout_7);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        label_4 = new QLabel(WidgetService);
        label_4->setObjectName("label_4");

        horizontalLayout_10->addWidget(label_4);

        lineEdit_Ypos = new QLineEdit(WidgetService);
        lineEdit_Ypos->setObjectName("lineEdit_Ypos");

        horizontalLayout_10->addWidget(lineEdit_Ypos);

        pushButton_Yplus = new QPushButton(WidgetService);
        pushButton_Yplus->setObjectName("pushButton_Yplus");
        pushButton_Yplus->setAutoRepeat(true);
        pushButton_Yplus->setAutoRepeatInterval(10);

        horizontalLayout_10->addWidget(pushButton_Yplus);

        pushButton_Yminus = new QPushButton(WidgetService);
        pushButton_Yminus->setObjectName("pushButton_Yminus");
        pushButton_Yminus->setAutoRepeat(true);
        pushButton_Yminus->setAutoRepeatInterval(10);

        horizontalLayout_10->addWidget(pushButton_Yminus);

        horizontalLayout_10->setStretch(0, 5);
        horizontalLayout_10->setStretch(1, 2);
        horizontalLayout_10->setStretch(2, 2);
        horizontalLayout_10->setStretch(3, 2);

        verticalLayout_10->addLayout(horizontalLayout_10);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        label_5 = new QLabel(WidgetService);
        label_5->setObjectName("label_5");

        horizontalLayout_9->addWidget(label_5);

        lineEdit_startSize = new QLineEdit(WidgetService);
        lineEdit_startSize->setObjectName("lineEdit_startSize");

        horizontalLayout_9->addWidget(lineEdit_startSize);

        pushButton_sizeplus = new QPushButton(WidgetService);
        pushButton_sizeplus->setObjectName("pushButton_sizeplus");
        pushButton_sizeplus->setAutoRepeat(true);
        pushButton_sizeplus->setAutoRepeatInterval(10);

        horizontalLayout_9->addWidget(pushButton_sizeplus);

        pushButton_sizeMinus = new QPushButton(WidgetService);
        pushButton_sizeMinus->setObjectName("pushButton_sizeMinus");
        pushButton_sizeMinus->setAutoRepeat(true);
        pushButton_sizeMinus->setAutoRepeatInterval(10);

        horizontalLayout_9->addWidget(pushButton_sizeMinus);

        horizontalLayout_9->setStretch(0, 5);
        horizontalLayout_9->setStretch(1, 2);
        horizontalLayout_9->setStretch(2, 2);
        horizontalLayout_9->setStretch(3, 2);

        verticalLayout_10->addLayout(horizontalLayout_9);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_7 = new QLabel(WidgetService);
        label_7->setObjectName("label_7");

        horizontalLayout_3->addWidget(label_7);

        lineEdit_options = new QLineEdit(WidgetService);
        lineEdit_options->setObjectName("lineEdit_options");

        horizontalLayout_3->addWidget(lineEdit_options);

        pushButton_OptionsPlus = new QPushButton(WidgetService);
        pushButton_OptionsPlus->setObjectName("pushButton_OptionsPlus");
        pushButton_OptionsPlus->setAutoRepeat(true);
        pushButton_OptionsPlus->setAutoRepeatInterval(10);

        horizontalLayout_3->addWidget(pushButton_OptionsPlus);

        pushButton_OptionsMinus = new QPushButton(WidgetService);
        pushButton_OptionsMinus->setObjectName("pushButton_OptionsMinus");
        pushButton_OptionsMinus->setAutoRepeat(true);
        pushButton_OptionsMinus->setAutoRepeatInterval(10);

        horizontalLayout_3->addWidget(pushButton_OptionsMinus);

        horizontalLayout_3->setStretch(0, 5);
        horizontalLayout_3->setStretch(1, 2);
        horizontalLayout_3->setStretch(2, 2);
        horizontalLayout_3->setStretch(3, 2);

        verticalLayout_10->addLayout(horizontalLayout_3);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");

        verticalLayout_10->addLayout(horizontalLayout_8);


        verticalLayout_4->addLayout(verticalLayout_10);

        verticalLayout_4->setStretch(0, 1);
        verticalLayout_4->setStretch(4, 5);
        verticalLayout_4->setStretch(9, 3);
        verticalLayout_4->setStretch(11, 3);

        retranslateUi(WidgetService);

        QMetaObject::connectSlotsByName(WidgetService);
    } // setupUi

    void retranslateUi(QWidget *WidgetService)
    {
        WidgetService->setWindowTitle(QCoreApplication::translate("WidgetService", "Form", nullptr));
        labelName->setText(QCoreApplication::translate("WidgetService", "TextLabel", nullptr));
        pushButton->setText(QCoreApplication::translate("WidgetService", "EMERGENCY STOP", nullptr));
        label_0_1->setText(QCoreApplication::translate("WidgetService", "0.1", nullptr));
        label_0_2->setText(QCoreApplication::translate("WidgetService", "0.2", nullptr));
        label_0_3->setText(QCoreApplication::translate("WidgetService", "0.3", nullptr));
        label1_1->setText(QCoreApplication::translate("WidgetService", "1.1", nullptr));
        label2_1->setText(QCoreApplication::translate("WidgetService", "2.1", nullptr));
        label3_1->setText(QCoreApplication::translate("WidgetService", "3.1", nullptr));
        label4_1->setText(QCoreApplication::translate("WidgetService", "4.1", nullptr));
        label1_2->setText(QCoreApplication::translate("WidgetService", "1.2", nullptr));
        label2_2->setText(QCoreApplication::translate("WidgetService", "2.2", nullptr));
        label3_2->setText(QCoreApplication::translate("WidgetService", "3.2", nullptr));
        label4_2->setText(QCoreApplication::translate("WidgetService", "4.2", nullptr));
        label1_3->setText(QCoreApplication::translate("WidgetService", "1.3", nullptr));
        label2_3->setText(QCoreApplication::translate("WidgetService", "2.3", nullptr));
        label3_3->setText(QCoreApplication::translate("WidgetService", "3.3", nullptr));
        label4_3->setText(QCoreApplication::translate("WidgetService", "4.3", nullptr));
        label5_1->setText(QCoreApplication::translate("WidgetService", "5.1", nullptr));
        lineEdit_5_2->setText(QCoreApplication::translate("WidgetService", "5.2", nullptr));
        pushButton_5_3->setText(QCoreApplication::translate("WidgetService", "5.3", nullptr));
        label6_1->setText(QCoreApplication::translate("WidgetService", "6_1", nullptr));
        lineEdit_6_2->setText(QCoreApplication::translate("WidgetService", "6.2", nullptr));
        pushButton_6_3->setText(QCoreApplication::translate("WidgetService", "6.3", nullptr));
        label_Notes->setText(QCoreApplication::translate("WidgetService", "Piez.", nullptr));
        label_3->setText(QCoreApplication::translate("WidgetService", "X start pos", nullptr));
        pushButton_Xplus->setText(QCoreApplication::translate("WidgetService", "+", nullptr));
        pushButton_Xminus->setText(QCoreApplication::translate("WidgetService", "-", nullptr));
        label_4->setText(QCoreApplication::translate("WidgetService", "Y start pos", nullptr));
        pushButton_Yplus->setText(QCoreApplication::translate("WidgetService", "+", nullptr));
        pushButton_Yminus->setText(QCoreApplication::translate("WidgetService", "-", nullptr));
        label_5->setText(QCoreApplication::translate("WidgetService", "start size", nullptr));
        pushButton_sizeplus->setText(QCoreApplication::translate("WidgetService", "+", nullptr));
        pushButton_sizeMinus->setText(QCoreApplication::translate("WidgetService", "-", nullptr));
        label_7->setText(QCoreApplication::translate("WidgetService", "Options", nullptr));
        pushButton_OptionsPlus->setText(QCoreApplication::translate("WidgetService", "+", nullptr));
        pushButton_OptionsMinus->setText(QCoreApplication::translate("WidgetService", "-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetService: public Ui_WidgetService {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETSERVICE_H
