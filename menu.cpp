#include "menu.h"
#include "ui_menu.h"

#include "bg.h"
#include "en.h"
#include "variables.h"
#include <QKeyEvent>
#include <QVariant>
#include <QTableView>
#include <QTreeView>
#include <QListView>
#include <QDesktopWidget>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include "LartosPointObj.h"
#include "TransLib/transform.h"
#include "TransLib/geodw.h"

bool isOffsetReticleVisible = false;

extern "C"
{
    #include "Periph/LucidCameraDraw.h"
    #include "Application/SharedVariables.h"
}

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);

    setAttribute(Qt::WA_AcceptTouchEvents, true);

    g_Transform->SetModuleDir(strTTT);
    g_Transform->InitializeTransform();

    ui->manufacturingBox->setGeometry(10, 10, 1260, 781);
    ui->manufacturingBox->hide();
    ui->btnChooseLang->setEnabled(false);
    ui->manufacturing->hide();
    ui->keyboard_qwerty->hide();
    ui->keyboard->hide();
    ui->btnReset->hide();
    ui->wrong_reset->hide();
    ui->invalid->hide();
    ui->frame_keyboard_md->hide();
    ui->grBoxPassMessage->hide();

    ui->settings->setCurrentIndex(6);
    ui->manufacturing->setCurrentIndex(2);

    QString pos_br = QString::number(ui->brightness->value());
    ui->brightness_lbl->setText("Brightness: ");

    QString pos_c = QString::number(ui->contrast->value());
    ui->contrast_lbl->setText("Contrast: ");

    QString pos_dde = QString::number(ui->dde->value());
    ui->dde_lbl->setText("DDE: ");

    qApp->installEventFilter(this);

    currentVideoPanelX = 990;
    currentVideoPanelY = 540;
    currentVideoPanel = ui->frameLabel;
    connect(thermController->processingThread,SIGNAL(newFrame(QPixmap)),this,SLOT(updateFrame(QPixmap)));

    _magnDecl = QString::number(magnDecl);
    //if(magnDecl != 0)
    //{
    //    ui->txtDegrees->setText(_magnDecl);
    //}
    //if(magnDecl < 0)
    //{
    //    ui->lblOperator->setText("-");
    //}

    capsLock = false;

    checkCoordinateSystem();
    checkPointsCoordinateType();
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width()-this->width()) / 2;
    int y = (screenGeometry.height()-this->height()) / 2;
    //this->move(485, 280);
    this->move(x, y);

    Menu::setSmallLetters();
    Menu::initTableView();
    saveuserdata = new SaveLartosUserData();
    hashPoint = savePointObj->readPointFromFile();
    Menu::loadPointData();

    Menu::readAllUserSettings();
}

Menu::~Menu()
{
    delete ui;
}

void Menu::updateFrame(const QPixmap &frame)
{
    if(currentVideoPanel==ui->frameLabel)
    {
        ui->frameLabel->setPixmap(frame);
    }
}

void Menu::setCoordinateSystemParameters()
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

void Menu::readAllUserSettings(){
    qDebug() << "Read json....";
    ui->dde_mode->setChecked(saveuserdata->getDeeModeParameter());
    qDebug() << saveuserdata->getDeeModeParameter();

    ui->dde->setValue(saveuserdata->getDeeValueParameter());
    qDebug() << saveuserdata->getDeeValueParameter();

    ui->lblDDE_value->setText(QString::number(saveuserdata->getDeeValueParameter()));
    qDebug() << saveuserdata->getDeeValueParameter();

    ui->contrast->setValue(saveuserdata->getContrastValueParameter());
    qDebug() << saveuserdata->getContrastValueParameter();

    ui->lblContrast_value->setText(QString::number(saveuserdata->getContrastValueParameter()));
    qDebug() << saveuserdata->getContrastValueParameter();

    ui->brightness->setValue(saveuserdata->getBrightnessValueParameter());
    qDebug() << saveuserdata->getBrightnessValueParameter();

    ui->lblBrightness_value->setText(QString::number(saveuserdata->getBrightnessValueParameter()));
    qDebug() << saveuserdata->getBrightnessValueParameter();
}

void Menu::checkCoordinateSystem()
{
    if(coordinate_system == "wgs")
    {
        ui->wgs->setChecked(true);
    }
    else if(coordinate_system == "krasovsky")
    {
        ui->krasovsky->setChecked(true);
        ui->utm_xy->setText("X,Y");
        ui->zone_35->setText("27");
        ui->zone_34->setText("21");
    }

    if(coordinate_type == "utm")
    {
        ui->utm_xy->setChecked(true);
    }
    else if(coordinate_type == "xy")
    {
        ui->utm_xy->setChecked(true);
    }
    else if(coordinate_type == "bl")
    {
        ui->bl->setChecked(true);
        ui->frame_zone->hide();
    }

    if(zone == "35" || zone == "27")
    {
        ui->zone_35->setChecked(true);
    }
    else if(zone == "34" || zone == "21")
    {
        ui->zone_34->setChecked(true);
    }
}

void Menu::checkPointsCoordinateType()
{
    if(coordinate_type == "utm")
    {
        ui->comboBox->setCurrentIndex(0);
        ui->label_3->setText("Northing");
        ui->label_4->setText("   Easting");
    }
    else if(coordinate_type == "xy")
    {
        ui->comboBox->setCurrentIndex(1);
        ui->label_3->setText("         X");
        ui->label_4->setText("         Y");
    }
    else if(coordinate_type == "bl")
    {
        ui->comboBox->setCurrentIndex(2);
        ui->label_3->setText("Latitude");
        ui->label_4->setText("Longitude");
    }
}

void Menu::setWgsStyleSheet()
{
    ui->wgs->setStyleSheet("QRadioButton::indicator:unchecked{"
                           "background:white;"
                           "border: 1px solid;"
                           "border-color: white;"
                           "width: 22px;"
                           "height: 22px;"
                           "border-radius: 12px;"
                           "}"
                           "QRadioButton::indicator:checked{"
                           "background:black;"
                           "border: 5px solid;"
                           "border-color: white;"
                           "width: 14px;"
                           "height: 14px;"
                           "border-radius: 12px;"
                           "}"
                           "QRadioButton{"
                           "color:white;"
                           "border:0px;"
                           "}");
}

void Menu::setKrasovskyStyleSheet()
{
    ui->krasovsky->setStyleSheet("QRadioButton::indicator:unchecked{"
                                 "background:white;"
                                 "border: 1px solid;"
                                 "border-color: white;"
                                 "width: 22px;"
                                 "height: 22px;"
                                 "border-radius: 12px;"
                                 "}"
                                 "QRadioButton::indicator:checked{"
                                 "background:black;"
                                 "border: 5px solid;"
                                 "border-color: white;"
                                 "width: 14px;"
                                 "height: 14px;"
                                 "border-radius: 12px;"
                                 "}"
                                 "QRadioButton{"
                                 "color:white;"
                                 "border:0px;"
                                 "}");
}

void Menu::setUtmStyleSheet()
{
    ui->utm_xy->setStyleSheet("QRadioButton::indicator:unchecked{"
                              "background:white;"
                              "border: 1px solid;"
                              "border-color: white;"
                              "width: 22px;"
                              "height: 22px;"
                              "border-radius: 12px;"
                              "}"
                              "QRadioButton::indicator:checked{"
                              "background:black;"
                              "border: 5px solid;"
                              "border-color: white;"
                              "width: 14px;"
                              "height: 14px;"
                              "border-radius: 12px;"
                              "}"
                              "QRadioButton{"
                              "color:white;"
                              "border:0px;"
                              "}");
}

void Menu::setDlhStyleSheet()
{
    ui->bl->setStyleSheet("QRadioButton::indicator:unchecked{"
                           "background:white;"
                           "border: 1px solid;"
                           "border-color: white;"
                           "width: 22px;"
                           "height: 22px;"
                           "border-radius: 12px;"
                           "}"
                           "QRadioButton::indicator:checked{"
                           "background:black;"
                           "border: 5px solid;"
                           "border-color: white;"
                           "width: 14px;"
                           "height: 14px;"
                           "border-radius: 12px;"
                           "}"
                           "QRadioButton{"
                           "color:white;"
                           "border:0px;"
                           "}");
}

void Menu::setZone1StyleSheet()
{
    ui->zone_35->setStyleSheet("QRadioButton::indicator:unchecked{"
                               "background:white;"
                               "border: 1px solid;"
                               "border-color: white;"
                               "width: 22px;"
                               "height: 22px;"
                               "border-radius: 12px;"
                               "}"
                               "QRadioButton::indicator:checked{"
                               "background:black;"
                               "border: 5px solid;"
                               "border-color: white;"
                               "width: 14px;"
                               "height: 14px;"
                               "border-radius: 12px;"
                               "}"
                               "QRadioButton{"
                               "color:white;"
                               "border:0px;"
                               "}");
}

void Menu::setZone2StyleSheet()
{
    ui->zone_34->setStyleSheet("QRadioButton::indicator:unchecked{"
                               "background:white;"
                               "border: 1px solid;"
                               "border-color: white;"
                               "width: 22px;"
                               "height: 22px;"
                               "border-radius: 12px;"
                               "}"
                               "QRadioButton::indicator:checked{"
                               "background:black;"
                               "border: 5px solid;"
                               "border-color: white;"
                               "width: 14px;"
                               "height: 14px;"
                               "border-radius: 12px;"
                               "}"
                               "QRadioButton{"
                               "color:white;"
                               "border:0px;"
                               "}");
}

void Menu::btnReset_pressed()
{
    ui->btnReset->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: black;"
                );
}

void Menu::btnReset_released()
{
    ui->btnReset->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}

void Menu::btnReset_selected()
{
    ui->btnReset->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: black;"
                );
}

void Menu::btnConfirmPassReset_pressed()
{
    ui->btnConfirmPassReset->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: black;"
                );
}

void Menu::btnConfirmPassReset_released()
{
    ui->btnConfirmPassReset->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}

void Menu::btnConfirmPassReset_selected()
{
    ui->btnConfirmPassReset->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: black;"
                );
}

void Menu::btnConfirmPass_pressed()
{
    ui->btnConfirmPass->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: black;"
                );
}

void Menu::btnConfirmPass_released()
{
    ui->btnConfirmPass->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}

void Menu::btnConfirmPass_selected()
{
    ui->btnConfirmPass->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: black;"
                );
}

void Menu::btnChooseLang_pressed()
{
    ui->btnChooseLang->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: black;"
                );
}

void Menu::btnChooseLang_released()
{
    ui->btnChooseLang->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}

void Menu::btnChooseLang_selected()
{
    ui->btnChooseLang->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: black;"
                );
}

void Menu::btnBack_pressed()
{
    ui->btnBack->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: black;"
                );
}

void Menu::btnBack_released()
{
    ui->btnBack->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}

void Menu::btnBack_selected()
{
    ui->btnBack->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: black;"
                );
}

void Menu::btnChooseCoordSys_pressed()
{
    ui->btnChooseCoordSys->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: black;"
                );
}

void Menu::btnChooseCoordSys_released()
{
    ui->btnChooseCoordSys->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}

void Menu::btnChooseCoordSys_selected()
{
    ui->btnChooseCoordSys->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: black;"
                );
}

void Menu::btnConfirmDecl_pressed()
{
    ui->btnConfirmDecl->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: black;"
                );
}

void Menu::btnConfirmDecl_released()
{
    ui->btnConfirmDecl->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}

void Menu::btnConfirmDecl_selected()
{
    ui->btnConfirmDecl->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: black;"
                );
}

void Menu::k1_pressed()
{
    ui->k1->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                "color: black;"
                );
}

void Menu::k1_released()
{
    ui->k1->setStyleSheet(
                "border: 2px solid black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: white;"
                "color: black;"
                );
}

void Menu::k1_selected()
{
    ui->k1->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                "color: black;"
                );
}

void Menu::k2_pressed()
{
    ui->k2->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                "color: black;"
                );
}

void Menu::k2_released()
{
    ui->k2->setStyleSheet(
                "border: 2px solid black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: white;"
                "color: black;"
                );
}


void Menu::k2_selected()
{
    ui->k2->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                "color: black;"
                );
}


void Menu::k3_pressed()
{
    ui->k3->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                "color: black;"
                );
}


void Menu::k3_released()
{
    ui->k3->setStyleSheet(
                "border: 2px solid black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: white;"
                "color: black;"
                );
}


void Menu::k3_selected()
{
    ui->k3->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                "color: black;"
                );
}


void Menu::k4_pressed()
{
    ui->k4->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                "color: black;"
                );
}


void Menu::k4_released()
{
    ui->k4->setStyleSheet(
                "border: 2px solid black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: white;"
                "color: black;"
                );
}

void Menu::k4_selected()
{
    ui->k4->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                "color: black;"
                );
}


void Menu::k5_pressed()
{
    ui->k5->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                "color: black;"
                );
}


void Menu::k5_released()
{
    ui->k5->setStyleSheet(
                "border: 2px solid black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: white;"
                "color: black;"
                );
}


void Menu::k5_selected()
{
    ui->k5->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                "color: black;"
                );
}


void Menu::k6_pressed()
{
    ui->k6->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                "color: black;"
                );
}


void Menu::k6_released()
{
    ui->k6->setStyleSheet(
                "border: 2px solid black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: white;"
                "color: black;"
                );
}


void Menu::k6_selected()
{
    ui->k6->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                "color: black;"
                );
}


void Menu::k7_pressed()
{
    ui->k7->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                "color: black;"
                );
}


void Menu::k7_released()
{
    ui->k7->setStyleSheet(
                "border: 2px solid black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: white;"
                "color: black;"
                );
}


void Menu::k7_selected()
{
    ui->k7->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                "color: black;"
                );
}


void Menu::k8_pressed()
{
    ui->k8->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                "color: black;"
                );
}


void Menu::k8_released()
{
    ui->k8->setStyleSheet(
                "border: 2px solid black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: white;"
                "color: black;"
                );
}


void Menu::k8_selected()
{
    ui->k8->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                "color: black;"
                );
}


void Menu::k9_pressed()
{
    ui->k9->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                "color: black;"
                );
}


void Menu::k9_released()
{
    ui->k9->setStyleSheet(
                "border: 2px solid black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: white;"
                "color: black;"
                );
}


void Menu::k9_selected()
{
    ui->k9->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                "color: black;"
                );
}


