#include "mainwindowhead.h"
#include "ui_mainwindowhead.h"
#include "Hik/CaptureThread.h"
#include "Hik/Controller.h"
#include "variables.h"

#include <QDesktopWidget>
#include <QScreen>
#include <QDir>

extern "C"
{
#include "Periph/HikCameraDraw.h"
#include "Periph/LucidCameraDraw.h"
#include "Periph/Rangefinder.h"
}

MainWindowHead::MainWindowHead(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindowHead)
{
    ui->setupUi(this);

    if(GetSelectedCamera()==THERMALCAM)
    {
        SelectCamera(DAYCAM);
    }

    currentVideoPanelX = 790;
    currentVideoPanelY = 630;
    currentVideoPanel = ui->frameLabel;
    connect(thermController->processingThread,SIGNAL(newFrame(QPixmap)),this,SLOT(updateFrame(QPixmap)));
}

MainWindowHead::~MainWindowHead()
{
    delete ui;
}

QIcon *zoom1x_head = new QIcon();
QIcon *zoom2x_head = new QIcon();
QIcon *zoom4x_head = new QIcon();
QIcon *zoom8x_head = new QIcon();
QIcon *zoom16x_head = new QIcon();
QIcon *day_head = new QIcon();
QIcon *thermal_head = new QIcon();

void MainWindowHead::updateFrame(const QPixmap &frame)
{
    if(currentVideoPanel==ui->frameLabel)
    {
        ui->frameLabel->setPixmap(frame);
    }
}

void MainWindowHead::setIconPixmap()
{
    zoom1x_head->addPixmap(QPixmap(":/new/prefix1/icons/zoom1.png"), QIcon::Normal, QIcon::On);
    zoom2x_head->addPixmap(QPixmap(":/new/prefix1/icons/zoom2.png"), QIcon::Normal, QIcon::On);
    zoom4x_head->addPixmap(QPixmap(":/new/prefix1/icons/zoom4.png"), QIcon::Normal, QIcon::On);
    zoom8x_head->addPixmap(QPixmap(":/new/prefix1/icons/zoom8.png"), QIcon::Normal, QIcon::On);
    zoom16x_head->addPixmap(QPixmap(":/new/prefix1/icons/zoom16.png"), QIcon::Normal, QIcon::On);
}

void MainWindowHead::setIrZoom()
{
    setIconPixmap();

    if(ir_zoom_head == "1X")
    {
        ui->btnZoom->setIcon(*zoom1x_head);
    }
    else if(ir_zoom_head == "2X")
    {
        ui->btnZoom->setIcon(*zoom2x_head);
    }
    else if(ir_zoom_head == "4X")
    {
        ui->btnZoom->setIcon(*zoom4x_head);
    }
    else if(ir_zoom_head == "8X")
    {
        ui->btnZoom->setIcon(*zoom8x_head);
    }
}

void MainWindowHead::setDayZoom()
{
    setIconPixmap();

    if(day_zoom_head == "1X")
    {
        ui->btnZoom->setIcon(*zoom1x_head);
    }
    else if(day_zoom_head == "2X")
    {
        ui->btnZoom->setIcon(*zoom2x_head);
    }
    else if(day_zoom_head == "4X")
    {
        ui->btnZoom->setIcon(*zoom4x_head);
    }
    else if(day_zoom_head == "8X")
    {
        ui->btnZoom->setIcon(*zoom8x_head);
    }
    else if(day_zoom_head == "16X")
    {
        ui->btnZoom->setIcon(*zoom16x_head);
    }
}

void MainWindowHead::changeZoom()
{
    if(day_ir_head == true)
    {
        checkIrZoom();
    }
    else if(day_ir_head == false)
    {
        checkDayZoom();
    }
}

void MainWindowHead::checkDayZoom()
{
    setIconPixmap();

    if(day_zoom_head == "1X")
    {
        SetZoomDayCam(2);
        ui->btnZoom->setIcon(*zoom2x_head);
        day_zoom_head = "2X";
    }
    else if(day_zoom_head == "2X")
    {
        SetZoomDayCam(4);
        ui->btnZoom->setIcon(*zoom4x_head);
        day_zoom_head = "4X";
    }
    else if (day_zoom_head == "4X")
    {
        SetZoomDayCam(8);
        ui->btnZoom->setIcon(*zoom8x_head);
        day_zoom_head = "8X";
    }
    else if (day_zoom_head == "8X")
    {
        SetZoomDayCam(16);
        ui->btnZoom->setIcon(*zoom16x_head);
        day_zoom_head = "16X";
    }
    else if (day_zoom_head == "16X")
    {
        SetZoomDayCam(1);
        ui->btnZoom->setIcon(*zoom1x_head);
        day_zoom_head = "1X";
    }
}

void MainWindowHead::checkIrZoom()
{
    setIconPixmap();

    if(ir_zoom_head == "1X")
    {
        hikVision->makeZoom(2);
        ui->btnZoom->setIcon(*zoom2x_head);
        ir_zoom_head = "2X";
    }
    else if(ir_zoom_head == "2X")
    {
        hikVision->makeZoom(3);
        ui->btnZoom->setIcon(*zoom4x_head);
        ir_zoom_head = "4X";
    }
    else if (ir_zoom_head == "4X")
    {
        hikVision->makeZoom(4);
        ui->btnZoom->setIcon(*zoom8x_head);
        ir_zoom_head = "8X";
    }
    else if (ir_zoom_head == "8X")
    {
        hikVision->makeZoom(1);
        ui->btnZoom->setIcon(*zoom1x_head);
        ir_zoom_head = "1X";
    }
}

