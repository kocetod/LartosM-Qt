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
#pragma once
#include "stdafx.h"
#include "ArenaC/ArenaCApi.h"
#include "SaveC/SaveCApi.h"
#include <stdlib.h>
#include "esUtil/esUtil.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>
#include "stdafx.h"
#include <time.h>
#include "LarDebug.h"
#include "LarMaterial.h"
#include "LarTexture.h"
#include "LarSquare.h"
#include "LarSprite.h"
#include "LarText.h"

#include "Periph/Uart.h"
#include "Periph/PanTiltU.h"
#include "Periph/UdpSocket.h"
#include "Application/GPSFormatter.h"
#include "Application/CompassCalibration.h"
#include "Periph/MUX.h"
#include "Periph/PeriphScheduler.h"
#include "Periph/GPS.h"
#include "Periph/Compass.h"
#include "Periph/LucidCamera.h"
#include <sys/resource.h>
#include "Configuration/ReadConfig.h"
#include "Periph/NetworkVariables.h"
#include "Periph/CompassDataManager.h"
#include "Periph/GpsDataManager.h"
#include "Periph/CommandsDataManager.h"
#include "Periph/Rangefinder.h"
#include "Periph/LucidCameraDraw.h"
#include "Periph/HikCameraDraw.h"
#include "Periph/PIC.h"
#include "Periph/ButtonsHead.h"
#include "Periph/ButtonsController.h"
#include "Periph/GpioWrapper.h"
#include "Periph/RangefinderDataManager.h"
#include "Periph/PtuDataManager.h"
#include "Periph/Diagnostic.h"
#include "Periph/PicDataManager.h"
#include "Periph/Diagnostic.h"
#include "Periph/CamerasController.h"
#include "Periph/HikCurlWrapper.h"
#include "Periph/ProxSensor.h"
#include "Application/CompassCalibration_PTU.h"

#define SCREEN_SIZE_X 1044

#define SCREEN_SIZE_Y 788


typedef struct
{
    GLuint programObject;
    GLuint programObjectCrosshair;

    GLint baseNewLoc;
    GLint baseOldLoc;
    GLint baseOldestLoc;
    GLint crosshairMapLoc;

    GLuint baseNewTexId;
    GLuint baseOldTexId;
    GLuint baseOldestTexId;

    GLuint crosshairMapTexId;
} UserData;

/*void InitRenderingDaycam( ESContext *esContextDaycam );*/

int InitPeripherals ();
