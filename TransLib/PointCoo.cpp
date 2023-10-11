#include "PointCoo.h"
#include "transform.h"
#include "geodw.h"
#include <math.h>

//*************************************************************
//							class CStationMeasure
//*************************************************************

CStationMeasure::CStationMeasure()
{
	m_bA = NO_DVALUE;
	m_bB = NO_DVALUE;
	m_bC = NO_DVALUE;
	m_bD = NO_DVALUE;
	m_bE = NO_DVALUE;
	m_bF = NO_DVALUE;
	m_dA = NO_DVALUE;
	m_dB = NO_DVALUE;
	m_dC = NO_DVALUE;
	m_dD = NO_DVALUE;
	m_dE = NO_DVALUE;
	m_dF = NO_DVALUE;
	m_vA = NO_DVALUE;
	m_vB = NO_DVALUE;
	m_vC = NO_DVALUE;
	m_vD = NO_DVALUE;
	m_vE = NO_DVALUE;
	m_vF = NO_DVALUE;
	m_nHorANgleType = CF_CODE_DD;
	m_nVertANgleType = CF_CODE_DD;
}

CStationMeasure::~CStationMeasure()
{
}

void CStationMeasure::SetMeasure(int nIndex, double b, double d, double v)
{
	switch (nIndex)
	{
	case 0:
		m_bA = b;
		m_dA = d;
		m_vA = v;
		break;
	case 1:
		m_bB = b;
		m_dB = d;
		m_vB = v;
		break;
	case 2:
		m_bC = b;
		m_dC = d;
		m_vC = v;
		break;
	case 3:
		m_bD = b;
		m_dD = d;
		m_vD = v;
		break;
	case 4:
		m_bE = b;
		m_dE = d;
		m_vE = v;
		break;
	case 5:
		m_bF = b;
		m_dF = d;
		m_vF = v;
		break;
	}
}

double CStationMeasure::GetPosoka(int nIndex, int nType)
{
	double dblReturn = NO_DVALUE;
	switch (nIndex)
	{
	case 0:
		dblReturn = ConvertAngleFormats(m_bA, m_nHorANgleType, nType);
		break;
	case 1:
		dblReturn = ConvertAngleFormats(m_bB, m_nHorANgleType, nType);
		break;
	case 2:
		dblReturn = ConvertAngleFormats(m_bC, m_nHorANgleType, nType);
		break;
	case 3:
		dblReturn = ConvertAngleFormats(m_bD, m_nHorANgleType, nType);
		break;
	case 4:
		dblReturn = ConvertAngleFormats(m_bE, m_nHorANgleType, nType);
		break;
	case 5:
		dblReturn = ConvertAngleFormats(m_bF, m_nHorANgleType, nType);
		break;
	}

	return dblReturn;
}

double CStationMeasure::GetPointsAngle(int left, int right, int nType)
{
	double dblReturn = NO_DVALUE;
	if (left != -1 && right != -1)
	{
		dblReturn = GetPosoka(right, nType) - GetPosoka(left, nType);
		if (dblReturn < 0) dblReturn = dblReturn + ConvertAngleFormats(360, CF_CODE_DD, nType);
	}

	return dblReturn;
}

double CStationMeasure::GetDistance(int nIndex)
{
	double dblReturn = NO_DVALUE;
	switch (nIndex)
	{
	case 0:
		dblReturn = m_dA;
		break;
	case 1:
		dblReturn = m_dB;
		break;
	case 2:
		dblReturn = m_dC;
		break;
	case 3:
		dblReturn = m_dD;
		break;
	case 4:
		dblReturn = m_dE;
		break;
	case 5:
		dblReturn = m_dF;
		break;
	}

	return dblReturn;
}

double CStationMeasure::GetVertical(int nIndex, int nType)
{
	double dblReturn = NO_DVALUE;
	switch (nIndex)
	{
	case 0:
		dblReturn = ConvertAngleFormats(m_vA, m_nVertANgleType, nType);
		break;
	case 1:
		dblReturn = ConvertAngleFormats(m_vB, m_nVertANgleType, nType);
		break;
	case 2:
		dblReturn = ConvertAngleFormats(m_vC, m_nVertANgleType, nType);
		break;
	case 3:
		dblReturn = ConvertAngleFormats(m_vD, m_nVertANgleType, nType);
		break;
	case 4:
		dblReturn = ConvertAngleFormats(m_vE, m_nVertANgleType, nType);
		break;
	case 5:
		dblReturn = ConvertAngleFormats(m_vF, m_nVertANgleType, nType);
		break;
	}

	return dblReturn;
}