void MainWindowHead::setBrightness()
{
    if(brightness_value_head == "10")
    {
        brightness_value_head = "20";
        SetBrightness(0.2f);
        SetBrightnessThermal(0.2f);
    }
    else if(brightness_value_head == "20")
    {
        brightness_value_head = "30";
        SetBrightness(0.3f);
        SetBrightnessThermal(0.3f);
    }
    else if(brightness_value_head == "30")
    {
        brightness_value_head = "40";
        SetBrightness(0.4f);
        SetBrightnessThermal(0.4f);
    }
    else if(brightness_value_head == "40")
    {
        brightness_value_head = "50";
        SetBrightness(0.5f);
        SetBrightnessThermal(0.5f);
    }
    else if(brightness_value_head == "50")
    {
        brightness_value_head = "60";
        SetBrightness(0.6f);
        SetBrightnessThermal(0.6f);
    }
    else if(brightness_value_head == "60")
    {
        brightness_value_head = "70";
        SetBrightness(0.7f);
        SetBrightnessThermal(0.7f);
    }
    else if(brightness_value_head == "70")
    {
        brightness_value_head = "80";
        SetBrightness(0.8f);
        SetBrightnessThermal(0.8f);
    }
    else if(brightness_value_head == "80")
    {
        brightness_value_head = "90";
        SetBrightness(0.9f);
        SetBrightnessThermal(0.9f);
    }
    else if(brightness_value_head == "90")
    {
        brightness_value_head = "100";
        SetBrightness(1.0f);
        SetBrightnessThermal(1.0f);
    }
    else if(brightness_value_head == "100")
    {
        brightness_value_head = "10";
        SetBrightness(0.1f);
        SetBrightnessThermal(0.1f);
    }
}

void MainWindowHead::makeScreenshot()
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

void MainWindowHead::btnDayir_func()
{
    day_head->addPixmap(QPixmap(":/new/prefix1/icons/day.png"), QIcon::Normal, QIcon::On);
    thermal_head->addPixmap(QPixmap(":/new/prefix1/icons/thermal.png"), QIcon::Normal, QIcon::On);

    if(GetSelectedCamera()==DAYCAM)
    {
        if(SelectCamera(THERMALCAM)==true)
        {
            btnDayir_pressed();

            setIrZoom();
            ui->btnDayIr->setIcon(*thermal_head);

            if(polarity_ir_head == true)
            {
                btnPolarity_pressed();
            }
            else if(polarity_ir_head == false)
            {
                btnPolarity_released();
            }

            day_ir_head = true;
        }
    }
    else if(GetSelectedCamera()==THERMALCAM)
    {
        if(SelectCamera(DAYCAM)==true)
        {
            btnDayir_released();
            setDayZoom();
            ui->btnDayIr->setIcon(*day_head);

            if(polarity_day_head == true)
            {
                btnPolarity_pressed();
            }
            else if(polarity_day_head == false)
            {
                btnPolarity_released();
            }

            day_ir_head = false;
        }
    }
}

void MainWindowHead::btnPolarity_func()
{
    if(day_ir_head == true)
    {
        if(polarity_ir_head == false)
        {
            hikVision->setPolarity(1);
            btnPolarity_pressed();
            polarity_ir_head = true;
        }
        else if(polarity_ir_head == true)
        {
            hikVision->setPolarity(2);
            btnPolarity_released();
            polarity_ir_head = false;
        }
    }
    else if(day_ir_head == false)
    {
        if(polarity_day_head == false)
        {
            btnPolarity_pressed();
            polarity_day_head = true;
        }
        else if(polarity_day_head == true)
        {
            btnPolarity_released();
            polarity_day_head = false;
        }
        SetGrayscaleOn(polarity_day_head);
    }
}

void MainWindowHead::btnBrightness_pressed()
{
    ui->btnBrightScrs->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}
void MainWindowHead::btnBrightness_released()
{
    ui->btnBrightScrs->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );

     setBrightness();
}
void MainWindowHead::btnScreenshot_released()
{ 

    ui->btnBrightScrs->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
        makeScreenshot();
}
void MainWindowHead::btnLrf_pressed()
{
    ui->btnLrf->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
    RfRequestMeasurement();
}
void MainWindowHead::btnLrf_released()
{
    ui->btnLrf->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}
void MainWindowHead::btnOnOff_pressed()
{
    ui->btnOnOff->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}
void MainWindowHead::btnOnOff_released()
{
    ui->btnOnOff->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}

void MainWindowHead::btnDayir_pressed()
{
    ui->btnDayIr->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}

void MainWindowHead::btnPolarity_pressed()
{
    ui->btnPolarity->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );
}
void MainWindowHead::btnPolarity_released()
{
    ui->btnPolarity->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}
void MainWindowHead::btnDayir_released()
{
    ui->btnDayIr->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}
void MainWindowHead::btnZoom_pressed()
{
    ui->btnZoom->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                "color: white;"
                );

    changeZoom();
}
void MainWindowHead::btnZoom_released()
{
    ui->btnZoom->setStyleSheet(
                "border: 2px white; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: white;"
                "color: black;"
                );
}
