#pragma once
//#include <wiringPi.h>
#include "GpioWrapper.h"
#include <stdbool.h>
#include "SoftwareTimer.h"
#include <time.h>

enum BTN_HEAD_INDEX
{
    BTN_HEAD_ON_OFF,
    BTN_HEAD_BRIGHTNESS,
    BTN_HEAD_LRF,
    BTN_HEAD_DAY_IR,
    BTN_HEAD_ZOOM,
    BTN_HEAD_POLARITY,
    BTN_HEAD_SENSOR,
    BTN_HEAD_COUNT
};

bool AddButtonsHead_OnPressedEventCallback(enum BTN_HEAD_INDEX argInButtonName,void* argInCallback);
bool AddButtonsHead_OnReleasedEventCallback(enum BTN_HEAD_INDEX argInButtonName,void* argInCallback);
bool AddButtonsHead_OnHoldPressEventCallback(enum BTN_HEAD_INDEX argInButtonName,void* argInCallback);
bool AddButtonsHead_OnReleaseAfterLongHoldEventCallback(enum BTN_HEAD_INDEX argInButtonName,void* argInCallback);

void InitButtonsHead();

