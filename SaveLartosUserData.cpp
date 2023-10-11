#include "SaveLartosUserData.h"

QString userPasswordParameter;
QString maintenancePasswordParameter;
QString brightnessValueParameter;
QString contrastValueParameter;
QString deeValueParameter;
QString deeModeParameter;
QString reticleXaxisPositionParameter;
QString reticleYaxisPositionParameter;
QString reticleXaxisOffsetParameter;
QString reticleYaxisOffsetParameter;
QString coordinateSystemParameter;
QString dateAndTime;


SaveLartosUserData::SaveLartosUserData()
{
    readJsonFromFile();
}

SaveLartosUserData::~SaveLartosUserData(){}

void SaveLartosUserData::removeJson()
{
    QFile fileUserSettings("/home/pi/LartosUserSettings.json");
    if(fileUserSettings.exists()){
    fileUserSettings.remove();
    }
}

void SaveLartosUserData::jsonFormater(QJsonObject jsonObjectValue){
    QJsonDocument jsonDocument(jsonObjectValue);
    QString jsonString = jsonDocument.toJson(QJsonDocument::Indented);
    saveJsonFile(jsonDocument);
    qDebug() << jsonString.toStdString().c_str();
}

void SaveLartosUserData::saveJsonFile(QJsonDocument doc){
    QFile fileUserSettings("/home/pi/LartosUserSettings.json");
    QByteArray bytes = doc.toJson( QJsonDocument::Indented );
    if( fileUserSettings.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) )
    {
        QTextStream iStream( &fileUserSettings );
        iStream.setCodec( "utf-8" );
        iStream << bytes;
        fileUserSettings.close();
    }
}

bool SaveLartosUserData::isJsonExist(){
     QFile fileUserSettings("/home/pi/LartosUserSettings.json");
     if(fileUserSettings.exists()){
         return true;
     } else {
         return false;
     }
}

void SaveLartosUserData::defaultValueSet(){
    obj["user_password"] = "1971";
    obj["maintenance_password"] = "1234567890";
    obj["brightness_value"] = QString::number(127);
    obj["contrast_value"] = QString::number(127);
    obj["dde_mode"] = false;
    obj["dde_value"] = QString::number(127);
    jsonFormater(obj);
}

void SaveLartosUserData::readJsonFromFile(){
    QFile fileUserSettings("/home/pi/LartosUserSettings.json");
    if(fileUserSettings.exists()){
        if( fileUserSettings.open( QIODevice::ReadOnly ) )
        {
            QByteArray bytes = fileUserSettings.readAll();
            fileUserSettings.close();

            QJsonParseError jsonError;
            QJsonDocument userParameters = QJsonDocument::fromJson( bytes, &jsonError );
            if( userParameters.isNull())
            {
                qDebug() << "Parse failed";
                return ;
            }
            if(userParameters.isObject()){
                obj = userParameters.object();
            }
        }
    }
}

void SaveLartosUserData::setUserPasswordParameter(QString user_password){
    obj["user_password"] = user_password;
    jsonFormater(obj);
}

QString SaveLartosUserData::getUserPasswordParameter(){
    QString value = obj.value("user_password").toString();
    if(value.isEmpty()){
        return "1971";
    }
     qDebug() << "Debug: " + value;
    return value;
}

void SaveLartosUserData::setMaintenancePasswordParameter(QString maintenance_password){
    obj["maintenance_password"] = maintenance_password;
    jsonFormater(obj);
}

QString SaveLartosUserData::getMaintenancePasswordParameter(){
    QString value = obj.value("maintenance_password").toString();

    if(value.isEmpty()){
        value = "1234567890";
    }
    qDebug() << "Debug: " + value;
    return value;
}

void SaveLartosUserData::setBrightnessValueParameter(int brightness_value){
    obj["brightness_value"] = QString::number(brightness_value);
    jsonFormater(obj);
}

int SaveLartosUserData::getBrightnessValueParameter(){
    int value = obj.value("brightness_value").toInt(127);
    qDebug() << "Debug: " + value;
    return value;
}

void SaveLartosUserData::setContrastValueParameter(int contrast_value){
    obj["contrast_value"] = QString::number(contrast_value);
    jsonFormater(obj);
}

