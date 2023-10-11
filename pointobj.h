#ifndef POINTOBJ_H
#define POINTOBJ_H

#include <QString>

class PointObj
{
public:
  PointObj();
  ~PointObj();

  void setPointIndex(QString index);

  void setPointName(QString name);

  void setPointLattitude(QString lat);

  void setPointLongitude(QString lng);

  void setPointAltitude(QString alt);

  QString getPointIndex();

  QString getPointName();

  QString getPointLattitude();

  QString getPointLongitude();

  QString getPointAltitude();

private:
  QString pointName;
  QString pointIndex;
  QString pointLat;
  QString pointLng;
  QString pointAlt;
};

#endif // POINTOBJ_H
