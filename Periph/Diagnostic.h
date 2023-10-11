#pragma once
# include <stdio.h>
# include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "Configuration/ReadConfig.h"
#include "Periph/GpsDataManager.h"
#include "Periph/CompassDataManager.h"
#include "Periph/RangefinderDataManager.h"
#include "Periph/PicDataManager.h"
#include "Periph/PtuDataManager.h"
#include "Periph/LucidCameraDraw.h"

enum DIAG_DEVICE
{
    DEV_GPS,
    DEV_COMPASS,
    DEV_RANGEFINDER,
    DEV_MB_HEAD,
    DEV_MB_CONTROLLER,
    DEV_PTU,
    DEV_LUCID_CAM,
    DEV_HIK_CAM,
    DIAG_DEVICES_COUNT
};

enum DIAG_STATE
{
    DIAG_NOT_CONFIGURED,
    DIAG_NOT_INITITALISED,
    DIAG_OK,
    DIAG_NOT_OK
};
enum DIAG_STATE GetDeviceDiagState(enum DIAG_DEVICE argInDevice);
void InitialiseDiagnostics();
void HikFrameReceived();
