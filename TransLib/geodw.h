#ifndef GEODW_H
#define  GEODW_H

#include "General/CHARString.h"

#ifndef sign_of
#define sign_of(x)	(x != 0)?((x > 0)?1:-1):0
#endif

double rtog(double a, int format);
double gtor(double a, int format);
double arctanm(double y, double x);
double ra(double a, int b);
double exponen (double x, int e);
CCHARString gtostr(double a, int format, int decimal);
//radian = 1 - radians
//radian = 0 - decimal degree
CCHARString rtostr(double a, int format, int precision = -1);
CCHARString ConvUnits(CCHARString stra, int sformat, int tformat, int precision = -1);
int RetGMS(double dd, int &deg, int &min, double &sec);
CCHARString angletostr(double a, int from_format, int to_format, int decimal);
//radian = 1 - radians
//radian = 0 - decimal degree
double ConvertAngleFormats(double a, int from_format, int to_format);
double cotg(double b);

#endif	//GEODW_H
