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
 *
 * MODIFICATIONS
 *
 *    Date              Description
 *    ----              -----------
 *    24-May-99         Original Code
 *
 */

/*                                  INCLUDES                                  */

#include "geoid.h"
#include <stdio.h>   /* standard C input/output library */
#include <math.h>    /* standard C math library */
#include <stdlib.h>  /* standard C general utility library */
#include <string.h>  /* standard C string handling library */
#include "TrUnivw.h"
#include "transform.h"

#ifndef LINUX_VER
//#include <windows.h>
//#include "CHARString.h"
#endif

#if !defined(LITTLE_ENDIAN)
#define LITTLE_ENDIAN
#endif
#define PI              3.1415926535897932384626433832795 /* PI     */

/*                                 FUNCTIONS                                  */

CGeoid::CGeoid()
{
	long Geoid_Initialized = 0;  /* indicates successful initialization */
}

CGeoid::~CGeoid()
{

}

long CGeoid::Initialize_Geoid(CCHARString strModuleDir)
/*
 * The function Initialize_Geoid reads geoid separation data from a file in
 * the current directory and builds the geoid separation table from it.  
 * If the separation file can not be found or accessed, an error code of 
 * GEOID_FILE_OPEN_ERROR is returned, If the separation file is incomplete 
 * or improperly formatted, an error code of GEOID_INITIALIZE_ERROR is returned, 
 * otherwise GEOID_NO_ERROR is returned.
 */
{
  int   ItemsRead = 0;
  long  ElevationsRead = 0;
  long  ItemsDiscarded = 0;
  long  num = 0;
  char FileName[256];
  CCHARString strFileName;
  //char  *PathName = getenv( "GEOID_DATA" );
  //char  *PathName = NULL;
  long error_code = GEOID_NO_ERROR;

  // new code
  char lpFileName[256];
  int length;
  int new_length = 0;
  int k, i;
  //char *new_path, *egm96_grd;
  char egm96_grd[11] = "egm96.grd";
  // end of new code
  if (Geoid_Initialized)
  {
      return (GEOID_NO_ERROR);
  }
    if (strModuleDir[strModuleDir.GetLength() - 1] != '\\' &&
        strModuleDir[strModuleDir.GetLength() - 1] != '/') 
        strModuleDir = strModuleDir + "/";
  
/*  Check the environment for a user provided path, else current directory;   */
/*  Build a File Name, including specified or default path:                   */

//  // new code
//#ifndef LINUX_VER
//	strFileName = strModuleDir + "egm96.grd";
//#else
//	strcpy( FileName, "./" );
//	strcat( FileName, "egm96.grd" );
//#endif
//  // end of new code
    strFileName = strModuleDir + "egm96.grd";
/*  Open the File READONLY, or Return Error Condition:                        */
	GeoidHeightFile = fopen(strFileName.GetCHAR(), "rb");
  if ( GeoidHeightFile == NULL)
  {
    error_code = GEOID_FILE_OPEN_ERROR;
	Geoid_Initialized = 0;
	//MessageBox(NULL, "GEOID_FILE_OPEN_ERROR", "", MB_OK);
	
	return error_code;
  }

/*  Skip the Header Line:                                                     */

  while ( num < NumbHeaderItems )
  {
    if (feof( GeoidHeightFile )) break;
    if (ferror( GeoidHeightFile )) break;
    GeoidHeightBuffer[num] = Read_Geoid_Height( &ItemsRead );
	ItemsDiscarded += ItemsRead;
    num++;
  }

/*  Determine if header read properly, or NOT:                                */

  if (GeoidHeightBuffer[0] !=  -90.0 ||
      GeoidHeightBuffer[1] !=   90.0 ||
      GeoidHeightBuffer[2] !=    0.0 ||
      GeoidHeightBuffer[3] !=  360.0 ||
      GeoidHeightBuffer[4] !=  ( 1.0 / ScaleFactor ) ||
      GeoidHeightBuffer[5] !=  ( 1.0 / ScaleFactor ) ||
      ItemsDiscarded != NumbHeaderItems)
  {
    fclose(GeoidHeightFile);
	return ( GEOID_INITIALIZE_ERROR );
  }

/*  Extract elements from the file:                                           */

  num = 0;
  while ( num < NumbGeoidElevs )
  {
    if (feof( GeoidHeightFile )) break;
    if (ferror( GeoidHeightFile )) break;
    GeoidHeightBuffer[num] = Read_Geoid_Height ( &ItemsRead );
    ElevationsRead += ItemsRead;
    num++;
  }

/*  Determine if all elevations of file read properly, or NOT:                */

  if (ElevationsRead != NumbGeoidElevs)
  {
    fclose(GeoidHeightFile);
	//MessageBox(NULL, "GEOID_INITIALIZE_ERROR 1", "", MB_OK);
    return ( GEOID_INITIALIZE_ERROR );
  }

  fclose(GeoidHeightFile);
  Geoid_Initialized = 1;
  return ( GEOID_NO_ERROR );
}

