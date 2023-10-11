#pragma once

# include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
//#include <wiringPi.h>
#include <sys/time.h>
#include "Configuration/ReadConfig.h" 


extern int commandPing;
extern int commandPerformCalibration;
extern int commandSetCalibrationPointInPlace;
extern int commandPerformMeasurement;
extern int commandShutDown;
extern float commandSetCrosshairPositionX;
extern float commandSetCrosshairPositionY;
