/********************************************************************************
** Form generated from reading UI file 'mainwindowhead.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOWHEAD_H
#define UI_MAINWINDOWHEAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_MainWindowHead
{
public:
    QToolButton *btnBrightScrs;
    QToolButton *btnLrf;
    QToolButton *btnOnOff;
    QToolButton *btnPolarity;
    QToolButton *btnDayIr;
    QToolButton *btnZoom;
    QFrame *Label;
    QLabel *frameLabel;

    void setupUi(QDialog *MainWindowHead)
    {
        if (MainWindowHead->objectName().isEmpty())
            MainWindowHead->setObjectName(QStringLiteral("MainWindowHead"));
        MainWindowHead->setEnabled(true);
        MainWindowHead->resize(1024, 768);
        MainWindowHead->setStyleSheet(QStringLiteral("background:rgb(31, 31, 31);"));
        btnBrightScrs = new QToolButton(MainWindowHead);
        btnBrightScrs->setObjectName(QStringLiteral("btnBrightScrs"));
        btnBrightScrs->setGeometry(QRect(5, 110, 101, 101));
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu"));
        font.setPointSize(40);
        font.setBold(true);
        font.setWeight(75);
        btnBrightScrs->setFont(font);
        btnBrightScrs->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/icons/bright_scr.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnBrightScrs->setIcon(icon);
        btnBrightScrs->setIconSize(QSize(200, 200));
        btnBrightScrs->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnLrf = new QToolButton(MainWindowHead);
        btnLrf->setObjectName(QStringLiteral("btnLrf"));
        btnLrf->setGeometry(QRect(5, 320, 101, 101));
        btnLrf->setFont(font);
        btnLrf->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/prefix1/icons/lrf.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnLrf->setIcon(icon1);
        btnLrf->setIconSize(QSize(200, 200));
        btnLrf->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnOnOff = new QToolButton(MainWindowHead);
        btnOnOff->setObjectName(QStringLiteral("btnOnOff"));
        btnOnOff->setGeometry(QRect(5, 530, 101, 101));
        btnOnOff->setFont(font);
        btnOnOff->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/new/prefix1/icons/onoff.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnOnOff->setIcon(icon2);
        btnOnOff->setIconSize(QSize(200, 200));
        btnOnOff->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnPolarity = new QToolButton(MainWindowHead);
        btnPolarity->setObjectName(QStringLiteral("btnPolarity"));
        btnPolarity->setGeometry(QRect(918, 110, 101, 101));
        btnPolarity->setFont(font);
        btnPolarity->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/new/prefix1/icons/palette.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPolarity->setIcon(icon3);
        btnPolarity->setIconSize(QSize(200, 200));
        btnPolarity->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnDayIr = new QToolButton(MainWindowHead);
        btnDayIr->setObjectName(QStringLiteral("btnDayIr"));
        btnDayIr->setGeometry(QRect(918, 320, 101, 101));
        QFont font1;
        font1.setFamily(QStringLiteral("Ubuntu"));
        font1.setPointSize(34);
        font1.setBold(true);
        font1.setWeight(75);
        btnDayIr->setFont(font1);
        btnDayIr->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/new/prefix1/icons/day.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnDayIr->setIcon(icon4);
        btnDayIr->setIconSize(QSize(200, 200));
        btnDayIr->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnZoom = new QToolButton(MainWindowHead);
        btnZoom->setObjectName(QStringLiteral("btnZoom"));
        btnZoom->setGeometry(QRect(918, 530, 101, 101));
        QFont font2;
        font2.setFamily(QStringLiteral("Ubuntu"));
        font2.setPointSize(60);
        font2.setBold(true);
        font2.setWeight(75);
        btnZoom->setFont(font2);
        btnZoom->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/new/prefix1/icons/zoom1.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnZoom->setIcon(icon5);
        btnZoom->setIconSize(QSize(200, 200));
        btnZoom->setToolButtonStyle(Qt::ToolButtonIconOnly);
        Label = new QFrame(MainWindowHead);
        Label->setObjectName(QStringLiteral("Label"));
        Label->setGeometry(QRect(111, 50, 800, 640));
        QFont font3;
        font3.setFamily(QStringLiteral("Ubuntu"));
        font3.setPointSize(18);
        Label->setFont(font3);
        Label->setFrameShape(QFrame::StyledPanel);
        Label->setFrameShadow(QFrame::Raised);
        frameLabel = new QLabel(Label);
        frameLabel->setObjectName(QStringLiteral("frameLabel"));
        frameLabel->setGeometry(QRect(5, 5, 790, 630));
        QFont font4;
        font4.setFamily(QStringLiteral("Ubuntu"));
        frameLabel->setFont(font4);

        retranslateUi(MainWindowHead);

        QMetaObject::connectSlotsByName(MainWindowHead);
    } // setupUi

    void retranslateUi(QDialog *MainWindowHead)
    {
        MainWindowHead->setWindowTitle(QApplication::translate("MainWindowHead", "Dialog", nullptr));
        btnBrightScrs->setText(QString());
        btnLrf->setText(QApplication::translate("MainWindowHead", "LRF", nullptr));
        btnOnOff->setText(QApplication::translate("MainWindowHead", "ON/\n"
"OFF", nullptr));
        btnPolarity->setText(QString());
        btnDayIr->setText(QApplication::translate("MainWindowHead", "DAY", nullptr));
        btnZoom->setText(QApplication::translate("MainWindowHead", "1X", nullptr));
        frameLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindowHead: public Ui_MainWindowHead {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWHEAD_H
