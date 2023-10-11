#include "esUtil/Init.h"


/*
void* imageBufferPtr;

int imageWidth = 0;
int imageHeight = 0;

void (*OnImageProcessedCallback)();

void (*OnThermalImageReceived)(int,int,acBuffer*);

void HikAddOnImageReceived(void* argInOnImageReceived)
{
    OnThermalImageReceived = argInOnImageReceived;
}

void AddImageProcessedCallback(void* argInCallback)
{
    OnImageProcessedCallback = argInCallback;
}


void* GetImageBuffer()
{
    return imageBufferPtr;
}

int GetDaycamImageWidth()
{
    return imageWidth;
}

int GetDaycamImageHeight()
{
    return imageHeight;
}*/
/*
ESContext esContext;
*/
void UpdateLoop ()
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

        /*if (esContext->updateFunc != NULL)
            esContext->updateFunc(esContext, deltatime);*/
    }
}
/*
void sleep_us(unsigned long argInMicrosecounds)
{
    struct timespec ts;
    ts.tv_sec = argInMicrosecounds/1000000ul;
    ts.tv_nsec = (argInMicrosecounds/1000000ul)*1000;
    nanosleep(&ts,NULL);
}*/
/*
void ThermalCameraOnImageReceived(int argInHikImageWidth, int argInHikImageHeight,void* argInImageData)
{
    pthread_mutex_lock(&lucidCameraMut);
    OnThermalImageReceived(argInHikImageWidth,argInHikImageHeight,(acBuffer*)argInImageData);
    pthread_mutex_unlock(&lucidCameraMut);
}*/
/*
void DrawLoop()
{
    char ImageBuffer[esContext.width*esContext.height*4];
    imageBufferPtr = &ImageBuffer[0];
    imageWidth = esContext.width;
    imageHeight = esContext.height;
    int i =0;
    while(1)
    {
        i++;
        pthread_mutex_lock(&lucidCameraMut);
        if (esContext.drawFunc != NULL)
        {esContext.drawFunc(&esContext);}
        pthread_mutex_unlock(&lucidCameraMut);

        eglSwapBuffers(esContext.eglDisplay, esContext.eglSurface);
        glReadPixels(0,0,esContext.width, esContext.height,GL_RGBA,GL_UNSIGNED_BYTE,&ImageBuffer);
        if(OnImageProcessedCallback!=NULL)
        {
            OnImageProcessedCallback();
        }
        if(i==250)
        {
            SaveSimpleImage(ImageBuffer,esContext.width, esContext.height,32,  "Test.png");
        }
        sleep_us(30);
    }
}*/

///
//  Global extern.  The application must declsare this function
//  that runs the application.
//
extern int esMain( ESContext *esContext );


/*
static void * _draw_thread(void * data);
static pthread_t draw_thread_id;

void * _draw_thread(void * data)
{
    DrawLoop();

    return NULL;
}*/

/*
int InitializeDrawThread(void * data)
{
    if(pthread_create(&draw_thread_id, NULL, _draw_thread, data))
    {
        return 0;
    }

    return 1;
}*/

/*
int main(int argc, char *argv[])
{
    MainUtil ();
    UpdateLoop ();
}*/

static acSystem hSystem = NULL;

//int main(int argc, char *argv[])
int MainUtil()
{

   //memset ( &esContext, 0, sizeof( esContext ) );

   //InitRendering(&esContext);
    //static acSystem hSystem;
    //AC_ERROR err = AC_ERR_SUCCESS;
    //err = acOpenSystem(&hSystem);
   InitPeripherals();
   /*
   if ( esMain ( &esContext ) != GL_TRUE )
      return 1;*/

    //InitializeDrawThread(&esContext);
    //UpdateLoop ( &esContext );

   //while(1);
   return 0;
}

/*
void Shutdown()
{
    if ( esContext.shutdownFunc != NULL )
       esContext.shutdownFunc ( &esContext );

    if ( esContext.userData != NULL )
       free ( esContext.userData );
}*/
