#pragma once

#include "Rangefinder.h"

# include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "Configuration/ReadConfig.h"

extern float rdmTarget1;
extern float rdmTarget2;
extern float rdmTarget3;
extern long rdmLastMeasurementTimeS;
extern long rdmLastMeasurementTimeuS;
extern long rdmLastPingTimeS;


void InitRangefinderDataManager();
