#pragma once
# include <stdio.h>
# include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "Periph/PeriphScheduler.h"
#include <sys/resource.h>
#include <sys/time.h>
#include "ArenaC/ArenaCApi.h"
#include "SaveC/SaveCApi.h"
#include "Merged/LarDebug.h"
#include "Configuration/ReadConfig.h"
#include <pthread.h>
#include "Periph/CamerasController.h"

extern pthread_mutex_t lucidCameraMut;
extern float frameDeltatime;

bool LcaStopCamera();
bool LcaStartCamera();
void LcaSet(int argInImageWidth, int argInImageHeight, char* argInExposureAuto, char* argInGainAuto, char* argInBalanceWhiteAuto);
void LcaInitCamera();
bool LcaCameraIsStreaming();
void LcaOnUpdateHandler();
void LcaAddOnImageReceived(void* argInOnImageReceived);
bool LcaCameraIsOff();

bool LcaSetOffset(int argInX, int argInY);

