/***************************************************************************/

#ifndef _STANDARD1_

/***************************************************************************/
/*
 *                               INCLUDES
 */

#include "projection.h"

/*
 *    math.h     - Standard C math library
 * 
 */


/***************************************************************************/
/*
 *                               DEFINES
 */

#define PI         3.1415926535897932384626433832795  /* PI                            */
#define PI_OVER_2  ( PI / 2.0)                 
#define TWO_PI     (2.0 * PI)                    
#define ES_SIN(sinlat)          (es * sinlat)
#define ONE_MINUS_SQR(x)        (1.0 - x * x)

CProjection::CProjection()
{
/* Ellipsoid Parameters, default to WGS 84 */
	a = 6378137.0;                   /* Semi-major axis of ellipsoid in meters */
	f = 1 / 298.257223563;           /* Flattening of ellipsoid */
	es = 0.08181919084262188000;            /* Eccentricity of ellipsoid */
	es2 = 0.0066943799901413800;            /* Eccentricity (0.08181919084262188000) squared         */
	es4 = 4.4814723452405e-005;             /* es2 * es2	 */
	one_MINUS_es2 = .99330562000986;        /* 1 - es2 */
	two_es = .16363838168524;               /* 2 * es */

/* Projection Parameters */
	Origin_Lat = (45 * PI / 180);    /* Latitude of origin in radians     */
	Origin_Long = 0.0;               /* Longitude of origin in radians    */
	Std_Parallel_1 = (40 * PI / 180);
	Std_Parallel_2 = (50 * PI / 180);
	False_Easting = 0.0;
	False_Northing = 0.0;

	Delta_Northing = 40000000;
	Delta_Easting = 40000000;
}

CProjection::~CProjection()
{

}


#endif //_STANDARD1_
