#include "BtnControllerEvManager.h"

Language* FindLanguageWindow()
{
    for(QWidget* pWidget : QApplication::topLevelWidgets())
    {
        Language* pLang = qobject_cast<Language*>(pWidget);
        if (pLang)
        {
            return pLang;
        }
    }
    return nullptr;
}

Entering* FindEnteringWindow()
{
    for(QWidget* pWidget : QApplication::topLevelWidgets())
    {
        Entering* pEnter = qobject_cast<Entering*>(pWidget);
        if (pEnter)
        {
            return pEnter;
        }
    }
    return nullptr;
}

Incorrect* FindIncorrectWindow()
{
    for(QWidget* pWidget : QApplication::topLevelWidgets())
    {
        Incorrect* pIncorr = qobject_cast<Incorrect*>(pWidget);
        if (pIncorr)
        {
            return pIncorr;
        }
    }
    return nullptr;
}

NorthAdjustment* FindNorthAdustmentWindow()
{
    for(QWidget* pWidget : QApplication::topLevelWidgets())
    {
        NorthAdjustment* pNorthAdj = qobject_cast<NorthAdjustment*>(pWidget);
        if (pNorthAdj)
        {
            return pNorthAdj;
        }
    }
    return nullptr;
}

CoordinateSystem* FindCoordinateSystemWindow()
{
    for(QWidget* pWidget : QApplication::topLevelWidgets())
    {
        CoordinateSystem* pCoordSysWin = qobject_cast<CoordinateSystem*>(pWidget);
        if(pCoordSysWin)
        {
            return pCoordSysWin;
        }
    }
    return nullptr;
}

MainWindow* FindMainWindow()
{
    for(QWidget* pWidget : QApplication::topLevelWidgets())
    {
        MainWindow* pMainWin = qobject_cast<MainWindow*>(pWidget);
        if (pMainWin)
        {
            return pMainWin;
        }
    }
    return nullptr;
}

ResultSelection* FindResultSelectionWindow()
{
    for(QWidget* pWidget : QApplication::topLevelWidgets())
    {
        ResultSelection* pResultSel = qobject_cast<ResultSelection*>(pWidget);
        if (pResultSel)
        {
            return pResultSel;
        }
    }
    return nullptr;
}

MediaBrowser* FindMediaBrowserWindow()
{
    for(QWidget* pWidget : QApplication::topLevelWidgets())
    {
        MediaBrowser* pMediaBr = qobject_cast<MediaBrowser*>(pWidget);
        if (pMediaBr)
        {
            return pMediaBr;
        }
    }
    return nullptr;
}

Tasks* FindTasksWindow()
{
    for(QWidget* pWidget : QApplication::topLevelWidgets())
    {
        Tasks* pTasks = qobject_cast<Tasks*>(pWidget);
        if (pTasks)
        {
            return pTasks;
        }
    }
    return nullptr;
}

Menu* FindMenuWindow()
{
    for(QWidget* pWidget : QApplication::topLevelWidgets())
    {
        Menu* pMenu = qobject_cast<Menu*>(pWidget);
        if (pMenu)
        {
            return pMenu;
        }
    }
    return nullptr;
}

Expanded* FindExpandedWindow()
{
    for(QWidget* pWidget : QApplication::topLevelWidgets())
    {
        Expanded* pExp = qobject_cast<Expanded*>(pWidget);
        if (pExp)
        {
            return pExp;
        }
    }
    return nullptr;
}



