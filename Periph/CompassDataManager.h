#pragma once

#include "Compass.h"

# include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
//#include <wiringPi.h>
#include <sys/time.h>
#include "Configuration/ReadConfig.h"

extern int cdmPitch;
extern int cdmRoll;
extern int cdmHeading;
extern int cdmCmpCalState;
extern int cdmLastCalResult;
extern int cdmCalibrationAbort;
extern long cdmLastMeasurementTimeS;
extern long cdmLastMeasurementTimeuS;

void InitCompassDataManager();

