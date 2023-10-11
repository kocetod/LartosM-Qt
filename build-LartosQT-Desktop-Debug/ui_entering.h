/********************************************************************************
** Form generated from reading UI file 'entering.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENTERING_H
#define UI_ENTERING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Entering
{
public:
    QPushButton *k5;
    QPushButton *k2;
    QPushButton *k1;
    QPushButton *k8;
    QPushButton *k_del;
    QPushButton *k7;
    QPushButton *btnConfirm;
    QPushButton *k4;
    QPushButton *k_dot;
    QPushButton *k3;
    QPushButton *k6;
    QPushButton *k9;
    QPushButton *k0;
    QLineEdit *txtPassword;
    QLabel *label;

    void setupUi(QDialog *Entering)
    {
        if (Entering->objectName().isEmpty())
            Entering->setObjectName(QStringLiteral("Entering"));
        Entering->setEnabled(true);
        Entering->resize(1280, 800);
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu"));
        Entering->setFont(font);
        Entering->setStyleSheet(QStringLiteral("background-color: black;"));
        k5 = new QPushButton(Entering);
        k5->setObjectName(QStringLiteral("k5"));
        k5->setGeometry(QRect(560, 322, 161, 120));
        QFont font1;
        font1.setFamily(QStringLiteral("Ubuntu"));
        font1.setPointSize(70);
        k5->setFont(font1);
        k5->setStyleSheet(QLatin1String("border: 2px rgb(173, 173, 173);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgb(173, 173, 173);"));
        k2 = new QPushButton(Entering);
        k2->setObjectName(QStringLiteral("k2"));
        k2->setGeometry(QRect(560, 198, 161, 120));
        k2->setFont(font1);
        k2->setStyleSheet(QLatin1String("border: 2px rgb(173, 173, 173);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgb(173, 173, 173);"));
        k1 = new QPushButton(Entering);
        k1->setObjectName(QStringLiteral("k1"));
        k1->setGeometry(QRect(390, 198, 161, 120));
        k1->setFont(font1);
        k1->setFocusPolicy(Qt::StrongFocus);
        k1->setContextMenuPolicy(Qt::DefaultContextMenu);
        k1->setAutoFillBackground(false);
        k1->setStyleSheet(QLatin1String("border: 2px rgb(173, 173, 173);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgb(173, 173, 173);"));
        k1->setInputMethodHints(Qt::ImhNone);
        k1->setAutoDefault(true);
        k1->setFlat(false);
        k8 = new QPushButton(Entering);
        k8->setObjectName(QStringLiteral("k8"));
        k8->setGeometry(QRect(560, 446, 161, 120));
        k8->setFont(font1);
        k8->setStyleSheet(QLatin1String("border: 2px rgb(173, 173, 173);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgb(173, 173, 173);"));
        k_del = new QPushButton(Entering);
        k_del->setObjectName(QStringLiteral("k_del"));
        k_del->setGeometry(QRect(390, 570, 161, 120));
        QFont font2;
        font2.setFamily(QStringLiteral("Ubuntu"));
        font2.setPointSize(42);
        k_del->setFont(font2);
        k_del->setStyleSheet(QLatin1String("border: 2px rgb(173, 173, 173);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgb(173, 173, 173);"));
        k7 = new QPushButton(Entering);
        k7->setObjectName(QStringLiteral("k7"));
        k7->setGeometry(QRect(390, 446, 161, 120));
        k7->setFont(font1);
        k7->setStyleSheet(QLatin1String("border: 2px rgb(173, 173, 173);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgb(173, 173, 173);"));
        btnConfirm = new QPushButton(Entering);
        btnConfirm->setObjectName(QStringLiteral("btnConfirm"));
        btnConfirm->setGeometry(QRect(0, 700, 1281, 101));
        QFont font3;
        font3.setFamily(QStringLiteral("Ubuntu"));
        font3.setPointSize(60);
        btnConfirm->setFont(font3);
        btnConfirm->setStyleSheet(QLatin1String("border: 2px rgb(173, 173, 173);\n"
"padding: 0 8px;\n"
"background: rgb(173, 173, 173);"));
        k4 = new QPushButton(Entering);
        k4->setObjectName(QStringLiteral("k4"));
        k4->setGeometry(QRect(390, 322, 161, 120));
        k4->setFont(font1);
        k4->setStyleSheet(QLatin1String("border: 2px rgb(173, 173, 173);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgb(173, 173, 173);"));
        k_dot = new QPushButton(Entering);
        k_dot->setObjectName(QStringLiteral("k_dot"));
        k_dot->setGeometry(QRect(730, 570, 161, 120));
        k_dot->setFont(font1);
        k_dot->setStyleSheet(QLatin1String("border: 2px rgb(173, 173, 173);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgb(173, 173, 173);"));
        k3 = new QPushButton(Entering);
        k3->setObjectName(QStringLiteral("k3"));
        k3->setGeometry(QRect(730, 198, 161, 120));
        k3->setFont(font1);
        k3->setStyleSheet(QLatin1String("border: 2px rgb(173, 173, 173);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgb(173, 173, 173);"));
        k6 = new QPushButton(Entering);
        k6->setObjectName(QStringLiteral("k6"));
        k6->setGeometry(QRect(730, 322, 161, 120));
        k6->setFont(font1);
        k6->setStyleSheet(QLatin1String("border: 2px rgb(173, 173, 173);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgb(173, 173, 173);"));
        k9 = new QPushButton(Entering);
        k9->setObjectName(QStringLiteral("k9"));
        k9->setGeometry(QRect(730, 446, 161, 120));
        k9->setFont(font1);
        k9->setStyleSheet(QLatin1String("border: 2px rgb(173, 173, 173);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgb(173, 173, 173);"));
        k0 = new QPushButton(Entering);
        k0->setObjectName(QStringLiteral("k0"));
        k0->setGeometry(QRect(560, 570, 161, 120));
        k0->setFont(font1);
        k0->setMouseTracking(false);
        k0->setStyleSheet(QLatin1String("border: 2px rgb(173, 173, 173);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgb(173, 173, 173);"));
        txtPassword = new QLineEdit(Entering);
        txtPassword->setObjectName(QStringLiteral("txtPassword"));
        txtPassword->setGeometry(QRect(364, 110, 551, 81));
        QFont font4;
        font4.setFamily(QStringLiteral("Ubuntu"));
        font4.setPointSize(60);
        font4.setBold(false);
        font4.setWeight(50);
        txtPassword->setFont(font4);
        txtPassword->setStyleSheet(QStringLiteral("background-color: white;"));
        txtPassword->setMaxLength(4);
        txtPassword->setEchoMode(QLineEdit::Password);
        label = new QLabel(Entering);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(280, 10, 711, 81));
        label->setFont(font4);
        label->setStyleSheet(QStringLiteral("color: white;"));

        retranslateUi(Entering);

        k1->setDefault(false);


        QMetaObject::connectSlotsByName(Entering);
    } // setupUi

    void retranslateUi(QDialog *Entering)
    {
        Entering->setWindowTitle(QApplication::translate("Entering", "Dialog", nullptr));
        k5->setText(QApplication::translate("Entering", "5", nullptr));
        k2->setText(QApplication::translate("Entering", "2", nullptr));
        k1->setText(QApplication::translate("Entering", "1", nullptr));
        k8->setText(QApplication::translate("Entering", "8", nullptr));
        k_del->setText(QApplication::translate("Entering", "Del", nullptr));
        k7->setText(QApplication::translate("Entering", "7", nullptr));
        btnConfirm->setText(QApplication::translate("Entering", "Confirm", nullptr));
        k4->setText(QApplication::translate("Entering", "4", nullptr));
        k_dot->setText(QApplication::translate("Entering", ".", nullptr));
        k3->setText(QApplication::translate("Entering", "3", nullptr));
        k6->setText(QApplication::translate("Entering", "6", nullptr));
        k9->setText(QApplication::translate("Entering", "9", nullptr));
        k0->setText(QApplication::translate("Entering", "0", nullptr));
        txtPassword->setInputMask(QString());
        label->setText(QApplication::translate("Entering", "INSERT PASSWORD", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Entering: public Ui_Entering {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENTERING_H
