/********************************************************************************
** Form generated from reading UI file 'scalesmass.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCALESMASS_H
#define UI_SCALESMASS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScalesMass
{
public:

    void setupUi(QWidget *ScalesMass)
    {
        if (ScalesMass->objectName().isEmpty())
            ScalesMass->setObjectName("ScalesMass");
        ScalesMass->resize(400, 300);

        retranslateUi(ScalesMass);

        QMetaObject::connectSlotsByName(ScalesMass);
    } // setupUi

    void retranslateUi(QWidget *ScalesMass)
    {
        ScalesMass->setWindowTitle(QCoreApplication::translate("ScalesMass", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScalesMass: public Ui_ScalesMass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCALESMASS_H
