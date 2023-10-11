#pragma once
#include "jRead/jRead.h"

enum RC_DeviceType
{
    RC_NONE = 0,
    RC_HeadDevice = 1,
    RC_Controller = 2
};

extern int rcThisDeviceType;
extern int rcHeadDeviceIp;
extern int rcControllerDeviceIp;
extern int rcPtuIp;
extern int rcPtuPort;
extern int rcPTUDeviceId;
extern int rcLucidCameraIp;
extern int rcRangefinderPointerTurnOn;
extern int rcADCBatteryMin;
extern int rcADCBatteryMax;

extern int rcLucidCameraResX;
extern int rcLucidCameraResY;

extern int rcLucidCameraOffsetX;
extern int rcLucidCameraOffsetY;


extern int rcLucidStreamMaxNumResendRequestsPerImage;
extern int rcLucidGevSCPD;
extern int rcLucidImageTimeout;
extern int rcLucidSystemTimeout;
extern int rcIgnorePing;

extern int rcSkipCalibration;
extern int rcShowDiagnosticBars;


void RcInit();
void RcOnExit();
