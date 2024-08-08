/********************************************************************************
** Form generated from reading UI file 'senslistsform.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENSLISTSFORM_H
#define UI_SENSLISTSFORM_H

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

class Ui_SensListsForm
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_head;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QFrame *line;
    QVBoxLayout *verticalLayout;
    QTableView *tableView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SensListsForm)
    {
        if (SensListsForm->objectName().isEmpty())
            SensListsForm->setObjectName("SensListsForm");
        SensListsForm->resize(652, 509);
        centralwidget = new QWidget(SensListsForm);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        horizontalLayout->addWidget(label_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label_head = new QLabel(centralwidget);
        label_head->setObjectName("label_head");

        horizontalLayout->addWidget(label_head);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

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
        tableView->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->verticalHeader()->setVisible(true);
        tableView->verticalHeader()->setHighlightSections(true);

        verticalLayout->addWidget(tableView);


        verticalLayout_2->addLayout(verticalLayout);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(2, 15);
        SensListsForm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SensListsForm);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 652, 17));
        SensListsForm->setMenuBar(menubar);
        statusbar = new QStatusBar(SensListsForm);
        statusbar->setObjectName("statusbar");
        SensListsForm->setStatusBar(statusbar);

        retranslateUi(SensListsForm);

        QMetaObject::connectSlotsByName(SensListsForm);
    } // setupUi

    void retranslateUi(QMainWindow *SensListsForm)
    {
        SensListsForm->setWindowTitle(QCoreApplication::translate("SensListsForm", "MainWindow", nullptr));
        label_3->setText(QCoreApplication::translate("SensListsForm", "Saukas k\305\253dra", nullptr));
        label_head->setText(QCoreApplication::translate("SensListsForm", "Iek\304\201rtu saraksts", nullptr));
        label->setText(QCoreApplication::translate("SensListsForm", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SensListsForm: public Ui_SensListsForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENSLISTSFORM_H
