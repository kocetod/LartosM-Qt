#include "Compass.h"

static char currentMessage[256];
static int currentSymbol=0;

#define MSG_COUNT 15
#define CMP_SPEED_LOW 9600
#define CMP_SPEED_HIGH 115200
#define CMP_MUX_DEVICE_ID MUX_DEVICE_1

#define CMP_MAX_SUBSCRIBERS 5


enum CMP_CUSTOM_MSG_INDEX  currentCustomMessage = CMP_CUS_MSG_NONE;
bool isInCustomMessageMode = false;

enum CMP_MSG_INDEX
{
    CMP_MSG_ReadPitchAngle,
    CMP_MSG_ReadRollAngle,
    CMP_MSG_ReadAzimuthAngle,
    CMP_MSG_ReadPitchRollHeading,
    CMP_MSG_SetCommunicationRate,
    CMP_MSG_SetMagneticDeclination,
    CMP_MSG_ReadMagneticDeclination,
    CMP_MSG_SetModuleAddress,
    CMP_MSG_QueryCurrentAddress,
    CMP_MSG_SetDataRate,
    CMP_MSG_SaveSettings,
    CMP_MSG_CalibrationStarted,
    CMP_MSG_CalibrationPointInPlace,
    CMP_MSG_CalibrationAborted,
    CMP_MSG_CalibrationResult,
    CMP_MSG_CalibrationCleared
};

