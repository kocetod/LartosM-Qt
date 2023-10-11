#pragma once
# include <stdio.h>
# include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "Periph/PeriphScheduler.h"
#include <sys/time.h>

#include "Periph/ButtonsHead.h"
#include "Periph/ButtonsController.h"

typedef struct
{
    char msgID;
    struct timeval msgTimeUsec;
    char msg[256];
    void (*OnMsgReceive)();
} Pic_MsgData;

bool ShutdownStarted();
void RequestShutdown();
bool AddPicMeasureCallback(void* argInCallback);
void InitPicMcu();
int GetLastBatteryMeasurement();
