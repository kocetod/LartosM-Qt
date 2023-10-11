#ifndef PROCESSINGTHREAD_H
#define PROCESSINGTHREAD_H

#include <QThread>
#include <QDialog>
#include "ImageBuffer.h"
#include "glob.h"

class ProcessingThread : public QThread
{
  Q_OBJECT
public:
    ProcessingThread(int inputSourceWidth, int inputSourceHeight);
    ~ProcessingThread();
    void stopProcessingThread();
    int getCurrentSizeOfBuffer();
private:
    int inputSourceWidth;
    int inputSourceHeight;
    int currentSizeOfBuffer;
    QImage currentFrame;
    QImage currentFrameGrayscale;
    QImage frame;
    QMutex updateMembersMutex;
    QSize frameSize;
    QPoint framePoint;
    QString name;

protected:
    void run();

signals:
    void newFrame(const QPixmap &frame);
    void newName(const QString &name);
};

#endif // PROCESSINGTHREAD_H
