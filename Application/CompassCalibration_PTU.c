#include "Application/CompassCalibration_PTU.h"

#define COMPASS_TILT_CORRECTION -15000

enum CCR_STATES
{
    CCR_START_CALIBRATION,
    CCR_WAIT_CALIBRATION_REPLY,
    CCR_REQUEST_GO_TO_POINT,
    CCR_CONFIRM_IN_POINT,
    CCR_SEND_POINT_IN_PLACE,
    CCR_CONFIRM_POINT_IN_PLACE,
    CCR_EVALUATE_CALIBRATION_RESULT,
    CCR_CALIBRATION_ERROR,
    CCR_CALIBRATION_COMPLETE,

    CCR_STATES_COUNT
};

typedef struct
{
    int pan;
    int tilt;
} Ccr_Points_t;

bool calibrationIsRequested = false;
bool compassIsCalibrated = false;
static enum CCR_STATES ccrCurrentState;
int currentPoint = -1;
bool pointError = false;

int evaluationFrameout = 150;

Ccr_Points_t ccrPoints[12] =
{
    {0      ,0/*+COMPASS_TILT_CORRECTION*/},
    {90000  ,0/*+COMPASS_TILT_CORRECTION*/},
    {180000 ,0/*+COMPASS_TILT_CORRECTION*/},
    {270000 ,0/*+COMPASS_TILT_CORRECTION*/},
    {30000  ,30000/*+COMPASS_TILT_CORRECTION*/},
    {120000 ,30000/*+COMPASS_TILT_CORRECTION*/},
    {210000 ,30000/*+COMPASS_TILT_CORRECTION*/},
    {300000 ,30000/*+COMPASS_TILT_CORRECTION*/},
    {60000  ,-45000/*+COMPASS_TILT_CORRECTION*/},
    {150000 ,-45000/*+COMPASS_TILT_CORRECTION*/},
    {240000 ,-45000/*+COMPASS_TILT_CORRECTION*/},
    {330000 ,-45000/*+COMPASS_TILT_CORRECTION*/}
};

bool calibrationHasStarted = false;
void CcrStartCalibrationCallback(char* argInMsg)
{
    calibrationHasStarted=true;
    printf("%s", argInMsg);
}

bool calibrationPointWasSet = false;
void CcrPointIsSetCallback(char* argInMsg)
{
    char calPoint = argInMsg[4];
    if(calPoint==currentPoint+1)
    {
        calibrationPointWasSet=true;
    }
    else
    {
        pointError = true;
    }
}

void RequestCaibrationStart()
{
    if(rcThisDeviceType==RC_HeadDevice)
    {
        cdmCmpCalState = -1;
        cdmCalibrationAbort = 0;
    }
    calibrationIsRequested = true;
    compassIsCalibrated = false;
    ccrCurrentState = CCR_START_CALIBRATION;
    cdmLastCalResult = -1;
}

void Ccr_StartCalibration()
{
    if(rcThisDeviceType==RC_HeadDevice)
    {
        if(CmpIsInCustomMessageMode()==false)
        {
            if(CmpEnterCustomMessageMode()==true)
            {
                CmpSendCustomMessage(CMP_CUS_MSG_CalibrationStart);
                ccrCurrentState = CCR_WAIT_CALIBRATION_REPLY;
            }
        }
        else
        {
            CmpSendCustomMessage(CMP_CUS_MSG_CalibrationStart);
            ccrCurrentState = CCR_WAIT_CALIBRATION_REPLY;
        }
    }
    else
    {
        commandPerformCalibration = 1;
        currentPoint = 0;
        ccrCurrentState = CCR_WAIT_CALIBRATION_REPLY;
    }
}

void Ccr_WaitCalibrationReply()
{
    if(rcThisDeviceType==RC_HeadDevice)
    {
        if(calibrationHasStarted==true)
        {
            calibrationHasStarted = false;
            ccrCurrentState = CCR_REQUEST_GO_TO_POINT;
        }
    }
    else
    {
        ccrCurrentState = CCR_REQUEST_GO_TO_POINT;
    }
}

void Ccr_RequestGoToPoint()
{
    if(rcThisDeviceType==RC_HeadDevice)
    {
        ccrCurrentState = CCR_CONFIRM_IN_POINT;
    }
    else
    {
        if(PtuGoToAbsolutePosition(ccrPoints[currentPoint].pan, ccrPoints[currentPoint].tilt)==true)
        {
            ccrCurrentState = CCR_CONFIRM_IN_POINT;
        }
    }
}
int frameout = 10;
void Ccr_ConfirmInPoint()
{
    if(rcThisDeviceType==RC_HeadDevice)
    {
        frameout--;
        if(frameout<=0)
        {
            frameout = 10;
            ccrCurrentState = CCR_SEND_POINT_IN_PLACE;
        }
    }
    else
    {
        int curPan = PtuGetCurrentPan();
        int curTilt = PtuGetCurrentTilt();

        if(PtuIsOperational()==true)
        {
            if(abs(ccrPoints[currentPoint].pan-curPan)<1000)
            {
                if(abs(ccrPoints[currentPoint].tilt-curTilt)<1000)
                {
                    ccrCurrentState = CCR_SEND_POINT_IN_PLACE;
                }
            }
            else if(abs(ccrPoints[currentPoint].pan-(curPan-360000))<1000)
            {
                if(abs(ccrPoints[currentPoint].tilt-curTilt)<1000)
                {
                    ccrCurrentState = CCR_SEND_POINT_IN_PLACE;
                }
            }

            if(ccrCurrentState==CCR_CONFIRM_IN_POINT)
            {
                ccrCurrentState = CCR_REQUEST_GO_TO_POINT;
            }
        }
    }
}

