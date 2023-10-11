#pragma once
#include <stdbool.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
//#include <wiringPi.h>

#include "MUX.h"
#include "Uart.h"
#include "SoftwareTimer.h"

typedef struct
{
    bool isValid;
    enum MUX_DEVICE_SELECT device;
    int currentPriority;
    bool isInterruptible;
    int requiredComSpeed;
    bool isSwitchingTo;
    bool isCurrent;
    void (*OnUpdate)(float);
    void (*Receive)(char);
} Com_User;


void InitScheduler();

bool PS_AddUser(enum MUX_DEVICE_SELECT argInDevice,void* argInOnUpdate,void* argInReceive);

bool PS_IsCurrent(enum MUX_DEVICE_SELECT argInDevice);
bool PS_IsSwitchingTo(enum MUX_DEVICE_SELECT argInDevice);

void PS_SetPriority(enum MUX_DEVICE_SELECT argInDevice, int argInPriority);
void PS_SetInterruptable(enum MUX_DEVICE_SELECT argInDevice, bool argInIsInterruptible);
void PeriphSchedulerRoutine(float argInDeltaTime);
void PS_Send(enum MUX_DEVICE_SELECT argInDevice,void* argInData, int argInSize);
void PS_SetRequiredComSpeed(enum MUX_DEVICE_SELECT argInDevice, int argInReqSpeed);






