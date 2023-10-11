/***************************************************************************/
/* RSC IDENTIFIER: LAMBERT
 *
 * ABSTRACT
 *
 *    This component provides conversions between Geodetic coordinates
 *    (latitude and longitude in radians) and Lambert Conformal Conic
 *    projection coordinates (easting and northing in meters) defined
 *    by two standard parallels.
 *
 * ERROR HANDLING
 *
 *    This component checks parameters for valid values.  If an invalid value
 *    is found the error code is combined with the current error code using
 *    the bitwise or.  This combining allows multiple error codes to be
 *    returned. The possible error codes are:
 *
 *       LAMBERT_NO_ERROR           : No errors occurred in function
 *       LAMBERT_LAT_ERROR          : Latitude outside of valid range
 *                                     (-90 to 90 degrees)
 *       LAMBERT_LON_ERROR          : Longitude outside of valid range
 *                                     (-180 to 360 degrees)
 *       LAMBERT_EASTING_ERROR      : Easting outside of valid range
 *                                     (depends on ellipsoid and projection
 *                                     parameters)
 *       LAMBERT_NORTHING_ERROR     : Northing outside of valid range
 *                                     (depends on ellipsoid and projection
 *                                     parameters)
 *       LAMBERT_FIRST_STDP_ERROR   : First standard parallel outside of valid
 *                                     range (-89 59 59.0 to 89 59 59.0 degrees)
 *       LAMBERT_SECOND_STDP_ERROR  : Second standard parallel outside of valid
 *                                     range (-89 59 59.0 to 89 59 59.0 degrees)
 *       LAMBERT_ORIGIN_LAT_ERROR   : Origin latitude outside of valid range
 *                                     (-89 59 59.0 to 89 59 59.0 degrees)
 *       LAMBERT_CENT_MER_ERROR     : Central meridian outside of valid range
 *                                     (-180 to 360 degrees)
 *       LAMBERT_A_ERROR            : Semi-major axis less than or equal to zero
 *       LAMBERT_INV_F_ERROR        : Inverse flattening outside of valid range
 *									                   (250 to 350)
 *       LAMBERT_HEMISPHERE_ERROR   : Standard parallels cannot be opposite latitudes
 *       LAMBERT_FIRST_SECOND_ERROR : The 1st & 2nd standard parallels cannot
 *                                     both be 0
 *
 *
 * REUSE NOTES
 *
 *    LAMBERT is intended for reuse by any application that performs a Lambert
 *    Conformal Conic projection or its inverse.
 *    
 * REFERENCES
 *
 *    Further information on LAMBERT can be found in the Reuse Manual.
 *
 *    LAMBERT originated from:
 *                      U.S. Army Topographic Engineering Center
 *                      Geospatial Information Division
 *                      7701 Telegraph Road
 *                      Alexandria, VA  22310-3864
 *
 * LICENSES
 *
 *    None apply to this component.
 *
 * RESTRICTIONS
 *
 *    LAMBERT has no restrictions.
 *
 * ENVIRONMENT
 *
 *    LAMBERT was tested and certified in the following environments:
 *
 *    1. Solaris 2.5 with GCC, version 2.8.1
 *    2. Windows 95 with MS Visual C++, version 6
 *
 * MODIFICATIONS
 *
 *    Date              Description
 *    ----              -----------
 *    10-02-97          Original Code
 *    08-15-99          Re-engineered Code
 *
 *
 */


/***************************************************************************/
/*
 *                               INCLUDES
 */

#include <math.h>
#include "lambert.h"


#include <stdio.h>
/*
 *    math.h     - Standard C math library
 *    lambert.h  - Is for prototype error checking
 */


/***************************************************************************/
/*                               DEFINES
 *
 */

