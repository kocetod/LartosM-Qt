// The MIT License (MIT)
//
// Copyright (c) 2013 Dan Ginsburg, Budirijanto Purnomo
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

//
// Book:      OpenGL(R) ES 3.0 Programming Guide, 2nd Edition
// Authors:   Dan Ginsburg, Budirijanto Purnomo, Dave Shreiner, Aaftab Munshi
// ISBN-10:   0-321-93388-5
// ISBN-13:   978-0-321-93388-1
// Publisher: Addison-Wesley Professional
// URLs:      http://www.opengles-book.com
//            http://my.safaribooksonline.com/book/animation-and-3d/9780133440133
//
// ESUtil.c
//
//    A utility library for OpenGL ES.  This library provides a
//    basic common framework for the example applications in the
//    OpenGL ES 3.0 Programming Guide.
//

///
//  Includes
//
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "esUtil.h"
#include "esUtil_win.h"
#include "Merged/LarDebug.h"

#ifdef ANDROID
#include <android/log.h>
#include <android_native_app_glue.h>
#include <android/asset_manager.h>
typedef AAsset esFile;
#else
typedef FILE esFile;
#endif

#ifdef __APPLE__
#include "FileWrapper.h"
#endif

///
//  Macros
//
#define INVERTED_BIT            (1 << 5)

///
//  Types
//
#ifndef __APPLE__
#pragma pack(push,x1)                            // Byte alignment (8-bit)
#pragma pack(1)
#endif

typedef struct
#ifdef __APPLE__
__attribute__ ( ( packed ) )
#endif
{
   unsigned char  IdSize,
            MapType,
            ImageType;
   unsigned short PaletteStart,
            PaletteSize;
   unsigned char  PaletteEntryDepth;
   unsigned short X,
            Y,
            Width,
            Height;
   unsigned char  ColorDepth,
            Descriptor;

} TGA_HEADER;

#ifndef __APPLE__
#pragma pack(pop,x1)
#endif

#ifndef __APPLE__

///
// GetContextRenderableType()
//
//    Check whether EGL_KHR_create_context extension is supported.  If so,
//    return EGL_OPENGL_ES3_BIT_KHR instead of EGL_OPENGL_ES2_BIT
//
EGLint GetContextRenderableType ( EGLDisplay eglDisplay )
{
#ifdef EGL_KHR_create_context
   const char *extensions = eglQueryString ( eglDisplay, EGL_EXTENSIONS );

   // check whether EGL_KHR_create_context is in the extension string
   if ( extensions != NULL && strstr( extensions, "EGL_KHR_create_context" ) )
   {
      // extension is supported
      return EGL_OPENGL_ES3_BIT_KHR;
   }
#endif
   // extension is not supported
   return EGL_OPENGL_ES2_BIT;
}
#endif

//////////////////////////////////////////////////////////////////
//
//  Public Functions
//
//

