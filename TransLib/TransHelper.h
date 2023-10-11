#ifndef TRANSHELPER_H
#define TRANSHELPER_H


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include "General/CHARString.h"

//********************************************//
// Coordinate systems transform               //
//********************************************//

#define TR_VALUE_NOT_USED		0
#define TR_4283_ETRS89			7
#define TR_ETRS89_BGS2005		13
#define TR_BGS2005_LAMBERT		14
#define TR_BGS2005_WGSG1762		17
#define TR_ONE_AND_SAME			99

int remainder(int a1, int a2);

long ReturnZoneMeridian(int type_koo, int width_koo, 
						double x, double y, int *zone, double *meridian);
void blhxyz(double a, double f, double &b, double &l, double &h);
void xyzblh(double a, double f, double &x, double &y, double &z);

bool valid_koo(double x, double y, double z);
double round(double chislo, double precision);
double sqr(double chislo, int mode = 0);
double mrad(double b, double a, double f);
double nrad(double b, double a, double f);

#endif /*TRANSHELPER_H*/
