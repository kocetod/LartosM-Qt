#include "Rangefinder.h"

#define RF_MUX_DEVICE_ID MUX_DEVICE_2
#define RF_SPEED 115200

#define RF_MAX_SUBSCRIBERS 5

static char currentMessage[256];
static int currentSymbol=0;

int missedPingsCounter = 0;
int lastMeasurementCommand = 0;
bool measureRequested = false;

void (*OnRFMeasureCallback[RF_MAX_SUBSCRIBERS])(float,float,float)=
{
   NULL,
   NULL,
   NULL,
   NULL,
   NULL
};

void (*OnRFPingCallback[RF_MAX_SUBSCRIBERS])()=
{
   NULL,
   NULL,
   NULL,
   NULL,
   NULL
};

void RfRequestMeasurement()
{
    if(rcThisDeviceType==RC_HeadDevice)
    {
        measureRequested = true;
    }
    else
    {
        commandPerformMeasurement++;
    }
}

enum RF_MSG_INDEX
{
    RF_MSG_StatusQuery,
    RF_MSG_SetPointer,
    RF_MSG_SetMinRange,
    RF_MSG_SetMaxRange,
    RF_MSG_ExecuteRangeMeasurement,
    RF_MSG_COUNT
};

static Rf_MsgData msgData[RF_MSG_COUNT]=
{
    {0xC7,6,{0,0},{""},NULL},
    {0xC5,4,{0,0},{""},NULL},
    {0x31,4,{0,0},{""},NULL},
    {0x32,4,{0,0},{""},NULL},
    {0xCC,22,{0,0},{""},NULL} 

};

static bool RfMessageChecksumIsValid()
{
    int msgIndex = -1;
    for(int i = 0; i < RF_MSG_COUNT; i++)
    {
        if(currentMessage[1]==msgData[i].msgID)
        {
            msgIndex = i;
            break;
        }
    }

    if(msgIndex>=0)
    {
        char calculatedChecksum = 0;
        for(int i=0;i<(msgData[msgIndex].msgDefaultFullLength-1);i++)
        {
            calculatedChecksum+=currentMessage[i];
        }
        calculatedChecksum^=0x50;

        if(calculatedChecksum==currentMessage[msgData[msgIndex].msgDefaultFullLength-1])
        {
            return true;
        }
    }
    return false;
}

static bool RfMessageHasFullDataLength()
{
    int msgIndex = -1;
    for(int i = 0; i < RF_MSG_COUNT; i++)
    {
        if(currentMessage[1]==msgData[i].msgID)
        {
            msgIndex = i;
            break;
        }
    }

    if(msgIndex>=0)
    {
        if(currentSymbol>(msgData[msgIndex].msgDefaultFullLength-1))
        {
            return true;
        }
    }
    else
    {
        if(currentSymbol>1)
        {
            //if(currentMessage[1]==0x00)
            //{
                currentSymbol = 0;
                memset(&currentMessage, 0, 256*sizeof(unsigned char));
                return false;
            //}
        }
    }
    return false;
}

static bool RfMessageHasValidStart()
{
    if(currentMessage[0]==0x59)
    {
        return true;
    }
    return false;
}

