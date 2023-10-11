#include "tasks.h"
#include "ui_tasks.h"

#include "expanded.h"
#include "ui_expanded.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "bg.h"
#include "en.h"
#include <QKeyEvent>
#include "variables.h"

Tasks::Tasks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tasks)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);

    //QCursor cursor(Qt::BlankCursor);
    //QApplication::setOverrideCursor(cursor);
    //QApplication::changeOverrideCursor(cursor);

    setAttribute(Qt::WA_AcceptTouchEvents, true);
    ui->task1A->setFocus();

    if(task == 1)
    {
        ui->task1A->setFocus();
        on_task1A_pressed();
    }
    else if(task == 2)
    {
        ui->task1B->setFocus();
        on_task1B_pressed();
    }
    else if(task == 3)
    {
        ui->task1C->setFocus();
        on_task1C_pressed();
    }
    else if(task == 4)
    {
        ui->task2->setFocus();
        on_task2_pressed();
    }
    else if(task == 5)
    {
        ui->task3->setFocus();
        on_task3_pressed();
    }
}

Tasks::~Tasks()
{
    delete ui;
}

void Tasks::task1a_pressed()
{
    task1a_released();
    task1b_released();
    task1c_released();
    task2_released();
    task3_released();
    btnBack_released();
    btnConfirm_released();

    ui->task1A->setStyleSheet(
                "border: 2px black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: black; "
                "color: white;"
                );
}
void Tasks::task1a_released()
{
    ui->task1A->setStyleSheet(
                "border: 2px rgb(173, 173, 173); "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: rgb(173, 173, 173); "
                "color: black;"
                );
}
void Tasks::task1b_pressed()
{
    task1a_released();
    task1b_released();
    task1c_released();
    task2_released();
    task3_released();
    btnBack_released();
    btnConfirm_released();

    ui->task1B->setStyleSheet(
                "border: 2px black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: black; "
                "color: white;"
                );
}
void Tasks::task1b_released()
{
    ui->task1B->setStyleSheet(
                "border: 2px rgb(173, 173, 173); "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: rgb(173, 173, 173); "
                "color: black;"
                );
}
void Tasks::task1c_pressed()
{
    task1a_released();
    task1b_released();
    task1c_released();
    task2_released();
    task3_released();
    btnBack_released();
    btnConfirm_released();

    ui->task1C->setStyleSheet(
                "border: 2px black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: black; "
                "color: white;"
                );
}
void Tasks::task1c_released()
{
    ui->task1C->setStyleSheet(
                "border: 2px rgb(173, 173, 173); "
                "border-radius: 10px; padding: 0 8px; "
                "background: rgb(173, 173, 173); "
                "color: black;"
                );
}
void Tasks::task2_pressed()
{
    task1a_released();
    task1b_released();
    task1c_released();
    task2_released();
    task3_released();
    btnBack_released();
    btnConfirm_released();

    ui->task2->setStyleSheet(
                "border: 2px black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: black; "
                "color: white;"
                );
}
void Tasks::task2_released()
{
    ui->task2->setStyleSheet(
                "border: 2px rgb(173, 173, 173); "
                "border-radius: 10px; padding: 0 8px; "
                "background: rgb(173, 173, 173); "
                "color: black;"
                );
}
void Tasks::task3_pressed()
{
    task1a_released();
    task1b_released();
    task1c_released();
    task2_released();
    task3_released();
    btnBack_released();
    btnConfirm_released();

    ui->task3->setStyleSheet(
                "border: 2px black; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: black; "
                "color: white;"
                );
}
void Tasks::task3_released()
{
    ui->task3->setStyleSheet(
                "border: 2px rgb(173, 173, 173); "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: rgb(173, 173, 173); "
                "color: black;"
                );
}
void Tasks::btnBack_pressed()
{
    ui->btnBack->setStyleSheet(
                "border: 3px solid black; "
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: gray;"
                );
}
void Tasks::btnBack_released()
{
    ui->btnBack->setStyleSheet(
                "border: 2px rgb(173, 173, 173);"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: rgb(173, 173, 173);"
                );
}