//#define PI         3.1415926535897932384626433832795   /* PI     */
//#define PI_OVER_2  (PI / 2.0)
//#define MAX_LAT    (( PI *  89.99972222222222) / 180.0)  /* 89 59 59.0 degrees in radians */
//#define TWO_PI     (2.0 * PI)
#define LAMBERT_m(clat,essin)                  (clat / sqrt(1.0 - essin * essin))
#define LAMBERT_t(lat,essin)                   tan(PI_OVER_4 - lat / 2) /				\
										       pow((1.0 - essin) / (1.0 + essin), es_OVER_2)
#define ES_SIN(sinlat)                         (es * sinlat)

#define PI              3.1415926535897932384626433832795 /* PI     */
#define PI_OVER_2       PI / 2.0e0
#define TWO_PI          2.0 * PI
#define PI_OVER_4       PI / 4.0e0


//void WriteMessage(const char* pFile, const char* pMessage)
//{
//	FILE *fp;
//	fopen_s(&fp, pFile, "a+");
//	if(fp)
//	{
//		fprintf(fp, "%s\n", pMessage);
//		fclose(fp);
//	}
//}

/************************************************************************/
/*                              FUNCTIONS
 *
 */
CLambert::CLambert()
{
	MAX_LAT = ((PI *  89.99972222222222) / 180.0);  /* 89 59 59.0 degrees in radians */
	/* Ellipsoid Parameters, default to WGS 84  */
	Lambert_a = 6378137.0;               /* Semi-major axis of ellipsoid, in meters */
	Lambert_f = 1 / 298.257223563;       /* Flattening of ellipsoid */
	es = 0.08181919084262188000;         /* Eccentricity of ellipsoid */
	es2 = 0.0066943799901413800;         /* Eccentricity squared */
	es_OVER_2 = .040909595421311;        /* Eccentricity / 2.0 */
	n = .70802074516367;                 /* Ratio of angle between meridians */
	F = 1.8538379832459;                 /* Flattening of ellipsoid */
	rho0 = 6356377.2707128;              /* Height above ellipsoid */
	Lambert_aF = 11824032.632946;        /* Lambert_a * F */

	/* Lambert_Conformal_Conic projection Parameters */
	Lambert_Std_Parallel_1 = (40 * PI / 180); /* Lower std. parallel, in radians */
	Lambert_Std_Parallel_2 = (50 * PI / 180); /* Upper std. parallel, in radians */
	Lambert_Origin_Lat = (45 * PI / 180);     /* Latitude of origin, in radians */
	Lambert_Origin_Long = 0.0;                /* Longitude of origin, in radians */
	Lambert_False_Northing = 0.0;             /* False northing, in meters */
	Lambert_False_Easting = 0.0;              /* False easting, in meters */

	/* Lambert_Conformal_Conic One standard parallel projection Parameter */
	Lambert_Scale_Factor = 1.0; /* Scale factor at natural origin */


	/* Maximum variance for easting and northing values for WGS 84. */
	Lambert_Delta_Easting = 40000000.0;
	Lambert_Delta_Northing = 40000000.0;

	/* These state variables are for optimization purposes. The only function
	 * that should modify them is Set_Lambert_Parameters.         */
}

CLambert::~CLambert()
{

}

long CLambert::Set_Lambert_Parameters(double a,
                            double f,
                            double Origin_Latitude,
                            double Central_Meridian,
                            double Std_Parallel_1,
                            double Std_Parallel_2,
                            double False_Easting,
                            double False_Northing)