int CStationMeasure::AnalyzeOrder(int nP)
{
	int nReturn = -1;
	if (nP != -1)
	{
		double b = GetPosoka(nP, CF_CODE_RADIANS);
		if (b != NO_DVALUE)
		{
			double b1;
			for (int i = 0; i < 6; i++)
			{
				b1 = GetPosoka(i, CF_CODE_RADIANS);
				if (b1 == NO_DVALUE) continue;
				if (b1 <= b) nReturn++;
			}
		}
		else
			nReturn = -1;
	}

	return nReturn;
}


//*************************************************************
//							class CPoint
//*************************************************************

CPoint::CPoint()
{
	m_dblX_L_E = NO_DVALUE;
	m_dblY_B_N = NO_DVALUE;
	m_dblZ_H = NO_DVALUE;
	m_nSys = CS_UNKNOWN_CODE;
	m_nType = CT_UNKNOWN_CODE;
	m_nWidth = ZW_UNKNOWN_CODE;
	m_dblZone = NO_DVALUE;
	m_nHSys = HS_UNKNOWN_CODE;
	m_bSet = false;
	nPointStatus = 0;
}

CPoint::~CPoint()
{
}

void CPoint::SetPoint(double x, double y, double z, int nSys, int nType,
	int nWidth, double dblZone, int nHSys)
{
	//geodetic orientation coordinates
	if (nType == CT_XYZ_CODE)
	{
		m_dblX_L_E = x;
		m_dblY_B_N = y;
	}
	else
	{
		m_dblX_L_E = y;
		m_dblY_B_N = x;
	}
	m_dblZ_H = z;
	m_nSys = nSys;
	m_nType = nType;
	m_nWidth = nWidth;
	m_dblZone = dblZone;
	m_nHSys = nHSys;
	m_bSet = true;
}

double CPoint::GetX(bool bReverse)
{
	double dblReturn = NO_DVALUE;
	if (bReverse)
	{
		if (m_nType == CT_XYZ_CODE)
			dblReturn = m_dblX_L_E;
		else
			dblReturn = m_dblY_B_N;
	}
	else
		dblReturn = m_dblX_L_E;

	return dblReturn;
}

double CPoint::GetY(bool bReverse)
{
	double dblReturn = NO_DVALUE;
	if (bReverse)
	{
		if (m_nType == CT_XYZ_CODE)
			dblReturn = m_dblY_B_N;
		else
			dblReturn = m_dblX_L_E;
	}
	else
		dblReturn = m_dblY_B_N;

	return dblReturn;
}

double CPoint::GetZ(bool bReverse)
{
	return m_dblZ_H;
}

bool CPoint::IsSet()
{
	return m_bSet;
}

bool CPoint::GetXYZ(double* x, double* y, double* z, bool bReverse)
{
	bool bReturn = false;
	if (IsSet())
	{
		if (bReverse && m_nType != CT_XYZ_CODE)
		{
			*x = m_dblY_B_N;
			*y = m_dblX_L_E;
		}
		else
		{
			*x = m_dblX_L_E;
			*y = m_dblY_B_N;
		}
		*z = m_dblZ_H;
		bReturn = true;
	}

	return bReturn;
}


//*************************************************************
//							class CPointCoo
//*************************************************************


CPointCoo::CPointCoo()
{
	b0 = NO_DVALUE;
	b1 = NO_DVALUE;
	b2 = NO_DVALUE;
	b3 = NO_DVALUE;
	b4 = NO_DVALUE;
	d0 = NO_DVALUE;
	d1 = NO_DVALUE;
	d2 = NO_DVALUE;
	d3 = NO_DVALUE;
	d4 = NO_DVALUE;
	d5 = NO_DVALUE;
	v0 = NO_DVALUE;
	v1 = NO_DVALUE;
	v2 = NO_DVALUE;
	v3 = NO_DVALUE;
	v4 = NO_DVALUE;
	v5 = NO_DVALUE;
	objTrans = NULL;
	m_nIndex = -1;
}

