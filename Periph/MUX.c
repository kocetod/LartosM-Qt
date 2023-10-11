# include "MUX.h"

static enum MUX_DEVICE_SELECT current = 0;


MuxSelectionData muxSelData[8] =
{
    {0, 0, 0, 0.1f},
    {0, 0, 1, 0.1f},
    {0, 1, 0, 0.1f},
    {0, 1, 1, 0.1f},
    {1, 0, 0, 0.1f},
    {1, 0, 1, 0.1f},
    {1, 1, 0, 0.1f},
    {1, 1, 1, 0.1f}
};


void SelectMuxDevice(enum MUX_DEVICE_SELECT argInDevice)
{
    if(argInDevice!=current)
    {
        muxSelData[current].timeout = 0.1f;
        current = argInDevice;

        if(rcThisDeviceType==RC_HeadDevice)
        {
            GpioWrapSetPinValue(0,muxSelData[current].INH);
            GpioWrapSetPinValue(3,muxSelData[current].A);
            GpioWrapSetPinValue(2,muxSelData[current].B);
        }
    }
}
/*
int GetSelectedDevice()
{
    if(muxSelData[current].timeout==0)
    {
        return current;
    }
    return -1;
}
*/
void MUXInit()
{
    if(rcThisDeviceType==RC_HeadDevice)
    {
        GpioWrapSetPinMode(0,GPIO_MODE_OUT);
        GpioWrapSetPinMode(3,GPIO_MODE_OUT);
        GpioWrapSetPinMode(2,GPIO_MODE_OUT);

        GpioWrapSetPinValue(0,muxSelData[current].INH);
        GpioWrapSetPinValue(3,muxSelData[current].A);
        GpioWrapSetPinValue(2,muxSelData[current].B);
    }
}
/*
void GPIORoutine(float argInElapsedTime)
{
    if(muxSelData[current].timeout>0)
    {
        muxSelData[current].timeout-=argInElapsedTime;
        if(argInElapsedTime<muxSelData[current].timeout)
        {
            muxSelData[current].timeout = 0;
        }
    }
}*/
