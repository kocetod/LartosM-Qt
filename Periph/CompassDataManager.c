#include "CompassDataManager.h"


int cdmPitch;
int cdmRoll;
int cdmHeading;
int cdmCmpCalState;
int cdmLastCalResult;
int cdmCalibrationAbort;
long cdmLastMeasurementTimeS;
long cdmLastMeasurementTimeuS;

void CdmReadCalibrationResult(char* argInMessage)
{
    char calResult_lsb = argInMessage[6];
    char calResult_b = argInMessage[5];
    char calResult_msb = argInMessage[4];
    cdmLastCalResult = calResult_lsb + (calResult_b<<4) + (calResult_msb<<8);
}

void CdmReadCompassResult(int argInPitch, int argInRoll, int argInHead)
{
    cdmPitch = argInPitch;
    cdmRoll = argInRoll;
    cdmHeading = argInHead;

    struct timeval currentTime;
    gettimeofday(&currentTime,NULL);
    cdmLastMeasurementTimeS = currentTime.tv_sec;
    cdmLastMeasurementTimeuS = currentTime.tv_usec;

}

void InitCompassDataManager()
{
    if(rcThisDeviceType==RC_HeadDevice)
    {
        CmpAddCustomMessageCallback(CMP_CUS_MSG_CalibrationResult, &CdmReadCalibrationResult);
        AddCompassMeasurementCallback(&CdmReadCompassResult);
    }
}
