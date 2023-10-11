#ifndef SAVEUSERDATA_H
#define SAVEUSERDATA_H
#include <QDateTime>
#include <qstring.h>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <istream>

extern QString userPassword;
extern QString maintenancePassword;
extern QString brightnessValue;
extern QString contrastValue;
extern QString deeValue;
extern QString deeMode;
extern QString reticleXaxisPosition;
extern QString reticleYaxisPosition;
extern QString coordinateSystem;
extern QString dateAndTime;
extern QString panSpeedFactor;
extern QString tiltSpeedFactor;

class saveUserData : public QObject
{
  Q_OBJECT
private:

  void jsonFormater(QJsonObject obj);

  void saveJasonFile(QJsonDocument doc);

  void readJsonFromFile();
public:

  saveUserData();
~saveUserData();

  void setUserPassword(QString value);

  void setMaintenancePassword(QString value);

  void setBrightnessValue(int value);

  void setContrastValue(int value);

  void setDeeValue(int value);

  void setDeeMode(bool flag);

  void setReticlePositionXaxis(int value);

  void setReticlePositionYasis(int value);

  void setCoordinateSystem(int byte);

  void setDateTime(QDateTime value);

  void setPanSpeed(long value);

  void setTiltSpeed(long value);

};

#endif // SAVEUSERDATA_H
