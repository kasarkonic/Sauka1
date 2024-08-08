/********************************************************************************
** Form generated from reading UI file 'scalesbase.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCALESBASE_H
#define UI_SCALESBASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScalesBase
{
public:

    void setupUi(QWidget *ScalesBase)
    {
        if (ScalesBase->objectName().isEmpty())
            ScalesBase->setObjectName("ScalesBase");
        ScalesBase->resize(400, 300);

        retranslateUi(ScalesBase);

        QMetaObject::connectSlotsByName(ScalesBase);
    } // setupUi

    void retranslateUi(QWidget *ScalesBase)
    {
        ScalesBase->setWindowTitle(QCoreApplication::translate("ScalesBase", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScalesBase: public Ui_ScalesBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCALESBASE_H
