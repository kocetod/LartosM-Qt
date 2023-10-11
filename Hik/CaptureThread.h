#ifndef CAPTURETHREAD_H
#define CAPTURETHREAD_H

#include <QThread>
#include <QDialog>
#include "HCNetSDK.h"
#include "LinuxPlayM4.h"
#include "PlayM4.h"
#include "QImage"
#include "QFile"
#include "variables.h"

#include "ImageBuffer.h"
#include "global.h"
#include "unistd.h"
#include <qobject.h>
#include "hikvision.h"
#include "SaveLartosUserData.h"
// Qt header files
#include <QDebug>

extern HikVision* hikVision;

void StopThermalCameraCapture();
void StartThermalCameraCapture();
void InitController();
void SetThermalCameraParameters();

class CaptureThread : public QThread
{
    Q_OBJECT

public:
    CaptureThread();
    void stopCaptureThread();
    int getInputSourceWidth();
    int getInputSourceHeight();
    void hik_init(); 
private: 
protected:
    void run();
};

#endif // CAPTURETHREAD_H
