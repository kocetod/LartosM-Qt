#ifndef SAVEPOINTS_H
#define SAVEPOINTS_H

#include <qstring.h>
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <istream>
#include <QVariantHash>
#include "pointobj.h"

class SavePoint : public QObject
{
  Q_OBJECT
public:
  SavePoint();
  ~SavePoint();

  void setPoint(QHash<QString, PointObj> hash);

  QHash<QString, PointObj> readPointFromFile();

private:

  PointObj pointObj;

  void jsonFormater(QJsonObject obj);

  void saveJasonFile(QJsonDocument doc);

};

#endif // SAVEPOINTS_H