void Menu::k0_pressed()
{
    ui->k0->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                "color: black;"
                );
}


void Menu::k0_released()
{
    ui->k0->setStyleSheet(
                "border: 2px solid black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: white;"
                "color: black;"
                );
}


void Menu::k0_selected()
{
    ui->k0->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                "color: black;"
                );
}


void Menu::ok_pressed()
{
    ui->ok->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                "color: black;"
                );
}


void Menu::ok_released()
{
    ui->ok->setStyleSheet(
                "border: 2px solid black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: white;"
                "color: black;"
                );
}


void Menu::ok_selected()
{
    ui->ok->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                "color: black;"
                );
}


void Menu::del_pressed()
{
    ui->del->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                "color: black;"
                );
}


void Menu::del_released()
{
    ui->del->setStyleSheet(
                "border: 2px solid black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: white;"
                "color: black;"
                );
}


void Menu::del_selected()
{
    ui->del->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                "color: black;"
                );
}


void Menu::m_confirmPass_pressed()
{
    ui->m_confirmPass->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: black;"
                );
}
void Menu::m_confirmPass_released()
{
    ui->m_confirmPass->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}
void Menu::m_ok_pressed()
{
    ui->m_ok->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "background: white;"
                "color: black;"
                );
}
void Menu::m_ok_released()
{
    ui->m_ok->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}
void Menu::m_back_pressed()
{
    ui->m_back->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: black;"
                );
}
void Menu::m_back_released()
{
    ui->m_back->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}
void Menu::up_pressed()
{
    ui->up->setStyleSheet(
                "border: 2px rgba(255, 255, 255, 0);"
                "border-radius: 10px;"
                "background: rgba(255, 255, 255, 0);"
                );
}
void Menu::up_released()
{
    ui->up->setStyleSheet(
                "border: 2px rgba(255, 255, 255, 0);"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: rgba(255, 255, 255, 0);"
                );
}
void Menu::down_pressed()
{
    ui->down->setStyleSheet(
                "border: 2px rgba(255, 255, 255, 0);"
                "border-radius: 10px;"
                "background: rgba(255, 255, 255, 0);"
                );
}
void Menu::down_released()
{
    ui->down->setStyleSheet(
                "border: 2px rgba(255, 255, 255, 0);"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: rgba(255, 255, 255, 0);"
                );
}
void Menu::left_pressed()
{
    ui->left->setStyleSheet(
                "border: 2px rgba(255, 255, 255, 0);"
                "border-radius: 10px;"
                "background: rgba(255, 255, 255, 0);"
                );
}
void Menu::left_released()
{
    ui->left->setStyleSheet(
                "border: 2px rgba(255, 255, 255, 0);"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: rgba(255, 255, 255, 0);"
                );
}
void Menu::right_pressed()
{
    ui->right->setStyleSheet(
                "border: 2px rgba(255, 255, 255, 0);"
                "border-radius: 10px;"
                "background: rgba(255, 255, 255, 0);"
                );
}
void Menu::right_released()
{
    ui->right->setStyleSheet(
                "border: 2px rgba(255, 255, 255, 0);"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: rgba(255, 255, 255, 0);"
                );
}


void Menu::k1_magneticDeclination_pressed()
{
    ui->k1_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid white;"
                "color: black;"
                );
}


void Menu::k1_magneticDeclination_released()
{
    ui->k1_magneticDeclination->setStyleSheet(
                "border: 2px solid white;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid black;"
                "color: white;"
                );
}


void Menu::k1_magneticDeclination_selected()
{
    ui->k1_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid gray;"
                "color: black;"
                );
}


void Menu::k2_magneticDeclination_pressed()
{
    ui->k2_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid white;"
                "color: black;"
                );
}


void Menu::k2_magneticDeclination_released()
{
    ui->k2_magneticDeclination->setStyleSheet(
                "border: 2px solid white;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid black;"
                "color: white;"
                );
}


void Menu::k2_magneticDeclination_selected()
{
    ui->k2_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid gray;"
                "color: black;"
                );
}


void Menu::k3_magneticDeclination_pressed()
{
    ui->k3_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid white;"
                "color: black;"
                );
}


void Menu::k3_magneticDeclination_released()
{
    ui->k3_magneticDeclination->setStyleSheet(
                "border: 2px solid white;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid black;"
                "color: white;"
                );
}


void Menu::k3_magneticDeclination_selected()
{
    ui->k3_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid gray;"
                "color: black;"
                );
}


void Menu::k4_magneticDeclination_pressed()
{
    ui->k4_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid white;"
                "color: black;"
                );
}


void Menu::k4_magneticDeclination_released()
{
    ui->k4_magneticDeclination->setStyleSheet(
                "border: 2px solid white;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid black;"
                "color: white;"
                );
}


void Menu::k4_magneticDeclination_selected()
{
    ui->k4_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid gray;"
                "color: black;"
                );
}


void Menu::k5_magneticDeclination_pressed()
{
    ui->k5_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid white;"
                "color: black;"
                );
}


void Menu::k5_magneticDeclination_released()
{
    ui->k5_magneticDeclination->setStyleSheet(
                "border: 2px solid white;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid black;"
                "color: white;"
                );
}


void Menu::k5_magneticDeclination_selected()
{
    ui->k5_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid gray;"
                "color: black;"
                );
}


void Menu::k6_magneticDeclination_pressed()
{
    ui->k6_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid white;"
                "color: black;"
                );
}


void Menu::k6_magneticDeclination_released()
{
    ui->k6_magneticDeclination->setStyleSheet(
                "border: 2px solid white;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid black;"
                "color: white;"
                );
}


void Menu::k6_magneticDeclination_selected()
{
    ui->k6_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid gray;"
                "color: black;"
                );
}


void Menu::k7_magneticDeclination_pressed()
{
    ui->k7_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid white;"
                "color: black;"
                );
}


void Menu::k7_magneticDeclination_released()
{
    ui->k7_magneticDeclination->setStyleSheet(
                "border: 2px solid white;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid black;"
                "color: white;"
                );
}


void Menu::k7_magneticDeclination_selected()
{
    ui->k7_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid gray;"
                "color: black;"
                );
}


void Menu::k8_magneticDeclination_pressed()
{
    ui->k8_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid white;"
                "color: black;"
                );
}


void Menu::k8_magneticDeclination_released()
{
    ui->k8_magneticDeclination->setStyleSheet(
                "border: 2px solid white;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid black;"
                "color: white;"
                );
}


void Menu::k8_magneticDeclination_selected()
{
    ui->k8_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid gray;"
                "color: black;"
                );
}


void Menu::k9_magneticDeclination_pressed()
{
    ui->k9_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid white;"
                "color: black;"
                );
}


void Menu::k9_magneticDeclination_released()
{
    ui->k9_magneticDeclination->setStyleSheet(
                "border: 2px solid white;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid black;"
                "color: white;"
                );
}


void Menu::k9_magneticDeclination_selected()
{
    ui->k9_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid gray;"
                "color: black;"
                );
}


void Menu::k0_magneticDeclination_pressed()
{
    ui->k0_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid white;"
                "color: black;"
                );
}


void Menu::k0_magneticDeclination_released()
{
    ui->k0_magneticDeclination->setStyleSheet(
                "border: 2px solid white;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid black;"
                "color: white;"
                );
}


void Menu::k0_magneticDeclination_selected()
{
    ui->k0_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid gray;"
                "color: black;"
                );
}


void Menu::k_minus_magneticDeclination_pressed()
{
    ui->k_minus_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid white;"
                "color: black;"
                );
}


void Menu::k_minus_magneticDeclination_released()
{
    ui->k_minus_magneticDeclination->setStyleSheet(
                "border: 2px solid white;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid black;"
                "color: white;"
                );
}


void Menu::k_minus_magneticDeclination_selected()
{
    ui->k_minus_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid gray;"
                "color: black;"
                );
}


void Menu::k_plus_magneticDeclination_pressed()
{
    ui->k_plus_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid white;"
                "color: black;"
                );
}


void Menu::k_plus_magneticDeclination_released()
{
    ui->k_plus_magneticDeclination->setStyleSheet(
                "border: 2px solid white;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid black;"
                "color: white;"
                );
}


void Menu::k_plus_magneticDeclination_selected()
{
    ui->k_plus_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid gray;"
                "color: black;"
                );
}


void Menu::k_dot_magneticDeclination_pressed()
{
    ui->k_dot_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid white;"
                "color: black;"
                );
}


void Menu::k_dot_magneticDeclination_released()
{
    ui->k_dot_magneticDeclination->setStyleSheet(
                "border: 2px solid white;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid black;"
                "color: white;"
                );
}


void Menu::k_dot_magneticDeclination_selected()
{
    ui->k_dot_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid gray;"
                "color: black;"
                );
}


void Menu::k_del_magneticDeclination_pressed()
{
    ui->k_del_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid white;"
                "color: black;"
                );
}


void Menu::k_del_magneticDeclination_released()
{
    ui->k_del_magneticDeclination->setStyleSheet(
                "border: 2px solid white;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid black;"
                "color: white;"
                );
}


void Menu::k_del_magneticDeclination_selected()
{
    ui->k_del_magneticDeclination->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: soid gray;"
                "color: black;"
                );
}