{ /* BEGIN Set_Lambert_Parameters */
/*
 * The function Set_Lambert_Parameters receives the ellipsoid parameters and
 * Lambert Conformal Conic projection parameters as inputs, and sets the
 * corresponding state variables.  If any errors occur, the error code(s)
 * are returned by the function, otherwise LAMBERT_NO_ERROR is returned.
 *
 *   a                   : Semi-major axis of ellipsoid, in meters   (input)
 *   f                   : Flattening of ellipsoid						       (input)
 *   Origin_Latitude     : Latitude of origin, in radians            (input)
 *   Central_Meridian    : Longitude of origin, in radians           (input)
 *   Std_Parallel_1      : First standard parallel, in radians       (input)
 *   Std_Parallel_2      : Second standard parallel, in radians      (input)
 *   False_Easting       : False easting, in meters                  (input)
 *   False_Northing      : False northing, in meters                 (input)
 *   Scale factor        : Scale factor at natural orign (1SP)       (input optional)
 */

  double slat, slat1, clat;
  double es_sin;
  double t0, t1, t2;
  double m1, m2;
  double inv_f = 1 / f;
  long Error_Code = LAMBERT_NO_ERROR;

  if (a <= 0.0)
  { /* Semi-major axis must be greater than zero */
    Error_Code |= LAMBERT_A_ERROR;
  }
  if ((inv_f < 250) || (inv_f > 350))
  { /* Inverse flattening must be between 250 and 350 */
    Error_Code |= LAMBERT_INV_F_ERROR;
  }
  if (((Origin_Latitude < -MAX_LAT) || (Origin_Latitude > MAX_LAT)) && (Origin_Latitude > -999))
  { /* Origin Latitude out of range */
    Error_Code |= LAMBERT_ORIGIN_LAT_ERROR;
  }
  if ((Std_Parallel_1 < -MAX_LAT) || (Std_Parallel_1 > MAX_LAT))
  { /* First Standard Parallel out of range */
    Error_Code |= LAMBERT_FIRST_STDP_ERROR;
  }
  if ((Std_Parallel_2 < -MAX_LAT) || (Std_Parallel_2 > MAX_LAT))
  { /* Second Standard Parallel out of range */
    Error_Code |= LAMBERT_SECOND_STDP_ERROR;
  }
  if ((Std_Parallel_1 == 0) && (Std_Parallel_2 == 0))
  { /* First & Second Standard Parallels are both 0 */
    Error_Code |= LAMBERT_FIRST_SECOND_ERROR;
  }
  if (Std_Parallel_1 == -Std_Parallel_2)
  { /* Parallels are the negation of each other */
    Error_Code |= LAMBERT_HEMISPHERE_ERROR;
  }
  if ((Central_Meridian < -PI) || (Central_Meridian > TWO_PI))
  { /* Origin Longitude out of range */
    Error_Code |= LAMBERT_CENT_MER_ERROR;
  }

  if (!Error_Code)
  { /* no errors */

    Lambert_a = a;
    Lambert_f = f;
    Lambert_Origin_Lat = Origin_Latitude;
    Lambert_Std_Parallel_1 = Std_Parallel_1;
    Lambert_Std_Parallel_2 = Std_Parallel_2;
    if (Central_Meridian > PI)
      Central_Meridian -= TWO_PI;
    Lambert_Origin_Long = Central_Meridian;
    Lambert_False_Easting = False_Easting;
    Lambert_False_Northing = False_Northing;

	if(Origin_Latitude < -900)
	{
		Lambert_Origin_Lat = Get_Origin_Lattitude(Lambert_Std_Parallel_1, Lambert_Std_Parallel_2, Lambert_f);
	}

    es2 = 2 * Lambert_f - Lambert_f * Lambert_f;
    es = sqrt(es2);
    es_OVER_2 = es / 2.0;

    slat = sin(Lambert_Origin_Lat);
    es_sin = ES_SIN(slat);
    t0 = LAMBERT_t(Lambert_Origin_Lat, es_sin);

    slat1 = sin(Lambert_Std_Parallel_1);
    clat = cos(Lambert_Std_Parallel_1);
    es_sin = ES_SIN(slat1);
    m1 = LAMBERT_m(clat, es_sin);
    t1 = LAMBERT_t(Lambert_Std_Parallel_1, es_sin);


    if (fabs(Lambert_Std_Parallel_1 - Lambert_Std_Parallel_2) > 1.0e-10)
    {
      slat = sin(Lambert_Std_Parallel_2);
      clat = cos(Lambert_Std_Parallel_2);
      es_sin = ES_SIN(slat);
      m2 = LAMBERT_m(clat, es_sin);
      t2 = LAMBERT_t(Lambert_Std_Parallel_2, es_sin);
      n = log(m1 / m2) / log(t1 / t2);
    }
    else
      n = slat1;
    F = m1 / (n * pow(t1, n));
    Lambert_aF = Lambert_a * Lambert_Scale_Factor * F;
	if ((t0 == 0) && (n < 0))
      rho0 = 0.0;
    else
      rho0 = Lambert_aF * pow(t0, n);
  }

  return (Error_Code);
} /* END OF Set_Lambert_Parameters */