static void OnBtn_OK_Pressed()
{
    Language* lang = FindLanguageWindow();
    if(lang!=NULL)
    {
        if(lang->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(lang,&Language::gpioBtnOk,Qt::AutoConnection);
        }
    }

    Entering* enter = FindEnteringWindow();
    if(enter!=NULL)
    {
        if(enter->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(enter,&Entering::gpioBtnOk,Qt::AutoConnection);
        }
    }
    Incorrect* incorr = FindIncorrectWindow();
    if(incorr!=NULL)
    {
        if(incorr->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(incorr,&Incorrect::gpioBtnOk,Qt::AutoConnection);
        }
    }

    NorthAdjustment* northAdj = FindNorthAdustmentWindow();
    if(northAdj!=NULL)
    {
        if(northAdj->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(northAdj,&NorthAdjustment::gpioBtnOk,Qt::AutoConnection);
        }
    }

    CoordinateSystem* coordSys = FindCoordinateSystemWindow();
    if(coordSys!=NULL)
    {
        if(coordSys->isActiveWindow() == true)
        {
            QMetaObject::invokeMethod(coordSys,&CoordinateSystem::gpioBtnOk,Qt::AutoConnection);
        }
    }

    MainWindow* mainWin = FindMainWindow();
    if(mainWin!=NULL)
    {
        if(mainWin->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(mainWin,&MainWindow::gpioBtnOk,Qt::AutoConnection);
        }
    }

    ResultSelection* resultSel = FindResultSelectionWindow();
    if(resultSel!=NULL)
    {
        if(resultSel->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(resultSel,&ResultSelection::gpioBtnOk,Qt::AutoConnection);
        }
    }

    MediaBrowser* mediaBr = FindMediaBrowserWindow();
    if(mediaBr!=NULL)
    {
        if(mediaBr->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(mediaBr,&MediaBrowser::gpioBtnOk,Qt::AutoConnection);
        }
    }

    Tasks* tasks = FindTasksWindow();
    if(tasks!=NULL)
    {
        if(tasks->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(tasks,&Tasks::gpioBtnOk,Qt::AutoConnection);
        }
    }

    Menu* menu = FindMenuWindow();
    if(menu!=NULL)
    {
        if(menu->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(menu,&Menu::gpioBtnOk,Qt::AutoConnection);
        }
    }

    Expanded* exp = FindExpandedWindow();
    if(exp!=NULL)
    {
        if(exp->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(exp,&Expanded::gpioBtnOk,Qt::AutoConnection);
        }
    }
}


static void OnBtn_LEFT_Pressed()
{
    Language* lang = FindLanguageWindow();
    if(lang!=NULL)
    {
        if(lang->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(lang,&Language::gpioBtnLeft,Qt::AutoConnection);
        }
    }

    Entering* enter = FindEnteringWindow();
    if(enter!=NULL)
    {
        if(enter->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(enter,&Entering::gpioBtnLeft,Qt::AutoConnection);
        }
    }

    NorthAdjustment* northAdj = FindNorthAdustmentWindow();
    if(northAdj!=NULL)
    {
        if(northAdj->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(northAdj,&NorthAdjustment::gpioBtnLeft,Qt::AutoConnection);
        }
    }

    CoordinateSystem* coordSys = FindCoordinateSystemWindow();
    if(coordSys!=NULL)
    {
        if(coordSys->isActiveWindow() == true)
        {
            QMetaObject::invokeMethod(coordSys,&CoordinateSystem::gpioBtnLeft,Qt::AutoConnection);
        }
    }

    MainWindow* mainWin = FindMainWindow();
    if(mainWin!=NULL)
    {
        if(mainWin->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(mainWin,&MainWindow::gpioBtnLeft,Qt::AutoConnection);
        }
    }

    ResultSelection* resultSel = FindResultSelectionWindow();
    if(resultSel!=NULL)
    {
        if(resultSel->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(resultSel,&ResultSelection::gpioBtnLeft,Qt::AutoConnection);
        }
    }

    MediaBrowser* mediaBr = FindMediaBrowserWindow();
    if(mediaBr!=NULL)
    {
        if(mediaBr->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(mediaBr,&MediaBrowser::gpioBtnLeft,Qt::AutoConnection);
        }
    }

    Tasks* tasks = FindTasksWindow();
    if(tasks!=NULL)
    {
        if(tasks->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(tasks,&Tasks::gpioBtnLeft,Qt::AutoConnection);
        }
    }

    Menu* menu = FindMenuWindow();
    if(menu!=NULL)
    {
        if(menu->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(menu,&Menu::gpioBtnLeft,Qt::AutoConnection);
        }
    }

    Expanded* exp = FindExpandedWindow();
    if(exp!=NULL)
    {
        if(exp->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(exp,&Expanded::gpioBtnLeft,Qt::AutoConnection);
        }
    }
}


