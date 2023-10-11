# include "GPS.h"

char currentMessage[256];
int currentSymbol=0;

bool currentlyReceivingMessage = false;

#define MSG_COUNT 7
#define GPS_SPEED_LOW 9600
#define GPS_SPEED_HIGH 115200
#define GPS_MUX_DEVICE_ID MUX_DEVICE_0

enum GPS_MSG_INDEX
{
    GPS_MSG_GPRMC,
    GPS_MSG_GPVTG,
    GPS_MSG_GPGGA,
    GPS_MSG_GPGSA,
    GPS_MSG_GPGSV,
    GPS_MSG_GPGLL,
    GPS_MSG_GPTXT
};


static GPS_MsgData msgData[MSG_COUNT]=
{
    {{"GPRMC"},0,{0,0},{""}},
    {{"GPVTG"},0,{0,0},{""}},
    {{"GPGGA"},0,{0,0},{""}},
    {{"GPGSA"},0,{0,0},{""}},
    {{"GPGSV"},0,{0,0},{""}},
    {{"GPGLL"},0,{0,0},{""}},
    {{"GPTXT"},0,{0,0},{""}}
};



static int GetMessageChecksum()
{
    char checksumChars[2];
    int currentChecksumChar = 0;
    bool checksumStarted = false;

    for(int i=0;i<256;i++)
    {
        if(checksumStarted==true)
        {
            checksumChars[currentChecksumChar] = currentMessage[i];
            currentChecksumChar++;
            if(currentChecksumChar==2)
            {
                break;
            }
        }
        if(currentMessage[i]=='*')
        {
            checksumStarted = true;
        }
    }
    int result = (int)strtol(checksumChars,NULL,16);
    return result;
}


static int CalculateChecksum()
{
    int result = 0;
    bool messageHasStarted = false;

    for(int i=0;i<256;i++)
    {
        if(currentMessage[i]=='*')
        {
            break;
        }
        if(messageHasStarted==true)
        {
            result^=currentMessage[i];
        }
        if(currentMessage[i]=='$')
        {
            messageHasStarted = true;
        }
    }
    return result;
}

static bool MessageHasSymbol(char argInChar)
{
    bool result = false;
    for(int i=0;i<256;i++)
    {
        if(currentMessage[i]==argInChar)
        {
            result = true;
            break;
        }
    }
    return result;
}

static bool MessageIsValid()
{
    if(MessageHasSymbol('$')&&MessageHasSymbol('*'))
    {
        int calculatedChecksum = 0;
        int receivedChecksum = 0;
        calculatedChecksum = CalculateChecksum();
        receivedChecksum = GetMessageChecksum();

        /*printf("%s", currentMessage);
        printf("%02x", calculatedChecksum);
        printf(" %02x", receivedChecksum);
        printf("\n");*/

        if(calculatedChecksum==receivedChecksum)
        {
            return true;
        }
        else
        {
            currentSymbol = 0;
            memset(&currentMessage, 0, 256*sizeof(unsigned char));
        }
    }
    return false;
}

static void GetMessageID(char argOutResult[5])
{
    bool messageHasStarted = false;
    int z = 0;

    for(int i=0;i<256;i++)
    {
        if(messageHasStarted==true)
        {
            if(z<5)
            {
                argOutResult[z]=currentMessage[i];
                z++;
            }
            else
            {
                break;
            }
        }
        if(currentMessage[i]=='$')
        {
            messageHasStarted = true;
        }
    }
}

static void StoreMessage()
{
    char msgId[5] = "";
    GetMessageID(msgId);
    for(int i = 0; i<MSG_COUNT;i++)
    {
        bool result = true;
        for(int z=0; z<5;z++)
        {
            if(msgId[z]!=msgData[i].msgID[z])
            {
                result = false;
                break;
            }
        }
        if(result==true)
        {
            time(&msgData[i].msgTime);
            gettimeofday(&msgData[i].msgTimeUsec,NULL);
            for(int z=0;z<256;z++)
            {
                msgData[i].msg[z]=currentMessage[z];
            }
            //if(i==GPS_MSG_GPRMC)
            //{
            //    SetSystemTime();
            //}
            break;
        }
    }
}

static void ProcessMessage()
{
    if(MessageIsValid()==true)
    {
        StoreMessage();
        //printf("\n");
        //printf("%s", currentMessage);
    }
    else
    {
         //printf("Invalid Message GPS \n");
    }
}



