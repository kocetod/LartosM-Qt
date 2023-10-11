#include "mainwindowhead.h"
#include "ui_mainwindowhead.h"

#include <QDebug>
#include <QDesktopWidget>
#include<QTouchEvent>

extern "C"
{
#include "Periph/ButtonsHead.h"
}

void InitBtnHeadEvents();
