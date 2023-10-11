#include "coordinatesystem.h"
#include "ui_coordinatesystem.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "bg.h"
#include "en.h"

#include "variables.h"
#include "TransLib/transform.h"
#include "TransLib/geodw.h"
#include "Periph/GpsDataManager.h"

extern "C"
{
    #include "Application/SharedVariables.h"
}

CoordinateSystem::CoordinateSystem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CoordinateSystem)
{
    ui->setupUi(this);
    g_Transform->SetModuleDir(strTTT);
    g_Transform->InitializeTransform();
    saveuserdata = new SaveLartosUserData();
    ui->wgs->setFocus();
    ui->frame_zone->hide();

    inputCooSys = CS_WGS84_CODE;
    inputCooType = CT_BL_CODE;
    inputZoneWidth = ZW_UNKNOWN_CODE;
    inputZone = 35;
    inputH = HS_UNKNOWN_CODE;

    //X_parameter = 4710481.1045;
    //Y_parameter = 266120.4208;
    //H_parameter = 302.256;
    QString x = gdmLattitude;
    QString y = gdmLongitude;
    QString h = gdmAltitude;
    double x_ = x.toDouble();
    double y_ = y.toDouble();
    double x_rad = gtor(x_, CF_CODE_DM);
    double y_rad = gtor(y_, CF_CODE_DM);
    X_parameter = rtog(x_rad, CF_CODE_DD);
    Y_parameter = rtog(y_rad, CF_CODE_DD);
    H_parameter = h.toDouble();

}

void CoordinateSystem::setCoordinateSystemParameters()
{
    if(ui->wgs->isChecked())
    {
    coordinate_system = "wgs";
        outputCooSys = CS_WGS84_CODE;
        outputH = HS_UNKNOWN_CODE;

        if(ui->utm_xy->isChecked())
        {
    coordinate_type = "utm";
            outputCooType = CT_UTM_CODE;
            outputZoneWidth = ZW_6DEGREE_CODE;

            if(ui->zone_35->isChecked())
            {
                zone = "35";
                outputZone = 35;
            }
            else if(ui->zone_34->isChecked())
            {
                zone = "34";
                outputZone = 34;
            }
        }
        else if(ui->bl->isChecked())
        {
            coordinate_type = "bl";
            outputCooType = CT_BL_CODE;
            outputZoneWidth = ZW_UNKNOWN_CODE;
        }
    }
    else if(ui->krasovsky->isChecked())
    {
        coordinate_system = "krasovsky";
        outputCooSys = CS_42_83_CODE;
        outputH = HS_UNKNOWN_CODE;

        if(ui->utm_xy->isChecked())
        {
            coordinate_type = "xy";
            outputCooType = CT_XY_CODE;
            outputZoneWidth = ZW_6DEGREE_CODE;

            if(ui->zone_35->isChecked())
            {
                zone = "27";
                outputZone = 27;
            }
            else if(ui->zone_34->isChecked())
            {
                zone = "21";
                outputZone = 21;
            }
        }
        else if(ui->bl->isChecked())
        {
            coordinate_type = "bl";
            outputCooType = CT_BL_CODE;
            outputZoneWidth = ZW_UNKNOWN_CODE;
        }
    }
}

CoordinateSystem::~CoordinateSystem()
{
    delete ui;
}

void CoordinateSystem::switchToBG()
{
    ui->lblChoose->setText(lblChooseCoordSys_BG);
    ui->lblChoose->adjustSize();
    ui->lblChoose->setGeometry(
                (this->width() - ui->lblChoose->width())/2,
                ui->lblChoose->geometry().y(),
                ui->lblChoose->width(),
                ui->lblChoose->height());

    ui->lblChooseType->setText(lblChooseCoordType_BG);
    ui->lblChooseType->adjustSize();
    ui->lblChooseType->setGeometry(
                (this->width() - ui->lblChooseType->width())/2,
                ui->lblChooseType->geometry().y(),
                ui->lblChooseType->width(),
                ui->lblChooseType->height());

    if(isWGS == true)
    {
        ui->lblChooseZone->setText(lblChooseZone_BG);
    }
    else if(isWGS == false)
    {
        ui->lblChooseZone->setText(lblChoosePrimeMer_BG);
    }
    ui->lblChooseZone->adjustSize();
    ui->lblChooseZone->setGeometry(
                (this->width() - ui->lblChooseZone->width())/2,
                ui->lblChooseZone->geometry().y(),
                ui->lblChooseZone->width(),
                ui->lblChooseZone->height());

    ui->btnChooseCoordSys->setText(btnChooseCoordSys_BG);

    flgBG_cs = true;
}

