#include "Periph/LucidCameraDraw.h"
#include "Periph/HikCameraDraw.h"
#include "esUtil/Init.h"

bool runThermal = false;
bool runDaycamDraw = false;

ESContext esContextDaycam;
void* imageBufferPtr;

int imageWidth = 0;
int imageHeight = 0;

GLfloat ScreenSizeX = 1044.0f;
GLfloat ScreenSizeY = 788.0f;
GLfloat AspectRatio = 1.325f;


Sprite *backgroundSprite;
Sprite *crosshairSprite;
Sprite *crosshairSOSprite;
Sprite *compassSprite;
Sprite *degreesSprite;
Sprite *compassPointerSprite;
Sprite *tiltPointerSprite;
Sprite *batterySprite;


Text *txtButton0;
Text *txtButton1;
Text *txtButton2;
Text *txtButton3;
Text *txtButton4;

Text *txtCompass;
Text *txtCalcDir;
Text *txtTilt;
Text *txtZoom;
Text *txtGPSLat;
Text *txtCalcLat;
Text *txtGPSLong;
Text *txtCalcLong;
Text *txtGPSAlt;
Text *txtCurrentTime;
Text *txtDistance;
Text *txtMeasureTime;

bool showNoDayCamText = false;
Text *txtNoDayCam;

bool showNoThermalCamText = false;
Text *txtNoThermalCam;

Text *txtBrightness;

Text *txtDiagnostic1;
Text *txtDiagnostic2;



float color[] = {0.0f,1.0f,0.0f,1.0f};

float hueVariant = 0.0f;
float grayscaleIsOn  = 0.0f;

float brightness = 0.1f;
float brightness_D = 0.1f;
float brightness_T = 0.1f;
int lastBrightnessUpdateOn = 0;

void SetBrightness(float argInSetting)
{
    brightness_D = argInSetting;

    struct timeval currentTime;
    gettimeofday(&currentTime,NULL);
    lastBrightnessUpdateOn = currentTime.tv_sec;
}

float GetBrightness()
{
    return brightness_D;
}

void SetBrightnessThermal(float argInSetting)
{
    brightness_T = argInSetting;

    struct timeval currentTime;
    gettimeofday(&currentTime,NULL);
    lastBrightnessUpdateOn = currentTime.tv_sec;
}

float GetBrightnessThermal()
{
    return brightness_T;
}

void SetGrayscaleOn(bool argInSetting)
{
    if(argInSetting==true)
    {
        grayscaleIsOn = 1.0f;
    }
    else
    {
        grayscaleIsOn = 0.0f;
    }
}

bool GetGrayscaleIsOn()
{
    if(grayscaleIsOn>0.0f)
    {
        return true;
    }
    else
    {
        return false;
    }
}

#define LUCID_DRAW_MAX_SUBS 5
void (*OnLucidFrameReceivedCallback[LUCID_DRAW_MAX_SUBS])()=
{
   NULL,
   NULL,
   NULL,
   NULL,
   NULL
};

bool AddLucidFrameReceivedCallback(void* argInCallback)
{
    for(int i =0; i <LUCID_DRAW_MAX_SUBS;i++)
    {
        if(OnLucidFrameReceivedCallback[i] == NULL)
        {
           OnLucidFrameReceivedCallback[i] = argInCallback;
           return true;
        }
    }
    return false;
}


Material *backgroundMaterial;
Material *backgroundMaterialGrayscale;

Material *crosshairMaterial;
float crosshairColor[] = {1.0f,0.3f,0.3f,1.0f};

void SetCrosshairColor(float R, float G, float B, float A)
{
    crosshairColor[0] = R;
    crosshairColor[1] = G;
    crosshairColor[2] = B;
    crosshairColor[3] = A;
}

Material *crosshairScreenOffsetMaterial;
float crosshairScreenOffsetColor[] = {0.3f,1.0f,0.3f,1.0f};

void SetCrosshairSOPColor(float R, float G, float B, float A)
{
    crosshairScreenOffsetColor[0] = R;
    crosshairScreenOffsetColor[1] = G;
    crosshairScreenOffsetColor[2] = B;
    crosshairScreenOffsetColor[3] = A;
}

bool showCrosshairSOPreview = false;
int crosshairSOPDisplacementInPixelsX = 0;
int crosshairSOPDisplacementInPixelsY = 0;


float compassScaleBackgroundColor[] = {0.0f,0.0f,0.0f,0.5f};
float highlightedTextColor[] = {0.7f,1.0f,0.9f,0.6f};
float buttonTextBackgroundColor[] = {0.0f,0.0f,0.0f,0.0f};

//float zoomCoef = 1.33f;
float zoom = 1.0f;
float batteryPercentage = 0.68f;

int compassBarDegrees = 90;
float compassAdjSpeedDegSec = 40;
struct timeval tprevDrawFrame, tThisDrawFrame;
float deltaDrawtime;
int compassDegrees = 90;
int compassSubDegrees = 0;
float compassMoveTime =0;

