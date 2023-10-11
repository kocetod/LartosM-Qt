#include "Periph/CamerasController.h"

bool cameraHasToBeOn = false;

enum CAMERAS selectedCamera;

bool daycamHasToStream = false;
bool thermalcamHasToStream = false;

float switchTimeout = 0.1f;


enum CAMERA_SELECTOR_STATES
{
    SEL_DAY,
    SEL_DAY_TO_THERM,
    SEL_THERM,
    SEL_THERM_TO_DAY,
    CAMERA_SELECTOR_STATES_COUNT
};

void (*SelStates[CAMERA_SELECTOR_STATES_COUNT])(float);

static enum CAMERA_SELECTOR_STATES selCurrentState;


enum CAMERAS GetSelectedCamera()
{
    return selectedCamera;
}

bool SelectCamera(enum CAMERAS arginCameraToSelect)
{
    if(arginCameraToSelect==DAYCAM)
    {
        if(selCurrentState==SEL_THERM)
        {
            selectedCamera = DAYCAM;
            return true;
        }
    }
    else if(arginCameraToSelect==THERMALCAM)
    {
        if(selCurrentState==SEL_DAY)
        {
            selectedCamera = THERMALCAM;
            return true;
        }
    }
    return false;
}

void SelStateDay(float argInDeltaTime)
{
    if(cameraHasToBeOn==true)
    {
        if(selectedCamera==DAYCAM)
        {
            if(DaycamDrawIsRunning()==false)
            {
                DaycamDrawStart();
            }
            if(ThermalIsRunning()==true)
            {
                ThermalDrawStop();
            }
            //daycamHasToStream=true;
            //thermalcamHasToStream =false;
            daycamHasToStream=true;
            thermalcamHasToStream =true;
        }
        else
        {
            //daycamHasToStream=false;
            //thermalcamHasToStream = true;
            daycamHasToStream=true;
            thermalcamHasToStream =true;
            switchTimeout = 0.1f;
            selCurrentState = SEL_DAY_TO_THERM;
        }
    }
    else
    {
        //daycamHasToStream=false;
        //thermalcamHasToStream = false;
        daycamHasToStream=false;
        thermalcamHasToStream =false;
        switchTimeout = 0.1f;
    }
}

void SelStateDayToTherm(float argInDeltaTime)
{
    if(cameraHasToBeOn==true)
    {
        if(DaycamDrawIsRunning()==true)
        {
            DaycamDrawStop();
        }
        if(ThermalIsRunning()==false)
        {
            ThermalDrawStart();
        }

        if(switchTimeout>0)
        {
            switchTimeout-=argInDeltaTime;
        }
        else
        {
            switchTimeout = 0.1f;
            selCurrentState = SEL_THERM;
        }
        //daycamHasToStream=false;
        //thermalcamHasToStream = true;
        daycamHasToStream=true;
        thermalcamHasToStream =true;
    }
    else
    {
        //daycamHasToStream=false;
        //thermalcamHasToStream = false;
        daycamHasToStream=false;
        thermalcamHasToStream =false;
    }
}

void SelStateTherm(float argInDeltaTime)
{
    if(cameraHasToBeOn==true)
    {
        if(selectedCamera==THERMALCAM)
        {
            if(DaycamDrawIsRunning()==true)
            {
                DaycamDrawStop();
            }
            if(ThermalIsRunning()==false)
            {
                ThermalDrawStart();
            }
            //thermalcamHasToStream=true;
            //daycamHasToStream=false;
            daycamHasToStream=true;
            thermalcamHasToStream =true;
        }
        else
        {
            daycamHasToStream=true;
            thermalcamHasToStream =true;
            //daycamHasToStream=true;
            //thermalcamHasToStream = false;
            switchTimeout = 0.1f;
            selCurrentState = SEL_THERM_TO_DAY;
        }
    }
    else
    {
        daycamHasToStream=false;
        thermalcamHasToStream =false;
        //daycamHasToStream=false;
        //thermalcamHasToStream = false;
        switchTimeout = 0.1f;
    }
}

