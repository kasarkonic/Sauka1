/********************************************************************************
** Form generated from reading UI file 'componentcard.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPONENTCARD_H
#define UI_COMPONENTCARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ComponentCard
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_Heder;
    QHBoxLayout *horizontalLayout_1;
    QLabel *label_comp_name;
    QLineEdit *lineEdit_comp_name;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_13;
    QLabel *label_1;
    QLabel *label_2;
    QLabel *label_3;
    QFrame *line;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label;
    QLineEdit *lineEdit_moisture;
    QLineEdit *lineEdit_moistureVol;
    QLineEdit *lineEdit_1_unit;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_4;
    QLineEdit *lineEdit_dray;
    QLineEdit *lineEdit_drayVol;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_5;
    QLineEdit *lineEdit_organic;
    QLineEdit *lineEdit_organicVol;
    QLineEdit *lineEdit_4;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_6;
    QLineEdit *lineEdit_humin;
    QLineEdit *lineEdit_huminVol;
    QLineEdit *lineEdit_7;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_7;
    QLineEdit *lineEdit_sarms;
    QLineEdit *lineEdit_sarmsVol;
    QLineEdit *lineEdit_10;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_8;
    QLineEdit *lineEdit_KO;
    QLineEdit *lineEdit_KOVol;
    QLineEdit *lineEdit_13;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_9;
    QLineEdit *lineEdit_param7;
    QLineEdit *lineEdit_param7_Vol;
    QLineEdit *lineEdit_16;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_10;
    QLineEdit *lineEdit_param8;
    QLineEdit *lineEdit_param8_Vol;
    QLineEdit *lineEdit_19;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_11;
    QLineEdit *lineEdit_param9;
    QLineEdit *lineEdit_param9_Vol;
    QLineEdit *lineEdit_22;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_12;
    QLineEdit *lineEdit_param10;
    QLineEdit *lineEdit_param10Vol;
    QLineEdit *lineEdit_25;
    QFrame *line_5;
    QHBoxLayout *horizontalLayout_4;
    QTextEdit *textEdit_notes;
    QFrame *line_4;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_exit;
    QLabel *label_14;
    QComboBox *comboBox_loadCard;
    QPushButton *pushButton_save;
    QPushButton *pushButton_clear;
    QPushButton *pushButton_del;
    QFrame *line_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_info;
    QFrame *line_2;

    void setupUi(QWidget *ComponentCard)
    {
        if (ComponentCard->objectName().isEmpty())
            ComponentCard->setObjectName("ComponentCard");
        ComponentCard->resize(1132, 700);
        verticalLayout_3 = new QVBoxLayout(ComponentCard);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_Heder = new QLabel(ComponentCard);
        label_Heder->setObjectName("label_Heder");
        QFont font;
        font.setPointSize(18);
        label_Heder->setFont(font);
        label_Heder->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_Heder);


        verticalLayout->addLayout(verticalLayout_2);

        horizontalLayout_1 = new QHBoxLayout();
        horizontalLayout_1->setObjectName("horizontalLayout_1");
        label_comp_name = new QLabel(ComponentCard);
        label_comp_name->setObjectName("label_comp_name");

        horizontalLayout_1->addWidget(label_comp_name);

        lineEdit_comp_name = new QLineEdit(ComponentCard);
        lineEdit_comp_name->setObjectName("lineEdit_comp_name");

        horizontalLayout_1->addWidget(lineEdit_comp_name);


        verticalLayout->addLayout(horizontalLayout_1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName("horizontalLayout_14");
        label_13 = new QLabel(ComponentCard);
        label_13->setObjectName("label_13");

        horizontalLayout_14->addWidget(label_13);

        label_1 = new QLabel(ComponentCard);
        label_1->setObjectName("label_1");

        horizontalLayout_14->addWidget(label_1);

        label_2 = new QLabel(ComponentCard);
        label_2->setObjectName("label_2");

        horizontalLayout_14->addWidget(label_2);

        label_3 = new QLabel(ComponentCard);
        label_3->setObjectName("label_3");

        horizontalLayout_14->addWidget(label_3);

        horizontalLayout_14->setStretch(0, 1);
        horizontalLayout_14->setStretch(1, 20);
        horizontalLayout_14->setStretch(2, 2);
        horizontalLayout_14->setStretch(3, 2);

        verticalLayout->addLayout(horizontalLayout_14);

        line = new QFrame(ComponentCard);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName("horizontalLayout_16");
        label = new QLabel(ComponentCard);
        label->setObjectName("label");

        horizontalLayout_16->addWidget(label);

        lineEdit_moisture = new QLineEdit(ComponentCard);
        lineEdit_moisture->setObjectName("lineEdit_moisture");
        lineEdit_moisture->setEnabled(true);

        horizontalLayout_16->addWidget(lineEdit_moisture);

        lineEdit_moistureVol = new QLineEdit(ComponentCard);
        lineEdit_moistureVol->setObjectName("lineEdit_moistureVol");

        horizontalLayout_16->addWidget(lineEdit_moistureVol);

        lineEdit_1_unit = new QLineEdit(ComponentCard);
        lineEdit_1_unit->setObjectName("lineEdit_1_unit");

        horizontalLayout_16->addWidget(lineEdit_1_unit);

        horizontalLayout_16->setStretch(0, 1);
        horizontalLayout_16->setStretch(1, 20);
        horizontalLayout_16->setStretch(2, 2);
        horizontalLayout_16->setStretch(3, 2);

        verticalLayout->addLayout(horizontalLayout_16);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName("horizontalLayout_15");
        label_4 = new QLabel(ComponentCard);
        label_4->setObjectName("label_4");

        horizontalLayout_15->addWidget(label_4);

        lineEdit_dray = new QLineEdit(ComponentCard);
        lineEdit_dray->setObjectName("lineEdit_dray");
        lineEdit_dray->setEnabled(true);

        horizontalLayout_15->addWidget(lineEdit_dray);

        lineEdit_drayVol = new QLineEdit(ComponentCard);
        lineEdit_drayVol->setObjectName("lineEdit_drayVol");

        horizontalLayout_15->addWidget(lineEdit_drayVol);

        lineEdit = new QLineEdit(ComponentCard);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout_15->addWidget(lineEdit);

        horizontalLayout_15->setStretch(0, 1);
        horizontalLayout_15->setStretch(1, 20);
        horizontalLayout_15->setStretch(2, 2);
        horizontalLayout_15->setStretch(3, 2);

        verticalLayout->addLayout(horizontalLayout_15);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        label_5 = new QLabel(ComponentCard);
        label_5->setObjectName("label_5");

        horizontalLayout_13->addWidget(label_5);

        lineEdit_organic = new QLineEdit(ComponentCard);
        lineEdit_organic->setObjectName("lineEdit_organic");
        lineEdit_organic->setEnabled(true);

        horizontalLayout_13->addWidget(lineEdit_organic);

        lineEdit_organicVol = new QLineEdit(ComponentCard);
        lineEdit_organicVol->setObjectName("lineEdit_organicVol");

        horizontalLayout_13->addWidget(lineEdit_organicVol);

        lineEdit_4 = new QLineEdit(ComponentCard);
        lineEdit_4->setObjectName("lineEdit_4");

        horizontalLayout_13->addWidget(lineEdit_4);

        horizontalLayout_13->setStretch(0, 1);
        horizontalLayout_13->setStretch(1, 20);
        horizontalLayout_13->setStretch(2, 2);
        horizontalLayout_13->setStretch(3, 2);

        verticalLayout->addLayout(horizontalLayout_13);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        label_6 = new QLabel(ComponentCard);
        label_6->setObjectName("label_6");

        horizontalLayout_12->addWidget(label_6);

        lineEdit_humin = new QLineEdit(ComponentCard);
        lineEdit_humin->setObjectName("lineEdit_humin");
        lineEdit_humin->setEnabled(true);

        horizontalLayout_12->addWidget(lineEdit_humin);

        lineEdit_huminVol = new QLineEdit(ComponentCard);
        lineEdit_huminVol->setObjectName("lineEdit_huminVol");

        horizontalLayout_12->addWidget(lineEdit_huminVol);

        lineEdit_7 = new QLineEdit(ComponentCard);
        lineEdit_7->setObjectName("lineEdit_7");

        horizontalLayout_12->addWidget(lineEdit_7);

        horizontalLayout_12->setStretch(0, 1);
        horizontalLayout_12->setStretch(1, 20);
        horizontalLayout_12->setStretch(2, 2);
        horizontalLayout_12->setStretch(3, 2);

        verticalLayout->addLayout(horizontalLayout_12);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        label_7 = new QLabel(ComponentCard);
        label_7->setObjectName("label_7");

        horizontalLayout_11->addWidget(label_7);

        lineEdit_sarms = new QLineEdit(ComponentCard);
        lineEdit_sarms->setObjectName("lineEdit_sarms");
        lineEdit_sarms->setEnabled(true);

        horizontalLayout_11->addWidget(lineEdit_sarms);

        lineEdit_sarmsVol = new QLineEdit(ComponentCard);
        lineEdit_sarmsVol->setObjectName("lineEdit_sarmsVol");

        horizontalLayout_11->addWidget(lineEdit_sarmsVol);

        lineEdit_10 = new QLineEdit(ComponentCard);
        lineEdit_10->setObjectName("lineEdit_10");

        horizontalLayout_11->addWidget(lineEdit_10);

        horizontalLayout_11->setStretch(0, 1);
        horizontalLayout_11->setStretch(1, 20);
        horizontalLayout_11->setStretch(2, 2);
        horizontalLayout_11->setStretch(3, 2);

        verticalLayout->addLayout(horizontalLayout_11);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        label_8 = new QLabel(ComponentCard);
        label_8->setObjectName("label_8");

        horizontalLayout_10->addWidget(label_8);

        lineEdit_KO = new QLineEdit(ComponentCard);
        lineEdit_KO->setObjectName("lineEdit_KO");
        lineEdit_KO->setEnabled(true);

        horizontalLayout_10->addWidget(lineEdit_KO);

        lineEdit_KOVol = new QLineEdit(ComponentCard);
        lineEdit_KOVol->setObjectName("lineEdit_KOVol");

        horizontalLayout_10->addWidget(lineEdit_KOVol);

        lineEdit_13 = new QLineEdit(ComponentCard);
        lineEdit_13->setObjectName("lineEdit_13");

        horizontalLayout_10->addWidget(lineEdit_13);

        horizontalLayout_10->setStretch(0, 1);
        horizontalLayout_10->setStretch(1, 20);
        horizontalLayout_10->setStretch(2, 2);
        horizontalLayout_10->setStretch(3, 2);

        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        label_9 = new QLabel(ComponentCard);
        label_9->setObjectName("label_9");

        horizontalLayout_9->addWidget(label_9);

        lineEdit_param7 = new QLineEdit(ComponentCard);
        lineEdit_param7->setObjectName("lineEdit_param7");

        horizontalLayout_9->addWidget(lineEdit_param7);

        lineEdit_param7_Vol = new QLineEdit(ComponentCard);
        lineEdit_param7_Vol->setObjectName("lineEdit_param7_Vol");

        horizontalLayout_9->addWidget(lineEdit_param7_Vol);

        lineEdit_16 = new QLineEdit(ComponentCard);
        lineEdit_16->setObjectName("lineEdit_16");

        horizontalLayout_9->addWidget(lineEdit_16);

        horizontalLayout_9->setStretch(0, 1);
        horizontalLayout_9->setStretch(1, 20);
        horizontalLayout_9->setStretch(2, 2);
        horizontalLayout_9->setStretch(3, 2);

        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_10 = new QLabel(ComponentCard);
        label_10->setObjectName("label_10");

        horizontalLayout_8->addWidget(label_10);

        lineEdit_param8 = new QLineEdit(ComponentCard);
        lineEdit_param8->setObjectName("lineEdit_param8");

        horizontalLayout_8->addWidget(lineEdit_param8);

        lineEdit_param8_Vol = new QLineEdit(ComponentCard);
        lineEdit_param8_Vol->setObjectName("lineEdit_param8_Vol");

        horizontalLayout_8->addWidget(lineEdit_param8_Vol);

        lineEdit_19 = new QLineEdit(ComponentCard);
        lineEdit_19->setObjectName("lineEdit_19");

        horizontalLayout_8->addWidget(lineEdit_19);

        horizontalLayout_8->setStretch(0, 1);
        horizontalLayout_8->setStretch(1, 20);
        horizontalLayout_8->setStretch(2, 2);
        horizontalLayout_8->setStretch(3, 2);

        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_11 = new QLabel(ComponentCard);
        label_11->setObjectName("label_11");

        horizontalLayout_7->addWidget(label_11);

        lineEdit_param9 = new QLineEdit(ComponentCard);
        lineEdit_param9->setObjectName("lineEdit_param9");

        horizontalLayout_7->addWidget(lineEdit_param9);

        lineEdit_param9_Vol = new QLineEdit(ComponentCard);
        lineEdit_param9_Vol->setObjectName("lineEdit_param9_Vol");

        horizontalLayout_7->addWidget(lineEdit_param9_Vol);

        lineEdit_22 = new QLineEdit(ComponentCard);
        lineEdit_22->setObjectName("lineEdit_22");

        horizontalLayout_7->addWidget(lineEdit_22);

        horizontalLayout_7->setStretch(0, 1);
        horizontalLayout_7->setStretch(1, 20);
        horizontalLayout_7->setStretch(2, 2);
        horizontalLayout_7->setStretch(3, 2);

        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_12 = new QLabel(ComponentCard);
        label_12->setObjectName("label_12");

        horizontalLayout_6->addWidget(label_12);

        lineEdit_param10 = new QLineEdit(ComponentCard);
        lineEdit_param10->setObjectName("lineEdit_param10");

        horizontalLayout_6->addWidget(lineEdit_param10);

        lineEdit_param10Vol = new QLineEdit(ComponentCard);
        lineEdit_param10Vol->setObjectName("lineEdit_param10Vol");

        horizontalLayout_6->addWidget(lineEdit_param10Vol);

        lineEdit_25 = new QLineEdit(ComponentCard);
        lineEdit_25->setObjectName("lineEdit_25");

        horizontalLayout_6->addWidget(lineEdit_25);

        horizontalLayout_6->setStretch(0, 1);
        horizontalLayout_6->setStretch(1, 20);
        horizontalLayout_6->setStretch(2, 2);
        horizontalLayout_6->setStretch(3, 2);

        verticalLayout->addLayout(horizontalLayout_6);

        line_5 = new QFrame(ComponentCard);
        line_5->setObjectName("line_5");
        line_5->setFrameShape(QFrame::Shape::HLine);
        line_5->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        textEdit_notes = new QTextEdit(ComponentCard);
        textEdit_notes->setObjectName("textEdit_notes");

        horizontalLayout_4->addWidget(textEdit_notes);


        verticalLayout->addLayout(horizontalLayout_4);

        line_4 = new QFrame(ComponentCard);
        line_4->setObjectName("line_4");
        line_4->setFrameShape(QFrame::Shape::HLine);
        line_4->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        pushButton_exit = new QPushButton(ComponentCard);
        pushButton_exit->setObjectName("pushButton_exit");

        horizontalLayout_3->addWidget(pushButton_exit);

        label_14 = new QLabel(ComponentCard);
        label_14->setObjectName("label_14");

        horizontalLayout_3->addWidget(label_14);

        comboBox_loadCard = new QComboBox(ComponentCard);
        comboBox_loadCard->setObjectName("comboBox_loadCard");
        comboBox_loadCard->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout_3->addWidget(comboBox_loadCard);

        pushButton_save = new QPushButton(ComponentCard);
        pushButton_save->setObjectName("pushButton_save");

        horizontalLayout_3->addWidget(pushButton_save);

        pushButton_clear = new QPushButton(ComponentCard);
        pushButton_clear->setObjectName("pushButton_clear");

        horizontalLayout_3->addWidget(pushButton_clear);

        pushButton_del = new QPushButton(ComponentCard);
        pushButton_del->setObjectName("pushButton_del");

        horizontalLayout_3->addWidget(pushButton_del);

        horizontalLayout_3->setStretch(0, 5);
        horizontalLayout_3->setStretch(1, 2);
        horizontalLayout_3->setStretch(2, 10);
        horizontalLayout_3->setStretch(3, 5);
        horizontalLayout_3->setStretch(4, 5);
        horizontalLayout_3->setStretch(5, 5);

        verticalLayout->addLayout(horizontalLayout_3);

        line_3 = new QFrame(ComponentCard);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::Shape::HLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_info = new QLabel(ComponentCard);
        label_info->setObjectName("label_info");

        horizontalLayout_2->addWidget(label_info);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout->setStretch(0, 2);
        verticalLayout->setStretch(1, 5);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(3, 1);
        verticalLayout->setStretch(4, 5);
        verticalLayout->setStretch(5, 5);
        verticalLayout->setStretch(6, 5);
        verticalLayout->setStretch(7, 5);
        verticalLayout->setStretch(8, 5);
        verticalLayout->setStretch(9, 5);
        verticalLayout->setStretch(10, 5);
        verticalLayout->setStretch(11, 5);
        verticalLayout->setStretch(12, 5);
        verticalLayout->setStretch(13, 5);
        verticalLayout->setStretch(14, 5);
        verticalLayout->setStretch(16, 1);
        verticalLayout->setStretch(18, 1);
        verticalLayout->setStretch(20, 1);

        verticalLayout_3->addLayout(verticalLayout);

        line_2 = new QFrame(ComponentCard);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_3->addWidget(line_2);


        retranslateUi(ComponentCard);

        QMetaObject::connectSlotsByName(ComponentCard);
    } // setupUi

    void retranslateUi(QWidget *ComponentCard)
    {
        ComponentCard->setWindowTitle(QCoreApplication::translate("ComponentCard", "Form", nullptr));
        label_Heder->setText(QCoreApplication::translate("ComponentCard", "KOMPONENTES KARTI\305\205A", nullptr));
        label_comp_name->setText(QCoreApplication::translate("ComponentCard", "Komponente", nullptr));
        lineEdit_comp_name->setText(QCoreApplication::translate("ComponentCard", "Komponentes nosaukums", nullptr));
        label_13->setText(QCoreApplication::translate("ComponentCard", "N.P.K.", nullptr));
        label_1->setText(QCoreApplication::translate("ComponentCard", "Parametrs", nullptr));
        label_2->setText(QCoreApplication::translate("ComponentCard", "Daudzums", nullptr));
        label_3->setText(QCoreApplication::translate("ComponentCard", "M\304\223rvien\304\253ba", nullptr));
        label->setText(QCoreApplication::translate("ComponentCard", " 1.", nullptr));
        lineEdit_moisture->setText(QCoreApplication::translate("ComponentCard", "Mitrums", nullptr));
        lineEdit_moistureVol->setText(QCoreApplication::translate("ComponentCard", "0", nullptr));
        lineEdit_1_unit->setText(QCoreApplication::translate("ComponentCard", "%", nullptr));
        label_4->setText(QCoreApplication::translate("ComponentCard", " 2.", nullptr));
        lineEdit_dray->setText(QCoreApplication::translate("ComponentCard", "Sausna", nullptr));
        lineEdit_drayVol->setText(QCoreApplication::translate("ComponentCard", "0", nullptr));
        lineEdit->setText(QCoreApplication::translate("ComponentCard", "%", nullptr));
        label_5->setText(QCoreApplication::translate("ComponentCard", " 3.", nullptr));
        lineEdit_organic->setText(QCoreApplication::translate("ComponentCard", "Organiska viela", nullptr));
        lineEdit_organicVol->setText(QCoreApplication::translate("ComponentCard", "0", nullptr));
        lineEdit_4->setText(QCoreApplication::translate("ComponentCard", "%", nullptr));
        label_6->setText(QCoreApplication::translate("ComponentCard", " 4.", nullptr));
        lineEdit_humin->setText(QCoreApplication::translate("ComponentCard", "Hum\304\253nsk\304\201bes", nullptr));
        lineEdit_huminVol->setText(QCoreApplication::translate("ComponentCard", "0", nullptr));
        lineEdit_7->setText(QCoreApplication::translate("ComponentCard", "%", nullptr));
        label_7->setText(QCoreApplication::translate("ComponentCard", " 5.", nullptr));
        lineEdit_sarms->setText(QCoreApplication::translate("ComponentCard", "S\304\201rms", nullptr));
        lineEdit_sarmsVol->setText(QCoreApplication::translate("ComponentCard", "0", nullptr));
        lineEdit_10->setText(QCoreApplication::translate("ComponentCard", "%", nullptr));
        label_8->setText(QCoreApplication::translate("ComponentCard", " 6.", nullptr));
        lineEdit_KO->setText(QCoreApplication::translate("ComponentCard", "K\304\201lija Oks\304\253ds", nullptr));
        lineEdit_KOVol->setText(QCoreApplication::translate("ComponentCard", "0", nullptr));
        lineEdit_13->setText(QCoreApplication::translate("ComponentCard", "%", nullptr));
        label_9->setText(QCoreApplication::translate("ComponentCard", " 7.", nullptr));
        lineEdit_param7->setText(QCoreApplication::translate("ComponentCard", "7. parametrs", nullptr));
        lineEdit_param7_Vol->setText(QCoreApplication::translate("ComponentCard", "0", nullptr));
        lineEdit_16->setText(QCoreApplication::translate("ComponentCard", "%", nullptr));
        label_10->setText(QCoreApplication::translate("ComponentCard", " 8.", nullptr));
        lineEdit_param8->setText(QCoreApplication::translate("ComponentCard", "8. parametrs", nullptr));
        lineEdit_param8_Vol->setText(QCoreApplication::translate("ComponentCard", "0", nullptr));
        lineEdit_19->setText(QCoreApplication::translate("ComponentCard", "%", nullptr));
        label_11->setText(QCoreApplication::translate("ComponentCard", " 9.", nullptr));
        lineEdit_param9->setText(QCoreApplication::translate("ComponentCard", "9. parametrs", nullptr));
        lineEdit_param9_Vol->setText(QCoreApplication::translate("ComponentCard", "0", nullptr));
        lineEdit_22->setText(QCoreApplication::translate("ComponentCard", "%", nullptr));
        label_12->setText(QCoreApplication::translate("ComponentCard", "10.", nullptr));
        lineEdit_param10->setText(QCoreApplication::translate("ComponentCard", "10. parametrs", nullptr));
        lineEdit_param10Vol->setText(QCoreApplication::translate("ComponentCard", "0", nullptr));
        lineEdit_25->setText(QCoreApplication::translate("ComponentCard", "%", nullptr));
        textEdit_notes->setHtml(QCoreApplication::translate("ComponentCard", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        pushButton_exit->setText(QCoreApplication::translate("ComponentCard", "Iziet bez izmai\305\206\304\201m", nullptr));
        label_14->setText(QCoreApplication::translate("ComponentCard", "Izv\304\223l\304\223ties karti\305\206u:", nullptr));
        pushButton_save->setText(QCoreApplication::translate("ComponentCard", "Saglab\304\201t", nullptr));
        pushButton_clear->setText(QCoreApplication::translate("ComponentCard", "Not\304\253r\304\253t laukus", nullptr));
        pushButton_del->setText(QCoreApplication::translate("ComponentCard", "Nodz\304\223st karti\305\206u", nullptr));
        label_info->setText(QCoreApplication::translate("ComponentCard", "Inform\304\201cija:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ComponentCard: public Ui_ComponentCard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPONENTCARD_H
