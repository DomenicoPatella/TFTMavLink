/*
 * TFT.cpp
 *
 *  Created on: 18 dic 2018
 *      Author: dpatella
 */

#include "TFT.h"

// CONSTRUCTORS ************************************************************
/*!
 @brief  Instantiate Adafruit ST7735 driver with software SPI
 @param  cs    Chip select pin #
 @param  dc    Data/Command pin #
 @param  mosi  SPI MOSI pin #
 @param  sclk  SPI Clock pin #
 @param  rst   Reset pin # (optional, pass -1 if unused)
 */
TFT::TFT(int8_t cs, int8_t dc, int8_t mosi, int8_t sclk, int8_t rst) :
		Adafruit_ST7735(cs, dc, mosi, sclk, rst) {
	color = ST7735_BLACK;
	FONT_WIDTH_SZ1 = 6;
	FONT_HEIGHT_SZ1 = 8;
	changeScreen, actualScreen = 0;
}

/*!
 @brief  Instantiate Adafruit ST7735 driver with default hardware SPI
 @param  cs   Chip select pin #
 @param  dc   Data/Command pin #
 @param  rst  Reset pin # (optional, pass -1 if unused)
 */
TFT::TFT(int8_t cs, int8_t dc, int8_t rst) :
		Adafruit_ST7735(cs, dc, rst) {
	color = ST7735_BLACK;
	FONT_WIDTH_SZ1 = 6;
	FONT_HEIGHT_SZ1 = 8;
	changeScreen, actualScreen = 0;
}

/*!
 @brief  Instantiate Adafruit ST7735 driver with selectable hardware SPI
 @param  spiClass  Pointer to an SPI device to use (e.g. &SPI1)
 @param  cs        Chip select pin #
 @param  dc        Data/Command pin #
 @param  rst       Reset pin # (optional, pass -1 if unused)
 */
TFT::TFT(SPIClass *spiClass, int8_t cs, int8_t dc, int8_t rst) :
		Adafruit_ST7735(spiClass, cs, dc, rst) {
	color = ST7735_BLACK;
	FONT_WIDTH_SZ1 = 6;
	FONT_HEIGHT_SZ1 = 8;
	changeScreen, actualScreen = 0;
}

/**
 *
 * @param text
 * @param forgcolor
 * @param backgcolor
 * @param x
 * @param y
 */
void TFT::drawtext(const char *text, uint16_t forgcolor = ST7735_WHITE,
		uint16_t backgcolor = ST7735_BLACK, int x = 0, int y = 0) {

	setTextColor(forgcolor, backgcolor);
	setCursor(x, y);
	print(text);

}

/**
 *
 * @param text
 * @param forgcolor
 * @param backgcolor
 * @param x
 * @param y
 */
void TFT::drawtext(int16_t text, uint16_t forgcolor = ST7735_WHITE,
		uint16_t backgcolor = ST7735_BLACK, int x = 0, int y = 0) {

	dtostrf(text, 5, 0, buffer);
	setCursor(x, y);
	setTextColor(forgcolor, backgcolor);
	print(buffer);
}

/**
 *
 * @param text
 * @param forgcolor
 * @param backgcolor
 * @param x
 * @param y
 */
void TFT::drawtext(uint16_t text, uint16_t forgcolor = ST7735_WHITE,
		uint16_t backgcolor = ST7735_BLACK, int x = 0, int y = 0) {

	dtostrf(text, 5, 0, buffer);
	setCursor(x, y);
	setTextColor(forgcolor, backgcolor);
	print(buffer);
}

/**
 *
 * @param text
 * @param forgcolor
 * @param backgcolor
 * @param x
 * @param y
 */
void TFT::drawtext(uint8_t text, uint16_t forgcolor = ST7735_WHITE,
		uint16_t backgcolor = ST7735_BLACK, int x = 0, int y = 0) {

	dtostrf(text, 5, 0, buffer);
	setCursor(x, y);
	setTextColor(forgcolor, backgcolor);
	print(buffer);
}

/**
 *
 * @param text
 * @param forgcolor
 * @param backgcolor
 * @param x
 * @param y
 */
void TFT::drawtext(uint32_t text, uint16_t forgcolor = ST7735_WHITE,
		uint16_t backgcolor = ST7735_BLACK, int x = 0, int y = 0) {

	dtostrf(text, 7, 0, buffer);
	setCursor(x, y);
	setTextColor(forgcolor, backgcolor);
	print(buffer);
}

