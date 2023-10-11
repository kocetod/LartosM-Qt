#pragma once
#include "esUtil/esUtil.h"
#include "string.h"
#include "LarMaterial.h"
#include "LarSquare.h"
#include "LarTexture.h"

#define SPRITES_MAX_COUNT 2000


typedef struct
{
    bool initialised;
    Square square;
    Material material;
    TextureData textureData;
} Sprite;

Sprite *InstantiateSprite(Material argInMaterial, Square argInSquare, TextureData argInTextureData);
void DestroySprite(Sprite* argInSprite);
void DrawSprite(Sprite* argInSprite);
