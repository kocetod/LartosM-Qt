#pragma once
#include "esUtil/esUtil.h"
#include "string.h"
#include <stdbool.h>

#define MAX_TEXTURE_DATAS 2000

typedef struct
{
    float x;
    float y;
}Point;

typedef struct
{
    bool initialised;
    float textureOffsetX;
    float textureOffsetY;

    float textureElementsX;
    float textureElementsY;

    float selectedElement;

    bool elementPositionsAreInvertedOnX;
    bool elementPositionsAreInvertedOnY;

    Point defaultTextureCoordTL;
    Point defaultTextureCoordBL;
    Point defaultTextureCoordBR;
    Point defaultTextureCoordTR;

    Point calculatedTextureCoordTL;
    Point calculatedTextureCoordBL;
    Point calculatedTextureCoordBR;
    Point calculatedTextureCoordTR;

} TextureData;

TextureData* InstantiateTexture();
void DestroyTexture(TextureData* argInTexture);
void SetTextureElementsCount(TextureData* argInTextureData, int argInCountX, int argInCountY);
void SetTextureOffset(TextureData* argInTextureData, float argInOffsetX, float argInOffsetY);
void SetTextureElementsInvertion(TextureData* argInTextureData, bool argInElementPositionsAreInvertedOnX, bool argInElementPositionsAreInvertedOnY);
void SetTextureSelectedElement(TextureData* argInTextureData, int argInSelectedElement);
void CalculateTextureCoords(TextureData* argInTextureData);
