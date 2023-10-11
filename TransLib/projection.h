#ifndef PROJECTION_H
#define PROJECTION_H


class CProjection
{
public:
	/* Ellipsoid Parameters, default to WGS 84 */
	double a;              /* Semi-major axis of ellipsoid in meters */
	double f;              /* Flattening of ellipsoid */
	double es;             /* Eccentricity of ellipsoid */
	double ebs;            /* Second Eccentricity squared */
	double es2;            /* Eccentricity (0.08181919084262188000) squared         */
	double es4;            /* es2 * es2	 */
	double one_MINUS_es2;  /* 1 - es2 */
	double two_es;         /* 2 * es */

	/* Projection Parameters */
	double Origin_Lat;            /* Latitude of origin in radians     */
	double Origin_Long;           /* Longitude of origin in radians    */
	double Std_Parallel_1;
	double Std_Parallel_2;
	double False_Easting;
	double False_Northing;
	double Scale_Factor;         /* Scale factor  */
	double Delta_Easting;
	double Delta_Northing;

public:
	CProjection();
	~CProjection();
};

#endif