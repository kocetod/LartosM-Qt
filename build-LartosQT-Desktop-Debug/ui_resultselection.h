/********************************************************************************
** Form generated from reading UI file 'resultselection.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESULTSELECTION_H
#define UI_RESULTSELECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_ResultSelection
{
public:
    QGroupBox *grBoxUpdatePosition;
    QLabel *lblNewY;
    QPushButton *btnNo;
    QLabel *lblCurrY;
    QLabel *lblCurrX;
    QLabel *lblNewH;
    QLabel *lblCurrentPos;
    QPushButton *btnUse;
    QLabel *lblNewX;
    QLabel *lblCurrH;
    QLabel *lblNewPos;
    QLabel *lblWantToUse;
    QGroupBox *grBoxPoints;
    QPushButton *btnChoose;
    QTableView *point_listView;
    QPushButton *pointA;
    QPushButton *pointB;
    QPushButton *pointC;
    QPushButton *pointD;
    QPushButton *btnClose;
    QGroupBox *grBoxUpdateDirAngle;
    QPushButton *btnNo_2;
    QLabel *lblCurrDirAngleValue;
    QLabel *lblCurrentDirAngle;
    QPushButton *btnUseDirAngle;
    QLabel *lblNewDirAngleValue;
    QLabel *lblNewDirAngle;
    QLabel *lblWantToUseAngle;

    void setupUi(QDialog *ResultSelection)
    {
        if (ResultSelection->objectName().isEmpty())
            ResultSelection->setObjectName(QStringLiteral("ResultSelection"));
        ResultSelection->resize(870, 500);
        ResultSelection->setStyleSheet(QStringLiteral("background: white;"));
        grBoxUpdatePosition = new QGroupBox(ResultSelection);
        grBoxUpdatePosition->setObjectName(QStringLiteral("grBoxUpdatePosition"));
        grBoxUpdatePosition->setGeometry(QRect(0, 500, 870, 500));
        lblNewY = new QLabel(grBoxUpdatePosition);
        lblNewY->setObjectName(QStringLiteral("lblNewY"));
        lblNewY->setGeometry(QRect(440, 205, 409, 61));
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu"));
        font.setPointSize(30);
        font.setBold(true);
        font.setWeight(75);
        lblNewY->setFont(font);
        lblNewY->setStyleSheet(QStringLiteral("border:1px solid black;"));
        btnNo = new QPushButton(grBoxUpdatePosition);
        btnNo->setObjectName(QStringLiteral("btnNo"));
        btnNo->setGeometry(QRect(460, 400, 301, 91));
        QFont font1;
        font1.setPointSize(70);
        font1.setBold(true);
        font1.setWeight(75);
        btnNo->setFont(font1);
        btnNo->setStyleSheet(QLatin1String("border: 2px solid black;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: lightgray;"));
        lblCurrY = new QLabel(grBoxUpdatePosition);
        lblCurrY->setObjectName(QStringLiteral("lblCurrY"));
        lblCurrY->setGeometry(QRect(325, 85, 334, 61));
        QFont font2;
        font2.setFamily(QStringLiteral("Ubuntu"));
        font2.setPointSize(30);
        lblCurrY->setFont(font2);
        lblCurrY->setStyleSheet(QStringLiteral("border:1px solid black;"));
        lblCurrX = new QLabel(grBoxUpdatePosition);
        lblCurrX->setObjectName(QStringLiteral("lblCurrX"));
        lblCurrX->setGeometry(QRect(0, 85, 324, 61));
        lblCurrX->setFont(font2);
        lblCurrX->setStyleSheet(QStringLiteral("border:1px solid black;"));
        lblNewH = new QLabel(grBoxUpdatePosition);
        lblNewH->setObjectName(QStringLiteral("lblNewH"));
        lblNewH->setGeometry(QRect(285, 268, 301, 61));
        lblNewH->setFont(font);
        lblNewH->setStyleSheet(QStringLiteral("border:1px solid black;"));
        lblCurrentPos = new QLabel(grBoxUpdatePosition);
        lblCurrentPos->setObjectName(QStringLiteral("lblCurrentPos"));
        lblCurrentPos->setGeometry(QRect(100, 25, 671, 51));
        QFont font3;
        font3.setFamily(QStringLiteral("Ubuntu"));
        font3.setPointSize(36);
        lblCurrentPos->setFont(font3);
        btnUse = new QPushButton(grBoxUpdatePosition);
        btnUse->setObjectName(QStringLiteral("btnUse"));
        btnUse->setGeometry(QRect(100, 400, 301, 91));
        btnUse->setFont(font1);
        btnUse->setStyleSheet(QLatin1String("border: 2px solid black;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: lightgray;"));
        lblNewX = new QLabel(grBoxUpdatePosition);
        lblNewX->setObjectName(QStringLiteral("lblNewX"));
        lblNewX->setGeometry(QRect(20, 205, 409, 61));
        lblNewX->setFont(font);
        lblNewX->setStyleSheet(QStringLiteral("border:1px solid black;"));
        lblCurrH = new QLabel(grBoxUpdatePosition);
        lblCurrH->setObjectName(QStringLiteral("lblCurrH"));
        lblCurrH->setGeometry(QRect(660, 85, 209, 61));
        lblCurrH->setFont(font2);
        lblCurrH->setStyleSheet(QStringLiteral("border:1px solid black;"));
        lblNewPos = new QLabel(grBoxUpdatePosition);
        lblNewPos->setObjectName(QStringLiteral("lblNewPos"));
        lblNewPos->setGeometry(QRect(30, 150, 801, 51));
        QFont font4;
        font4.setFamily(QStringLiteral("Ubuntu"));
        font4.setPointSize(35);
        lblNewPos->setFont(font4);
        lblWantToUse = new QLabel(grBoxUpdatePosition);
        lblWantToUse->setObjectName(QStringLiteral("lblWantToUse"));
        lblWantToUse->setGeometry(QRect(15, 329, 841, 71));
        QFont font5;
        font5.setFamily(QStringLiteral("Ubuntu"));
        font5.setPointSize(26);
        lblWantToUse->setFont(font5);
        grBoxPoints = new QGroupBox(ResultSelection);
        grBoxPoints->setObjectName(QStringLiteral("grBoxPoints"));
        grBoxPoints->setGeometry(QRect(0, 0, 870, 500));
        btnChoose = new QPushButton(grBoxPoints);
        btnChoose->setObjectName(QStringLiteral("btnChoose"));
        btnChoose->setGeometry(QRect(430, 390, 301, 91));
        QFont font6;
        font6.setPointSize(40);
        font6.setBold(true);
        font6.setWeight(75);
        btnChoose->setFont(font6);
        btnChoose->setStyleSheet(QLatin1String("border: 2px solid black;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: lightgray;"));
        point_listView = new QTableView(grBoxPoints);
        point_listView->setObjectName(QStringLiteral("point_listView"));
        point_listView->setGeometry(QRect(20, 30, 831, 351));
        QFont font7;
        font7.setPointSize(17);
        point_listView->setFont(font7);
        point_listView->setStyleSheet(QLatin1String("background:white;\n"
"color:black;"));
        point_listView->horizontalHeader()->setCascadingSectionResizes(false);
        point_listView->horizontalHeader()->setHighlightSections(true);
        pointA = new QPushButton(grBoxPoints);
        pointA->setObjectName(QStringLiteral("pointA"));
        pointA->setGeometry(QRect(20, 390, 91, 91));
        QFont font8;
        font8.setFamily(QStringLiteral("Ubuntu"));
        font8.setPointSize(70);
        font8.setBold(true);
        font8.setWeight(75);
        pointA->setFont(font8);
        pointA->setFocusPolicy(Qt::NoFocus);
        pointA->setContextMenuPolicy(Qt::DefaultContextMenu);
        pointA->setAutoFillBackground(false);
        pointA->setStyleSheet(QLatin1String("border: 2px rgb(173, 173, 173);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgb(173, 173, 173);"));
        pointA->setInputMethodHints(Qt::ImhNone);
        pointA->setAutoDefault(true);
        pointA->setFlat(false);
        pointB = new QPushButton(grBoxPoints);
        pointB->setObjectName(QStringLiteral("pointB"));
        pointB->setGeometry(QRect(120, 390, 91, 91));
        pointB->setFont(font8);
        pointB->setFocusPolicy(Qt::NoFocus);
        pointB->setContextMenuPolicy(Qt::DefaultContextMenu);
        pointB->setAutoFillBackground(false);
        pointB->setStyleSheet(QLatin1String("border: 2px rgb(173, 173, 173);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgb(173, 173, 173);"));
        pointB->setInputMethodHints(Qt::ImhNone);
        pointB->setAutoDefault(true);
        pointB->setFlat(false);
        pointC = new QPushButton(grBoxPoints);
        pointC->setObjectName(QStringLiteral("pointC"));
        pointC->setGeometry(QRect(220, 390, 91, 91));
        pointC->setFont(font8);
        pointC->setFocusPolicy(Qt::NoFocus);
        pointC->setContextMenuPolicy(Qt::DefaultContextMenu);
        pointC->setAutoFillBackground(false);
        pointC->setStyleSheet(QLatin1String("border: 2px rgb(173, 173, 173);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgb(173, 173, 173);"));
        pointC->setInputMethodHints(Qt::ImhNone);
        pointC->setAutoDefault(true);
        pointC->setFlat(false);
        pointD = new QPushButton(grBoxPoints);
        pointD->setObjectName(QStringLiteral("pointD"));
        pointD->setGeometry(QRect(320, 390, 91, 91));
        pointD->setFont(font8);
        pointD->setFocusPolicy(Qt::NoFocus);
        pointD->setContextMenuPolicy(Qt::DefaultContextMenu);
        pointD->setAutoFillBackground(false);
        pointD->setStyleSheet(QLatin1String("border: 2px rgb(173, 173, 173);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgb(173, 173, 173);"));
        pointD->setInputMethodHints(Qt::ImhNone);
        pointD->setAutoDefault(true);
        pointD->setFlat(false);
        btnClose = new QPushButton(grBoxPoints);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setGeometry(QRect(750, 390, 101, 91));
        btnClose->setFont(font6);
        btnClose->setStyleSheet(QLatin1String("border: 2px solid black;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: lightgray;"));
        grBoxUpdateDirAngle = new QGroupBox(ResultSelection);
        grBoxUpdateDirAngle->setObjectName(QStringLiteral("grBoxUpdateDirAngle"));
        grBoxUpdateDirAngle->setGeometry(QRect(0, 1000, 870, 500));
        btnNo_2 = new QPushButton(grBoxUpdateDirAngle);
        btnNo_2->setObjectName(QStringLiteral("btnNo_2"));
        btnNo_2->setGeometry(QRect(460, 400, 301, 91));
        btnNo_2->setFont(font1);
        btnNo_2->setStyleSheet(QLatin1String("border: 2px solid black;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: lightgray;"));
        lblCurrDirAngleValue = new QLabel(grBoxUpdateDirAngle);
        lblCurrDirAngleValue->setObjectName(QStringLiteral("lblCurrDirAngleValue"));
        lblCurrDirAngleValue->setGeometry(QRect(240, 100, 381, 61));
        lblCurrDirAngleValue->setFont(font2);
        lblCurrDirAngleValue->setStyleSheet(QStringLiteral("border:1px solid black;"));
        lblCurrentDirAngle = new QLabel(grBoxUpdateDirAngle);
        lblCurrentDirAngle->setObjectName(QStringLiteral("lblCurrentDirAngle"));
        lblCurrentDirAngle->setGeometry(QRect(100, 25, 671, 61));
        lblCurrentDirAngle->setFont(font3);
        btnUseDirAngle = new QPushButton(grBoxUpdateDirAngle);
        btnUseDirAngle->setObjectName(QStringLiteral("btnUseDirAngle"));
        btnUseDirAngle->setGeometry(QRect(100, 400, 301, 91));
        btnUseDirAngle->setFont(font1);
        btnUseDirAngle->setStyleSheet(QLatin1String("border: 2px solid black;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: lightgray;"));
        lblNewDirAngleValue = new QLabel(grBoxUpdateDirAngle);
        lblNewDirAngleValue->setObjectName(QStringLiteral("lblNewDirAngleValue"));
        lblNewDirAngleValue->setGeometry(QRect(238, 250, 381, 61));
        lblNewDirAngleValue->setFont(font);
        lblNewDirAngleValue->setStyleSheet(QStringLiteral("border:1px solid black;"));
        lblNewDirAngle = new QLabel(grBoxUpdateDirAngle);
        lblNewDirAngle->setObjectName(QStringLiteral("lblNewDirAngle"));
        lblNewDirAngle->setGeometry(QRect(30, 180, 801, 61));
        lblNewDirAngle->setFont(font4);
        lblWantToUseAngle = new QLabel(grBoxUpdateDirAngle);
        lblWantToUseAngle->setObjectName(QStringLiteral("lblWantToUseAngle"));
        lblWantToUseAngle->setGeometry(QRect(15, 320, 841, 71));
        lblWantToUseAngle->setFont(font5);

        retranslateUi(ResultSelection);

        pointA->setDefault(false);
        pointB->setDefault(false);
        pointC->setDefault(false);
        pointD->setDefault(false);


        QMetaObject::connectSlotsByName(ResultSelection);
    } // setupUi

    void retranslateUi(QDialog *ResultSelection)
    {
        ResultSelection->setWindowTitle(QApplication::translate("ResultSelection", "Dialog", nullptr));
        grBoxUpdatePosition->setTitle(QString());
        lblNewY->setText(QString());
        btnNo->setText(QApplication::translate("ResultSelection", "No", nullptr));
        lblCurrY->setText(QString());
        lblCurrX->setText(QString());
        lblNewH->setText(QString());
        lblCurrentPos->setText(QApplication::translate("ResultSelection", "Currently used device position:", nullptr));
        btnUse->setText(QApplication::translate("ResultSelection", "Yes", nullptr));
        lblNewX->setText(QString());
        lblCurrH->setText(QString());
        lblNewPos->setText(QApplication::translate("ResultSelection", "Position from the solved task's result:", nullptr));
        lblWantToUse->setText(QApplication::translate("ResultSelection", "Do you want to use the new position from the result?", nullptr));
        grBoxPoints->setTitle(QString());
        btnChoose->setText(QApplication::translate("ResultSelection", "Choose", nullptr));
        pointA->setText(QApplication::translate("ResultSelection", "A", nullptr));
        pointB->setText(QApplication::translate("ResultSelection", "B", nullptr));
        pointC->setText(QApplication::translate("ResultSelection", "C", nullptr));
        pointD->setText(QApplication::translate("ResultSelection", "D", nullptr));
        btnClose->setText(QApplication::translate("ResultSelection", "X", nullptr));
        grBoxUpdateDirAngle->setTitle(QString());
        btnNo_2->setText(QApplication::translate("ResultSelection", "No", nullptr));
        lblCurrDirAngleValue->setText(QString());
        lblCurrentDirAngle->setText(QApplication::translate("ResultSelection", "Currently used direction angle:", nullptr));
        btnUseDirAngle->setText(QApplication::translate("ResultSelection", "Yes", nullptr));
        lblNewDirAngleValue->setText(QString());
        lblNewDirAngle->setText(QApplication::translate("ResultSelection", "Angle from the solved task's result:", nullptr));
        lblWantToUseAngle->setText(QApplication::translate("ResultSelection", "Do you want to use the new angle from the result?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ResultSelection: public Ui_ResultSelection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESULTSELECTION_H
