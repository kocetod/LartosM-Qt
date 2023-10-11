#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

 #pragma warning(disable : 4996)

#include "TransHelper.h"
#include "General/GlobalVariables.h"


int remainder(int a1, int a2)
{
	int step;

	if(a1 < a2) return a1;
	else 
	{
		step = a1 / a2;
		return a1 - step*a2;
	}
}

//------------------------------------------------------------------------------------------------------

long ReturnZoneMeridian(int type_koo, int width_koo, double x, double y, 
						int *zone, double *meridian)
//---------------------------------------------------------
//This function return Zone from Meridian and Meridian if it is not defined
//type_koo  - Type of source coordinates                        (input)
//width_koo - Width of zone for source coordinates              (input)
//x,y       - Coordinates                                       (input)
//zone      - Zone number                                       (output)
//meridian  - Central meridian in degree (output in radians)  (input/output)
//---------------------------------------------------------
{
	long Return_Error = TRANS_NO_ERROR;
	if(type_koo == CT_XYZ_CODE || type_koo == CT_UTM_CODE) return 2; 
	//We don't process geocentric and UTM coordinates
	int mer = (int)*meridian;
	if (mer == VALUE_NOT_USED) {
		if (type_koo == CT_XY_CODE) {
			*zone = (int) (y / 1000000);
			if (*zone == 0) return TRANS_SOURCECOORDINATES_INVALID;
			if (width_koo == ZW_3DEGREE_CODE)
				*meridian = *zone * 3;
			else if (width_koo == ZW_6DEGREE_CODE)
				*meridian = *zone * 6 - 3;
		}
		else if (type_koo == CT_BL_CODE) {
			double yr = y * 180 / PI;
			if (width_koo == ZW_3DEGREE_CODE) {
				if ((yr - ((int) (yr / 3) * 3)) > 1.5)
					*meridian = (int)(yr / 3) * 3 + 3;
				else
					*meridian = (int) (yr / 3) * 3;
				*zone = ((int)fabs(*meridian)) / 3;
			}
			else if (width_koo == ZW_6DEGREE_CODE) {
				if(yr >= 0)
				{
					*meridian = (int) (yr / 6) * 6 + 3;
					*zone = ((int)(fabs(*meridian) + 3)) / 6;
				}
				else
				{
					*meridian = (int) (yr / 6) * 6 - 3;
					*zone = 31 - ((int)(fabs(*meridian) + 3)) / 6;
				}
			}
			else if(width_koo == ZW_UNKNOWN_CODE)
				return TRANS_TOWIDTH_ERROR;
		}
		*meridian = *meridian * PI / 180.0;
		Return_Error = 0;
	}
	else {
		if (width_koo == ZW_3DEGREE_CODE) 
			*zone = mer / 3;
		else if (width_koo == ZW_6DEGREE_CODE)
			*zone = (mer + 3) / 6;
		else if(width_koo == ZW_UNKNOWN_CODE)
				return TRANS_TOWIDTH_ERROR;
		*meridian = mer * PI / 180.0;
		Return_Error = 0;
	}
	return Return_Error;
}

void blhxyz(double a, double f, double &b, double &l, double &h)
{
//{Transform B, L, H -----> X, Y, Z }
	//pw p;
    double n, e2, x, y, z/*, a, f*/;

	e2 = 2 * f - sqr(f);
	n = a / sqrt(1 - e2 * sqr(sin(b)));
	x = (n + h) * cos(b) * cos(l);
	y = (n + h) * cos(b) * sin(l);
	z = (n + h - e2 * n) * sin(b);
	b = x; l = y; h = z;
}

void xyzblh(double a, double f, double &x, double &y, double &z)
{
//{Transform Y, Z -----> B, L, H }
	//pw p;
    double n, e2, tb, d, ee, tb1, c/*, a, f*/;

	e2 = 2 * f - sqr(f);
	ee = 1 / (1 - e2);
	c = a / (1 - f);
	d = sqrt(x * x + y * y);
	tb1 = z * ee / d;
	do
	{
		tb = tb1;
		tb1 = e2 * c * tb / (d * sqrt(ee + sqr(tb))) + z / d;
	}
	while(fabs(tb - tb1) > 1.0E-15);
	y = atan(y / x);
	x = atan(tb1);
	n = a / sqrt(1 - e2 * sqr(sin(x)));
	z = d / cos(x) - n;
}

bool valid_koo(double x, double y, double z)
{
	if ((x == -1) || (y == -1) || (z == -1)) return false;
	return true;
}

double round(double chislo, double precision)
{
	CCHARString strTemp;
	strTemp.Format("1E%0lf",precision);
	precision = ConvertTextToDouble(strTemp.GetCHAR());
	int nInt = int(chislo * precision);
	return double(nInt / precision);
}

double sqr(double chislo, int mode)
{
	return pow(chislo, 2);
}

double mrad(double b, double a, double f)
{
	double er;
	er = 2 * f - sqr(f);

	return (a * (1 - er) / pow((1 - er * sqr(sin(b))), 1.5));
}

double nrad(double b, double a, double f)
{
	double er;
	er = 2 * f - sqr(f);

	return a / sqrt(1 - er * sqr(sin(b)));
}
