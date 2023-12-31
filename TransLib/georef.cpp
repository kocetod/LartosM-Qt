#ifndef _STANDARD1_
/***************************************************************************/
/* RSC IDENTIFIER: GEOREF
 *
 * ABSTRACT
 *
 *    This component provides conversions from Geodetic coordinates (latitude
 *    and longitude in radians) to a GEOREF coordinate string.
 *
 * ERROR HANDLING
 *
 *    This component checks parameters for valid values.  If an invalid value
 *    is found, the error code is combined with the current error code using 
 *    the bitwise or.  This combining allows multiple error codes to be
 *    returned. The possible error codes are:
 *
 *          GEOREF_NO_ERROR          : No errors occurred in function
 *          GEOREF_LAT_ERROR         : Latitude outside of valid range 
 *                                      (-90 to 90 degrees)
 *          GEOREF_LON_ERROR         : Longitude outside of valid range
 *                                      (-180 to 360 degrees)
 *          GEOREF_STR_ERROR         : A GEOREF string error: string too long,
 *                                      string too short, or string length
 *                                      not even.
 *          GEOREF_STR_LAT_ERROR     : The latitude part of the GEOREF string
 *                                     (second or fourth character) is invalid.
 *          GEOREF_STR_LON_ERROR     : The longitude part of the GEOREF string
 *                                     (first or third character) is invalid.
 *          GEOREF_STR_LAT_MIN_ERROR : The latitude minute part of the GEOREF
 *                                      string is greater than 60.
 *          GEOREF_STR_LON_MIN_ERROR : The longitude minute part of the GEOREF
 *                                      string is greater than 60.
 *          GEOREF_PRECISION_ERROR   : The precision must be between 0 and 5 
 *                                      inclusive.
 *
 *
 * REUSE NOTES
 *
 *    GEOREF is intended for reuse by any application that performs a 
 *    conversion between Geodetic and GEOREF coordinates.
 *    
 * REFERENCES
 *
 *    Further information on GEOREF can be found in the Reuse Manual.
 *
 *    GEOREF originated from :  U.S. Army Topographic Engineering Center
 *                              Geospatial Information Division
 *                              7701 Telegraph Road
 *                              Alexandria, VA  22310-3864
 *
 * LICENSES
 *
 *    None apply to this component.
 *
 * RESTRICTIONS
 *
 *    GEOREF has no restrictions.
 *
 * ENVIRONMENT
 *
 *    GEOREF was tested and certified in the following environments:
 *
 *    1. Solaris 2.5 with GCC version 2.8.1
 *    2. Windows 95 with MS Visual C++ version 6
 *
 * MODIFICATIONS
 *
 *    Date              Description
 *    ----              -----------
 *    20-02-97          Original Code
 */


/***************************************************************************/
/*
 *                               INCLUDES
 */

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "georef.h"
#include <algorithm>
/*
 *  ctype.h    - Standard C character handling library
 *  math.h     - Standard C math library
 *  stdio.h    - Standard C input/output library
 *  stdlib.h   - Standard C general utility library
 *  string.h   - Standard C string handling library
 *  georef.h   - for prototype error checking
 */


/***************************************************************************/
/*
 *                              DEFINES
 */

#define TRUE                1
#define FALSE               0
#define LATITUDE_LOW      -90  /* Minimum latitude                      */
#define LATITUDE_HIGH      90  /* Maximum latitude                      */
#define LONGITUDE_LOW    -180  /* Minimum longitude                     */
#define LONGITUDE_HIGH    360  /* Maximum longitude                     */
#define MIN_PER_DEG        60  /* Number of minutes per degree          */
#define GEOREF_MINIMUM      4  /* Minimum number of chars for GEOREF    */
#define GEOREF_MAXIMUM     14  /* Maximum number of chars for GEOREF    */
#define GEOREF_LETTERS      4  /* Number of letters in GEOREF string    */
#define MAX_PRECISION       5  /* Maximum precision of minutes part     */
#define LETTER_I            8  /* Index for letter I                    */
#define LETTER_M           12  /* Index for letter M                    */
#define LETTER_O           14  /* Index for letter O                    */
#define LETTER_Q           16  /* Index for letter Q                    */
#define LETTER_Z           25  /* Index for letter Z                    */
#define LETTER_A_OFFSET    65  /* Letter A offset in character set      */
#define ZERO_OFFSET        48  /* Number zero offset in character set   */
#define PI    3.1415926535897932384626433832795  /* PI                  */
#define DEGREE_TO_RADIAN   (PI / 180.0)
#define RADIAN_TO_DEGREE   (180.0 / PI)
#define QUAD               15  /* Degrees per grid square               */
#define ROUND_ERROR  0.0000005 /* Rounding factor                       */


