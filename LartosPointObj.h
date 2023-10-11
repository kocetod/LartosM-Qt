#ifndef POINTOBJ_H
#define POINTOBJ_H

#include <QObject>
#include <QString>

class LartosPointObj
{
public:
  LartosPointObj();
  ~LartosPointObj();

  void setLartosPointIndex(QString index);

  void setLartosPointName(QString name);

  void setLartosPointLattitude(QString lat);

  void setLartosPointLongitude(QString lng);

  void setLartosPointAltitude(QString alt);

  void setCoordinatesType(QString value);

  QString getCoordinatesType();

  QString getLartosPointIndex();

  QString getLartosPointName();

  QString getLartosPointLattitude();

  QString getLartosPointLongitude();

  QString getLartosPointAltitude();

  QString typeOfCoordinates;

private:
  QString pointName;
  QString pointIndex;
  QString pointLat;
  QString pointLng;
  QString pointAlt; 


};

#endif // POINTOBJ_H
