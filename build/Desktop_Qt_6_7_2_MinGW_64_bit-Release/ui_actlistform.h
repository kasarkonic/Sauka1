/********************************************************************************
** Form generated from reading UI file 'actlistform.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACTLISTFORM_H
#define UI_ACTLISTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ActListForm
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer;
    QLabel *label_head;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QFrame *line;
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ActListForm)
    {
        if (ActListForm->objectName().isEmpty())
            ActListForm->setObjectName("ActListForm");
        ActListForm->resize(670, 570);
        centralwidget = new QWidget(ActListForm);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        horizontalLayout->addWidget(label_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_head = new QLabel(centralwidget);
        label_head->setObjectName("label_head");

        horizontalLayout->addWidget(label_head);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);


        verticalLayout_2->addLayout(horizontalLayout);

        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_2->addWidget(line);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        tableView = new QTableView(centralwidget);
        tableView->setObjectName("tableView");

        verticalLayout->addWidget(tableView);


        verticalLayout_2->addLayout(verticalLayout);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(2, 15);
        ActListForm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ActListForm);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 670, 17));
        ActListForm->setMenuBar(menubar);
        statusbar = new QStatusBar(ActListForm);
        statusbar->setObjectName("statusbar");
        ActListForm->setStatusBar(statusbar);

        retranslateUi(ActListForm);

        QMetaObject::connectSlotsByName(ActListForm);
    } // setupUi

    void retranslateUi(QMainWindow *ActListForm)
    {
        ActListForm->setWindowTitle(QCoreApplication::translate("ActListForm", "MainWindow", nullptr));
        label_3->setText(QCoreApplication::translate("ActListForm", "Saukas k\305\253dra", nullptr));
        label_head->setText(QCoreApplication::translate("ActListForm", "Iek\304\201rtu saraksts", nullptr));
        label->setText(QCoreApplication::translate("ActListForm", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ActListForm: public Ui_ActListForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACTLISTFORM_H
