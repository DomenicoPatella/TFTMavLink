/*
 * Resource.h
 *
 *  Created on: 23 dic 2018
 *      Author: dpatella
 */

#ifndef MYLIB_RESOURCE_H_
#define MYLIB_RESOURCE_H_

#include <avr/pgmspace.h>

#define PIDEG 57.29577


//////////////////////////////////////////////////////////
//  String tables LOGO Page
const char string_logo0[] PROGMEM = "OSD TFT V2.2";
const char string_logo1[] PROGMEM = "Inspirated by:";
const char string_logo2[] PROGMEM = "FrSkyTelemtry";
const char string_logo3[] PROGMEM = "Mavlink";
const char string_logo4[] PROGMEM = "Author:";
const char string_logo5[] PROGMEM = "Domenico Patella";
const char string_logo6[] PROGMEM = "G.T.E Druento";


const char* const string_logo[] PROGMEM = {
		string_logo0,
		string_logo1,
		string_logo2,
		string_logo3,
		string_logo4,
		string_logo5,
		string_logo6

};
////////////////////////////////////////////////////////
///

//////////////////////////////////////////////////////////
//  String tables SYS Page
const char string_sys0[] PROGMEM = "SYSTEM STATUS";
const char string_sys1[] PROGMEM = "CONNECTED";
const char string_sys2[] PROGMEM = "DISCONNECTED";
const char string_sys3[] PROGMEM = "Mode:";
const char string_sys4[] PROGMEM = "ARMED";
const char string_sys5[] PROGMEM = "DISARMED";
const char string_sys6[] PROGMEM = "GPS Status";
const char string_sys7[] PROGMEM = "GPS Sat";
const char string_sys8[] PROGMEM = "GPS HDOP";
const char string_sys9[] PROGMEM = "RSSI [%]";
const char string_sys10[] PROGMEM = "Battery [V]";

const char* const string_sys[] PROGMEM = {
		string_sys0,
		string_sys1,
		string_sys2,
		string_sys3,
		string_sys4,
		string_sys5,
		string_sys6,
		string_sys7,
		string_sys8,
		string_sys9,
		string_sys10
};
////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
//  String tables HUD Page

const char string_hud0[] PROGMEM = "OSD HUD ";
const char string_hud1[] PROGMEM = "Heading";
const char string_hud2[] PROGMEM = "Groundspeed";
const char string_hud3[] PROGMEM = "Alt";
const char string_hud4[] PROGMEM = "Climb";
const char string_hud5[] PROGMEM = "Throttle";


const char* const string_hud[] PROGMEM = {
		string_hud0,
		string_hud1,
		string_hud2,
		string_hud3,
		string_hud4,
		string_hud5

};
////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
//  String tables ATTITUDE Page

const char string_att0[] PROGMEM = "OSD ATTITUDE ";
const char string_att1[] PROGMEM = "Roll";
const char string_att2[] PROGMEM = "Pitch";
const char string_att3[] PROGMEM = "Yaw";
const char string_att4[] PROGMEM = "Rollspeed";
const char string_att5[] PROGMEM = "Pitchspeed";
const char string_att6[] PROGMEM = "Yawspeed";


const char* const string_att[] PROGMEM = {
		string_att0,
		string_att1,
		string_att2,
		string_att3,
		string_att4,
		string_att5,
		string_att6


};
////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
//  String tables RC Page
const char string_rc0[] PROGMEM = "RC CHANNEL";
const char string_rc1[] PROGMEM = "CH1";
const char string_rc2[] PROGMEM = "CH2";
const char string_rc3[] PROGMEM = "CH3";
const char string_rc4[] PROGMEM = "CH4";
const char string_rc5[] PROGMEM = "CH5";
const char string_rc6[] PROGMEM = "CH6";
const char string_rc7[] PROGMEM = "CH7";
const char string_rc8[] PROGMEM = "CH8";
const char string_rc9[] PROGMEM = "RSSI:[%]";



const char* const string_rc[] PROGMEM = {
		string_rc0,
		string_rc1,
		string_rc2,
		string_rc3,
		string_rc4,
		string_rc5,
		string_rc6,
		string_rc7,
		string_rc8,
		string_rc9,

};
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
//  String tables BAT Page
const char string_batt0[] PROGMEM = "BATTERY";
const char string_batt1[] PROGMEM = "Voltage[V]";
const char string_batt2[] PROGMEM = "Cell1[V]";
const char string_batt3[] PROGMEM = "Cell2[V]";
const char string_batt4[] PROGMEM = "Cell3[V]";
const char string_batt5[] PROGMEM = "Cell4[V]";



const char* const string_batt[] PROGMEM = {
		string_batt0,
		string_batt1,
		string_batt2,
		string_batt3,
		string_batt4,
		string_batt5,


};
//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
//  String tables Telem Page
const char string_telem0[] PROGMEM = "TELEMETRY";



const char* const string_telem[] PROGMEM = {
		string_telem0,

};
//////////////////////////////////////////////////////////





