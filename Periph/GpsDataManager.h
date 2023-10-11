#pragma once

#include "GPS.h"

# include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
//#include <wiringPi.h>
#include <sys/time.h>
#include "Configuration/ReadConfig.h"

extern char gdmLattitude[16];
extern char gdmLatNS[1];

extern long gdmLatLastMsgTime;

extern char gdmLongitude[16];
extern char gdmLongEW[1];

extern long gdmLongLastMsgTime;

extern char gdmAltitude[8];
extern char gdmAltitudeSep[8];
extern long gdmAltLastMsgTime;

extern char gdmTime[10];
extern long gdmTimeLastMsgTime;

extern char gdmDate[6];
extern long gdmDateLastMsgTime;

void InitGpsDataManager();

