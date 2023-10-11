#include "PIC.h"

#define PIC_MUX_DEVICE_ID MUX_DEVICE_3
#define PIC_SPEED 115200
#define PIC_MAX_SUBSCRIBERS 5


static char currentMessage[256];
static int currentSymbol=0;

bool shutdownRequested = false;
bool shutdownAcknowledged = false;

int lastMeasureResult = 0;

void (*OnPicMeasureCallback[PIC_MAX_SUBSCRIBERS])(int)=
{
   NULL,
   NULL,
   NULL,
   NULL,
   NULL
};

enum PIC_MSG_INDEX
{
    PIC_MSG_PrepareTurnOff,
    PIC_MSG_ReadAdc,
    PIC_MSG_COUNT
};

int GetLastBatteryMeasurement()
{
    return lastMeasureResult;
}

void ShutdownAcknowledged()
{
    shutdownAcknowledged = true;
    GpioWrapRequestShutDown();
}

static Pic_MsgData msgDataIn[PIC_MSG_COUNT]=
{
    {0x11,{0,0},{""},&ShutdownAcknowledged},
    {0x21,{0,0},{""},NULL}
};


void RequestShutdown()
{
    shutdownRequested = true;
}

bool ShutdownStarted()
{
    return shutdownAcknowledged;
}

static bool PicMessageChecksumIsValid()
{
    int msgIndex = -1;
    for(int i = 0; i < PIC_MSG_COUNT; i++)
    {
        if(currentMessage[2]==msgDataIn[i].msgID)
        {
            msgIndex = i;
            break;
        }
    }

    if(msgIndex>=0)
    {
        char calculatedChecksum = 0;
        int msgDataLengthWithoutChecksum = 3+currentMessage[1];

        for(int i=1;i<msgDataLengthWithoutChecksum;i++)
        {
            calculatedChecksum+=currentMessage[i];
        }

        if(calculatedChecksum==currentMessage[msgDataLengthWithoutChecksum])
        {
            return true;
        }
    }
    return false;
}

static bool PicMessageHasFullDataLength()
{
    int dl = (int)currentMessage[1];
    if(dl>0)
    {
        if(currentSymbol> (3+dl))
        {
            return true;
        }
    }
    return false;
}

static bool PicMessageHasValidStart()
{
    if(currentMessage[0]==0x7e)
    {
        return true;
    }
    return false;
}

static bool PicMessageIsValid()
{
    if(PicMessageHasValidStart()==true)
    {
        if(PicMessageHasFullDataLength()==true)
        {
            if(PicMessageChecksumIsValid()==true)
            {
                return true;
            }
            else
            {
                currentSymbol = 0;
                memset(&currentMessage, 0, 256*sizeof(unsigned char));
            }
        }
    }
    else
    {
        currentSymbol = 0;
        memset(&currentMessage, 0, 256*sizeof(unsigned char));
    }
    return false;
}

static char PicGetMessageID()
{
    return currentMessage[2];
}

static void PicStoreMessage()
{
    char msgId = PicGetMessageID();
    for(int i = 0; i<PIC_MSG_COUNT;i++)
    {
        if(msgDataIn[i].msgID==msgId)
        {
            gettimeofday(&msgDataIn[i].msgTimeUsec,NULL);
            for(int z=0;z<256;z++)
            {
                msgDataIn[i].msg[z]=currentMessage[z];
            }
            if(msgDataIn[i].OnMsgReceive!=NULL)
            {
                (*(msgDataIn[i].OnMsgReceive))();
            }
            break;
        }
    }
}

static void PicProcessMessage()
{
    if(PicMessageIsValid()==true)
    {
        PicStoreMessage();
        currentSymbol = 0;
        memset(&currentMessage, 0, 256*sizeof(unsigned char));
    }
}

static void PicProcessChar(char argInChar)
{
    currentMessage[currentSymbol] = argInChar;
    if(currentSymbol<(256-1))
    {
        currentSymbol++;
    }
    PicProcessMessage();
}

static void PicRequestADCData()
{
    if(PS_IsCurrent(PIC_MUX_DEVICE_ID))
    {
        char message[4];

        message[0] = 0x7e;
        message[1] = 0x00;
        message[2] = 0x20;
        message[3] = 0x20;

        PS_Send(PIC_MUX_DEVICE_ID,&message,4);
    }
}

static void PicRequestTurnOff()
{
    if(PS_IsCurrent(PIC_MUX_DEVICE_ID))
    {
        char message[4];

        message[0] = 0x7e;
        message[1] = 0x00;
        message[2] = 0x10;
        message[3] = 0x10;

        PS_Send(PIC_MUX_DEVICE_ID,&message,4);
    }
}

