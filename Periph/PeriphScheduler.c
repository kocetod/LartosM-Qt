# include "PeriphScheduler.h"

#define COM_USERS_COUNT 10


Com_User comUsers[COM_USERS_COUNT];
float switchingTimeout = 0.05f;

bool PS_AddUser
(
        enum MUX_DEVICE_SELECT argInDevice,
        void* argInOnUpdate,
        void* argInReceive
)
{
    Com_User* selectedSlot = NULL;
    bool slotTaken = false;

    for(int i = 0; i<COM_USERS_COUNT; i++)
    {
        /*if(comUsers[i].isValid==false)
        {
            if(selectedSlot==NULL)
            {
                selectedSlot = &comUsers[i];
            }
        }
        else */
        if(comUsers[i].device==argInDevice)
        {
            if(comUsers[i].isValid==false)
            {
                selectedSlot = &comUsers[i];
            }
            else
            {
                slotTaken = true;
            }
            break;
        }
    }

    if((slotTaken==false)&&(selectedSlot!=NULL))
    {
        selectedSlot->isValid = true;
        selectedSlot->device = argInDevice;
        selectedSlot->OnUpdate = argInOnUpdate;
        selectedSlot->Receive = argInReceive;
    }
    return false;
}

bool PS_IsCurrent(enum MUX_DEVICE_SELECT argInDevice)
{
    for(int i =0; i<COM_USERS_COUNT; i++)
    {
        if((comUsers[i].device==argInDevice)&&(comUsers[i].isValid==true))
        {
            return comUsers[i].isCurrent;
        }
    }
    return false;
}

int GetCurrent()
{
    for(int i =0; i<COM_USERS_COUNT; i++)
    {
        if(PS_IsCurrent(comUsers[i].device)==true)
        {
            return comUsers[i].device;
        }
    }
    return -1;
}

bool PS_IsSwitchingTo(enum MUX_DEVICE_SELECT argInDevice)
{
    for(int i =0; i<COM_USERS_COUNT; i++)
    {
        if((comUsers[i].device==argInDevice)&&(comUsers[i].isValid==true))
        {
            return comUsers[i].isSwitchingTo;
        }
    }
    return false;
}

void PS_SetRequiredComSpeed(enum MUX_DEVICE_SELECT argInDevice, int argInReqSpeed)
{
    for(int i =0; i<COM_USERS_COUNT; i++)
    {
        if((comUsers[i].device==argInDevice)&&(comUsers[i].isValid==true))
        {
            if(comUsers[i].requiredComSpeed!=argInReqSpeed)
            {
                if((comUsers[i].isCurrent==false)&&(comUsers[i].isSwitchingTo==false))
                {
                    comUsers[i].requiredComSpeed = argInReqSpeed;
                }
                else if(comUsers[i].isSwitchingTo==true)
                {
                    comUsers[i].requiredComSpeed = argInReqSpeed;
                    switchingTimeout = 0.05f;
                    ComSetSpeed(argInReqSpeed);
                }
                else if(comUsers[i].isCurrent==true)
                {
                    comUsers[i].requiredComSpeed = argInReqSpeed;
                    comUsers[i].isCurrent = false;
                    comUsers[i].isSwitchingTo = true;
                    switchingTimeout = 0.05f;
                    ComSetSpeed(argInReqSpeed);
                }
            }
            break;
        }
    }
}

void PS_SetPriority(enum MUX_DEVICE_SELECT argInDevice, int argInPriority)
{
    for(int i =0; i<COM_USERS_COUNT; i++)
    {
        if((comUsers[i].device==argInDevice)&&(comUsers[i].isValid==true))
        {
            comUsers[i].currentPriority = argInPriority;
            break;
        }
    }
}

void PS_SetInterruptable(enum MUX_DEVICE_SELECT argInDevice, bool argInIsInterruptible)
{
    for(int i =0; i<COM_USERS_COUNT; i++)
    {
        if((comUsers[i].device==argInDevice)&&(comUsers[i].isValid==true))
        {
            comUsers[i].isInterruptible = argInIsInterruptible;
            break;
        }
    }
}

