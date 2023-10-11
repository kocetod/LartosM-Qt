#include "Periph/HikCameraDraw.h"

bool runThermal = false;

ESContext esContextThermalcam;
void* imageBufferPtr;

int imageWidth_t = 0;
int imageHeight_t = 0;

GLfloat ScreenSizeX_t = 1044.0f;
GLfloat ScreenSizeY_t = 788.0f;
GLfloat AspectRatio_t = 1.325f;


Sprite *backgroundSprite_t;
Sprite *crosshairSprite_t;
Sprite *compassSprite_t;
Sprite *compassPointerSprite_t;
Sprite *batterySprite_t;


Text *txtButton0_t;
Text *txtButton1_t;
Text *txtButton2_t;
Text *txtButton3_t;
Text *txtButton4_t;

Text *txtCompass_t;
Text *txtZoom_t;
Text *txtGPS_t;
Text *txtCurrentTime_t;

Text *txtDistance_t;
Text *txtDistance_1t;
Text *txtDistance_2t;

Text *txtMeasureTime_t;
Text *txtMode_t;

float color_t[] = {0.0f,1.0f,0.0f,1.0f};

float hueVariant_t = 0.0f;
int crosshairMaterialVariant_t = 1;
Material *crosshairMaterial1_t;
Material *crosshairMaterial2_t;

float compassScaleBackgroundColor_t[] = {0.0f,0.0f,0.0f,0.65f};
float buttonTextBackgroundColor_t[] = {0.0f,0.0f,0.0f,0.0f};

float zoomCoef_t = 1.33f;
float zoom_t = 1.0f;
float batteryPercentage_t = 0.68f;
int compassDegrees_t = 130;

bool drawThermalCamInitialised = false;

void SetZoomThermalCam(float argInValue)
{
    zoom_t = argInValue;
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
    return (runThermal&&drawThermalCamInitialised);
}

float grayscaleIsOn_T = 0.0f;
float brightness_T = 0.1f;

void SetBrightnessThermal(float argInSetting)
{
    brightness_T = argInSetting;
}

float GetBrightnessThermal()
{
    return brightness_T;
}

