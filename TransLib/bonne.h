#ifndef _STANDARD1_
#ifndef BONNE_H
#define BONNE_H

/***************************************************************************/
/* RSC IDENTIFIER: BONNE
 *
 * ABSTRACT
 *
 *    This component provides conversions between Geodetic coordinates 
 *    (latitude and longitude in radians) and Bonne projection coordinates
 *    (easting and northing in meters).
 *
 * ERROR HANDLING
 *
 *    This component checks parameters for valid values.  If an invalid value
 *    is found, the error code is combined with the current error code using 
 *    the bitwise or.  This combining allows multiple error codes to be
 *    returned. The possible error codes are:
 *
 *          BONN_NO_ERROR           : No errors occurred in function
 *          BONN_LAT_ERROR          : Latitude outside of valid range
 *                                      (-90 to 90 degrees)
 *          BONN_LON_ERROR          : Longitude outside of valid range
 *                                      (-180 to 360 degrees)
 *          BONN_EASTING_ERROR      : Easting outside of valid range
 *                                      (False_Easting +/- ~20,500,000 m,
 *                                       depending on ellipsoid parameters
 *                                       and Origin_Latitude)
 *          BONN_NORTHING_ERROR     : Northing outside of valid range
 *                                      (False_Northing +/- ~23,500,000 m,
 *                                       depending on ellipsoid parameters
 *                                       and Origin_Latitude)
 *          BONN_ORIGIN_LAT_ERROR   : Origin latitude outside of valid range
 *                                      (-90 to 90 degrees)
 *          BONN_CENT_MER_ERROR     : Central meridian outside of valid range
 *                                      (-180 to 360 degrees)
 *          BONN_A_ERROR            : Semi-major axis less than or equal to zero
 *          BONN_INV_F_ERROR        : Inverse flattening outside of valid range
 *									                    (250 to 350)
 *
 * REUSE NOTES
 *
 *    BONNE is intended for reuse by any application that performs a
 *    Bonne projection or its inverse.
 *    
 * REFERENCES
 *
 *    Further information on BONNE can be found in the Reuse Manual.
 *
 *    BONNE originated from :  U.S. Army Topographic Engineering Center
 *                             Geospatial Information Division
 *                             7701 Telegraph Road
 *                             Alexandria, VA  22310-3864
 *
 * LICENSES
 *
 *    None apply to this component.
 *
 * RESTRICTIONS
 *
 *    BONNE has no restrictions.
 *
 * ENVIRONMENT
 *
 *    BONNE was tested and certified in the following environments:
 *
 *    1. Solaris 2.5 with GCC 2.8.1
 *    2. MS Windows 95 with MS Visual C++ 6
 *
 * MODIFICATIONS
 *
 *    Date              Description
 *    ----              -----------
 *    04-16-99          Original Code
 *
 */
#include "sinusoid.h"

/***************************************************************************/
/*
 *                              DEFINES
 */

#define BONN_NO_ERROR           0x0000
#define BONN_LAT_ERROR          0x0001
#define BONN_LON_ERROR          0x0002
#define BONN_EASTING_ERROR      0x0004
#define BONN_NORTHING_ERROR     0x0008
#define BONN_ORIGIN_LAT_ERROR   0x0010
#define BONN_CENT_MER_ERROR     0x0020
#define BONN_A_ERROR            0x0040
#define BONN_INV_F_ERROR        0x0080

#include "projection.h"
/***************************************************************************/
/*
 *                              FUNCTION PROTOTYPES
 *                                for BONNE.C
 */

class CBonne :CProjection
{
public:
	/* Ellipsoid Parameters, default to WGS 84 */
	double Bonn_a;                 /* Semi-major axis of ellipsoid in meters */
	double Bonn_f;         /* Flattening of ellipsoid */
	double es2;        /* Eccentricity (0.08181919084262188000) squared  */
	double es4;         /* es2 * es2 */
	double es6;         /* es4 * es2 */
	double M1;               /* Bonn_M(Bonna,c0lat,c1s2lat,c2s4lat,c3s6lat) */
	double m1;               /* Bonn_m(coslat,sinlat,es2) */
	double c0;               /* 1 - es2 / 4.0 - 3.0 * es4 / 64.0 - 5.0 * es6 / 256.0 */
	double c1;             /* 3.0 * es2 / 8.0 + 3.0 * es4 / 32.0 + 45.0 * es6 / 1024.0 */
	double c2;          /* 15.0 * es4 / 256.0 + 45.0 * es6 / 1024.0 */
	double c3;          /* 35.0 * es6 / 3072.0 */
	double a0;             /* 3.0 * e1 / 2.0 - 27.0 * e3 / 32.0 */
	double a1;          /* 21.0 * e2 / 16.0 - 55.0 * e4 / 32.0 */
	double a2;          /* 151.0 * e3 / 96.0 */
	double a3;          /* 1097.0 * e4 / 512.0 */


