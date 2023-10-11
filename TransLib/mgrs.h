#ifndef MGRS_H
  #define MGRS_H

/***************************************************************************/
/* RSC IDENTIFIER:  MGRS
 *
 * ABSTRACT
 *
 *    This component converts between geodetic coordinates (latitude and 
 *    longitude) and Military Grid Reference System (MGRS) coordinates. 
 *
 * ERROR HANDLING
 *
 *    This component checks parameters for valid values.  If an invalid value
 *    is found, the error code is combined with the current error code using 
 *    the bitwise or.  This combining allows multiple error codes to be
 *    returned. The possible error codes are:
 *
 *          MGRS_NO_ERROR          : No errors occurred in function
 *          MGRS_LAT_ERROR         : Latitude outside of valid range 
 *                                    (-90 to 90 degrees)
 *          MGRS_LON_ERROR         : Longitude outside of valid range
 *                                    (-180 to 360 degrees)
 *          MGRS_STR_ERROR         : An MGRS string error: string too long,
 *                                    too short, or badly formed
 *          MGRS_PRECISION_ERROR   : The precision must be between 0 and 5 
 *                                    inclusive.
 *          MGRS_A_ERROR           : Semi-major axis less than or equal to zero
 *          MGRS_INV_F_ERROR       : Inverse flattening outside of valid range
 *									                  (250 to 350)
 *          MGRS_EASTING_ERROR     : Easting outside of valid range
 *                                    (100,000 to 900,000 meters for UTM)
 *                                    (0 to 4,000,000 meters for UPS)
 *          MGRS_NORTHING_ERROR    : Northing outside of valid range
 *                                    (0 to 10,000,000 meters for UTM)
 *                                    (0 to 4,000,000 meters for UPS)
 *          MGRS_ZONE_ERROR        : Zone outside of valid range (1 to 60)
 *          MGRS_HEMISPHERE_ERROR  : Invalid hemisphere ('N' or 'S')
 *
 * REUSE NOTES
 *
 *    MGRS is intended for reuse by any application that does conversions
 *    between geodetic coordinates and MGRS coordinates.
 *
 * REFERENCES
 *
 *    Further information on MGRS can be found in the Reuse Manual.
 *
 *    MGRS originated from : U.S. Army Topographic Engineering Center
 *                           Geospatial Information Division
 *                           7701 Telegraph Road
 *                           Alexandria, VA  22310-3864
 *
 * LICENSES
 *
 *    None apply to this component.
 *
 * RESTRICTIONS
 *
 *
 * ENVIRONMENT
 *
 *    MGRS was tested and certified in the following environments:
 *
 *    1. Solaris 2.5 with GCC version 2.8.1
 *    2. Windows 95 with MS Visual C++ version 6
 *
 * MODIFICATIONS
 *
 *    Date              Description
 *    ----              -----------
 *    16-11-94          Original Code
 *    15-09-99          Reengineered upper layers
 *
 */

/***************************************************************************/
/*
 *                              DEFINES
 */

  #define MGRS_NO_ERROR                0x0000
  #define MGRS_LAT_ERROR               0x0001
  #define MGRS_LON_ERROR               0x0002
  #define MGRS_STRING_ERROR            0x0004
  #define MGRS_PRECISION_ERROR         0x0008
  #define MGRS_A_ERROR                 0x0010
  #define MGRS_INV_F_ERROR             0x0020
  #define MGRS_EASTING_ERROR           0x0040
  #define MGRS_NORTHING_ERROR          0x0080
  #define MGRS_ZONE_ERROR              0x0100
  #define MGRS_HEMISPHERE_ERROR        0x0200

	#define MGRS_LETTERS  3  /* NUMBER OF LETTERS IN MGRS              */

//#include "CHARString.h"
/***************************************************************************/
/*
 *                              FUNCTION PROTOTYPES
 */

