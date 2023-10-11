#include "global.h"


QLabel *currentVideoPanel = NULL;
int currentVideoPanelX = 1000;
int currentVideoPanelY = 700;

QMutex stoppedMutex;
QMutex stoppedMutex1;
ImageBuffer *imageBuffer;
volatile bool stopped = true;
volatile bool stopped1 = true;
