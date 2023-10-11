/***************************************************************************************
 ***                                                                                 ***
 ***  Copyright (c) 2021, Lucid Vision Labs, Inc.                                    ***
 ***                                                                                 ***
 ***  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     ***
 ***  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       ***
 ***  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    ***
 ***  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         ***
 ***  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  ***
 ***  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  ***
 ***  SOFTWARE.                                                                      ***
 ***                                                                                 ***
 ***************************************************************************************/

#include "C_Acquisition.h"


#define TAB1_ "  "
#define TAB2_ "    "

// Image timeout
//    Timeout for grabbing images (in milliseconds). If no image is available at
//    the end of the timeout, an exception is thrown. The timeout is the maximum
//    time to wait for an image; however, getting an image will return as soon as
//    an image is available, not waiting the full extent of the timeout.
#define FILE_NAME "Images/C_Save/image"

#define FILE_EXT ".png"

#define IMAGE_TIMEOUT 10000

// number of images to grab
#define NUM_IMAGES 25

// maximum buffer length
#define MAX_BUF 512

// timeout for detecting camera devices (in milliseconds).
#define SYSTEM_TIMEOUT 100



///
// Cleanup
//
/*
void ShutDown ( ESContext *esContext )
{
   UserData *userData = esContext->userData;

   // Delete texture object
   glDeleteTextures ( 1, &userData->baseNewTexId );
   glDeleteTextures ( 1, &userData->baseOldTexId );
   glDeleteTextures ( 1, &userData->baseOldestTexId );
   glDeleteTextures ( 1, &userData->crosshairMapTexId );

   // Delete program object
   glDeleteProgram ( userData->programObject );
   glDeleteProgram ( userData->programObjectCrosshair );
   DestroySprites();
   RcOnExit();
}*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////











/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
void LcaImageReceivedCallback(int argInWidth,int argInHeight, acBuffer* argInImage)
{
    UpdateMaterialTexture(&(backgroundSprite->material),"s_baseNew",argInWidth,argInHeight, GL_RGB,argInImage);
}*/
/*
void HIKImageReceivedCallback(int argInWidth,int argInHeight, acBuffer* argInImage)
{
    UpdateMaterialTexture(&(backgroundSprite->material),"s_baseNew",argInWidth,argInHeight, GL_RGB,argInImage);
}*/
float testTimeout = 10.0f;


void Update(ESContext *esContext, float argInDeltaTime )
{
    //int newLeft = digitalRead(3);
    //int newUp = digitalRead(4);
    //int newDown = digitalRead(5);
    //int newRight = digitalRead(6);

    if(rcThisDeviceType==RC_HeadDevice)
    {
        /*if(rcThisDeviceType==rcPtuControlledBy)
        {
            if(commandPerformCalibration>0)
            {
                compassIsCalibrated = false;
            }
            CompassCalibrationRoutine();
        }*/
    }

    printf("\n Compass Data: %d  %d  %d \n",  cdmPitch, cdmRoll, cdmHeading);
}
/*
void OnKeyPress(ESContext *esContext,unsigned char argInKey, int pointX, int pointY)
{
    if(argInKey=='z'){printf("Zoom IN \n"); zoom*= zoomCoef;}
    if(argInKey=='x'){printf("Zoom OUT \n"); zoom/= zoomCoef; if(zoom<1.0f){zoom=1.0f;}}

    if(argInKey=='1'){printf("Battery Charged \n"); batteryPercentage += 0.0733f; if(batteryPercentage>1.0f){batteryPercentage=1.0f;}}
    if(argInKey=='2'){printf("Battery Discharged \n"); batteryPercentage -= 0.0613f; if(batteryPercentage<0.0f){batteryPercentage=0.0f;}}


    if(argInKey=='4'){printf("Rotate 5 CW \n"); compassDegrees += 5; if(compassDegrees>360){compassDegrees-=360;}}
    if(argInKey=='5'){printf("Rotate 5 CCW \n"); compassDegrees -= 5; if(compassDegrees<0.0f){compassDegrees+=360;}}

    if(argInKey=='7'){printf("Change Color \n"); hueVariant+= 1.0f; if(hueVariant>=3.0f){hueVariant=0.0f;}}
    if(argInKey=='8'){printf("Change Crosshair \n"); crosshairMaterialVariant+= 1.0f; if(crosshairMaterialVariant>=2.0f){crosshairMaterialVariant=0.0f;}}

    if(argInKey=='a')
    {PtuGoToAbsolutePosition(120000,15000);
        if(rcISendCommandData>0)
        {
            if(commandPerformCalibration==0)
            {
                commandPerformCalibration=1;
            }
            else
            {
                commandPerformCalibration = 0;
            }
        }
    }
    if(argInKey=='q'){PtuGoToAbsolutePosition(230000,-15000);}
}*/

