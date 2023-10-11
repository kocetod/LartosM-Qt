#pragma once

#include "Merged/C_Acquisition.h"
#include "esUtil/esUtil.h"
#include <sys/time.h>
#include "Periph/Shaders.h"

void SetZoomThermalCam(float argInValue);

void ThermalDrawStop();

void ThermalDrawStart();

bool ThermalIsRunning();

void* GetHikImageBuffer();

int GetThermalImageWidth();

int GetThermalImageHeight();

void InitialiseHikDraw();
void SetBrightnessThermal(float argInSetting);
float GetBrightnessThermal();
void ThermalImageReceivedCallback(int arginWidth, int arginHeight, void* argInImage);