///
//  esCreateWindow()
//
//      title - name for title bar of window
//      width - width of window to create
//      height - height of window to create
//      flags  - bitwise or of window creation flags
//          ES_WINDOW_ALPHA       - specifies that the framebuffer should have alpha
//          ES_WINDOW_DEPTH       - specifies that a depth buffer should be created
//          ES_WINDOW_STENCIL     - specifies that a stencil buffer should be created
//          ES_WINDOW_MULTISAMPLE - specifies that a multi-sample buffer should be created
//
GLboolean ESUTIL_API esCreateWindow ( ESContext *esContext, const char *title, GLint width, GLint height, GLuint flags )
{
#ifndef __APPLE__
   EGLConfig config;
   EGLint majorVersion;
   EGLint minorVersion;
   EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE };

   if ( esContext == NULL )
   {
      return GL_FALSE;
   }
   esContext->width = width;
   esContext->height = height;

   if ( !WinCreate ( esContext, title ) )
   {
      return GL_FALSE;
   }

   esContext->eglDisplay = eglGetDisplay( esContext->eglNativeDisplay );
   if ( esContext->eglDisplay == EGL_NO_DISPLAY )
   {
      return GL_FALSE;
   }

   // Initialize EGL
   if ( !eglInitialize ( esContext->eglDisplay, &majorVersion, &minorVersion ) )
   {
      return GL_FALSE;
   }

   {
      EGLint numConfigs = 0;
      EGLint attribList[] =
      {
         EGL_RED_SIZE,       5,
         EGL_GREEN_SIZE,     6,
         EGL_BLUE_SIZE,      5,
         EGL_ALPHA_SIZE,     ( flags & ES_WINDOW_ALPHA ) ? 8 : EGL_DONT_CARE,
         EGL_DEPTH_SIZE,     ( flags & ES_WINDOW_DEPTH ) ? 8 : EGL_DONT_CARE,
         EGL_STENCIL_SIZE,   ( flags & ES_WINDOW_STENCIL ) ? 8 : EGL_DONT_CARE,
         EGL_SAMPLE_BUFFERS, ( flags & ES_WINDOW_MULTISAMPLE ) ? 1 : 0,
         // if EGL_KHR_create_context extension is supported, then we will use
         // EGL_OPENGL_ES3_BIT_KHR instead of EGL_OPENGL_ES2_BIT in the attribute list
         EGL_RENDERABLE_TYPE, GetContextRenderableType ( esContext->eglDisplay ),
         EGL_NONE
      };

      // Choose config
      if ( !eglChooseConfig ( esContext->eglDisplay, attribList, &config, 1, &numConfigs ) )
      {
         return GL_FALSE;
      }

      if ( numConfigs < 1 )
      {
         return GL_FALSE;
      }
   }

   // Create a surface
   esContext->eglSurface = eglCreateWindowSurface ( esContext->eglDisplay, config, 
                                                    esContext->eglNativeWindow, NULL );

   if ( esContext->eglSurface == EGL_NO_SURFACE )
   {
      return GL_FALSE;
   }

   // Create a GL context
   esContext->eglContext = eglCreateContext ( esContext->eglDisplay, config, 
                                              EGL_NO_CONTEXT, contextAttribs );

   if ( esContext->eglContext == EGL_NO_CONTEXT )
   {
      return GL_FALSE;
   }

   // Make the context current
   if ( !eglMakeCurrent ( esContext->eglDisplay, esContext->eglSurface, 
                          esContext->eglSurface, esContext->eglContext ) )
   {
      return GL_FALSE;
   }

#endif // #ifndef __APPLE__

   return GL_TRUE;
}

///
//  esRegisterDrawFunc()
//
void ESUTIL_API esRegisterDrawFunc ( ESContext *esContext, void ( ESCALLBACK *drawFunc ) ( ESContext * ) )
{
   esContext->drawFunc = drawFunc;
}

///
//  esRegisterShutdownFunc()
//
void ESUTIL_API esRegisterShutdownFunc ( ESContext *esContext, void ( ESCALLBACK *shutdownFunc ) ( ESContext * ) )
{
   esContext->shutdownFunc = shutdownFunc;
}

///
//  esRegisterUpdateFunc()
//
void ESUTIL_API esRegisterUpdateFunc ( ESContext *esContext, void ( ESCALLBACK *updateFunc ) ( ESContext *, float ) )
{
   esContext->updateFunc = updateFunc;
}


///
//  esRegisterKeyFunc()
//
void ESUTIL_API esRegisterKeyFunc ( ESContext *esContext,
                                    void ( ESCALLBACK *keyFunc ) ( ESContext *, unsigned char, int, int ) )
{
   esContext->keyFunc = keyFunc;
}

void ESUTIL_API esRegisterKeyReleaseFunc ( ESContext *esContext,
                                    void ( ESCALLBACK *keyReleaseFunc ) ( ESContext *, unsigned char, int, int ) )
{
   esContext->keyReleaseFunc = keyReleaseFunc;
}
///
// esLogMessage()
//
//    Log an error message to the debug output for the platform
//
void ESUTIL_API esLogMessage ( const char *formatStr, ... )
{
   va_list params;
   char buf[BUFSIZ];

   va_start ( params, formatStr );
   vsprintf ( buf, formatStr, params );

#ifdef ANDROID
   __android_log_print ( ANDROID_LOG_INFO, "esUtil" , "%s", buf );
#else
   printf ( "%s", buf );
#endif

   va_end ( params );
}