void Menu::ok_reset_pressed()
{
    ui->ok_reset->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "background: white;"
                "color: black;"
                );
}
void Menu::ok_reset_released()
{
    ui->ok_reset->setStyleSheet(
                "border: 2px solid black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}


void Menu::switchToBG()
{
    flgBG_m = true;

    //Settings
    ui->lblSettings->setText(lblSettingsTxt_BG);
    ui->lblSettings->adjustSize();
    ui->lblSettings->setGeometry(
                (ui->settingsBox->width() - ui->lblSettings->width())/2,
                ui->lblSettings->geometry().y(),
                ui->lblSettings->width(),
                ui->lblSettings->height());

    ui->lblCurrPass->setText(lblCurrPassTxt_BG);
    ui->lblNewPass->setText(lblNewPassTxt_BG);
    ui->lblConfPass->setText(lblConfPassTxt_BG);
    ui->btnConfirmPass->setText(btnConfirmTxt_BG);

    ui->lblChooseLang->setText(lblChooseLangTxt_BG);
    ui->lblChooseLang->adjustSize();
    ui->lblChooseLang->setGeometry(
                (ui->settings->width() - ui->lblChooseLang->width())/2,
                ui->lblChooseLang->geometry().y(),
                ui->lblChooseLang->width(),
                ui->lblChooseLang->height());

    ui->btnChooseLang->setText(btnChooseTxt_BG);
    ui->k_del_magneticDeclination->setText(btnDelTxt_BG);
    ui->lblInsert->setText(lblInsertTxt_m_BG);
    ui->btnConfirmDecl->setText(btnConfirmTxt_BG);

    //ui->lblChoose->setText(lblChooseCSTxt_BG);
    //ui->lblChoose->adjustSize();
    //ui->lblChoose->setGeometry(
    //            (ui->settings->width() - ui->lblChoose->width())/2,
    //            ui->lblChoose->geometry().y(),
    //            ui->lblChoose->width(),
    //            ui->lblChoose->height());

    ui->btnChooseCoordSys->setText(btnChooseTxt_BG);
    ui->settings->setItemText(0, tabChangePassTxt_BG);
    ui->settings->setItemText(1, tabLanguageTxt_BG);
    ui->settings->setItemText(2, tabMagnDeclTxt_BG);
    ui->settings->setItemText(3, tabCoordSysTxt_BG);
    ui->settings->setItemText(4, tabPointsTxt_BG);
    ui->settings->setItemText(5, tabFactoryResetTxt_BG);

    ui->lblInsertPassword->setText(lblInsertTxt_BG);
    ui->lblInsertPassword->adjustSize();
    ui->lblInsertPassword->setGeometry(
                (ui->grBoxReset->width() - ui->lblInsertPassword->width())/2,
                ui->lblInsertPassword->geometry().y(),
                ui->lblInsertPassword->width(),
                ui->lblInsertPassword->height());

    ui->lblWrongPass->setText(lblWrongPassTxt_BG);
    ui->lblWrongPass->adjustSize();
    ui->lblWrongPass->setGeometry(
                (ui->wrong_reset->width() - ui->lblWrongPass->width())/2,
                ui->lblWrongPass->geometry().y(),
                ui->lblWrongPass->width(),
                ui->lblWrongPass->height());

    ui->btnConfirmPassReset->setText(btnConfirmTxt_BG);

    ui->add_btn->setText(btnAddTxt_BG);
    ui->delete_btn->setText(btnRemoveTxt_BG);

    ui->lblChoose->setText(lblChooseCoordSys_m_BG);
    ui->lblChoose->adjustSize();
    ui->lblChoose->setGeometry(
                (ui->frame_->width() - ui->lblChoose->width())/2,
                ui->lblChoose->geometry().y(),
                ui->lblChoose->width(),
                ui->lblChoose->height());
    ui->lblChooseType->setText(lblChooseCoordType_m_BG);
    ui->lblChooseType->adjustSize();
    ui->lblChooseType->setGeometry(
                (ui->frame_type->width() - ui->lblChooseType->width())/2,
                ui->lblChooseType->geometry().y(),
                ui->lblChooseType->width(),
                ui->lblChooseType->height());

    if(isWGS == true)
    {
        ui->lblChoose_zone->setText(lblChooseZone_m_BG);
    }
    else if(isWGS == false)
    {
        ui->lblChoose_zone->setText(lblChoosePrimeMer_m_BG);
    }
    ui->lblChoose_zone->adjustSize();
    ui->lblChoose_zone->setGeometry(
                (ui->frame_zone->width() - ui->lblChoose_zone->width())/2,
                ui->lblChoose_zone->geometry().y(),
                ui->lblChoose_zone->width(),
                ui->lblChoose_zone->height());

    //ui->label->setText(lblNameTxt_BG);
    //ui->label_3->setText(lblLatitudeTxt_BG);
    //ui->label_4->setText(lblLongitudeTxt_BG);
    //ui->label_5->setText(lblAltitudeTxt_BG);


    //Manufacturing
    ui->label_2->setText(lblManSettingsTxt_BG);
    ui->label_2->adjustSize();
    ui->label_2->setGeometry(
                (ui->manufacturingBox->width() - ui->label_2->width())/2,
                ui->label_2->geometry().y(),
                ui->label_2->width(),
                ui->label_2->height());

    ui->label_7->setText(lblInsertTxt_BG);
    ui->label_7->adjustSize();
    ui->label_7->setGeometry(
                (ui->grBoxPass->width() - ui->label_7->width())/2,
                ui->label_7->geometry().y(),
                ui->label_7->width(),
                ui->label_7->height());

    ui->label_8->setText(lblWrongPassTxt_BG);
    ui->label_8->adjustSize();
    ui->label_8->setGeometry(
                (ui->wrong->width() - ui->label_8->width())/2,
                ui->label_8->geometry().y(),
                ui->label_8->width(),
                ui->label_8->height());

    ui->m_confirmPass->setText(btnConfirmTxt_BG);
    ui->brightness_lbl->setText(lblBrightnessTxt_BG);
    ui->contrast_lbl->setText(lblContrastTxt_BG);
    ui->manufacturing->setItemText(0, tabThermalCameraTxt_BG);
    ui->manufacturing->setItemText(1, tabBoresightTxt_BG);
    ui->btnSaveReticlePos->setText(btnSaveTxt_BG);
    ui->btnConfirmCamSettings->setText(btnConfirmTxt_BG);

    ui->lblInsertValueDecl->setText(lbl_na_BG);
}

void Menu::switchToEN()
{
    flgBG_m = false;

    //Settings
    ui->lblSettings->setText(lblSettingsTxt_EN);
    ui->lblSettings->adjustSize();
    ui->lblSettings->setGeometry(
                (ui->settingsBox->width() - ui->lblSettings->width())/2,
                ui->lblSettings->geometry().y(),
                ui->lblSettings->width(),
                ui->lblSettings->height());

    ui->lblCurrPass->setText(lblCurrPassTxt_EN);
    ui->lblNewPass->setText(lblNewPassTxt_EN);
    ui->lblConfPass->setText(lblConfPassTxt_EN);
    ui->btnConfirmPass->setText(btnConfirmTxt_EN);

    ui->lblChooseLang->setText(lblChooseLangTxt_EN);
    ui->lblChooseLang->adjustSize();
    ui->lblChooseLang->setGeometry(
                (ui->settings->width() - ui->lblChooseLang->width())/2,
                ui->lblChooseLang->geometry().y(),
                ui->lblChooseLang->width(),
                ui->lblChooseLang->height());

    ui->btnChooseLang->setText(btnChooseTxt_EN);
    ui->k_del_magneticDeclination->setText(btnDelTxt_EN);
    ui->lblInsert->setText(lblInsertTxt_m_EN);
    ui->btnConfirmDecl->setText(btnConfirmTxt_EN);

    //ui->lblChoose->setText(lblChooseCSTxt_EN);
    //ui->lblChoose->adjustSize();
    //ui->lblChoose->setGeometry(
    //            (ui->settings->width() - ui->lblChoose->width())/2,
    //            ui->lblChoose->geometry().y(),
    //            ui->lblChoose->width(),
    //            ui->lblChoose->height());

    ui->btnChooseCoordSys->setText(btnChooseTxt_EN);
    ui->settings->setItemText(0, tabChangePassTxt_EN);
    ui->settings->setItemText(1, tabLanguageTxt_EN);
    ui->settings->setItemText(2, tabMagnDeclTxt_EN);
    ui->settings->setItemText(3, tabCoordSysTxt_EN);
    ui->settings->setItemText(4, tabPointsTxt_EN);
    ui->settings->setItemText(5, tabFactoryResetTxt_EN);
  

    ui->lblInsertPassword->setText(lblInsertTxt_EN);
    ui->lblInsertPassword->adjustSize();
    ui->lblInsertPassword->setGeometry(
                (ui->grBoxReset->width() - ui->lblInsertPassword->width())/2,
                ui->lblInsertPassword->geometry().y(),
                ui->lblInsertPassword->width(),
                ui->lblInsertPassword->height());

    ui->btnConfirmPassReset->setText(btnConfirmTxt_EN);

    ui->lblWrongPass->setText(lblWrongPassTxt_EN);
    ui->lblWrongPass->adjustSize();
    ui->lblWrongPass->setGeometry(
                (ui->wrong_reset->width() - ui->lblWrongPass->width())/2,
                ui->lblWrongPass->geometry().y(),
                ui->lblWrongPass->width(),
                ui->lblWrongPass->height());

    ui->add_btn->setText(btnAddTxt_EN);
    ui->delete_btn->setText(btnRemoveTxt_EN);

    ui->lblChoose->setText(lblChooseCoordSys_m_EN);
    ui->lblChoose->adjustSize();
    ui->lblChoose->setGeometry(
                (ui->frame_->width() - ui->lblChoose->width())/2,
                ui->lblChoose->geometry().y(),
                ui->lblChoose->width(),
                ui->lblChoose->height());
    ui->lblChooseType->setText(lblChooseCoordType_m_EN);
    ui->lblChooseType->adjustSize();
    ui->lblChooseType->setGeometry(
                (ui->frame_type->width() - ui->lblChooseType->width())/2,
                ui->lblChooseType->geometry().y(),
                ui->lblChooseType->width(),
                ui->lblChooseType->height());

    if(isWGS == true)
    {
        ui->lblChoose_zone->setText(lblChooseZone_m_EN);
    }
    else if(isWGS == false)
    {
        ui->lblChoose_zone->setText(lblChoosePrimeMer_m_EN);
    }
    ui->lblChoose_zone->adjustSize();
    ui->lblChoose_zone->setGeometry(
                (ui->frame_zone->width() - ui->lblChoose_zone->width())/2,
                ui->lblChoose_zone->geometry().y(),
                ui->lblChoose_zone->width(),
                ui->lblChoose_zone->height());

    //ui->label->setText(lblNameTxt_EN);
    //ui->label_3->setText(lblLatitudeTxt_EN);
    //ui->label_4->setText(lblLongitudeTxt_EN);
    //ui->label_5->setText(lblAltitudeTxt_EN);

    //Manufacturing
    ui->label_2->setText(lblManSettingsTxt_EN);
    ui->label_2->adjustSize();
    ui->label_2->setGeometry(
                (ui->manufacturingBox->width() - ui->label_2->width())/2,
                ui->label_2->geometry().y(),
                ui->label_2->width(),
                ui->label_2->height());

    ui->label_7->setText(lblInsertTxt_EN);
    ui->label_7->adjustSize();
    ui->label_7->setGeometry(
                (ui->grBoxPass->width() - ui->label_7->width())/2,
                ui->label_7->geometry().y(),
                ui->label_7->width(),
                ui->label_7->height());

    ui->label_8->setText(lblWrongPassTxt_EN);
    ui->label_8->adjustSize();
    ui->label_8->setGeometry(
                (ui->wrong->width() - ui->label_8->width())/2,
                ui->label_8->geometry().y(),
                ui->label_8->width(),
                ui->label_8->height());

    ui->m_confirmPass->setText(btnConfirmTxt_EN);
    ui->brightness_lbl->setText(lblBrightnessTxt_EN);
    ui->contrast_lbl->setText(lblContrastTxt_EN);
    ui->manufacturing->setItemText(0, tabThermalCameraTxt_EN);
    ui->manufacturing->setItemText(1, tabBoresightTxt_EN);
    ui->manufacturing->setItemText(2, tabMediaTxt_EN);
    ui->btnSaveReticlePos->setText(btnSaveTxt_EN);
    ui->btnConfirmCamSettings->setText(btnConfirmTxt_EN);

    ui->lblInsertValueDecl->setText(lbl_na_EN);
}

void Menu::showKeyboard()
{
    ui->keyboard->setGeometry(815, 130, 250, 291);
}

void Menu::hideKeyboard()
{
    ui->keyboard->hide();
}

void Menu::moveLeft()
{
    ui->groupBox->setGeometry(115, 0, 591, 251);
}

void Menu::moveRight()
{
    ui->groupBox->setGeometry(250, 0, 591, 251);
}

void Menu::moveLeftM()
{
    ui->grBoxPass->setGeometry(150, 100, 471, 231);
}

void Menu::moveRightM()
{
    ui->grBoxPass->setGeometry(290, 100, 471, 231);
}

void Menu::showKeyboardM()
{
    ui->keyboard->setGeometry(760, 230, 250, 291);
}

void Menu::hideKeyboardM()
{
    ui->keyboard->hide();
}

void Menu::showWrongM()
{
    ui->wrong->setGeometry(345, 140, 361, 221);
}

void Menu::hideWrongM()
{
    ui->wrong->hide();
}

void Menu::showManufacturing()
{
    ui->manufacturingBox->show();
}

void Menu::hideManufacturing()
{
    ui->manufacturingBox->hide();
}

void Menu::restoreToolBox()
{
    moveRight();
    hideKeyboard();
}

void Menu::expandToolBox()
{
    ui->keyboard->show();
    moveLeft();
    showKeyboard();
}

void Menu::restoreToolBoxM()
{
    moveRightM();
    hideKeyboardM();
}

void Menu::expandToolBoxM()
{
    moveLeftM();
    ui->keyboard->show();
    showKeyboardM();
}

void Menu::showMenu()
{
    ui->hide->setGeometry(20,40,91,91);
    ui->manufacturing->hide();
    hideWrongM();
    ui->password_grbox->show();
    restoreToolBoxM();

    menu_visible = true;
}

void Menu::hideMenu()
{
    ui->hide->setGeometry(1170,40,91,91);
    ui->m_pass->clear();
    hideWrongM();
    restoreToolBoxM();

    menu_visible = false;
}

void Menu::checkMPass()
{
    restoreToolBoxM();

    m_password = saveuserdata->getMaintenancePasswordParameter();

    if(ui->m_pass->text() == m_password)
    {
        ui->m_pass->clear();
        ui->password_grbox->hide();
        ui->manufacturing->show();
        ui->keyboard->hide();
    }
    else
    {
        ui->m_pass->clear();
        ui->wrong->show();
        showWrongM();
    }
}

bool Menu::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->txtCurrPass && event->type() == QEvent::MouseButtonPress)
    {
        expandToolBox();
    }

    if(obj == ui->txtNewPass && event->type() == QEvent::MouseButtonPress)
    {
        expandToolBox();
    }

    if(obj == ui->txtConfPass && event->type() == QEvent::MouseButtonPress)
    {
        expandToolBox();
    }

    if(obj == ui->txtPassReset && event->type() == QEvent::MouseButtonPress)
    {
        ui->grBoxReset->setGeometry(120,50,551,271);
        ui->keyboard->setGeometry(800,375,250,291);
        ui->keyboard->show();
    }

    if(obj == ui->settings && event->type() == QEvent::MouseButtonPress)
    {
        restoreToolBox();
        ui->grBoxReset->setGeometry(270,50,551,271);
        ui->keyboard_qwerty->hide();

        if(ui->settings->currentIndex() == 0)
        {
            releaseAll();
            ui->txtCurrPass->setFocus();
            txt_m = "f";
        }
        else if(ui->settings->currentIndex() == 1)
        {
            releaseAll();
            ui->btnBG->setFocus();
        }
        else if(ui->settings->currentIndex() == 2)
        {
            releaseAll();
            ui->txtDegrees->setFocus();
            txt_m_md = "f";
        }
        else if(ui->settings->currentIndex() == 3)
        {
            releaseAll();
            ui->wgs->setFocus();
        }
        else if(ui->settings->currentIndex() == 4)
        {
            releaseAll();
            ui->point_name->setFocus();
        }
        else if(ui->settings->currentIndex() == 5)
        {
            releaseAll();
            ui->txtPassReset->setFocus();
            txt_m = "f";
        }
    }

    if(obj == ui->manufacturingBox && event->type() == QEvent::MouseButtonPress)
    {
        restoreToolBoxM();
    }

    if(obj == ui->m_pass && event->type() == QEvent::MouseButtonPress)
    {
        expandToolBoxM();

    }
    if(obj == ui->point_name && event->type() == QEvent::MouseButtonPress)
    {
        ui->keyboard_qwerty->show();
    }
    if(obj == ui->point_att && event->type() == QEvent::MouseButtonPress)
    {
        ui->keyboard_qwerty->show();
    }
    if(obj == ui->point_latt && event->type() == QEvent::MouseButtonPress)
    {
        ui->keyboard_qwerty->show();
    }
    if(obj == ui->point_long && event->type() == QEvent::MouseButtonPress)
    {
        ui->keyboard_qwerty->show();
    }
    return QObject::eventFilter(obj, event);
}


void Menu::on_btnConfirmPass_pressed()
{
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    btnConfirmPass_pressed();
}


void Menu::on_btnConfirmPass_released()
{
    btnConfirmPass_released();

    changeUserPassword();

    ui->txtCurrPass->clear();
    ui->txtNewPass->clear();
    ui->txtConfPass->clear();
    restoreToolBox();
}


void Menu::on_btnChooseLang_pressed()
{
    btnConfirmPass_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    btnChooseLang_pressed();

    if(flgBG_m == true)
    {
        switchToBG();
        flgBG_w = true;
    }
    else if(flgBG_m == false)
    {
        switchToEN();
        flgBG_w = false;
    }
}


void Menu::on_btnChooseLang_released()
{
    btnChooseLang_released();
}


void Menu::on_btnBack_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    btnReset_released();
    btnConfirmPassReset_released();

    btnBack_pressed();
    txt_m = "f";
    txt_m_md = "f";
}


void Menu::on_btnBack_released()
{
    btnBack_released();
    menu_visible = false;
    currentVideoPanel = NULL;
    this->close();
}


void Menu::on_btnBG_pressed()
{
    ui->btnBG->setIconSize(QSize(190, 190));
    ui->btnEN->setIconSize(QSize(240, 260));
    ui->btnChooseLang->setEnabled(true);

    flgBG_m = true;
}


void Menu::on_btnEN_pressed()
{
    ui->btnBG->setIconSize(QSize(240, 260));
    ui->btnEN->setIconSize(QSize(190, 190));
    ui->btnChooseLang->setEnabled(true);

    flgBG_m = false;
}


void Menu::on_brightness_sliderMoved(int position)
{
    QString pos = QString::number(position);
    ui->lblBrightness_value->setText(pos);
}


void Menu::on_contrast_sliderMoved(int position)
{
    QString pos = QString::number(position);
    ui->lblContrast_value->setText(pos);
}


