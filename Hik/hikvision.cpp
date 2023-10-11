#include "Hik/hikvision.h"
#include <QDebug>
#include <QString>
#include <QChar>
#include <Qt>
#include "Hik/HCNetSDK.h"
#include <QMessageBox>
#include <variables.h>
extern "C"
{
    #include "Periph/HikCurlWrapper.h"
}


QString CURL_HEADER   =       "curl --digest -X PUT -H Content-Type: text/xml -d ";

QString PALETTE_URL   =       "/ISAPI/Image/channels/1/Palettes";
QString DDE_URL       =       "/ISAPI/Image/channels/1/DDE";
QString ZOOM_URL      =       "/ISAPI/Image/channels/1/digitalZoom";
QString COLOR_URL     =       "/ISAPI/Image/channels/1/color";
QString NUC_URL       =       "/ISAPI/Image/channels/1/ManualShutterCorrect";

QString WHITE_HOT     =       "WhiteHot";
QString BLACK_HOT     =       "BlackHot";

QString ip_address    =       ID_IP;
QString password      =       ID_PASSWORD;
QString username      =       ID_USER;


QString HikVision::generateLink(QString parameterUri){
    QString command = "http://" + username + ":" + password + "@" + ip_address + parameterUri;
    return command;
}

QString HikVision::rtspLink(){
    return "rtsp://" + username + ":" + password + "@" + ip_address + ":554/Streaming/channels/1";
}

QString HikVision::httpLink(){
    return "http://" + username + ":" + password + "@" + ip_address + "/Streaming/channels/1/httppreview";
}

void HikVision::executeSystemCommand(QString command){
    QProcess process;
    QString cmd;
    if(!command.contains("curl",Qt::CaseSensitive)){
        cmd = CURL_HEADER + command;
        //process.execute(cmd);
    } else {
        cmd = command;
        //process.execute(cmd);
    }
}


void HikVision::doNuc()
{
    HikCurlWrapDoNUC();
}

QString HikVision::setZoomFactor(int value){
    QString stringValue = QString::number(value);
    QString zoom = "<DigitalZoom><ZoomRatio>" + stringValue + "x</ZoomRatio></DigitalZoom>";
    return zoom;
}

 QString setPalette(QString param){
    QString palette = "<Palettes><mode>" + param + "</mode></Palettes>";
    return palette;
}

void HikVision::makeZoom(int zoomFactor)
{
    HikCurlWrapSetZoom(zoomFactor);
}

void HikVision::setPolarity(int value)
{
    HikCurlWrapSetPolarity(value);
}

void HikVision::setBrightness(int value)
{

   HikCurlWrapSetBrightness(value);
}

void HikVision::setContrast(int value)
{

  HikCurlWrapSetContrast(value);
}

void HikVision::setDde(int value){

  QString stringValue = QString::number(value);
  QString dde = "<DDE><mode>general</mode><GeneralMode><enhanceLevel>" + stringValue + "</enhanceLevel></GeneralMode></DDE>";
  QString ddeCmd = dde + " " + generateLink(DDE_URL);

  executeSystemCommand(ddeCmd);
}

void HikVision::setDdeMode(bool mode){

   QString modeCmd;

   if(mode){
      modeCmd = "general";
   } else {
      modeCmd = "close";
   }

   QString dde = "<DDE><mode>" + modeCmd + "</mode></DDE>";

   QString ddeModeCmd = dde + " " + generateLink(DDE_URL);
}

