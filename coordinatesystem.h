#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H

#include <QDialog>
#include <QKeyEvent>
#include "SaveLartosUserData.h"

namespace Ui {
class CoordinateSystem;
}

class CoordinateSystem : public QDialog
{
    Q_OBJECT

public:
    explicit CoordinateSystem(QWidget *parent = nullptr);
    ~CoordinateSystem();

    void openMainWin();

    void switchToBG();

    void switchToEN();

    void gpioBtnOk();

    void gpioBtnLeft();

    void gpioBtnRight();

    void gpioBtnUp();

    void gpioBtnDown();

private slots:
    void setCoordinateSystemParameters();

    void on_wgs_pressed();

    void on_krasovsky_pressed();

    void on_utm_xy_pressed();

    void on_bl_pressed();

    void on_btnChooseCoordSys_pressed();

    void setWgsStyleSheet();
    void setKrasovskyStyleSheet();
    void setUtmStyleSheet();
    void setBlStyleSheet();
    void setZone1StyleSheet();
    void setZone2StyleSheet();

    void btnChooseCoordSys_pressed();
    void btnChooseCoordSys_released();
    void btnChooseCoordSys_selected();

    void on_zone_35_pressed();

    void on_zone_34_pressed();

    void on_btnChooseCoordSys_released();

private:
    Ui::CoordinateSystem *ui;

    SaveLartosUserData  *saveuserdata;
};

#endif // COORDINATESYSTEM_H
