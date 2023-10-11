//#include "mainwindow.h"
//#include "calibration.h"
//#include "entering.h"
//#include "incorrect.h"
//#include "northAdjustment.h"
#include "BtnControllerEvManager.h"
#include "BtnHeadEvManager.h"
#include "selfcheck.h"
#include "language.h"
//#include "expanded.h"
//#include "tasks.h"
//#include "menu.h" 
#include "mainwindowhead.h"
#include "mainwindow.h"
#include "Hik/CaptureThread.h"
#include "Hik/Controller.h"
#include "SaveLartosUserData.h"

extern "C"
{
#include "Merged/C_Acquisition.h"
#include "esUtil/Init.h"
#include "Periph/LucidCamera.h"
#include "Periph/LucidCameraDraw.h"
#include "Periph/PanTiltU.h"
#include "Configuration/ReadConfig.h"
}

#include <QApplication>

Controller* cont;
SaveLartosUserData* saveUserData;

int main(int argc, char *argv[])
{
    qputenv("QT_QPA_EGLFS_PHYSICAL_WIDTH", QByteArray("320"));
    qputenv("QT_QPA_EGLFS_PHYSICAL_HEIGHT", QByteArray("240"));
    qputenv("QT_QPA_EGLFS_FORCE888", QByteArray("1"));
    qputenv("QT_QPA_EGLFS_DEPTH", QByteArray("32"));
    MainUtil();

    //CameraOffset_Tag  Must be called before the camera starts. Here I'm using Config.json params, but you can use the ones you save in file.
    saveUserData = new SaveLartosUserData;
    int xAxisOffsetParameter = saveUserData->getReticleOffsetXaxisParameter().toInt();
    int yAxisOffsetParameter = saveUserData->getReticleOffsetYaxisParameter().toInt();
    //LcaSetOffset(rcLucidCameraOffsetX,rcLucidCameraOffsetY);
    LcaSetOffset(xAxisOffsetParameter,yAxisOffsetParameter);

    InitBtnControllerEvents();
    InitBtnHeadEvents();
    if(rcThisDeviceType==RC_HeadDevice)
    {
        qputenv("QT_QPA_EGLFS_ROTATION", QByteArray("0"));
        qputenv("QT_QPA_EGLFS_TOUCHSCREEN_PARAMETERS", QByteArray("/dev/input/event0:rotate=0"));  
    }
    else
    {
        qputenv("QT_QPA_EGLFS_ROTATION", QByteArray("90"));
        qputenv("QT_QPA_EVDEV_TOUCHSCREEN_PARAMETERS", QByteArray("/dev/input/event1:rotate=90"));
        qputenv("QT_QPA_EGLFS_HIDECURSOR", QByteArray("1"));
    }


    SetBrightness(0.7f);
    SetBrightnessThermal(0.7f);
    cont = new Controller();
    cont->StartImageProcessing();
    //AddImageProcessedCallback(((void*)&TestCallback));
    //StartThermalCameraCapture();
    PtuRegisterTiltProvider((void*)&MainWinTiltSpeedCallback);
    PtuRegisterPanProvider((void*)&MainWinPanSpeedCallback);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);
    SelfCheck check;
    MainWindowHead mainWinHead;
    Language l;
    if(rcThisDeviceType==RC_HeadDevice)
    {
        //MainWindowHead mainWinHead;
        //mainWinHead.setWindowFlags(Qt::WindowTitleHint);
        mainWinHead.show();
    }
    else
    {
        //Language l;
        //l.setWindowFlags(Qt::WindowTitleHint);
        l.show();
    }

    return a.exec();
}
