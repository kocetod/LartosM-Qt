# include "PanTiltU.h"

#define MY_UDP_PORT 3002
#define PTU_MAX_SUBSCRIBERS 5

//#define PTU_MESSAGE_HANDLES_COUNT 1

int ptuSocketId = -1;
ushort ptuSocketPort = MY_UDP_PORT;


void (*OnPtuStatusReceivedCallback[PTU_MAX_SUBSCRIBERS])(int,int)=
{
   NULL,
   NULL,
   NULL,
   NULL,
   NULL
};

enum PTU_REC_MSG_INDEX
{
    PTU_REC_MSG_CheckConnection,
    PTU_REC_MSG_StatusReport,
    PTU_RECEIVE_MSG_COUNT
};

Ptu_MsgData ptuRecMsgData[PTU_RECEIVE_MSG_COUNT] =
{
    {0x21,{0,0},{""},NULL},
    {0xf2,{0,0},{""},NULL}
};


static bool PtuMessageIsValid(void* argInSocketData)
{
    Udp_SocketData* mySData = (Udp_SocketData*)(argInSocketData);
    if(mySData->buffer[0]==0xff)
    {
        if(mySData->buffer[2]==0xbe)
        {
            if(mySData->buffer[3]==0x01)
            {
                char dataLenMsb = mySData->buffer[4];
                char dataLenLsb = mySData->buffer[5];

                uint16_t dataLen = (uint16_t)dataLenMsb;
                dataLen=dataLen<<8;
                dataLen=dataLen|dataLenLsb;

                if((dataLen+2)<=MAX_PACKET_SIZE)
                {
                    char msgChecksumMsb = mySData->buffer[dataLen-2];
                    char msgChecksumLsb = mySData->buffer[dataLen-1];

                    uint16_t msgChecksum = (uint16_t)msgChecksumMsb;
                    msgChecksum=msgChecksum<<8;
                    msgChecksum=msgChecksum|msgChecksumLsb;

                    uint16_t calculatedChecksum = 0;
                    for(int i=1;i<dataLen-2;i++)
                    {
                        calculatedChecksum+=mySData->buffer[i];
                    }
                    if(calculatedChecksum==msgChecksum)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

static void PtuStoreMessage(Udp_SocketData* argInSocketData)
{
    char msgId = argInSocketData->buffer[6];
    for(int i = 0; i<PTU_RECEIVE_MSG_COUNT;i++)
    {
        if(ptuRecMsgData[i].msgID==msgId)
        {
            gettimeofday(&ptuRecMsgData[i].msgTimeUsec,NULL);
            for(int z=0;z<PTU_MAX_MSG_LENGTH;z++)
            {
                ptuRecMsgData[i].msg[z]=(argInSocketData->buffer)[z];
            }
            if(ptuRecMsgData[i].OnMsgReceive!=NULL)
            {
                (*(ptuRecMsgData[i].OnMsgReceive))();
            }
            break;
        }
    }
}

void PtuOnReceive(void* argInSocketData)
{
    Udp_SocketData* mySData = (Udp_SocketData*)(argInSocketData);
    if(PtuMessageIsValid(mySData)==true)
    {
        PtuStoreMessage(mySData);
    }
    UdpSocketClearReceiveBuffer(ptuSocketId);
}


enum PTU_SEND_MSG_INDEX
{
    PTU_SEND_MSG_CheckConnection,
    PTU_SEND_MSG_StatusReportSetup,
    PTU_SEND_MSG_StartMechanicalInitialisation,
    PTU_SEND_MSG_SetSpeed,
    PTU_SEND_MSG_GoToAbsolute,
    PTU_SEND_MSG_Stop,
    PTU_SEND_MSG_COUNT
};


typedef struct
{
    char msgID;
    bool (*MsgConstruct)(void* argInData);
} Ptu_MsgSendData;

static char ptuConstructedMessage[PTU_MAX_MSG_LENGTH];
static int ptuConstructedMessageLength;
static int ptuPSpeed = 0;
static int ptuTSpeed = 0;

static int ptuTargAbsPan = 0;
static int ptuTargAbsTilt = 0;

static int ptuCurrentPan = 0;
static int ptuCurrentTilt = 0;
static bool ptuIsInPosition = false;
static bool ptuIsCalibrated = false;
static bool ptuIsCalibrating = false;


int PtuGetCurrentPan()
{
    return ptuCurrentPan;
}

int PtuGetCurrentTilt()
{
    return ptuCurrentTilt;
}

bool Ptu_MsgConstruct_CheckConnection(void* argInData)
{
    ptuConstructedMessageLength = 0;
    return true;
}

bool Ptu_MsgConstruct_StatusReportSetup(void* argInData)
{

    ptuConstructedMessageLength = 0;

    ptuConstructedMessage[ptuConstructedMessageLength] = 0x0;
    ptuConstructedMessageLength++;
    ptuConstructedMessage[ptuConstructedMessageLength] = ',';
    ptuConstructedMessageLength++;
    ptuConstructedMessage[ptuConstructedMessageLength] = '1';
    ptuConstructedMessageLength++;

    return true;
}

bool Ptu_MsgConstruct_MechInit(void* argInData)
{
    ptuConstructedMessageLength = 0;
    return true;
}


bool Ptu_MsgConstruct_GoToAbsolutePosition(void* argInData)
{
    int pRemPan = ptuTargAbsPan;

    int pBytedPan[6] = {0,0,0,0,0,0};

    pBytedPan[0] = pRemPan/100000;
    pRemPan -= pBytedPan[0]*100000;
    pBytedPan[1] = pRemPan/10000;
    pRemPan -= (pBytedPan[1]*10000);
    pBytedPan[2] = pRemPan/1000;
    pRemPan -= (pBytedPan[2]*1000);
    pBytedPan[3] = pRemPan/100;
    pRemPan -= (pBytedPan[3]*100);
    pBytedPan[4] = pRemPan/10;
    pRemPan -= (pBytedPan[4]*10);
    pBytedPan[5] = pRemPan;

    bool tsign = false;
    int tRemTilt = ptuTargAbsTilt;
    if(tRemTilt<0)
    {
        tRemTilt = -tRemTilt;
        tsign = true;
    }

    int tBytedTilt[6] = {0,0,0,0,0,0};

    tBytedTilt[0] = tRemTilt/100000;
    tRemTilt -= tBytedTilt[0]*100000;
    tBytedTilt[1] = tRemTilt/10000;
    tRemTilt -= (tBytedTilt[1]*10000);
    tBytedTilt[2] = tRemTilt/1000;
    tRemTilt -= (tBytedTilt[2]*1000);
    tBytedTilt[3] = tRemTilt/100;
    tRemTilt -= (tBytedTilt[3]*100);
    tBytedTilt[4] = tRemTilt/10;
    tRemTilt -= (tBytedTilt[4]*10);
    tBytedTilt[5] = tRemTilt;




    ptuConstructedMessageLength = 0;

    bool pFirstValidSymbolAdded = false;
    for(int i=0; i<6; i++)
    {
        if((pBytedPan[i]!=0)||(pFirstValidSymbolAdded==true)||(i>=2))
        {
            ptuConstructedMessage[ptuConstructedMessageLength] = pBytedPan[i]+0x30;
            pFirstValidSymbolAdded = true;
            ptuConstructedMessageLength++;
            if(i==2)
            {
                ptuConstructedMessage[ptuConstructedMessageLength] = '.';
                ptuConstructedMessageLength++;
            }
        }
    }

    ptuConstructedMessage[ptuConstructedMessageLength]=0x2c;
    ptuConstructedMessageLength++;

    if(tsign==true)
    {
        ptuConstructedMessage[ptuConstructedMessageLength] = 0x2D;
        ptuConstructedMessageLength++;
    }

    bool tFirstValidSymbolAdded = false;
    for(int i=0; i<6; i++)
    {
        if((tBytedTilt[i]!=0)||(tFirstValidSymbolAdded==true)||(i>=2))
        {
            ptuConstructedMessage[ptuConstructedMessageLength] = tBytedTilt[i]+0x30;
            tFirstValidSymbolAdded = true;
            ptuConstructedMessageLength++;
            if(i==2)
            {
                ptuConstructedMessage[ptuConstructedMessageLength] = '.';
                ptuConstructedMessageLength++;
            }
        }
    }

    ptuConstructedMessage[ptuConstructedMessageLength]=0x2a;
    ptuConstructedMessageLength++;

    return true;
}

bool Ptu_MsgConstruct_SetSpeed(void* argInData)
{

    bool psign = false;
    int pRemSpeed = ptuPSpeed;
    if(ptuPSpeed<0)
    {
        pRemSpeed = -ptuPSpeed;
        psign = true;
    }

    int pBytedSpeed[6] = {0,0,0,0,0,0};

    pBytedSpeed[0] = pRemSpeed/100000;
    pRemSpeed -= pBytedSpeed[0]*100000;
    pBytedSpeed[1] = pRemSpeed/10000;
    pRemSpeed -= (pBytedSpeed[1]*10000);
    pBytedSpeed[2] = pRemSpeed/1000;
    pRemSpeed -= (pBytedSpeed[2]*1000);
    pBytedSpeed[3] = pRemSpeed/100;
    pRemSpeed -= (pBytedSpeed[3]*100);
    pBytedSpeed[4] = pRemSpeed/10;
    pRemSpeed -= (pBytedSpeed[4]*10);
    pBytedSpeed[5] = pRemSpeed;

    bool tsign = false;
    int tRemSpeed = ptuTSpeed;
    if(ptuTSpeed<0)
    {
        tRemSpeed = -ptuTSpeed;
        tsign = true;
    }

    int tBytedSpeed[6] = {0,0,0,0,0,0};

    tBytedSpeed[0] = tRemSpeed/100000;
    tRemSpeed -= tBytedSpeed[0]*100000;
    tBytedSpeed[1] = tRemSpeed/10000;
    tRemSpeed -= (tBytedSpeed[1]*10000);
    tBytedSpeed[2] = tRemSpeed/1000;
    tRemSpeed -= (tBytedSpeed[2]*1000);
    tBytedSpeed[3] = tRemSpeed/100;
    tRemSpeed -= (tBytedSpeed[3]*100);
    tBytedSpeed[4] = tRemSpeed/10;
    tRemSpeed -= (tBytedSpeed[4]*10);
    tBytedSpeed[5] = tRemSpeed;


    ptuConstructedMessageLength = 0;

    if(psign==true)
    {
        ptuConstructedMessage[ptuConstructedMessageLength] = 0x2D;
        ptuConstructedMessageLength++;
    }

    bool pFirstValidSymbolAdded = false;
    for(int i=0; i<6; i++)
    {
        if((pBytedSpeed[i]!=0)||(pFirstValidSymbolAdded==true)||(i==5))
        {
            ptuConstructedMessage[ptuConstructedMessageLength] = pBytedSpeed[i]+0x30;
            pFirstValidSymbolAdded = true;
            ptuConstructedMessageLength++;
        }
    }

    ptuConstructedMessage[ptuConstructedMessageLength]=0x2c;
    ptuConstructedMessageLength++;

    if(tsign==true)
    {
        ptuConstructedMessage[ptuConstructedMessageLength] = 0x2D;
        ptuConstructedMessageLength++;
    }

    bool tFirstValidSymbolAdded = false;
    for(int i=0; i<6; i++)
    {
        if((tBytedSpeed[i]!=0)||(tFirstValidSymbolAdded==true)||(i==5))
        {
            ptuConstructedMessage[ptuConstructedMessageLength] = tBytedSpeed[i]+0x30;
            tFirstValidSymbolAdded = true;
            ptuConstructedMessageLength++;
        }
    }

    ptuConstructedMessage[ptuConstructedMessageLength]=0x2a;
    ptuConstructedMessageLength++;

    return true;
}


bool Ptu_MsgConstruct_Stop(void* argInData)
{
    ptuConstructedMessageLength = 4;

    ptuConstructedMessage[0] = 0x30;
    ptuConstructedMessage[1] = 0x2c;
    ptuConstructedMessage[2] = 0x30;
    ptuConstructedMessage[3] = 0x2a;
    return true;
}
static Ptu_MsgSendData ptuMsgSendData[PTU_SEND_MSG_COUNT]=
{
    {0x3f,&Ptu_MsgConstruct_CheckConnection},
    {0xf3,&Ptu_MsgConstruct_StatusReportSetup},
    {0x30,&Ptu_MsgConstruct_MechInit},
    {0xb0,&Ptu_MsgConstruct_SetSpeed},
    {0xb1,&Ptu_MsgConstruct_GoToAbsolutePosition},
    {0xb0,&Ptu_MsgConstruct_Stop}
};

char ptuData[256];
int ptuLength = 0;
void GenerateMessage(char argInPlatformId, enum PTU_SEND_MSG_INDEX argInCommand)
{
    ptuData[0] = 0xff;
    ptuData[1] = argInPlatformId;
    ptuData[2] = 0xbe;
    ptuData[3] = 0x01;
    ptuData[4] = 0x00;
    ptuData[5] = 0x00;
    ptuData[6] = ptuMsgSendData[argInCommand].msgID;

    uint16_t currentMsgIndex = 7;

    if(((*(ptuMsgSendData[argInCommand].MsgConstruct))(NULL))==true)
    {
        for(int i =0; i<ptuConstructedMessageLength;i++)
        {
            ptuData[currentMsgIndex] = ptuConstructedMessage[i];
            currentMsgIndex++;
        }
    }

    uint16_t ptuDataLen = currentMsgIndex+2;
    uint8_t* dataLenPtr8 = (&ptuDataLen);

    ptuData[4] = (char)(*(dataLenPtr8+1));
    ptuData[5] = (char)(*(dataLenPtr8));

    uint16_t checksum = 0;
    uint8_t* checksumPtr8 = (&checksum);

    for(int i =1;i<currentMsgIndex;i++)
    {
        checksum+=ptuData[i];
    }
    ptuData[currentMsgIndex] = (char)(*(checksumPtr8+1));
    currentMsgIndex++;
    ptuData[currentMsgIndex] = (char)(*(checksumPtr8));
    ptuLength = currentMsgIndex+1; 
}

///////////////////////////////////////////
/// \brief LcaStatemachine
/// \param argInDeltaTime
///
///

int (*GetTilt)();
int (*GetPan)();

void PtuRegisterPanProvider(void* argInPanProvider)
{
    GetPan = argInPanProvider;
}

void PtuRegisterTiltProvider(void* argInTiltProvider)
{
    GetTilt = argInTiltProvider;
}

enum PTU_DEVICE_STATES
{
    PTU_CONNECT,
    PTU_MECH_INIT,
    PTU_OPERATIONAL,
    PTU_GO_TO_ABSOLUTE_POSITION,

    PTU_DEVICE_STATES_COUNT
};

void (*PtuStates[PTU_DEVICE_STATES_COUNT])(float);

static enum PTU_DEVICE_STATES ptuCurrentState;

bool PtuIsOperational()
{
    return (ptuCurrentState==PTU_OPERATIONAL);
}

bool PtuGoToAbsolutePosition(int argInTargetPan, int argInTargetTilt)
{
    if((ptuCurrentState==PTU_OPERATIONAL)||(ptuCurrentState==PTU_GO_TO_ABSOLUTE_POSITION))
    {
        if((argInTargetPan>=0)&&(argInTargetPan<=360000))
        {
            if((argInTargetTilt>=-90000)&&(argInTargetTilt<=90000))
            {
                if(ptuCurrentState==PTU_OPERATIONAL)
                {
                    ptuTSpeed = 0;
                    ptuPSpeed = 0;
                }

                ptuTargAbsPan = argInTargetPan;
                ptuTargAbsTilt = argInTargetTilt;
                GenerateMessage(rcPTUDeviceId,PTU_SEND_MSG_GoToAbsolute);
                UdpSend(ptuSocketId, &ptuData[0], ptuLength);
                ptuCurrentState = PTU_GO_TO_ABSOLUTE_POSITION;
                return true;
            }
        }
    }
    return false;
}


float ptuConnectTimeout = 1.0f;
void PtuStateConnect(float argInDeltaTime)
{
    if(ptuConnectTimeout>0)
    {
        ptuConnectTimeout-=argInDeltaTime;
    }
    else
    {
        GenerateMessage(rcPTUDeviceId,PTU_SEND_MSG_CheckConnection);
        UdpSend(ptuSocketId, &ptuData[0], ptuLength);
        ptuConnectTimeout = 1.0f;
    }
}

float mechInitTimeToStart = 0.0f;
float mechInitTimeout = 0.0f;

void PtuStateMechInit(float argInDeltaTime)
{
    if(mechInitTimeToStart>0)
    {
        mechInitTimeToStart-=argInDeltaTime;
    }
    else
    {
        if((ptuIsCalibrated==false)&&(ptuIsCalibrating==false))
        {
            if(mechInitTimeout>0)
            {
                mechInitTimeout-=argInDeltaTime;
            }
            else
            {
                GenerateMessage(rcPTUDeviceId,PTU_SEND_MSG_StatusReportSetup);
                UdpSend(ptuSocketId, &ptuData[0], ptuLength);
                GenerateMessage(rcPTUDeviceId,PTU_SEND_MSG_StartMechanicalInitialisation);
                UdpSend(ptuSocketId, &ptuData[0], ptuLength);
                mechInitTimeout = 10.0f;
                }
        }
    }
    if((ptuIsCalibrated==true)&&(ptuIsInPosition==true))
    {
        mechInitTimeout = 0.0f;
        mechInitTimeToStart = 0.35f;
        ptuCurrentState = PTU_OPERATIONAL;
    }
}

int lastSetPan = 0;
int lastSetTilt = 0;

int pingCounter = 5;

void PtuStateOperational(float argInDeltaTime)
{
    ptuTSpeed = 0;
    ptuPSpeed = 0;
    pingCounter--;

    if(pingCounter==0)
    {
        GenerateMessage(rcPTUDeviceId,PTU_SEND_MSG_StatusReportSetup);
        UdpSend(ptuSocketId, &ptuData[0], ptuLength);
        pingCounter=5;
    }

    if(GetPan!=NULL)
    {
        ptuPSpeed = GetPan();
    }

    if(GetTilt!=NULL)
    {
        ptuTSpeed = GetTilt();
    }


    if((ptuPSpeed!=0)||(ptuTSpeed!=0))
    {
        GenerateMessage(rcPTUDeviceId,PTU_SEND_MSG_SetSpeed);
        UdpSend(ptuSocketId, &ptuData[0], ptuLength);
        lastSetPan = ptuPSpeed;
        lastSetTilt = ptuTSpeed;
    }
    else
    {
        if((lastSetPan!=0)||(lastSetTilt!=0))
        {
            GenerateMessage(rcPTUDeviceId,PTU_SEND_MSG_Stop);
            UdpSend(ptuSocketId, &ptuData[0], ptuLength);
            lastSetPan = ptuPSpeed;
            lastSetTilt = ptuTSpeed;
        }
    }
}

float ptuIsInPositionCheck = 0.35f;
void PtuStateGoToAbsolutePosition(float argInDeltaTime)
{
    if(ptuIsInPositionCheck>0)
    {
        ptuIsInPositionCheck-=argInDeltaTime;
    }
    else
    {
        if(ptuIsInPosition==true)
        {
            ptuCurrentState = PTU_OPERATIONAL;
        }
        ptuIsInPositionCheck = 0.35f;
    }

    pingCounter--;

    if(pingCounter==0)
    {
        GenerateMessage(rcPTUDeviceId,PTU_SEND_MSG_StatusReportSetup);
        UdpSend(ptuSocketId, &ptuData[0], ptuLength);
        pingCounter=5;
    }
}

static void Ptu_OnMsgReceive_CheckConnection()
{
    if(ptuCurrentState==PTU_CONNECT)
    {
        ptuCurrentState = PTU_MECH_INIT;
    }
    else if(ptuCurrentState==PTU_MECH_INIT)
    {
        if(ptuRecMsgData[PTU_REC_MSG_CheckConnection].msg[7]==0x31)
        {
            /*if((ptuIsCalibrated==false)&&(ptuIsInPosition==true))
            {
                mechInitTimeToStart = 0.35f;
                ptuCurrentState = PTU_OPERATIONAL;
            }*/
        }
    }
}

static void Ptu_OnMsgReceive_StatusReport()
{
    if(ptuCurrentState==PTU_CONNECT)
    {
        ptuCurrentState = PTU_MECH_INIT;
    }
    else
    {

        char dataLenMSB = ptuRecMsgData[PTU_REC_MSG_StatusReport].msg[4];
        char dataLenLSB = ptuRecMsgData[PTU_REC_MSG_StatusReport].msg[5];

        int dl = (((int)dataLenMSB)<<8) + dataLenLSB;

        int panEndIndex = 0;
        int panResult = 0;

        int tiltEndIndex = 0;
        int tiltResult = 0;

        for(int i = 7;i<(dl-2);i++)
        {
            char curCh = ptuRecMsgData[PTU_REC_MSG_StatusReport].msg[i];
            if(curCh==',')
            {
                panEndIndex = i;
                break;
            }
        }
        if(panEndIndex!=0)
        {
            int dp = 0;
            for(int i = panEndIndex-1;i>=7;i--)
            {
                char curCh = ptuRecMsgData[PTU_REC_MSG_StatusReport].msg[i];
                if(curCh=='-')
                {
                    panResult = -panResult;
                    break;
                }
                else if((curCh>='0')&&(curCh<='9'))
                {
                    panResult+=((int)(curCh-'0'))*(pow(10,dp));
                    dp++;
                }
            }

            for(int i = panEndIndex+1;i<(dl-2);i++)
            {
                char curCh = ptuRecMsgData[PTU_REC_MSG_StatusReport].msg[i];
                if(curCh==',')
                {
                    tiltEndIndex = i;
                    break;
                }
            }

            if(tiltEndIndex!=0)
            {
                int dt = 0;
                for(int i = tiltEndIndex-1;i>panEndIndex;i--)
                {
                    char curCh = ptuRecMsgData[PTU_REC_MSG_StatusReport].msg[i];
                    if(curCh=='-')
                    {
                        tiltResult = -tiltResult;
                        break;
                    }
                    else if((curCh>='0')&&(curCh<='9'))
                    {
                        tiltResult+=((int)(curCh-'0'))*(pow(10,dt));
                        dt++;
                    }
                }

                if(ptuRecMsgData[PTU_REC_MSG_StatusReport].msg[tiltEndIndex+1]=='0')
                {
                    ptuIsCalibrated = false;
                    ptuIsCalibrating = false;
                }
                else if(ptuRecMsgData[PTU_REC_MSG_StatusReport].msg[tiltEndIndex+1]=='1')
                {
                    ptuIsCalibrated = false;
                    ptuIsCalibrating = true;
                }
                else
                {
                    ptuIsCalibrated = true;
                    ptuIsCalibrating = false;
                }

                if(ptuRecMsgData[PTU_REC_MSG_StatusReport].msg[tiltEndIndex+3]=='0')
                {
                    ptuIsInPosition = false;
                }
                else
                {
                    ptuIsInPosition = true;
                }

                ptuCurrentPan = panResult;
                ptuCurrentTilt = tiltResult;

                for(int i =0; i <PTU_MAX_SUBSCRIBERS;i++)
                {
                    if(OnPtuStatusReceivedCallback[i] != NULL)
                    {
                       OnPtuStatusReceivedCallback[i](ptuCurrentPan,ptuCurrentTilt);
                    }
                }

            }
        }
    }
}

void PtuStatemachine(float argInDeltaTime)
{
    (*(PtuStates[ptuCurrentState]))(argInDeltaTime);
}

static void PtuOnUpdate(float argInDeltaTime)
{
    PtuStatemachine(argInDeltaTime);
}

static void InitPtuStatemachine()
{
    PtuStates[PTU_CONNECT] = &PtuStateConnect;
    PtuStates[PTU_MECH_INIT] = &PtuStateMechInit;
    PtuStates[PTU_OPERATIONAL] = &PtuStateOperational;
    PtuStates[PTU_GO_TO_ABSOLUTE_POSITION] = &PtuStateGoToAbsolutePosition;
}

struct timeval ptuTprevFrame, ptuTthisFrame;
float ptuDeltatime;


void PtuSWTimerHandler(size_t argInTimerId, void * arginData)
{
    gettimeofday(&ptuTthisFrame, NULL);
    ptuDeltatime = (float)(ptuTthisFrame.tv_sec - ptuTprevFrame.tv_sec + (ptuTthisFrame.tv_usec - ptuTprevFrame.tv_usec) * 1e-6);
    ptuTprevFrame = ptuTthisFrame;
    PtuOnUpdate(ptuDeltatime);
}


bool AddPtuStatusCallback(void* argInCallback)
{
    for(int i =0; i <PTU_MAX_SUBSCRIBERS;i++)
    {
        if(OnPtuStatusReceivedCallback[i] == NULL)
        {
           OnPtuStatusReceivedCallback[i] = argInCallback;
           return true;
        }
    }
    return false;
}

void PtuInit()
{
    ptuSocketId = UdpCreateSocket_Int(ptuSocketPort, rcPtuPort, rcPtuIp, &PtuOnReceive);
    InitPtuStatemachine();
    ptuCurrentState = PTU_CONNECT;
    StartSoftwareTimer(10, &PtuSWTimerHandler, TIMER_PERIODIC, NULL);
    ptuRecMsgData[PTU_REC_MSG_CheckConnection].OnMsgReceive = &Ptu_OnMsgReceive_CheckConnection;
    ptuRecMsgData[PTU_REC_MSG_StatusReport].OnMsgReceive = &Ptu_OnMsgReceive_StatusReport;
}