int tiltBarDegrees = 90;
int tiltDegrees = 0;
int tiltSubDegrees = 0;
float tiltMoveTime =0;

float tiltScaleOffset=0.2f;


float crosshairDisplacementX = 0.0f;
float crosshairDisplacementY = 0.0f;

float GetCrosshairDisplacementX()
{
    return crosshairDisplacementX;
}

float GetCrosshairDisplacementY()
{
    return crosshairDisplacementY;
}

void DisplaceCrosshair(float argInDisplacementX, float argInDisplacementY)
{
    crosshairDisplacementX+=argInDisplacementX;
    crosshairDisplacementY+=argInDisplacementY;
}

void SetCrosshairDisplacementValue(float argInDisplacementX, float argInDisplacementY)
{
    crosshairDisplacementX = argInDisplacementX;
    crosshairDisplacementY = argInDisplacementY;
}


int GetCrosshairSOPDisplacementX()
{
    return crosshairSOPDisplacementInPixelsX;
}

int GetCrosshairSOPDisplacementY()
{
    return crosshairSOPDisplacementInPixelsY;
}

void DisplaceCrosshairSOP(int argInDisplacementX_InPixels, int argInDisplacementY_InPixels)
{
    crosshairSOPDisplacementInPixelsX+=argInDisplacementX_InPixels;
    crosshairSOPDisplacementInPixelsY+=argInDisplacementY_InPixels;
}

void SetCrosshairSOPDisplacementValue(int argInDisplacementX_InPixels, int argInDisplacementY_InPixels)
{
    crosshairSOPDisplacementInPixelsX = argInDisplacementX_InPixels;
    crosshairSOPDisplacementInPixelsY = argInDisplacementY_InPixels;
}

void ShowCrosshairSOP(bool argInShowScreenOffsetPreview)
{
    showCrosshairSOPreview = argInShowScreenOffsetPreview;
}


bool drawDaycamInitialised = false;

void SetZoomDayCam(float argInValue)
{
    zoom = argInValue;
}

void DaycamDrawStop()
{
    runDaycamDraw = false;
}

void DaycamDrawStart()
{
    runDaycamDraw = true;
}

bool DaycamDrawIsRunning()
{
    return (runDaycamDraw&&drawDaycamInitialised);
}

void ThermalDrawStop()
{
    runThermal = false;
}

void ThermalDrawStart()
{
    runThermal = true;
}

bool ThermalIsRunning()
{
    return (runThermal&&drawDaycamInitialised);
}

