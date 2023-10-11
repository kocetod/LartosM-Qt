#include "transform.h"
//#include "TransHelper.h"
//#include "TrUnivw.h"
#include "secret.h"
#include "geodw.h"
//#include <string.h>
#include "General/GlobalVariables.h"
#include "utm.h"
#include "mgrs.h"
#include <math.h>

#ifdef   _DEBUG
#define  SET_CRT_DEBUG_FIELD(a) \
            _CrtSetDbgFlag((a) | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#define  CLEAR_CRT_DEBUG_FIELD(a) \
            _CrtSetDbgFlag(~(a) & _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#else
#define  SET_CRT_DEBUG_FIELD(a)   ((void) 0)
#define  CLEAR_CRT_DEBUG_FIELD(a) ((void) 0)
#endif
//*************************************************************
//							Directives
//*************************************************************
//_EXCLUDE_BSTR_
//WINDOWS_VER
//*************************************************************

CTransform* g_objTransform = NULL;

//*************************************************************
//							class CTransform
//*************************************************************

CTransform::CTransform()
{
	g_bTransInitialized = false;
	g_bUseLogFile = false;

	//g_OtherSystemsUsed = false;
	
	g_objEGM96 = NULL;
	g_TrUnivw = NULL;
	g_nChoiceHeightMethod = CHOICE_H_METOD_NOTDEFINED;
	
	m_strGeoidData = "";
	m_nHMChoice = CHOICE_H_METOD_NOTDEFINED;
	m_bEGMModel = false;
	m_strEGMModel = "";
	m_bTransformHeight = true;
}

CTransform::~CTransform()
{
	FreeTrans();
}

int CTransform::Transform(int nSys1, int nSys2, int nType1, int nType2, int nWidth1, int nWidth2, int nZone1, int* pZone2,
	int nHSys1, int nHSys2, double* pX, double* pY, double* pH)
{
	int nReturn = TRANS_NO_ERROR;
	if (!IsInitialized()) return TRANS_NOT_INITIALIZED;
#ifndef _TRIAL_VERSION_
	double x = *pX;
	double y = *pY;
	double h = pH ? (*pH) : 0;
	int nZone2 = *pZone2;
	long nStatus = 0;
	int nRealChoice;
	nReturn = g_TrUnivw->Coordtr(nSys1, nType1, nWidth1, nSys2, nType2, nWidth2, nZone1, nZone2, x, y, h);
	if (nReturn == TRANS_NO_ERROR && IsSetTransformHeight())
	{
		nStatus = TransformAllHeight(nSys2, nType2, nWidth2, nZone2, nHSys1, nHSys2, x, y, h, g_nChoiceHeightMethod, nRealChoice);
	}

	if (nReturn == TRANS_NO_ERROR)
	{
		if (nStatus != TRANS_NO_ERROR)
			nReturn = TRANS_HEIGHTISNOTTRANSFORMED_ERROR;
		*pX = x;
		*pY = y;
		if (pH)
			*pH = h;
		*pZone2 = nZone2;
	}
#endif //_TRIAL_VERSION_
	return nReturn;
}

void CTransform::FreeTrans()
{
	if (g_TrUnivw) delete g_TrUnivw;
	delete g_objEGM96;
	g_objEGM96 = NULL;
	g_bTransInitialized = false;
}

void CTransform::SetModuleDir(CCHARString strModuleDir)
{
	if (strModuleDir[strModuleDir.GetLength() - 1] != '\\' &&
		strModuleDir[strModuleDir.GetLength() - 1] != '/')
		strModuleDir += "/";
	g_strModuleDir = strModuleDir;
}

void CTransform::SetGeoidPath(CCHARString strGeoid1, CCHARString strGeoid2)
{
	if (strGeoid1 == "-" || strGeoid1 == "")
	{
		if(g_strGeoidPath == "") g_strGeoidPath = g_strModuleDir + "geoidbul.grd";
	}
	else g_strGeoidPath = strGeoid1;
	if (strGeoid2 != "") g_strGeoidPath1 = strGeoid2;
}

void CTransform::SetGlobalLogFile(CCHARString strFileName)
{
	g_strLogFileError = strFileName;
	if (g_strLogFileError == "")
		g_bUseLogFile = false;
	else
	{
		g_bUseLogFile = true;
		remove(g_strLogFileError);
	}
}

int CTransform::SaveLogFile(CCHARString strText)
{
	if (g_bUseLogFile)
	{
		FILE *outfile = fopen(g_strLogFileError.GetCHAR(), "a+t");
		if (outfile == NULL) return 5;
		strText = strText + "\n";
		fputs(strText.GetCHAR(), outfile);

		fclose(outfile);
	}

	return 0;
}

long CTransform::TransformAllHeight(int syst, int type, int width, int zmer, int shsyst, int thsyst,
	double& x, double& y, double& h, int nChoice, int& nNewChoice)
{
	long nReturn = TRANS_NO_ERROR;
	nNewChoice = CHOICE_H_METOD_NOTDEFINED;
	if (!IsInitialized()) return TRANS_NOT_INITIALIZED;
	double trOriX = x, trOriY = y, trOriZ = h;
	double trX = trOriX, trY = trOriY, trZ = trOriZ;
	int nTempZone = NO_VALUE;
	long status = TRANS_NO_ERROR;
	double trxx, tryy, DeltaHeight = VALUE_H_NOT_USED;
	double dblNewHeight = VALUE_H_NOT_USED;
	double dblDHOrthometric = 0;
	CCHARString strTemp1;

	if (shsyst == thsyst ||
		(shsyst == HS_UNKNOWN_CODE || thsyst == HS_UNKNOWN_CODE)) return nReturn;
	if (h == 0.0) return nReturn;
	trX = trOriX; trY = trOriY; trZ = trOriZ;
	x = trOriX; y = trOriY; h = trOriZ;
	if (g_objEGM96 != NULL)
	{
		if (g_objEGM96->Geoid_Initialized)
		{
			nReturn = g_objEGM96->TransformAllHeight((void*)this, syst, type, width, zmer, shsyst, thsyst, x, y, h, GRD_HEIGHTTYPE_WGS_EVRS2000);
		}
		else nReturn = TRANS_NOGEOIDMODEL_ERROR;

	}
	else
		nReturn = TRANS_NOGEOIDMODEL_ERROR;
	if (nReturn == TRANS_NO_ERROR)
	{
		if (nChoice == CHOICE_H_METOD_GRD_GLOBAL || nChoice == CHOICE_H_METOD_NOTDEFINED)
		{
			nNewChoice = CHOICE_H_METOD_GRD_GLOBAL;
			if (!m_bEGMModel)
			{
				m_bEGMModel = true;
				m_strEGMModel = "egm96.grd";
				m_strGeoidData = "EGM96";
				m_nHMChoice = CHOICE_H_METOD_GRD_GLOBAL;
			}

			return TRANS_NO_ERROR;
		}
	}
	else if (nChoice == CHOICE_H_METOD_GRD_GLOBAL) return nReturn;

	strTemp1.Format("Not transformed height with status = %ld", nReturn);
	SaveLogFile(strTemp1);

	return TRANS_HEIGHTISNOTTRANSFORMED_ERROR;
}

long CTransform::PrepareCoordinates(int ssyst, int stype, int swidth, int szmer, int tsyst, int ttype, int twidth, int tzmer,
	double &x, double &y, double &h)
{
	long nReturn = 0;
	nReturn = g_TrUnivw->Coordtr(ssyst, stype, swidth, tsyst, ttype, twidth, szmer, tzmer, x, y, h);

	return nReturn;
}

long CTransform::InitializeTransform()
{
	if (!IsInitialized())
	{
		try
		{
			g_TrUnivw = new CTrUnivw;
			if (g_TrUnivw == NULL) return TRANS_NOT_CREATED;
			g_TrUnivw->SetLogFile(g_strLogFileError);
			g_objEGM96 = new CGeoid();
			g_objEGM96->Initialize_Geoid(g_strModuleDir);
			SetGeoidPath();
			g_bTransInitialized = true;
		}
		catch (...)
		{
		}
	}

	return  TRANS_NO_ERROR;
}

void CTransform::SetHMethod(int nChocieHMethod)
{
	g_nChoiceHeightMethod = nChocieHMethod;
}

int CTransform::GetHMethod()
{
	return g_nChoiceHeightMethod;
}

long CTransform::M_G(double a, double f, double b, double l, double *gama, double *m, int nProjection)
{//nProjection = 0 TransverseMercator; nProjection = 1 Lambert Conic
	double dblGama, dblM;
	if (nProjection == 0)
	{
		MandG(a, f, b, l, dblGama, dblM);
		*gama = dblGama;
		*m = dblM;
	}
	else
	{
		*gama = GetLambertConvergence(b, l);
	}
	return 1;
}

long CTransform::M_G(int nSys, double b, double l, double *gama, double *m, int nProjection)
{//nProjection = 0 TransverseMercator; nProjection = 1 Lambert Conic
	double dblGama, dblM;
	double a = 0, f = 0, Scale = 1;

	Get_Ellipsoid_Parameters_By_System(nSys, &a, &f, &Scale);
	if (nProjection == 0)
	{
		MandG(a, f, b, l, dblGama, dblM);
		*gama = dblGama;
		*m = dblM;
	}
	else
	{
		*gama = GetLambertConvergence(b, l);
	}
	return 1;
}

bool CTransform::IsInitialized()
{
	return g_bTransInitialized;
}

int CTransform::UTMZoneFromBL(double B, double L)
{
	int nReturn = -1;
	int nUTMZone = -1;
	CUTM objUTM;
	long nStatus = objUTM.UTMZoneFromBL(B, L, &nUTMZone);
	if (nStatus == UTM_NO_ERROR) nReturn = nUTMZone;
	
	return nReturn;
}

long CTransform::RETMGRS(double x, double y, int type, int Zone, char *MGRS)
{
	long error_code = TRANS_NO_ERROR;
	long Precision = 5;
	size_t Index;
	CCHARString Elipsoid_Code;
	double a, f, Scale;
	char Hemisphere = 'N';
	Elipsoid_Code = "RF";
	Get_Ellipsoid_Parameters_By_System(CS_WGS84_CODE, &a, &f, &Scale);
	CMGRS objMGRS;
	objMGRS.Set_MGRS_Parameters(a, f, "RF");
	switch (type)
	{
	case CT_UTM_CODE:
		if (!objMGRS.Convert_UTM_To_MGRS(Zone, Hemisphere, x, y, Precision, MGRS))
			return TRANS_MGRS_ERROR;
		break;
	case CT_BL_CODE:
		if (!objMGRS.Convert_Geodetic_To_MGRS(x, y, Precision, MGRS))
			return TRANS_MGRS_ERROR;
	}

	return error_code;
}

long CTransform::PrepareGeographicCoo(double Angle, double* dblResult, int nCodeFormat)
{
	long nReturn = PREPGEOCOO_NO_ERROR;
	if (nCodeFormat == CF_CODE_DMS ||
		nCodeFormat == CF_CODE_D_M_S ||
		nCodeFormat == CF_CODE_D_MS ||
		nCodeFormat == CF_CODE_DD ||
		nCodeFormat == CF_CODE_DM ||
		nCodeFormat == CF_CODE_SECS)
		*dblResult = rtog(Angle, nCodeFormat);
	else
		nReturn = PREPGEOCOO_FORMAT_ERROR;

		return nReturn;
}


CCHARString CTransform::PrepareGeographicCoo(double Angle, int nFromFormat, int nToFormat, int decimal)
{
	CCHARString strReturn = "";
	strReturn = angletostr(Angle, nFromFormat, nToFormat, decimal);

	return strReturn;
}

CCHARString CTransform::PrepareCooString(double dblCoo, int nFromFormat, int nToFormat, int decimal)
{
	CCHARString strReturn = "";
	if (nFromFormat == CF_CODE_METERS)
	{
		nToFormat = nFromFormat;
		strReturn.Format("%0.*lf", decimal, dblCoo);
	}
	else
	{
		strReturn = angletostr(dblCoo, nFromFormat, nToFormat, decimal);
	}

	return strReturn;
}

//bool CTransform::IsWebServiceUsed()
//{
//	return g_WebServiceUsed;
//}
//
//void CTransform::SetWebServiceUsed(bool bUse)
//{
//	g_WebServiceUsed = bUse;
//}

//bool CTransform::IsWebServiceTurnedOn()
//{
//#ifdef _WEBSERVICE_
//	return g_objWebUtility->IsWebServiceTurnedOn();
//#else
//	return false;
//#endif //_WEBSERVICE_
//}

void CTransform::GetUsedGeoidChoiceAndData(CCHARString &strGeoidData, int &nHMChoice)
{
	strGeoidData = m_strGeoidData;
	nHMChoice = m_nHMChoice;
}

int CTransform::CalcHeight(int shsyst, int thsyst, int syst, int type, int width, int zone, double B, double L, double H, double& HNew, double DeltaHeight, int nTypeOfGeoid)
{
	double HEVRF2000 = 0;
	double HEVRF2007 = 0;
	CCHARString strMessage;
	int nTempZone = ZONE_AUTO;
	double dblH = H;
	//int nStatus = Transform(syst, CS_WGS84_CODE, type, CT_BL_CODE, width, ZW_UNKNOWN_CODE, zone, &nTempZone,
	//						HS_UNKNOWN_CODE, HS_UNKNOWN_CODE, &B, &L, &dblH);
	int nStatus = g_TrUnivw->Coordtr(syst, type, width, CS_WGS84_CODE, CT_BL_CODE, ZW_UNKNOWN_CODE, zone, nTempZone, B, L, dblH);
	H = dblH;
	BG_KRON_NH_to_EVRF2000(B, L, HEVRF2000);
	BG_KRON_NH_to_EVRF2007(B, L, HEVRF2007);
	if (nStatus == TRANS_NO_ERROR)
	{
		if (nTypeOfGeoid == GRD_HEIGHTTYPE_UNDEFINED)
		{
			if (H == VALUE_H_NOT_USED) nStatus = TRANS_GEOID_HEIGHTTYPE_UNDEFINED;
            else
            {
                H += fabs(DeltaHeight);
			    HNew = H;
			}
			return nStatus;
		}
		switch (shsyst)
		{
		case HS_BALTIC_CODE:
		{
			if (thsyst == HS_WGS_CODE)
			{
				if (nTypeOfGeoid == GRD_HEIGHTTYPE_WGS_EVRS2000)
				{
					H += HEVRF2000;
				}
				else if (nTypeOfGeoid == GRD_HEIGHTTYPE_WGS_EVRS2007)
				{
					H += HEVRF2007;
				}
                if (DeltaHeight != VALUE_H_NOT_USED)
				    H += fabs(DeltaHeight);
                else
                    nStatus = TRANS_HEIGHTISNOTTRANSFORMED_ERROR;
			}
			else if (thsyst == HS_EVRF2000_CODE)
			{
				H += HEVRF2000;
			}
			else if (thsyst == HS_EVRF2007_CODE)
			{
				H += HEVRF2007;
			}
		}
		break;
		case HS_WGS_CODE:
		{
			if (DeltaHeight != VALUE_H_NOT_USED)
			{
				H -= fabs(DeltaHeight);
				if (thsyst == HS_BALTIC_CODE)
				{
					if (nTypeOfGeoid == GRD_HEIGHTTYPE_WGS_EVRS2000)
					{
						H -= HEVRF2000;
					}
					else if (nTypeOfGeoid == GRD_HEIGHTTYPE_WGS_EVRS2007)
					{
						H -= HEVRF2007;
					}
				}
				else if (thsyst == HS_EVRF2000_CODE)
				{
					if (nTypeOfGeoid == GRD_HEIGHTTYPE_WGS_BALTIC)
					{
						H += HEVRF2000;
					}
					else if (nTypeOfGeoid == GRD_HEIGHTTYPE_WGS_EVRS2007)
					{
						H = H - HEVRF2007 + HEVRF2000;
					}
				}
				else if (thsyst == HS_EVRF2007_CODE)
				{
					if (nTypeOfGeoid == GRD_HEIGHTTYPE_WGS_BALTIC)
					{
						H += HEVRF2007;
					}
					else if (nTypeOfGeoid == GRD_HEIGHTTYPE_WGS_EVRS2000)
					{
						H = H - HEVRF2000 + HEVRF2007;
					}
				}
			}
            else
                    nStatus = TRANS_HEIGHTISNOTTRANSFORMED_ERROR;
		}
		break;
		case HS_EVRF2000_CODE:
		{
			if (thsyst == HS_BALTIC_CODE)
			{
				H -= HEVRF2000;
			}
			else if (thsyst == HS_WGS_CODE)
			{
				if (nTypeOfGeoid == GRD_HEIGHTTYPE_WGS_BALTIC)
				{
					H -= HEVRF2000;
				}
				else if (nTypeOfGeoid == GRD_HEIGHTTYPE_WGS_EVRS2007)
				{
					H = H - HEVRF2000 + HEVRF2007;
				}
				if (DeltaHeight != VALUE_H_NOT_USED)
					H += fabs(DeltaHeight);
			}
			else if (thsyst == HS_EVRF2007_CODE)
			{
				H = H - HEVRF2000 + HEVRF2007;
			}
		}
		break;
		case HS_EVRF2007_CODE:
		{
			if (thsyst == HS_BALTIC_CODE)
			{
				H -= HEVRF2007;
			}
			else if (thsyst == HS_WGS_CODE)
			{
				if (nTypeOfGeoid == GRD_HEIGHTTYPE_WGS_BALTIC)
				{
					H -= HEVRF2007;
				}
				else if (nTypeOfGeoid == GRD_HEIGHTTYPE_WGS_EVRS2000)
				{
					H = H - HEVRF2007 + HEVRF2000;
				}
				if (DeltaHeight != VALUE_H_NOT_USED)
					H += fabs(DeltaHeight);
			}
			else if (thsyst == HS_EVRF2000_CODE)
			{
				H = H - HEVRF2007 + HEVRF2000;
			}
		}
		break;
		}
	}
	HNew = H;
	if (HNew == VALUE_H_NOT_USED) nStatus = TRUNIVW_HEIGHT_TRANSFORM_ERROR;

	return nStatus;
}

//bool CTransform::IsOtherSystemsUsed()
//{
//	return g_OtherSystemsUsed;
//}

//void CTransform::reversecoo(int nType1, double* x, double* y)
//{
//	if (nType1 != CT_XYZ_CODE)
//	{
//		double X1 = *y, Y1 = *x;
//		*x = X1;
//		*y = Y1;
//	}
//}

void CTransform::SetTransformHeight(bool bSet)
{
	m_bTransformHeight = bSet;
}

bool CTransform::IsSetTransformHeight()
{
	return m_bTransformHeight;
}

//************************End of class CTransform************************************

//*************************************************************
//							Global Functions
//*************************************************************

void* CreateTransCustom(CCHARString strModuleDir, CCHARString strLogFileName, bool bUseLog)
{
	CCHARString strF;
	CTransform* objTransform = new CTransform();
	if (objTransform != NULL)
	{
		objTransform->SetModuleDir(strModuleDir);
		if (strLogFileName != "")
		{
			remove(strLogFileName);
		}
		objTransform->SetGlobalLogFile(strLogFileName);
		objTransform->InitializeTransform();
		if (objTransform->IsInitialized())
			return (void*)objTransform;
	}

	return NULL;
}

int CreateTransCustomF(void** objTr, CCHARString strModuleDir, CCHARString strLogFileName, bool bUseLog)
{
	int nReturn = 0;
	CTransform * objTransform = new CTransform();
	if (objTransform != NULL)
	{
		objTransform->SetModuleDir(strModuleDir);
		if (strLogFileName != "")
		{	
			remove(strLogFileName);
		}
		objTransform->SetGlobalLogFile(strLogFileName);
		objTransform->InitializeTransform();
		if (objTransform->IsInitialized())
			*objTr = (void*)objTransform;
		else
			nReturn = 9;
	}

	return nReturn;
}

int DeleteTransCustom(void *objTransform)
{
	if (objTransform != 0)
	{
		CTransform * m_objTransform = (CTransform *)objTransform;
		delete m_objTransform;
	}

	return 0;
}

int TrCust(void *objTransform, int nSys1, int nSys2, int nType1, int nType2, int nWidth1, int nWidth2, int nZone1, int* pZone2,
	int nHSys1, int nHSys2, double* pX, double* pY, double* pH, int nChoiceHMethod)
{
	int nReturn = TRANS_NO_ERROR;
	CTransform * m_objTransform = (CTransform *)objTransform;
	if(objTransform != NULL)
	{
		if (m_objTransform->IsInitialized())
		{
			m_objTransform->SetHMethod(nChoiceHMethod);
			nReturn = m_objTransform->Transform(nSys1, nSys2, nType1, nType2, nWidth1, nWidth2,
					nZone1, pZone2, nHSys1, nHSys2, pX, pY, pH);
		}
		else nReturn = TRANS_NOT_INITIALIZED;
	}
	else nReturn = TRANS_NOT_CREATED;

	return nReturn;
}
