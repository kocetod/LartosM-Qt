#pragma once
# include <stdio.h>
# include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "Periph/PeriphScheduler.h"
//#include <wiringPi.h>
#include "GpioWrapper.h"
#include <sys/time.h>


typedef struct
{
    char msgID[5];
    time_t msgTime;
    struct timeval msgTimeUsec;
    char msg[256];
} GPS_MsgData;

void InitGPS();

void SetSystemTime();
time_t GetLatitudeValue(char argOutLatitude[32]);
time_t GetLongitudeValue(char argOutLatitude[32]);
time_t GetLatitudeNS(char argOutLatitudeNS[32]);
time_t GetLongitudeEW(char argOutLatitudeEW[32]);
time_t GetAltitude_WGS84(char argOutAltitudeWGS84[32]);
time_t GetAltitude_Sep(char argOutAltitudeSep[32]);
time_t GetTimeValue(char argOutTime[32]);
time_t GetDateValue(char argOutDate[32]);
