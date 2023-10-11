#include "expanded.h"
#include "ui_expanded.h"

#include "tasks.h"
#include "ui_tasks.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "resultselection.h"
#include "ui_resultselection.h"

#include "bg.h"
#include "en.h"
#include "Hik/hikvision.h"
#include "Hik/global.h"

#include <QDesktopWidget>
#include <QScreen>
#include <QKeyEvent>

#include "TransLib/PointCoo.h"
#include "TransLib/geodw.h"
#include <QTimer>
#include <TransLib/transform.h>
#include "variables.h"

extern "C"
{
#include "Periph/LucidCameraDraw.h"
}

QTimer* timer_ex = new QTimer();
QTimer* timer_readData = new QTimer();

QIcon *zoom1x_ex = new QIcon();
QIcon *zoom2x_ex = new QIcon();
QIcon *zoom4x_ex = new QIcon();
QIcon *zoom8x_ex = new QIcon();
QIcon *zoom16x_ex = new QIcon();

QIcon *day_ex = new QIcon();
QIcon *thermal_ex = new QIcon();

QIcon *shutter_open_ex = new QIcon();
QIcon *shutter_closed_ex = new QIcon();

double startAngle;
double endAngle;

double xp, yp, hp, Dopc, Lopc, dhopc;
double xa;
double ya;
double ha;
double xop;
double yop;
double hop;

double alfa1;
double alfa2;
double alfa3;
double alfa4;

double Sc;
double Lc;
double Vc;

double Sr;
double Lr;
double Vr;

Expanded::Expanded(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Expanded)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    //StartSoftwareTimer(100, waitForMeasurement, TIMER_PERIODIC, NULL);

    connect(timer_readData, SIGNAL(timeout()), this, SLOT(waitForMeasurement()));
    timer_readData->start(100);

    g_Transform->SetModuleDir(strTTT);
    g_Transform->InitializeTransform();

    //QCursor cursor(Qt::BlankCursor);
    //QApplication::setOverrideCursor(cursor);
    //QApplication::changeOverrideCursor(cursor);

    setAttribute(Qt::WA_AcceptTouchEvents, true);

    ui->frame1A->setVisible(true);
    ui->frame1B->setVisible(false);
    ui->frame1C->setVisible(false);
    ui->frame2->setVisible(false);
    ui->frame3->setVisible(false);
    ui->btnDayir_ex->setVisible(false);
    ui->btnZoom_ex->setVisible(false);
    ui->btnNuc_ex->setVisible(false);
    ui->btnPolarity_ex->setVisible(false);
    ui->btnPantilt_up->setVisible(false);
    ui->btnPantilt_down->setVisible(false);
    ui->btnPantilt_left->setVisible(false);
    ui->btnPantilt_right->setVisible(false);
    ui->btnPantilt_ex->setVisible(false);
    ui->btnScreenshot->setVisible(false);
    ui->keyboard->setVisible(false);
    ui->grBoxPixmap->hide();

    ui->btnPantilt_up->setGeometry(395, -20, 150, 150);
    ui->btnPantilt_down->setGeometry(395, 670, 150, 150);
    ui->btnPantilt_left->setGeometry(0, 325, 150, 150);
    ui->btnPantilt_right->setGeometry(790, 325, 150, 150);

    updateCoordParameters();

    qApp->installEventFilter(this);

    ui->frameLabel->setGeometry(0, 0, 940, 700);
    connect(thermController->processingThread,SIGNAL(newFrame(QPixmap)),this,SLOT(updateFrame(QPixmap)));

    currentVideoPanelX = 940;
    currentVideoPanelY = 700;
    currentVideoPanel = ui->frameLabel;

    day_ex->addPixmap(QPixmap(":/new/prefix1/icons/day.png"), QIcon::Normal, QIcon::On);
    thermal_ex->addPixmap(QPixmap(":/new/prefix1/icons/thermal.png"), QIcon::Normal, QIcon::On);

    if(day_ir == true)
    {
        _ir = true;
        btnDayir_pressed();
        ui->btnDayir->setIcon(*thermal_ex);
        setIrZoom();
    }
    else if(day_ir == false)
    {
        _ir = false;
        setDayZoom();
    }

    _fullExp = false;
    ui->btnDayir->setFocus();

    checkCoordinateInputType();
}

Expanded::~Expanded()
{
    delete ui;
}

void Expanded::updateFrame(const QPixmap &frame)
{
    if(currentVideoPanel==ui->frameLabel)
    {
        ui->frameLabel->setPixmap(frame);
    }
}

void Expanded::checkBeforeTransform()
{
    if(coordinate_system == "wgs")
    {
        outputCooSys = CS_WGS84_CODE;
        outputCooType = CT_UTM_CODE;
        outputZone = 35;
        outputZoneWidth = ZW_6DEGREE_CODE;
    }
    else if(coordinate_system == "krasovsky")
    {
        outputCooSys = CS_42_83_CODE;
        outputCooType = CT_XY_CODE;
        outputZone = 27;
        outputZoneWidth = ZW_6DEGREE_CODE;
    }
}

void Expanded::updateInputParameters()
{
    inputCooSys = outputCooSys;
    inputCooType = outputCooType;
    inputZoneWidth = outputZoneWidth;
    inputZone = outputZone;
}

void Expanded::checkAfterTransform()
{
    if(coordinate_system == "wgs")
    {
        outputCooSys = CS_WGS84_CODE;
        outputCooType = CT_BL_CODE;
        outputZone = ZONE_AUTO;
        outputZoneWidth = ZW_UNKNOWN_CODE;
    }
    else if(coordinate_system == "krasovsky")
    {
        outputCooSys = CS_42_83_CODE;
        outputCooType = CT_BL_CODE;
        outputZone = ZONE_AUTO;
        outputZoneWidth = ZW_UNKNOWN_CODE;
    }
}

void Expanded::transformBeforeTasks_A()
{
    XA_parameter_input = gtor(XA_parameter_input, CF_CODE_DD);
    YA_parameter_input = gtor(YA_parameter_input, CF_CODE_DD);

    g_Transform->Transform(inputCooSys, outputCooSys, inputCooType, outputCooType, inputZoneWidth, outputZoneWidth, inputZone, &outputZone, inputH, outputH, &XA_parameter_input, &YA_parameter_input, &H_parameter);

    isTransformed_A = true;
}


void Expanded::transformBeforeTasks_B()
{
    XB_parameter_input = gtor(XB_parameter_input, CF_CODE_DD);
    YB_parameter_input = gtor(YB_parameter_input, CF_CODE_DD);

    g_Transform->Transform(inputCooSys, outputCooSys, inputCooType, outputCooType, inputZoneWidth, outputZoneWidth, inputZone, &outputZone, inputH, outputH, &XB_parameter_input, &YB_parameter_input, &H_parameter);

    isTransformed_B = true;
}


void Expanded::transformBeforeTasks_C()
{
    XC_parameter_input = gtor(XC_parameter_input, CF_CODE_DD);
    YC_parameter_input = gtor(YC_parameter_input, CF_CODE_DD);

    g_Transform->Transform(inputCooSys, outputCooSys, inputCooType, outputCooType, inputZoneWidth, outputZoneWidth, inputZone, &outputZone, inputH, outputH, &XC_parameter_input, &YC_parameter_input, &H_parameter);

    isTransformed_C = true;
}


void Expanded::transformBeforeTasks_D()
{
    XD_parameter_input = gtor(XD_parameter_input, CF_CODE_DD);
    YD_parameter_input = gtor(YD_parameter_input, CF_CODE_DD);

    g_Transform->Transform(inputCooSys, outputCooSys, inputCooType, outputCooType, inputZoneWidth, outputZoneWidth, inputZone, &outputZone, inputH, outputH, &XD_parameter_input, &YD_parameter_input, &H_parameter);

    isTransformed_D = true;
}


void Expanded::transformAfterTasks_A()
{
    g_Transform->Transform(inputCooSys, outputCooSys, inputCooType, outputCooType, inputZoneWidth, outputZoneWidth, inputZone, &outputZone, inputH, outputH, &XA_parameter_output, &YA_parameter_output, &H_parameter);

    XA_parameter_output = rtog(XA_parameter_output, CF_CODE_DD);
    YA_parameter_output = rtog(YA_parameter_output, CF_CODE_DD);
}


void Expanded::transformAfterTasks_B()
{
    g_Transform->Transform(inputCooSys, outputCooSys, inputCooType, outputCooType, inputZoneWidth, outputZoneWidth, inputZone, &outputZone, inputH, outputH, &XB_parameter_output, &YB_parameter_output, &H_parameter);

    XB_parameter_output = rtog(XB_parameter_output, CF_CODE_DD);
    YB_parameter_output = rtog(YB_parameter_output, CF_CODE_DD);
}


void Expanded::transformAfterTasks_C()
{
    g_Transform->Transform(inputCooSys, outputCooSys, inputCooType, outputCooType, inputZoneWidth, outputZoneWidth, inputZone, &outputZone, inputH, outputH, &XC_parameter_output, &YC_parameter_output, &H_parameter);

    XC_parameter_output = rtog(XC_parameter_output, CF_CODE_DD);
    YC_parameter_output = rtog(YC_parameter_output, CF_CODE_DD);
}


void Expanded::transformAfterTasks_D()
{
    g_Transform->Transform(inputCooSys, outputCooSys, inputCooType, outputCooType, inputZoneWidth, outputZoneWidth, inputZone, &outputZone, inputH, outputH, &XD_parameter_output, &YD_parameter_output, &H_parameter);

    XD_parameter_output = rtog(XD_parameter_output, CF_CODE_DD);
    YD_parameter_output = rtog(YD_parameter_output, CF_CODE_DD);
}

void Expanded::checkCoordinateInputType()
{
    if(coordinate_type == "utm")
    {
        ui->x_1A->setText("Northing:");
        ui->x_1B->setText("Northing:");
        ui->x_1C->setText("Northing:");
        ui->x_2->setText("Northing:");
        ui->x_3->setText("Northing:");
        ui->y_1A->setText("Easting:");
        ui->y_1B->setText("Easting:");
        ui->y_1C->setText("Easting:");
        ui->y_2->setText("Easting:");
        ui->y_3->setText("Easting:");

        ui->btnDirAngleType->setText("MIL");
        ui->btnDirAngleType_1A->setText("MIL");
        ui->btnDirAngleType_1B->setText("MIL");
        ui->label_21->setText("(AB),mil");
        ui->label_26->setText("(AC),mil");
        ui->label_27->setText("(AD),mil");
        ui->label_7->setText("(AB),mil");
        ui->label_8->setText("(Incl),mil");
    }
    else if(coordinate_type == "xy")
    {
        ui->x_1A->setText("X-position:");
        ui->x_1B->setText("X-position:");
        ui->x_1C->setText("X-position:");
        ui->x_2->setText("X-position:");
        ui->x_3->setText("X-position:");
        ui->y_1A->setText("Y-position:");
        ui->y_1B->setText("Y-position:");
        ui->y_1C->setText("Y-position:");
        ui->y_2->setText("Y-position:");
        ui->y_3->setText("Y-position:");

        ui->btnDirAngleType->setText("TH");
        ui->btnDirAngleType_1A->setText("TH");
        ui->btnDirAngleType_1B->setText("TH");
        ui->label_21->setText("(AB),th");
        ui->label_26->setText("(AC),th");
        ui->label_27->setText("(AD),th");
        ui->label_7->setText("(AB),th");
        ui->label_8->setText("(Incl),th");
    }
    else if(coordinate_type == "bl")
    {
        ui->x_1A->setText("Latitude:");
        ui->x_1B->setText("Latitude:");
        ui->x_1C->setText("Latitude:");
        ui->x_2->setText("Latitude:");
        ui->x_3->setText("Latitude:");
        ui->y_1A->setText("Longitude:");
        ui->y_1B->setText("Longitude:");
        ui->y_1C->setText("Longitude:");
        ui->y_2->setText("Longitude:");
        ui->y_3->setText("Longitude:");

        ui->btnDirAngleType->setText("DEG");
        ui->btnDirAngleType_1A->setText("DEG");
        ui->btnDirAngleType_1B->setText("DEG");
        ui->label_21->setText("(AB),deg");
        ui->label_26->setText("(AC),deg");
        ui->label_27->setText("(AD),deg");
        ui->label_7->setText("(AB),deg");
        ui->label_8->setText("(Incl),deg");
    }
}

void Expanded::increaseUpSpeed()
{
    if(mainWinTiltSpeed < 100000)
    {
        mainWinTiltSpeed+=5000;
    }
}
void Expanded::decreaseUpSpeed()
{
    if(mainWinTiltSpeed > 100)
    {
        mainWinTiltSpeed-=5000;
    }
    else if(mainWinTiltSpeed == 100)
    {
        mainWinTiltSpeed = 0;
    }
}

void Expanded::increaseDownSpeed()
{
    if(mainWinTiltSpeed > -100000)
    {
        mainWinTiltSpeed-=5000;
    }
}
void Expanded::decreaseDownSpeed()
{
    if(mainWinTiltSpeed < -100)
    {
        mainWinTiltSpeed+=5000;
    }
    else if(mainWinTiltSpeed == -100)
    {
        mainWinTiltSpeed = 0;
    }
}

void Expanded::increaseLeftSpeed()
{
    if(mainWinPanSpeed > -100000)
    {
        mainWinPanSpeed-=5000;
    }
}
void Expanded::decreaseLeftSpeed()
{
    if(mainWinPanSpeed < -100)
    {
        mainWinPanSpeed+=5000;
    }
    else if(mainWinPanSpeed == -100)
    {
        mainWinPanSpeed = 0;
    }
}

void Expanded::increaseRightSpeed()
{
    if(mainWinPanSpeed < 100000)
    {
        mainWinPanSpeed+=5000;
    }
}
void Expanded::decreaseRightSpeed()
{
    if(mainWinPanSpeed > 100)
    {
        mainWinPanSpeed-=5000;
    }
    else if(mainWinPanSpeed == 100)
    {
        mainWinPanSpeed = 0;
    }
}

void Expanded::startIncreasingUp()
{
    timer_ex->stop();
    mainWinTiltSpeed = 5000;

    if(timer_ex)
    {
        timer_ex->deleteLater();
    }

    timer_ex = new QTimer;
    timer_ex->start(300);
    connect(timer_ex, SIGNAL(timeout()), this, SLOT(increaseUpSpeed()));
    if(mainWinTiltSpeed == 100000)
    {
        timer_ex->stop();
        timer_ex->deleteLater();
    }
}
void Expanded::startIncreasingDown()
{
    timer_ex->stop();
    mainWinTiltSpeed = -5000;

    if(timer_ex)
    {
        timer_ex->deleteLater();
    }

    timer_ex = new QTimer;
    timer_ex->start(300);
    connect(timer_ex, SIGNAL(timeout()), this, SLOT(increaseDownSpeed()));
    if(mainWinTiltSpeed == -100000)
    {
        timer_ex->stop();
        timer_ex->deleteLater();
    }
}
void Expanded::startIncreasingLeft()
{
    timer_ex->stop();
    mainWinPanSpeed = -5000;

    if(timer_ex)
    {
        timer_ex->deleteLater();
    }

    timer_ex = new QTimer;
    timer_ex->start(300);
    connect(timer_ex, SIGNAL(timeout()), this, SLOT(increaseLeftSpeed()));
    if(mainWinPanSpeed == -100000)
    {
        timer_ex->stop();
        timer_ex->deleteLater();
    }
}
void Expanded::startIncreasingRight()
{
    timer_ex->stop();
    mainWinPanSpeed = 5000;

    if(timer_ex)
    {
        timer_ex->deleteLater();
    }

    timer_ex = new QTimer;
    timer_ex->start(300);
    connect(timer_ex, SIGNAL(timeout()), this, SLOT(increaseRightSpeed()));
    if(mainWinPanSpeed == 100000)
    {
        timer_ex->stop();
        timer_ex->deleteLater();
    }
}

void Expanded::setIconPixmap()
{
    zoom1x_ex->addPixmap(QPixmap(":/new/prefix1/icons/zoom1.png"), QIcon::Normal, QIcon::On);
    zoom2x_ex->addPixmap(QPixmap(":/new/prefix1/icons/zoom2.png"), QIcon::Normal, QIcon::On);
    zoom4x_ex->addPixmap(QPixmap(":/new/prefix1/icons/zoom4.png"), QIcon::Normal, QIcon::On);
    zoom8x_ex->addPixmap(QPixmap(":/new/prefix1/icons/zoom8.png"), QIcon::Normal, QIcon::On);
    zoom16x_ex->addPixmap(QPixmap(":/new/prefix1/icons/zoom16.png"),QIcon::Normal, QIcon::On);
}

