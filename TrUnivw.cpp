#include <math.h>
#ifdef _QT_
#include <stdlib.h>
#endif
#ifdef LINUX_VER
#include <stdlib.h>
#endif
#include "TransLib/secret.h"
#include "TransLib/geodw.h"
#include "TransLib/tranmerc.h"
#include "TransLib/geocent.h"
#include "TransLib/utm.h"
#include "TransLib/lambert.h"
#include "TransLib/geoid.h"
#include "TrUnivw.h"
#include "TransLib/transform.h"
#include "TransLib/TransHelper.h"

//---------------class CTrUnivw--------------------------

CTrUnivw::CTrUnivw()
{
	m_strLogFileError = "";
}

CTrUnivw::~CTrUnivw()
{
	
}

long CTrUnivw::prepkoo(int syst, int &tk, int &tw, int tk1, int tw1, int &smer, int tmer, double &xd, double &yd, double &hd)
/*
	syst - bulgarian coordinate system
	tk - type of source coordinate
	tw - source zone width
	tk1 - type of target coordinate
	tw1 - target zone width
	smer - source central meridian
	tmer - target central meridian
	sheight - source height system
	theight - target height system
*/
{
	double a,f,b,l,h;
	double Origin_Latitude,False_Easting,False_Northing,Scale;
	double from_mer, to_mer;
	long status; 
	int cod, prev_cod;
	char Hemisphere = 'N';	//Must to organized for south hemisphere
	int sheight = HS_UNKNOWN_CODE, theight = HS_UNKNOWN_CODE;
	CCHARString strTemp;
	
	if (!Get_Ellipsoid_Parameters_By_System(syst, &a, &f, &Scale))
	{
		return TRUNIVW_ELLIPSOID_PARAMETERS_ERROR;
	}
	False_Northing = 0;
	Origin_Latitude = 0;
     	from_mer = smer;
	to_mer = tmer;
	CTranMerc objTranMerc;
	CGeocent objGeocent;
	CUTM objUTM;
	switch(tk)
	{
	case CT_XY_CODE:
        switch(tk1)
		{
		case CT_XY_CODE:
			if (ReturnZoneMeridian(tk,tw,xd,yd,&cod,&from_mer) != 0)
			{
				return TRUNIVW_CENTRAL_MERIDIAN_ERROR;
			}
			prev_cod = cod;
			False_Easting = cod * 1000000.0 + 500000.0;
			
			status = objTranMerc.Set_Transverse_Mercator_Parameters(a,f,Origin_Latitude,from_mer,
							False_Easting,False_Northing,Scale);
			status = objTranMerc.Convert_Transverse_Mercator_To_Geodetic(yd,xd,&b,&l);
			
			if (status != 0 && status != TRANMERC_LON_WARNING)
			{
				return TRUNIVW_TRANSFORM_ERROR;
			}
			if (ReturnZoneMeridian(1,tw1,b,l,&cod,&to_mer) != 0)
			{
				return TRUNIVW_CENTRAL_MERIDIAN_ERROR;
			}
			if(cod != 4 && cod != 5 && cod != 8 && cod != 9 && 
				(syst == CS_42_83_CODE))
			{				
				if(tw1 == ZW_3DEGREE_CODE)
					to_mer = cod * 3;
				else
					to_mer = cod * 6 - 3;
				to_mer *= PI / 180.0; 
			}
			False_Easting = cod * 1000000.0 + 500000.0;
			status = objTranMerc.Set_Transverse_Mercator_Parameters(a,f,Origin_Latitude,to_mer,
							False_Easting,False_Northing,Scale);
			status = objTranMerc.Convert_Geodetic_To_Transverse_Mercator (b,l,&yd,&xd);
			if (status != 0 && status != TRANMERC_LON_WARNING)
			{
				return TRUNIVW_GEODETIC_MERCATOR_ERROR;
			}
			smer = (int) round_1((to_mer * 180 / PI));
			tw = tw1;
			break;
		case CT_BL_CODE:
			if (ReturnZoneMeridian(tk,tw,xd,yd,&cod,&from_mer) != 0)
			{
				return TRUNIVW_CENTRAL_MERIDIAN_ERROR;
			}
			False_Easting = cod * 1000000.0 + 500000.0;
			status = objTranMerc.Set_Transverse_Mercator_Parameters(a,f,Origin_Latitude,from_mer,
							False_Easting,False_Northing,Scale);
			b = xd;
			l = yd;
			status = objTranMerc.Convert_Transverse_Mercator_To_Geodetic(l,b,&xd,&yd);
			
			if (status != 0 && status != TRANMERC_LON_WARNING)
			{
				return TRUNIVW_GEODETIC_MERCATOR_ERROR;
			}
			smer = VALUE_NOT_USED;
			tk = CT_BL_CODE;
			tw = ZW_UNKNOWN_CODE;
			break;
		case CT_XYZ_CODE:
			if (ReturnZoneMeridian(tk,tw,xd,yd,&cod,&from_mer) != 0)
			{
				return TRUNIVW_CENTRAL_MERIDIAN_ERROR;
			}
			False_Easting = cod * 1000000.0 + 500000.0;
			status = objTranMerc.Set_Transverse_Mercator_Parameters(a,f,Origin_Latitude,from_mer,
						False_Easting,False_Northing,Scale);
			status = objTranMerc.Convert_Transverse_Mercator_To_Geodetic(yd,xd,&b,&l);
			if (status != 0 && status != TRANMERC_LON_WARNING)
			{
				return TRUNIVW_GEODETIC_MERCATOR_ERROR;
			}
			h = hd;
			status = objGeocent.Set_Geocentric_Parameters (a,f);
			status = objGeocent.Convert_Geodetic_To_Geocentric (b,l,h,&xd,&yd,&hd);
			
			if (status != 0)
			{
				return TRUNIVW_GEODETIC_GEOCENTRIC_ERROR;
			}
			smer = VALUE_NOT_USED;
			tk = CT_XYZ_CODE;
			tw = ZW_UNKNOWN_CODE;
			break;
		case CT_UTM_CODE:
			//Do nothing
			break;
		case CT_CAD_CODE:
			//Do nothing, may be error
			break;
        }
        break;
	case CT_BL_CODE:
        switch(tk1)
		{
		case CT_XY_CODE:
			status = ReturnZoneMeridian(tk,tw1,xd,yd,&cod,&to_mer);
			if (status != TRANS_NO_ERROR)
			{
				return status;
			}
			False_Easting = cod * 1000000.0 + 500000.0;
			status = objTranMerc.Set_Transverse_Mercator_Parameters(a,f,Origin_Latitude,to_mer,
							False_Easting,False_Northing,Scale);
			b = xd;
			l = yd;
			status = objTranMerc.Convert_Geodetic_To_Transverse_Mercator (b,l,&yd,&xd);
			
			if (status != TRANS_NO_ERROR && status != TRANMERC_LON_WARNING)
			{
				return TRUNIVW_GEODETIC_MERCATOR_ERROR;
			}
			smer = (int) round_1((to_mer * 180 / PI));
			tk = CT_XY_CODE;
			tw = tw1;
			break;
		case CT_BL_CODE:
              //{ Will do nothing }
			break;
		case CT_XYZ_CODE:
			status = objGeocent.Set_Geocentric_Parameters (a,f);
			b = xd;
			l = yd;
			h = hd;
            status = objGeocent.Convert_Geodetic_To_Geocentric (b,l,h,&xd,&yd,&hd);
			if (status != 0)
			{
				return TRUNIVW_GEODETIC_GEOCENTRIC_ERROR;
			}
			smer = VALUE_NOT_USED;
			tk = CT_XYZ_CODE;
			tw = ZW_UNKNOWN_CODE;
			break;
		case CT_UTM_CODE:
			if(tmer == -999)
			{
				tmer = (int)((yd * 180 / PI) / 6) + 31;
			}
			else if ((tmer < 1) || (tmer > 60))
			{
				return TRUNIVW_UTM_ZONE_ERROR;
			}
			status = objUTM.Set_UTM_Parameters(a,f,tmer);
			b = xd;
			l = yd;
			status = objUTM.Convert_Geodetic_To_UTM (b,l, (long *)&tmer,&Hemisphere,&yd,&xd);
			
			if (status != 0 && !((status & UTM_WARNING) == UTM_WARNING) && !((status & UTM_EASTING_ERROR) == UTM_EASTING_ERROR))
			{
				return TRUNIVW_GEODETIC_UTM_ERROR;
			}
			smer = tmer;
			tk = CT_UTM_CODE;
			tw = ZW_6DEGREE_CODE;
			break;
		case CT_CAD_CODE:
			BGS2005_Lambert(1, tk, tw, smer, sheight, theight, xd, yd, hd);
			break;
        }
        break;
	case CT_XYZ_CODE:
        switch(tk1)
		{
		case CT_XY_CODE:
			status = objGeocent.Set_Geocentric_Parameters (a,f);
			objGeocent.Convert_Geocentric_To_Geodetic (xd,yd,hd,&b,&l,&h);
			if (ReturnZoneMeridian(1,tw1,b,l,&cod,&to_mer) != 0)
			{
				return TRUNIVW_CENTRAL_MERIDIAN_ERROR;
			}
			False_Easting = cod * 1000000.0 + 500000.0;
			status = objTranMerc.Set_Transverse_Mercator_Parameters(a,f,Origin_Latitude,to_mer,
							False_Easting,False_Northing,Scale);
			status = objTranMerc.Convert_Geodetic_To_Transverse_Mercator (b,l,&yd,&xd);
			
			if (status != 0 && status != TRANMERC_LON_WARNING)
			{
				return TRUNIVW_GEODETIC_MERCATOR_ERROR;
			}
			hd = h;
			smer = (int) round_1((to_mer * 180 / PI));
			tk = CT_XY_CODE;
			tw = tw1;
			break;
		case CT_BL_CODE:
			status = objGeocent.Set_Geocentric_Parameters (a,f);
			b = xd;
			l = yd;
			h = hd;
			objGeocent.Convert_Geocentric_To_Geodetic (b,l,h,&xd,&yd,&hd);
			smer = VALUE_NOT_USED;
			tk = CT_BL_CODE;
			tw = ZW_UNKNOWN_CODE;
			break;
        case CT_XYZ_CODE:
              //{ Will do nothing }
              break;
		case CT_UTM_CODE:
			status = objGeocent.Set_Geocentric_Parameters (a,f);
			objGeocent.Convert_Geocentric_To_Geodetic (xd,yd,hd,&b,&l,&h);
			hd = h;
			if ((tmer < 1) || (tmer > 60))
			{
				return TRUNIVW_UTM_ZONE_ERROR;
			}
			status = objUTM.Set_UTM_Parameters(a,f,tmer);
			status = objUTM.Convert_Geodetic_To_UTM (b,l, (long *)&tmer,&Hemisphere,&yd,&xd);
			
			if (status != 0 && status != UTM_WARNING)
			{
				if(!((status & UTM_EASTING_ERROR) == UTM_EASTING_ERROR) && !((status & UTM_NORTHING_ERROR) == UTM_NORTHING_ERROR))
					return TRUNIVW_GEODETIC_UTM_ERROR;
			}
			smer = tmer;
			tk = CT_UTM_CODE;
			tw = ZW_6DEGREE_CODE;
			break;
		case CT_CAD_CODE:
			status = objGeocent.Set_Geocentric_Parameters (a,f);
			b = xd;
			l = yd;
			h = hd;
			objGeocent.Convert_Geocentric_To_Geodetic (b,l,h,&xd,&yd,&hd);
			smer = VALUE_NOT_USED;
			tk = CT_BL_CODE;
			tw = ZW_UNKNOWN_CODE;
			BGS2005_Lambert(1, tk, tw, smer, sheight, theight, xd, yd, hd);
			break;
        }
        break;
	case CT_UTM_CODE:
		if ((smer < 1) || (smer > 60))
		{
			return TRUNIVW_UTM_ZONE_ERROR;
		}
		status = objUTM.Set_UTM_Parameters(a,f,smer);
		switch(tk1)
		{
		case CT_XY_CODE:
			status = objUTM.Convert_UTM_To_Geodetic(smer,Hemisphere,yd,xd,&b,&l);
			
			if (status != 0 && status != UTM_WARNING)
			{
				return TRUNIVW_GEODETIC_UTM_ERROR;
			}
			if (ReturnZoneMeridian(1,tw1,b,l,&cod,&to_mer) != 0)
			{
				return TRUNIVW_CENTRAL_MERIDIAN_ERROR;
			}
			False_Easting = cod * 1000000.0 + 500000.0;
			status = objTranMerc.Set_Transverse_Mercator_Parameters(a,f,Origin_Latitude,to_mer,
							False_Easting,False_Northing,Scale);
			status = objTranMerc.Convert_Geodetic_To_Transverse_Mercator (b,l,&yd,&xd);		
			
			if (status != 0)
			{
				if (status == TRANMERC_LON_WARNING)
				{
					
				}
				else return TRUNIVW_TRANSFORM_ERROR;
			}
			smer = (int) round_1((to_mer * 180 / PI));
			tk = CT_XY_CODE;
			tw = tw1;
			break;
		case CT_BL_CODE:
			b = xd;
			l = yd;
			status = objUTM.Convert_UTM_To_Geodetic(smer,Hemisphere,l,b,&xd,&yd);
			
			if (status != 0)
			{
				if (status == UTM_WARNING)
				{
					
				}
				else return TRUNIVW_GEODETIC_UTM_ERROR;
			}
			smer = VALUE_NOT_USED;
			tk = CT_BL_CODE;
			tw = ZW_UNKNOWN_CODE;
			break;
		case CT_XYZ_CODE:
			status = objUTM.Convert_UTM_To_Geodetic(smer,Hemisphere,yd,xd,&b,&l);
			
			if (status != 0)
			{
				if (status == UTM_WARNING)
				{
					
				}
				else return TRUNIVW_GEODETIC_UTM_ERROR;
			}
			h = hd;
			status = objGeocent.Set_Geocentric_Parameters (a,f);
			status = objGeocent.Convert_Geodetic_To_Geocentric (b,l,h,&xd,&yd,&hd);
			
			if (status != 0)
			{
				return TRUNIVW_GEODETIC_GEOCENTRIC_ERROR;
			}
			smer = VALUE_NOT_USED;
			tk = CT_XYZ_CODE;
			tw = ZW_UNKNOWN_CODE;
			break;
		case CT_UTM_CODE:
			if(smer == tmer) break;
			status = objUTM.Set_UTM_Parameters(a,f,smer);
			status = objUTM.Convert_UTM_To_Geodetic(smer,Hemisphere,yd,xd,&b,&l);
			
			if (status != 0 && status != UTM_WARNING)
			{
				return TRUNIVW_GEODETIC_UTM_ERROR;
			}
			status = objUTM.Set_UTM_Parameters(a,f,tmer);
			status = objUTM.Convert_Geodetic_To_UTM (b,l,(long *)&tmer,&Hemisphere,&yd,&xd);
			
			if (status != 0 && status != UTM_WARNING)
			{
				if (!(status & UTM_EASTING_ERROR))
				return TRUNIVW_TRANSFORM_ERROR;
			}
			smer = tmer;
			tk = CT_XYZ_CODE;
			tw = ZW_6DEGREE_CODE;
			break;
		case CT_CAD_CODE:
			b = xd;
			l = yd;
			status = objUTM.Convert_UTM_To_Geodetic(smer,Hemisphere,l,b,&xd,&yd);
			
			if (status != 0)
			{
				if (status == UTM_WARNING)
				{
					
				}
				else return TRUNIVW_GEODETIC_UTM_ERROR;
			}
			smer = VALUE_NOT_USED;
			tk = CT_BL_CODE;
			tw = ZW_UNKNOWN_CODE;
			BGS2005_Lambert(1, tk, tw, smer, sheight, theight, xd, yd, hd);
			break;
        }
        break;
	case CT_CAD_CODE:
        switch(tk1)
		{
		case CT_XY_CODE:
			//This is not alowwed. May be error
			break;
		case CT_BL_CODE:
			BGS2005_Lambert(2, tk, tw, smer, sheight, theight, xd, yd, hd);
			smer = VALUE_NOT_USED;
			tk = CT_BL_CODE;
			tw = ZW_UNKNOWN_CODE;
			break;
        case CT_XYZ_CODE:
			BGS2005_Lambert(2, tk, tw, smer, sheight, theight, xd, yd, hd);
			status = objGeocent.Set_Geocentric_Parameters (a,f);
			b = xd;
			l = yd;
			h = hd;
            status = objGeocent.Convert_Geodetic_To_Geocentric (b,l,h,&xd,&yd,&hd);
			if (status != 0)
			{
				return TRUNIVW_GEODETIC_GEOCENTRIC_ERROR;
			}
			smer = VALUE_NOT_USED;
			tk = CT_XYZ_CODE;
			tw = ZW_UNKNOWN_CODE;
			break;
		case CT_UTM_CODE:
			BGS2005_Lambert(2, tk, tw, smer, sheight, theight, xd, yd, hd);
			if ((tmer < 1) || (tmer > 60))
			{
				return TRUNIVW_UTM_ZONE_ERROR;
			}
			status = objUTM.Set_UTM_Parameters(a,f,tmer);
			b = xd;
			l = yd;
			status = objUTM.Convert_Geodetic_To_UTM (b,l, (long *)&tmer,&Hemisphere,&yd,&xd);
			
			if (status != 0)
			{
				if (status == UTM_WARNING)
				{
					
				}
				else return TRUNIVW_GEODETIC_UTM_ERROR;
			}
			smer = tmer;
			tk = CT_UTM_CODE;
			tw = ZW_6DEGREE_CODE;
			break;
		case CT_CAD_CODE:
			//Do nothing
			break;
        }
        break;
	}

	return TRUNIVW_NO_ERROR;
}