static time_t GetMsgTimeSec(enum PIC_MSG_INDEX argInMsg)
{
    return msgDataIn[argInMsg].msgTimeUsec.tv_sec;
}

static __suseconds_t GetMsgTimeUsec(enum PIC_MSG_INDEX argInMsg)
{
    return msgDataIn[argInMsg].msgTimeUsec.tv_usec;
}


static long PicGetMsgTimeDifferenceToCurrentTimeUs(enum PIC_MSG_INDEX argInMsg)
{
    struct timeval currentTime;
    gettimeofday(&currentTime,NULL);

    time_t msgTimeSec = GetMsgTimeSec(argInMsg);
    __suseconds_t msgTimeUsec = GetMsgTimeUsec(argInMsg);

    long diff = (long)(currentTime.tv_sec-msgTimeSec);
    long diffU = diff*1000000.0f + (long)(currentTime.tv_usec-msgTimeUsec);

    return diffU;
}

int GetADCValue()
{
    int result =0;
    long timeToMsg = PicGetMsgTimeDifferenceToCurrentTimeUs(PIC_MSG_ReadAdc);

    if(timeToMsg<2000000)
    {
        result = msgDataIn[PIC_MSG_ReadAdc].msg[3]*256+msgDataIn[PIC_MSG_ReadAdc].msg[4];
    }
    return result;
}

enum PIC_DEVICE_STATES
{
    PIC_NOT_CONNECTED,
    PIC_REQUEST_ADC_DATA,
    PIC_WAIT_ADC_DATA,
    PIC_IDLE,
    PIC_REQUEST_SHUTDOWN,
    PIC_WAIT_SHUTDOWN_ACK,
    PIC_WAIT_SHUTDOWN,
    PIC_DEVICE_STATES_COUNT
};

void (*PicStates[PIC_DEVICE_STATES_COUNT])(float);

static enum PIC_DEVICE_STATES currentState;

static void PicOnMsgReceive_PrepareTurnOfAcknowledge()
{
    shutdownAcknowledged = true;
    currentState=PIC_WAIT_SHUTDOWN;
}

static void PicOnMsgReceive_ReadAdcData()
{
    if((currentState==PIC_WAIT_ADC_DATA)||(currentState==PIC_REQUEST_ADC_DATA))
    {
        lastMeasureResult = GetADCValue();
        for(int i =0;i<PIC_MAX_SUBSCRIBERS;i++)
        {
            if(OnPicMeasureCallback[i]!=NULL)
            {
                OnPicMeasureCallback[i](lastMeasureResult);
            }
        }
        currentState=PIC_IDLE;
    }
}

float picPingReplyTimeout = 0.15f;
float picShutdownReplyTimeout = 0.15f;
float picConnectAttemptTimeout = 0.3f;
float picIdleTimeout = 3.77f;

void PicStateNotConnected(float argInDeltaTime)
{
    PS_SetPriority(PIC_MUX_DEVICE_ID,21);
    PS_SetInterruptable(PIC_MUX_DEVICE_ID,true);
    picConnectAttemptTimeout-=argInDeltaTime;

    if(picConnectAttemptTimeout<=0)
    {
        currentState = PIC_REQUEST_ADC_DATA;
        picConnectAttemptTimeout = 3.3f;
    }
}

void PicStateRequestADCData(float arginDeltaTime)
{
    PS_SetPriority(PIC_MUX_DEVICE_ID,47);
    PS_SetInterruptable(PIC_MUX_DEVICE_ID,false);
    if(PS_IsCurrent(PIC_MUX_DEVICE_ID)==true)
    {
        PicRequestADCData();
        PS_SetPriority(PIC_MUX_DEVICE_ID,90);
        PS_SetInterruptable(PIC_MUX_DEVICE_ID,false);
        currentState = PIC_WAIT_ADC_DATA;
        picPingReplyTimeout = 0.15f;
    }
}


static void PicStateWaitADCData(float argInDeltaTime)
{
    PS_SetPriority(PIC_MUX_DEVICE_ID,90);
    PS_SetInterruptable(PIC_MUX_DEVICE_ID,false);
    picPingReplyTimeout-=argInDeltaTime;
    if(picPingReplyTimeout<=0)
    {
        PS_SetPriority(PIC_MUX_DEVICE_ID,21);
        PS_SetInterruptable(PIC_MUX_DEVICE_ID,true);
        currentState = PIC_NOT_CONNECTED;
        picPingReplyTimeout = 0.15f;
    }
}

