#include "language.h"
#include "ui_language.h"
#include "entering.h"
#include "ui_entering.h"

#include <QDebug>
#include <QDesktopWidget>
#include<QTouchEvent>


Language::Language(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Language)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_AcceptTouchEvents, true);

    this->setWindowFlags(Qt::FramelessWindowHint);
    //QCursor cursor(Qt::BlankCursor);
    //QApplication::setOverrideCursor(cursor);
    //QApplication::changeOverrideCursor(cursor);
    ui->label_8->adjustSize();
    ui->label_8->setGeometry(
                (this->width() - ui->label_8->width())/2,
                ui->label_8->geometry().y(),
                ui->label_8->width(),
                ui->label_8->height());

    ui->label_7->adjustSize();
    ui->label_7->setGeometry(
                (this->width() - ui->label_7->width())/2,
                ui->label_7->geometry().y(),
                ui->label_7->width(),
                ui->label_7->height());
}

Language::~Language()
{
    delete ui;
}

void Language::on_btnBG_released()
{
    this->hide();

    Entering e;
    e.setModal(true);
    e.showFullScreen();
    //e.show();
    e.switchToBG();
    e.exec();
}


void Language::on_btnEN_released()
{
    this->hide();

    Entering e;
    e.setModal(true);
    //e.showFullScreen();
    e.show();
    e.switchToEN();
    e.exec();
}

void Language::gpioBtnOk()
{
    if(ui->btnBG->hasFocus())
    {
        on_btnBG_released();
    }
    else if(ui->btnEN->hasFocus())
    {
        on_btnEN_released();
    }
}

void Language::gpioBtnLeft()
{
    if(ui->btnEN->hasFocus())
    {
        ui->btnEN->setIconSize(QSize(360,270));
        ui->btnBG->setFocus();
        ui->btnBG->setIconSize(QSize(310,270));
    }
    else if(ui->btnBG->hasFocus())
    {
        ui->btnBG->setIconSize(QSize(360,270));
        ui->btnEN->setFocus();
        ui->btnEN->setIconSize(QSize(310,270));
    }
}

void Language::gpioBtnRight()
{
    if(ui->btnEN->hasFocus())
    {
        ui->btnEN->setIconSize(QSize(360,270));
        ui->btnBG->setFocus();
        ui->btnBG->setIconSize(QSize(310,270));
    }
    else if(ui->btnBG->hasFocus())
    {
        ui->btnBG->setIconSize(QSize(360,270));
        ui->btnEN->setFocus();
        ui->btnEN->setIconSize(QSize(310,270));
    }
}