int CTrUnivw::trans_one_step(int nIndex, int& from_syst, int &from_type, int &from_width,
	int &from_Zone_Meridian, int to_type, int to_width,
	int to_Zone_Meridian, double &xd, double &yd, double &hd, bool &prep)
	//-------------------------------------------------------------------
	//Transform coordinates by one step
	//uk                 - Direction of transformation path
	//trset              - Which method to be used
	//trset1             - Which parameters to be used
	//from_type          - Type of coordinates
	//from_width         - Width of zones of coordinates
	//from_Zone_Meridian - Central meridian (degree) or Zone of coordinates
	//to_type            - Type of transformed coordinates
	//to_width           - Width of zone for transformed coordinates
	//to_Zone_Meridian   - Central Meridian or Zone for transformed coordinates
	//xd,yd,hd           - Coordinates
	//--------------------------------------------------------------------
{
	int to_syst;
	int uk;
	long status = TRUNIVW_NO_ERROR;
	int trset = 0;
	CCHARString strTemp;

	switch (abs(nIndex))
	{
	case TR_4283_ETRS89: //{42/83<-->ETRS89}
		trset = 0;
		to_type = CT_BL_CODE;
		to_width = ZW_UNKNOWN_CODE;
		status = prepkoo(from_syst, from_type, from_width, to_type, to_width,
			from_Zone_Meridian, VALUE_NOT_USED, xd, yd, hd);
		if (status != 0) return status;
		if (nIndex > 0)
		{
			status = bltrans(2, 2, trset, xd, yd, hd); //{ 42/83 -> WGS84 }
			if (status != 0) return status;
			from_syst = CS_WGS84_CODE;
		}
		else
		{
			status = bltrans(1, 2, trset, xd, yd, hd); //{ WGS84 -> 42/83 }
			if (status != 0)
			{
				return status;
			}
			from_syst = CS_42_83_CODE;
		}
		from_type = CT_BL_CODE;
		from_width = ZW_UNKNOWN_CODE;
	prep = true;
	break;
	case TR_ETRS89_BGS2005: //{ETRS89<-->BGS2005}
		trset = 0;
		to_type = CT_BL_CODE;
		to_width = ZW_UNKNOWN_CODE;
		status = prepkoo(from_syst, from_type, from_width, to_type, to_width,
			from_Zone_Meridian, VALUE_NOT_USED, xd, yd, hd);
		if (status != 0) return status;
		if (nIndex > 0)
		{
			status = bltrans(1, 7, trset, xd, yd, hd); //{ BULREF -> BGS2005 }
			if (status != 0) return status;
			from_syst = CS_BGS_CODE;
		}
		else
		{
			status = bltrans(2, 7, trset, xd, yd, hd); //{ BGS2005 -> 42/83 }
			if (status != 0)
			{
				return status;
			}
			from_syst = CS_WGS84_CODE;
		}
		from_type = CT_BL_CODE;
		from_width = ZW_UNKNOWN_CODE;
		prep = true;
		break;
	case TR_BGS2005_LAMBERT: //{BGS2005<-->BGS2005_Lambert}
	{
		CLambert objLambert;
		double Lamb_a = 6378137.0;
		double Lamb_f = 1 / 298.257222101;
		double Lamb_Central_Meridian = gtor(253000, CF_CODE_D_M_S);
		double Lamb_Std_Parallel_1 = gtor(420000.00, CF_CODE_D_M_S);
		double Lamb_Std_Parallel_2 = gtor(432000.00, CF_CODE_D_M_S);
		double Lamb_Origin_Latitude = objLambert.Get_Origin_Lattitude(Lamb_Std_Parallel_1, Lamb_Std_Parallel_2, Lamb_f);
		double Lamb_False_Easting = 500000;
		double North_Meridian = B_Mer(Lamb_Origin_Latitude, Lamb_f, Lamb_a, 1);
#ifdef _MARIAN
		double NM = ret_X0(Lamb_Origin_Latitude);
#endif
		double Lamb_False_Northing = North_Meridian;
		objLambert.Set_Lambert_Parameters(Lamb_a, Lamb_f, Lamb_Origin_Latitude, Lamb_Central_Meridian,
			Lamb_Std_Parallel_1, Lamb_Std_Parallel_2, Lamb_False_Easting, Lamb_False_Northing);
		to_type = CT_BL_CODE;
		to_width = ZW_UNKNOWN_CODE;
		double east, north;
		if (nIndex > 0)
		{
			status = prepkoo(from_syst, from_type, from_width, to_type, to_width,
				from_Zone_Meridian, VALUE_NOT_USED, xd, yd, hd);
			if (status != 0) return status;
			status = objLambert.Convert_Geodetic_To_Lambert(xd, yd, &east, &north);
#ifdef _MARIAN
			double EE, NN;
			BLToGrid(xd, yd, &EE, &NN);
#endif
			if (status != 0) return status;
			xd = north;
			yd = east;
			from_syst = CS_BGS_CODE;
			from_type = CT_XY_CODE;
			prep = false;
		}
		else
		{
			north = xd;
			east = yd;
			status = objLambert.Convert_Lambert_To_Geodetic(east, north, &xd, &yd);
#ifdef _MARIAN
			double B, L;
			GridToBL(east, north, &B, &L);
#endif
			if (status != 0)
			{
				return status;
			}
			from_syst = CS_BGS_CODE;
			from_type = CT_BL_CODE;
			prep = true;
		}
		from_width = ZW_UNKNOWN_CODE;
	}
	break;
	case TR_BGS2005_WGSG1762: //{BGS2005<-->BGS2005_WGSG1762}
		//Not implemented
		prep = true;
		break;
	}//switch nIndex

	return TRUNIVW_NO_ERROR;
}


