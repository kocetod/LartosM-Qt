#ifndef GEOID_H
#define GEOID_H

/****************************************************************************/
/* RSC IDENTIFIER:  Geoid
 *
 * ABSTRACT
 *
 *    The purpose of GEOID is to support conversions between WGS84 ellipsoid
 *    heights and WGS84 geoid heights.
 *
 *
 * ERROR HANDLING
 *
 *    This component checks parameters for valid values.  If an invalid value
 *    is found, the error code is combined with the current error code using 
 *    the bitwise or.  This combining allows multiple error codes to be
 *    returned. The possible error codes are:
 *
 *  GEOID_NO_ERROR               : No errors occured in function
 *  GEOID_FILE_OPEN_ERROR        : Geoid file opening error
 *  GEOID_INITIALIZE_ERROR       : Geoid seoaration database can not initialize
 *  GEOID_NOT_INITIALIZED_ERROR  : Geoid separation database not initialized properly
 *  GEOID_LAT_ERROR              : Latitude out of valid range
 *                                 (-90 to 90 degrees)
 *  GEOID_LON_ERROR              : Longitude out of valid range
 *                                 (-180 to 360 degrees)
 *
 * REUSE NOTES
 *
 *    Geoid is intended for reuse by any application that requires conversion
 *    between WGS84 ellipsoid heights and WGS84 geoid heights.
 *     
 * REFERENCES
 *
 *    Further information on Geoid can be found in the Reuse Manual.
 *
 *    Geoid originated from :  U.S. Army Topographic Engineering Center
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
 *    Geoid has no restrictions.
 *
 * ENVIRONMENT
 *
 *    Geoid was tested and certified in the following environments
 *
 *    1. Solaris 2.5 with GCC 2.8.1
 *    2. MS Windows 95 with MS Visual C++ 6
 *
 * MODIFICATIONS
 *
 *    Date              Description
 *    ----              -----------
 *    24-May-99         Original Code
 *
 */

#include <stdio.h>   /* standard C input/output library */
#include "General/CHARString.h"
/***************************************************************************/
/*
 *                               GLOBALS
 */

#define GEOID_NO_ERROR              0x0000
#define GEOID_FILE_OPEN_ERROR       0x0001
#define GEOID_INITIALIZE_ERROR      0x0002
#define GEOID_NOT_INITIALIZED_ERROR 0x0004
#define GEOID_LAT_ERROR             0x0008
#define GEOID_LON_ERROR             0x0010

#define NumbGeoidCols 1441   /* 360 degrees of longitude at 15 minute spacing */
#define NumbGeoidRows  721   /* 180 degrees of latitude  at 15 minute spacing */
#define NumbHeaderItems 6    /* min, max lat, min, max long, lat, long spacing*/
#define ScaleFactor     4    /* 4 grid cells per degree at 15 minute spacing  */
#define NumbGeoidElevs NumbGeoidCols * NumbGeoidRows


/***************************************************************************/
/*
 *                          FUNCTION PROTOTYPES
 *                             for ellipse.c
 */

class CGeoid
{
private:
	FILE *GeoidHeightFile;
public:
	float GeoidHeightBuffer[NumbGeoidElevs];
	long Geoid_Initialized;  /* indicates successful initialization */
	//CCHARString m_strLogFile;
public:
	CGeoid();
	~CGeoid();
	/* Function used to read from the geoid height file */
	float Read_Geoid_Height(int *NumRead);
  long Initialize_Geoid (CCHARString strModuleDir);
/*
 * The function Initialize_Geiud reads geoid separation data from a file in
 * the current directory and builds the geoid separation table from it.  If an
 * error occurs, the error code is returned, otherwise GEOID_NO_ERROR is 
 * returned.
 */

  long Convert_Ellipsoid_To_Geoid_Height (double Latitude,
                                          double Longitude,
                                          double Ellipsoid_Height,
                                          double *Geoid_Height);
/*
 * The function Convert_Ellipsoid_To_Geoid_Height converts the specified WGS84
 * ellipsoid height at the specified geodetic coordinates to the equivalent
 * geoid height, using the EGM96 gravity model.
 *
 *    Latitude            : Geodetic latitude in radians           (input)
 *    Longitude           : Geodetic longitude in radians          (input)
 *    Ellipsoid_Height    : Ellipsoid height, in meters            (input)
 *    Geoid_Height        : Geoid height, in meters.               (output)
 *
 */

  long Convert_Geoid_To_Ellipsoid_Height (double Latitude,
                                          double Longitude,
                                          double Geoid_Height,
                                          double *Ellipsoid_Height);
/*
 * The function Convert_Geoid_To_Ellipsoid_Height converts the specified WGS84
 * geoid height at the specified geodetic coordinates to the equivalent
 * ellipsoid height, using the EGM96 gravity model.
 *
 *    Latitude            : Geodetic latitude in radians           (input)
 *    Longitude           : Geodetic longitude in radians          (input)
 *    Geoid_Height        : Geoid height, in meters                (input)
 *    Ellipsoid_Height    : Ellipsoid height, in meters.           (output)
 *
 */

  long Get_Geoid_Height ( double Latitude,
                        double Longitude,
                        double *DeltaHeight );
/*
 * The function Get_Geoid_Height returns the height of the 
 * WGS84 geiod above or below the WGS84 ellipsoid, 
 * at the specified geodetic coordinates,
 * using a grid of height adjustments from the EGM96 gravity model.
 *
 *    Latitude            : Geodetic latitude in radians           (input)
 *    Longitude           : Geodetic longitude in radians          (input)
 *    DeltaHeight         : Height Adjustment, in meters.          (output)
 *
 */

	void Return_Geoid_Error_Text(long status, char *String);
//Return Geoid Errors
	long TransformAllHeight(void* g_Transform, int syst, int type, int width, int zmer, int shsyst, int thsyst,
		double &x, double &y, double &h, int nChoice);
	//void SetLogFileName(CCHARString strLogFile);
};

#endif /* GEOID_H */
