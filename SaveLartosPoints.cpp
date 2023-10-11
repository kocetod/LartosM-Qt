#include "SaveLartosPoints.h"

#include <QFile>
#include <QJsonArray>

QJsonObject objPoint;
QJsonDocument pointParameters;

SaveLartosPoint::SaveLartosPoint(){}

SaveLartosPoint::~SaveLartosPoint(){}

void SaveLartosPoint::setPointData(QHash<QString, LartosPointObj> hash){
  QJsonObject point;
  QJsonObject pointChild;

  int indexPoint = 1;

  foreach (LartosPointObj currentPoint, hash) {
      pointChild["point_name"] = currentPoint.getLartosPointName();
      pointChild["point_lattitude"] = currentPoint.getLartosPointLattitude();
      pointChild["point_longitude"] = currentPoint.getLartosPointLongitude();
      pointChild["point_altitude"] = currentPoint.getLartosPointAltitude();
      pointChild["point_typeCoord"] = currentPoint.getCoordinatesType();

      point["point_" + QString::number(indexPoint)] = pointChild;
      indexPoint++;
    }

  SaveLartosPoint::jsonFormater(point);
}

void SaveLartosPoint::jsonFormater(QJsonObject objPoint){
  QJsonDocument doc(objPoint);
  QString jsonString = doc.toJson(QJsonDocument::Indented);
  qDebug() << jsonString.toStdString().c_str();

  saveJasonFile(doc);
}

void SaveLartosPoint::saveJasonFile(QJsonDocument doc){
  QByteArray bytes = doc.toJson( QJsonDocument::Indented );
  QFile filePoint("/home/pi/points.json");
  if( filePoint.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) )
    {
      QTextStream iStream( &filePoint );
      iStream.setCodec( "utf-8" );
      iStream << bytes;
      filePoint.close();
    }
}

QHash<QString, LartosPointObj> SaveLartosPoint::readPointFromFile(){
  LartosPointObj point;
  QFile filePoint("/home/pi/points.json");
  QHash<QString, LartosPointObj> hash;

  int index;
  if( filePoint.open( QIODevice::ReadOnly ) )
    {
      QByteArray bytes = filePoint.readAll();
      filePoint.close();
      QJsonParseError jsonError;
      pointParameters = QJsonDocument::fromJson( bytes, &jsonError );
      if( jsonError.error != QJsonParseError::NoError )
        {
          // return 0 ;
        }
      if( pointParameters.isObject() )
        {
          index = 1;

          objPoint = pointParameters.object();

          foreach(QJsonValue val, objPoint ) {
              QJsonObject valObj = val.toObject();
              point.setLartosPointName(valObj.take("point_name").toString());
              point.setLartosPointLattitude(valObj.take("point_lattitude").toString());
              point.setLartosPointLongitude(valObj.take("point_longitude").toString());
              point.setLartosPointAltitude(valObj.take("point_altitude").toString());
              point.setCoordinatesType(valObj.take("point_typeCoord").toString());


              hash.insert(point.getLartosPointName(), point);
            }
        }
    }
  return hash;
}
