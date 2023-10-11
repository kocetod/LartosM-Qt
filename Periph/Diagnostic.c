#include "Periph/Diagnostic.h"

typedef struct
{
    enum DIAG_DEVICE device;
    bool applicable;
    bool initialised;
    long (*GetLastOkTime)();
    bool (*isSetInConf)();
    long timeToInitialise;
    long timeToError;
    enum DIAG_STATE currentState;
} DiagnosticDevice;


long diagStartTime = 0;

long GetLastOkTime_GPS()
{
    long lastMsgTime = 0;
    if(gdmLatLastMsgTime>lastMsgTime){lastMsgTime=gdmLatLastMsgTime;}
    if(gdmLongLastMsgTime>lastMsgTime){lastMsgTime=gdmLongLastMsgTime;}
    if(gdmAltLastMsgTime>lastMsgTime){lastMsgTime=gdmAltLastMsgTime;}
    if(gdmTimeLastMsgTime>lastMsgTime){lastMsgTime=gdmTimeLastMsgTime;}
    if(gdmDateLastMsgTime>lastMsgTime){lastMsgTime=gdmDateLastMsgTime;}
    return lastMsgTime;
}

bool IsSetInConf_GPS()
{
    /*if(rcGpsControlledBy==rcThisDeviceType)
    {*/
        return true;
    /*}
    else
    {
        if(rcIReceiveGpsData==true)
        {
            return true;
        }
    }
    return false;*/
}

long GetLastOkTime_Compass()
{
    return cdmLastMeasurementTimeS;
}

bool IsSetInConf_Compass()
{
   /* if(rcCompassControlledBy==rcThisDeviceType)
    {*/
        return true;
   /* }
    else
    {
        if(rcIReceiveCompassData==true)
        {
            return true;
        }
    }
    return false;*/
}

long GetLastOkTime_Rangefinder()
{
    return rdmLastPingTimeS;
}

bool IsSetInConf_Rangefinder()
{
    /*if(rcRfControlledBy==rcThisDeviceType)
    {*/
        return true;
    /*}
    else
    {
        if(rcIReceiveRfData==true)
        {
            return true;
        }
    }
    return false;*/
}

long GetLastOkTime_MB_Head()
{
    return admAdcHeadLastMeasurementTimeS;
}

bool IsSetInConf_MB_Head()
{
    return true;
}

long GetLastOkTime_MB_Controller()
{
    return admAdcControllerLastMeasurementTimeS;
}
bool IsSetInConf_MB_Controller()
{
    if(RC_Controller==rcThisDeviceType)
    {
        return true;
    }
    return false;
}

long GetLastOkTime_PTU()
{
    return pdmLastStatusTimeS;
}
bool IsSetInConf_PTU()
{
    if(RC_Controller==rcThisDeviceType)
    {
        return true;
    }
    return false;
}

int lucidLastFrameS = 0;
void LucidFrameReceived()
{
    struct timeval currentTime;
    gettimeofday(&currentTime,NULL);
    lucidLastFrameS = currentTime.tv_sec;
}

long GetLastOkTime_LucidCam()
{
    if(cameraHasToBeOn==false)
    {
        struct timeval currentTime;
        gettimeofday(&currentTime,NULL);
        lucidLastFrameS = currentTime.tv_sec;
    }
    return lucidLastFrameS;
}
bool IsSetInConf_LucidCam()
{
    return true;
}

int hikLastFrameS = 0;
void HikFrameReceived()
{
    struct timeval currentTime;
    gettimeofday(&currentTime,NULL);
    hikLastFrameS = currentTime.tv_sec;
}

long GetLastOkTime_HikCam()
{
    if(cameraHasToBeOn==false)
    {
        struct timeval currentTime;
        gettimeofday(&currentTime,NULL);
        hikLastFrameS = currentTime.tv_sec;
    }
    return hikLastFrameS;
}

bool IsSetInConf_HikCam()
{return true;}

DiagnosticDevice DiagDevices[DIAG_DEVICES_COUNT] =
{
    {
        DEV_GPS,
        true,
        false,
        &GetLastOkTime_GPS,
        &IsSetInConf_GPS,
        10,
        20,
        DIAG_NOT_CONFIGURED
    },
    {
        DEV_COMPASS,
        true,
        false,
        &GetLastOkTime_Compass,
        &IsSetInConf_Compass,
        10,
        20,
        DIAG_NOT_CONFIGURED
    },
    {
        DEV_RANGEFINDER,
        true,
        false,
        &GetLastOkTime_Rangefinder,
        &IsSetInConf_Rangefinder,
        10,
        20,
        DIAG_NOT_CONFIGURED
    },
    {
        DEV_MB_HEAD,
        true,
        false,
        &GetLastOkTime_MB_Head,
        &IsSetInConf_MB_Head,
        10,
        20,
        DIAG_NOT_CONFIGURED
    },
    {
        DEV_MB_CONTROLLER,
        true,
        false,
        &GetLastOkTime_MB_Controller,
        &IsSetInConf_MB_Controller,
        10,
        20,
        DIAG_NOT_CONFIGURED
    },
    {
        DEV_PTU,
        true,
        false,
        &GetLastOkTime_PTU,
        &IsSetInConf_PTU,
        10,
        20,
        DIAG_NOT_CONFIGURED
    },
    {
        DEV_LUCID_CAM,
        true,
        false,
        &GetLastOkTime_LucidCam,
        &IsSetInConf_LucidCam,
        15,
        25,
        DIAG_NOT_CONFIGURED
    },
    {
        DEV_HIK_CAM,
        true,
        false,
        &GetLastOkTime_HikCam,
        &IsSetInConf_HikCam,
        20,
        30,
        DIAG_NOT_CONFIGURED
    }
};

void RunDiagnostics()
{
    for(int i=0;i<DIAG_DEVICES_COUNT;i++)
    {
        if(DiagDevices[i].applicable==true)
        {
            if(DiagDevices[i].currentState==DIAG_NOT_CONFIGURED)
            {
                if(DiagDevices[i].isSetInConf()==true)
                {
                    DiagDevices[i].currentState = DIAG_NOT_INITITALISED;
                }
            }
            else if((DiagDevices[i].currentState==DIAG_NOT_INITITALISED)||(DiagDevices[i].currentState==DIAG_NOT_OK)||(DiagDevices[i].currentState==DIAG_OK))
            {
                struct timeval currentTime;
                gettimeofday(&currentTime,NULL);
                long cTime = currentTime.tv_sec;

                if(cTime>(diagStartTime+DiagDevices[i].timeToInitialise))
                {
                    if(cTime>(DiagDevices[i].GetLastOkTime()+DiagDevices[i].timeToError))
                    {
                        DiagDevices[i].currentState = DIAG_NOT_OK;
                    }
                    else
                    {
                        DiagDevices[i].currentState = DIAG_OK;
                    }
                }
            }
        }
    }
}

void SWTimerHandlerDiagnostics(size_t argInTimerId, void * arginData)
{
    RunDiagnostics();
}

enum DIAG_STATE GetDeviceDiagState(enum DIAG_DEVICE argInDevice)
{
    return DiagDevices[argInDevice].currentState;
}


void InitialiseDiagnostics()
{
    struct timeval currentTime;
    gettimeofday(&currentTime,NULL);
    diagStartTime = currentTime.tv_sec;
    AddLucidFrameReceivedCallback(&LucidFrameReceived);
    StartSoftwareTimer(500, &SWTimerHandlerDiagnostics, TIMER_PERIODIC, NULL);
}
