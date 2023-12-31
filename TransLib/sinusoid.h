#ifndef _STANDARD1_
#ifndef SINUSOID_H
  #define SINUSOID_H

/***************************************************************************/
/* RSC IDENTIFIER: SINUSOIDAL
 *
 * ABSTRACT
 *
 *    This component provides conversions between Geodetic coordinates 
 *    (latitude and longitude in radians) and Sinusoid projection coordinates
 *    (easting and northing in meters).
 *
 * ERROR HANDLING
 *
 *    This component checks parameters for valid values.  If an invalid value
 *    is found, the error code is combined with the current error code using 
 *    the bitwise or.  This combining allows multiple error codes to be
 *    returned. The possible error codes are:
 *
 *          SINU_NO_ERROR           : No errors occurred in function
 *          SINU_LAT_ERROR          : Latitude outside of valid range
 *                                      (-90 to 90 degrees)
 *          SINU_LON_ERROR          : Longitude outside of valid range
 *                                      (-180 to 360 degrees)
 *          SINU_EASTING_ERROR      : Easting outside of valid range
 *                                      (False_Easting +/- ~20,000,000 m,
 *                                       depending on ellipsoid parameters)
 *          SINU_NORTHING_ERROR     : Northing outside of valid range
 *                                      (False_Northing +/- ~10,000,000 m,
 *                                       depending on ellipsoid parameters)
 *          SINU_CENT_MER_ERROR     : Origin longitude outside of valid range
 *                                      (-180 to 360 degrees)
 *          SINU_A_ERROR            : Semi-major axis less than or equal to zero
 *          SINU_INV_F_ERROR        : Inverse flattening outside of valid range
 *								  	                  (250 to 350)
 *
 * REUSE NOTES
 *
 *    SINUSOIDAL is intended for reuse by any application that performs a
 *    Sinusoid projection or its inverse.
 *    
 * REFERENCES
 *
 *    Further information on SINUSOIDAL can be found in the Reuse Manual.
 *
 *    SINUSOIDAL originated from :  U.S. Army Topographic Engineering Center
 *                                  Geospatial Information Division
 *                                  7701 Telegraph Road
 *                                  Alexandria, VA  22310-3864
 *
 * LICENSES
 *
 *    None apply to this component.
 *
 * RESTRICTIONS
 *
 *    SINUSOIDAL has no restrictions.
 *
 * ENVIRONMENT
 *
 *    SINUSOIDAL was tested and certified in the following environments:
 *
 *    1. Solaris 2.5 with GCC, version 2.8.1
 *    2. Windows 95 with MS Visual C++, version 6
 *
 * MODIFICATIONS
 *
 *    Date              Description
 *    ----              -----------
 *    7-15-99          Original Code
 *
 */


/***************************************************************************/
/*
 *                              DEFINES
 */

  #define SINU_NO_ERROR           0x0000
  #define SINU_LAT_ERROR          0x0001
  #define SINU_LON_ERROR          0x0002
  #define SINU_EASTING_ERROR      0x0004
  #define SINU_NORTHING_ERROR     0x0008
  #define SINU_CENT_MER_ERROR     0x0020
  #define SINU_A_ERROR            0x0040
  #define SINU_INV_F_ERROR        0x0080

#include "projection.h"
/***************************************************************************/
/*
 *                              FUNCTION PROTOTYPES
 *                                for SINUSOID.C
 */
class CSinusoidal :CProjection
{
public:
	/* Ellipsoid Parameters, default to WGS 84 */
	double Sinu_a;                      /* Semi-major axis of ellipsoid in meters */
	double Sinu_f;              /* Flattening of ellipsoid */
	double es2;             /* Eccentricity (0.08181919084262188000) squared         */
	double es4;              /* es2 * es2 */
	double es6;              /* es4 * es2 */
	double c0;           /* 1 - es2 / 4.0 - 3.0 * es4 / 64.0 - 5.0 * es6 / 256.0 */
	double c1;     /* 3.0 * es2 / 8.0 + 3.0 * es4 / 32.0 + 45.0 * es6 / 1024.0 */
	double c2;             /* 15.0 * es4 / 256.0 + 45.0 * es6 / 1024.0 */
	double c3;               /* 35.0 * es6 / 3072.0 */
	double a0;                  /* 3.0 * e1 / 2.0 - 27.0 * e3 / 32.0 */
	double a1;               /* 21.0 * e2 / 16.0 - 55.0 * e4 / 32.0 */
	double a2;               /* 151.0 * e3 / 96.0 */
	double a3;               /* 1097.0 * e4 / 512.0 */

