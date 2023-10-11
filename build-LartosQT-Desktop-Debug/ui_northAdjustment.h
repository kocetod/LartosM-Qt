/********************************************************************************
** Form generated from reading UI file 'northAdjustment.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NORTHADJUSTMENT_H
#define UI_NORTHADJUSTMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_NorthAdjustment
{
public:
    QPushButton *k5;
    QPushButton *k_del;
    QPushButton *k2;
    QPushButton *k1;
    QPushButton *k0;
    QLabel *label;
    QPushButton *btnConfirm;
    QPushButton *k7;
    QPushButton *k_minus;
    QPushButton *k3;
    QPushButton *k9;
    QPushButton *k_plus;
    QPushButton *k6;
    QPushButton *k4;
    QPushButton *k_dot;
    QPushButton *k8;
    QPushButton *btnSkip;
    QLineEdit *txtDegrees;
    QGroupBox *invalid;
    QLabel *lbl;
    QPushButton *btnOK;
    QLineEdit *txtMinutes;
    QLineEdit *txtSeconds;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *lblOperator;

    void setupUi(QDialog *NorthAdjustment)
    {
        if (NorthAdjustment->objectName().isEmpty())
            NorthAdjustment->setObjectName(QStringLiteral("NorthAdjustment"));
        NorthAdjustment->resize(1280, 800);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(16);
        NorthAdjustment->setFont(font);
        NorthAdjustment->setStyleSheet(QStringLiteral("background: rgb(215, 215, 215);"));
        k5 = new QPushButton(NorthAdjustment);
        k5->setObjectName(QStringLiteral("k5"));
        k5->setGeometry(QRect(180, 165, 160, 150));
        QFont font1;
        font1.setFamily(QStringLiteral("Ubuntu"));
        font1.setPointSize(70);
        k5->setFont(font1);
        k5->setFocusPolicy(Qt::NoFocus);
        k5->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"border: 2px solid black;\n"
"padding: 0 8px;\n"
"background: gray;"));
        k_del = new QPushButton(NorthAdjustment);
        k_del->setObjectName(QStringLiteral("k_del"));
        k_del->setGeometry(QRect(180, 645, 331, 151));
        QFont font2;
        font2.setFamily(QStringLiteral("Ubuntu"));
        font2.setPointSize(60);
        k_del->setFont(font2);
        k_del->setFocusPolicy(Qt::NoFocus);
        k_del->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"border: 2px solid black;\n"
"padding: 0 8px;\n"
"background: gray;"));
        k2 = new QPushButton(NorthAdjustment);
        k2->setObjectName(QStringLiteral("k2"));
        k2->setGeometry(QRect(180, 5, 160, 150));
        k2->setFont(font1);
        k2->setFocusPolicy(Qt::NoFocus);
        k2->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"border: 2px solid black;\n"
"padding: 0 8px;\n"
"background: gray;"));
        k1 = new QPushButton(NorthAdjustment);
        k1->setObjectName(QStringLiteral("k1"));
        k1->setGeometry(QRect(10, 5, 160, 150));
        k1->setFont(font1);
        k1->setFocusPolicy(Qt::NoFocus);
        k1->setContextMenuPolicy(Qt::DefaultContextMenu);
        k1->setAutoFillBackground(false);
        k1->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"border: 2px solid black;\n"
"padding: 0 8px;\n"
"background: gray;"));
        k1->setAutoDefault(true);
        k1->setFlat(false);
        k0 = new QPushButton(NorthAdjustment);
        k0->setObjectName(QStringLiteral("k0"));
        k0->setGeometry(QRect(180, 485, 160, 150));
        k0->setFont(font1);
        k0->setFocusPolicy(Qt::NoFocus);
        k0->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"border: 2px solid black;\n"
"padding: 0 8px;\n"
"background: gray;"));
        label = new QLabel(NorthAdjustment);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(530, 120, 731, 201));
        QFont font3;
        font3.setFamily(QStringLiteral("Ubuntu"));
        font3.setPointSize(40);
        label->setFont(font3);
        btnConfirm = new QPushButton(NorthAdjustment);
        btnConfirm->setObjectName(QStringLiteral("btnConfirm"));
        btnConfirm->setGeometry(QRect(650, 460, 241, 101));
        QFont font4;
        font4.setFamily(QStringLiteral("Ubuntu"));
        font4.setPointSize(33);
        btnConfirm->setFont(font4);
        btnConfirm->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"border: 2px solid black;\n"
"padding: 0 8px;\n"
"background: gray;"));
        k7 = new QPushButton(NorthAdjustment);
        k7->setObjectName(QStringLiteral("k7"));
        k7->setGeometry(QRect(10, 325, 160, 150));
        k7->setFont(font1);
        k7->setFocusPolicy(Qt::NoFocus);
        k7->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"border: 2px solid black;\n"
"padding: 0 8px;\n"
"background: gray;"));
        k_minus = new QPushButton(NorthAdjustment);
        k_minus->setObjectName(QStringLiteral("k_minus"));
        k_minus->setGeometry(QRect(10, 485, 160, 150));
        k_minus->setFont(font1);
        k_minus->setFocusPolicy(Qt::NoFocus);
        k_minus->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"border: 2px solid black;\n"
"padding: 0 8px;\n"
"background: gray;"));
        k3 = new QPushButton(NorthAdjustment);
        k3->setObjectName(QStringLiteral("k3"));
        k3->setGeometry(QRect(350, 5, 160, 150));
        k3->setFont(font1);
        k3->setFocusPolicy(Qt::NoFocus);
        k3->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"border: 2px solid black;\n"
"padding: 0 8px;\n"
"background: gray;"));
        k9 = new QPushButton(NorthAdjustment);
        k9->setObjectName(QStringLiteral("k9"));
        k9->setGeometry(QRect(350, 325, 160, 150));
        k9->setFont(font1);
        k9->setFocusPolicy(Qt::NoFocus);
        k9->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"border: 2px solid black;\n"
"padding: 0 8px;\n"
"background: gray;"));
        k_plus = new QPushButton(NorthAdjustment);
        k_plus->setObjectName(QStringLiteral("k_plus"));
        k_plus->setGeometry(QRect(350, 485, 160, 150));
        k_plus->setFont(font1);
        k_plus->setFocusPolicy(Qt::NoFocus);
        k_plus->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"border: 2px solid black;\n"
"padding: 0 8px;\n"
"background: gray;"));
        k6 = new QPushButton(NorthAdjustment);
        k6->setObjectName(QStringLiteral("k6"));
        k6->setGeometry(QRect(350, 165, 160, 150));
        k6->setFont(font1);
        k6->setFocusPolicy(Qt::NoFocus);
        k6->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"border: 2px solid black;\n"
"padding: 0 8px;\n"
"background: gray;"));
        k4 = new QPushButton(NorthAdjustment);
        k4->setObjectName(QStringLiteral("k4"));
        k4->setGeometry(QRect(10, 165, 160, 150));
        k4->setFont(font1);
        k4->setFocusPolicy(Qt::NoFocus);
        k4->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"border: 2px solid black;\n"
"padding: 0 8px;\n"
"background: gray;"));
        k_dot = new QPushButton(NorthAdjustment);
        k_dot->setObjectName(QStringLiteral("k_dot"));
        k_dot->setGeometry(QRect(10, 645, 160, 150));
        k_dot->setFont(font1);
        k_dot->setFocusPolicy(Qt::NoFocus);
        k_dot->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"border: 2px solid black;\n"
"padding: 0 8px;\n"
"background: gray;"));
        k8 = new QPushButton(NorthAdjustment);
        k8->setObjectName(QStringLiteral("k8"));
        k8->setGeometry(QRect(180, 325, 160, 150));
        k8->setFont(font1);
        k8->setFocusPolicy(Qt::NoFocus);
        k8->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"border: 2px solid black;\n"
"padding: 0 8px;\n"
"background: gray;"));
        btnSkip = new QPushButton(NorthAdjustment);
        btnSkip->setObjectName(QStringLiteral("btnSkip"));
        btnSkip->setGeometry(QRect(900, 460, 241, 101));
        QFont font5;
        font5.setFamily(QStringLiteral("Ubuntu"));
        font5.setPointSize(34);
        btnSkip->setFont(font5);
        btnSkip->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"border: 2px solid black;\n"
"padding: 0 8px;\n"
"background: gray;"));
        txtDegrees = new QLineEdit(NorthAdjustment);
        txtDegrees->setObjectName(QStringLiteral("txtDegrees"));
        txtDegrees->setGeometry(QRect(660, 359, 121, 81));
        QFont font6;
        font6.setFamily(QStringLiteral("Ubuntu"));
        font6.setPointSize(32);
        txtDegrees->setFont(font6);
        txtDegrees->setStyleSheet(QLatin1String("border: 2px solid black;\n"
"background-color: white;"));
        txtDegrees->setMaxLength(32767);
        invalid = new QGroupBox(NorthAdjustment);
        invalid->setObjectName(QStringLiteral("invalid"));
        invalid->setGeometry(QRect(640, 330, 521, 291));
        QFont font7;
        font7.setFamily(QStringLiteral("Ubuntu"));
        font7.setPointSize(16);
        invalid->setFont(font7);
        invalid->setStyleSheet(QLatin1String("background: white;\n"
"color:black;\n"
"border: 5px solid black;"));
        lbl = new QLabel(invalid);
        lbl->setObjectName(QStringLiteral("lbl"));
        lbl->setGeometry(QRect(20, 10, 461, 131));
        lbl->setFont(font5);
        lbl->setStyleSheet(QLatin1String("color:black;\n"
"border: 0px;"));
        btnOK = new QPushButton(invalid);
        btnOK->setObjectName(QStringLiteral("btnOK"));
        btnOK->setGeometry(QRect(150, 170, 201, 81));
        QFont font8;
        font8.setFamily(QStringLiteral("Ubuntu"));
        font8.setPointSize(50);
        btnOK->setFont(font8);
        btnOK->setStyleSheet(QLatin1String("border-radius: 10px;\n"
"border: 2px solid black;\n"
"padding: 0 8px;\n"
"background: gray;"));
        btnOK->raise();
        lbl->raise();
        txtMinutes = new QLineEdit(NorthAdjustment);
        txtMinutes->setObjectName(QStringLiteral("txtMinutes"));
        txtMinutes->setGeometry(QRect(835, 360, 121, 81));
        txtMinutes->setFont(font6);
        txtMinutes->setStyleSheet(QLatin1String("border: 2px solid black;\n"
"background-color: white;"));
        txtMinutes->setMaxLength(32767);
        txtSeconds = new QLineEdit(NorthAdjustment);
        txtSeconds->setObjectName(QStringLiteral("txtSeconds"));
        txtSeconds->setGeometry(QRect(1010, 360, 121, 81));
        txtSeconds->setFont(font6);
        txtSeconds->setStyleSheet(QLatin1String("border: 2px solid black;\n"
"background-color: white;"));
        txtSeconds->setMaxLength(32767);
        label_2 = new QLabel(NorthAdjustment);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(785, 360, 31, 41));
        QFont font9;
        font9.setFamily(QStringLiteral("Ubuntu"));
        font9.setPointSize(38);
        label_2->setFont(font9);
        label_3 = new QLabel(NorthAdjustment);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(960, 360, 21, 41));
        label_3->setFont(font9);
        label_4 = new QLabel(NorthAdjustment);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(1135, 360, 31, 41));
        label_4->setFont(font9);
        lblOperator = new QLabel(NorthAdjustment);
        lblOperator->setObjectName(QStringLiteral("lblOperator"));
        lblOperator->setGeometry(QRect(610, 360, 41, 81));
        lblOperator->setFont(font8);
        k5->raise();
        k_del->raise();
        k2->raise();
        k1->raise();
        k0->raise();
        label->raise();
        btnConfirm->raise();
        k7->raise();
        k_minus->raise();
        k3->raise();
        k9->raise();
        k_plus->raise();
        k6->raise();
        k4->raise();
        k_dot->raise();
        k8->raise();
        btnSkip->raise();
        txtDegrees->raise();
        txtMinutes->raise();
        txtSeconds->raise();
        label_2->raise();
        label_3->raise();
        label_4->raise();
        lblOperator->raise();
        invalid->raise();

        retranslateUi(NorthAdjustment);

        k1->setDefault(false);


        QMetaObject::connectSlotsByName(NorthAdjustment);
    } // setupUi

    void retranslateUi(QDialog *NorthAdjustment)
    {
        NorthAdjustment->setWindowTitle(QApplication::translate("NorthAdjustment", "Dialog", nullptr));
        k5->setText(QApplication::translate("NorthAdjustment", "5", nullptr));
        k_del->setText(QApplication::translate("NorthAdjustment", "Delete", nullptr));
        k2->setText(QApplication::translate("NorthAdjustment", "2", nullptr));
        k1->setText(QApplication::translate("NorthAdjustment", "1", nullptr));
        k0->setText(QApplication::translate("NorthAdjustment", "0", nullptr));
        label->setText(QApplication::translate("NorthAdjustment", "          Insert a value for\n"
"      magnetic declination.", nullptr));
        btnConfirm->setText(QApplication::translate("NorthAdjustment", "Confirm", nullptr));
        k7->setText(QApplication::translate("NorthAdjustment", "7", nullptr));
        k_minus->setText(QApplication::translate("NorthAdjustment", "-", nullptr));
        k3->setText(QApplication::translate("NorthAdjustment", "3", nullptr));
        k9->setText(QApplication::translate("NorthAdjustment", "9", nullptr));
        k_plus->setText(QApplication::translate("NorthAdjustment", "+", nullptr));
        k6->setText(QApplication::translate("NorthAdjustment", "6", nullptr));
        k4->setText(QApplication::translate("NorthAdjustment", "4", nullptr));
        k_dot->setText(QApplication::translate("NorthAdjustment", ".", nullptr));
        k8->setText(QApplication::translate("NorthAdjustment", "8", nullptr));
        btnSkip->setText(QApplication::translate("NorthAdjustment", "Skip", nullptr));
        txtDegrees->setInputMask(QString());
        invalid->setTitle(QString());
        lbl->setText(QApplication::translate("NorthAdjustment", "<html><head/><body><p>Insert a value between</p><p>	-10 and +10!</p></body></html>", nullptr));
        btnOK->setText(QApplication::translate("NorthAdjustment", "OK", nullptr));
        txtMinutes->setInputMask(QString());
        txtSeconds->setInputMask(QString());
        label_2->setText(QApplication::translate("NorthAdjustment", "\302\260", nullptr));
        label_3->setText(QApplication::translate("NorthAdjustment", "'", nullptr));
        label_4->setText(QApplication::translate("NorthAdjustment", "\"", nullptr));
        lblOperator->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class NorthAdjustment: public Ui_NorthAdjustment {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NORTHADJUSTMENT_H
