#pragma once
#include "esUtil/esUtil.h"
#include "string.h"
#include "LarMaterial.h"
#include "LarSquare.h"
#include "LarTexture.h"
#include "LarSprite.h"
#include "string.h"

#define TEXTS_MAX_COUNT 50
#define TEXT_MAX_CHARS 32

enum TextAlignment
{
    TextAlignment_Left,
    TextAlignment_Centered,
    TextAlignment_Right
};

typedef struct
{
    bool initialised;
    char* textString;
    Material *textMaterial;
    float positionX;
    float positionY;
    enum TextAlignment alignment;
    Sprite *textCharacters[TEXT_MAX_CHARS];
    bool charactersDisplayed[TEXT_MAX_CHARS];
} Text;

Text *InstantiateText(Material *argInMaterial, float characterSizeX, float characterSizeY);
void SetFontTextureGrid(Text* argInText, int argInSizeX, int argInSizeY, bool argInInvertX, bool arginInvertY);
void SetTextString(Text* argInText, char* argInTextString);
void SetTextPosition(Text* argInText, float argInX, float argInY, enum TextAlignment argInAlignment);
void DrawText(Text* argInText);
