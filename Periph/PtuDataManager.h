#pragma once

#include "PanTiltU.h"

# include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "Configuration/ReadConfig.h"


extern int pdmPan;
extern int pdmTilt;
extern long pdmLastStatusTimeS;
extern long pdmLastStatusTimeuS;


void InitPTUDataManager();
