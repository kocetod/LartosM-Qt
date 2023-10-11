# include "GpioWrapper.h"


char gpioStatMessage[256];


GPIO_Data gpioData[30] =
{
    {(char)GPIO_MODE_IN,0},
    {(char)GPIO_MODE_IN,0},
    {(char)GPIO_MODE_IN,0},
    {(char)GPIO_MODE_IN,0},
    {(char)GPIO_MODE_IN,0},
    {(char)GPIO_MODE_IN,0},
    {(char)GPIO_MODE_IN,0},
    {(char)GPIO_MODE_IN,0},
    {(char)GPIO_MODE_IN,0},
    {(char)GPIO_MODE_IN,0},

    {(char)GPIO_MODE_ALT,0},
    {(char)GPIO_MODE_ALT,0},
    {(char)GPIO_MODE_ALT,0},
    {(char)GPIO_MODE_ALT,0},
    {(char)GPIO_MODE_ALT,0},
    {(char)GPIO_MODE_IN,0},
    {(char)GPIO_MODE_IN,0},
    {(char)GPIO_MODE_IN,0},
    {(char)GPIO_MODE_IN,0},
    {(char)GPIO_MODE_IN,0},

    {(char)GPIO_MODE_IN,0},
    {(char)GPIO_MODE_IN,0},
    {(char)GPIO_MODE_IN,0},
    {(char)GPIO_MODE_IN,0},
    {(char)GPIO_MODE_IN,0},
    {(char)GPIO_MODE_ALT,0},
    {(char)GPIO_MODE_IN,0},
    {(char)GPIO_MODE_IN,0},
    {(char)GPIO_MODE_ALT,0},
    {(char)GPIO_MODE_ALT,0}

};

int mySock = -1;
char gpioMessage[32];

char GpioWrapReadPinValue(unsigned char argInPin)
{
    if(argInPin<30)
    {
        return gpioData[argInPin].value;
    }
    return 0;
}

void GpioWrapSetPinMode(char argInPin, char argInPinMode)
{
    memset(&(gpioMessage),0,32);
    gpioMessage[0] = 'M';
    gpioMessage[1] = argInPin;
    gpioMessage[2] = argInPinMode;
    UdpSend(mySock,gpioMessage,32);
}

void GpioWrapSetPinValue(char argInPin, char argInPinValue)
{
    memset(&(gpioMessage),0,32);
    gpioMessage[0] = 'V';
    gpioMessage[1] = argInPin;
    gpioMessage[2] = argInPinValue;
    UdpSend(mySock,gpioMessage,32);
}

void GpioWrapRequestTurnOnMonitor()
{
    memset(&(gpioMessage),0,32);
    gpioMessage[0] = 'N';
    UdpSend(mySock,gpioMessage,32);
}

void GpioWrapRequestTurnOffMonitor()
{
    memset(&(gpioMessage),0,32);
    gpioMessage[0] = 'F';
    UdpSend(mySock,gpioMessage,32);
}

void GpioWrapRequestShutDown()
{
    memset(&(gpioMessage),0,32);
    gpioMessage[0] = 'S';
    UdpSend(mySock,gpioMessage,32);
}

void GpioWrapSetTime(long argInTimeS)
{
    memset(&(gpioMessage),0,32);
    gpioMessage[0] = 'T';

    unsigned char *bytePtr=(unsigned char*)(&argInTimeS);
    for(int i =0; i<8;i++)
    {
        gpioMessage[1+i] = bytePtr[i];
    }

    UdpSend(mySock,gpioMessage,32);
}

void GPIOWrapOnReceive(void* argInSocketData)
{
    Udp_SocketData* mySData = (Udp_SocketData*)(argInSocketData);

    int currentInd = 0;
    for(int i = 0;i<30;i++)
    {
        gpioData[i].mode = (char)mySData->buffer[currentInd];
        currentInd++;
        gpioData[i].value = (char)mySData->buffer[currentInd];
        currentInd++;
    }
    UdpSocketClearReceiveBuffer(mySock);
}

void GpioWrapInitGpioWrapper()
{
    mySock = UdpCreateSocket(17001,17000,"127.0.0.1",GPIOWrapOnReceive);
}
