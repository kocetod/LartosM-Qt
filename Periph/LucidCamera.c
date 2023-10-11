# include "LucidCamera.h"
#include "Merged/LarDebug.h"

#define LUCID_MAXRES_X 2448
#define LUCID_MAXRES_Y 2048
#define SYSTEM_TIMEOUT rcLucidSystemTimeout
#define TAB1_ "  "
#define TAB2_ "    "
#define ERR_BUF 512
#define IMAGE_TIMEOUT rcLucidImageTimeout

pthread_mutex_t lucidCameraMut = PTHREAD_MUTEX_INITIALIZER;

int lcaSetupData_Width = 1200;//1000;//100;//1600;//533;//160;//1600;
int lcaSetupData_Height = 750;//740;//50;//1207;//400;//120;//1207;
char* lcaSetupData_ExposureAuto = "Continuous";
char* lcaSetupData_GainAuto = "Continuous";
char* lcaSetupData_BalanceWhiteAuto = "Continuous";

int lcaOffsetX = 0;
int lcaOffsetY = 0;

bool LcaSetOffset(int argInX, int argInY)
{
    int cornerX = (int)(LUCID_MAXRES_X-rcLucidCameraResX)/2;
    int cornerY = (int)(LUCID_MAXRES_Y-rcLucidCameraResY)/2;
    if  (
        ((cornerX+argInX)>0)
        &&((cornerY+argInY)>0)
        &&((rcLucidCameraResX+argInX)<LUCID_MAXRES_X)
        &&((rcLucidCameraResY+argInY)<LUCID_MAXRES_Y)
        )
    {
        lcaOffsetX = argInX;
        lcaOffsetY = argInY;
    }
    else
    {
        return false;
    }
}

enum CAMERA_DEVICE_STATES
{
    LCA_INIT,
    LCA_FORCE_IP,
    LCA_INIT_TIMEOUT,
    LCA_SETUP,
    LCA_STREAM,
    LCA_STOP_STREAM_TO_SETUP,
    LCA_TURN_OFF,
    LCA_OFF,
    CAMERA_DEVICE_STATES_COUNT
};

void (*LcaStates[CAMERA_DEVICE_STATES_COUNT])(float);

static enum CAMERA_DEVICE_STATES lcaCurrentState;

acSystem hSystem;
acDevice hDevice;
acNodeMap hNodeMap;

float acStreamErrorTime = 0;

void sleep_us_(unsigned long argInMicrosecounds)
{
    struct timespec ts;
    ts.tv_sec = argInMicrosecounds/1000000ul;
    ts.tv_nsec = (argInMicrosecounds/1000000ul)*1000;
    nanosleep(&ts,NULL);
}

bool ThereIsError(AC_ERROR err)
{
    if (err != AC_ERR_SUCCESS)
    {
        char pMessageBuf[ERR_BUF];
        size_t pBufLen = ERR_BUF;
        acGetLastErrorMessage(pMessageBuf, &pBufLen);
        printf("\nError: %s", pMessageBuf);
        printf("\n\nPress enter to complete\n");
        getchar();
        return true;
    }
    return false;
}

int64_t SetIntValue(acNodeMap hNodeMap, const char* nodeName, int64_t value)
{
    AC_ERROR err = AC_ERR_SUCCESS;

    acNode hNode = NULL;
    AC_ACCESS_MODE accessMode = 0;

    err = acNodeMapGetNodeAndAccessMode(hNodeMap, nodeName, &hNode, &accessMode);
    if (err != AC_ERR_SUCCESS)
        return err;

    if (accessMode != AC_ACCESS_MODE_WO && accessMode != AC_ACCESS_MODE_RW)
        return AC_ERR_ERROR;

    int64_t minimum = 0;
    int64_t maximum = 0;
    int64_t increment = 0;

    err = acIntegerGetMin(hNode, &minimum);
    if (err != AC_ERR_SUCCESS)
        return err;

    err = acIntegerGetMax(hNode, &maximum);
    if (err != AC_ERR_SUCCESS)
        return err;

    err = acIntegerGetInc(hNode, &increment);
    if (err != AC_ERR_SUCCESS)
        return err;
    value = (((value - minimum) / increment) * increment) + minimum;

    if (value < minimum)
    {
        value = minimum;
    }
    if (value > maximum)
    {
        value = maximum;
    }
    err = acIntegerSetValue(hNode, value);
    if (err != AC_ERR_SUCCESS)
        return err;

    return value;
}