float CGeoid::Read_Geoid_Height ( int *NumRead )
/*
 * The private function Read_Geoid_Height returns the geoid height 
 * read from the geoid file. 4 bytes are read from the file and,
 * if necessary, the bytes are swapped.
 *
 *    NumRead             : Number of heights read from file         (output)
 *
 */
{
 	float result;
	char* swap = (char*)&result;
	char temp;
    *NumRead = fread( swap, 4, 1, GeoidHeightFile );
	
#ifdef LITTLE_ENDIAN
	temp = swap[0];
	swap[0] = swap[3];
	swap[3] = temp;
	temp = swap[1];
	swap[1] = swap[2];
	swap[2] = temp;
#endif
	return result;
}


long CGeoid::Get_Geoid_Height ( double Latitude,
                        double Longitude,
                        double *DeltaHeight )
/*
 * The private function Get_Geoid_Height returns the height of the 
 * WGS84 geiod above or below the WGS84 ellipsoid, 
 * at the specified geodetic coordinates,
 * using a grid of height adjustments from the EGM96 gravity model.
 *
 *    Latitude            : Geodetic latitude in radians           (input)
 *    Longitude           : Geodetic longitude in radians          (input)
 *    DeltaHeight         : Height Adjustment, in meters.          (output)
 *
 */
{
  long    Index;
  double DeltaX, DeltaY;
  double ElevationSE, ElevationSW, ElevationNE, ElevationNW;
  double LatitudeDD, LongitudeDD;
  double OffsetX, OffsetY;
  double PostX, PostY;
  double UpperY, LowerY;
  long Error_Code = 0;

  if (!Geoid_Initialized)
  {
    return (GEOID_NOT_INITIALIZED_ERROR);
  }
  if ((Latitude < -PI/2.0) || (Latitude > PI/2.0))
  { /* Latitude out of range */
    Error_Code |= GEOID_LAT_ERROR;
  }
  if ((Longitude < -PI) || (Longitude > (2*PI)))
  { /* Longitude out of range */
    Error_Code |= GEOID_LON_ERROR;
  }

  if (!Error_Code)
  { /* no errors */
    LatitudeDD  = Latitude  * 180.0 / PI;
    LongitudeDD = Longitude * 180.0 / PI;

    /*  Compute X and Y Offsets into Geoid Height Array:                          */

    if (LongitudeDD < 0.0)
    {
      OffsetX = ( LongitudeDD + 360.0 ) * ScaleFactor;
    }
    else
    {
      OffsetX = LongitudeDD * ScaleFactor;
    }
    OffsetY = ( 90.0 - LatitudeDD ) * ScaleFactor;

    /*  Find Four Nearest Geoid Height Cells for specified Latitude, Longitude;   */
    /*  Assumes that (0,0) of Geoid Height Array is at Northwest corner:          */

    PostX = floor( OffsetX );
    if ((PostX + 1) == NumbGeoidCols)
      PostX--;
    PostY = floor( OffsetY );
    if ((PostY + 1) == NumbGeoidRows)
      PostY--;

    Index = (long)(PostY * NumbGeoidCols + PostX);
    ElevationNW = GeoidHeightBuffer[ Index ];
    ElevationNE = GeoidHeightBuffer[ Index+ 1 ];

    Index = (long)((PostY + 1) * NumbGeoidCols + PostX);
    ElevationSW = GeoidHeightBuffer[ Index ];
    ElevationSE = GeoidHeightBuffer[ Index + 1 ];

    /*  Perform Bi-Linear Interpolation to compute Height above Ellipsoid:        */

    DeltaX = OffsetX - PostX;
    DeltaY = OffsetY - PostY;

    UpperY = ElevationNW + DeltaX * ( ElevationNE - ElevationNW );
    LowerY = ElevationSW + DeltaX * ( ElevationSE - ElevationSW );

    *DeltaHeight = UpperY + DeltaY * ( LowerY - UpperY );
  }
  return Error_Code;
}


long CGeoid::Convert_Ellipsoid_To_Geoid_Height ( double Latitude,
                                         double Longitude,
                                         double Ellipsoid_Height,
                                         double *Geoid_Height )
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
{
  double  DeltaHeight;
  long Error_Code;
  Error_Code = Get_Geoid_Height ( Latitude, Longitude, &DeltaHeight );
  *Geoid_Height = Ellipsoid_Height - DeltaHeight;
  return ( Error_Code );
}