void CLambert::Get_Lambert_Parameters(double *a,
                            double *f,
                            double *Origin_Latitude,
                            double *Central_Meridian,
                            double *Std_Parallel_1,
                            double *Std_Parallel_2,
                            double *False_Easting,
                            double *False_Northing)

{ /* BEGIN Get_Lambert_Parameters */
/*                         
 * The function Get_Lambert_Parameters returns the current ellipsoid
 * parameters and Lambert Conformal Conic projection parameters.
 *
 *   a                   : Semi-major axis of ellipsoid, in meters   (output)
 *   f                   : Flattening of ellipsoid					         (output)
 *   Origin_Latitude     : Latitude of origin, in radians            (output)
 *   Central_Meridian    : Longitude of origin, in radians           (output)
 *   Std_Parallel_1      : First standard parallel, in radians       (output)
 *   Std_Parallel_2      : Second standard parallel, in radians      (output)
 *   False_Easting       : False easting, in meters                  (output)
 *   False_Northing      : False northing, in meters                 (output)
 */


  *a = Lambert_a;
  *f = Lambert_f;
  *Std_Parallel_1 = Lambert_Std_Parallel_1;
  *Std_Parallel_2 = Lambert_Std_Parallel_2;
  *Origin_Latitude = Lambert_Origin_Lat;
  *Central_Meridian = Lambert_Origin_Long;
  *False_Easting = Lambert_False_Easting;
  *False_Northing = Lambert_False_Northing;
  return;
} /* END OF Get_Lambert_Parameters */


long CLambert::Convert_Geodetic_To_Lambert (double Latitude,
                                  double Longitude,
                                  double *Easting,
                                  double *Northing)

{ /* BEGIN Convert_Geodetic_To_Lambert */
/*
 * The function Convert_Geodetic_To_Lambert converts Geodetic (latitude and
 * longitude) coordinates to Lambert Conformal Conic projection (easting
 * and northing) coordinates, according to the current ellipsoid and
 * Lambert Conformal Conic projection parameters.  If any errors occur, the
 * error code(s) are returned by the function, otherwise LAMBERT_NO_ERROR is
 * returned.
 *
 *    Latitude         : Latitude, in radians                         (input)
 *    Longitude        : Longitude, in radians                        (input)
 *    Easting          : Easting (X), in meters                       (output)
 *    Northing         : Northing (Y), in meters                      (output)
 */

  double slat;
  double es_sin;
  double t;
  double rho;
  double dlam;
  double theta;
  long  Error_Code = LAMBERT_NO_ERROR;
  
  if ((Latitude < -PI_OVER_2) || (Latitude > PI_OVER_2))
  {  /* Latitude out of range */
    Error_Code|= LAMBERT_LAT_ERROR;
  }
  if ((Longitude < -PI) || (Longitude > TWO_PI))
  {  /* Longitude out of range */
    Error_Code|= LAMBERT_LON_ERROR;
  }

  if (!Error_Code)
  { /* no errors */

    if (fabs(fabs(Latitude) - PI_OVER_2) > 1.0e-10)
    {
      slat = sin(Latitude);
      es_sin = ES_SIN(slat);
      t = LAMBERT_t(Latitude, es_sin);
      rho = Lambert_aF * pow(t, n);
    }
    else
    {
      if ((Latitude * n) <= 0)
      { /* Point can not be projected */
        Error_Code |= LAMBERT_LAT_ERROR;
        return (Error_Code);
      }
      rho = 0.0;
    }

    dlam = Longitude - Lambert_Origin_Long;

    if (dlam > PI)
    {
      dlam -= TWO_PI;
    }
    if (dlam < -PI)
    {
      dlam += TWO_PI;
    }

    theta = n * dlam;

    *Easting = rho * sin(theta) + Lambert_False_Easting;
    *Northing = rho0 - rho * cos(theta) + Lambert_False_Northing;
  }
  return (Error_Code);
} /* END OF Convert_Geodetic_To_Lambert */



