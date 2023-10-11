#ifndef GLOBAL_H
#define GLOBAL_H

#include <QtWidgets/QLabel>
#include "ImageBuffer.h"

extern QLabel *currentVideoPanel;
extern int currentVideoPanelX;
extern int currentVideoPanelY;

extern ImageBuffer *imageBuffer;
extern QMutex stoppedMutex;
extern volatile bool stopped;
extern QMutex stoppedMutex1;
extern volatile bool stopped1;
#endif // GLOBAL_H
