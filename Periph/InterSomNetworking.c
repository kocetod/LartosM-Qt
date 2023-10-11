# include "InterSomNetworking.h"

#define ISN_HEAD_UDP_PORT 29299
#define ISN_CONTROLLER_UDP_PORT 29298

#define ISN_MSG_PROVIDERS_COUNT 8
#define ISN_MSG_RECEIVERS_COUNT 8


char (*IsnPacketProviders[ISN_MSG_PROVIDERS_COUNT])(void*) =
{
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

void (*IsnPacketReceivers[ISN_MSG_RECEIVERS_COUNT])(void*) =
{
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

enum RC_DeviceType myDeviceType = RC_NONE;
int isnSocketId = -1;
ushort isnMyPort;
ushort isnPeerPort;
int isnPeerIp;

static bool IsnMessageIsValid(void* argInSocketData)
{
    Udp_SocketData* mySData = (Udp_SocketData*)(argInSocketData);
    if(mySData->buffer[0]=='@')
    {
        char dlen = mySData->buffer[1];
        char len = dlen+2;

        char checksum = 0;
        for(int i=0;i<len;i++)
        {
            checksum+=mySData->buffer[i];
        }
        if(checksum==mySData->buffer[len])
        {
            return true;
        }
    }
    return false;
}

static void IsnStoreMessage(Udp_SocketData* argInSocketData)
{
}

void IsnOnReceive(void* argInSocketData)
{
    Udp_SocketData* mySData = (Udp_SocketData*)(argInSocketData);
    if(IsnMessageIsValid(mySData)==true)
    {
        for(int i=0;i<ISN_MSG_RECEIVERS_COUNT;i++)
        {
            if(IsnPacketReceivers[i]!=NULL)
            {
                IsnPacketReceivers[i](&(mySData->buffer[2]));
            }
        }
    }
    UdpSocketClearReceiveBuffer(isnSocketId);
}

char isnData[256];
int isnLength = 0;

void IsnGenerateMessage(void* argInPacket, char argInPacketLength)
{
    if(argInPacketLength<=253)
    {
        unsigned char checksum = 0;
        int len = 0;
        isnData[0] = '@';
        len++;
        isnData[1] = argInPacketLength;
        len++;

        for(int i =0; i< argInPacketLength; i++)
        {
            isnData[len] = ((unsigned char*)argInPacket)[i];
            len++;
        }

        for(int i =0; i<len;i++)
        {
            checksum+=isnData[i];
        }
        isnData[len] = checksum;
        len++;
        isnLength = len;
    }
}

float pingTimeout = 0.25f;
char pack[255];
char packLen = 0;
void IsnStateNotConnected(float argInDeltaTime)
{
    if(pingTimeout>0)
    {
        pingTimeout-=argInDeltaTime;
    }
    else
    {
        for(int i=0;i<ISN_MSG_PROVIDERS_COUNT;i++)
        {
            if(IsnPacketProviders[i]!=NULL)
            {
                packLen = IsnPacketProviders[i](&(pack[0]));
                IsnGenerateMessage(&pack,packLen);
                UdpSend(isnSocketId, &isnData[0], isnLength);
            }
        }
        pingTimeout = 0.15f;
    }
}


enum ISN_STATES
{
    ISN_NOT_CONNECTED,

    ISN_STATES_COUNT
};

void (*IsnStates[ISN_STATES_COUNT])(float);

static enum ISN_STATES isnCurrentState;


void IsnStatemachine(float argInDeltaTime)
{
    (*(IsnStates[isnCurrentState]))(argInDeltaTime);
}

static void IsnOnUpdate(float argInDeltaTime)
{
    IsnStatemachine(argInDeltaTime);
}

static void InitIsnStatemachine()
{
    IsnStates[ISN_NOT_CONNECTED] = &IsnStateNotConnected;
}

struct timeval isnTprevFrame, isnTthisFrame;
float isnDeltatime;


void IsnSWTimerHandler(size_t argInTimerId, void * arginData)
{
    gettimeofday(&isnTthisFrame, NULL);
    isnDeltatime = (float)(isnTthisFrame.tv_sec - isnTprevFrame.tv_sec + (isnTthisFrame.tv_usec - isnTprevFrame.tv_usec) * 1e-6);
    isnTprevFrame = isnTthisFrame;
    IsnOnUpdate(isnDeltatime);
}

bool AddIsnPacketReceiver(void* argInPacketReceiverFunction)
{
    for(int i =0; i <ISN_MSG_PROVIDERS_COUNT;i++)
    {
        if(IsnPacketReceivers[i] == NULL)
        {
           IsnPacketReceivers[i] = argInPacketReceiverFunction;
           return true;
        }
    }
    return false;
}

bool AddIsnPacketProvider(void* argInPacketProviderFunction)
{
    for(int i =0; i <ISN_MSG_PROVIDERS_COUNT;i++)
    {
        if(IsnPacketProviders[i] == NULL)
        {
           IsnPacketProviders[i] = argInPacketProviderFunction;
           return true;
        }
    }
    return false;
}


void IsnInit()
{
    //int locpMyType =0;
    //int loctLength =0;
    //int result;
    //result = RcGetConfVar(RC_ThisDeviceType,&loctLength);
    //locpMyType = *result;

    myDeviceType = rcThisDeviceType;
    if(rcThisDeviceType==RC_HeadDevice)
    {
        isnMyPort = ISN_HEAD_UDP_PORT;
        isnPeerPort = ISN_CONTROLLER_UDP_PORT;
        isnPeerIp = rcControllerDeviceIp;
    }
    else if(rcThisDeviceType==RC_Controller)
    {
        isnMyPort = ISN_CONTROLLER_UDP_PORT;
        isnPeerPort = ISN_HEAD_UDP_PORT;
        isnPeerIp = rcHeadDeviceIp;
    }
    isnSocketId = UdpCreateSocket_Int(isnMyPort, isnPeerPort, isnPeerIp, &IsnOnReceive);
    InitIsnStatemachine();
    isnCurrentState = ISN_NOT_CONNECTED;
    StartSoftwareTimer(40, &IsnSWTimerHandler, TIMER_PERIODIC, NULL);

    //isnRecMsgData[PTU_REC_MSG_CheckConnection].OnMsgReceive = &Ptu_OnMsgReceive_CheckConnection;
    //ptuRecMsgData[PTU_REC_MSG_StatusReport].OnMsgReceive = &Ptu_OnMsgReceive_StatusReport;
}