void InitSprites( ESContext *esContext )
{
    backgroundMaterial = InstantiateMaterial();
    GenerateShaderProgram(backgroundMaterial,vShaderStr,fShaderStr);
    AddMaterialParametterTextureFromFile(backgroundMaterial, "s_baseNew", esContextDaycam.platformData, "basemap.tga");
    AddMaterialParametter(backgroundMaterial,"grayscale",&grayscaleIsOn, MatParamType_1f);
    AddMaterialParametter(backgroundMaterial,"brightness",&brightness, MatParamType_1f);

    TextureData *backgroundTData = InstantiateTexture();

    Square *sq = InstantiateSquare();
    ScaleSquareX(sq,zoom);
    ScaleSquareY(sq,-(zoom));
    backgroundSprite = InstantiateSprite(*backgroundMaterial,*sq,*backgroundTData);

    /////
    crosshairMaterial = InstantiateMaterial();
    GenerateShaderProgram(crosshairMaterial,vShaderStr,fShaderCrosshair);
    SetMaterialAlphaBlending(crosshairMaterial,TRUE);
    AddMaterialParametterTextureFromFile(crosshairMaterial, "s_baseMap", esContextDaycam.platformData, "CrosshairRed_03.tga");
    AddMaterialParametter(crosshairMaterial,"color",&crosshairColor, MatParamType_4f);

    TextureData *crosshairTData = InstantiateTexture();

    Square *sqCr = InstantiateSquare();
    ScaleSquareX(sqCr,0.2f);
    ScaleSquareY(sqCr,0.2f);
    SetSquareAspectRatio(sqCr, AspectRatio);
    crosshairSprite = InstantiateSprite(*crosshairMaterial,*sqCr,*crosshairTData);


    crosshairScreenOffsetMaterial = InstantiateMaterial();
    GenerateShaderProgram(crosshairScreenOffsetMaterial,vShaderStr,fShaderCrosshair);
    SetMaterialAlphaBlending(crosshairScreenOffsetMaterial,TRUE);
    AddMaterialParametterTextureFromFile(crosshairScreenOffsetMaterial, "s_baseMap", esContextDaycam.platformData, "CrosshairRed_03.tga");
    AddMaterialParametter(crosshairScreenOffsetMaterial,"color",&crosshairScreenOffsetColor, MatParamType_4f);

    TextureData *crosshairSOTData = InstantiateTexture();

    Square *sqSOCr = InstantiateSquare();
    ScaleSquareX(sqSOCr,0.2f);
    ScaleSquareY(sqSOCr,0.2f);
    SetSquareAspectRatio(sqSOCr, AspectRatio);
    crosshairSOSprite = InstantiateSprite(*crosshairScreenOffsetMaterial,*sqSOCr,*crosshairSOTData);
    //////

    Material *compassScaleMaterial = InstantiateMaterial(); 
    GenerateShaderProgram(compassScaleMaterial,vShaderStr,fShaderCompassScale);
    SetMaterialAlphaBlending(compassScaleMaterial,TRUE);
    SetMaterialTextureWrap(compassScaleMaterial,TRUE);
    AddMaterialParametterTextureFromFile(compassScaleMaterial, "s_baseMap", esContextDaycam.platformData, "Compass_Bar_TGA.tga");
    AddMaterialParametter(compassScaleMaterial,"backgroundColor",&compassScaleBackgroundColor, MatParamType_4f);

    TextureData *compassScaleTData = InstantiateTexture();

    Square *sqCompass = InstantiateSquare();
    ScaleSquareX(sqCompass,1.30f);
    ScaleSquareY(sqCompass,0.050f);
    SetSquareAspectRatio(sqCompass, AspectRatio);
    SetSquarePosition(sqCompass, 0.0f, 0.93f);
    compassSprite = InstantiateSprite(*compassScaleMaterial,*sqCompass,*compassScaleTData);

    //////
    /// \brief compassScaleMaterial
    ///

    Material *degreesScaleMaterial = InstantiateMaterial();
    GenerateShaderProgram(degreesScaleMaterial,vShaderStr,fShaderTiltScale);
    SetMaterialAlphaBlending(degreesScaleMaterial,TRUE);
    SetMaterialTextureWrap(degreesScaleMaterial,TRUE);
    AddMaterialParametterTextureFromFile(degreesScaleMaterial, "s_baseMap", esContextDaycam.platformData, "Degree_Bar_TGA.tga");
    AddMaterialParametterTextureFromFile(degreesScaleMaterial, "s_mask", esContextDaycam.platformData, "Degree_Bar_Mask_TGA.tga");
    AddMaterialParametter(degreesScaleMaterial,"offsetY",&tiltScaleOffset, MatParamType_1f);
    AddMaterialParametter(degreesScaleMaterial,"backgroundColor",&compassScaleBackgroundColor, MatParamType_4f);

    TextureData *degreesScaleTData = InstantiateTexture();

    Square *sqDegrees = InstantiateSquare();
    ScaleSquareX(sqDegrees,0.045f);
    ScaleSquareY(sqDegrees,2.20f);
    SetSquareAspectRatio(sqDegrees, AspectRatio);
    SetSquarePosition(sqDegrees, 0.95f, 0.0f);
    degreesSprite = InstantiateSprite(*degreesScaleMaterial,*sqDegrees,*degreesScaleTData);

    //////////
    /// \brief compassPointerMaterial
    ///
    Material *compassPointerMaterial = InstantiateMaterial();
    GenerateShaderProgram(compassPointerMaterial,vShaderStr,fShaderCompassPointer);
    AddMaterialParametterTextureFromFile(compassPointerMaterial, "s_baseMap", esContextDaycam.platformData, "CursorPan.tga");

    TextureData *compassPointerTData = InstantiateTexture();

    Square *sqCompassPointer = InstantiateSquare();
    ScaleSquareX(sqCompassPointer,0.03f);
    ScaleSquareY(sqCompassPointer,0.05f);
    SetSquareAspectRatio(sqCompassPointer, AspectRatio);
    SetSquarePosition(sqCompassPointer, 0.0f, 0.90f);

    compassPointerSprite = InstantiateSprite(*compassPointerMaterial,*sqCompassPointer,*compassPointerTData);

    ////////////
    /// \brief compassPointerMaterial
    ///
    Material *tiltPointerMaterial = InstantiateMaterial();
    GenerateShaderProgram(tiltPointerMaterial,vShaderStr,fShaderCompassPointer);
    AddMaterialParametterTextureFromFile(tiltPointerMaterial, "s_baseMap", esContextDaycam.platformData, "CursorTilt.tga");

    TextureData *tiltPointerTData = InstantiateTexture();

    Square *sqTiltPointer = InstantiateSquare();
    ScaleSquareX(sqTiltPointer,0.05f);
    ScaleSquareY(sqTiltPointer,0.03f);
    SetSquareAspectRatio(sqTiltPointer, AspectRatio);
    SetSquarePosition(sqTiltPointer, 0.93f, 0.0f);

    tiltPointerSprite = InstantiateSprite(*tiltPointerMaterial,*sqTiltPointer,*tiltPointerTData);

    //

    Material *batteryMaterial = InstantiateMaterial();
    GenerateShaderProgram(batteryMaterial,vShaderStr,fShaderBattery);
    SetMaterialAlphaBlending(batteryMaterial,TRUE);
    AddMaterialParametterTextureFromFile(batteryMaterial, "s_baseMap", esContextDaycam.platformData, "Battery.tga");
    AddMaterialParametter(batteryMaterial,"backgroundColor",&compassScaleBackgroundColor, MatParamType_4f);
    AddMaterialParametter(batteryMaterial,"batteryPercentage",&batteryPercentage, MatParamType_1f);

    TextureData *batteryTData = InstantiateTexture();

    Square *sqBattery = InstantiateSquare();
    ScaleSquareX(sqBattery,0.10f);
    ScaleSquareY(sqBattery,0.05f);
    SetSquareAspectRatio(sqBattery, AspectRatio);
    SetSquarePosition(sqBattery, -0.90f, 0.8f);

    batterySprite = InstantiateSprite(*batteryMaterial,*sqBattery,*batteryTData);
//////////////////////////////////////
    Material *textMaterial = InstantiateMaterial();
    GenerateShaderProgram(textMaterial,vShaderStr,fShaderCompassScale);
    SetMaterialAlphaBlending(textMaterial,TRUE);
    AddMaterialParametterTextureFromFile(textMaterial, "s_baseMap", esContextDaycam.platformData, "Font_Quake_TGA_6.tga");
    AddMaterialParametter(textMaterial,"backgroundColor",&compassScaleBackgroundColor, MatParamType_4f);


    Material *highlightTextMaterial = InstantiateMaterial();
    GenerateShaderProgram(highlightTextMaterial,vShaderStr,fShaderHighlightedText);
    SetMaterialAlphaBlending(highlightTextMaterial,TRUE);
    AddMaterialParametterTextureFromFile(highlightTextMaterial, "s_baseMap", esContextDaycam.platformData, "Font_Quake_TGA_6.tga");
    AddMaterialParametter(highlightTextMaterial,"backgroundColor",&compassScaleBackgroundColor, MatParamType_4f);
    AddMaterialParametter(highlightTextMaterial,"fillColor",&highlightedTextColor, MatParamType_4f);

    txtCompass = InstantiateText(textMaterial,0.012f,0.025f);
    SetFontTextureGrid(txtCompass,16,16,FALSE,TRUE);
    SetTextString(txtCompass,"142@23'5\"");
    SetTextPosition(txtCompass,-0.0f,0.82f,TextAlignment_Centered);

    txtCalcDir = InstantiateText(highlightTextMaterial,0.012f,0.025f);
    SetFontTextureGrid(txtCalcDir,16,16,FALSE,TRUE);
    SetTextString(txtCalcDir,"142@23'5\"");
    SetTextPosition(txtCalcDir,-0.0f,0.76f,TextAlignment_Centered);

    txtTilt = InstantiateText(textMaterial,0.012f,0.025f);
    SetFontTextureGrid(txtTilt,16,16,FALSE,TRUE);
    SetTextString(txtTilt,"142@23'5\"");
    SetTextPosition(txtTilt,0.87f,0.0f,TextAlignment_Right);

    txtCurrentTime = InstantiateText(textMaterial,0.012f,0.025f);
    SetFontTextureGrid(txtCurrentTime,16,16,FALSE,TRUE);
    SetTextString(txtCurrentTime,"18:19:25");
    SetTextPosition(txtCurrentTime,-0.97f,-0.94f,TextAlignment_Left);

    txtGPSLat = InstantiateText(textMaterial,0.012f,0.025f);
    SetFontTextureGrid(txtGPSLat,16,16,FALSE,TRUE);
    SetTextString(txtGPSLat,"42.464177 | 24.136397 | 211");
    SetTextPosition(txtGPSLat,-0.40f,-0.94f,TextAlignment_Left);

    txtCalcLat = InstantiateText(highlightTextMaterial,0.012f,0.025f);
    SetFontTextureGrid(txtCalcLat,16,16,FALSE,TRUE);
    SetTextString(txtCalcLat,"42.464177 | 24.136397 | 211");
    SetTextPosition(txtCalcLat,-0.40f,-0.88f,TextAlignment_Left);

    txtGPSLong = InstantiateText(textMaterial,0.012f,0.025f);
    SetFontTextureGrid(txtGPSLong,16,16,FALSE,TRUE);
    SetTextString(txtGPSLong,"42.464177 | 24.136397 | 211");
    SetTextPosition(txtGPSLong,0.04f,-0.94f,TextAlignment_Left);

    txtCalcLong = InstantiateText(highlightTextMaterial,0.012f,0.025f);
    SetFontTextureGrid(txtCalcLong,16,16,FALSE,TRUE);
    SetTextString(txtCalcLong,"42.464177 | 24.136397 | 211");
    SetTextPosition(txtCalcLong,0.04f,-0.88f,TextAlignment_Left);

    txtGPSAlt= InstantiateText(textMaterial,0.012f,0.025f);
    SetFontTextureGrid(txtGPSAlt,16,16,FALSE,TRUE);
    SetTextString(txtGPSAlt,"4201M");
    SetTextPosition(txtGPSAlt,0.49f,-0.94f,TextAlignment_Left);

    txtMeasureTime = InstantiateText(textMaterial,0.012f,0.025f);
    SetFontTextureGrid(txtMeasureTime,16,16,FALSE,TRUE);
    SetTextString(txtMeasureTime,"--:--:--");
    SetTextPosition(txtMeasureTime,-0.97f,-0.10f,TextAlignment_Left);

    txtDistance = InstantiateText(textMaterial,0.012f,0.025f);
    SetFontTextureGrid(txtDistance,16,16,FALSE,TRUE);
    SetTextString(txtDistance,"----");
    SetTextPosition(txtDistance,-0.97f,-0.2f,TextAlignment_Left);

    txtNoDayCam = InstantiateText(textMaterial,0.020f,0.035f);
    SetFontTextureGrid(txtNoDayCam,16,16,FALSE,TRUE);
    SetTextString(txtNoDayCam,"NO DAY CAMERA");
    SetTextPosition(txtNoDayCam,0.0f,-0.3f,TextAlignment_Centered);

    txtNoThermalCam = InstantiateText(textMaterial,0.020f,0.035f);
    SetFontTextureGrid(txtNoThermalCam,16,16,FALSE,TRUE);
    SetTextString(txtNoThermalCam,"NO THERMAL CAMERA");
    SetTextPosition(txtNoThermalCam,0.0f,-0.3f,TextAlignment_Centered);

    txtBrightness = InstantiateText(textMaterial,0.015f,0.025f);
    SetFontTextureGrid(txtBrightness,16,16,FALSE,TRUE);
    SetTextString(txtBrightness,"BRIGHTNESS:");
    SetTextPosition(txtBrightness,-0.97f,-0.7f,TextAlignment_Left);

    txtDiagnostic1 = InstantiateText(textMaterial,0.015f,0.025f);
    SetFontTextureGrid(txtDiagnostic1,16,16,FALSE,TRUE);
    SetTextString(txtDiagnostic1,"DIAG:");
    SetTextPosition(txtDiagnostic1,-0.0f,-0.7f,TextAlignment_Centered);

    txtDiagnostic2 = InstantiateText(textMaterial,0.015f,0.025f);
    SetFontTextureGrid(txtDiagnostic2,16,16,FALSE,TRUE);
    SetTextString(txtDiagnostic2,"DRAW:");
    SetTextPosition(txtDiagnostic2,-0.0f,-0.6f,TextAlignment_Centered);


    drawDaycamInitialised = true;
}

