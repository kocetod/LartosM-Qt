# include "NetworkVariables.h" 



static char currentPacket[512];
static char currentPacketLength=0;

void NvSerialize(void* argInVar, int argInNvTypeLength, char * argOutResult)
{
    unsigned char *bytePtr=(unsigned char*)argInVar;
    for(int i =0; i<argInNvTypeLength;i++)
    {
        argOutResult[i] = bytePtr[i];
    }
}

void NvDeserialize(void* argInVarStart, int argInTypeLength, void* argOutResult)
{
    unsigned char *bytePtr=(unsigned char*)argInVarStart;
    unsigned char *outPtr = (unsigned char*)argOutResult;
    for(int i =0; i<argInTypeLength;i++)
    {
        outPtr[i] = bytePtr[i];
    }
}

void AddVarToPacket(void* argInVarStart, int argInTypeLength)
{
    char serBuff[511];
    NvSerialize(argInVarStart,argInTypeLength,&serBuff);
    for(int i=0;i<argInTypeLength;i++)
    {
        currentPacket[(int)currentPacketLength]=serBuff[i];
        currentPacketLength++;
    }
}

//////////Compass

char PacketCompassData(void* argOutData)
{
    currentPacketLength =0;
    currentPacket[0]= 'C';
    currentPacketLength++;
    AddVarToPacket(&cdmPitch, sizeof(int));
    AddVarToPacket(&cdmRoll, sizeof(int));
    AddVarToPacket(&cdmHeading, sizeof(int));
    AddVarToPacket(&cdmLastCalResult, sizeof(int));
    AddVarToPacket(&cdmLastMeasurementTimeS, sizeof(long));
    AddVarToPacket(&cdmLastMeasurementTimeuS, sizeof(long));
    for(int i=0;i<currentPacketLength;i++)
    {
        ((char*)argOutData)[i] = currentPacket[i];
    }
    return currentPacketLength;
}

void UnpackCompassData(void* argInData)
{
    int currentindex = 0;
    char* pData = (char*)argInData;
    if(pData[0]=='C')
    {
        currentindex++;
        NvDeserialize(&(pData[currentindex]), sizeof(int), &cdmPitch);
        currentindex+=sizeof(int);
        NvDeserialize(&(pData[currentindex]), sizeof(int), &cdmRoll);
        currentindex+=sizeof(int);
        NvDeserialize(&(pData[currentindex]), sizeof(int), &cdmHeading);
        currentindex+=sizeof(int);
        NvDeserialize(&(pData[currentindex]), sizeof(int), &cdmLastCalResult);
        currentindex+=sizeof(int);
        NvDeserialize(&(pData[currentindex]), sizeof(long), &cdmLastMeasurementTimeS);
        currentindex+=sizeof(long);
        NvDeserialize(&(pData[currentindex]), sizeof(long), &cdmLastMeasurementTimeuS);
        currentindex+=sizeof(long);
    }
}   





////////////////GPS

//char gdmTime[10];
//long gdmTimeLastMsgTime;

//char gdmDate[6];
//long gdmTimeLastMsgDate;

char PacketGpsData(void* argOutData)
{
    currentPacketLength =0;
    currentPacket[0]= 'G';
    currentPacketLength++;

    AddVarToPacket(&gdmLattitude, 16);
    AddVarToPacket(&gdmLatNS, 1);
    AddVarToPacket(&gdmLatLastMsgTime, sizeof(long));

    AddVarToPacket(&gdmLongitude, 16);
    AddVarToPacket(&gdmLongEW, 1);
    AddVarToPacket(&gdmLongLastMsgTime, sizeof(long));

    AddVarToPacket(&gdmAltitude, 8);
    AddVarToPacket(&gdmAltitudeSep, 8);
    AddVarToPacket(&gdmAltLastMsgTime, sizeof(long));

    AddVarToPacket(&gdmTime, 10);
    AddVarToPacket(&gdmTimeLastMsgTime, sizeof(long));

    AddVarToPacket(&gdmDate, 6);
    AddVarToPacket(&gdmDateLastMsgTime, sizeof(long));

    for(int i=0;i<currentPacketLength;i++)
    {
        ((char*)argOutData)[i] = currentPacket[i];
    }
    return currentPacketLength;
}