void Tasks::btnConfirm_pressed()
{
    //task1a_released();
    //task1b_released();
    //task1c_released();
    //task2_released();
    //task3_released();
    btnBack_released();
    btnConfirm_released();

    ui->btnConfirm->setStyleSheet(
                "border: 4px solid gray;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: black;"
                "color:white;"
                );
}

void Tasks::btnConfirm_released()
{
    ui->btnConfirm->setStyleSheet(
                "border: 2px black;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "background: black;"
                "color:white;"
                );
}

void Tasks::switchToBG()
{
    ui->label->setText(lblChooseTxt_t_BG);
    ui->label->adjustSize();
    ui->label->setGeometry(
                (this->width() - ui->label->width())/2,
                ui->label->geometry().y(),
                ui->label->width(),
                ui->label->height());

    ui->task1A->setText(lblTask1ATxt_BG);
    ui->task1B->setText(lblTask1BTxt_BG);
    ui->task1C->setText(lblTask1CTxt_BG);
    ui->task2->setText(lblTask2Txt_BG);
    ui->task3->setText(lblTask3Txt_BG);

    ui->btnConfirm->setText(btnConfirmTxt_BG);

    flgBG_t = true;
}

void Tasks::switchToEN()
{
    ui->label->setText(lblChooseTxt_t_EN);
    ui->label->adjustSize();
    ui->label->setGeometry(
                (this->width() - ui->label->width())/2,
                ui->label->geometry().y(),
                ui->label->width(),
                ui->label->height());

    ui->task1A->setText(lblTask1ATxt_EN);
    ui->task1B->setText(lblTask1BTxt_EN);
    ui->task1C->setText(lblTask1CTxt_EN);
    ui->task2->setText(lblTask2Txt_EN);
    ui->task3->setText(lblTask3Txt_EN);

    ui->btnConfirm->setText(btnConfirmTxt_EN);

    flgBG_t = false;
}

void Tasks::on_task1A_pressed()
{
    task = 1;

    task1a_pressed();
    task1b_released();
    task1c_released();
    task2_released();
    task3_released();
}


void Tasks::on_task1B_pressed()
{
    task = 2;

    task1a_released();
    task1b_pressed();
    task1c_released();
    task2_released();
    task3_released();
}


void Tasks::on_task1C_pressed()
{
    task = 3;

    task1a_released();
    task1b_released();
    task1c_pressed();
    task2_released();
    task3_released();
}


void Tasks::on_task2_pressed()
{
    task = 4;

    task1a_released();
    task1b_released();
    task1c_released();
    task2_pressed();
    task3_released();
}


void Tasks::on_task3_pressed()
{
    task = 5;

    task1a_released();
    task1b_released();
    task1c_released();
    task2_released();
    task3_pressed();
}


void Tasks::on_btnConfirm_pressed()
{
    Expanded ex;
    ex.setModal(true);
    ex.showFullScreen();

    if(flgBG_t == true)
    {
        ex.switchToBG();
    }
    else if(flgBG_t == false)
    {
        ex.switchToEN();
    }

    if(task == 1)
    {
        ex.task1A();
    }
    else if(task == 2)
    {
        ex.task1B();
    }
    else if(task == 3)
    {
        ex.task1C();
    }
    else if(task == 4)
    {
        ex.task2();
    }
    else if(task == 5)
    {
        ex.task3();
    }

    this->close();

    ex.exec();
}


void Tasks::on_btnBack_pressed()
{
    task1a_released();
    task1b_released();
    task1c_released();
    task2_released();
    task3_released();
    btnConfirm_released();

    btnBack_pressed();
}


void Tasks::on_btnBack_released()
{
    btnBack_released();

    this->close();
}

void Tasks::gpioBtnOk()
{
    if(ui->btnConfirm->hasFocus())
    {
        on_btnConfirm_pressed();
    }
    else if(ui->btnBack->hasFocus())
    {
        on_btnBack_released();
    }
}

