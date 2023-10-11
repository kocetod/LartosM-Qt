/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QToolButton *btnMenu;
    QToolButton *btnMedia;
    QToolButton *btnDayir;
    QToolButton *btnPantilt;
    QToolButton *btnNuc;
    QToolButton *btnZoom;
    QToolButton *btnPolarity;
    QWidget *widget;
    QToolButton *btnExpand;
    QToolButton *btnPantilt_left;
    QToolButton *btnPantilt_up;
    QToolButton *btnPantilt_right;
    QToolButton *btnPantilt_down;
    QFrame *Label;
    QLabel *frameLabel;
    QToolButton *btnLRF;
    QToolButton *btnTasks;
    QToolButton *btnScreenshot;
    QLabel *coordInfo;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(1280, 800);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        MainWindow->setFont(font);
        MainWindow->setFocusPolicy(Qt::NoFocus);
        MainWindow->setStyleSheet(QStringLiteral("background:rgb(31, 31, 31);"));
        MainWindow->setToolButtonStyle(Qt::ToolButtonIconOnly);
        MainWindow->setDockOptions(QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        MainWindow->setUnifiedTitleAndToolBarOnMac(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setFont(font);
        btnMenu = new QToolButton(centralwidget);
        btnMenu->setObjectName(QStringLiteral("btnMenu"));
        btnMenu->setGeometry(QRect(1149, 480, 121, 121));
        QFont font1;
        font1.setFamily(QStringLiteral("Ubuntu"));
        font1.setPointSize(26);
        font1.setBold(true);
        font1.setWeight(75);
        btnMenu->setFont(font1);
        btnMenu->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/icons/menu.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnMenu->setIcon(icon);
        btnMenu->setIconSize(QSize(200, 200));
        btnMenu->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnMedia = new QToolButton(centralwidget);
        btnMedia->setObjectName(QStringLiteral("btnMedia"));
        btnMedia->setGeometry(QRect(10, 480, 121, 121));
        QFont font2;
        font2.setFamily(QStringLiteral("Ubuntu"));
        font2.setPointSize(24);
        font2.setBold(true);
        font2.setWeight(75);
        btnMedia->setFont(font2);
        btnMedia->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/prefix1/icons/media.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnMedia->setIcon(icon1);
        btnMedia->setIconSize(QSize(200, 200));
        btnMedia->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnDayir = new QToolButton(centralwidget);
        btnDayir->setObjectName(QStringLiteral("btnDayir"));
        btnDayir->setGeometry(QRect(10, 180, 121, 121));
        btnDayir->setFont(font2);
        btnDayir->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/new/prefix1/icons/day.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnDayir->setIcon(icon2);
        btnDayir->setIconSize(QSize(200, 200));
        btnDayir->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnPantilt = new QToolButton(centralwidget);
        btnPantilt->setObjectName(QStringLiteral("btnPantilt"));
        btnPantilt->setGeometry(QRect(10, 330, 121, 121));
        QFont font3;
        font3.setFamily(QStringLiteral("Ubuntu"));
        font3.setPointSize(30);
        font3.setBold(true);
        font3.setWeight(75);
        btnPantilt->setFont(font3);
        btnPantilt->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/new/prefix1/icons/pantilt_.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPantilt->setIcon(icon3);
        btnPantilt->setIconSize(QSize(200, 200));
        btnPantilt->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnNuc = new QToolButton(centralwidget);
        btnNuc->setObjectName(QStringLiteral("btnNuc"));
        btnNuc->setGeometry(QRect(1149, 35, 121, 121));
        QFont font4;
        font4.setFamily(QStringLiteral("Ubuntu"));
        font4.setPointSize(40);
        font4.setBold(true);
        font4.setWeight(75);
        btnNuc->setFont(font4);
        btnNuc->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/new/prefix1/icons/shutter_closed.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnNuc->setIcon(icon4);
        btnNuc->setIconSize(QSize(200, 200));
        btnNuc->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnZoom = new QToolButton(centralwidget);
        btnZoom->setObjectName(QStringLiteral("btnZoom"));
        btnZoom->setGeometry(QRect(1149, 180, 121, 121));
        QFont font5;
        font5.setFamily(QStringLiteral("Ubuntu"));
        font5.setPointSize(46);
        font5.setBold(true);
        font5.setWeight(75);
        btnZoom->setFont(font5);
        btnZoom->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/new/prefix1/icons/zoom1.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnZoom->setIcon(icon5);
        btnZoom->setIconSize(QSize(200, 200));
        btnZoom->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnPolarity = new QToolButton(centralwidget);
        btnPolarity->setObjectName(QStringLiteral("btnPolarity"));
        btnPolarity->setGeometry(QRect(1149, 330, 121, 121));
        btnPolarity->setFont(font1);
        btnPolarity->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/new/prefix1/icons/palette.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPolarity->setIcon(icon6);
        btnPolarity->setIconSize(QSize(200, 200));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(140, 35, 1001, 711));
        QFont font6;
        font6.setFamily(QStringLiteral("Ubuntu"));
        widget->setFont(font6);
        btnExpand = new QToolButton(widget);
        btnExpand->setObjectName(QStringLiteral("btnExpand"));
        btnExpand->setGeometry(QRect(910, 620, 91, 91));
        btnExpand->setFont(font6);
        btnExpand->setStyleSheet(QLatin1String("border: 2px rgba(255, 255, 255, 0);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgba(255, 255, 255, 0);"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/new/prefix1/icons/expand.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnExpand->setIcon(icon7);
        btnExpand->setIconSize(QSize(90, 90));
        btnPantilt_left = new QToolButton(widget);
        btnPantilt_left->setObjectName(QStringLiteral("btnPantilt_left"));
        btnPantilt_left->setGeometry(QRect(-11, 280, 150, 150));
        btnPantilt_left->setFont(font6);
        btnPantilt_left->setStyleSheet(QLatin1String("border: 2px rgba(255, 255, 255, 0);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgba(255, 255, 255, 0);"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/new/prefix1/icons/left.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPantilt_left->setIcon(icon8);
        btnPantilt_left->setIconSize(QSize(150, 150));
        btnPantilt_up = new QToolButton(widget);
        btnPantilt_up->setObjectName(QStringLiteral("btnPantilt_up"));
        btnPantilt_up->setGeometry(QRect(425, -21, 150, 150));
        btnPantilt_up->setFont(font6);
        btnPantilt_up->setStyleSheet(QLatin1String("border: 2px rgba(255, 255, 255, 0);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgba(255, 255, 255, 0);"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/new/prefix1/icons/up.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPantilt_up->setIcon(icon9);
        btnPantilt_up->setIconSize(QSize(150, 150));
        btnPantilt_right = new QToolButton(widget);
        btnPantilt_right->setObjectName(QStringLiteral("btnPantilt_right"));
        btnPantilt_right->setGeometry(QRect(861, 280, 150, 150));
        btnPantilt_right->setFont(font6);
        btnPantilt_right->setStyleSheet(QLatin1String("border: 2px rgba(255, 255, 255, 0);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgba(255, 255, 255, 0);"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/new/prefix1/icons/right.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPantilt_right->setIcon(icon10);
        btnPantilt_right->setIconSize(QSize(150, 150));
        btnPantilt_down = new QToolButton(widget);
        btnPantilt_down->setObjectName(QStringLiteral("btnPantilt_down"));
        btnPantilt_down->setGeometry(QRect(425, 580, 150, 150));
        btnPantilt_down->setFont(font6);
        btnPantilt_down->setStyleSheet(QLatin1String("border: 2px rgba(255, 255, 255, 0);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgba(255, 255, 255, 0);"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/new/prefix1/icons/down.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPantilt_down->setIcon(icon11);
        btnPantilt_down->setIconSize(QSize(150, 150));
        Label = new QFrame(widget);
        Label->setObjectName(QStringLiteral("Label"));
        Label->setGeometry(QRect(0, 0, 1001, 711));
        QFont font7;
        font7.setFamily(QStringLiteral("Ubuntu"));
        font7.setPointSize(18);
        Label->setFont(font7);
        Label->setFrameShape(QFrame::StyledPanel);
        Label->setFrameShadow(QFrame::Raised);
        frameLabel = new QLabel(Label);
        frameLabel->setObjectName(QStringLiteral("frameLabel"));
        frameLabel->setGeometry(QRect(5, 6, 990, 700));
        frameLabel->setFont(font6);
        Label->raise();
        btnExpand->raise();
        btnPantilt_left->raise();
        btnPantilt_right->raise();
        btnPantilt_down->raise();
        btnPantilt_up->raise();
        btnLRF = new QToolButton(centralwidget);
        btnLRF->setObjectName(QStringLiteral("btnLRF"));
        btnLRF->setGeometry(QRect(10, 35, 121, 121));
        btnLRF->setFont(font4);
        btnLRF->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/new/prefix1/icons/lrf.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnLRF->setIcon(icon12);
        btnLRF->setIconSize(QSize(200, 200));
        btnLRF->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnTasks = new QToolButton(centralwidget);
        btnTasks->setObjectName(QStringLiteral("btnTasks"));
        btnTasks->setGeometry(QRect(10, 625, 121, 121));
        btnTasks->setFont(font2);
        btnTasks->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/new/prefix1/icons/tasks.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnTasks->setIcon(icon13);
        btnTasks->setIconSize(QSize(120, 120));
        btnTasks->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnScreenshot = new QToolButton(centralwidget);
        btnScreenshot->setObjectName(QStringLiteral("btnScreenshot"));
        btnScreenshot->setGeometry(QRect(1149, 625, 121, 121));
        QFont font8;
        font8.setFamily(QStringLiteral("Ubuntu"));
        font8.setPointSize(20);
        font8.setBold(true);
        font8.setWeight(75);
        btnScreenshot->setFont(font8);
        btnScreenshot->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/new/prefix1/icons/scr.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnScreenshot->setIcon(icon14);
        btnScreenshot->setIconSize(QSize(200, 200));
        btnScreenshot->setToolButtonStyle(Qt::ToolButtonIconOnly);
        coordInfo = new QLabel(centralwidget);
        coordInfo->setObjectName(QStringLiteral("coordInfo"));
        coordInfo->setGeometry(QRect(0, 750, 1281, 50));
        QFont font9;
        font9.setFamily(QStringLiteral("Ubuntu"));
        font9.setPointSize(30);
        coordInfo->setFont(font9);
        coordInfo->setStyleSheet(QStringLiteral("color:white;"));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        btnMenu->setText(QApplication::translate("MainWindow", "MENU", nullptr));
        btnMedia->setText(QApplication::translate("MainWindow", "MEDIA", nullptr));
        btnDayir->setText(QApplication::translate("MainWindow", "DAY", nullptr));
        btnPantilt->setText(QApplication::translate("MainWindow", "PAN-\n"
"TILT", nullptr));
        btnNuc->setText(QApplication::translate("MainWindow", "NUC", nullptr));
        btnZoom->setText(QApplication::translate("MainWindow", "1X", nullptr));
        btnPolarity->setText(QApplication::translate("MainWindow", "POLA-\n"
"RITY", nullptr));
        btnExpand->setText(QString());
        btnPantilt_left->setText(QString());
        btnPantilt_up->setText(QString());
        btnPantilt_right->setText(QString());
        btnPantilt_down->setText(QString());
        frameLabel->setText(QString());
        btnLRF->setText(QApplication::translate("MainWindow", "LRF", nullptr));
        btnTasks->setText(QApplication::translate("MainWindow", "TASKS", nullptr));
        btnScreenshot->setText(QApplication::translate("MainWindow", "SCREEN\n"
"SHOT", nullptr));
        coordInfo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
