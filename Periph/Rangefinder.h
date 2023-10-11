#pragma once
# include <stdio.h>
# include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "PeriphScheduler.h"
#include "GpioWrapper.h"
#include <sys/time.h>
#include "Periph/CommandsDataManager.h">

#include "ButtonsHead.h" 


typedef struct
{
    char msgID;
    char msgDefaultFullLength;
    struct timeval msgTimeUsec;
    char msg[256];
    void (*OnMsgReceive)();
} Rf_MsgData;

void InitRangeFinder();
void RfRequestMeasurement();
bool AddRFMeasurementCallback(void* argInCallback);
bool AddRFPingCallback(void* argInCallback);
