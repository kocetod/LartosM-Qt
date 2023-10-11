#ifndef TRUNIVW_H
#define TRUNIVW_H

#include "geoid.h"
#include "General/GlobalVariables.h"

//***************************************************************************/
//
//                               GLOBALS
//

#define TRUNIVW_NO_ERROR					0x0000
#define TRUNIVW_ELLIPSOID_ERROR				0x5001
#define TRUNIVW_CENTRAL_MERIDIAN_ERROR      0x5002
#define TRUNIVW_ELLIPSOID_PARAMETERS_ERROR	0x5004
#define TRUNIVW_TRANSFORM_ERROR             0x5008
#define TRUNIVW_UTM_ZONE_ERROR				0x5010
#define TRUNIVW_COORDINATE_SYSTEM_ERROR		0x5020
#define TRUNIVW_GEODETIC_MERCATOR_ERROR		0x5040
#define TRUNIVW_GEODETIC_GEOCENTRIC_ERROR	0x5080
#define TRUNIVW_GEODETIC_UTM_ERROR			0x5100
#define TRUNIVW_CS1930_CS1950_ERROR			0x5200
#define TRUNIVW_CS1950_CS1970_ERROR			0x5400
#define TRUNIVW_GEODETIC_CSBGS2005_ERROR	0x5800
#define TRUNIVW_TRANSGOD_NOTPARAMETER_ERROR	0x6000
#define TRUNIVW_DEFAULTGEOIDMODEL_ERROR		0x6001
#define TRUNIVW_UNKNOWNGEOID_DH_ERROR		0x6002
#define TRUNIVW_DLL_PARAMETERS_ERROR		0x6004
#define TRUNIVW_DLL_PARAM_NOTVALID_ERROR	0x6008
#define TRUNIVW_HEIGHT_TRANSFORM_ERROR		0x6010
#define TRUNIVW_WEBSERVICE_ERROR			0x6020
#define TRUNIVW_WEBSERVICE_READ_ERROR		0x6040
#define TRUNIVW_HARMONICMODEL_READ_ERROR	0x6080

#define TRUNIVW_ERROR_WEBSERVICE_VALUE			0x6100
#define TRUNIVW_WEBSERVICE_STOPPED				0x6101
#define TRUNIVW_WEBSERVICE_ERROR_INITIALIZE		0x6102
#define TRUNIVW_WEBSERVICE_ERROR_OPENSESSION	0x6104
#define TRUNIVW_WEBSERVICE_ERROR_READFILE		0x6108
#define TRUNIVW_WEBSERVICE_ERROR_LOADXML		0x6110
#define TRUNIVW_WEBSERVICE_ERROR_RETURNVALUE	0x6120
#define TRUNIVW_WEBSERVICE_NOT_USED				0x6140

#define TRUNIVW_MODULE_ERROR					0x6200


#define CHOICE_H_METOD_NOTDEFINED	-1
#define CHOICE_H_METOD_GEOID_MODEL	1
#define CHOICE_H_METOD_WEBSERVICE	2
#define CHOICE_H_METOD_GRD_SPECIFIC	3
#define CHOICE_H_METOD_GRD_PRECISE	4
#define CHOICE_H_METOD_GRD_GLOBAL	5
#define CHOICE_H_METOD_EGM96		6

#define TYPE_TILES		1
#define TYPE_ZONES		2

class CTrUnivw
{
public:
	CTrUnivw();
	~CTrUnivw();

public:
	CCHARString m_strLogFileError;
	bool m_bUseLogFile;

public:
	long Coordtr(int ssyst, int stype, int swidth, int to_syst, int to_type,
		int to_width, int from_Central_Meridian, int& to_Central_Meridian,
		double& xd, double& yd, double& hd);

	long prepkoo(int syst, int& tk, int& tw, int tk1, int tw1, int& smer, int tmer, double& xd, double& yd, double& hd);
	int trans_one_step(int nIndex, int& from_syst, int& from_type, int& from_width,
		int& from_Zone_Meridian, int to_type, int to_width,
		int to_Zone_Meridian, double& xd, double& yd, double& hd, bool& prep);
	/*
		uk - ot dirtrans
		trset              - Which method to be used
		trset1             - Which parameters to be used
		from_type
		from_width
		from_Zone_Meridian
		to_type
		to_width
		to_Zone_Meridian
		xd,yd,hd - coordinates
	*/

	long Prep_Geoid_Coo(int nSys, int nTypeOfCoo, int nWidth, int nZone, double& x, double& y);
	double lin_red_to_surface(int kod, int ss, int st, int sw, int hs, int zm, double x1, double y1, double h1, double hi1, double hgeoid1, double x2, double y2, double h2, double hi2, double hgeoid2, double dsurvey);

	int SaveLogFile(CCHARString strText);
	void xyzazs(double dblAB, double dblAL, double dblBB, double dblBL, double* pAzimuth, double* pZenith, double* pHorD, double* pS);
	void SetLogFile(CCHARString strFileName);
};

void clearxyh(double& x, double& y, double& h);
//int dirtrans(int sys1, int sys2);
/*
	sys1,sys2 - transformation from sys1 to sys2
	Return code for transformation
	30-->50         1,-1
	50-->70         2,-2
	50-->42         3,-3
	50-->42/83      4,-4
	42-->Bessel     5,-5
	42/83-->Bessel  6,-6
	42/83-->WGS84   7,-7
	50-->Sofijska   8,-8
	42-->42/83      9,-9
	Bessel-->WGS84 10,-10
*/

//procedure MandG(elips : integer; ff,l : double; var gama,ma : double);
void MandG(double a, double f, double ff, double l, double& gama, double& ma);
int BGS2005_Lambert(int direction, int& from_to_type, int& from_to_width, int& from_to_Zone_Meridian,
	int& from_HSys, int to_HSys, double& x, double& y, double& z, const char* strGRDFile = "");
double lin_slope_to_ellipsoid(double B1, double h1p, double B2, double h2p, double dist, double alfll, double rm);

double B_Mer(double fi, double al, double ap, double mo);

int Transform_Helmert_4(int nPath, double X0, double Y0, double F0, double scale, double& x, double& y);
double GetLambertConvergence(double B, double L);

#endif	//TRUNIVW_H