/***************************************************************************/
/*
 *                              FUNCTIONS     
 */
CGeoref::CGeoref()
{

}

CGeoref::~CGeoref()
{

}

long CGeoref::Extract_Degrees (char *georef,
                      double *latitude,
                      double *longitude)
{ /* BEGIN Extract_Degrees */
/*    
 *  This function extracts the latitude and longitude degree parts of the 
 *  GEOREF string.  The latitude and longitude degree parts are the first four
 *  characters.
 *
 *    georef        : GEOREF string             (input)
 *    latitude      : Latitude in degrees       (output)
 *    longitude     : Longitude in degrees      (output)
 */
  long i;                             /* counter in for loops            */
  long temp_char;                     /* temporary character             */
  long letter_number[GEOREF_LETTERS]; /* number corresponding to letter  */
  long error_code = GEOREF_NO_ERROR;

  for (i=0;i<GEOREF_LETTERS;i++)
  {
    temp_char = toupper(georef[i]);
    temp_char = temp_char - LETTER_A_OFFSET;
    if ((!isalpha(georef[i]))
        || (temp_char == LETTER_I)
        || (temp_char == LETTER_O))
    {
      if ((i == 0) || (i == 2))
        error_code |= GEOREF_STR_LON_ERROR;
      else
        error_code |= GEOREF_STR_LAT_ERROR;
    }
    letter_number[i] = temp_char;
  }
  for (i=0;i<4;i++)
  {
    if (letter_number[i] > LETTER_O)
      letter_number[i] -= 2;
    else if (letter_number[i] > LETTER_I)
      letter_number[i] -= 1;
  }
  if ((letter_number[0] > 23) || (letter_number[2] > 14))
    error_code |= GEOREF_STR_LON_ERROR;
  if ((letter_number[1] > 11) || (letter_number[3] > 14))
    error_code |= GEOREF_STR_LAT_ERROR;
  *latitude = (double)(letter_number[1]) * QUAD + (double)(letter_number[3]);
  *longitude = (double)(letter_number[0]) * QUAD + (double)(letter_number[2]);
  return (error_code);
} /* END Extract_Degrees */


long CGeoref::Extract_Minutes (char *georef,
                      long start,
                      long length,
                      long ERROR_TYPE,
                      double *minutes)
{ /* BEGIN Extract_Minutes */
/*    
 *  This function extracts the minutes from the GEOREF string.  The minutes
 *  part begins at position start and has length length.  The ERROR_TYPE is
 *  to allow this function to work with both latitude and longitude minutes.
 *
 *    georef : GEOREF string                                        (input)
 *    start  : Start position in the GEOREF string                  (input)
 *    length : length of minutes in the GEOREF string               (input)
 *    ERROR_TYPE  : has a value of either GEOREF_STR_LAT_MIN_ERROR  (input)
 *                    or GEOREF_STR_LON_MIN_ERROR
 *    minutes: minute part                                          (output)
 */
  long i;                    /* counter in for loop  */
  long error_code = GEOREF_NO_ERROR;
  int MaxSize = (GEOREF_MAXIMUM - GEOREF_LETTERS) / 2 + 1;
 #ifdef WINDOWS_VER
  char temp_str[(GEOREF_MAXIMUM - GEOREF_LETTERS) / 2 + 1];
#else
  char temp_str[MaxSize];
#endif
  for (i=0;i<length;i++)
  {
    if (i < MaxSize && isdigit(georef[start+i]))
      temp_str[i] = georef[start+i];
    else
      error_code |= ERROR_TYPE;
  }
  length = std::min(length, long(MaxSize - 1));
  temp_str[length] = 0;
  *minutes = (double)atof(temp_str);  /* need atof, atoi can't handle 59999 */
  while (length > 2)
  {
    *minutes = *minutes / 10;
    length = length - 1;
  }
  if (*minutes > (double)MIN_PER_DEG)
    error_code |= ERROR_TYPE;
  return (error_code);
} /* END OF Extract_Minutes */