void Menu::on_dde_sliderMoved(int position)
{
    QString pos = QString::number(position);
    ui->lblDDE_value->setText(pos);
}


void Menu::on_k1_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    k1_pressed();

    _txt = "1";
    keyboardInput();
}


void Menu::on_k1_released()
{
    k1_released();
}


void Menu::on_k2_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    k2_pressed();

    _txt = "2";
    keyboardInput();
}


void Menu::on_k2_released()
{
    k2_released();
}


void Menu::on_k3_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    k3_pressed();

    _txt = "3";
    keyboardInput();
}


void Menu::on_k3_released()
{
    k3_released();
}


void Menu::on_k4_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    k4_pressed();

    _txt = "4";
    keyboardInput();
}


void Menu::on_k4_released()
{
    k4_released();
}


void Menu::on_k5_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    k5_pressed();

    _txt = "5";
    keyboardInput();
}


void Menu::on_k5_released()
{
    k5_released();
}


void Menu::on_k6_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    k6_pressed();

    _txt = "6";
    keyboardInput();
}


void Menu::on_k6_released()
{
    k6_released();
}


void Menu::on_k7_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    k7_pressed();

    _txt = "7";
    keyboardInput();
}


void Menu::on_k7_released()
{
    k7_released();
}


void Menu::on_k8_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    k8_pressed();

    _txt = "8";
    keyboardInput();
}


void Menu::on_k8_released()
{
    k8_released();
}


void Menu::on_k9_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    k9_pressed();

    _txt = "9";
    keyboardInput();
}


void Menu::on_k9_released()
{
    k9_released();
}


void Menu::on_k0_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    k0_pressed();

    _txt = "0";
    keyboardInput();
}


void Menu::on_k0_released()
{
    k0_released();
}


void Menu::on_ok_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    ok_pressed();
}


void Menu::on_ok_released()
{
    ok_released();

    if(menu_visible == false)
    {
        restoreToolBox();
    }

    else if(menu_visible == true)
    {
        restoreToolBoxM();
    }
    ui->grBoxReset->setGeometry(270,50,551,271);
}


void Menu::on_del_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    del_pressed();

    deleteLast();
}

void Menu::on_del_released()
{
    del_released();
}

void Menu::keyboardInput()
{
    if(ui->txtCurrPass->hasFocus())
    {
        ui->txtCurrPass->setText(ui->txtCurrPass->text() + _txt);
    }

    else if(ui->txtNewPass->hasFocus())
    {
        ui->txtNewPass->setText(ui->txtNewPass->text() + _txt);
    }

    else if(ui->txtConfPass->hasFocus())
    {
        ui->txtConfPass->setText(ui->txtConfPass->text() + _txt);
    }

    else if(ui->m_pass->hasFocus())
    {
        ui->m_pass->setText(ui->m_pass->text() + _txt);
    }
    else if(ui->txtPassReset->hasFocus())
    {
        ui->txtPassReset->setText(ui->txtPassReset->text() + _txt);
    }
}

void Menu::deleteLast()
{
    if(ui->txtCurrPass->hasFocus())
    {
        ui->txtCurrPass->backspace();
    }

    else if(ui->txtNewPass->hasFocus())
    {
        ui->txtNewPass->backspace();
    }

    else if(ui->txtConfPass->hasFocus())
    {
        ui->txtConfPass->backspace();
    }

    else if(ui->m_pass->hasFocus())
    {
        ui->m_pass->backspace();
    }
    else if(ui->txtPassReset->hasFocus())
    {
        ui->txtPassReset->backspace();
    }
    else if(ui->txtDegrees->hasFocus())
    {
        ui->txtDegrees->backspace();
    }
    else if(ui->txtMinutes->hasFocus())
    {
        ui->txtMinutes->backspace();
    }
    else if(ui->txtSeconds->hasFocus())
    {
        ui->txtSeconds->backspace();
    }
}

void Menu::on_m_confirmPass_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    m_confirmPass_pressed();
}


void Menu::on_m_confirmPass_released()
{
    m_confirmPass_released();

    checkMPass();
}


void Menu::on_m_ok_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    m_ok_pressed();

    //ui->wrong->hide();
    hideWrongM();
    ui->m_pass->clear();
    restoreToolBoxM();
}


void Menu::on_hide_pressed()
{
    ui->keyboard_qwerty->hide();

    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    if(menu_visible == false)
    {
        showMenu();
        restoreToolBox();
        showManufacturing();
        ui->frame_keyboard_md->hide();
    }

    else if(menu_visible == true)
    {
        hideMenu();
        hideManufacturing();
        if(ui->settings->currentIndex() == 2)
        {
            ui->frame_keyboard_md->show();
        }
    }
}


void Menu::on_m_back_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    m_back_pressed();
}


void Menu::on_m_back_released()
{
    m_back_released();

    menu_visible = false;

    this->close();
}


void Menu::on_settings_currentChanged(int index)
{
    ui->grBoxReset->setGeometry(270,50,551,271);
    ui->keyboard->hide();
    ui->txtNewPass->clear();
    ui->txtConfPass->clear();
    ui->btnBG->setIconSize(QSize(240, 260));
    ui->btnEN->setIconSize(QSize(240, 260));
    ui->keyboard_qwerty->hide();
    ui->frame_keyboard_md->hide();
    ui->grBoxPassMessage->hide();
    checkCoordinateSystem();
    checkPointsCoordinateType();
    if(magnDecl!= 0)
    {
        ui->txtDegrees->setText(QString::number(degrees));
        ui->txtMinutes->setText(QString::number(minutes));
        ui->txtSeconds->setText(QString::number(seconds));
        if(magnDecl < 0)
        {
            ui->lblOperator->setText("-");
        }
        else if(magnDecl > 0)
        {
            ui->lblOperator->setText("+");
        }
    }
    if(index == 0)
    {
        ui->txtCurrPass->setFocus();
        releaseAll();
    }
    else if(index == 1)
    {
        ui->btnBG->setFocus();
        releaseAll();
    }
    else if(index == 2)
    {
        ui->frame_keyboard_md->setGeometry(150, 240, 321,351);
        ui->frame_keyboard_md->show();
        ui->txtDegrees->setFocus();
        releaseAll();
    }
    else if(index == 3)
    {
        ui->wgs->setFocus();
        releaseAll();
    }
    else if(index == 4)
    {
        ui->point_name->setFocus();
        releaseAll();
    }
    else if(index == 5)
    {
        ui->txtPassReset->setFocus();
        releaseAll();
    }

    txt_m = "f";
    txt_m_md = "f";
}

void Menu::releaseAll()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();
    btnReset_released();
    setWgsStyleSheet();
    setKrasovskyStyleSheet();
    setUtmStyleSheet();
    setDlhStyleSheet();
    setZone1StyleSheet();
    setZone2StyleSheet();
}


void Menu::on_btnChooseCoordSys_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();
    setWgsStyleSheet();
    setKrasovskyStyleSheet();
    setUtmStyleSheet();
    setDlhStyleSheet();
    setZone1StyleSheet();
    setZone2StyleSheet();

    btnChooseCoordSys_pressed();

    setCoordinateSystemParameters();

    if(inputCooType == CT_XY_CODE && outputCooType == CT_UTM_CODE)
    {
        ui->krasovsky->setChecked(true);
        on_krasovsky_pressed();
    }
    else
    {
        if(inputCooType == CT_BL_CODE)
        {
            X_parameter = gtor(X_parameter, CF_CODE_DD);
            Y_parameter = gtor(Y_parameter, CF_CODE_DD);
        }
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
}


void Menu::on_btnChooseCoordSys_released()
{
    btnChooseCoordSys_released();
}


void Menu::on_up_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    up_pressed();

    if(isOffsetReticleVisible == true)
    {
        DisplaceCrosshairSOP(0, 1);
    }
    else
    {
        DisplaceCrosshair(0, 0.001);
    }

    //ui->reticle->move(ui->reticle->pos().x(), ui->reticle->pos().y()-10);

}


void Menu::on_up_released()
{
    up_released();
}


void Menu::on_down_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    down_pressed();

    if(isOffsetReticleVisible == true)
    {
        DisplaceCrosshairSOP(0, -1);
    }
    else
    {
        DisplaceCrosshair(0, -0.001);
    }

    //ui->reticle->move(ui->reticle->pos().x(), ui->reticle->pos().y()+10);
}


void Menu::on_down_released()
{
    down_released();
}


void Menu::on_left_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    left_pressed();

    if(isOffsetReticleVisible == true)
    {
        DisplaceCrosshairSOP(-1, 0);
    }
    else
    {
        DisplaceCrosshair(-0.001, 0);
    }
    //ui->reticle->move(ui->reticle->pos().x()-10, ui->reticle->pos().y());
}


void Menu::on_left_released()
{
    left_released();
}


void Menu::on_right_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    right_pressed();

    if(isOffsetReticleVisible == true)
    {
        DisplaceCrosshairSOP(1, 0);
    }
    else
    {
        DisplaceCrosshair(0.001, 0);
    }

    //ui->reticle->move(ui->reticle->pos().x()+10, ui->reticle->pos().y());
}


void Menu::on_right_released()
{
    right_released();
}

void Menu::keyboardInput_m()
{
    foreach(QLineEdit* le, findChildren<QLineEdit*>())
        if(le->hasFocus())
        {
            le->setText(le->text() + txt_input_m);
        }
}

void Menu::on_k1_magneticDeclination_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    k1_magneticDeclination_pressed();
    txt_input_m = "1";
    keyboardInput_m();
}


void Menu::on_k1_magneticDeclination_released()
{
    k1_magneticDeclination_released();
}


void Menu::on_k2_magneticDeclination_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    k2_magneticDeclination_pressed();
    txt_input_m = "2";
    keyboardInput_m();
}


void Menu::on_k2_magneticDeclination_released()
{
    k2_magneticDeclination_released();
}


void Menu::on_k3_magneticDeclination_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    k3_magneticDeclination_pressed();
    txt_input_m = "3";
    keyboardInput_m();
}


void Menu::on_k3_magneticDeclination_released()
{
    k3_magneticDeclination_released();
}


void Menu::on_k4_magneticDeclination_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    k4_magneticDeclination_pressed();
    txt_input_m = "4";
    keyboardInput_m();
}


void Menu::on_k4_magneticDeclination_released()
{
    k4_magneticDeclination_released();
}


void Menu::on_k5_magneticDeclination_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    k5_magneticDeclination_pressed();
    txt_input_m = "5";
    keyboardInput_m();
}


void Menu::on_k5_magneticDeclination_released()
{
    k5_magneticDeclination_released();
}


void Menu::on_k6_magneticDeclination_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    k6_magneticDeclination_pressed();
    txt_input_m = "6";
    keyboardInput_m();
}


void Menu::on_k6_magneticDeclination_released()
{
    k6_magneticDeclination_released();
}


void Menu::on_k7_magneticDeclination_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    k7_magneticDeclination_pressed();
    txt_input_m = "7";
    keyboardInput_m();
}


void Menu::on_k7_magneticDeclination_released()
{
    k7_magneticDeclination_released();
}


void Menu::on_k8_magneticDeclination_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    k8_magneticDeclination_pressed();
    txt_input_m = "8";
    keyboardInput_m();
}


void Menu::on_k8_magneticDeclination_released()
{
    k8_magneticDeclination_released();
}


void Menu::on_k9_magneticDeclination_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    k9_magneticDeclination_pressed();
    txt_input_m = "9";
    keyboardInput_m();
}


void Menu::on_k9_magneticDeclination_released()
{
    k9_magneticDeclination_released();
}


void Menu::on_k0_magneticDeclination_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    k0_magneticDeclination_pressed();
    txt_input_m = "0";
    keyboardInput_m();
}


void Menu::on_k0_magneticDeclination_released()
{
    k0_magneticDeclination_released();
}


void Menu::on_k_minus_magneticDeclination_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    k_minus_magneticDeclination_pressed();
    //txt_input_m = "-";
   //keyboardInput_m();
    ui->lblOperator->setText("-");
}


void Menu::on_k_minus_magneticDeclination_released()
{
    k_minus_magneticDeclination_released();
}


void Menu::on_k_plus_magneticDeclination_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    k_plus_magneticDeclination_pressed();
    //txt_input_m = "+";
    //keyboardInput_m();
    ui->lblOperator->setText("+");
}


void Menu::on_k_plus_magneticDeclination_released()
{
    k_plus_magneticDeclination_released();
}


void Menu::on_k_dot_magneticDeclination_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    k_dot_magneticDeclination_pressed();
    txt_input_m = ".";
    keyboardInput_m();
}


void Menu::on_k_dot_magneticDeclination_released()
{
    k_dot_magneticDeclination_released();
}


void Menu::on_k_del_magneticDeclination_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    k_del_magneticDeclination_pressed();
    deleteLast();
}


void Menu::on_k_del_magneticDeclination_released()
{
    k_del_magneticDeclination_released();
}


void Menu::on_btnConfirmDecl_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    btnConfirmDecl_pressed();
}


void Menu::on_btnConfirmDecl_released()
{
    btnConfirmDecl_released();

    degrees = ui->txtDegrees->text().toFloat();
    minutes = ui->txtMinutes->text().toFloat();
    seconds = ui->txtSeconds->text().toFloat();

    if(ui->txtDegrees->text() != NULL && ui->txtMinutes->text() == NULL && ui->txtSeconds->text() == NULL)
    {
        currValue = degrees;
    }
    else if(ui->txtDegrees->text() != NULL && ui->txtMinutes->text() != NULL && ui->txtSeconds->text() == NULL)
    {
        currValue = degrees + (minutes*constMinutes);
    }
    else if(ui->txtDegrees->text() != NULL && ui->txtMinutes->text() != NULL && ui->txtSeconds->text() != NULL)
    {
        currValue = degrees + (minutes*constMinutes) + (seconds*constSeconds);
    }
    else if(ui->txtDegrees->text() == NULL && ui->txtMinutes->text() != NULL && ui->txtSeconds->text() != NULL)
    {
        currValue = (minutes*constMinutes) + (seconds*constSeconds);
    }
    else if(ui->txtDegrees->text() == NULL && ui->txtMinutes->text() == NULL && ui->txtSeconds->text() != NULL)
    {
        currValue = seconds*constSeconds;
    }
    else if(ui->txtDegrees->text() != NULL && ui->txtMinutes->text() == NULL && ui->txtSeconds->text() != NULL)
    {
        currValue = degrees + (seconds*constSeconds);
    }

    if(ui->lblOperator->text() == "+")
    {
        currValue = currValue;
    }
    else if(ui->lblOperator->text() == "-")
    {
        currValue = - currValue;
    }

    if(currValue < minValue || currValue > maxValue || currValue == plusOperand.toFloat() || currValue == minusOperand.toFloat())
    {
        ui->invalid->show();
        btnConfirmDecl_released();
        ui->btnOkDecl->setFocus();
        btnOkDecl_selected();
    }
    else
    {
        magnDecl = currValue;

        if(currValue != 0.000)
        {
            magneticDeclination = currValue*10000;
            updateMagneticDeclination = true;
        }
    }
}