long CTrUnivw::Coordtr(int ssyst, int stype, int swidth, int to_syst, int to_type,
			 int to_width, int from_Central_Meridian, int &to_Central_Meridian,
			 double &xd, double &yd, double &hd)
//	ssyst,stype,swidth - source system,type of source coordinate,source width
//  shsyst - source height system
//	to_syst,to_type,to_width  - target system,type of target coordinate,traget width
//  to_hsyst - target height system
//	from_Central_Meridian - central meridian or zone in 70 for source
//	to_Central_Meridian - central meridian or zone in 70 for source
{
	long nReturn = TRANS_NO_ERROR;
	if(ssyst == CS_UNKNOWN_CODE || to_syst == CS_UNKNOWN_CODE) return TRANS_NO_ERROR;
	int status = TRANS_NO_ERROR;
    int tr_syst, tr_type, tr_width, tr_om, tr_to_Central_Meridian;
    bool prep;
	int index = 0;
	CCHARString strTemp;


	if(ssyst == to_syst && stype == to_type && swidth == to_width && from_Central_Meridian == to_Central_Meridian)
	{
		return TRANS_NO_ERROR;
	}
	else
	{
		prep = true;
		tr_syst = ssyst;
		tr_type = stype;
		tr_width = swidth;
		tr_om = from_Central_Meridian;
		tr_to_Central_Meridian = to_Central_Meridian;
		if (ssyst == CS_42_83_CODE && to_syst == CS_WGS84_CODE)
			index = TR_4283_ETRS89;
		else if (ssyst == CS_WGS84_CODE && to_syst == CS_42_83_CODE)
			index = -TR_4283_ETRS89;
		else if (ssyst == CS_WGS84_CODE && to_syst == CS_BGS_CODE)
			index = TR_ETRS89_BGS2005;
		else if (ssyst == CS_BGS_CODE && to_syst == CS_WGS84_CODE)
			index = -TR_ETRS89_BGS2005;
		else if (ssyst == CS_BGS_CODE && to_syst == CS_BGS_CODE)
		{
			if (stype == CT_CAD_CODE)
				index = TR_BGS2005_LAMBERT;
			else if (to_type == CT_CAD_CODE)
				index = -TR_BGS2005_LAMBERT;
		}
		nReturn = trans_one_step(index, tr_syst, tr_type, tr_width, tr_om, to_type, to_width,
			tr_to_Central_Meridian, xd, yd, hd, prep);
		if (nReturn != 0)
		{
			prep = false;
		}
	}
	if (prep)
	{
		status = prepkoo(to_syst, tr_type, tr_width, to_type, to_width, tr_om,
			tr_to_Central_Meridian, xd, yd, hd);
		if (status != 0)
		{
			if (status == TRUNIVW_ELLIPSOID_PARAMETERS_ERROR)
				nReturn = TRANS_COORDINATE_SYSTEM_ERROR;
		}
		else
			to_Central_Meridian = tr_om;
	}
	else
		to_Central_Meridian = tr_to_Central_Meridian;

	if (nReturn != TRANS_NO_ERROR)
	{
		clearxyh(xd, yd, hd);
	}

	return nReturn;
}

