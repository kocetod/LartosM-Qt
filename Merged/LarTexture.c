#include "LarTexture.h"

TextureData TextureDatasPool[MAX_TEXTURE_DATAS];

void InitialiseTextureDatas()
{
    for(int i=0;i<MAX_TEXTURE_DATAS;i++)
    {
        TextureDatasPool[i].initialised=false;
    }
}

TextureData* InstantiateTexture()
{
    TextureData *newTexture = NULL;
    for(int i=0;i<MAX_TEXTURE_DATAS;i++)
    {
        if(TextureDatasPool[i].initialised==false)
        {
            TextureDatasPool[i].initialised = true;
            newTexture = &TextureDatasPool[i];
            break;
        }
    }
    if(newTexture!=NULL)
    {
        //TextureData *newTexture = malloc ( sizeof ( TextureData ));
        newTexture->textureOffsetX = 0.0f;
        newTexture->textureOffsetY = 0.0f;

        newTexture->textureElementsX = 1.0f;
        newTexture->textureElementsY = 1.0f;

        newTexture->selectedElement = 0.0f;

        newTexture->defaultTextureCoordTL.x = 0.0f;
        newTexture->defaultTextureCoordTL.y = 1.0f;

        newTexture->defaultTextureCoordBL.x = 0.0f;
        newTexture->defaultTextureCoordBL.y = 0.0f;

        newTexture->defaultTextureCoordBR.x = 1.0f;
        newTexture->defaultTextureCoordBR.y = 0.0f;

        newTexture->defaultTextureCoordTR.x = 1.0f;
        newTexture->defaultTextureCoordTR.y = 1.0f;

        newTexture->calculatedTextureCoordTL.x = 0.0f;
        newTexture->calculatedTextureCoordTL.y = 1.0f;

        newTexture->calculatedTextureCoordBL.x = 0.0f;
        newTexture->calculatedTextureCoordBL.y = 0.0f;

        newTexture->calculatedTextureCoordBR.x = 1.0f;
        newTexture->calculatedTextureCoordBR.y = 0.0f;

        newTexture->calculatedTextureCoordTR.x = 1.0f;
        newTexture->calculatedTextureCoordTR.y = 1.0f;

        newTexture->elementPositionsAreInvertedOnX = FALSE;
        newTexture->elementPositionsAreInvertedOnY = FALSE;

    }
    return newTexture;
}

void DestroyTexture(TextureData* argInTextureData)
{
    //free(argInTextureData);
}

void SetTextureElementsCount(TextureData* argInTextureData, int argInCountX, int argInCountY)
{
    argInTextureData->textureElementsX = (float)argInCountX;
    argInTextureData->textureElementsY = (float)argInCountY;
}

void SetTextureElementsInvertion(TextureData* argInTextureData, bool argInElementPositionsAreInvertedOnX, bool argInElementPositionsAreInvertedOnY)
{
    argInTextureData->elementPositionsAreInvertedOnX = argInElementPositionsAreInvertedOnX;
    argInTextureData->elementPositionsAreInvertedOnY = argInElementPositionsAreInvertedOnY;
}


void SetTextureOffset(TextureData* argInTextureData, float argInOffsetX, float argInOffsetY)
{
    argInTextureData->textureOffsetX = (float)argInOffsetX;
    argInTextureData->textureOffsetY = (float)argInOffsetY;
}

void SetTextureSelectedElement(TextureData* argInTextureData, int argInSelectedElement)
{
    if((argInTextureData->textureElementsX*argInTextureData->textureElementsY)>=(float)argInSelectedElement)
    {
        argInTextureData->selectedElement = (float)argInSelectedElement;
    }
}

void CalculateTextureCoords(TextureData* argInTextureData)
{
    float textureScaleX = 1.0f/argInTextureData->textureElementsX;
    float textureScaleY = 1.0f/argInTextureData->textureElementsY;

    float scaledTextureOffsetX = textureScaleX*argInTextureData->textureOffsetX;
    float scaledTextureOffsetY = textureScaleY*argInTextureData->textureOffsetY;


    Point scaledTL = {.x = argInTextureData->defaultTextureCoordTL.x*textureScaleX, .y = argInTextureData->defaultTextureCoordTL.y*textureScaleY};
    Point scaledBL = {.x = argInTextureData->defaultTextureCoordBL.x*textureScaleX, .y = argInTextureData->defaultTextureCoordBL.y*textureScaleY};
    Point scaledBR = {.x = argInTextureData->defaultTextureCoordBR.x*textureScaleX, .y = argInTextureData->defaultTextureCoordBR.y*textureScaleY};
    Point scaledTR = {.x = argInTextureData->defaultTextureCoordTR.x*textureScaleX, .y = argInTextureData->defaultTextureCoordTR.y*textureScaleY};

    float selectedElementX = (float)(((int)argInTextureData->selectedElement)%((int)(argInTextureData->textureElementsX)));
    float selectedElementY = ((int)argInTextureData->selectedElement-(int)selectedElementX)/(int)argInTextureData->textureElementsY;

    float selectedElementLocationX = textureScaleX*selectedElementX;
    float selectedElementLocationY = textureScaleY*selectedElementY;
    if(argInTextureData->elementPositionsAreInvertedOnX==TRUE)
    {
        selectedElementLocationX = textureScaleX*(argInTextureData->textureElementsX-(selectedElementX+1));
    }
    if(argInTextureData->elementPositionsAreInvertedOnY==TRUE)
    {
        selectedElementLocationY = textureScaleY*(argInTextureData->textureElementsY-(selectedElementY+1));
    }


    argInTextureData->calculatedTextureCoordTL.x = scaledTL.x+selectedElementLocationX+scaledTextureOffsetX;
    argInTextureData->calculatedTextureCoordTL.y = scaledTL.y+selectedElementLocationY+scaledTextureOffsetY;

    argInTextureData->calculatedTextureCoordBL.x = scaledBL.x+selectedElementLocationX+scaledTextureOffsetX;
    argInTextureData->calculatedTextureCoordBL.y = scaledBL.y+selectedElementLocationY+scaledTextureOffsetY;

    argInTextureData->calculatedTextureCoordBR.x = scaledBR.x+selectedElementLocationX+scaledTextureOffsetX;
    argInTextureData->calculatedTextureCoordBR.y = scaledBR.y+selectedElementLocationY+scaledTextureOffsetY;

    argInTextureData->calculatedTextureCoordTR.x = scaledTR.x+selectedElementLocationX+scaledTextureOffsetX;
    argInTextureData->calculatedTextureCoordTR.y = scaledTR.y+selectedElementLocationY+scaledTextureOffsetY;
}
