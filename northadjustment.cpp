#include "northAdjustment.h"
#include "ui_northAdjustment.h"

#include "calibration.h"
#include "ui_calibration.h"

#include "bg.h"
#include "en.h"

#include "variables.h"
#include <QKeyEvent>
#include <QDesktopWidget>

extern "C"
{
    #include "Application/SharedVariables.h"
}

NorthAdjustment::NorthAdjustment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NorthAdjustment)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    qApp->installEventFilter(this);

    //QCursor cursor(Qt::BlankCursor);
    //QApplication::setOverrideCursor(cursor);
    //QApplication::changeOverrideCursor(cursor);

    setAttribute(Qt::WA_AcceptTouchEvents, true);

    ui->invalid->hide();
    ui->txtDegrees->setFocus();
    ui->btnSkip->setFocus();
}

NorthAdjustment::~NorthAdjustment()
{
    delete ui;
}

bool NorthAdjustment::eventFilter(QObject *obj, QEvent *event)
{
    foreach(QLineEdit* le, findChildren<QLineEdit*>())
        if (obj == le && event->type() == QEvent::MouseButtonPress)
        {
            txt_na = "f";
        }
    return QObject::eventFilter(obj, event);
}

void NorthAdjustment::keyboardInput()
{
    foreach(QLineEdit* le, findChildren<QLineEdit*>())
        if(le->hasFocus())
        {
            le->setText(le->text() + txt_input);
        }
}

void NorthAdjustment::deleteLast()
{
    foreach(QLineEdit* le, findChildren<QLineEdit*>())
        if(le->hasFocus())
        {
            le->backspace();
        }
}

void NorthAdjustment::k1_pressed()
{
    ui->k1->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::k1_released()
{
    ui->k1->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: solid gray;"
                );
}