AC_ERROR GetNodeValue(acNodeMap hNodeMap, const char* nodeName, char* pValue, size_t* pLen)
{
    AC_ERROR err = AC_ERR_SUCCESS;
    acNode hNode = NULL;
    AC_ACCESS_MODE accessMode = 0;

    err = acNodeMapGetNodeAndAccessMode(hNodeMap, nodeName, &hNode, &accessMode);
    if (err != AC_ERR_SUCCESS){return err;}
    if (accessMode != AC_ACCESS_MODE_RO && accessMode != AC_ACCESS_MODE_RW){return AC_ERR_ERROR;}
    err = acValueToString(hNode, pValue, pLen);
    return err;
}

AC_ERROR SetNodeValue(acNodeMap hNodeMap, const char* nodeName, const char* pValue)
{
    AC_ERROR err = AC_ERR_SUCCESS;
    acNode hNode = NULL;
    AC_ACCESS_MODE accessMode = 0;

    err = acNodeMapGetNodeAndAccessMode(hNodeMap, nodeName, &hNode, &accessMode);
    if (err != AC_ERR_SUCCESS){ return err;}
    if (accessMode != AC_ACCESS_MODE_WO && accessMode != AC_ACCESS_MODE_RW){return AC_ERR_ERROR;}
    err = acValueFromString(hNode, pValue);
    return err;
}

uint32_t GenerateNewIp(uint32_t ifSubnet, uint32_t ifIp)
{
    uint32_t newIp = 0;
    uint32_t randNum = (uint32_t)rand() & (~ifSubnet);
    while (randNum == 0 || randNum == 0xFFFFFFFF || newIp == 0 || newIp == ifIp)
    {
        randNum = (uint32_t)rand() & (~ifSubnet);
        newIp = (ifIp & ifSubnet) | (randNum);
    }

    return newIp;
}


uint32_t GenerateNewIpTest(uint32_t ifSubnet, uint32_t ifIp)
{
    unsigned char bytes[4];
    bytes[0] = 10;
    bytes[1] = 10;
    bytes[2] = 5;
    bytes[3] = 11;
    uint32_t newIp = (bytes[0]<<24)|(bytes[1]<<16)|(bytes[2]<<8)|(bytes[3]);

    return newIp;
}


void LcaStateInit(float argInDeltaTime)
{
    if(daycamHasToStream==false)
    {
        lcaCurrentState = LCA_OFF;
    }
    else
    {
        AC_ERROR err = AC_ERR_SUCCESS;
        err = acOpenSystem(&hSystem);
        //sleep(1);
        printf("\n Open System");
        err = acSystemUpdateDevices(hSystem, SYSTEM_TIMEOUT);
        //sleep(1);
        if (err == AC_ERR_SUCCESS)
        {
            printf("\n Devices");
            size_t numDevices = 0;
            err = acSystemGetNumDevices(hSystem, &numDevices);
            if (err == AC_ERR_SUCCESS)
            {
                if (numDevices == 0)
                {
                    printf("\nNo camera connected\n");
                    acCloseSystem(hSystem);
                    lcaCurrentState = LCA_INIT_TIMEOUT;
                }
                else
                {
                    printf("%sDevices(s) Available : %d\n", TAB1_, (int)numDevices);

                    // get device information, used to force ip if needed
                    uint64_t macAddress = 0;
                    uint32_t ipAddress = 0;
                    uint32_t subnetMask = 0;
                    uint32_t defaultGateway = 0;

                    err =   acSystemGetDeviceMacAddress(hSystem, 0, &macAddress) |
                            acSystemGetDeviceIpAddress(hSystem, 0, &ipAddress) |
                            acSystemGetDeviceSubnetMask(hSystem, 0, &subnetMask) |
                            acSystemGetDeviceDefaultGateway(hSystem, 0, &defaultGateway);

                    if (err != AC_ERR_SUCCESS)
                    {
                        printf("\nWarning: failed to retrieve one or more initial address integer values\n");
                        acCloseSystem(hSystem);
                        lcaCurrentState = LCA_INIT_TIMEOUT;
                    }
                    else
                    {
                        printf("%sCurrent IP Address is ", TAB2_);
                        Print_ip(ipAddress);

                        printf("%sCurrent Subnet Mask is ", TAB2_);
                        Print_ip(subnetMask);
                        // try creating a device, if unsuccessful then the device is on the wrong network, force ip
                        //acDevice hDevice;
                        err = acSystemCreateDevice(hSystem, 0, &hDevice);
                        if (err != AC_ERR_SUCCESS)
                        {
                            lcaCurrentState = LCA_FORCE_IP;
                        }
                        else
                        {
                            printf("%sDevice already on correct network", TAB1_);
                            lcaCurrentState = LCA_SETUP;
                        }
                    }
                }
            }
            else
            {
                acCloseSystem(hSystem);
                lcaCurrentState = LCA_INIT_TIMEOUT;
            }
        }
        else
        {
            acCloseSystem(hSystem);
            lcaCurrentState = LCA_INIT_TIMEOUT;
        }
    }
}