/**
 *
 * @param text
 * @param forgcolor
 * @param backgcolor
 * @param x
 * @param y
 */
void TFT::drawtext(int32_t text, uint16_t forgcolor = ST7735_WHITE,
		uint16_t backgcolor = ST7735_BLACK, int x = 0, int y = 0) {

	dtostrf(text, 5, 2, buffer);
	setCursor(x, y);
	setTextColor(forgcolor, backgcolor);
	print(buffer);
}

/**
 *
 * @param text
 * @param forgcolor
 * @param backgcolor
 * @param w
 * @param p
 * @param x
 * @param y
 */
void TFT::drawtext(float text, uint16_t forgcolor = ST7735_WHITE,
		uint16_t backgcolor = ST7735_BLACK, signed char w = 5, unsigned char p =
				2, int x = 0, int y = 0) {

	dtostrf(text, w, p, buffer);
	setCursor(x, y);
	setTextColor(forgcolor, backgcolor);
	print(buffer);
}

/**
 * @brief Show screen intro
 */
void TFT::pageLogo() {

	setTextSize(1);
	int offsY = 10;
	drawtext(OSD_LOGO(0), ST7735_WHITE, ST7735_BLACK, 30, 0);
	drawtext(OSD_LOGO(1), ST7735_WHITE, ST7735_BLACK, 0, 16);
	drawtext(OSD_LOGO(2), ST7735_GREEN, ST7735_BLACK, 0, getCursorY() + offsY);
	drawtext(OSD_LOGO(3), ST7735_GREEN, ST7735_BLACK, 0, getCursorY() + offsY);
	drawtext(OSD_LOGO(4), ST7735_WHITE, ST7735_BLACK, 0, getCursorY() + offsY);
	drawtext(OSD_LOGO(5), ST7735_GREEN, ST7735_BLACK, 0, getCursorY() + offsY);
	drawtext(OSD_LOGO(6), ST7735_GREEN, ST7735_BLACK, 0, getCursorY() + offsY);
	setTextSize(0);
	actualScreen = PLOGO;

}

/**
 * @brief Show screen system page
 * @param mav_telemetry
 * @param connected
 * @param stream
 */
void TFT::pageSys(const MavlinkProcessor::MavlinkTelemetry& mav_telemetry,
		bool connected, MavlinkProcessor::stream &stream) {

	char text[8];
	int offsY = 12;
	stream.START_SYS_STATUS = 1;
	stream.START_ATTITUDE = 0;
	stream.START_VFR = 0;
	stream.START_BATT = 0;
	stream.START_RC = 0;

	//Title
	drawtext(OSD_SYS(0), ST7735_WHITE, ST7735_BLACK, 0, 0);

	// Icon status mavlink connection
	if (connected) {
		drawIcon(144, 0, iconConnection, ST7735_GREEN);
	} else {
		drawIcon(144, 0, iconDiscconnection, ST7735_RED);
	}

	drawtext(OSD_SYS(3), ST7735_BLUE, ST7735_BLACK, 0, 16);
	if (mav_telemetry.base_mode == MAV_MODE_FLAG_SAFETY_ARMED) {
		drawtext(OSD_SYS(4), ST7735_GREEN, ST7735_BLACK, 36, 16);
	} else {
		drawtext(OSD_SYS(5), ST7735_RED, ST7735_BLACK, 36, 16);
	}

	drawtext(OSD_SYS(6), ST7735_BLUE, ST7735_BLACK, 0, getCursorY() + offsY);
	drawtext(OSD_SYS(7), ST7735_BLUE, ST7735_BLACK, 0, getCursorY() + offsY);
	drawtext(OSD_SYS(8), ST7735_BLUE, ST7735_BLACK, 0, getCursorY() + offsY);
	drawtext(OSD_SYS(10), ST7735_BLUE, ST7735_BLACK, 0, getCursorY() + offsY);

	switch (mav_telemetry.gps_raw.fix_type) {
	case 0:
		strcpy(text, "No Fix");
		break;
	case 1:
		strcpy(text, "No Fix");
		break;
	case 2:
		strcpy(text, "2D Fix");
		break;
	case 3:
		strcpy(text, "3D Fix");
		break;
	}
	drawtext(text, ST7735_WHITE, ST7735_BLACK, 72, 16+offsY);
	drawtext(mav_telemetry.gps_raw.satellites_visible, ST7735_WHITE,
			ST7735_BLACK, 84, getCursorY() + offsY);
	drawtext(mav_telemetry.gps_raw.eph, ST7735_WHITE, ST7735_BLACK, 84,
			getCursorY() + offsY);
	drawtext((float) mav_telemetry.sys_status.voltage_battery / 1000.0,
			ST7735_WHITE, ST7735_BLACK, 2, 3, 84, getCursorY() + offsY);
	drawtext(mav_telemetry.status_text.text, ST7735_ORANGE, ST7735_BLACK, 0,
			getCursorY() + offsY);

	actualScreen = PSYS;

}