void DestroySprites()
{
    DestroySprite(backgroundSprite);
    DestroySprite(crosshairSprite);
    DestroySprite(crosshairSOSprite);
    DestroySprite(compassSprite);
    DestroySprite(compassPointerSprite);
    DestroySprite(tiltPointerSprite);
    DestroySprite(batterySprite);
    DestroySprite(degreesSprite);
}


int InitDraw ( ESContext *esContext )
{
   InitSprites(&esContextDaycam);
   glClearColor ( 0.0f, 1.0f, 1.0f, 0.0f );
   return TRUE;
}

void DrawViewPort ( ESContext *esContext )
{
    glViewport ( 0, 0, esContextDaycam.width, esContextDaycam.height );
    glClear ( GL_COLOR_BUFFER_BIT );
}

void Draw ( ESContext *esContext )
{
    if(DaycamDrawIsRunning()==true)
    {
        brightness = brightness_D;
    }
    else if (ThermalIsRunning()==true)
    {
        brightness = brightness_T;
    }

    if(drawDaycamInitialised == true)
    {

        ScaleSquareX(&(backgroundSprite->square),zoom);
        ScaleSquareY(&(backgroundSprite->square),-(zoom));

        char compassAll[15]="";
        compassDegrees = (int)cdmHeading/(int)1000;
        compassSubDegrees = (int)cdmHeading%(int)1000;
        sprintf(compassAll, "%d,%d",compassDegrees,compassSubDegrees);
        SetTextString(txtCompass,compassAll);

        if(compassDegrees==compassBarDegrees)
        {
            compassMoveTime = 0;
        }
        else
        {
            compassMoveTime+=deltaDrawtime;
        }

        gettimeofday(&tThisDrawFrame, NULL);
        deltaDrawtime = (float)(tThisDrawFrame.tv_sec - tprevDrawFrame.tv_sec + (tThisDrawFrame.tv_usec - tprevDrawFrame.tv_usec) * 1e-6);
        tprevDrawFrame = tThisDrawFrame;

        float maxDegThisFrame = compassAdjSpeedDegSec*(1.0f+(compassMoveTime*4.0f))*deltaDrawtime;

        float totalOffset = (float)compassDegrees-(float)compassBarDegrees;
        if(fabsf(totalOffset)>180)
        {
            if(totalOffset>0)
            {
                totalOffset = (float)compassDegrees-((float)compassBarDegrees+360.0f);
            }
            else
            {
                totalOffset = (float)compassDegrees-((float)compassBarDegrees-360.0f);
            }
        }
        float compassOfsset = totalOffset;

        if( fabsf(compassOfsset)<maxDegThisFrame)
        {
            compassBarDegrees = compassDegrees;
        }
        else
        {
            if(compassOfsset<0)
            {
                compassBarDegrees-=maxDegThisFrame;
            }
            else
            {
                compassBarDegrees+=maxDegThisFrame;
            }
        }
        SetTextureOffset(&compassSprite->textureData, ((float)(((float)compassBarDegrees)-360.0f)/360.0f),0.0f);


        char tiltAll[15]="";
        tiltDegrees = (int)cdmPitch/(int)1000;
        tiltSubDegrees = (int)cdmPitch%(int)1000;
        if(tiltSubDegrees<0){tiltSubDegrees=-tiltSubDegrees;}
        sprintf(tiltAll, "%d,%d",tiltDegrees,tiltSubDegrees);
        SetTextString(txtTilt,tiltAll);

        if(tiltDegrees==tiltBarDegrees)
        {
            tiltMoveTime = 0;
        }
        else
        {
            tiltMoveTime+=deltaDrawtime;
        }

        float maxDegTiltThisFrame = compassAdjSpeedDegSec*(1.0f+(tiltMoveTime*4.0f))*deltaDrawtime;

        float totalTOffset = (float)tiltDegrees-(float)tiltBarDegrees;
        if( fabsf(totalTOffset)<maxDegTiltThisFrame)
        {
            tiltBarDegrees = tiltDegrees;
        }
        else
        {
            if(totalTOffset<0)
            {
                tiltBarDegrees-=maxDegTiltThisFrame;
            }
            else
            {
                tiltBarDegrees+=maxDegTiltThisFrame;
            }
        }
        tiltScaleOffset = ((float)tiltBarDegrees)/240.0f;

        /////////////
        if(DaycamDrawIsRunning()==true)
        {
            float sopDisplX = (((float)crosshairSOPDisplacementInPixelsX)/((float)rcLucidCameraResX/2))*zoom;
            float sopDisplY = (((float)crosshairSOPDisplacementInPixelsY)/((float)rcLucidCameraResY/2))*zoom;
            SetSquarePosition(&(crosshairSOSprite->square), sopDisplX,sopDisplY );
            SetSquarePosition(&(crosshairSprite->square), sopDisplX+(crosshairDisplacementX*zoom), sopDisplY+crosshairDisplacementY*zoom);
        }
        else if(ThermalIsRunning()==true)
        {
            SetSquarePosition(&(crosshairSprite->square), 0, 0);
        }
        ////////////////////////////////////////////

        if(rdmLastMeasurementTimeS!=0)
        {
            time_t lastMeasureT = (time_t)rdmLastMeasurementTimeS;
            char finalLRFMTimeStr[32]="";
            strftime(finalLRFMTimeStr, sizeof finalLRFMTimeStr, "%H:%M:%S",localtime(&lastMeasureT));
            SetTextString(txtMeasureTime,finalLRFMTimeStr);
        }
        //        txtMeasureTime

        char finalLRFStr[32] = "";
        sprintf(finalLRFStr, "%.1f",rdmTarget1);
        SetTextString(txtDistance,finalLRFStr);

        char finalGPSLatstr[32] = "";
        GetFormattedLat(finalGPSLatstr);
        SetTextString(txtGPSLat,finalGPSLatstr);

        char finalGPSLongstr[32] = "";
        GetFormattedLong(finalGPSLongstr);
        SetTextString(txtGPSLong,finalGPSLongstr);

        char finalDTSstr[32];
        GetFormattedDateTime(finalDTSstr);
        SetTextString(txtCurrentTime,finalDTSstr);

        char finalAltstr[32];
        GetFormattedAltitude(finalAltstr);
        SetTextString(txtGPSAlt,finalAltstr);

        int batValue = GetLastBatteryMeasurement();
        if(batValue<rcADCBatteryMin){batteryPercentage=0.0f;}
        else if(batValue>rcADCBatteryMax){batteryPercentage=1.0f;}
        else
        {
            int adcRange = rcADCBatteryMax-rcADCBatteryMin;
            int normVal = batValue-rcADCBatteryMin;

            batteryPercentage = ((float)normVal)/((float)adcRange);
        }

        DrawViewPort(&esContextDaycam);
        DrawSprite(backgroundSprite);
        DrawSprite(crosshairSprite);
        if(showCrosshairSOPreview==true)
        {
            DrawSprite(crosshairSOSprite);
        }
        DrawSprite(compassSprite);
        DrawSprite(degreesSprite);
        DrawSprite(compassPointerSprite);
        DrawSprite(tiltPointerSprite);
        DrawSprite(batterySprite);

        DrawText(txtCompass);
        DrawText(txtTilt);
        if(updateCoordinates==true)
        {
            char finalCalcLatstr[32] = "";
            sprintf(finalCalcLatstr, "%f",calculatedLat);
            SetTextString(txtCalcLat,finalCalcLatstr);

            DrawText(txtCalcLat);

            char finalCalcLongstr[32] = "";
            sprintf(finalCalcLongstr, "%f",calculatedLong);
            SetTextString(txtCalcLong,finalCalcLongstr);
            DrawText(txtCalcLong);
        }

        if(updateDirAngle==true)
        {
            char finalCalcDirstr[32] = "";
            sprintf(finalCalcDirstr, "%f",calculatedDirAngle);
            SetTextString(txtCalcDir,finalCalcDirstr);
            DrawText(txtCalcDir);
        }

        DrawText(txtGPSLat);
        DrawText(txtGPSLong);
        DrawText(txtGPSAlt);
        DrawText(txtCurrentTime);
        DrawText(txtDistance);

        DrawText(txtMeasureTime);

        if(DaycamDrawIsRunning()==true)
        {
            if(showNoDayCamText==true)
            {
                int camState = GetCamerasControllerState();
                if(camState==0)
                {
                    if(rcThisDeviceType!=RC_HeadDevice)
                    {
                        SetTextString(txtNoDayCam,"DAYCAM NOT CONNECTED");
                    }
                    else
                    {
                        SetTextString(txtNoDayCam,"DAYCAM BUSY");
                    }
                }
                else
                {
                    int cdState = GetDeviceDiagState(DEV_LUCID_CAM);
                    if(cdState <= 2)
                    {
                        SetTextString(txtNoDayCam,"TURNING DAYCAM ON");
                    }
                    else
                    {
                        SetTextString(txtNoDayCam,"DAYCAM ERROR");
                    }
                }
                DrawText(txtNoDayCam);
            }
        }
        else if(ThermalIsRunning()==true)
        {
            if(showNoThermalCamText==true)
            {
                int camStateT = GetCamerasControllerState();
                if(camStateT==0)
                {
                    if(rcThisDeviceType!=RC_HeadDevice)
                    {
                        SetTextString(txtNoThermalCam,"THERMALCAM NOT CONNECTED");
                    }
                    else
                    {
                        SetTextString(txtNoThermalCam,"THERMALCAM BUSY");
                    }
                }
                else
                {
                    int cdState = GetDeviceDiagState(DEV_HIK_CAM);
                    if(cdState <= 2)
                    {
                        SetTextString(txtNoThermalCam,"TURNING THERMALCAM ON");
                    }
                    else
                    {
                        SetTextString(txtNoThermalCam,"THERMALCAM ERROR");
                    }
                }
                DrawText(txtNoThermalCam);
            }
        }

        struct timeval currentTime;
        gettimeofday(&currentTime,NULL);
        if(lastBrightnessUpdateOn+5>currentTime.tv_sec)
        {
            char brightnessAll[16]="";
            sprintf(brightnessAll, "BRIGHTNESS:%d%%",((int)(brightness*100.0f)));
            SetTextString(txtBrightness,brightnessAll);
            DrawText(txtBrightness);
        }

        if(rcShowDiagnosticBars==1)
        {
            char finalDiagstr[32] = "";
            enum DIAG_STATE gpsState = GetDeviceDiagState(DEV_GPS);
            enum DIAG_STATE compassState = GetDeviceDiagState(DEV_COMPASS);
            enum DIAG_STATE rangefinderState = GetDeviceDiagState(DEV_RANGEFINDER);
            enum DIAG_STATE mbHeadState = GetDeviceDiagState(DEV_MB_HEAD);
            enum DIAG_STATE mbControllerState = GetDeviceDiagState(DEV_MB_CONTROLLER);
            enum DIAG_STATE ptuState = GetDeviceDiagState(DEV_PTU);
            enum DIAG_STATE lucidState = GetDeviceDiagState(DEV_LUCID_CAM);
            enum DIAG_STATE hikState = GetDeviceDiagState(DEV_HIK_CAM);

            sprintf(finalDiagstr, "G:%d C:%d R:%d B:%d D:%d P:%d L:%d H:%d",gpsState,compassState,rangefinderState,mbHeadState,mbControllerState,ptuState,lucidState,hikState);
            SetTextString(txtDiagnostic1,finalDiagstr);
            DrawText(txtDiagnostic1);

            char finalDiagstr2[32] = "";
            sprintf(finalDiagstr2, "LF:%f DF:%f",frameDeltatime,deltaDrawtime);
            SetTextString(txtDiagnostic2,finalDiagstr2);
            DrawText(txtDiagnostic2);
        }

    }
}

