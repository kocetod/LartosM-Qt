#include "LarSprite.h"
#include "string.h"

Sprite SpritesPool[SPRITES_MAX_COUNT];

void InitialiseSprites()
{
    for(int i=0;i<SPRITES_MAX_COUNT;i++)
    {
        SpritesPool[i].initialised=false;
    }
}


Sprite *InstantiateSprite(Material argInMaterial, Square argInSquare, TextureData argInTextureData)
{
    Sprite *newSprite = NULL;
    for(int i=0;i<SQUARES_MAX_COUNT;i++)
    {
        if(SpritesPool[i].initialised==false)
        {
            SpritesPool[i].initialised = true;
            newSprite = &SpritesPool[i];
            break;
        }
    }
    if(newSprite!=NULL)
    {
        //Sprite *newSprite = (Sprite*)malloc ( sizeof ( Sprite ));
        newSprite->square = argInSquare;
        newSprite->material = argInMaterial;
        newSprite->textureData = argInTextureData;
    }
    return newSprite;
}

void DestroySprite(Sprite* argInSprite)
{
    DestroyMaterial(&(argInSprite->material));
    DestroySquare(&(argInSprite->square));
    DestroyTexture(&(argInSprite->textureData));
    //free(argInSprite);
}

void ApplyTextureCoords(Sprite* argInSprite)
{
    CalculateTextureCoords(&(argInSprite->textureData));
    SetTexturePoints(&(argInSprite->square),argInSprite->textureData.calculatedTextureCoordTL,argInSprite->textureData.calculatedTextureCoordBL,argInSprite->textureData.calculatedTextureCoordBR,argInSprite->textureData.calculatedTextureCoordTR);
}

void DrawSprite(Sprite* argInSprite)
{
    ApplyTextureCoords(argInSprite);
    ApplySquareTransformations(&(argInSprite->square));

    glUseProgram ( argInSprite->material.shaderProgram );

    if(argInSprite->material.enableAlphaBlending==TRUE)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    }
    else
    {
        glDisable(GL_BLEND);
    }

    glVertexAttribPointer ( 0, 3, GL_FLOAT,GL_FALSE, 5 * sizeof ( GLfloat ), argInSprite->square.translatedVertexes );
    glVertexAttribPointer ( 1, 2, GL_FLOAT,GL_FALSE, 5 * sizeof ( GLfloat ), &(argInSprite->square.translatedVertexes[3]));
    glEnableVertexAttribArray ( 0 );
    glEnableVertexAttribArray ( 1 );

    int activeTexture = 0;
    for(int i=0;i<MATERIAL_MAX_PARAMS;i++)
    {
        if(argInSprite->material.params[i].assigned==1)
        {
            if(argInSprite->material.params[i].paramType==MatParamType_4f)
            {
                int colorLocation = glGetUniformLocation(argInSprite->material.shaderProgram,argInSprite->material.params[i].name);
                glUniform4f(colorLocation,
                             ((float*)(argInSprite->material.params[i].argInDataPtr))[0],
                             ((float*)(argInSprite->material.params[i].argInDataPtr))[1],
                             ((float*)(argInSprite->material.params[i].argInDataPtr))[2],
                             ((float*)(argInSprite->material.params[i].argInDataPtr))[3]);
            }
            else if(argInSprite->material.params[i].paramType==MatParamType_1f)
            {
                int floatLocation = glGetUniformLocation(argInSprite->material.shaderProgram,argInSprite->material.params[i].name);
                glUniform1f(floatLocation,((float*)(argInSprite->material.params[i].argInDataPtr))[0]);
            }
            else if(argInSprite->material.params[i].paramType==MatParamType_1i)
            {
                if(activeTexture==0){glActiveTexture ( GL_TEXTURE0 );}
                if(activeTexture==1){glActiveTexture ( GL_TEXTURE1 );}
                if(activeTexture==2){glActiveTexture ( GL_TEXTURE2 );}
                if(activeTexture==3){glActiveTexture ( GL_TEXTURE3 );}

                glBindTexture ( GL_TEXTURE_2D, *((GLuint*)(argInSprite->material.params[i].argInDataPtr)));

                if(argInSprite->material.textureWrapRepeat==TRUE)
                {
                    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
                }
                else
                {
                    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
                    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
                }

                int texLocation = glGetUniformLocation (argInSprite->material.shaderProgram, argInSprite->material.params[i].name );
                glUniform1i ( texLocation, activeTexture );

                activeTexture++;
            }
        }
    }

    glDrawElements ( GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, argInSprite->square.indices );
}