void LcaStateForceIp(float argInDeltaTime)
{
    if(daycamHasToStream==false)
    {
        lcaCurrentState = LCA_TURN_OFF;
    }
    else
    {
        AC_ERROR err = AC_ERR_SUCCESS;
        uint64_t macAddress = 0;
        uint32_t ipAddress = 0;
        uint32_t subnetMask = 0;
        uint32_t defaultGateway = 0;

        err =   acSystemGetDeviceMacAddress(hSystem, 0, &macAddress) |
                acSystemGetDeviceIpAddress(hSystem, 0, &ipAddress) |
                acSystemGetDeviceSubnetMask(hSystem, 0, &subnetMask) |
                acSystemGetDeviceDefaultGateway(hSystem, 0, &defaultGateway);
        if (err != AC_ERR_SUCCESS)
        {
            printf("\nWarning: failed to retrieve one or more initial address integer values\n");
            acCloseSystem(hSystem);
            lcaCurrentState = LCA_INIT_TIMEOUT;
        }
        else
        {
            printf("%sDevice is on an incorrect network, Force Ip\n", TAB1_);

            uint32_t ifIntSubnet = 0;
            err = acSystemGetInterfaceSubnetMask(hSystem, 0, &ifIntSubnet);
            if (err == AC_ERR_SUCCESS)
            {
                uint32_t ifIntIp = 0;
                err = acSystemGetInterfaceIpAddress(hSystem, 0, &ifIntIp);
                if (err == AC_ERR_SUCCESS)
                {
                    uint32_t newIp = GenerateNewIpTest(ifIntSubnet, ifIntIp);

                    err = acSystemForceIpAddress(hSystem, macAddress, newIp, subnetMask, defaultGateway);
                    if (err != AC_ERR_SUCCESS)
                    {
                        printf("%sForced Camera to the correct network\n", TAB1_);
                    }
                }
            }
        }
        acCloseSystem(hSystem);
        lcaCurrentState = LCA_INIT;
    }
}

float lcaInitTimeout = 2.0f;

void LcaStateInitTimeout(float argInDeltaTime)
{
    if(daycamHasToStream==false)
    {
        lcaInitTimeout = 2.0f;
        lcaCurrentState = LCA_OFF;
    }
    else
    {
        if(lcaInitTimeout<=0)
        {
            lcaInitTimeout = 2.0f;
            lcaCurrentState = LCA_INIT;
        }
        else
        {
            lcaInitTimeout-=argInDeltaTime;
        }
    }
}


