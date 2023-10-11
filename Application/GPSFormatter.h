#pragma once
#include "Periph/GPS.h"
#include "Periph/GpsDataManager.h"
# include <stdio.h>
# include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


void GetFormattedValue(char argOutFormattedData[32]);
void GetFormattedDateTime(char argOutFormattedData[32]);
void GetFormattedAltitude(char argOutFormattedData[32]);
void GetFormattedLat(char argOutFormattedData[32]);

void GetFormattedLong(char argOutFormattedData[32]);

