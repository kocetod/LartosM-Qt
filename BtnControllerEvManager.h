#include "language.h"
#include "ui_language.h"
#include "entering.h"
#include "ui_entering.h"
#include "incorrect.h"
#include "ui_incorrect.h"
#include "calibration.h"
#include "ui_calibration.h"
#include "northAdjustment.h"
#include "ui_northAdjustment.h"
#include "coordinatesystem.h"
#include "ui_coordinatesystem.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mediabrowser.h"
#include "ui_mediabrowser.h"
#include "expanded.h"
#include "ui_expanded.h"
#include "tasks.h"
#include "ui_tasks.h"
#include "menu.h"
#include "ui_menu.h"
#include "resultselection.h"
#include "ui_resultselection.h"

#include <QDebug>
#include <QDesktopWidget>
#include<QTouchEvent>

extern "C"
{
#include "Periph/ButtonsController.h"
}

void InitBtnControllerEvents();
