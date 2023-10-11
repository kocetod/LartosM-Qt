#include "LartosPointObj.h"

LartosPointObj::LartosPointObj(){}

LartosPointObj::~LartosPointObj(){}

void LartosPointObj::setLartosPointIndex(QString index){
  this->pointIndex = index;
}

void LartosPointObj::setLartosPointName(QString name){
  this->pointName = name;
}

void LartosPointObj::setLartosPointLattitude(QString lat){
  this->pointLat = lat;
}

void LartosPointObj::setLartosPointLongitude(QString lng){
  this->pointLng = lng;
}

void LartosPointObj::setLartosPointAltitude(QString alt){
  this->pointAlt = alt;
}

void LartosPointObj::setCoordinatesType(QString value){
  this->typeOfCoordinates = value;
}

QString LartosPointObj::getCoordinatesType(){
  return typeOfCoordinates;
}

QString LartosPointObj::getLartosPointIndex(){
  return pointIndex;
}

QString LartosPointObj::getLartosPointName(){
  return pointName;
}

QString LartosPointObj::getLartosPointLattitude(){
  return pointLat;
}

QString LartosPointObj::getLartosPointLongitude(){
  return pointLng;
}

QString LartosPointObj::getLartosPointAltitude(){
  return pointAlt;
}
