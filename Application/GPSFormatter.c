# include "GPSFormatter.h"


void ConcatString(char argInString1[32],char argInString2[32],char argOutResult[32])
{
    int z=0;
    int r=0;
    for(int i=0; i<32; i++)
    {
        if((int)argInString1[i]!=0)
        {
            argOutResult[r]=argInString1[i];
            r++;
        }
        else
        {
            argOutResult[r] = argInString2[z];
            r++;
            z++;
        }
    }
}

void GetFormattedLatitude(char argOutFormattedLattitude[32])
{
    //char lastLatitude[32];

    char latitudeDeg[2];
    char latitudeMin[2];
    char latitudeSecDec[4];

    int latSec_Thous = 0;

    //GetLatitudeValue(lastLatitude);



    if(gdmLattitude[0]!=(int)NULL)
    {
        latitudeDeg[0]=gdmLattitude[0];
        latitudeDeg[1]=gdmLattitude[1];
        latitudeMin[0]=gdmLattitude[2];
        latitudeMin[1]=gdmLattitude[3];

        latitudeSecDec[0] = gdmLattitude[5];
        latitudeSecDec[1] = gdmLattitude[6];
        latitudeSecDec[2] = gdmLattitude[7];
        latitudeSecDec[3] = gdmLattitude[8];

        latSec_Thous = (int)(latitudeSecDec[0]-'0')*1000;
        latSec_Thous += (int)(latitudeSecDec[1]-'0')*100;
        latSec_Thous += (int)(latitudeSecDec[2]-'0')*10;
        latSec_Thous += (int)(latitudeSecDec[3]-'0');

        float latitudeSec = ((((float)(latSec_Thous))/10000.0f)*60.0f);
        latitudeSec*=100.0f;

        int latitudeSec_thous= (((int)latitudeSec)/1000);
        int latitudeSec_hund= ((((int)latitudeSec)-(latitudeSec_thous)*1000)/100);
        int latitudeSec_dec= ((((int)latitudeSec)-(latitudeSec_thous)*1000 - latitudeSec_hund*100)/10);
        int latitudeSec_uno= ((((int)latitudeSec)-(latitudeSec_thous)*1000 - latitudeSec_hund*100 - latitudeSec_dec*10));

        argOutFormattedLattitude[0] = latitudeDeg[0];
        argOutFormattedLattitude[1] = latitudeDeg[1];
        argOutFormattedLattitude[2] = '@';
        argOutFormattedLattitude[3] = latitudeMin[0];
        argOutFormattedLattitude[4] = latitudeMin[1];
        argOutFormattedLattitude[5] = '\'';
        argOutFormattedLattitude[6] = latitudeSec_thous+'0';
        argOutFormattedLattitude[7] = latitudeSec_hund+'0';
        argOutFormattedLattitude[8] = '.';
        argOutFormattedLattitude[9] = latitudeSec_dec+'0';
        argOutFormattedLattitude[10] = latitudeSec_uno+'0';
        argOutFormattedLattitude[11] = '\"';
    }
    else
    {
        argOutFormattedLattitude[0] = 'N';
        argOutFormattedLattitude[1] = 'O';
        argOutFormattedLattitude[2] = ' ';
        argOutFormattedLattitude[3] = 'L';
        argOutFormattedLattitude[4] = 'A';
        argOutFormattedLattitude[5] = 'T';
    }
}

