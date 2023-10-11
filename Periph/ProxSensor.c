#include "Periph/ProxSensor.h"

void SensorOn()
{
    GpioWrapRequestTurnOffMonitor();
}

void SensorOff()
{
    GpioWrapRequestTurnOnMonitor();
}

void InitSensor()
{
    AddButtonsHead_OnPressedEventCallback(BTN_HEAD_SENSOR,&SensorOn);
    AddButtonsHead_OnReleasedEventCallback(BTN_HEAD_SENSOR,&SensorOff);
}
