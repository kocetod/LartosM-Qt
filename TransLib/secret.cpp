#include <string.h>
#include <math.h>
#include "secret.h"
#include "geodw.h"
#include "geocent.h"
#include "TransHelper.h"
#include "General/GlobalVariables.h"
#include "utm.h"

void MoBo(double xm, double ym, double zm, double dx, double dy, double dz, double rx,
		double ry, double rz, double sc, double &x, double &y, double &z)
/*{...Molodenski-Badekas similarity transformation
Coordinate Frame Rotation (geocentric domain)
  Transformation parameters:
   xm, ym, zm - transformation origin
   dx, dy, dz - shifts
   rx, ry, rz - rotations
   sc         - scale factor
}*/
{
	double xxm, yym, zzm;

	xxm = x - xm;
	yym = y - ym;
	zzm = z - zm;
	x = dx + xm +  sc*(xxm + rz*yym - ry*zzm);
	y = dy + ym +  sc*(yym - rz*xxm + rx*zzm);
	z = dz + zm +  sc*(zzm + ry*xxm - rx*yym);
}

long WGS_4283(int trset, int it, double &xm, double &ym, double &zm,
					double &dx, double &dy, double &dz,
					double &rx, double &ry, double &rz, double &sc)
/*...Assign values to the parameters of Molodenski-Badekas transformation
   trset - transformation parameters
        0 - From Plamen
        1 - From Border
...Options: IT  1 ........ WGS84   --> 1942/83
            IT  2 ........ 1942/83 --> WGS84
...Transformation parameters:
   xm, ym, zm - transformation origin
   dx, dy, dz - shifts
   rx, ry, rz - rotations
   sign of rx,ry,rz are oposite from derived in Leica software
   sc         - scale factor /part from ppm/
...Ellipsoide parameters:
     "Old" ellipsoide - a1,e1  (a - semi-major axis)
     "New" ellipsoide - a2,e2  (e - first eccentricity squared)
*/

{
	switch(trset)
	{
	case 0: //{From Plamen}
		{
			xm =  4188742.631;
			ym =  2016041.319;
			zm =  4349746.951;
			dx =       -5.426;
			dy =      131.928;
			dz =      103.833;
			rx =     1.363718;
			ry =     1.980293;
			rz =    -3.422231;
			sc = 3.779720e-06;
			break;
		}
		case 3: //{BGS2005}
		{
			xm =  4223395.516;
			ym =  2017789.911;
			zm =  4315571.480;
			dx =      -5.0514;
			dy =     132.3215;
			dz =     104.0649;
			rx =     1.368805;
			ry =     2.003175;
			rz =    -3.415297;
			sc =   3.9295e-06;
			break;
		}
		case 6: //{New_param 2 BGS2005 - 42_83}
		{
			xm =  4223032.260;
			ym =  2032777.529;
			zm =  4309209.044;
			dx =      -5.2493;
			dy =     132.3430;
			dz =     103.9394;
			rx =     1.370062;
			ry =     2.006591;
			rz =    -3.409304;
			sc =   3.9901e-06;
			break;
		}
	default: return TRANS_PARAMETERS_NOT_DEFINED_ERROR;
	}
	if (it == 2)
	{
		dx = -dx;
		dy = -dy;
		dz = -dz;
		rx = -rx;
		ry = -ry;
		rz = -rz;
		sc = -sc;
	}
	sc =  sc + 1;
	//...Turn rotations to radians
	rx = gtor(rx, CF_CODE_SECS);//Seconds to radians
	ry = gtor(ry, CF_CODE_SECS);
	rz = gtor(rz, CF_CODE_SECS);
	return TRANS_NO_ERROR;
}

long WGS_BGS2005 (int trset, int it, double &xm, double &ym, double &zm,
					double &dx, double &dy, double &dz,
					double &rx, double &ry, double &rz, double &sc)
{
	switch(trset)
	{
	case 0: //{Plamen 2011}
		{
			xm =  4232496.704;
			ym =  1993413.221;
			zm =  4316918.266;
			dx =      0.0658;
			dy =     -0.0246;
			dz =     -0.0527;
			rx =    0.000230;
			ry =   -0.002430;
			rz =    0.001506;
			sc =   -1.16E-08;
			break;
		}
	default: return TRANS_PARAMETERS_NOT_DEFINED_ERROR;
	}
	if (it == 2)
	{
		dx = -dx;
		dy = -dy;
		dz = -dz;
		rx = -rx;
		ry = -ry;
		rz = -rz;
		sc = -sc;
	}
	sc =  sc + 1;
	//...Turn rotations to radians
	rx = gtor(rx, CF_CODE_SECS);//Seconds to radians
	ry = gtor(ry, CF_CODE_SECS);
	rz = gtor(rz, CF_CODE_SECS);
	return TRANS_NO_ERROR;
}