class CMGRS
{
private:
	double DEGRAD; /* PI/180                          */
	double R3; /* RADIANS FOR  3 DEGREES          */
	double R8; /* RADIANS FOR  8 DEGREES          */
	double R9; /* RADIANS FOR  9 DEGREES          */
	double R21; /* RADIANS FOR  21 DEGREES         */
	double R33; /* RADIANS FOR  33 DEGREES         */
	double R56; /* RADIANS FOR  56 DEGREES         */
	double R64; /* RADIANS FOR  64 DEGREES         */
	double R72; /* RADIANS FOR  72 DEGREES         */
	double R80; /* RADIANS FOR  80 DEGREES         */
	int UPS_SOUTH;    /* UPS COORDINATE IN SOUTHERN HEMISPHERE */
	int UPS_NORTH;    /* UPS COORDINATE IN NORTHERN HEMISPHERE */
	int UTM;    /* UTM COORDINATE                        */
	char ALBET[28]; /* ALPHABET       */
	int LETTER_A;   /* ARRAY INDEX FOR LETTER A               */
	int LETTER_B;   /* ARRAY INDEX FOR LETTER B               */
	int LETTER_C;   /* ARRAY INDEX FOR LETTER C               */
	int LETTER_D;   /* ARRAY INDEX FOR LETTER D               */
	int LETTER_E;   /* ARRAY INDEX FOR LETTER E               */
	int LETTER_H;  /* ARRAY INDEX FOR LETTER H               */
	int LETTER_I;   /* ARRAY INDEX FOR LETTER I               */
	int LETTER_J;   /* ARRAY INDEX FOR LETTER J               */
	int LETTER_L;   /* ARRAY INDEX FOR LETTER L               */
	int LETTER_M;   /* ARRAY INDEX FOR LETTER M               */
	int LETTER_N;   /* ARRAY INDEX FOR LETTER N               */
	int LETTER_O;   /* ARRAY INDEX FOR LETTER O               */
	int LETTER_P;   /* ARRAY INDEX FOR LETTER P               */
	int LETTER_Q;   /* ARRAY INDEX FOR LETTER Q               */
	int LETTER_R;   /* ARRAY INDEX FOR LETTER R               */
	int LETTER_S;   /* ARRAY INDEX FOR LETTER S               */
	int LETTER_U;   /* ARRAY INDEX FOR LETTER U               */
	int LETTER_V;   /* ARRAY INDEX FOR LETTER V               */
	int LETTER_W;   /* ARRAY INDEX FOR LETTER W               */
	int LETTER_X;   /* ARRAY INDEX FOR LETTER X               */
	int LETTER_Y;   /* ARRAY INDEX FOR LETTER Y               */
	int LETTER_Z;   /* ARRAY INDEX FOR LETTER Z               */
	double RND1;  /* ROUND TO NEAREST .1            */
	double RND5;  /* ROUND TO NEAREST .5            */
	char EOLN[1];  /* END OF STRING CHARACTER        */
	char BLANK[2];  /* BLANK CHARACTER                */
	//int MGRS_LETTERS;  /* NUMBER OF LETTERS IN MGRS              */
	int NUM_OFFSET;  /* USED TO CONVERT NUMBERS TO LETTERS     */
	double ONEHT;    /* ONE HUNDRED THOUSAND                  */
	double TWOMIL;    /* TWO MILLION                           */
	double EIGHT;    /* EIGHT HUNDRED THOUSAND                */
	double ONE3HT;    /* ONE MILLION THREE HUNDRED THOUSAND    */
	double ZERO;  /* ZERO                           */
	double TEN;    /* TEN                                   */
	//TRUE = 1  /* CONSTANT VALUE FOR TRUE VALUE  */
	//FALSE = 0  /* CONSTANT VALUE FOR FALSE VALUE */
	//PI_OVER_2(PI / 2.0e0)
	char NUM[13];                /* NUMBERS        */
	int MAXALBET;   /* LAST INDEX IN ALPHABET ARRAY(0-25)     */
	int MAXNUMBER;   /* LAST INDEX IN NUMBER ARRAY(0-9)        */
	int MGRS_ZONE_AND_LETTERS;  /* NUM. OF CHARS. IN ZONE AND LETTERS     */
	int MGRS_MINIMUM;  /* MINIMUM NUMBER OF CHARS FOR MGRS       */
	int MGRS_MAXIMUM;  /* MAXIMUM NUMBER OF CHARS FOR MGRS       */