static void ProcessChar(char argInChar)
{
    if(argInChar=='$')
    {
        currentSymbol = 0;
        memset(&currentMessage, 0, 256*sizeof(unsigned char));
    }
    else if(argInChar==0x0A)
    {
        if(currentSymbol>0)
        {
            if(currentMessage[currentSymbol-1]== 0x0D)
            {
                ProcessMessage();
                currentSymbol = 0;
                memset(&currentMessage, 0, 256*sizeof(unsigned char));
            }
        }
    }

    currentMessage[currentSymbol] = argInChar;
    //message[17] = 0x0D;
    //message[18] = 0x0A;


    if(currentSymbol<(256-1))
    {
        currentSymbol++;
    }
}










time_t GetMsgTime(enum GPS_MSG_INDEX argInMsg)
{
    return msgData[argInMsg].msgTime;
}

struct timeval GetMsgTimeUsec(enum GPS_MSG_INDEX argInMsg)
{
    return msgData[argInMsg].msgTimeUsec;
}

void GetMsgData(enum GPS_MSG_INDEX argInMsg, int argInMsgDataIndex, char argOutData[32])
{
    int msgDataCounter =-1;
    int z = 0;
    if(msgData[argInMsg].msgTime>0)
    {
        for(int i=0; i<256;i++)
        {
            if(msgData[argInMsg].msg[i]=='$')
            {
                msgDataCounter=0;
            }
            else if(msgData[argInMsg].msg[i]==',')
            {
                msgDataCounter++;
            }
            else if(msgDataCounter==argInMsgDataIndex)
            {
                argOutData[z]=msgData[argInMsg].msg[i];
                z++;
            }
            else if(msgDataCounter>argInMsgDataIndex)
            {
                break;
            }
        }
    }
}

void SetSystemTime()
{
    char lastDate[32];
    char lastTime[32];

    GetMsgData(GPS_MSG_GPRMC, 1, lastTime);
    GetMsgData(GPS_MSG_GPRMC, 9, lastDate);

    struct tm tm_ptr;
    struct tm tm_ptr2;

    int day = (lastDate[0]-'0')*10 + (lastDate[1]-'0');
    int month = (lastDate[2]-'0')*10 + (lastDate[3]-'0');
    int year = (lastDate[4]-'0')*10 + (lastDate[5]-'0');

    int hour = (lastTime[0]-'0')*10 + (lastTime[1]-'0');
    int min = (lastTime[2]-'0')*10 + (lastTime[3]-'0');
    int sec = (lastTime[4]-'0')*10 + (lastTime[5]-'0');

    tm_ptr.tm_mday = day;
    tm_ptr.tm_mon = month;
    tm_ptr.tm_year = year + (2000-1900);

    tm_ptr.tm_hour = hour;
    tm_ptr.tm_min = min;
    tm_ptr.tm_sec = sec;

    tm_ptr2.tm_mday = 1;
    tm_ptr2.tm_mon = 1;
    tm_ptr2.tm_year = 0 + (2000-1900);

    tm_ptr2.tm_hour = 0;
    tm_ptr2.tm_min = 0;
    tm_ptr2.tm_sec = 0;
    const struct timeval tv = {mktime(&tm_ptr),0};
    const struct timeval tv_test = {mktime(&tm_ptr2),0};

    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);

    if(year<80)
    {
        if(tv_test.tv_sec<tv.tv_sec)
        {
            if((currentTime.tv_sec>(tv.tv_sec+2))||(currentTime.tv_sec<(tv.tv_sec-2)))
            {
                GpioWrapSetTime(tv.tv_sec);
            }
        }
    }
}

time_t GetLatitudeValue(char argOutLatitude[32])
{
    memset(&argOutLatitude[0],0,sizeof(char)*32);
    time_t currentTime;
    time_t ggaTime;
    time_t rmcTime;
    time_t gllTime;

    time(&currentTime);
    ggaTime = GetMsgTime(GPS_MSG_GPGGA);
    rmcTime = GetMsgTime(GPS_MSG_GPRMC);
    gllTime = GetMsgTime(GPS_MSG_GPGLL);

    if(currentTime>ggaTime+8)
    {
        if(currentTime>rmcTime+8)
        {
            if(currentTime>gllTime+8)
            {
                argOutLatitude = "";
                return 0;
            }
            else
            {
                GetMsgData(GPS_MSG_GPGLL, 1, argOutLatitude);
                return gllTime;
            }
        }
        else
        {
            GetMsgData(GPS_MSG_GPRMC, 3, argOutLatitude);
            return rmcTime;
        }
    }
    else
    {
        GetMsgData(GPS_MSG_GPGGA, 2, argOutLatitude);
        return ggaTime;
    }
}