void LcaSetupCamera(float argInDeltaTime)
{
    //sleep(1);
    AC_ERROR err = AC_ERR_SUCCESS;
    err = acDeviceGetNodeMap(hDevice, &hNodeMap);
    //sleep(1);
    SetIntValue(hNodeMap, "Width", rcLucidCameraResX);
    //sleep(1);
    SetIntValue(hNodeMap, "Height", rcLucidCameraResY);
    //sleep(1);
    SetIntValue(hNodeMap,"OffsetX",((int)(LUCID_MAXRES_X-rcLucidCameraResX)/2)+lcaOffsetX);
    SetIntValue(hNodeMap,"OffsetY",((int)(LUCID_MAXRES_Y-rcLucidCameraResY)/2)+lcaOffsetY);
    //err = acNodeMapSetEnumerationValue(hNodeMap, "PixelFormat", "Mono8");  //"Mono8" "BayerRG8"
    err = SetNodeValue(hNodeMap,"AcquisitionMode","Continuous");
    //sleep(1);
    err = SetNodeValue(hNodeMap,"ExposureAuto",lcaSetupData_ExposureAuto);
    //sleep(1);
    err = SetNodeValue(hNodeMap,"GainAuto",lcaSetupData_GainAuto);
    //sleep(1);
    err = SetNodeValue(hNodeMap,"BalanceWhiteAuto",lcaSetupData_BalanceWhiteAuto);
    //sleep(1);
    acNodeMap hTLStreamNodeMap = NULL;
    //sleep(1);
    err = acDeviceGetTLStreamNodeMap(hDevice, &hTLStreamNodeMap);
    //sleep(1);
    err = SetNodeValue(hTLStreamNodeMap,"StreamBufferHandlingMode","NewestOnly");
    //sleep(1);
    err = acNodeMapSetBooleanValue(hTLStreamNodeMap, "StreamAutoNegotiatePacketSize", true);
    //sleep(1);
    err = acNodeMapSetBooleanValue(hTLStreamNodeMap, "StreamPacketResendEnable", true);
    //sleep(1);
    err = acNodeMapSetIntegerValue(hTLStreamNodeMap, "StreamMaxNumResendRequestsPerImage", rcLucidStreamMaxNumResendRequestsPerImage);
    //sleep(1);
    err = acNodeMapSetIntegerValue(hNodeMap, "GevSCPD", rcLucidGevSCPD);
    //sleep(1);
    err = acDeviceStartStream(hDevice);
    lcaCurrentState = LCA_STREAM;
}

acBuffer hBuffer = NULL;
size_t lcaImagewidth = 0;
size_t lcaImageheight = 0;

void (*OnImageReceived)(int,int,acBuffer*);

void LcaAddOnImageReceived(void* argInOnImageReceived)
{
    OnImageReceived = argInOnImageReceived;
}

acBuffer lcaConvertedImagess[3] = {NULL,NULL,NULL};
int currentImage = 0;
int delImage = 0;

bool LcaCameraIsStreaming()
{
    return (lcaCurrentState == LCA_STREAM);
}

int u =0;
int t =0;
uint8_t* pData = NULL;

struct timeval tprevFrame, tThisFrame;
float frameDeltatime;

float frameDeltaTimeArray[20];
int lastFrameDeltaTime;

