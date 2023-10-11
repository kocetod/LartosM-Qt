#pragma once

#include "Merged/C_Acquisition.h"
#include "esUtil/esUtil.h"
#include <sys/time.h>
#include "Periph/LucidCamera.h"
#include "Merged/C_Acquisition.h"
#include "Periph/Shaders.h"
#include "Periph/RangefinderDataManager.h" 
#include "Periph/Diagnostic.h"
#include <pthread.h> 
#include "Application/SharedVariables.h"


float GetCrosshairDisplacementX();
float GetCrosshairDisplacementY();
void DisplaceCrosshair(float argInDisplacementX, float argInDisplacementY);
void SetCrosshairDisplacementValue(float argInDisplacementX, float argInDisplacementY);

//CameraOffset_Tag Use these - remember that the offset is in pixels.
int GetCrosshairSOPDisplacementX();
int GetCrosshairSOPDisplacementY();
void DisplaceCrosshairSOP(int argInDisplacementX_InPixels, int argInDisplacementY_InPixels);
void SetCrosshairSOPDisplacementValue(int argInDisplacementX_InPixels, int argInDisplacementY_InPixels);
void ShowCrosshairSOP(bool argInShowScreenOffsetPreview);   //Call this when Entering/Exiting the configuration screen

//CameraOffset_Tag Bonus feature
void SetCrosshairColor(float R, float G, float B, float A); //color values are from 0.0f to 1.0f
void SetCrosshairSOPColor(float R, float G, float B, float A);

void SetZoomDayCam(float argInValue);

void DaycamDrawStop();
void DaycamDrawStart();

bool DaycamDrawIsRunning();
bool AddLucidFrameReceivedCallback(void* argInCallback);

void* GetLucidImageBuffer();

void SetGrayscaleOn(bool argInSetting);

bool GetGrayscaleIsOn();

void SetBrightness(float argInSetting);
float GetBrightness();


int GetDaycamImageWidth();

int GetDaycamImageHeight();
void NightImageReceivedCallback(int arginWidth, int arginHeight, void* argInImage);
int InitialiseLucidDraw ();
void DrawDay();
void Shutdown();