time_t GetLatitudeNS(char argOutLatitudeNS[32])
{
    memset(&argOutLatitudeNS[0],0,sizeof(char)*32);
    time_t currentTime;
    time_t ggaTime;
    time_t rmcTime;
    time_t gllTime;

    time(&currentTime);
    ggaTime = GetMsgTime(GPS_MSG_GPGGA);
    rmcTime = GetMsgTime(GPS_MSG_GPRMC);
    gllTime = GetMsgTime(GPS_MSG_GPGLL);

    if(currentTime>ggaTime+8)
    {
        if(currentTime>rmcTime+8)
        {
            if(currentTime>gllTime+8)
            {
                argOutLatitudeNS = "";
                return 0;
            }
            else
            {
                GetMsgData(GPS_MSG_GPGLL, 2, argOutLatitudeNS);
                return gllTime;
            }
        }
        else
        {
            GetMsgData(GPS_MSG_GPRMC, 4, argOutLatitudeNS);
            return rmcTime;
        }
    }
    else
    {
        GetMsgData(GPS_MSG_GPGGA, 3, argOutLatitudeNS);
        return ggaTime;
    }
}

time_t GetLongitudeValue(char argOutLongitude[32])
{
    memset(&argOutLongitude[0],0,sizeof(char)*32);
    time_t currentTime;
    time_t ggaTime;
    time_t rmcTime;
    time_t gllTime;

    time(&currentTime);
    ggaTime = GetMsgTime(GPS_MSG_GPGGA);
    rmcTime = GetMsgTime(GPS_MSG_GPRMC);
    gllTime = GetMsgTime(GPS_MSG_GPGLL);

    if(currentTime>ggaTime+8)
    {
        if(currentTime>rmcTime+8)
        {
            if(currentTime>gllTime+8)
            {
                argOutLongitude = "";
                return 0;
            }
            else
            {
                GetMsgData(GPS_MSG_GPGLL, 3, argOutLongitude);
                return gllTime;
            }
        }
        else
        {
            GetMsgData(GPS_MSG_GPRMC, 5, argOutLongitude);
            return rmcTime;
        }
    }
    else
    {
        GetMsgData(GPS_MSG_GPGGA, 4, argOutLongitude);
        return ggaTime;
    }
}

time_t GetLongitudeEW(char argOutLongitudeEW[32])
{
    memset(&argOutLongitudeEW[0],0,sizeof(char)*32);
    time_t currentTime;
    time_t ggaTime;
    time_t rmcTime;
    time_t gllTime;

    time(&currentTime);
    ggaTime = GetMsgTime(GPS_MSG_GPGGA);
    rmcTime = GetMsgTime(GPS_MSG_GPRMC);
    gllTime = GetMsgTime(GPS_MSG_GPGLL);

    if(currentTime>ggaTime+8)
    {
        if(currentTime>rmcTime+8)
        {
            if(currentTime>gllTime+8)
            {
                argOutLongitudeEW = "";
                return 0;
            }
            else
            {
                GetMsgData(GPS_MSG_GPGLL, 4, argOutLongitudeEW);
                return gllTime;
            }
        }
        else
        {
            GetMsgData(GPS_MSG_GPRMC, 6, argOutLongitudeEW);
            return rmcTime;
        }
    }
    else
    {
        GetMsgData(GPS_MSG_GPGGA, 5, argOutLongitudeEW);
        return ggaTime;
    }
}



time_t GetAltitude_WGS84(char argOutAltitudeWGS84[32])
{
    memset(&argOutAltitudeWGS84[0],0,sizeof(char)*32);
    time_t currentTime;
    time_t ggaTime;

    time(&currentTime);
    ggaTime = GetMsgTime(GPS_MSG_GPGGA);

    if(currentTime>ggaTime+8)
    {
        argOutAltitudeWGS84 = "";
        return 0;
    }
    else
    {
        GetMsgData(GPS_MSG_GPGGA, 9, argOutAltitudeWGS84);
        return ggaTime;
    }
}