AC_ERROR AcquireImages(acDevice hDevice)
{
    t++;
    bool convBuffAllocated = false;
    bool8_t hasImageData = false;
    bool8_t isIncomplete = false;
    size_t sizeFilled = 0;

    AC_ERROR err = AC_ERR_SUCCESS;
    err = acDeviceGetBuffer(hDevice, IMAGE_TIMEOUT, &hBuffer);
    if (err != AC_ERR_SUCCESS)
    {
        //acDeviceRequeueBuffer(hDevice, hBuffer);
        return err;
    }

    err = acBufferHasImageData(hBuffer, &hasImageData);
    if (err != AC_ERR_SUCCESS)
    {
        acDeviceRequeueBuffer(hDevice, hBuffer);
        return err;
    }

    err = acBufferIsIncomplete(hBuffer, &isIncomplete);
    if (err != AC_ERR_SUCCESS)
    {
        acDeviceRequeueBuffer(hDevice, hBuffer);
        return err;
    }

    if((hasImageData==true)&&(isIncomplete==false))
    {
        err = acBufferGetSizeFilled(hBuffer, &sizeFilled);
        if (err != AC_ERR_SUCCESS)
        {
            acDeviceRequeueBuffer(hDevice, hBuffer);
            return err;
        }
        err = acImageGetWidth(hBuffer, &lcaImagewidth);
        if (err != AC_ERR_SUCCESS)
        {
            acDeviceRequeueBuffer(hDevice, hBuffer);
            return err;
        }
        err = acImageGetHeight(hBuffer, &lcaImageheight);
        if (err != AC_ERR_SUCCESS)
        {
            acDeviceRequeueBuffer(hDevice, hBuffer);
            return err;
        }

        //if(((float)sizeFilled)==(((float)(lcaImageheight*lcaImagewidth))))
        //{
            currentImage++;
            if(currentImage>=3){currentImage=0;}

            err = acImageFactoryConvert(hBuffer, PFNC_RGB8, &(lcaConvertedImagess[currentImage]));
            if (err != AC_ERR_SUCCESS)
            {
                acDeviceRequeueBuffer(hDevice, hBuffer);
                return err;
            }
            else
            {
                pthread_mutex_lock(&lucidCameraMut);
                uint8_t* lcaImageData = NULL;
                acImageGetData(lcaConvertedImagess[currentImage], &lcaImageData);

                //gettimeofday(&tThisFrame, NULL);
                //frameDeltatime = (float)((tThisFrame.tv_sec - tprevFrame.tv_sec) + ((tThisFrame.tv_usec - tprevFrame.tv_usec)* 1e-6));
                //tprevFrame = tThisFrame;

                OnImageReceived(lcaImagewidth,lcaImageheight,(acBuffer*)lcaImageData);
                pthread_mutex_unlock(&lucidCameraMut);
                convBuffAllocated=true;
            }
            delImage = currentImage+1;
            if(delImage>=3){delImage=0;}

            if(lcaConvertedImagess[delImage]!=NULL)
            {
                if(convBuffAllocated==true){acImageFactoryDestroy(lcaConvertedImagess[delImage]); convBuffAllocated = false;}
            }
        //}
    }
    else
    {
        acDeviceRequeueBuffer(hDevice, hBuffer);
        return AC_ERR_ERROR;
    }
    acDeviceRequeueBuffer(hDevice, hBuffer);
    //sleep_us_(30000);
    return err;
}


void LcaStream(float argInDeltaTime)
{
    if(daycamHasToStream==false)
    {
        lcaCurrentState = LCA_TURN_OFF;
    }
    else
    {
        AC_ERROR err = AC_ERR_SUCCESS;
        if(AcquireImages(hDevice)<0)
        {
            acStreamErrorTime+=argInDeltaTime;
            if(acStreamErrorTime>1.0f)
            {
                acDeviceStopStream(hDevice);
                acSystemDestroyDevice(hSystem, hDevice);
                acCloseSystem(hSystem);
                lcaCurrentState = LCA_INIT;
                acStreamErrorTime = 0.0f;
            }
        }
        else
        {
            acStreamErrorTime=0.0f;
        }
    }
}

void LcaStopStreamToSetup(float argInDeltaTime)
{
    acDeviceStopStream(hDevice);
    lcaCurrentState = LCA_SETUP;
}

void LcaTurnOffCamera(float argInDeltaTime)
{
    if((hSystem!=NULL)&&(hDevice!=NULL))
    {
        if((hSystem!=NULL)&&(hDevice!=NULL))
        {
            if(rcThisDeviceType==RC_Controller)
            {
                acSystemDestroyDevice(hSystem, hDevice);
            }
            else
            {
                bool8_t acDevResult;
                acDeviceIsConnected(hDevice,&acDevResult);
                if(acDevResult==true)
                {
                    acDeviceStopStream(hDevice);
                    acSystemDestroyDevice(hSystem, hDevice);
                }
            }
        }
    }
    if(hSystem!=NULL)
    {
        acCloseSystem(hSystem);
    }
    lcaCurrentState = LCA_OFF;
}

void LcaOff(float argInDeltaTime)
{
    if(daycamHasToStream==true)
    {
        lcaCurrentState = LCA_INIT_TIMEOUT;
    }
    else
    {
        sleep(1);
    }
}


void LcaStatemachine(float argInDeltaTime)
{
    (*(LcaStates[lcaCurrentState]))(argInDeltaTime);
}

static void LcaOnUpdate(float argInDeltaTime)
{
    LcaStatemachine(argInDeltaTime);
}

