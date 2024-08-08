/********************************************************************************
** Form generated from reading UI file 'procui2.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROCUI2_H
#define UI_PROCUI2_H

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

class Ui_ProcUI2
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_Logo;
    QSpacerItem *horizontalSpacer;
    QLabel *label_Heder;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_Stop;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_Process;
    QWidget *desktop;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QTextEdit *textEdit_Info;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ProcUI2)
    {
        if (ProcUI2->objectName().isEmpty())
            ProcUI2->setObjectName("ProcUI2");
        ProcUI2->resize(800, 600);
        centralwidget = new QWidget(ProcUI2);
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

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_Heder = new QLabel(centralwidget);
        label_Heder->setObjectName("label_Heder");
        QFont font;
        font.setPointSize(20);
        label_Heder->setFont(font);

        horizontalLayout_2->addWidget(label_Heder);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButton_Stop = new QPushButton(centralwidget);
        pushButton_Stop->setObjectName("pushButton_Stop");

        horizontalLayout_2->addWidget(pushButton_Stop);


        verticalLayout->addLayout(horizontalLayout_2);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line_2);

        horizontalLayout_Process = new QHBoxLayout();
        horizontalLayout_Process->setObjectName("horizontalLayout_Process");
        desktop = new QWidget(centralwidget);
        desktop->setObjectName("desktop");

        horizontalLayout_Process->addWidget(desktop);


        verticalLayout->addLayout(horizontalLayout_Process);

        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout->addWidget(line);

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

        ProcUI2->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ProcUI2);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        ProcUI2->setMenuBar(menubar);
        statusbar = new QStatusBar(ProcUI2);
        statusbar->setObjectName("statusbar");
        ProcUI2->setStatusBar(statusbar);

        retranslateUi(ProcUI2);

        QMetaObject::connectSlotsByName(ProcUI2);
    } // setupUi

    void retranslateUi(QMainWindow *ProcUI2)
    {
        ProcUI2->setWindowTitle(QCoreApplication::translate("ProcUI2", "MainWindow", nullptr));
        label_Logo->setText(QCoreApplication::translate("ProcUI2", "TextLabel", nullptr));
        label_Heder->setText(QCoreApplication::translate("ProcUI2", "Procesa vad\304\253bas sh\304\223ma 2", nullptr));
        pushButton_Stop->setText(QCoreApplication::translate("ProcUI2", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProcUI2: public Ui_ProcUI2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROCUI2_H