void UnpackGpsData(void* argInData)
{
    int currentindex = 0;
    char* pData = (char*)argInData;
    if(pData[0]=='G')
    {
        currentindex++;

        NvDeserialize(&(pData[currentindex]), 16, &gdmLattitude);
        currentindex+=16;
        NvDeserialize(&(pData[currentindex]), 1, &gdmLatNS);
        currentindex+=1;
        NvDeserialize(&(pData[currentindex]), sizeof(long), &gdmLatLastMsgTime);
        currentindex+=sizeof(long);

        NvDeserialize(&(pData[currentindex]), 16, &gdmLongitude);
        currentindex+=16;
        NvDeserialize(&(pData[currentindex]), 1, &gdmLongEW);
        currentindex+=1;
        NvDeserialize(&(pData[currentindex]), sizeof(long), &gdmLongLastMsgTime);
        currentindex+=sizeof(long);

        NvDeserialize(&(pData[currentindex]), 8, &gdmAltitude);
        currentindex+=8;
        NvDeserialize(&(pData[currentindex]), 8, &gdmAltitudeSep);
        currentindex+=8;
        NvDeserialize(&(pData[currentindex]), sizeof(long), &gdmAltLastMsgTime);
        currentindex+=sizeof(long);

        NvDeserialize(&(pData[currentindex]), 10, &gdmTime);
        currentindex+=10;
        NvDeserialize(&(pData[currentindex]), sizeof(long), &gdmTimeLastMsgTime);
        currentindex+=sizeof(long);

        NvDeserialize(&(pData[currentindex]), 6, &gdmDate);
        currentindex+=6;
        NvDeserialize(&(pData[currentindex]), sizeof(long), &gdmDateLastMsgTime);
        currentindex+=sizeof(long);
    }
}

//////////////Rangefinder

//float rdmTarget1;
//float rdmTarget2;
//float rdmTarget3;
//long rdmLastMeasurementTimeS;
//long rdmLastMeasurementTimeuS;


char PacketRangefinderData(void* argOutData)
{
    currentPacketLength =0;
    currentPacket[0]= 'R';
    currentPacketLength++;

    AddVarToPacket(&rdmTarget1, sizeof(float));
    AddVarToPacket(&rdmTarget2, sizeof(float));
    AddVarToPacket(&rdmTarget3, sizeof(float));

    AddVarToPacket(&rdmLastMeasurementTimeS, sizeof(long));
    AddVarToPacket(&rdmLastMeasurementTimeuS, sizeof(long));
    AddVarToPacket(&rdmLastPingTimeS, sizeof(long));

    for(int i=0;i<currentPacketLength;i++)
    {
        ((char*)argOutData)[i] = currentPacket[i];
    }
    return currentPacketLength;
}

void UnpackRangefinderData(void* argInData)
{
    int currentindex = 0;
    char* pData = (char*)argInData;
    if(pData[0]=='R')
    {
        currentindex++;
        NvDeserialize(&(pData[currentindex]), sizeof(float), &rdmTarget1);
        currentindex+=sizeof(float);
        NvDeserialize(&(pData[currentindex]), sizeof(float), &rdmTarget2);
        currentindex+=sizeof(float);
        NvDeserialize(&(pData[currentindex]), sizeof(float), &rdmTarget3);
        currentindex+=sizeof(float);
        NvDeserialize(&(pData[currentindex]), sizeof(long), &rdmLastMeasurementTimeS);
        currentindex+=sizeof(long);
        NvDeserialize(&(pData[currentindex]), sizeof(long), &rdmLastMeasurementTimeuS);
        currentindex+=sizeof(long);
        NvDeserialize(&(pData[currentindex]), sizeof(long), &rdmLastPingTimeS);
        currentindex+=sizeof(long);
    }
}

