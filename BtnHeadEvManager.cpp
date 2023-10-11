#include "BtnHeadEvManager.h"

MainWindowHead* FindMainWindowHead()
{
    for(QWidget* pWidget : QApplication::topLevelWidgets())
    {
        MainWindowHead* pHead = qobject_cast<MainWindowHead*>(pWidget);
        if (pHead)
        {
            return pHead;
        }
    }
    return nullptr;
}

static void OnBtn_Brightness_Pressed()
{
    MainWindowHead* head = FindMainWindowHead();
    if(head!=NULL)
    {
        if(head->isVisible()==true)
        {
            QMetaObject::invokeMethod(head,&MainWindowHead::btnBrightness_pressed,Qt::AutoConnection);
        }
    }
}

static void OnBtn_Brightness_Released()
{
    MainWindowHead* head = FindMainWindowHead();
    if(head!=NULL)
    {
        if(head->isVisible()==true)
        {
            QMetaObject::invokeMethod(head,&MainWindowHead::btnBrightness_released,Qt::AutoConnection);
        }
    }
}

static void OnBtn_Screenshot_Released()
{
    MainWindowHead* head = FindMainWindowHead();
    if(head!=NULL)
    {
        if(head->isVisible()==true)
        {
            QMetaObject::invokeMethod(head,&MainWindowHead::btnScreenshot_released,Qt::AutoConnection);
        }
    }
}

static void OnBtn_Lrf_Pressed()
{
    MainWindowHead* head = FindMainWindowHead();
    if(head!=NULL)
    {
        if(head->isVisible()==true)
        {
            QMetaObject::invokeMethod(head,&MainWindowHead::btnLrf_pressed,Qt::AutoConnection);
        }
    }
}

static void OnBtn_Lrf_Released()
{
    MainWindowHead* head = FindMainWindowHead();
    if(head!=NULL)
    {
        if(head->isVisible()==true)
        {
            QMetaObject::invokeMethod(head,&MainWindowHead::btnLrf_released,Qt::AutoConnection);
        }
    }
}

static void OnBtn_SwitchDown_Pressed()
{
    MainWindowHead* head = FindMainWindowHead();
    if(head!=NULL)
    {
        if(head->isVisible()==true)
        {
            QMetaObject::invokeMethod(head,&MainWindowHead::btnOnOff_pressed,Qt::AutoConnection);
        }
    }
}

static void OnBtn_Polarity_Pressed()
{
    MainWindowHead* head = FindMainWindowHead();
    if(head!=NULL)
    {
        if(head->isVisible()==true)
        {
            QMetaObject::invokeMethod(head,&MainWindowHead::btnPolarity_func,Qt::AutoConnection);
        }
    }
}

static void OnBtn_DayIr_Pressed()
{
    MainWindowHead* head = FindMainWindowHead();
    if(head!=NULL)
    {
        if(head->isVisible()==true)
        {
            QMetaObject::invokeMethod(head,&MainWindowHead::btnDayir_func,Qt::AutoConnection);
        }
    }
}

static void OnBtn_Zoom_Pressed()
{
    MainWindowHead* head = FindMainWindowHead();
    if(head!=NULL)
    {
        if(head->isVisible()==true)
        {
            QMetaObject::invokeMethod(head,&MainWindowHead::btnZoom_pressed,Qt::AutoConnection);
        }
    }
}

static void OnBtn_Zoom_Released()
{
    MainWindowHead* head = FindMainWindowHead();
    if(head!=NULL)
    {
        if(head->isVisible()==true)
        {
            QMetaObject::invokeMethod(head,&MainWindowHead::btnZoom_released,Qt::AutoConnection);
        }
    }
}


void InitBtnHeadEvents()
{
    AddButtonsHead_OnPressedEventCallback(BTN_HEAD_BRIGHTNESS,(void*)&OnBtn_Brightness_Pressed);
    AddButtonsHead_OnReleasedEventCallback(BTN_HEAD_BRIGHTNESS,(void*)&OnBtn_Brightness_Released);
    AddButtonsHead_OnReleaseAfterLongHoldEventCallback(BTN_HEAD_BRIGHTNESS,(void*)&OnBtn_Screenshot_Released);
    AddButtonsHead_OnPressedEventCallback(BTN_HEAD_LRF,(void*)&OnBtn_Lrf_Pressed);
    AddButtonsHead_OnReleasedEventCallback(BTN_HEAD_LRF,(void*)&OnBtn_Lrf_Released);
    AddButtonsHead_OnPressedEventCallback(BTN_HEAD_ON_OFF,(void*)&OnBtn_SwitchDown_Pressed);
    AddButtonsHead_OnPressedEventCallback(BTN_HEAD_DAY_IR,(void*)&OnBtn_DayIr_Pressed);
    AddButtonsHead_OnPressedEventCallback(BTN_HEAD_POLARITY,(void*)&OnBtn_Polarity_Pressed);
    AddButtonsHead_OnPressedEventCallback(BTN_HEAD_ZOOM,(void*)&OnBtn_Zoom_Pressed);
    AddButtonsHead_OnReleasedEventCallback(BTN_HEAD_ZOOM,(void*)&OnBtn_Zoom_Released);
}
