/********************************************************************************
** Form generated from reading UI file 'incorrect.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INCORRECT_H
#define UI_INCORRECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Incorrect
{
public:
    QPushButton *btnOk;
    QLabel *label;

    void setupUi(QDialog *Incorrect)
    {
        if (Incorrect->objectName().isEmpty())
            Incorrect->setObjectName(QStringLiteral("Incorrect"));
        Incorrect->resize(600, 400);
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu"));
        Incorrect->setFont(font);
        Incorrect->setStyleSheet(QStringLiteral("background: rgb(249, 249, 249);"));
        btnOk = new QPushButton(Incorrect);
        btnOk->setObjectName(QStringLiteral("btnOk"));
        btnOk->setGeometry(QRect(220, 190, 151, 141));
        QFont font1;
        font1.setFamily(QStringLiteral("Ubuntu"));
        font1.setPointSize(50);
        btnOk->setFont(font1);
        btnOk->setStyleSheet(QLatin1String("border: 2px lightgray;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: lightgray;"));
        label = new QLabel(Incorrect);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 60, 571, 101));
        QFont font2;
        font2.setFamily(QStringLiteral("Ubuntu"));
        font2.setPointSize(44);
        label->setFont(font2);

        retranslateUi(Incorrect);

        QMetaObject::connectSlotsByName(Incorrect);
    } // setupUi

    void retranslateUi(QDialog *Incorrect)
    {
        Incorrect->setWindowTitle(QApplication::translate("Incorrect", "Dialog", nullptr));
        btnOk->setText(QApplication::translate("Incorrect", "OK", nullptr));
        label->setText(QApplication::translate("Incorrect", "WRONG PASSWORD!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Incorrect: public Ui_Incorrect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INCORRECT_H
