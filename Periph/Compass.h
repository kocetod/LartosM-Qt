#pragma once
# include <stdio.h>
# include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "Periph/PeriphScheduler.h"
#include "GpioWrapper.h"
#include <sys/time.h>

enum CMP_CUSTOM_MSG_INDEX
{
    CMP_CUS_MSG_NONE,
    CMP_CUS_MSG_RequestPitchRollHeading,
    CMP_CUS_MSG_CalibrationStart,
    CMP_CUS_MSG_CalibrationPointInPlace,
    CMP_CUS_MSG_CalibrationAborted,
    CMP_CUS_MSG_CalibrationResult,
    CMP_CUS_MSG_CalibrationDataCleared,
    CMP_CUS_MSG_COUNT
};

typedef struct
{
    char msgID;
    struct timeval msgTimeUsec;
    char msg[256];
    void (*OnMsgReceive)();
} Cmp_MsgData;

bool CmpIsInCustomMessageMode();
bool CmpExitCustomMessageMode();
bool CmpEnterCustomMessageMode();
void CmpSendCustomMessage(enum CMP_CUSTOM_MSG_INDEX argInCustomMessage);

bool AddCompassMeasurementCallback(void* argInCallback);
bool CmpAddCustomMessageCallback(enum CMP_CUSTOM_MSG_INDEX argInCustomMessage, void* argInCallback);
void InitCompass();

