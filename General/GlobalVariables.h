#ifndef GLOBALVARIABLES_H
#define  GLOBALVARIABLES_H
//#ifndef __TRANS_DEFINES_H__
#pragma once

//#include <string.h>
#include "CHARString.h"

#ifdef _MARIANDEBUG_
#define _DEBUGMY
#endif

#define CHR_NUMBER		60
#define ENGBUL_NUMBER	11

//********************************************//
//				TRANS ErrorCodes              //
//********************************************//
#define TRANS_NO_ERROR						0
#define TRANS_TRANSFORM_ERROR				1
#define TRANS_COORDINATE_SYSTEM_ERROR		2
#define TRANS_INVALID_TILE_ERROR			3
#define TRANS_PARAMETERS_NOT_DEFINED_ERROR	4
#define TRANS_NOVALID70_ERROR				5
#define TRANS_NOVALID30_ERROR				6
#define TRANS_NOLICENSE_ERROR				7
#define TRANS_TOWIDTH_ERROR					8
#define TRANS_DEFAULTGEOIDMODEL_ERROR		9
#define TRANS_HEIGHTISNOTTRANSFORMED_ERROR	10
#define TRANS_OUTOFTRANSFORMATIONAREA_ERROR	11
#define TRANS_NOGEOIDMODEL_ERROR			12
#define TRANS_PARAMETERSNOTREGISTERED_ERROR	13
#define TRANS_SOURCECOORDINATES_INVALID		14
#define TRANS_TARGETCOORDINATES_INVALID		15
#define TRANS_NOMVARIABLE_NULL				16
#define TRANS_GEOIDPARAMETERSFILE_NOTFOUND	17


#define TRANS_IN_X_ERROR					101
#define TRANS_IN_Y_ERROR					102
#define TRANS_OUT_X_ERROR					103
#define TRANS_OUT_Y_ERROR					104
#define TRANS_CS70_ZONE_ERROR				105
#define TRANS_WGS84_ZONE_ERROR				106
#define TRANS_PATH_ERROR					107
#define TRANS_SOFIJSKA_ERROR				108
#define TRANS_NOT_INITIALIZED				109
#define TRANS_MGRS_ERROR					110
#define TRANS_NOT_AVAILABLE					111
#define TRANS_UNKNOWN_ERROR					112
#define TRANS_GRIDFILE_ERROR				113
#define TRANS_NOT_CREATED					114
#define TRANS_INPUTFILE_ERROR				115
#define TRANS_GEOID_HEIGHTTYPE_UNDEFINED    116
#define TRANS_ONE_AND_SAME					199

//********************************************//
//				  System Codes                //
//********************************************//
#define CS_UNKNOWN_CODE				-999
#define CS_42_83_CODE				4
#define CS_WGS84_CODE				6
#define CS_BGS_CODE					8
#define CS_WGS84_G1762_CODE			13

#define NUMBER_BULGARIAN_SYSTEMS	4

#define SYSTEM_UNKNOWN				"UNKNOWN"
#define SYSTEM_42_83				"1942/83"
#define SYSTEM_WGS84				"ETRS89"
#define SYSTEM_BGS					"BGS2005"
#define SYSTEM_WGS84_G1762			"WGS84_G1762"

//********************************************//
// coordinate systems text bulgarian		  //
//********************************************//
#define CS_UNKNOWN					"Координатна система неопределена"
#define CS_42_83					"Координатна система 1942/83"
#define CS_WGS84					"Координатна система ETRS89, епоха 1989.0"
#define CS_BGS						"Координатна система БГС2005"
#define CS_WGS84_G1762				"Координатна система WGS84, реализация G1762"
//********************************************//
// coordinate systems text english
//********************************************//
#define CS_UNKNOWN_EN				"Coordinate system unknown"
#define CS_42_83_EN					"Coordinate system 1942/83"
#define CS_WGS84_EN					"Coordinate system ETRS89, epoh 1989.0"
#define CS_BGS_EN					"Coordinate system BGS2005"
#define CS_WGS84_G1762_EN			"Coordinate system WGS84, version G1762"

//********************************************//
//			Coordinate Types Codes            //
//********************************************//
#define CT_UNKNOWN_CODE				-999
#define CT_XY_CODE					0
#define CT_BL_CODE					1
#define CT_XYZ_CODE					2
#define CT_UTM_CODE					3
#define CT_CAD_CODE					4

//********************************************//
// Coordinate types text bulgarian/english    //
//********************************************//
#define CT_XY						"xy (правоъгълни)"
#define CT_BL						"BL (географски)"
#define CT_XYZ						"XYZ (геоцентрични)"
#define CT_UTM						"UTM"
#define CT_UNKNOWN					"Неопределен"
#define CT_CAD						"Кадастрални"

#define CT_XY_EN					"xy (plane)"
#define CT_BL_EN					"BL (geographic)"
#define CT_XYZ_EN					"XYZ (geocentric)"
#define CT_UTM_EN					"UTM"
#define CT_UNKNOWN_EN				"Undefined"
#define CT_CAD_EN					"Cadastral"

//********************************************//
//			    Zone width Codes              //
//********************************************//
#define ZW_UNKNOWN_CODE				-999
#define ZW_3DEGREE_CODE				0
#define ZW_6DEGREE_CODE				1
#define ZW_3DEGREE					"3 градуса"
#define ZW_6DEGREE					"6 градуса"
#define ZW_3DEGREE_EN				"3 degrees"
#define ZW_6DEGREE_EN				"6 degrees"
#define ZW_UNKNOWN					"неопределена"
#define ZW_UNKNOWN_EN				"unknown"

