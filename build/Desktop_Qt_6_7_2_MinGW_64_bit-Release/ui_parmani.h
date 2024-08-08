/********************************************************************************
** Form generated from reading UI file 'parmani.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARMANI_H
#define UI_PARMANI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParMani
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QLabel *label;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButtonExit;
    QSpacerItem *verticalSpacer_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ParMani)
    {
        if (ParMani->objectName().isEmpty())
            ParMani->setObjectName("ParMani");
        ParMani->resize(274, 322);
        centralwidget = new QWidget(ParMani);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        label = new QLabel(centralwidget);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushButtonExit = new QPushButton(centralwidget);
        pushButtonExit->setObjectName("pushButtonExit");

        verticalLayout->addWidget(pushButtonExit);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        verticalLayout->setStretch(0, 2);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 5);
        verticalLayout->setStretch(3, 1);
        verticalLayout->setStretch(4, 1);

        verticalLayout_2->addLayout(verticalLayout);

        ParMani->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ParMani);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 274, 17));
        ParMani->setMenuBar(menubar);
        statusbar = new QStatusBar(ParMani);
        statusbar->setObjectName("statusbar");
        ParMani->setStatusBar(statusbar);

        retranslateUi(ParMani);

        QMetaObject::connectSlotsByName(ParMani);
    } // setupUi

    void retranslateUi(QMainWindow *ParMani)
    {
        ParMani->setWindowTitle(QCoreApplication::translate("ParMani", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("ParMani", "TextLabel", nullptr));
        pushButtonExit->setText(QCoreApplication::translate("ParMani", "EXIT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ParMani: public Ui_ParMani {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARMANI_H