void GetFormattedLongitude(char argOutFormattedLongitude[32])
{
    //char lastLongitude[32];

    char longitudeDeg[3];
    char longitudeMin[2];
    char longitudeSecDec[4];

    int longSec_Thous = 0;

    //GetLongitudeValue(lastLongitude);

    if(gdmLongitude[0]!=(int)NULL)
    {
        longitudeDeg[0]=gdmLongitude[0];
        longitudeDeg[1]=gdmLongitude[1];
        longitudeDeg[2]=gdmLongitude[2];
        longitudeMin[0]=gdmLongitude[3];
        longitudeMin[1]=gdmLongitude[4];

        longitudeSecDec[0] = gdmLongitude[6];
        longitudeSecDec[1] = gdmLongitude[7];
        longitudeSecDec[2] = gdmLongitude[8];
        longitudeSecDec[3] = gdmLongitude[9];

        longSec_Thous = (int)(gdmLongitude[0]-'0')*1000;
        longSec_Thous += (int)(gdmLongitude[1]-'0')*100;
        longSec_Thous += (int)(gdmLongitude[2]-'0')*10;
        longSec_Thous += (int)(gdmLongitude[3]-'0');

        float longitudeSec = ((((float)(longSec_Thous))/10000.0f)*60.0f);
        longitudeSec*=100.0f;

        int longitudeSec_thous= (((int)longitudeSec)/1000);
        int longitudeSec_hund= ((((int)longitudeSec)-(longitudeSec_thous)*1000)/100);
        int longitudeSec_dec= ((((int)longitudeSec)-(longitudeSec_thous)*1000 - longitudeSec_hund*100)/10);
        int longitudeSec_uno= ((((int)longitudeSec)-(longitudeSec_thous)*1000 - longitudeSec_hund*100 - longitudeSec_dec*10));

        argOutFormattedLongitude[0] = longitudeDeg[0];
        argOutFormattedLongitude[1] = longitudeDeg[1];
        argOutFormattedLongitude[2] = longitudeDeg[2];
        argOutFormattedLongitude[3] = '@';
        argOutFormattedLongitude[4] = longitudeMin[0];
        argOutFormattedLongitude[5] = longitudeMin[1];
        argOutFormattedLongitude[6] = '\'';
        argOutFormattedLongitude[7] = longitudeSec_thous+'0';
        argOutFormattedLongitude[8] = longitudeSec_hund+'0';
        argOutFormattedLongitude[9] = '.';
        argOutFormattedLongitude[10] = longitudeSec_dec+'0';
        argOutFormattedLongitude[11] = longitudeSec_uno+'0';
        argOutFormattedLongitude[12] = '\"';
    }
    else
    {
        argOutFormattedLongitude[0] = 'N';
        argOutFormattedLongitude[1] = 'O';
        argOutFormattedLongitude[2] = ' ';
        argOutFormattedLongitude[3] = 'L';
        argOutFormattedLongitude[4] = 'O';
        argOutFormattedLongitude[5] = 'N';
        argOutFormattedLongitude[6] = 'G';
    }
}


void GetFormattedLat(char argOutFormattedData[32])
{
    memset(&argOutFormattedData[0],0,sizeof(char)*32);

    char latitude[32];

    GetFormattedLatitude(latitude);

    argOutFormattedData[0] = latitude[0];
    argOutFormattedData[1] = latitude[1];
    argOutFormattedData[2] = latitude[2];
    argOutFormattedData[3] = latitude[3];
    argOutFormattedData[4] = latitude[4];
    argOutFormattedData[5] = latitude[5];
    argOutFormattedData[6] = latitude[6];
    argOutFormattedData[7] = latitude[7];
    argOutFormattedData[8] = latitude[8];
    argOutFormattedData[9] = latitude[9];
    argOutFormattedData[10] = latitude[10];
    argOutFormattedData[11] = latitude[11];

    argOutFormattedData[12] = gdmLatNS[0];
}

void GetFormattedLong(char argOutFormattedData[32])
{
    memset(&argOutFormattedData[0],0,sizeof(char)*32);

    char longitude[32];

    GetFormattedLongitude(longitude);

    argOutFormattedData[0] = longitude[0];
    argOutFormattedData[1] = longitude[1];
    argOutFormattedData[2] = longitude[2];
    argOutFormattedData[3] = longitude[3];
    argOutFormattedData[4] = longitude[4];
    argOutFormattedData[5] = longitude[5];
    argOutFormattedData[6] = longitude[6];
    argOutFormattedData[7] = longitude[7];
    argOutFormattedData[8] = longitude[8];
    argOutFormattedData[9] = longitude[9];
    argOutFormattedData[10] = longitude[10];
    argOutFormattedData[11] = longitude[11];

    argOutFormattedData[12] = gdmLongEW[0];
}

