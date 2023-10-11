#pragma once
//#include <wiringPi.h>
//#include <wiringPiI2C.h>

#include "GpioWrapper.h"
#include "Configuration/ReadConfig.h"
#include <stdbool.h>


enum MUX_DEVICE_SELECT
{
    MUX_DEVICE_0,
    MUX_DEVICE_1,
    MUX_DEVICE_2,
    MUX_DEVICE_3,
    MUX_DEVICE_4,
    MUX_DEVICE_5,
    MUX_DEVICE_6,
    MUX_DEVICE_7
};

typedef struct
{
    int INH;
    int A;
    int B;
    float timeout;
} MuxSelectionData;

void MUXInit();
void GPIORoutine(float argInElapsedTime);
void SelectMuxDevice(enum MUX_DEVICE_SELECT argInDevice);
int GetSelectedDevice();