void CoordinateSystem::switchToEN()
{
    ui->lblChoose->setText(lblChooseCoordSys_EN);
    ui->lblChoose->adjustSize();
    ui->lblChoose->setGeometry(
                (this->width() - ui->lblChoose->width())/2,
                ui->lblChoose->geometry().y(),
                ui->lblChoose->width(),
                ui->lblChoose->height());

    ui->lblChooseType->setText(lblChooseCoordType_EN);
    ui->lblChooseType->adjustSize();
    ui->lblChooseType->setGeometry(
                (this->width() - ui->lblChooseType->width())/2,
                ui->lblChooseType->geometry().y(),
                ui->lblChooseType->width(),
                ui->lblChooseType->height());

    if(isWGS == true)
    {
        ui->lblChooseZone->setText(lblChooseZone_EN);
    }
    else if(isWGS == false)
    {
        ui->lblChooseZone->setText(lblChoosePrimeMer_EN);
    }
    ui->lblChooseZone->adjustSize();
    ui->lblChooseZone->setGeometry(
                (this->width() - ui->lblChooseZone->width())/2,
                ui->lblChooseZone->geometry().y(),
                ui->lblChooseZone->width(),
                ui->lblChooseZone->height());

    ui->btnChooseCoordSys->setText(btnChooseTxt_EN);

    flgBG_cs = false;
}

void CoordinateSystem::on_wgs_pressed()
{
    setKrasovskyStyleSheet();
    setUtmStyleSheet();
    setBlStyleSheet();
    setZone1StyleSheet();
    setZone2StyleSheet();
    btnChooseCoordSys_released();

    if(flgBG_cs == true)
    {
        ui->lblChooseZone->setText(lblChooseZone_BG);
    }
    else if(flgBG_cs == false)
    {
        ui->lblChooseZone->setText(lblChooseZone_EN);
    }
    ui->lblChooseZone->adjustSize();
    ui->lblChooseZone->setGeometry(
                (ui->frame_zone->width() - ui->lblChooseZone->width())/2,
                ui->lblChooseZone->geometry().y(),
                ui->lblChooseZone->width(),
                ui->lblChooseZone->height());

    ui->utm_xy->setText("UTM");
    ui->zone_35->setText("35");
    ui->zone_34->setText("34");

    ui->utm_xy->setChecked(true);
    ui->frame_zone->show();
    ui->zone_35->setChecked(true);

    isWGS = true;
}


void CoordinateSystem::on_krasovsky_pressed()
{
    setWgsStyleSheet();
    setUtmStyleSheet();
    setBlStyleSheet();
    setZone1StyleSheet();
    setZone2StyleSheet();
    btnChooseCoordSys_released();

    if(flgBG_cs == true)
    {
        ui->lblChooseZone->setText(lblChoosePrimeMer_BG);
    }
    else if(flgBG_cs == false)
    {
        ui->lblChooseZone->setText(lblChoosePrimeMer_EN);
    }
    ui->lblChooseZone->adjustSize();
    ui->lblChooseZone->setGeometry(
                (ui->frame_zone->width() - ui->lblChooseZone->width())/2,
                ui->lblChooseZone->geometry().y(),
                ui->lblChooseZone->width(),
                ui->lblChooseZone->height());

    ui->utm_xy->setText("X,Y");
    ui->zone_35->setText("27");
    ui->zone_34->setText("21");

    ui->utm_xy->setChecked(true);
    ui->frame_zone->show();
    ui->zone_35->setChecked(true);

    isWGS = false;
}