CPointCoo::~CPointCoo()
{
}

long CPointCoo::GetTransformed(CPoint* pPoint, double* X, double* Y, double* Z, int nSys, int nType, int nWidth, double dblZone, int nHSys)
{
	long nReturn = TRANS_TRANSFORM_ERROR;
	if (pPoint == NULL) return nReturn;
	if (pPoint->IsSet() && objTrans != NULL)
	{
		CTransform* objTransform = (CTransform*)objTrans;
		long nStatus = TRANS_NO_ERROR;
		pPoint->GetXYZ(X, Y, Z, true);
		int nZone2 = dblZone;
		int nTempSys = pPoint->m_nSys;
		nStatus = objTransform->Transform(pPoint->m_nSys, nSys, pPoint->m_nType, nType, pPoint->m_nWidth, nWidth, pPoint->m_dblZone, &nZone2, pPoint->m_nHSys, nHSys, X, Y, Z);
		if (nStatus == TRANS_NO_ERROR)
		{
			nReturn = nStatus;
		}
	}

	return nReturn;
}

long CPointCoo::GetGeocentricH0(CPoint* pPoint, double* X, double* Y, double* Z, double* Hori)
{
	long nReturn = TRANS_TRANSFORM_ERROR;
	if (pPoint->IsSet() && objTrans != NULL)
	{
		CTransform* objTransform = (CTransform*)objTrans;
		long nStatus = TRANS_NO_ERROR;
		double x1, y1, z1;
		nStatus = GetBLH(pPoint, &x1, &y1, &z1);
		if (nStatus == TRANS_NO_ERROR)
		{
			*Hori = z1;
			z1 = 0;
			int nZone2 = ZONE_AUTO;
			int nTempSys = pPoint->m_nSys;
			nStatus = objTransform->Transform(nTempSys, nTempSys, CT_BL_CODE, CT_XYZ_CODE, ZW_UNKNOWN_CODE, ZW_UNKNOWN_CODE, ZONE_AUTO, &nZone2,
				HS_UNKNOWN_CODE, HS_UNKNOWN_CODE, &x1, &y1, &z1);
			if (nStatus == TRANS_NO_ERROR)
			{
				*X = x1;
				*Y = y1;
				*Z = z1;
				nReturn = nStatus;
			}
		}
	}

	return nReturn;
}

long CPointCoo::GetBLH(CPoint* pPoint, double* B, double* L, double* H)
{
	long nReturn = TRANS_TRANSFORM_ERROR;
	if (pPoint->IsSet() && objTrans != NULL)
	{
		CTransform* objTransform = (CTransform*)objTrans;
		long nStatus = TRANS_NO_ERROR;
		double x1, y1, z1;
		pPoint->GetXYZ(&x1, &y1, &z1, true);
		int nZone2 = ZONE_AUTO;
		int nTempSys1 = pPoint->m_nSys, nTempSys2 = pPoint->m_nSys;
		nStatus = objTransform->Transform(nTempSys1, nTempSys2, pPoint->m_nType, CT_BL_CODE, pPoint->m_nWidth, ZW_UNKNOWN_CODE,
			pPoint->m_dblZone, &nZone2, pPoint->m_nHSys, pPoint->m_nHSys, &x1, &y1, &z1);
		if (nStatus == TRANS_NO_ERROR)
		{

			*B = x1;
			*L = y1;
			*H = z1;
			nReturn = nStatus;
		}
	}

	return nReturn;
}

long CPointCoo::GetCooByType(CPoint* pPoint, int nType, int nWidth, double dblZone, double* x, double* y, double* h)
{
	long nReturn = TRANS_TRANSFORM_ERROR;
	if (pPoint->IsSet() && objTrans != NULL)
	{
		CTransform* objTransform = (CTransform*)objTrans;
		long nStatus = TRANS_NO_ERROR;
		double x1, y1, z1;
		pPoint->GetXYZ(&x1, &y1, &z1, true);
		int nZone2 = dblZone;
		int nTempSys1 = pPoint->m_nSys, nTempSys2 = pPoint->m_nSys;
		nZone2 = dblZone;
		if (pPoint->m_nType != nType)
		{
			nStatus = objTransform->Transform(nTempSys1, nTempSys2, pPoint->m_nType, nType, pPoint->m_nWidth, nWidth,
				pPoint->m_dblZone, &nZone2, pPoint->m_nHSys, pPoint->m_nHSys, &x1, &y1, &z1);
		}
		if (nStatus == TRANS_NO_ERROR)
		{
			*x = x1;
			*y = y1;
			*h = z1;
			nReturn = nStatus;
		}
	}

	return nReturn;
}



