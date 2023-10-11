#include "Periph/PicDataManager.h"

int admAdcResultHead;
int admAdcResultController;

long admAdcHeadLastMeasurementTimeS;
long admAdcControllerLastMeasurementTimeS;

void admMeasureReceived(int argInMeasurementResult)
{
    struct timeval currentTime;
    gettimeofday(&currentTime,NULL);
    if(rcThisDeviceType==RC_HeadDevice)
    {
        admAdcResultHead = argInMeasurementResult;
        admAdcHeadLastMeasurementTimeS = currentTime.tv_sec;
    }
    else
    {
        admAdcResultController = argInMeasurementResult;
        admAdcControllerLastMeasurementTimeS = currentTime.tv_sec;
    }
}

void InitPicDataManager()
{
    AddPicMeasureCallback(admMeasureReceived);
}
