#ifndef SAVEUSERDATA_H
#define SAVEUSERDATA_H

#include <QDateTime>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <istream>
#include <string.h>

extern QString userPasswordParameter;
extern QString maintenancePasswordParameter;
extern QString brightnessValueParameter;
extern QString contrastValueParameter;
extern QString deeValueParameter;
extern QString deeModeParameter;
extern QString reticleXaxisPositionParameter;
extern QString reticleYaxisPositionParameter;
extern QString reticleXaxisOffsetParameter;
extern QString reticleYaxisOffsetParameter;
extern QString coordinateSystemParameter;
extern QString dateAndTime;
extern QString coordinateTypeParameter;

class SaveLartosUserData
{
private:
  void jsonFormater(QJsonObject jsonObjectValue);

  void saveJsonFile(QJsonDocument jsonDocumentValue);

  QJsonObject obj;

public:
  SaveLartosUserData();
  ~SaveLartosUserData();

  void readJsonFromFile();

  void setCoordinateZoneParameter(QString coordinate_zone);
  void setUserPasswordParameter(QString user_password);
  void setMaintenancePasswordParameter(QString maintenance_password);
  void setBrightnessValueParameter(int brightness_value);
  void setContrastValueParameter(int contrast_value);
  void setCoordinateSystemParameter(QString coordinate_system);
  void setCoordinateTypeParameter(QString coordinate_type);
  void setDeeModeParameter(bool dde_mode);
  void setDeeValueParameter(int dde_value);
  void setReticlePositionXaxisParameter(float reticle_Xpos);
  void setReticlePositionYasisParameter(float reticle_Ypos);
  void setReticleOffsetXaxisParameter(int reticle_Xoffset);
  void setReticleOffsetYaxisParameter(int reticle_Yoffset);
  QString getReticlePositionYasisParameter();
  QString getUserPasswordParameter();
  QString getMaintenancePasswordParameter();
  int getBrightnessValueParameter();
  int getContrastValueParameter();
  QString getCoordinateSystemParameter();
  QString getCoordinateZoneParameter();
  QString getCoordinateTypeParameter();
  bool getDeeModeParameter();
  int getDeeValueParameter();
  QString getReticlePositionXasisParameter();
  QString getReticleOffsetXaxisParameter();
  QString getReticleOffsetYaxisParameter();
  void defaultValueSet();
  bool isJsonExist();

  void removeJson();
};

#endif //SAVEUSERDATA_H
