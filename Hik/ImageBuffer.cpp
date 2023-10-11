#include "ImageBuffer.h"
#include <QDebug>

ImageBuffer::ImageBuffer(int bufferSize, bool dropFrame) : bufferSize(bufferSize), dropFrame(dropFrame)
{
    bufferError = false;
    // Semaphore initializations
    freeSlots = new QSemaphore(bufferSize);
    usedSlots = new QSemaphore(0);
    clearBuffer1 = new QSemaphore(2);
    clearBuffer2 = new QSemaphore(2);
    // Save value of dropFrame to private member

    this->dropFrame=dropFrame;
}
void ImageBuffer::addFrame(const QImage& frame)
{
    if(clearBuffer1->tryAcquire(1,500)==true)
    {
        if(freeSlots->tryAcquire()==true)
        {
            if(imageQueueProtect.tryLock(500)==true)
            {
                imageQueue.enqueue(frame);
                usedSlots->release();
                imageQueueProtect.unlock();
            }
            else
            {
                bufferError=true;
            }
        }
        clearBuffer1->release();
    }
    else
    {
        bufferError=true;
    }
}
/*if(dropFrame==true)
{
if(freeSlots->tryAcquire())
{
    imageQueueProtect.lock();
        imageQueue.enqueue(frame);
    imageQueueProtect.unlock();
    usedSlots->release();
}
}
else
{
    freeSlots->acquire();
    imageQueueProtect.lock();
        imageQueue.enqueue(frame);
    imageQueueProtect.unlock();
    usedSlots->release();
}*/

QImage ImageBuffer::getFrame()
{
    QImage tempFrame;
    if(clearBuffer2->tryAcquire(1,500)==true)
    {
        if(usedSlots->tryAcquire(imageQueue.size(),500)==true)
        {
            if(imageQueueProtect.tryLock(500)==true)
            {
                if(imageQueue.count()>0)
                {
                    tempFrame=imageQueue.dequeue();
                    freeSlots->release();
                }
                imageQueueProtect.unlock();
            }
            else
            {
                bufferError=true;
            }
        }
        else
        {
            bufferError=true;
        }
        clearBuffer2->release();
    }
    else
    {
        bufferError=true;
    }

    return tempFrame;
}

void ImageBuffer::clearBuffer()
{
    if(imageQueue.size()!=0)
    {
        if(clearBuffer1->tryAcquire(1,500)==true)
        {
            if(clearBuffer2->tryAcquire(1,500)==true)
            {
                freeSlots->release(imageQueue.size());
                if(freeSlots->tryAcquire(bufferSize,500)==true)
                {
                    if(usedSlots->tryAcquire(imageQueue.size(),500)==true)
                    {
                        imageQueue.clear();
                    }
                    else
                    {
                        bufferError=true;
                    }
                    freeSlots->release(bufferSize);
                }
                else
                {
                    bufferError=true;
                }
                clearBuffer2->release();
            }
            else
            {
                bufferError=true;
            }
            clearBuffer1->release();
        }
        else
        {
            bufferError=true;
        }
    }
    else
    {
        qDebug() << "WARNING: Could not clear image buffer: already empty.";
    }
}

int ImageBuffer::getSizeOfImageBuffer()
{
    return imageQueue.size();
}