//********************************************//
//			    Height system Codes          //
//********************************************//
//#define HS_DEFAULT_CODE				-1
#define HS_UNKNOWN_CODE				-999
#define HS_BALTIC_CODE				0
#define HS_WGS_CODE					1
#define HS_EVRF2000_CODE			2
#define HS_EVRF2007_CODE			3
#define HS_ORTHOMETRIC_CODE			4

#define NUMBER_HEIGHT_SYSTEMS		6

//********************************************//
// geoid codes 
//********************************************//
#define GRD_HEIGHTTYPE_UNDEFINED				0
#define GRD_HEIGHTTYPE_WGS_BALTIC				1	//H_WGS - H_BALTIC
#define GRD_HEIGHTTYPE_WGS_EVRS2000				2	//H_WGS - H_EVRS200
#define GRD_HEIGHTTYPE_WGS_EVRS2007				3	//H_WGS - H_EVRS207

//********************************************//
// elipsoids code 
//********************************************//
#define EL_CODE_HEYFORD			1
#define EL_CODE_KARS			2 
#define EL_CODE_BESS			3
#define EL_CODE_WGS84			4
#define EL_CODE_GRS80			5
#define EL_CODE_OTHER			9


//********************************************//
// spheroid a, f
//********************************************//
#define SHEROIDHEYF_A	6378388
#define SHEROIDHEYF_F	297
#define SHEROIDKRAS_A	6378245
#define SHEROIDKRAS_F	298.3
#define SHEROIDBESS_A	6377397.155
#define SHEROIDBESS_F	299.1528128
#define SHEROIDWGS_A	6378137
#define SHEROIDWGS_F	298.257223563
#define SHEROIDETRS_A	6378137
#define SHEROIDETRS_F	298.257222101

//********************************************//
//			    Undefined values              //
//********************************************//
#define VALUE_H_NOT_USED			-9999
#define VALUE_NOT_USED				-999
#define NO_VALUE					-999
#define NO_IVALUE					-9999
#define NO_DVALUE					-9999.0
#define GRD_NO_VALUE				-9999
#define NO_SVALUE					" - "
#define SVALUE_NOT_USED				"-----"
#define LONGVALUE_MISSED			-99999
#define NO_DVALUE_MISSED			-9999.0

//********************************************//
//          Date/Time Format string codes     //
//********************************************//
#define DTF_UNDEFINED			"UNDEFINED"
#define DTF_DDMMYYYY			"DDMMYYYY"
#define DTF_MMDDYYYY			"MMDDYYYY"
#define DTF_YYYYMMDD			"YYYYMMDD"
#define DTF_YYYYDDMM			"YYYYDDMM"

#define DTF_CODE_UNDEFINED			0
#define DTF_CODE_DDMMYYYY			1
#define DTF_CODE_MMDDYYYY			2
#define DTF_CODE_YYYYMMDD			3
#define DTF_CODE_YYYYDDMM			4

#define CF_NUMBERS					9	//Number of defined units
#define CF_CODE_UNDEFINED			0	//Undefined
#define CF_CODE_DMS					1	//Degree_Minutes_Seconds.
#define CF_CODE_D_MS				2	//Degree.Minutes_Seconds
#define CF_CODE_DD					3	//Decimal degree
#define CF_CODE_DM					4	//Degree_minutes.
#define CF_CODE_D_M_S				5	//Degree_ *minutes_ *seconds.
#define CF_CODE_SECS				6	//seconds
#define CF_CODE_METERS				7	//meters
#define CF_CODE_RADIANS				8	//radians
#define CF_CODE_MILIMETERS			10	//milimeters
#define CF_CODE_SECS1000			11	//seconds * 1000

#define HEMI_CODE_NORTH			0
#define HEMI_CODE_SOUTH			1

#define HEMI_CHAR_NORTH			'N'
#define HEMI_CHAR_SOUTH			'S'

#define HEMI_TEXT_NORTH_B		"Северно"
#define HEMI_TEXT_SOUTH_B		"Южно"

#define HEMI_TEXT_NORTH_E		"Northern"
#define HEMI_TEXT_SOUTH_E		"Southern"


#define AUTO_E "Auto"
#define AUTO_B "Автоматично"
#define ZONE_AUTO		-999



#define PI 3.1415926535897932384626433832795

extern CCHARString strUnits[CF_NUMBERS];
extern CCHARString strUnits_en[CF_NUMBERS];

void InitUnits();
bool IsNumber(CCHARString str);
bool IsNullXYZValue(double nValue, int nCode);
CCHARString ConvertSystemToText(int system, int Language);
CCHARString ConvertSystemToShortText(int system);
CCHARString ConvertCoordinatesType(int type, int lang);
int ConvertSystemToIndex(CCHARString system);
int ConvertCoordTypeToCode(CCHARString strCoordType);
int ConvertShortSysTextToIndex(CCHARString system);
int ConvertHemiToIndex(CCHARString strHemi);
int ConvertFromAngToInt(CCHARString &format);
CCHARString ConvertFromAngToText(int nFormat, int nLanguage);
int WriteToLog(CCHARString strFileName, CCHARString strText, bool bAppend = true);
int ReturnPrecision(CCHARString strValue);
double round_1(double chislo);

extern char dos[CHR_NUMBER];
extern char dos1[CHR_NUMBER];
extern char win[CHR_NUMBER];
extern char eng[ENGBUL_NUMBER];
extern char bul[ENGBUL_NUMBER];

bool StartsWith(CCHARString &strString, CCHARString strStartsWith);
double ConvertTextToDouble(const char* strText);
#endif	//GLOBALVARIABLES_H
