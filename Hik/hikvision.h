#ifndef HIKVISION_H
#define HIKVISION_H

#include <QProcess>
#include "Hik/HCNetSDK.h"
#include <QFrame>

class HikVision
{
public:
    QString generateLink(QString parameterUri);

    QString rtspLink();

    QString httpLink();

    void executeSystemCommand(QString command);

    void SendHttpRequest(QString argInUrl, QString argInCommand);

    void doNuc();

    void setDde(int value);

    void setDdeMode(bool mode);

    void setBrightness(int value);

    void setContrast(int value);

    QString setZoomFactor(int value);

    void makeZoom(int zoomFactor);

    void setPolarity(int value);

    void initHCNetSDK();

    void login();


};


#endif // HIKVISION_H