void (*CmpCustomMessagesCallbacks[CMP_CUS_MSG_COUNT])(char*) =
{
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

static Cmp_MsgData msgData[MSG_COUNT]=
{
    {0x81,{0,0},{""},NULL},
    {0x82,{0,0},{""},NULL},
    {0x83,{0,0},{""},NULL},
    {0x84,{0,0},{""},NULL},
    {0x8B,{0,0},{""},NULL},
    {0x86,{0,0},{""},NULL},
    {0x87,{0,0},{""},NULL},
    {0x8F,{0,0},{""},NULL},
    {0x1F,{0,0},{""},NULL},
    {0x8C,{0,0},{""},NULL},
    {0x8A,{0,0},{""},NULL},
    {0x3C,{0,0},{""},NULL},
    {0x3E,{0,0},{""},NULL},
    {0x3D,{0,0},{""},NULL},
    {0x3F,{0,0},{""},NULL},
    {0x90,{0,0},{""},NULL}
};

static bool MessageChecksumIsValid()
{
    int dl = (int)currentMessage[1];
    int checksumIndex = 1+dl-1;
    if(checksumIndex<256)
    {
        int checksum = currentMessage[checksumIndex];
        int msgChecksum = 0;
        for(int i=1;i<checksumIndex;i++)
        {
            msgChecksum+=currentMessage[i];
        }
        int trimmedChecksum = msgChecksum%256;
        if(checksum==trimmedChecksum)
        {
            return true;
        }
    }
    return false;
}

static bool MessageHasFullDataLength()
{
    int dl = (int)currentMessage[1];
    if(dl>0)
    {
        if(currentSymbol>= (1+dl))
        {
            return true;
        }
    }
    return false;
}

static bool MessageHasValidStart()
{
    if(currentMessage[0]==0x77)
    {
        return true;
    }
    return false;
}

static bool MessageIsValid()
{
    if(MessageHasValidStart()==true)
    {
        if(MessageHasFullDataLength()==true)
        {
            if(MessageChecksumIsValid()==true)
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

static char GetMessageID()
{
    return currentMessage[3];
}

static void StoreMessage()
{
    char msgId = GetMessageID();
    for(int i = 0; i<MSG_COUNT;i++)
    {
        if(msgData[i].msgID==msgId)
        {
            gettimeofday(&msgData[i].msgTimeUsec,NULL);
            for(int z=0;z<256;z++)
            {
                msgData[i].msg[z]=currentMessage[z];
            }
            if(msgData[i].OnMsgReceive!=NULL)
            {
                (*(msgData[i].OnMsgReceive))();
            }
            break;
        }
    }
}

static void ProcessMessage()
{
    if(MessageIsValid()==true)
    {
        StoreMessage();
        currentSymbol = 0;
        memset(&currentMessage, 0, 256*sizeof(unsigned char));
    }
}

static void ProcessChar(char argInChar)
{
    currentMessage[currentSymbol] = argInChar;
    if(currentSymbol<(256-1))
    {
        currentSymbol++;
    }
    ProcessMessage();
}


/////////////////////////////////////////////////
/// \brief The COMPASS_DEVICE_STATES enum
///
///
///
///
///

void (*OnReadResultCallback[CMP_MAX_SUBSCRIBERS])(int,int,int);

static time_t GetMsgTimeSec(enum CMP_MSG_INDEX argInMsg)
{
    return msgData[argInMsg].msgTimeUsec.tv_sec;
}

static __suseconds_t GetMsgTimeUsec(enum CMP_MSG_INDEX argInMsg)
{
    return msgData[argInMsg].msgTimeUsec.tv_usec;
}

static long GetMsgTimeDifferenceToCurrentTimeUs(enum CMP_MSG_INDEX argInMsg)
{
    struct timeval currentTime;
    gettimeofday(&currentTime,NULL);

    time_t msgTimeSec = GetMsgTimeSec(argInMsg);
    __suseconds_t msgTimeUsec = GetMsgTimeUsec(argInMsg);

    long diff = (long)(currentTime.tv_sec-msgTimeSec);
    long diffU = diff*1000000.0f + (long)(currentTime.tv_usec-msgTimeUsec);

    return diffU;
}

int BCDByteToInt(char argInBCD)
{
    int result = 0;
    char buffLSB = argInBCD;
    char buffMSB = argInBCD;

    buffLSB&=0b00001111;
    buffMSB&=0b11110000;
    buffMSB>>=4;

    result = buffLSB+(buffMSB*10);
    return result;
}

int ConstructValueFromBytes(int argInMSB, int argInB, int argInLSB)
{
    int result = (argInLSB*10)+(argInB*1000)+(argInMSB*100000);
    int sign = result/1000000;
    if(sign==1)
    {   result-=1000000;
        result=-result;
    }
    return result;
}


void GetPitchRollHeadingValues()
{
    long timeToMsg = GetMsgTimeDifferenceToCurrentTimeUs(CMP_MSG_ReadPitchRollHeading);

    if(timeToMsg<2000000)
    {
        int head = ConstructValueFromBytes(BCDByteToInt(msgData[CMP_MSG_ReadPitchRollHeading].msg[10]), BCDByteToInt(msgData[CMP_MSG_ReadPitchRollHeading].msg[11]), BCDByteToInt(msgData[CMP_MSG_ReadPitchRollHeading].msg[12]));
        int roll = ConstructValueFromBytes(BCDByteToInt(msgData[CMP_MSG_ReadPitchRollHeading].msg[7]), BCDByteToInt(msgData[CMP_MSG_ReadPitchRollHeading].msg[8]), BCDByteToInt(msgData[CMP_MSG_ReadPitchRollHeading].msg[9]));
        int pitch = ConstructValueFromBytes(BCDByteToInt(msgData[CMP_MSG_ReadPitchRollHeading].msg[4]), BCDByteToInt(msgData[CMP_MSG_ReadPitchRollHeading].msg[5]), BCDByteToInt(msgData[CMP_MSG_ReadPitchRollHeading].msg[6]));
        //printf("%d  %d  %d \n",  pitch, roll, head);
        for(int i =0; i <CMP_MAX_SUBSCRIBERS;i++)
        {
            if(OnReadResultCallback[i] != NULL)
            {
               (*(OnReadResultCallback[i]))(pitch,roll,head);
            }
        }
    }
}


enum COMPASS_DEVICE_STATES
{
    CMP_TIMEOUT,
    CMP_SET_COMPASS_HS,
    CMP_SET_COMPASS_HS_WAIT_RESPONSE,
    CMP_REQUEST_ANGLES_HS,
    CMP_WAIT_ANGLES_HS,
    CMP_REQUEST_ANGLES_LS,
    CMP_WAIT_ANGLES_LS,
    CMP_CUSTOM_COMMAND_REQUEST_HS,
    CMP_CUSTOM_COMMAND_WAIT_HS,
    CMP_IDLE,
    CMP_DEVICE_STATES_COUNT
};

void (*CmpStates[CMP_DEVICE_STATES_COUNT])(float);

static enum COMPASS_DEVICE_STATES currentState;


static void OnMsgReceive_SetCommunicationRate()
{
    if((currentState==CMP_SET_COMPASS_HS_WAIT_RESPONSE)||(currentState==CMP_SET_COMPASS_HS))
    {
        if(msgData[CMP_MSG_SetCommunicationRate].msg[4]==0x00)
        {
            currentState = CMP_IDLE;
        }
    }
}

static void OnMsgReceive_ReadPitchRollHeading()
{
    GetPitchRollHeadingValues();
    if((currentState==CMP_WAIT_ANGLES_LS)||(currentState==CMP_REQUEST_ANGLES_LS))
    {
        currentState = CMP_SET_COMPASS_HS;
    }
    else if((currentState==CMP_WAIT_ANGLES_HS)||(currentState==CMP_REQUEST_ANGLES_HS))
    {
        currentState = CMP_IDLE;
    }
    else if(currentState==CMP_CUSTOM_COMMAND_WAIT_HS)
    {
        currentState = CMP_CUSTOM_COMMAND_REQUEST_HS;
        if(CmpCustomMessagesCallbacks[CMP_CUS_MSG_RequestPitchRollHeading]!=NULL)
        {
            CmpCustomMessagesCallbacks[CMP_CUS_MSG_RequestPitchRollHeading](msgData[CMP_MSG_ReadPitchRollHeading].msg);
        }
    }
}

static void OnMsgReceive_CalibrationStarted()
{
    if(currentState==CMP_CUSTOM_COMMAND_WAIT_HS)
    {
        currentState = CMP_CUSTOM_COMMAND_REQUEST_HS;
        if(CmpCustomMessagesCallbacks[CMP_CUS_MSG_CalibrationStart]!=NULL)
        {
            CmpCustomMessagesCallbacks[CMP_CUS_MSG_CalibrationStart](msgData[CMP_MSG_CalibrationStarted].msg);
        }
    }
}

static void OnMsgReceive_CalibrationPointInPlace()
{
    if(currentState==CMP_CUSTOM_COMMAND_WAIT_HS)
    {
        currentState = CMP_CUSTOM_COMMAND_REQUEST_HS;
        if(CmpCustomMessagesCallbacks[CMP_CUS_MSG_CalibrationPointInPlace]!=NULL)
        {
            CmpCustomMessagesCallbacks[CMP_CUS_MSG_CalibrationPointInPlace](msgData[CMP_MSG_CalibrationPointInPlace].msg);
        }
    }
}

static void OnMsgReceive_CalibrationResult()
{
    if(CmpCustomMessagesCallbacks[CMP_CUS_MSG_CalibrationResult]!=NULL)
    {
        CmpCustomMessagesCallbacks[CMP_CUS_MSG_CalibrationResult](msgData[CMP_MSG_CalibrationResult].msg);
    }
}

float cmpConnectAttemptTimeout = 0.1f;
static void CmpStateNotConnected(float argInDeltaTime)
{
    PS_SetPriority(CMP_MUX_DEVICE_ID,25);
    PS_SetInterruptable(CMP_MUX_DEVICE_ID,true);
    cmpConnectAttemptTimeout-=argInDeltaTime;

    if(cmpConnectAttemptTimeout<=0)
    {
        currentState = CMP_REQUEST_ANGLES_HS;
        cmpConnectAttemptTimeout = 1.0f;
    }
}
bool setComspeedFrameout = false;
float cmpSetMySpeedTimeout = 0.1f;

static void CmpStateSettingComSpeed(float argInDeltaTime)
{
    if(setComspeedFrameout==false)
    {
        PS_SetRequiredComSpeed(CMP_MUX_DEVICE_ID,CMP_SPEED_LOW);
        setComspeedFrameout = true;
    }
    else
    {
        if(PS_IsCurrent(CMP_MUX_DEVICE_ID))
        {
            PS_SetPriority(CMP_MUX_DEVICE_ID,100);
            PS_SetInterruptable(CMP_MUX_DEVICE_ID,false);

            char message[6];

            message[0] = 0x77;
            message[1] = 0x05;
            message[2] = 0x00;
            message[3] = 0x0B;
            message[4] = 0x04;
            message[5] = 0x14;

            PS_Send(CMP_MUX_DEVICE_ID,&message,6);
            currentState = CMP_SET_COMPASS_HS_WAIT_RESPONSE;
            cmpSetMySpeedTimeout = 0.1f;
            setComspeedFrameout = false;
        }
    }
}


static void CmpRequestPitchRollHeading()
{
    if(PS_IsCurrent(CMP_MUX_DEVICE_ID))
    {
        char message[5];

        message[0] = 0x77;
        message[1] = 0x04;
        message[2] = 0x00;
        message[3] = 0x04;
        message[4] = 0x08;

        PS_Send(CMP_MUX_DEVICE_ID,&message,5);
    }
}

static void CmpRequestCalibrationStart()
{
    if(PS_IsCurrent(CMP_MUX_DEVICE_ID))
    {
        char message[5];

        message[0] = 0x77;
        message[1] = 0x04;
        message[2] = 0x00;
        message[3] = 0x3C;
        message[4] = 0x40;

        PS_Send(CMP_MUX_DEVICE_ID,&message,5);
    }
}

static void CmpSendPointInPlace()
{
    if(PS_IsCurrent(CMP_MUX_DEVICE_ID))
    {
        char message[5];

        message[0] = 0x77;
        message[1] = 0x04;
        message[2] = 0x00;
        message[3] = 0x3E;
        message[4] = 0x42;

        PS_Send(CMP_MUX_DEVICE_ID,&message,5);
    }
}

static void CmpSendTerminateCalibration()
{
    if(PS_IsCurrent(CMP_MUX_DEVICE_ID))
    {
        char message[5];

        message[0] = 0x77;
        message[1] = 0x04;
        message[2] = 0x00;
        message[3] = 0x3D;
        message[4] = 0x41;

        PS_Send(CMP_MUX_DEVICE_ID,&message,5);
    }
}

static void CmpSendClearCalibrationData()
{
    if(PS_IsCurrent(CMP_MUX_DEVICE_ID))
    {
        char message[5];

        message[0] = 0x77;
        message[1] = 0x04;
        message[2] = 0x00;
        message[3] = 0x10;
        message[4] = 0x14;

        PS_Send(CMP_MUX_DEVICE_ID,&message,5);
    }
}



void (*CmpCustomMessages[CMP_CUS_MSG_COUNT])() =
{
    NULL,
    &CmpRequestPitchRollHeading,
    &CmpRequestCalibrationStart,
    &CmpSendPointInPlace,
    &CmpSendTerminateCalibration,
    NULL,
    &CmpSendClearCalibrationData
};



float comSpeedSetupTimeout = 0.35f;
static void CmpStateWaitComspeedSetup(float argInDeltaTime)
{
    comSpeedSetupTimeout-=argInDeltaTime;
    if(comSpeedSetupTimeout<=0)
    {
        PS_SetPriority(CMP_MUX_DEVICE_ID,45);
        PS_SetInterruptable(CMP_MUX_DEVICE_ID,true);
        currentState = CMP_TIMEOUT;
        comSpeedSetupTimeout = 0.35f;
    }
}

float requestAngleDataTimeout = 0.10f;


static void CmpStateConnectedRequestAngles_HS(float argInDeltaTime)
{
    PS_SetPriority(CMP_MUX_DEVICE_ID,55);
    PS_SetInterruptable(CMP_MUX_DEVICE_ID,true);
    if(setComspeedFrameout==false)
    {
        setComspeedFrameout = true;
        PS_SetRequiredComSpeed(CMP_MUX_DEVICE_ID,CMP_SPEED_HIGH);
    }
    else
    {
        if(isInCustomMessageMode==true)
        {
            currentState = CMP_CUSTOM_COMMAND_REQUEST_HS;
            setComspeedFrameout = false;
        }
        else
        {
            if(PS_IsCurrent(CMP_MUX_DEVICE_ID)==true)
            {
                CmpRequestPitchRollHeading();
                PS_SetPriority(CMP_MUX_DEVICE_ID,90);
                PS_SetInterruptable(CMP_MUX_DEVICE_ID,false);
                currentState = CMP_WAIT_ANGLES_HS;
                setComspeedFrameout = false;
            }
        }
    }
}

static void CmpStateConnectedWaitAngles_HS(float argInDeltaTime)
{

    PS_SetPriority(CMP_MUX_DEVICE_ID,90);
    PS_SetInterruptable(CMP_MUX_DEVICE_ID,false);
    if(requestAngleDataTimeout>=0)
    {
        requestAngleDataTimeout-=argInDeltaTime;
    }
    else
    {
        requestAngleDataTimeout = 0.15f;
        currentState = CMP_REQUEST_ANGLES_LS;
    }
}

static void CmpStateConnectedRequestAngles_LS(float argInDeltaTime)
{
    PS_SetPriority(CMP_MUX_DEVICE_ID,45);
    PS_SetInterruptable(CMP_MUX_DEVICE_ID,true);

    if(setComspeedFrameout==false)
    {
        setComspeedFrameout = true;
        PS_SetRequiredComSpeed(CMP_MUX_DEVICE_ID,CMP_SPEED_LOW);
    }
    else
    {
        if(PS_IsCurrent(CMP_MUX_DEVICE_ID)==true)
        {
            CmpRequestPitchRollHeading();
            PS_SetPriority(CMP_MUX_DEVICE_ID,90);
            PS_SetInterruptable(CMP_MUX_DEVICE_ID,false);
            currentState = CMP_WAIT_ANGLES_LS;
            requestAngleDataTimeout = 0.35f;
            setComspeedFrameout = false;
        }
    }
}

static void CmpStateConnectedWaitAngles_LS(float argInDeltaTime)
{
    PS_SetPriority(CMP_MUX_DEVICE_ID,90);
    PS_SetInterruptable(CMP_MUX_DEVICE_ID,false);
    if(requestAngleDataTimeout>=0)
    {
        requestAngleDataTimeout-=argInDeltaTime;
    }
    else
    {
        requestAngleDataTimeout = 0.15f;
        currentState = CMP_TIMEOUT;
    }
}

static void CmpStateConnectedWaitIdle(float argInDeltaTime)
{
    PS_SetPriority(CMP_MUX_DEVICE_ID,25);
    PS_SetInterruptable(CMP_MUX_DEVICE_ID,true);
    requestAngleDataTimeout-=argInDeltaTime;
    if(requestAngleDataTimeout>=0)
    {}
    else
    {
        requestAngleDataTimeout = 0.15f;
        currentState = CMP_REQUEST_ANGLES_HS;
        PS_SetPriority(CMP_MUX_DEVICE_ID,45);
        PS_SetInterruptable(CMP_MUX_DEVICE_ID,true);
    }
}

static void CmpStateConnectedRequestCustomCommands_HS(float argInDeltaTime)
{
    PS_SetPriority(CMP_MUX_DEVICE_ID,99);
    PS_SetInterruptable(CMP_MUX_DEVICE_ID,false);

    if(setComspeedFrameout==false)
    {
        setComspeedFrameout = true;
        PS_SetRequiredComSpeed(CMP_MUX_DEVICE_ID,CMP_SPEED_HIGH);
    }
    else
    {
        if(isInCustomMessageMode==false)
        {
            currentState = CMP_TIMEOUT;
        }
        else
        {
            if(currentCustomMessage!=CMP_CUS_MSG_NONE)
            {
                if(PS_IsCurrent(CMP_MUX_DEVICE_ID)==true)
                {
                    if(CmpCustomMessages[currentCustomMessage]!=NULL)
                    {
                        CmpCustomMessages[currentCustomMessage]();
                    }
                    currentCustomMessage = CMP_CUS_MSG_NONE;
                    PS_SetPriority(CMP_MUX_DEVICE_ID,99);
                    PS_SetInterruptable(CMP_MUX_DEVICE_ID,false);
                    currentState = CMP_CUSTOM_COMMAND_WAIT_HS;
                    setComspeedFrameout = false;
                }
            }
        }
    }
}

static void CmpStateConnectedWaitCustomCommands_HS(float argInDeltaTime)
{
    PS_SetPriority(CMP_MUX_DEVICE_ID,99);
    PS_SetInterruptable(CMP_MUX_DEVICE_ID,false);
    if(isInCustomMessageMode==true)
    {
    }
    else
    {
        if(requestAngleDataTimeout>=0)
        {
            requestAngleDataTimeout-=argInDeltaTime;
        }
        else
        {
            requestAngleDataTimeout = 0.15f;
            currentState = CMP_TIMEOUT;
        }
    }
}

void CmpStatemachine(float argInDeltaTime)
{
    (*(CmpStates[currentState]))(argInDeltaTime);
}

static void CmpOnUpdate(float argInDeltaTime)
{
    CmpStatemachine(argInDeltaTime);
}

static void InitCMPStatemachine()
{
    CmpStates[CMP_TIMEOUT] = &CmpStateNotConnected;
    CmpStates[CMP_SET_COMPASS_HS] = &CmpStateSettingComSpeed;
    CmpStates[CMP_SET_COMPASS_HS_WAIT_RESPONSE] = &CmpStateWaitComspeedSetup;
    CmpStates[CMP_REQUEST_ANGLES_HS] = &CmpStateConnectedRequestAngles_HS;
    CmpStates[CMP_WAIT_ANGLES_HS] = &CmpStateConnectedWaitAngles_HS;
    CmpStates[CMP_REQUEST_ANGLES_LS] = &CmpStateConnectedRequestAngles_LS;
    CmpStates[CMP_WAIT_ANGLES_LS] = &CmpStateConnectedWaitAngles_LS;
    CmpStates[CMP_CUSTOM_COMMAND_REQUEST_HS] = &CmpStateConnectedRequestCustomCommands_HS;
    CmpStates[CMP_CUSTOM_COMMAND_WAIT_HS] = &CmpStateConnectedWaitCustomCommands_HS;
    CmpStates[CMP_IDLE] = &CmpStateConnectedWaitIdle;
}


bool CmpExitCustomMessageMode()
{
    if(isInCustomMessageMode==true)
    {
        if((currentState==CMP_CUSTOM_COMMAND_REQUEST_HS)||(currentState==CMP_CUSTOM_COMMAND_WAIT_HS))
        {
            currentCustomMessage = CMP_CUS_MSG_NONE;
            isInCustomMessageMode = false;
            return true;
        }
    }
    return false;
}

bool CmpIsInCustomMessageMode()
{
    return isInCustomMessageMode;
}

bool CmpEnterCustomMessageMode()
{
    if((currentState==CMP_REQUEST_ANGLES_HS)||(currentState==CMP_WAIT_ANGLES_HS))
    {
        if(isInCustomMessageMode==false)
        {
            currentCustomMessage = CMP_CUS_MSG_NONE;
            isInCustomMessageMode = true;
            return true;
        }
    }
    return false;
}

void CmpSendCustomMessage(enum CMP_CUSTOM_MSG_INDEX argInCustomMessage)
{
    if(currentCustomMessage==CMP_CUS_MSG_NONE)
    {
        if(CmpCustomMessages[argInCustomMessage]!=NULL)
        {
            currentCustomMessage = argInCustomMessage;
        }
    }
}

bool CmpAddCustomMessageCallback(enum CMP_CUSTOM_MSG_INDEX argInCustomMessage, void* argInCallback)
{
    if(argInCustomMessage!=CMP_CUS_MSG_NONE)
    {
        if(CmpCustomMessagesCallbacks[argInCustomMessage]==NULL)
        {
            CmpCustomMessagesCallbacks[argInCustomMessage] = argInCallback;
            return true;
        }
    }
    return false;
}

bool AddCompassMeasurementCallback(void* argInCallback)
{
    for(int i =0; i <CMP_MAX_SUBSCRIBERS;i++)
    {
        if(OnReadResultCallback[i] == NULL)
        {
           OnReadResultCallback[i] = argInCallback;
           return true;
        } 
    }
    return false;
}

void InitCompass()
{
    GpioWrapSetPinMode(4,GPIO_MODE_OUT);
    GpioWrapSetPinValue(4,1); 
    isInCustomMessageMode = false;
    for(int i =0; i <CMP_MAX_SUBSCRIBERS;i++)
    {
        OnReadResultCallback[i] = NULL;
    }
    InitCMPStatemachine();
    PS_AddUser(CMP_MUX_DEVICE_ID,&CmpOnUpdate,&ProcessChar);
    PS_SetPriority(CMP_MUX_DEVICE_ID,45);
    msgData[CMP_MSG_SetCommunicationRate].OnMsgReceive = &OnMsgReceive_SetCommunicationRate;
    msgData[CMP_MSG_ReadPitchRollHeading].OnMsgReceive = &OnMsgReceive_ReadPitchRollHeading;
    msgData[CMP_MSG_CalibrationStarted].OnMsgReceive = &OnMsgReceive_CalibrationStarted;
    msgData[CMP_MSG_CalibrationPointInPlace].OnMsgReceive = &OnMsgReceive_CalibrationPointInPlace;
    msgData[CMP_MSG_CalibrationResult].OnMsgReceive = &OnMsgReceive_CalibrationResult;
}
