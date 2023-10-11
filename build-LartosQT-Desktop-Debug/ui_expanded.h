/********************************************************************************
** Form generated from reading UI file 'expanded.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPANDED_H
#define UI_EXPANDED_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Expanded
{
public:
    QWidget *video;
    QToolButton *btnLRF;
    QToolButton *btnDayir;
    QGroupBox *groupBox;
    QPushButton *btnChange;
    QLabel *label;
    QPushButton *calculate;
    QToolButton *btnInfo;
    QToolButton *btnPoints;
    QPushButton *correction;
    QToolButton *btnBack;
    QToolButton *btnDayir_ex;
    QToolButton *btnZoom_ex;
    QToolButton *btnNuc_ex;
    QToolButton *btnPolarity_ex;
    QToolButton *btnPantilt;
    QToolButton *btnZoom;
    QToolButton *btnPantilt_up;
    QToolButton *btnPantilt_left;
    QToolButton *btnPantilt_right;
    QToolButton *btnPantilt_down;
    QToolButton *btnPantilt_ex;
    QToolButton *btnScreenshot;
    QFrame *keyboard;
    QPushButton *k1;
    QPushButton *k3;
    QPushButton *k7;
    QPushButton *k8;
    QPushButton *k2;
    QPushButton *k0;
    QPushButton *k_minus;
    QPushButton *k5;
    QPushButton *k9;
    QPushButton *k4;
    QPushButton *k6;
    QPushButton *del;
    QPushButton *k_dot;
    QLabel *frameLabel;
    QLabel *coordInfo;
    QFrame *frame1B;
    QLabel *label_26;
    QLabel *label_21;
    QLabel *label_18;
    QLabel *label_20;
    QLabel *x_1B;
    QLabel *y_1B;
    QLabel *label_19;
    QLabel *label_23;
    QLabel *label_27;
    QLineEdit *Ax_1B;
    QLineEdit *Ay_1B;
    QLineEdit *Bx_1B;
    QLineEdit *By_1B;
    QLineEdit *Cx_1B;
    QLineEdit *Cy_1B;
    QLineEdit *AB_1B;
    QLineEdit *AC_1B;
    QLineEdit *AD_1B;
    QLineEdit *Dx_1B;
    QLineEdit *Dy_1B;
    QToolButton *btnDirAngleType_1B;
    QFrame *frame1C;
    QLabel *label_38;
    QLabel *y_1C;
    QLabel *label_33;
    QLabel *x_1C;
    QLabel *label_32;
    QLabel *label_30;
    QLineEdit *DistA_1C;
    QLineEdit *DistB_1C;
    QLineEdit *Ax_1C;
    QLineEdit *Ay_1C;
    QLineEdit *Bx_1C;
    QLineEdit *By_1C;
    QFrame *frame2;
    QLabel *x_2;
    QLabel *label_35;
    QLabel *y_2;
    QLabel *label_31;
    QLineEdit *Ax_2;
    QLineEdit *Ay_2;
    QLineEdit *Bx_2;
    QLineEdit *By_2;
    QFrame *frame3;
    QLabel *y_3;
    QLabel *label_51;
    QLabel *x_3;
    QLabel *label_44;
    QLabel *label_50;
    QLabel *label_39;
    QLineEdit *TH_3;
    QLineEdit *RH_3;
    QLineEdit *Tx_3;
    QLineEdit *Ty_3;
    QLineEdit *Rx_3;
    QLineEdit *Ry_3;
    QFrame *frame1A;
    QLabel *x_1A;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *y_1A;
    QLabel *label_6;
    QLineEdit *Ax_1a;
    QLineEdit *Ay_1a;
    QLineEdit *H_1A;
    QLineEdit *Dist_1A;
    QLineEdit *AB_1A;
    QLineEdit *Incl_1A;
    QToolButton *btnDirAngleType_1A;
    QGroupBox *result;
    QLabel *result_text_3;
    QLabel *result_text_2;
    QLabel *result_text_4;
    QLabel *result_text_1;
    QLabel *result_text_5;
    QLabel *result_text_6;
    QToolButton *btnDirAngleType;
    QGroupBox *grBoxPixmap;
    QLabel *task_pixmap;
    QLabel *lblTaskName;
    QLabel *lblTaskDescription;
    QToolButton *btnClose;

    void setupUi(QDialog *Expanded)
    {
        if (Expanded->objectName().isEmpty())
            Expanded->setObjectName(QStringLiteral("Expanded"));
        Expanded->resize(1280, 800);
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu"));
        Expanded->setFont(font);
        Expanded->setStyleSheet(QStringLiteral("background: black;"));
        video = new QWidget(Expanded);
        video->setObjectName(QStringLiteral("video"));
        video->setGeometry(QRect(0, 0, 1280, 800));
        video->setFont(font);
        video->setFocusPolicy(Qt::NoFocus);
        btnLRF = new QToolButton(video);
        btnLRF->setObjectName(QStringLiteral("btnLRF"));
        btnLRF->setGeometry(QRect(2, 110, 151, 101));
        QFont font1;
        font1.setPointSize(60);
        font1.setBold(true);
        font1.setWeight(75);
        btnLRF->setFont(font1);
        btnLRF->setStyleSheet(QLatin1String("border: 2px solid gray;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: black;"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/icons/lrf.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnLRF->setIcon(icon);
        btnLRF->setIconSize(QSize(200, 200));
        btnLRF->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnDayir = new QToolButton(video);
        btnDayir->setObjectName(QStringLiteral("btnDayir"));
        btnDayir->setGeometry(QRect(2, 2, 151, 101));
        QFont font2;
        font2.setFamily(QStringLiteral("Ubuntu"));
        font2.setPointSize(30);
        font2.setBold(true);
        font2.setWeight(75);
        btnDayir->setFont(font2);
        btnDayir->setStyleSheet(QLatin1String("border: 2px solid gray;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: black;"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/prefix1/icons/day.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnDayir->setIcon(icon1);
        btnDayir->setIconSize(QSize(200, 200));
        btnDayir->setToolButtonStyle(Qt::ToolButtonIconOnly);
        groupBox = new QGroupBox(video);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(940, -10, 341, 811));
        groupBox->setFont(font);
        groupBox->setStyleSheet(QStringLiteral(""));
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        groupBox->setChecked(false);
        btnChange = new QPushButton(groupBox);
        btnChange->setObjectName(QStringLiteral("btnChange"));
        btnChange->setGeometry(QRect(0, 12, 331, 70));
        QFont font3;
        font3.setFamily(QStringLiteral("Ubuntu"));
        font3.setPointSize(30);
        font3.setBold(false);
        font3.setWeight(50);
        btnChange->setFont(font3);
        btnChange->setStyleSheet(QLatin1String("border: 2px solid gray;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 100, 81, 21));
        QFont font4;
        font4.setFamily(QStringLiteral("Ubuntu"));
        font4.setPointSize(13);
        font4.setBold(true);
        font4.setWeight(75);
        label->setFont(font4);
        label->setStyleSheet(QStringLiteral("color:white;"));
        calculate = new QPushButton(groupBox);
        calculate->setObjectName(QStringLiteral("calculate"));
        calculate->setGeometry(QRect(10, 360, 321, 71));
        QFont font5;
        font5.setFamily(QStringLiteral("Ubuntu"));
        font5.setPointSize(34);
        calculate->setFont(font5);
        calculate->setFocusPolicy(Qt::NoFocus);
        calculate->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        btnInfo = new QToolButton(groupBox);
        btnInfo->setObjectName(QStringLiteral("btnInfo"));
        btnInfo->setGeometry(QRect(3, 83, 51, 51));
        btnInfo->setStyleSheet(QLatin1String("background:white;\n"
"border-radius: 25px;\n"
"border: 3px solid gray;"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/new/prefix1/icons/info.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnInfo->setIcon(icon2);
        btnInfo->setIconSize(QSize(100, 100));
        btnPoints = new QToolButton(groupBox);
        btnPoints->setObjectName(QStringLiteral("btnPoints"));
        btnPoints->setGeometry(QRect(280, 83, 51, 51));
        QFont font6;
        font6.setFamily(QStringLiteral("DejaVu Serif"));
        font6.setPointSize(32);
        font6.setBold(true);
        font6.setItalic(false);
        font6.setWeight(75);
        btnPoints->setFont(font6);
        btnPoints->setStyleSheet(QLatin1String("background:white;\n"
"border-radius: 25px;\n"
"border: 3px solid gray;"));
        btnPoints->setIconSize(QSize(100, 100));
        correction = new QPushButton(groupBox);
        correction->setObjectName(QStringLiteral("correction"));
        correction->setGeometry(QRect(10, 360, 321, 71));
        QFont font7;
        font7.setFamily(QStringLiteral("Ubuntu"));
        font7.setPointSize(25);
        correction->setFont(font7);
        correction->setFocusPolicy(Qt::NoFocus);
        correction->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        btnBack = new QToolButton(video);
        btnBack->setObjectName(QStringLiteral("btnBack"));
        btnBack->setGeometry(QRect(10, 729, 101, 61));
        QFont font8;
        font8.setFamily(QStringLiteral("Ubuntu"));
        font8.setPointSize(12);
        font8.setBold(true);
        font8.setWeight(75);
        btnBack->setFont(font8);
        btnBack->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/new/prefix1/icons/back.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnBack->setIcon(icon3);
        btnBack->setIconSize(QSize(100, 60));
        btnBack->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnDayir_ex = new QToolButton(video);
        btnDayir_ex->setObjectName(QStringLiteral("btnDayir_ex"));
        btnDayir_ex->setGeometry(QRect(130, 610, 121, 121));
        QFont font9;
        font9.setFamily(QStringLiteral("Ubuntu"));
        font9.setPointSize(24);
        font9.setBold(true);
        font9.setWeight(75);
        btnDayir_ex->setFont(font9);
        btnDayir_ex->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        btnDayir_ex->setIcon(icon1);
        btnDayir_ex->setIconSize(QSize(200, 200));
        btnDayir_ex->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnZoom_ex = new QToolButton(video);
        btnZoom_ex->setObjectName(QStringLiteral("btnZoom_ex"));
        btnZoom_ex->setGeometry(QRect(260, 610, 121, 121));
        QFont font10;
        font10.setFamily(QStringLiteral("Ubuntu"));
        font10.setPointSize(46);
        font10.setBold(true);
        font10.setWeight(75);
        btnZoom_ex->setFont(font10);
        btnZoom_ex->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/new/prefix1/icons/zoom1.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnZoom_ex->setIcon(icon4);
        btnZoom_ex->setIconSize(QSize(200, 200));
        btnZoom_ex->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnNuc_ex = new QToolButton(video);
        btnNuc_ex->setObjectName(QStringLiteral("btnNuc_ex"));
        btnNuc_ex->setGeometry(QRect(390, 610, 121, 121));
        QFont font11;
        font11.setFamily(QStringLiteral("Ubuntu"));
        font11.setPointSize(40);
        font11.setBold(true);
        font11.setWeight(75);
        btnNuc_ex->setFont(font11);
        btnNuc_ex->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/new/prefix1/icons/shutter_closed.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnNuc_ex->setIcon(icon5);
        btnNuc_ex->setIconSize(QSize(200, 200));
        btnNuc_ex->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnPolarity_ex = new QToolButton(video);
        btnPolarity_ex->setObjectName(QStringLiteral("btnPolarity_ex"));
        btnPolarity_ex->setGeometry(QRect(520, 610, 121, 121));
        QFont font12;
        font12.setFamily(QStringLiteral("Ubuntu"));
        font12.setPointSize(26);
        font12.setBold(true);
        font12.setWeight(75);
        btnPolarity_ex->setFont(font12);
        btnPolarity_ex->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/new/prefix1/icons/palette.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPolarity_ex->setIcon(icon6);
        btnPolarity_ex->setIconSize(QSize(200, 200));
        btnPolarity_ex->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnPantilt = new QToolButton(video);
        btnPantilt->setObjectName(QStringLiteral("btnPantilt"));
        btnPantilt->setGeometry(QRect(783, 2, 151, 101));
        QFont font13;
        font13.setFamily(QStringLiteral("Ubuntu"));
        font13.setPointSize(32);
        font13.setBold(true);
        font13.setWeight(75);
        btnPantilt->setFont(font13);
        btnPantilt->setStyleSheet(QLatin1String("border: 2px solid gray;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: black;"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/new/prefix1/icons/pantilt_.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPantilt->setIcon(icon7);
        btnPantilt->setIconSize(QSize(200, 200));
        btnPantilt->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnZoom = new QToolButton(video);
        btnZoom->setObjectName(QStringLiteral("btnZoom"));
        btnZoom->setGeometry(QRect(783, 110, 151, 101));
        QFont font14;
        font14.setFamily(QStringLiteral("Ubuntu"));
        font14.setPointSize(50);
        font14.setBold(true);
        font14.setWeight(75);
        btnZoom->setFont(font14);
        btnZoom->setStyleSheet(QLatin1String("border: 2px solid gray;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: black;"));
        btnZoom->setIcon(icon4);
        btnZoom->setIconSize(QSize(200, 200));
        btnZoom->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnPantilt_up = new QToolButton(video);
        btnPantilt_up->setObjectName(QStringLiteral("btnPantilt_up"));
        btnPantilt_up->setGeometry(QRect(395, -20, 150, 150));
        btnPantilt_up->setFont(font);
        btnPantilt_up->setStyleSheet(QLatin1String("border: 2px rgba(255, 255, 255, 0);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgba(255, 255, 255, 0);"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/new/prefix1/icons/up.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPantilt_up->setIcon(icon8);
        btnPantilt_up->setIconSize(QSize(150, 150));
        btnPantilt_left = new QToolButton(video);
        btnPantilt_left->setObjectName(QStringLiteral("btnPantilt_left"));
        btnPantilt_left->setGeometry(QRect(0, 325, 150, 150));
        btnPantilt_left->setFont(font);
        btnPantilt_left->setStyleSheet(QLatin1String("border: 2px rgba(255, 255, 255, 0);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgba(255, 255, 255, 0);"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/new/prefix1/icons/left.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPantilt_left->setIcon(icon9);
        btnPantilt_left->setIconSize(QSize(150, 150));
        btnPantilt_right = new QToolButton(video);
        btnPantilt_right->setObjectName(QStringLiteral("btnPantilt_right"));
        btnPantilt_right->setGeometry(QRect(790, 325, 150, 150));
        btnPantilt_right->setFont(font);
        btnPantilt_right->setStyleSheet(QLatin1String("border: 2px rgba(255, 255, 255, 0);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgba(255, 255, 255, 0);"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/new/prefix1/icons/right.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPantilt_right->setIcon(icon10);
        btnPantilt_right->setIconSize(QSize(150, 150));
        btnPantilt_down = new QToolButton(video);
        btnPantilt_down->setObjectName(QStringLiteral("btnPantilt_down"));
        btnPantilt_down->setGeometry(QRect(395, 670, 150, 150));
        btnPantilt_down->setFont(font);
        btnPantilt_down->setStyleSheet(QLatin1String("border: 2px rgba(255, 255, 255, 0);\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: rgba(255, 255, 255, 0);"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/new/prefix1/icons/down.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPantilt_down->setIcon(icon11);
        btnPantilt_down->setIconSize(QSize(150, 150));
        btnPantilt_ex = new QToolButton(video);
        btnPantilt_ex->setObjectName(QStringLiteral("btnPantilt_ex"));
        btnPantilt_ex->setGeometry(QRect(650, 610, 121, 121));
        btnPantilt_ex->setFont(font2);
        btnPantilt_ex->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        btnPantilt_ex->setIcon(icon7);
        btnPantilt_ex->setIconSize(QSize(200, 200));
        btnPantilt_ex->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnScreenshot = new QToolButton(video);
        btnScreenshot->setObjectName(QStringLiteral("btnScreenshot"));
        btnScreenshot->setGeometry(QRect(780, 610, 121, 121));
        QFont font15;
        font15.setFamily(QStringLiteral("Ubuntu"));
        font15.setPointSize(20);
        font15.setBold(true);
        font15.setWeight(75);
        btnScreenshot->setFont(font15);
        btnScreenshot->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/new/prefix1/icons/scr.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnScreenshot->setIcon(icon12);
        btnScreenshot->setIconSize(QSize(200, 200));
        btnScreenshot->setToolButtonStyle(Qt::ToolButtonIconOnly);
        keyboard = new QFrame(video);
        keyboard->setObjectName(QStringLiteral("keyboard"));
        keyboard->setGeometry(QRect(710, 790, 250, 361));
        keyboard->setFont(font);
        keyboard->setStyleSheet(QLatin1String("background:rgb(60, 60, 60);\n"
"border-radius: 10px;\n"
"border: 2px solid gray;"));
        keyboard->setFrameShape(QFrame::StyledPanel);
        keyboard->setFrameShadow(QFrame::Raised);
        k1 = new QPushButton(keyboard);
        k1->setObjectName(QStringLiteral("k1"));
        k1->setGeometry(QRect(3, 3, 80, 70));
        QFont font16;
        font16.setFamily(QStringLiteral("Ubuntu"));
        font16.setPointSize(40);
        k1->setFont(font16);
        k1->setFocusPolicy(Qt::NoFocus);
        k1->setStyleSheet(QLatin1String("border: 2px solid black;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        k3 = new QPushButton(keyboard);
        k3->setObjectName(QStringLiteral("k3"));
        k3->setGeometry(QRect(167, 3, 80, 70));
        k3->setFont(font16);
        k3->setFocusPolicy(Qt::NoFocus);
        k3->setStyleSheet(QLatin1String("border: 2px solid black;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        k7 = new QPushButton(keyboard);
        k7->setObjectName(QStringLiteral("k7"));
        k7->setGeometry(QRect(3, 147, 80, 70));
        k7->setFont(font16);
        k7->setFocusPolicy(Qt::NoFocus);
        k7->setStyleSheet(QLatin1String("border: 2px solid black;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        k8 = new QPushButton(keyboard);
        k8->setObjectName(QStringLiteral("k8"));
        k8->setGeometry(QRect(85, 147, 80, 70));
        k8->setFont(font16);
        k8->setFocusPolicy(Qt::NoFocus);
        k8->setStyleSheet(QLatin1String("border: 2px solid black;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        k2 = new QPushButton(keyboard);
        k2->setObjectName(QStringLiteral("k2"));
        k2->setGeometry(QRect(85, 3, 80, 70));
        k2->setFont(font16);
        k2->setFocusPolicy(Qt::NoFocus);
        k2->setStyleSheet(QLatin1String("border: 2px solid black;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        k0 = new QPushButton(keyboard);
        k0->setObjectName(QStringLiteral("k0"));
        k0->setGeometry(QRect(85, 220, 80, 70));
        k0->setFont(font16);
        k0->setFocusPolicy(Qt::NoFocus);
        k0->setStyleSheet(QLatin1String("border: 2px solid black;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        k_minus = new QPushButton(keyboard);
        k_minus->setObjectName(QStringLiteral("k_minus"));
        k_minus->setGeometry(QRect(3, 219, 80, 70));
        k_minus->setFont(font16);
        k_minus->setFocusPolicy(Qt::NoFocus);
        k_minus->setStyleSheet(QLatin1String("border: 2px solid black;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        k5 = new QPushButton(keyboard);
        k5->setObjectName(QStringLiteral("k5"));
        k5->setGeometry(QRect(85, 75, 80, 70));
        k5->setFont(font16);
        k5->setFocusPolicy(Qt::NoFocus);
        k5->setStyleSheet(QLatin1String("border: 2px solid black;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        k9 = new QPushButton(keyboard);
        k9->setObjectName(QStringLiteral("k9"));
        k9->setGeometry(QRect(167, 147, 80, 70));
        k9->setFont(font16);
        k9->setFocusPolicy(Qt::NoFocus);
        k9->setStyleSheet(QLatin1String("border: 2px solid black;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        k4 = new QPushButton(keyboard);
        k4->setObjectName(QStringLiteral("k4"));
        k4->setGeometry(QRect(3, 75, 80, 70));
        k4->setFont(font16);
        k4->setFocusPolicy(Qt::NoFocus);
        k4->setStyleSheet(QLatin1String("border: 2px solid black;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        k6 = new QPushButton(keyboard);
        k6->setObjectName(QStringLiteral("k6"));
        k6->setGeometry(QRect(167, 75, 80, 70));
        k6->setFont(font16);
        k6->setFocusPolicy(Qt::NoFocus);
        k6->setStyleSheet(QLatin1String("border: 2px solid black;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        del = new QPushButton(keyboard);
        del->setObjectName(QStringLiteral("del"));
        del->setGeometry(QRect(3, 291, 244, 66));
        del->setFont(font16);
        del->setFocusPolicy(Qt::NoFocus);
        del->setStyleSheet(QLatin1String("border: 2px solid black;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        k_dot = new QPushButton(keyboard);
        k_dot->setObjectName(QStringLiteral("k_dot"));
        k_dot->setGeometry(QRect(167, 220, 80, 70));
        k_dot->setFont(font16);
        k_dot->setFocusPolicy(Qt::NoFocus);
        k_dot->setStyleSheet(QLatin1String("border: 2px solid black;\n"
"border-radius: 10px;\n"
"padding: 0 8px;\n"
"background: white;"));
        frameLabel = new QLabel(video);
        frameLabel->setObjectName(QStringLiteral("frameLabel"));
        frameLabel->setGeometry(QRect(0, 0, 940, 800));
        coordInfo = new QLabel(video);
        coordInfo->setObjectName(QStringLiteral("coordInfo"));
        coordInfo->setGeometry(QRect(120, 740, 820, 50));
        QFont font17;
        font17.setFamily(QStringLiteral("Ubuntu"));
        font17.setPointSize(30);
        coordInfo->setFont(font17);
        coordInfo->setStyleSheet(QStringLiteral("color:white;"));
        frameLabel->raise();
        btnPantilt->raise();
        btnPantilt_left->raise();
        btnPantilt_ex->raise();
        btnScreenshot->raise();
        btnPolarity_ex->raise();
        btnZoom_ex->raise();
        btnLRF->raise();
        groupBox->raise();
        btnDayir_ex->raise();
        btnNuc_ex->raise();
        btnPantilt_right->raise();
        btnPantilt_up->raise();
        btnDayir->raise();
        btnBack->raise();
        btnZoom->raise();
        keyboard->raise();
        coordInfo->raise();
        btnPantilt_down->raise();
        frame1B = new QFrame(Expanded);
        frame1B->setObjectName(QStringLiteral("frame1B"));
        frame1B->setGeometry(QRect(190, 870, 321, 431));
        frame1B->setFont(font);
        frame1B->setStyleSheet(QLatin1String("background:rgb(60, 60, 60);\n"
"border-radius: 10px;\n"
"border: 2px solid white;"));
        frame1B->setFrameShape(QFrame::StyledPanel);
        frame1B->setFrameShadow(QFrame::Raised);
        label_26 = new QLabel(frame1B);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(5, 315, 61, 51));
        QFont font18;
        font18.setFamily(QStringLiteral("Ubuntu"));
        font18.setPointSize(11);
        label_26->setFont(font18);
        label_26->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        label_26->setAlignment(Qt::AlignCenter);
        label_21 = new QLabel(frame1B);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(5, 260, 61, 51));
        label_21->setFont(font18);
        label_21->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        label_21->setAlignment(Qt::AlignCenter);
        label_18 = new QLabel(frame1B);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(5, 95, 61, 51));
        QFont font19;
        font19.setFamily(QStringLiteral("Ubuntu"));
        font19.setPointSize(16);
        label_18->setFont(font19);
        label_18->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        label_18->setAlignment(Qt::AlignCenter);
        label_20 = new QLabel(frame1B);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(5, 40, 61, 51));
        label_20->setFont(font19);
        label_20->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        label_20->setAlignment(Qt::AlignCenter);
        x_1B = new QLabel(frame1B);
        x_1B->setObjectName(QStringLiteral("x_1B"));
        x_1B->setGeometry(QRect(75, 5, 111, 31));
        QFont font20;
        font20.setFamily(QStringLiteral("Ubuntu"));
        font20.setPointSize(15);
        x_1B->setFont(font20);
        x_1B->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        x_1B->setAlignment(Qt::AlignCenter);
        y_1B = new QLabel(frame1B);
        y_1B->setObjectName(QStringLiteral("y_1B"));
        y_1B->setGeometry(QRect(203, 5, 111, 31));
        y_1B->setFont(font20);
        y_1B->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        y_1B->setAlignment(Qt::AlignCenter);
        label_19 = new QLabel(frame1B);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(5, 205, 61, 51));
        label_19->setFont(font19);
        label_19->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        label_19->setAlignment(Qt::AlignCenter);
        label_23 = new QLabel(frame1B);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(5, 150, 61, 51));
        label_23->setFont(font19);
        label_23->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        label_23->setAlignment(Qt::AlignCenter);
        label_27 = new QLabel(frame1B);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(5, 370, 61, 51));
        label_27->setFont(font18);
        label_27->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        label_27->setAlignment(Qt::AlignCenter);
        Ax_1B = new QLineEdit(frame1B);
        Ax_1B->setObjectName(QStringLiteral("Ax_1B"));
        Ax_1B->setEnabled(true);
        Ax_1B->setGeometry(QRect(70, 40, 121, 51));
        QFont font21;
        font21.setFamily(QStringLiteral("Ubuntu Condensed"));
        font21.setPointSize(24);
        Ax_1B->setFont(font21);
        Ax_1B->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: red;"));
        Ax_1B->setInputMethodHints(Qt::ImhNone);
        Ax_1B->setMaxLength(20);
        Ay_1B = new QLineEdit(frame1B);
        Ay_1B->setObjectName(QStringLiteral("Ay_1B"));
        Ay_1B->setEnabled(true);
        Ay_1B->setGeometry(QRect(196, 40, 121, 51));
        Ay_1B->setFont(font21);
        Ay_1B->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: red;"));
        Ay_1B->setInputMethodHints(Qt::ImhNone);
        Ay_1B->setMaxLength(20);
        Bx_1B = new QLineEdit(frame1B);
        Bx_1B->setObjectName(QStringLiteral("Bx_1B"));
        Bx_1B->setEnabled(true);
        Bx_1B->setGeometry(QRect(70, 95, 121, 51));
        Bx_1B->setFont(font21);
        Bx_1B->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: red;"));
        Bx_1B->setInputMethodHints(Qt::ImhNone);
        Bx_1B->setMaxLength(20);
        By_1B = new QLineEdit(frame1B);
        By_1B->setObjectName(QStringLiteral("By_1B"));
        By_1B->setEnabled(true);
        By_1B->setGeometry(QRect(196, 95, 121, 51));
        By_1B->setFont(font21);
        By_1B->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: red;"));
        By_1B->setInputMethodHints(Qt::ImhNone);
        By_1B->setMaxLength(20);
        Cx_1B = new QLineEdit(frame1B);
        Cx_1B->setObjectName(QStringLiteral("Cx_1B"));
        Cx_1B->setEnabled(true);
        Cx_1B->setGeometry(QRect(70, 150, 121, 51));
        Cx_1B->setFont(font21);
        Cx_1B->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: red;"));
        Cx_1B->setInputMethodHints(Qt::ImhNone);
        Cx_1B->setMaxLength(20);
        Cy_1B = new QLineEdit(frame1B);
        Cy_1B->setObjectName(QStringLiteral("Cy_1B"));
        Cy_1B->setEnabled(true);
        Cy_1B->setGeometry(QRect(196, 150, 121, 51));
        Cy_1B->setFont(font21);
        Cy_1B->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: red;"));
        Cy_1B->setInputMethodHints(Qt::ImhNone);
        Cy_1B->setMaxLength(20);
        AB_1B = new QLineEdit(frame1B);
        AB_1B->setObjectName(QStringLiteral("AB_1B"));
        AB_1B->setEnabled(true);
        AB_1B->setGeometry(QRect(70, 260, 247, 51));
        AB_1B->setFont(font21);
        AB_1B->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: black;"));
        AB_1B->setInputMethodHints(Qt::ImhNone);
        AB_1B->setMaxLength(20);
        AC_1B = new QLineEdit(frame1B);
        AC_1B->setObjectName(QStringLiteral("AC_1B"));
        AC_1B->setEnabled(true);
        AC_1B->setGeometry(QRect(70, 315, 247, 51));
        AC_1B->setFont(font21);
        AC_1B->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: black;"));
        AC_1B->setInputMethodHints(Qt::ImhNone);
        AC_1B->setMaxLength(20);
        AD_1B = new QLineEdit(frame1B);
        AD_1B->setObjectName(QStringLiteral("AD_1B"));
        AD_1B->setEnabled(true);
        AD_1B->setGeometry(QRect(70, 370, 247, 51));
        AD_1B->setFont(font21);
        AD_1B->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: black;"));
        AD_1B->setInputMethodHints(Qt::ImhNone);
        AD_1B->setMaxLength(20);
        Dx_1B = new QLineEdit(frame1B);
        Dx_1B->setObjectName(QStringLiteral("Dx_1B"));
        Dx_1B->setEnabled(true);
        Dx_1B->setGeometry(QRect(70, 205, 121, 51));
        Dx_1B->setFont(font21);
        Dx_1B->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: red;"));
        Dx_1B->setInputMethodHints(Qt::ImhNone);
        Dx_1B->setMaxLength(20);
        Dy_1B = new QLineEdit(frame1B);
        Dy_1B->setObjectName(QStringLiteral("Dy_1B"));
        Dy_1B->setEnabled(true);
        Dy_1B->setGeometry(QRect(196, 205, 121, 51));
        Dy_1B->setFont(font21);
        Dy_1B->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: red;"));
        Dy_1B->setInputMethodHints(Qt::ImhNone);
        Dy_1B->setMaxLength(20);
        btnDirAngleType_1B = new QToolButton(frame1B);
        btnDirAngleType_1B->setObjectName(QStringLiteral("btnDirAngleType_1B"));
        btnDirAngleType_1B->setGeometry(QRect(0, 0, 58, 51));
        QFont font22;
        font22.setFamily(QStringLiteral("Ubuntu"));
        font22.setPointSize(20);
        btnDirAngleType_1B->setFont(font22);
        btnDirAngleType_1B->setStyleSheet(QLatin1String("color:white;\n"
"background:red;"));
        frame1C = new QFrame(Expanded);
        frame1C->setObjectName(QStringLiteral("frame1C"));
        frame1C->setGeometry(QRect(550, 840, 321, 266));
        frame1C->setFont(font);
        frame1C->setStyleSheet(QLatin1String("background:rgb(60, 60, 60);\n"
"border-radius: 10px;\n"
"border: 2px solid white;"));
        frame1C->setFrameShape(QFrame::StyledPanel);
        frame1C->setFrameShadow(QFrame::Raised);
        label_38 = new QLabel(frame1C);
        label_38->setObjectName(QStringLiteral("label_38"));
        label_38->setGeometry(QRect(5, 210, 61, 40));
        QFont font23;
        font23.setFamily(QStringLiteral("Ubuntu"));
        font23.setPointSize(12);
        label_38->setFont(font23);
        label_38->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        label_38->setAlignment(Qt::AlignCenter);
        y_1C = new QLabel(frame1C);
        y_1C->setObjectName(QStringLiteral("y_1C"));
        y_1C->setGeometry(QRect(203, 5, 111, 31));
        y_1C->setFont(font20);
        y_1C->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        y_1C->setAlignment(Qt::AlignCenter);
        label_33 = new QLabel(frame1C);
        label_33->setObjectName(QStringLiteral("label_33"));
        label_33->setGeometry(QRect(5, 150, 61, 51));
        label_33->setFont(font23);
        label_33->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        label_33->setAlignment(Qt::AlignCenter);
        x_1C = new QLabel(frame1C);
        x_1C->setObjectName(QStringLiteral("x_1C"));
        x_1C->setGeometry(QRect(75, 5, 111, 31));
        x_1C->setFont(font20);
        x_1C->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        x_1C->setAlignment(Qt::AlignCenter);
        label_32 = new QLabel(frame1C);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setGeometry(QRect(5, 40, 61, 51));
        label_32->setFont(font19);
        label_32->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        label_32->setAlignment(Qt::AlignCenter);
        label_30 = new QLabel(frame1C);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(5, 95, 61, 51));
        label_30->setFont(font19);
        label_30->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        label_30->setAlignment(Qt::AlignCenter);
        DistA_1C = new QLineEdit(frame1C);
        DistA_1C->setObjectName(QStringLiteral("DistA_1C"));
        DistA_1C->setEnabled(true);
        DistA_1C->setGeometry(QRect(70, 150, 247, 51));
        DistA_1C->setFont(font21);
        DistA_1C->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: black;"));
        DistA_1C->setInputMethodHints(Qt::ImhNone);
        DistA_1C->setMaxLength(20);
        DistB_1C = new QLineEdit(frame1C);
        DistB_1C->setObjectName(QStringLiteral("DistB_1C"));
        DistB_1C->setEnabled(true);
        DistB_1C->setGeometry(QRect(70, 205, 247, 51));
        DistB_1C->setFont(font21);
        DistB_1C->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: black;"));
        DistB_1C->setInputMethodHints(Qt::ImhNone);
        DistB_1C->setMaxLength(20);
        Ax_1C = new QLineEdit(frame1C);
        Ax_1C->setObjectName(QStringLiteral("Ax_1C"));
        Ax_1C->setEnabled(true);
        Ax_1C->setGeometry(QRect(70, 40, 121, 51));
        Ax_1C->setFont(font21);
        Ax_1C->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: red;"));
        Ax_1C->setInputMethodHints(Qt::ImhNone);
        Ax_1C->setMaxLength(20);
        Ay_1C = new QLineEdit(frame1C);
        Ay_1C->setObjectName(QStringLiteral("Ay_1C"));
        Ay_1C->setEnabled(true);
        Ay_1C->setGeometry(QRect(196, 40, 121, 51));
        Ay_1C->setFont(font21);
        Ay_1C->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: red;"));
        Ay_1C->setInputMethodHints(Qt::ImhNone);
        Ay_1C->setMaxLength(20);
        Bx_1C = new QLineEdit(frame1C);
        Bx_1C->setObjectName(QStringLiteral("Bx_1C"));
        Bx_1C->setEnabled(true);
        Bx_1C->setGeometry(QRect(70, 95, 121, 51));
        Bx_1C->setFont(font21);
        Bx_1C->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: red;"));
        Bx_1C->setInputMethodHints(Qt::ImhNone);
        Bx_1C->setMaxLength(20);
        By_1C = new QLineEdit(frame1C);
        By_1C->setObjectName(QStringLiteral("By_1C"));
        By_1C->setEnabled(true);
        By_1C->setGeometry(QRect(196, 95, 121, 51));
        By_1C->setFont(font21);
        By_1C->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: red;"));
        By_1C->setInputMethodHints(Qt::ImhNone);
        By_1C->setMaxLength(20);
        frame2 = new QFrame(Expanded);
        frame2->setObjectName(QStringLiteral("frame2"));
        frame2->setGeometry(QRect(910, 880, 321, 156));
        frame2->setFont(font);
        frame2->setStyleSheet(QLatin1String("background:rgb(60, 60, 60);\n"
"border-radius: 10px;\n"
"border: 2px solid white;"));
        frame2->setFrameShape(QFrame::StyledPanel);
        frame2->setFrameShadow(QFrame::Raised);
        x_2 = new QLabel(frame2);
        x_2->setObjectName(QStringLiteral("x_2"));
        x_2->setGeometry(QRect(75, 5, 111, 31));
        x_2->setFont(font20);
        x_2->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        x_2->setAlignment(Qt::AlignCenter);
        label_35 = new QLabel(frame2);
        label_35->setObjectName(QStringLiteral("label_35"));
        label_35->setGeometry(QRect(5, 40, 61, 51));
        label_35->setFont(font19);
        label_35->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        label_35->setAlignment(Qt::AlignCenter);
        y_2 = new QLabel(frame2);
        y_2->setObjectName(QStringLiteral("y_2"));
        y_2->setGeometry(QRect(203, 5, 111, 31));
        y_2->setFont(font20);
        y_2->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        y_2->setAlignment(Qt::AlignCenter);
        label_31 = new QLabel(frame2);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(5, 95, 61, 51));
        label_31->setFont(font19);
        label_31->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        label_31->setAlignment(Qt::AlignCenter);
        Ax_2 = new QLineEdit(frame2);
        Ax_2->setObjectName(QStringLiteral("Ax_2"));
        Ax_2->setEnabled(true);
        Ax_2->setGeometry(QRect(70, 40, 121, 51));
        Ax_2->setFont(font21);
        Ax_2->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: red;"));
        Ax_2->setInputMethodHints(Qt::ImhNone);
        Ax_2->setMaxLength(20);
        Ay_2 = new QLineEdit(frame2);
        Ay_2->setObjectName(QStringLiteral("Ay_2"));
        Ay_2->setEnabled(true);
        Ay_2->setGeometry(QRect(196, 40, 121, 51));
        Ay_2->setFont(font21);
        Ay_2->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: red;"));
        Ay_2->setInputMethodHints(Qt::ImhNone);
        Ay_2->setMaxLength(20);
        Bx_2 = new QLineEdit(frame2);
        Bx_2->setObjectName(QStringLiteral("Bx_2"));
        Bx_2->setEnabled(true);
        Bx_2->setGeometry(QRect(70, 95, 121, 51));
        Bx_2->setFont(font21);
        Bx_2->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: red;"));
        Bx_2->setInputMethodHints(Qt::ImhNone);
        Bx_2->setMaxLength(20);
        By_2 = new QLineEdit(frame2);
        By_2->setObjectName(QStringLiteral("By_2"));
        By_2->setEnabled(true);
        By_2->setGeometry(QRect(196, 95, 121, 51));
        By_2->setFont(font21);
        By_2->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: red;"));
        By_2->setInputMethodHints(Qt::ImhNone);
        By_2->setMaxLength(20);
        frame3 = new QFrame(Expanded);
        frame3->setObjectName(QStringLiteral("frame3"));
        frame3->setGeometry(QRect(910, 1070, 321, 266));
        frame3->setFont(font);
        frame3->setStyleSheet(QLatin1String("background:rgb(60, 60, 60);\n"
"border-radius: 10px;\n"
"border: 2px solid white;"));
        frame3->setFrameShape(QFrame::StyledPanel);
        frame3->setFrameShadow(QFrame::Raised);
        y_3 = new QLabel(frame3);
        y_3->setObjectName(QStringLiteral("y_3"));
        y_3->setGeometry(QRect(203, 5, 111, 31));
        y_3->setFont(font20);
        y_3->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        y_3->setAlignment(Qt::AlignCenter);
        label_51 = new QLabel(frame3);
        label_51->setObjectName(QStringLiteral("label_51"));
        label_51->setGeometry(QRect(5, 205, 61, 51));
        label_51->setFont(font19);
        label_51->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        label_51->setAlignment(Qt::AlignCenter);
        x_3 = new QLabel(frame3);
        x_3->setObjectName(QStringLiteral("x_3"));
        x_3->setGeometry(QRect(75, 5, 111, 31));
        x_3->setFont(font20);
        x_3->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        x_3->setAlignment(Qt::AlignCenter);
        label_44 = new QLabel(frame3);
        label_44->setObjectName(QStringLiteral("label_44"));
        label_44->setGeometry(QRect(5, 40, 61, 51));
        label_44->setFont(font19);
        label_44->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        label_44->setAlignment(Qt::AlignCenter);
        label_50 = new QLabel(frame3);
        label_50->setObjectName(QStringLiteral("label_50"));
        label_50->setGeometry(QRect(5, 95, 61, 51));
        label_50->setFont(font19);
        label_50->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        label_50->setAlignment(Qt::AlignCenter);
        label_39 = new QLabel(frame3);
        label_39->setObjectName(QStringLiteral("label_39"));
        label_39->setGeometry(QRect(5, 150, 61, 51));
        label_39->setFont(font19);
        label_39->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        label_39->setAlignment(Qt::AlignCenter);
        TH_3 = new QLineEdit(frame3);
        TH_3->setObjectName(QStringLiteral("TH_3"));
        TH_3->setEnabled(true);
        TH_3->setGeometry(QRect(70, 95, 247, 51));
        TH_3->setFont(font21);
        TH_3->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: black;"));
        TH_3->setInputMethodHints(Qt::ImhNone);
        TH_3->setMaxLength(20);
        RH_3 = new QLineEdit(frame3);
        RH_3->setObjectName(QStringLiteral("RH_3"));
        RH_3->setEnabled(true);
        RH_3->setGeometry(QRect(70, 205, 247, 51));
        RH_3->setFont(font21);
        RH_3->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: black;"));
        RH_3->setInputMethodHints(Qt::ImhNone);
        RH_3->setMaxLength(20);
        Tx_3 = new QLineEdit(frame3);
        Tx_3->setObjectName(QStringLiteral("Tx_3"));
        Tx_3->setEnabled(true);
        Tx_3->setGeometry(QRect(70, 40, 121, 51));
        Tx_3->setFont(font21);
        Tx_3->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: red;"));
        Tx_3->setInputMethodHints(Qt::ImhNone);
        Tx_3->setMaxLength(20);
        Ty_3 = new QLineEdit(frame3);
        Ty_3->setObjectName(QStringLiteral("Ty_3"));
        Ty_3->setEnabled(true);
        Ty_3->setGeometry(QRect(196, 40, 121, 51));
        Ty_3->setFont(font21);
        Ty_3->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: red;"));
        Ty_3->setInputMethodHints(Qt::ImhNone);
        Ty_3->setMaxLength(20);
        Rx_3 = new QLineEdit(frame3);
        Rx_3->setObjectName(QStringLiteral("Rx_3"));
        Rx_3->setEnabled(true);
        Rx_3->setGeometry(QRect(70, 150, 121, 51));
        Rx_3->setFont(font21);
        Rx_3->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: red;"));
        Rx_3->setInputMethodHints(Qt::ImhNone);
        Rx_3->setMaxLength(20);
        Ry_3 = new QLineEdit(frame3);
        Ry_3->setObjectName(QStringLiteral("Ry_3"));
        Ry_3->setEnabled(true);
        Ry_3->setGeometry(QRect(196, 150, 121, 51));
        Ry_3->setFont(font21);
        Ry_3->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: red;"));
        Ry_3->setInputMethodHints(Qt::ImhNone);
        Ry_3->setMaxLength(20);
        frame1A = new QFrame(Expanded);
        frame1A->setObjectName(QStringLiteral("frame1A"));
        frame1A->setEnabled(true);
        frame1A->setGeometry(QRect(550, 1130, 321, 321));
        frame1A->setFont(font);
        frame1A->setStyleSheet(QLatin1String("background:rgb(60, 60, 60);\n"
"border-radius: 10px;\n"
"border: 2px solid white;"));
        frame1A->setFrameShape(QFrame::StyledPanel);
        frame1A->setFrameShadow(QFrame::Raised);
        frame1A->setLineWidth(4);
        x_1A = new QLabel(frame1A);
        x_1A->setObjectName(QStringLiteral("x_1A"));
        x_1A->setGeometry(QRect(75, 5, 111, 31));
        x_1A->setFont(font20);
        x_1A->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        x_1A->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(frame1A);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(5, 40, 61, 51));
        label_4->setFont(font19);
        label_4->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        label_4->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(frame1A);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(5, 95, 61, 51));
        label_5->setFont(font19);
        label_5->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        label_5->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(frame1A);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(5, 205, 61, 51));
        label_7->setFont(font18);
        label_7->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        label_7->setAlignment(Qt::AlignCenter);
        label_8 = new QLabel(frame1A);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(5, 260, 61, 51));
        QFont font24;
        font24.setFamily(QStringLiteral("Ubuntu"));
        font24.setPointSize(10);
        label_8->setFont(font24);
        label_8->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        label_8->setAlignment(Qt::AlignCenter);
        y_1A = new QLabel(frame1A);
        y_1A->setObjectName(QStringLiteral("y_1A"));
        y_1A->setGeometry(QRect(203, 5, 111, 31));
        y_1A->setFont(font20);
        y_1A->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        y_1A->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(frame1A);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(5, 150, 61, 51));
        QFont font25;
        font25.setFamily(QStringLiteral("Ubuntu"));
        font25.setPointSize(14);
        label_6->setFont(font25);
        label_6->setStyleSheet(QLatin1String("color: white;\n"
"border: 2px solid rgb(60, 60, 60);"));
        label_6->setAlignment(Qt::AlignCenter);
        Ax_1a = new QLineEdit(frame1A);
        Ax_1a->setObjectName(QStringLiteral("Ax_1a"));
        Ax_1a->setEnabled(true);
        Ax_1a->setGeometry(QRect(70, 40, 121, 51));
        Ax_1a->setFont(font21);
        Ax_1a->setMouseTracking(true);
        Ax_1a->setFocusPolicy(Qt::StrongFocus);
        Ax_1a->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: red;"));
        Ax_1a->setInputMethodHints(Qt::ImhNone);
        Ax_1a->setMaxLength(20);
        Ax_1a->setClearButtonEnabled(false);
        Ay_1a = new QLineEdit(frame1A);
        Ay_1a->setObjectName(QStringLiteral("Ay_1a"));
        Ay_1a->setEnabled(true);
        Ay_1a->setGeometry(QRect(196, 40, 121, 51));
        Ay_1a->setFont(font21);
        Ay_1a->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: red;"));
        Ay_1a->setInputMethodHints(Qt::ImhNone);
        Ay_1a->setMaxLength(20);
        H_1A = new QLineEdit(frame1A);
        H_1A->setObjectName(QStringLiteral("H_1A"));
        H_1A->setEnabled(true);
        H_1A->setGeometry(QRect(70, 95, 247, 51));
        H_1A->setFont(font21);
        H_1A->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: black;"));
        H_1A->setInputMethodHints(Qt::ImhNone);
        H_1A->setMaxLength(20);
        Dist_1A = new QLineEdit(frame1A);
        Dist_1A->setObjectName(QStringLiteral("Dist_1A"));
        Dist_1A->setEnabled(true);
        Dist_1A->setGeometry(QRect(70, 150, 247, 51));
        Dist_1A->setFont(font21);
        Dist_1A->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: black;"));
        Dist_1A->setInputMethodHints(Qt::ImhNone);
        Dist_1A->setMaxLength(20);
        AB_1A = new QLineEdit(frame1A);
        AB_1A->setObjectName(QStringLiteral("AB_1A"));
        AB_1A->setEnabled(true);
        AB_1A->setGeometry(QRect(70, 205, 247, 51));
        AB_1A->setFont(font21);
        AB_1A->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: black;"));
        AB_1A->setInputMethodHints(Qt::ImhNone);
        AB_1A->setMaxLength(20);
        Incl_1A = new QLineEdit(frame1A);
        Incl_1A->setObjectName(QStringLiteral("Incl_1A"));
        Incl_1A->setEnabled(true);
        Incl_1A->setGeometry(QRect(70, 260, 247, 51));
        Incl_1A->setFont(font21);
        Incl_1A->setStyleSheet(QLatin1String("border: 2px white;\n"
"border-radius: 5px;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: black;"));
        Incl_1A->setInputMethodHints(Qt::ImhNone);
        Incl_1A->setMaxLength(20);
        btnDirAngleType_1A = new QToolButton(frame1A);
        btnDirAngleType_1A->setObjectName(QStringLiteral("btnDirAngleType_1A"));
        btnDirAngleType_1A->setGeometry(QRect(0, 0, 58, 51));
        btnDirAngleType_1A->setFont(font22);
        btnDirAngleType_1A->setStyleSheet(QLatin1String("color:white;\n"
"background:red;"));
        result = new QGroupBox(Expanded);
        result->setObjectName(QStringLiteral("result"));
        result->setGeometry(QRect(950, 450, 321, 351));
        QFont font26;
        font26.setFamily(QStringLiteral("Ubuntu"));
        font26.setPointSize(22);
        result->setFont(font26);
        result->setStyleSheet(QStringLiteral("color: white;"));
        result_text_3 = new QLabel(result);
        result_text_3->setObjectName(QStringLiteral("result_text_3"));
        result_text_3->setGeometry(QRect(5, 138, 310, 47));
        QFont font27;
        font27.setPointSize(28);
        result_text_3->setFont(font27);
        result_text_3->setStyleSheet(QLatin1String("background:white;\n"
"color:black;"));
        result_text_2 = new QLabel(result);
        result_text_2->setObjectName(QStringLiteral("result_text_2"));
        result_text_2->setGeometry(QRect(5, 89, 310, 47));
        result_text_2->setFont(font27);
        result_text_2->setStyleSheet(QLatin1String("background:white;\n"
"color:black;"));
        result_text_4 = new QLabel(result);
        result_text_4->setObjectName(QStringLiteral("result_text_4"));
        result_text_4->setGeometry(QRect(5, 187, 310, 47));
        result_text_4->setFont(font27);
        result_text_4->setStyleSheet(QLatin1String("background:white;\n"
"color:black;"));
        result_text_1 = new QLabel(result);
        result_text_1->setObjectName(QStringLiteral("result_text_1"));
        result_text_1->setGeometry(QRect(5, 40, 310, 47));
        result_text_1->setFont(font27);
        result_text_1->setStyleSheet(QLatin1String("background:white;\n"
"color:black;"));
        result_text_5 = new QLabel(result);
        result_text_5->setObjectName(QStringLiteral("result_text_5"));
        result_text_5->setGeometry(QRect(5, 236, 310, 47));
        result_text_5->setFont(font27);
        result_text_5->setStyleSheet(QLatin1String("background:white;\n"
"color:black;"));
        result_text_6 = new QLabel(result);
        result_text_6->setObjectName(QStringLiteral("result_text_6"));
        result_text_6->setGeometry(QRect(5, 285, 310, 47));
        result_text_6->setFont(font27);
        result_text_6->setStyleSheet(QLatin1String("background:white;\n"
"color:black;"));
        btnDirAngleType = new QToolButton(result);
        btnDirAngleType->setObjectName(QStringLiteral("btnDirAngleType"));
        btnDirAngleType->setGeometry(QRect(257, 137, 58, 48));
        btnDirAngleType->setFont(font22);
        btnDirAngleType->setStyleSheet(QStringLiteral("border: 2px solid gray;"));
        grBoxPixmap = new QGroupBox(Expanded);
        grBoxPixmap->setObjectName(QStringLiteral("grBoxPixmap"));
        grBoxPixmap->setGeometry(QRect(0, 1500, 1280, 800));
        grBoxPixmap->setStyleSheet(QLatin1String("background:white;\n"
"border:0px;"));
        grBoxPixmap->setFlat(true);
        task_pixmap = new QLabel(grBoxPixmap);
        task_pixmap->setObjectName(QStringLiteral("task_pixmap"));
        task_pixmap->setGeometry(QRect(160, 90, 960, 600));
        lblTaskName = new QLabel(grBoxPixmap);
        lblTaskName->setObjectName(QStringLiteral("lblTaskName"));
        lblTaskName->setGeometry(QRect(240, 20, 640, 81));
        QFont font28;
        font28.setPointSize(30);
        lblTaskName->setFont(font28);
        lblTaskDescription = new QLabel(grBoxPixmap);
        lblTaskDescription->setObjectName(QStringLiteral("lblTaskDescription"));
        lblTaskDescription->setGeometry(QRect(160, 680, 880, 91));
        lblTaskDescription->setFont(font28);
        btnClose = new QToolButton(grBoxPixmap);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setGeometry(QRect(1046, 2, 231, 81));
        QFont font29;
        font29.setPointSize(40);
        btnClose->setFont(font29);
        btnClose->setStyleSheet(QStringLiteral("border:5px solid black;"));
        video->raise();
        frame2->raise();
        frame1C->raise();
        frame3->raise();
        frame1B->raise();
        frame1A->raise();
        result->raise();
        grBoxPixmap->raise();

        retranslateUi(Expanded);

        QMetaObject::connectSlotsByName(Expanded);
    } // setupUi

    void retranslateUi(QDialog *Expanded)
    {
        Expanded->setWindowTitle(QApplication::translate("Expanded", "Dialog", nullptr));
        btnLRF->setText(QApplication::translate("Expanded", "LRF", nullptr));
        btnDayir->setText(QString());
        groupBox->setTitle(QString());
        btnChange->setText(QApplication::translate("Expanded", "Choose task", nullptr));
        label->setText(QApplication::translate("Expanded", "TASK 1A", nullptr));
        calculate->setText(QApplication::translate("Expanded", "Calculate", nullptr));
        btnInfo->setText(QString());
        btnPoints->setText(QApplication::translate("Expanded", "P", nullptr));
        correction->setText(QApplication::translate("Expanded", "Calculate for target", nullptr));
        btnBack->setText(QString());
        btnDayir_ex->setText(QString());
        btnZoom_ex->setText(QApplication::translate("Expanded", "1X", nullptr));
        btnNuc_ex->setText(QApplication::translate("Expanded", "NUC", nullptr));
        btnPolarity_ex->setText(QApplication::translate("Expanded", "POLA-\n"
"RITY", nullptr));
        btnPantilt->setText(QApplication::translate("Expanded", "PAN-\n"
"TILT", nullptr));
        btnZoom->setText(QApplication::translate("Expanded", "1X", nullptr));
        btnPantilt_up->setText(QString());
        btnPantilt_left->setText(QString());
        btnPantilt_right->setText(QString());
        btnPantilt_down->setText(QString());
        btnPantilt_ex->setText(QApplication::translate("Expanded", "PAN-\n"
"TILT", nullptr));
        btnScreenshot->setText(QApplication::translate("Expanded", "SCREEN\n"
"SHOT", nullptr));
        k1->setText(QApplication::translate("Expanded", "1", nullptr));
        k3->setText(QApplication::translate("Expanded", "3", nullptr));
        k7->setText(QApplication::translate("Expanded", "7", nullptr));
        k8->setText(QApplication::translate("Expanded", "8", nullptr));
        k2->setText(QApplication::translate("Expanded", "2", nullptr));
        k0->setText(QApplication::translate("Expanded", "0", nullptr));
        k_minus->setText(QApplication::translate("Expanded", "-", nullptr));
        k5->setText(QApplication::translate("Expanded", "5", nullptr));
        k9->setText(QApplication::translate("Expanded", "9", nullptr));
        k4->setText(QApplication::translate("Expanded", "4", nullptr));
        k6->setText(QApplication::translate("Expanded", "6", nullptr));
        del->setText(QApplication::translate("Expanded", "Del", nullptr));
        k_dot->setText(QApplication::translate("Expanded", ".", nullptr));
        frameLabel->setText(QString());
        coordInfo->setText(QString());
        label_26->setText(QApplication::translate("Expanded", "(AC)", nullptr));
        label_21->setText(QApplication::translate("Expanded", "(AB)", nullptr));
        label_18->setText(QApplication::translate("Expanded", "B", nullptr));
        label_20->setText(QApplication::translate("Expanded", "A", nullptr));
        x_1B->setText(QApplication::translate("Expanded", "X-position", nullptr));
        y_1B->setText(QApplication::translate("Expanded", "Y-position", nullptr));
        label_19->setText(QApplication::translate("Expanded", "D", nullptr));
        label_23->setText(QApplication::translate("Expanded", "C", nullptr));
        label_27->setText(QApplication::translate("Expanded", "(AD)", nullptr));
        Ax_1B->setInputMask(QString());
        Ay_1B->setInputMask(QString());
        Bx_1B->setInputMask(QString());
        By_1B->setInputMask(QString());
        Cx_1B->setInputMask(QString());
        Cy_1B->setInputMask(QString());
        AB_1B->setInputMask(QString());
        AC_1B->setInputMask(QString());
        AD_1B->setInputMask(QString());
        Dx_1B->setInputMask(QString());
        Dy_1B->setInputMask(QString());
        btnDirAngleType_1B->setText(QApplication::translate("Expanded", "MIL", nullptr));
        label_38->setText(QApplication::translate("Expanded", "DistB,m", nullptr));
        y_1C->setText(QApplication::translate("Expanded", "Y-position", nullptr));
        label_33->setText(QApplication::translate("Expanded", "DistA,m", nullptr));
        x_1C->setText(QApplication::translate("Expanded", "X-position", nullptr));
        label_32->setText(QApplication::translate("Expanded", "A", nullptr));
        label_30->setText(QApplication::translate("Expanded", "B", nullptr));
        DistA_1C->setInputMask(QString());
        DistB_1C->setInputMask(QString());
        Ax_1C->setInputMask(QString());
        Ay_1C->setInputMask(QString());
        Bx_1C->setInputMask(QString());
        By_1C->setInputMask(QString());
        x_2->setText(QApplication::translate("Expanded", "X-position", nullptr));
        label_35->setText(QApplication::translate("Expanded", "A", nullptr));
        y_2->setText(QApplication::translate("Expanded", "Y-position", nullptr));
        label_31->setText(QApplication::translate("Expanded", "B", nullptr));
        Ax_2->setInputMask(QString());
        Ay_2->setInputMask(QString());
        Bx_2->setInputMask(QString());
        By_2->setInputMask(QString());
        y_3->setText(QApplication::translate("Expanded", "Y-position", nullptr));
        label_51->setText(QApplication::translate("Expanded", "RH, m", nullptr));
        x_3->setText(QApplication::translate("Expanded", "X-position", nullptr));
        label_44->setText(QApplication::translate("Expanded", "T", nullptr));
        label_50->setText(QApplication::translate("Expanded", "TH, m", nullptr));
        label_39->setText(QApplication::translate("Expanded", "R", nullptr));
        TH_3->setInputMask(QString());
        RH_3->setInputMask(QString());
        Tx_3->setInputMask(QString());
        Ty_3->setInputMask(QString());
        Rx_3->setInputMask(QString());
        Ry_3->setInputMask(QString());
        x_1A->setText(QApplication::translate("Expanded", "X-position", nullptr));
        label_4->setText(QApplication::translate("Expanded", "A", nullptr));
        label_5->setText(QApplication::translate("Expanded", "H, m", nullptr));
        label_7->setText(QApplication::translate("Expanded", "(AB)", nullptr));
        label_8->setText(QApplication::translate("Expanded", "(Incl)", nullptr));
        y_1A->setText(QApplication::translate("Expanded", "Y-position", nullptr));
        label_6->setText(QApplication::translate("Expanded", "Dist, m", nullptr));
        Ax_1a->setInputMask(QString());
        Ay_1a->setInputMask(QString());
        H_1A->setInputMask(QString());
        Dist_1A->setInputMask(QString());
        AB_1A->setInputMask(QString());
        Incl_1A->setInputMask(QString());
        btnDirAngleType_1A->setText(QApplication::translate("Expanded", "MIL", nullptr));
        result->setTitle(QApplication::translate("Expanded", "RESULT", nullptr));
        result_text_3->setText(QString());
        result_text_2->setText(QString());
        result_text_4->setText(QString());
        result_text_1->setText(QString());
        result_text_5->setText(QString());
        result_text_6->setText(QString());
        btnDirAngleType->setText(QApplication::translate("Expanded", "MIL", nullptr));
        grBoxPixmap->setTitle(QString());
        task_pixmap->setText(QString());
        lblTaskName->setText(QApplication::translate("Expanded", "TextLabel", nullptr));
        lblTaskDescription->setText(QApplication::translate("Expanded", "TextLabel", nullptr));
        btnClose->setText(QApplication::translate("Expanded", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Expanded: public Ui_Expanded {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPANDED_H
