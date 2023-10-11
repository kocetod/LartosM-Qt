#pragma once
# include <stdio.h>
# include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "Configuration/ReadConfig.h"
#include "Periph/SoftwareTimer.h"
#include "Periph/CommandsDataManager.h"
#include "Periph/LucidCamera.h"
#include "Periph/LucidCameraDraw.h"
#include "Periph/CamerasDataManager.h"

extern bool cameraHasToBeOn;
extern bool daycamHasToStream;
extern bool thermalcamHasToStream;

enum CAMERAS
{
    DAYCAM,
    THERMALCAM,
    CAMERAS_COUNT
};

enum CAMERAS GetSelectedCamera();
bool SelectCamera(enum CAMERAS arginCameraToSelect);
void InitialiseCamerasController();
int GetCamerasControllerState();