long CTrUnivw::Prep_Geoid_Coo(int nSys, int nTypeOfCoo, int nWidth, int nZone, double& x, double& y)
{
	long bReturnValue = true;
	int nType1 = CT_BL_CODE;
	int nWidth1 = ZW_UNKNOWN_CODE;
	int nZone1 = NO_VALUE;
	double h = 0;

	bReturnValue = prepkoo(nSys, nType1, nWidth1, nTypeOfCoo, nWidth, nZone1, nZone, x, y, h);
	if (bReturnValue == TRUNIVW_NO_ERROR && nType1 == CT_BL_CODE)
	{// geographic decimal degree coordinates
		x = x * 180 / PI;
		y = y * 180 / PI;
	}

	return bReturnValue;
}

double CTrUnivw::lin_red_to_surface(int kod, int ss, int st, int sw, int hs, int zm, double x1, double y1, double h1, double hi1, double hgeoid1, double x2, double y2, double h2, double hi2, double hgeoid2, double dsurvey)
{//kod = 1 to_surface; kod = 2 to_projection
	double nReturn = 0;
	double dy, ym, tmp;
	double rm, eta, N, M, f, a, ei, f1;
	double B1, L1, H1, B2, L2, H2;
	double alfll, dll;
	int status = 0;
	int tomer = zm;
	double mo = 0.9996;
	Get_Ellipsoid_Parameters_By_System(ss, &a, &f, &mo);
	B1 = x1;
	L1 = y1;
	H1 = h1;
	B2 = x2;
	L2 = y2;
	H2 = h2;
	int temptype = st;
	int tempwidth = sw;
	int tempsys = ss;
	int tempmer = zm;
	if (st != CT_BL_CODE)
	{
		status = Coordtr(ss, st, tempwidth, tempsys, CT_BL_CODE, ZW_UNKNOWN_CODE, zm, tomer, B1, L1, H1);
		tomer = tempmer;
		status = Coordtr(ss, st, sw, ss, CT_BL_CODE, ZW_UNKNOWN_CODE, zm, tomer, B2, L2, H2);
	}
	if (st == CT_XYZ_CODE)
	{
		if (ss == CS_WGS84_CODE)
		{
			temptype = CT_UTM_CODE;
		}
		else if (ss == CS_BGS_CODE)
		{
			temptype = CT_UTM_CODE;
		}
		else temptype = CT_XY_CODE;
		tempwidth = ZW_6DEGREE_CODE;
		status = Coordtr(ss, st, sw, tempsys, temptype, tempwidth, zm, tempmer, x1, y1, h1);
		tomer = tempmer;
		status = Coordtr(ss, st, sw, tempsys, temptype, tempwidth, zm, tempmer, x2, y2, h2);
	}
	else if (st == CT_CAD_CODE)
	{
		temptype = CT_UTM_CODE;
		status = Coordtr(ss, st, sw, tempsys, temptype, tempwidth, zm, tempmer, x1, y1, h1);
		tomer = tempmer;
		status = Coordtr(ss, st, sw, tempsys, temptype, tempwidth, zm, tempmer, x2, y2, h2);
		mo = 1.0;
	}
	else
	{
		if (ss == CS_WGS84_CODE || (ss == CS_WGS84_CODE && st == CT_UTM_CODE))
		{
			mo = 0.9996;
		}
		else
		{
			mo = 1.0;
		}
		tomer = tempmer;
		status = Coordtr(ss, st, sw, tempsys, temptype, tempwidth, zm, tempmer, x1, y1, h1);
		tomer = tempmer;
		status = Coordtr(ss, st, sw, tempsys, temptype, tempwidth, zm, tempmer, x2, y2, h2);
	}
	double dl;

	if (tempwidth == ZW_3DEGREE_CODE)
	{
		int nT1 = int((L1 * 180.0 / PI) / 3);
		if ((L1 - gtor(nT1 * 3, CF_CODE_DD)) < gtor(1.5, CF_CODE_DD)) dl = L1 - gtor(nT1 * 3, CF_CODE_DD);
		else dl = gtor((nT1 * 3 + 3), CF_CODE_DD) - L1;
	}
	else
	{
		int nT1 = int((L1 * 180.0 / PI - 3) / 6) + 1;
		if ((L1 - gtor(nT1 * 6 - 3, CF_CODE_DD)) < gtor(3.0, CF_CODE_DD)) dl = L1 - gtor(nT1 * 6 - 3, CF_CODE_DD);
		else dl = gtor((nT1 * 6 + 3), CF_CODE_DD) - L1;
	}
	double gama, ma;
	MandG(a, f, B1, dl, gama, ma);
	Obratna_zadacha(x1, y1, x2, y2, alfll, dll);
	alfll += gama;
	ei = (1 - sqr(1 - f)) / sqr(1 - f);
	if (temptype != CT_UTM_CODE)
	{
		y1 = y1 - int(y1 / 1000000.0) * 1000000.0;
		y2 = y2 - int(y2 / 1000000.0) * 1000000.0;
	}
	y1 = y1 - 500000.0;
	y2 = y2 - 500000.0;
	dy = (y2 - y1);
	ym = (y2 + y1) / 2.0;
	f1 = (B1 + B2) / 2.0;
	eta = ei * sqr(cos(f1));
	N = nrad(B1, a, f);
	M = mrad(B1, a, f);
	rm = (M * N) / (N * sqr(cos(alfll)) + M * sqr(sin(alfll)));
	double h1p = H1 + hgeoid1 + hi1;
	double h2p = H2 + hgeoid2 + hi2;
	double ra = N * sqrt(1 + eta * sqr(cos(alfll)));
	double rmn = sqrt(M * N) * mo;
	double sd = lin_slope_to_ellipsoid(B1, h1p, B2, h2p, dsurvey, alfll, ra);
	if (kod == 1)
	{
		tmp = (1 + (sqr(ym) / (2 * sqr(rm))) + (sqr(dy) / (24 * sqr(rm))) - (5 * pow(ym, 4) / (24 * pow(rm, 4)))) * mo;
	}
	else
	{
		tmp = (1 + (sqr(ym) / (2.0 * sqr(rmn))) + (sqr(dy) / (24.0 * sqr(rmn))) + (pow(ym, 4) / (24 * pow(rmn, 4)))) * mo;
	}
	nReturn = sd * tmp;

	return nReturn;
}