	double MIN_EASTING;
	double MAX_EASTING;
	double MIN_NORTHING;
	double MAX_NORTHING;
	int MAX_PRECISION;   /* Maximum precision of easting & northing */
	double MIN_UTM_LAT; /* -80 degrees in radians    */
	double MAX_UTM_LAT;  /* 84 degrees in radians     */

	double MIN_EAST_NORTH;
	double MAX_EAST_NORTH;

public:
	/* Ellipsoid parameters, default to WGS 84 */
	double MGRS_a;    /* Semi-major axis of ellipsoid in meters */
	double MGRS_f; /* Flattening of ellipsoid           */
	double MGRS_recpf;
	char MGRS_Ellipsoid_Code[3];

	char CLARKE_1866[3];
	char CLARKE_1880[3];
	char BESSEL_1841[3];

public:
	CMGRS();
	~CMGRS();
	void UTMSET(long izone,
		long* ltrlow,
		long* ltrhi,
		double *fnltr);
	void UTMLIM(long* n,
		double sphi,
		long izone,
		double *spsou,
		double *spnor,
		double *sleast,
		double *slwest);
	void UTMMGRS(long izone,
		long* ltrnum,
		double sphi,
		double x,
		double y);
	void UPSSET(long n,
		long* ltrlow,
		long* ltrhi,
		double *feltr,
		double *fnltr,
		long* ltrhy);
	void UPS(char* mgrs,
		long* ltrnum,
		double x,
		double y,
		long iarea);
	void LTR2UPS(long* ltrnum,
		long ltrlow,
		long ltrhi,
		long ltrhy,
		long* ierr,
		double *xltr,
		double *yltr,
		double fnltr,
		double feltr,
		double *x,
		double *y,
		double sign);
	void GRID_UPS(long   *Letters,
		char   *Hemisphere,
		double *Easting,
		double *Northing,
		long   *Error);
	void LTR2UTM(long* ltrnum,
		long ltrlow,
		long ltrhi,
		long* ierr,
		double *xltr,
		double *yltr,
		double fnltr,
		double yslow,
		double ylow);
	void GRID_UTM(long   *Zone,
		long   *Letters,
		char   *Hemisphere,
		double *Easting,
		double *Northing,
		long   In_Precision,
		long   *Error);
	long Round_MGRS(double value);
	long Make_MGRS_String(char* MGRS,
		long Zone,
		long ltrnum[MGRS_LETTERS],
		double Easting,
		double Northing,
		long Precision);
	long Break_MGRS_String(char* MGRS,
		long* Zone,
		long Letters[MGRS_LETTERS],
		double* Easting,
		double* Northing,
		long* Precision);
  long Set_MGRS_Parameters(double a,
                           double f,
                           const char   *Ellipsoid_Code);
/*
 * The function Set_MGRS_Parameters receives the ellipsoid parameters and sets
 * the corresponding state variables. If any errors occur, the error code(s)
 * are returned by the function, otherwise MGRS_NO_ERROR is returned.
 *
 *   a                : Semi-major axis of ellipsoid in meters (input)
 *   f                : Flattening of ellipsoid					       (input)
 *   Ellipsoid_Code   : 2-letter code for ellipsoid            (input)
 */


  void Get_MGRS_Parameters(double *a,
                           double *f,
                           char   *Ellipsoid_Code);
/*
 * The function Get_MGRS_Parameters returns the current ellipsoid
 * parameters.
 *
 *  a                : Semi-major axis of ellipsoid, in meters (output)
 *  f                : Flattening of ellipsoid					       (output)
 *  Ellipsoid_Code   : 2-letter code for ellipsoid             (output)
 */


