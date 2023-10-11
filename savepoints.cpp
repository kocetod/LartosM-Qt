#include "savepoints.h"

#include <QFile>
#include <QJsonArray>
#include "pointobj.h"

QJsonObject objPoint;
QJsonDocument pointParameters;
QFile filePoint(QDir::homePath() + "/points.json");

SavePoint::SavePoint(){}

SavePoint::~SavePoint(){}

void SavePoint::setPoint(QHash<QString, PointObj> hash){
  QJsonObject point;
  QJsonObject pointChild;

  int indexPoint = 1;

  foreach (PointObj currentPoint, hash) {
      pointChild["point_name"] = currentPoint.getPointName();
      pointChild["point_lattitude"] = currentPoint.getPointLattitude();
      pointChild["point_longitude"] = currentPoint.getPointLongitude();
      pointChild["point_altitude"] = currentPoint.getPointAltitude();

      point["point_" + QString::number(indexPoint)] = pointChild;
      indexPoint++;
    }

  SavePoint::jsonFormater(point);
}

void SavePoint::jsonFormater(QJsonObject objPoint){
  QJsonDocument doc(objPoint);
  QString jsonString = doc.toJson(QJsonDocument::Indented);
  qDebug() << jsonString.toStdString().c_str();

  saveJasonFile(doc);
}

void SavePoint::saveJasonFile(QJsonDocument doc){
  QByteArray bytes = doc.toJson( QJsonDocument::Indented );

  if( filePoint.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) )
    {
      QTextStream iStream( &filePoint );
      iStream.setCodec( "utf-8" );
      iStream << bytes;
      filePoint.close();
    }
}

QHash<QString, PointObj> SavePoint::readPointFromFile(){
  PointObj point;
  QHash<QString, PointObj> hash;

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
              point.setPointName(valObj.take("point_name").toString());
              point.setPointLattitude(valObj.take("point_lattitude").toString());
              point.setPointLongitude(valObj.take("point_longitude").toString());
              point.setPointAltitude(valObj.take("point_altitude").toString());

              hash.insert(point.getPointName(), point);
            }
        }
    }
  return hash;
}