static void OnBtn_RIGHT_Pressed()
{
    Language* lang = FindLanguageWindow();
    if(lang!=NULL)
    {
        if(lang->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(lang,&Language::gpioBtnRight,Qt::AutoConnection);
        }
    }

    Entering* enter = FindEnteringWindow();
    if(enter!=NULL)
    {
        if(enter->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(enter,&Entering::gpioBtnRight,Qt::AutoConnection);
        }
    }

    NorthAdjustment* northAdj = FindNorthAdustmentWindow();
    if(northAdj!=NULL)
    {
        if(northAdj->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(northAdj,&NorthAdjustment::gpioBtnRight,Qt::AutoConnection);
        }
    }

    CoordinateSystem* coordSys = FindCoordinateSystemWindow();
    if(coordSys!=NULL)
    {
        if(coordSys->isActiveWindow() == true)
        {
            QMetaObject::invokeMethod(coordSys,&CoordinateSystem::gpioBtnRight,Qt::AutoConnection);
        }
    }

    MainWindow* mainWin = FindMainWindow();
    if(mainWin!=NULL)
    {
        if(mainWin->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(mainWin,&MainWindow::gpioBtnRight,Qt::AutoConnection);
        }
    }

    ResultSelection* resultSel = FindResultSelectionWindow();
    if(resultSel!=NULL)
    {
        if(resultSel->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(resultSel,&ResultSelection::gpioBtnRight,Qt::AutoConnection);
        }
    }

    MediaBrowser* mediaBr = FindMediaBrowserWindow();
    if(mediaBr!=NULL)
    {
        if(mediaBr->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(mediaBr,&MediaBrowser::gpioBtnRight,Qt::AutoConnection);
        }
    }

    Tasks* tasks = FindTasksWindow();
    if(tasks!=NULL)
    {
        if(tasks->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(tasks,&Tasks::gpioBtnRight,Qt::AutoConnection);
        }
    }

    Menu* menu = FindMenuWindow();
    if(menu!=NULL)
    {
        if(menu->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(menu,&Menu::gpioBtnRight,Qt::AutoConnection);
        }
    }

    Expanded* exp = FindExpandedWindow();
    if(exp!=NULL)
    {
        if(exp->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(exp,&Expanded::gpioBtnRight,Qt::AutoConnection);
        }
    }
}


static void OnBtn_UP_Pressed()
{
    Entering* enter = FindEnteringWindow();
    if(enter!=NULL)
    {
        if(enter->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(enter,&Entering::gpioBtnUp,Qt::AutoConnection);
        }
    }

    NorthAdjustment* northAdj = FindNorthAdustmentWindow();
    if(northAdj!=NULL)
    {
        if(northAdj->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(northAdj,&NorthAdjustment::gpioBtnUp,Qt::AutoConnection);
        }
    }

    CoordinateSystem* coordSys = FindCoordinateSystemWindow();
    if(coordSys!=NULL)
    {
        if(coordSys->isActiveWindow() == true)
        {
            QMetaObject::invokeMethod(coordSys,&CoordinateSystem::gpioBtnUp,Qt::AutoConnection);
        }
    }

    MainWindow* mainWin = FindMainWindow();
    if(mainWin!=NULL)
    {
        if(mainWin->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(mainWin,&MainWindow::gpioBtnUp,Qt::AutoConnection);
        }
    }

    Tasks* tasks = FindTasksWindow();
    if(tasks!=NULL)
    {
        if(tasks->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(tasks,&Tasks::gpioBtnUp,Qt::AutoConnection);
        }
    }

    Menu* menu = FindMenuWindow();
    if(menu!=NULL)
    {
        if(menu->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(menu,&Menu::gpioBtnUp,Qt::AutoConnection);
        }
    }

    Expanded* exp = FindExpandedWindow();
    if(exp!=NULL)
    {
        if(exp->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(exp,&Expanded::gpioBtnUp,Qt::AutoConnection);
        }
    }
}


static void OnBtn_DOWN_Pressed()
{
    Entering* enter = FindEnteringWindow();
    if(enter!=NULL)
    {
        if(enter->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(enter,&Entering::gpioBtnDown,Qt::AutoConnection);
        }
    }

    NorthAdjustment* northAdj = FindNorthAdustmentWindow();
    if(northAdj!=NULL)
    {
        if(northAdj->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(northAdj,&NorthAdjustment::gpioBtnDown,Qt::AutoConnection);
        }
    }

    CoordinateSystem* coordSys = FindCoordinateSystemWindow();
    if(coordSys!=NULL)
    {
        if(coordSys->isActiveWindow() == true)
        {
            QMetaObject::invokeMethod(coordSys, &CoordinateSystem::gpioBtnDown,Qt::AutoConnection);
        }
    }

    MainWindow* mainWin = FindMainWindow();
    if(mainWin!=NULL)
    {
        if(mainWin->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(mainWin,&MainWindow::gpioBtnDown,Qt::AutoConnection);
        }
    }

    Tasks* tasks = FindTasksWindow();
    if(tasks!=NULL)
    {
        if(tasks->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(tasks,&Tasks::gpioBtnDown,Qt::AutoConnection);
        }
    }

    Menu* menu = FindMenuWindow();
    if(menu!=NULL)
    {
        if(menu->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(menu,&Menu::gpioBtnDown,Qt::AutoConnection);
        }
    }

    Expanded* exp = FindExpandedWindow();
    if(exp!=NULL)
    {
        if(exp->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(exp,&Expanded::gpioBtnDown,Qt::AutoConnection);
        }
    }
}

