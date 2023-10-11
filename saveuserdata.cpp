#include "saveuserdata.h"


QString userPassword;
QString maintenancePassword;
QString brightnessValue;
QString contrastValue;
QString deeValue;
QString deeMode;
QString reticleXaxisPosition;
QString reticleYaxisPosition;
QString coordinateSystem;
QString dateAndTime;
QString panSpeedFactor;
QString tiltSpeedFactor;

QJsonObject obj;
QJsonDocument userParameters;
QFile file(QDir::homePath() + "/1.json");

saveUserData::saveUserData()
{
  //QFile save_file("./tempwpf");
  //if(save_file.open(QIODevice::WriteOnly)){
  //    QJsonDocument json_doc(json);
  //    save_file.write(obj);
  //}
}

saveUserData::~saveUserData()
{
  //QFile save_file("./tempwpf");
  //if(save_file.open(QIODevice::WriteOnly)){
  //    QJsonDocument json_doc(json);
  //    save_file.write(obj);
  //}
}

void saveUserData::jsonFormater(QJsonObject obj){
  QJsonDocument doc(obj);
  QString jsonString = doc.toJson(QJsonDocument::Indented);
  qDebug() << jsonString.toStdString().c_str();
}

void saveUserData::saveJasonFile(QJsonDocument doc){
  QByteArray bytes = doc.toJson( QJsonDocument::Indented );

  if( file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) )
    {
      QTextStream iStream( &file );
      iStream.setCodec( "utf-8" );
      iStream << bytes;
      file.close();
    }

}

void saveUserData::readJsonFromFile(){
  if( file.open( QIODevice::ReadOnly ) )
    {
      QByteArray bytes = file.readAll();
      file.close();
      QJsonParseError jsonError;
      userParameters = QJsonDocument::fromJson( bytes, &jsonError );
      if( jsonError.error != QJsonParseError::NoError )
        {
          return ;
        }
      if( userParameters.isObject() )
        {
          obj = userParameters.object();
        }
    }
}

void saveUserData::setUserPassword(QString value){

  obj["user_password"] = value;
  jsonFormater(obj);

}

void saveUserData::setMaintenancePassword(QString value){
  obj["maintenance_password"] = value;
  jsonFormater(obj);
}

void saveUserData::setDateTime(QDateTime value){
  obj["date_and_time"] = value.toString("yyyy-MM-dd-hh-ss");
  jsonFormater(obj);
}

void saveUserData::setBrightnessValue(int value){
    obj["brightness_value"] = QString::number(value);
    jsonFormater(obj);
}

void saveUserData::setContrastValue(int value){
    obj["contrast_value"] = QString::number(value);
    jsonFormater(obj);
}

void saveUserData::setCoordinateSystem(int byte){
    obj["coordinate_system"] = QString::number(byte);
    jsonFormater(obj);
}

void saveUserData::setDeeMode(bool flag){
    obj["dde_mode"] = QString::number(flag);
    jsonFormater(obj);
}

void saveUserData::setDeeValue(int value){
    obj["dde_value"] = QString::number(value);
    jsonFormater(obj);
}

void saveUserData::setPanSpeed(long value){
    obj["pan_speed"] = QString::number(value);
    jsonFormater(obj);
}

void saveUserData::setTiltSpeed(long value){
    obj["tilt_speed"] = QString::number(value);
    jsonFormater(obj);
}

void saveUserData::setReticlePositionXaxis(int value){
    obj["reticle_Xpos"] = QString::number(value);
    jsonFormater(obj);
}

void saveUserData::setReticlePositionYasis(int value){
    obj["reticle_Ypos"] = QString::number(value);
    jsonFormater(obj);
}