long CGeoref::Round_GEOREF (double value)
/* Round value to nearest integer, using standard engineering rule */
{ /* Round_GEOREF */
  double ivalue;
  long ival;
  double fraction = modf (value, &ivalue);
  ival = (long)(ivalue);
  if ((fraction > 0.5) || ((fraction == 0.5) && (ival%2 == 1)))
    ival++;
  return (ival);
} /* Round_GEOREF */


void CGeoref::Convert_Minutes_To_String(double minutes,
                               long precision,
                               char *str)
{ /* BEGIN Convert_Minutes_To_String */
/*    
 *  This function converts minutes to a string of length precision.
 *
 *    minutes       : Minutes to be converted                  (input)
 *    precision     : Length of resulting string               (input)
 *    str           : String to hold converted minutes         (output)
 */
  double divisor;
  long min;
  divisor = pow (10.0, (5 - precision));
  if (minutes == 60.0)
    minutes = 59.999;
  minutes = minutes * 1000;
  min = Round_GEOREF (minutes/divisor);
  sprintf (str, "%*.*ld", precision, precision, min);
  if (precision == 1)
    strcat (str, "0");
} /* END Convert_Minutes_To_String */


long CGeoref::Convert_GEOREF_To_Geodetic (char *georef,
                                 double *latitude, 
                                 double *longitude)
{ /* BEGIN Convert_GEOREF_To_Geodetic */
/*
 *  This function converts a GEOREF coordinate string to Geodetic (latitude
 *  and longitude in radians) coordinates.
 *
 *    georef    : GEOREF coordinate string.     (input)
 *    latitude  : Latitude in radians.          (output)
 *    longitude : Longitude in radians.         (output)
 *
 *    CALLS THE FOLLOWING FUNCTIONS:
 *
 *    Extract_Degrees
 *    Extract_Minutes
 */
  long start;                /* Position in the GEOREF string                */
  long minutes_length;       /* length of minutes in the GEOREF string       */
  long georef_length;        /* length of GEOREF string                      */
  double origin_long;       /* Origin longitude                             */
  double origin_lat;        /* Origin latitude                              */
  double long_minutes;      /* Longitude minute part of GEOREF              */
  double lat_minutes;       /* Latitude minute part of GEOREF               */
  long error_code = GEOREF_NO_ERROR;

  origin_long = (double)LONGITUDE_LOW;
  origin_lat = (double)LATITUDE_LOW;
  georef_length = strlen(georef);
  if ((georef_length < GEOREF_MINIMUM) || (georef_length > GEOREF_MAXIMUM) 
      || ((georef_length % 2) != 0))
  {
    error_code |= GEOREF_STR_ERROR;
  }
  if (!error_code)
  {
    error_code |= Extract_Degrees(georef,latitude,longitude);
    start = GEOREF_LETTERS;
    minutes_length = (georef_length - start) / 2;
    if (!error_code)
    {
      error_code |= Extract_Minutes(georef, start, minutes_length, 
                                    GEOREF_STR_LON_MIN_ERROR, &long_minutes);
      if (!error_code)
      {
        error_code |= Extract_Minutes(georef, (start+minutes_length),
                                      minutes_length, GEOREF_STR_LAT_MIN_ERROR, &lat_minutes);
        *latitude = *latitude + origin_lat + lat_minutes / (double)MIN_PER_DEG;
        *longitude = *longitude + origin_long + long_minutes / (double)MIN_PER_DEG;
        *latitude = *latitude * DEGREE_TO_RADIAN;
        *longitude = *longitude * DEGREE_TO_RADIAN;
      }
    }
  }
  return (error_code);
} /* END OF Convert_GEOREF_To_Geodetic */


