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

#include "stdafx.h"
#include "ArenaC/ArenaCApi.h"
#include "SaveC/SaveCApi.h"
#include <stdlib.h>
#include "esUtil/esUtil.h"
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>


void Print_ip(uint32_t ip)
{
    unsigned char bytes[4];
    bytes[0] = ip & 0xFF;
    bytes[1] = (ip >> 8) & 0xFF;
    bytes[2] = (ip >> 16) & 0xFF;
    bytes[3] = (ip >> 24) & 0xFF;

    printf("%d.%d.%d.%d\n", bytes[3], bytes[2], bytes[1], bytes[0]);
}

GLuint CreateSimpleTexture2D( )
{
   GLuint textureId;

   // 2x2 Image, 3 bytes per pixel (R, G, B)
   GLubyte pixels[4 * 3] =
   {
      255,   0,   0, // Red
        0, 255,   0, // Green
        0,   0, 255, // Blue
      255, 255,   0  // Yellow
   };

   glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );    // Use tightly packed data
   glGenTextures ( 1, &textureId );             // Generate a texture object
   glBindTexture ( GL_TEXTURE_2D, textureId );  // Bind the texture object
   glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels ); // Load the texture
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST ); // Set the filtering mode
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

   return textureId;
}

AC_ERROR SaveImage(acBuffer hBuffer, const char* filename)
{
	AC_ERROR acErr = AC_ERR_SUCCESS;
	acBuffer hConverted = NULL;

    acErr = acImageFactoryConvert(hBuffer, PFNC_RGB8, &hConverted);
    if (acErr != AC_ERR_SUCCESS){return acErr;}

	size_t width = 0;
	acErr = acImageGetWidth(hConverted, &width);
    if (acErr != AC_ERR_SUCCESS){return acErr;}

	size_t height = 0;
    acErr = acImageGetHeight(hConverted, &height);
    if (acErr != AC_ERR_SUCCESS){return acErr;}

	size_t bpp = 0;
    acErr = acImageGetBitsPerPixel(hConverted, &bpp);
    if (acErr != AC_ERR_SUCCESS){return acErr;}

	saveWriter hWriter = NULL;
	saveWriterCreate(width, height, bpp, &hWriter);
	saveWriterSetFileNamePattern(hWriter, filename);

	uint8_t* pData = NULL;
	acErr = acImageGetData(hConverted, &pData);
    if (acErr != AC_ERR_SUCCESS){return acErr;}

	saveWriterSave(hWriter, pData);
	saveWriterDestroy(hWriter);
	acErr = acImageFactoryDestroy(hConverted);
    return acErr;
}

AC_ERROR SaveConvertedImage(acBuffer hBuffer, const char* filename)
{
    AC_ERROR acErr = AC_ERR_SUCCESS;
    acBuffer hConverted = hBuffer;

    /*acErr = acImageFactoryConvert(hBuffer, PFNC_RGB8, &hConverted);
    if (acErr != AC_ERR_SUCCESS){return acErr;}*/

    size_t width = 0;
    acErr = acImageGetWidth(hConverted, &width);
    if (acErr != AC_ERR_SUCCESS){return acErr;}

    size_t height = 0;
    acErr = acImageGetHeight(hConverted, &height);
    if (acErr != AC_ERR_SUCCESS){return acErr;}

    size_t bpp = 0;
    acErr = acImageGetBitsPerPixel(hConverted, &bpp);
    if (acErr != AC_ERR_SUCCESS){return acErr;}

    saveWriter hWriter = NULL;
    saveWriterCreate(width, height, bpp, &hWriter);
    saveWriterSetFileNamePattern(hWriter, filename);

    uint8_t* pData = NULL;
    acErr = acImageGetData(hConverted, &pData);
    if (acErr != AC_ERR_SUCCESS){return acErr;}

    saveWriterSave(hWriter, pData);
    saveWriterDestroy(hWriter);
    return acErr;
}

void SaveSimpleImage(acBuffer pData, int width, int height, int bpp,  const char* filename)
{
    /*AC_ERROR acErr = AC_ERR_SUCCESS;
    acBuffer hConverted = NULL;

    acErr = acImageFactoryConvert(hBuffer, PFNC_RGB8, &hConverted);
    if (acErr != AC_ERR_SUCCESS){return acErr;}

    size_t width = 0;
    acErr = acImageGetWidth(hConverted, &width);
    if (acErr != AC_ERR_SUCCESS){return acErr;}

    size_t height = 0;
    acErr = acImageGetHeight(hConverted, &height);
    if (acErr != AC_ERR_SUCCESS){return acErr;}

    size_t bpp = 0;
    acErr = acImageGetBitsPerPixel(hConverted, &bpp);
    if (acErr != AC_ERR_SUCCESS){return acErr;}*/

    saveWriter hWriter = NULL;
    saveWriterCreate(width, height, bpp, &hWriter);
    saveWriterSetFileNamePattern(hWriter, filename);

    /*uint8_t* pData = NULL;
    acErr = acImageGetData(hConverted, &pData);
    if (acErr != AC_ERR_SUCCESS){return acErr;}*/

    saveWriterSave(hWriter, pData);
    saveWriterDestroy(hWriter);
    //acErr = acImageFactoryDestroy(hConverted);
    return;
}
