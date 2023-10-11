#ifndef SELFCHECK_H
#define SELFCHECK_H

#include <QDialog>

namespace Ui {
class SelfCheck;
}

class SelfCheck : public QDialog
{
    Q_OBJECT

public:
    explicit SelfCheck(QWidget *parent = nullptr);
    ~SelfCheck();

private slots:
    void setDayCamInitialized();
    void setThermalCamInitialized();
    void setLrfInitialized();
    void setGpsInitialized();
    void setDmcInitialized();
    void setPantiltInitialized();

    void checkStatus();
    void openLangWindow();

    void checkDayCam();
    void checkThermalCam();
    void checkLrf();
    void checkGps();
    void checkDmc();
    void checkPantilt();

    void initializationFailed();
    void startLoadingAnimation();

private:
    Ui::SelfCheck *ui;

    bool isDayCamInitialized = false;
    bool isThermalCamInitialized = false;
    bool isLrfInitialized = false;
    bool isGpsInitialized = false;
    bool isDmcInitialized = false;
    bool isPantiltInitialized = false;
};

#endif // SELFCHECK_H