void ShutDownDrawing ( ESContext *esContext )
{
   UserData *userData = esContextDaycam.userData;

   // Delete texture object
   /*glDeleteTextures ( 1, &userData->baseNewTexId );
   glDeleteTextures ( 1, &userData->baseOldTexId );
   glDeleteTextures ( 1, &userData->baseOldestTexId );
   glDeleteTextures ( 1, &userData->crosshairMapTexId );*/

   // Delete program object
   /*glDeleteProgram ( userData->programObject );
   glDeleteProgram ( userData->programObjectCrosshair );*/
   DestroySprites();
   RcOnExit();
}

int inputWidth = 0;
int inputHeight = 0;
acBuffer* inputImage;
int lucidLastReceivedFrameOn = 0;

void DrawAndReadImage()
{
    char ImageBuffer[esContextDaycam.width*esContextDaycam.height*4];
    imageBufferPtr = &ImageBuffer[0];
    imageWidth = esContextDaycam.width;
    imageHeight = esContextDaycam.height;

    Draw(&esContextDaycam);

    eglSwapBuffers(esContextDaycam.eglDisplay, esContextDaycam.eglSurface);
    glReadPixels(0,0,esContextDaycam.width, esContextDaycam.height,GL_RGBA,GL_UNSIGNED_BYTE,&ImageBuffer);
}

