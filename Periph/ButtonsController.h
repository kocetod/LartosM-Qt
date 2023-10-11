#pragma once
#include "GpioWrapper.h"
#include <stdbool.h>
#include "SoftwareTimer.h"
#include <time.h>

enum BTN_CONTROLLER_INDEX
{
    BTN_CONTROLLER_OK,
    BTN_CONTROLLER_LEFT,
    BTN_CONTROLLER_RIGHT,
    BTN_CONTROLLER_UP,
    BTN_CONTROLLER_DOWN,
    BTN_CONTROLLER_PT_LEFT,
    BTN_CONTROLLER_PT_RIGHT,
    BTN_CONTROLLER_PT_UP,
    BTN_CONTROLLER_PT_DOWN,
    BTN_CONTROLLER_ZOOM_LRF,
    BTN_CONTROLLER_SHUTDOWN,
    BTN_CONTROLLER_COUNT
};

bool AddButtonsController_OnPressedEventCallback(enum BTN_CONTROLLER_INDEX argInButtonName,void* argInCallback);
bool AddButtonsController_OnReleasedEventCallback(enum BTN_CONTROLLER_INDEX argInButtonName,void* argInCallback);
bool AddButtonsController_OnHoldPressEventCallback(enum BTN_CONTROLLER_INDEX argInButtonName,void* argInCallback);
bool AddButtonsController_OnReleaseAfterLongHoldEventCallback(enum BTN_CONTROLLER_INDEX argInButtonName,void* argInCallback);

void InitButtonsController();