static void InitLcaStatemachine()
{
    LcaStates[LCA_INIT] = &LcaStateInit;
    LcaStates[LCA_FORCE_IP] = &LcaStateForceIp;
    LcaStates[LCA_INIT_TIMEOUT] = &LcaStateInitTimeout;
    LcaStates[LCA_SETUP] = &LcaSetupCamera;
    LcaStates[LCA_STREAM] = &LcaStream;
    LcaStates[LCA_STOP_STREAM_TO_SETUP] = &LcaStopStreamToSetup;
    LcaStates[LCA_TURN_OFF] = &LcaTurnOffCamera;
    LcaStates[LCA_OFF] = &LcaOff;
}

struct timeval lcaTprevFrame, lcaTthisFrame;
float lcaDeltatime;

void LcaOnUpdateHandler()
{
    gettimeofday(&lcaTthisFrame, NULL);
    lcaDeltatime = (float)(lcaTthisFrame.tv_sec - lcaTprevFrame.tv_sec + (lcaTthisFrame.tv_usec - lcaTprevFrame.tv_usec) * 1e-6);
    lcaTprevFrame = lcaTthisFrame;
    LcaOnUpdate(lcaDeltatime);
}

static void * _lca_thread(void * data);
static pthread_t lca_thread_id;


void * _lca_thread(void * data)
{
    //setpriority(PRIO_PROCESS,0,5);
    while(1)
    {
        lastFrameDeltaTime++;
        if(lastFrameDeltaTime>19)
        {
            lastFrameDeltaTime=0;
        }

        LcaOnUpdateHandler();
        gettimeofday(&tThisFrame, NULL);
        frameDeltaTimeArray[lastFrameDeltaTime] = (float)((tThisFrame.tv_sec - tprevFrame.tv_sec) + ((tThisFrame.tv_usec - tprevFrame.tv_usec)* 1e-6));
        tprevFrame = tThisFrame;

        float addD = 0;
        for(int i=0;i<20;i++)
        {
            addD+=frameDeltaTimeArray[i];
        }
        frameDeltatime = addD/20.0f;
        frameDeltatime = frameDeltaTimeArray[lastFrameDeltaTime];
    }

    return NULL;
}


int InitializeLcaThread()
{
    /*pthread_attr_t tattr;
    struct sched_param param;


    pthread_attr_init(&tattr);
    pthread_attr_getschedparam(&tattr,&param);
    param.sched_priority = -1;
    pthread_attr_setschedparam(&tattr,&param);*/


    if(pthread_create(&lca_thread_id, NULL, _lca_thread, NULL))
    {
        return 0;
    }

    return 1;
}

void LcaInitCamera()
{
    InitLcaStatemachine();
    lcaCurrentState = LCA_OFF;
    InitializeLcaThread();
}

void LcaSet(int argInImageWidth, int argInImageHeight, char* argInExposureAuto, char* argInGainAuto, char* argInBalanceWhiteAuto)
{
    if((lcaCurrentState==LCA_FORCE_IP)||(lcaCurrentState==LCA_INIT)||(lcaCurrentState==LCA_INIT_TIMEOUT)||(lcaCurrentState==LCA_STREAM)||(lcaCurrentState==LCA_STOP_STREAM_TO_SETUP)||(lcaCurrentState==LCA_OFF))
    {
        lcaSetupData_Width = argInImageWidth;
        lcaSetupData_Height = argInImageHeight;
        lcaSetupData_ExposureAuto = argInExposureAuto;
        lcaSetupData_GainAuto = argInGainAuto;
        lcaSetupData_BalanceWhiteAuto = argInBalanceWhiteAuto;
    }
    if(lcaCurrentState==LCA_STREAM)
    {
        lcaCurrentState = LCA_STOP_STREAM_TO_SETUP;
    }
}

bool LcaCameraIsOff()
{
    return (lcaCurrentState==LCA_OFF);
}

bool LcaStopCamera()
{
    if(lcaCurrentState!=LCA_OFF)
    {
        lcaCurrentState = LCA_TURN_OFF;
        return true;
    }
    return false;
}

bool LcaStartCamera()
{
    if(lcaCurrentState==LCA_OFF)
    {
        lcaCurrentState = LCA_INIT;
        return true;
    }
    return false;
}
