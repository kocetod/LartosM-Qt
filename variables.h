#ifndef VARIABLES_H
#define VARIABLES_H

#include <QString>
#include <QDate>
#include <QTime>
#include "TransLib/transform.h"

extern float magnDecl;

//extern double calculatedDirAngle;
//extern double calculatedLat;
//extern double calculatedLong;
//extern bool updateCoordinates;
//extern bool updateDirAngle;

extern CCHARString strTTT;
extern CTransform *g_Transform;

extern int mainWinTiltSpeed;
extern int mainWinPanSpeed;

extern long requestMeasureTime;

//Mainwindow
extern bool day_ir;
extern bool polarity_ir;
extern bool polarity_day;
extern bool pantilt_;
extern bool flgBG_w;
extern QString day_zoom;
extern QString ir_zoom;

//Calibration
extern bool flgBG_c;
extern bool calibrationFinished;

//Entering
extern bool flgBG_e;
extern QString passwordValue;
extern QString passwordCheck;

//Expanded
extern QString _task1a;
extern QString _task1b;
extern QString _task1c;
extern QString _task2;
extern QString _task3;
extern QString txt;
extern QString txt_h;
extern bool _ir;
extern bool _day_ir;
extern bool _pantilt;
extern bool _pantilt_ex;
extern bool flgBtnsVisible;
extern bool flgBtnsVisible_ex;
extern bool _fullExp;
extern bool flgBG_ex;
extern bool isTransformed_A;
extern bool isTransformed_B;
extern bool isTransformed_C;
extern bool isTransformed_D;
extern double alfa_deg;
extern double alfa_mil;
extern double alfa_th;
extern double degToMil;
extern double degToTh;
extern double milToDeg;
extern double thToDeg;

extern QString coordinate_system;
extern QString coordinate_type;
extern QString zone;
extern QString prime_meridian;
extern bool isZone;

extern bool firstTargetMeasured;

extern double distance;
extern QString measuredDistance;
extern bool updateDistance;

//Menu
extern QString _txt;
extern QString m_password;
extern QString password_reset;
extern QString _magnDecl;
extern bool menu_visible;
extern bool flgBG_m;
extern QString txt_m;
extern QString txt_input_m;
extern QString txt_m_md;

//NorthAdjustment
extern bool flgBG_na;
extern float currValue;
extern float minValue;
extern float maxValue;
extern QString plusOperand;
extern QString minusOperand;
extern float degrees;
extern float minutes;
extern float seconds;
extern float constMinutes;
extern float constSeconds;
extern QString txt_na;
extern QString txt_input;


//Tasks
extern int task;
extern bool flgBG_t;
extern char ID_USER[];
extern char ID_PASSWORD[];
extern char ID_IP[];

//MediaBrowser
extern bool flgBG_mb;

//ResultSelection
extern bool flgBG_rs;
extern QString selectedPoint;
extern QString currLat;
extern QString currLong;
extern QString currAlt;
extern double newLat;
extern double newLong;
extern QString newAlt;
extern bool insertPoint;

//CoordSys
extern bool flgBG_cs;
extern bool isWGS;
extern int inputCooSys;
extern int inputCooType;
extern int inputZone;
extern int inputZoneWidth;
extern int inputH;
extern int outputCooSys;
extern int outputCooType;
extern int outputZone;
extern int outputZoneWidth;
extern int outputH;
extern double X_parameter;
extern double Y_parameter;
extern double H_parameter;
extern double H_parameter_input;
extern double HB_parameter_input;
extern double X_parameter_new;
extern double Y_parameter_new;
extern double XA_parameter_input;
extern double YA_parameter_input;
extern double XA_parameter_output;
extern double YA_parameter_output;
extern double XB_parameter_input;
extern double YB_parameter_input;
extern double XB_parameter_output;
extern double YB_parameter_output;
extern double XC_parameter_input;
extern double YC_parameter_input;
extern double XC_parameter_output;
extern double YC_parameter_output;
extern double XD_parameter_input;
extern double YD_parameter_input;
extern double XD_parameter_output;
extern double YD_parameter_output;

//MainWindowHead
extern QString day_zoom_head;
extern QString ir_zoom_head;
extern bool day_ir_head;
extern QString brightness_value_head;
extern bool polarity_day_head;
extern bool polarity_ir_head;

#endif // VARIABLES_H