int SaveLartosUserData::getContrastValueParameter(){
    int value = obj.value("contrast_value").toInt(127);
    qDebug() << "Debug: " + value;
    return value;
}

void SaveLartosUserData::setCoordinateSystemParameter(QString coordinate_system){
    obj["coordinate_system"] = coordinate_system;
    jsonFormater(obj);
}

QString SaveLartosUserData::getCoordinateSystemParameter(){
    QString value = obj.value("coordinate_system").toString();
    if(value.isEmpty()){
        value="wgs";
    }
    qDebug() << "Debug: " + value;
    return value;
}

void SaveLartosUserData::setCoordinateZoneParameter(QString coordinate_zone){
    obj["coordinate_zone"] = coordinate_zone;
    jsonFormater(obj);
}

QString SaveLartosUserData::getCoordinateZoneParameter(){
    QString value = obj.value("coordinate_zone").toString();
    if(value.isEmpty()){
        value = "35";
    }
    qDebug() << "Debug: " + value;
    return value;
}

void SaveLartosUserData::setCoordinateTypeParameter(QString coordinate_type){
    obj["coordinate_type"] = coordinate_type;
    jsonFormater(obj);
}

QString SaveLartosUserData::getCoordinateTypeParameter(){
    QString value = obj.value("coordinate_type").toString();
    if(value.isEmpty()){
        value = "utm";
    }
    qDebug() << "Debug: " + value;
    return value;
}

void SaveLartosUserData::setDeeModeParameter(bool dde_mode){
    obj["dde_mode"] = dde_mode;
    jsonFormater(obj);
}

bool SaveLartosUserData::getDeeModeParameter(){
    bool value = obj.value("dde_mode").toBool();
    qDebug() << "Debug: " + value;
    return value;
}

void SaveLartosUserData::setDeeValueParameter(int dde_value){
    obj["dde_value"] = QString::number(dde_value);
    jsonFormater(obj);
}

int SaveLartosUserData::getDeeValueParameter(){
    int value = obj.value("dde_value").toInt(127);
    qDebug() << "Debug: " + value;
    return value;
}

void SaveLartosUserData::setReticlePositionXaxisParameter(float reticle_Xpos){
    obj["reticle_Xpos"] = QString::number(reticle_Xpos);
    //char str[32] = "";
    //sprintf(str, "%.5f",reticle_Xpos);
    //obj["reticle_Xpos"] = str;
    jsonFormater(obj);
}

QString SaveLartosUserData::getReticlePositionXasisParameter(){
    QString value = obj.value("reticle_Xpos").toString();
    if(value.isEmpty()){
        value = "0";
    }
    qDebug() << "Debug: " + value;
    return value;
}

void SaveLartosUserData::setReticlePositionYasisParameter(float reticle_Ypos){
    obj["reticle_Ypos"] = QString::number(reticle_Ypos);
    jsonFormater(obj);
}

QString SaveLartosUserData::getReticlePositionYasisParameter(){
    QString value = obj.value("reticle_Ypos").toString();
    if(value.isEmpty()){
        value = "0";
    }
    qDebug() << "Debug: " + value;
    return value;
}

void SaveLartosUserData::setReticleOffsetXaxisParameter(int reticle_Xoffset){
    obj["reticle_Xoffset"] = QString::number(reticle_Xoffset);
    jsonFormater(obj);
}

QString SaveLartosUserData::getReticleOffsetXaxisParameter(){
    QString value = obj.value("reticle_Xoffset").toString();
    if(value.isEmpty()){
        value = "0";
    }
    qDebug() << "Debug: " + value;
    return value;
}

void SaveLartosUserData::setReticleOffsetYaxisParameter(int reticle_Yoffset){
    obj["reticle_Yoffset"] = QString::number(reticle_Yoffset);
    jsonFormater(obj);
}

QString SaveLartosUserData::getReticleOffsetYaxisParameter(){
    QString value = obj.value("reticle_Yoffset").toString();
    if(value.isEmpty()){
        value = "0";
    }
    qDebug() << "Debug: " + value;
    return value;
}



