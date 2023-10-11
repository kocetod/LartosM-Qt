#include "calibration.h"
#include "ui_calibration.h"

#include "coordinatesystem.h"
#include "ui_coordinatesystem.h"

#include "bg.h"
#include "en.h"

#include "variables.h"

#include <QDesktopWidget>
#include <QTimeLine>
#include <QTouchEvent>
#include <QTimer>

extern "C"
{
    #include "Application/CompassCalibration_PTU.h"
    #include "Configuration/ReadConfig.h"
}

//QTimeLine *timeLine = new QTimeLine(2000);


Calibration::Calibration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Calibration)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    //QCursor cursor(Qt::BlankCursor);
    //QApplication::setOverrideCursor(cursor);
    //QApplication::changeOverrideCursor(cursor);

    setAttribute(Qt::WA_AcceptTouchEvents, true);

    ui->btnTryAgain->hide();
    ui->lblFailed->hide();
    //ui->progressBar->setRange(0, 100);
    ui->progressBar->setRange(0, 11);

    //timeLine->setFrameRange(0, 100);
    //timeLine->setLoopCount(1);
    //connect(timeLine, &QTimeLine::frameChanged, ui->progressBar, &QProgressBar::setValue);
    //timeLine->start();
    //connect(timeLine, SIGNAL(finished()), this, SLOT(openCoordSys()));
    QTimer *timer_calibration = new QTimer(this);
    connect(timer_calibration, SIGNAL(timeout()), this, SLOT(checkStatus()));
    timer_calibration->start(500);

    if(rcSkipCalibration==0)
    {
        RequestCaibrationStart();
    }
}

Calibration::~Calibration()
{
    delete ui;
}

void Calibration::showBtnTryAgain()
{
    //timeLine->stop();
    ui->progressBar->setValue(0);
    ui->lblFailed->show();
    ui->btnTryAgain->show();
}

void Calibration::checkStatus()
{
    ui->progressBar->setValue(cdmCmpCalState);
    if(cdmLastCalResult > 0)
    {
        openCoordSys();
    }
    if(cdmCalibrationAbort == 1)
    {
        showBtnTryAgain();
    }
}

void Calibration::switchToBG()
{
    ui->label->setText(lblSelfTxt_BG);
    ui->label->adjustSize();
    ui->label->setGeometry(
                (this->width() - ui->label->width())/2,
                ui->label->geometry().y(),
                ui->label->width(),
                ui->label->height());
    ui->lblFailed->setText(lblFailedTxt_BG);
    ui->lblFailed->adjustSize();
    ui->lblFailed->setGeometry(
                (this->width() - ui->lblFailed->width())/2,
                ui->lblFailed->geometry().y(),
                ui->lblFailed->width(),
                ui->lblFailed->height());
    ui->btnTryAgain->setText(btnTryAgainTxt_BG);
    ui->btnSkip->setText(btnSkipCalibrationTxt_BG);

    flgBG_c = true;
}

void Calibration::switchToEN()
{
    ui->label->setText(lblSelfTxt_EN);
    ui->label->adjustSize();
    ui->label->setGeometry(
                (this->width() - ui->label->width())/2,
                ui->label->geometry().y(),
                ui->label->width(),
                ui->label->height());
    ui->lblFailed->setText(lblFailedTxt_EN);
    ui->lblFailed->adjustSize();
    ui->lblFailed->setGeometry(
                (this->width() - ui->lblFailed->width())/2,
                ui->lblFailed->geometry().y(),
                ui->lblFailed->width(),
                ui->lblFailed->height());
    ui->btnTryAgain->setText(btnTryAgainTxt_EN);
    ui->btnSkip->setText(btnSkipCalibrationTxt_EN);


    flgBG_c = false;
}

void Calibration::on_btnTryAgain_pressed()
{
    ui->lblFailed->hide();
    ui->btnTryAgain->hide();

    if(rcSkipCalibration==0)
    {
        RequestCaibrationStart();
    }
}


void Calibration::openCoordSys()
{
    this->close();

    CoordinateSystem cs;
    cs.setModal(true);
    cs.showFullScreen();
    //cs.show();
    if(flgBG_c == true)
    {
        cs.switchToBG();
    }
    else if(flgBG_c == false)
    {
        cs.switchToEN();
    }
    cs.exec();
}

void Calibration::on_btnSkip_pressed()
{
    openCoordSys();
}