void Menu::on_btnConfirmPassReset_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();

    btnConfirmPassReset_pressed();
}

void Menu::on_btnConfirmPassReset_released()
{
    btnConfirmPassReset_released();

    password_reset = saveuserdata->getUserPasswordParameter();
    if(ui->txtPassReset->text() == password_reset)
    {
        ui->grBoxReset->setGeometry(270,50,551,271);
        ui->grBoxReset->hide();
        ui->keyboard->hide();
        ui->btnReset->show();
        ui->txtPassReset->clear();
        ui->btnReset->setFocus();
    }
    else
    {
        ui->grBoxReset->setGeometry(270,50,551,271);
        ui->keyboard->hide();
        ui->wrong_reset->show();
        ui->ok_reset->setFocus();
        ui->txtPassReset->clear();
    }
}

void Menu::on_btnReset_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    ok_reset_released();
    btnConfirmPassReset_released();

    ui->btnReset->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: black;"
                );
}

void Menu::on_btnReset_released()
{
    ui->btnReset->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );

    if(saveuserdata->isJsonExist() == true)
    {
        saveuserdata->removeJson();
    }
}

void Menu::on_ok_reset_pressed()
{
    btnConfirmPass_released();
    btnChooseLang_released();
    btnBack_released();
    m_confirmPass_released();
    m_ok_released();
    m_back_released();
    btnChooseCoordSys_released();
    up_released();
    down_released();
    left_released();
    right_released();
    btnConfirmDecl_released();
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    ok_released();
    del_released();
    k1_magneticDeclination_released();
    k2_magneticDeclination_released();
    k3_magneticDeclination_released();
    k4_magneticDeclination_released();
    k5_magneticDeclination_released();
    k6_magneticDeclination_released();
    k7_magneticDeclination_released();
    k8_magneticDeclination_released();
    k9_magneticDeclination_released();
    k0_magneticDeclination_released();
    k_minus_magneticDeclination_released();
    k_plus_magneticDeclination_released();
    k_dot_magneticDeclination_released();
    k_del_magneticDeclination_released();
    btnConfirmPassReset_released();

    ok_reset_pressed();

    ui->wrong_reset->hide();
    ui->txtPassReset->clear();
}

void Menu::on_ok_reset_released()
{
    ok_reset_released();
}

void Menu::on_wgs_pressed()
{
    setKrasovskyStyleSheet();
    setUtmStyleSheet();
    setDlhStyleSheet();
    setZone1StyleSheet();
    setZone2StyleSheet();
    btnChooseCoordSys_released();

    if(flgBG_m == true)
    {
        ui->lblChoose_zone->setText(lblChooseZone_m_BG);
    }
    else if(flgBG_m == false)
    {
        ui->lblChoose_zone->setText(lblChooseZone_m_EN);
    }

    ui->utm_xy->setText("UTM");
    ui->zone_35->setText("35");
    ui->zone_34->setText("34");

    ui->utm_xy->setChecked(true);
    ui->frame_zone->show();
    ui->zone_35->setChecked(true);

    isWGS = true;
}


void Menu::on_krasovsky_pressed()
{
    setWgsStyleSheet();
    setUtmStyleSheet();
    setDlhStyleSheet();
    setZone1StyleSheet();
    setZone2StyleSheet();
    btnChooseCoordSys_released();

    if(flgBG_m == true)
    {
        ui->lblChoose_zone->setText(lblChoosePrimeMer_m_BG);
    }
    else if(flgBG_m == false)
    {
        ui->lblChoose_zone->setText(lblChoosePrimeMer_m_EN);
    }
    ui->lblChoose_zone->adjustSize();
    ui->lblChoose_zone->setGeometry(
                (ui->frame_zone->width() - ui->lblChoose_zone->width())/2,
                ui->lblChoose_zone->geometry().y(),
                ui->lblChoose_zone->width(),
                ui->lblChoose_zone->height());

    ui->utm_xy->setText("X,Y");
    ui->zone_35->setText("27");
    ui->zone_34->setText("21");

    ui->utm_xy->setChecked(true);
    ui->frame_zone->show();
    ui->zone_35->setChecked(true);

    isWGS = false;
}

void Menu::on_btnConfirmCamSettings_pressed()
{
    ui->btnConfirmCamSettings->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: black;"
                );

    int brightness_value = ui->brightness->value();
    saveuserdata->setBrightnessValueParameter(brightness_value);

    int contrast_value = ui->contrast->value();
    saveuserdata->setContrastValueParameter(contrast_value);

    bool ddeMode;
    if(ui->dde_mode->isChecked() == true)
    {
        ddeMode = true;
    }
    else if(ui->dde_mode->isChecked() == false)
    {
        ddeMode = false;
    }
    saveuserdata->setDeeModeParameter(ddeMode);

    if(ui->dde->isEnabled())
    {
        int dde_value = ui->dde->value();
        saveuserdata->setDeeValueParameter(dde_value);
    }
}


void Menu::on_btnConfirmCamSettings_released()
{
    ui->btnConfirmCamSettings->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}


void Menu::on_dde_mode_stateChanged(int mode)
{
    if(mode == Qt::Checked)
    {
        ui->dde->setEnabled(true);
    }
    else if(mode == Qt::Unchecked)
    {
        ui->dde->setEnabled(false);
    }
}

void Menu::gpioBtnOk()
{
    if(ui->settings->currentIndex() == 6)
    {
        ui->settings->setCurrentIndex(0);
        ui->txtCurrPass->setFocus();
        moveLeft();
        showKeyboard();
        ui->keyboard->show();
    }
    else if(ui->btnOk->hasFocus())
    {
        on_btnOk_pressed();
    }
    else if(ui->btnConfirmDecl->hasFocus())
    {
        on_btnConfirmDecl_released();
    }
    else if(ui->btnOkDecl->hasFocus())
    {
        on_btnOkDecl_released();
    }
    else if(ui->wgs->hasFocus())
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
    else if(ui->settings->currentIndex() == 0)
    {
        foreach(QLineEdit* ledit, findChildren<QLineEdit*>())
            if(ledit->hasFocus())
            {
                if(txt_m == "f")
                {
                    moveLeft();
                    showKeyboard();
                    ui->keyboard->show();
                    k1_selected();
                    txt_m = "1";
                }
                else if(txt_m == "1")
                {
                    ledit->setText(ledit->text() + "1");
                }
                else if(txt_m == "2")
                {
                    ledit->setText(ledit->text() + "2");
                }
                else if(txt_m == "3")
                {
                    ledit->setText(ledit->text() + "3");
                }
                else if(txt_m == "4")
                {
                    ledit->setText(ledit->text() + "4");
                }
                else if(txt_m == "5")
                {
                    ledit->setText(ledit->text() + "5");
                }
                else if(txt_m == "6")
                {
                    ledit->setText(ledit->text() + "6");
                }
                else if(txt_m == "7")
                {
                    ledit->setText(ledit->text() + "7");
                }
                else if(txt_m == "8")
                {
                    ledit->setText(ledit->text() + "8");
                }
                else if(txt_m == "9")
                {
                    ledit->setText(ledit->text() + "9");
                }
                else if(txt_m == "0")
                {
                    ledit->setText(ledit->text() + "0");
                }
                else if(txt_m == "del")
                {
                    ledit->backspace();
                }
                else if(txt_m == "ok")
                {
                    on_ok_released();
                    moveRight();
                    hideKeyboard();
                    txt_m = "f";
                }
            }
        if(ui->btnConfirmPass->hasFocus())
        {
            on_btnConfirmPass_pressed();
            on_btnConfirmPass_released();
        }
    }
    else if(ui->txtPassReset->hasFocus())
    {
        if(txt_m == "1")
        {
            ui->txtPassReset->setText(ui->txtPassReset->text() + "1");
        }
        else if(txt_m == "2")
        {
            ui->txtPassReset->setText(ui->txtPassReset->text() + "2");
        }
        else if(txt_m == "3")
        {
            ui->txtPassReset->setText(ui->txtPassReset->text() + "3");
        }
        else if(txt_m == "4")
        {
            ui->txtPassReset->setText(ui->txtPassReset->text() + "4");
        }
        else if(txt_m == "5")
        {
            ui->txtPassReset->setText(ui->txtPassReset->text() + "5");
        }
        else if(txt_m == "6")
        {
            ui->txtPassReset->setText(ui->txtPassReset->text() + "6");
        }
        else if(txt_m == "7")
        {
            ui->txtPassReset->setText(ui->txtPassReset->text() + "7");
        }
        else if(txt_m == "8")
        {
            ui->txtPassReset->setText(ui->txtPassReset->text() + "8");
        }
        else if(txt_m == "9")
        {
            ui->txtPassReset->setText(ui->txtPassReset->text() + "9");
        }
        else if(txt_m == "0")
        {
            ui->txtPassReset->setText(ui->txtPassReset->text() + "0");
        }
        else if(txt_m == "del")
        {
            ui->txtPassReset->backspace();
        }
        else if(txt_m == "ok")
        {
            on_ok_released();
            ui->grBoxReset->setGeometry(270,50,551,271);
            hideKeyboard();
            txt_m = "f";
        }
        else if(txt_m == "f")
        {
            ui->grBoxReset->setGeometry(120,50,551,271);
            ui->keyboard->setGeometry(800,350,250,291);
            ui->keyboard->show();
            k1_selected();
            txt_m = "1";
        }
    }
    else if(ui->btnConfirmPassReset->hasFocus())
    {
        on_btnConfirmPassReset_released();

        if(ui->btnReset->hasFocus())
        {
            btnReset_pressed();
        }
    }
    else if(ui->ok_reset->hasFocus())
    {
        ui->wrong_reset->hide();
        ui->txtPassReset->setFocus();
    }
    else if(ui->btnChooseLang->hasFocus())
    {
        on_btnChooseLang_pressed();
    }
    else if(ui->btnBack->hasFocus())
    {
        on_btnBack_released();
    }
    else if(ui->settings->currentIndex() == 2)
    {
        foreach(QLineEdit* ledit, findChildren<QLineEdit*>())
            if(ledit->hasFocus())
            {
                if(txt_m_md == "f")
                {
                    k1_magneticDeclination_selected();
                    txt_m_md = "1";
                }
                else if(txt_m_md == "1")
                {
                    ledit->setText(ledit->text() + "1");
                }
                else if(txt_m_md == "2")
                {
                    ledit->setText(ledit->text() + "2");
                }
                else if(txt_m_md == "3")
                {
                    ledit->setText(ledit->text() + "3");
                }
                else if(txt_m_md == "4")
                {
                    ledit->setText(ledit->text() + "4");
                }
                else if(txt_m_md == "5")
                {
                    ledit->setText(ledit->text() + "5");
                }
                else if(txt_m_md == "6")
                {
                    ledit->setText(ledit->text() + "6");
                }
                else if(txt_m_md == "7")
                {
                    ledit->setText(ledit->text() + "7");
                }
                else if(txt_m_md == "8")
                {
                    ledit->setText(ledit->text() + "8");
                }
                else if(txt_m_md == "9")
                {
                    ledit->setText(ledit->text() + "9");
                }
                else if(txt_m_md == "0")
                {
                    ledit->setText(ledit->text() + "0");
                }
                else if(txt_m_md == "plus")
                {
                    ledit->setText(ledit->text() + "+");
                }
                else if(txt_m_md == "minus")
                {
                    ledit->setText(ledit->text() + "-");
                }
                else if(txt_m_md == "del")
                {
                    ledit->backspace();
                }
                else if(txt_m_md == "dot")
                {
                    ledit->setText(ledit->text() + ".");
                }
            }
    }
}

