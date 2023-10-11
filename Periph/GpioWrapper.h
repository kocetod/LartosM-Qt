#pragma once
#include <stdio.h>
#include "UdpSocket.h"
#include <unistd.h>
#include "SoftwareTimer.h"

enum GPIO_MODES
{
    GPIO_MODE_IN,
    GPIO_MODE_OUT,
    GPIO_MODE_ALT
};

typedef struct
{
    char mode;
    char value;
} GPIO_Data;

void GpioWrapRequestShutDown();
void GpioWrapSetTime(long argInTimeS);


char GpioWrapReadPinValue(unsigned char argInPin);
void GpioWrapSetPinMode(char argInPin, char argInPinMode);

void GpioWrapSetPinValue(char argInPin, char argInPinValue);
void GpioWrapInitGpioWrapper();
void GpioWrapRequestTurnOnMonitor();

void GpioWrapRequestTurnOffMonitor();
