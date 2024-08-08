/********************************************************************************
** Form generated from reading UI file 'runprocess.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RUNPROCESS_H
#define UI_RUNPROCESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Runprocess
{
public:
    QLabel *label;

    void setupUi(QWidget *Runprocess)
    {
        if (Runprocess->objectName().isEmpty())
            Runprocess->setObjectName("Runprocess");
        Runprocess->resize(249, 192);
        label = new QLabel(Runprocess);
        label->setObjectName("label");
        label->setGeometry(QRect(70, 80, 111, 41));

        retranslateUi(Runprocess);

        QMetaObject::connectSlotsByName(Runprocess);
    } // setupUi

    void retranslateUi(QWidget *Runprocess)
    {
        Runprocess->setWindowTitle(QCoreApplication::translate("Runprocess", "Form", nullptr));
        label->setText(QCoreApplication::translate("Runprocess", "Runprocess.UI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Runprocess: public Ui_Runprocess {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RUNPROCESS_H