void Menu::gpioBtnLeft()
{
    if(ui->btnEN->hasFocus())
    {
        ui->btnBG->setFocus();
        on_btnBG_pressed();
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
        setDlhStyleSheet();

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
    else if(ui->point_att->hasFocus())
    {
        ui->point_long->setFocus();
    }
    else if(ui->point_long->hasFocus())
    {
        ui->point_latt->setFocus();
    }
    else if(ui->point_latt->hasFocus())
    {
        ui->point_name->setFocus();
    }
    else if(ui->settings->currentIndex() == 2)
    {
        if(txt_m_md == "f")
        {
            if(ui->txtSeconds->hasFocus())
            {
                ui->txtMinutes->setFocus();
            }
            else if(ui->txtMinutes->hasFocus())
            {
                ui->txtDegrees->setFocus();
            }
        }
        else if(txt_m_md == "del")
        {
            k_del_magneticDeclination_released();
            k_dot_magneticDeclination_selected();
            txt_m_md = "dot";
        }
        else if(txt_m_md == "dot")
        {
            k_dot_magneticDeclination_released();
            k_plus_magneticDeclination_selected();
            txt_m_md = "plus";
        }
        else if(txt_m_md == "plus")
        {
            k_plus_magneticDeclination_released();
            k0_magneticDeclination_selected();
            txt_m_md = "0";
        }
        else if(txt_m_md == "0")
        {
            k0_magneticDeclination_released();
            k_minus_magneticDeclination_selected();
            txt_m_md = "minus";
        }
        else if(txt_m_md == "minus")
        {
            k_minus_magneticDeclination_released();
            k9_magneticDeclination_selected();
            txt_m_md = "9";
        }
        else if(txt_m_md == "9")
        {
            k9_magneticDeclination_released();
            k8_magneticDeclination_selected();
            txt_m_md = "8";
        }
        else if(txt_m_md == "8")
        {
            k8_magneticDeclination_released();
            k7_magneticDeclination_selected();
            txt_m_md = "7";
        }
        else if(txt_m_md == "7")
        {
            k7_magneticDeclination_released();
            k6_magneticDeclination_selected();
            txt_m_md = "6";
        }
        else if(txt_m_md == "6")
        {
            k6_magneticDeclination_released();
            k5_magneticDeclination_selected();
            txt_m_md = "5";
        }
        else if(txt_m_md == "5")
        {
            k5_magneticDeclination_released();
            k4_magneticDeclination_selected();
            txt_m_md = "4";
        }
        else if(txt_m_md == "4")
        {
            k4_magneticDeclination_released();
            k3_magneticDeclination_selected();
            txt_m_md = "3";
        }
        else if(txt_m_md == "3")
        {
            k3_magneticDeclination_released();
            k2_magneticDeclination_selected();
            txt_m_md = "2";
        }
        else if(txt_m_md == "2")
        {
            k2_magneticDeclination_released();
            k1_magneticDeclination_selected();
            txt_m_md = "1";
        }
    }
    else if(txt_m == "del")
    {
        del_released();
        k0_selected();
        txt_m = "0";
    }
    else if(txt_m == "0")
    {
        k0_released();
        ok_selected();
        txt_m = "ok";
    }
    else if(txt_m == "ok")
    {
        ok_released();
        k9_selected();
        txt_m = "9";
    }
    else if(txt_m == "9")
    {
        k9_released();
        k8_selected();
        txt_m = "8";
    }
    else if(txt_m == "8")
    {
        k8_released();
        k7_selected();
        txt_m = "7";
    }
    else if(txt_m == "7")
    {
        k7_released();
        k6_selected();
        txt_m = "6";
    }
    else if(txt_m == "6")
    {
        k6_released();
        k5_selected();
        txt_m = "5";
    }
    else if(txt_m == "5")
    {
        k5_released();
        k4_selected();
        txt_m = "4";
    }
    else if(txt_m == "4")
    {
        k4_released();
        k3_selected();
        txt_m = "3";
    }
    else if(txt_m == "3")
    {
        k3_released();
        k2_selected();
        txt_m = "2";
    }
    else if(txt_m == "2")
    {
        k2_released();
        k1_selected();
        txt_m = "1";
    }
    //else if(txt_m == "1")
    //{
    //    k1_released();
    //    txt_m = "f";
    //}

}

void Menu::gpioBtnRight()
{
    if(ui->btnBG->hasFocus())
    {
        ui->btnEN->setFocus();
        on_btnEN_pressed();
    }
    else if(ui->wgs->hasFocus())
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
        if(ui->frame_zone->isVisible())
        {
            setDlhStyleSheet();
            ui->zone_35->setFocus();
            ui->zone_35->setStyleSheet("background:gray;");
        }
    }
    else if(ui->zone_35->hasFocus())
    {
        setZone1StyleSheet();
        ui->zone_34->setFocus();
        ui->zone_34->setStyleSheet("background:gray;");
    }
    else if(ui->point_name->hasFocus())
    {
        ui->point_latt->setFocus();
    }
    else if(ui->point_latt->hasFocus())
    {
        ui->point_long->setFocus();
    }
    else if(ui->point_long->hasFocus())
    {
        ui->point_att->setFocus();
    }
    else if(ui->settings->currentIndex() == 2)
    {
        if(txt_m_md == "1")
        {
            k1_magneticDeclination_released();
            k2_magneticDeclination_selected();
            txt_m_md = "2";
        }
        else if(txt_m_md == "2")
        {
            k2_magneticDeclination_released();
            k3_magneticDeclination_selected();
            txt_m_md = "3";
        }
        else if(txt_m_md == "3")
        {
            k3_magneticDeclination_released();
            k4_magneticDeclination_selected();
            txt_m_md = "4";
        }
        else if(txt_m_md == "4")
        {
            k4_magneticDeclination_released();
            k5_magneticDeclination_selected();
            txt_m_md = "5";
        }
        else if(txt_m_md == "5")
        {
            k5_magneticDeclination_released();
            k6_magneticDeclination_selected();
            txt_m_md = "6";
        }
        else if(txt_m_md == "6")
        {
            k6_magneticDeclination_released();
            k7_magneticDeclination_selected();
            txt_m_md = "7";
        }
        else if(txt_m_md == "7")
        {
            k7_magneticDeclination_released();
            k8_magneticDeclination_selected();
            txt_m_md = "8";
        }
        else if(txt_m_md == "8")
        {
            k8_magneticDeclination_released();
            k9_magneticDeclination_selected();
            txt_m_md = "9";
        }
        else if(txt_m_md == "9")
        {
            k9_magneticDeclination_released();
            k_minus_magneticDeclination_selected();
            txt_m_md = "minus";
        }
        else if(txt_m_md == "minus")
        {
            k_minus_magneticDeclination_released();
            k0_magneticDeclination_selected();
            txt_m_md = "0";
        }
        else if(txt_m_md == "0")
        {
            k0_magneticDeclination_released();
            k_plus_magneticDeclination_selected();
            txt_m_md = "plus";
        }
        else if(txt_m_md == "plus")
        {
            k_plus_magneticDeclination_released();
            k_dot_magneticDeclination_selected();
            txt_m_md = "dot";
        }
        else if(txt_m_md == "dot")
        {
            k_dot_magneticDeclination_released();
            k_del_magneticDeclination_selected();
            txt_m_md = "del";
        }
        else if(txt_m_md == "del")
        {
            k_del_magneticDeclination_released();
            ui->txtDegrees->setFocus();
            txt_m_md = "f";
        }
        else if(txt_m_md == "f")
        {
            if(ui->txtDegrees->hasFocus())
            {
                ui->txtMinutes->setFocus();
            }
            else if(ui->txtMinutes->hasFocus())
            {
                ui->txtSeconds->setFocus();
            }
        }
    }
    else if(txt_m == "1")
    {
        k1_released();
        k2_selected();
        txt_m = "2";
    }
    else if(txt_m == "2")
    {
        k2_released();
        k3_selected();
        txt_m = "3";
    }
    else if(txt_m == "3")
    {
        k3_released();
        k4_selected();
        txt_m = "4";
    }
    else if(txt_m == "4")
    {
        k4_released();
        k5_selected();
        txt_m = "5";
    }
    else if(txt_m == "5")
    {
        k5_released();
        k6_selected();
        txt_m = "6";
    }
    else if(txt_m == "6")
    {
        k6_released();
        k7_selected();
        txt_m = "7";
    }
    else if(txt_m == "7")
    {
        k7_released();
        k8_selected();
        txt_m = "8";
    }
    else if(txt_m == "8")
    {
        k8_released();
        k9_selected();
        txt_m = "9";
    }
    else if(txt_m == "9")
    {
        k9_released();
        ok_selected();
        txt_m = "ok";
    }
    else if(txt_m == "ok")
    {
        ok_released();
        k0_selected();
        txt_m = "0";
    }
    else if(txt_m == "0")
    {
        k0_released();
        del_selected();
        txt_m = "del";
    }
}

void Menu::gpioBtnUp()
{
    //if(ui->settings->currentIndex() == 7)
    //{
    //    ui->settings->setCurrentIndex(6);
    //    ui->btnConfirmPassReset->setFocus();
    //    btnConfirmPassReset_pressed();
    //}

    if(ui->btnBack->hasFocus())
    {
        btnBack_released();
        ui->settings->setCurrentIndex(5);
        ui->btnConfirmPassReset->setFocus();
        btnConfirmPassReset_selected();
    }
    else if(ui->btnConfirmPassReset->hasFocus())
    {
        btnConfirmPassReset_released();
        ui->txtPassReset->setFocus();
    }
    else if(ui->txtPassReset->hasFocus())
    {
        ui->settings->setCurrentIndex(4);
        ui->delete_btn->setFocus();
        btnDelete_selected();
    }
    else if(ui->delete_btn->hasFocus())
    {
        btnDelete_released();
        ui->add_btn->setFocus();
        btnAdd_selected();
    }
    else if(ui->add_btn->hasFocus())
    {
        btnAdd_released();
        ui->point_name->setFocus();
    }
    else if(ui->btnReset->hasFocus())
    {
        btnReset_released();
        ui->btnReset->hide();
        ui->grBoxReset->show();
        ui->settings->setCurrentIndex(4);
        ui->delete_btn->setFocus();
        btnDelete_selected();
    }
    else if(ui->point_name->hasFocus() || ui->point_latt->hasFocus() || ui->point_long->hasFocus() || ui->point_att->hasFocus())
    {
        ui->settings->setCurrentIndex(3);
        ui->btnChooseCoordSys->setFocus();
        btnChooseCoordSys_selected();
    }
    else if(ui->btnChooseCoordSys->hasFocus())
    {
        btnChooseCoordSys_released();
        ui->wgs->setFocus();
        ui->wgs->setStyleSheet("background:gray;");
    }
    else if(ui->wgs->hasFocus() || ui->krasovsky->hasFocus() || ui->utm_xy->hasFocus() || ui->bl->hasFocus() || ui->zone_35->hasFocus() || ui->zone_34->hasFocus())
    {
        setWgsStyleSheet();
        setKrasovskyStyleSheet();
        setUtmStyleSheet();
        setDlhStyleSheet();
        setZone1StyleSheet();
        setZone2StyleSheet();

        ui->settings->setCurrentIndex(2);
        ui->btnConfirmDecl->setFocus();
        btnConfirmDecl_selected();
    }
    //else if(ui->txtDegrees->hasFocus() || ui->txtMinutes->hasFocus() || ui->txtSeconds->hasFocus())
    //{
    //    ui->settings->setCurrentIndex(1);
    //    ui->btnChooseLang->setFocus();
    //    btnChooseLang_selected();
    //}
    else if(ui->btnChooseLang->hasFocus())
    {
        btnChooseLang_released();
        ui->btnBG->setFocus();
        on_btnBG_pressed();
    }
    else if(ui->btnBG->hasFocus() || ui->btnEN->hasFocus())
    {
        ui->settings->setCurrentIndex(0);
        ui->btnConfirmPass->setFocus();
        btnConfirmPass_selected();
    }
    else if(ui->settings->currentIndex() == 2)
    {
        if(txt_m_md == "f")
        {
            if(ui->btnConfirmDecl->hasFocus())
            {
                btnConfirmDecl_released();
                ui->txtDegrees->setFocus();
            }
            else if(ui->txtDegrees->hasFocus() || ui->txtMinutes->hasFocus() || ui->txtSeconds->hasFocus())
            {
                ui->settings->setCurrentIndex(1);
                ui->btnChooseLang->setFocus();
                btnChooseLang_selected();
            }
        }
        else if(txt_m_md == "del")
        {
            k_del_magneticDeclination_released();
            k_plus_magneticDeclination_selected();
            txt_m_md = "plus";
        }
        else if(txt_m_md == "plus")
        {
            k_plus_magneticDeclination_released();
            k9_magneticDeclination_selected();
            txt_m_md = "9";
        }
        else if(txt_m_md == "9")
        {
            k9_magneticDeclination_released();
            k6_magneticDeclination_selected();
            txt_m_md = "6";
        }
        else if(txt_m_md == "6")
        {
            k6_magneticDeclination_released();
            k3_magneticDeclination_selected();
            txt_m_md = "3";
        }
        else if(txt_m_md == "dot")
        {
            k_dot_magneticDeclination_released();
            k_minus_magneticDeclination_selected();
            txt_m_md = "minus";
        }
        else if(txt_m_md == "minus")
        {
            k_minus_magneticDeclination_released();
            k7_magneticDeclination_selected();
            txt_m_md = "7";
        }
        else if(txt_m_md == "7")
        {
            k7_magneticDeclination_released();
            k4_magneticDeclination_selected();
            txt_m_md = "4";
        }
        else if(txt_m_md == "4")
        {
            k4_magneticDeclination_released();
            k1_magneticDeclination_selected();
            txt_m_md = "1";
        }
        else if(txt_m_md == "0")
        {
            k0_magneticDeclination_released();
            k8_magneticDeclination_selected();
            txt_m_md = "8";
        }
        else if(txt_m_md == "8")
        {
            k8_magneticDeclination_released();
            k5_magneticDeclination_selected();
            txt_m_md = "5";
        }
        else if(txt_m_md == "5")
        {
            k5_magneticDeclination_released();
            k2_magneticDeclination_selected();
            txt_m_md = "2";
        }
    }

    else if(txt_m == "f")
    {
        if(ui->btnConfirmPass->hasFocus())
        {
            btnConfirmPass_released();
            ui->txtConfPass->setFocus();
            moveLeft();
            showKeyboard();
            ui->keyboard->show();
        }
        else if(ui->txtConfPass->hasFocus())
        {
            ui->txtNewPass->setFocus();
            moveLeft();
            showKeyboard();
            ui->keyboard->show();
        }
        else if(ui->txtNewPass->hasFocus())
        {
            ui->txtCurrPass->setFocus();
            moveLeft();
            showKeyboard();
            ui->keyboard->show();
        }
        else if(ui->txtPassReset->hasFocus())
        {
            ui->grBoxReset->setGeometry(270,50,551,271);
            hideKeyboard();
            btnConfirmPassReset_released();
            ui->settings->setCurrentIndex(5);
            ui->point_name->setFocus();
        }
    }
    else if(txt_m == "del")
    {
        del_released();
        k9_selected();
        txt_m = "9";
    }
    else if(txt_m == "9")
    {
        k9_released();
        k6_selected();
        txt_m = "6";
    }
    else if(txt_m == "6")
    {
        k6_released();
        k3_selected();
        txt_m = "3";
    }
    else if(txt_m == "0")
    {
        k0_released();
        k8_selected();
        txt_m = "8";
    }
    else if(txt_m == "8")
    {
        k8_released();
        k5_selected();
        txt_m = "5";
    }
    else if(txt_m == "5")
    {
        k5_released();
        k2_selected();
        txt_m = "2";
    }
    else if(txt_m == "ok")
    {
        ok_released();
        k7_selected();
        txt_m = "7";
    }
    else if(txt_m == "7")
    {
        k7_released();
        k4_selected();
        txt_m = "4";
    }
    else if(txt_m == "4")
    {
        k4_released();
        k1_selected();
        txt_m = "1";
    }
}

