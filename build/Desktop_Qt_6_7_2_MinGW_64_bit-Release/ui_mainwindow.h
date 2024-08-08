/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
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

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_logo;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_Mix;
    QPushButton *pushButton_Dyno;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Stop;
    QFrame *line_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_Recipes;
    QPushButton *pushButton_Settings;
    QPushButton *pushButton_4;
    QPushButton *pushButton_Service;
    QPushButton *pushButton_about;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout_ProcessFlow;
    QFrame *line;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QComboBox *comboBox;
    QTextEdit *textEdit_Field;
    QMenuBar *Saukas_Kdra;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(987, 738);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_logo = new QLabel(centralwidget);
        label_logo->setObjectName("label_logo");

        horizontalLayout->addWidget(label_logo);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        QFont font;
        font.setPointSize(12);
        label_3->setFont(font);

        horizontalLayout->addWidget(label_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        pushButton_Mix = new QPushButton(centralwidget);
        pushButton_Mix->setObjectName("pushButton_Mix");

        horizontalLayout->addWidget(pushButton_Mix);

        pushButton_Dyno = new QPushButton(centralwidget);
        pushButton_Dyno->setObjectName("pushButton_Dyno");

        horizontalLayout->addWidget(pushButton_Dyno);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_Stop = new QPushButton(centralwidget);
        pushButton_Stop->setObjectName("pushButton_Stop");

        horizontalLayout->addWidget(pushButton_Stop);


        verticalLayout_2->addLayout(horizontalLayout);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_2->addWidget(line_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        pushButton_Recipes = new QPushButton(centralwidget);
        pushButton_Recipes->setObjectName("pushButton_Recipes");

        horizontalLayout_4->addWidget(pushButton_Recipes);

        pushButton_Settings = new QPushButton(centralwidget);
        pushButton_Settings->setObjectName("pushButton_Settings");

        horizontalLayout_4->addWidget(pushButton_Settings);

        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");

        horizontalLayout_4->addWidget(pushButton_4);

        pushButton_Service = new QPushButton(centralwidget);
        pushButton_Service->setObjectName("pushButton_Service");

        horizontalLayout_4->addWidget(pushButton_Service);

        pushButton_about = new QPushButton(centralwidget);
        pushButton_about->setObjectName("pushButton_about");

        horizontalLayout_4->addWidget(pushButton_about);


        verticalLayout_3->addLayout(horizontalLayout_4);


        verticalLayout_2->addLayout(verticalLayout_3);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        verticalLayout_2->addWidget(label_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_ProcessFlow = new QHBoxLayout();
        horizontalLayout_ProcessFlow->setObjectName("horizontalLayout_ProcessFlow");

        horizontalLayout_2->addLayout(horizontalLayout_ProcessFlow);

        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        horizontalLayout_2->addWidget(line);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout_5->addWidget(label);

        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName("comboBox");

        horizontalLayout_5->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout_5);

        textEdit_Field = new QTextEdit(centralwidget);
        textEdit_Field->setObjectName("textEdit_Field");

        verticalLayout->addWidget(textEdit_Field);


        horizontalLayout_3->addLayout(verticalLayout);

        horizontalLayout_3->setStretch(0, 8);

        horizontalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_2->setStretch(0, 8);
        horizontalLayout_2->setStretch(2, 2);

        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(4, 25);
        MainWindow->setCentralWidget(centralwidget);
        Saukas_Kdra = new QMenuBar(MainWindow);
        Saukas_Kdra->setObjectName("Saukas_Kdra");
        Saukas_Kdra->setGeometry(QRect(0, 0, 987, 25));
        MainWindow->setMenuBar(Saukas_Kdra);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_logo->setText(QCoreApplication::translate("MainWindow", "Saukas k\305\253dra", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Procesa vad\304\253bas sh\304\223ma", nullptr));
        pushButton_Mix->setText(QCoreApplication::translate("MainWindow", "Mix", nullptr));
        pushButton_Dyno->setText(QCoreApplication::translate("MainWindow", "Dyno", nullptr));
        pushButton_Stop->setText(QCoreApplication::translate("MainWindow", "STOP", nullptr));
        pushButton_Recipes->setText(QCoreApplication::translate("MainWindow", "Receptes", nullptr));
        pushButton_Settings->setText(QCoreApplication::translate("MainWindow", "Iestat\304\253jumi", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_Service->setText(QCoreApplication::translate("MainWindow", "Serviss", nullptr));
        pushButton_about->setText(QCoreApplication::translate("MainWindow", "Par Mani", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Izv\304\223lne", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