int bltrans(int it, int sys, int trset,
			 double &B, double &L, double H)
/* Transform B,L using Molodenski Badekash
  it = 1  direct
  it = 2  reverse
  sys - transformations
    2 - BGS2005 - 42/83
    3 - WGS84 - ED50
    4 - WGS84 - Bessel
    5 - Bessel - 42/83
	6 - 1950 - BGS2005
	7 - BULREF - BGS2005
  trset = transformation parameters
*/
  
//var xm,ym,zm,dx,dy,dz,rx,ry,rz,sc : double;
{
	double xm = 0, ym = 0, zm = 0, dx = 0, dy = 0, dz = 0, rx = 0, ry = 0, rz = 0, sc = 0;
	double a = 0, f = 0;
	double X = 0, Y = 0, Z = 0;
	double tmpHeight = 0.0, debugHeight = H;
	int status = TRANS_NO_ERROR;
	//long Index;
	//char en[5];
	
	int nSys;
	double Scale;

	switch(sys)
	{
	case 2: //WE --> KA
		if (it == 1) nSys = CS_WGS84_CODE; // ExamineFunc(Get_Ellipsoid_Index("RF",&Index),3);
		else if (it == 2) nSys = CS_42_83_CODE; // ExamineFunc(Get_Ellipsoid_Index("KA",&Index),3); 
		break;
	case 6: //WE --> KA
		if (it == 1) nSys = CS_BGS_CODE; // ExamineFunc(Get_Ellipsoid_Index("RF",&Index),3);
		else if (it == 2) nSys = CS_42_83_CODE; // ExamineFunc(Get_Ellipsoid_Index("KA",&Index),3); 
		break;
	case 7: // WE --> WE
		if (it == 1) nSys = CS_WGS84_CODE;
		else if (it == 2) nSys = CS_BGS_CODE;
		break;
	}
	CGeocent objGeocent;
	Get_Ellipsoid_Parameters_By_System(nSys, &a, &f, &Scale);
	objGeocent.Set_Geocentric_Parameters(a, f);
	status = objGeocent.Convert_Geodetic_To_Geocentric(B, L, tmpHeight, &X, &Y, &Z);
	if (status != TRANS_NO_ERROR)
		return TRANS_SOURCECOORDINATES_INVALID;
	switch(sys)
	{
	case 2: status = WGS_4283(trset,it,xm,ym,zm,dx,dy,dz,rx,ry,rz,sc); break;
	case 7: status = WGS_BGS2005(trset,it,xm,ym,zm,dx,dy,dz,rx,ry,rz,sc); break;
	}
	
	if(status) return status;
	
	MoBo(xm,ym,zm,dx,dy,dz,rx,ry,rz,sc,X,Y,Z);

	switch(sys)
	{
	case 2: // WE --> KA
		if (it == 1) nSys = CS_42_83_CODE; // ExamineFunc(Get_Ellipsoid_Index("KA",&Index),3);
		else if (it == 2) nSys = CS_BGS_CODE; // ExamineFunc(Get_Ellipsoid_Index("RF",&Index),3); 
		break;
	case 6: // WE --> KA
		if (it == 1) nSys = CS_42_83_CODE; // ExamineFunc(Get_Ellipsoid_Index("KA",&Index),3);
		else if (it == 2) nSys = CS_BGS_CODE; // ExamineFunc(Get_Ellipsoid_Index("RF",&Index),3); 
		break;
	case 7: // WE --> WE
		if (it == 1) nSys = CS_BGS_CODE;
		else if (it == 2) nSys = CS_WGS84_CODE;
		break;
	}

	Get_Ellipsoid_Parameters_By_System(nSys, &a, &f, &Scale);
	objGeocent.Set_Geocentric_Parameters(a, f);
	objGeocent.Convert_Geocentric_To_Geodetic(X, Y, Z, &B, &L, &tmpHeight);

	return TRANS_NO_ERROR;
}