void Menu::gpioBtnDown()
{
    //if(ui->settings->currentIndex() == 6)
    //{
    //    ui->btnBack->setFocus();
    //    btnBack_pressed();
    //}
    if(ui->btnConfirmPass->hasFocus())
    {
        btnConfirmPass_released();
        ui->settings->setCurrentIndex(1);
        ui->btnBG->setFocus();
        on_btnBG_pressed();
    }
    else if(ui->btnConfirmPassReset->hasFocus())
    {
        btnConfirmPassReset_released();
        ui->btnBack->setFocus();
        btnBack_selected();
    }
    else if(ui->btnReset->hasFocus())
    {
        btnReset_released();
        ui->btnReset->hide();
        ui->grBoxReset->show();
        ui->btnBack->setFocus();
        btnBack_selected();
    }
    else if(ui->btnBG->hasFocus() || ui->btnEN->hasFocus())
    {
        ui->btnChooseLang->setFocus();
        btnChooseLang_selected();
    }
    else if(ui->btnChooseLang->hasFocus())
    {
        btnChooseLang_released();
        ui->settings->setCurrentIndex(2);
        ui->txtDegrees->setFocus();
    }
    else if(ui->settings->currentIndex() == 2)
    {
        if(txt_m_md == "f")
        {
            if(ui->txtDegrees->hasFocus() || ui->txtMinutes->hasFocus() || ui->txtSeconds->hasFocus())
            {
                ui->btnConfirmDecl->setFocus();
                btnConfirmDecl_selected();
            }
            else if(ui->btnConfirmDecl->hasFocus())
            {
                btnConfirmDecl_released();
                ui->settings->setCurrentIndex(3);
                ui->wgs->setFocus();
                ui->wgs->setStyleSheet("background:gray;");
            }
        }
        else if(txt_m_md == "1")
        {
            k1_magneticDeclination_released();
            k4_magneticDeclination_selected();
            txt_m_md = "4";
        }
        else if(txt_m_md == "4")
        {
            k4_magneticDeclination_released();
            k7_magneticDeclination_selected();
            txt_m_md = "7";
        }
        else if(txt_m_md == "7")
        {
            k7_magneticDeclination_released();
            k_minus_magneticDeclination_selected();
            txt_m_md = "minus";
        }
        else if(txt_m_md == "minus")
        {
            k_minus_magneticDeclination_released();
            k_dot_magneticDeclination_selected();
            txt_m_md = "dot";
        }
        else if(txt_m_md == "2")
        {
            k2_magneticDeclination_released();
            k5_magneticDeclination_selected();
            txt_m_md = "5";
        }
        else if(txt_m_md == "5")
        {
            k5_magneticDeclination_released();
            k8_magneticDeclination_selected();
            txt_m_md = "8";
        }
        else if(txt_m_md == "8")
        {
            k8_magneticDeclination_released();
            k0_magneticDeclination_selected();
            txt_m_md = "0";
        }
        else if(txt_m_md == "0")
        {
            k0_magneticDeclination_released();
            k_del_magneticDeclination_selected();
            txt_m_md = "del";
        }
        else if(txt_m_md == "3")
        {
            k3_magneticDeclination_released();
            k6_magneticDeclination_selected();
            txt_m_md = "6";
        }
        else if(txt_m_md == "6")
        {
            k6_magneticDeclination_released();
            k9_magneticDeclination_selected();
            txt_m_md = "9";
        }
        else if(txt_m_md == "9")
        {
            k9_magneticDeclination_released();
            k_plus_magneticDeclination_selected();
            txt_m_md = "plus";
        }
        else if(txt_m_md == "plus")
        {
            k_plus_magneticDeclination_released();
            k_del_magneticDeclination_selected();
            txt_m_md = "del";
        }
    }
    else if(ui->wgs->hasFocus() || ui->krasovsky->hasFocus() || ui->utm_xy->hasFocus() || ui->bl->hasFocus() || ui->zone_35->hasFocus() || ui->zone_34->hasFocus())
    {
        setWgsStyleSheet();
        setKrasovskyStyleSheet();
        setUtmStyleSheet();
        setDlhStyleSheet();
        setZone1StyleSheet();
        setZone2StyleSheet();

        ui->btnChooseCoordSys->setFocus();
        btnChooseCoordSys_selected();
    }
    else if(ui->krasovsky->hasFocus())
    {
        setKrasovskyStyleSheet();

        ui->btnChooseCoordSys->setFocus();
        btnChooseCoordSys_selected();
    }
    else if(ui->btnChooseCoordSys->hasFocus())
    {
        btnChooseCoordSys_released();
        ui->settings->setCurrentIndex(4);
        ui->point_name->setFocus();
    }
    else if(ui->point_name->hasFocus() || ui->point_latt->hasFocus() || ui->point_long->hasFocus() || ui->point_att->hasFocus())
    {
        ui->add_btn->setFocus();
        btnAdd_selected();
    }
    else if(ui->add_btn->hasFocus())
    {
        btnAdd_released();
        ui->delete_btn->setFocus();
        btnDelete_selected();
    }
    else if(ui->delete_btn->hasFocus())
    {
        btnDelete_released();
        ui->settings->setCurrentIndex(5);
        ui->txtPassReset->setFocus();
    }
    else if(txt_m == "f")
    {
        if(ui->txtCurrPass->hasFocus())
        {
            ui->txtNewPass->setFocus();
            moveLeft();
            showKeyboard();
            ui->keyboard->show();
        }
        else if(ui->txtNewPass->hasFocus())
        {
            ui->txtConfPass->setFocus();
            moveLeft();
            showKeyboard();
            ui->keyboard->show();
        }
        else if(ui->txtConfPass->hasFocus())
        {
            ui->btnConfirmPass->setFocus();
            btnConfirmPass_selected();
            moveRight();
            hideKeyboard();
        }
        else if(ui->txtPassReset->hasFocus())
        {
            ui->grBoxReset->setGeometry(270,50,551,271);
            hideKeyboard();
            ui->btnConfirmPassReset->setFocus();
            btnConfirmPassReset_selected();
        }
    }

    else if(txt_m == "1")
    {
        k1_released();
        k4_selected();
        txt_m = "4";
    }
    else if(txt_m == "4")
    {
        k4_released();
        k7_selected();
        txt_m = "7";
    }
    else if(txt_m == "7")
    {
        k7_released();
        ok_selected();
        txt_m = "ok";
    }
    else if(txt_m == "2")
    {
        k2_released();
        k5_selected();
        txt_m = "5";
    }
    else if(txt_m == "5")
    {
        k5_released();
        k8_selected();
        txt_m = "8";
    }
    else if(txt_m == "8")
    {
        k8_released();
        k0_selected();
        txt_m = "0";
    }
    else if(txt_m == "3")
    {
        k3_released();
        k6_selected();
        txt_m = "6";
    }
    else if(txt_m == "6")
    {
        k6_released();
        k9_selected();
        txt_m = "9";
    }
    else if(txt_m == "9")
    {
        k9_released();
        del_selected();
        txt_m = "del";
    }
}


void Menu::addLetter(QString value){

    if(ui->point_name->hasFocus() == true){

        ui->point_name->setText(ui->point_name->text() + value);

    } else if (ui->point_latt->hasFocus()){

        ui->point_latt->setText(ui->point_latt->text() + value);

    } else if (ui->point_long->hasFocus()){

        ui->point_long->setText(ui->point_long->text() + value);

    } else if (ui->point_att->hasFocus()) {

        ui->point_att->setText(ui->point_att->text() + value);
    }
}

void Menu::removeLetter(){
    if(ui->point_name->hasFocus()){

        ui->point_name->backspace();

    } else if (ui->point_latt->hasFocus()){

        ui->point_latt->backspace();

    } else if (ui->point_long->hasFocus()){

        ui->point_long->backspace();

    } else if (ui->point_att->hasFocus()) {

        ui->point_att->backspace();
    }
}

void Menu::on_btna_pressed()
{
    QString value;
    if(!capsLock){
        value = "a";
    } else {
        value = "A";
    }
    addLetter(value);
    setSmallLetters();
}

void Menu::on_btnb_pressed(){
    QString value;
    if(!capsLock){
        value = "b";
    } else {
        value = "B";
    }
    addLetter(value);
    setSmallLetters();
}

void Menu::on_btnc_pressed(){
    QString value;
    if(!capsLock){
        value = "c";
    } else {
        value = "C";
    }
    addLetter(value);
    setSmallLetters();
}

void Menu::on_btnd_pressed(){
    QString value;
    if(!capsLock){
        value = "d";
    } else {
        value = "D";
    }
    addLetter(value);
    setSmallLetters();
}

void Menu::on_btne_pressed(){
    QString value;
    if(!capsLock){
        value = "e";
    } else {
        value = "E";
    }
    addLetter(value);
    setSmallLetters();
}

void Menu::on_btnf_pressed(){
    QString value;
    if(!capsLock){
        value = "f";
    } else {
        value = "F";
    }
    addLetter(value);
    setSmallLetters();
}

void Menu::on_btng_pressed(){
    QString value;
    if(!capsLock){
        value = "g";
    } else {
        value = "G";
    }
    addLetter(value);
    setSmallLetters();
}

void Menu::on_btnh_pressed(){
    QString value;
    if(!capsLock){
        value = "h";
    } else {
        value = "H";
    }
    addLetter(value);
    setSmallLetters();
}
void Menu::on_btni_pressed(){
    QString value;
    if(!capsLock){
        value = "i";
    } else {
        value = "I";
    }
    addLetter(value);
    setSmallLetters();
}
void Menu::on_btnj_pressed(){
    QString value;
    if(!capsLock){
        value = "j";
    } else {
        value = "J";
    }
    addLetter(value);
    setSmallLetters();
}
void Menu::on_btnk_pressed(){
    QString value;
    if(!capsLock){
        value = "k";
    } else {
        value = "K";
    }
    addLetter(value);
    setSmallLetters();
}
void Menu::on_btnl_pressed(){
    QString value;
    if(!capsLock){
        value = "l";
    } else {
        value = "L";
    }
    addLetter(value);
    setSmallLetters();
}
void Menu::on_btnm_pressed(){
    QString value;
    if(!capsLock){
        value = "m";
    } else {
        value = "M";
    }
    addLetter(value);
    setSmallLetters();
}

void Menu::on_btnn_pressed(){
    QString value;
    if(!capsLock){
        value = "n";
    } else {
        value = "N";
    }
    addLetter(value);
    setSmallLetters();
}

void Menu::on_btno_pressed(){
    QString value;
    if(!capsLock){
        value = "o";
    } else {
        value = "O";
    }
    addLetter(value);
    setSmallLetters();
}

void Menu::on_btnp_pressed(){
    QString value;
    if(!capsLock){
        value = "p";
    } else {
        value = "P";
    }
    addLetter(value);
    setSmallLetters();
}

void Menu::on_btnq_pressed(){
    QString value;
    if(!capsLock){
        value = "q";
    } else {
        value = "Q";
    }
    addLetter(value);
    setSmallLetters();
}

void Menu::on_btnr_pressed(){
    QString value;
    if(!capsLock){
        value = "r";
    } else {
        value = "R";
    }
    addLetter(value);
    setSmallLetters();
}

void Menu::on_btns_pressed(){
    QString value;
    if(!capsLock){
        value = "s";
    } else {
        value = "S";
    }
    addLetter(value);
    setSmallLetters();
}

void Menu::on_btnt_pressed(){
    QString value;
    if(!capsLock){
        value = "t";
    } else {
        value = "T";
    }
    addLetter(value);
    setSmallLetters();
}

void Menu::on_btnu_pressed(){
    QString value;
    if(!capsLock){
        value = "u";
    } else {
        value = "U";
    }
    addLetter(value);
    setSmallLetters();
}

void Menu::on_btnv_pressed(){
    QString value;
    if(!capsLock){
        value = "v";
    } else {
        value = "V";
    }
    addLetter(value);
    setSmallLetters();
}

void Menu::on_btnw_pressed(){
    QString value;
    if(!capsLock){
        value = "w";
    } else {
        value = "W";
    }
    addLetter(value);
    setSmallLetters();
}

void Menu::on_btnx_pressed(){
    QString value;
    if(!capsLock){
        value = "x";
    } else {
        value = "X";
    }
    addLetter(value);
    setSmallLetters();
}

void Menu::on_btny_pressed(){
    QString value;
    if(!capsLock){
        value = "y";
    } else {
        value = "Y";
    }
    addLetter(value);
    setSmallLetters();
}

void Menu::on_btnz_pressed(){
    QString value;
    if(!capsLock){
        value = "z";
    } else {
        value = "Z";
    }
    addLetter(value);
    setSmallLetters();
}

void Menu::on_btn_Sym1_pressed(){
    addLetter(ui->btn_Sym1->text());
}

void Menu::on_btn_Sym2_pressed(){
    addLetter(ui->btn_Sym2->text());
}

void Menu::on_btn_Sym3_pressed(){
    addLetter(ui->btn_Sym3->text());
}

void Menu::on_btn_Sym4_pressed(){
    addLetter(ui->btn_Sym4->text());
}

void Menu::on_btn_Sym5_pressed(){
    addLetter("&");
}

void Menu::on_btn_Sym6_pressed(){
    addLetter(ui->btn_Sym6->text());
}

void Menu::on_btn_Sym7_pressed(){
    addLetter(ui->btn_Sym7->text());
}

void Menu::on_btn_Sym8_pressed(){
    addLetter(ui->btn_Sym8->text());
}

void Menu::on_btn_Sym9_pressed(){
    addLetter(ui->btn_Sym9->text());
}

void Menu::on_btn_Sym10_pressed(){
    addLetter(ui->btn_Sym10->text());
}

void Menu::on_btn_Sym11_pressed(){
    addLetter(ui->btn_Sym11->text());
}

void Menu::on_btn_Sym12_pressed(){
    addLetter(ui->btn_Sym12->text());
}

void Menu::on_btn_Sym13_pressed(){
    addLetter(ui->btn_Sym13->text());
}

void Menu::on_btn_Sym14_pressed(){
    addLetter(ui->btn_Sym14->text());
}

void Menu::on_btn_Sym15_pressed(){
    addLetter(ui->btn_Sym15->text());
}

void Menu::on_btn_Sym16_pressed(){
    addLetter(ui->btn_Sym16->text());
}

void Menu::on_btn_Sym17_pressed(){
    addLetter(ui->btn_Sym17->text());
}

void Menu::on_btn_Sym18_pressed(){
    addLetter(ui->btn_Sym18->text());
}

void Menu::on_btn_Sym19_pressed(){
    addLetter(ui->btn_Sym19->text());
}

