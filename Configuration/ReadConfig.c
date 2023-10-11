#include "ReadConfig.h"

struct FileBuffer rcConfigurationFile;

int rcThisDeviceType;
int rcHeadDeviceIp;
int rcControllerDeviceIp;
int rcPtuIp;
int rcPtuPort;
int rcPTUDeviceId;
int rcLucidCameraIp;
int rcRangefinderPointerTurnOn;
int rcADCBatteryMin;
int rcADCBatteryMax;
int rcLucidCameraResX=1200;
int rcLucidCameraResY=750;
int rcLucidCameraOffsetX;
int rcLucidCameraOffsetY;
int rcLucidStreamMaxNumResendRequestsPerImage;
int rcLucidGevSCPD;
int rcLucidImageTimeout;
int rcLucidSystemTimeout;
int rcSkipCalibration;
int rcShowDiagnosticBars;

int RcReadIp(char* argInString)
{
    int result = 0;
    struct jReadElement arrayElement;
    unsigned char bytes[4];

    jRead((char*)rcConfigurationFile.data,argInString,&arrayElement);
    for(int z = 0; z<arrayElement.elements;z++)
    {
        bytes[z] = (unsigned char)jRead_int((char*)arrayElement.pValue,"[*",&z);
    }
    result = (bytes[3]<<24)|(bytes[2]<<16)|(bytes[1]<<8)|(bytes[0]);
    return result;
}

void RcInit()
{

    int i = readFileBuffer("/home/pi/Config.json",&rcConfigurationFile,FILE_BUFFER_MAXLEN);
    if(i>0)
    {
        rcThisDeviceType = jRead_int((char*)rcConfigurationFile.data,"{'ThisDeviceType'",NULL);

        rcHeadDeviceIp = RcReadIp("{'HeadDeviceIp'");
        rcControllerDeviceIp = RcReadIp("{'ControllerDeviceIp'");
        rcPtuIp = RcReadIp("{'PtuIp'");
        rcPtuPort = jRead_int((char*)rcConfigurationFile.data,"{'PtuPort'",NULL);
        rcPTUDeviceId = jRead_int((char*)rcConfigurationFile.data,"{'PTUDeviceId'",NULL);
        rcLucidCameraIp = RcReadIp("{'LucidCameraIp'");

        rcRangefinderPointerTurnOn = jRead_int((char*)rcConfigurationFile.data,"{'RangefinderPointerTurnOn'",NULL);
        rcADCBatteryMin = jRead_int((char*)rcConfigurationFile.data,"{'ADCBatteryMin'",NULL);
        rcADCBatteryMax = jRead_int((char*)rcConfigurationFile.data,"{'ADCBatteryMax'",NULL);


        rcLucidCameraResX = jRead_int((char*)rcConfigurationFile.data,"{'LucidCameraResX'",NULL);
        rcLucidCameraResY = jRead_int((char*)rcConfigurationFile.data,"{'LucidCameraResY'",NULL);
        rcLucidCameraOffsetX = jRead_int((char*)rcConfigurationFile.data,"{'LucidCameraOffsetX'",NULL);
        rcLucidCameraOffsetY = jRead_int((char*)rcConfigurationFile.data,"{'LucidCameraOffsetY'",NULL);

        rcLucidStreamMaxNumResendRequestsPerImage = jRead_int((char*)rcConfigurationFile.data,"{'LucidStreamMaxNumResendRequestsPerImage'",NULL);
        rcLucidGevSCPD = jRead_int((char*)rcConfigurationFile.data,"{'LucidGevSCPD'",NULL);
        rcLucidImageTimeout = jRead_int((char*)rcConfigurationFile.data,"{'LucidImageTimeout'",NULL);
        rcLucidSystemTimeout = jRead_int((char*)rcConfigurationFile.data,"{'LucidSystemTimeout'",NULL);

        rcSkipCalibration = jRead_int((char*)rcConfigurationFile.data,"{'SkipCalibration'",NULL);
        rcShowDiagnosticBars = jRead_int((char*)rcConfigurationFile.data,"{'ShowDiagnosticBars'",NULL);
    }
}
void RcOnExit()
{
    freeFileBuffer(&rcConfigurationFile);
}

