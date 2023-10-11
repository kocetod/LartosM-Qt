#include "selfcheck.h"
#include "ui_selfcheck.h"
#include "language.h"

#include <QDesktopWidget>
#include <QThread>
#include <QTimer>
#include <QMovie>

extern "C"
{
    #include "Periph/Diagnostic.h"
}

QTimer* timeout = new QTimer();
QTimer* timer_check = new QTimer();

SelfCheck::SelfCheck(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelfCheck)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    startLoadingAnimation();
    timeout->start(20000);
    timer_check->singleShot(700, this, SLOT(checkGps()));
    connect(timeout, SIGNAL(timeout()), this, SLOT(initializationFailed()));
}

void SelfCheck::startLoadingAnimation()
{
    QMovie *movie = new QMovie(":/new/prefix1/icons/loading.gif");
    movie->setScaledSize(QSize(81,61));
    movie->setSpeed(500);
    ui->day->setMovie(movie);
    ui->ir->setMovie(movie);
    ui->lrf->setMovie(movie);
    ui->gps->setMovie(movie);
    ui->dmc->setMovie(movie);
    ui->pantilt->setMovie(movie);
    movie->start();
}

void SelfCheck::initializationFailed()
{
    if(!isDayCamInitialized)
    {
        ui->day->setStyleSheet("color:red;");
        ui->day->setText("X");
    }

    if(!isThermalCamInitialized)
    {
        ui->ir->setStyleSheet("color:red;");
        ui->ir->setText("X");
    }

    if(!isLrfInitialized)
    {
        ui->lrf->setStyleSheet("color:red;");
        ui->lrf->setText("X");
    }

    if(!isGpsInitialized)
    {
        ui->gps->setStyleSheet("color:red;");
        ui->gps->setText("X");
    }

    if(!isDmcInitialized)
    {
        ui->dmc->setStyleSheet("color:red;");
        ui->dmc->setText("X");
    }

    if(!isPantiltInitialized)
    {
        ui->pantilt->setStyleSheet("color:red;");
        ui->pantilt->setText("X");
    }
}

void SelfCheck::checkDayCam()
{
    if(GetDeviceDiagState(DEV_LUCID_CAM) == DIAG_OK)
    {
        setDayCamInitialized();
    }
    else
    {
        //ui->day->setStyleSheet("color:red;");
        //ui->day->setText("X");
    }
    timer_check->singleShot(700, this, SLOT(checkThermalCam()));
}
void SelfCheck::checkThermalCam()
{
    if(GetDeviceDiagState(DEV_HIK_CAM) == DIAG_OK)
    {
        setThermalCamInitialized();
    }
    else
    {
        //ui->ir->setStyleSheet("color:red;");
        //ui->ir->setText("X");
    }
    timer_check->singleShot(400, this, SLOT(checkStatus()));
}
void SelfCheck::checkLrf()
{
    if(GetDeviceDiagState(DEV_RANGEFINDER) == DIAG_OK)
    {
        setLrfInitialized();
    }
    else
    {
        //ui->lrf->setStyleSheet("color:red;");
        //ui->lrf->setText("X");
    }
    timer_check->singleShot(700, this, SLOT(checkPantilt()));
}
void SelfCheck::checkGps()
{
    if(GetDeviceDiagState(DEV_GPS) == DIAG_OK)
    {
        setGpsInitialized();
    }
    else
    {
        //ui->gps->setStyleSheet("color:red;");
        //ui->gps->setText("X");
    }
    timer_check->singleShot(700, this, SLOT(checkDmc()));
}
void SelfCheck::checkDmc()
{
    if(GetDeviceDiagState(DEV_COMPASS) == DIAG_OK)
    {
        setDmcInitialized();
    }
    else
    {
        //ui->dmc->setStyleSheet("color:red;");
        //ui->dmc->setText("X");
    }
    timer_check->singleShot(700, this, SLOT(checkLrf()));
}
void SelfCheck::checkPantilt()
{
    if(GetDeviceDiagState(DEV_PTU) == DIAG_OK)
    {
        setPantiltInitialized();
    }
    else
    {
        //ui->pantilt->setStyleSheet("color:red;");
        //ui->pantilt->setText("X");
    }
    timer_check->singleShot(700, this, SLOT(checkDayCam()));
}

void SelfCheck::openLangWindow()
{
    this->close();

    Language lang;
    lang.setModal(true);
    //lang.showFullScreen();
    lang.show();
    lang.exec();
}
void SelfCheck::checkStatus()
{
    if(isDayCamInitialized && isThermalCamInitialized && isLrfInitialized && isGpsInitialized && isDmcInitialized && isPantiltInitialized)
    {
        openLangWindow();
    }
    else
    {
        timer_check->singleShot(700, this, SLOT(checkGps()));
    }
}

void SelfCheck::setDayCamInitialized()
{
    ui->day->setStyleSheet("color:green;");
    ui->day->setText("✓");
    isDayCamInitialized = true;
    //checkStatus();
}
void SelfCheck::setThermalCamInitialized()
{
    ui->ir->setStyleSheet("color:green;");
    ui->ir->setText("✓");
    isThermalCamInitialized = true;
    //checkStatus();
}
void SelfCheck::setLrfInitialized()
{
    ui->lrf->setStyleSheet("color:green;");
    ui->lrf->setText("✓");
    isLrfInitialized = true;
    //checkStatus();
}
void SelfCheck::setGpsInitialized()
{
    ui->gps->setStyleSheet("color:green;");
    ui->gps->setText("✓");
    isGpsInitialized = true;
    //checkStatus();
}
void SelfCheck::setDmcInitialized()
{
    ui->dmc->setStyleSheet("color:green;");
    ui->dmc->setText("✓");
    isDmcInitialized = true;
    //checkStatus();
}
void SelfCheck::setPantiltInitialized()
{
    ui->pantilt->setStyleSheet("color:green;");
    ui->pantilt->setText("✓");
    isPantiltInitialized = true;
    //checkStatus();
}

SelfCheck::~SelfCheck()
{
    delete ui;
}