static bool RfMessageIsValid()
{
    if(RfMessageHasValidStart()==true)
    {
        if(currentSymbol>1)
        {
            if(RfMessageHasFullDataLength()==true)
            {
                if(RfMessageChecksumIsValid()==true)
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
    }
    else
    {
        currentSymbol = 0;
        memset(&currentMessage, 0, 256*sizeof(unsigned char));
    }
    return false;
}

static char RfGetMessageID()
{
    return currentMessage[1];
}

static void RfStoreMessage()
{
    char msgId = RfGetMessageID();
    for(int i = 0; i<RF_MSG_COUNT;i++)
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

static void RfProcessMessage()
{
    if(RfMessageIsValid()==true)
    {
        RfStoreMessage();
        currentSymbol = 0;
        memset(&currentMessage, 0, 256*sizeof(unsigned char));
    }
}

static void RfProcessChar(char argInChar)
{
    currentMessage[currentSymbol] = argInChar;
    if(currentSymbol<(256-1))
    {
        currentSymbol++;
    }
    RfProcessMessage();
}
int rfMaxRange = 25000;
int rfMinRange = 2;
int targetNum = 0;
float targetOne = 0;
float targetTwo = 0;
float targetThree = 0;

void ReadTargets(char dataArr[])
{

  uint8_t targetOneArr[4] = {dataArr[5], dataArr[4], dataArr[3], dataArr[2]};
  uint8_t targetTwoArr[4] = {dataArr[11], dataArr[10], dataArr[9], dataArr[8]};
  uint8_t targetThreeArr[4] = {dataArr[17], dataArr[16], dataArr[15], dataArr[14]};

  float valueOne = 0;
  uint32_t *const pyOne = (uint32_t *)&valueOne;

  *pyOne = ((uint32_t)targetOneArr[0] << 24) |
           ((uint32_t)targetOneArr[1] << 16) |
           ((uint32_t)targetOneArr[2] << 8) |
           ((uint32_t)targetOneArr[3] << 0);

  targetOne = (valueOne);

  if (targetOne < (float)rfMinRange)
  {
    targetOne = 0.00;
  }
  if (targetOne != 0.00)
  {
    targetNum = 1;
  }
  float valueTwo = 0;
  uint32_t *const pyTwo = (uint32_t *)&valueTwo;

  *pyTwo = ((uint32_t)targetTwoArr[0] << 24) |
           ((uint32_t)targetTwoArr[1] << 16) |
           ((uint32_t)targetTwoArr[2] << 8) |
           ((uint32_t)targetTwoArr[3] << 0);

  targetTwo = (valueTwo);

  if (targetTwo < (float)rfMinRange)
  {
    targetTwo = 0.00;
  }
  if (targetTwo != 0.00)
  {
    targetNum = 2;
  }
  float valueThree = 0;
  uint32_t *const pyThree = (uint32_t *)&valueThree;

  *pyThree = ((uint32_t)targetThreeArr[0] << 24) |
             ((uint32_t)targetThreeArr[1] << 16) |
             ((uint32_t)targetThreeArr[2] << 8) |
             ((uint32_t)targetThreeArr[3] << 0);

  targetThree = (valueThree);

  if (targetThree < (float)rfMinRange)
  {
    targetThree = 0.00;
  }

  if (targetThree != 0.00)
  {
    targetNum = 3;
  }

  if (targetOne == 0.00 && targetTwo == 0.00 && targetThree == 0.00)
  {
    targetNum = 0;
  }
}

const char singleMeasureCmd[] = {0xCC, 0x20, 0x00, 0x00, 0xBC};
const char setPointeOnCmd[] = {0xC5, 0x02, 0x97};
const char initLrfCmd[] = {0xC0, 0x90}; 

static void RfSendMeasurementRequest()
{
    if (PS_IsCurrent(RF_MUX_DEVICE_ID))
    {
        char message[5];

        message[0] = 0xCC;
        //message[1] = 0x03;
        message[1] = 0x20;
        message[2] = 0x00;
        message[3] = 0x00;
        message[4] = 0xBC;
        //message[4] = 0x9F;

        PS_Send(RF_MUX_DEVICE_ID, &message, 5);
    }
}


static void RfSendPing()
{
    if(PS_IsCurrent(RF_MUX_DEVICE_ID))
    {
        char message[2];

        message[0] = 0xC7;
        message[1] = 0x97;

        PS_Send(RF_MUX_DEVICE_ID,&message,2);
    }
}  


static void RfSetPointer()
{
    if(PS_IsCurrent(RF_MUX_DEVICE_ID))
    {
        char message[3];

        message[0] = 0xC5;
        if(rcRangefinderPointerTurnOn==1)
        {
            message[1] = 0x02;
        }
        else
        {
            message[1] = 0x00;
        }
        message[2] = (message[0]+message[1])^0x50;


        PS_Send(RF_MUX_DEVICE_ID,&message,3);
    }
}

static void RfSetMinRange()
{
    if(PS_IsCurrent(RF_MUX_DEVICE_ID))
    {
        char message[4];

        message[0] = 0x31;
        message[1] = 0x02;//(char)rfMinRange;
        message[2] = 0x00;//(char)(rfMinRange>>8);

        message[3] = (message[0]+message[1]+message[2])^0x50;


        PS_Send(RF_MUX_DEVICE_ID,&message,4);
    }
}

static void RfSetMaxRange()
{
    if(PS_IsCurrent(RF_MUX_DEVICE_ID))
    {
        char message[4];

        message[0] = 0x32;
        message[1] = 0xA8;//(char)rfMaxRange;
        message[2] = 0x61;//(char)(rfMaxRange>>8);

        message[3] = (message[0]+message[1]+message[2])^0x50;


        PS_Send(RF_MUX_DEVICE_ID,&message,4);
    }
}

enum RANGEFINDER_DEVICE_STATES
{
    RF_NOT_CONNECTED,
    RF_SEND_PING,
    RF_WAIT_PING_REPLY,
    RF_SET_POINTER,
    RF_SET_POINTER_WAIT_RESPONCE,
    RF_SET_MIN_RANGE,
    RF_SET_MIN_RANGE_WAIT_RESPONCE,
    RF_SET_MAX_RANGE,
    RF_SET_MAX_RANGE_WAIT_RESPONCE,
    RF_EXECUTE_MEASUREMENT,
    RF_EXECUTE_MEASUREMENT_WAIT_RESPONCE,
    RF_IDLE,
    RF_IDLE_CHECK_CONNECTION,
    RF_IDLE_CHECK_CONNECTION_WAIT_RESPONCE,
    RF_DEVICE_STATES_COUNT
};
void (*RfStates[RF_DEVICE_STATES_COUNT])(float);

static enum RANGEFINDER_DEVICE_STATES currentState;


float pointerReplyTimeout = 0.55f;
float pingWaitTimeout = 0.35f;
float idlePingTimeout = 2.33f;
float pointerMaxRangeTimeout = 0.55f;
float pointerMinRangeTimeout = 0.55f;
float pingReplyTimeout = 0.35f;
float rfConnectAttemptTimeout = 0.1f;
float measureWaitTimeout = 2.0f;

float rftestTimeout = 15;

static void RfOnMsgReceive_StatusQuery()
{
    if((currentState==RF_WAIT_PING_REPLY)||(currentState==RF_SEND_PING))
    {
        currentState=RF_SET_POINTER;
        pingWaitTimeout = 0.35;
    }
    else if((currentState==RF_IDLE_CHECK_CONNECTION_WAIT_RESPONCE)||(currentState==RF_IDLE_CHECK_CONNECTION))
    {
        idlePingTimeout = 2.33f;
        PS_SetPriority(RF_MUX_DEVICE_ID,27);
        PS_SetInterruptable(RF_MUX_DEVICE_ID,true);
        currentState = RF_IDLE;
    }
    missedPingsCounter = 0;

    for(int i =0; i <RF_MAX_SUBSCRIBERS;i++)
    {
        if(OnRFPingCallback[i] != NULL)
        {
           OnRFPingCallback[i]();
        }
    }
}

static void RfOnMsgReceive_SetPointer()
{
    if((currentState==RF_SET_POINTER_WAIT_RESPONCE)||(currentState==RF_SET_POINTER))
    {
        currentState=RF_SET_MIN_RANGE;
        pointerReplyTimeout = 0.55f;
    }
}

static void RfOnMsgReceive_SetMinRange()
{
    if((currentState==RF_SET_MIN_RANGE_WAIT_RESPONCE)||(currentState==RF_SET_MIN_RANGE))
    {
        currentState=RF_SET_MAX_RANGE;
        pointerMinRangeTimeout = 0.55f;
    }
}

static void RfOnMsgReceive_SetMaxRange()
{
    if((currentState==RF_SET_MAX_RANGE_WAIT_RESPONCE)||(currentState==RF_SET_MAX_RANGE))
    {
        currentState=RF_IDLE;
        pointerMaxRangeTimeout = 0.55f;
    }
}

static void RfOnMsgReceive_MeasurementExecuted()
{
    if((currentState==RF_EXECUTE_MEASUREMENT_WAIT_RESPONCE)||(currentState==RF_EXECUTE_MEASUREMENT))
    {
        ReadTargets((char*)(&(msgData[RF_MSG_ExecuteRangeMeasurement].msg)));
        for(int i =0; i <RF_MAX_SUBSCRIBERS;i++)
        {
            if(OnRFMeasureCallback[i] != NULL)
            {
               OnRFMeasureCallback[i](targetOne,targetTwo,targetThree);
            }
        }
        measureWaitTimeout = 2.0f;
        currentState=RF_IDLE;
    }
}

void RfStateNotConnected(float argInDeltaTime)
{
    PS_SetPriority(RF_MUX_DEVICE_ID,27);
    PS_SetInterruptable(RF_MUX_DEVICE_ID,true);
    rfConnectAttemptTimeout-=argInDeltaTime;

    if(rfConnectAttemptTimeout<=0)
    {
        GpioWrapSetPinValue(5,1);
        currentState = RF_SEND_PING;
        rfConnectAttemptTimeout = 1.7f;
    }
    else if(rfConnectAttemptTimeout>1.6f)
    {
        GpioWrapSetPinValue(5,0);
    }
}

void RfStateSendPing(float arginDeltaTime)
{
    PS_SetPriority(RF_MUX_DEVICE_ID,57);
    PS_SetInterruptable(RF_MUX_DEVICE_ID,false);
    if(PS_IsCurrent(RF_MUX_DEVICE_ID)==true)
    {
        RfSendPing();
        PS_SetPriority(RF_MUX_DEVICE_ID,90);
        PS_SetInterruptable(RF_MUX_DEVICE_ID,false);
        currentState = RF_WAIT_PING_REPLY;
        pingReplyTimeout = 0.2f;
    }
} 

static void RfStateWaitPingReply(float argInDeltaTime)
{
    PS_SetPriority(RF_MUX_DEVICE_ID,90);
    PS_SetInterruptable(RF_MUX_DEVICE_ID,false);
    pingReplyTimeout-=argInDeltaTime;
    if(pingReplyTimeout<=0)
    {
        missedPingsCounter++;
        PS_SetPriority(RF_MUX_DEVICE_ID,27);
        PS_SetInterruptable(RF_MUX_DEVICE_ID,true);
        pingReplyTimeout = 0.2f;

        if(missedPingsCounter>3) 
        {
            currentState = RF_NOT_CONNECTED;
            missedPingsCounter = 0;
        }
        else
        {
            currentState = RF_SEND_PING;
        }
    }
}

static void RfStateSetPointer(float argInDeltaTime)
{
    PS_SetPriority(RF_MUX_DEVICE_ID,90);
    PS_SetInterruptable(RF_MUX_DEVICE_ID,false);
    if(PS_IsCurrent(RF_MUX_DEVICE_ID)==true)
    {
        RfSetPointer();
        PS_SetPriority(RF_MUX_DEVICE_ID,90);
        PS_SetInterruptable(RF_MUX_DEVICE_ID,false);
        currentState = RF_SET_POINTER_WAIT_RESPONCE;
        pointerReplyTimeout = 0.55f;
    }
}



static void RfStateWaitPointerReply(float argInDeltaTime)
{
    PS_SetPriority(RF_MUX_DEVICE_ID,90);
    PS_SetInterruptable(RF_MUX_DEVICE_ID,false);
    pointerReplyTimeout-=argInDeltaTime;
    if(pointerReplyTimeout<=0)
    {
        PS_SetPriority(RF_MUX_DEVICE_ID,27);
        PS_SetInterruptable(RF_MUX_DEVICE_ID,true);
        currentState = RF_NOT_CONNECTED;
        pointerReplyTimeout = 0.35f;
    }
}

static void RfStateSetMinRange(float argInDeltaTime)
{
    PS_SetPriority(RF_MUX_DEVICE_ID,90);
    PS_SetInterruptable(RF_MUX_DEVICE_ID,false);
    if(PS_IsCurrent(RF_MUX_DEVICE_ID)==true)
    {
        RfSetMinRange();
        PS_SetPriority(RF_MUX_DEVICE_ID,90);
        PS_SetInterruptable(RF_MUX_DEVICE_ID,false);
        currentState = RF_SET_MIN_RANGE_WAIT_RESPONCE;
        pointerMinRangeTimeout = 0.35f;
    }
}

static void RfStateWaitMinRangeReply(float argInDeltaTime)
{
    PS_SetPriority(RF_MUX_DEVICE_ID,90);
    PS_SetInterruptable(RF_MUX_DEVICE_ID,false);
    pointerMinRangeTimeout-=argInDeltaTime;
    if(pointerMinRangeTimeout<=0)
    {
        PS_SetPriority(RF_MUX_DEVICE_ID,27);
        PS_SetInterruptable(RF_MUX_DEVICE_ID,true);
        currentState = RF_NOT_CONNECTED;
        pointerMinRangeTimeout = 0.35f;
    }
}

static void RfStateSetMaxRange(float argInDeltaTime)
{
    PS_SetPriority(RF_MUX_DEVICE_ID,90);
    PS_SetInterruptable(RF_MUX_DEVICE_ID,false);
    if(PS_IsCurrent(RF_MUX_DEVICE_ID)==true)
    {
        RfSetMaxRange();
        PS_SetPriority(RF_MUX_DEVICE_ID,90);
        PS_SetInterruptable(RF_MUX_DEVICE_ID,false);
        currentState = RF_SET_MAX_RANGE_WAIT_RESPONCE;
        pointerMaxRangeTimeout = 0.55f;
    }
}

static void RfStateWaitMaxRangeReply(float argInDeltaTime)
{
    PS_SetPriority(RF_MUX_DEVICE_ID,90);
    PS_SetInterruptable(RF_MUX_DEVICE_ID,false);
    pointerMaxRangeTimeout-=argInDeltaTime;
    if(pointerMaxRangeTimeout<=0)
    {
        PS_SetPriority(RF_MUX_DEVICE_ID,27);
        PS_SetInterruptable(RF_MUX_DEVICE_ID,true);
        currentState = RF_NOT_CONNECTED;
        pointerMaxRangeTimeout = 0.55f;
    }
}

static void RfStateIdle(float argInDeltaTime)
{
    idlePingTimeout-=argInDeltaTime;
    if(idlePingTimeout<=0)
    {
        PS_SetPriority(RF_MUX_DEVICE_ID,57);
        PS_SetInterruptable(RF_MUX_DEVICE_ID,false);
        if(PS_IsCurrent(RF_MUX_DEVICE_ID)==true)
        {
            currentState = RF_IDLE_CHECK_CONNECTION;
            idlePingTimeout = 2.33f;
        }
    }
    else
    {
        PS_SetPriority(RF_MUX_DEVICE_ID,27);
        PS_SetInterruptable(RF_MUX_DEVICE_ID,true);

        if(lastMeasurementCommand!=commandPerformMeasurement)
        {
            lastMeasurementCommand=commandPerformMeasurement;
            measureRequested=true;
        }

        if(measureRequested==true)
        {
            idlePingTimeout = 2.33f;
            currentState = RF_EXECUTE_MEASUREMENT;
            PS_SetPriority(RF_MUX_DEVICE_ID, 99);
            PS_SetInterruptable(RF_MUX_DEVICE_ID, false);
            measureRequested = false;
        }
    }
}

static void RfStateIdleCheckConnection(float argInDeltaTime)
{
    PS_SetPriority(RF_MUX_DEVICE_ID,90);
    PS_SetInterruptable(RF_MUX_DEVICE_ID,false);
    if(PS_IsCurrent(RF_MUX_DEVICE_ID)==true)
    {
        RfSendPing();
        PS_SetPriority(RF_MUX_DEVICE_ID,90);
        PS_SetInterruptable(RF_MUX_DEVICE_ID,false);
        currentState = RF_IDLE_CHECK_CONNECTION_WAIT_RESPONCE;
        pingWaitTimeout = 0.35f;
    }
}

static void RfStateIdleCheckConnectionWaitReply(float argInDeltaTime)
{
    PS_SetPriority(RF_MUX_DEVICE_ID,90);
    PS_SetInterruptable(RF_MUX_DEVICE_ID,false);
    pingWaitTimeout-=argInDeltaTime;
    if(pingWaitTimeout<=0)
    {
        PS_SetPriority(RF_MUX_DEVICE_ID,27);
        PS_SetInterruptable(RF_MUX_DEVICE_ID,true);
        currentState = RF_SEND_PING;
        pingWaitTimeout = 0.35f;
    }
}

static void RfStateIdleRequestMeasurement(float argInDeltaTime)
{
    PS_SetPriority(RF_MUX_DEVICE_ID, 90);
    PS_SetInterruptable(RF_MUX_DEVICE_ID, false);
    if (PS_IsCurrent(RF_MUX_DEVICE_ID) == true)
    {
        RfSendMeasurementRequest();
        PS_SetPriority(RF_MUX_DEVICE_ID, 90);
        PS_SetInterruptable(RF_MUX_DEVICE_ID, false);
        currentState = RF_EXECUTE_MEASUREMENT_WAIT_RESPONCE;
        pingWaitTimeout = 0.35f;
    }
}

static void RfStateRequestMeasurementWaitReply(float argInDeltaTime)
{
    PS_SetPriority(RF_MUX_DEVICE_ID, 99);
    PS_SetInterruptable(RF_MUX_DEVICE_ID, false);
    measureWaitTimeout -= argInDeltaTime;
    if (measureWaitTimeout <= 0)
    {
        PS_SetPriority(RF_MUX_DEVICE_ID, 27);
        PS_SetInterruptable(RF_MUX_DEVICE_ID, true);
        currentState = RF_IDLE;
        measureWaitTimeout = 2.0f;
    }
}
void RfStatemachine(float argInDeltaTime)
{
    (*(RfStates[currentState]))(argInDeltaTime);
}

static void RfOnUpdate(float argInDeltaTime)
{
    RfStatemachine(argInDeltaTime);
}

static void InitRFStatemachine()
{
    RfStates[RF_NOT_CONNECTED] = &RfStateNotConnected;
    RfStates[RF_SEND_PING] = &RfStateSendPing;
    RfStates[RF_WAIT_PING_REPLY] = &RfStateWaitPingReply;
    RfStates[RF_SET_POINTER] = &RfStateSetPointer;
    RfStates[RF_SET_POINTER_WAIT_RESPONCE] = &RfStateWaitPointerReply;
    RfStates[RF_SET_MIN_RANGE] = &RfStateSetMinRange;
    RfStates[RF_SET_MIN_RANGE_WAIT_RESPONCE] = &RfStateWaitMinRangeReply;
    RfStates[RF_SET_MAX_RANGE] = &RfStateSetMaxRange;
    RfStates[RF_SET_MAX_RANGE_WAIT_RESPONCE] = &RfStateWaitMaxRangeReply;
    RfStates[RF_EXECUTE_MEASUREMENT] = &RfStateIdleRequestMeasurement;
    RfStates[RF_EXECUTE_MEASUREMENT_WAIT_RESPONCE] = &RfStateRequestMeasurementWaitReply;
    RfStates[RF_IDLE] = &RfStateIdle;
    RfStates[RF_IDLE_CHECK_CONNECTION] = &RfStateIdleCheckConnection;
    RfStates[RF_IDLE_CHECK_CONNECTION_WAIT_RESPONCE] = &RfStateIdleCheckConnectionWaitReply;
}

bool AddRFMeasurementCallback(void* argInCallback)
{
    for(int i =0; i <RF_MAX_SUBSCRIBERS;i++)
    {
        if(OnRFMeasureCallback[i] == NULL)
        {
           OnRFMeasureCallback[i] = argInCallback;
           return true;
        }
    }
    return false;
}

bool AddRFPingCallback(void* argInCallback)
{
    for(int i =0; i <RF_MAX_SUBSCRIBERS;i++)
    {
        if(OnRFPingCallback[i] == NULL)
        {
           OnRFPingCallback[i] = argInCallback;
           return true;
        }
    }
    return false;
}

void OnMeasurePressed()
{
    RfRequestMeasurement();
}

void InitRangeFinder()
{
    GpioWrapSetPinMode(5,GPIO_MODE_OUT);
    GpioWrapSetPinValue(5,1);
    InitRFStatemachine();
    PS_AddUser(RF_MUX_DEVICE_ID,&RfOnUpdate,&RfProcessChar);
    PS_SetPriority(RF_MUX_DEVICE_ID,50);
    PS_SetRequiredComSpeed(RF_MUX_DEVICE_ID,RF_SPEED);
    msgData[RF_MSG_StatusQuery].OnMsgReceive = &RfOnMsgReceive_StatusQuery;
    msgData[RF_MSG_SetPointer].OnMsgReceive = &RfOnMsgReceive_SetPointer;
    msgData[RF_MSG_SetMinRange].OnMsgReceive = &RfOnMsgReceive_SetMinRange;
    msgData[RF_MSG_SetMaxRange].OnMsgReceive = &RfOnMsgReceive_SetMaxRange;
    msgData[RF_MSG_ExecuteRangeMeasurement].OnMsgReceive = &RfOnMsgReceive_MeasurementExecuted;
    lastMeasurementCommand = commandPerformMeasurement;
    AddButtonsHead_OnPressedEventCallback(BTN_HEAD_LRF,&OnMeasurePressed);

}
