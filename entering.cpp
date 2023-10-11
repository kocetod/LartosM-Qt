#include "entering.h"
#include "ui_entering.h"

#include "northAdjustment.h"
#include "ui_northAdjustment.h"

#include "incorrect.h"
#include "ui_incorrect.h"

#include "bg.h"
#include "en.h"
#include "variables.h"

#include <QLineEdit>
#include <QTextCursor>
#include <QDesktopWidget>
#include <QTouchEvent>

Entering::Entering(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Entering)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    //QCursor cursor(Qt::BlankCursor);
    //QApplication::setOverrideCursor(cursor);
    //QApplication::changeOverrideCursor(cursor);

    setAttribute(Qt::WA_AcceptTouchEvents, true);
    ui->k1->setFocus();

    saveuserdata = new SaveLartosUserData();
    passwordValue = saveuserdata->getUserPasswordParameter();
    //saveuserdata->defaultValueSet();
}

Entering::~Entering()
{
    delete ui;
}

void Entering::btnConfirm_pressed()
{
    ui->btnConfirm->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}


void Entering::btnConfirm_released()
{
    ui->btnConfirm->setStyleSheet(
                "border: 2px rgb(173, 173, 173); "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: rgb(173, 173, 173);"
                );
}


void Entering::btnConfirm_selected()
{
    ui->btnConfirm->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}


void Entering::k1_pressed()
{
    ui->k1->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}


void Entering::k1_released()
{
    ui->k1->setStyleSheet(
                "border: 2px rgb(173, 173, 173); "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: rgb(173, 173, 173);"
                );
}


void Entering::k1_selected()
{
    ui->k1->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}


void Entering::k2_pressed()
{
    ui->k2->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}


void Entering::k2_released()
{
    ui->k2->setStyleSheet(
                "border: 2px rgb(173, 173, 173); "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: rgb(173, 173, 173);"
                );
}

void Entering::k2_selected()
{
    ui->k2->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}


void Entering::k3_pressed()
{
    ui->k3->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}


void Entering::k3_released()
{
    ui->k3->setStyleSheet(
                "border: 2px rgb(173, 173, 173); "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: rgb(173, 173, 173);"
                );
}

void Entering::k3_selected()
{
    ui->k3->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}


void Entering::k4_pressed()
{
    ui->k4->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}


void Entering::k4_released()
{
    ui->k4->setStyleSheet(
                "border: 2px rgb(173, 173, 173); "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: rgb(173, 173, 173);"
                );
}

void Entering::k4_selected()
{
    ui->k4->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}


void Entering::k5_pressed()
{
    ui->k5->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}


void Entering::k5_released()
{
    ui->k5->setStyleSheet(
                "border: 2px rgb(173, 173, 173); "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: rgb(173, 173, 173);"
                );
}

void Entering::k5_selected()
{
    ui->k5->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}


void Entering::k6_pressed()
{
    ui->k6->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}


void Entering::k6_released()
{
    ui->k6->setStyleSheet(
                "border: 2px rgb(173, 173, 173); "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: rgb(173, 173, 173);"
                );
}

void Entering::k6_selected()
{
    ui->k6->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}


void Entering::k7_pressed()
{
    ui->k7->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}


void Entering::k7_released()
{
    ui->k7->setStyleSheet(
                "border: 2px rgb(173, 173, 173); "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: rgb(173, 173, 173);"
                );
}

void Entering::k7_selected()
{
    ui->k7->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}


void Entering::k8_pressed()
{
    ui->k8->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}


void Entering::k8_released()
{
    ui->k8->setStyleSheet(
                "border: 2px rgb(173, 173, 173); "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: rgb(173, 173, 173);"
                );
}

void Entering::k8_selected()
{
    ui->k8->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}


void Entering::k9_pressed()
{
    ui->k9->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}


void Entering::k9_released()
{
    ui->k9->setStyleSheet(
                "border: 2px rgb(173, 173, 173); "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: rgb(173, 173, 173);"
                );
}

void Entering::k9_selected()
{
    ui->k9->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}


void Entering::k_del_pressed()
{
    ui->k_del->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}


void Entering::k_del_released()
{
    ui->k_del->setStyleSheet(
                "border: 2px rgb(173, 173, 173); "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: rgb(173, 173, 173);"
                );
}

void Entering::k_del_selected()
{
    ui->k_del->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}


void Entering::k0_pressed()
{
    ui->k0->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}


void Entering::k0_released()
{
    ui->k0->setStyleSheet(
                "border: 2px rgb(173, 173, 173); "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: rgb(173, 173, 173);"
                );
}

