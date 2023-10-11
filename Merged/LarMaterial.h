#pragma once
#include "esUtil/esUtil.h"
#include "string.h"
#include <stdbool.h>

#define MATERIAL_MAX_COUNT 60
#define MATERIAL_DATA_MAX_CHARS 20
#define MATERIAL_MAX_PARAMS 16
#define MATERIAL_MAX_Textures 4

enum MatParamType
{
    MatParamType_None,
    MatParamType_1f,
    MatParamType_4f,
    MatParamType_1i
};

typedef struct
{
    void *argInDataPtr;
    uint8_t assigned;
    char *name;
    enum MatParamType paramType;
} MaterialParam;

typedef struct
{
    bool initialised;
    GLuint shaderProgram;
    bool enableAlphaBlending;
    bool textureWrapRepeat;
    MaterialParam params[MATERIAL_MAX_PARAMS];
    GLuint textureIds[MATERIAL_MAX_Textures];
} Material;

Material *InstantiateMaterial();
void DestroyMaterial(Material* argInMaterial);
uint8_t AddMaterialParametter(Material* argInMaterial, char *argInName, void *dataAddres, enum MatParamType argInType);
void GenerateShaderProgram(Material* argInMaterial, char* argInVertexShaderString, char *argInFragmentShaderString);
void UpdateMaterialTexture(Material* argInMaterial, char* argInTextureName, GLsizei argInWidth, GLsizei argInHeight, int argInFormat,void* argInNewTextureData);
void AddMaterialParametterTextureFromFile(Material* argInMaterial, char *argInName, void *argInIoContext, char *argInFileName);
GLuint LoadTextureFromFile ( void *ioContext, char *fileName );
void SetMaterialAlphaBlending(Material* argInMaterial,bool argInUseAlphaBlending);
void SetMaterialTextureWrap(Material* argInMaterial,bool argInTextureWrapRepeat);