long CGeoid::Convert_Geoid_To_Ellipsoid_Height ( double Latitude,
                                         double Longitude,
                                         double Geoid_Height,
                                         double *Ellipsoid_Height )
/*
 * The function Convert_Geoid_To_Ellipsoid_Height converts the specified WGS84
 * geoid height at the specified geodetic coordinates to the equivalent
 * ellipsoid height, using the EGM96 gravity model.
 *
 *    Latitude            : Geodetic latitude in radians           (input)
 *    Longitude           : Geodetic longitude in radians          (input)
 *    Ellipsoid_Height    : Ellipsoid height, in meters            (input)
 *    Geoid_Height        : Geoid height, in meters.               (output)
 *
 */
{
  double  DeltaHeight;
  long Error_Code;
  Error_Code = Get_Geoid_Height ( Latitude, Longitude, &DeltaHeight );
  *Ellipsoid_Height = Geoid_Height + DeltaHeight;
  return ( Error_Code );
}

void CGeoid::Return_Geoid_Error_Text(long status, char *String)
{
	String[0] = 0;
	//if((status & GEOID_NO_ERROR) == GEOID_NO_ERROR)
	//	strcat(String,"Geoid not Error | ");
	//if((status & GEOID_FILE_OPEN_ERROR) == GEOID_FILE_OPEN_ERROR)
	//	strcat(String,"Geoid file is not opened | ");
	//if((status & GEOID_INITIALIZE_ERROR) == GEOID_INITIALIZE_ERROR)
	//	strcat(String,"Geoid is not initialized | ");
	//if((status & GEOID_NOT_INITIALIZED_ERROR) == GEOID_NOT_INITIALIZED_ERROR)
	//	strcat(String,"Geoid is not initialized | ");
	//if((status & GEOID_LAT_ERROR) == GEOID_LAT_ERROR)
	//	strcat(String,"Error for geoid height in Latitude | ");
	//if((status & GEOID_LON_ERROR) == GEOID_LON_ERROR)
	//	strcat(String,"Error for geoid height in Longitude | ");
	//strcat(String, "\n");
	return;
}



long CGeoid::TransformAllHeight(void* g_Transform, int syst, int type, int width, int zmer, int shsyst, int thsyst,
	double &x, double &y, double &h, int nChoice)
{
    long nReturn = TRUNIVW_NO_ERROR;
	double trX = x, trY = y, trZ = h;
	bool bFindH = false;
	CTransform* objTransform = NULL;
	if (g_Transform != NULL)
		objTransform = (CTransform*)g_Transform;
	else
		return TRUNIVW_MODULE_ERROR;
    if (shsyst == thsyst ||
        (shsyst == HS_UNKNOWN_CODE || thsyst == HS_UNKNOWN_CODE)) return nReturn;
    if (h == 0.0) return nReturn;
	int nTempZone = ZONE_AUTO;
    nReturn = objTransform->Transform(syst, CS_WGS84_CODE, type, CT_BL_CODE, width, ZW_UNKNOWN_CODE, zmer, &nTempZone,
			HS_UNKNOWN_CODE, HS_UNKNOWN_CODE, &trX, &trY, &trZ);
	double DeltaHeight = VALUE_H_NOT_USED;
	int nTypeOfGeoid;
    nReturn = Get_Geoid_Height(trX, trY, &DeltaHeight);
	if (nReturn == 0)
	{
        double dblhNew = VALUE_H_NOT_USED;
        nReturn == objTransform->CalcHeight(shsyst, thsyst, CS_WGS84_CODE, CT_BL_CODE, ZW_UNKNOWN_CODE, ZONE_AUTO, trX, trY, trZ, dblhNew, DeltaHeight, GRD_HEIGHTTYPE_WGS_EVRS2000);
        if (type == CT_XYZ_CODE && nReturn == TRUNIVW_NO_ERROR)
        {
            nTempZone = ZONE_AUTO;
            nReturn = objTransform->Transform(syst, syst, type, CT_BL_CODE, width, ZW_UNKNOWN_CODE, zmer, &nTempZone,
                HS_UNKNOWN_CODE, HS_UNKNOWN_CODE, &x, &y, &h);
            h = dblhNew;
            nTempZone = ZONE_AUTO;
            nReturn = objTransform->Transform(syst, syst, CT_BL_CODE, type, ZW_UNKNOWN_CODE, ZW_UNKNOWN_CODE, ZONE_AUTO, &nTempZone,
                HS_UNKNOWN_CODE, HS_UNKNOWN_CODE, &x, &y, &h);
        }
        else
            h = dblhNew;
	}
	else
        nReturn = TRUNIVW_UNKNOWNGEOID_DH_ERROR;
	
	return nReturn;
}

//void CGeoid::SetLogFileName(CCHARString strLogFile)
//{
//	m_strLogFile = strLogFile;
//}
