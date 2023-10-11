#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "TrUnivw.h"
#include "PointCoo.h"

#define PREPGEOCOO_NO_ERROR			0
#define PREPGEOCOO_FORMAT_ERROR		1


#define REG_STORAGE_REGISTRY		1
#define REG_STORAGE_FILE			2

#define COMPANYSTRINGMY		"Geomatics"
#define PROGRAMMNAMEMY		"Trans_dll"

//class COtherTransFunc;
class CTransform
{
public:
	int g_nChoiceHeightMethod;
	bool g_bTransInitialized;
	CCHARString g_strModuleDir;
	CCHARString g_strGeoidPath;
	CCHARString g_strGeoidPath1;
	CCHARString g_strLogFileError;
	bool g_bUseLogFile;
	CCHARString m_strGeoidData;
	bool m_bEGMModel;
	CCHARString m_strEGMModel;

	int m_nHMChoice;

	CTrUnivw* g_TrUnivw;
	CGeoid* g_objEGM96;
	bool m_bTransformHeight;

public:
	CTransform();
	~CTransform();
	int Transform(int nSys1, int nSys2, int nType1, int nType2, int nWidth1, int nWidth2, int nZone1, int* pZone2, int nHSys1, int nHSys2, double* pX, double* pY, double* pH);
	void FreeTrans();
	void SetModuleDir(CCHARString strModuleDir);
	void SetGeoidPath(CCHARString strGeoid1 = "-", CCHARString strGeoid2 = "");
	void SetGlobalLogFile(CCHARString strFileName);
	int SaveLogFile(CCHARString strText);
	long TransformAllHeight(int syst, int type, int width, int zmer, int shsyst, int thsyst,
		double &x, double &y, double &h, int nChoice, int &nNewChoice);
	long PrepareCoordinates(int ssyst, int stype, int swidth, int szmer, int tsyst, int ttype, int twidth, int tzmer,
		double &x, double &y, double &h);
	long InitializeTransform();
	void SetHMethod(int nChocieHMethod);
	int GetHMethod();
	//nProjection = 0 TransverseMercator; nProjection = 1 Lambert Conic
	long M_G(double a, double f, double b, double l, double *gama, double *m, int nProjection);
	long M_G(int nSys, double b, double l, double *gama, double *m, int nProjection);
	bool IsInitialized();
	int UTMZoneFromBL(double B, double L);

	long RETMGRS(double x, double y, int type, int Zone, char *MGRS);
	long PrepareGeographicCoo(double Angle, double* dblResult, int nCodeFormat);
	CCHARString PrepareGeographicCoo(double Angle, int nFromFormat, int nToFormat, int decimal);
	CCHARString PrepareCooString(double dblCoo, int nFromFormat, int nToFormat, int decimal);
	void GetUsedGeoidChoiceAndData(CCHARString& strGeoidData, int& nHMChoice);
	int CalcHeight(int shsyst, int thsyst, int syst, int type, int width, int zone, double B, double L, double H, double& HNew, double DeltaHeight, int nTypeOfGeoid);
	void SetTransformHeight(bool bSet);
	bool IsSetTransformHeight();
};

void* CreateTransCustom(CCHARString strModuleDir, CCHARString strLogFileName, bool bUseLog = true);
int CreateTransCustomF(void** objTr, CCHARString strModuleDir, CCHARString strLogFileName, bool bUseLog);
int TrCust(void *objTransform, int nSys1, int nSys2, int nType1, int nType2, int nWidth1, int nWidth2, int nZone1, int* pZone2,
	int nHSys1, int nHSys2, double* pX, double* pY, double* pH, int nChoiceHMethod = -1);
int DeleteTransCustom(void *objTransform);

#endif //__TRANSFORM_H__