long CPointCoo::CalcPosition(int nP1, int nP2, int nP3, int nP4)
{
	long nReturn = 0;
	long nStatus = 0;
	double b0, b1, b2, b3;
	int nNewP1 = nP1, nNewP2 = nP2, nNewP3 = nP3, nNewP4 = -1;
	nReturn = AnalyzeOrder(nNewP1, nNewP2, nNewP3, nNewP4);
	b0 = Station.GetPointsAngle(nNewP1, nNewP2, CF_CODE_RADIANS);
	b1 = Station.GetPointsAngle(nNewP2, nNewP3, CF_CODE_RADIANS);
	b2 = Station.GetPointsAngle(nNewP1, nP4, CF_CODE_RADIANS);

	double X1 = NO_DVALUE, Y1 = NO_DVALUE, H1 = NO_DVALUE, X2 = NO_DVALUE, Y2 = NO_DVALUE, H2 = NO_DVALUE;
	double X3 = NO_DVALUE, Y3 = NO_DVALUE, H3 = NO_DVALUE, X4 = NO_DVALUE, Y4 = NO_DVALUE, H4 = NO_DVALUE;
	double X5 = NO_DVALUE, Y5 = NO_DVALUE, H5 = NO_DVALUE, X6 = NO_DVALUE, Y6 = NO_DVALUE, H6 = NO_DVALUE;
	double XP = NO_DVALUE, YP = NO_DVALUE, HP = NO_DVALUE;
	double mu = NO_DVALUE;
	GetTransformed(GetPointByIndex(nNewP1), &X1, &Y1, &H1, m_tsyst, m_ttype, m_twidth, m_tzone, m_theight);
	GetTransformed(GetPointByIndex(nNewP2), &X2, &Y2, &H2, m_tsyst, m_ttype, m_twidth, m_tzone, m_theight);
	GetTransformed(GetPointByIndex(nNewP3), &X3, &Y3, &H3, m_tsyst, m_ttype, m_twidth, m_tzone, m_theight);
	GetTransformed(GetPointByIndex(nP4), &X4, &Y4, &H4, m_tsyst, m_ttype, m_twidth, m_tzone, m_theight);
	if (nP2 != -1 && nP3 == -1)
	{
		if (b0 != NO_DVALUE)
		{//obratna zasechka 2
			mu = Obratna_Zasechka_2(b0, d0, d1, X1, Y1, X2, Y2, XP, YP);
		}
		else
		{//linejna zasechka
			mu = Linejna_Zasechka(d0, d1, X1, Y1, X2, Y2, XP, YP);
		}

	}
	else if (nP3 != -1)
	{
		//obratna zasechka
		mu = Obratna_Zasechka(b0, b1, X1, Y1, X2, Y2, X3, Y3, XP, YP);
		nStatus = Obratna_Zasechka_Snelius(b0, b1, X1, Y1, X2, Y2, X3, Y3, XP, YP);
		if (nP4 != -1)
		{//Kontrol
			mu = Obratna_Zasechka_ctg(b0, b1, b2,X1, Y1, X2, Y2, X3, Y3, X4, Y4, XP, YP);
		}
	}

	return nReturn;
}

void CPointCoo::SetMeasure(int nIndex, double b, double d, double v)
{
	Station.SetMeasure(nIndex, b, d, v);
	switch (nIndex)
	{
	case 0:
		d0 = d;
		v0 = Station.GetVertical(0, CF_CODE_RADIANS);
		break;
	case 1:
		d1 = d;
		v1 = Station.GetVertical(1, CF_CODE_RADIANS);
		break;
	case 2:
		d2 = d;
		v2 = Station.GetVertical(2, CF_CODE_RADIANS);
		break;
	case 3:
		d3 = d;
		v3 = Station.GetVertical(3, CF_CODE_RADIANS);
		break;
	case 4:
		d4 = d;
		v4 = Station.GetVertical(4, CF_CODE_RADIANS);
		break;
	case 5:
		b4 = Station.GetPointsAngle(4, 5, CF_CODE_RADIANS);
		d5 = d;
		v5 = Station.GetVertical(5, CF_CODE_RADIANS);
		break;
	}
	if (m_nIndex < nIndex) m_nIndex = nIndex;
}