Material *backgroundMaterial_t;
void InitSpritesThermal( ESContext *esContext )
{

    backgroundMaterial_t = InstantiateMaterial();
    GenerateShaderProgram(backgroundMaterial_t,vShaderStr,fShaderStrGrayscale);
    AddMaterialParametterTextureFromFile(backgroundMaterial_t, "s_baseNew", esContextThermalcam.platformData, "basemap.tga");
    AddMaterialParametter(backgroundMaterial_t,"grayscale",&grayscaleIsOn_T, MatParamType_1f);
    AddMaterialParametter(backgroundMaterial_t,"brightness",&brightness_T, MatParamType_1f);

    TextureData *backgroundTData = InstantiateTexture();

    Square *sq = InstantiateSquare();
    ScaleSquareX(sq,zoom_t);
    ScaleSquareY(sq,-zoom_t);
    backgroundSprite_t = InstantiateSprite(*backgroundMaterial_t,*sq,*backgroundTData);


    /*crosshairMaterial1_t = InstantiateMaterial();
    GenerateShaderProgram(crosshairMaterial1_t,vShaderStr,fShaderCrosshair);
    SetMaterialAlphaBlending(crosshairMaterial1_t,TRUE);
    AddMaterialParametterTextureFromFile(crosshairMaterial1_t, "s_baseMap", esContextThermalcam.platformData, "CrosshairRed.tga");
    AddMaterialParametter(crosshairMaterial1_t,"hueVariant",&hueVariant_t, MatParamType_1f);*/

    crosshairMaterial2_t = InstantiateMaterial();
    GenerateShaderProgram(crosshairMaterial2_t,vShaderStr,fShaderCrosshair);
    SetMaterialAlphaBlending(crosshairMaterial2_t,TRUE);
    AddMaterialParametterTextureFromFile(crosshairMaterial2_t, "s_baseMap", esContextThermalcam.platformData, "CrosshairRed_03.tga");
    AddMaterialParametter(crosshairMaterial2_t,"hueVariant",&hueVariant_t, MatParamType_1f);

    TextureData *crosshairTData = InstantiateTexture();

    Square *sqCr = InstantiateSquare();
    ScaleSquareX(sqCr,0.14f);
    ScaleSquareY(sqCr,0.14f);
    SetSquareAspectRatio(sqCr, AspectRatio_t);
    crosshairSprite_t = InstantiateSprite(*crosshairMaterial2_t,*sqCr,*crosshairTData);

    //

    Material *compassScaleMaterial = InstantiateMaterial();
    GenerateShaderProgram(compassScaleMaterial,vShaderStr,fShaderCompassScale);
    SetMaterialAlphaBlending(compassScaleMaterial,TRUE);
    SetMaterialTextureWrap(compassScaleMaterial,TRUE);
    AddMaterialParametterTextureFromFile(compassScaleMaterial, "s_baseMap", esContextThermalcam.platformData, "Compass_Bar_TGA.tga");
    AddMaterialParametter(compassScaleMaterial,"backgroundColor",&compassScaleBackgroundColor_t, MatParamType_4f);

    TextureData *compassScaleTData = InstantiateTexture();

    Square *sqCompass = InstantiateSquare();
    ScaleSquareX(sqCompass,1.30f);
    ScaleSquareY(sqCompass,0.045f);
    SetSquareAspectRatio(sqCompass, AspectRatio_t);
    SetSquarePosition(sqCompass, 0.0f, 0.94f);
    compassSprite_t = InstantiateSprite(*compassScaleMaterial,*sqCompass,*compassScaleTData);

    //

    Material *compassPointerMaterial = InstantiateMaterial();
    GenerateShaderProgram(compassPointerMaterial,vShaderStr,fShaderCompassPointer);
    AddMaterialParametterTextureFromFile(compassPointerMaterial, "s_baseMap", esContextThermalcam.platformData, "CompassPointer_.tga");

    TextureData *compassPointerTData = InstantiateTexture();

    Square *sqCompassPointer = InstantiateSquare();
    ScaleSquareX(sqCompassPointer,0.03f);
    ScaleSquareY(sqCompassPointer,0.03f);
    SetSquareAspectRatio(sqCompassPointer, AspectRatio_t);
    SetSquarePosition(sqCompassPointer, 0.0f, 0.90f);

    compassPointerSprite_t = InstantiateSprite(*compassPointerMaterial,*sqCompassPointer,*compassPointerTData);

    //

    Material *batteryMaterial = InstantiateMaterial();
    GenerateShaderProgram(batteryMaterial,vShaderStr,fShaderBattery);
    SetMaterialAlphaBlending(batteryMaterial,TRUE);
    AddMaterialParametterTextureFromFile(batteryMaterial, "s_baseMap", esContextThermalcam.platformData, "Battery.tga");
    AddMaterialParametter(batteryMaterial,"backgroundColor",&compassScaleBackgroundColor_t, MatParamType_4f);
    AddMaterialParametter(batteryMaterial,"batteryPercentage",&batteryPercentage_t, MatParamType_1f);

    TextureData *batteryTData = InstantiateTexture();

    Square *sqBattery = InstantiateSquare();
    ScaleSquareX(sqBattery,0.10f);
    ScaleSquareY(sqBattery,0.05f);
    SetSquareAspectRatio(sqBattery, AspectRatio_t);
    SetSquarePosition(sqBattery, 0.90f, 0.8f);

    batterySprite_t = InstantiateSprite(*batteryMaterial,*sqBattery,*batteryTData);

    Material *textMaterial = InstantiateMaterial();
    GenerateShaderProgram(textMaterial,vShaderStr,fShaderCompassScale);
    SetMaterialAlphaBlending(textMaterial,TRUE);
    AddMaterialParametterTextureFromFile(textMaterial, "s_baseMap", esContextThermalcam.platformData, "Font_Quake_TGA_6.tga");
    AddMaterialParametter(textMaterial,"backgroundColor",&compassScaleBackgroundColor_t, MatParamType_4f);

    txtCompass_t = InstantiateText(textMaterial,0.032f,0.05f);
    SetFontTextureGrid(txtCompass_t,16,16,FALSE,TRUE);
    SetTextString(txtCompass_t,"142@23'5\"");
    SetTextPosition(txtCompass_t,-0.0f,0.82f,TextAlignment_Centered);

    txtGPS_t = InstantiateText(textMaterial,0.02f,0.03f);
    SetFontTextureGrid(txtGPS_t,16,16,FALSE,TRUE);
    SetTextString(txtGPS_t,"42.464177 | 24.136397 | 211");
    SetTextPosition(txtGPS_t,-0.97f,-0.94f,TextAlignment_Left);

    txtCurrentTime_t = InstantiateText(textMaterial,0.02f,0.03f);
    SetFontTextureGrid(txtCurrentTime_t,16,16,FALSE,TRUE);
    SetTextString(txtCurrentTime_t,"18:19:25");
    SetTextPosition(txtCurrentTime_t,-0.97f,-0.87f,TextAlignment_Left);


    txtMeasureTime_t = InstantiateText(textMaterial,0.02f,0.03f);
    SetFontTextureGrid(txtMeasureTime_t,16,16,FALSE,TRUE);
    SetTextString(txtMeasureTime_t,"18:19:23");
    SetTextPosition(txtMeasureTime_t,-0.97f,-0.10f,TextAlignment_Left);
    drawThermalCamInitialised = true;

    txtDistance_t = InstantiateText(textMaterial,0.02f,0.03f);
    SetFontTextureGrid(txtDistance_t,16,16,FALSE,TRUE);
    SetTextString(txtDistance_t,"20 492M");
    SetTextPosition(txtDistance_t,-0.97f,-0.2f,TextAlignment_Left);

    txtDistance_1t = InstantiateText(textMaterial,0.02f,0.03f);
    SetFontTextureGrid(txtDistance_1t,16,16,FALSE,TRUE);
    SetTextString(txtDistance_1t,"14 201M");
    SetTextPosition(txtDistance_1t,-0.97f,-0.27f,TextAlignment_Left);

    txtDistance_2t = InstantiateText(textMaterial,0.02f,0.03f);
    SetFontTextureGrid(txtDistance_2t,16,16,FALSE,TRUE);
    SetTextString(txtDistance_2t," 4 885M");
    SetTextPosition(txtDistance_2t,-0.97f,-0.34f,TextAlignment_Left);
}