/**
 * @brief Show page telemetry HUD
 * @param mav_telemetry
 * @param connected
 * @param stream
 */
void TFT::pageHud(const MavlinkProcessor::MavlinkTelemetry& mav_telemetry,
		bool connected, MavlinkProcessor::stream &stream) {

	int offsY = 12;

	stream.START_SYS_STATUS = 0;
	stream.START_ATTITUDE = 0;
	stream.START_VFR = 1;
	stream.START_BATT = 0;
	stream.START_RC = 0;

	//Title;
	drawtext(OSD_HUD(0), ST7735_WHITE, ST7735_BLACK, 0, 0);
	if (connected) {
		drawIcon(144, 0, iconConnection, ST7735_GREEN);
	} else {
		drawIcon(144, 0, iconDiscconnection, ST7735_RED);
	}

	drawtext(OSD_HUD(1), ST7735_BLUE, ST7735_BLACK, 0, 16);
	drawtext(OSD_HUD(2), ST7735_BLUE, ST7735_BLACK, 0, getCursorY() + offsY);
	drawtext(OSD_HUD(3), ST7735_BLUE, ST7735_BLACK, 0, getCursorY() + offsY);
	drawtext(OSD_HUD(4), ST7735_BLUE, ST7735_BLACK, 0, getCursorY() + offsY);
	drawtext(OSD_HUD(5), ST7735_BLUE, ST7735_BLACK, 0, getCursorY() + offsY);
	drawIcon(0, getCursorY() + 16, iconGps, ST7735_GREEN);
	drawtext(mav_telemetry.gps_raw.satellites_visible, ST7735_WHITE,
			ST7735_BLACK, 20, getCursorY() + 20);

// 158 ms 176 ms con icona
	drawtext(mav_telemetry.hud_raw.heading, ST7735_WHITE, ST7735_BLACK, 72, 16);
	drawtext(mav_telemetry.hud_raw.groundspeed, ST7735_WHITE, ST7735_BLACK, 5,
			2, 72, getCursorY() + offsY);
	drawtext(mav_telemetry.hud_raw.alt, ST7735_WHITE, ST7735_BLACK, 5, 2, 72,
			getCursorY() + offsY);
	drawtext(mav_telemetry.hud_raw.climb, ST7735_WHITE, ST7735_BLACK, 5, 2, 72,
			getCursorY() + offsY);
	drawtext(mav_telemetry.hud_raw.throttle, ST7735_WHITE, ST7735_BLACK, 72,
			getCursorY() + offsY);

	actualScreen = PHUD;

}

void TFT::RawBar(uint16_t channel, int x, int y, int &temp) {
	// Values
	// X,Y  lunghezza , altezza
	int k;
	k = map((int) (channel), 800, 2200, 1, 64);
	if (k > 0 && k != temp) {
		fillRect(x, y, 64, 8, ST7735_BLACK);
		fillRect(x, y, k, 8, ST7735_GREEN);
	}
	temp = k;
}

/**
 * @brief Show page RC Channels
 * @param mav_telemetry
 * @param connected
 */
