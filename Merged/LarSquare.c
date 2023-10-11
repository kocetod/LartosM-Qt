#include "LarSquare.h"

Square SquaresPool[SQUARES_MAX_COUNT];

void InitialiseSquares()
{
    for(int i=0;i<SQUARES_MAX_COUNT;i++)
    {
        SquaresPool[i].initialised=false;
    }
}


Anchor anchCross = {.pivotX = 0.0f, .pivotY = 0.0f, .offsetModifierX = -0.5f, .offsetModifierY = 0.5f};

const Square basicSquare = {
                .vertexes = {
                      -1.0f,  1.0f, 0.1f,         // Position 0
                      0.0f,  1.0f,                // TexCoord 0

                      -1.0f, -1.0f, 0.1f,         // Position 1
                      0.0f,  0.0f,                // TexCoord 1

                      1.0f, -1.0f, 0.1f,          // Position 2
                      1.0f,  0.0f,                // TexCoord 2

                      1.0f,  1.0f, 0.1f,          // Position 3
                      1.0f,  1.0f                 // TexCoord 3
                      },
                .translatedVertexes = {
                      -1.0f,  1.0f, 0.1f,         // Position 0
                      0.0f,  1.0f,                // TexCoord 0

                      -1.0f, -1.0f, 0.1f,         // Position 1
                      0.0f,  0.0f,                // TexCoord 1

                      1.0f, -1.0f, 0.1f,          // Position 2
                      1.0f,  0.0f,                // TexCoord 2

                      1.0f,  1.0f, 0.1f,          // Position 3
                      1.0f,  1.0f                 // TexCoord 3
                      },
                .indices = { 0, 1, 2, 0, 2, 3 },
                .positionX = 0.0f ,
                .positionY = 0.0f ,
                .scaleX = 1.0f,
                .scaleY = 1.0f,
                .textCoordTL = {.x=0.0f,.y=1.0f},
                .textCoordBL = {.x=0.0f,.y=0.0f},
                .textCoordBR = {.x=1.0f,.y=0.0f},
                .textCoordTR = {.x=1.0f,.y=1.0f},
                };

Square* InstantiateSquare()
{
    Square *newSquare = NULL;
    for(int i=0;i<SQUARES_MAX_COUNT;i++)
    {
        if(SquaresPool[i].initialised==false)
        {
            SquaresPool[i].initialised = true;
            newSquare = &SquaresPool[i];
            break;
        }
    }
    if(newSquare!=NULL)
    {
        //Square *newSquare = (Square*)malloc ( sizeof ( Square ));
        for(int i =0; i<20; i++)
        {
            newSquare->vertexes[i] = basicSquare.vertexes[i];
        }
        for(int i =0; i<20; i++)
        {
            newSquare->translatedVertexes[i] = basicSquare.translatedVertexes[i];
        }
        for(int i =0; i<6; i++)
        {
            newSquare->indices[i] = basicSquare.indices[i];
        }
        newSquare->positionX = 0.0f;
        newSquare->positionY = 0.0f;
        newSquare->scaleX = 1.0f;
        newSquare->scaleY = 1.0f;

        newSquare->textCoordTL.x=0.0f;
        newSquare->textCoordTL.y=1.0f;

        newSquare->textCoordBL.x=0.0f;
        newSquare->textCoordBL.y=0.0f;

        newSquare->textCoordBR.x=1.0f;
        newSquare->textCoordBR.y=0.0f;

        newSquare->textCoordTR.x=1.0f;
        newSquare->textCoordTR.y=1.0f;
    }
    return newSquare;
}

void DestroySquare(Square* argInSquare)
{
    free(argInSquare);
}

void ScaleSquareX(Square* argInSquare, float argInScale)
{
    argInSquare->scaleX = argInScale;
}

void ScaleSquareY(Square* argInSquare, float argInScale)
{
    argInSquare->scaleY = argInScale;
}

void SetSquareAspectRatio(Square* argInSquare, float argInRatio)
{
    ScaleSquareX(argInSquare,argInSquare->scaleX*(1.0f/argInRatio));
}

void SetSquarePosition(Square* argInSquare, float argInPositionX, float argInPositionY)
{
    argInSquare->positionX = argInPositionX;
    argInSquare->positionY = argInPositionY;
}
/*
void SetTextureOffsetX(Square* argInSquare, float argInTextureOffsetX)
{
    argInSquare->textureOffsetX = argInTextureOffsetX;
}

void SetTextureOffsetY(Square* argInSquare, float argInTextureOffsetY)
{
    argInSquare->textureOffsetX= argInTextureOffsetY;
}*/

void SetTexturePoints(Square* argInSquare, Point argInTL, Point argInBL, Point argInBR, Point argInTR)
{
    argInSquare->textCoordTL.x=argInTL.x;
    argInSquare->textCoordTL.y=argInTL.y;

    argInSquare->textCoordBL.x=argInBL.x;
    argInSquare->textCoordBL.y=argInBL.y;

    argInSquare->textCoordBR.x=argInBR.x;
    argInSquare->textCoordBR.y=argInBR.y;

    argInSquare->textCoordTR.x=argInTR.x;
    argInSquare->textCoordTR.y=argInTR.y;
}


void ApplySquareTransformations(Square* argInSquare)
{
    argInSquare->translatedVertexes[0] = (argInSquare->vertexes[0] * argInSquare->scaleX)+argInSquare->positionX;
    argInSquare->translatedVertexes[5] = (argInSquare->vertexes[5] * argInSquare->scaleX)+argInSquare->positionX;
    argInSquare->translatedVertexes[10] = (argInSquare->vertexes[10] * argInSquare->scaleX)+argInSquare->positionX;
    argInSquare->translatedVertexes[15] = (argInSquare->vertexes[15] * argInSquare->scaleX)+argInSquare->positionX;

    argInSquare->translatedVertexes[1] = (argInSquare->vertexes[1] * argInSquare->scaleY)+argInSquare->positionY;
    argInSquare->translatedVertexes[6] = (argInSquare->vertexes[6] * argInSquare->scaleY)+argInSquare->positionY;
    argInSquare->translatedVertexes[11] = (argInSquare->vertexes[11] * argInSquare->scaleY)+argInSquare->positionY;
    argInSquare->translatedVertexes[16] = (argInSquare->vertexes[16] * argInSquare->scaleY)+argInSquare->positionY;

    argInSquare->translatedVertexes[3] = argInSquare->textCoordTL.x;
    argInSquare->translatedVertexes[4] = argInSquare->textCoordTL.y;

    argInSquare->translatedVertexes[8] = argInSquare->textCoordBL.x;
    argInSquare->translatedVertexes[9] = argInSquare->textCoordBL.y;

    argInSquare->translatedVertexes[13] = argInSquare->textCoordBR.x;
    argInSquare->translatedVertexes[14] = argInSquare->textCoordBR.y;

    argInSquare->translatedVertexes[18] = argInSquare->textCoordTR.x;
    argInSquare->translatedVertexes[19] = argInSquare->textCoordTR.y;
}