void ScheduleComUser()
{
    int currentHighestPriority = -1;
    int highestPriorityUser = 0;
    for(int i =0; i<COM_USERS_COUNT; i++)
    {
        if(comUsers[i].isValid==true)
        {
            if(comUsers[i].isCurrent==true)
            {
                highestPriorityUser = i;
                currentHighestPriority = i;
                if(comUsers[i].isInterruptible==false)
                {
                    return;
                }
            }
        }
    }

    for(int i =0; i<COM_USERS_COUNT; i++)
    {
        if(comUsers[i].isValid==true)
        {
            if(comUsers[i].currentPriority>comUsers[highestPriorityUser].currentPriority)
            {
               highestPriorityUser = i;
            }
        }
    }

    if(highestPriorityUser!=currentHighestPriority)
    {
        if(comUsers[highestPriorityUser].isValid==true)
        {
            if(currentHighestPriority>=0)
            {
                comUsers[currentHighestPriority].isCurrent = false;
                comUsers[currentHighestPriority].isSwitchingTo = false;
            }
            comUsers[highestPriorityUser].isCurrent = false;
            comUsers[highestPriorityUser].isSwitchingTo = true;
            SelectMuxDevice(comUsers[highestPriorityUser].device);
            ComSetSpeed(comUsers[highestPriorityUser].requiredComSpeed);
            switchingTimeout = 0.05f;
        }
    }
}

void PeriphSchedulerRoutine(float argInDeltaTime)
{

    float dT = argInDeltaTime;
    int switchingDevice = -1;
    for(int i = 0; i<COM_USERS_COUNT;i++)
    {
        if(comUsers[i].isValid==true)
        {
            if(PS_IsSwitchingTo(comUsers[i].device)==true)
            {
                switchingDevice = i;
            }
        }
    }

    //printf("%.4f \n",switchingTimeout);

    if(switchingDevice>=0)
    {
        if(switchingTimeout<=0)
        {
            comUsers[switchingDevice].isSwitchingTo = false;
            comUsers[switchingDevice].isCurrent = true;
        }
        else
        {
            switchingTimeout-=dT;
        }
    }
    else
    {
        ScheduleComUser();
    }

    for(int i = 0; i<COM_USERS_COUNT;i++)
    {
        if(comUsers[i].isValid==true)
        {
            if(comUsers[i].OnUpdate!=NULL)
            {
                (*(comUsers[i].OnUpdate))(dT);
            }
        }
    }
}

void PeriphSchedulerOnReceiveChar(char argInChar)
{
    for(int i = 0; i<COM_USERS_COUNT; i++)
    {
        if(comUsers[i].isValid==true)
        {
           (*(comUsers[i].Receive))(argInChar);
        }
    }
    //int dev = GetCurrent();
    //if(dev>=0)
    //{
        //(*(comUsers[dev].Receive))(argInChar);
    //}
}

void PS_Send(enum MUX_DEVICE_SELECT argInDevice,void* argInData, int argInSize)
{
    if(GetCurrent()==(int)argInDevice)
    {
        ComSend(argInData, argInSize);
    }
}

struct timeval tprevFrame, tThisFrame;
float deltatime;

void SWTimerHandler(size_t argInTimerId, void * arginData)
{
    gettimeofday(&tThisFrame, NULL);
    deltatime = (float)(tThisFrame.tv_sec - tprevFrame.tv_sec + (tThisFrame.tv_usec - tprevFrame.tv_usec) * 1e-6);
    tprevFrame = tThisFrame;
    PeriphSchedulerRoutine(deltatime);
    ComRoutine();
}

void InitScheduler()
{
    for(int i = 0; i<COM_USERS_COUNT; i++)
    {
        comUsers[i].isValid = false;
        comUsers[i].device = i;
        comUsers[i].currentPriority = 0;
        comUsers[i].isInterruptible = true;
        comUsers[i].requiredComSpeed = 9600;
        comUsers[i].isSwitchingTo = false;
        comUsers[i].isCurrent = false;
        comUsers[i].OnUpdate = NULL;
        comUsers[i].Receive = NULL;
    }
    ComAddOnReceive(PeriphSchedulerOnReceiveChar);
    gettimeofday(&tprevFrame, NULL);
    StartSoftwareTimer(5, &SWTimerHandler, TIMER_PERIODIC, NULL);
}