int CTrUnivw::SaveLogFile(CCHARString strText)
{
	if (m_bUseLogFile)
	{
		FILE* outfile = fopen(m_strLogFileError.GetCHAR(), "a+t");
		if (outfile == NULL) return 5;
		strText = strText + "\n";
		fputs(strText.GetCHAR(), outfile);

		fclose(outfile);
	}

	return 0;
}

void CTrUnivw::xyzazs(double dblAB, double dblAL, double dblBB, double dblBL, double* pAzimuth, double* pZenith, double* pHorD, double* pS)
{
	double dx, dy, dz, x1, y1, z1;

	//dx = pB->m_x - pA->m_x;
	//dy = pB->m_y - pA->m_y;
	//dz = pB->m_z - pA->m_z;

	//x1 = -sin(pA->m_b) * cos(pA->m_l) * dx -
	//	sin(pA->m_b) * sin(pA->m_l) * dy + cos(pA->m_b) * dz;
	//y1 = -sin(pA->m_l) * dx + cos(pA->m_l) * dy; // + 0 * dz;
	//z1 = cos(pA->m_b) * cos(pA->m_l) * dx +
	//	cos(pA->m_b) * sin(pA->m_l) * dy + sin(pA->m_b) * dz;

	//*pHorD = sqrt(pow(x1, 2) + pow(y1, 2));
	////*pAzimuth = arctanm(y1, x1);
	//*pAzimuth = atan2(y1, x1);
	//*pS = sqrt(pow(x1, 2) + pow(y1, 2) + pow(z1, 2));
	////*pZenith = arctanm(*pHorD, z1);
	//*pZenith = atan2(*pHorD, z1);

	double dbldB = dblBB - dblAB;
	double dbldL = dblBL - dblAL;

	double Azim = sin(dbldB / 2) * sin(dbldB / 2) +
		cos(dblAB) * cos(dblBB) *
		sin(dbldL / 2) * sin(dbldL / 2);
	double c = 2 * atan2(sqrt(Azim), sqrt(1 - Azim));

	double Dist = 6371000 * c; // in metres

	*pAzimuth = Azim;
	*pS = Dist;
}