CPoint* CPointCoo::GetPointByIndex(int nIndex)
{
	CPoint* pPoint = NULL;
	switch (nIndex)
	{
	case 0:
		pPoint = &PointA;
		break;
	case 1:
		pPoint = &PointB;
		break;
	case 2:
		pPoint = &PointC;
		break;
	case 3:
		pPoint = &PointD;
		break;
	case 4:
		pPoint = &PointE;
		break;
	case 5:
		pPoint = &PointF;
		break;
	}

	return pPoint;
}

int CPointCoo::AnalyzeOrder(int& nP1, int& nP2, int& nP3, int& nP4)
{
	int nReturn = 0;
	int nOldP1 = nP1, nOldP2 = nP2, nOldP3 = nP3, nOldP4 = nP4;
	nOldP1 = Station.AnalyzeOrder(nP1);
	nOldP2 = Station.AnalyzeOrder(nP2);
	nOldP3 = Station.AnalyzeOrder(nP3);
	nOldP4 = Station.AnalyzeOrder(nP4);
	int mas[4] = { nOldP1, nOldP2, nOldP3, nOldP4 };
	int masi[4] = { 0, 0, 0, 0 };
	int nTemp = -1;
	int nTempIndex = -1;
	for (int j = 0; j < 4; j++)
	{
		nTemp = 5;
		nTempIndex = -1;
		for (int i = 0; i < 4; i++)
		{
			if (mas[i] != -1 && mas[i] < nTemp)
			{
				nTemp = mas[i];
				nTempIndex = i;
			}
		}
		masi[j] = nTempIndex;
		mas[nTempIndex] = -1;
	}
	nP1 = masi[0];
	nP2 = masi[1];
	nP3 = masi[2];
	nP4 = masi[3];

	return nReturn;
}

//*************************************************************
//							Global fubction
//*************************************************************

long Prava_zadacha(double XA, double YA, double R, double Alfa, double& XP, double& YP)
{
	//geodetic orientation coordinates
	//Alpha = in radians 
	long nReturn = 0;
	XP = XA + R * cos(Alfa);
	YP = YA + R * sin(Alfa);

	return nReturn;
}

long Obratna_zadacha(double XA, double YA, double XB, double YB, double& R, double& Alfa)
{
	//geodetic orientation coordinates
	//Alpha = in radians 
	long nReturn = 0;
	double dx, dy;

	dx = XB - XA;
	dy = YB - YA;
	if (dx == 0)
	{
		if (dy == 0) {
			Alfa = 0;
			R = 0;
			return 9;
		}
		Alfa = PI / 2;
		if (dy < 0) Alfa += PI;
	}
	else
	{
		Alfa = atan(dy / dx);
		if (dx < 0) Alfa = Alfa + PI;
		else if (dy < 0) Alfa = Alfa + 2 * PI;
	}
    if (fabs(dx) > fabs(dy)) R = dx / cos(Alfa);
	else if (fabs(dy) > fabs(dx)) R = dy / sin(Alfa);

	return nReturn;
}

long Prava_Zasechka(double b1, double b2, double xa, double ya, double xb, double yb, double& xp, double& yp)
{
	//geodetic orientation coordinates
	//b1, b2 in radians
	long nReturn = 0;
	double cotgb1, cotgb2;
	cotgb1 = cotg(b1);
	cotgb2 = cotg(b2);
	xp = (yb - ya + xa * cotgb2 + xb * cotgb1) / (cotgb1 + cotgb2);
	yp = (xa - xb + ya * cotgb2 + yb * cotgb1) / (cotgb1 + cotgb2);

	return nReturn;
}

