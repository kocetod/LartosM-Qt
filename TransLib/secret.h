#ifndef SECRET_H
#define  SECRET_H

void MoBo(double xm, double ym, double zm, double dx, double dy, double dz, double rx,
		double ry, double rz, double sc, double &x, double &y, double &z);
/*{...Molodenski-Badekas similarity transformation
  Transformation parameters:
   xm, ym, zm - transformation origin
   dx, dy, dz - shifts
   rx, ry, rz - rotations
   sc         - scale factor
}*/
int bltrans(int it, int sys, int trset,
			 double &B, double &L, double H);
/* Transform B,L using Molodenski Badekash
  it = 1  direct
  it = 2  reverse
  sys - transformations
    2 - WGS84 - 42/83
	7 - WGS84 - WGS2005
  trset = transformation parameters
*/

long WGS_4283 (int trset, int it, double &xm, double &ym, double &zm,
					double &dx, double &dy, double &dz,
					double &rx, double &ry, double &rz, double &sc);
long WGS_BGS2005 (int trset, int it, double &xm, double &ym, double &zm,
					double &dx, double &dy, double &dz,
					double &rx, double &ry, double &rz, double &sc);

int ncc(char ss);
long BG_KRON_NH_to_EVRF2000(double B, double L, double &H);
long BG_KRON_NH_to_EVRF2007(double B, double L, double &H);
bool Get_Ellipsoid_Parameters_By_System(int system, double* a, double* f, double* scale);
long RO_CONST_NH_to_EVRF2007(double B, double L, double& H);

#endif	//SECRET_H

