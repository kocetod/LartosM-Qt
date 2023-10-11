#include "pointobj.h"

PointObj::PointObj()
{

}

PointObj::~PointObj(){}


void PointObj::setPointIndex(QString index){
  this->pointIndex = index;
}

void PointObj::setPointName(QString name){
  this->pointName = name;
}

void PointObj::setPointLattitude(QString lat){
  this->pointLat = lat;
}

void PointObj::setPointLongitude(QString lng){
  this->pointLng = lng;
}

void PointObj::setPointAltitude(QString alt){
  this->pointAlt = alt;
}

QString PointObj::getPointIndex(){
  return pointIndex;
}

QString PointObj::getPointName(){
  return pointName;
}

QString PointObj::getPointLattitude(){
  return pointLat;
}

QString PointObj::getPointLongitude(){
  return pointLng;
}

QString PointObj::getPointAltitude(){
  return pointAlt;
}