long Prava_Zasechka_direc(double AP, double BP, double xa, double ya, double xb, double yb, double& xp, double& yp)
{
	//geodetic orientation coordinates
	//b1, b2 in radians direccionni agli
	long nReturn = 0;
	if ((fabs(AP - PI) < gtor(2, CF_CODE_DD)) || (fabs(BP - PI) < gtor(2, CF_CODE_DD)) ||
		(AP < gtor(2, CF_CODE_DD)) || (BP < gtor(2, CF_CODE_DD)))
	{
		double tgAP, tgBP;
		tgAP = tan(AP);
		tgBP = tan(BP);
		xp = (xa * tgAP - xb * tgBP + yb - ya) / (tgAP - tgBP);
		yp = (xp - xa) * tgAP + ya;
	}
	else
	{
		double cotgAP, cotgBP;
		cotgAP = cotg(AP);
		cotgBP = cotg(BP);
		yp = (yb * cotgBP - ya * cotgAP + xa - xb) / (cotgBP - cotgAP);
		xp = (yp - ya) * cotgAP + xa;
	}
	
	return nReturn;
}

double Error_Prava_Zasechka(double b1, double b2, double xa, double ya, double xb, double yb, double xp, double yp)
{
	//geodetic orientation coordinates
	//b1, b2 in radians 
	long nReturn = 0;
	double mb = gtor(60.0 / 3600.0, CF_CODE_DD);// accuracy measured angles
	double Dap, Dbp, Dab, AP, AB, BP, BA, b3;
	Obratna_zadacha(xa, ya, xb, yb, Dab, AB);
	if (b1 == 0 || b2 == 0)
	{
		Obratna_zadacha(xa, ya, xp, yp, Dap, AP);
		Obratna_zadacha(xb, yb, xp, yp, Dbp, BP);
		b1 = AB - AP;
		b2 = (AB + PI) - BP;
		if (b1 < 0) b1 = b1 + 2 * PI;
		if (b2 < 0) b2 = b2 + 2 * PI;
	}
	b3 = PI - (b1 + b2);
	nReturn = (mb * Dab * sqrt(pow(sin(b1), 2) + pow(sin(b2), 2))) / (pow(sin(b3), 2));

	return nReturn;
}

double Obratna_Zasechka(double b1, double b2, double xa, double ya, double xb, double yb, double xc, double yc, double& xp, double& yp)
{
	//geodetic orientation coordinates
	//b1, b2 in radians 
	double nReturn = 0.0;
	double AngleBoundary = 30.0;
	if (b1 < gtor(AngleBoundary, CF_CODE_DD) || b2 < gtor(AngleBoundary, CF_CODE_DD))
	{//Angles are not valid.
		nReturn = 9;
	}
	double ct1 = cotg(b1);
	double ct2 = cotg(b2);
	double a1 = yb - ya - (xb - xa) * ct1;
	double a2 = xb - xa + (yb - ya) * ct1;
	double a3 = yb - yc + (xb - xc) * ct2;
	double a4 = xb - xc - (yb - yc) * ct2;
	double a = (a1 * (a2 - a4) - a2 * (a1 - a3)) / (pow((a1 - a3), 2.0) + pow((a2 - a4), 2.0));
	xp = xb + a * (a1 - a3);
	yp = yb - a * (a2 - a4);

	//Error_Obratna_Zasechka

	double mb = gtor(60.0, CF_CODE_SECS);// accuracy measured angles
	double mR = mb / sqrt(2.0);
	double Dap, Dbp, Dab, AP, AB, BP, BA, b3;
	double Dcp, CP, Dbc, BC, Dac, AC;
	Obratna_zadacha(xa, ya, xb, yb, Dab, AB);
	Obratna_zadacha(xa, ya, xp, yp, Dap, AP);
	Obratna_zadacha(xb, yb, xp, yp, Dbp, BP);
	Obratna_zadacha(xc, yc, xp, yp, Dcp, CP);
	Obratna_zadacha(xb, yb, xc, yc, Dbc, BC);
	Obratna_zadacha(xa, ya, xc, yc, Dac, AC);
	double cc1 = sqrt(pow(Dap, 2) * pow(Dbc, 2) + pow(Dbp, 2) * pow(Dac, 2) + pow(Dcp, 2) * pow(Dab, 2));
	double cc2 = Dcp * sin(b1) + Dap * sin(b2) - Dbp * sin(b1 + b2);
	nReturn = mR * cc1 / cc2;

	return nReturn;
}