void Entering::k0_selected()
{
    ui->k0->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}


void Entering::k_dot_pressed()
{
    ui->k_dot->setStyleSheet(
                "border: 2px gray; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}


void Entering::k_dot_released()
{
    ui->k_dot->setStyleSheet(
                "border: 2px rgb(173, 173, 173); "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: rgb(173, 173, 173);"
                );
}

void Entering::k_dot_selected()
{
    ui->k_dot->setStyleSheet(
                "border: 2px solid white; "
                "border-radius: 10px; "
                "padding: 0 8px; "
                "background: gray;"
                );
}

void Entering::switchToBG()
{
    ui->label->setText(lblInsertTxt_BG);
    ui->label->adjustSize();
    ui->label->setGeometry(
                (this->width() - ui->label->width())/2,
                ui->label->geometry().y(),
                ui->label->width(),
                ui->label->height());

    ui->k_del->setText(btnDelTxt_BG);
    ui->btnConfirm->setText(btnConfirmEnteringTxt_BG);

    flgBG_e = true;
}

void Entering::switchToEN()
{
    ui->label->setText(lblInsertTxt_EN);
    ui->label->adjustSize();
    ui->label->setGeometry(
                (this->width() - ui->label->width())/2,
                ui->label->geometry().y(),
                ui->label->width(),
                ui->label->height());

    ui->k_del->setText(btnDelTxt_EN);
    ui->btnConfirm->setText(btnConfirmEnteringTxt_EN);

    flgBG_e = false;
}

void checkPassword(){

}

void Entering::on_k0_pressed()
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
    k_del_released();
    k_dot_released();
    btnConfirm_released();

    k0_pressed();

    ui->txtPassword->setText(ui->txtPassword->text() + "0");
}


void Entering::on_k0_released()
{
    k0_released();
}


void Entering::on_k1_pressed()
{
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k_del_released();
    k0_released();
    k_dot_released();
    btnConfirm_released();

    k1_pressed();

    ui->txtPassword->setText(ui->txtPassword->text() + "1");
}


void Entering::on_k1_released()
{
    k1_released();
}


void Entering::on_k2_pressed()
{
    k1_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k_del_released();
    k0_released();
    k_dot_released();
    btnConfirm_released();

    k2_pressed();

    ui->txtPassword->setText(ui->txtPassword->text() + "2");
}


void Entering::on_k2_released()
{
    k2_released();
}


void Entering::on_k3_pressed()
{
    k1_released();
    k2_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k_del_released();
    k0_released();
    k_dot_released();
    btnConfirm_released();

    k3_pressed();

    ui->txtPassword->setText(ui->txtPassword->text() + "3");
}


void Entering::on_k3_released()
{
    k3_released();
}


void Entering::on_k4_pressed()
{
    k1_released();
    k2_released();
    k3_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k_del_released();
    k0_released();
    k_dot_released();
    btnConfirm_released();

    k4_pressed();

    ui->txtPassword->setText(ui->txtPassword->text() + "4");
}


void Entering::on_k4_released()
{
    k4_released();
}


void Entering::on_k5_pressed()
{
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k_del_released();
    k0_released();
    k_dot_released();
    btnConfirm_released();

    k5_pressed();

    ui->txtPassword->setText(ui->txtPassword->text() + "5");
}


void Entering::on_k5_released()
{
    k5_released();
}


void Entering::on_k6_pressed()
{
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k7_released();
    k8_released();
    k9_released();
    k_del_released();
    k0_released();
    k_dot_released();
    btnConfirm_released();

    k6_pressed();

    ui->txtPassword->setText(ui->txtPassword->text() + "6");
}


void Entering::on_k6_released()
{
    k6_released();
}


void Entering::on_k7_pressed()
{
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k8_released();
    k9_released();
    k_del_released();
    k0_released();
    k_dot_released();
    btnConfirm_released();

    k7_pressed();

    ui->txtPassword->setText(ui->txtPassword->text() + "7");
}


void Entering::on_k7_released()
{
    k7_released();
}


void Entering::on_k8_pressed()
{
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k9_released();
    k_del_released();
    k0_released();
    k_dot_released();
    btnConfirm_released();

    k8_pressed();

    ui->txtPassword->setText(ui->txtPassword->text() + "8");
}


void Entering::on_k8_released()
{
    k8_released();
}


void Entering::on_k9_pressed()
{
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k_del_released();
    k0_released();
    k_dot_released();
    btnConfirm_released();

    k9_pressed();

    ui->txtPassword->setText(ui->txtPassword->text() + "9");
}


void Entering::on_k9_released()
{
    k9_released();
}


void Entering::on_k_dot_pressed()
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
    k_del_released();
    k0_released();
    btnConfirm_released();

    k_dot_pressed();

    ui->txtPassword->setText(ui->txtPassword->text() + ".");
}


