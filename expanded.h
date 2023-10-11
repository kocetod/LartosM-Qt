#ifndef EXPANDED_H
#define EXPANDED_H

#include <QDialog>
#include <QLineEdit>
#include "Hik/hikvision.h"
#include "mediabrowser.h"
#include "variables.h"
#include "resultselection.h"


namespace Ui {
class Expanded;
}

class Expanded : public QDialog
{
    Q_OBJECT

public:
    explicit Expanded(QWidget *parent = nullptr);
    ~Expanded();

    void updateCoordParameters();

    void task1A();

    void task1B();

    void task1C();

    void task2();

    void task3();

    void taskStyle();

    void switchToBG();

    void switchToEN();

    void setIconPixmap();

    void setIrZoom();

    void setDayZoom();

    void setIrZoom_ex();

    void setDayZoom_ex();

    void gpioBtnOk();

    void gpioBtnLeft();

    void gpioBtnRight();

    void gpioBtnUp();

    void gpioBtnDown();

    void gpioBtnZoom();

    void gpioBtnLrf();

    void gpioBtnPantiltUpPressed();

    void gpioBtnPantiltDownPressed();

    void gpioBtnPantiltLeftPressed();

    void gpioBtnPantiltRightPressed();

    void gpioBtnPantiltUpReleased();

    void gpioBtnPantiltDownReleased();

    void gpioBtnPantiltLeftReleased();

    void gpioBtnPantiltRightReleased();

protected:

    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void waitForMeasurement();

    void checkBeforeTransform();
    void updateInputParameters();
    void checkAfterTransform();
    void transformBeforeTasks_A();
    void transformAfterTasks_A();
    void transformBeforeTasks_B();
    void transformAfterTasks_B();
    void transformBeforeTasks_C();
    void transformAfterTasks_C();
    void transformBeforeTasks_D();
    void transformAfterTasks_D();
    void checkCoordinateInputType();

    void increaseUpSpeed();
    void decreaseUpSpeed();

    void increaseDownSpeed();
    void decreaseDownSpeed();

    void increaseLeftSpeed();
    void decreaseLeftSpeed();

    void increaseRightSpeed();
    void decreaseRightSpeed();

    void startIncreasingUp();
    void startIncreasingDown();
    void startIncreasingLeft();
    void startIncreasingRight();

    void btnDayir_ex_pressed();
    void btnZoom_ex_pressed();
    void btnNuc_ex_pressed();
    void btnPolarity_ex_pressed();
    void btnPantilt_ex_pressed();
    void btnScreenshot_pressed();
    void btnBack_pressed();
    void btnPantilt_up_pressed();
    void btnPantilt_down_pressed();
    void btnPantilt_left_pressed();
    void btnPantilt_right_pressed();
    void btnDayir_ex_released();
    void btnZoom_ex_released();
    void btnNuc_ex_released();
    void btnPolarity_ex_released();
    void btnPantilt_ex_released();
    void btnScreenshot_released();
    void btnBack_released();
    void btnPantilt_up_released();
    void btnPantilt_down_released();
    void btnPantilt_left_released();
    void btnPantilt_right_released();

    void btnDayir_ex_selected();
    void btnZoom_ex_selected();
    void btnNuc_ex_selected();
    void btnPolarity_ex_selected();
    void btnPantilt_ex_selected();
    void btnScreenshot_selected();
    void btnBack_selected();
    void btnPantilt_up_selected();
    void btnPantilt_down_selected();
    void btnPantilt_left_selected();
    void btnPantilt_right_selected();


    void btnDayir_pressed();
    void btnPantilt_pressed();
    void btnLrf_pressed();
    void btnZoom_pressed();
    void btnChange_pressed();
    void k1_pressed();
    void k2_pressed();
    void k3_pressed();
    void k4_pressed();
    void k5_pressed();
    void k6_pressed();
    void k7_pressed();
    void k8_pressed();
    void k9_pressed();
    void k0_pressed();
    void k_minus_pressed();
    void k_del_pressed();
    void k_calc_pressed();
    void k_correction_pressed();
    void k_dot_pressed();
    void btnDayir_released();
    void btnPantilt_released();
    void btnLrf_released();
    void btnZoom_released();
    void btnChange_released();
    void k1_released();
    void k2_released();
    void k3_released();
    void k4_released();
    void k5_released();
    void k6_released();
    void k7_released();
    void k8_released();
    void k9_released();
    void k0_released();
    void k_minus_released();
    void k_del_released();
    void k_calc_released();
    void k_correction_released();
    void k_dot_released();


    void btnDayir_selected();
    void btnPantilt_selected();
    void btnLrf_selected();
    void btnZoom_selected();
    void btnChange_selected();
    void k1_selected();
    void k2_selected();
    void k3_selected();
    void k4_selected();
    void k5_selected();
    void k6_selected();
    void k7_selected();
    void k8_selected();
    void k9_selected();
    void k0_selected();
    void k_minus_selected();
    void k_del_selected();
    void k_calc_selected();
    void k_correction_selected();
    void k_dot_selected();

    void showKeyboard();

    void showPanTilt();

    void hidePanTilt();

    void showPanTiltEx();

    void showIrButtons();

    void hideIrButtons();

    void moveRightButtons();

    void moveLeftButtons();

    void makeScreenshot();

    void checkTask();

    void hideTasksBox();

    void showTasksBox();

    void keyboardInput();

    void deleteLast();

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

    void on_k0_pressed();

    void on_k0_released();

    void on_k_minus_pressed();

    void on_k_minus_released();

    void on_del_pressed();

    void on_del_released();

    void on_calculate_pressed();

    void on_calculate_released();

    void on_btnChange_released();

    void on_btnBack_pressed();

    void on_btnDayir_pressed();

    void on_btnLRF_pressed();

    void on_btnLRF_released();

    void on_btnBack_released();

    void on_btnChange_pressed();

    void on_btnDayir_ex_pressed();

    void on_btnNuc_ex_pressed();

    void on_btnZoom_ex_released();

    void on_btnZoom_ex_pressed();

    void on_btnPolarity_ex_pressed();

    void on_btnNuc_ex_released();

    void on_btnPantilt_pressed();

    void on_btnZoom_pressed();

    void on_btnZoom_released();

    void on_btnPantilt_up_pressed();

    void on_btnPantilt_up_released();

    void on_btnPantilt_down_pressed();

    void on_btnPantilt_down_released();

    void on_btnPantilt_left_pressed();

    void on_btnPantilt_left_released();

    void on_btnPantilt_right_pressed();

    void on_btnPantilt_right_released();

    void on_btnPantilt_ex_pressed();

    void on_btnScreenshot_pressed();

    void on_btnScreenshot_released();


    void on_k_dot_pressed();

    void on_k_dot_released();



    void task1AInfo();

    void task1BInfo();

    void task1CInfo();

    void task2Info();

    void task3Info();


    void checkIrZoom_ex();

    void checkDayZoom_ex();

    void checkIrZoom();

    void checkDayZoom();

    void on_btnInfo_released();

    void on_btnClose_pressed();

    void on_btnClose_released();

    void on_btnPoints_pressed();

    void on_btnDirAngleType_pressed();

    void on_btnDirAngleType_1B_pressed();

    void on_btnDirAngleType_1A_pressed();

    void on_correction_pressed();

    void on_correction_released();
    void updateFrame(const QPixmap &frame);

private:
    Ui::Expanded *ui;
    HikVision* hikVision;
    ResultSelection resultSelection;


    void task1_func();
    void task2_func();
    void task1B_func();
    void task1C_func();
    void task3_func();
};

#endif // EXPANDED_H
