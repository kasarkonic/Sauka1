/********************************************************************************
** Form generated from reading UI file 'procui1.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROCUI1_H
#define UI_PROCUI1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
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

class Ui_ProcUI1
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_Logo;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_Heder;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Stop;
    QFrame *line;
    QHBoxLayout *horizontalLayout_Process;
    QWidget *desktop;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout;
    QTextEdit *textEdit_Info;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ProcUI1)
    {
        if (ProcUI1->objectName().isEmpty())
            ProcUI1->setObjectName("ProcUI1");
        ProcUI1->resize(800, 600);
        centralwidget = new QWidget(ProcUI1);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_Logo = new QLabel(centralwidget);
        label_Logo->setObjectName("label_Logo");

        horizontalLayout_2->addWidget(label_Logo);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label_Heder = new QLabel(centralwidget);
        label_Heder->setObjectName("label_Heder");
        QFont font;
        font.setPointSize(20);
        label_Heder->setFont(font);

        horizontalLayout_2->addWidget(label_Heder);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton_Stop = new QPushButton(centralwidget);
        pushButton_Stop->setObjectName("pushButton_Stop");

        horizontalLayout_2->addWidget(pushButton_Stop);


        verticalLayout->addLayout(horizontalLayout_2);

        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout_Process = new QHBoxLayout();
        horizontalLayout_Process->setObjectName("horizontalLayout_Process");
        desktop = new QWidget(centralwidget);
        desktop->setObjectName("desktop");

        horizontalLayout_Process->addWidget(desktop);


        verticalLayout->addLayout(horizontalLayout_Process);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        textEdit_Info = new QTextEdit(centralwidget);
        textEdit_Info->setObjectName("textEdit_Info");

        horizontalLayout->addWidget(textEdit_Info);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(2, 7);
        verticalLayout->setStretch(4, 2);

        verticalLayout_2->addLayout(verticalLayout);

        ProcUI1->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ProcUI1);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        ProcUI1->setMenuBar(menubar);
        statusbar = new QStatusBar(ProcUI1);
        statusbar->setObjectName("statusbar");
        ProcUI1->setStatusBar(statusbar);

        retranslateUi(ProcUI1);

        QMetaObject::connectSlotsByName(ProcUI1);
    } // setupUi

    void retranslateUi(QMainWindow *ProcUI1)
    {
        ProcUI1->setWindowTitle(QCoreApplication::translate("ProcUI1", "MainWindow", nullptr));
        label_Logo->setText(QCoreApplication::translate("ProcUI1", "TextLabel", nullptr));
        label_Heder->setText(QCoreApplication::translate("ProcUI1", "Procesa vad\304\253bas sh\304\223ma 1", nullptr));
        pushButton_Stop->setText(QCoreApplication::translate("ProcUI1", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProcUI1: public Ui_ProcUI1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROCUI1_H
