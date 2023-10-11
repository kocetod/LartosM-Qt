#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <QDialog>

namespace Ui {
class Calibration;
}

class Calibration : public QDialog
{
    Q_OBJECT

public:
    explicit Calibration(QWidget *parent = nullptr);
    ~Calibration();
    void switchToBG();

    void switchToEN();

public slots:
    void openCoordSys();

private slots:
    void on_btnTryAgain_pressed();

    void checkStatus();

    void showBtnTryAgain();

    void on_btnSkip_pressed();

private:
    Ui::Calibration *ui;
};

#endif // CALIBRATION_H
