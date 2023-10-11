#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "CaptureThread.h"
#include "ProcessingThread.h"
#include "ImageBuffer.h"
#include <QDialog>
#include <QImage>
#include <QTimer>

class Controller : public QObject
{
public:
  Controller();
  ~Controller();
  //ImageBuffer *imageBuffer;
  ProcessingThread *processingThread;
  CaptureThread *captureThread;
  bool connectToCamera(int,int);
  void StartImageProcessing();
  //void stopCaptureThread();
  //void stopProcessingThread();
  //void deleteCaptureThread();
  //void deleteProcessingThread();
  //void run();
  void clearImageBuffer();
  void deleteImageBuffer();

  struct timeval hikTprevFrame, hikTthisFrame;
  float hikDeltatime;
  void HikOnUpdate(float argInDeltaTime);
  enum HIK_DEVICE_STATES
  {
      HIK_NOT_CONNECTED,
      HIK_CONNECT,
      HIK_WAIT_STREAM,
      HIK_STREAM,
      HIK_TURN_OFF,
      HIK_OFF,
      HIK_DEVICE_STATES_COUNT
  };
  enum HIK_DEVICE_STATES hikCurrentState;

private:
  int imageBufferSize;
  void HikStatemachine(float argInDeltaTime);
  void HikNotConnected(float argInDeltaTime);
  void HikConnectToCamera(float argInDeltaTime);
  void HikWaitStream(float argInDeltaTime);
  void HikStream(float argInDeltaTime);
  void HikTurnOff(float argInDeltaTime);
  void HikOff(float argInDeltaTime);
  void (Controller::*HikStates[Controller::HIK_DEVICE_STATES_COUNT])(float);
  int sourceWidth = 0;
  int sourceHeight = 0;
  void StartThermalCameraCapture();
  void SetThermalCameraParameters();
  HikVision* hikVision;
  double connectTimeout;
  double startCaptureTimeout;
 /*private slots:
  void HikOnUpdateHandler(size_t argInTimerId, void * arginData);*/
};

extern Controller *thermController;

#endif // CONTROLLER_H
