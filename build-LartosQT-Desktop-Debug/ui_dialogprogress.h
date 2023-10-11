/********************************************************************************
** Form generated from reading UI file 'dialogprogress.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGPROGRESS_H
#define UI_DIALOGPROGRESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DialogProgress
{
public:
    QPushButton *pushButton;

    void setupUi(QDialog *DialogProgress)
    {
        if (DialogProgress->objectName().isEmpty())
            DialogProgress->setObjectName(QStringLiteral("DialogProgress"));
        DialogProgress->resize(335, 213);
        DialogProgress->setStyleSheet(QStringLiteral("background:white;"));
        pushButton = new QPushButton(DialogProgress);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(50, 130, 231, 61));
        QFont font;
        font.setPointSize(26);
        pushButton->setFont(font);
        pushButton->setStyleSheet(QLatin1String("background: gray;\n"
"color:white;\n"
"border-radius:10px;"));

        retranslateUi(DialogProgress);

        QMetaObject::connectSlotsByName(DialogProgress);
    } // setupUi

    void retranslateUi(QDialog *DialogProgress)
    {
        DialogProgress->setWindowTitle(QApplication::translate("DialogProgress", "Dialog", nullptr));
        pushButton->setText(QApplication::translate("DialogProgress", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogProgress: public Ui_DialogProgress {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGPROGRESS_H