void CTrUnivw::SetLogFile(CCHARString strFileName)
{
	m_strLogFileError = strFileName;
	if (m_strLogFileError == "")
		m_bUseLogFile = false;
	else
	{
		m_bUseLogFile = true;
		remove(m_strLogFileError);
	}
}

/////////////////////////////////////////////////////////////////////////
//Additional functions
////////////////////////////////////////////////////////////////////////
void MandG(double a, double f, double ff, double l, double& gama, double& ma)
{
	double a1, a2, a3, a4;
	double l2, l4, l6, s, c2, c4, c6, t2, t4, en, er;

	try
	{
		er = 2 * f - sqr(f);
		en = er / (1 - er) * sqr(cos(ff));
		l2 = sqr(l); l4 = sqr(l2); l6 = l4 * l2;
		c2 = sqr(ff); c4 = sqr(c2); c6 = c2 * c4;
		s = sin(ff);
		t2 = sqr(tan(ff)); t4 = sqr(t2);
		a1 = s * l;
		a2 = 1 + 3 * en + 2 * sqr(en);
		a2 = a2 * c2 * s * l2 * l / 3;
		a3 = 2 - t2 + 15 * en - 15 * t2 * en;
		a3 = a3 * c4 * s * l4 * l / 15;
		a4 = 17 - 26 * t2 + 2 * t4;
		a4 = a4 * c6 * s * l6 * l / 315;
		gama = a1 + a2 + a3 + a4;
		a1 = (1 + en) * c2 * l2 / 2;
		a2 = 5 - 4 * t2 + 14 * en - 28 * t2 * en;
		a2 = a2 * c4 * l4 / 24;
		a3 = 61 - 148 * t2 + 16 * t4;
		a3 = a3 * c6 * l6 / 720;
		ma = 1 + a1 + a2 + a3;
	}
	catch (...)
	{
		gama = -1;
		ma = -1;
	}
}

