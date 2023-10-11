#include "LarText.h"
#include "string.h"


Text TextsPool[TEXTS_MAX_COUNT];

void InitialiseTexts()
{
    for(int i=0;i<TEXTS_MAX_COUNT;i++)
    {
        TextsPool[i].initialised=false;
    }
}

Text *InstantiateText(Material *argInMaterial, float characterSizeX, float characterSizeY)
{
    Text *newText = NULL;
    for(int i=0;i<TEXTS_MAX_COUNT;i++)
    {
        if(TextsPool[i].initialised==false)
        {
            TextsPool[i].initialised = true;
            newText = &TextsPool[i];
            break;
        }
    }
    if(newText!=NULL)
    {
        //Text *newText = (Text*)malloc ( sizeof ( Text ));
        for(int i=0;i<TEXT_MAX_CHARS;i++)
        {
            TextureData *chTData = InstantiateTexture();
            Square *chSquare = InstantiateSquare();
            ScaleSquareX(chSquare,characterSizeX);
            ScaleSquareY(chSquare,characterSizeY);

            newText->textCharacters[i]=InstantiateSprite(*argInMaterial,*chSquare,*chTData);
            newText->charactersDisplayed[i] = FALSE;
        }
    }
    return newText;
}

void SetFontTextureGrid(Text* argInText, int argInSizeX, int argInSizeY, bool argInInvertX, bool arginInvertY)
{
    for(int i=0;i<TEXT_MAX_CHARS;i++)
    {
        SetTextureElementsCount(&(argInText->textCharacters[i]->textureData),argInSizeX,argInSizeY);
    }
    for(int i=0;i<TEXT_MAX_CHARS;i++)
    {
        SetTextureElementsInvertion(&(argInText->textCharacters[i]->textureData),argInInvertX,arginInvertY);
    }
}

void SetTextPosition(Text* argInText, float argInX, float argInY, enum TextAlignment argInAlignment)
{
    argInText->positionX = argInX;
    argInText->positionY = argInY;
    argInText->alignment = argInAlignment;

    int stringLength = strlen(argInText->textString);

    if(stringLength>0)
    {
        float stringOffset = 0;
        if(argInAlignment==TextAlignment_Centered)
        {
            stringOffset=-((stringLength-0.5f)*argInText->textCharacters[0]->square.scaleX);
        }
        else if(argInAlignment==TextAlignment_Right)
        {
            stringOffset=-((stringLength-1)*argInText->textCharacters[0]->square.scaleX*2);
        }

        float accumulatedX = 0.0f;
        for(int i=0;i<stringLength;i++)
        {
            SetSquarePosition(&(argInText->textCharacters[i]->square), argInX+accumulatedX+stringOffset, argInY);
            accumulatedX+=2.0f*(argInText->textCharacters[i]->square.scaleX);
        }
    }
}


void SetCharacter(Text* argInText, int argInElement, int argInCharacter)
{
    if(argInElement<TEXT_MAX_CHARS)
    {
        argInText->textCharacters[argInElement]->textureData.selectedElement=argInCharacter;
    }
}

void SetTextString(Text* argInText, char* argInTextString)
{
    argInText->textString = argInTextString;
    int stringLength = strlen(argInTextString);
    for(int i=0;i<TEXT_MAX_CHARS;i++)
    {
        if(i<stringLength)
        {
            SetCharacter(argInText, i, (int)(argInTextString[i]));
            argInText->charactersDisplayed[i]=TRUE;
        }
        else
        {
            argInText->charactersDisplayed[i]=FALSE;
        }
    }
    SetTextPosition(argInText, argInText->positionX, argInText->positionY, argInText->alignment);
}

void DrawText(Text* argInText)
{
    for(int i=0;i<TEXT_MAX_CHARS;i++)
    {
        if(argInText->charactersDisplayed[i]==TRUE)
        {
            DrawSprite(argInText->textCharacters[i]);
        }
    }
}