long CGeoref::Convert_Geodetic_To_GEOREF (double latitude,
                                 double longitude,
                                 long precision,
                                 char *georef)
{ /* BEGIN Convert_Geodetic_To_GEOREF */
/*   
 *  This function converts Geodetic (latitude and longitude in radians)
 *  coordinates to a GEOREF coordinate string.  Precision specifies the
 *  number of digits in the GEOREF string for latitude and longitude:
 *                                  0 for nearest degree
 *                                  1 for nearest ten minutes
 *                                  2 for nearest minute
 *                                  3 for nearest tenth of a minute
 *                                  4 for nearest hundredth of a minute
 *                                  5 for nearest thousandth of a minute
 *
 *    latitude  : Latitude in radians.                   (input)
 *    longitude : Longitude in radians.                  (input)
 *    precision : Precision specified by the user.       (input)
 *    georef    : GEOREF coordinate string.              (output)
 *
 *    CALLS THE FOLLOWING FUNCTIONS:
 *
 *    Convert_Minutes_To_String
 */

  double long_min;                        /* GEOREF longitude minute part   */
  double lat_min;                         /* GEOREF latitude minute part    */
  double origin_long;                     /* Origin longitude (-180 degrees)*/
  double origin_lat;                      /* Origin latitude (-90 degrees)  */
  long letter_number[GEOREF_LETTERS + 1]; /* GEOREF letters                 */
  char long_min_str[MAX_PRECISION + 1];   /* Longitude minute string        */
  char lat_min_str[MAX_PRECISION + 1];    /* Latitude minute string         */
  long i;                                 /* counter in for loop            */
  long error_code = GEOREF_NO_ERROR;

  latitude = latitude * RADIAN_TO_DEGREE;
  longitude = longitude * RADIAN_TO_DEGREE;
  if ((latitude < (double)LATITUDE_LOW) 
      || (latitude > (double)LATITUDE_HIGH))
    error_code |= GEOREF_LAT_ERROR;
  if ((longitude < (double)LONGITUDE_LOW) 
      || (longitude > (double)LONGITUDE_HIGH))
    error_code |= GEOREF_LON_ERROR;
  if ((precision < 0) || (precision > MAX_PRECISION))
    error_code |= GEOREF_PRECISION_ERROR;
  if (!error_code)
  {
    if (longitude > 180)
      longitude -= 360;
    origin_long = (double)LONGITUDE_LOW;
    origin_lat = (double)LATITUDE_LOW;
    letter_number[0] = (long)((longitude-origin_long) / QUAD + ROUND_ERROR);
    longitude = longitude - ((double)letter_number[0] * QUAD + origin_long);
    letter_number[2] = (long)(longitude + ROUND_ERROR);
    long_min = (longitude - (double)letter_number[2]) * (double)MIN_PER_DEG;
    letter_number[1] = (long)((latitude - origin_lat) / QUAD + ROUND_ERROR);
    latitude = latitude - ((double)letter_number[1] * QUAD + origin_lat);
    letter_number[3] = (long)(latitude + ROUND_ERROR);
    lat_min = (latitude - (double)letter_number[3]) * (double)MIN_PER_DEG;
    for (i = 0;i < 4; i++)
    {
      if (letter_number[i] >= LETTER_I)
        letter_number[i] += 1;
      if (letter_number[i] >= LETTER_O)
        letter_number[i] += 1;
    }

    if (letter_number[0] == 26)
    { /* longitude of 180 degrees */
      letter_number[0] = LETTER_Z;
      letter_number[2] = LETTER_Q;
      long_min = 59.999;
    }
    if (letter_number[1] == 13)
    { /* latitude of 90 degrees */
      letter_number[1] = LETTER_M;
      letter_number[3] = LETTER_Q;
      lat_min = 59.999;
    }

    for (i=0;i<4;i++)
      georef[i] = (char)(letter_number[i] + LETTER_A_OFFSET);
    georef[4] = 0;
    Convert_Minutes_To_String(long_min,precision,long_min_str);
    Convert_Minutes_To_String(lat_min,precision,lat_min_str);
    strcat(georef,long_min_str);
    strcat(georef,lat_min_str);
  }
  return (error_code);
} /* END OF Convert_Geodetic_To_GEOREF */
#endif //_STANDARD1_
