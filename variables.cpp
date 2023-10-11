#include "variables.h"

float magnDecl;

//double calculatedDirAngle;
//double calculatedLat;
//double calculatedLong;
//bool updateCoordinates = false;
//bool updateDirAngle = false;

CCHARString strTTT = "/home/pi/egm96.grd";
CTransform* g_Transform = new CTransform;

int mainWinTiltSpeed = 0;
int mainWinPanSpeed = 0;

long requestMeasureTime;

//Mainwindow
bool day_ir = false;
bool polarity_ir = false;
bool polarity_day = false;
bool pantilt_ = false;
bool flgBG_w;
QString day_zoom = "1X";
QString ir_zoom = "1X";

//Calibration
bool flgBG_c;
bool calibrationFinished;

//Entering
bool flgBG_e;
QString passwordValue;
QString passwordCheck;

//Expanded
QString _task1a;
QString _task1b;
QString _task1c;
QString _task2;
QString _task3;
QString txt;
QString txt_h = 0;
bool _ir = false;
bool _day_ir = false;
bool _pantilt = false;
bool _pantilt_ex = false;
bool flgBtnsVisible = false;
bool flgBtnsVisible_ex = false;
bool _fullExp = false;
bool flgBG_ex;
bool isTransformed_A = false;
bool isTransformed_B = false;
bool isTransformed_C = false;
bool isTransformed_D = false;

QString coordinate_system = "wgs";
QString coordinate_type = "utm";
QString zone = "35";
QString prime_meridian = "27";
bool isZone = true;

double alfa_deg;
double alfa_mil;
double alfa_th;
double degToMil = 17.77777778;
double degToTh = 16.66666667;
double milToDeg = 0.05625;
double thToDeg = 0.06;

bool firstTargetMeasured = false;

double distance;
QString measuredDistance;
bool updateDistance = false;

//Menu
QString _txt;
QString m_password;
QString password_reset;
QString _magnDecl;
bool menu_visible = false;
bool flgBG_m;
QString txt_m = "f";
QString txt_input_m;
QString txt_m_md;

//NorthAdjustment
bool flgBG_na;
float currValue;
float minValue = -10.0;
float maxValue = 10.0;
QString plusOperand = "+";
QString minusOperand = "-";
float degrees;
float minutes;
float seconds;
float constMinutes = 0.01666667;
float constSeconds = 0.000277778;
QString txt_na = "f";
QString txt_input;

//Tasks
int task = 1;
bool flgBG_t;

char ID_USER[] = "oeg";
char ID_PASSWORD[] = "Opticoelectron";
char ID_IP[] = "10.10.5.25";

//MediaBrowser
bool flgBG_mb;

//ResultSelection
bool flgBG_rs;
QString selectedPoint;
QString currLat;
QString currLong;
QString currAlt;
double newLat;
double newLong;
QString newAlt;
bool insertPoint = false;

//CoordSys
bool flgBG_cs;
bool isWGS = true;
int inputCooSys;
int inputCooType;
int inputZone;
int inputZoneWidth;
int inputH;
int outputCooSys;
int outputCooType;
int outputZone;
int outputZoneWidth;
int outputH;
double X_parameter;
double Y_parameter;
double H_parameter;
double H_parameter_input;
double HB_parameter_input;
double X_parameter_new;
double Y_parameter_new;
double XA_parameter_input;
double YA_parameter_input;
double XA_parameter_output;
double YA_parameter_output;
double XB_parameter_input;
double YB_parameter_input;
double XB_parameter_output;
double YB_parameter_output;
double XC_parameter_input;
double YC_parameter_input;
double XC_parameter_output;
double YC_parameter_output;
double XD_parameter_input;
double YD_parameter_input;
double XD_parameter_output;
double YD_parameter_output;

//MainWindowHead
QString day_zoom_head = "1X";
QString ir_zoom_head = "1X";
bool day_ir_head = false;
QString brightness_value_head = "70";
bool polarity_day_head = false;
bool polarity_ir_head = false;
