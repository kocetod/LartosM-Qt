#include "ProcessingThread.h"
#include <QDebug>
#include "global.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "expanded.h"
#include "ui_expanded.h"

#include "tasks.h"
#include "ui_tasks.h"

#include "menu.h"
#include "ui_menu.h"

#include "hikvision.h"
#include "variables.h"

#include <QDesktopWidget>
#include <QScreen>
#include "global.h"

#include "Controller.h"


extern "C"
{
    #include "Periph/HikCameraDraw.h"
    #include "Periph/LucidCamera.h"
}

ProcessingThread::ProcessingThread(int inputSourceWidth, int inputSourceHeight) : QThread(),
                                   inputSourceWidth(inputSourceWidth),
                                   inputSourceHeight(inputSourceHeight)
{
    stopped1=false;
}

ProcessingThread::~ProcessingThread()
{
}

int imageNotProvided = 0;
void ProcessingThread::run()
{
    while(1)
    {
        if((ThermalIsRunning()==true)&&(DaycamDrawIsRunning()==false))
        {
            imageNotProvided++;
            if(thermController!=NULL)
            {
                if(thermController->hikCurrentState==Controller::HIK_STREAM)
                {
                    QImage convertedFrame;
                    currentFrame=imageBuffer->getFrame();
                    if(currentFrame.isNull()==false)
                    {
                        convertedFrame = currentFrame.convertToFormat(QImage::Format_RGBA8888);
                        NightImageReceivedCallback(convertedFrame.width(),convertedFrame.height(),(void*)(convertedFrame.bits()));
                        imageNotProvided = 0;
                    }
                }
            }

            if(imageNotProvided>50)
            {
                NightImageReceivedCallback(0,0,(void*)NULL);
            }
        }

        if((DaycamDrawIsRunning()==true)&&(ThermalIsRunning()==false))
        {
            DrawDay();
        }

        if(DaycamDrawIsRunning()||ThermalIsRunning())
        {
            QImage image((unsigned char*)GetLucidImageBuffer(), GetDaycamImageWidth(), GetDaycamImageHeight(), QImage::Format_RGBA8888, NULL, NULL );
            if(image.isNull()==false)
            {
                image = image.mirrored(false,true);
                QPixmap pixmap;
                pixmap = pixmap.fromImage(image.scaled(currentVideoPanelX,currentVideoPanelY,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
                if(currentVideoPanel!=NULL)
                {
                    if(pixmap.isNull()==false)
                    {
                        emit newFrame(pixmap);
                        //currentVideoPanel->setPixmap(pixmap);
                    }
                }
            }
        }
    }
    qDebug() << "Stopping processing thread...";
}

void ProcessingThread::stopProcessingThread()
{
    stoppedMutex.lock();
    stopped=true;
    stoppedMutex.unlock();
}


int ProcessingThread::getCurrentSizeOfBuffer()
{
    return currentSizeOfBuffer;
}
