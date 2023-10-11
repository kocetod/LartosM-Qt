#ifndef SAVEPOINTS_H
#define SAVEPOINTS_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <istream>
#include <QVariantHash>
#include "LartosPointObj.h"

class SaveLartosPoint
{
public:
  SaveLartosPoint();
  ~SaveLartosPoint();

  void setPointData(QHash<QString, LartosPointObj> hash);

  QHash<QString, LartosPointObj> readPointFromFile();

private:

  LartosPointObj pointObj;

  void jsonFormater(QJsonObject obj);

  void saveJasonFile(QJsonDocument doc);

};

#endif // SAVEPOINTS_H