long CLambert::Convert_Lambert_To_Geodetic (double Easting,
                                  double Northing,
                                  double *Latitude,
                                  double *Longitude)

{ /* BEGIN Convert_Lambert_To_Geodetic */
/*
 * The function Convert_Lambert_To_Geodetic converts Lambert Conformal
 * Conic projection (easting and northing) coordinates to Geodetic
 * (latitude and longitude) coordinates, according to the current ellipsoid
 * and Lambert Conformal Conic projection parameters.  If any errors occur,
 * the error code(s) are returned by the function, otherwise LAMBERT_NO_ERROR
 * is returned.
 *
 *    Easting          : Easting (X), in meters                       (input)
 *    Northing         : Northing (Y), in meters                      (input)
 *    Latitude         : Latitude, in radians                         (output)
 *    Longitude        : Longitude, in radians                        (output)
 */


  double dy, dx;
  double rho, rho0_MINUS_dy;
  double t;
  double PHI;
  double tempPHI = 0.0;
  double sin_PHI;
  double es_sin;
  double theta = 0.0;
  double tolerance = 4.85e-10;
  long Error_Code = LAMBERT_NO_ERROR;

  if ((Easting < (Lambert_False_Easting - Lambert_Delta_Easting))
      ||(Easting > (Lambert_False_Easting + Lambert_Delta_Easting)))
  { /* Easting out of range  */
    Error_Code |= LAMBERT_EASTING_ERROR;
  }
  if ((Northing < (Lambert_False_Northing - Lambert_Delta_Northing))
      || (Northing > (Lambert_False_Northing + Lambert_Delta_Northing)))
  { /* Northing out of range */
    Error_Code |= LAMBERT_NORTHING_ERROR;
  }

  if (!Error_Code)
  { /* no errors */

    dy = Northing - Lambert_False_Northing;
    dx = Easting - Lambert_False_Easting;
    rho0_MINUS_dy = rho0 - dy;
    rho = sqrt(dx * dx + (rho0_MINUS_dy) * (rho0_MINUS_dy));

    if (n < 0.0)
    {
      rho *= -1.0;
      dy *= -1.0;
      dx *= -1.0;
      rho0_MINUS_dy *= -1.0;
    }

    if (rho != 0.0)
    {
      theta = atan2(dx, rho0_MINUS_dy);
      t = pow(rho / (Lambert_aF) , 1.0 / n);
      PHI = PI_OVER_2 - 2.0 * atan(t);
      while (fabs(PHI - tempPHI) > tolerance)
      {
        tempPHI = PHI;
        sin_PHI = sin(PHI);
        es_sin = ES_SIN(sin_PHI);
        PHI = PI_OVER_2 - 2.0 * atan(t * pow((1.0 - es_sin) / (1.0 + es_sin), es_OVER_2));
      }
      *Latitude = PHI;
      *Longitude = theta / n + Lambert_Origin_Long;
	  if (fabs(*Latitude) < 2.0e-7)  /* force lat to 0 to avoid -0 degrees */
        *Latitude = 0.0;
      if (*Latitude > PI_OVER_2)  /* force distorted values to 90, -90 degrees */
        *Latitude = PI_OVER_2;
      else if (*Latitude < -PI_OVER_2)
        *Latitude = -PI_OVER_2;

      if (*Longitude > PI)
      {
        if (*Longitude - PI < 3.5e-6) 
          *Longitude = PI;
        else
          *Longitude -= TWO_PI;
      }
      if (*Longitude < -PI)
      {
        if (fabs(*Longitude + PI) < 3.5e-6)
          *Longitude = -PI;
        else
          *Longitude += TWO_PI;
      }

      if (fabs(*Longitude) < 2.0e-7)  /* force lon to 0 to avoid -0 degrees */
        *Longitude = 0.0;
      if (*Longitude > PI)  /* force distorted values to 180, -180 degrees */
        *Longitude = PI;
      else if (*Longitude < -PI)
        *Longitude = -PI;
    }
    else
    {
      if (n > 0.0)
        *Latitude = PI_OVER_2;
      else
        *Latitude = -PI_OVER_2;
      *Longitude = Lambert_Origin_Long;
    }
  }
  return (Error_Code);
} /* END OF Convert_Lambert_To_Geodetic */