void TFT::pageRC(const MavlinkProcessor::MavlinkTelemetry& mav_telemetry,
		bool connected, MavlinkProcessor::stream &stream) {

	stream.START_SYS_STATUS = 0;
	stream.START_ATTITUDE = 0;
	stream.START_VFR = 0;
	stream.START_BATT = 0;
	stream.START_RC = 1;

	int offsY = 10;
	//Icon
	drawtext(OSD_RC(0), ST7735_WHITE, ST7735_BLACK, 0, 0);
	if (connected) {
		drawIcon(144, 0, iconConnection, ST7735_GREEN);
	} else {
		drawIcon(144, 0, iconDiscconnection, ST7735_RED);

	}

	drawtext(OSD_RC(1), ST7735_BLUE, ST7735_BLACK, 0, 16);
	drawtext(OSD_RC(2), ST7735_BLUE, ST7735_BLACK, 0, getCursorY() + offsY);
	drawtext(OSD_RC(3), ST7735_BLUE, ST7735_BLACK, 0, getCursorY() + offsY);
	drawtext(OSD_RC(4), ST7735_BLUE, ST7735_BLACK, 0, getCursorY() + offsY);
	drawtext(OSD_RC(5), ST7735_BLUE, ST7735_BLACK, 0, getCursorY() + offsY);
	drawtext(OSD_RC(6), ST7735_BLUE, ST7735_BLACK, 0, getCursorY() + offsY);
	drawtext(OSD_RC(7), ST7735_BLUE, ST7735_BLACK, 0, getCursorY() + offsY);
	drawtext(OSD_RC(8), ST7735_BLUE, ST7735_BLACK, 0, getCursorY() + offsY);
	drawtext(OSD_RC(9), ST7735_BLUE, ST7735_BLACK, 0, getCursorY() + offsY);

// Values

	// X,Y  lunghezza , altezza
	RawBar(mav_telemetry.rc_raw.chan1_raw, 72, 16, lastRawRc[0]);
	RawBar(mav_telemetry.rc_raw.chan2_raw, 72, 26, lastRawRc[1]);
	RawBar(mav_telemetry.rc_raw.chan3_raw, 72, 36, lastRawRc[2]);
	RawBar(mav_telemetry.rc_raw.chan4_raw, 72, 46, lastRawRc[3]);
	RawBar(mav_telemetry.rc_raw.chan5_raw, 72, 56, lastRawRc[4]);
	RawBar(mav_telemetry.rc_raw.chan6_raw, 72, 66, lastRawRc[5]);
	RawBar(mav_telemetry.rc_raw.chan7_raw, 72, 76, lastRawRc[6]);
	RawBar(mav_telemetry.rc_raw.chan8_raw, 72, 86, lastRawRc[7]);

	drawtext(mav_telemetry.rc_raw.rssi * 100 / 255, ST7735_WHITE, ST7735_BLACK,
			72, 96);

	actualScreen = PRC;

}

void TFT::checkVoltageMinMax(float _voltage, uint16_t& color) {
	if (_voltage < 3.5 || _voltage > 4.2) {
		color = ST7735_RED;
	} else {
		color = ST7735_YELLOW;
	}

}

/**
 * @brief Show page battery cell/voltage
 * @param mav_telemetry
 * @param connected
 */
void TFT::pageBatt(const MavlinkProcessor::MavlinkTelemetry& mav_telemetry,
		bool connected, MavlinkProcessor::stream &stream, float _voltage[]) {

	stream.START_SYS_STATUS = 0;
	stream.START_ATTITUDE = 0;
	stream.START_VFR = 0;
	stream.START_BATT = 1;
	stream.START_RC = 0;

	int offsY = 12;
	//Title;
	drawtext(OSD_BATT(0), ST7735_WHITE, ST7735_BLACK, 0, 0);
	if (connected) {
		drawIcon(144, 0, iconConnection, ST7735_GREEN);
	} else {
		drawIcon(144, 0, iconDiscconnection, ST7735_RED);

	}

	drawtext(OSD_BATT(1), ST7735_BLUE, ST7735_BLACK, 0, 16);
	drawtext(OSD_BATT(2), ST7735_BLUE, ST7735_BLACK, 0, getCursorY() + offsY);
	drawtext(OSD_BATT(3), ST7735_BLUE, ST7735_BLACK, 0, getCursorY() + offsY);
	drawtext(OSD_BATT(4), ST7735_BLUE, ST7735_BLACK, 0, getCursorY() + offsY);
	drawtext(OSD_BATT(5), ST7735_BLUE, ST7735_BLACK, 0, getCursorY() + offsY);

	float tot = _voltage[0] + _voltage[1] + _voltage[2] + _voltage[3];
	drawtext(tot, ST7735_GREEN, ST7735_BLACK, 5, 2, 72, 16);
	uint16_t color;

	checkVoltageMinMax(_voltage[0], color);
	drawtext(_voltage[0], color, ST7735_BLACK, 1, 3, 72,
			getCursorY() + offsY);
	checkVoltageMinMax(_voltage[1], color);
	drawtext(_voltage[1], color, ST7735_BLACK, 1, 3, 72,
			getCursorY() + offsY);

	checkVoltageMinMax(_voltage[2], color);
	drawtext(_voltage[2], color, ST7735_BLACK, 1, 3, 72,
			getCursorY() + offsY);

	checkVoltageMinMax(_voltage[3], color);
	drawtext(_voltage[3], color, ST7735_BLACK, 1, 3, 72,
			getCursorY() + offsY);

	actualScreen = PBATT;

}

