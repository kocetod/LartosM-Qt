#ifndef MAINWINDOWHEAD_H
#define MAINWINDOWHEAD_H

#include <QDialog>
#include "Hik/global.h"

namespace Ui {
class MainWindowHead;
}

class MainWindowHead : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindowHead(QWidget *parent = nullptr);
    ~MainWindowHead();
    void btnBrightness_pressed();
    void btnBrightness_released();
    void btnScreenshot_pressed();
    void btnScreenshot_released();
    void btnLrf_pressed();
    void btnLrf_released();
    void btnOnOff_pressed();
    void btnOnOff_released();
    void btnPolarity_pressed();
    void btnPolarity_released();
    void btnDayir_pressed();
    void btnDayir_released();
    void btnZoom_pressed();
    void btnZoom_released();

    void btnPolarity_func();

    void btnDayir_func();

    void setIconPixmap();

    void setIrZoom();

    void setDayZoom();

    void setBrightness();

    void makeScreenshot();

    void changeZoom();

    void checkDayZoom();

    void checkIrZoom();

private:
    Ui::MainWindowHead *ui;
private slots:
    void updateFrame(const QPixmap &frame);
};

#endif // MAINWINDOWHEAD_H