	/* Bonne projection Parameters */
	double  Bonn_Origin_Lat;           /* Latitude of origin in radians     */
	double  Bonn_Origin_Long;                          /* Longitude of origin in radians    */
	double  Bonn_False_Northing;                       /* False northing in meters          */
	double  Bonn_False_Easting;                        /* False easting in meters           */
	double  Sin_Bonn_Origin_Lat;           /* sin(Bonn_Origin_Lat)              */
	double  Bonn_am1sin;                   /* Bonn_a * m1 / Sin_Bonn_Origin_Lat */

	/* Maximum variance for easting and northing values for WGS 84.
	 */
	double  Bonn_Max_Easting;
	double  Bonn_Min_Easting;
	double  Bonn_Delta_Northing;

	CSinusoidal objSinusoidal;

public:
	CBonne();
	~CBonne();
	long Set_Bonne_Parameters(double a,
		double f,
		double Origin_Latitude,
		double Central_Meridian,
		double False_Easting,
		double False_Northing);
	/*
	 * The function Set_Bonne_Parameters receives the ellipsoid parameters and
	 * Bonne projcetion parameters as inputs, and sets the corresponding state
	 * variables.  If any errors occur, the error code(s) are returned by the
	 * function, otherwise BONN_NO_ERROR is returned.
	 *
	 *    a                 : Semi-major axis of ellipsoid, in meters   (input)
	 *    f                 : Flattening of ellipsoid                   (input)
	 *    Origin_Latitude   : Latitude in radians at which the          (input)
	 *                          point scale factor is 1.0
	 *    Central_Meridian  : Longitude in radians at the center of     (input)
	 *                          the projection
	 *    False_Easting     : A coordinate value in meters assigned to the
	 *                          central meridian of the projection.     (input)
	 *    False_Northing    : A coordinate value in meters assigned to the
	 *                          origin latitude of the projection       (input)
	 */


	void Get_Bonne_Parameters(double *a,
		double *f,
		double *Origin_Latitude,
		double *Central_Meridian,
		double *False_Easting,
		double *False_Northing);
	/*
	 * The function Get_Bonne_Parameters returns the current ellipsoid
	 * parameters and Bonne projection parameters.
	 *
	 *    a                 : Semi-major axis of ellipsoid, in meters   (output)
	 *    f                 : Flattening of ellipsoid                   (output)
	 *    Origin_Latitude   : Latitude in radians at which the          (output)
	 *                          point scale factor is 1.0
	 *    Central_Meridian  : Longitude in radians at the center of     (output)
	 *                          the projection
	 *    False_Easting     : A coordinate value in meters assigned to the
	 *                          central meridian of the projection.     (output)
	 *    False_Northing    : A coordinate value in meters assigned to the
	 *                          origin latitude of the projection       (output)
	 */


	long Convert_Geodetic_To_Bonne(double Latitude,
		double Longitude,
		double *Easting,
		double *Northing);
	/*
	 * The function Convert_Geodetic_To_Bonne converts geodetic (latitude and
	 * longitude) coordinates to Bonne projection easting, and northing
	 * coordinates, according to the current ellipsoid and Bonne projection
	 * parameters.  If any errors occur, the error code(s) are returned by the
	 * function, otherwise BONN_NO_ERROR is returned.
	 *
	 *    Latitude          : Latitude (phi) in radians           (input)
	 *    Longitude         : Longitude (lambda) in radians       (input)
	 *    Easting           : Easting (X) in meters               (output)
	 *    Northing          : Northing (Y) in meters              (output)
	 */


	long Convert_Bonne_To_Geodetic(double Easting,
		double Northing,
		double *Latitude,
		double *Longitude);
	/*
	 * The function Convert_Bonne_To_Geodetic converts Bonne projection
	 * easting and northing coordinates to geodetic (latitude and longitude)
	 * coordinates, according to the current ellipsoid and Bonne projection
	 * coordinates.  If any errors occur, the error code(s) are returned by the
	 * function, otherwise BONN_NO_ERROR is returned.
	 *
	 *    Easting           : Easting (X) in meters                  (input)
	 *    Northing          : Northing (Y) in meters                 (input)
	 *    Latitude          : Latitude (phi) in radians              (output)
	 *    Longitude         : Longitude (lambda) in radians          (output)
	 */
};

#endif /* BONNE_H */
#endif //_STANDARD1_