static void OnBtn_PANTILT_UP_Pressed()
{
    MainWindow* mainWin = FindMainWindow();
    if(mainWin!=NULL)
    {
        if(mainWin->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(mainWin,&MainWindow::gpioBtnPantiltUpPressed,Qt::AutoConnection);
        }
    }

    Expanded* exp = FindExpandedWindow();
    if(exp!=NULL)
    {
        if(exp->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(exp,&Expanded::gpioBtnPantiltUpPressed,Qt::AutoConnection);
        }
    }
}

static void OnBtn_PANTILT_UP_Released()
{
    MainWindow* mainWin = FindMainWindow();
    if(mainWin!=NULL)
    {
        if(mainWin->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(mainWin,&MainWindow::gpioBtnPantiltUpReleased,Qt::AutoConnection);
        }
    }

    Expanded* exp = FindExpandedWindow();
    if(exp!=NULL)
    {
        if(exp->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(exp,&Expanded::gpioBtnPantiltUpReleased,Qt::AutoConnection);
        }
    }
}

static void OnBtn_PANTILT_DOWN_Pressed()
{
    MainWindow* mainWin = FindMainWindow();
    if(mainWin!=NULL)
    {
        if(mainWin->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(mainWin,&MainWindow::gpioBtnPantiltDownPressed,Qt::AutoConnection);
        }
    }

    Expanded* exp = FindExpandedWindow();
    if(exp!=NULL)
    {
        if(exp->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(exp,&Expanded::gpioBtnPantiltDownPressed,Qt::AutoConnection);
        }
    }
}

static void OnBtn_PANTILT_DOWN_Released()
{
    MainWindow* mainWin = FindMainWindow();
    if(mainWin!=NULL)
    {
        if(mainWin->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(mainWin,&MainWindow::gpioBtnPantiltDownReleased,Qt::AutoConnection);
        }
    }

    Expanded* exp = FindExpandedWindow();
    if(exp!=NULL)
    {
        if(exp->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(exp,&Expanded::gpioBtnPantiltDownReleased,Qt::AutoConnection);
        }
    }
}

static void OnBtn_PANTILT_LEFT_Pressed()
{
    MainWindow* mainWin = FindMainWindow();
    if(mainWin!=NULL)
    {
        if(mainWin->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(mainWin,&MainWindow::gpioBtnPantiltLeftPressed,Qt::AutoConnection);
        }
    }

    Expanded* exp = FindExpandedWindow();
    if(exp!=NULL)
    {
        if(exp->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(exp,&Expanded::gpioBtnPantiltLeftPressed,Qt::AutoConnection);
        }
    }
}

static void OnBtn_PANTILT_LEFT_Released()
{
    MainWindow* mainWin = FindMainWindow();
    if(mainWin!=NULL)
    {
        if(mainWin->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(mainWin,&MainWindow::gpioBtnPantiltLeftReleased,Qt::AutoConnection);
        }
    }

    Expanded* exp = FindExpandedWindow();
    if(exp!=NULL)
    {
        if(exp->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(exp,&Expanded::gpioBtnPantiltLeftReleased,Qt::AutoConnection);
        }
    }
}

static void OnBtn_PANTILT_RIGHT_Pressed()
{
    MainWindow* mainWin = FindMainWindow();
    if(mainWin!=NULL)
    {
        if(mainWin->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(mainWin,&MainWindow::gpioBtnPantiltRightPressed,Qt::AutoConnection);
        }
    }

    Expanded* exp = FindExpandedWindow();
    if(exp!=NULL)
    {
        if(exp->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(exp,&Expanded::gpioBtnPantiltRightPressed,Qt::AutoConnection);
        }
    }
}