///
// esFileRead()
//
//    Wrapper for platform specific File open
//
static esFile *esFileOpen ( void *ioContext, const char *fileName )
{
   esFile *pFile = NULL;

#ifdef ANDROID

   if ( ioContext != NULL )
   {
      AAssetManager *assetManager = ( AAssetManager * ) ioContext;
      pFile = AAssetManager_open ( assetManager, fileName, AASSET_MODE_BUFFER );
   }

#else
#ifdef __APPLE__
   // iOS: Remap the filename to a path that can be opened from the bundle.
   fileName = GetBundleFileName ( fileName );
#endif

   pFile = fopen ( fileName, "rb" );
#endif

   return pFile;
}

///
// esFileRead()
//
//    Wrapper for platform specific File close
//
static void esFileClose ( esFile *pFile )
{
   if ( pFile != NULL )
   {
#ifdef ANDROID
      AAsset_close ( pFile );
#else
      fclose ( pFile );
      pFile = NULL;
#endif
   }
}

///
// esFileRead()
//
//    Wrapper for platform specific File read
//
static int esFileRead ( esFile *pFile, int bytesToRead, void *buffer )
{
   int bytesRead = 0;

   if ( pFile == NULL )
   {
      return bytesRead;
   }

#ifdef ANDROID
   bytesRead = AAsset_read ( pFile, buffer, bytesToRead );
#else
   bytesRead = fread ( buffer, bytesToRead, 1, pFile );
#endif

   return bytesRead;
}

///
// esLoadTGA()
//
//    Loads a 8-bit, 24-bit or 32-bit TGA image from a file
//
char *ESUTIL_API esLoadTGA ( void *ioContext, const char *fileName, int *width, int *height )
{
   char        *buffer;
   esFile      *fp;
   TGA_HEADER   Header;
   int          bytesRead;

   // Open the file for reading
   fp = esFileOpen ( ioContext, fileName );

   if ( fp == NULL )
   {
      // Log error as 'error in opening the input file from apk'
      esLogMessage ( "esLoadTGA FAILED to load : { %s }\n", fileName );
      return NULL;
   }

   bytesRead = esFileRead ( fp, sizeof ( TGA_HEADER ), &Header );

   *width = Header.Width;
   *height = Header.Height;

   if ( Header.ColorDepth == 8 ||
         Header.ColorDepth == 24 || Header.ColorDepth == 32 )
   {
      int bytesToRead = sizeof ( char ) * ( *width ) * ( *height ) * Header.ColorDepth / 8;

      // Allocate the image data buffer
      buffer = ( char * ) malloc ( bytesToRead );

      if ( buffer )
      {
         bytesRead = esFileRead ( fp, bytesToRead, buffer );
         esFileClose ( fp );

         return ( buffer );
      }
   }

   return ( NULL );
}


