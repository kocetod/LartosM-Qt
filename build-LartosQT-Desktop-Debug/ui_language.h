/********************************************************************************
** Form generated from reading UI file 'language.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LANGUAGE_H
#define UI_LANGUAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Language
{
public:
    QLabel *label_7;
    QPushButton *btnBG;
    QPushButton *btnEN;
    QLabel *label_8;

    void setupUi(QDialog *Language)
    {
        if (Language->objectName().isEmpty())
            Language->setObjectName(QStringLiteral("Language"));
        Language->resize(1280, 800);
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu"));
        Language->setFont(font);
        Language->setStyleSheet(QStringLiteral("background: black;"));
        label_7 = new QLabel(Language);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(250, 190, 771, 101));
        QFont font1;
        font1.setFamily(QStringLiteral("Ubuntu"));
        font1.setPointSize(60);
        font1.setBold(false);
        font1.setWeight(50);
        label_7->setFont(font1);
        label_7->setStyleSheet(QStringLiteral("color: white;"));
        btnBG = new QPushButton(Language);
        btnBG->setObjectName(QStringLiteral("btnBG"));
        btnBG->setGeometry(QRect(200, 400, 351, 231));
        btnBG->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/icons/bg.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnBG->setIcon(icon);
        btnBG->setIconSize(QSize(360, 270));
        btnEN = new QPushButton(Language);
        btnEN->setObjectName(QStringLiteral("btnEN"));
        btnEN->setGeometry(QRect(720, 400, 351, 231));
        btnEN->setFont(font);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/prefix1/icons/en.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        btnEN->setIcon(icon1);
        btnEN->setIconSize(QSize(360, 270));
        label_8 = new QLabel(Language);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(340, 60, 601, 111));
        label_8->setFont(font1);
        label_8->setStyleSheet(QStringLiteral("color: white;"));

        retranslateUi(Language);

        QMetaObject::connectSlotsByName(Language);
    } // setupUi

    void retranslateUi(QDialog *Language)
    {
        Language->setWindowTitle(QApplication::translate("Language", "Dialog", nullptr));
        label_7->setText(QApplication::translate("Language", "CHOOSE LANGUAGE", nullptr));
        btnBG->setText(QString());
        btnEN->setText(QString());
        label_8->setText(QApplication::translate("Language", "\320\230\320\227\320\221\320\225\320\240\320\225\320\242\320\225 \320\225\320\227\320\230\320\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Language: public Ui_Language {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LANGUAGE_H