static void OnBtn_PANTILT_RIGHT_Released()
{
    MainWindow* mainWin = FindMainWindow();
    if(mainWin!=NULL)
    {
        if(mainWin->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(mainWin,&MainWindow::gpioBtnPantiltRightReleased,Qt::AutoConnection);
        }
    }

    Expanded* exp = FindExpandedWindow();
    if(exp!=NULL)
    {
        if(exp->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(exp,&Expanded::gpioBtnPantiltRightReleased,Qt::AutoConnection);
        }
    }
}

static void OnBtn_ZOOM_Pressed()
{
    Expanded* exp = FindExpandedWindow();
    MainWindow* mainWin = FindMainWindow();
    if(mainWin!=NULL)
    {
        if(mainWin->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(mainWin,&MainWindow::gpioBtnZoom,Qt::AutoConnection);
        }
    }
    if(exp!=NULL)
    {
         if(exp->isActiveWindow()==true)
         {
             QMetaObject::invokeMethod(exp,&Expanded::gpioBtnZoom,Qt::AutoConnection);
         }
    }
}

static void OnBtn_LRF_Pressed()
{
    Expanded* exp = FindExpandedWindow();
    MainWindow* mainWin = FindMainWindow();
    if(mainWin!=NULL)
    {
        if(mainWin->isActiveWindow()==true)
        {
            QMetaObject::invokeMethod(mainWin,&MainWindow::gpioBtnLrf,Qt::AutoConnection);
        }
    }
    if(exp!=NULL)
    {
         if(exp->isActiveWindow()==true)
         {
             QMetaObject::invokeMethod(exp,&Expanded::gpioBtnLrf,Qt::AutoConnection);
         }
    }
}


/*Trqbva da se izvika kogato i da e sled MainUtil(). V momenta i dvete sa v na4aloto na main. */
void InitBtnControllerEvents()
{
    AddButtonsController_OnPressedEventCallback(BTN_CONTROLLER_OK,(void*)&OnBtn_OK_Pressed);
    AddButtonsController_OnPressedEventCallback(BTN_CONTROLLER_UP,(void*)&OnBtn_UP_Pressed);
    AddButtonsController_OnPressedEventCallback(BTN_CONTROLLER_DOWN,(void*)&OnBtn_DOWN_Pressed);
    AddButtonsController_OnPressedEventCallback(BTN_CONTROLLER_LEFT,(void*)&OnBtn_LEFT_Pressed);
    AddButtonsController_OnPressedEventCallback(BTN_CONTROLLER_RIGHT,(void*)&OnBtn_RIGHT_Pressed);

    AddButtonsController_OnPressedEventCallback(BTN_CONTROLLER_PT_UP,(void*)&OnBtn_PANTILT_UP_Pressed);
    AddButtonsController_OnPressedEventCallback(BTN_CONTROLLER_PT_DOWN,(void*)&OnBtn_PANTILT_DOWN_Pressed);
    AddButtonsController_OnPressedEventCallback(BTN_CONTROLLER_PT_LEFT,(void*)&OnBtn_PANTILT_LEFT_Pressed);
    AddButtonsController_OnPressedEventCallback(BTN_CONTROLLER_PT_RIGHT,(void*)&OnBtn_PANTILT_RIGHT_Pressed);

    AddButtonsController_OnReleasedEventCallback(BTN_CONTROLLER_PT_UP,(void*)&OnBtn_PANTILT_UP_Released);
    AddButtonsController_OnReleasedEventCallback(BTN_CONTROLLER_PT_DOWN,(void*)&OnBtn_PANTILT_DOWN_Released);
    AddButtonsController_OnReleasedEventCallback(BTN_CONTROLLER_PT_LEFT,(void*)&OnBtn_PANTILT_LEFT_Released);
    AddButtonsController_OnReleasedEventCallback(BTN_CONTROLLER_PT_RIGHT,(void*)&OnBtn_PANTILT_RIGHT_Released);

    AddButtonsController_OnReleasedEventCallback(BTN_CONTROLLER_ZOOM_LRF,(void*)&OnBtn_ZOOM_Pressed);
    AddButtonsController_OnReleaseAfterLongHoldEventCallback(BTN_CONTROLLER_ZOOM_LRF,(void*)&OnBtn_LRF_Pressed);
}
