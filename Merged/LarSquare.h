#pragma once
#include "esUtil/esUtil.h"
#include "string.h"
#include "LarTexture.h"

#define SQUARES_MAX_COUNT 2000

typedef struct
{
    bool initialised;
    GLfloat vertexes[20];
    GLfloat translatedVertexes[20];
    GLushort indices[6];
    GLfloat positionX;
    GLfloat positionY;
    GLfloat scaleX;
    GLfloat scaleY;
    Point textCoordTL;
    Point textCoordBL;
    Point textCoordBR;
    Point textCoordTR;
} Square;

typedef struct
{
    float pivotX;
    float pivotY;
    float offsetModifierX;
    float offsetModifierY;

} Anchor;

Square* InstantiateSquare();

void DestroySquare(Square* argInSquare);

void ScaleSquareX(Square* argInSquare, float argInScale);

void ScaleSquareY(Square* argInSquare, float argInScale);

void SetSquareAspectRatio(Square* argInSquare, float argInRatio);
void SetSquarePosition(Square* argInSquare, float argInPositionX, float argInPositionY);
void ApplySquareTransformations(Square* argInSquare);
void SetTexturePoints(Square* argInSquare, Point argInTL, Point argInBL, Point argInBR, Point argInTR);