void CoordinateSystem::on_utm_xy_pressed()
{
    setWgsStyleSheet();
    setKrasovskyStyleSheet();
    setBlStyleSheet();
    setZone1StyleSheet();
    setZone2StyleSheet();
    btnChooseCoordSys_released();

    ui->frame_zone->show();
    ui->zone_35->setChecked(true);
}


void CoordinateSystem::on_bl_pressed()
{
    setWgsStyleSheet();
    setKrasovskyStyleSheet();
    setUtmStyleSheet();
    setZone1StyleSheet();
    setZone2StyleSheet();
    btnChooseCoordSys_released();

    ui->frame_zone->hide();
}


void CoordinateSystem::on_btnChooseCoordSys_pressed()
{
    setWgsStyleSheet();
    setKrasovskyStyleSheet();
    setUtmStyleSheet();
    setBlStyleSheet();
    setZone1StyleSheet();
    setZone2StyleSheet();

    btnChooseCoordSys_pressed();
}

void CoordinateSystem::openMainWin()
{
    this->close();
    MainWindow *w = new MainWindow();
    if(flgBG_cs == true)
    {
        w->switchToBG();
    }
    else if(flgBG_cs == false)
    {
        w->switchToEN();
    }
    //w->showFullScreen();
   w->show();
}

void CoordinateSystem::setWgsStyleSheet()
{
    ui->wgs->setStyleSheet("QRadioButton::indicator:unchecked{"
                           "background:white;"
                           "border: 1px solid;"
                           "border-color: white;"
                           "width: 33px;"
                           "height: 33px;"
                           "border-radius: 17px;"
                           "}"
                           "QRadioButton::indicator:checked{"
                           "background:black;"
                           "border: 7px solid;"
                           "border-color: white;"
                           "width: 21px;"
                           "height: 21px;"
                           "border-radius: 17px;"
                           "}"
                           "QRadioButton{"
                           "color:white;"
                           "}");
}

void CoordinateSystem::setKrasovskyStyleSheet()
{
    ui->krasovsky->setStyleSheet("QRadioButton::indicator:unchecked{"
                                 "background:white;"
                                 "border: 1px solid;"
                                 "border-color: white;"
                                 "width: 33px;"
                                 "height: 33px;"
                                 "border-radius: 17px;"
                                 "}"
                                 "QRadioButton::indicator:checked{"
                                 "background:black;"
                                 "border: 7px solid;"
                                 "border-color: white;"
                                 "width: 21px;"
                                 "height: 21px;"
                                 "border-radius: 17px;"
                                 "}"
                                 "QRadioButton{"
                                 "color:white;"
                                 "}");
}

void CoordinateSystem::setUtmStyleSheet()
{
    ui->utm_xy->setStyleSheet("QRadioButton::indicator:unchecked{"
                               "background:white;"
                               "border: 1px solid;"
                               "border-color: white;"
                               "width: 33px;"
                               "height: 33px;"
                               "border-radius: 17px;"
                               "}"
                               "QRadioButton::indicator:checked{"
                               "background:black;"
                               "border: 7px solid;"
                               "border-color: white;"
                               "width: 21px;"
                               "height: 21px;"
                               "border-radius: 17px;"
                               "}"
                               "QRadioButton{"
                               "color:white;"
                               "}");
}

void CoordinateSystem::setBlStyleSheet()
{
    ui->bl->setStyleSheet("QRadioButton::indicator:unchecked{"
                               "background:white;"
                               "border: 1px solid;"
                               "border-color: white;"
                               "width: 33px;"
                               "height: 33px;"
                               "border-radius: 17px;"
                               "}"
                               "QRadioButton::indicator:checked{"
                               "background:black;"
                               "border: 7px solid;"
                               "border-color: white;"
                               "width: 21px;"
                               "height: 21px;"
                               "border-radius: 17px;"
                               "}"
                               "QRadioButton{"
                               "color:white;"
                               "}");
}

void CoordinateSystem::setZone1StyleSheet()
{
    ui->zone_35->setStyleSheet("QRadioButton::indicator:unchecked{"
                               "background:white;"
                               "border: 1px solid;"
                               "border-color: white;"
                               "width: 33px;"
                               "height: 33px;"
                               "border-radius: 17px;"
                               "}"
                               "QRadioButton::indicator:checked{"
                               "background:black;"
                               "border: 7px solid;"
                               "border-color: white;"
                               "width: 21px;"
                               "height: 21px;"
                               "border-radius: 17px;"
                               "}"
                               "QRadioButton{"
                               "color:white;"
                               "}");
}

