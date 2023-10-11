#include <string.h>
#ifdef _QT_
#include <stdio.h>
#include <stdlib.h>
#endif
#include <math.h>
#include "geodw.h"
#include "General/GlobalVariables.h"
#ifdef LINUX_VER
#include <stdlib.h>
#endif

double rtog(double a, int format)
{
	if (a == NO_DVALUE) return NO_DVALUE;
	double tmp, g, m, s;
	switch (format) {
	case CF_CODE_UNDEFINED:
	case CF_CODE_DMS:	
	case CF_CODE_D_M_S:
		tmp = a * 180 / PI;
		g = (int)tmp;
		m = (int)((tmp - g) * 60);
		s = (((tmp - g) * 60) - m) * 60;
		if (s + 0.0000005 >= 60)
		{
			s = 0;
			m = m + 1;
			if (m == 60)
			{
				m = 0;
				g = g + 1;
			}
		}
		if (g == 360) g = 0;
		return(g * 10000 + m * 100 + s);
	case CF_CODE_D_MS:
		tmp = a * 180 / PI;
		g = (int)tmp;
		m = (int)((tmp - g) * 60);
		s = (((tmp - g) * 60) - m) * 60;
		if (s + 0.0000005 >= 60)
		{
			s = 0;
			m = m + 1;
			if (m == 60)
			{
				m = 0;
				g = g + 1;
			}
		}
		if (g == 360) g = 0;
		return(g + m / 100 + s / 10000);
	case CF_CODE_DD:
		return a * 180 / PI;
	case CF_CODE_DM:
		tmp = a * 180 / PI;
		g = (int)tmp;
		m = (tmp - g) * 60;
		if (g == 360) g = 0;
		return(g * 100 + m);
	case CF_CODE_SECS:
		return a * 180 / PI * 3600;
	case CF_CODE_RADIANS:
		return a;
	}

	return NO_VALUE;
}

double gtor (double a, int format)
{
	double rg, rm;
	double rs,rg1,rm1;
	int znak;
	double nReturn = 0;

	if (a == NO_DVALUE) return NO_DVALUE;
	znak = sign_of(a); 
	a = fabs(a);

	switch (format) {
    case CF_CODE_UNDEFINED:
	case CF_CODE_DMS:	
	case CF_CODE_D_M_S:
		rg = (int) (a / 10000.0 + 0.00000000005);
		rg1 = a - (rg * 10000.0);
		rm = (int) (rg1 / 100.0 + 0.000000005);
		rm1 = rg1 - (rm * 100.0);
		rs = rm1 / 60.0;
		rm = (rm + rs) / 60.0;
		//return((rg + rm) * PI / 180.0 * znak);
		nReturn = ((rg + rm) * PI / 180.0 * znak);
		break;
	case CF_CODE_D_MS:
		rg = (int) a;
		rg1 = a - rg;
		rm = (int) (rg1 * 100.0);
		rm1 = rg1 - (rm / 100.0);
		rs = rm1 * 10000.0 / 60.0;
		rm = (rm + rs) / 60.0;
		//return((rg + rm) * PI / 180.0 * znak);
		nReturn = (((rg + rm) * PI) / 180.0) * znak;
		break;
	case CF_CODE_DD:
		//return (a * PI / 180.0 * znak);
		nReturn = ((a * PI) / 180.0) * znak;
		break;
	case CF_CODE_DM:
		rg = (int) (a / 100.0 + 0.00000000005);
		rg1 = (a - (rg * 100.0)) / 60.0;
		rm = rg + rg1;
		//return rm * PI / 180.0 * znak;
		nReturn = ((rm * PI) / 180.0) * znak;
		break;
	case CF_CODE_SECS:
		//return (a / 3600.0) * PI / 180.0 * znak;
		nReturn = (((a / 3600.0) * PI) / 180.0) * znak;
		break;
	case CF_CODE_SECS1000:
		//return (a / 1000.0 / 3600.0) * PI / 180.0 * znak;
		nReturn = (((a / 1000.0 / 3600.0) * PI) / 180.0) * znak;
		break;
	default:
		nReturn = a * znak;
	}

	//return a;
	return nReturn;
}

double exponen (double x, int e)
{
	if (e > 0)
		while (e--) x = x*10;
	else
		while (e++) x = x/10;
	return x;
}

double arctanm(double y, double x)
{
	double a;

	a = atan(y / x);
	if (x < 0) a = a + PI;
	else if (y < 0) a = a + 2 * PI;
	return a;
}

double ra(double a, int b)
{
	double tb;
	int zn;

	if (a < 0)
	{
		a = fabs(a);
		zn = -1;
	}
	else zn = 1;
	tb = pow(10.0,b);
	return (int)(a * tb + 0.5) / tb * zn;
}