void Entering::on_k_dot_released()
{
    k_dot_released();
}

void Entering::openNext()
{
    Incorrect i;

    passwordCheck = ui->txtPassword->text();

    if(passwordCheck == passwordValue)
    {
        this->close();

        NorthAdjustment na;
        na.setModal(true);
        na.showFullScreen();
        //na.show();
        if(flgBG_e == true)
        {
            na.switchToBG();
        }
        else if(flgBG_e == false)
        {
            na.switchToEN();
        }
        na.exec();
    }
    else
    {
        i.setModal(true);

        if(flgBG_e == true)
        {
            i.switchToBG();
        }
        else if(flgBG_e == false)
        {
            i.switchToEN();
        }

        i.exec();
    }

    ui->txtPassword->clear();
}


void Entering::on_btnConfirm_pressed()
{
    openNext();
}


void Entering::on_k_del_pressed()
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
    k_dot_released();
    btnConfirm_released();

    k_del_pressed();

    ui->txtPassword->backspace();
}


void Entering::on_k_del_released()
{
    k_del_released();
}

void Entering::gpioBtnOk()
{
    if(ui->btnConfirm->hasFocus()){
        openNext();
    }
    else if(ui->k_del->hasFocus())
    {
        ui->txtPassword->backspace();
    }
    else if(ui->k0->hasFocus())
    {
        ui->txtPassword->setText(ui->txtPassword->text() + "0");
    }
    else if(ui->k1->hasFocus())
    {
        ui->txtPassword->setText(ui->txtPassword->text() + "1");
    }
    else if(ui->k2->hasFocus())
    {
        ui->txtPassword->setText(ui->txtPassword->text() + "2");
    }
    else if(ui->k3->hasFocus())
    {
        ui->txtPassword->setText(ui->txtPassword->text() + "3");
    }
    else if(ui->k4->hasFocus())
    {
        ui->txtPassword->setText(ui->txtPassword->text() + "4");
    }
    else if(ui->k5->hasFocus())
    {
        ui->txtPassword->setText(ui->txtPassword->text() + "5");
    }
    else if(ui->k6->hasFocus())
    {
        ui->txtPassword->setText(ui->txtPassword->text() + "6");
    }
    else if(ui->k7->hasFocus())
    {
        ui->txtPassword->setText(ui->txtPassword->text() + "7");
    }
    else if(ui->k8->hasFocus())
    {
        ui->txtPassword->setText(ui->txtPassword->text() + "8");
    }
    else if(ui->k9->hasFocus())
    {
        ui->txtPassword->setText(ui->txtPassword->text() + "9");
    }
    else if(ui->k_dot->hasFocus())
    {
        ui->txtPassword->setText(ui->txtPassword->text() + ".");
    }
}

void Entering::gpioBtnLeft()
{
    if(ui->k2->hasFocus())
    {
        k2_released();
        ui->k1->setFocus();
        k1_selected();
    }
    else if(ui->k3->hasFocus())
    {
        k3_released();
        ui->k2->setFocus();
        k2_selected();
    }
    else if(ui->k4->hasFocus())
    {
        k4_released();
        ui->k3->setFocus();
        k3_selected();
    }
    else if(ui->k5->hasFocus())
    {
        k5_released();
        ui->k4->setFocus();
        k4_selected();
    }
    else if(ui->k6->hasFocus())
    {
        k6_released();
        ui->k5->setFocus();
        k5_selected();
    }
    else if(ui->k7->hasFocus())
    {
        k7_released();
        ui->k6->setFocus();
        k6_selected();
    }
    else if(ui->k8->hasFocus())
    {
        k8_released();
        ui->k7->setFocus();
        k7_selected();
    }
    else if(ui->k9->hasFocus())
    {
        k9_released();
        ui->k8->setFocus();
        k8_selected();
    }
    else if(ui->k_del->hasFocus())
    {
        k_del_released();
        ui->k9->setFocus();
        k9_selected();
    }
    else if(ui->k0->hasFocus())
    {
        k0_released();
        ui->k_del->setFocus();
        k_del_selected();
    }
    else if(ui->k_dot->hasFocus())
    {
        k_dot_released();
        ui->k0->setFocus();
        k0_selected();
    }
}

