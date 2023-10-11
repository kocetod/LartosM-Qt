# include "ButtonsHead.h" 

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
} ButtonsHead_EventData;

ButtonsHead_EventData btnHeadEv[BTN_HEAD_COUNT] =
{
    {
        true,
        1,
        1,
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
        1,
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
        1,
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
        1,
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
        1,
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
        1,
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
        14,
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

void BtnHeadSWTimerHandler(size_t argInTimerId, void * arginData)
{
    gettimeofday(&btnTthisFrame, NULL);
    btnDeltatime = (float)(btnTthisFrame.tv_sec - btnTprevFrame.tv_sec + (btnTthisFrame.tv_usec - btnTprevFrame.tv_usec) * 1e-6);
    btnTprevFrame = btnTthisFrame;

    for(int i=0; i<BTN_HEAD_COUNT; i++)
    {
        if(btnHeadEv[i].isInitialised==true)
        {
            int result = (int)GpioWrapReadPinValue(btnHeadEv[i].gpioNum);
            if(result==btnHeadEv[i].notPressedValue)
            {
                if(btnHeadEv[i].isPressed==true)
                {
                    if(btnHeadEv[i].timePressed>btnHeadEv[i].timeToRegisterLongHoldEvent)
                    {
                        for(int z=0; z<4; z++)
                        {
                            if(btnHeadEv[i].OnReleaseAfterLongHoldCallback[z]!=NULL)
                            {
                                btnHeadEv[i].OnReleaseAfterLongHoldCallback[z]();
                            }
                        }
                    }
                    if(btnHeadEv[i].timePressed>btnHeadEv[i].timeToRegisterPressEvent)
                    {
                        for(int z=0; z<4; z++)
                        {
                            if(btnHeadEv[i].OnReleasedCallback[z]!=NULL)
                            {
                                btnHeadEv[i].OnReleasedCallback[z]();
                            }
                        }
                    }
                }
                btnHeadEv[i].isPressed =false;
                btnHeadEv[i].timePressed = 0;
            }
            else
            {
                if(btnHeadEv[i].isPressed==false)
                {
                    for(int z=0; z<4; z++)
                    {
                        if(btnHeadEv[i].OnPressedCallback[z]!=NULL)
                        {
                            btnHeadEv[i].OnPressedCallback[z]();
                        }
                    }
                }
                if(btnHeadEv[i].timePressed>btnHeadEv[i].timeToRegisterPressEvent)
                {
                    for(int z=0; z<4; z++)
                    {
                        if(btnHeadEv[i].OnHoldPressCallback[z]!=NULL)
                        {
                            btnHeadEv[i].OnHoldPressCallback[z]();
                        }
                    }
                }
                btnHeadEv[i].isPressed =true;
                btnHeadEv[i].timePressed += btnDeltatime;
            }
        }
    }
}

bool AddButtonsHead_OnPressedEventCallback(enum BTN_HEAD_INDEX argInButtonName,void* argInCallback)
{
    if(btnHeadEv[argInButtonName].isInitialised==true)
    {
        for(int i =0; i <4;i++)
        {
            if(btnHeadEv[argInButtonName].OnPressedCallback[i] == NULL)
            {
               btnHeadEv[argInButtonName].OnPressedCallback[i] = argInCallback;
               return true;
            }
        }
    }
    return false;
}


bool AddButtonsHead_OnReleasedEventCallback(enum BTN_HEAD_INDEX argInButtonName,void* argInCallback)
{
    if(btnHeadEv[argInButtonName].isInitialised==true)
    {
        for(int i =0; i <4;i++)
        {
            if(btnHeadEv[argInButtonName].OnReleasedCallback[i] == NULL)
            {
               btnHeadEv[argInButtonName].OnReleasedCallback[i] = argInCallback;
               return true;
            }
        }
    }
    return false;
}

bool AddButtonsHead_OnHoldPressEventCallback(enum BTN_HEAD_INDEX argInButtonName,void* argInCallback)
{
    if(btnHeadEv[argInButtonName].isInitialised==true)
    {
        for(int i =0; i <4;i++)
        {
            if(btnHeadEv[argInButtonName].OnHoldPressCallback[i] == NULL)
            {
               btnHeadEv[argInButtonName].OnHoldPressCallback[i] = argInCallback;
               return true;
            }
        }
    }
    return false;
}

bool AddButtonsHead_OnReleaseAfterLongHoldEventCallback(enum BTN_HEAD_INDEX argInButtonName,void* argInCallback)
{
    if(btnHeadEv[argInButtonName].isInitialised==true)
    {
        for(int i =0; i <4;i++)
        {
            if(btnHeadEv[argInButtonName].OnReleaseAfterLongHoldCallback[i] == NULL)
            {
               btnHeadEv[argInButtonName].OnReleaseAfterLongHoldCallback[i] = argInCallback;
               return true;
            }
        }
    }
    return false;
}

void InitButtonsHead()
{
    for(int i=0; i<BTN_HEAD_COUNT; i++)
    {
        if(btnHeadEv[i].isInitialised==true)
        {
            GpioWrapSetPinMode(btnHeadEv[i].gpioNum, GPIO_MODE_IN);
        }
    } 

    StartSoftwareTimer(40, &BtnHeadSWTimerHandler, TIMER_PERIODIC, NULL);
}
