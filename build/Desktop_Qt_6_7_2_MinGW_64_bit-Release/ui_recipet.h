/********************************************************************************
** Form generated from reading UI file 'recipet.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECIPET_H
#define UI_RECIPET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Recipet
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_Rec_name;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_6;
    QComboBox *comboBox_1_ingr;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *lineEdit_1_ingr_val;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_7;
    QComboBox *comboBox_2_ingr;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *lineEdit_2_ingr_val;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_8;
    QComboBox *comboBox_3_ingr;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *lineEdit_3_ingr_val;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_9;
    QComboBox *comboBox_4_ingr;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *lineEdit_4_ingr_val;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_10;
    QComboBox *comboBox_5_ingr;
    QSpacerItem *horizontalSpacer_6;
    QLineEdit *lineEdit_5_ingr_val;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_11;
    QComboBox *comboBox_6_ingr;
    QSpacerItem *horizontalSpacer_7;
    QLineEdit *lineEdit_6_ingr_val;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_21;
    QComboBox *comboBox_7_ingr;
    QSpacerItem *horizontalSpacer_8;
    QLineEdit *lineEdit_7_ingr_val;
    QHBoxLayout *horizontalLayout_16;
    QSpacerItem *horizontalSpacer_12;
    QLabel *label_13;
    QSpacerItem *horizontalSpacer_13;
    QLabel *label_sum;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_19;
    QComboBox *comboBox_8_ingr;
    QSpacerItem *horizontalSpacer_9;
    QLineEdit *lineEdit_8_ingr_val;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_18;
    QComboBox *comboBox_9_ingr;
    QSpacerItem *horizontalSpacer_10;
    QLineEdit *lineEdit_9_ingr_val;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_20;
    QComboBox *comboBox_10_ingr;
    QSpacerItem *horizontalSpacer_11;
    QLineEdit *lineEdit_10_ingr_val;
    QHBoxLayout *horizontalLayout_12;
    QTextEdit *textEdit_notes;
    QHBoxLayout *horizontalLayout_11;
    QPushButton *pushButton_exit;
    QLabel *label_12;
    QComboBox *comboBox_reciep;
    QPushButton *pushButton_save;
    QPushButton *pushButton_clear;
    QPushButton *pushButton_delet;
    QPushButton *pushButton_components_Card;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_notes;

    void setupUi(QWidget *Recipet)
    {
        if (Recipet->objectName().isEmpty())
            Recipet->setObjectName("Recipet");
        Recipet->resize(677, 700);
        verticalLayout_3 = new QVBoxLayout(Recipet);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(Recipet);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(16);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(Recipet);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        lineEdit_Rec_name = new QLineEdit(Recipet);
        lineEdit_Rec_name->setObjectName("lineEdit_Rec_name");

        horizontalLayout_2->addWidget(lineEdit_Rec_name);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_5 = new QLabel(Recipet);
        label_5->setObjectName("label_5");

        horizontalLayout_4->addWidget(label_5);

        label_4 = new QLabel(Recipet);
        label_4->setObjectName("label_4");

        horizontalLayout_4->addWidget(label_4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        label_3 = new QLabel(Recipet);
        label_3->setObjectName("label_3");

        horizontalLayout_4->addWidget(label_3);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_6 = new QLabel(Recipet);
        label_6->setObjectName("label_6");

        horizontalLayout_7->addWidget(label_6);

        comboBox_1_ingr = new QComboBox(Recipet);
        comboBox_1_ingr->setObjectName("comboBox_1_ingr");

        horizontalLayout_7->addWidget(comboBox_1_ingr);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);

        lineEdit_1_ingr_val = new QLineEdit(Recipet);
        lineEdit_1_ingr_val->setObjectName("lineEdit_1_ingr_val");

        horizontalLayout_7->addWidget(lineEdit_1_ingr_val);

        horizontalLayout_7->setStretch(1, 20);
        horizontalLayout_7->setStretch(2, 1);
        horizontalLayout_7->setStretch(3, 3);

        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_7 = new QLabel(Recipet);
        label_7->setObjectName("label_7");

        horizontalLayout_5->addWidget(label_7);

        comboBox_2_ingr = new QComboBox(Recipet);
        comboBox_2_ingr->setObjectName("comboBox_2_ingr");

        horizontalLayout_5->addWidget(comboBox_2_ingr);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        lineEdit_2_ingr_val = new QLineEdit(Recipet);
        lineEdit_2_ingr_val->setObjectName("lineEdit_2_ingr_val");

        horizontalLayout_5->addWidget(lineEdit_2_ingr_val);

        horizontalLayout_5->setStretch(1, 20);
        horizontalLayout_5->setStretch(2, 1);
        horizontalLayout_5->setStretch(3, 3);

        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_8 = new QLabel(Recipet);
        label_8->setObjectName("label_8");

        horizontalLayout_6->addWidget(label_8);

        comboBox_3_ingr = new QComboBox(Recipet);
        comboBox_3_ingr->setObjectName("comboBox_3_ingr");

        horizontalLayout_6->addWidget(comboBox_3_ingr);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);

        lineEdit_3_ingr_val = new QLineEdit(Recipet);
        lineEdit_3_ingr_val->setObjectName("lineEdit_3_ingr_val");

        horizontalLayout_6->addWidget(lineEdit_3_ingr_val);

        horizontalLayout_6->setStretch(1, 20);
        horizontalLayout_6->setStretch(2, 1);
        horizontalLayout_6->setStretch(3, 3);

        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        label_9 = new QLabel(Recipet);
        label_9->setObjectName("label_9");

        horizontalLayout_10->addWidget(label_9);

        comboBox_4_ingr = new QComboBox(Recipet);
        comboBox_4_ingr->setObjectName("comboBox_4_ingr");

        horizontalLayout_10->addWidget(comboBox_4_ingr);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_5);

        lineEdit_4_ingr_val = new QLineEdit(Recipet);
        lineEdit_4_ingr_val->setObjectName("lineEdit_4_ingr_val");

        horizontalLayout_10->addWidget(lineEdit_4_ingr_val);

        horizontalLayout_10->setStretch(1, 20);
        horizontalLayout_10->setStretch(2, 1);
        horizontalLayout_10->setStretch(3, 3);

        verticalLayout->addLayout(horizontalLayout_10);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        label_10 = new QLabel(Recipet);
        label_10->setObjectName("label_10");

        horizontalLayout_9->addWidget(label_10);

        comboBox_5_ingr = new QComboBox(Recipet);
        comboBox_5_ingr->setObjectName("comboBox_5_ingr");

        horizontalLayout_9->addWidget(comboBox_5_ingr);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_6);

        lineEdit_5_ingr_val = new QLineEdit(Recipet);
        lineEdit_5_ingr_val->setObjectName("lineEdit_5_ingr_val");

        horizontalLayout_9->addWidget(lineEdit_5_ingr_val);

        horizontalLayout_9->setStretch(1, 20);
        horizontalLayout_9->setStretch(2, 1);
        horizontalLayout_9->setStretch(3, 3);

        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_11 = new QLabel(Recipet);
        label_11->setObjectName("label_11");

        horizontalLayout_8->addWidget(label_11);

        comboBox_6_ingr = new QComboBox(Recipet);
        comboBox_6_ingr->setObjectName("comboBox_6_ingr");

        horizontalLayout_8->addWidget(comboBox_6_ingr);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_7);

        lineEdit_6_ingr_val = new QLineEdit(Recipet);
        lineEdit_6_ingr_val->setObjectName("lineEdit_6_ingr_val");

        horizontalLayout_8->addWidget(lineEdit_6_ingr_val);

        horizontalLayout_8->setStretch(1, 20);
        horizontalLayout_8->setStretch(2, 1);
        horizontalLayout_8->setStretch(3, 3);

        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_21 = new QLabel(Recipet);
        label_21->setObjectName("label_21");

        horizontalLayout_3->addWidget(label_21);

        comboBox_7_ingr = new QComboBox(Recipet);
        comboBox_7_ingr->setObjectName("comboBox_7_ingr");

        horizontalLayout_3->addWidget(comboBox_7_ingr);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_8);

        lineEdit_7_ingr_val = new QLineEdit(Recipet);
        lineEdit_7_ingr_val->setObjectName("lineEdit_7_ingr_val");

        horizontalLayout_3->addWidget(lineEdit_7_ingr_val);

        horizontalLayout_3->setStretch(1, 20);
        horizontalLayout_3->setStretch(2, 1);
        horizontalLayout_3->setStretch(3, 3);

        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName("horizontalLayout_16");
        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_12);

        label_13 = new QLabel(Recipet);
        label_13->setObjectName("label_13");

        horizontalLayout_16->addWidget(label_13);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_13);

        label_sum = new QLabel(Recipet);
        label_sum->setObjectName("label_sum");

        horizontalLayout_16->addWidget(label_sum);

        horizontalLayout_16->setStretch(0, 42);
        horizontalLayout_16->setStretch(3, 6);

        verticalLayout->addLayout(horizontalLayout_16);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName("horizontalLayout_15");
        label_19 = new QLabel(Recipet);
        label_19->setObjectName("label_19");

        horizontalLayout_15->addWidget(label_19);

        comboBox_8_ingr = new QComboBox(Recipet);
        comboBox_8_ingr->setObjectName("comboBox_8_ingr");

        horizontalLayout_15->addWidget(comboBox_8_ingr);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_9);

        lineEdit_8_ingr_val = new QLineEdit(Recipet);
        lineEdit_8_ingr_val->setObjectName("lineEdit_8_ingr_val");

        horizontalLayout_15->addWidget(lineEdit_8_ingr_val);

        horizontalLayout_15->setStretch(1, 20);
        horizontalLayout_15->setStretch(2, 1);
        horizontalLayout_15->setStretch(3, 3);

        verticalLayout->addLayout(horizontalLayout_15);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName("horizontalLayout_14");
        label_18 = new QLabel(Recipet);
        label_18->setObjectName("label_18");

        horizontalLayout_14->addWidget(label_18);

        comboBox_9_ingr = new QComboBox(Recipet);
        comboBox_9_ingr->setObjectName("comboBox_9_ingr");

        horizontalLayout_14->addWidget(comboBox_9_ingr);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_10);

        lineEdit_9_ingr_val = new QLineEdit(Recipet);
        lineEdit_9_ingr_val->setObjectName("lineEdit_9_ingr_val");

        horizontalLayout_14->addWidget(lineEdit_9_ingr_val);

        horizontalLayout_14->setStretch(1, 20);
        horizontalLayout_14->setStretch(2, 1);
        horizontalLayout_14->setStretch(3, 3);

        verticalLayout->addLayout(horizontalLayout_14);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        label_20 = new QLabel(Recipet);
        label_20->setObjectName("label_20");

        horizontalLayout_13->addWidget(label_20);

        comboBox_10_ingr = new QComboBox(Recipet);
        comboBox_10_ingr->setObjectName("comboBox_10_ingr");

        horizontalLayout_13->addWidget(comboBox_10_ingr);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_11);

        lineEdit_10_ingr_val = new QLineEdit(Recipet);
        lineEdit_10_ingr_val->setObjectName("lineEdit_10_ingr_val");

        horizontalLayout_13->addWidget(lineEdit_10_ingr_val);

        horizontalLayout_13->setStretch(1, 20);
        horizontalLayout_13->setStretch(2, 1);
        horizontalLayout_13->setStretch(3, 3);

        verticalLayout->addLayout(horizontalLayout_13);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        textEdit_notes = new QTextEdit(Recipet);
        textEdit_notes->setObjectName("textEdit_notes");

        horizontalLayout_12->addWidget(textEdit_notes);


        verticalLayout->addLayout(horizontalLayout_12);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        pushButton_exit = new QPushButton(Recipet);
        pushButton_exit->setObjectName("pushButton_exit");

        horizontalLayout_11->addWidget(pushButton_exit);

        label_12 = new QLabel(Recipet);
        label_12->setObjectName("label_12");

        horizontalLayout_11->addWidget(label_12);

        comboBox_reciep = new QComboBox(Recipet);
        comboBox_reciep->setObjectName("comboBox_reciep");

        horizontalLayout_11->addWidget(comboBox_reciep);

        pushButton_save = new QPushButton(Recipet);
        pushButton_save->setObjectName("pushButton_save");

        horizontalLayout_11->addWidget(pushButton_save);

        pushButton_clear = new QPushButton(Recipet);
        pushButton_clear->setObjectName("pushButton_clear");

        horizontalLayout_11->addWidget(pushButton_clear);

        pushButton_delet = new QPushButton(Recipet);
        pushButton_delet->setObjectName("pushButton_delet");

        horizontalLayout_11->addWidget(pushButton_delet);

        pushButton_components_Card = new QPushButton(Recipet);
        pushButton_components_Card->setObjectName("pushButton_components_Card");

        horizontalLayout_11->addWidget(pushButton_components_Card);


        verticalLayout->addLayout(horizontalLayout_11);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_notes = new QLabel(Recipet);
        label_notes->setObjectName("label_notes");

        verticalLayout_2->addWidget(label_notes);


        verticalLayout->addLayout(verticalLayout_2);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 10);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(3, 10);
        verticalLayout->setStretch(4, 10);
        verticalLayout->setStretch(5, 10);
        verticalLayout->setStretch(6, 10);
        verticalLayout->setStretch(7, 10);
        verticalLayout->setStretch(8, 10);
        verticalLayout->setStretch(14, 3);
        verticalLayout->setStretch(15, 10);
        verticalLayout->setStretch(16, 1);

        verticalLayout_3->addLayout(verticalLayout);


        retranslateUi(Recipet);

        QMetaObject::connectSlotsByName(Recipet);
    } // setupUi

    void retranslateUi(QWidget *Recipet)
    {
        Recipet->setWindowTitle(QCoreApplication::translate("Recipet", "Form", nullptr));
        label->setText(QCoreApplication::translate("Recipet", "Recepte", nullptr));
        label_2->setText(QCoreApplication::translate("Recipet", "Recepte", nullptr));
        label_5->setText(QCoreApplication::translate("Recipet", "N.P.K", nullptr));
        label_4->setText(QCoreApplication::translate("Recipet", "Ingradients", nullptr));
        label_3->setText(QCoreApplication::translate("Recipet", "Daudzums kg/T", nullptr));
        label_6->setText(QCoreApplication::translate("Recipet", "1. ", nullptr));
        label_7->setText(QCoreApplication::translate("Recipet", "2. ", nullptr));
        label_8->setText(QCoreApplication::translate("Recipet", "3. ", nullptr));
        label_9->setText(QCoreApplication::translate("Recipet", "4. ", nullptr));
        label_10->setText(QCoreApplication::translate("Recipet", "5. ", nullptr));
        label_11->setText(QCoreApplication::translate("Recipet", "6. ", nullptr));
        label_21->setText(QCoreApplication::translate("Recipet", "7. ", nullptr));
        label_13->setText(QCoreApplication::translate("Recipet", "Kop\304\201", nullptr));
        label_sum->setText(QString());
        label_19->setText(QCoreApplication::translate("Recipet", "8. ", nullptr));
        label_18->setText(QCoreApplication::translate("Recipet", "9. ", nullptr));
        label_20->setText(QCoreApplication::translate("Recipet", "10.", nullptr));
        pushButton_exit->setText(QCoreApplication::translate("Recipet", "Iziet bez izmai\305\206\304\201m", nullptr));
        label_12->setText(QCoreApplication::translate("Recipet", "Izv\304\223l\304\223ties recepti", nullptr));
        pushButton_save->setText(QCoreApplication::translate("Recipet", "Saglab\304\201t", nullptr));
        pushButton_clear->setText(QCoreApplication::translate("Recipet", "Not\304\253r\304\253t laukus", nullptr));
        pushButton_delet->setText(QCoreApplication::translate("Recipet", "Nodz\304\223st recepti", nullptr));
        pushButton_components_Card->setText(QCoreApplication::translate("Recipet", "Komponentes", nullptr));
        label_notes->setText(QCoreApplication::translate("Recipet", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Recipet: public Ui_Recipet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECIPET_H
