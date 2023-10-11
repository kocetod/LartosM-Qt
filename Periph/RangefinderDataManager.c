#include "Periph/RangefinderDataManager.h"

float rdmTarget1;
float rdmTarget2;
float rdmTarget3;
long rdmLastMeasurementTimeS;
long rdmLastMeasurementTimeuS;
long rdmLastPingTimeS;

void RdmReadRfResult(float argInTarget1, float argInTarget2, float argInTarget3)
{
    rdmTarget1 = argInTarget1;
    rdmTarget2 = argInTarget2;
    rdmTarget3 = argInTarget3;

    struct timeval currentTime;
    gettimeofday(&currentTime,NULL);
    rdmLastMeasurementTimeS = currentTime.tv_sec;
    rdmLastMeasurementTimeuS = currentTime.tv_usec;

}

void RdmPingReceived()
{
    struct timeval currentTime;
    gettimeofday(&currentTime,NULL);
    rdmLastPingTimeS = currentTime.tv_sec;
}

void InitRangefinderDataManager()
{
    if(rcThisDeviceType==RC_HeadDevice)
    {
        AddRFMeasurementCallback(&RdmReadRfResult);
        AddRFPingCallback(&RdmPingReceived);
    }
}
