#pragma once
#include <math.h>
#include <sys/time.h>
#include "UdpSocket.h"
#include "SoftwareTimer.h"
#include "Configuration/ReadConfig.h"

#define PTU_MAX_MSG_LENGTH 256

typedef struct
{
    char msgID;
    struct timeval msgTimeUsec;
    char msg[PTU_MAX_MSG_LENGTH];
    void (*OnMsgReceive)();
} Ptu_MsgData;

void PtuInit();
bool PtuIsOperational();
bool PtuGoToAbsolutePosition(int argInTargetPan, int argInTargetTilt);
void PtuRegisterPanProvider(void* argInPanProvider);
void PtuRegisterTiltProvider(void* argInTiltProvider);
int PtuGetCurrentPan();
int PtuGetCurrentTilt();
bool AddPtuStatusCallback(void* argInCallback);