void Menu::on_btn_Sym20_pressed(){
    addLetter(ui->btn_Sym20->text());
}

void Menu::on_btn_Sym21_pressed(){
    addLetter(ui->btn_Sym21->text());
}

void Menu::on_btn0_pressed(){
    addLetter(ui->btn0->text());
}

void Menu::on_btn00_pressed(){
    addLetter(ui->btn00->text());
}
void Menu::on_btn1_pressed(){
    addLetter(ui->btn1->text());
}

void Menu::on_btn2_pressed(){
    addLetter(ui->btn2->text());
}

void Menu::on_btn3_pressed(){
    addLetter(ui->btn3->text());
}
void Menu::on_btn4_pressed(){
    addLetter(ui->btn4->text());
}

void Menu::on_btn5_pressed(){
    addLetter(ui->btn5->text());
}

void Menu::on_btn6_pressed(){
    addLetter(ui->btn6->text());
}

void Menu::on_btn7_pressed(){
    addLetter(ui->btn7->text());
}

void Menu::on_btn8_pressed(){
    addLetter(ui->btn8->text());
}

void Menu::on_btn9_pressed(){
    addLetter(ui->btn9->text());
}

void Menu::on_btnDot_pressed(){
    addLetter(ui->btnDot->text());
}

void Menu::on_btn_Space_pressed(){
    addLetter(" ");
}

void Menu::on_btn_Enter_pressed(){
    addLetter(ui->btn_Sym21->text());
}

void Menu::setCapLetters(){
    ui->btna->setText("A");
    ui->btnb->setText("B");
    ui->btnc->setText("C");
    ui->btnd->setText("D");
    ui->btne->setText("E");
    ui->btnf->setText("F");
    ui->btng->setText("G");
    ui->btnh->setText("H");
    ui->btni->setText("I");
    ui->btnj->setText("J");
    ui->btnk->setText("K");
    ui->btnl->setText("L");
    ui->btnm->setText("M");
    ui->btnn->setText("N");
    ui->btno->setText("O");
    ui->btnp->setText("P");
    ui->btnq->setText("Q");
    ui->btnr->setText("R");
    ui->btns->setText("S");
    ui->btnt->setText("T");
    ui->btnu->setText("U");
    ui->btnv->setText("V");
    ui->btnw->setText("W");
    ui->btnx ->setText("X");
    ui->btny->setText("Y");
    ui->btnz->setText("Z");

    capsLock = true;
}
void Menu::setSmallLetters(){
    ui->btna->setText("a");
    ui->btnb->setText("b");
    ui->btnc->setText("c");
    ui->btnd->setText("d");
    ui->btne->setText("e");
    ui->btnf->setText("f");
    ui->btng->setText("g");
    ui->btnh->setText("h");
    ui->btni->setText("i");
    ui->btnj->setText("j");
    ui->btnk->setText("k");
    ui->btnl->setText("l");
    ui->btnm->setText("m");
    ui->btnn->setText("n");
    ui->btno->setText("o");
    ui->btnp->setText("p");
    ui->btnq->setText("q");
    ui->btnr->setText("r");
    ui->btns->setText("s");
    ui->btnt->setText("t");
    ui->btnu->setText("u");
    ui->btnv->setText("v");
    ui->btnw->setText("w");
    ui->btnx ->setText("x");
    ui->btny->setText("y");
    ui->btnz->setText("z");

    capsLock = false;
}

void Menu::on_btn_capslock_pressed(){
    if(capsLock){
        Menu::setSmallLetters();
    } else {
        Menu::setCapLetters();
    }
}

void Menu::on_btn_backspace_pressed(){
    removeLetter();
}

void Menu::addPoints(QString name, QString lattitude, QString longitude, QString altitude, QString type){

  pointObj.setLartosPointName(name);
  pointObj.setLartosPointLattitude(lattitude);
  pointObj.setLartosPointLongitude(longitude);
  pointObj.setLartosPointAltitude(altitude);
  pointObj.setCoordinatesType(type);

  Menu::showDataInTableView(pointObj);

  hashPoint.insert(name, pointObj);

  savePointObj->setPointData(hashPoint);

    ui->point_name->setText("");
    ui->point_att->setText("");
    ui->point_long->setText("");
    ui->point_latt->setText("");
}

void Menu::on_add_btn_pressed(){

    btnAdd_pressed();

    ui->keyboard_qwerty->hide();

    QString name = ui->point_name->text();
    QString lat = ui->point_latt->text();
    QString lng = ui->point_long->text();
    QString alt = ui->point_att->text();
    QString type = ui->comboBox->currentText();

    if(name!=NULL && lat!=NULL && lng!=NULL && alt!=NULL &&type!=NULL)
    {
        Menu::addPoints(name, lat, lng, alt, type);
        ui->point_listView->resizeRowsToContents();
        ui->point_listView->resizeColumnsToContents();
    }
}

void Menu::loadPointData(){

  int indexNew = 1;
  foreach (LartosPointObj val, hashPoint) {
      val.setLartosPointIndex(QString::number(indexNew));
      Menu::showDataInTableView(val);
      indexNew++;
    }
}

void Menu::showDataInTableView(LartosPointObj point){

  QStandardItem *idCol = new QStandardItem(point.getLartosPointIndex());
  idCol->setEditable(false);
  QStandardItem *nameCol = new QStandardItem(point.getLartosPointName());
  QFont fontCol;
  fontCol.setBold(true);
  nameCol->setFont(fontCol);
  QStandardItem *latCol = new QStandardItem(point.getLartosPointLattitude());
  QStandardItem *longCol = new QStandardItem(point.getLartosPointLongitude());
  QStandardItem *atiCol = new QStandardItem(point.getLartosPointAltitude());
  QStandardItem *typeCol = new QStandardItem(point.getCoordinatesType());

  model->appendRow( QList<QStandardItem*>() << nameCol << latCol << longCol << atiCol << typeCol);
  ui->point_listView->resizeColumnsToContents();
  ui->point_listView->resizeRowsToContents();
}

void Menu::initTableView(){
    horizontalHeader.append("Име");
    horizontalHeader.append("Lat/N/X");
    horizontalHeader.append("Long/E/Y");
    horizontalHeader.append("H");
    horizontalHeader.append("Тип");
    model = new QStandardItemModel();

    model->setHorizontalHeaderLabels(horizontalHeader);
    model->setVerticalHeaderLabels(verticalHeader);

    ui->point_listView->setModel(model);

    ui->point_listView->verticalHeader()->setVisible(false);
    ui->point_listView->verticalHeader()->setDefaultSectionSize(15);
    ui->point_listView->setEnabled(true);
    ui->point_listView->setShowGrid(false);

    QFont fontHeader = ui->point_listView->horizontalHeader()->font();
    fontHeader.setPointSize(42);
    ui->point_listView->horizontalHeader()->setFont(fontHeader);
    ui->point_listView->horizontalHeader()->setStyleSheet("QHeaderView { font-size: 18pt; }");
}


void Menu::removePoint(QString name){
  hashPoint.remove(name);
  savePointObj->setPointData(hashPoint);
}

void Menu::on_point_listView_clicked(const QModelIndex &index){
    int indexRow = index.row();
    pointForDelete = index.sibling(index.row(), index.column()).data().toString();
}

void Menu::on_delete_btn_released()
{
    btnDelete_released();
}


void Menu::on_add_btn_released()
{
    btnAdd_released();
}


void Menu::on_delete_btn_pressed()
{
    btnDelete_pressed();

    QItemSelection selection = ui->point_listView->selectionModel()->selection();
      QList<int> rows;
      foreach( const QModelIndex & index, selection.indexes() ) {
          rows.append( index.row() );
        }
      qSort( rows );

      int prev = -1;
      for( int i = rows.count() - 1; i >= 0; i -= 1 ) {
          int current = rows[i];
          if( current != prev ) {
              model->removeRows( current, 1 );
              prev = current;
            }
        }

      Menu::removePoint(pointForDelete);
}


void Menu::on_btnOkDecl_pressed()
{
    btnOkDecl_pressed();
}

void Menu::on_btnOkDecl_released()
{
    btnOkDecl_released();
    ui->invalid->hide();
    if(magnDecl != 0)
    {
        ui->txtDegrees->setText(QString::number(degrees));
        ui->txtMinutes->setText(QString::number(minutes));
        ui->txtSeconds->setText(QString::number(seconds));
        if(magnDecl < 0)
        {
            ui->lblOperator->setText("-");
        }
        else if(magnDecl > 0)
        {
            ui->lblOperator->setText("+");
        }
    }
    ui->txtDegrees->setFocus();
    txt_m_md = "f";
}

void Menu::btnOkDecl_pressed()
{
    ui->btnOkDecl->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid white;"
                "padding: 0 8px; "
                "background: gray;"
                "color:black;"
                );
}


void Menu::btnOkDecl_released()
{
    ui->btnOkDecl->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid gray;"
                "padding: 0 8px; "
                "background: solid white;"
                "color:black;"
                );
}


void Menu::btnOkDecl_selected()
{
    ui->btnOkDecl->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid gray;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                "color:white;"
                );
}

void Menu::btnAdd_selected()
{
    ui->add_btn->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid gray;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                "color:white;"
                );
}

void Menu::btnDelete_selected()
{
    ui->delete_btn->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid gray;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                "color:white;"
                );
}

void Menu::btnAdd_pressed()
{
    ui->add_btn->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid white;"
                "padding: 0 8px; "
                "background: gray;"
                "color:black;"
                );
}

void Menu::btnAdd_released()
{
    ui->add_btn->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid gray;"
                "padding: 0 8px; "
                "background: solid white;"
                "color:black;"
                );
}

void Menu::btnDelete_pressed()
{
    ui->delete_btn->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid white;"
                "padding: 0 8px; "
                "background: gray;"
                "color:black;"
                );
}

void Menu::btnDelete_released()
{
    ui->delete_btn->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid gray;"
                "padding: 0 8px; "
                "background: solid white;"
                "color:black;"
                );
}


void Menu::on_utm_xy_pressed()
{
    setWgsStyleSheet();
    setKrasovskyStyleSheet();
    setDlhStyleSheet();
    setZone1StyleSheet();
    setZone2StyleSheet();
    btnChooseCoordSys_released();

    ui->frame_zone->show();
    ui->zone_35->setChecked(true);
}


void Menu::on_bl_pressed()
{
    setWgsStyleSheet();
    setKrasovskyStyleSheet();
    setUtmStyleSheet();
    setZone1StyleSheet();
    setZone2StyleSheet();
    btnChooseCoordSys_released();

    ui->frame_zone->hide();
}


void Menu::on_zone_35_pressed()
{
    setWgsStyleSheet();
    setKrasovskyStyleSheet();
    setUtmStyleSheet();
    setDlhStyleSheet();
    setZone2StyleSheet();
    btnChooseCoordSys_released();
}


void Menu::on_zone_34_pressed()
{
    setWgsStyleSheet();
    setKrasovskyStyleSheet();
    setUtmStyleSheet();
    setDlhStyleSheet();
    setZone1StyleSheet();
    btnChooseCoordSys_released();
}


void Menu::on_btnOk_pressed()
{
    ui->grBoxPassMessage->hide();
    ui->txtCurrPass->setFocus();
}

void Menu::on_comboBox_currentTextChanged(const QString &type)
{
    if(type == "UTM")
    {
        ui->label_3->setText("Northing");
        ui->label_4->setText("   Easting");
    }
    else if(type == "X,Y")
    {
        ui->label_3->setText("         X");
        ui->label_4->setText("         Y");
    }
    else if(type == "B,L")
    {
        ui->label_3->setText("Latitude");
        ui->label_4->setText("Longitude");
    }
}

void Menu::on_btnSaveReticlePos_pressed()
{
    ui->btnSaveReticlePos->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: black;"
                );

    saveuserdata->setReticlePositionXaxisParameter(GetCrosshairDisplacementX());
    saveuserdata->setReticlePositionYasisParameter(GetCrosshairDisplacementY());
    saveuserdata->setReticleOffsetXaxisParameter(saveuserdata->getReticleOffsetXaxisParameter().toInt() + (-GetCrosshairSOPDisplacementX()));
    saveuserdata->setReticleOffsetYaxisParameter(saveuserdata->getReticleOffsetYaxisParameter().toInt() + (-GetCrosshairSOPDisplacementY()));
}

void Menu::on_btnSaveReticlePos_released()
{
    ui->btnSaveReticlePos->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}

void Menu::changeUserPassword()
{
    QString checkPass = saveuserdata->getUserPasswordParameter();
    if(ui->txtCurrPass->text() == checkPass)
    {
        if(ui->txtNewPass->text() == ui->txtConfPass->text())
        {
            QString newPass = ui->txtNewPass->text();
            saveuserdata->setUserPasswordParameter(newPass);
            if(flgBG_m == false)
            {
                ui->lblPassMessage->setText(lblPassSuccessfulTxt_EN);
            }
            else
            {
                ui->lblPassMessage->setText(lblPassSuccessfulTxt_BG);
            }
            ui->grBoxPassMessage->show();
            ui->btnOk->setFocus();
        }
        else
        {
            if(flgBG_m == false)
            {
                ui->lblPassMessage->setText(lblPassDontMatchTxt_EN);
            }
            else
            {
                ui->lblPassMessage->setText(lblPassDontMatchTxt_BG);
            }
            ui->grBoxPassMessage->show();
            ui->btnOk->setFocus();
        }
    }
    else
    {
        if(flgBG_m == false)
        {
            ui->lblPassMessage->setText(lblWrongPassMessageTxt_EN);
        }
        else
        {
            ui->lblPassMessage->setText(lblWrongPassMessageTxt_BG);
        }
        ui->grBoxPassMessage->show();
        ui->btnOk->setFocus();
    }
}

void Menu::on_btnCenterReticle_pressed()
{
    SetCrosshairDisplacementValue(0, 0);
}

void Menu::on_btnShowOffsetCorrectionReticle_pressed()
{
    if(isOffsetReticleVisible == false)
    {
        ShowCrosshairSOP(true);
        isOffsetReticleVisible = true;
    }
    else if(isOffsetReticleVisible == true)
    {
        ShowCrosshairSOP(false);
        isOffsetReticleVisible = false;
    }
}

void Menu::on_btnShowOffsetCorrectionReticle_released()
{

}