void Expanded::setDayZoom()
{
    setIconPixmap();

    if(day_zoom == "1X")
    {
        ui->btnZoom->setIcon(*zoom1x_ex);
    }
    else if(day_zoom == "2X")
    {
        ui->btnZoom->setIcon(*zoom2x_ex);
    }
    else if(day_zoom == "4X")
    {
        ui->btnZoom->setIcon(*zoom4x_ex);
    }
    else if(day_zoom == "8X")
    {
        ui->btnZoom->setIcon(*zoom8x_ex);
    }
    else if(day_zoom == "16X")
    {
        ui->btnZoom->setIcon(*zoom16x_ex);
    }
}

void Expanded::setIrZoom()
{
    setIconPixmap();

    if(ir_zoom == "1X")
    {
        ui->btnZoom->setIcon(*zoom1x_ex);
    }
    else if(ir_zoom == "2X")
    {
        ui->btnZoom->setIcon(*zoom2x_ex);
    }
    else if(ir_zoom == "4X")
    {
        ui->btnZoom->setIcon(*zoom4x_ex);
    }
    else if(ir_zoom == "8X")
    {
        ui->btnZoom->setIcon(*zoom8x_ex);
    }
}

void Expanded::setDayZoom_ex()
{
    setIconPixmap();

    if(day_zoom == "1X")
    {
        ui->btnZoom_ex->setIcon(*zoom1x_ex);
    }
    else if(day_zoom == "2X")
    {
        ui->btnZoom_ex->setIcon(*zoom2x_ex);
    }
    else if(day_zoom == "4X")
    {
        ui->btnZoom_ex->setIcon(*zoom4x_ex);
    }
    else if(day_zoom == "8X")
    {
        ui->btnZoom_ex->setIcon(*zoom8x_ex);
    }
    else if(day_zoom == "16X")
    {
        ui->btnZoom_ex->setIcon(*zoom16x_ex);
    }
}

void Expanded::setIrZoom_ex()
{
    setIconPixmap();

    if(ir_zoom == "1X")
    {
        ui->btnZoom_ex->setIcon(*zoom1x_ex);
    }
    else if(ir_zoom == "2X")
    {
        ui->btnZoom_ex->setIcon(*zoom2x_ex);
    }
    else if(ir_zoom == "4X")
    {
        ui->btnZoom_ex->setIcon(*zoom4x_ex);
    }
    else if(ir_zoom == "8X")
    {
        ui->btnZoom_ex->setIcon(*zoom8x_ex);
    }
}

void Expanded::task1_func(){
    XA_parameter_input = ui->Ax_1a->text().toDouble();
    YA_parameter_input = ui->Ay_1a->text().toDouble();

    if(coordinate_type == "bl")
    {
        checkBeforeTransform();
        transformBeforeTasks_A();
        updateInputParameters();
    }
    else
    {
        isTransformed_A = false;
    }

    double XA = XA_parameter_input;
    double YA = YA_parameter_input;
    //double distance = 3604.62; //or get from LRF
    double distance = ui->Dist_1A->text().toDouble();
    //double alfaAngleAB = gtor(1.12108566356359, CF_CODE_DD);
    double alfaAngleAB = 0;
    double alfaAngleAB_input = ui->AB_1A->text().toDouble();
    //double alfaAngleAB_input = double(cdmHeading)/1000;
    if(ui->btnDirAngleType_1A->text() == "DEG")
    {
        alfaAngleAB = alfaAngleAB_input;
    }
    else if(ui->btnDirAngleType_1A->text() == "MIL")
    {
        alfaAngleAB = alfaAngleAB_input * milToDeg;
    }
    else if(ui->btnDirAngleType_1A->text() == "TH")
    {
        alfaAngleAB = alfaAngleAB_input * thToDeg;
    }
    alfaAngleAB = gtor(alfaAngleAB, CF_CODE_DD);

    double XP;
    double YP;

    Prava_zadacha(XA, YA, distance, alfaAngleAB, XP, YP);

    XA_parameter_output = XP;
    YA_parameter_output = YP;
    if(isTransformed_A == true)
    {
        checkAfterTransform();
        transformAfterTasks_A();
        updateInputParameters();
        isTransformed_A = false;
    }

    ui->result_text_1->setText("X: " + QString().setNum(XA_parameter_output, 'g', 7));
    ui->result_text_2->setText("Y: " + QString().setNum(YA_parameter_output, 'g', 7));
}

void Expanded::task1B_func(){
    double XA_input = ui->Ax_1B->text().toDouble();
    double YA_input = ui->Ay_1B->text().toDouble();

    double XB_input = ui->Bx_1B->text().toDouble();
    double YB_input = ui->By_1B->text().toDouble();

    double XC_input = ui->Cx_1B->text().toDouble();
    double YC_input = ui->Cy_1B->text().toDouble();

    double XD_input = ui->Dx_1B->text().toDouble();
    double YD_input = ui->Dy_1B->text().toDouble();

    XA_parameter_input = XA_input;
    YA_parameter_input = YA_input;

    XB_parameter_input = XB_input;
    YB_parameter_input = YB_input;

    XC_parameter_input = XC_input;
    YC_parameter_input = YC_input;

    XD_parameter_input = XD_input;
    YD_parameter_input = YD_input;

    if(coordinate_type == "bl")
    {
        checkBeforeTransform();
        transformBeforeTasks_A();
        transformBeforeTasks_B();
        transformBeforeTasks_C();
        transformBeforeTasks_D();
        updateInputParameters();
    }
    else
    {
        isTransformed_A = false;
        isTransformed_B = false;
        isTransformed_C = false;
        isTransformed_D = false;
    }

    double XA = XA_parameter_input;
    double YA = YA_parameter_input;
    double XB = XB_parameter_input;
    double YB = YB_parameter_input;
    double XC = XC_parameter_input;
    double YC = YC_parameter_input;
    double XD = XD_parameter_input;
    double YD = YD_parameter_input;
    //double alfaAngleAB = gtor(23.9787529678481, CF_CODE_DD);
    //double alfaAngleAC = gtor(87.0250013534813, CF_CODE_DD);
    //double alfaAngleAD = gtor(106.016631358686, CF_CODE_DD);

    double alfaAngleAB_input = ui->AB_1B->text().toDouble();
    double alfaAngleAC_input = ui->AC_1B->text().toDouble();
    double alfaAngleAD_input = ui->AD_1B->text().toDouble();

    double alfaAngleAB = 0;
    double alfaAngleAC = 0;
    double alfaAngleAD = 0;

    if(ui->btnDirAngleType_1B->text() == "DEG")
    {
        alfaAngleAB = alfaAngleAB_input;
        alfaAngleAC = alfaAngleAC_input;
        alfaAngleAD = alfaAngleAD_input;
    }
    else if(ui->btnDirAngleType_1B->text() == "MIL")
    {
        alfaAngleAB = alfaAngleAB_input * milToDeg;
        alfaAngleAC = alfaAngleAC_input * milToDeg;
        alfaAngleAD = alfaAngleAD_input * milToDeg;
    }
    else if(ui->btnDirAngleType_1B->text() == "TH")
    {
        alfaAngleAB = alfaAngleAB_input * thToDeg;
        alfaAngleAC = alfaAngleAC_input * thToDeg;
        alfaAngleAD = alfaAngleAD_input * thToDeg;
    }
    alfaAngleAB = gtor(alfaAngleAB, CF_CODE_DD);
    alfaAngleAC = gtor(alfaAngleAC, CF_CODE_DD);
    alfaAngleAD = gtor(alfaAngleAD, CF_CODE_DD);

    double XP;
    double YP;

    Obratna_Zasechka_ctg(alfaAngleAB, alfaAngleAC, alfaAngleAD, XA, YA, XB, YB, XC, YC, XD, YD, XP, YP);

    XA_parameter_output = XP;
    YA_parameter_output = YP;
    if(isTransformed_A == true && isTransformed_B == true && isTransformed_C == true && isTransformed_D == true)
    {
        checkAfterTransform();
        transformAfterTasks_A();
        updateInputParameters();
        isTransformed_A = false;
        isTransformed_B = false;
        isTransformed_C = false;
        isTransformed_D = false;
    }

    ui->result_text_1->setText("X: " + QString().setNum(XA_parameter_output, 'g', 7));
    ui->result_text_2->setText("Y: " + QString().setNum(YA_parameter_output, 'g', 7));
}


void Expanded::task1C_func(){

    double XA_input = ui->Ax_1C->text().toDouble();
    double YA_input = ui->Ay_1C->text().toDouble();
    XA_parameter_input = XA_input;
    YA_parameter_input = YA_input;
    double XB_input = ui->Bx_1C->text().toDouble();
    double YB_input = ui->By_1C->text().toDouble();
    XB_parameter_input = XB_input;
    YB_parameter_input = YB_input;

    if(coordinate_type == "bl")
        {
            checkBeforeTransform();
            transformBeforeTasks_A();
            transformBeforeTasks_B();
            updateInputParameters();
        }
        else
        {
            isTransformed_A = false;
            isTransformed_B = false;
        }

        double XA = XA_parameter_input;
        double YA = YA_parameter_input;
        double XB = XB_parameter_input;
        double YB = YB_parameter_input;

    //double distanceA = 3604.62172855;
    //double distanceB = 8429.95301619;
    double distanceA = ui->DistA_1C->text().toDouble();
    double distanceB = ui->DistB_1C->text().toDouble();

    double XP;
    double YP;

    Linejna_Zasechka(distanceA, distanceB, XA, YA, XB, YB, XP, YP);

    XA_parameter_output = XP;
    YA_parameter_output = YP;
    if(isTransformed_A == true && isTransformed_B == true)
    {
        checkAfterTransform();
        transformAfterTasks_A();
        updateInputParameters();
        isTransformed_A = false;
        isTransformed_B = false;
    }

    ui->result_text_1->setText(QString().setNum(XA_parameter_output, 'g', 8));
    ui->result_text_2->setText(QString().setNum(YA_parameter_output, 'g', 8));
}


void Expanded::task2_func(){

    XA_parameter_input = ui->Ax_2->text().toDouble();
    YA_parameter_input = ui->Ay_2->text().toDouble();
    double XB_input = ui->Bx_2->text().toDouble();
    double YB_input = ui->By_2->text().toDouble();
    XB_parameter_input = XB_input;
    YB_parameter_input = YB_input;

    if(coordinate_type == "bl")
    {
        checkBeforeTransform();
        transformBeforeTasks_A();
        transformBeforeTasks_B();
        updateInputParameters();
    }
    else
    {
        isTransformed_A = false;
        isTransformed_B = false;
    }

    double XA = XA_parameter_input;
    double YA = YA_parameter_input;
    double XB = XB_parameter_input;
    double YB = YB_parameter_input;


    double distance;
    double alfa;

    Obratna_zadacha(XA, YA, XB, YB, distance, alfa);

    if(isTransformed_A == true && isTransformed_B == true)
    {
        checkAfterTransform();
        updateInputParameters();
        isTransformed_A = false;
        isTransformed_B = false;
    }
    alfa_deg = rtog(alfa, CF_CODE_DD);
    alfa_mil = alfa_deg * degToMil;
    alfa_th = alfa_deg * degToTh;

    ui->result_text_1->setText(QString().setNum(distance, 'g', 7));
    if(ui->btnDirAngleType->text() == "DEG")
    {
        ui->result_text_2->setText(QString::number(alfa_deg));
    }
    else if(ui->btnDirAngleType->text() == "MIL")
    {
        ui->result_text_2->setText(QString::number(alfa_mil));
    }
    else if(ui->btnDirAngleType->text() == "TH")
    {
        ui->result_text_2->setText(QString::number(alfa_th));
    }
}


void Expanded::task3_func(){
    //double Sr = 17029.2587950558;
    //double Sr = (double)rdmTarget1;
    //double Lr = gtor(303.984802039406, CF_CODE_DD);
    //double Lr = gtor(double(cdmHeading)/1000, CF_CODE_DD);
    //double Vr = gtor(0.126991546018999, CF_CODE_DD);
    //double Vr = gtor(double(pdmTilt)/1000, CF_CODE_DD);

    double dDopr = Dopc;
    double dLopr = Lopc;
    double ddhopr = dhopc;

    Calc_Data_For_Razriv(Sr, Lr, Vr, xa, ya, ha, xop, yop, hop, xp, yp, hp, dDopr, dLopr, ddhopr);

    XA_parameter_output = xp;
    YA_parameter_output = yp;

    if(isTransformed_A == true && isTransformed_B == true)
    {
        checkAfterTransform();
        transformAfterTasks_A();
        transformAfterTasks_B();
        updateInputParameters();
        isTransformed_A = false;
        isTransformed_B = false;
    }

    alfa_deg = rtog(dLopr, CF_CODE_DD);
    alfa_mil = alfa_deg * degToMil;
    alfa_th = alfa_deg * degToTh;

    ui->result_text_1->setText("X: " + QString().setNum(XA_parameter_output, 'g', 7));
    ui->result_text_2->setText("Y: " + QString().setNum(YA_parameter_output, 'g', 7));
    ui->result_text_3->setText("H: " + QString::number(hp));
    ui->result_text_4->setText(QString::number(dDopr));
    if(ui->btnDirAngleType->text() == "DEG")
    {
        ui->result_text_5->setText(QString::number(alfa_deg));
    }
    else if(ui->btnDirAngleType->text() == "MIL")
    {
        ui->result_text_5->setText(QString::number(alfa_mil));
    }
    else if(ui->btnDirAngleType->text() == "TH")
    {
        ui->result_text_5->setText(QString::number(alfa_th));
    }
    //ui->result_text_5->setText(QString::number(rtog(dLopr, CF_CODE_DD)));
    ui->result_text_6->setText(QString::number(ddhopr));
    ui->btnDirAngleType->show();
}

void Expanded::showKeyboard()
{
    ui->keyboard->setGeometry(690, 150, 250, 361);
    ui->keyboard->show();
}

void Expanded::btnDayir_ex_pressed()
{
    ui->btnDayir_ex->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}

void Expanded::btnDayir_ex_selected()
{
    ui->btnDayir_ex->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}

void Expanded::btnZoom_ex_pressed()
{
    ui->btnZoom_ex->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}

void Expanded::btnZoom_ex_selected()
{
    ui->btnZoom_ex->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}

void Expanded::btnNuc_ex_pressed()
{
    ui->btnNuc_ex->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}

void Expanded::btnNuc_ex_selected()
{
    ui->btnNuc_ex->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}

void Expanded::btnPolarity_ex_pressed()
{
    ui->btnPolarity_ex->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}

void Expanded::btnPolarity_ex_selected()
{
    ui->btnPolarity_ex->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}

void Expanded::btnPantilt_ex_pressed()
{
    ui->btnPantilt_ex->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}

void Expanded::btnPantilt_ex_selected()
{
    ui->btnPantilt_ex->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}

void Expanded::btnScreenshot_pressed()
{
    ui->btnScreenshot->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}

void Expanded::btnScreenshot_selected()
{
    ui->btnScreenshot->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}

void Expanded::btnBack_pressed()
{
    ui->btnBack->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}

void Expanded::btnBack_selected()
{
    ui->btnBack->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}

void Expanded::btnPantilt_up_pressed()
{
    ui->btnPantilt_up->setStyleSheet(
                "border: 2px rgba(255, 255, 255, 0);"
                "border-radius: 10px;"
                "background: rgba(255, 255, 255, 0);"
                );
}

void Expanded::btnPantilt_up_selected()
{
    ui->btnPantilt_up->setStyleSheet(
                "border: 2px solid white;"
                "border-radius: 10px;"
                "background: rgba(255, 255, 255, 0);"
                );
}

void Expanded::btnPantilt_down_pressed()
{
    ui->btnPantilt_down->setStyleSheet(
                "border: 2px rgba(255, 255, 255, 0);"
                "border-radius: 10px;"
                "background: rgba(255, 255, 255, 0);"
                );
}

void Expanded::btnPantilt_down_selected()
{
    ui->btnPantilt_down->setStyleSheet(
                "border: 2px solid white;"
                "border-radius: 10px;"
                "background: rgba(255, 255, 255, 0);"
                );
}

void Expanded::btnPantilt_left_pressed()
{
    ui->btnPantilt_left->setStyleSheet(
                "border: 2px rgba(255, 255, 255, 0);"
                "border-radius: 10px;"
                "background: rgba(255, 255, 255, 0);"
                );
}

void Expanded::btnPantilt_left_selected()
{
    ui->btnPantilt_left->setStyleSheet(
                "border: 2px solid white;"
                "border-radius: 10px;"
                "background: rgba(255, 255, 255, 0);"
                );
}

void Expanded::btnPantilt_right_pressed()
{
    ui->btnPantilt_right->setStyleSheet(
                "border: 2px rgba(255, 255, 255, 0);"
                "border-radius: 10px;"
                "background: rgba(255, 255, 255, 0);"
                );
}

void Expanded::btnPantilt_right_selected()
{
    ui->btnPantilt_right->setStyleSheet(
                "border: 2px solid white;"
                "border-radius: 10px;"
                "background: rgba(255, 255, 255, 0);"
                );
}