void SelStateThermToDay(float argInDeltaTime)
{
    if(cameraHasToBeOn==true)
    {
        if(DaycamDrawIsRunning()==false)
        {
            DaycamDrawStart();
        }
        if(ThermalIsRunning()==true)
        {
            ThermalDrawStop();
        }

        if(switchTimeout>0)
        {
            switchTimeout-=argInDeltaTime;
        }
        else
        {
            switchTimeout = 0.1f;
            selCurrentState = SEL_DAY;
        }

        daycamHasToStream=true;
        thermalcamHasToStream =true;
        //daycamHasToStream=true;
        //thermalcamHasToStream = false;
    }
    else
    {
        daycamHasToStream=false;
        thermalcamHasToStream =false;
        //daycamHasToStream=false;
        //thermalcamHasToStream = false;
        switchTimeout = 0.1f;
    }
}

void SelStatemachine(float argInDeltaTime)
{
    (*(SelStates[selCurrentState]))(argInDeltaTime);
}

static void InitSelStatemachine()
{
    SelStates[SEL_DAY] = &SelStateDay;
    SelStates[SEL_DAY_TO_THERM] = &SelStateDayToTherm;
    SelStates[SEL_THERM] = &SelStateTherm;
    SelStates[SEL_THERM_TO_DAY] = &SelStateThermToDay;
}



int lastPingCommand = 0;
int lastPingCommandTime = 0;

float turnOffTimeH = 3.0f;
float turnOffTimeC = 3.0f;
float turnOnTimeC = 1.0f;

struct timeval ccTprevFrame, ccTthisFrame;
float ccDeltatime;

enum CONTROLLER_CAMERA_CONTROL_STATES
{
    CCC_OFF,
    CCC_CAMERAS_RUNNING,
    CCC_CAMERAS_WAIT_TURN_OFF,
    CONTROLLER_CAMERA_CONTROL_STATES_COUNT
};

void (*CccStates[CONTROLLER_CAMERA_CONTROL_STATES_COUNT])(float);

static enum CONTROLLER_CAMERA_CONTROL_STATES cccCurrentState;

void CccStateOff(float argInDeltaTime)
{
    if(ccTthisFrame.tv_sec<lastPingCommandTime+1)
    {
        if(camsHeadIsInControl==0)
        {
            turnOnTimeC-=argInDeltaTime;
            if(turnOnTimeC<=0)
            {
                turnOnTimeC = 1.0f;
                cameraHasToBeOn = true;
                cccCurrentState = CCC_CAMERAS_RUNNING;
            }
        }
    }
}

void CccStateCamerasRunning(float argInDeltaTime)
{
    if((ccTthisFrame.tv_sec>lastPingCommandTime+2)||(camsHeadIsInControl==1))
    {
        cameraHasToBeOn = false;
        cccCurrentState = CCC_CAMERAS_WAIT_TURN_OFF;
        camsHeadIsInControl = 1;
    }
    else
    {
        if(cameraHasToBeOn==false)
        {
            cameraHasToBeOn = true;
        }
    }
}

void CccStateCamerasWaitTurnOff(float argInDeltaTime)
{
    turnOffTimeC-=argInDeltaTime;
    if(turnOffTimeC<=0)
    {
        cameraHasToBeOn = false;
        turnOffTimeC = 3.0f;
        cccCurrentState = CCC_OFF;
    }
}


void CccStatemachine(float argInDeltaTime)
{
    (*(CccStates[cccCurrentState]))(argInDeltaTime);
}

static void InitCccStatemachine()
{
    CccStates[CCC_OFF] = &CccStateOff;
    CccStates[CCC_CAMERAS_RUNNING] = &CccStateCamerasRunning;
    CccStates[CCC_CAMERAS_WAIT_TURN_OFF] = &CccStateCamerasWaitTurnOff;
}

////////////////////////////