CCHARString gtostr(double a, int format, int decimal)
{
	CCHARString strReturn("");
	CCHARString strt;
	if (a == NO_DVALUE) return strReturn;
	double nFactor = 0.5 / pow(10.0,decimal);
	
	double rg, rm;
	double rs,rg1;
	int znak;
	if (format == CF_CODE_RADIANS)
	{
		a = a * 180.0 / PI;
		format = CF_CODE_DD;
	}
	znak = 1;
	//if (a == 0) return 0;
	if (a < 0)
	{
		znak = -1;
		a = fabs(a);
	}
	switch (format) {
	case CF_CODE_UNDEFINED:
	case CF_CODE_DMS:	
	case CF_CODE_D_M_S:
		rg = (int) (a / 10000);
		rg1 = a - (rg * 10000);
		rm = (int) (rg1 / 100);
		rs = rg1 - (rm * 100);
		if (rs + nFactor >= 60)
		{
			rs = 0;
			rm = rm + 1;
			if (rm == 60)
			{
				rm = 0;
				rg = rg + 1;
			}
		}
		if (rg == 360) rg = 0;
		if(format == CF_CODE_D_M_S)
		{
			if(rm < 10)
				strReturn.Format("%d%c 0%d%c %0*.*lf%c", (int)rg, 176,(int)rm, 39, decimal + 3, decimal, rs, 34);
			else
				strReturn.Format("%d%c %d%c %0*.*lf%c", (int)rg, 176,(int)rm, 39, decimal + 3, decimal, rs, 34);
		}
		else
			strReturn.Format("%d%0*.*lf", (int)(rg * 100 + rm), decimal + 3, decimal, rs);
		break;
	case CF_CODE_D_MS:
		rg = (int) a;
		rg1 = a - rg;
		rm = (int) (rg1 * 100);
		rs = (rg1 - (rm / 100)) * 10000;
		if (rs + nFactor >= 60)
		{
			rs = 0;
			rm = rm + 1;
			if (rm == 60)
			{
				rm = 0;
				rg = rg + 1;
			}
		}
		if (rg == 360) rg = 0;
		strReturn.Format("%0.2lf%0.*ld", rg + rm / 100,decimal + 2, (int)(rs * pow(10.0,decimal)));
		break;
	case CF_CODE_DD:
		strReturn.Format("%0.*lf", decimal, a);
		break;
	case CF_CODE_DM:
		rg = (int) (a / 100);
		rm = (a - (rg * 100));
		if (rm + nFactor >= 60)
		{
			rm = 0;
			rg = rg + 1;
		}
		if (rg == 360) rg = 0;
		//if((int)rm > 9)
		//	strt.Format("%0.*ld",decimal + 2,(int)(rm * pow(10,decimal)));
		//else
		//	strt.Format("0%*ld",decimal + 2,(int)(rm * pow(10,decimal)));
		strReturn.Format("%ld%0.*lf", (int)rg,decimal, rm);
		break;
	case CF_CODE_SECS:
		strReturn.Format("%0.0lf", a);
		break;
	}
	
	return strReturn;
}

CCHARString rtostr(double a, int format, int precision)
{
	double tmp, g, m, s;
	CCHARString strReturn = "";
	if (a == NO_DVALUE) return strReturn;
	tmp = a * 180 / PI;
	switch (format) {
	case CF_CODE_UNDEFINED:
	case CF_CODE_DMS:	
	case CF_CODE_D_M_S:	
		g = (int)tmp;
		m = (int)((tmp - g) * 60);
		s = (((tmp - g) * 60) - m) * 60;
		if (s + 0.0000005 >= 60)
		{
			s = 0;
			m = m + 1;
			if (m == 60)
			{
				m = 0;
				g = g + 1;
			}
		}
		if (g == 360) g = 0;
		if (precision == -1) precision = 6;
		strReturn.Format("%*.*lf", 7 + precision, precision, (g * 10000 + m * 100 + s));
		break;
	case CF_CODE_D_MS:
		g = (int)tmp;
		m = (int)((tmp - g) * 60);
		s = (((tmp - g) * 60) - m) * 60;
		if (s + 0.0000005 >= 60)
		{
			s = 0;
			m = m + 1;
			if (m == 60)
			{
				m = 0;
				g = g + 1;
			}
		}
		if (g == 360) g = 0;
		if (precision == -1) precision = 10;
		strReturn.Format("%3.*lf", precision, (g + m / 100 + s / 10000));
		break;
	case CF_CODE_DD:
		if (precision == -1) precision = 12;
		strReturn.Format("%3.*lf", precision, tmp);
		break;
	case CF_CODE_DM:
		g = (int)tmp;
		m = (tmp - g) * 60;
		if (g == 360) g = 0;
		if (precision == -1) precision = 8;
		strReturn.Format("%5.*lf", precision, (g * 100 + m));
		break;
	case CF_CODE_SECS:
		if (precision == -1) precision = 6;
		strReturn.Format("%.*lf", precision, (tmp * 3600));
		break;
	}

	return strReturn;
}