int mainTestFBO() {
    unsetenv( "DISPLAY" );
    size_t imgWidth, imgHeight;
    //auto imgData = LoadImageInterleaved("../res/textures/penguin.png", imgWidth, imgHeight);
    /*
     * EGL initialization and OpenGL context creation.
     */
    EGLint majorVersion;
    EGLint minorVersion;

    EGLDisplay display;
    EGLConfig config;
    EGLContext context;
    EGLSurface surface;
    EGLint num_config;

    const EGLint DISPLAY_ATTRIBS[] = {
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_BLUE_SIZE, 5, EGL_GREEN_SIZE, 6, EGL_RED_SIZE, 5,
            EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
            EGL_NONE
    };

    const EGLint CONTEXT_ATTRIBS[] = {
            EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE
    };

    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    //assertEGLError("eglGetDisplay");

    eglInitialize(display, &majorVersion, &minorVersion);
    //assertEGLError("eglInitialize");

    eglChooseConfig(display, DISPLAY_ATTRIBS, &config, 1, &num_config);
    //assertEGLError("eglChooseConfig");

    eglBindAPI(EGL_OPENGL_API);
    //assertEGLError("eglBindAPI");

    context = eglCreateContext(display, config, EGL_NO_CONTEXT, CONTEXT_ATTRIBS);
    //assertEGLError("eglCreateContext");

    int winWidth = 256;
    int winHeight = 256;

    EGLint SURFACE_ATTRIBS[] = {
        EGL_WIDTH, winWidth,
        EGL_HEIGHT, winHeight,
        EGL_NONE
    };

    surface = eglCreatePbufferSurface(display, config, SURFACE_ATTRIBS);
    //assertEGLError("eglCreatePbufferSurface");

    eglMakeCurrent(display, surface, surface, context);
    //eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, context);
    //assertEGLError("eglMakeCurrent");

    //std::string versionString = std::string((const char*)glGetString(GL_VERSION));
    //std::cout<<versionString<<std::endl;

    //Enable blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    /*
     * Create an OpenGL framebuffer as render target.
     */
    GLuint frameBuffer;
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    //assertOpenGLError("glBindFramebuffer");

    /*
     * Create a texture as color attachment.
     */
    GLuint outputTexId;

    outputTexId = CreateSimpleTexture2D( );

    /*CreateTexture(outputTex, winWidth, winHeight, nullptr);

    //auto CreateTexture = [](GLuint& tex, int width, int height, void* data) {
        glGenTextures(1, &outputTexId);
        assertOpenGLError("glGenTextures");
        glBindTexture(GL_TEXTURE_2D, tex);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, winWidth, winHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        assertOpenGLError("glTexImage2D");
        glBindTexture(GL_TEXTURE_2D, 0);
    //};*/

    glBindTexture(GL_TEXTURE_2D, outputTexId);
    /*
     * Attach the texture to the framebuffer.
     */
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, outputTexId, 0);
    //assertOpenGLError("glFramebufferTexture2D");

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        return -1;
    }

    /*
     * Create an OpenGL texture and load it with image data.
     */

    GLuint inputTex;
    inputTex = CreateSimpleTexture2D( );
    //CreateTexture(inputTex, imgWidth, imgHeight, imgData.data());
    glBindTexture(GL_TEXTURE_2D, inputTex);
    int textureSlot = 0;
    glActiveTexture(GL_TEXTURE0+textureSlot);
    //assertOpenGLError("glActiveTexture");

    //Build and use the shaders
            //program = CreateShader(vertexShader, fragmentShader);
            //glUseProgram(program);
            //assertOpenGLError("glUseProgram");

            //glUniform1i(glGetUniformLocation(program, "u_Texture"), textureSlot);
            //assertOpenGLError("glUniform1i, glGetUniformLocation");

    /*
    glm::mat4 proj = glm::ortho(0.f, (float)winWidth, 0.f, (float)winHeight, -1.f, 1.f);
    glUniformMatrix4fv(glGetUniformLocation(program, "u_MVP"), 1, GL_FALSE, &proj[0][0]);
    assertOpenGLError("glUniformMatrix4fv, glGetUniformLocation");*/

    //Define geometry to render and texture mapping
    float positions[] = {0.f, 0.f, 0.f, 0.f,
                        winWidth, 0.f, 1.f, 0.f,
                        winWidth, winHeight, 1.f, 1.f,
                        0.f, winHeight, 0.f, 1.f
                        };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (const void*) 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (const void*) (2*sizeof(GLfloat)));

    /*
     * Render something.
     */
    //glClearColor(0.3, 0.8, 0.5, 1.0);

                //glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
    //glClear(GL_COLOR_BUFFER_BIT);
    glFlush();


    /*
     * Read the framebuffer and save to disk as an image
     */
    //std::vector<unsigned char> buf(winWidth*winHeight*3);

    glReadBuffer(GL_COLOR_ATTACHMENT0);
                //glReadPixels(0, 0, winWidth, winHeight, GL_RGB, GL_UNSIGNED_BYTE, buf.data());
    //assertOpenGLError("glReadPixels");

                //SaveRGBImageToDisk("output", winWidth, winHeight, buf.data());

    /*
     * Destroy context.
     */
    glDeleteBuffers(1, &ibo);
    glDeleteBuffers(1, &vbo);
    glDeleteTextures(1, &inputTex);
    glDeleteFramebuffers(1, &frameBuffer);
                    //glDeleteTextures(1, &outputTex);
                    //glDeleteProgram(program);

    eglDestroySurface(display, surface);
    //assertEGLError("eglDestroySurface");

    eglDestroyContext(display, context);
    //assertEGLError("eglDestroyContext");

    eglTerminate(display);
    //assertEGLError("eglTerminate");

    return 0;
}


