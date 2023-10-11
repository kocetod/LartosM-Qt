#include "LarMaterial.h"


Material MaterialsPool[MATERIAL_MAX_COUNT];

void InitialiseMaterials()
{
    for(int i=0;i<MATERIAL_MAX_COUNT;i++)
    {
        MaterialsPool[i].initialised=false;
    }
}


Material *InstantiateMaterial()
{
    Material *newMaterial = NULL;
    for(int i=0;i<MATERIAL_MAX_COUNT;i++)
    {
        if(MaterialsPool[i].initialised==false)
        {
            MaterialsPool[i].initialised = true;
            newMaterial = &MaterialsPool[i];
            break;
        }
    }
    if(newMaterial!=NULL)
    {
    //Material *newMaterial = (Material*)malloc ( sizeof ( Material ));
        for(int i = 0; i<MATERIAL_MAX_PARAMS; i++)
        {
            char *noName = (char*) malloc(sizeof(char)*MATERIAL_DATA_MAX_CHARS);
            newMaterial->params[i].assigned=0;
            newMaterial->params[i].name=noName;
            newMaterial->params[i].argInDataPtr=0;
            newMaterial->params[i].paramType = MatParamType_None;
        }
        for(int i = 0; i<MATERIAL_MAX_Textures; i++)
        {
            newMaterial->textureIds[i] = 9999;
        }
        newMaterial->enableAlphaBlending = FALSE;
        newMaterial->textureWrapRepeat = FALSE;
    }
    return newMaterial;
}

void DestroyMaterial(Material* argInMaterial)
{
   /* for(int i = 0; i<MATERIAL_MAX_PARAMS; i++)
    {
        free(argInMaterial->params[i].name);
    }*/
    for(int i = 0; i<MATERIAL_MAX_Textures; i++)
    {
        if(argInMaterial->textureIds[i]!=9999)
        {
            glDeleteTextures ( 1, &(argInMaterial->textureIds[i]));
        }
    }
    glDeleteProgram ( argInMaterial->shaderProgram );
    /*free(argInMaterial);*/
}

uint8_t AddMaterialParametter(Material* argInMaterial, char *argInName, void *argInDataPtr, enum MatParamType arginParamType)
{
    uint8_t result = 0;
    for(int i = 0; i<MATERIAL_MAX_PARAMS; i++)
    {
        if(argInMaterial->params[i].assigned==0)
        {
            strcpy(argInMaterial->params[i].name,argInName);
            argInMaterial->params[i].argInDataPtr = argInDataPtr;
            argInMaterial->params[i].assigned = 1;
            argInMaterial->params[i].paramType = arginParamType;
            result = 1;
            break;
        }
    }
    return result;
}

void GenerateShaderProgram(Material* argInMaterial, char* argInVertexShaderString, char *argInFragmentShaderString)
{
    argInMaterial->shaderProgram = esLoadProgram ( argInVertexShaderString, argInFragmentShaderString );
}

void UpdateMaterialTexture(Material* argInMaterial,char* argInTextureName, GLsizei argInWidth, GLsizei argInHeight, int argInFormat, void* argInNewTextureData)
{
    for(int i=0;i<MATERIAL_MAX_PARAMS;i++)
    {
        if(argInMaterial->params[i].assigned==1)
        {
            if(argInMaterial->params[i].paramType==MatParamType_1i)
            {
                if(strcmp(argInMaterial->params[i].name,argInTextureName)==0)
                {
                    glBindTexture ( GL_TEXTURE_2D, *((GLuint*)(argInMaterial->params[i].argInDataPtr)) );
                    glTexImage2D ( GL_TEXTURE_2D, 0, argInFormat, argInWidth, argInHeight, 0, argInFormat, GL_UNSIGNED_BYTE, argInNewTextureData );
                    break;
                }
            }
        }
    }
}

GLuint LoadTextureFromFile ( void *ioContext, char *fileName )
{
   int width, height;
   GLuint texId;
   char *buffer = esLoadTGA ( ioContext, fileName, &width, &height );
   if ( buffer == NULL )
   {
      esLogMessage ( "Error loading (%s) image.\n", fileName );
      return 0;
   }

   glGenTextures ( 1, &texId );
   glBindTexture ( GL_TEXTURE_2D, texId );
   glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer );
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
   glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

   free ( buffer );

   return texId;
}

void AddMaterialParametterTextureFromFile(Material* argInMaterial, char *argInName, void *argInIoContext, char *argInFileName)
{
    for(int i = 0; i<MATERIAL_MAX_PARAMS; i++)
    {
        if(argInMaterial->textureIds[i]==9999)
        {
            argInMaterial->textureIds[i] = LoadTextureFromFile ( argInIoContext, argInFileName );
            AddMaterialParametter(argInMaterial,argInName,&(argInMaterial->textureIds[i]), MatParamType_1i);
            break;
        }
    }
}

void SetMaterialAlphaBlending(Material* argInMaterial,bool argInUseAlphaBlending)
{
    argInMaterial->enableAlphaBlending = argInUseAlphaBlending;
}

void SetMaterialTextureWrap(Material* argInMaterial,bool argInTextureWrapRepeat)
{
    argInMaterial->textureWrapRepeat = argInTextureWrapRepeat;
}
