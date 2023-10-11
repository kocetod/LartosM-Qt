#include "GpsDataManager.h"


char gdmLattitude[16];
char gdmLatNS[1];

long gdmLatLastMsgTime;

char gdmLongitude[16];
char gdmLongEW[1];

long gdmLongLastMsgTime;

char gdmAltitude[8];
char gdmAltitudeSep[8];
long gdmAltLastMsgTime;

char gdmTime[10];
long gdmTimeLastMsgTime;

char gdmDate[6];
long gdmDateLastMsgTime;


void GdmSWTimerHandler(size_t argInTimerId, void * arginData)
{
    char lastAltitude[32];
    char lastLatitude[32];
    char lastLongitude[32];

    char lastAltitude_Sep[32];

    char time[32];
    char date[32];
    char latNS[32];
    char longEW[32];

    gdmLatLastMsgTime = GetLatitudeValue(lastLatitude);
    gdmLongLastMsgTime = GetLongitudeValue(lastLongitude);
    GetLongitudeEW(longEW);
    GetLatitudeNS(latNS);
    gdmAltLastMsgTime = GetAltitude_WGS84(lastAltitude);
    GetAltitude_Sep(lastAltitude_Sep);
    gdmTimeLastMsgTime = GetTimeValue(time);
    gdmDateLastMsgTime = GetDateValue(date);

    for(int i=0;i<16;i++){gdmLattitude[i] = lastLatitude[i];}
    for(int i=0;i<1;i++){gdmLatNS[i] = latNS[i];}
    for(int i=0;i<16;i++){gdmLongitude[i] = lastLongitude[i];}
    for(int i=0;i<1;i++){gdmLongEW[i] = longEW[i];}
    for(int i=0;i<8;i++){gdmAltitude[i] = lastAltitude[i];}
    for(int i=0;i<8;i++){gdmAltitudeSep[i] = lastAltitude_Sep[i];}
    for(int i=0;i<10;i++){gdmTime[i] = time[i];}
    for(int i=0;i<6;i++){gdmDate[i] = date[i];}
}


void InitGpsDataManager()
{
    if(rcThisDeviceType==RC_HeadDevice)
    {
        StartSoftwareTimer(150, &GdmSWTimerHandler, TIMER_PERIODIC, NULL);
    }
}