GLboolean ESUTIL_API esCreateRenderSurface ( ESContext *esContext, GLint width, GLint height, GLuint flags )
{
   EGLConfig config;
   EGLint majorVersion;
   EGLint minorVersion;
   EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE };

   if ( esContext == NULL )
   {
      return GL_FALSE;
   }
   esContext->width = width;
   esContext->height = height;

   /*if ( !WinCreate ( esContext, title ) )
   {
      return GL_FALSE;
   }*/
   esContext->eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
   if ( esContext->eglDisplay == EGL_NO_DISPLAY )
   {
      return GL_FALSE;
   }

   // Initialize EGL
   if ( !eglInitialize ( esContext->eglDisplay, &majorVersion, &minorVersion ) )
   {
      return GL_FALSE;
   }

      EGLint numConfigs = 0;
      EGLint attribList[] =
      {
         EGL_RED_SIZE,       5,
         EGL_GREEN_SIZE,     6,
         EGL_BLUE_SIZE,      5,
         EGL_ALPHA_SIZE,     ( flags & ES_WINDOW_ALPHA ) ? 8 : EGL_DONT_CARE,
         EGL_DEPTH_SIZE,     ( flags & ES_WINDOW_DEPTH ) ? 8 : EGL_DONT_CARE,
         EGL_STENCIL_SIZE,   ( flags & ES_WINDOW_STENCIL ) ? 8 : EGL_DONT_CARE,
         EGL_SAMPLE_BUFFERS, ( flags & ES_WINDOW_MULTISAMPLE ) ? 1 : 0,
         // if EGL_KHR_create_context extension is supported, then we will use
         // EGL_OPENGL_ES3_BIT_KHR instead of EGL_OPENGL_ES2_BIT in the attribute list
         EGL_RENDERABLE_TYPE, GetContextRenderableType ( esContext->eglDisplay ),
         EGL_NONE
      };

      const EGLint DISPLAY_ATTRIBS[] = {
              EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
              EGL_BLUE_SIZE, 5, EGL_GREEN_SIZE, 6, EGL_RED_SIZE, 5,
              EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
              EGL_NONE
      };

      const EGLint CONTEXT_ATTRIBS[] = {
              EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE
      };
      // Choose config
      if ( !eglChooseConfig ( esContext->eglDisplay, DISPLAY_ATTRIBS, &config, 1, &numConfigs ) )
      {
         return GL_FALSE;
      }

      if ( numConfigs < 1 )
      {
         return GL_FALSE;
      }

   eglBindAPI(EGL_OPENGL_API);
   //assertEGLError("eglBindAPI");

   esContext->eglContext = eglCreateContext(esContext->eglDisplay, config, EGL_NO_CONTEXT, CONTEXT_ATTRIBS);

   if ( esContext->eglContext == EGL_NO_CONTEXT )
   {
      return GL_FALSE;
   }
   // Create a surface
   //esContext->eglSurface = eglCreateWindowSurface ( esContext->eglDisplay, config,
   //                                                 esContext->eglNativeWindow, NULL );

   EGLint SURFACE_ATTRIBS[] = {
       EGL_WIDTH, width,
       EGL_HEIGHT, height,
       EGL_NONE
   };

   esContext->eglSurface = eglCreatePbufferSurface(esContext->eglDisplay, config, SURFACE_ATTRIBS);

   if ( esContext->eglSurface == EGL_NO_SURFACE )
   {
      return GL_FALSE;
   }

   // Create a GL context
   /*esContext->eglContext = eglCreateContext ( esContext->eglDisplay, config,
                                              EGL_NO_CONTEXT, contextAttribs );*/

   // Make the context current

   if ( !eglMakeCurrent ( esContext->eglDisplay, esContext->eglSurface,
                          esContext->eglSurface, esContext->eglContext ) )
   {
      return GL_FALSE;
   }

   return GL_TRUE;
}
