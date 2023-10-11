#include "Periph/PtuDataManager.h"

int pdmPan;
int pdmTilt;
long pdmLastStatusTimeS;
long pdmLastStatusTimeuS;

void PdmReadPTUAngles(int argInPan, int argInTilt)
{
    pdmPan = argInPan;
    pdmTilt = argInTilt;

    struct timeval currentTime;
    gettimeofday(&currentTime,NULL);
    pdmLastStatusTimeS = currentTime.tv_sec;
    pdmLastStatusTimeuS = currentTime.tv_usec;

}

void InitPTUDataManager()
{
    if(rcThisDeviceType==RC_Controller)
    {
        AddPtuStatusCallback(&PdmReadPTUAngles);
    }
}
