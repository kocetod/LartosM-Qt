/********************************************************************************
** Form generated from reading UI file 'tasks.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKS_H
#define UI_TASKS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_Tasks
{
public:
    QPushButton *task1A;
    QPushButton *task2;
    QPushButton *task3;
    QPushButton *task1B;
    QPushButton *task1C;
    QLabel *label;
    QPushButton *btnConfirm;
    QToolButton *btnBack;

    void setupUi(QDialog *Tasks)
    {
        if (Tasks->objectName().isEmpty())
            Tasks->setObjectName(QStringLiteral("Tasks"));
        Tasks->resize(850, 450);
        Tasks->setStyleSheet(QStringLiteral("background:white;"));
        task1A = new QPushButton(Tasks);
        task1A->setObjectName(QStringLiteral("task1A"));
        task1A->setGeometry(QRect(10, 129, 151, 141));
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu"));
        font.setPointSize(21);
        font.setBold(false);
        font.setWeight(50);
        task1A->setFont(font);
        task1A->setFocusPolicy(Qt::NoFocus);
        task1A->setContextMenuPolicy(Qt::DefaultContextMenu);
        task1A->setAutoFillBackground(false);
        task1A->setStyleSheet(QLatin1String("border: 2px rgb(173, 173, 173);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgb(173, 173, 173);"));
        task1A->setInputMethodHints(Qt::ImhNone);
        task1A->setAutoDefault(true);
        task1A->setFlat(false);
        task2 = new QPushButton(Tasks);
        task2->setObjectName(QStringLiteral("task2"));
        task2->setGeometry(QRect(520, 130, 151, 141));
        QFont font1;
        font1.setFamily(QStringLiteral("Ubuntu"));
        font1.setPointSize(21);
        task2->setFont(font1);
        task2->setFocusPolicy(Qt::NoFocus);
        task2->setContextMenuPolicy(Qt::DefaultContextMenu);
        task2->setAutoFillBackground(false);
        task2->setStyleSheet(QLatin1String("border: 2px rgb(173, 173, 173);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgb(173, 173, 173);"));
        task2->setInputMethodHints(Qt::ImhNone);
        task2->setAutoDefault(true);
        task2->setFlat(false);
        task3 = new QPushButton(Tasks);
        task3->setObjectName(QStringLiteral("task3"));
        task3->setGeometry(QRect(690, 130, 151, 141));
        task3->setFont(font1);
        task3->setFocusPolicy(Qt::NoFocus);
        task3->setContextMenuPolicy(Qt::DefaultContextMenu);
        task3->setAutoFillBackground(false);
        task3->setStyleSheet(QLatin1String("border: 2px rgb(173, 173, 173);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgb(173, 173, 173);"));
        task3->setInputMethodHints(Qt::ImhNone);
        task3->setAutoDefault(true);
        task3->setFlat(false);
        task1B = new QPushButton(Tasks);
        task1B->setObjectName(QStringLiteral("task1B"));
        task1B->setGeometry(QRect(180, 130, 151, 141));
        task1B->setFont(font1);
        task1B->setFocusPolicy(Qt::NoFocus);
        task1B->setContextMenuPolicy(Qt::DefaultContextMenu);
        task1B->setAutoFillBackground(false);
        task1B->setStyleSheet(QLatin1String("border: 2px rgb(173, 173, 173);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgb(173, 173, 173);"));
        task1B->setInputMethodHints(Qt::ImhNone);
        task1B->setAutoDefault(true);
        task1B->setFlat(false);
        task1C = new QPushButton(Tasks);
        task1C->setObjectName(QStringLiteral("task1C"));
        task1C->setGeometry(QRect(350, 130, 151, 141));
        task1C->setFont(font1);
        task1C->setFocusPolicy(Qt::NoFocus);
        task1C->setContextMenuPolicy(Qt::DefaultContextMenu);
        task1C->setAutoFillBackground(false);
        task1C->setStyleSheet(QLatin1String("border: 2px rgb(173, 173, 173);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgb(173, 173, 173);"));
        task1C->setInputMethodHints(Qt::ImhNone);
        task1C->setAutoDefault(true);
        task1C->setFlat(false);
        label = new QLabel(Tasks);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(240, 20, 371, 61));
        QFont font2;
        font2.setFamily(QStringLiteral("Ubuntu"));
        font2.setPointSize(42);
        font2.setBold(false);
        font2.setWeight(50);
        label->setFont(font2);
        btnConfirm = new QPushButton(Tasks);
        btnConfirm->setObjectName(QStringLiteral("btnConfirm"));
        btnConfirm->setGeometry(QRect(290, 330, 261, 81));
        QFont font3;
        font3.setFamily(QStringLiteral("Ubuntu"));
        font3.setPointSize(36);
        btnConfirm->setFont(font3);
        btnConfirm->setStyleSheet(QLatin1String("border: 2px black;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: black;\n"
"color:white;"));
        btnBack = new QToolButton(Tasks);
        btnBack->setObjectName(QStringLiteral("btnBack"));
        btnBack->setGeometry(QRect(10, 370, 111, 71));
        QFont font4;
        font4.setFamily(QStringLiteral("Ubuntu"));
        font4.setPointSize(12);
        font4.setBold(true);
        font4.setWeight(75);
        btnBack->setFont(font4);
        btnBack->setStyleSheet(QLatin1String("border: 2px rgb(173, 173, 173);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgb(173, 173, 173);"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/icons/back.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnBack->setIcon(icon);
        btnBack->setIconSize(QSize(110, 70));
        btnBack->setToolButtonStyle(Qt::ToolButtonIconOnly);

        retranslateUi(Tasks);

        task1A->setDefault(false);
        task2->setDefault(false);
        task3->setDefault(false);
        task1B->setDefault(false);
        task1C->setDefault(false);


        QMetaObject::connectSlotsByName(Tasks);
    } // setupUi

    void retranslateUi(QDialog *Tasks)
    {
        Tasks->setWindowTitle(QApplication::translate("Tasks", "Dialog", nullptr));
        task1A->setText(QApplication::translate("Tasks", "\320\237\320\240\320\220\320\222\320\220\n"
"\320\227\320\220\320\224\320\220\320\247\320\220", nullptr));
        task2->setText(QApplication::translate("Tasks", "\320\236\320\221\320\240\320\220\320\242\320\235\320\220\n"
"\320\227\320\220\320\224\320\220\320\247\320\220", nullptr));
        task3->setText(QApplication::translate("Tasks", "\320\232\320\236\320\240\320\225\320\232-\n"
"\320\246\320\230\320\257 \320\235\320\220\n"
"\320\236\320\223\320\252\320\235\320\257", nullptr));
        task1B->setText(QApplication::translate("Tasks", "\320\236\320\221\320\240\320\220\320\242\320\235\320\220\n"
"\320\227\320\220\320\241\320\225\320\247\320\232\320\220", nullptr));
        task1C->setText(QApplication::translate("Tasks", "\320\233\320\230\320\235\320\225\320\231\320\235\320\220\n"
"\320\227\320\220\320\241\320\225\320\247\320\232\320\220", nullptr));
        label->setText(QApplication::translate("Tasks", "CHOOSE TASK", nullptr));
        btnConfirm->setText(QApplication::translate("Tasks", "Confirm", nullptr));
        btnBack->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Tasks: public Ui_Tasks {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKS_H