////////////// Commands
char PacketCommandsData(void* argOutData)
{
    currentPacketLength =0;
    currentPacket[0]= 'O';
    currentPacketLength++;
    AddVarToPacket(&commandPing, sizeof(int));
    AddVarToPacket(&commandPerformCalibration, sizeof(int));
    AddVarToPacket(&commandSetCalibrationPointInPlace, sizeof(int));
    AddVarToPacket(&commandPerformMeasurement, sizeof(int));
    AddVarToPacket(&commandShutDown,sizeof(int));
    AddVarToPacket(&commandSetCrosshairPositionX,sizeof(float));
    AddVarToPacket(&commandSetCrosshairPositionY,sizeof(float));

    for(int i=0;i<currentPacketLength;i++)
    {
        ((char*)argOutData)[i] = currentPacket[i];
    }
    return currentPacketLength;
}

void UnpackCommandsData(void* argInData)
{
    int currentindex = 0;
    char* pData = (char*)argInData;
    if(pData[0]=='O')
    {
        currentindex++;
        NvDeserialize(&(pData[currentindex]), sizeof(int), &commandPing);
        currentindex+=sizeof(int);
        NvDeserialize(&(pData[currentindex]), sizeof(int), &commandPerformCalibration);
        currentindex+=sizeof(int);
        NvDeserialize(&(pData[currentindex]), sizeof(int), &commandSetCalibrationPointInPlace);
        currentindex+=sizeof(int);
        NvDeserialize(&(pData[currentindex]), sizeof(int), &commandPerformMeasurement);
        currentindex+=sizeof(int);
        NvDeserialize(&(pData[currentindex]), sizeof(int), &commandShutDown);
        currentindex+=sizeof(int);
        NvDeserialize(&(pData[currentindex]), sizeof(float), &commandSetCrosshairPositionX);
        currentindex+=sizeof(float);
        NvDeserialize(&(pData[currentindex]), sizeof(float), &commandSetCrosshairPositionY);
        currentindex+=sizeof(float);
    }
}


////Cameras

char PacketCamerasData(void* argOutData)
{
    currentPacketLength =0;
    currentPacket[0]= 'A';
    currentPacketLength++;
    AddVarToPacket(&camsHeadIsInControl, sizeof(int));
    AddVarToPacket(&camsHeadPing, sizeof(long));

    for(int i=0;i<currentPacketLength;i++)
    {
        ((char*)argOutData)[i] = currentPacket[i];
    }
    return currentPacketLength;
}

void UnpackCamerasData(void* argInData)
{
    int currentindex = 0;
    char* pData = (char*)argInData;
    if(pData[0]=='A')
    {
        currentindex++;
        NvDeserialize(&(pData[currentindex]), sizeof(int), &camsHeadIsInControl);
        currentindex+=sizeof(int);
        NvDeserialize(&(pData[currentindex]), sizeof(long), &camsHeadPing);
        currentindex+=sizeof(int);
    }
}

/////////////////////ALL