double Obratna_Zasechka_ctg(double b1, double b2, double b3, double xa, double ya, double xb, double yb, double xc, double yc,
							double xd, double yd, double& xp, double& yp)
{
	//geodetic orientation coordinates
	//b1, b2, b3 in radians 
	double nReturn = 0.0;
	double ct1 = cotg(b1);
	double ct2 = cotg(b1 + b2);
	double a1 = (xb - xa) * ct1 + (xa - xc) * ct2 + yb - yc;
	double a2 = (yb - ya) * ct1 + (ya - yc) * ct2 + xc - xb;
	double PA = atan(a2 / a1);
	if (PA < 0) PA = PA + 2 * PI;
	double AP = PA + PI;
	if (AP > 2 * PI) AP = AP - 2 * PI;
	double BP = PA + PI + b1;
	if (BP > 2 * PI) BP = BP - 2 * PI;
	double CP = PA + PI + b1 + b2;
	if (CP > 2 * PI) CP = CP - 2 * PI;
	double xp1, yp1, xp2, yp2;
	Prava_Zasechka_direc(AP, BP, xa, ya, xb, yb, xp1, yp1);
	Prava_Zasechka_direc(BP, CP, xb, yb, xc, yc, xp2, yp2);
	xp = (xp1 + xp2) / 2.0;
	yp = (yp1 + yp2) / 2.0;
	if (b3 != NO_DVALUE)
	{
		double PD, Dpd;
		Obratna_zadacha(xp, yp, xd, yd, Dpd, PD);
		double PD1 = AP + PI + b3;
		if (PD1 > 2 * PI) PD1 = PD1 - 2 * PI;
		double raz = fabs(PD - PD1);
		//norma 24' / Dpd (km)
		double norm = gtor(((24.0 / (Dpd / 1000.0)) / 60.0), CF_CODE_DD);
		nReturn = raz;
	}

	return nReturn;
}

double Linejna_Zasechka(double d1, double d2, double x1, double y1, double x2, double y2, double& xp, double& yp)
{//return greshkata
	//geodetic orientation coordinates
	double nReturn = 0.0;
	double AB, Dab, AP, BP;
	double xa, ya, xb, yb, ba, bb;
	Obratna_zadacha(x1, y1, x2, y2, Dab, AB);
	if (d1 > d2)
	{
		ba = acos((pow(d1, 2) + pow(Dab, 2) - pow(d2, 2)) / (2 * d1 * Dab));
		AP = AB + ba;
		if (AP > 2 * PI) AP = AP - 2 * PI;
		Prava_zadacha(x1, y1, d1, AP, xp, yp);
	}
	else
	{
		bb = acos((pow(d2, 2) + pow(Dab, 2) - pow(d1, 2)) / (2 * d2 * Dab));
		BP = AB + PI - bb;
		if (BP > 2 * PI) BP = BP - 2 * PI;
		Prava_zadacha(x2, y2, d2, BP, xp, yp);
	}

	double Dpa, Dpb, PA, PB, b3;
	double mda = 3.0;	//greshka w opredeljane na daljinata
	double mdb = 3.0;	//greshka w opredeljane na daljinata
	Obratna_zadacha(xp, yp, x1, y1, Dpa, PA);
	Obratna_zadacha(xp, yp, x2, y2, Dpb, PB);
	b3 = fabs(PA - PB);
	nReturn = sqrt(pow(mda, 2) + pow(mdb, 2)) / sin(b3);

	return nReturn;
}

long Obratna_Zasechka_Snelius(double b1, double b2, double xa, double ya, double xb, double yb, double xc, double yc, double& xp, double& yp)
{
	//geodetic orientation coordinates
	//Alpha = in radians 
	double nReturn = 0;
	double BA, BC, Dba, Dbc;

	Obratna_zadacha(xb, yb, xa, ya, Dba, BA);
	Obratna_zadacha(xb, yb, xc, yc, Dbc, BC);
	double K1, K2;
	K1 = Dba / sin(b1);
	K2 = Dbc / sin(b2);
	double Sigma = b1 + b2 + (BA - BC);
	double ctg = -(K2 * cos(Sigma) + K1) / (K2 * sin(Sigma));
	double ff = atan(1 / ctg);
	double AP = BA + PI + ff;
	if (AP > 2 * PI) AP = AP - 2 * PI;
	double Dap = K1 * sin(b1 + ff);
	if ((b1 + b2 + (BA - BC) - PI) < gtor(1, CF_CODE_SECS)) nReturn = 10;
	xp = xa + Dap * cos(AP);
	yp = ya + Dap * sin(AP);

	return nReturn;
}

