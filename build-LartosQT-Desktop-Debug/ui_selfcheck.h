/********************************************************************************
** Form generated from reading UI file 'selfcheck.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELFCHECK_H
#define UI_SELFCHECK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_SelfCheck
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *day;
    QLabel *ir;
    QLabel *lrf;
    QLabel *gps;
    QLabel *dmc;
    QLabel *pantilt;

    void setupUi(QDialog *SelfCheck)
    {
        if (SelfCheck->objectName().isEmpty())
            SelfCheck->setObjectName(QStringLiteral("SelfCheck"));
        SelfCheck->resize(1280, 800);
        SelfCheck->setStyleSheet(QStringLiteral("background:black;"));
        label = new QLabel(SelfCheck);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(370, 160, 431, 61));
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu"));
        font.setPointSize(44);
        label->setFont(font);
        label->setStyleSheet(QStringLiteral("color: white;"));
        label_2 = new QLabel(SelfCheck);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(370, 260, 431, 61));
        label_2->setFont(font);
        label_2->setStyleSheet(QStringLiteral("color: white;"));
        label_3 = new QLabel(SelfCheck);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(370, 360, 431, 61));
        label_3->setFont(font);
        label_3->setStyleSheet(QStringLiteral("color: white;"));
        label_4 = new QLabel(SelfCheck);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(370, 460, 431, 61));
        label_4->setFont(font);
        label_4->setStyleSheet(QStringLiteral("color: white;"));
        label_5 = new QLabel(SelfCheck);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(370, 560, 431, 61));
        label_5->setFont(font);
        label_5->setStyleSheet(QStringLiteral("color: white;"));
        label_6 = new QLabel(SelfCheck);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(370, 660, 431, 61));
        label_6->setFont(font);
        label_6->setStyleSheet(QStringLiteral("color: white;"));
        label_7 = new QLabel(SelfCheck);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(285, 20, 711, 101));
        QFont font1;
        font1.setFamily(QStringLiteral("Ubuntu"));
        font1.setPointSize(94);
        label_7->setFont(font1);
        label_7->setStyleSheet(QStringLiteral("color: white;"));
        day = new QLabel(SelfCheck);
        day->setObjectName(QStringLiteral("day"));
        day->setGeometry(QRect(820, 160, 81, 61));
        QFont font2;
        font2.setFamily(QStringLiteral("Ubuntu"));
        font2.setPointSize(46);
        day->setFont(font2);
        day->setStyleSheet(QStringLiteral("color: white;"));
        ir = new QLabel(SelfCheck);
        ir->setObjectName(QStringLiteral("ir"));
        ir->setGeometry(QRect(820, 260, 81, 61));
        ir->setFont(font2);
        ir->setStyleSheet(QStringLiteral("color: white;"));
        lrf = new QLabel(SelfCheck);
        lrf->setObjectName(QStringLiteral("lrf"));
        lrf->setGeometry(QRect(820, 360, 81, 61));
        lrf->setFont(font2);
        lrf->setStyleSheet(QStringLiteral("color: white;"));
        gps = new QLabel(SelfCheck);
        gps->setObjectName(QStringLiteral("gps"));
        gps->setGeometry(QRect(820, 460, 81, 61));
        gps->setFont(font2);
        gps->setStyleSheet(QStringLiteral("color: white;"));
        dmc = new QLabel(SelfCheck);
        dmc->setObjectName(QStringLiteral("dmc"));
        dmc->setGeometry(QRect(820, 560, 81, 61));
        dmc->setFont(font2);
        dmc->setStyleSheet(QStringLiteral("color: white;"));
        pantilt = new QLabel(SelfCheck);
        pantilt->setObjectName(QStringLiteral("pantilt"));
        pantilt->setGeometry(QRect(820, 660, 81, 61));
        pantilt->setFont(font2);
        pantilt->setStyleSheet(QStringLiteral("color: white;"));

        retranslateUi(SelfCheck);

        QMetaObject::connectSlotsByName(SelfCheck);
    } // setupUi

    void retranslateUi(QDialog *SelfCheck)
    {
        SelfCheck->setWindowTitle(QApplication::translate("SelfCheck", "Dialog", nullptr));
        label->setText(QApplication::translate("SelfCheck", "DAY CAMERA....", nullptr));
        label_2->setText(QApplication::translate("SelfCheck", "IR CAMERA.......", nullptr));
        label_3->setText(QApplication::translate("SelfCheck", "LRF.....................", nullptr));
        label_4->setText(QApplication::translate("SelfCheck", "GPS....................", nullptr));
        label_5->setText(QApplication::translate("SelfCheck", "DMC..................", nullptr));
        label_6->setText(QApplication::translate("SelfCheck", "PAN-TILT...........", nullptr));
        label_7->setText(QApplication::translate("SelfCheck", "SELF CHECK", nullptr));
        day->setText(QString());
        ir->setText(QString());
        lrf->setText(QString());
        gps->setText(QString());
        dmc->setText(QString());
        pantilt->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SelfCheck: public Ui_SelfCheck {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELFCHECK_H
