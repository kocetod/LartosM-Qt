/********************************************************************************
** Form generated from reading UI file 'coordinatesystem.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COORDINATESYSTEM_H
#define UI_COORDINATESYSTEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_CoordinateSystem
{
public:
    QPushButton *btnChooseCoordSys;
    QFrame *frame_system;
    QRadioButton *krasovsky;
    QRadioButton *wgs;
    QLabel *lblChoose;
    QFrame *frame_type;
    QLabel *lblChooseType;
    QRadioButton *utm_xy;
    QRadioButton *bl;
    QFrame *frame_zone;
    QRadioButton *zone_35;
    QLabel *lblChooseZone;
    QRadioButton *zone_34;

    void setupUi(QDialog *CoordinateSystem)
    {
        if (CoordinateSystem->objectName().isEmpty())
            CoordinateSystem->setObjectName(QStringLiteral("CoordinateSystem"));
        CoordinateSystem->resize(1280, 800);
        CoordinateSystem->setStyleSheet(QStringLiteral("background:black;"));
        btnChooseCoordSys = new QPushButton(CoordinateSystem);
        btnChooseCoordSys->setObjectName(QStringLiteral("btnChooseCoordSys"));
        btnChooseCoordSys->setGeometry(QRect(0, 700, 1281, 101));
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu"));
        font.setPointSize(60);
        font.setBold(false);
        font.setWeight(50);
        btnChooseCoordSys->setFont(font);
        btnChooseCoordSys->setFocusPolicy(Qt::ClickFocus);
        btnChooseCoordSys->setStyleSheet(QLatin1String("border: 2px white;\n"
"padding: 0 8px;\n"
"background: white;\n"
"color: black;"));
        frame_system = new QFrame(CoordinateSystem);
        frame_system->setObjectName(QStringLiteral("frame_system"));
        frame_system->setGeometry(QRect(10, 20, 1261, 221));
        frame_system->setFrameShape(QFrame::StyledPanel);
        frame_system->setFrameShadow(QFrame::Raised);
        krasovsky = new QRadioButton(frame_system);
        krasovsky->setObjectName(QStringLiteral("krasovsky"));
        krasovsky->setGeometry(QRect(720, 80, 331, 131));
        QFont font1;
        font1.setFamily(QStringLiteral("Ubuntu"));
        font1.setPointSize(44);
        krasovsky->setFont(font1);
        krasovsky->setFocusPolicy(Qt::ClickFocus);
        krasovsky->setStyleSheet(QLatin1String("QRadioButton::indicator:unchecked{\n"
"background:white;\n"
"border: 1px solid;\n"
"border-color: white;\n"
"width: 33px;\n"
"height: 33px;\n"
"border-radius: 17px;\n"
"}\n"
"QRadioButton::indicator:checked{\n"
"background:black;\n"
"border: 7px solid;\n"
"border-color: white;\n"
"width: 21px;\n"
"height: 21px;\n"
"border-radius: 17px;\n"
"}\n"
"QRadioButton{\n"
"color:white;\n"
"}"));
        wgs = new QRadioButton(frame_system);
        wgs->setObjectName(QStringLiteral("wgs"));
        wgs->setGeometry(QRect(230, 80, 281, 131));
        wgs->setFont(font1);
        wgs->setFocusPolicy(Qt::ClickFocus);
        wgs->setStyleSheet(QLatin1String("QRadioButton::indicator:unchecked{\n"
"background:white;\n"
"border: 1px solid;\n"
"border-color: white;\n"
"width: 33px;\n"
"height: 33px;\n"
"border-radius: 17px;\n"
"}\n"
"QRadioButton::indicator:checked{\n"
"background:black;\n"
"border: 7px solid;\n"
"border-color: white;\n"
"width: 21px;\n"
"height: 21px;\n"
"border-radius: 17px;\n"
"}\n"
"QRadioButton{\n"
"color:white;\n"
"}"));
        wgs->setChecked(true);
        lblChoose = new QLabel(frame_system);
        lblChoose->setObjectName(QStringLiteral("lblChoose"));
        lblChoose->setGeometry(QRect(0, -10, 871, 81));
        QFont font2;
        font2.setFamily(QStringLiteral("Ubuntu"));
        font2.setPointSize(55);
        font2.setBold(false);
        font2.setWeight(50);
        lblChoose->setFont(font2);
        lblChoose->setStyleSheet(QStringLiteral("color: white;"));
        frame_type = new QFrame(CoordinateSystem);
        frame_type->setObjectName(QStringLiteral("frame_type"));
        frame_type->setGeometry(QRect(10, 250, 1261, 181));
        frame_type->setFrameShape(QFrame::StyledPanel);
        frame_type->setFrameShadow(QFrame::Raised);
        lblChooseType = new QLabel(frame_type);
        lblChooseType->setObjectName(QStringLiteral("lblChooseType"));
        lblChooseType->setGeometry(QRect(10, 0, 791, 91));
        lblChooseType->setFont(font2);
        lblChooseType->setStyleSheet(QStringLiteral("color: white;"));
        utm_xy = new QRadioButton(frame_type);
        utm_xy->setObjectName(QStringLiteral("utm_xy"));
        utm_xy->setGeometry(QRect(450, 100, 171, 81));
        utm_xy->setFont(font1);
        utm_xy->setFocusPolicy(Qt::ClickFocus);
        utm_xy->setStyleSheet(QLatin1String("QRadioButton::indicator:unchecked{\n"
"background:white;\n"
"border: 1px solid;\n"
"border-color: white;\n"
"width: 33px;\n"
"height: 33px;\n"
"border-radius: 17px;\n"
"}\n"
"QRadioButton::indicator:checked{\n"
"background:black;\n"
"border: 7px solid;\n"
"border-color: white;\n"
"width: 21px;\n"
"height: 21px;\n"
"border-radius: 17px;\n"
"}\n"
"QRadioButton{\n"
"color:white;\n"
"}"));
        utm_xy->setChecked(false);
        bl = new QRadioButton(frame_type);
        bl->setObjectName(QStringLiteral("bl"));
        bl->setGeometry(QRect(690, 100, 161, 81));
        bl->setFont(font1);
        bl->setFocusPolicy(Qt::ClickFocus);
        bl->setStyleSheet(QLatin1String("QRadioButton::indicator:unchecked{\n"
"background:white;\n"
"border: 1px solid;\n"
"border-color: white;\n"
"width: 33px;\n"
"height: 33px;\n"
"border-radius: 17px;\n"
"}\n"
"QRadioButton::indicator:checked{\n"
"background:black;\n"
"border: 7px solid;\n"
"border-color: white;\n"
"width: 21px;\n"
"height: 21px;\n"
"border-radius: 17px;\n"
"}\n"
"QRadioButton{\n"
"color:white;\n"
"}"));
        bl->setChecked(true);
        utm_xy->raise();
        bl->raise();
        lblChooseType->raise();
        frame_zone = new QFrame(CoordinateSystem);
        frame_zone->setObjectName(QStringLiteral("frame_zone"));
        frame_zone->setGeometry(QRect(10, 440, 1261, 191));
        frame_zone->setFrameShape(QFrame::StyledPanel);
        frame_zone->setFrameShadow(QFrame::Raised);
        zone_35 = new QRadioButton(frame_zone);
        zone_35->setObjectName(QStringLiteral("zone_35"));
        zone_35->setGeometry(QRect(480, 110, 131, 81));
        zone_35->setFont(font1);
        zone_35->setFocusPolicy(Qt::ClickFocus);
        zone_35->setStyleSheet(QLatin1String("QRadioButton::indicator:unchecked{\n"
"background:white;\n"
"border: 1px solid;\n"
"border-color: white;\n"
"width: 33px;\n"
"height: 33px;\n"
"border-radius: 17px;\n"
"}\n"
"QRadioButton::indicator:checked{\n"
"background:black;\n"
"border: 7px solid;\n"
"border-color: white;\n"
"width: 21px;\n"
"height: 21px;\n"
"border-radius: 17px;\n"
"}\n"
"QRadioButton{\n"
"color:white;\n"
"}"));
        zone_35->setChecked(true);
        lblChooseZone = new QLabel(frame_zone);
        lblChooseZone->setObjectName(QStringLiteral("lblChooseZone"));
        lblChooseZone->setGeometry(QRect(5, 10, 421, 91));
        lblChooseZone->setFont(font2);
        lblChooseZone->setStyleSheet(QStringLiteral("color: white;"));
        zone_34 = new QRadioButton(frame_zone);
        zone_34->setObjectName(QStringLiteral("zone_34"));
        zone_34->setGeometry(QRect(660, 110, 131, 81));
        zone_34->setFont(font1);
        zone_34->setFocusPolicy(Qt::ClickFocus);
        zone_34->setStyleSheet(QLatin1String("QRadioButton::indicator:unchecked{\n"
"background:white;\n"
"border: 1px solid;\n"
"border-color: white;\n"
"width: 33px;\n"
"height: 33px;\n"
"border-radius: 17px;\n"
"}\n"
"QRadioButton::indicator:checked{\n"
"background:black;\n"
"border: 7px solid;\n"
"border-color: white;\n"
"width: 21px;\n"
"height: 21px;\n"
"border-radius: 17px;\n"
"}\n"
"QRadioButton{\n"
"color:white;\n"
"}"));
        zone_35->raise();
        zone_34->raise();
        lblChooseZone->raise();

        retranslateUi(CoordinateSystem);

        QMetaObject::connectSlotsByName(CoordinateSystem);
    } // setupUi

    void retranslateUi(QDialog *CoordinateSystem)
    {
        CoordinateSystem->setWindowTitle(QApplication::translate("CoordinateSystem", "Dialog", nullptr));
        btnChooseCoordSys->setText(QApplication::translate("CoordinateSystem", "Choose", nullptr));
        krasovsky->setText(QApplication::translate("CoordinateSystem", " Krasovsky\n"
" (1942/83)", nullptr));
        wgs->setText(QApplication::translate("CoordinateSystem", "  NATO\n"
"(WGS84)", nullptr));
        lblChoose->setText(QApplication::translate("CoordinateSystem", "Choose coordinate system", nullptr));
        lblChooseType->setText(QApplication::translate("CoordinateSystem", "Choose coordinate type", nullptr));
        utm_xy->setText(QApplication::translate("CoordinateSystem", "UTM", nullptr));
        bl->setText(QApplication::translate("CoordinateSystem", "B,L", nullptr));
        zone_35->setText(QApplication::translate("CoordinateSystem", "35", nullptr));
        lblChooseZone->setText(QApplication::translate("CoordinateSystem", "Choose zone", nullptr));
        zone_34->setText(QApplication::translate("CoordinateSystem", "34", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CoordinateSystem: public Ui_CoordinateSystem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COORDINATESYSTEM_H