void Entering::gpioBtnRight()
{
    if(ui->k1->hasFocus())
    {
        k1_released();
        ui->k2->setFocus();
        k2_selected();
    }
    else if(ui->k2->hasFocus())
    {
        k2_released();
        ui->k3->setFocus();
        k3_selected();
    }
    else if(ui->k3->hasFocus())
    {
        k3_released();
        ui->k4->setFocus();
        k4_selected();
    }
    else if(ui->k4->hasFocus())
    {
        k4_released();
        ui->k5->setFocus();
        k5_selected();
    }
    else if(ui->k5->hasFocus())
    {
        k5_released();
        ui->k6->setFocus();
        k6_selected();
    }
    else if(ui->k6->hasFocus())
    {
        k6_released();
        ui->k7->setFocus();
        k7_selected();
    }
    else if(ui->k7->hasFocus())
    {
        k7_released();
        ui->k8->setFocus();
        k8_selected();
    }
    else if(ui->k8->hasFocus())
    {
        k8_released();
        ui->k9->setFocus();
        k9_selected();
    }
    else if(ui->k9->hasFocus())
    {
        k9_released();
        ui->k_del->setFocus();
        k_del_selected();
    }
    else if(ui->k_del->hasFocus())
    {
        k_del_released();
        ui->k0->setFocus();
        k0_selected();
    }
    else if(ui->k0->hasFocus())
    {
        k0_released();
        ui->k_dot->setFocus();
        k_dot_selected();
    }
}

void Entering::gpioBtnUp()
{
    if(ui->k4->hasFocus())
    {
        k4_released();
        ui->k1->setFocus();
        k1_selected();
    }
    else if(ui->k5->hasFocus())
    {
        k5_released();
        ui->k2->setFocus();
        k2_selected();
    }
    else if(ui->k6->hasFocus())
    {
        k6_released();
        ui->k3->setFocus();
        k3_selected();
    }
    else if(ui->k7->hasFocus())
    {
        k7_released();
        ui->k4->setFocus();
        k4_selected();
    }
    else if(ui->k8->hasFocus())
    {
        k8_released();
        ui->k5->setFocus();
        k5_selected();
    }
    else if(ui->k9->hasFocus())
    {
        k9_released();
        ui->k6->setFocus();
        k6_selected();
    }
    else if(ui->k_del->hasFocus())
    {
        k_del_released();
        ui->k7->setFocus();
        k7_selected();
    }
    else if(ui->k0->hasFocus())
    {
        k0_released();
        ui->k8->setFocus();
        k8_selected();
    }
    else if(ui->k_dot->hasFocus())
    {
        k_dot_released();
        ui->k9->setFocus();
        k9_selected();
    }
    else if(ui->btnConfirm->hasFocus())
    {
        btnConfirm_released();
        ui->k_del->setFocus();
        k_del_selected();
    }
}

void Entering::gpioBtnDown()
{
    if(ui->k1->hasFocus())
    {
        k1_released();
        ui->k4->setFocus();
        k4_selected();
    }
    else if(ui->k2->hasFocus())
    {
        k2_released();
        ui->k5->setFocus();
        k5_selected();
    }
    else if(ui->k3->hasFocus())
    {
        k3_released();
        ui->k6->setFocus();
        k6_selected();
    }
    else if(ui->k4->hasFocus())
    {
        k4_released();
        ui->k7->setFocus();
        k7_selected();
    }
    else if(ui->k5->hasFocus())
    {
        k5_released();
        ui->k8->setFocus();
        k8_selected();
    }
    else if(ui->k6->hasFocus())
    {
        k6_released();
        ui->k9->setFocus();
        k9_selected();
    }
    else if(ui->k7->hasFocus())
    {
        k7_released();
        ui->k_del->setFocus();
        k_del_selected();
    }
    else if(ui->k8->hasFocus())
    {
        k8_released();
        ui->k0->setFocus();
        k0_selected();
    }
    else if(ui->k9->hasFocus())
    {
        k9_released();
        ui->k_dot->setFocus();
        k_dot_selected();
    }
    else if(ui->k_del->hasFocus())
    {
        k_del_released();
        ui->btnConfirm->setFocus();
        btnConfirm_selected();
    }
    else if(ui->k0->hasFocus())
    {
        k0_released();
        ui->btnConfirm->setFocus();
        btnConfirm_selected();
    }
    else if(ui->k_dot->hasFocus())
    {
        k_dot_released();
        ui->btnConfirm->setFocus();
        btnConfirm_selected();
    }
}