long BG_KRON_NH_to_EVRF2000(double B, double L, double &H)
{
	double a = 6378137.0;         /* Semi-major axis of ellipsoid in meters  */
	//double f = 1 / 298.257223563; /* Flattening of ellipsoid WGS84           */
	double f = 1 / 298.257222101;  //for GRS80
	double a1 = +0.182;	//vertical translation
	double a2 = gtor(+0.001,CF_CODE_D_M_S);	//slope in the direction of the meridian
	double a3 = gtor(-0.004,CF_CODE_D_M_S);	//slope in the direction perpendicular to the meridian
	double HH = H;
	double L0 = gtor(252236,CF_CODE_D_M_S);
	double B0 = gtor(423730,CF_CODE_D_M_S);
	double dL = L - L0;
	double dB = B - B0;
	long status = TRANS_NO_ERROR/*, Index = 0*/;
	//status = Get_Ellipsoid_Index("WE",&Index);
	
	double Mo = mrad(B0,a,f);
	double No = nrad(B0,a,f);

	H = a1 + a2 * Mo * dB + a3 * No * dL * cos(B); 

	return status;
}

long BG_KRON_NH_to_EVRF2007(double B, double L, double &H)
{
	double a = 6378137.0;         /* Semi-major axis of ellipsoid in meters  */
	//double f = 1 / 298.257223563; /* Flattening of ellipsoid WGS84           */
	double f = 1 / 298.257222101;  //for GRS80
	double a1 = +0.228;	//vertical translation
	double a2 = gtor(-0.009,CF_CODE_D_M_S);	//slope in the direction of the meridian
	double a3 = gtor(-0.003,CF_CODE_D_M_S);	//slope in the direction perpendicular to the meridian
	double HH = H;
	double L0 = gtor(252236,CF_CODE_D_M_S);
	double B0 = gtor(423730,CF_CODE_D_M_S);
	double dL = L - L0;
	double dB = B - B0;
	long status = TRANS_NO_ERROR/*, Index = 0*/;
	//status = Get_Ellipsoid_Index("WE",&Index);
	
	double Mo = mrad(B0,a,f);
	double No = nrad(B0,a,f);

	H = a1 + a2 * Mo * dB + a3 * No * dL * cos(B); 

	return status;
}

bool Get_Ellipsoid_Parameters_By_System(int system, double* a, double* f, double* scale)
{
	switch (system)
	{
	case CS_42_83_CODE:
		{ *a = 6378245; *f = 1 / 298.3; *scale = 1.0; }  //Krasovsky
		break;
	case CS_WGS84_CODE:
	case CS_BGS_CODE:
		{ *a = 6378137; *f = 1 / 298.257222101; *scale = 0.9996; } //GRS80
		break;
	case CS_WGS84_G1762_CODE:
		{ *a = 6378137; *f = 1 / 298.257223563; *scale = 0.9996; } //WGS84
		break;
	default: 
		return false;
	}
	return true;
}

long RO_CONST_NH_to_EVRF2007(double B, double L, double& H)
{
	double a = 6378137.0;         /* Semi-major axis of ellipsoid in meters  */
	//double f = 1 / 298.257223563; /* Flattening of ellipsoid WGS84           */
	double f = 1 / 298.257222101;  //for GRS80
	double a1 = +0.062;	//vertical translation
	double a2 = gtor(-0.005, CF_CODE_D_M_S);	//slope in the direction of the meridian
	double a3 = gtor(0.008, CF_CODE_D_M_S);	//slope in the direction perpendicular to the meridian
	double HH = H;
	double L0 = gtor(244900, CF_CODE_D_M_S);
	double B0 = gtor(460100, CF_CODE_D_M_S);
	double dL = L - L0;
	double dB = B - B0;
	long status = TRANS_NO_ERROR/*, Index = 0*/;
	//status = Get_Ellipsoid_Index("WE",&Index);

	double Mo = mrad(B0, a, f);
	double No = nrad(B0, a, f);

	H = a1 + a2 * Mo * dB + a3 * No * dL * cos(B);

	return status;
}
