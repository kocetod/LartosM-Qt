/********************************************************************************
** Form generated from reading UI file 'calibration.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALIBRATION_H
#define UI_CALIBRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Calibration
{
public:
    QPushButton *btnTryAgain;
    QLabel *label;
    QProgressBar *progressBar;
    QLabel *lblFailed;
    QPushButton *btnSkip;

    void setupUi(QDialog *Calibration)
    {
        if (Calibration->objectName().isEmpty())
            Calibration->setObjectName(QStringLiteral("Calibration"));
        Calibration->resize(1280, 800);
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu"));
        Calibration->setFont(font);
        Calibration->setLayoutDirection(Qt::LeftToRight);
        Calibration->setStyleSheet(QStringLiteral("background: lightgray;"));
        btnTryAgain = new QPushButton(Calibration);
        btnTryAgain->setObjectName(QStringLiteral("btnTryAgain"));
        btnTryAgain->setGeometry(QRect(0, 700, 1281, 101));
        QFont font1;
        font1.setFamily(QStringLiteral("Ubuntu"));
        font1.setPointSize(60);
        btnTryAgain->setFont(font1);
        btnTryAgain->setStyleSheet(QLatin1String("border: 2px solid gray;\n"
"padding: 0 8px;\n"
"background: solid gray;"));
        label = new QLabel(Calibration);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 200, 1261, 131));
        QFont font2;
        font2.setFamily(QStringLiteral("Ubuntu"));
        font2.setPointSize(52);
        font2.setBold(false);
        font2.setWeight(50);
        label->setFont(font2);
        label->setWordWrap(false);
        progressBar = new QProgressBar(Calibration);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(45, 450, 1181, 71));
        QFont font3;
        font3.setFamily(QStringLiteral("Ubuntu"));
        font3.setPointSize(22);
        progressBar->setFont(font3);
        progressBar->setValue(0);
        progressBar->setTextVisible(false);
        progressBar->setInvertedAppearance(false);
        lblFailed = new QLabel(Calibration);
        lblFailed->setObjectName(QStringLiteral("lblFailed"));
        lblFailed->setGeometry(QRect(345, 580, 591, 71));
        QFont font4;
        font4.setFamily(QStringLiteral("Ubuntu"));
        font4.setPointSize(44);
        font4.setBold(false);
        font4.setWeight(50);
        lblFailed->setFont(font4);
        btnSkip = new QPushButton(Calibration);
        btnSkip->setObjectName(QStringLiteral("btnSkip"));
        btnSkip->setGeometry(QRect(930, 0, 351, 101));
        QFont font5;
        font5.setFamily(QStringLiteral("Ubuntu"));
        font5.setPointSize(40);
        btnSkip->setFont(font5);
        btnSkip->setStyleSheet(QLatin1String("border: 2px solid white;\n"
"padding: 0 8px;\n"
"background: solid gray;"));

        retranslateUi(Calibration);

        QMetaObject::connectSlotsByName(Calibration);
    } // setupUi

    void retranslateUi(QDialog *Calibration)
    {
        Calibration->setWindowTitle(QApplication::translate("Calibration", "Dialog", nullptr));
        btnTryAgain->setText(QApplication::translate("Calibration", "TRY AGAIN", nullptr));
        label->setText(QApplication::translate("Calibration", "SELF CALIBRATION OF DMC", nullptr));
        lblFailed->setText(QApplication::translate("Calibration", "CALIBRATION FAILED!", nullptr));
        btnSkip->setText(QApplication::translate("Calibration", "SKIP", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Calibration: public Ui_Calibration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALIBRATION_H