void Ccr_SendPointInPlace()
{
    if(rcThisDeviceType==RC_HeadDevice)
    {
        if(commandSetCalibrationPointInPlace>currentPoint)
        {
            if(CmpIsInCustomMessageMode()==true)
            {
                CmpSendCustomMessage(CMP_CUS_MSG_CalibrationPointInPlace);
                ccrCurrentState = CCR_CONFIRM_POINT_IN_PLACE;
            }
        }
    }
    else
    {
        commandSetCalibrationPointInPlace = currentPoint;
        ccrCurrentState = CCR_CONFIRM_POINT_IN_PLACE;
    }
} 

int ccrTimeout =10;

void Ccr_ConfirmPointInPlace()
{
    if(rcThisDeviceType==RC_HeadDevice)
    {
        if(calibrationPointWasSet==true)
        {
            currentPoint=commandSetCalibrationPointInPlace;
            cdmCmpCalState = currentPoint;
            calibrationPointWasSet = false;
            if(currentPoint>=11)
            {
                currentPoint = -1;
                ccrCurrentState = CCR_EVALUATE_CALIBRATION_RESULT;
            }
            else
            {
                ccrCurrentState = CCR_REQUEST_GO_TO_POINT;
            }
        }
        else if(pointError==true)
        {
            cdmCalibrationAbort = 1;
            CmpSendCustomMessage(CMP_CUS_MSG_CalibrationAborted);
            ccrCurrentState = CCR_CALIBRATION_COMPLETE;
        }
        else
        {
            ccrTimeout--;
            if(ccrTimeout==0)
            {
                ccrTimeout=10;
                ccrCurrentState = CCR_SEND_POINT_IN_PLACE;
            }
        }
    }
    else
    {
        if(cdmCmpCalState==currentPoint)
        {
            currentPoint++;
            if(currentPoint>=12)
            {
                currentPoint = 0;
                ccrCurrentState = CCR_EVALUATE_CALIBRATION_RESULT;
            }
            else
            {
                ccrCurrentState = CCR_REQUEST_GO_TO_POINT;
            }
        }
        else if(cdmCalibrationAbort==1)
        {
            PtuGoToAbsolutePosition(0, 0);
            ccrCurrentState = CCR_CALIBRATION_COMPLETE;
        }
    }
}

void Ccr_EvaluateCalibrationResult()
{
    if(rcThisDeviceType==RC_HeadDevice)
    {
        evaluationFrameout--;
        if(evaluationFrameout<=0)
        {
            evaluationFrameout = 150;
            CmpExitCustomMessageMode();
            ccrCurrentState = CCR_CALIBRATION_COMPLETE;
        }
        else if(cdmLastCalResult>0)
        {
            evaluationFrameout = 150;
            CmpExitCustomMessageMode();
            ccrCurrentState = CCR_CALIBRATION_COMPLETE;
        }
    }
    else
    {
        PtuGoToAbsolutePosition(0, 0);
        ccrCurrentState = CCR_CALIBRATION_COMPLETE;
    }
}

void Ccr_CalibrationError()
{
    if(rcThisDeviceType==RC_HeadDevice)
    {
        if(pointError==true)
        {
            pointError=false;
            CmpSendCustomMessage(CMP_CUS_MSG_CalibrationDataCleared);
            ccrCurrentState = CCR_CALIBRATION_COMPLETE;
        }
    }
}

void Ccr_CalibrationComplete()
{
    if(rcThisDeviceType==RC_HeadDevice)
    {
        if(pointError==true)
        {
            pointError=false;
            CmpSendCustomMessage(CMP_CUS_MSG_CalibrationDataCleared);
            compassIsCalibrated = false;
        }
        if(CmpIsInCustomMessageMode()==true)
        {
            CmpExitCustomMessageMode();
        }
    }
    else
    {
        PtuGoToAbsolutePosition(0, 0);
    }
    currentPoint = -1;
    pointError = false;
    calibrationIsRequested = false;
    compassIsCalibrated = true;
}

void (*CcrStates[CCR_STATES_COUNT])() =
{
    &Ccr_StartCalibration,
    &Ccr_WaitCalibrationReply,
    &Ccr_RequestGoToPoint,
    &Ccr_ConfirmInPoint,
    &Ccr_SendPointInPlace,
    &Ccr_ConfirmPointInPlace,
    &Ccr_EvaluateCalibrationResult,
    &Ccr_CalibrationError,
    &Ccr_CalibrationComplete

};


void CcrStatemachine()
{
    (*(CcrStates[(int)ccrCurrentState]))();
}


bool CompassCalibrationIsComplete()
{
    return compassIsCalibrated;
}

void CompassCalibrationRoutinePTU()
{
    if(calibrationIsRequested==true)
    {
        if(compassIsCalibrated==false)
        {
            if(PtuIsOperational()==true)
            {
                CcrStatemachine();
            }
        }
    }
}

void CompassCalibrationRoutineCmp()
{
    if(compassIsCalibrated==false)
    {
        if(commandPerformCalibration==1)
        {
            CcrStatemachine();
        }
    }
}

void CompassCalibrationRoutine(size_t argInTimerId, void * arginData)
{
    if(rcThisDeviceType!=RC_HeadDevice)
    {
        CompassCalibrationRoutinePTU();
    }
    else
    {
        CompassCalibrationRoutineCmp();
    }
}

void InitCalibrationRoutine()
{
    StartSoftwareTimer(100, &CompassCalibrationRoutine, TIMER_PERIODIC, NULL);
    CmpAddCustomMessageCallback(CMP_CUS_MSG_CalibrationStart, &CcrStartCalibrationCallback);
    CmpAddCustomMessageCallback(CMP_CUS_MSG_CalibrationPointInPlace, &CcrPointIsSetCallback);
    cdmCmpCalState = -1;
}