void DrawDay()
{
    if(drawDaycamInitialised==true)
    {
        if(runDaycamDraw==true)
        {
            eglMakeCurrent ( esContextDaycam.eglDisplay, esContextDaycam.eglSurface,esContextDaycam.eglSurface, esContextDaycam.eglContext );
            struct timeval currentTime;
            gettimeofday(&currentTime,NULL);
            pthread_mutex_lock(&lucidCameraMut);
            if((lucidLastReceivedFrameOn+2)>currentTime.tv_sec)
            {
                UpdateMaterialTexture(&(backgroundSprite->material),"s_baseNew",inputWidth,inputHeight, GL_RGB,inputImage);
                showNoDayCamText = false;
            }
            else
            {
                UpdateMaterialTexture(&(backgroundSprite->material),"s_baseNew",0,0, GL_RGBA,NULL);
                showNoDayCamText = true;
            }
            DrawAndReadImage();
            pthread_mutex_unlock(&lucidCameraMut);
        }
    }
}

void NightImageReceivedCallback(int arginWidth, int arginHeight, void* argInImage)
{
    if(ThermalIsRunning()==true)
    {
        if((arginWidth!=0)&&(arginHeight!=0))
        {
            showNoThermalCamText = false;
        }
        else
        {
            showNoThermalCamText = true;
        }
        eglMakeCurrent ( esContextDaycam.eglDisplay, esContextDaycam.eglSurface,esContextDaycam.eglSurface, esContextDaycam.eglContext );
        UpdateMaterialTexture(&(backgroundSprite->material),"s_baseNew",arginWidth,arginHeight, GL_RGBA,argInImage);
        DrawAndReadImage();
    }
}