  long Convert_Geodetic_To_MGRS (double Latitude,
                                 double Longitude,
                                 long   Precision,
                                 char *MGRS);
/*
 * The function Convert_Geodetic_To_MGRS converts geodetic (latitude and
 * longitude) coordinates to an MGRS coordinate string, according to the 
 * current ellipsoid parameters.  If any errors occur, the error code(s) 
 * are returned by the  function, otherwise MGRS_NO_ERROR is returned.
 *
 *    Latitude   : Latitude in radians              (input)
 *    Longitude  : Longitude in radians             (input)
 *    Precision  : Precision level of MGRS string   (input)
 *    MGRS       : MGRS coordinate string           (output)
 *  
 */


  long Convert_MGRS_To_Geodetic (char *MGRS,
                                 double *Latitude,
                                 double *Longitude);
/*
 * This function converts an MGRS coordinate string to Geodetic (latitude
 * and longitude in radians) coordinates.  If any errors occur, the error 
 * code(s) are returned by the  function, otherwise MGRS_NO_ERROR is returned.  
 *
 *    MGRS       : MGRS coordinate string           (input)
 *    Latitude   : Latitude in radians              (output)
 *    Longitude  : Longitude in radians             (output)
 *  
 */


  long Convert_UTM_To_MGRS (long Zone,
                            char Hemisphere,
                            double Easting,
                            double Northing,
                            long Precision,
                            char *MGRS);
/*
 * The function Convert_UTM_To_MGRS converts UTM (zone, easting, and
 * northing) coordinates to an MGRS coordinate string, according to the 
 * current ellipsoid parameters.  If any errors occur, the error code(s) 
 * are returned by the  function, otherwise MGRS_NO_ERROR is returned.
 *
 *    Zone       : UTM zone                         (input)
 *    Hemisphere : North or South hemisphere        (input)
 *    Easting    : Easting (X) in meters            (input)
 *    Northing   : Northing (Y) in meters           (input)
 *    Precision  : Precision level of MGRS string   (input)
 *    MGRS       : MGRS coordinate string           (output)
 */


  long Convert_MGRS_To_UTM (char   *MGRS,
                            long   *Zone,
                            char   *Hemisphere,
                            double *Easting,
                            double *Northing); 
/*
 * The function Convert_MGRS_To_UTM converts an MGRS coordinate string
 * to UTM projection (zone, hemisphere, easting and northing) coordinates 
 * according to the current ellipsoid parameters.  If any errors occur, 
 * the error code(s) are returned by the function, otherwise UTM_NO_ERROR 
 * is returned.
 *
 *    MGRS       : MGRS coordinate string           (input)
 *    Zone       : UTM zone                         (output)
 *    Hemisphere : North or South hemisphere        (output)
 *    Easting    : Easting (X) in meters            (output)
 *    Northing   : Northing (Y) in meters           (output)
 */



  long Convert_UPS_To_MGRS ( char   Hemisphere,
                             double Easting,
                             double Northing,
                             long Precision,
                             char *MGRS);

/*
 *  The function Convert_UPS_To_MGRS converts UPS (hemisphere, easting, 
 *  and northing) coordinates to an MGRS coordinate string according to 
 *  the current ellipsoid parameters.  If any errors occur, the error
 *  code(s) are returned by the function, otherwise UPS_NO_ERROR is 
 *  returned.
 *
 *    Hemisphere    : Hemisphere either 'N' or 'S'     (input)
 *    Easting       : Easting/X in meters              (input)
 *    Northing      : Northing/Y in meters             (input)
 *    Precision     : Precision level of MGRS string   (input)
 *    MGRS          : MGRS coordinate string           (output)
 */


  long Convert_MGRS_To_UPS ( char   *MGRS,
                             char   *Hemisphere,
                             double *Easting,
                             double *Northing);
/*
 *  The function Convert_MGRS_To_UPS converts an MGRS coordinate string
 *  to UPS (hemisphere, easting, and northing) coordinates, according 
 *  to the current ellipsoid parameters. If any errors occur, the error 
 *  code(s) are returned by the function, otherwide UPS_NO_ERROR is returned.
 *
 *    MGRS          : MGRS coordinate string           (input)
 *    Hemisphere    : Hemisphere either 'N' or 'S'     (output)
 *    Easting       : Easting/X in meters              (output)
 *    Northing      : Northing/Y in meters             (output)
 */
};

#endif /* MGRS_H */
