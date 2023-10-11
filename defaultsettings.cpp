#include "defaultsettings.h"

DefaultSettings::DefaultSettings()
{

}

void DefaultSettings::readJsonFromFile(){
    QFile fileUserSettings("/home/pi/LartosUserSettingsDef.json");
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

QString DefaultSettings::getUserPasswordParameter(){
    QString value = obj.value("user_password").toString();
    qDebug() << value;
    return value;
}

int SaveLartosUserData::getContrastValueParameter(){
    QString value = obj.value("contrast_value").toString();
    qDebug() << value;
    return value.toInt();
}

int SaveLartosUserData::getBrightnessValueParameter(){
    QString value = obj.value("brightness_value").toString();
    qDebug() << value;
    return value.toInt();
}

QString SaveLartosUserData::getDeeValueParameter(){
    QString value = obj.value("dde_value").toString();
    qDebug() << value;
    return value;
}

bool SaveLartosUserData::getDeeModeParameter(){
    QString value = obj.value("dde_mode").toString();
    qDebug() << value;

    if(value.compare("true")){
       return true;
    } else {
       return false;
    }
}
