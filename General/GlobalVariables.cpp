//#include "stdafx.h"
#include "GlobalVariables.h"
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include "CHARString.h"
//#include <Windows.h>
#include <locale>
#include <string>
#include <sstream>
#include <limits>
#include <iostream>
#include <ios>

//#ifdef LINUX_VER
#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),  (mode)))==NULL
//#endif //LINUX_VER

CCHARString strUnits[CF_NUMBERS];
CCHARString strUnits_en[CF_NUMBERS];

void InitUnits()
{
	strUnits[0].Format("Íåäåôèíèðàí");				//CF_CODE_UNDEFINED
	strUnits[1].Format("ÃÃÃÌÌÑÑ.*");				//CF_CODE_DMS
	strUnits[2].Format("ÃÃÃ.ÌÌÑÑ*");				//CF_CODE_D_MS
	strUnits[3].Format("ÃÃÃ.*");					//CF_CODE_DD
	strUnits[4].Format("ÃÃÃÌÌ.*");					//CF_CODE_DM
	strUnits[5].Format("ÃÃÃ%c ?Ì' ?Ñ''.*", 176);	//CF_CODE_D_M_S
	strUnits[6].Format("ñåêóíäè");					//CF_CODE_SECS
	strUnits[7].Format("ìåòðè");					//CF_CODE_METERS
	strUnits[8].Format("ðàäèàíè");				//CF_CODE_RADIANS
	strUnits_en[0].Format("Undefined");				//CF_CODE_UNDEFINED
	strUnits_en[1].Format("DDDMMSS.*");				//CF_CODE_DMS
	strUnits_en[2].Format("DDD.MMSS*");				//CF_CODE_D_MS
	strUnits_en[3].Format("DDD.*");					//CF_CODE_DD
	strUnits_en[4].Format("DDDMM.*");				//CF_CODE_DM
	strUnits_en[5].Format("DDD%c ?M' ?S''.*", 176);	//CF_CODE_D_M_S
	strUnits_en[6].Format("seconds");				//CF_CODE_SECS
	strUnits_en[7].Format("meters");				//CF_CODE_METERS
	strUnits_en[8].Format("radians");				//CF_CODE_RADIANS
}

bool IsNumber(CCHARString str)
{
	// Postavqme po-obshto ponqtie za chislo.
	// Chislo e vseki string, kojto ima dyljina po-golqma ot 0 i zapochva s cifra.
	// Tova se priema, zashtoto pri konvertirane na stringa kym chislo s nqkoq ot 
	// funkciite atoi, atol, atof, te shte vyrnat chislo kato ignorirat vsichko 
	// sled poslednata namerana v stringa cifra.

	bool bReturn = false;
//	if(str != NULL)
//	{
		size_t nLength = strlen(str);
		if(nLength > 0)
		{
			if(str[(size_t)0] == '+' || str[(size_t)0] == '-')
			{
				if(nLength >= 2)
				{
					if(str[(size_t)1] >= '0' && str[(size_t)1] <= '9') bReturn = true;
				}
			}
			else
			{
				if(str[(size_t)0] >= '0' && str[(size_t)0] <= '9') bReturn = true;
			}
		}
//	}

	return bReturn;
}

bool IsNullXYZValue(double nValue, int nCode)
{
	bool bResult = false;
	if(nValue == NO_DVALUE)
		bResult = true;
	if(nCode == 2 && nValue == 0.0)
		bResult = true;

	return bResult;
}

