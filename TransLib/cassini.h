#ifndef _STANDARD1_
#ifndef CASSINI_H
  #define CASSINI_H

/***************************************************************************/
/* RSC IDENTIFIER: CASSINI
 *
 * ABSTRACT
 *
 *    This component provides conversions between Geodetic coordinates 
 *    (latitude and longitude in radians) and Cassini projection coordinates
 *    (easting and northing in meters).
 *
 * ERROR HANDLING
 *
 *    This component checks parameters for valid values.  If an invalid value
 *    is found, the error code is combined with the current error code using 
 *    the bitwise or.  This combining allows multiple error codes to be
 *    returned. The possible error codes are:
 *
 *          CASS_NO_ERROR           : No errors occurred in function
 *          CASS_LAT_ERROR          : Latitude outside of valid range
 *                                      (-90 to 90 degrees)
 *          CASS_LON_ERROR          : Longitude outside of valid range
 *                                      (-180 to 360 degrees)
 *          CASS_EASTING_ERROR      : Easting outside of valid range
 *                                      (False_Easting +/- ~20,000,000 m,
 *                                       depending on ellipsoid parameters
 *                                       and Origin_Latitude)
 *          CASS_NORTHING_ERROR     : Northing outside of valid range
 *                                      (False_Northing +/- ~57,000,000 m,
 *                                       depending on ellipsoid parameters
 *                                       and Origin_Latitude)
 *          CASS_ORIGIN_LAT_ERROR   : Origin latitude outside of valid range
 *                                      (-90 to 90 degrees)
 *          CASS_CENT_MER_ERROR     : Central meridian outside of valid range
 *                                      (-180 to 360 degrees)
 *          CASS_A_ERROR            : Semi-major axis less than or equal to zero
 *          CASS_INV_F_ERROR        : Inverse flattening outside of valid range
 *									                    (250 to 350)
 *			CASS_LON_WARNING        : Distortion will result if longitude is more
 *                                      than 4 degrees from the Central Meridian
 *
 * REUSE NOTES
 *
 *    CASSINI is intended for reuse by any application that performs a
 *    Cassini projection or its inverse.
 *    
 * REFERENCES
 *
 *    Further information on CASSINI can be found in the Reuse Manual.
 *
 *    CASSINI originated from :  U.S. Army Topographic Engineering Center
 *                               Geospatial Information Division
 *                               7701 Telegraph Road
 *                               Alexandria, VA  22310-3864
 *
 * LICENSES
 *
 *    None apply to this component.
 *
 * RESTRICTIONS
 *
 *    CASSINI has no restrictions.
 *
 * ENVIRONMENT
 *
 *    CASSINI was tested and certified in the following environments:
 *
 *    1. Solaris 2.5 with GCC 2.8.1
 *    2. MS Windows 95 with MS Visual C++ 6
 *
 * MODIFICATIONS
 *
 *    Date              Description
 *    ----              -----------
 *    04/16/99          Original Code
 *
 */


/***************************************************************************/
/*
 *                              DEFINES
 */

  #define CASS_NO_ERROR           0x0000
  #define CASS_LAT_ERROR          0x0001
  #define CASS_LON_ERROR          0x0002
  #define CASS_EASTING_ERROR      0x0004
  #define CASS_NORTHING_ERROR     0x0008
  #define CASS_ORIGIN_LAT_ERROR   0x0010
  #define CASS_CENT_MER_ERROR     0x0020
  #define CASS_A_ERROR            0x0040
  #define CASS_INV_F_ERROR        0x0080
  #define CASS_LON_WARNING        0x0100

#include "projection.h"
/***************************************************************************/
/*
 *                              FUNCTION PROTOTYPES
 *                                for CASSINI.C
 */
class CCassini :CProjection
{
public:
	/* Ellipsoid Parameters, default to WGS 84 */
	double Cass_a;                      /* Semi-major axis of ellipsoid in meters */
	double Cass_f;              /* Flattening of ellipsoid */
	double es2;             /* Eccentricity (0.08181919084262188000) squared  */
	double es4;               /* es2 * es2 */
	double es6;              /* es4 * es2 */
	double M0;
	double c0;                    /* 1 - es2 / 4.0 - 3.0 * es4 / 64.0 - 5.0 * es6 / 256.0 */
	double c1;                  /* 3.0 * es2 / 8.0 + 3.0 * es4 / 32.0 + 45.0 * es6 / 1024.0 */
	double c2;               /* 15.0 * es4 / 256.0 + 45.0 * es6 / 1024.0 */
	double c3;               /* 35.0 * es6 / 3072.0 */
	double one_MINUS_es2;         /* 1.0 - es2 */
	double a0;                  /* 3.0 * e1 / 2.0 - 27.0 * e3 / 32.0 */
	double a1;               /* 21.0 * e2 / 16.0 - 55.0 * e4 / 32.0 */
	double a2;               /* 151.0 * e3 / 96.0 */
	double a3;               /* 1097.0 * e4 /512.0 */