time_t GetAltitude_Sep(char argOutAltitudeSep[32])
{
    memset(&argOutAltitudeSep[0],0,sizeof(char)*32);
    time_t currentTime;
    time_t ggaTime;

    time(&currentTime);
    ggaTime = GetMsgTime(GPS_MSG_GPGGA);

    if(currentTime>ggaTime+8)
    {
        argOutAltitudeSep = "";
        return 0;
    }
    else
    {
        GetMsgData(GPS_MSG_GPGGA, 11, argOutAltitudeSep);
        return ggaTime;
    }
}


time_t GetTimeValue(char argOutTime[32])
{
    memset(&argOutTime[0],0,sizeof(char)*32);
    time_t currentTime;

    time_t rmcTime;
    time_t gllTime;

    time(&currentTime);

    rmcTime = GetMsgTime(GPS_MSG_GPRMC);
    gllTime = GetMsgTime(GPS_MSG_GPGLL);

    if(currentTime>rmcTime+8)
    {
        if(currentTime>gllTime+8)
        {
            argOutTime = "";
            return 0;
        }
        else
        {
            GetMsgData(GPS_MSG_GPGLL, 5, argOutTime);
            return gllTime;
        }
    }
    else
    {
        GetMsgData(GPS_MSG_GPRMC, 1, argOutTime);
        return rmcTime;
    }
}

time_t GetDateValue(char argOutDate[32])
{
    memset(&argOutDate[0],0,sizeof(char)*32);
    time_t currentTime;

    time_t rmcTime;

    time(&currentTime);

    rmcTime = GetMsgTime(GPS_MSG_GPRMC);

    if(currentTime>rmcTime+8)
    {
            argOutDate = "";
            return 0;
    }
    else
    {
        GetMsgData(GPS_MSG_GPRMC, 9, argOutDate);
        return rmcTime;
    }
}




//////////////////////////////////////
/// \brief The GPS_DEVICE_STATES enum
///
///
///
///



enum GPS_DEVICE_STATES
{
    GPS_TIMEOUT,
    GPS_SETTING_GPS_HS,
    GPS_SETTING_COM_HS,
    GPS_CONNECTED,
    GPS_LISTEN_HS,
    GPS_LISTEN_LS,
    GPS_RESET,
    GPS_DEVICE_STATES_COUNT
};

void (*GpsStates[GPS_DEVICE_STATES_COUNT])(float);

static enum GPS_DEVICE_STATES currentState;


float timeoutBeforeListenHS = 0.8f;
float listenHS_Time = 2.0f;
float timeoutBeforeListenLS = 0.8f;
float listenLS_Time = 2.0f;


float highPriorityTime = 0.0f;
int highPrioritySygnalStatus = 0;

float connectAttemptTimeout = 0.1f;

float setMySpeedTimeout = 0.1f;

static void DeviceStateNotConnected(float argInDeltaTime)
{
    PS_SetPriority(GPS_MUX_DEVICE_ID,20);
    PS_SetInterruptable(GPS_MUX_DEVICE_ID,true);
    connectAttemptTimeout-=argInDeltaTime;
    if(connectAttemptTimeout<=0)
    {
        currentState = GPS_LISTEN_HS;
        connectAttemptTimeout = 3.0f;
    }
}

static void DeviceStateSettingComSpeed(float argInDeltaTime)
{
    if(PS_IsCurrent(GPS_MUX_DEVICE_ID))
    {
        PS_SetPriority(GPS_MUX_DEVICE_ID,100);
        PS_SetInterruptable(GPS_MUX_DEVICE_ID,false);

        char message[20];
        message[0] = '$';
        message[1] = 'P';
        message[2] = 'M';
        message[3] = 'T';
        message[4] = 'K';
        message[5] = '2';
        message[6] = '5';
        message[7] = '1';
        message[8] = ',';
        message[9] = '1';
        message[10] = '1';
        message[11] = '5';
        message[12] = '2';
        message[13] = '0';
        message[14] = '0';
        message[15] = '*';
        message[16] = '1';
        message[17] = 'F';
        message[18] = 0x0D;
        message[19] = 0x0A;

        /*message[0] = '$';
        message[1] = 'P';
        message[2] = 'M';
        message[3] = 'T';
        message[4] = 'K';
        message[5] = '2';
        message[6] = '5';
        message[7] = '1';
        message[8] = ',';
        message[9] = '3';
        message[10] = '8';
        message[11] = '4';
        message[12] = '0';
        message[13] = '0';
        message[14] = '*';
        message[15] = '2';
        message[16] = '7';
        message[17] = 0x0D;
        message[18] = 0x0A;*/

        PS_Send(GPS_MUX_DEVICE_ID,&message,20);
        currentState = GPS_SETTING_COM_HS;
        setMySpeedTimeout = 0.1f;
    }
    else
    {
        PS_SetPriority(GPS_MUX_DEVICE_ID,50);
        PS_SetInterruptable(GPS_MUX_DEVICE_ID,true);
    }
}