void NorthAdjustment::k1_selected()
{
    ui->k1->setStyleSheet(
                "border-radius: 10px; "
                "border: 3px solid white;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::k2_pressed()
{
    ui->k2->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::k2_released()
{
    ui->k2->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: solid gray;"
                );
}


void NorthAdjustment::k2_selected()
{
    ui->k2->setStyleSheet(
                "border-radius: 10px; "
                "border: 3px solid white;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::k3_pressed()
{
    ui->k3->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::k3_released()
{
    ui->k3->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: solid gray;"
                );
}


void NorthAdjustment::k3_selected()
{
    ui->k3->setStyleSheet(
                "border-radius: 10px; "
                "border: 3px solid white;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::k4_pressed()
{
    ui->k4->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::k4_released()
{
    ui->k4->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: solid gray;"
                );
}


void NorthAdjustment::k4_selected()
{
    ui->k4->setStyleSheet(
                "border-radius: 10px; "
                "border: 3px solid white;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::k5_pressed()
{
    ui->k5->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::k5_released()
{
    ui->k5->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: solid gray;"
                );
}


void NorthAdjustment::k5_selected()
{
    ui->k5->setStyleSheet(
                "border-radius: 10px; "
                "border: 3px solid white;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::k6_pressed()
{
    ui->k6->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::k6_released()
{
    ui->k6->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: solid gray;"
                );
}


void NorthAdjustment::k6_selected()
{
    ui->k6->setStyleSheet(
                "border-radius: 10px; "
                "border: 3px solid white;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::k7_pressed()
{
    ui->k7->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::k7_released()
{
    ui->k7->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: solid gray;"
                );
}


void NorthAdjustment::k7_selected()
{
    ui->k7->setStyleSheet(
                "border-radius: 10px; "
                "border: 3px solid white;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::k8_pressed()
{
    ui->k8->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::k8_released()
{
    ui->k8->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: solid gray;"
                );
}


void NorthAdjustment::k8_selected()
{
    ui->k8->setStyleSheet(
                "border-radius: 10px; "
                "border: 3px solid white;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::k9_pressed()
{
    ui->k9->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::k9_released()
{
    ui->k9->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: solid gray;"
                );
}


void NorthAdjustment::k9_selected()
{
    ui->k9->setStyleSheet(
                "border-radius: 10px; "
                "border: 3px solid white;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::k_minus_pressed()
{
    ui->k_minus->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::k_minus_released()
{
    ui->k_minus->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: solid gray;"
                );
}


void NorthAdjustment::k_minus_selected()
{
    ui->k_minus->setStyleSheet(
                "border-radius: 10px; "
                "border: 3px solid white;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::k_plus_pressed()
{
    ui->k_plus->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::k_plus_released()
{
    ui->k_plus->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: solid gray;"
                );
}


void NorthAdjustment::k_plus_selected()
{
    ui->k_plus->setStyleSheet(
                "border-radius: 10px; "
                "border: 3px solid white;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::k_del_pressed()
{
    ui->k_del->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::k_del_released()
{
    ui->k_del->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: solid gray;"
                );
}


void NorthAdjustment::k_del_selected()
{
    ui->k_del->setStyleSheet(
                "border-radius: 10px; "
                "border: 3px solid white;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::k0_pressed()
{
    ui->k0->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::k0_released()
{
    ui->k0->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: solid gray;"
                );
}


void NorthAdjustment::k0_selected()
{
    ui->k0->setStyleSheet(
                "border-radius: 10px; "
                "border: 3px solid white;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::k_dot_pressed()
{
    ui->k_dot->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::k_dot_released()
{
    ui->k_dot->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: solid gray;"
                );
}


void NorthAdjustment::k_dot_selected()
{
    ui->k_dot->setStyleSheet(
                "border-radius: 10px; "
                "border: 3px solid white;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::btnConfirm_pressed()
{
    ui->btnConfirm->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::btnConfirm_released()
{
    ui->btnConfirm->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: solid gray;"
                );
}


void NorthAdjustment::btnConfirm_selected()
{
    ui->btnConfirm->setStyleSheet(
                "border-radius: 10px; "
                "border: 3px solid white;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::btnSkip_pressed()
{
    ui->btnSkip->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::btnSkip_released()
{
    ui->btnSkip->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: solid gray;"
                );
}


void NorthAdjustment::btnSkip_selected()
{
    ui->btnSkip->setStyleSheet(
                "border-radius: 10px; "
                "border: 3px solid white;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::btnOk_pressed()
{
    ui->btnOK->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::btnOk_released()
{
    ui->btnOK->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid black;"
                "padding: 0 8px; "
                "background: solid gray;"
                );
}


void NorthAdjustment::btnOk_selected()
{
    ui->btnOK->setStyleSheet(
                "border-radius: 10px; "
                "border: 2px solid gray;"
                "padding: 0 8px; "
                "background: rgb(75, 75, 75);"
                );
}


void NorthAdjustment::switchToBG()
{
    ui->label->setText(lblInsertTxt_na_BG);
    ui->k_del->setText(btnDeleteTxt_BG);
    ui->btnConfirm->setText(btnConfirmTxt_BG);
    ui->btnSkip->setText(btnSkipTxt_na_BG);
    ui->lbl->setText(lbl_na_BG);

    flgBG_na = true;
}

void NorthAdjustment::switchToEN()
{
    ui->label->setText(lblInsertTxt_na_EN);
    ui->k_del->setText(btnDeleteTxt_EN);
    ui->btnConfirm->setText(btnConfirmTxt_EN);
    ui->btnSkip->setText(btnSkipTxt_na_EN);
    ui->lbl->setText(lbl_na_EN);

    flgBG_na = false;
}

void NorthAdjustment::on_k1_pressed()
{
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k_minus_released();
    k_plus_released();
    k_del_released();
    k0_released();
    k_dot_released();
    btnConfirm_released();
    btnSkip_released();
    btnOk_released();

    k1_pressed();
    txt_input = "1";
    keyboardInput();
}


void NorthAdjustment::on_k1_released()
{
    k1_released();
}


void NorthAdjustment::on_k2_pressed()
{
    k1_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k_minus_released();
    k_plus_released();
    k_del_released();
    k0_released();
    k_dot_released();
    btnConfirm_released();
    btnSkip_released();
    btnOk_released();

    k2_pressed();
    txt_input = "2";
    keyboardInput();
}


void NorthAdjustment::on_k2_released()
{
    k2_released();
}


void NorthAdjustment::on_k3_pressed()
{
    k1_released();
    k2_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k_minus_released();
    k_plus_released();
    k_del_released();
    k0_released();
    k_dot_released();
    btnConfirm_released();
    btnSkip_released();
    btnOk_released();

    k3_pressed();
    txt_input = "3";
    keyboardInput();
}


void NorthAdjustment::on_k3_released()
{
    k3_released();
}


void NorthAdjustment::on_k4_pressed()
{
    k1_released();
    k2_released();
    k3_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k_minus_released();
    k_plus_released();
    k_del_released();
    k0_released();
    k_dot_released();
    btnConfirm_released();
    btnSkip_released();
    btnOk_released();

    k4_pressed();
    txt_input = "4";
    keyboardInput();
}


void NorthAdjustment::on_k4_released()
{
    k4_released();
}


void NorthAdjustment::on_k5_pressed()
{
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k6_released();
    k7_released();
    k8_released();
    k9_released();
    k_minus_released();
    k_plus_released();
    k_del_released();
    k0_released();
    k_dot_released();
    btnConfirm_released();
    btnSkip_released();
    btnOk_released();

    k5_pressed();
    txt_input = "5";
    keyboardInput();
}


void NorthAdjustment::on_k5_released()
{
    k5_released();
}


void NorthAdjustment::on_k6_pressed()
{
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k7_released();
    k8_released();
    k9_released();
    k_minus_released();
    k_plus_released();
    k_del_released();
    k0_released();
    k_dot_released();
    btnConfirm_released();
    btnSkip_released();
    btnOk_released();

    k6_pressed();
    txt_input = "6";
    keyboardInput();
}


void NorthAdjustment::on_k6_released()
{
    k6_released();
}


void NorthAdjustment::on_k7_pressed()
{
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k8_released();
    k9_released();
    k_minus_released();
    k_plus_released();
    k_del_released();
    k0_released();
    k_dot_released();
    btnConfirm_released();
    btnSkip_released();
    btnOk_released();

    k7_pressed();
    txt_input = "7";
    keyboardInput();
}


void NorthAdjustment::on_k7_released()
{
    k7_released();
}


void NorthAdjustment::on_k8_pressed()
{
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k9_released();
    k_minus_released();
    k_plus_released();
    k_del_released();
    k0_released();
    k_dot_released();
    btnConfirm_released();
    btnSkip_released();
    btnOk_released();

    k8_pressed();
    txt_input = "8";
    keyboardInput();
}


void NorthAdjustment::on_k8_released()
{
    k8_released();
}


void NorthAdjustment::on_k9_pressed()
{
    k1_released();
    k2_released();
    k3_released();
    k4_released();
    k5_released();
    k6_released();
    k7_released();
    k8_released();
    k_minus_released();
    k_plus_released();
    k_del_released();
    k0_released();
    k_dot_released();
    btnConfirm_released();
    btnSkip_released();
    btnOk_released();

    k9_pressed();
    txt_input = "9";
    keyboardInput();
}


void NorthAdjustment::on_k9_released()
{
    k9_released();
}


void NorthAdjustment::on_k_dot_pressed()
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
    k_plus_released();
    k_del_released();
    k0_released();
    btnConfirm_released();
    btnSkip_released();
    btnOk_released();

    k_dot_pressed();
    txt_input = ".";
    keyboardInput();
}


void NorthAdjustment::on_k_dot_released()
{
    k_dot_released();
}


void NorthAdjustment::on_k0_pressed()
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
    k_plus_released();
    k_del_released();
    k_dot_released();
    btnConfirm_released();
    btnSkip_released();
    btnOk_released();

    k0_pressed();
    txt_input = "0";
    keyboardInput();
}


void NorthAdjustment::on_k0_released()
{
    k0_released();
}


void NorthAdjustment::on_k_del_pressed()
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
    k_plus_released();
    k0_released();
    k_dot_released();
    btnConfirm_released();
    btnSkip_released();
    btnOk_released();

    k_del_pressed();
    deleteLast();
}


void NorthAdjustment::on_k_del_released()
{
    k_del_released();
}


void NorthAdjustment::on_btnConfirm_pressed()
{
    btnConfirm_pressed();
}


void NorthAdjustment::on_btnConfirm_released()
{
    btnConfirm_released();

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
        btnConfirm_released();
        ui->btnOK->setFocus();
        btnOk_selected();
    }
    else
    {
        magnDecl = currValue;
        if(currValue != 0.000)
        {
            magneticDeclination = currValue*10000;
            updateMagneticDeclination = true;
        }
        showCalibration();
    }
}

void NorthAdjustment::on_k_minus_pressed()
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
    k_plus_released();
    k_del_released();
    k0_released();
    k_dot_released();
    btnConfirm_released();
    btnSkip_released();
    btnOk_released();

    k_minus_pressed();
    //txt_input = "-";
    //keyboardInput();
    ui->lblOperator->setText("-");
}


void NorthAdjustment::on_k_minus_released()
{
    k_minus_released();
}


void NorthAdjustment::on_k_plus_pressed()
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
    k0_released();
    k_dot_released();
    btnConfirm_released();
    btnSkip_released();
    btnOk_released();

    k_plus_pressed();
    //txt_input = "+";
    //keyboardInput();
    ui->lblOperator->setText("+");
}


void NorthAdjustment::on_k_plus_released()
{
    k_plus_released();
}


void NorthAdjustment::on_btnSkip_pressed()
{
    btnSkip_pressed();
}

void NorthAdjustment::on_btnOK_pressed()
{
    btnOk_released();
    ui->invalid->hide();
    ui->txtDegrees->clear();
    ui->txtDegrees->setFocus();
}

void NorthAdjustment::showCalibration()
{
    this->close();

    Calibration c;
    c.setModal(true);
    //c.showFullScreen();
    c.show();
    if(flgBG_na == true)
    {
        c.switchToBG();
    }
    else if(flgBG_na == false)
    {
        c.switchToEN();
    }

    c.exec();
}

void NorthAdjustment::gpioBtnOk()
{
    if(ui->btnConfirm->hasFocus())
    {
        on_btnConfirm_pressed();
    }
    else if(ui->btnSkip->hasFocus())
    {
        on_btnSkip_released();
    }
    else if(ui->btnOK->hasFocus())
    {
        on_btnOK_pressed();
    }
    foreach(QLineEdit* ledit, findChildren<QLineEdit*>())
        if(ledit->hasFocus())
        {
            if(txt_na == "f")
            {
                k1_selected();
                txt_na = "1";
            }
            else if(txt_na == "1")
            {
                ledit->setText(ledit->text() + "1");
            }
            else if(txt_na == "2")
            {
                ledit->setText(ledit->text() + "2");
            }
            else if(txt_na == "3")
            {
                ledit->setText(ledit->text() + "3");
            }
            else if(txt_na == "4")
            {
                ledit->setText(ledit->text() + "4");
            }
            else if(txt_na == "5")
            {
                ledit->setText(ledit->text() + "5");
            }
            else if(txt_na == "6")
            {
                ledit->setText(ledit->text() + "6");
            }
            else if(txt_na == "7")
            {
                ledit->setText(ledit->text() + "7");
            }
            else if(txt_na == "8")
            {
                ledit->setText(ledit->text() + "8");
            }
            else if(txt_na == "9")
            {
                ledit->setText(ledit->text() + "9");
            }
            else if(txt_na == "0")
            {
                ledit->setText(ledit->text() + "0");
            }
            else if(txt_na == "plus")
            {
                ledit->setText(ledit->text() + "+");
            }
            else if(txt_na == "minus")
            {
                ledit->setText(ledit->text() + "-");
            }
            else if(txt_na == "del")
            {
                ledit->backspace();
            }
            else if(txt_na == "dot")
            {
                ledit->setText(ledit->text() + ".");
            }
        }
}

void NorthAdjustment::gpioBtnLeft()
{
    if(ui->btnSkip->hasFocus())
    {
        btnSkip_released();
        ui->btnConfirm->setFocus();
        btnConfirm_selected();
    }
    else if(txt_na == "f")
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
    else if(txt_na == "2")
    {
        k2_released();
        k1_selected();
        txt_na = "1";
    }
    else if(txt_na == "3")
    {
        k3_released();
        k2_selected();
        txt_na = "2";
    }
    else if(txt_na == "4")
    {
        k4_released();
        k3_selected();
        txt_na = "3";
    }
    else if(txt_na == "5")
    {
        k5_released();
        k4_selected();
        txt_na = "4";
    }
    else if(txt_na == "6")
    {
        k6_released();
        k5_selected();
        txt_na = "5";
    }
    else if(txt_na == "7")
    {
        k7_released();
        k6_selected();
        txt_na = "6";
    }
    else if(txt_na == "8")
    {
        k8_released();
        k7_selected();
        txt_na = "7";
    }
    else if(txt_na == "9")
    {
        k9_released();
        k8_selected();
        txt_na = "8";
    }
    else if(txt_na == "minus")
    {
        k_minus_released();
        k9_selected();
        txt_na = "9";
    }
    else if(txt_na == "0")
    {
        k0_released();
        k_minus_selected();
        txt_na = "minus";
    }
    else if(txt_na == "plus")
    {
        k_plus_released();
        k0_selected();
        txt_na = "0";
    }
    else if(txt_na == "dot")
    {
        k_dot_released();
        k_plus_selected();
        txt_na = "plus";
    }
    else if(txt_na == "del")
    {
        k_del_released();
        k_dot_selected();
        txt_na = "dot";
    }
}

void NorthAdjustment::gpioBtnRight()
{
    if(ui->btnConfirm->hasFocus())
    {
        btnConfirm_released();
        ui->btnSkip->setFocus();
        btnSkip_selected();
    }
    else if(txt_na == "f")
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
    else if(txt_na == "1")
    {
        k1_released();
        k2_selected();
        txt_na = "2";
    }
    else if(txt_na == "2")
    {
        k2_released();
        k3_selected();
        txt_na = "3";
    }
    else if(txt_na == "3")
    {
        k3_released();
        k4_selected();
        txt_na = "4";
    }
    else if(txt_na == "4")
    {
        k4_released();
        k5_selected();
        txt_na = "5";
    }
    else if(txt_na == "5")
    {
        k5_released();
        k6_selected();
        txt_na = "6";
    }
    else if(txt_na == "6")
    {
        k6_released();
        k7_selected();
        txt_na = "7";
    }
    else if(txt_na == "7")
    {
        k7_released();
        k8_selected();
        txt_na = "8";
    }
    else if(txt_na == "8")
    {
        k8_released();
        k9_selected();
        txt_na = "9";
    }
    else if(txt_na == "9")
    {
        k9_released();
        k_minus_selected();
        txt_na = "minus";
    }
    else if(txt_na == "minus")
    {
        k_minus_released();
        k0_selected();
        txt_na = "0";
    }
    else if(txt_na == "0")
    {
        k0_released();
        k_plus_selected();
        txt_na = "plus";
    }
    else if(txt_na == "plus")
    {
        k_plus_released();
        k_dot_selected();
        txt_na = "dot";
    }
    else if(txt_na == "dot")
    {
        k_dot_released();
        k_del_selected();
        txt_na = "del";
    }
    else if(txt_na == "del")
    {
        k_del_released();
        ui->txtDegrees->setFocus();
        txt_na = "f";
    }
}

void NorthAdjustment::gpioBtnUp()
{
    if(ui->btnConfirm->hasFocus())
    {
        btnConfirm_released();
        ui->txtDegrees->setFocus();
    }
    else if(ui->btnSkip->hasFocus())
    {
        btnSkip_released();
        ui->txtDegrees->setFocus();
    }
    else if(txt_na == "del")
    {
        k_del_released();
        k_plus_selected();
        txt_na = "plus";
    }
    else if(txt_na == "plus")
    {
        k_plus_released();
        k9_selected();
        txt_na = "9";
    }
    else if(txt_na == "9")
    {
        k9_released();
        k6_selected();
        txt_na = "6";
    }
    else if(txt_na == "6")
    {
        k6_released();
        k3_selected();
        txt_na = "3";
    }
    else if(txt_na == "0")
    {
        k0_released();
        k8_selected();
        txt_na = "8";
    }
    else if(txt_na == "8")
    {
        k8_released();
        k5_selected();
        txt_na = "5";
    }
    else if(txt_na == "5")
    {
        k5_released();
        k2_selected();
        txt_na = "2";
    }
    else if(txt_na == "dot")
    {
        k_dot_released();
        k_minus_selected();
        txt_na = "minus";
    }
    else if(txt_na == "minus")
    {
        k_minus_released();
        k7_selected();
        txt_na = "7";
    }
    else if(txt_na == "7")
    {
        k7_released();
        k4_selected();
        txt_na = "4";
    }
    else if(txt_na == "4")
    {
        k4_released();
        k1_selected();
        txt_na = "1";
    }
}

void NorthAdjustment::gpioBtnDown()
{
    if(ui->txtDegrees->hasFocus() || ui->txtMinutes->hasFocus() || ui->txtSeconds->hasFocus())
    {
        ui->btnConfirm->setFocus();
        btnConfirm_selected();
    }
    else if(txt_na == "1")
    {
        k1_released();
        k4_selected();
        txt_na = "4";
    }
    else if(txt_na == "4")
    {
        k4_released();
        k7_selected();
        txt_na = "7";
    }
    else if(txt_na == "7")
    {
        k7_released();
        k_minus_selected();
        txt_na = "minus";
    }
    else if(txt_na == "minus")
    {
        k_minus_released();
        k_dot_selected();
        txt_na = "dot";
    }
    else if(txt_na == "dot")
    {
        k2_released();
        k5_selected();
        txt_na = "5";
    }
    else if(txt_na == "5")
    {
        k5_released();
        k8_selected();
        txt_na = "8";
    }
    else if(txt_na == "8")
    {
        k8_released();
        k0_selected();
        txt_na = "0";
    }
    else if(txt_na == "0")
    {
        k0_released();
        k_del_selected();
        txt_na = "del";
    }
    else if(txt_na == "3")
    {
        k3_released();
        k6_selected();
        txt_na = "6";
    }
    else if(txt_na == "6")
    {
        k6_released();
        k9_selected();
        txt_na = "9";
    }
    else if(txt_na == "9")
    {
        k9_released();
        k_plus_selected();
        txt_na = "plus";
    }
    else if(txt_na == "plus")
    {
        k_plus_released();
        k_del_selected();
        txt_na = "del";
    }
}

void NorthAdjustment::on_btnSkip_released()
{
    btnSkip_released();
    showCalibration();
}