double B_Mer(double fi, double al, double ap, double mo)
{
	//Calculates dyga po meridiana 
	double e,b;
	double aa,bb,cc,dd,ee,ff;
	
	e = 2 * al - sqr(al);
	aa = 1+3.0/4.0*e+45.0/64.0*sqr(e)+175.0/256.0*e*sqr(e)+11025.0/16384.0*sqr(e)*sqr(e)+
			43659.0/65536.0*sqr(e)*sqr(e)*e;
	bb = (3.0/4.0*e+15.0/16.0*sqr(e)+525.0/512.0*e*sqr(e)+2205.0/2048.0*sqr(e)*sqr(e)+
			72765.0/65536.0*sqr(e)*sqr(e)*e)/2.0;
	cc = (15.0/64.0*sqr(e)+105.0/256.0*e*sqr(e)+2205.0/4096.0*sqr(e)*sqr(e)+
			10395.0/16384.0*sqr(e)*sqr(e)*e)/4.0;
	dd = (35.0/512.0*e*sqr(e)+315.0/2048.0*sqr(e)*sqr(e)+
			31185.0/131072.0*sqr(e)*sqr(e)*e)/6.0;
	ee = (315.0/16384.0*sqr(e)*sqr(e)+
			3465.0/65536.0*sqr(e)*sqr(e)*e)/8.0;
	ff = (693.0/131072.0*sqr(e)*sqr(e)*e)/10.0;
	b = aa*fi-bb*sin(2.0*fi)+cc*sin(4.0*fi)-dd*sin(6.0*fi)+ee*sin(8.0*fi)-ff*sin(10.0*fi);
	
	return b * ap * mo * (1 - e);
}