//Marian add
double CLambert::ret_W(double ff, double ees2)
{
	double retVal = 0;
	
	retVal = sqrt(1 - ees2 * pow(sin(ff), 2));

	return retVal;
}

double CLambert::ret_Q(double ff, double ees)
{
	double retVal = 0, tt1, tt2, tt3, tt4, pp1, pp2;
	tt1 = 1+sin(ff);
	tt2 = 1-sin(ff);
	tt3 = 1+ees*sin(ff);
	tt4 = 1-ees*sin(ff);
	pp1 = tt1 / tt2;
	pp2 = tt3 / tt4;
	retVal = (log(pp1) - ees * log(pp2)) / 2.0;
	
	return retVal;
}

double CLambert::ret_X0(double F0)
{
	double retVal, tt1, tt2, tt3;
	double m0, m2, m4, m6, m8;
	double a0, a2, a4, a6;
	
	m0 = Lambert_a * (1 - es2);
	m2 = 1.5 * es2 * m0;
	m4 = 1.25 * es2 * m2;
	m6 = 7.0 * es2 * m4 / 6.0;
	m8 = 1.125 * es2 * m6;
	a0 = m0 + 0.5 * m2 + 0.375 * m4 + 0.3125 * m6 + 0.2734375 * m8;
	a2 = 0.5 * m2 + 0.5 * m4 + 0.46875 * m6 + 0.2734375 * m8;
	a4 = 0.125 * m4 + 0.1875 * m6 + 0.21875 * m8;
	a6 = 0.03125 * m6 + 0.0625 * m8;
	tt1 = sin(F0) * cos(F0);
	tt2 = (2.0 * a4 - 16.0 * a6  / 3.0) * pow(sin(F0), 2);
	tt3 = (16.0 * a6  / 3.0) *  pow(sin(F0), 4);
	retVal = a0 * F0 - tt1 * (a2 - a4 + a6 + tt2 + tt3);
	
	return retVal;
}

long CLambert::Set_Other_Method(double *KK, double *R0, double *F0, double *X0)
{
	double WU, WL, QU, QL, QB, sinf0, tt1, tt2, tt3, tt4;

	WU = ret_W(Lambert_Std_Parallel_2, es2);
	WL = ret_W(Lambert_Std_Parallel_1, es2);
	QU = ret_Q(Lambert_Std_Parallel_2, es);
	QL = ret_Q(Lambert_Std_Parallel_1, es);
	tt1 = WU * cos(Lambert_Std_Parallel_1);
	tt2 = WL * cos(Lambert_Std_Parallel_2);
	tt3 = tt1 / tt2;
	tt4 = QU - QL;
	tt1 = log(tt3);
	sinf0 = tt1 / tt4;
	*F0 = asin(sinf0);
	tt1 = Lambert_a * cos(Lambert_Std_Parallel_1);
	tt2 = exp(QL * sinf0);
	tt3 = WL * sinf0;
	*KK = (tt1 * tt2) / tt3;
	QB = ret_Q(*F0, es);
	tt1 = exp(QB * sinf0);
	*R0 = *KK / tt1;
	*X0 = ret_X0(*F0);

	return 0;
}