void DestroySpritesThermal()
{
    DestroySprite(backgroundSprite_t);
    DestroySprite(crosshairSprite_t);
    DestroySprite(compassSprite_t);
    DestroySprite(compassPointerSprite_t);
    DestroySprite(batterySprite_t);
}


int InitThermalDraw ( ESContext *esContext )
{
   InitSpritesThermal(esContext);
   glClearColor ( 0.0f, 1.0f, 1.0f, 0.0f );
   return TRUE;
}

void DrawViewPortThermal ( ESContext *esContext )
{
    glViewport ( 0, 0, esContext->width, esContext->height );
    glClear ( GL_COLOR_BUFFER_BIT );
}

void DrawThermal ( ESContext *esContext )
{
    ScaleSquareX(&(backgroundSprite_t->square),zoom_t);
    ScaleSquareY(&(backgroundSprite_t->square),-(zoom_t));

    /*char zoomX[10] = "x";
    char zoomTxt[5];
    gcvt(zoom_t,3,zoomTxt);
    strcat(zoomX,zoomTxt);
    SetTextString(txtZoom_t,zoomX);*/

    char compassAll[15]="";
    char compassD[3] = "";
    sprintf(compassD, "%d",compassDegrees_t);
    strcat(compassAll,compassD);
    strcat(compassAll,"*23'5\"");
    SetTextString(txtCompass_t,compassAll);


    SetTextureOffset(&compassSprite_t->textureData, ((float)(((float)compassDegrees_t)-360.0f)/360.0f),0.0f);

    if(crosshairMaterialVariant_t==0)
    {
        crosshairSprite_t->material=*crosshairMaterial1_t;
    }
    else
    {
        crosshairSprite_t->material=*crosshairMaterial2_t;
    }

    /*
    char finalGPSstr[32];
    GetFormattedValue(finalGPSstr);
    SetTextString(txtGPS_t,finalGPSstr);
    char finalDTSstr[32];
    GetFormattedDateTime(finalDTSstr);
    SetTextString(txtCurrentTime_t,finalDTSstr);*/

    DrawViewPortThermal(&esContextThermalcam);
    DrawSprite(backgroundSprite_t);
    DrawSprite(crosshairSprite_t);
    DrawSprite(compassSprite_t);
    DrawSprite(compassPointerSprite_t);
    DrawSprite(batterySprite_t);

    /*
    DrawSprite(buttonSprite0_t);
    DrawSprite(buttonSprite1_t);
    DrawSprite(buttonSprite2_t);
    DrawSprite(buttonSprite3_t);
    DrawSprite(buttonSprite4_t);

    DrawText(txtButton0_t);
    DrawText(txtButton1_t);
    DrawText(txtButton2_t);
    DrawText(txtButton3_t);
    DrawText(txtButton4_t);
*/

    DrawText(txtCompass_t);
    //DrawText(txtZoom_t);
    //DrawText(txtMode_t);
    DrawText(txtGPS_t);
    DrawText(txtCurrentTime_t);
    DrawText(txtDistance_t);
    DrawText(txtDistance_1t);
    DrawText(txtDistance_2t);
    DrawText(txtMeasureTime_t);
}