double Obratna_Zasechka_2(double p, double d1, double d2, double xa, double ya, double xb, double yb, double& xp, double& yp)
{
	//geodetic orientation coordinates
	//p in radians 
	double nReturn = 0;
	double Dab, AB, AP, BP;
	double a, b;

	Obratna_zadacha(xa, ya, xb, yb, Dab, AB);
	if (d1 < d2)
	{
		a = asin((d1 / Dab) * sin(p));
		AP = AB + a;
		if (AP > (2 * PI)) AP = AP - 2 * PI;
		Prava_zadacha(xa, ya, d1, AP, xp, yp);
	}
	else
	{
		b = asin((d2 / Dab) * sin(p));
		BP = AB + PI - (PI - b - p);
		if (BP > (2 * PI)) BP = BP - 2 * PI;
		Prava_zadacha(xb, yb, d2, BP, xp, yp);
	}

	double Dpa, Dpb, PA, PB, b3;
	double mda = 3.0;	//greshka w opredeljane na daljinata
	double mdb = 3.0;	//greshka w opredeljane na daljinata
	Obratna_zadacha(xp, yp, xa, ya, Dpa, PA);
	Obratna_zadacha(xp, yp, xb, yb, Dpb, PB);
	b3 = fabs(PA - PB);
	nReturn = sqrt(pow(mda, 2) + pow(mdb, 2)) / sin(b3);

	return nReturn;
}

double Calc_Data_For_Target(double Sc, double Lc, double Vc, double xa, double ya, double ha, double xop, double yop, double hop,
                            double& xp, double& yp, double& hp, double& Dopc, double& Lopc, double& dhopc)
{
    //geodetic orientation coordinates
    //angles in radians

    //Input data
    //Sc – distance to target;
    //Lc – angle of direction to target;
    //Vc – vertical angle to target
    //xa, ya, ha - our coordinates
    //xop, yop, hop - coordinates of artilery position

    //Output data
    //xp, yp, hp - coordinates of target
    //Dopc – distance from Artilery position to target;
    //Lopc – angle of direction from Artilery position to target;
    //dhopc - deviation in height from Artilery position in artilery units (hilqdni)

    double nReturn = 0;

    Prava_zadacha(xa, ya, Sc, Lc, xp, yp);
    hp = ha + Sc * sin(Vc);
    Obratna_zadacha(xop, yop, xp, yp, Dopc, Lopc);
    dhopc = (hp - hop) / (Dopc / 1000);

    return nReturn;
}

double Calc_Data_For_Razriv(double Sr, double Lr, double Vr, double xa, double ya, double ha, double xop, double yop, double hop,
    double& xp, double& yp, double& hp, double& dDopr, double& dLopr, double& ddhopr)
{
    //geodetic orientation coordinates
    //angles in radians

    //Input data
    //Sr – distance to razriv;
    //Lr – angle of direction to razriv;
    //Vr – vertical angle to razriv
    //xa, ya, ha - our coordinates
    //xop, yop, hop - coordinates of artilery position
    //dDopr – distance from Artilery position to target;
    //dLopr – angle of direction from Artilery position to target;
    //ddhopc - deviation in height from Artilery position in artilery units (hilqdni)

    //Output data
    //xp, yp, hp - coordinates of razriv
    //dDopr – deviation of distance from target to razriv;
    //dLopr – deviation of angle of direction from target to razriv;
    //ddhopc - deviation in height from target  to razriv in artilery units (hilqdni)

    double nReturn = 0;
    double Dopc = dDopr, Lopc = dLopr;

    Prava_zadacha(xa, ya, Sr, Lr, xp, yp);
    hp = ha + Sr * sin(Vr);
    Obratna_zadacha(xop, yop, xp, yp, dDopr, dLopr);
    ddhopr = ddhopr - (hp - hop) / (dDopr / 1000);
    dDopr = Dopc - dDopr;
    dLopr = Lopc - dLopr;

    return nReturn;
}
