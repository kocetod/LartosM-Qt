#ifndef ENTERING_H
#define ENTERING_H

#include <QDialog>
#include <SaveLartosUserData.h>

namespace Ui {
class Entering;
}

class Entering : public QDialog
{
    Q_OBJECT

public:
    explicit Entering(QWidget *parent = nullptr);
    ~Entering();

    void switchToBG();

    void switchToEN();

    void gpioBtnOk();

    void gpioBtnLeft();

    void gpioBtnRight();

    void gpioBtnUp();

    void gpioBtnDown();

private slots:
    void k1_pressed();
    void k1_released();
    void k2_pressed();
    void k2_released();
    void k3_pressed();
    void k3_released();
    void k4_pressed();
    void k4_released();
    void k5_pressed();
    void k5_released();
    void k6_pressed();
    void k6_released();
    void k7_pressed();
    void k7_released();
    void k8_pressed();
    void k8_released();
    void k9_pressed();
    void k9_released();
    void k_del_pressed();
    void k_del_released();
    void k0_pressed();
    void k0_released();
    void k_dot_pressed();
    void k_dot_released();
    void btnConfirm_pressed();
    void btnConfirm_released();

    void k1_selected();
    void k2_selected();
    void k3_selected();
    void k4_selected();
    void k5_selected();
    void k6_selected();
    void k7_selected();
    void k8_selected();
    void k9_selected();
    void k_del_selected();
    void k0_selected();
    void k_dot_selected();
    void btnConfirm_selected();

    void openNext();

    void on_k0_pressed();

    void on_k0_released();

    void on_k1_pressed();

    void on_k1_released();

    void on_k2_pressed();

    void on_k2_released();

    void on_k3_pressed();

    void on_k3_released();

    void on_k4_pressed();

    void on_k4_released();

    void on_k5_pressed();

    void on_k5_released();

    void on_k6_pressed();

    void on_k6_released();

    void on_k7_pressed();

    void on_k7_released();

    void on_k8_pressed();

    void on_k8_released();

    void on_k9_pressed();

    void on_k9_released();

    void on_k_dot_pressed();

    void on_k_dot_released();

    void on_btnConfirm_pressed();

    void on_k_del_pressed();

    void on_k_del_released();

private:
    Ui::Entering *ui;
    SaveLartosUserData *saveuserdata;
};

#endif // ENTERING_H
