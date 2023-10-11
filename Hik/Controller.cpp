#include "Controller.h"
#include "ImageBuffer.h"
#include "global.h"
#include "QDebug"
#include <sys/time.h>
#include <pthread.h>

extern "C"
{
    #include "Periph/SoftwareTimer.h"
    #include "Periph/CamerasController.h"
}

SaveLartosUserData  *saveuserdata;
/*static void * _hik_config_thread(void * data);
static pthread_t hik_config_thread_id;*/

/*
void * _hik_config_thread(void * data)
{
    saveuserdata = new SaveLartosUserData();
    hikVision->setBrightness(saveuserdata->getBrightnessValueParameter());
    hikVision->setContrast(saveuserdata->getContrastValueParameter());
    if(saveuserdata->getDeeModeParameter())
    {
        hikVision->setDde(saveuserdata->getDeeValueParameter());
    }

    return NULL;
}


int RunHikConfigThread()
{
    if(pthread_create(&hik_config_thread_id, NULL, _hik_config_thread, NULL))
    {
        return 0;
    }

    return 1;
}*/

Controller *thermController = NULL;

void HikOnUpdateHandler(size_t argInTimerId, void * arginData)
{
    static int z;
    z++;
    gettimeofday(&(thermController->hikTthisFrame), NULL);
    thermController->hikDeltatime = (float)(thermController->hikTthisFrame.tv_sec - thermController->hikTprevFrame.tv_sec + (thermController->hikTthisFrame.tv_usec - thermController->hikTprevFrame.tv_usec) * 1e-6);
    thermController->hikTprevFrame = thermController->hikTthisFrame;
    thermController->HikOnUpdate(thermController->hikDeltatime);
}

QTimer *statemachineTimer;
Controller::Controller()
{
    connectTimeout = 1.0f;
    hikCurrentState = HIK_OFF;
    HikStates[HIK_NOT_CONNECTED] = &Controller::HikNotConnected;
    HikStates[HIK_CONNECT] = &Controller::HikConnectToCamera;
    HikStates[HIK_WAIT_STREAM] = &Controller::HikWaitStream;
    HikStates[HIK_STREAM] = &Controller::HikStream;
    HikStates[HIK_TURN_OFF] = &Controller::HikTurnOff;
    HikStates[HIK_OFF] = &Controller::HikOff;

    gettimeofday(&hikTprevFrame, NULL);

    StartSoftwareTimer(200, HikOnUpdateHandler, TIMER_PERIODIC, NULL);
    thermController = this;
    /*statemachineTimer = new QTimer();
    connect(statemachineTimer,SIGNAL(timeout()),this,SLOT(HikOnUpdateHandler()));
    statemachineTimer->start(20);*/
}

Controller::~Controller()
{
}

void Controller::StartImageProcessing()
{
    processingThread = new ProcessingThread(640,512);
    processingThread->start((QThread::Priority)5);
}

bool Controller::connectToCamera(int capThreadPrio, int procThreadPrio)
{
    captureThread = new CaptureThread();
    captureThread->start((QThread::Priority)capThreadPrio);
    return true;
}

void Controller::HikStatemachine(float argInDeltaTime)
{
    (this->*HikStates[hikCurrentState])(argInDeltaTime);
}

void Controller::HikOnUpdate(float argInDeltaTime)
{
    HikStatemachine(argInDeltaTime);
}

void Controller::HikNotConnected(float argInDeltaTime)
{
    connectTimeout-=argInDeltaTime;
    if(connectTimeout<=0.0f)
    {
        hikCurrentState = HIK_CONNECT;
        connectTimeout = 1.0f;
    }
    if(thermalcamHasToStream==false)
    {
        hikCurrentState = HIK_OFF;
        connectTimeout = 1.0f;
    }
}

void Controller::HikConnectToCamera(float argInDeltaTime)
{
    imageBuffer = new ImageBuffer(1,true);
    connectToCamera(5,5);
    startCaptureTimeout = 1.0f;
    hikCurrentState = HIK_WAIT_STREAM;
}

void Controller::HikWaitStream(float argInDeltaTime)
{
    startCaptureTimeout-=argInDeltaTime;
    if(startCaptureTimeout<=0.0f)
    {
        StartThermalCameraCapture();
        hikCurrentState = HIK_STREAM;
        startCaptureTimeout = 1.0f;
    }
    if(thermalcamHasToStream==false)
    {
        hikCurrentState = HIK_TURN_OFF;
        startCaptureTimeout = 1.0f;
    }
}

void Controller::HikStream(float argInDeltaTime)
{
    if(imageBuffer->bufferError==true)
    {
        captureThread->stopCaptureThread();
        if(imageBuffer->getSizeOfImageBuffer()==imageBufferSize)
        {
            QImage temp=imageBuffer->getFrame();
        }
        captureThread->wait();
        delete imageBuffer;
        hikCurrentState = HIK_NOT_CONNECTED;
    }
    if(thermalcamHasToStream==false)
    {
        hikCurrentState = HIK_TURN_OFF;
    }
 }

void Controller::HikTurnOff(float argInDeltaTime) 
{
    captureThread->stopCaptureThread();
    if(imageBuffer->getSizeOfImageBuffer()==imageBufferSize)
    {
        QImage temp=imageBuffer->getFrame();
    }
    captureThread->wait();
    delete imageBuffer;
    delete captureThread;
    hikCurrentState = HIK_OFF;
}

void Controller::HikOff(float argInDeltaTime)
{
    if(thermalcamHasToStream==true)
    {
        hikCurrentState = HIK_NOT_CONNECTED;
    }
}

void Controller::StartThermalCameraCapture()
{
    sourceWidth=captureThread->getInputSourceWidth();
    sourceHeight=captureThread->getInputSourceHeight();
    SetThermalCameraParameters();
}

void Controller::SetThermalCameraParameters()
{
    saveuserdata = new SaveLartosUserData();
    hikVision->setBrightness(saveuserdata->getBrightnessValueParameter());
    hikVision->setContrast(saveuserdata->getContrastValueParameter());
    if(saveuserdata->getDeeModeParameter())
    {
        hikVision->setDde(saveuserdata->getDeeValueParameter());
    }
   //RunHikConfigThread();
}

/*
void Controller::stopCaptureThread()
{
    qDebug() << "About to stop capture thread...";
    captureThread->stopCaptureThread();
    // Take one frame off a FULL queue to allow the capture thread to finish
    if(imageBuffer->getSizeOfImageBuffer()==imageBufferSize)
        QImage temp=imageBuffer->getFrame();
    captureThread->wait();
    qDebug() << "Capture thread successfully stopped.";
}

void Controller::stopProcessingThread()
{
    qDebug() << "About to stop processing thread...";
    processingThread->stopProcessingThread();
    processingThread->wait();
    qDebug() << "Processing thread successfully stopped.";
}

void Controller::deleteCaptureThread()
{
    delete captureThread;
}

void Controller::deleteProcessingThread()
{
    delete processingThread;
}

void Controller::clearImageBuffer()
{
    imageBuffer->clearBuffer();
}

void Controller::deleteImageBuffer()
{
    delete imageBuffer;
}*/