void TFT::pageAttitue(const MavlinkProcessor::MavlinkTelemetry& mav_telemetry,
		bool connected, MavlinkProcessor::stream &stream) {

	stream.START_SYS_STATUS = 0;
	stream.START_ATTITUDE = 1;
	stream.START_VFR = 0;
	stream.START_BATT = 0;
	stream.START_RC = 0;

	int offsY = 12;
	//Title;
	drawtext(OSD_ATT(0), ST7735_WHITE, ST7735_BLACK, 0, 0);
	if (connected) {
		drawIcon(144, 0, iconConnection, ST7735_GREEN);
	} else {
		drawIcon(144, 0, iconDiscconnection, ST7735_RED);

	}

	// K=57.2957
	drawtext(OSD_ATT(1), ST7735_BLUE, ST7735_BLACK, 0, 16); //roll
	drawtext(OSD_ATT(2), ST7735_BLUE, ST7735_BLACK, 0, getCursorY() + offsY); //pitch
	drawtext(OSD_ATT(3), ST7735_BLUE, ST7735_BLACK, 0, getCursorY() + offsY); //yaw
	drawtext(OSD_ATT(4), ST7735_BLUE, ST7735_BLACK, 0, getCursorY() + offsY); //rollspeed
	drawtext(OSD_ATT(5), ST7735_BLUE, ST7735_BLACK, 0, getCursorY() + offsY); //pitchspeed
	drawtext(OSD_ATT(6), ST7735_BLUE, ST7735_BLACK, 0, getCursorY() + offsY); //yawspeed

	drawtext(mav_telemetry.attitude.roll*PIDEG , ST7735_WHITE, ST7735_BLACK,4,2,72, 16);
	drawtext(mav_telemetry.attitude.pitch*PIDEG, ST7735_WHITE, ST7735_BLACK,4,2,72,getCursorY() + offsY );
	drawtext(mav_telemetry.attitude.yaw*PIDEG, ST7735_WHITE, ST7735_BLACK,4,2,72,getCursorY() + offsY );
	drawtext(mav_telemetry.attitude.rollspeed*PIDEG, ST7735_WHITE, ST7735_BLACK,4,2,72,getCursorY() + offsY );
	drawtext(mav_telemetry.attitude.pitchspeed*PIDEG, ST7735_WHITE, ST7735_BLACK,4,2,72,getCursorY() + offsY );
	drawtext(mav_telemetry.attitude.yawspeed*PIDEG, ST7735_WHITE, ST7735_BLACK,4,2,72,getCursorY() + offsY );



	actualScreen = PATT;

}

/**
 * @brief Draw an icon 16x16
 * @param x
 * @param y
 * @param icon
 * @param fgcolor  Color of icon
 * @param bgcolor  Color of background icon
 * @return Done
 */
bool TFT::drawIcon(int x, int y, const int icon[][16], uint16_t fgcolor,
		uint16_t bgcolor) {

	for (int row = 0; row < 16; row++) {

		for (int col = 0; col < 16; col++) {
			int val = (int*) pgm_read_word(&(icon[row][col]));
			if (val != 0) {
				drawPixel(col + x, row + y, fgcolor);
			} else {
				drawPixel(col + x, row + y, bgcolor);

			}

		}
	}
	return true;

}

/**
 * @brief Write string line with
 *        TFT 160x128
 * @param text   String to write
 */
void TFT::console(const char* text) {

	int col;
	col = getCursorY();
	col = col / FONT_HEIGHT_SZ1;

	if (col <= 18) {
		setCursor(0, col * FONT_HEIGHT_SZ1);
		println(text);
	} else {

		fillScreen(color);
		setCursor(0, 0);

	}

}