static void DeviceStateSettingMyCOMSpeed(float argInDeltaTime)
{
    if(PS_IsCurrent(GPS_MUX_DEVICE_ID))
    {
        if(setMySpeedTimeout<=0)
        {
            PS_SetRequiredComSpeed(GPS_MUX_DEVICE_ID,GPS_SPEED_HIGH);
            currentState = GPS_LISTEN_HS;
        }
        setMySpeedTimeout-=argInDeltaTime;
    }
    else
    {
        PS_SetPriority(GPS_MUX_DEVICE_ID,100);
        PS_SetInterruptable(GPS_MUX_DEVICE_ID,false);
    }
}

static void DeviceStateConnected(float argInDeltaTime)
{

    highPriorityTime-=argInDeltaTime;
    if(highPriorityTime<0)
    {
        highPriorityTime = 0;
    }

    time_t currentTime;
    struct timeval currentTimeUsec;
    time_t ggaTime;
    time_t rmcTime;
    time_t gllTime;

    time(&currentTime);
    gettimeofday(&currentTimeUsec,NULL);
    ggaTime = GetMsgTime(GPS_MSG_GPGGA);
    rmcTime = GetMsgTime(GPS_MSG_GPRMC);
    gllTime = GetMsgTime(GPS_MSG_GPGLL);
    if((currentTime>(ggaTime+9))&&(currentTime>(rmcTime+9))&&(currentTime>(gllTime+9)))
    {
        currentState = GPS_LISTEN_HS;
        PS_SetPriority(GPS_MUX_DEVICE_ID,20);
        PS_SetInterruptable(GPS_MUX_DEVICE_ID,true);
    }
    else
    {
        int newSygnalStatus = GpioWrapReadPinValue(7);
        if(newSygnalStatus!=highPrioritySygnalStatus)
        {
            if(newSygnalStatus>0)
            {
                highPriorityTime = 0.3f;
            }
        }

        highPrioritySygnalStatus = newSygnalStatus;

        struct timeval rmcTimeUsec;

        rmcTimeUsec = GetMsgTimeUsec(GPS_MSG_GPRMC);

        int curtUsec = currentTimeUsec.tv_usec;

        int targetUSecLow = rmcTimeUsec.tv_usec-150000;
        int targetUSecHigh = rmcTimeUsec.tv_usec;
        if(targetUSecLow<0)
        {
            targetUSecLow+=1000000;
        }
        if(targetUSecHigh>1000000)
        {
            targetUSecHigh-=1000000;
        }
        if(targetUSecLow<targetUSecHigh)
        {
            if((curtUsec>targetUSecLow)&&(curtUsec<targetUSecHigh))
            {
                highPriorityTime=0.1f;
            }
        }
        else
        {
            if((curtUsec>targetUSecLow)||(curtUsec<targetUSecHigh))
            {
                highPriorityTime=0.1f;
            }
        }
        if(highPriorityTime>0)
        {
            PS_SetPriority(GPS_MUX_DEVICE_ID,100);
            PS_SetInterruptable(GPS_MUX_DEVICE_ID,false);
        }
        else
        {
            PS_SetPriority(GPS_MUX_DEVICE_ID,30);
            PS_SetInterruptable(GPS_MUX_DEVICE_ID,true);
        }
    }
}