void Tasks::gpioBtnLeft()
{
    if(ui->task1A->hasFocus())
    {
        ui->task3->setFocus();
        on_task3_pressed();
    }
    else if(ui->task1B->hasFocus())
    {
        ui->task1A->setFocus();
        on_task1A_pressed();
    }
    else if(ui->task1C->hasFocus())
    {
        ui->task1B->setFocus();
        on_task1B_pressed();
    }
    else if(ui->task2->hasFocus())
    {
        ui->task1C->setFocus();
        on_task1C_pressed();
    }
    else if(ui->task3->hasFocus())
    {
        ui->task2->setFocus();
        on_task2_pressed();
    }
}

void Tasks::gpioBtnRight()
{
    if(ui->task1A->hasFocus())
    {
        ui->task1B->setFocus();
        on_task1B_pressed();
    }
    else if(ui->task1B->hasFocus())
    {
        ui->task1C->setFocus();
        on_task1C_pressed();
    }
    else if(ui->task1C->hasFocus())
    {
        ui->task2->setFocus();
        on_task2_pressed();
    }
    else if(ui->task2->hasFocus())
    {
        ui->task3->setFocus();
        on_task3_pressed();
    }
    else if(ui->task3->hasFocus())
    {
        ui->task1A->setFocus();
        on_task1A_pressed();
    }
}

void Tasks::gpioBtnUp()
{
    if(ui->btnConfirm->hasFocus())
    {
        btnConfirm_released();
        if(task == 1)
        {
            ui->task1A->setFocus();
            on_task1A_pressed();
        }
        else if(task == 2)
        {
            ui->task1B->setFocus();
            on_task1B_pressed();
        }
        else if(task == 3)
        {
            ui->task1C->setFocus();
            on_task1C_pressed();
        }
        else if(task == 4)
        {
            ui->task2->setFocus();
            on_task2_pressed();
        }
        else if(task == 5)
        {
            ui->task3->setFocus();
            on_task3_pressed();
        }
    }
    else if(ui->btnBack->hasFocus())
    {
        ui->btnConfirm->setFocus();
        btnConfirm_pressed();
    }
    else if(ui->task1A->hasFocus())
    {
        ui->btnBack->setFocus();
        btnBack_pressed();
    }
    else if(ui->task1B->hasFocus())
    {
        ui->btnBack->setFocus();
        btnBack_pressed();
    }
    else if(ui->task1C->hasFocus())
    {
        ui->btnBack->setFocus();
        btnBack_pressed();
    }
    else if(ui->task2->hasFocus())
    {
        ui->btnBack->setFocus();
        btnBack_pressed();
    }
    else if(ui->task3->hasFocus())
    {
        ui->btnBack->setFocus();
        btnBack_pressed();
    }
}

void Tasks::gpioBtnDown()
{
    if(ui->task1A->hasFocus() || ui->task1B->hasFocus() || ui->task1C->hasFocus() || ui->task2->hasFocus() || ui->task3->hasFocus())
    {
        ui->btnConfirm->setFocus();
        btnConfirm_pressed();
    }
    else if(ui->btnConfirm->hasFocus())
    {
        btnConfirm_released();
        ui->btnBack->setFocus();
        btnBack_pressed();
    }
    else if(ui->btnBack->hasFocus())
    {
        btnBack_released();
        if(task == 1)
        {
            ui->task1A->setFocus();
            on_task1A_pressed();
        }
        else if(task == 2)
        {
            ui->task1B->setFocus();
            on_task1B_pressed();
        }
        else if(task == 3)
        {
            ui->task1C->setFocus();
            on_task1C_pressed();
        }
        else if(task == 4)
        {
            ui->task2->setFocus();
            on_task2_pressed();
        }
        else if(task == 5)
        {
            ui->task3->setFocus();
            on_task3_pressed();
        }
    }
}