void Expanded::btnDayir_ex_released()
{
    ui->btnDayir_ex->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}
void Expanded::btnZoom_ex_released()
{
    ui->btnZoom_ex->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}
void Expanded::btnNuc_ex_released()
{
    ui->btnNuc_ex->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}
void Expanded::btnPolarity_ex_released()
{
    ui->btnPolarity_ex->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}
void Expanded::btnPantilt_ex_released()
{
    ui->btnPantilt_ex->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}
void Expanded::btnScreenshot_released()
{
    ui->btnScreenshot->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}
void Expanded::btnBack_released()
{
    ui->btnBack->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}
void Expanded::btnPantilt_up_released()
{
    ui->btnPantilt_up->setStyleSheet(
                "border: 2px rgba(255, 255, 255, 0);"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: rgba(255, 255, 255, 0);"
                );
}
void Expanded::btnPantilt_down_released()
{
    ui->btnPantilt_down->setStyleSheet(
                "border: 2px rgba(255, 255, 255, 0);"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: rgba(255, 255, 255, 0);"
                );
}
void Expanded::btnPantilt_left_released()
{
    ui->btnPantilt_left->setStyleSheet(
                "border: 2px rgba(255, 255, 255, 0);"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: rgba(255, 255, 255, 0);"
                );
}
void Expanded::btnPantilt_right_released()
{
    ui->btnPantilt_right->setStyleSheet(
                "border: 2px rgba(255, 255, 255, 0);"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: rgba(255, 255, 255, 0);"
                );
}