long CLambert::BLToGrid(double B, double L, double *E, double *N)
{
	double Q, R, G, sinf0, tt1/*, tt2, tt3, tt4*/;
	double KK, R0, F0, X0;
	
	Set_Other_Method(&KK, &R0, &F0, &X0);
	sinf0 = sin(F0);
	Q = ret_Q(B, es);
	tt1 = exp(Q * sinf0);
	R = KK / tt1;
	G = (Lambert_Origin_Long - L) * sinf0;
	*E = Lambert_False_Easting - R * sin(G);
	*N = R0 + X0 - R * cos(G);

	return 0;
}

long CLambert::GridToBL(double E, double N, double *B, double *L)
{
	double Q, R, R1, G, E1, sinf0, sinf, tempf = 0.0, f, f1, f2;
	double KK, R0, F0, X0;
	double tolerance = 4.85e-13;
	
	Set_Other_Method(&KK, &R0, &F0, &X0);
	sinf0 = sin(F0);
	R1 = R0 - N + Lambert_False_Northing;
	E1 = E - Lambert_False_Easting;
	G = atan(E1 / R1);
	*L = Lambert_Origin_Long + (G / sinf0);
	R = sqrt(pow(R1, 2) + pow(E1, 2));
	Q = log(KK / R) / sinf0;
	sinf = (exp(2.0 * Q) - 1) / (exp(2.0 * Q) + 1);
	f = asin(sinf);
	while (fabs(f - tempf) > tolerance)
	{
		tempf = f;
		sinf = sin(f);
		f1 = ret_Q(f, es) - Q;
		f2 = (1.0 / (1.0 - pow(sinf, 2))) - (es2 / (1.0 - es2 * pow(sinf, 2)));
		f = asin(sinf - (f1 / f2));
	}

	*B = asin(sinf);

	return 0;
}

double CLambert::Get_Origin_Lattitude(double Std_Parallel_1, double Std_Parallel_2, double flat)
{
	double nRetValue = 0;
	double WU, WL, QU, QL, tt1, tt2, tt3, tt4;
	double ees2, ees;
	if(Std_Parallel_1 == Std_Parallel_2) return Std_Parallel_1;
	//Calculate Lambert_Origin_Lat
	ees2 = 2.0 * flat - flat * flat;
    ees = sqrt(ees2);
	WU = ret_W(Std_Parallel_2, ees2);
	WL = ret_W(Std_Parallel_1, ees2);
	QU = ret_Q(Std_Parallel_2, ees);
	QL = ret_Q(Std_Parallel_1, ees);
	tt1 = WU * cos(Std_Parallel_1);
	tt2 = WL * cos(Std_Parallel_2);
	tt3 = tt1 / tt2;
	tt4 = QU - QL;
	tt1 = log(tt3);
	nRetValue = asin(tt1 / tt4);

	return nRetValue;
}

double CLambert::Get_Convegence(double B, double L)
{
	double nRetValue = 0;
	double slat, slat1, clat;
	double es_sin;
	double t0, t1, t2;
	double m1, m2;


	slat = sin(Lambert_Origin_Lat);
	es_sin = ES_SIN(slat);
	t0 = LAMBERT_t(Lambert_Origin_Lat, es_sin);

	slat1 = sin(Lambert_Std_Parallel_1);
	clat = cos(Lambert_Std_Parallel_1);
	es_sin = ES_SIN(slat1);
	
	m1 = LAMBERT_m(clat, es_sin);
	t1 = LAMBERT_t(Lambert_Std_Parallel_1, es_sin);


	if (fabs(Lambert_Std_Parallel_1 - Lambert_Std_Parallel_2) > 1.0e-10)
	{
		slat = sin(Lambert_Std_Parallel_2);
		clat = cos(Lambert_Std_Parallel_2);
		es_sin = ES_SIN(slat);
		m2 = LAMBERT_m(clat, es_sin);
		t2 = LAMBERT_t(Lambert_Std_Parallel_2, es_sin);
		n = log(m1 / m2) / log(t1 / t2);
	}
	else
		n = slat1;
	
	nRetValue = n * (L - Lambert_Origin_Long);
	
	return nRetValue;
}