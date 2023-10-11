# include "CompassCalibration_PTU.h"


/*
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
    CCR_CALIBRATION_COMPLETE,

    CCR_STATES_COUNT
};

typedef struct
{
    int pan;
    int tilt;
} Ccr_Points_t;

bool calibrationIsInitialised = false;
bool compassIsCalibrated = true;
static enum CCR_STATES ccrCurrentState;
int currentPoint = 0;

Ccr_Points_t ccrPoints[12] =
{
    {0      ,0},
    {90000  ,0},
    {180000 ,0},
    {270000 ,0},
    {30000  ,30000},
    {120000 ,30000},
    {210000 ,30000},
    {300000 ,30000},
    {60000  ,-45000},
    {150000 ,-45000},
    {240000 ,-45000},
    {330000 ,-45000}
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
    calibrationPointWasSet=true;
    printf("%s", argInMsg);
}


void Ccr_StartCalibration()
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

void Ccr_WaitCalibrationReply()
{
    if(calibrationHasStarted==true)
    {
        calibrationHasStarted = false;
        ccrCurrentState = CCR_REQUEST_GO_TO_POINT;
    }
}

void Ccr_RequestGoToPoint()
{
    if(PtuGoToAbsolutePosition(ccrPoints[currentPoint].pan, ccrPoints[currentPoint].tilt)==true)
    {
        ccrCurrentState = CCR_CONFIRM_IN_POINT;
    }
}
void Ccr_ConfirmInPoint()
{
    int curPan = PtuGetCurrentPan();
    int curTilt = PtuGetCurrentTilt();

    if(abs(ccrPoints[currentPoint].pan-curPan)<1000)
    {
        if(abs(ccrPoints[currentPoint].tilt-curTilt)<1000)
        {
            ccrCurrentState = CCR_SEND_POINT_IN_PLACE;
        }
    }
}

void Ccr_SendPointInPlace()
{
    if(CmpIsInCustomMessageMode()==true)    {
        CmpSendCustomMessage(CMP_CUS_MSG_CalibrationPointInPlace);
        ccrCurrentState = CCR_CONFIRM_POINT_IN_PLACE;
    }
}

void Ccr_ConfirmPointInPlace()
{
    if(calibrationPointWasSet==true)
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
        calibrationPointWasSet = false;
    }
}

void Ccr_EvaluateCalibrationResult()
{
    if(CmpIsInCustomMessageMode()==false)
    {
        CmpExitCustomMessageMode();
    }
    PtuGoToAbsolutePosition(0, 0);
    compassIsCalibrated = true;
    ccrCurrentState = CCR_CALIBRATION_COMPLETE;
}

void Ccr_CalibrationComplete()
{
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

void CompassCalibrationRoutine()
{
    if(calibrationIsInitialised==false)
    {
        if(CmpAddCustomMessageCallback(CMP_CUS_MSG_CalibrationStart, &CcrStartCalibrationCallback)==true)
        {
            if(CmpAddCustomMessageCallback(CMP_CUS_MSG_CalibrationPointInPlace, &CcrPointIsSetCallback)==true)
            {
                calibrationIsInitialised = true;
            }
        }
    }
    else
    {
        if(compassIsCalibrated==false)
        {
            if(PtuIsOperational()==true)
            {
                CcrStatemachine();
            }
        }
    }
}*/


