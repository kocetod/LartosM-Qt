#ifndef IMAGEBUFFER_H
#define IMAGEBUFFER_H

#include <QMutex>
#include <QQueue>
#include <QSemaphore>
#include <QImage>

class ImageBuffer
{
public:
    ImageBuffer(int size, bool dropFrame);
    void addFrame(const QImage& frame);
    QImage getFrame();
    void clearBuffer();
    int getSizeOfImageBuffer();
    bool bufferError;
private:
    QMutex imageQueueProtect;
    QQueue<QImage> imageQueue;
    QSemaphore *freeSlots;
    QSemaphore *usedSlots;
    QSemaphore *clearBuffer1;
    QSemaphore *clearBuffer2;
    int bufferSize;
    bool dropFrame;
};

#endif // IMAGEBUFFER_H