/*
int PanSpeed()
{

    int newLeft = digitalRead(3);
    int newRight = digitalRead(6);
    int speed = 0;
    if(newLeft>0)
    {
        speed = -30000;
    }
    else if(newRight>0)
    {
        speed = 30000;
    }

    return speed;
}

int TiltSpeed()
{
    int newUp = digitalRead(4);
    int newDown = digitalRead(5);
    int speed = 0;
    if(newUp>0)
    {
        speed = 30000;
    }
    else if(newDown>0)
    {
        speed = -30000;
    }
    return speed;
}*/
/*
void InitRenderingDaycam( ESContext *esContextDaycam )
{
    esContextDaycam->userData = malloc ( sizeof ( UserData ) );

    //esCreateWindow ( esContext, "MultiTexture", SCREEN_SIZE_X, SCREEN_SIZE_Y, ES_WINDOW_RGB );
    esCreateRenderSurface( esContextDaycam, SCREEN_SIZE_X, SCREEN_SIZE_Y, ES_WINDOW_RGB );;
    esRegisterDrawFunc ( esContextDaycam, Draw );
    esRegisterShutdownFunc ( esContextDaycam, ShutDown );
    InitDraw ( esContextDaycam );
}*/
/*
void InitRendering( ESContext *esContext )
{
    esContext->userData = malloc ( sizeof ( UserData ) );

    //esCreateWindow ( esContext, "MultiTexture", SCREEN_SIZE_X, SCREEN_SIZE_Y, ES_WINDOW_RGB );
    esCreateRenderSurface( esContext, SCREEN_SIZE_X, SCREEN_SIZE_Y, ES_WINDOW_RGB );;
    esRegisterDrawFunc ( esContext, Draw );
    esRegisterShutdownFunc ( esContext, ShutDown );
    //esRegisterUpdateFunc(esContext, Update);
    InitDraw ( esContext );
}*/

int InitPeripherals ()
{
   setpriority(PRIO_PROCESS,0,-20);
   //wiringPiSetup();
   RcInit();
   InitializeSoftwareTimerManager();
   GpioWrapInitGpioWrapper();
   HikCurlWrapInitHikCurlWrapper();
   if(rcThisDeviceType==RC_HeadDevice)
   {
       ComInit(9600);
       MUXInit();
       InitScheduler();
       InitGPS();
       InitCompass();
       InitRangeFinder();
       InitPicMcu();
       InitButtonsHead();
       InitSensor();
   }
   else if(rcThisDeviceType==RC_Controller)
   {
        ComInit(9600);
        MUXInit();
        InitScheduler();
        InitPicMcu();
        InitButtonsController();
   }

   //if(rcThisDeviceType==RC_)
   //{
        LcaInitCamera();
        InitialiseLucidDraw();
   //}

   if(rcThisDeviceType==RC_Controller)
   {
        PtuInit();
   }

   IsnInit();
   InitPTUDataManager();
   InitRangefinderDataManager();
   InitCompassDataManager();
   InitGpsDataManager();
   InitPicDataManager();
   InitNetworkVariables();
   InitialiseDiagnostics();
   InitialiseCamerasController();
   InitCalibrationRoutine();

   return GL_TRUE;
}