CCHARString ConvUnits(CCHARString stra, int sformat, int tformat, int precision)
{
	CCHARString strReturn = stra;
	if(tformat == CF_CODE_METERS)
	{
		return strReturn;
	}
	double a;
	a = ConvertTextToDouble(stra);
	a = gtor(a,sformat);
	strReturn = rtostr(a,tformat,precision);
	
	return strReturn;
}

int RetGMS(double dd, int &deg, int &min, double &sec)
{
	if (dd == NO_DVALUE) return 1;
	int znak = 1;
	if(dd < 0) znak = -1;
	dd = fabs(dd);
	deg = (int)dd;
	min = (int)((dd - deg) * 60);
	sec = (((dd - deg) * 60) - min) * 60;
	if (sec + 0.0000005 >= 60)
	{
		sec = 0;
		min++;
		if (min == 60)
		{
			min = 0;
			deg++;
		}
	}
	if (deg == 360)
	{
		deg = 0;
	}
	else
	{
		deg = deg * znak;
	}

	return 0;
}

CCHARString angletostr(double a, int from_format, int to_format, int decimal)
{
	CCHARString strReturn("");
	if (a == NO_DVALUE) return strReturn;
	double nFactor = 0.5 / pow(10.0, decimal);
	CCHARString strt;

	double rg, rm;
	double rs, rg1;
	int znak;
	if (a == 0) return "0";
	if (from_format == CF_CODE_RADIANS)
	{
		a = a * 180.0 / PI;
		from_format = CF_CODE_DD;
	}
	znak = 1;
	if (a < 0)
	{
		znak = -1;
		a = fabs(a);
	}
	switch (from_format) {
	case CF_CODE_UNDEFINED:
	case CF_CODE_DMS:
	case CF_CODE_D_M_S:
		rg = (int)(a / 10000);
		rg1 = a - (rg * 10000);
		rm = (int)(rg1 / 100);
		rs = rg1 - (rm * 100);
		if (rs + nFactor >= 60)
		{
			rs = 0;
			rm = rm + 1;
			if (rm == 60)
			{
				rm = 0;
				rg = rg + 1;
			}
		}
		if (rg == 360) rg = 0;
		break;
	case CF_CODE_D_MS:
		rg = (int)a;
		rg1 = a - rg;
		rm = (int)(rg1 * 100);
		rs = (rg1 - (rm / 100)) * 10000;
		if (rs + nFactor >= 60)
		{
			rs = 0;
			rm = rm + 1;
			if (rm == 60)
			{
				rm = 0;
				rg = rg + 1;
			}
		}
		if (rg == 360) rg = 0;
		break;
	case CF_CODE_DD:
		rg = (int)a;
		rg1 = a - rg;

		rm = (int)(rg1 * 60);
		rs = ((rg1 * 60) - rm) * 60;
		if (rs + nFactor >= 60)
		{
			rs = 0;
			rm = rm + 1;
			if (rm == 60)
			{
				rm = 0;
				rg = rg + 1;
			}
		}
		if (rg >= 360) rg -= 360;
		break;
	case CF_CODE_DM:
		rg = (int)(a / 100);
		rm = (a - (rg * 100));
		if (rm + nFactor >= 60)
		{
			rm = 0;
			rg = rg + 1;
		}
		if (rg == 360) rg = 0;
		break;
	case CF_CODE_SECS:
		a = a / 3600.0;
		break;
	}
	//if (strReturn == "") return strReturn;
	switch (to_format) {
	case CF_CODE_UNDEFINED:
	case CF_CODE_DMS:
		strReturn.Format("%d%0*.*lf", (int)(rg * 100 + rm), decimal + 3, decimal, rs);
		break;
	case CF_CODE_D_M_S:
		if (rm < 10)
			strReturn.Format("%d%c 0%d%c %0*.*lf%c", (int)rg, 176, (int)rm, 39, decimal + 3, decimal, rs, 34);
		else
			strReturn.Format("%d%c %d%c %0*.*lf%c", (int)rg, 176, (int)rm, 39, decimal + 3, decimal, rs, 34);
		break;
	case CF_CODE_D_MS:
		strReturn.Format("%0.2lf%0.*ld", rg + rm / 100, decimal + 2, (int)(rs * pow(10.0, decimal)));
		break;
	case CF_CODE_DD:
		strReturn.Format("%0.*lf", decimal, a);
		break;
	case CF_CODE_DM:
		strReturn.Format("%ld%0.*lf", (int)rg, decimal, rm);
		break;
	case CF_CODE_SECS:
		strReturn.Format("%0.0lf", a * 3600.0);
		break;
	}


	return strReturn;
}

double ConvertAngleFormats(double a, int from_format, int to_format)
{
	double dblReturn = NO_DVALUE;
	if (a != NO_DVALUE)
	{
		a = gtor(a, from_format);
		dblReturn = rtog(a, to_format);
	}

	return dblReturn;
}

double cotg(double b)
{
	double dblReturn = 0.0;
	dblReturn = cos(b) / sin(b);

	return dblReturn;
}
