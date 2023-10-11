#pragma once

#include "Periph/PIC.h"

# include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "Configuration/ReadConfig.h"

extern int admAdcResultHead;
extern int admAdcResultController;

extern long admAdcHeadLastMeasurementTimeS;
extern long admAdcControllerLastMeasurementTimeS;


void InitPicDataManager();