static void DeviceStateListenHS(float argInDeltaTime)
{
    if(timeoutBeforeListenHS<=0)
    {
        PS_SetPriority(GPS_MUX_DEVICE_ID,100);
        PS_SetInterruptable(GPS_MUX_DEVICE_ID,false);
        PS_SetRequiredComSpeed(GPS_MUX_DEVICE_ID,GPS_SPEED_HIGH);
        if(PS_IsCurrent(GPS_MUX_DEVICE_ID))
        {
            listenHS_Time-=argInDeltaTime;

            time_t currentTime;
            time_t ggaTime;
            time_t rmcTime;
            time_t gllTime;

            time(&currentTime);
            ggaTime = GetMsgTime(GPS_MSG_GPGGA);
            rmcTime = GetMsgTime(GPS_MSG_GPRMC);
            gllTime = GetMsgTime(GPS_MSG_GPGLL);
            if((currentTime<=(ggaTime+1))||(currentTime<=(rmcTime+1))||(currentTime<=(gllTime+1)))
            {
                currentState = GPS_CONNECTED;
                listenHS_Time= 2.0f;
                timeoutBeforeListenHS = 0.8f;
            }
            else
            {
                if(listenHS_Time<0)
                {
                    currentState = GPS_LISTEN_LS;
                    listenHS_Time= 2.0f;
                    timeoutBeforeListenHS = 0.8f;
                }
            }
        }
    }
    else
    {
        PS_SetPriority(GPS_MUX_DEVICE_ID,20);
        PS_SetInterruptable(GPS_MUX_DEVICE_ID,true);
        timeoutBeforeListenHS-=argInDeltaTime;
    }
}

static void DeviceStateListenLS(float argInDeltaTime)
{
    if(timeoutBeforeListenLS<=0)
    {
        PS_SetPriority(GPS_MUX_DEVICE_ID,100);
        PS_SetInterruptable(GPS_MUX_DEVICE_ID,false);
        PS_SetRequiredComSpeed(GPS_MUX_DEVICE_ID,GPS_SPEED_LOW);
        if(PS_IsCurrent(GPS_MUX_DEVICE_ID))
        {
            listenLS_Time-=argInDeltaTime;

            time_t currentTime;
            time_t ggaTime;
            time_t rmcTime;
            time_t gllTime;

            time(&currentTime);
            ggaTime = GetMsgTime(GPS_MSG_GPGGA);
            rmcTime = GetMsgTime(GPS_MSG_GPRMC);
            gllTime = GetMsgTime(GPS_MSG_GPGLL);
            if((currentTime<=(ggaTime+1))||(currentTime<=(rmcTime+1))||(currentTime<=(gllTime+1)))
            {
                currentState = GPS_SETTING_GPS_HS;
                listenLS_Time= 2.0f;
                timeoutBeforeListenLS = 0.8f;
            }
            else
            {
                if(listenLS_Time<0)
                {
                    currentState = GPS_TIMEOUT;
                    listenLS_Time= 2.0f;
                    timeoutBeforeListenLS = 0.8f;
                }
            }
        }
    }
    else
    {
        PS_SetPriority(GPS_MUX_DEVICE_ID,20);
        PS_SetInterruptable(GPS_MUX_DEVICE_ID,true);
        timeoutBeforeListenLS-=argInDeltaTime;
    }
}

void GPSStatemachine(float argInDeltaTime)
{
    (*(GpsStates[currentState]))(argInDeltaTime);
}

static void OnUpdate(float argInDeltaTime)
{
    GPSStatemachine(argInDeltaTime);
}

static void InitGPSStatemachine()
{
    GpsStates[GPS_TIMEOUT] = &DeviceStateNotConnected;
    GpsStates[GPS_SETTING_GPS_HS] = &DeviceStateSettingComSpeed;
    GpsStates[GPS_SETTING_COM_HS] = &DeviceStateSettingMyCOMSpeed;
    GpsStates[GPS_CONNECTED] = &DeviceStateConnected;
    GpsStates[GPS_LISTEN_HS] = &DeviceStateListenHS;
    GpsStates[GPS_LISTEN_LS] = &DeviceStateListenLS;
    GpsStates[GPS_RESET] = &DeviceStateNotConnected;
}

void InitGPS()
{
    GpioWrapSetPinMode(6,GPIO_MODE_OUT);
    GpioWrapSetPinValue(6,1);
    GpioWrapSetPinMode(7,GPIO_MODE_IN); 
    InitGPSStatemachine();
    PS_AddUser(GPS_MUX_DEVICE_ID,&OnUpdate,&ProcessChar);
    PS_SetPriority(GPS_MUX_DEVICE_ID,50);
    PS_SetRequiredComSpeed(GPS_MUX_DEVICE_ID,GPS_SPEED_LOW);
}