void Expanded::btnDayir_pressed()
{
    ui->btnDayir->setStyleSheet(
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}

void Expanded::btnDayir_selected()
{
    ui->btnDayir->setStyleSheet(
                "border: 2px solid white;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}

void Expanded::btnPantilt_pressed()
{
    ui->btnPantilt->setStyleSheet(
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}

void Expanded::btnPantilt_selected()
{
    ui->btnPantilt->setStyleSheet(
                "border: 2px solid white;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}

void Expanded::btnLrf_pressed()
{
    ui->btnLRF->setStyleSheet(
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}

void Expanded::btnLrf_selected()
{
    ui->btnLRF->setStyleSheet(
                "border: 2px solid white;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}

void Expanded::btnZoom_pressed()
{
    ui->btnZoom->setStyleSheet(
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}

void Expanded::btnZoom_selected()
{
    ui->btnZoom->setStyleSheet(
                "border: 2px solid white;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}

void Expanded::btnChange_pressed()
{
    ui->btnChange->setStyleSheet(
                "border: 2px gray;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                );
}

void Expanded::btnChange_selected()
{
    ui->btnChange->setStyleSheet(
                "border: 2px solid white;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                );
}

void Expanded::k1_pressed()
{
    ui->k1->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k1_selected()
{
    ui->k1->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k2_pressed()
{
    ui->k2->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k2_selected()
{
    ui->k2->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k3_pressed()
{
    ui->k3->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k3_selected()
{
    ui->k3->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k4_pressed()
{
    ui->k4->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k4_selected()
{
    ui->k4->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k5_pressed()
{
    ui->k5->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k5_selected()
{
    ui->k5->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k6_pressed()
{
    ui->k6->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k6_selected()
{
    ui->k6->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k7_pressed()
{
    ui->k7->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k7_selected()
{
    ui->k7->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k8_pressed()
{
    ui->k8->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k8_selected()
{
    ui->k8->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k9_pressed()
{
    ui->k9->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k9_selected()
{
    ui->k9->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k0_pressed()
{
    ui->k0->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k0_selected()
{
    ui->k0->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k_minus_pressed()
{
    ui->k_minus->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k_minus_selected()
{
    ui->k_minus->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k_del_pressed()
{
    ui->del->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k_del_selected()
{
    ui->del->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k_calc_pressed()
{
    ui->calculate->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k_calc_selected()
{
    ui->calculate->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k_correction_selected()
{
    ui->correction->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::btnDayir_released()
{
    ui->btnDayir->setStyleSheet(
                "border: 2px solid gray;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}
void Expanded::btnPantilt_released()
{
    ui->btnPantilt->setStyleSheet(
                "border: 2px solid gray;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}
void Expanded::btnLrf_released()
{
    ui->btnLRF->setStyleSheet(
                "border: 2px solid gray;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}
void Expanded::btnZoom_released()
{
    ui->btnZoom->setStyleSheet(
                "border: 2px solid gray;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}
void Expanded::btnChange_released()
{
    ui->btnChange->setStyleSheet(
                "border: 2px solid gray;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                );
}
void Expanded::k1_released()
{
    ui->k1->setStyleSheet(
                "border: 2px solid black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: white;"
                );
}
void Expanded::k2_released()
{
    ui->k2->setStyleSheet(
                "border: 2px solid black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: white;"
                );
}
void Expanded::k3_released()
{
    ui->k3->setStyleSheet(
                "border: 2px solid black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: white;"
                );
}
void Expanded::k4_released()
{
    ui->k4->setStyleSheet(
                "border: 2px solid black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: white;"
                );
}
void Expanded::k5_released()
{
    ui->k5->setStyleSheet(
                "border: 2px solid black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: white;"
                );
}
void Expanded::k6_released()
{
    ui->k6->setStyleSheet(
                "border: 2px solid black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: white;"
                );
}
void Expanded::k7_released()
{
    ui->k7->setStyleSheet(
                "border: 2px solid black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: white;"
                );
}
void Expanded::k8_released()
{
    ui->k8->setStyleSheet(
                "border: 2px solid black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: white;"
                );
}
void Expanded::k9_released()
{
    ui->k9->setStyleSheet(
                "border: 2px solid black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: white;"
                );
}
void Expanded::k0_released()
{
    ui->k0->setStyleSheet(
                "border: 2px solid black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: white;"
                );
}
void Expanded::k_minus_released()
{
    ui->k_minus->setStyleSheet(
                "border: 2px solid black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: white;"
                );
}
void Expanded::k_del_released()
{
    ui->del->setStyleSheet(
                "border: 2px solid black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: white;"
                );
}
void Expanded::k_calc_released()
{
    ui->calculate->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: white;"
                );
}

void Expanded::k_correction_pressed()
{
    ui->correction->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k_correction_released()
{
    ui->correction->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: white;"
                );
}

void Expanded::switchToBG()
{
    flgBG_ex = true;

    //if(_fullExp == true)
    //{
    _task1a = lblTasksTxt_1a_BG;
    _task1b = lblTasksTxt_1b_BG;
    _task1c = lblTasksTxt_1c_BG;
    _task2 = lblTasksTxt_2_BG;
    _task3 = lblTasksTxt_3_BG;
    ui->btnChange->setText(btnChangeTxt_BG);
    ui->result->setTitle(grBoxResultTxt_BG);
    ui->calculate->setText(btnCalculateTxt_BG);
    ui->correction->setText(btnCorrectionTxt_BG);
    ui->del->setText(btnDelTxt_BG);
    ui->btnClose->setText(btnCloseTxt_BG);
}

void Expanded::switchToEN()
{
    flgBG_ex = false;

    _task1a = lblTasksTxt_1a_EN;
    _task1b = lblTasksTxt_1b_EN;
    _task1c = lblTasksTxt_1c_EN;
    _task2 = lblTasksTxt_2_EN;
    _task3 = lblTasksTxt_3_EN;
    ui->btnChange->setText(btnChangeTxt_EN);
    ui->result->setTitle(grBoxResultTxt_EN);
    ui->calculate->setText(btnCalculateTxt_EN);
    ui->correction->setText(btnCorrectionTxt_EN);
    ui->del->setText(btnDelTxt_EN);
    ui->btnClose->setText(btnCloseTxt_EN);
}

void Expanded::showPanTilt()
{
    ui->btnPantilt_up->setGeometry(395, -20, 150, 150);
    ui->btnPantilt_down->setGeometry(395, 670, 150, 150);
    ui->btnPantilt_right->setGeometry(790, 325, 150, 150);

    ui->btnPantilt_up->show();
    ui->btnPantilt_down->show();
    ui->btnPantilt_left->show();
    ui->btnPantilt_right->show();
}

void Expanded::hidePanTilt()
{
    ui->btnPantilt_up->hide();
    ui->btnPantilt_down->hide();
    ui->btnPantilt_left->hide();
    ui->btnPantilt_right->hide();
}

void Expanded::showPanTiltEx()
{
    ui->btnPantilt_up->setGeometry(565, -20, 150, 150);
    ui->btnPantilt_down->setGeometry(565, 670, 150, 150);
    ui->btnPantilt_right->setGeometry(1130, 325, 150, 150);

    ui->btnPantilt_up->show();
    ui->btnPantilt_down->show();
    ui->btnPantilt_left->show();
    ui->btnPantilt_right->show();
}


void Expanded::showIrButtons()
{
    ui->btnNuc_ex->show();
}

void Expanded::hideIrButtons()
{
    ui->btnNuc_ex->hide();
}

void Expanded::makeScreenshot()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap pixmap = screen->grabWindow(0, this->geometry().x(), this->geometry().y(), this->width(), this->height());

    QDateTime now = QDateTime::currentDateTime();
    QString timestamp = now.toString(QLatin1String("dd.MM.yyyy hh-mm-ss"));

    QString directory = "/LartosImages";
    QDir pathToDir;

    auto fileName = QString(pathToDir.homePath()  + directory  + "/" + timestamp + ".bmp");
    pixmap.save(fileName);
}

void Expanded::checkTask()
{
    if(ui->label->text() == _task1a)
    {
        ui->frame1A->show();
    }
    else if(ui->label->text() == _task1b)
    {
        ui->frame1B->show();
    }
    else if(ui->label->text() == _task1c)
    {
        ui->frame1C->show();
    }
    else if(ui->label->text() == _task2)
    {
        ui->frame2->show();
    }
    else if(ui->label->text() == _task3)
    {
        ui->frame3->show();
    }
}


void Expanded::moveRightButtons()
{
    ui->btnPantilt->setGeometry(1157, 2, 121, 71);
    ui->btnZoom->setGeometry(1157, 80, 121, 71);
    ui->btnPantilt_up->setGeometry(565, -20, 150, 150);
    ui->btnPantilt_down->setGeometry(565, 670, 150, 150);
    ui->btnPantilt_right->setGeometry(1130, 325, 150, 150);
}


void Expanded::moveLeftButtons()
{
    ui->btnPantilt->setGeometry(857, 2, 121, 71);
    ui->btnZoom->setGeometry(857, 80, 121, 71);
    ui->btnPantilt_up->setGeometry(395, -20, 150, 150);
    ui->btnPantilt_down->setGeometry(395, 670, 150, 150);
    ui->btnPantilt_right->setGeometry(790, 325, 150, 150);
}


void Expanded::hideTasksBox()
{
    ui->groupBox->hide();
    ui->frame1A->hide();
    ui->frame1B->hide();
    ui->frame1C->hide();
    ui->frame2->hide();
    ui->frame3->hide();
    ui->keyboard->hide();
}


void Expanded::showTasksBox()
{
    ui->groupBox->show();
    checkTask();
}

bool Expanded::eventFilter(QObject *obj, QEvent *event)
{
    foreach(QLineEdit* le, findChildren<QLineEdit*>())
        if (obj == le && event->type() == QEvent::MouseButtonPress)
        {
            showKeyboard();
            txt_h = "f";
        }

    if (obj == ui->video && event->type() == QEvent::MouseButtonPress)
    {
        ui->keyboard->hide();
        ui->video->setFocus();

        if(_fullExp == false)
        {
            if(flgBtnsVisible == false)
            {
                ui->frameLabel->setGeometry(0, 0, 1280, 800);
                currentVideoPanelX = 1280;
                currentVideoPanelY = 800;
                currentVideoPanel = ui->frameLabel;

                hideTasksBox();

                ui->btnDayir->hide();
                ui->btnLRF->hide();
                ui->btnPantilt->hide();
                ui->btnZoom->hide();
                ui->result->hide();
                ui->coordInfo->hide();

                if(_pantilt == true)
                {
                    ui->btnPantilt_up->setGeometry(565,-20,150,150);
                    ui->btnPantilt_down->setGeometry(565,670,150,150);
                    ui->btnPantilt_right->setGeometry(1130,325,150,150);

                    btnPantilt_pressed();
                }

                else  if(_pantilt == false)
                {
                    btnPantilt_released();
                }

                btnLrf_released();
                btnZoom_released();
                btnChange_released();

                if(_ir == false)
                {
                    btnDayir_released();
                }
                else if(_ir == true)
                {
                    btnDayir_pressed();
                }

                flgBtnsVisible = true;
            }

            else if(flgBtnsVisible == true)
            {
                ui->frameLabel->setGeometry(0, 0, 940, 800);
                currentVideoPanelX = 940;
                currentVideoPanelY = 700;
                currentVideoPanel = ui->frameLabel;

                showTasksBox();

                ui->btnDayir->show();
                ui->btnLRF->show();
                ui->btnPantilt->show();
                ui->btnZoom->show();
                ui->result->show();
                ui->coordInfo->show();

                if(_pantilt == true)
                {
                    ui->btnPantilt_up->setGeometry(395,-20,150,150);
                    ui->btnPantilt_down->setGeometry(395,670,150,150);
                    ui->btnPantilt_right->setGeometry(790,325,150,150);
                }

                ui->btnDayir->setFocus();

                flgBtnsVisible = false;
            }
        }

        if(_fullExp == true)
        {
            if(flgBtnsVisible_ex == false)
            {
                ui->btnDayir_ex->hide();
                ui->btnZoom_ex->hide();
                ui->btnPantilt_ex->hide();
                ui->btnScreenshot->hide();
                ui->btnPolarity_ex->hide();
                ui->coordInfo->hide();

                if(_day_ir == true)
                {
                    ui->btnNuc_ex->hide();
                    btnDayir_ex_pressed();

                    if(polarity_ir == false)
                    {
                        btnPolarity_ex_released();
                    }
                    else if(polarity_ir == true)
                    {
                        btnPolarity_ex_pressed();
                    }
                }
                else if(_day_ir == false)
                {
                    btnDayir_ex_released();

                    if(polarity_day == false)
                    {
                        btnPolarity_ex_released();
                    }
                    else if(polarity_day == true)
                    {
                        btnPolarity_ex_pressed();
                    }
                }

                if(_pantilt_ex == false)
                {
                    btnPantilt_ex_released();
                }
                else if(_pantilt_ex == true)
                {
                    btnPantilt_ex_pressed();
                }

                btnZoom_ex_released();
                btnNuc_ex_released();
                btnScreenshot_released();

                ui->btnPantilt_up->setFocus();

                flgBtnsVisible_ex = true;
            }

            else if(flgBtnsVisible_ex == true)
            {
                ui->btnDayir_ex->show();
                ui->btnZoom_ex->show();
                ui->btnPantilt_ex->show();
                ui->btnScreenshot->show();
                ui->btnPolarity_ex->show();
                ui->coordInfo->show();

                if(_day_ir == true)
                {
                    ui->btnNuc_ex->show();
                }

                ui->btnDayir_ex->setFocus();

                flgBtnsVisible_ex = false;
            }
        }
    }
    else if (obj == this && event->type() == QEvent::WindowUnblocked)
    {
        if(insertPoint == true)
        {
            if(task == 2)
            {
                if(selectedPoint == "A")
                {
                    ui->Ax_1B->setText(currLat);
                    ui->Ay_1B->setText(currLong);
                }
                else if(selectedPoint == "B")
                {
                    ui->Bx_1B->setText(currLat);
                    ui->By_1B->setText(currLong);
                }
                else if(selectedPoint == "C")
                {
                    ui->Cx_1B->setText(currLat);
                    ui->Cy_1B->setText(currLong);
                }
                else if(selectedPoint == "D")
                {
                    ui->Dx_1B->setText(currLat);
                    ui->Dy_1B->setText(currLong);
                }
            }
            else if(task == 3)
            {
                if(selectedPoint == "A")
                {
                    ui->Ax_1C->setText(currLat);
                    ui->Ay_1C->setText(currLong);
                }
                else if(selectedPoint == "B")
                {
                    ui->Bx_1C->setText(currLat);
                    ui->By_1C->setText(currLong);
                }
            }
            else if(task == 4)
            {
                if(selectedPoint == "A")
                {
                    ui->Ax_2->setText(currLat);
                    ui->Ay_2->setText(currLong);
                }
                else if(selectedPoint == "B")
                {
                    ui->Bx_2->setText(currLat);
                    ui->By_2->setText(currLong);
                }
            }
        }
        selectedPoint = "0";
    }

    if((obj == ui->Ax_1B || obj == ui->Ay_1B) && event->type() == QEvent::MouseButtonPress)
    {
        alfa1 = double(cdmHeading)/1000;
    }
    if((obj == ui->Bx_1B || obj == ui->By_1B) && event->type() == QEvent::MouseButtonPress)
    {
        alfa2 =(double(cdmHeading)/1000) - alfa1;
        ui->AB_1B->setText(QString().setNum(alfa2, 'g', 8));
    }
    if((obj == ui->Cx_1B || obj == ui->Cy_1B) && event->type() == QEvent::MouseButtonPress)
    {
        alfa3 =(double(cdmHeading)/1000) - alfa1;
        ui->AC_1B->setText(QString().setNum(alfa3, 'g', 8));
    }
    if((obj == ui->Dx_1B || obj == ui->Dy_1B) && event->type() == QEvent::MouseButtonPress)
    {
        alfa4 =(double(cdmHeading)/1000) - alfa1;
        ui->AD_1B->setText(QString().setNum(alfa4, 'g', 8));
    }
    return QObject::eventFilter(obj, event);
}


void Expanded::taskStyle()
{
    _fullExp = true;
    ui->frameLabel->setGeometry(0, 0, 1280, 800);
    currentVideoPanelX = 1280;
    currentVideoPanelY = 800;
    currentVideoPanel = ui->frameLabel;

    ui->groupBox->setVisible(false);
    ui->btnDayir->setVisible(false);
    ui->btnLRF->setVisible(false);
    ui->btnPantilt->setVisible(false);
    ui->btnZoom->setVisible(false);
    ui->frame1A->setVisible(false);
    ui->frame1B->setVisible(false);
    ui->frame1C->setVisible(false);
    ui->frame2->setVisible(false);
    ui->frame3->setVisible(false);
    ui->result->setVisible(false);
    ui->btnDayir_ex->setGeometry(10,10,121,121);
    ui->btnDayir_ex->setVisible(true);
    ui->btnZoom_ex->setGeometry(140,10,121,121);
    ui->btnZoom_ex->setVisible(true);
    ui->btnNuc_ex->setGeometry(400,10,121,121);
    ui->btnNuc_ex->setVisible(false);
    ui->btnPolarity_ex->setGeometry(270,10,121,121);
    ui->btnPolarity_ex->setVisible(true);
    ui->btnPantilt_ex->setGeometry(1010,10,121,121);
    ui->btnScreenshot->setGeometry(1140,10,121,121);
    ui->btnPantilt_ex->setVisible(true);
    ui->btnScreenshot->setVisible(true);
    ui->btnDayir_ex->setFocus();

    updateCoordParameters();


    if(day_ir == true)
    {
        //player->play();

        _day_ir = true;
        btnDayir_ex_pressed();
        ui->btnDayir_ex->setIcon(*thermal_ex);

        showIrButtons();

        setIrZoom_ex();

        if(polarity_ir == true)
        {
            btnPolarity_ex_pressed();
        }
        else if(polarity_ir == false)
        {
            btnPolarity_ex_released();
        }
    }
    else if(day_ir == false)
    {
        _day_ir= false;
        setDayZoom_ex();

        if(polarity_day == true)
        {
            btnPolarity_ex_pressed();
        }
        else if(polarity_day == false)
        {
            btnPolarity_ex_released();
        }
    }

    ui->btnDayir_ex->setFocus();
}


void Expanded::on_k1_pressed()
{
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    k_minus_released();
    k_del_released();
    k_dot_released();

    k1_pressed();

    txt = "1";
    keyboardInput();
}


void Expanded::on_k1_released()
{
    k1_released();
}


void Expanded::on_k2_pressed()
{
    k1_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    k_minus_released();
    k_del_released();
    k_dot_released();

    k2_pressed();

    txt = "2";
    keyboardInput();
}


void Expanded::on_k2_released()
{
    k2_released();
}


void Expanded::on_k3_pressed()
{
    k1_released();
    k2_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    k_minus_released();
    k_del_released();
    k_dot_released();

    k3_pressed();

    txt = "3";
    keyboardInput();
}


void Expanded::on_k3_released()
{
    k3_released();
}


void Expanded::on_k4_pressed()
{
    k1_released();
    k2_released();
    k3_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    k_minus_released();
    k_del_released();
    k_dot_released();

    k4_pressed();

    txt = "4";
    keyboardInput();
}


void Expanded::on_k4_released()
{
    k4_released();
}


void Expanded::on_k5_pressed()
{
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    k_minus_released();
    k_del_released();
    k_dot_released();

    k5_pressed();

    txt = "5";
    keyboardInput();
}


void Expanded::on_k5_released()
{
    k5_released();
}


void Expanded::on_k6_pressed()
{
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k7_released();
    k8_released();
    k9_released();
    k0_released();
    k_minus_released();
    k_del_released();
    k_dot_released();

    k6_pressed();

    txt = "6";
    keyboardInput();
}


void Expanded::on_k6_released()
{
    k6_released();
}


void Expanded::on_k7_pressed()
{
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k8_released();
    k9_released();
    k0_released();
    k_minus_released();
    k_del_released();
    k_dot_released();

    k7_pressed();

    txt = "7";
    keyboardInput();
}


void Expanded::on_k7_released()
{
    k7_released();
}


void Expanded::on_k8_pressed()
{
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k9_released();
    k0_released();
    k_minus_released();
    k_del_released();
    k_dot_released();

    k8_pressed();

    txt = "8";
    keyboardInput();
}


void Expanded::on_k8_released()
{
    k8_released();
}


void Expanded::on_k9_pressed()
{
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k0_released();
    k_minus_released();
    k_del_released();
    k_dot_released();

    k9_pressed();

    txt = "9";
    keyboardInput();
}


void Expanded::on_k9_released()
{
    k9_released();
}


void Expanded::on_k0_pressed()
{
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k_minus_released();
    k_del_released();
    k_dot_released();

    k0_pressed();

    txt = "0";
    keyboardInput();
}


void Expanded::on_k0_released()
{
    k0_released();
}


void Expanded::on_k_minus_pressed()
{
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
    k_del_released();
    k_dot_released();

    k_minus_pressed();

    txt = "-";
    keyboardInput();
}


void Expanded::on_k_minus_released()
{
    k_minus_released();
}


void Expanded::on_del_pressed()
{
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
    k_minus_released();
    k_dot_released();

    k_del_pressed();

    deleteLast();
}


void Expanded::on_del_released()
{
    k_del_released();
}


void Expanded::on_calculate_pressed()
{
    btnLrf_released();
    btnZoom_released();
    btnChange_released();
    btnBack_released();

    k_calc_pressed();
}


void Expanded::on_calculate_released()
{
    k_calc_released();

    if(ui->frame1A->isVisible())
    {
        task1_func();
    }
    else if(ui->frame1B->isVisible())
    {
        task1B_func();
    }
    else if(ui->frame1C->isVisible())
    {
        task1C_func();
    }
    else if(ui->frame2->isVisible())
    {
        task2_func();
    }
    else if(ui->frame3->isVisible())
    {
        task3_func();
    }

    ui->keyboard->hide();
    makeScreenshot();

    if(task == 2 || task == 3)
    {
        if(QString::number(XA_parameter_output) != "nan" && QString::number(YA_parameter_output) != "nan")
        {
            newLat = XA_parameter_output;
            newLong = YA_parameter_output;
            newAlt = QString::number(H_parameter);
            resultSelection.showTaskResult();
            resultSelection.switchToBG();
            resultSelection.exec();
        }
    }
    else if(task == 4)
    {
        if(QString::number(alfa_deg) != "nan")
        {
            resultSelection.showDirAngleResult();
            resultSelection.switchToBG();
            resultSelection.exec();
        }
    }
}


void Expanded::task1A()
{
    _pantilt = false;

    ui->label->setText(_task1a);
    ui->label->adjustSize();

    ui->frame1A->setVisible(true);
    ui->frame1B->setVisible(false);
    ui->frame1C->setVisible(false);
    ui->frame2->setVisible(false);
    ui->frame3->setVisible(false);

    ui->frame1A->setGeometry(950, 126, 321, 321);
    ui->calculate->setGeometry(10, 465, 321, 70);
    ui->result->setGeometry(950, 530, 321, 138);
    ui->calculate->show();
    ui->correction->hide();
    ui->calculate->setEnabled(true);

    ui->btnPoints->hide();
    ui->btnDirAngleType->hide();

    ui->Ax_1a->setText(QString().setNum(X_parameter, 'g', 8));
    ui->Ay_1a->setText(QString().setNum(Y_parameter, 'g', 8));
    ui->H_1A->setText(QString::number(H_parameter));

    if(_ir == true)
    {
        btnDayir_pressed();
    }
}
void Expanded::task1B()
{
    _pantilt = false;

    ui->label->setText(_task1b);
    ui->label->adjustSize();

    ui->frame1A->setVisible(false);
    ui->frame1B->setVisible(true);
    ui->frame1C->setVisible(false);
    ui->frame2->setVisible(false);
    ui->frame3->setVisible(false);

    ui->frame1B->setGeometry(950, 126, 321, 431);
    ui->calculate->setGeometry(10, 575, 321, 70);
    ui->result->setGeometry(950, 640, 321, 138);
    ui->calculate->show();
    ui->correction->hide();
    ui->calculate->setEnabled(true);

    ui->btnPoints->show();
    ui->btnDirAngleType->hide();

    if(_ir == true)
    {
        btnDayir_pressed();
    }
}

void Expanded::task1C()
{
    firstTargetMeasured = false;
    _pantilt = false;

    ui->label->setText(_task1c);
    ui->label->adjustSize();

    ui->frame1A->setVisible(false);
    ui->frame1B->setVisible(false);
    ui->frame1C->setVisible(true);
    ui->frame2->setVisible(false);
    ui->frame3->setVisible(false);

    ui->frame1C->setGeometry(950, 126, 321, 266);
    ui->calculate->setGeometry(10, 410, 321, 70);
    ui->result->setGeometry(950, 475, 321, 138);
    ui->calculate->show();
    ui->correction->hide();
    ui->calculate->setEnabled(true);

    ui->btnPoints->show();
    ui->btnDirAngleType->hide();

    if(_ir == true)
    {
        btnDayir_pressed();
    }
}

void Expanded::task2()
{
    _pantilt = false;

    ui->label->setText(_task2);
    ui->label->adjustSize();

    ui->frame1A->setVisible(false);
    ui->frame1B->setVisible(false);
    ui->frame1C->setVisible(false);
    ui->frame2->setVisible(true);
    ui->frame3->setVisible(false);

    ui->frame2->setGeometry(950, 126, 321, 156);
    ui->calculate->setGeometry(10, 300, 321, 70);
    ui->result->setGeometry(950, 365, 321, 138);
    ui->calculate->show();
    ui->correction->hide();
    ui->calculate->setEnabled(true);

    ui->btnPoints->show();
    ui->btnDirAngleType->setGeometry(255,88,61,48);
    ui->btnDirAngleType->show();

    ui->Ax_2->setText(QString().setNum(X_parameter, 'g', 8));
    ui->Ay_2->setText(QString().setNum(Y_parameter, 'g', 8));

    if(_ir == true)
    {
        btnDayir_pressed();
    }
}

void Expanded::task3()
{
    _pantilt = false;

    ui->label->setText(_task3);
    ui->label->adjustSize();

    ui->frame1A->setVisible(false);
    ui->frame1B->setVisible(false);
    ui->frame1C->setVisible(false);
    ui->frame2->setVisible(false);
    ui->frame3->setVisible(true);

    ui->frame3->setGeometry(950, 126, 321, 266);
    ui->calculate->setGeometry(10, 405, 321, 70);
    ui->correction->setGeometry(10, 405, 321, 70);
    //ui->result->setGeometry(950, 465, 321, 185);
    ui->result->setGeometry(950, 465, 321, 351);

    ui->calculate->hide();
    ui->btnDirAngleType->hide();
    ui->correction->show();

    ui->correction->setEnabled(false);

    ui->btnPoints->hide();
    ui->btnDirAngleType->setGeometry(255,236,61,48);
    //ui->btnDirAngleType->show();

    ui->Tx_3->setText(QString().setNum(X_parameter, 'g', 8));
    ui->Ty_3->setText(QString().setNum(Y_parameter, 'g', 8));
    ui->TH_3->setText(QString::number(H_parameter));

    if(_ir == true)
    {
        btnDayir_pressed();
    }
}


void Expanded::keyboardInput()
{
    foreach(QLineEdit* le, findChildren<QLineEdit*>())
        if(le->hasFocus())
        {
            le->setText(le->text() + txt);
        }
}

void Expanded::deleteLast()
{
    foreach(QLineEdit* le, findChildren<QLineEdit*>())
        if(le->hasFocus())
        {
            le->backspace();
        }
}


void Expanded::on_btnChange_released()
{
    btnChange_released();
    currentVideoPanel = NULL;

    Tasks* t = new Tasks();
    //t.setModal(true);
    t->show();

    if(flgBG_ex == true)
    {
        t->switchToBG();
    }
    else if(flgBG_ex == false)
    {
        t->switchToEN();
    }

    //t.exec();

    this->close();
}


void Expanded::on_btnBack_pressed()
{
    ui->btnBack->setFocus();

    btnLrf_released();
    btnZoom_released();
    btnChange_released();
    k_calc_released();

    if(_ir == false)
    {
        btnDayir_released();
    }

    if(_pantilt == false)
    {
        btnPantilt_released();
    }

    btnBack_pressed();
}


void Expanded::on_btnDayir_pressed()
{
    ui->btnDayir->setFocus();

    if(GetSelectedCamera()==DAYCAM)
    {
        if(SelectCamera(THERMALCAM)==true)
        {
            btnDayir_pressed();
            ui->btnDayir->setIcon(*thermal_ex);
            setIrZoom();
            _ir = true;
            day_ir = true;

        }
    }
    else if(GetSelectedCamera()==THERMALCAM)
    {
        if(SelectCamera(DAYCAM)==true)
        {
            btnDayir_released();
            ui->btnDayir->setIcon(*day_ex);
            setDayZoom();
            _ir = false;
	    day_ir = false;

        }
    }

    btnBack_released();
    btnLrf_released();
    btnZoom_released();
    btnChange_released();
    k_calc_released();

    if(_pantilt == false)
    {
        btnPantilt_released();
    }
}


void Expanded::on_btnLRF_pressed()
{
    requestMeasureTime = rdmLastMeasurementTimeS;
    RfRequestMeasurement();

    ui->btnLRF->setFocus();

    btnLrf_pressed();

    btnBack_released();
    btnZoom_released();
    btnChange_released();
    k_calc_released();

    if(_ir == false)
    {
        btnDayir_released();
    }

    if(_pantilt == false)
    {
        btnPantilt_released();
    }
}

void Expanded::waitForMeasurement()
{
    if(requestMeasureTime != -1 && requestMeasureTime < rdmLastMeasurementTimeS)
    {
        distance = (double)rdmTarget1;
        measuredDistance = QString::number(distance);
        double angleDifference = 0;

        if(task == 1)
        {
            double angle = double(cdmHeading)/1000;
            double inclination = double(pdmTilt)/1000;
            ui->Dist_1A->setText(measuredDistance);
            ui->AB_1A->setText(QString().setNum(angle, 'g', 8));
            ui->Incl_1A->setText(QString().setNum(inclination, 'g', 8));
        }
        else if(task == 3)
        {
            if(firstTargetMeasured == false)
            {
                ui->DistA_1C->setText(measuredDistance);
                if(distance > 0.0)
                {
                    startAngle = double(cdmHeading)/1000;
                    firstTargetMeasured = true;
                }
            }
            else if(firstTargetMeasured == true)
            {
                endAngle = double(cdmHeading)/1000;
                angleDifference = endAngle - startAngle;
                if(endAngle > startAngle)
                {
                    if(angleDifference > 29.999)
                    {
                        ui->DistB_1C->setText(measuredDistance);
                        if(distance > 0.0)
                        {
                            firstTargetMeasured = false;
                        }
                    }
                }
            }
        }
        else if(task == 5)
        {
            if(ui->correction->isVisible() == true)
            {
                Sc = (double)rdmTarget1;
                Lc = gtor(double(cdmHeading)/1000, CF_CODE_DD);
                Vc = gtor(double(pdmTilt)/1000, CF_CODE_DD);
                if(Sc > 0.0)
                {
                    ui->correction->setEnabled(true);
                }
            }
            else if(ui->calculate->isVisible() == true)
            {
                Sr = (double)rdmTarget1;
                Lr = gtor(double(cdmHeading)/1000, CF_CODE_DD);
                Vr = gtor(double(pdmTilt)/1000, CF_CODE_DD);
                if(Sr > 0.0)
                {
                    ui->calculate->setEnabled(true);
                }
            }
        }
        requestMeasureTime = -1;
    }
}


void Expanded::on_btnLRF_released()
{
    btnLrf_released();
}


void Expanded::on_btnBack_released()
{
    btnBack_released();
    firstTargetMeasured = false;
    currentVideoPanel = NULL;
    _fullExp = false;

    this->close();
}


void Expanded::on_btnChange_pressed()
{
    ui->btnChange->setFocus();

    btnBack_released();
    btnLrf_released();
    btnZoom_released();
    k_calc_released();

    if(_ir == false)
    {
        btnDayir_released();
    }

    if(_pantilt == false)
    {
        btnPantilt_released();
    }

    btnChange_pressed();
}


void Expanded::on_btnDayir_ex_pressed()
{
    ui->btnDayir_ex->setFocus();

    btnZoom_ex_released();
    btnNuc_ex_released();
    btnScreenshot_released();
    btnBack_released();

    if(_pantilt_ex == false)
    {
        btnPantilt_ex_released();
    }

    if(GetSelectedCamera()==DAYCAM)
    {
        if(SelectCamera(THERMALCAM)==true)
        {
            btnDayir_ex_pressed();
            ui->btnDayir_ex->setIcon(*thermal_ex);
            setIrZoom_ex();
            showIrButtons();

            if(polarity_ir == false)
            {
                btnPolarity_ex_released();
            }
            else if(polarity_ir == true)
            {
                btnPolarity_ex_pressed();
            }
            _day_ir = true;
            day_ir = true;
        }
    }
    else if(GetSelectedCamera()==THERMALCAM)
    {
        if(SelectCamera(DAYCAM)==true)
        {
            btnDayir_ex_released();
            ui->btnDayir_ex->setIcon(*day_ex);
            setDayZoom_ex();
            hideIrButtons();

            if(polarity_day == false)
            {
                btnPolarity_ex_released();
            }
            else if(polarity_day == true)
            {
                btnPolarity_ex_pressed();
            }
            _day_ir = false;
            day_ir = false;
        }
    } 
}


void Expanded::on_btnNuc_ex_pressed()
{
    shutter_open_ex->addPixmap(QPixmap(":/new/prefix1/icons/shutter_open.png"), QIcon::Normal, QIcon::On);

    ui->btnNuc_ex->setFocus();

    if(_day_ir == false)
    {
        btnDayir_ex_released();

        if(polarity_day == false)
        {
            btnPolarity_ex_released();
        }
    }
    else if(_day_ir == true)
    {
        if(polarity_ir == false)
        {
            btnPolarity_ex_released();
        }
    }

    if(_pantilt_ex == false)
    {
        btnPantilt_ex_released();
    }
    btnZoom_ex_released();
    btnScreenshot_released();
    btnBack_released();

    btnNuc_ex_pressed();
    ui->btnNuc_ex->setIcon(*shutter_open_ex);
    hikVision->doNuc();
}

void Expanded::on_btnZoom_ex_pressed()
{
    ui->btnZoom_ex->setFocus();
    btnZoom_ex_pressed();

    if(_day_ir == false)
    {
        btnDayir_ex_released();

        checkDayZoom_ex();

        if(polarity_day == false)
        {
            btnPolarity_ex_released();
        }
    }
    else if(_day_ir == true)
    {
        checkIrZoom_ex();

        if(polarity_ir == false)
        {
            btnPolarity_ex_released();
        }
    }

    if(_pantilt_ex == false)
    {
        btnPantilt_ex_released();
    }
    btnNuc_ex_released();
    btnScreenshot_released();
    btnBack_released();
}


void Expanded::on_btnZoom_ex_released()
{
    btnZoom_ex_released();
}


void Expanded::on_btnPolarity_ex_pressed()
{
    ui->btnPolarity_ex->setFocus();

    if(_day_ir == false)
    {
        btnDayir_ex_released();

        if(polarity_day == false)
        {
            btnPolarity_ex_pressed();
            polarity_day = true;
        }
        else if(polarity_day == true)
        {
            btnPolarity_ex_released();
            polarity_day = false;
        }
        SetGrayscaleOn(polarity_day);
    }
    else if(_day_ir == true)
    {
        if(polarity_ir == false)
        {
            btnPolarity_ex_pressed();
            hikVision->setPolarity(1);
            polarity_ir = true;
        }
        else if(polarity_ir == true)
        {
            btnPolarity_ex_released();
            hikVision->setPolarity(2);
            polarity_ir = false;
        }
    }

    if(_pantilt_ex == false)
    {
        btnPantilt_ex_released();
    }

    btnNuc_ex_released();
    btnZoom_ex_released();
    btnScreenshot_released();
    btnBack_released();
}

void Expanded::on_btnNuc_ex_released()
{
    shutter_closed_ex->addPixmap(QPixmap(":/new/prefix1/icons/shutter_closed.png"), QIcon::Normal, QIcon::On);
    btnNuc_ex_released();
    ui->btnNuc_ex->setIcon(*shutter_closed_ex);
}

void Expanded::on_btnPantilt_pressed()
{
    ui->btnPantilt->setFocus();

    if(_pantilt == false)
    {
        btnPantilt_pressed();

        showPanTilt();

        _pantilt = true;
    }
    else if(_pantilt == true)
    {
        btnPantilt_released();

        hidePanTilt();

        _pantilt = false;
    }

    btnBack_released();
    btnLrf_released();
    btnZoom_released();
    btnChange_released();
    k_calc_released();

    if(_ir == false)
    {
        btnDayir_released();
    }
}


void Expanded::on_btnZoom_pressed()
{
    btnBack_released();
    btnLrf_released();
    btnChange_released();
    k_calc_released();

    if(_ir == false)
    {
        btnDayir_released();
    }

    if(_pantilt == false)
    {
        btnPantilt_released();
    }

    btnZoom_pressed();

    if(_ir == true)
    {
        checkIrZoom();
    }
    else if(_ir == false)
    {
        checkDayZoom();
    }
}


void Expanded::on_btnZoom_released()
{
    ui->btnZoom->setFocus();

    btnZoom_released();
}


void Expanded::on_btnPantilt_up_pressed()
{
    mainWinPanSpeed = 0;
    mainWinTiltSpeed = 100;

    btnBack_released();
    btnLrf_released();
    btnZoom_released();
    btnChange_released();
    k_calc_released();

    if(_ir == false)
    {
        btnDayir_released();
    }

    btnPantilt_up_pressed();

    if(timer_ex)
    {
        timer_ex->deleteLater();
    }

    timer_ex = new QTimer;
    timer_ex->start(1000);
    connect(timer_ex, SIGNAL(timeout()), this, SLOT(startIncreasingUp()));
}


void Expanded::on_btnPantilt_up_released()
{
    timer_ex->stop();

    btnPantilt_up_released();

    if(timer_ex)
    {
        timer_ex->deleteLater();
    }

    timer_ex = new QTimer;
    timer_ex->start(25);
    connect(timer_ex, SIGNAL(timeout()), this, SLOT(decreaseUpSpeed()));
    if(mainWinTiltSpeed == 0)
    {
        timer_ex->stop();
    }
}


void Expanded::on_btnPantilt_down_pressed()
{
    mainWinPanSpeed = 0;
    mainWinTiltSpeed = -100;

    btnBack_released();
    btnLrf_released();
    btnZoom_released();
    btnChange_released();
    k_calc_released();

    if(_ir == false)
    {
        btnDayir_released();
    }

    btnPantilt_down_pressed();

    if(timer_ex)
    {
        timer_ex->deleteLater();
    } 
    timer_ex = new QTimer;
    timer_ex->start(1000);
    connect(timer_ex, SIGNAL(timeout()), this, SLOT(startIncreasingDown()));
}


void Expanded::on_btnPantilt_down_released()
{
    timer_ex->stop();

    btnPantilt_down_released();

    if(timer_ex)
    {
        timer_ex->deleteLater();
    } 
    timer_ex = new QTimer;
    timer_ex->start(25);
    connect(timer_ex, SIGNAL(timeout()), this, SLOT(decreaseDownSpeed()));
    if(mainWinTiltSpeed == 0)
    {
        timer_ex->stop();
    }
}


void Expanded::on_btnPantilt_left_pressed()
{
    mainWinTiltSpeed = 0;
    mainWinPanSpeed = -100;

    btnBack_released();
    btnLrf_released();
    btnZoom_released();
    btnChange_released();
    k_calc_released();

    if(_ir == false)
    {
        btnDayir_released();
    }

    btnPantilt_left_pressed();

    if(timer_ex)
    {
        timer_ex->deleteLater();
    } 
    timer_ex = new QTimer;
    timer_ex->start(1000);
    connect(timer_ex, SIGNAL(timeout()), this, SLOT(startIncreasingLeft()));
}


void Expanded::on_btnPantilt_left_released()
{
    timer_ex->stop();

    btnPantilt_left_released();

    if(timer_ex)
    {
        timer_ex->deleteLater();
    } 
    timer_ex = new QTimer;
    timer_ex->start(25);
    connect(timer_ex, SIGNAL(timeout()), this, SLOT(decreaseLeftSpeed()));
    if(mainWinPanSpeed == 0)
    {
        timer_ex->stop();
    }
}


void Expanded::on_btnPantilt_right_pressed()
{
    mainWinTiltSpeed = 0;
    mainWinPanSpeed = 100;

    btnBack_released();
    btnLrf_released();
    btnZoom_released();
    btnChange_released();
    k_calc_released();

    if(_ir == false)
    {
        btnDayir_released();
    }

    btnPantilt_right_pressed();

    if(timer_ex)
    {
        timer_ex->deleteLater();
    } 
    timer_ex = new QTimer;
    timer_ex->start(1000);
    connect(timer_ex, SIGNAL(timeout()), this, SLOT(startIncreasingRight()));
}


void Expanded::on_btnPantilt_right_released()
{
    timer_ex->stop();

    btnPantilt_right_released();

    if(timer_ex)
    {
        timer_ex->deleteLater();
    } 
    timer_ex = new QTimer;
    timer_ex->start(25);
    connect(timer_ex, SIGNAL(timeout()), this, SLOT(decreaseRightSpeed()));
    if(mainWinPanSpeed == 0)
    {
        timer_ex->stop();
    }
}


void Expanded::on_btnPantilt_ex_pressed()
{
    ui->btnPantilt_ex->setFocus();

    if(_pantilt_ex == false)
    {
        btnPantilt_ex_pressed();

        showPanTiltEx();

        _pantilt_ex = true;
    }
    else if(_pantilt_ex == true)
    {
        btnPantilt_ex_released();

        hidePanTilt();

        _pantilt_ex = false;
    }

    if(_day_ir == false)
    {
        btnDayir_ex_released();

        if(polarity_day == false)
        {
            btnPolarity_ex_released();
        }
    }
    else if(_day_ir == true)
    {
        if(polarity_ir == false)
        {
            btnPolarity_ex_released();
        }
    }

    btnNuc_ex_released();
    btnZoom_ex_released();
    btnScreenshot_released();
    btnBack_released();
}


void Expanded::on_btnScreenshot_pressed()
{
    btnNuc_ex_released();
    btnZoom_ex_released();
    btnBack_released();

    if(_day_ir == false)
    {
        btnDayir_ex_released();

        if(polarity_day == false)
        {
            btnPolarity_ex_released();
        }
    }
    else if(_day_ir == true)
    {
        if(polarity_ir == false)
        {
            btnPolarity_ex_released();
        }
    }

    if(_pantilt_ex == false)
    {
        btnPantilt_ex_released();
    }

    btnScreenshot_pressed();
}


void Expanded::on_btnScreenshot_released()
{
    btnScreenshot_released();

    makeScreenshot();
    taskStyle();
    ui->btnScreenshot->setFocus();
    if(_day_ir == true)
    {
        btnDayir_ex_pressed();
        showIrButtons();
    }
}

void Expanded::on_k_dot_pressed()
{
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
    k_minus_released();
    k_del_released();

    k_dot_pressed();

    txt = ".";
    keyboardInput();
}

void Expanded::on_k_dot_released()
{
    k_dot_released();
}

void Expanded::k_dot_pressed()
{
    ui->k_dot->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::k_dot_released()
{
    ui->k_dot->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: white;"
                );
}

void Expanded::k_dot_selected()
{
    ui->k_dot->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Expanded::gpioBtnOk()
{
    if(_fullExp == true)
    {
        if(ui->btnDayir_ex->hasFocus())
        {
            on_btnDayir_ex_pressed();
            btnDayir_ex_selected();
        }
        else if(ui->btnZoom_ex->hasFocus())
        {
            on_btnZoom_ex_pressed();
            btnZoom_ex_selected();
        }
        else if(ui->btnNuc_ex->hasFocus())
        {
            on_btnNuc_ex_released();
            btnNuc_ex_selected();
        }
        else if(ui->btnPolarity_ex->hasFocus())
        {
            on_btnPolarity_ex_pressed();
            btnPolarity_ex_selected();
        }
        else if(ui->btnPantilt_ex->hasFocus())
        {
            on_btnPantilt_ex_pressed();
            btnPantilt_ex_selected();
        }
        else if(ui->btnScreenshot->hasFocus())
        {
            on_btnScreenshot_released();
            btnScreenshot_selected();
        }
        else if(ui->btnBack->hasFocus())
        {
            on_btnBack_released();
        }
    }

    else if(_fullExp == false)
    {
        if(ui->btnDayir->hasFocus())
        {
            on_btnDayir_pressed();
            btnDayir_selected();
        }
        else if(ui->btnPantilt->hasFocus())
        {
            on_btnPantilt_pressed();
            btnPantilt_selected();
        }
        else if(ui->btnLRF->hasFocus())
        {
            on_btnLRF_pressed();
            btnLrf_selected();
        }
        else if(ui->btnZoom->hasFocus())
        {
            on_btnZoom_pressed();
            btnZoom_selected();
        }
        else if(ui->btnChange->hasFocus())
        {
            on_btnChange_released();
            btnChange_selected();
        }
        else if(ui->btnBack->hasFocus())
        {
            on_btnBack_released();
        }
        else if(ui->calculate->hasFocus())
        {
            on_calculate_released();
        }
        else if(ui->correction->hasFocus())
        {
            on_correction_released();
        }

        foreach(QLineEdit* ledit, findChildren<QLineEdit*>())
            if(ledit->hasFocus())
            {
                if(txt_h == "f")
                {
                    showKeyboard();
                    k1_selected();
                    txt_h = "1";
                }
                else if(txt_h == "1")
                {
                    ledit->setText(ledit->text() + "1");
                }
                else if(txt_h == "2")
                {
                    ledit->setText(ledit->text() + "2");
                }
                else if(txt_h == "3")
                {
                    ledit->setText(ledit->text() + "3");
                }
                else if(txt_h == "4")
                {
                    ledit->setText(ledit->text() + "4");
                }
                else if(txt_h == "5")
                {
                    ledit->setText(ledit->text() + "5");
                }
                else if(txt_h == "6")
                {
                    ledit->setText(ledit->text() + "6");
                }
                else if(txt_h == "7")
                {
                    ledit->setText(ledit->text() + "7");
                }
                else if(txt_h == "8")
                {
                    ledit->setText(ledit->text() + "8");
                }
                else if(txt_h == "9")
                {
                    ledit->setText(ledit->text() + "9");
                }
                else if(txt_h == "0")
                {
                    ledit->setText(ledit->text() + "0");
                }
                else if(txt_h == "minus")
                {
                    ledit->setText(ledit->text() + "-");
                }
                else if(txt_h == "del")
                {
                    ledit->backspace();
                }
                else if(txt_h == "dot")
                {
                    ledit->setText(ledit->text() + ".");
                    //txt_h = "f";
                }
            }
    }
}

void Expanded::gpioBtnLeft()
{
    if(_fullExp == true)
    {
        if(ui->btnScreenshot->hasFocus())
        {
            btnScreenshot_released();
            ui->btnPantilt_ex->setFocus();
            btnPantilt_ex_selected();
        }
        else if(ui->btnPantilt_ex->hasFocus())
        {
            if(_pantilt_ex == true)
            {
                btnPantilt_ex_pressed();

                if(_day_ir == true)
                {
                    ui->btnPolarity_ex->setFocus();
                    btnPolarity_ex_selected();
                }
                else if(_day_ir == false)
                {
                    ui->btnZoom_ex->setFocus();
                    btnZoom_ex_selected();
                }
            }
            else
            {
                btnPantilt_ex_released();

                if(_day_ir == true)
                {
                    ui->btnPolarity_ex->setFocus();
                    btnPolarity_ex_selected();
                }
                else if(_day_ir == false)
                {
                    ui->btnZoom_ex->setFocus();
                    btnZoom_ex_selected();
                }
            }
        }
        else if(ui->btnPolarity_ex->hasFocus())
        {
            if(_day_ir == false)
            {
                if(polarity_day == false)
                {
                    btnPolarity_ex_released();
                }
            }
            else if(_day_ir == true)
            {
                if(polarity_ir == false)
                {
                    btnPolarity_ex_released();
                }
            }
            ui->btnNuc_ex->setFocus();
            btnNuc_ex_selected();
        }
        else if(ui->btnNuc_ex->hasFocus())
        {
            btnNuc_ex_released();
            ui->btnZoom_ex->setFocus();
            btnZoom_ex_selected();
        }
        else if(ui->btnZoom_ex->hasFocus())
        {
            btnZoom_ex_released();
            ui->btnDayir_ex->setFocus();
            btnDayir_ex_selected();
        }
    }
    else if(_fullExp == false)
    {
        if(txt_h == "f")
        {
            if(ui->keyboard->isHidden())
            {
                showKeyboard();
            }

            //frame1A
            if(ui->frame1A->isVisible())
            {
                if(ui->Incl_1A->hasFocus())
                {
                    ui->AB_1A->setFocus();
                }
                else if(ui->AB_1A->hasFocus())
                {
                    ui->Dist_1A->setFocus();
                }
                else if(ui->Dist_1A->hasFocus())
                {
                    ui->H_1A->setFocus();
                }
                else if(ui->H_1A->hasFocus())
                {
                    ui->Ay_1a->setFocus();
                }
                else if(ui->Ay_1a->hasFocus())
                {
                    ui->Ax_1a->setFocus();
                }
                else if(ui->Ax_1a->hasFocus())
                    //|| ui->H_1A->hasFocus() || ui->Dist_1A->hasFocus() || ui->AB_1A->hasFocus() || ui->Incl_1A->hasFocus())
                {
                    if(ui->keyboard->isVisible())
                    {
                        k1_selected();
                        txt_h = "1";
                    }
                }
            }

            //frame1B
            else if(ui->frame1B->isVisible())
            {
                if(ui->AD_1B->hasFocus())
                {
                    ui->AC_1B->setFocus();
                }
                else if(ui->AC_1B->hasFocus())
                {
                    ui->AB_1B->setFocus();
                }
                else if(ui->AB_1B->hasFocus())
                {
                    ui->Dy_1B->setFocus();
                }
                else if(ui->Dy_1B->hasFocus())
                {
                    ui->Dx_1B->setFocus();
                }
                else if(ui->Dx_1B->hasFocus())
                {
                    ui->Cy_1B->setFocus();
                }
                else if(ui->Cy_1B->hasFocus())
                {
                    ui->Cx_1B->setFocus();
                }
                else if(ui->Cx_1B->hasFocus())
                {
                    ui->By_1B->setFocus();
                }
                else if(ui->By_1B->hasFocus())
                {
                    ui->Bx_1B->setFocus();
                }
                else if(ui->Bx_1B->hasFocus())
                {
                    ui->Ay_1B->setFocus();
                }
                else if(ui->Ay_1B->hasFocus())
                {
                    ui->Ax_1B->setFocus();
                }
                else if(ui->Ax_1B->hasFocus())
                    //|| ui->Bx_1B->hasFocus() || ui->Cx_1B->hasFocus() || ui->Dx_1B->hasFocus() || ui->AB_1B->hasFocus() || ui->AC_1B->hasFocus() || ui->AD_1B->hasFocus())
                {
                    if(ui->keyboard->isVisible())
                    {
                        k1_selected();
                        txt_h = "1";
                    }
                }
            }

            //frame1C
            else if(ui->frame1C->isVisible())
            {
                if(ui->DistB_1C->hasFocus())
                {
                    ui->DistA_1C->setFocus();
                }
                else if(ui->DistA_1C->hasFocus())
                {
                    ui->By_1C->setFocus();
                }
                else if(ui->By_1C->hasFocus())
                {
                    ui->Bx_1C->setFocus();
                }
                else if(ui->Bx_1C->hasFocus())
                {
                    ui->Ay_1C->setFocus();
                }
                else if(ui->Ay_1C->hasFocus())
                {
                    ui->Ax_1C->setFocus();
                }
                else if(ui->Ax_1C->hasFocus())
                    //|| ui->Bx_1C->hasFocus() || ui->DistA_1C->hasFocus() || ui->DistB_1C->hasFocus())
                {
                    if(ui->keyboard->isVisible())
                    {
                        k1_selected();
                        txt_h = "1";
                    }
                }
            }

            //frame2
            else if(ui->frame2->isVisible())
            {
                if(ui->By_2->hasFocus())
                {
                    ui->Bx_2->setFocus();
                }
                else if(ui->Bx_2->hasFocus())
                {
                    ui->Ay_2->setFocus();
                }
                else if(ui->Ay_2->hasFocus())
                {
                    ui->Ax_2->setFocus();
                }
                else if(ui->Ax_2->hasFocus())
                    //|| ui->Bx_2->hasFocus())
                {
                    if(ui->keyboard->isVisible())
                    {
                        k1_selected();
                        txt_h = "1";
                    }
                }
            }

            //frame3
            else if(ui->frame3->isVisible())
            {
                if(ui->RH_3->hasFocus())
                {
                    ui->Ry_3->setFocus();
                }
                else if(ui->Ry_3->hasFocus())
                {
                    ui->Rx_3->setFocus();
                }
                else if(ui->Rx_3->hasFocus())
                {
                    ui->TH_3->setFocus();
                }
                else if(ui->TH_3->hasFocus())
                {
                    ui->Ty_3->setFocus();
                }
                else if(ui->Ty_3->hasFocus())
                {
                    ui->Tx_3->setFocus();
                }
                else if(ui->Tx_3->hasFocus())
                    //|| ui->TH_3->hasFocus() || ui->Rx_3->hasFocus() || ui->RH_3->hasFocus())
                {
                    if(ui->keyboard->isVisible())
                    {
                        k1_selected();
                        txt_h = "1";
                    }
                }
            }
        }

        else if(ui->btnPantilt->hasFocus())
        {
            if(_pantilt == true)
            {
                btnPantilt_pressed();
                ui->btnDayir->setFocus();
                btnDayir_selected();
            }
            else
            {
                btnPantilt_released();
                ui->btnDayir->setFocus();
                btnDayir_selected();
            }
        }
        else if(ui->btnZoom->hasFocus())
        {
            btnZoom_released();
            ui->btnLRF->setFocus();
            btnLrf_selected();
        }
        else if(ui->btnChange->hasFocus())
        {
            btnChange_released();
            ui->btnPantilt->setFocus();
            btnPantilt_selected();
        }
        else if(txt_h == "del")
        {
            k_del_released();
            k_dot_selected();
            txt_h = "dot";
        }
        else if(txt_h == "dot")
        {
            k_dot_released();
            k0_selected();
            txt_h = "0";
        }
        else if(txt_h == "0")
        {
            k0_released();
            k_minus_selected();
            txt_h = "minus";
        }
        else if(txt_h == "minus")
        {
            k_minus_released();
            k9_selected();
            txt_h = "9";
        }
        else if(txt_h == "9")
        {
            k9_released();
            k8_selected();
            txt_h = "8";
        }
        else if(txt_h == "8")
        {
            k8_released();
            k7_selected();
            txt_h = "7";
        }
        else if(txt_h == "7")
        {
            k7_released();
            k6_selected();
            txt_h = "6";
        }
        else if(txt_h == "6")
        {
            k6_released();
            k5_selected();
            txt_h = "5";
        }
        else if(txt_h == "5")
        {
            k5_released();
            k4_selected();
            txt_h = "4";
        }
        else if(txt_h == "4")
        {
            k4_released();
            k3_selected();
            txt_h = "3";
        }
        else if(txt_h == "3")
        {
            k3_released();
            k2_selected();
            txt_h = "2";
        }
        else if(txt_h == "2")
        {
            k2_released();
            k1_selected();
            txt_h = "1";
        }
        else if(txt_h == "1")
        {
            if(ui->keyboard->isVisible())
            {
                k1_released();
                ui->keyboard->hide();
                ui->btnZoom->setFocus();
                btnZoom_selected();
            }
        }
    }
}

void Expanded::gpioBtnRight()
{
    if(_fullExp == true)
    {
        if(ui->btnDayir_ex->hasFocus())
        {
            if(_day_ir == true)
            {
                btnDayir_ex_pressed();

                ui->btnZoom_ex->setFocus();
                btnZoom_ex_selected();
            }
            else
            {
                btnDayir_ex_released();
                ui->btnZoom_ex->setFocus();
                btnZoom_ex_selected();
            }
        }
        else if(ui->btnZoom_ex->hasFocus())
        {
            btnZoom_ex_released();
            if(_day_ir == true)
            {
                ui->btnNuc_ex->setFocus();
                btnNuc_ex_selected();
            }
            else if(_day_ir == false)
            {
                ui->btnPantilt_ex->setFocus();
                btnPantilt_ex_selected();
            }
        }
        else if(ui->btnNuc_ex->hasFocus())
        {
            btnNuc_ex_released();
            ui->btnPolarity_ex->setFocus();
            btnPolarity_ex_selected();
        }
        else if(ui->btnPolarity_ex->hasFocus())
        {
            if(_day_ir == false)
            {
                if(polarity_day == false)
                {
                    btnPolarity_ex_released();
                }
            }
            else if(_day_ir == true)
            {
                if(polarity_ir == false)
                {
                    btnPolarity_ex_released();
                }
            }
            ui->btnPantilt_ex->setFocus();
            btnPantilt_ex_selected();
        }
        else if(ui->btnPantilt_ex->hasFocus())
        {
            if(_pantilt_ex == true)
            {
                btnPantilt_ex_pressed();

                ui->btnScreenshot->setFocus();
                btnScreenshot_selected();
            }
            else
            {
                btnPantilt_ex_released();
                ui->btnScreenshot->setFocus();
                btnScreenshot_selected();
            }
        }
    }

    else if(_fullExp == false)
    {
        if(ui->btnDayir->hasFocus())
        {
            if(_ir == true)
            {
                btnDayir_pressed();
                ui->btnPantilt->setFocus();
                btnPantilt_selected();
            }
            else
            {
                btnDayir_released();
                ui->btnPantilt->setFocus();
                btnPantilt_selected();
            }
        }
        else if(ui->btnLRF->hasFocus())
        {
            btnLrf_released();
            ui->btnZoom->setFocus();
            btnZoom_selected();
        }
        else if(ui->btnPantilt->hasFocus())
        {
            if(_pantilt == true)
            {
                btnPantilt_pressed();
                ui->btnChange->setFocus();
                btnChange_selected();
            }
            else
            {
                btnPantilt_released();
                ui->btnChange->setFocus();
                btnChange_selected();
            }
        }
        else if(ui->btnZoom->hasFocus())
        {
            btnZoom_released();
            ui->btnChange->setFocus();
            btnChange_selected();
        }
        else if(ui->btnChange->hasFocus())
        {
            btnChange_released();

            if(ui->frame1A->isVisible())
            {
                ui->Ax_1a->setFocus();
                showKeyboard();
            }
            else if(ui->frame1B->isVisible())
            {
                ui->Ax_1B->setFocus();
                showKeyboard();
            }
            else if(ui->frame1C->isVisible())
            {
                ui->Ax_1C->setFocus();
                showKeyboard();
            }
            else if(ui->frame2->isVisible())
            {
                ui->Ax_2->setFocus();
                showKeyboard();
            }
            else if(ui->frame3->isVisible())
            {
                ui->Tx_3->setFocus();
                showKeyboard();
            }
            txt_h = "f";
        }
        //frame1A
        else if(txt_h == "f")
        {
            if(ui->keyboard->isHidden())
            {
                showKeyboard();
            }

            if(ui->Ax_1a->hasFocus())
            {
                ui->Ay_1a->setFocus();
            }
            else if(ui->Ay_1a->hasFocus())
            {
                ui->H_1A->setFocus();
            }
            else if(ui->H_1A->hasFocus())
            {
                ui->Dist_1A->setFocus();
            }
            else if(ui->Dist_1A->hasFocus())
            {
                ui->AB_1A->setFocus();
            }
            else if(ui->AB_1A->hasFocus())
            {
                ui->Incl_1A->setFocus();
            }

            //frame1B
            else if(ui->Ax_1B->hasFocus())
            {
                ui->Ay_1B->setFocus();
            }
            else if(ui->Ay_1B->hasFocus())
            {
                ui->Bx_1B->setFocus();
            }
            else if(ui->Bx_1B->hasFocus())
            {
                ui->By_1B->setFocus();
            }
            else if(ui->By_1B->hasFocus())
            {
                ui->Cx_1B->setFocus();
            }
            else if(ui->Cx_1B->hasFocus())
            {
                ui->Cy_1B->setFocus();
            }
            else if(ui->Cy_1B->hasFocus())
            {
                ui->Dx_1B->setFocus();
            }
            else if(ui->Dx_1B->hasFocus())
            {
                ui->Dy_1B->setFocus();
            }
            else if(ui->Dy_1B->hasFocus())
            {
                ui->AB_1B->setFocus();
            }
            else if(ui->AB_1B->hasFocus())
            {
                ui->AC_1B->setFocus();
            }
            else if(ui->AC_1B->hasFocus())
            {
                ui->AD_1B->setFocus();
            }
            //frame1C
            else if(ui->Ax_1C->hasFocus())
            {
                ui->Ay_1C->setFocus();
            }
            else if(ui->Ay_1C->hasFocus())
            {
                ui->Bx_1C->setFocus();
            }
            else if(ui->Bx_1C->hasFocus())
            {
                ui->By_1C->setFocus();
            }
            else if(ui->By_1C->hasFocus())
            {
                ui->DistA_1C->setFocus();
            }
            else if(ui->DistA_1C->hasFocus())
            {
                ui->DistB_1C->setFocus();
            }
            //frame2
            else if(ui->Ax_2->hasFocus())
            {
                ui->Ay_2->setFocus();
            }
            else if(ui->Ay_2->hasFocus())
            {
                ui->Bx_2->setFocus();
            }
            else if(ui->Bx_2->hasFocus())
            {
                ui->By_2->setFocus();
            }
            //frame3
            else if(ui->Tx_3->hasFocus())
            {
                ui->Ty_3->setFocus();
            }
            else if(ui->Ty_3->hasFocus())
            {
                ui->TH_3->setFocus();
            }
            else if(ui->TH_3->hasFocus())
            {
                ui->Rx_3->setFocus();
            }
            else if(ui->Rx_3->hasFocus())
            {
                ui->Ry_3->setFocus();
            }
            else if(ui->Ry_3->hasFocus())
            {
                ui->RH_3->setFocus();
            }
        }
        //keyboard
        else if(txt_h == "1")
        {
            k1_released();
            k2_selected();
            txt_h = "2";
        }
        else if(txt_h == "2")
        {
            k2_released();
            k3_selected();
            txt_h = "3";
        }
        else if(txt_h == "3")
        {
            k3_released();
            k4_selected();
            txt_h = "4";
        }
        else if(txt_h == "4")
        {
            k4_released();
            k5_selected();
            txt_h = "5";
        }
        else if(txt_h == "5")
        {
            k5_released();
            k6_selected();
            txt_h = "6";
        }
        else if(txt_h == "6")
        {
            k6_released();
            k7_selected();
            txt_h = "7";
        }
        else if(txt_h == "7")
        {
            k7_released();
            k8_selected();
            txt_h = "8";
        }
        else if(txt_h == "8")
        {
            k8_released();
            k9_selected();
            txt_h = "9";
        }
        else if(txt_h == "9")
        {
            k9_released();
            k_minus_selected();
            txt_h = "minus";
        }
        else if(txt_h == "minus")
        {
            k_minus_released();
            k0_selected();
            txt_h = "0";
        }
        else if(txt_h == "0")
        {
            k0_released();
            k_dot_selected();
            txt_h = "dot";
        }
        else if(txt_h == "dot")
        {
            k_dot_released();
            k_del_selected();
            txt_h = "del";
        }
        else if(txt_h == "del")
        {
            k_del_released();
            txt_h = "f";

            foreach(QLineEdit* ledit, findChildren<QLineEdit*>())
                if(ledit->hasFocus())
                {
                    ledit->setFocus();
                }
        }
    }
}

void Expanded::gpioBtnUp()
{
    if(_fullExp == true)
    {
        if(ui->btnBack->hasFocus())
        {
            btnBack_released();
            ui->btnDayir_ex->setFocus();
            btnDayir_ex_selected();
        }
    }

    else if(_fullExp == false)
    {
        if(txt_h == "f")
        {
            if(ui->keyboard->isHidden())
            {
                showKeyboard();
            }

            //frame1A
            if(ui->frame1A->isVisible())
            {
                if(ui->Incl_1A->hasFocus())
                {
                    ui->AB_1A->setFocus();
                }
                else if(ui->AB_1A->hasFocus())
                {
                    ui->Dist_1A->setFocus();
                }
                else if(ui->Dist_1A->hasFocus())
                {
                    ui->H_1A->setFocus();
                }
                else if(ui->H_1A->hasFocus())
                {
                    ui->Ax_1a->setFocus();
                }
                else if(ui->Dy_1B->hasFocus())
                {
                    ui->Cy_1B->setFocus();
                }
                else if(ui->Cy_1B->hasFocus())
                {
                    ui->By_1B->setFocus();
                }
                else if(ui->By_1B->hasFocus())
                {
                    ui->Ay_1B->setFocus();
                }
                else if(ui->calculate->hasFocus())
                {
                    k_calc_released();
                    ui->Incl_1A->setFocus();
                }
            }

            //frame1B
            else if(ui->frame1B->isVisible())
            {
                if(ui->AD_1B->hasFocus())
                {
                    ui->AC_1B->setFocus();
                }
                else if(ui->AC_1B->hasFocus())
                {
                    ui->AB_1B->setFocus();
                }
                else if(ui->AB_1B->hasFocus())
                {
                    ui->Dx_1B->setFocus();
                }
                else if(ui->Dx_1B->hasFocus())
                {
                    ui->Cx_1B->setFocus();
                }
                else if(ui->Cx_1B->hasFocus())
                {
                    ui->Bx_1B->setFocus();
                }
                else if(ui->Bx_1B->hasFocus())
                {
                    ui->Ax_1B->setFocus();
                }
                else if(ui->calculate->hasFocus())
                {
                    k_calc_released();
                    ui->AD_1B->setFocus();
                }
            }

            //frame1C
            else if(ui->frame1C->isVisible())
            {
                if(ui->DistB_1C->hasFocus())
                {
                    ui->DistA_1C->setFocus();
                }
                else if(ui->DistA_1C->hasFocus())
                {
                    ui->Bx_1C->setFocus();
                }
                else if(ui->Bx_1C->hasFocus())
                {
                    ui->Ax_1C->setFocus();
                }
                else if(ui->By_1C->hasFocus())
                {
                    ui->Ay_1C->setFocus();
                }
                else if(ui->calculate->hasFocus())
                {
                    k_calc_released();
                    ui->DistB_1C->setFocus();
                }
            }

            //frame2
            else if(ui->frame2->isVisible())
            {
                if(ui->Bx_2->hasFocus())
                {
                    ui->Ax_2->setFocus();
                }
                else if(ui->By_2->hasFocus())
                {
                    ui->Ay_2->setFocus();
                }
                else if(ui->calculate->hasFocus())
                {
                    k_calc_released();
                    ui->Bx_2->setFocus();
                }
            }

            //frame3
            else if(ui->frame3->isVisible())
            {
                if(ui->RH_3->hasFocus())
                {
                    ui->Rx_3->setFocus();
                }
                else if(ui->Rx_3->hasFocus() ||ui->Ry_3->hasFocus())
                {
                    ui->TH_3->setFocus();
                }
                else if(ui->TH_3->hasFocus())
                {
                    ui->Tx_3->setFocus();
                }
                else if(ui->calculate->hasFocus() || ui->correction->hasFocus())
                {
                    k_calc_released();
                    k_correction_released();
                    ui->RH_3->setFocus();
                }
            }
        }
        if(ui->btnBack->hasFocus())
        {
            btnBack_released();
            ui->btnLRF->setFocus();
            btnLrf_selected();
        }
        else if(ui->btnLRF->hasFocus())
        {
            btnLrf_released();
            ui->btnDayir->setFocus();
            btnDayir_selected();
        }
        else if(ui->btnZoom->hasFocus())
        {
            btnZoom_released();
            ui->btnPantilt->setFocus();
            btnPantilt_selected();
        }
    }
}

void Expanded::gpioBtnDown()
{
    if(_fullExp == true)
    {
        if(ui->btnPantilt_ex->hasFocus())
        {
            btnPantilt_ex_released();
            ui->btnBack->setFocus();
            btnBack_selected();
        }
        else if(ui->btnDayir_ex->hasFocus())
        {
            if(_day_ir == true)
            {
                btnDayir_ex_pressed();
                ui->btnBack->setFocus();
                btnBack_selected();
            }
            else
            {
                btnDayir_ex_released();
                ui->btnBack->setFocus();
                btnBack_selected();
            }
        }
        else if(ui->btnZoom_ex->hasFocus())
        {
            btnZoom_ex_released();
            ui->btnBack->setFocus();
            btnBack_selected();
        }
        else if(ui->btnNuc_ex->hasFocus())
        {
            btnNuc_ex_released();
            ui->btnBack->setFocus();
            btnBack_selected();
        }
        else if(ui->btnPolarity_ex->hasFocus())
        {
            if(_day_ir == false)
            {
                if(polarity_day == false)
                {
                    btnPolarity_ex_released();
                }
            }
            else if(_day_ir == true)
            {
                if(polarity_ir == false)
                {
                    btnPolarity_ex_released();
                }
            }
            ui->btnBack->setFocus();
            btnBack_selected();
        }
        else if(ui->btnScreenshot->hasFocus())
        {
            btnScreenshot_released();
            ui->btnBack->setFocus();
            btnBack_selected();
        }
    }
    else if(_fullExp == false)
    {
        if(txt_h == "f")
        {
            if(ui->keyboard->isHidden())
            {
                showKeyboard();
            }

            //frame1A
            if(ui->frame1A->isVisible())
            {
                if(ui->Ax_1a->hasFocus() || ui->Ay_1a->hasFocus())
                {
                    ui->H_1A->setFocus();
                }
                else if(ui->H_1A->hasFocus())
                {
                    ui->Dist_1A->setFocus();
                }
                else if(ui->Dist_1A->hasFocus())
                {
                    ui->AB_1A->setFocus();
                }
                else if(ui->AB_1A->hasFocus())
                {
                    ui->Incl_1A->setFocus();
                }
                else if(ui->Incl_1A->hasFocus())
                {
                    ui->calculate->setFocus();
                    k_calc_selected();
                    ui->keyboard->hide();
                }
                else if(ui->calculate->hasFocus())
                {
                    ui->keyboard->hide();
                }
            }

            //frame1B
            else if(ui->frame1B->isVisible())
            {
                if(ui->Ax_1B->hasFocus())
                {
                    ui->Bx_1B->setFocus();
                }
                else if(ui->Bx_1B->hasFocus())
                {
                    ui->Cx_1B->setFocus();
                }
                else if(ui->Cx_1B->hasFocus())
                {
                    ui->Dx_1B->setFocus();
                }
                else if(ui->Ay_1B->hasFocus())
                {
                    ui->By_1B->setFocus();
                }
                else if(ui->By_1B->hasFocus())
                {
                    ui->Cy_1B->setFocus();
                }
                else if(ui->Cy_1B->hasFocus())
                {
                    ui->Dy_1B->setFocus();
                }
                else if(ui->Dx_1B->hasFocus() || ui->Dy_1B->hasFocus())
                {
                    ui->AB_1B->setFocus();
                }
                else if(ui->AB_1B->hasFocus())
                {
                    ui->AC_1B->setFocus();
                }
                else if(ui->AC_1B->hasFocus())
                {
                    ui->AD_1B->setFocus();
                }
                else if(ui->AD_1B->hasFocus())
                {
                    ui->calculate->setFocus();
                    k_calc_selected();
                    ui->keyboard->hide();
                }
                else if(ui->calculate->hasFocus())
                {
                    ui->keyboard->hide();
                }
            }

            //frame1C
            else if(ui->frame1C->isVisible())
            {
                if(ui->Ax_1C->hasFocus())
                {
                    ui->Bx_1C->setFocus();
                }
                else if(ui->Ay_1C->hasFocus())
                {
                    ui->By_1C->setFocus();
                }
                else if(ui->Bx_1C->hasFocus() || ui->By_1C->hasFocus())
                {
                    ui->DistA_1C->setFocus();
                }
                else if(ui->DistA_1C->hasFocus())
                {
                    ui->DistB_1C->setFocus();
                }
                else if(ui->DistB_1C->hasFocus())
                {
                    ui->calculate->setFocus();
                    k_calc_selected();
                    ui->keyboard->hide();
                }
                else if(ui->calculate->hasFocus())
                {
                    ui->keyboard->hide();
                }
            }

            //frame2
            else if(ui->frame2->isVisible())
            {
                if(ui->Ax_2->hasFocus())
                {
                    ui->Bx_2->setFocus();
                }
                else if(ui->Ay_2->hasFocus())
                {
                    ui->By_2->setFocus();
                }
                else if(ui->Bx_2->hasFocus() || ui->By_2->hasFocus())
                {
                    ui->calculate->setFocus();
                    k_calc_selected();
                    ui->keyboard->hide();
                }
                else if(ui->calculate->hasFocus())
                {
                    ui->keyboard->hide();
                }
            }

            //frame3
            else if(ui->frame3->isVisible())
            {
                if(ui->Tx_3->hasFocus() || ui->Ty_3->hasFocus())
                {
                    ui->TH_3->setFocus();
                }
                else if(ui->TH_3->hasFocus())
                {
                    ui->Rx_3->setFocus();
                }
                else if(ui->Rx_3->hasFocus() || ui->Ry_3->hasFocus())
                {
                    ui->RH_3->setFocus();
                }
                else if(ui->RH_3->hasFocus())
                {
                    if(ui->calculate->isVisible())
                    {
                        ui->calculate->setFocus();
                        k_calc_selected();
                    }
                    else if(ui->correction->isVisible())
                    {
                        ui->correction->setFocus();
                        k_correction_selected();
                    }
                    ui->keyboard->hide();
                }
                else if(ui->calculate->hasFocus() || ui->correction->hasFocus())
                {
                    ui->keyboard->hide();
                }
            }
        }
        if(ui->btnDayir->hasFocus())
        {
            if(_ir == true)
            {
                btnDayir_pressed();
            }
            else
            {
                btnDayir_released();
            }
            ui->btnLRF->setFocus();
            btnLrf_selected();
        }
        else if(ui->btnPantilt->hasFocus())
        {
            if(_pantilt == true)
            {
                btnPantilt_pressed();
            }
            else
            {
                btnPantilt_released();
            }
            ui->btnZoom->setFocus();
            btnZoom_selected();
        }
        else if(ui->btnLRF->hasFocus())
        {
            btnLrf_released();
            ui->btnBack->setFocus();
            btnBack_selected();
        }

        else if(ui->btnZoom->hasFocus())
        {
            btnZoom_released();
            ui->btnBack->setFocus();
            btnBack_selected();
        }
        else if(ui->btnChange->hasFocus())
        {
            btnChange_released();
            if(ui->frame1A->isVisible())
            {
                ui->Ax_1a->setFocus();
                showKeyboard();
            }
            else if(ui->frame1B->isVisible())
            {
                ui->Ax_1B->setFocus();
                showKeyboard();
            }
            else if(ui->frame1C->isVisible())
            {
                ui->Ax_1C->setFocus();
                showKeyboard();
            }
            else if(ui->frame2->isVisible())
            {
                ui->Ax_2->setFocus();
                showKeyboard();
            }
            else if(ui->frame3->isVisible())
            {
                ui->Tx_3->setFocus();
                showKeyboard();
            }
            txt_h = "f";
        }
    }
}

void Expanded::checkIrZoom_ex()
{
    if(ir_zoom == "1X")
    {
        hikVision->makeZoom(2);
        ui->btnZoom_ex->setIcon(*zoom2x_ex);
        ir_zoom = "2X";
    }
    else if(ir_zoom == "2X")
    {
        hikVision->makeZoom(3);
        ui->btnZoom_ex->setIcon(*zoom4x_ex);
        ir_zoom = "4X";
    }
    else if (ir_zoom == "4X")
    {
        hikVision->makeZoom(4);
        ui->btnZoom_ex->setIcon(*zoom8x_ex);
        ir_zoom = "8X";
    }
    else if (ir_zoom == "8X")
    {
        hikVision->makeZoom(1);
        ui->btnZoom_ex->setIcon(*zoom1x_ex);
        ir_zoom = "1X";
    }
}

void Expanded::checkDayZoom_ex()
{
    if(day_zoom == "1X")
    {
        SetZoomDayCam(2);
        ui->btnZoom_ex->setIcon(*zoom2x_ex);
        day_zoom = "2X";
    }
    else if(day_zoom == "2X")
    {
        SetZoomDayCam(4);
        ui->btnZoom_ex->setIcon(*zoom4x_ex);
        day_zoom = "4X";
    }
    else if (day_zoom == "4X")
    {
        SetZoomDayCam(8);
        ui->btnZoom_ex->setIcon(*zoom8x_ex);
        day_zoom = "8X";
    }
    else if (day_zoom == "8X")
    {
        SetZoomDayCam(16);
        ui->btnZoom_ex->setIcon(*zoom16x_ex);
        day_zoom = "16X";
    }
    else if (day_zoom == "16X")
    {
        SetZoomDayCam(1);
        ui->btnZoom_ex->setIcon(*zoom1x_ex);
        day_zoom = "1X";
    }
}

void Expanded::checkIrZoom()
{
    if(ir_zoom == "1X")
    {
        hikVision->makeZoom(2);
        ui->btnZoom->setIcon(*zoom2x_ex);
        ir_zoom = "2X";
    }
    else if(ir_zoom == "2X")
    {
        hikVision->makeZoom(3);
        ui->btnZoom->setIcon(*zoom4x_ex);
        ir_zoom = "4X";
    }
    else if (ir_zoom == "4X")
    {
        hikVision->makeZoom(4);
        ui->btnZoom->setIcon(*zoom8x_ex);
        ir_zoom = "8X";
    }
    else if (ir_zoom == "8X")
    {
        hikVision->makeZoom(1);
        ui->btnZoom->setIcon(*zoom1x_ex);
        ir_zoom = "1X";
    }
}

void Expanded::checkDayZoom()
{
    if(day_zoom == "1X")
    {
        SetZoomDayCam(2);
        ui->btnZoom->setIcon(*zoom2x_ex);
        day_zoom = "2X";
    }
    else if(day_zoom == "2X")
    {
        SetZoomDayCam(4);
        ui->btnZoom->setIcon(*zoom4x_ex);
        day_zoom = "4X";
    }
    else if (day_zoom == "4X")
    {
        SetZoomDayCam(8);
        ui->btnZoom->setIcon(*zoom8x_ex);
        day_zoom = "8X";
    }
    else if (day_zoom == "8X")
    {
        SetZoomDayCam(16);
        ui->btnZoom->setIcon(*zoom16x_ex);
        day_zoom = "16X";
    }
    else if (day_zoom == "16X")
    {
        SetZoomDayCam(1);
        ui->btnZoom->setIcon(*zoom1x_ex);
        day_zoom = "1X";
    }
}


void Expanded::on_btnInfo_released()
{
    if(ui->frame1A->isVisible())
    {
        task1AInfo();
    }
    else if(ui->frame1B->isVisible())
    {
        task1BInfo();
    }
    else if(ui->frame1C->isVisible())
    {
        task1CInfo();
    }
    else if(ui->frame2->isVisible())
    {
        task2Info();
    }
    else if(ui->frame3->isVisible())
    {
        task3Info();
    }
}


void Expanded::task1AInfo()
{
    ui->task_pixmap->clear();
    QPixmap p = QPixmap(":/new/prefix1/icons/1A.png");
    int w = ui->task_pixmap->width();
    int h = ui->task_pixmap->height();
    ui->task_pixmap->setPixmap(p.scaled(w,h,Qt::KeepAspectRatio));
    ui->grBoxPixmap->setGeometry(0,0,1280,800);
    ui->grBoxPixmap->show();

    if(flgBG_ex == true)
    {
        ui->lblTaskName->setText(lblTasksTxt_1a_BG);
        ui->lblTaskName->adjustSize();
        ui->lblTaskName->setGeometry((ui->grBoxPixmap->width() - ui->lblTaskName->width())/2,
                                     ui->lblTaskName->geometry().y(),
                                     ui->lblTaskName->width(),
                                     ui->lblTaskName->height());

        ui->lblTaskDescription->setText(lblTaskDescriptionTxt_1a_BG);
        ui->lblTaskDescription->adjustSize();
        ui->lblTaskDescription->setGeometry((ui->grBoxPixmap->width() - ui->lblTaskDescription->width())/2,
                                            ui->lblTaskDescription->geometry().y(),
                                            ui->lblTaskDescription->width(),
                                            ui->lblTaskDescription->height());
    }

    else if(flgBG_ex == false)
    {
        ui->lblTaskName->setText(lblTasksTxt_1a_EN);
        ui->lblTaskName->adjustSize();
        ui->lblTaskName->setGeometry((ui->grBoxPixmap->width() - ui->lblTaskName->width())/2,
                                     ui->lblTaskName->geometry().y(),
                                     ui->lblTaskName->width(),
                                     ui->lblTaskName->height());

        ui->lblTaskDescription->setText(lblTaskDescriptionTxt_1a_EN);
        ui->lblTaskDescription->adjustSize();
        ui->lblTaskDescription->setGeometry((ui->grBoxPixmap->width() - ui->lblTaskDescription->width())/2,
                                            ui->lblTaskDescription->geometry().y(),
                                            ui->lblTaskDescription->width(),
                                            ui->lblTaskDescription->height());
    }
}

void Expanded::task1BInfo()
{
    ui->task_pixmap->clear();
    QPixmap p = QPixmap(":/new/prefix1/icons/1B.png");
    int w = ui->task_pixmap->width();
    int h = ui->task_pixmap->height();
    ui->task_pixmap->setPixmap(p.scaled(w,h,Qt::KeepAspectRatio));
    ui->grBoxPixmap->setGeometry(0,0,1280,800);
    ui->grBoxPixmap->show();

    if(flgBG_ex == true)
    {
        ui->lblTaskName->setText(lblTasksTxt_1b_BG);
        ui->lblTaskName->adjustSize();
        ui->lblTaskName->setGeometry((ui->grBoxPixmap->width() - ui->lblTaskName->width())/2,
                                     ui->lblTaskName->geometry().y(),
                                     ui->lblTaskName->width(),
                                     ui->lblTaskName->height());

        ui->lblTaskDescription->setText(lblTaskDescriptionTxt_1b_BG);
        ui->lblTaskDescription->adjustSize();
        ui->lblTaskDescription->setGeometry((ui->grBoxPixmap->width() - ui->lblTaskDescription->width())/2,
                                            ui->lblTaskDescription->geometry().y(),
                                            ui->lblTaskDescription->width(),
                                            ui->lblTaskDescription->height());
    }
    else if(flgBG_ex == false)
    {
        ui->lblTaskName->setText(lblTasksTxt_1b_EN);
        ui->lblTaskName->adjustSize();
        ui->lblTaskName->setGeometry((ui->grBoxPixmap->width() - ui->lblTaskName->width())/2,
                                     ui->lblTaskName->geometry().y(),
                                     ui->lblTaskName->width(),
                                     ui->lblTaskName->height());

        ui->lblTaskDescription->setText(lblTaskDescriptionTxt_1b_EN);
        ui->lblTaskDescription->adjustSize();
        ui->lblTaskDescription->setGeometry((ui->grBoxPixmap->width() - ui->lblTaskDescription->width())/2,
                                            ui->lblTaskDescription->geometry().y(),
                                            ui->lblTaskDescription->width(),
                                            ui->lblTaskDescription->height());
    }
}

void Expanded::task1CInfo()
{
    ui->task_pixmap->clear();
    QPixmap p = QPixmap(":/new/prefix1/icons/1C.png");
    int w = ui->task_pixmap->width();
    int h = ui->task_pixmap->height();
    ui->task_pixmap->setPixmap(p.scaled(w,h,Qt::KeepAspectRatio));
    ui->grBoxPixmap->setGeometry(0,0,1280,800);
    ui->grBoxPixmap->show();

    if(flgBG_ex == true)
    {
        ui->lblTaskName->setText(lblTasksTxt_1c_BG);
        ui->lblTaskName->adjustSize();
        ui->lblTaskName->setGeometry((ui->grBoxPixmap->width() - ui->lblTaskName->width())/2,
                                     ui->lblTaskName->geometry().y(),
                                     ui->lblTaskName->width(),
                                     ui->lblTaskName->height());

        ui->lblTaskDescription->setText(lblTaskDescriptionTxt_1c_BG);
        ui->lblTaskDescription->adjustSize();
        ui->lblTaskDescription->setGeometry((ui->grBoxPixmap->width() - ui->lblTaskDescription->width())/2,
                                            ui->lblTaskDescription->geometry().y(),
                                            ui->lblTaskDescription->width(),
                                            ui->lblTaskDescription->height());
    }
    else if(flgBG_ex == false)
    {
        ui->lblTaskName->setText(lblTasksTxt_1c_EN);
        ui->lblTaskName->adjustSize();
        ui->lblTaskName->setGeometry((ui->grBoxPixmap->width() - ui->lblTaskName->width())/2,
                                     ui->lblTaskName->geometry().y(),
                                     ui->lblTaskName->width(),
                                     ui->lblTaskName->height());

        ui->lblTaskDescription->setText(lblTaskDescriptionTxt_1c_EN);
        ui->lblTaskDescription->adjustSize();
        ui->lblTaskDescription->setGeometry((ui->grBoxPixmap->width() - ui->lblTaskDescription->width())/2,
                                            ui->lblTaskDescription->geometry().y(),
                                            ui->lblTaskDescription->width(),
                                            ui->lblTaskDescription->height());
    }
}

void Expanded::task2Info()
{
    ui->task_pixmap->clear();
    QPixmap p = QPixmap(":/new/prefix1/icons/2.png");
    int w = ui->task_pixmap->width();
    int h = ui->task_pixmap->height();
    ui->task_pixmap->setPixmap(p.scaled(w,h,Qt::KeepAspectRatio));
    ui->grBoxPixmap->setGeometry(0,0,1280,800);
    ui->grBoxPixmap->show();

    if(flgBG_ex == true)
    {
        ui->lblTaskName->setText(lblTasksTxt_2_BG);
        ui->lblTaskName->adjustSize();
        ui->lblTaskName->setGeometry((ui->grBoxPixmap->width() - ui->lblTaskName->width())/2,
                                     ui->lblTaskName->geometry().y(),
                                     ui->lblTaskName->width(),
                                     ui->lblTaskName->height());

        ui->lblTaskDescription->setText(lblTaskDescriptionTxt_2_BG);
        ui->lblTaskDescription->adjustSize();
        ui->lblTaskDescription->setGeometry((ui->grBoxPixmap->width() - ui->lblTaskDescription->width())/2,
                                            ui->lblTaskDescription->geometry().y(),
                                            ui->lblTaskDescription->width(),
                                            ui->lblTaskDescription->height());
    }
    else if(flgBG_ex == false)
    {
        ui->lblTaskName->setText(lblTasksTxt_2_EN);
        ui->lblTaskName->adjustSize();
        ui->lblTaskName->setGeometry((ui->grBoxPixmap->width() - ui->lblTaskName->width())/2,
                                     ui->lblTaskName->geometry().y(),
                                     ui->lblTaskName->width(),
                                     ui->lblTaskName->height());

        ui->lblTaskDescription->setText(lblTaskDescriptionTxt_2_EN);
        ui->lblTaskDescription->adjustSize();
        ui->lblTaskDescription->setGeometry((ui->grBoxPixmap->width() - ui->lblTaskDescription->width())/2,
                                            ui->lblTaskDescription->geometry().y(),
                                            ui->lblTaskDescription->width(),
                                            ui->lblTaskDescription->height());
    }
}

void Expanded::task3Info()
{
    ui->task_pixmap->clear();
    QPixmap p = QPixmap(":/new/prefix1/icons/3.png");
    int w = ui->task_pixmap->width();
    int h = ui->task_pixmap->height();
    ui->task_pixmap->setPixmap(p.scaled(w,h,Qt::KeepAspectRatio));
    ui->grBoxPixmap->setGeometry(0,0,1280,800);
    ui->grBoxPixmap->show();

    if(flgBG_ex == true)
    {
        ui->lblTaskName->setText(lblTasksTxt_3_BG);
        ui->lblTaskName->adjustSize();
        ui->lblTaskName->setGeometry((ui->grBoxPixmap->width() - ui->lblTaskName->width())/2,
                                     ui->lblTaskName->geometry().y(),
                                     ui->lblTaskName->width(),
                                     ui->lblTaskName->height());
    }
    else if(flgBG_ex == false)
    {
        ui->lblTaskName->setText(lblTasksTxt_3_EN);
        ui->lblTaskName->adjustSize();
        ui->lblTaskName->setGeometry((ui->grBoxPixmap->width() - ui->lblTaskName->width())/2,
                                     ui->lblTaskName->geometry().y(),
                                     ui->lblTaskName->width(),
                                     ui->lblTaskName->height());

        ui->lblTaskDescription->setText(lblTaskDescriptionTxt_3_EN);
        ui->lblTaskDescription->adjustSize();
        ui->lblTaskDescription->setGeometry((ui->grBoxPixmap->width() - ui->lblTaskDescription->width())/2,
                                            ui->lblTaskDescription->geometry().y(),
                                            ui->lblTaskDescription->width(),
                                            ui->lblTaskDescription->height());
    }
}


void Expanded::on_btnClose_pressed()
{
    ui->btnClose->setStyleSheet(
                "background:gray;"
                "border:5px solid black;"
                );
}


void Expanded::on_btnClose_released()
{
    ui->btnClose->setStyleSheet(
                "background:white;"
                "border:5px solid black;"
                );

    ui->grBoxPixmap->hide();
}


void Expanded::on_btnPoints_pressed()
{
    ResultSelection resultSelection;

    resultSelection.setModal(true);
    if(flgBG_ex == true)
    {
        resultSelection.switchToBG();
    }
    else if(flgBG_ex == false)
    {
        resultSelection.switchToEN();
    }
    resultSelection.exec();
}

void Expanded::gpioBtnZoom()
{
    if(_fullExp == true)
    {
        ui->btnZoom->setFocus();
        on_btnZoom_ex_pressed();
        btnZoom_ex_selected();
    }
    else if(_fullExp == false)
    {
        ui->btnZoom->setFocus();
        on_btnZoom_pressed();
        btnZoom_selected();
    }
}

void Expanded::gpioBtnLrf()
{
    ui->btnLRF->setFocus();
    on_btnLRF_pressed();
    on_btnLRF_released();
    btnLrf_selected();
}

void Expanded::gpioBtnPantiltUpPressed()
{
    on_btnPantilt_up_pressed();
}

void Expanded::gpioBtnPantiltDownPressed()
{
    on_btnPantilt_down_pressed();
}

void Expanded::gpioBtnPantiltLeftPressed()
{
    on_btnPantilt_left_pressed();
}

void Expanded::gpioBtnPantiltRightPressed()
{
    on_btnPantilt_right_pressed();
}

void Expanded::gpioBtnPantiltUpReleased()
{
    on_btnPantilt_up_released();
}

void Expanded::gpioBtnPantiltDownReleased()
{
    on_btnPantilt_down_released();
}

void Expanded::gpioBtnPantiltLeftReleased()
{
    on_btnPantilt_left_released();
}

void Expanded::gpioBtnPantiltRightReleased()
{
    on_btnPantilt_right_released();
}

void Expanded::on_btnDirAngleType_pressed()
{
    if(ui->btnDirAngleType->text() == "MIL")
    {
        ui->btnDirAngleType->setText("DEG");

        if(task == 4)
        {
            if(ui->result_text_2->text() != NULL)
            {
                ui->result_text_2->setText(QString().setNum(alfa_deg));
            }
        }
        else if(task == 5)
        {
            if(ui->result_text_5->text() != NULL)
            {
                ui->result_text_5->setText(QString().setNum(alfa_deg));
            }
        }
    }
    else if(ui->btnDirAngleType->text() == "DEG")
    {
        ui->btnDirAngleType->setText("TH");

        if(task == 4)
        {
            if(ui->result_text_2->text() != NULL)
            {
                ui->result_text_2->setText(QString().setNum(alfa_th));
            }
        }
        else if(task == 5)
        {
            if(ui->result_text_5->text() != NULL)
            {
                ui->result_text_5->setText(QString().setNum(alfa_th));
            }
        }
    }
    else if(ui->btnDirAngleType->text() == "TH")
    {
        ui->btnDirAngleType->setText("MIL");

        if(task == 4)
        {
            if(ui->result_text_2->text() != NULL)
            {
                ui->result_text_2->setText(QString().setNum(alfa_mil));
            }
        }
        else if(task == 5)
        {
            if(ui->result_text_5->text() != NULL)
            {
                ui->result_text_5->setText(QString().setNum(alfa_mil));
            }
        }
    }
}

void Expanded::on_btnDirAngleType_1B_pressed()
{
    if(ui->btnDirAngleType_1B->text() == "MIL")
    {
        ui->btnDirAngleType_1B->setText("DEG");
        ui->label_21->setText("(AB),deg");
        ui->label_26->setText("(AC),deg");
        ui->label_27->setText("(AD),deg");
    }
    else if(ui->btnDirAngleType_1B->text() == "DEG")
    {
        ui->btnDirAngleType_1B->setText("TH");
        ui->label_21->setText("(AB),th");
        ui->label_26->setText("(AC),th");
        ui->label_27->setText("(AD),th");
    }
    else if(ui->btnDirAngleType_1B->text() == "TH")
    {
        ui->btnDirAngleType_1B->setText("MIL");
        ui->label_21->setText("(AB),mil");
        ui->label_26->setText("(AC),mil");
        ui->label_27->setText("(AD),mil");
    }
}

void Expanded::on_btnDirAngleType_1A_pressed()
{
    if(ui->btnDirAngleType_1A->text() == "MIL")
    {
        ui->btnDirAngleType_1A->setText("DEG");
        ui->label_7->setText("(AB),deg");
        ui->label_8->setText("(Incl),deg");
    }
    else if(ui->btnDirAngleType_1A->text() == "DEG")
    {
        ui->btnDirAngleType_1A->setText("TH");
        ui->label_7->setText("(AB),th");
        ui->label_8->setText("(Incl),th");
    }
    else if(ui->btnDirAngleType_1A->text() == "TH")
    {
        ui->btnDirAngleType_1A->setText("MIL");
        ui->label_7->setText("(AB),mil");
        ui->label_8->setText("(Incl),mil");
    }
}

void Expanded::on_correction_pressed()
{
    btnLrf_released();
    btnZoom_released();
    btnChange_released();
    btnBack_released();

    k_correction_pressed();
}

void Expanded::on_correction_released()
{
    ui->keyboard->hide();

    //double Sc = 14283.7331580014;
    //double Sc = (double)rdmTarget1;
    //double Lc = gtor(304.152709813702, CF_CODE_DD);
    //double Lc = gtor(double(cdmHeading)/1000, CF_CODE_DD);
    //double Vc = gtor(0.432189288302368, CF_CODE_DD);
    //double Vc = gtor(double(pdmTilt)/1000, CF_CODE_DD);

    XA_parameter_input = ui->Tx_3->text().toDouble();
    YA_parameter_input = ui->Ty_3->text().toDouble();
    H_parameter_input = ui->TH_3->text().toDouble();
    //XB_parameter_input = 4710528.3768;
    //YB_parameter_input = 265823.1609;
    XB_parameter_input = ui->Rx_3->text().toDouble();
    YB_parameter_input = ui->Ry_3->text().toDouble();
    HB_parameter_input = ui->RH_3->text().toDouble();

    if(coordinate_type == "bl")
    {
        checkBeforeTransform();
        transformBeforeTasks_A();
        transformBeforeTasks_B();
        updateInputParameters();
    }
    else
    {
        isTransformed_A = false;
        isTransformed_B = false;
    }

    //double hop = 280;

    xa = XA_parameter_input;
    ya = YA_parameter_input;
    ha = H_parameter_input;
    xop = XB_parameter_input;
    yop = YB_parameter_input;
    hop = HB_parameter_input;

    Calc_Data_For_Target(Sc, Lc, Vc, xa, ya, ha, xop, yop, hop, xp, yp, hp, Dopc, Lopc, dhopc);

    alfa_deg = rtog(Lopc, CF_CODE_DD);
    alfa_mil = alfa_deg * degToMil;
    alfa_th = alfa_deg * degToTh;

    ui->result_text_1->setText(QString::number(xp, 'g', 7));
    ui->result_text_2->setText(QString::number(yp, 'g', 7));
    ui->result_text_3->setText(QString::number(hp));

    ui->result_text_4->setText(QString::number(Dopc));
    if(coordinate_type == "bl")
    {
        ui->result_text_5->setText(QString::number(alfa_deg));
    }
    else if(coordinate_type == "utm")
    {
        ui->result_text_5->setText(QString::number(alfa_mil));
    }
    else if(coordinate_type == "xy")
    {
        ui->result_text_5->setText(QString::number(alfa_th));
    }
    ui->result_text_6->setText(QString::number(dhopc));

    ui->correction->hide();
    ui->calculate->show();
    ui->calculate->setEnabled(false);
    //ui->result->setGeometry(950, 465, 321, 351);

    k_correction_released();
}

void Expanded::updateCoordParameters()
{
    QString cs, ct, pm_z;

    if(coordinate_system == "wgs")
    {
        cs = "NATO(WGS84)";
        if(coordinate_type == "utm")
        {
            ct = "UTM";
            if(zone == "35")
            {
                pm_z = "35";
            }
            else if(zone == "34")
            {
                pm_z = "34";
            }
        }
        else if(coordinate_type == "bl")
        {
            ct = "B,L";
            pm_z = "";
        }
    }
    else if(coordinate_system == "krasovsky")
    {
        cs = "Krasovsky(1942/83)";
        if(coordinate_type == "xy")
        {
            ct = "X,Y";
            if(zone == "27")
            {
                pm_z = "27";
            }
            else if(zone == "21")
            {
                pm_z = "21";
            }
        }
        else if(coordinate_type == "bl")
        {
            ct = "B,L";
            pm_z = "";
        }
    }

    ui->coordInfo->setText("   " + cs + "   " + ct + "   " + pm_z);
}