char PacketAllHeadData(void* argOutData)
{
    currentPacketLength =0;
    currentPacket[0]= 'H';
    currentPacketLength++;

    AddVarToPacket(&cdmPitch, sizeof(int));
    AddVarToPacket(&cdmRoll, sizeof(int));
    AddVarToPacket(&cdmHeading, sizeof(int));
    AddVarToPacket(&cdmCmpCalState, sizeof(int));
    AddVarToPacket(&cdmLastCalResult, sizeof(int));
    AddVarToPacket(&cdmCalibrationAbort, sizeof(int));
    AddVarToPacket(&cdmLastMeasurementTimeS, sizeof(long));
    AddVarToPacket(&cdmLastMeasurementTimeuS, sizeof(long));

    AddVarToPacket(&gdmLattitude, 16);
    AddVarToPacket(&gdmLatNS, 1);
    AddVarToPacket(&gdmLatLastMsgTime, sizeof(long));
    AddVarToPacket(&gdmLongitude, 16);
    AddVarToPacket(&gdmLongEW, 1);
    AddVarToPacket(&gdmLongLastMsgTime, sizeof(long));
    AddVarToPacket(&gdmAltitude, 8);
    AddVarToPacket(&gdmAltitudeSep, 8);
    AddVarToPacket(&gdmAltLastMsgTime, sizeof(long));
    AddVarToPacket(&gdmTime, 10);
    AddVarToPacket(&gdmTimeLastMsgTime, sizeof(long));
    AddVarToPacket(&gdmDate, 6);
    AddVarToPacket(&gdmDateLastMsgTime, sizeof(long));

    AddVarToPacket(&rdmTarget1, sizeof(float));
    AddVarToPacket(&rdmTarget2, sizeof(float));
    AddVarToPacket(&rdmTarget3, sizeof(float));
    AddVarToPacket(&rdmLastMeasurementTimeS, sizeof(long));
    AddVarToPacket(&rdmLastMeasurementTimeuS, sizeof(long));
    AddVarToPacket(&rdmLastPingTimeS, sizeof(long));

    AddVarToPacket(&camsHeadIsInControl, sizeof(int));
    AddVarToPacket(&camsHeadPing, sizeof(long));

    for(int i=0;i<currentPacketLength;i++)
    {
        ((char*)argOutData)[i] = currentPacket[i];
    }
    return currentPacketLength;
}

void UnpackAllHeadData(void* argInData)
{
    int currentindex = 0;
    char* pData = (char*)argInData;
    if(pData[0]=='H')
    {
        currentindex++;

        NvDeserialize(&(pData[currentindex]), sizeof(int), &cdmPitch);
        currentindex+=sizeof(int);
        NvDeserialize(&(pData[currentindex]), sizeof(int), &cdmRoll);
        currentindex+=sizeof(int);
        NvDeserialize(&(pData[currentindex]), sizeof(int), &cdmHeading);
        currentindex+=sizeof(int);
        NvDeserialize(&(pData[currentindex]), sizeof(int), &cdmCmpCalState);
        currentindex+=sizeof(int);
        NvDeserialize(&(pData[currentindex]), sizeof(int), &cdmLastCalResult);
        currentindex+=sizeof(int);
        NvDeserialize(&(pData[currentindex]), sizeof(int), &cdmCalibrationAbort);
        currentindex+=sizeof(int);
        NvDeserialize(&(pData[currentindex]), sizeof(long), &cdmLastMeasurementTimeS);
        currentindex+=sizeof(long);
        NvDeserialize(&(pData[currentindex]), sizeof(long), &cdmLastMeasurementTimeuS);
        currentindex+=sizeof(long);

        NvDeserialize(&(pData[currentindex]), 16, &gdmLattitude);
        currentindex+=16;
        NvDeserialize(&(pData[currentindex]), 1, &gdmLatNS);
        currentindex+=1;
        NvDeserialize(&(pData[currentindex]), sizeof(long), &gdmLatLastMsgTime);
        currentindex+=sizeof(long);
        NvDeserialize(&(pData[currentindex]), 16, &gdmLongitude);
        currentindex+=16;
        NvDeserialize(&(pData[currentindex]), 1, &gdmLongEW);
        currentindex+=1;
        NvDeserialize(&(pData[currentindex]), sizeof(long), &gdmLongLastMsgTime);
        currentindex+=sizeof(long);
        NvDeserialize(&(pData[currentindex]), 8, &gdmAltitude);
        currentindex+=8;
        NvDeserialize(&(pData[currentindex]), 8, &gdmAltitudeSep);
        currentindex+=8;
        NvDeserialize(&(pData[currentindex]), sizeof(long), &gdmAltLastMsgTime);
        currentindex+=sizeof(long);
        NvDeserialize(&(pData[currentindex]), 10, &gdmTime);
        currentindex+=10;
        NvDeserialize(&(pData[currentindex]), sizeof(long), &gdmTimeLastMsgTime);
        currentindex+=sizeof(long);
        NvDeserialize(&(pData[currentindex]), 6, &gdmDate);
        currentindex+=6;
        NvDeserialize(&(pData[currentindex]), sizeof(long), &gdmDateLastMsgTime);
        currentindex+=sizeof(long);

        NvDeserialize(&(pData[currentindex]), sizeof(float), &rdmTarget1);
        currentindex+=sizeof(float);
        NvDeserialize(&(pData[currentindex]), sizeof(float), &rdmTarget2);
        currentindex+=sizeof(float);
        NvDeserialize(&(pData[currentindex]), sizeof(float), &rdmTarget3);
        currentindex+=sizeof(float);
        NvDeserialize(&(pData[currentindex]), sizeof(long), &rdmLastMeasurementTimeS);
        currentindex+=sizeof(long);
        NvDeserialize(&(pData[currentindex]), sizeof(long), &rdmLastMeasurementTimeuS);
        currentindex+=sizeof(long);
        NvDeserialize(&(pData[currentindex]), sizeof(long), &rdmLastPingTimeS);
        currentindex+=sizeof(long);

        NvDeserialize(&(pData[currentindex]), sizeof(int), &camsHeadIsInControl);
        currentindex+=sizeof(int);
        NvDeserialize(&(pData[currentindex]), sizeof(long), &camsHeadPing);
        currentindex+=sizeof(int);
    }
}