void GetFormattedValue(char argOutFormattedData[32])
{
    memset(&argOutFormattedData[0],0,sizeof(char)*32);

    char latitude[32];
    char longitude[32];
    //char latNS[32];
    //char longEW[32];

    //longEW = gdmLongEW;
    //latNS = gdmLatNS;
    //GetLongitudeEW(longEW);
    //GetLatitudeNS(latNS);

    GetFormattedLatitude(latitude);
    GetFormattedLongitude(longitude);

    argOutFormattedData[0] = latitude[0];
    argOutFormattedData[1] = latitude[1];
    argOutFormattedData[2] = latitude[2];
    argOutFormattedData[3] = latitude[3];
    argOutFormattedData[4] = latitude[4];
    argOutFormattedData[5] = latitude[5];
    argOutFormattedData[6] = latitude[6];
    argOutFormattedData[7] = latitude[7];
    argOutFormattedData[8] = latitude[8];
    argOutFormattedData[9] = latitude[9];
    argOutFormattedData[10] = latitude[10];
    argOutFormattedData[11] = latitude[11];

    argOutFormattedData[12] = gdmLatNS[0];

    argOutFormattedData[13] = ' ';
    argOutFormattedData[14] = '/';
    argOutFormattedData[15] = ' ';

    argOutFormattedData[16] = longitude[0];
    argOutFormattedData[17] = longitude[1];
    argOutFormattedData[18] = longitude[2];
    argOutFormattedData[19] = longitude[3];
    argOutFormattedData[20] = longitude[4];
    argOutFormattedData[21] = longitude[5];
    argOutFormattedData[22] = longitude[6];
    argOutFormattedData[23] = longitude[7];
    argOutFormattedData[24] = longitude[8];
    argOutFormattedData[25] = longitude[9];
    argOutFormattedData[26] = longitude[10];
    argOutFormattedData[27] = longitude[11];
    argOutFormattedData[28] = longitude[12];

    argOutFormattedData[29] = gdmLongEW[0];
}

void GetFormattedDateTime(char argOutFormattedData[32])
{
    memset(&argOutFormattedData[0],0,sizeof(char)*32);

    //char time[32];
    //char date[32];

    //GetTimeValue(time);
    //GetDateValue(date);

    if(gdmDate[0]!=(int)NULL)
    {
        argOutFormattedData[0] = gdmDate[0];
        argOutFormattedData[1] = gdmDate[1];
        argOutFormattedData[2] = '.';
        argOutFormattedData[3] = gdmDate[2];
        argOutFormattedData[4] = gdmDate[3];
        argOutFormattedData[5] = '.';
        argOutFormattedData[6] = gdmDate[4];
        argOutFormattedData[7] = gdmDate[5];

        argOutFormattedData[8] = ' ';

        argOutFormattedData[9] =  gdmTime[0];
        argOutFormattedData[10] = gdmTime[1];
        argOutFormattedData[11] = ':';
        argOutFormattedData[12] = gdmTime[2];
        argOutFormattedData[13] = gdmTime[3];
        argOutFormattedData[14] = ':';
        argOutFormattedData[15] = gdmTime[4];
        argOutFormattedData[16] = gdmTime[5];
    }
    else
    {
        argOutFormattedData[0] = 'N';
        argOutFormattedData[1] = 'O';
        argOutFormattedData[2] = ' ';
        argOutFormattedData[3] = 'G';
        argOutFormattedData[4] = 'P';
        argOutFormattedData[5] = 'S';
        argOutFormattedData[8] = ' ';
        argOutFormattedData[9] =  'T';
        argOutFormattedData[10] = 'I';
        argOutFormattedData[11] = 'M';
        argOutFormattedData[12] = 'E';
    }
}
void GetFormattedAltitude(char argOutFormattedData[32])
{
    memset(&argOutFormattedData[0],0,sizeof(char)*32);

    if(gdmAltitude[0]!=(int)NULL)
    {
        bool decPassed = false;
        for(int i=0;i<8;i++)
        {
            if(decPassed==false)
            {
                if(i>0)
                {
                    if(gdmAltitude[i-1]=='.')
                    {
                        decPassed = true;
                    }
                }
                argOutFormattedData[i] = gdmAltitude[i];
            }
            else
            {
                argOutFormattedData[i] = 'M';
                break;
            }
        }
    }
    else
    {
        argOutFormattedData[0] = 'N';
        argOutFormattedData[1] = 'O';
        argOutFormattedData[2] = ' ';
        argOutFormattedData[3] = 'A';
        argOutFormattedData[4] = 'L';
        argOutFormattedData[5] = 'T';
    }
}