static void PicStateIdle(float argInDeltaTime)
{
    picIdleTimeout-=argInDeltaTime;
    if(shutdownRequested==false)
    {
        if(picIdleTimeout<=0)
        {
            PS_SetPriority(PIC_MUX_DEVICE_ID,47);
            PS_SetInterruptable(PIC_MUX_DEVICE_ID,false);
            if(PS_IsCurrent(PIC_MUX_DEVICE_ID)==true)
            {
                currentState = PIC_REQUEST_ADC_DATA;
                picIdleTimeout = 3.77f;
            }
        }
        else
        {
            PS_SetPriority(PIC_MUX_DEVICE_ID,21);
            PS_SetInterruptable(PIC_MUX_DEVICE_ID,true);
        }
    }
    else
    {
        PS_SetPriority(PIC_MUX_DEVICE_ID,47);
        PS_SetInterruptable(PIC_MUX_DEVICE_ID,false);
        if(PS_IsCurrent(PIC_MUX_DEVICE_ID)==true)
        {
            currentState = PIC_REQUEST_SHUTDOWN;
            picIdleTimeout = 3.77f;
        }
    }
}



static void PicStateRequestShutdown(float argInDeltaTime)
{
    PS_SetPriority(PIC_MUX_DEVICE_ID,98);
    PS_SetInterruptable(PIC_MUX_DEVICE_ID,false);
    if(PS_IsCurrent(PIC_MUX_DEVICE_ID)==true)
    {
        PicRequestTurnOff();
        PS_SetPriority(PIC_MUX_DEVICE_ID,98);
        PS_SetInterruptable(PIC_MUX_DEVICE_ID,false);
        currentState = PIC_WAIT_SHUTDOWN_ACK;
        picShutdownReplyTimeout = 0.15f;
    }
}


static void PicStateWaitShutdownAcknowledge(float argInDeltaTime)
{
    PS_SetPriority(PIC_MUX_DEVICE_ID,98);
    PS_SetInterruptable(PIC_MUX_DEVICE_ID,false);
    picShutdownReplyTimeout-=argInDeltaTime;
    if(picShutdownReplyTimeout<=0)
    {
        PS_SetPriority(PIC_MUX_DEVICE_ID,21);
        PS_SetInterruptable(PIC_MUX_DEVICE_ID,true);
        currentState = PIC_IDLE;
        picShutdownReplyTimeout = 0.15f;
    }
}

static void PicStateWaitShutdown(float argInDeltaTime)
{
    PS_SetPriority(PIC_MUX_DEVICE_ID,21);
    PS_SetInterruptable(PIC_MUX_DEVICE_ID,true);
}

void PicStatemachine(float argInDeltaTime)
{
    (*(PicStates[currentState]))(argInDeltaTime);
}

static void PicOnUpdate(float argInDeltaTime)
{
    PicStatemachine(argInDeltaTime);
}

bool AddPicMeasureCallback(void* argInCallback)
{
    for(int i =0; i <PIC_MAX_SUBSCRIBERS;i++)
    {
        if(OnPicMeasureCallback[i] == NULL)
        {
           OnPicMeasureCallback[i] = argInCallback;
           return true;
        }
    }
    return false;
}

static void InitPicStatemachine()
{
    PicStates[PIC_NOT_CONNECTED] = &PicStateNotConnected;
    PicStates[PIC_REQUEST_ADC_DATA] = &PicStateRequestADCData;
    PicStates[PIC_WAIT_ADC_DATA] = &PicStateWaitADCData;
    PicStates[PIC_IDLE] = &PicStateIdle;
    PicStates[PIC_REQUEST_SHUTDOWN] = &PicStateRequestShutdown;
    PicStates[PIC_WAIT_SHUTDOWN_ACK] = &PicStateWaitShutdownAcknowledge;
    PicStates[PIC_WAIT_SHUTDOWN] = &PicStateWaitShutdown;
}


void InitPicMcu()
{
    InitPicStatemachine();
    PS_AddUser(PIC_MUX_DEVICE_ID,&PicOnUpdate,&PicProcessChar);
    PS_SetPriority(PIC_MUX_DEVICE_ID,50);
    PS_SetRequiredComSpeed(PIC_MUX_DEVICE_ID,PIC_SPEED);
    msgDataIn[PIC_MSG_PrepareTurnOff].OnMsgReceive = &PicOnMsgReceive_PrepareTurnOfAcknowledge;
    msgDataIn[PIC_MSG_ReadAdc].OnMsgReceive = &PicOnMsgReceive_ReadAdcData;

    AddButtonsHead_OnReleaseAfterLongHoldEventCallback(BTN_HEAD_ON_OFF,&RequestShutdown);
    AddButtonsController_OnReleaseAfterLongHoldEventCallback(BTN_CONTROLLER_SHUTDOWN,&RequestShutdown);

}