CCHARString ConvertSystemToText(int system, int Language)
{
	CCHARString strText("");
	switch (system)
	{
	case CS_42_83_CODE:
		if(Language == 0) strText = CS_42_83;
		else strText = CS_42_83_EN;
		break;
	case CS_WGS84_CODE:
		if(Language == 0) strText = CS_WGS84;
		else strText = CS_WGS84_EN;
		break;
	case CS_BGS_CODE:
		if(Language == 0) strText = CS_BGS;
		else strText = CS_BGS_EN;
		break;
	case CS_UNKNOWN_CODE:
		if(Language == 0) strText = CS_UNKNOWN;
		else strText = CS_UNKNOWN_EN;
		break;
	case CS_WGS84_G1762_CODE:
		if (Language == 0) strText = CS_WGS84_G1762;
		else strText = CS_WGS84_G1762_EN;
		break;
	}
	
	return strText;
}

CCHARString ConvertSystemToShortText(int system)
{
	CCHARString strText("");
	switch (system)
	{
	case CS_42_83_CODE:
		strText = SYSTEM_42_83;
		break;
	case CS_WGS84_CODE:
		strText = SYSTEM_WGS84;
		break;
	case CS_BGS_CODE:
		strText = SYSTEM_BGS;
		break;
	case CS_UNKNOWN_CODE:
		strText = SYSTEM_UNKNOWN;
		break;
	case CS_WGS84_G1762_CODE:
		strText = SYSTEM_WGS84_G1762;
		break;
	}
	
	return strText;
}

CCHARString ConvertHemiToText(int nHemi, int Language)
{
	CCHARString strText("");
	switch (nHemi)
	{
	case HEMI_CODE_NORTH: 
		if(Language == 1) strText = HEMI_TEXT_NORTH_E;
		else strText = HEMI_TEXT_NORTH_B;
		break;
	case HEMI_CODE_SOUTH: 
		if(Language == 1) strText = HEMI_TEXT_SOUTH_E;
		else strText = HEMI_TEXT_SOUTH_B;
		break;
	}

	return strText;
}

int ConvertHemiToIndex(CCHARString strHemi)
{
	int nIndex;
	if(strHemi == HEMI_TEXT_NORTH_B  || strHemi == HEMI_TEXT_NORTH_E) nIndex = HEMI_CODE_NORTH;
	else nIndex = HEMI_CODE_SOUTH;
	
	return nIndex;
}

CCHARString ConvertCoordinatesType(int type, int lang)
{
	CCHARString strTemp("");
	if(lang == 1)		//English language
	{
		switch (type)
		{
		case CT_XY_CODE:
			strTemp = CT_XY_EN;
			break;
		case CT_BL_CODE:
			strTemp = CT_BL_EN;
			break;
		case CT_UTM_CODE:
			strTemp = CT_UTM_EN;
			break;
		case CT_XYZ_CODE:
			strTemp = CT_XYZ_EN;
			break;
		case CT_CAD_CODE:
			strTemp = CT_CAD_EN;
			break;
		default:
			strTemp = CT_UNKNOWN_EN;
		}
	}
	else				//Bulgarian language
	{
		switch (type)
		{
		case CT_XY_CODE:
			strTemp = CT_XY;
			break;
		case CT_BL_CODE:
			strTemp = CT_BL;
			break;
		case CT_UTM_CODE:
			strTemp = CT_UTM;
			break;
		case CT_XYZ_CODE:
			strTemp = CT_XYZ;
			break;
		case CT_CAD_CODE:
			strTemp = CT_CAD;
			break;
		default:
			strTemp = CT_UNKNOWN;
		}
	}
	
	return strTemp;
}

int ConvertSystemToIndex(CCHARString system)
{
	int RetValue = CS_UNKNOWN_CODE;
	
	if(system == CS_UNKNOWN_EN || system == CS_UNKNOWN)
		RetValue = CS_UNKNOWN_CODE;
	else if(system == CS_42_83_EN || system == CS_42_83)
		RetValue = CS_42_83_CODE;
	else if(system == CS_WGS84_EN || system == CS_WGS84)
		RetValue = CS_WGS84_CODE;
	else if(system == CS_BGS_EN || system == CS_BGS)
		RetValue = CS_BGS_CODE;
	else if (system == CS_WGS84_G1762_EN || system == CS_WGS84_G1762)
		RetValue = CS_WGS84_G1762_CODE;
	
	return RetValue;
}

