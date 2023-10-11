# include "ButtonsController.h"



typedef struct
{
    bool isInitialised;
    int gpioNum;
    int notPressedValue;
    float timeToRegisterPressEvent;
    float timeToRegisterLongHoldEvent;
    bool isPressed;
    float timePressed;
    void (*OnPressedCallback[4])();
    void (*OnReleasedCallback[4])();
    void (*OnHoldPressCallback[4])();
    void (*OnReleaseAfterLongHoldCallback[4])();
} ButtonsController_EventData;

ButtonsController_EventData btnControllerEv[BTN_CONTROLLER_COUNT] =
{
    {
        true,
        0,
        0,
        0.1f,
        2.0f,
        false,
        0,
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL}
    },
    {
        true,
        1,
        0,
        0.1f,
        2.0f,
        false,
        0,
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL}
    },
    {
        true,
        2,
        0,
        0.1f,
        2.0f,
        false,
        0,
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL}
    },
    {
        true,
        3,
        0,
        0.1f,
        2.0f,
        false,
        0,
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL}
    },
    {
        true,
        4,
        0,
        0.1f,
        2.0f,
        false,
        0,
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL}
    },
    {
        true,
        22,
        0,
        0.1f,
        2.0f,
        false,
        0,
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL}
    },
    {
        true,
        23,
        0,
        0.1f,
        2.0f,
        false,
        0,
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL}
    },
    {
        true,
        24,
        0,
        0.1f,
        2.0f,
        false,
        0,
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL}
    },
    {
        true,
        27,
        0,
        0.1f,
        2.0f,
        false,
        0,
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL}
    },
    {
        true,
        21,
        0,
        0.1f,
        2.0f,
        false,
        0,
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL}
    },
    {
        true,
        5,
        1,
        0.1f,
        2.0f,
        false,
        0,
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL},
        {NULL,NULL,NULL,NULL}
    }

};

struct timeval btnTprevFrame, btnTthisFrame;
float btnDeltatime;

void BtnControllerSWTimerHandler(size_t argInTimerId, void * arginData)
{
    gettimeofday(&btnTthisFrame, NULL);
    btnDeltatime = (float)(btnTthisFrame.tv_sec - btnTprevFrame.tv_sec + (btnTthisFrame.tv_usec - btnTprevFrame.tv_usec) * 1e-6);
    btnTprevFrame = btnTthisFrame;

    for(int i=0; i<BTN_CONTROLLER_COUNT; i++)
    {
        if(btnControllerEv[i].isInitialised==true)
        {
            int result = (int)GpioWrapReadPinValue(btnControllerEv[i].gpioNum); //digitalRead(btnControllerEv[i].gpioNum);
            if(result==btnControllerEv[i].notPressedValue)
            {
                if(btnControllerEv[i].isPressed==true)
                {
                    if(btnControllerEv[i].timePressed>btnControllerEv[i].timeToRegisterLongHoldEvent)
                    {
                        for(int z=0; z<4; z++)
                        {
                            if(btnControllerEv[i].OnReleaseAfterLongHoldCallback[z]!=NULL)
                            {
                                btnControllerEv[i].OnReleaseAfterLongHoldCallback[z]();
                            }
                        }
                    }
                    if(btnControllerEv[i].timePressed>btnControllerEv[i].timeToRegisterPressEvent)
                    {
                        for(int z=0; z<4; z++)
                        {
                            if(btnControllerEv[i].OnReleasedCallback[z]!=NULL)
                            {
                                btnControllerEv[i].OnReleasedCallback[z]();
                            }
                        }
                    }
                }
                btnControllerEv[i].isPressed =false;
                btnControllerEv[i].timePressed = 0;
            }
            else
            {
                if(btnControllerEv[i].isPressed==false)
                {
                    for(int z=0; z<4; z++)
                    {
                        if(btnControllerEv[i].OnPressedCallback[z]!=NULL)
                        {
                            btnControllerEv[i].OnPressedCallback[z]();
                        }
                    }
                }
                if(btnControllerEv[i].timePressed>btnControllerEv[i].timeToRegisterPressEvent)
                {
                    for(int z=0; z<4; z++)
                    {
                        if(btnControllerEv[i].OnHoldPressCallback[z]!=NULL)
                        {
                            btnControllerEv[i].OnHoldPressCallback[z]();
                        }
                    }
                }
                btnControllerEv[i].isPressed =true;
                btnControllerEv[i].timePressed += btnDeltatime;
            }
        }
    }
}

bool AddButtonsController_OnPressedEventCallback(enum BTN_CONTROLLER_INDEX argInButtonName,void* argInCallback)
{
    if(btnControllerEv[argInButtonName].isInitialised==true)
    {
        for(int i =0; i <4;i++)
        {
            if(btnControllerEv[argInButtonName].OnPressedCallback[i] == NULL)
            {
               btnControllerEv[argInButtonName].OnPressedCallback[i] = argInCallback;
               return true;
            }
        }
    }
    return false;
}

bool AddButtonsController_OnReleasedEventCallback(enum BTN_CONTROLLER_INDEX argInButtonName,void* argInCallback)
{
    if(btnControllerEv[argInButtonName].isInitialised==true)
    {
        for(int i =0; i <4;i++)
        {
            if(btnControllerEv[argInButtonName].OnReleasedCallback[i] == NULL)
            {
               btnControllerEv[argInButtonName].OnReleasedCallback[i] = argInCallback;
               return true;
            }
        }
    }
    return false;
}

bool AddButtonsController_OnHoldPressEventCallback(enum BTN_CONTROLLER_INDEX argInButtonName,void* argInCallback)
{
    if(btnControllerEv[argInButtonName].isInitialised==true)
    {
        for(int i =0; i <4;i++)
        {
            if(btnControllerEv[argInButtonName].OnHoldPressCallback[i] == NULL)
            {
               btnControllerEv[argInButtonName].OnHoldPressCallback[i] = argInCallback;
               return true;
            }
        }
    }
    return false;
}

bool AddButtonsController_OnReleaseAfterLongHoldEventCallback(enum BTN_CONTROLLER_INDEX argInButtonName,void* argInCallback)
{
    if(btnControllerEv[argInButtonName].isInitialised==true)
    {
        for(int i =0; i <4;i++)
        {
            if(btnControllerEv[argInButtonName].OnReleaseAfterLongHoldCallback[i] == NULL)
            {
               btnControllerEv[argInButtonName].OnReleaseAfterLongHoldCallback[i] = argInCallback;
               return true;
            }
        }
    }
    return false;
}

void InitButtonsController()
{
    for(int i=0; i<BTN_CONTROLLER_COUNT; i++)
    {
        if(btnControllerEv[i].isInitialised==true)
        {
            GpioWrapSetPinMode(btnControllerEv[i].gpioNum, GPIO_MODE_IN);
        }
    }
    StartSoftwareTimer(40, &BtnControllerSWTimerHandler, TIMER_PERIODIC, NULL);
}