	/* Cassini projection Parameters */
	double Cass_Origin_Lat;                   /* Latitude of origin in radians     */
	double Cass_Origin_Long;                  /* Longitude of origin in radians    */
	double Cass_False_Northing;               /* False northing in meters          */
	double Cass_False_Easting;                /* False easting in meters           */

	/* Maximum variance for easting and northing values for WGS 84.
	 */
	double Cass_Min_Easting;
	double Cass_Max_Easting;
	double Cass_Min_Northing;
	double Cass_Max_Northing;

public:
	CCassini();
	~CCassini();
	long Set_Cassini_Parameters(double a,
		double f,
		double Origin_Latitude,
		double Central_Meridian,
		double False_Easting,
		double False_Northing);
	/*
	 * The function Set_Cassini_Parameters receives the ellipsoid parameters and
	 * Cassini projcetion parameters as inputs, and sets the corresponding state
	 * variables.  If any errors occur, the error code(s) are returned by the
	 * function, otherwise CASS_NO_ERROR is returned.
	 *
	 *    a                 : Semi-major axis of ellipsoid, in meters   (input)
	 *    f                 : Flattening of ellipsoid						        (input)
	 *    Origin_Latitude   : Latitude in radians at which the          (input)
	 *                          point scale factor is 1.0
	 *    Central_Meridian  : Longitude in radians at the center of     (input)
	 *                          the projection
	 *    False_Easting     : A coordinate value in meters assigned to the
	 *                          central meridian of the projection.     (input)
	 *    False_Northing    : A coordinate value in meters assigned to the
	 *                          origin latitude of the projection       (input)
	 */


	void Get_Cassini_Parameters(double *a,
		double *f,
		double *Origin_Latitude,
		double *Central_Meridian,
		double *False_Easting,
		double *False_Northing);
	/*
	 * The function Get_Cassini_Parameters returns the current ellipsoid
	 * parameters, and Cassini projection parameters.
	 *
	 *    a                 : Semi-major axis of ellipsoid, in meters   (output)
	 *    f                 : Flattening of ellipsoid						        (output)
	 *    Origin_Latitude   : Latitude in radians at which the          (output)
	 *                          point scale factor is 1.0
	 *    Central_Meridian  : Longitude in radians at the center of     (output)
	 *                          the projection
	 *    False_Easting     : A coordinate value in meters assigned to the
	 *                          central meridian of the projection.     (output)
	 *    False_Northing    : A coordinate value in meters assigned to the
	 *                          origin latitude of the projection       (output)
	 */


	long Convert_Geodetic_To_Cassini(double Latitude,
		double Longitude,
		double *Easting,
		double *Northing);
	/*
	 * The function Convert_Geodetic_To_Cassini converts geodetic (latitude and
	 * longitude) coordinates to Cassini projection easting, and northing
	 * coordinates, according to the current ellipsoid and Cassini projection
	 * parameters.  If any errors occur, the error code(s) are returned by the
	 * function, otherwise CASS_NO_ERROR is returned.
	 *
	 *    Latitude          : Latitude (phi) in radians           (input)
	 *    Longitude         : Longitude (lambda) in radians       (input)
	 *    Easting           : Easting (X) in meters               (output)
	 *    Northing          : Northing (Y) in meters              (output)
	 */


	long Convert_Cassini_To_Geodetic(double Easting,
		double Northing,
		double *Latitude,
		double *Longitude);
	/*
	 * The function Convert_Cassini_To_Geodetic converts Cassini projection
	 * easting and northing coordinates to geodetic (latitude and longitude)
	 * coordinates, according to the current ellipsoid and Cassini projection
	 * coordinates.  If any errors occur, the error code(s) are returned by the
	 * function, otherwise CASS_NO_ERROR is returned.
	 *
	 *    Easting           : Easting (X) in meters                  (input)
	 *    Northing          : Northing (Y) in meters                 (input)
	 *    Latitude          : Latitude (phi) in radians              (output)
	 *    Longitude         : Longitude (lambda) in radians          (output)
	 */

};

#endif /* CASSINI_H */
#endif //_STANDARD1_
