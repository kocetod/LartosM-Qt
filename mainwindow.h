#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include "Hik/hikvision.h"
#include <QMainWindow>
#include "Hik/Controller.h"
#include <QTextCodec>
#include <fstream>
#include "SaveLartosUserData.h"
#include "mediabrowser.h"
#include "Hik/global.h"

#define REALPLAY_MAX_NUM 36
#define  HPR_OK 0
#define  HPR_ERROR -1

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

int MainWinPanSpeedCallback();
int MainWinTiltSpeedCallback();
void TestCallback();

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static MainWindow* instance;
    Ui::MainWindow *ui;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void switchToBG();

    void switchToEN();

    void updateCoordParameters();

    void startSinglePreview();

    void OnSingleClickPlayWindow();

    void updateFrameDayCam();

    void setIconPixmap();

    void setIrZoom();

    void setDayZoom();

    void setIrPolarity();

    void setDayPolarity();

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

    //void setThermalCameraParameters();
protected:
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
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

    void btnLrf_pressed();
    void btnLrf_released();
    void btnDayir_pressed();
    void btnDayir_released();
    void btnPantilt_pressed();
    void btnPantilt_released();
    void btnMedia_pressed();
    void btnMedia_released();
    void btnTasks_pressed();
    void btnTasks_released();
    void btnNuc_pressed();
    void btnNuc_released();
    void btnZoom_pressed();
    void btnZoom_released();
    void btnPolarity_pressed();
    void btnPolarity_released();
    void btnMenu_pressed();
    void btnMenu_released();
    void btnScreenshot_pressed();
    void btnScreenshot_released();
    void btnExpand_pressed();
    void btnExpand_released();
    void btnPantilt_up_pressed();
    void btnPantilt_up_released();
    void btnPantilt_down_pressed();
    void btnPantilt_down_released();
    void btnPantilt_left_pressed();
    void btnPantilt_left_released();
    void btnPantilt_right_pressed();
    void btnPantilt_right_released();

    void btnLrf_selected();
    void btnDayir_selected();
    void btnPantilt_selected();
    void btnMedia_selected();
    void btnTasks_selected();
    void btnNuc_selected();
    void btnZoom_selected();
    void btnPolarity_selected();
    void btnMenu_selected();
    void btnScreenshot_selected();
    void btnExpand_selected();
    void btnPantilt_up_selected();
    void btnPantilt_down_selected();
    void btnPantilt_left_selected();
    void btnPantilt_right_selected();

    void openMediaBrowser();
    void openTasksWin();
    void changeZoom();
    void openMenuWin();
    void openExpandedWin();

    //void StartThermalCameraCapture();

    //void StopThermalCameraCapture();

    void updateFrame(const QPixmap &frame);

    void hidePanTilt();

    void showPanTilt();

    void makeScreenshot();

    void on_btnMedia_pressed();

    void on_btnMedia_released();

    void on_btnExpand_pressed();

    void on_btnTasks_released();

    void on_btnZoom_pressed();

    void on_btnZoom_released();

    void on_btnMenu_released();

    void on_btnDayir_pressed();

    void on_btnTasks_pressed();

    void on_btnMenu_pressed();

    void on_btnExpand_released();

    void on_btnNuc_pressed();

    void on_btnScreenshot_pressed();

    void on_btnScreenshot_released();

    void on_btnPolarity_pressed();

    void on_btnNuc_released();

    void on_btnPantilt_pressed();

    void on_btnPantilt_up_pressed();

    void on_btnPantilt_up_released();

    void on_btnPantilt_down_pressed();

    void on_btnPantilt_down_released();

    void on_btnPantilt_left_pressed();

    void on_btnPantilt_left_released();

    void on_btnPantilt_right_pressed();

    void on_btnPantilt_right_released();

    void on_btnLRF_pressed();

    void on_btnLRF_released();

    void checkIrZoom();

    void checkDayZoom();

private:

    //HikVision* hikVision;
    //Controller *controller;
    //SaveLartosUserData  *saveuserdata;
    MediaBrowser open_mediaBrowser;
    SaveLartosUserData *saveuserdata;
    //int sourceWidth;
    //int sourceHeight;
    //int imageBufferSize;
};
#endif // MAINWINDOW_H