const int iconConnection [][16] PROGMEM = {
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 14, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 14, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 14, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 11, 0, 13, 14, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 11, 0, 13, 14, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 11, 0, 13, 14, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 7, 8, 0, 10, 11, 0, 13, 14, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 7, 8, 0, 10, 11, 0, 13, 14, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 7, 8, 0, 10, 11, 0, 13, 14, 0 },
			{ 0, 0, 0, 0, 4, 5, 0, 7, 8, 0, 10, 11, 0, 13, 14, 0 },
			{ 0, 0, 0, 0, 4, 5, 0, 7, 8, 0, 10, 11, 0, 13, 14, 0 },
			{ 0, 0, 0, 0, 4, 5, 0, 7, 8, 0, 10, 11, 0, 13, 14, 0 },
			{ 0, 0, 0, 0, 4, 5, 0, 7, 8, 0, 10, 11, 0, 13, 14, 0 },
			{ 0, 1, 2, 0, 4, 5, 0, 7, 8, 0, 10, 11, 0, 13, 14, 0 },
			{ 0, 1, 2, 0, 4, 5, 0, 7, 8, 0, 10, 11, 0, 13, 14, 0 },
			{ 0, 1, 2, 0, 4, 5, 0, 7, 8, 0, 10, 11, 0, 13, 14, 0 },
            };

const int iconDiscconnection [][16] PROGMEM = {
		{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	15},
		{0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	14,	0},
		{0,	0,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	13,	0,	0},
		{0,	0,	0,	3,	0,	0,	0,	0,	0,	0,	0,	0,	12,	0,	0,	0},
		{0,	0,	0,	0,	4,	0,	0,	0,	0,	0,	0,	11,	0,	0,	0,	0},
		{0,	0,	0,	0,	0,	5,	0,	0,	0,	0,	10,	0,	0,	0,	0,	0},
		{0,	0,	0,	0,	0,	0,	6,	0,	0,	9,	0,	0,	0,	0,	0,	0},
		{0,	0,	0,	0,	0,	0,	0,	7,	8,	0,	0,	0,	0,	0,	0,	0},
		{0,	0,	0,	0,	0,	0,	0,	7,	8,	0,	0,	0,	0,	0,	0,	0},
		{0,	0,	0,	0,	0,	0,	6,	0,	0,	9,	0,	0,	0,	13,	14,	0},
		{0,	0,	0,	0,	0,	5,	0,	0,	0,	0,	10,	11,	0,	13,	14,	0},
		{0,	0,	0,	0,	4,	0,	0,	7,	8,	0,	10,	11,	0,	13,	14,	0},
		{0,	0,	0,	3,	0,	0,	0,	7,	8,	0,	10,	11,	12,	13,	14,	0},
		{0,	0,	2,	0,	4,	5,	0,	7,	8,	0,	10,	11,	0,	13,	14,	0},
		{0,	1,	2,	0,	4,	5,	0,	7,	8,	0,	10,	11,	0,	13,	14,	0},
		{0,	1,	2,	0,	4,	5,	0,	7,	8,	0,	10,	11,	0,	13,	14,	15},
		};


const int iconGps [][16] PROGMEM={
		{0,0,	0,	0,	0,	6,	0,	0,	0,	0,	0,	0,	0,	0,	0,},
		{0,	0,	0,	0,	5,	0,	7,	0,	0,	0,	0,	0,	0,	0,	0,},
		{0,	0,	0,	4,	0,	0,	0,	8,	0,	0,	0,	0,	0,	0,	0,},
		{0,	0,	3,	0,	0,	0,	0,	0,	9,	10,	11,	0,	0,	0,	0,},
		{0,	0,	0,	4,	0,	0,	0,	0,	9,	10,	11,	0,	0,	0,	0,},
		{0,	0,	0,	0,	5,	0,	0,	8,	9,	10,	11,	0,	0,	0,	0,},
		{0,	0,	0,	0,	0,	6,	7,	8,	9,	0,	0,	12,	0,	0,	0,},
		{0,	0,	3,	0,	0,	6,	7,	8,	0,	0,	0,	0,	13,	0,	0,},
		{0,	2,	0,	0,	0,	6,	7,	8,	0,	0,	0,	0,	0,	14,	0,},
		{0,	2,	0,	4,	0,	0,	0,	0,	9,	0,	0,	0,	13,	0,	0,},
		{0,	2,	0,	0,	5,	0,	0,	0,	0,	10,	0,	12,	0,	0,	0,},
		{0,	0,	3,	0,	0,	0,	7,	0,	0,	0,	11,	0,	0,	0,	0,},
		{0,	0,	0,	4,	0,	0,	7,	0,	0,	0,	0,	0,	0,	0,	0,},
		{0,	0,	0,	0,	5,	6,	0,	0,	0,	0,	0,	0,	0,	0,	0,},
		{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,},
		{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,},
};


#endif /* FRSKYTELEMETRYMAVLINK_MYLIB_RESOURCE_H_ */