void CoordinateSystem::setZone2StyleSheet()
{
    ui->zone_34->setStyleSheet("QRadioButton::indicator:unchecked{"
                               "background:white;"
                               "border: 1px solid;"
                               "border-color: white;"
                               "width: 33px;"
                               "height: 33px;"
                               "border-radius: 17px;"
                               "}"
                               "QRadioButton::indicator:checked{"
                               "background:black;"
                               "border: 7px solid;"
                               "border-color: white;"
                               "width: 21px;"
                               "height: 21px;"
                               "border-radius: 17px;"
                               "}"
                               "QRadioButton{"
                               "color:white;"
                               "}");
}

void CoordinateSystem::gpioBtnOk()
{
    if(ui->wgs->hasFocus())
    {
        ui->wgs->setChecked(true);
        on_wgs_pressed();
    }
    else if(ui->krasovsky->hasFocus())
    {
        ui->krasovsky->setChecked(true);
        on_krasovsky_pressed();
    }
    else if(ui->utm_xy->hasFocus())
    {
        ui->utm_xy->setChecked(true);
        on_utm_xy_pressed();
    }
    else if(ui->bl->hasFocus())
    {
        ui->bl->setChecked(true);
        on_bl_pressed();
    }
    else if(ui->zone_35->hasFocus())
    {
        ui->zone_35->setChecked(true);
        on_zone_35_pressed();
    }
    else if(ui->zone_34->hasFocus())
    {
        ui->zone_34->setChecked(true);
        on_zone_34_pressed();
    }
    else if(ui->btnChooseCoordSys->hasFocus())
    {
        on_btnChooseCoordSys_released();
    }
}

void CoordinateSystem::gpioBtnLeft()
{
    if(ui->btnChooseCoordSys->hasFocus())
    {
        btnChooseCoordSys_released();
        ui->zone_34->setFocus();
        ui->zone_34->setStyleSheet("background:gray;");
    }
    else if(ui->zone_34->hasFocus())
    {
        setZone2StyleSheet();

        ui->zone_35->setFocus();
        ui->zone_35->setStyleSheet("background:gray;");
    }
    else if(ui->zone_35->hasFocus())
    {
        setZone1StyleSheet();

        ui->bl->setFocus();
        ui->bl->setStyleSheet("background:gray;");
    }
    else if(ui->bl->hasFocus())
    {
        setBlStyleSheet();

        ui->utm_xy->setFocus();
        ui->utm_xy->setStyleSheet("background:gray;");
    }
    else if(ui->utm_xy->hasFocus())
    {
        setUtmStyleSheet();

        ui->krasovsky->setFocus();
        ui->krasovsky->setStyleSheet("background:gray;");
    }
    else if(ui->krasovsky->hasFocus())
    {
        setKrasovskyStyleSheet();

        ui->wgs->setFocus();
        ui->wgs->setStyleSheet("background:gray;");
    }
}

void CoordinateSystem::gpioBtnRight()
{
    if(ui->wgs->hasFocus())
    {
        setWgsStyleSheet();

        ui->krasovsky->setFocus();
        ui->krasovsky->setStyleSheet("background:gray;");
    }
    else if(ui->krasovsky->hasFocus())
    {
        setKrasovskyStyleSheet();

        ui->utm_xy->setFocus();
        ui->utm_xy->setStyleSheet("background:gray;");
    }
    else if(ui->utm_xy->hasFocus())
    {
        setUtmStyleSheet();

        ui->bl->setFocus();
        ui->bl->setStyleSheet("background:gray;");
    }
    else if(ui->bl->hasFocus())
    {
        setBlStyleSheet();

        ui->zone_35->setFocus();
        ui->zone_35->setStyleSheet("background:gray;");
    }
    else if(ui->zone_35->hasFocus())
    {
        setZone1StyleSheet();

        ui->zone_34->setFocus();
        ui->zone_34->setStyleSheet("background:gray;");
    }
    else if(ui->zone_34->hasFocus())
    {
        setZone2StyleSheet();

        ui->btnChooseCoordSys->setFocus();
        btnChooseCoordSys_selected();
    }
}

