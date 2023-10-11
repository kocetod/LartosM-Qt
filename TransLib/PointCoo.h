#ifndef __POINTCOO_H__
#define __POINTCOO_H__
#pragma once

#include "General/GlobalVariables.h"

class CStationMeasure
{
public:
	CStationMeasure();
	~CStationMeasure();
	void SetMeasure(int nIndex, double b, double d, double v);
	double GetPosoka(int nIndex, int nType);
	double GetPointsAngle(int left, int right, int nType);
	double GetDistance(int nIndex);
	double GetVertical(int nIndex, int nType);
	int AnalyzeOrder(int nP);
public:
	double m_bA, m_bB, m_bC, m_bD, m_bE, m_bF;
	double m_dA, m_dB, m_dC, m_dD, m_dE, m_dF;
	double m_vA, m_vB, m_vC, m_vD, m_vE, m_vF;
	int m_nHorANgleType, m_nVertANgleType;
};

class CPoint
{
public:
	CPoint();
	~CPoint();
	void SetPoint(double x, double y, double z, int m_nSys = CS_BGS_CODE, int m_nType = CT_UTM_CODE,
		int m_nWidth = ZW_6DEGREE_CODE, double m_dblZone = 35, int m_nHSys = HS_EVRF2007_CODE);
	double GetX(bool bReverse = false);
	double GetY(bool bReverse = false);
	double GetZ(bool bReverse = false);
	bool GetXYZ(double* x, double* y, double* z, bool bReverse);
	bool IsSet();

public:
	double m_dblX_L_E;
	double m_dblY_B_N;
	double m_dblZ_H;
	int m_nSys;
	int m_nType;
	int m_nWidth;
	double m_dblZone;
	int m_nHSys;
	bool m_bSet;
	int nPointStatus;	//1-Known; 2-Calculated
};

class CPointCoo
{
public:
	CPointCoo();
	~CPointCoo();
	long GetTransformed(CPoint* pPoint, double* X, double* Y, double* Z, int nSys = CS_BGS_CODE, int nType = CT_UTM_CODE, int nWidth = ZW_6DEGREE_CODE,
		double dblZone = 35, int nHSys = HS_EVRF2007_CODE);
	long GetGeocentricH0(CPoint* pPoint, double* X, double* Y, double* Z, double* Hori);
	long GetBLH(CPoint* pPoint, double* B, double* L, double* H);
	long GetCooByType(CPoint* pPoint, int nType, int nWidth, double dblZone, double* x, double* y, double* h);
	long CalcPosition(int nP1, int nP2, int nP3, int nP4);
	void SetMeasure(int nIndex, double b, double d, double v);
	CPoint* GetPointByIndex(int nIndex);
	int AnalyzeOrder(int& nP1, int& nP2, int& nP3, int& nP4);

public:
	void* objTrans;
	CPoint PointA;
	CPoint PointB;
	CPoint PointC;
	CPoint PointD;
	CPoint PointE;
	CPoint PointF;
	CPoint PointP;
	CStationMeasure Station;
	int m_tsyst, m_ttype, m_twidth, m_tzone, m_theight;
	double b0, b1, b2, b3, b4;
	double d0, d1, d2, d3, d4, d5;
	double v0, v1, v2, v3, v4, v5;
	int m_nIndex;
};

long Prava_zadacha(double XA, double YA, double R, double Alfa, double& XP, double& YP);
long Obratna_zadacha(double XA, double YA, double XB, double YB, double& R, double& Alfa);
double Error_Prava_Zasechka(double b1, double b2, double xa, double ya, double xb, double yb, double xp, double yp);
long Prava_Zasechka(double b1, double b2, double xa, double ya, double xb, double yb, double& xp, double& yp);
long Prava_Zasechka_direc(double AP, double BP, double xa, double ya, double xb, double yb, double& xp, double& yp);
double Obratna_Zasechka(double b1, double b2, double xa, double ya, double xb, double yb, double xc, double yc, double& xp, double& yp);
double Obratna_Zasechka_ctg(double b1, double b2, double b3, double xa, double ya, double xb, double yb, double xc, double yc,
	double xd, double yd, double& xp, double& yp);
double Linejna_Zasechka(double d1, double d2, double x1, double y1, double x2, double y2, double& xp, double& yp);
long Obratna_Zasechka_Snelius(double b1, double b2, double xa, double ya, double xb, double yb, double xc, double yc, double& xp, double& yp);
double Obratna_Zasechka_2(double p, double d1, double d2, double xa, double ya, double xb, double yb, double& xp, double& yp);
double Calc_Data_For_Target(double Sc, double Lc, double Vc, double xa, double ya, double ha, double xop, double yop, double hop, double& xp, double& yp, double& hp, double& Dopc, double& Lopc, double& dhopc);
double Calc_Data_For_Razriv(double Sr, double Lr, double Vr, double xa, double ya, double ha, double xop, double yop, double hop, double& xp, double& yp, double& hp, double& dDopr, double& dLopr, double& ddhopr);

#endif //__POINTCOO_H__
