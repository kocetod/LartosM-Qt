
//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Wesley Professional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengles-book.com
//

// esUtil_X11.c
//
//    This file contains the LinuxX11 implementation of the windowing functions. 

///
// Includes
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/time.h>
#include "esUtil.h"

#include  <X11/Xlib.h>
#include  <X11/Xatom.h>
#include  <X11/Xutil.h>

#include "Periph/LucidCamera.h"
#include "Merged/LarDebug.h"
#include <pthread.h>


//#include "Test.h"

// X11 related local variables
static Display *x_display = NULL;
static Atom s_wmDeleteMessage;

//////////////////////////////////////////////////////////////////
//
//  Private Functions
//
//


//////////////////////////////////////////////////////////////////
//
//  Public Functions
//
//

///
//  WinCreate()
//
//      This function initialized the native X11 display and window for EGL
//
EGLBoolean WinCreate(ESContext *esContext, const char *title)
{
    Window root;
    XSetWindowAttributes swa;
    XSetWindowAttributes  xattr;
    Atom wm_state;
    XWMHints hints;
    XEvent xev;
    //EGLConfig ecfg;
    EGLint num_config;
    Window win;

    /*
     * X11 native display initialization
     */

    x_display = XOpenDisplay(NULL);
    if ( x_display == NULL )
    {
        return EGL_FALSE;
    }

    root = DefaultRootWindow(x_display);

    swa.event_mask  =  ExposureMask | PointerMotionMask | KeyPressMask;
    win = XCreateWindow(
               x_display, root,
               0, 0, esContext->width, esContext->height, 0,
               CopyFromParent, InputOutput,
               CopyFromParent, CWEventMask,
               &swa );
    s_wmDeleteMessage = XInternAtom(x_display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(x_display, win, &s_wmDeleteMessage, 1);

    xattr.override_redirect = FALSE;
    XChangeWindowAttributes ( x_display, win, CWOverrideRedirect, &xattr );

    hints.input = TRUE;
    hints.flags = InputHint;
    XSetWMHints(x_display, win, &hints);

    // make the window visible on the screen
    XMapWindow (x_display, win);
    XStoreName (x_display, win, title);

    // get identifiers for the provided atom name strings
    wm_state = XInternAtom (x_display, "_NET_WM_STATE", FALSE);

    memset ( &xev, 0, sizeof(xev) );
    xev.type                 = ClientMessage;
    xev.xclient.window       = win;
    xev.xclient.message_type = wm_state;
    xev.xclient.format       = 32;
    xev.xclient.data.l[0]    = 1;
    xev.xclient.data.l[1]    = FALSE;
    XSendEvent (
       x_display,
       DefaultRootWindow ( x_display ),
       FALSE,
       SubstructureNotifyMask,
       &xev );

    esContext->eglNativeWindow = (EGLNativeWindowType) win;
    esContext->eglNativeDisplay = (EGLNativeDisplayType) x_display;
    return EGL_TRUE;
}

///
//  userInterrupt()
//
//      Reads from X11 event loop and interrupt program if there is a keypress, or
//      window close action.
//
GLboolean userInterrupt(ESContext *esContext)
{
    XEvent xev;
    KeySym key;
    GLboolean userinterrupt = GL_FALSE;
    char text;

    // Pump all messages from X server. Keypresses are directed to keyfunc (if defined)
    while ( XPending ( x_display ) )
    {
        XNextEvent( x_display, &xev );
        if ( xev.type == KeyPress )
        {
            if (XLookupString(&xev.xkey,&text,1,&key,0)==1)
            {
                if (esContext->keyFunc != NULL)
                    esContext->keyFunc(esContext, text, 0, 0);
            }
        }

        if(xev.type == KeyRelease)
        {
            if (XLookupString(&xev.xkey,&text,1,&key,0)==1)
            {
                if (esContext->keyReleaseFunc != NULL)
                    esContext->keyReleaseFunc(esContext, text, 0, 0);
            }
        }

        if (xev.type == ClientMessage) {
            if (xev.xclient.data.l[0] == s_wmDeleteMessage) {
                userinterrupt = GL_TRUE;
            }
        }
        if ( xev.type == DestroyNotify )
            userinterrupt = GL_TRUE;
    }
    return userinterrupt;
}

///
//  WinLoop()
//
//      Start main windows loop
//
/*
void WinLoop ( ESContext *esContext )
{
    struct timeval t1, t2;
    struct timezone tz;
    float deltatime;

    gettimeofday ( &t1 , &tz );

    int i =0;
    while(1)
    {
        i++;
        gettimeofday(&t2, &tz);
        deltatime = (float)(t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) * 1e-6);
        t1 = t2;

        if (esContext->updateFunc != NULL)
            esContext->updateFunc(esContext, deltatime);
    }
}*/
/*
void sleep_us(unsigned long argInMicrosecounds)
{
    struct timespec ts;
    ts.tv_sec = argInMicrosecounds/1000000ul;
    ts.tv_nsec = (argInMicrosecounds/1000000ul)*1000;
    nanosleep(&ts,NULL);
}*/
/*
void DrawLoop(ESContext *esContext)
{
    char ImageBuffer[esContext->width*esContext->height*4];

    int i =0;
    while(1)
    {
        i++;
        pthread_mutex_lock(&lucidCameraMut);
        if (esContext->drawFunc != NULL)
        {esContext->drawFunc(esContext);}
        pthread_mutex_unlock(&lucidCameraMut);

        eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
        glReadPixels(0,0,esContext->width, esContext->height,GL_RGBA,GL_UNSIGNED_BYTE,&ImageBuffer);
        if(i==250)
        {
            SaveSimpleImage(ImageBuffer,esContext->width, esContext->height,32,  "Test.png");
        }
        sleep_us(30);
    }
}*/
/*
///
//  Global extern.  The application must declsare this function
//  that runs the application.
//
extern int esMain( ESContext *esContext );*/


/*
static void * _draw_thread(void * data);
static pthread_t draw_thread_id;

void * _draw_thread(void * data)
{
    DrawLoop((ESContext*)data);

    return NULL;
}


int InitializeDrawThread(void * data)
{
    if(pthread_create(&draw_thread_id, NULL, _draw_thread, data))
    {
        return 0;
    }

    return 1;
}*/

/*
int mainUtil ()
{
   ESContext esContext;
   
   memset ( &esContext, 0, sizeof( esContext ) );


   if ( esMain ( &esContext ) != GL_TRUE )
      return 1;   
 
   //mainTestFBO();
    InitializeDrawThread(&esContext);
    WinLoop ( &esContext );

   if ( esContext.shutdownFunc != NULL )
	   esContext.shutdownFunc ( &esContext );

   if ( esContext.userData != NULL )
	   free ( esContext.userData );

   return 0;
}*/