void CoordinateSystem::gpioBtnUp()
{
    if(ui->btnChooseCoordSys->hasFocus())
    {
        btnChooseCoordSys_released();
        ui->zone_35->setFocus();
        ui->zone_35->setStyleSheet("background:gray;");
    }
    else if(ui->zone_35->hasFocus() || ui->zone_34->hasFocus())
    {
        setZone1StyleSheet();
        setZone2StyleSheet();

        ui->utm_xy->setFocus();
        ui->utm_xy->setStyleSheet("background:gray;");
    }
    else if(ui->utm_xy->hasFocus() || ui->bl->hasFocus())
    {
        setUtmStyleSheet();
        setWgsStyleSheet();

        ui->wgs->setFocus();
        ui->wgs->setStyleSheet("background:gray;");
    }
}

void CoordinateSystem::gpioBtnDown()
{
    if(ui->wgs->hasFocus() || ui->krasovsky->hasFocus())
    {
        setWgsStyleSheet();
        setKrasovskyStyleSheet();

        ui->utm_xy->setFocus();
        ui->utm_xy->setStyleSheet("background:gray;");
    }
    else if(ui->utm_xy->hasFocus() || ui->bl->hasFocus())
    {
        setUtmStyleSheet();
        setBlStyleSheet();

        ui->zone_35->setFocus();
        ui->zone_35->setStyleSheet("background:gray;");
    }
    else if(ui->zone_35->hasFocus() || ui->zone_34->hasFocus())
    {
        setZone1StyleSheet();
        setZone2StyleSheet();

        ui->btnChooseCoordSys->setFocus();
        btnChooseCoordSys_selected();
    }
}

void CoordinateSystem::btnChooseCoordSys_pressed()
{
    ui->btnChooseCoordSys->setStyleSheet(
                "padding: 0 8px;"
                "background: gray;"
                "color: black;"
                );
}

void CoordinateSystem::btnChooseCoordSys_released()
{
    ui->btnChooseCoordSys->setStyleSheet(
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}

void CoordinateSystem::btnChooseCoordSys_selected()
{
    ui->btnChooseCoordSys->setStyleSheet(
                "border: 5px solid white; "
                "padding: 0 8px;"
                "background: gray;"
                "color: black;"
                );
}

void CoordinateSystem::on_zone_35_pressed()
{
    setWgsStyleSheet();
    setKrasovskyStyleSheet();
    setUtmStyleSheet();
    setBlStyleSheet();
    setZone2StyleSheet();
    btnChooseCoordSys_released();
}


void CoordinateSystem::on_zone_34_pressed()
{
    setWgsStyleSheet();
    setKrasovskyStyleSheet();
    setUtmStyleSheet();
    setBlStyleSheet();
    setZone1StyleSheet();
    btnChooseCoordSys_released();
}


void CoordinateSystem::on_btnChooseCoordSys_released()
{
    btnChooseCoordSys_released();

    setCoordinateSystemParameters();
    if(inputCooType == CT_XY_CODE && outputCooType == CT_UTM_CODE)
    {}
    else
    {
        g_Transform->Transform(inputCooSys, outputCooSys, inputCooType, outputCooType, inputZoneWidth, outputZoneWidth, inputZone, &outputZone, inputH, outputH, &X_parameter, &Y_parameter, &H_parameter);
        if(outputCooType == CT_BL_CODE)
        {
            X_parameter = rtog(X_parameter, CF_CODE_DD);
            Y_parameter = rtog(Y_parameter, CF_CODE_DD);
        }
        inputCooSys = outputCooSys;
        inputCooType = outputCooType;
        inputZone = outputZone;
        inputH = outputH;
        inputZoneWidth = outputZoneWidth;
    }
    calculatedLat = X_parameter;
    calculatedLong = Y_parameter;
    updateCoordinates = true;
    openMainWin();
}