void LcaImageReceivedCallback(int argInWidth,int argInHeight, acBuffer* argInImage)
{
    if(drawDaycamInitialised==true)
    {
        if(runDaycamDraw==true)
        { 
            inputWidth = argInWidth;
            inputHeight = argInHeight;
            inputImage = argInImage;
        }
        struct timeval currentTime;
        gettimeofday(&currentTime,NULL);
        lucidLastReceivedFrameOn = currentTime.tv_sec;
        for(int i =0; i <LUCID_DRAW_MAX_SUBS;i++)
        {
            if(OnLucidFrameReceivedCallback[i] != NULL)
            {
               OnLucidFrameReceivedCallback[i]();
            }
        }
    }
}

void* GetLucidImageBuffer()
{
    return imageBufferPtr;
}

int GetDaycamImageWidth()
{
    return imageWidth;
}

int GetDaycamImageHeight()
{
    return imageHeight;
} 

void InitRenderingDaycam()
{
    esContextDaycam.userData = malloc ( sizeof ( UserData ) );

    //esCreateWindow ( esContext, "MultiTexture", SCREEN_SIZE_X, SCREEN_SIZE_Y, ES_WINDOW_RGB );
    esCreateRenderSurface( &esContextDaycam, SCREEN_SIZE_X, SCREEN_SIZE_Y, ES_WINDOW_RGB );
    InitDraw ( &esContextDaycam );
}

int InitialiseLucidDraw()
{
    memset ( &esContextDaycam, 0, sizeof( esContextDaycam ) );
    InitRenderingDaycam();
    LcaAddOnImageReceived(LcaImageReceivedCallback);

    return 0;
}


void Shutdown()
{
    ShutDownDrawing(&esContextDaycam);

    if ( esContextDaycam.userData != NULL )
       free ( esContextDaycam.userData );
}