int ConvertShortSysTextToIndex(CCHARString system)
{
	int RetValue = -1;
	if(system == SYSTEM_UNKNOWN)	RetValue = CS_UNKNOWN_CODE;
	else if(system == SYSTEM_42_83)	RetValue = CS_42_83_CODE;
	else if(system == SYSTEM_WGS84)	RetValue = CS_WGS84_CODE;
	else if(system == SYSTEM_BGS)	RetValue = CS_BGS_CODE;
	else if (system == SYSTEM_WGS84_G1762)	RetValue = CS_WGS84_G1762_CODE;
	
	return RetValue;
}

int ConvertCoordTypeToCode(CCHARString strCoordType)
{
	int nCode = CT_UNKNOWN_CODE;
	if(strCoordType == CT_XY || strCoordType == CT_XY_EN || strCoordType == "CT_XY_CODE")
		nCode = CT_XY_CODE;
	else if(strCoordType == CT_BL || strCoordType == CT_BL_EN || strCoordType == "CT_BL_CODE") 
		nCode = CT_BL_CODE;
	else if(strCoordType == CT_XYZ || strCoordType == CT_XYZ_EN || strCoordType == "CT_XYZ_CODE") 
		nCode = CT_XYZ_CODE;
	else if(strCoordType == CT_UTM || strCoordType == CT_UTM_EN || strCoordType == "CT_UTM_CODE") 
		nCode = CT_UTM_CODE;
	else if(strCoordType == CT_CAD || strCoordType == CT_CAD_EN || strCoordType == "CT_CAD_CODE")
		nCode = CT_CAD_CODE;

	return nCode;
}


int ConvertFromAngToInt(CCHARString &format)
{
	int result = 0;
	for(int i = 1; i < CF_NUMBERS; i++)
	{
		if(format == strUnits[i] || format == strUnits_en[i])
		{
			result = i;
		}
	}

	return result;
}

CCHARString ConvertFromAngToText(int nFormat, int nLanguage)
{
	CCHARString strResult("");
	if(nLanguage)
	{
		strResult = strUnits_en[nFormat];
	}
	else
	{
		strResult = strUnits[nFormat];
	}
	
	return strResult;
}

int WriteToLog(CCHARString strFileName, CCHARString strText, bool bAppend)
{
	if(strFileName == "") return 1;
	FILE *outfile = NULL;
    fopen_s(&outfile, strFileName.GetCHAR(), bAppend ?"a+t": "wt" );
	if(outfile == NULL) return 5;
	strText = strText + "\n";
	fputs(strText.GetCHAR(), outfile);
				
	fclose(outfile);

	return 0;
}

int ReturnPrecision(CCHARString strValue)
{
	int nReturn = 0;
	int nPos = strValue.Find(".");
	int nPosE = strValue.Find("e");
	if(nPosE < 0) nPosE = strValue.Find("E");
	if(nPos >= 0)
	{
		if(nPosE < 0)
			nReturn = strValue.GetLength() - nPos - 1;
		else
			nReturn = nPosE - nPos - 1;
	}

	return nReturn;
}

double round_1(double chislo)
{
	return chislo + 0.000000000000005;
}

bool StartsWith(CCHARString &strString, CCHARString strStartsWith)
{
	int nLength = strStartsWith.GetLength();
	if (!strString.Left(nLength).CompareNoCase(strStartsWith))
		return true;

	return false;
}

double ConvertTextToDouble(const char* strText)
{
	std::string text(strText);
	std::istringstream stream(text);

	std::locale locale("C");
	stream.imbue(locale);

	double result = 0;
	stream >> result;
	if (stream.fail())
	{
		result = std::numeric_limits<double>::quiet_NaN();
		result = 0;
	}

	return result;
}
