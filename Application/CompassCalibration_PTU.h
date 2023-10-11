#pragma once
#include "Periph/PanTiltU.h"
# include <stdio.h>
# include <string.h>
#include <time.h>
#include "Periph/Compass.h"
#include "Periph/CommandsDataManager.h"
#include "Periph/CompassDataManager.h"

extern bool compassIsCalibrated;

void InitCalibrationRoutine();
bool CompassCalibrationIsComplete();
void RequestCaibrationStart();

