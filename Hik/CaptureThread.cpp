#include "Hik/CaptureThread.h"
#include "Hik/Controller.h"

int nPort=0;
volatile int gbHandling=3 ;
unsigned int count=1;
bool isCameraConnected = false;
int sourceWidth = 0;
int sourceHeight = 0;

//SaveLartosUserData  *saveuserdata;
HikVision* hikVision; 

extern "C"
{
    #include "Periph/Diagnostic.h"
}

void StopThermalCameraCapture()
{
    if(isCameraConnected==true)
    {
        //CaptureThread::disconnect(controller->processingThread,SIGNAL(newFrame(QImage)),0,0);
        //controller->stopProcessingThread();
        //controller->stopCaptureThread();
        //controller->deleteProcessingThread();
        //controller->deleteCaptureThread();
        //ThermalDrawStop();
        //isCameraConnected = false;
        //ui->frameLabel->clear();
    }
    //delete controller;
    /*ThermalDrawStop();*/
}


void CALLBACK DecCBFun(int nPort, char * pBuf, int nSize, FRAME_INFO * pFrameInfo, void * nReserved1, int nReserved2)
{
    QImageCleanupFunction cleanupFunction = NULL;
    const uchar* buffer = (unsigned char*)pBuf;

    long int width = pFrameInfo->nWidth;
    long int height = pFrameInfo->nHeight;

    if (gbHandling)
    {
        gbHandling--;
        return;
    }

    long lFrameType = pFrameInfo->nType;
    if (lFrameType == T_YV12)
    {
        QImage frame(buffer, width, height, QImage::Format_Indexed8, cleanupFunction, NULL);
        if(thermController->hikCurrentState==Controller::HIK_STREAM)
        {
            imageBuffer->addFrame(frame);
        }
        HikFrameReceived();
    }

    gbHandling = 0;
}

void CALLBACK fRealDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser)
{

    switch (dwDataType)
    {
    case NET_DVR_SYSHEAD:

        if (!PlayM4_GetPort(&nPort))
        {
            break;
        }
        if (dwBufSize > 0)
        {
            qDebug() << "dwBufSize      " + dwBufSize;
            if (!PlayM4_SetStreamOpenMode(nPort, STREAME_REALTIME))
            {
                break;
            }

            if (!PlayM4_OpenStream(nPort, pBuffer, dwBufSize, 10*1024 * 1024))
            {
                break;
            }

            if (!PlayM4_Play(nPort, NULL))
            {
                break;
            }
            if (!PlayM4_SetDecCallBackEx(nPort, DecCBFun, NULL, NULL))
            {
                break;
            }
        }
        break;
    case NET_DVR_STREAMDATA:
        if (dwBufSize > 0 && nPort != -1)
        {
            if (!PlayM4_InputData(nPort, pBuffer, dwBufSize))
            {
                qDebug() << "error" << PlayM4_GetLastError(nPort);
                break;
            }
        }
        break;
    default:
        if (dwBufSize > 0 && nPort != -1)
        {
            if (!PlayM4_InputData(nPort, pBuffer, dwBufSize))
            {
                break;
            }
        }
        break;
    }
}

void CALLBACK g_ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser)
{
    char tempbuf[256] = { 0 };
    switch (dwType)
    {
    case EXCEPTION_RECONNECT:
        printf("----------reconnect--------%d\n", time(NULL));
        break;
    default:
        break;
    }
}

CaptureThread::CaptureThread() : QThread()
{
    // Initialize variables
    stopped=false;
}

void CaptureThread::run()
{
    NET_DVR_Init();
    NET_DVR_SetConnectTime(2000, 1);
    NET_DVR_SetReconnect(10000, true);
    LONG lUserID;
    NET_DVR_DEVICEINFO_V30 struDeviceInfo;
    lUserID = NET_DVR_Login_V30(ID_IP, 8000, ID_USER, ID_PASSWORD, &struDeviceInfo);
    if (lUserID < 0)
    {
        printf("Login error, %d\n", NET_DVR_GetLastError());
        NET_DVR_Cleanup();
        return;
    }
    NET_DVR_SetExceptionCallBack_V30(0, NULL, g_ExceptionCallBack, NULL);
    LONG lRealPlayHandle;

    NET_DVR_PREVIEWINFO struPlayInfo = { 0 };
    struPlayInfo.hPlayWnd = NULL;
    struPlayInfo.lChannel = 1;
    struPlayInfo.dwStreamType = 0;
    struPlayInfo.dwLinkMode = 1;

    lRealPlayHandle = NET_DVR_RealPlay_V40(lUserID, &struPlayInfo, fRealDataCallBack, NULL);


    if (lRealPlayHandle < 0)
    {
         qDebug() << "Stopping capture thread...";
        printf("NET_DVR_RealPlay_V40 error\n");
        printf("%d\n", NET_DVR_GetLastError());
        NET_DVR_Logout(lUserID);
        NET_DVR_Cleanup();
        return;
    }
}

void CaptureThread::stopCaptureThread()
{
    stoppedMutex.lock();
    stopped=true;
    stoppedMutex.unlock();
} // stopCaptureThread()


int CaptureThread::getInputSourceWidth()
{
    return 640;
}

int CaptureThread::getInputSourceHeight()
{
    return 512;
}