int BGS2005_Lambert(int direction, int &from_to_type, int &from_to_width, int &from_to_Zone_Meridian, 
					int &from_HSys, int to_HSys, double &x, double &y, double &z, const char* strGRDFile)
{//{BGS2005<-->BGS2005_Lambert}
	CLambert objLambert;
	double Lamb_a = 6378137.0;
	double Lamb_f = 1 / 298.257222101;
	double Lamb_Central_Meridian = gtor(253000, CF_CODE_D_M_S);
	double Lamb_Std_Parallel_1 = gtor(420000.00, CF_CODE_D_M_S);
	double Lamb_Std_Parallel_2 = gtor(432000.00, CF_CODE_D_M_S);
	double Lamb_Origin_Latitude = objLambert.Get_Origin_Lattitude(Lamb_Std_Parallel_1, Lamb_Std_Parallel_2, Lamb_f);
	double Lamb_False_Easting = 500000;
	double North_Meridian = B_Mer(Lamb_Origin_Latitude, Lamb_f, Lamb_a, 1);
#ifdef _MARIAN
	double NM = ret_X0(Lamb_Origin_Latitude);
#endif
	double Lamb_False_Northing = North_Meridian;
	long status = 0;
	objLambert.Set_Lambert_Parameters(Lamb_a, Lamb_f, Lamb_Origin_Latitude, Lamb_Central_Meridian,
			Lamb_Std_Parallel_1, Lamb_Std_Parallel_2, Lamb_False_Easting, Lamb_False_Northing);
	double east, north;
	if (direction == 1)
	{
		status = objLambert.Convert_Geodetic_To_Lambert(x, y, &east, &north);
#ifdef _MARIAN
		double EE, NN;
		BLToGrid(x, y, &EE, &NN);
#endif
		if (status != 0) return status;
		x = north;
		y = east;
		from_to_type = CT_CAD_CODE;
	}
	else
	{
		north = x;
		east = y;
		status = objLambert.Convert_Lambert_To_Geodetic (east, north, &x, &y);
#ifdef _MARIAN
		double B, L;
		GridToBL(east, north, &B, &L);
#endif
		if (status != 0) 
		{
			return status;
		}
		from_to_type = CT_BL_CODE;
	}
	from_to_width = ZW_UNKNOWN_CODE;

	return 0;
}

double GetLambertConvergence(double B, double L)
{
	CLambert objLambert;
	double nReturn = NO_DVALUE;
	double Lamb_a = 6378137.0;
	double Lamb_f = 1 / 298.257222101;
	double Lamb_Central_Meridian = gtor(253000, CF_CODE_D_M_S);
	double Lamb_Std_Parallel_1 = gtor(420000.00, CF_CODE_D_M_S);
	double Lamb_Std_Parallel_2 = gtor(432000.00, CF_CODE_D_M_S);
	double Lamb_Origin_Latitude = objLambert.Get_Origin_Lattitude(Lamb_Std_Parallel_1, Lamb_Std_Parallel_2, Lamb_f);
	double Lamb_False_Easting = 500000;
	double North_Meridian = B_Mer(Lamb_Origin_Latitude, Lamb_f, Lamb_a, 1);
#ifdef _MARIAN
	double NM = ret_X0(Lamb_Origin_Latitude);
#endif
	double Lamb_False_Northing = North_Meridian;
	long status = 0;
	//int to_type, to_width;
	objLambert.Set_Lambert_Parameters(Lamb_a, Lamb_f, Lamb_Origin_Latitude, Lamb_Central_Meridian,
		Lamb_Std_Parallel_1, Lamb_Std_Parallel_2, Lamb_False_Easting, Lamb_False_Northing);
	
	nReturn = objLambert.Get_Convegence(B, L);

	return nReturn;
}

double lin_slope_to_ellipsoid(double B1, double h1p, double B2, double h2p, double dist, double alfll, double rm)
{
	double dhp = h2p - h1p;
	double ttt1 = sqrt((sqr(dist) - sqr(dhp)) / ((1 + h1p / rm) * (1 + h2p / rm)));
	double ttt2 = 2 * rm*asin(ttt1 / (2 * rm));

	return ttt2;
}

void clearxyh(double& x, double& y, double& h)
{
	x = -1.0;
	y = -1.0;
	if (h != 0.0) h = -1.0;
}

int Transform_Helmert_4(int nPath, double X0, double Y0, double F0, double scale, double &x, double &y)
{
	//nPath = 0 direct transformation
	//nPath = 1 reverse transformation
	//x,y - geodetic orientation
	//Helmert 4 parameter transformation
	double xtr, ytr;
	if(nPath == 0)
	{
		xtr = X0 + x * scale * cos(F0) + y * scale * sin(F0);
		ytr = Y0 - x * scale * sin(F0) + y * scale * cos(F0);
	}
	else
	{
		xtr = (x - X0) * cos(F0) - (y - Y0) * sin(F0);
		ytr = (x - X0) * sin(F0) + (y - Y0) * cos(F0);
	}
	
	x = xtr;
	y = ytr;

	return TRUNIVW_NO_ERROR;
}