enum HEAD_CAMERA_CONTROL_STATES
{
    HCC_OFF,
    HCC_CAMERAS_RUNNING,
    HCC_CAMERAS_WAIT_TURN_OFF,
    HEAD_CAMERA_CONTROL_STATES_COUNT
};

void (*HccStates[HEAD_CAMERA_CONTROL_STATES_COUNT])(float);

static enum HEAD_CAMERA_CONTROL_STATES hccCurrentState;

void HccStateOff(float argInDeltaTime)
{
    if(ccTthisFrame.tv_sec>lastPingCommandTime+3)
    {
        cameraHasToBeOn = true;
        camsHeadIsInControl = 1;
        hccCurrentState = HCC_CAMERAS_RUNNING;
    }
    else
    {
        camsHeadIsInControl = 0;
        cameraHasToBeOn = false;
    }
}

void HccStateCamerasRunning(float argInDeltaTime)
{
    camsHeadIsInControl = 1;
    if(ccTthisFrame.tv_sec<lastPingCommandTime+2)
    {
        cameraHasToBeOn = false;
        hccCurrentState = HCC_CAMERAS_WAIT_TURN_OFF;
    }
    else
    {
        cameraHasToBeOn = true;
    }
}

void HccStateCamerasWaitTurnOff(float argInDeltaTime)
{
    turnOffTimeH-=argInDeltaTime;
    if(turnOffTimeH<=0)
    {
        cameraHasToBeOn = false;
        turnOffTimeH = 3.0f;
        hccCurrentState = HCC_OFF;
        camsHeadIsInControl = 0;
    }
}


void HccStatemachine(float argInDeltaTime)
{
    (*(HccStates[hccCurrentState]))(argInDeltaTime);
}

static void InitHccStatemachine()
{
    HccStates[HCC_OFF] = &HccStateOff;
    HccStates[HCC_CAMERAS_RUNNING] = &HccStateCamerasRunning;
    HccStates[HCC_CAMERAS_WAIT_TURN_OFF] = &HccStateCamerasWaitTurnOff;
}


void RunCamerasControll()
{
    gettimeofday(&ccTthisFrame, NULL);
    ccDeltatime = (float)(ccTthisFrame.tv_sec - ccTprevFrame.tv_sec + (ccTthisFrame.tv_usec - ccTprevFrame.tv_usec) * 1e-6);
    ccTprevFrame = ccTthisFrame;

    if(rcThisDeviceType==RC_HeadDevice)
    {
        camsHeadPing++;
        if(lastPingCommand!=commandPing)
        {
            lastPingCommandTime = ccTthisFrame.tv_sec;
            lastPingCommand = commandPing;
        }
        HccStatemachine(ccDeltatime);
    }
    else
    {
        commandPing++;
        if(lastPingCommand!=camsHeadPing)
        {
            lastPingCommandTime = ccTthisFrame.tv_sec;
            lastPingCommand = camsHeadPing;
        }
        CccStatemachine(ccDeltatime);
    }
    SelStatemachine(ccDeltatime);
}

void SWTimerHandlerCameras(size_t argInTimerId, void * arginData)
{
    RunCamerasControll();
}

void InitialiseCamerasController()
{
    struct timeval currentTime;

    gettimeofday(&currentTime,NULL);
    cameraHasToBeOn = false;

    if(rcThisDeviceType==RC_HeadDevice)
    {
        lastPingCommand = commandPing;
        lastPingCommandTime = currentTime.tv_sec;
    }
    else
    {
        lastPingCommandTime = ccTthisFrame.tv_sec;
        lastPingCommand = camsHeadPing;
    }
    InitHccStatemachine();
    InitCccStatemachine();
    InitSelStatemachine();
    StartSoftwareTimer(50, &SWTimerHandlerCameras, TIMER_PERIODIC, NULL);
}

int GetCamerasControllerState()
{
    if(rcThisDeviceType==RC_HeadDevice)
    {
        return (int) hccCurrentState;
    }
    else
    {
        return (int) cccCurrentState;
    }
}