	/* Sinusoid projection Parameters */
	double Sinu_Origin_Long;                  /* Longitude of origin in radians    */
	double Sinu_False_Northing;               /* False northing in meters          */
	double Sinu_False_Easting;                /* False easting in meters           */

	/* Maximum variance for easting and northing values for WGS 84.
	 */
	double Sinu_Max_Easting;
	double Sinu_Min_Easting;
	double Sinu_Delta_Northing;

public:
	CSinusoidal();
	~CSinusoidal();
	long Set_Sinusoidal_Parameters(double a,
		double f,
		double Central_Meridian,
		double False_Easting,
		double False_Northing);

	/*
	 * The function Set_Sinusoidal_Parameters receives the ellipsoid parameters and
	 * Sinusoidal projcetion parameters as inputs, and sets the corresponding state
	 * variables. If any errors occur, the error code(s) are returned by the function,
	 * otherwise SINU_NO_ERROR is returned.
	 *
	 *    a                 : Semi-major axis of ellipsoid, in meters   (input)
	 *    f                 : Flattening of ellipsoid                   (input)
	 *    Central_Meridian  : Longitude in radians at the center of     (input)
	 *                          the projection
	 *    False_Easting     : A coordinate value in meters assigned to the
	 *                          central meridian of the projection.     (input)
	 *    False_Northing    : A coordinate value in meters assigned to the
	 *                          origin latitude of the projection       (input)
	 */


	void Get_Sinusoidal_Parameters(double *a,
		double *f,
		double *Central_Meridian,
		double *False_Easting,
		double *False_Northing);

	/*
	 * The function Get_Sinusoidal_Parameters returns the current ellipsoid
	 * parameters and Sinusoidal projection parameters.
	 *
	 *    a                 : Semi-major axis of ellipsoid, in meters   (output)
	 *    f                 : Flattening of ellipsoid                   (output)
	 *    Central_Meridian  : Longitude in radians at the center of     (output)
	 *                          the projection
	 *    False_Easting     : A coordinate value in meters assigned to the
	 *                          central meridian of the projection.     (output)
	 *    False_Northing    : A coordinate value in meters assigned to the
	 *                          origin latitude of the projection       (output)
	 */


	long Convert_Geodetic_To_Sinusoidal(double Latitude,
		double Longitude,
		double *Easting,
		double *Northing);
	/*
	 * The function Convert_Geodetic_To_Sinusoidal converts geodetic (latitude and
	 * longitude) coordinates to Sinusoidal projection easting, and northing
	 * coordinates, according to the current ellipsoid and Sinusoidal projection
	 * parameters.  If any errors occur, the error code(s) are returned by the
	 * function, otherwise SINU_NO_ERROR is returned.
	 *
	 *    Latitude          : Latitude (phi) in radians           (input)
	 *    Longitude         : Longitude (lambda) in radians       (input)
	 *    Easting           : Easting (X) in meters               (output)
	 *    Northing          : Northing (Y) in meters              (output)
	 */


	long Convert_Sinusoidal_To_Geodetic(double Easting,
		double Northing,
		double *Latitude,
		double *Longitude);
	/*
	 * The function Convert_Sinusoidal_To_Geodetic converts Sinusoidal projection
	 * easting and northing coordinates to geodetic (latitude and longitude)
	 * coordinates, according to the current ellipsoid and Sinusoida projection
	 * coordinates.  If any errors occur, the error code(s) are returned by the
	 * function, otherwise SINU_NO_ERROR is returned.
	 *
	 *    Easting           : Easting (X) in meters                  (input)
	 *    Northing          : Northing (Y) in meters                 (input)
	 *    Latitude          : Latitude (phi) in radians              (output)
	 *    Longitude         : Longitude (lambda) in radians          (output)
	 */

};

#endif /* SINUSOID_H */

#endif //_STANDARD1_