/////Init

void InitNetworkVariables()
{
    if(rcThisDeviceType==RC_HeadDevice)
    {
        //AddIsnPacketProvider(&PacketCompassData);
        //AddIsnPacketProvider(&PacketGpsData);
        //AddIsnPacketProvider(&PacketRangefinderData);
        //AddIsnPacketProvider(&PacketCamerasData);

        AddIsnPacketProvider(&PacketAllHeadData);
        AddIsnPacketReceiver(&UnpackCommandsData);
    }
    if(rcThisDeviceType==RC_Controller)
    {
        //AddIsnPacketReceiver(&UnpackCompassData);
        //AddIsnPacketReceiver(&UnpackGpsData);
        //AddIsnPacketReceiver(&UnpackRangefinderData);
        //AddIsnPacketReceiver(&UnpackCamerasData);

        AddIsnPacketReceiver(&UnpackAllHeadData);
        AddIsnPacketProvider(&PacketCommandsData);
    }
    //if(rcThisDeviceType==RC_HeadDevice)
    //{
    //    AddIsnPacketProvider(&PacketGpsData);
    //}
    //if(rcThisDeviceType==RC_Controller)
    //{
    //    AddIsnPacketReceiver(&UnpackGpsData);
    //}
    //if(rcThisDeviceType==RC_HeadDevice)
    //{
    //    AddIsnPacketProvider(&PacketRangefinderData);
    //}
    //if(rcThisDeviceType==RC_Controller)
    //{
    //    AddIsnPacketReceiver(&UnpackRangefinderData);
    //}

    //if(rcThisDeviceType==RC_Controller)
    //{
    //    AddIsnPacketProvider(&PacketCommandsData);
    //}
    //if(rcThisDeviceType==RC_HeadDevice)
    //{
    //    AddIsnPacketReceiver(&UnpackCommandsData);
    //}

    //if(rcThisDeviceType==RC_HeadDevice)
    //{
    //    AddIsnPacketProvider(&PacketCamerasData);
    //}
    //if(rcThisDeviceType==RC_Controller)
    //{
    //    AddIsnPacketReceiver(&UnpackCamerasData);
    //}
}