char ImageBuffer[SCREEN_SIZE_X*SCREEN_SIZE_Y*4];

void* GetHikImageBuffer()
{
    return &ImageBuffer;
}

int GetThermalImageWidth()
{
    return esContextThermalcam.width;
}

int GetThermalImageHeight()
{
    return esContextThermalcam.height;
}
int frame =0;
void ThermalImageReceivedCallback(int arginWidth, int arginHeight, void* argInImage)
{
    frame++;
    if(runThermal==true)
    {
        if(drawThermalCamInitialised==true)
        {
            eglMakeCurrent ( esContextThermalcam.eglDisplay, esContextThermalcam.eglSurface,esContextThermalcam.eglSurface, esContextThermalcam.eglContext );

            //if(i==10)
            //{
            //    SaveSimpleImage(argInImage,arginWidth, arginHeight,32,  "Test1BeforeRender.png");
            //}

            UpdateMaterialTexture(&(backgroundSprite_t->material),"s_baseNew",arginWidth,arginHeight, GL_RGBA,argInImage);
            if (esContextThermalcam.drawFunc != NULL)
            {esContextThermalcam.drawFunc(&esContextThermalcam);}

            eglSwapBuffers(esContextThermalcam.eglDisplay, esContextThermalcam.eglSurface);
            glReadPixels(0,0,esContextThermalcam.width, esContextThermalcam.height,GL_RGBA,GL_UNSIGNED_BYTE,&ImageBuffer);

            //if(i==10)
            //{
            //    SaveSimpleImage(ImageBuffer,esContextThermalcam.width, esContextThermalcam.height,32,  "Test1.png");
            //}
        }
    }
}

void ShutDownDrawingThermal ( ESContext *esContext )
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
   DestroySpritesThermal();
   RcOnExit();
}


void InitRenderingThermalCam()
{
    esContextThermalcam.userData = malloc ( sizeof ( UserData ) );

    //esCreateWindow ( esContext, "MultiTexture", SCREEN_SIZE_X, SCREEN_SIZE_Y, ES_WINDOW_RGB );
    esCreateRenderSurface( &esContextThermalcam, SCREEN_SIZE_X, SCREEN_SIZE_Y, ES_WINDOW_RGB );;
    esRegisterDrawFunc ( &esContextThermalcam, DrawThermal );
    InitThermalDraw ( &esContextThermalcam );
}

void InitialiseHikDraw()
{

    memset ( &esContextThermalcam, 0, sizeof( esContextThermalcam ) );
    InitRenderingThermalCam();
    //LcaAddOnImageReceived(LcaImageReceivedCallback);
}


void ShutdownThermal()
{
    ShutDownDrawingThermal(&esContextThermalcam);

    if ( esContextThermalcam.userData != NULL )
       free ( esContextThermalcam.userData );
}
