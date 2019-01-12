/*
 * TFT.h
 *
 *  Created on: 18 dic 2018
 *      Author: dpatella
 */

#ifndef MYLIB_TFT_H_
#define MYLIB_TFT_H_
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "../MavlinkProcessor.h"
#include "Resource.h"

#define OSD_LOGO(ROW) strcpy_P(buffer, (char*)pgm_read_word(&(string_logo[ROW])))
#define OSD_SYS(ROW) strcpy_P(buffer, (char*)pgm_read_word(&(string_sys[ROW])))
#define OSD_HUD(ROW) strcpy_P(buffer, (char*)pgm_read_word(&(string_hud[ROW])))
#define OSD_RC(ROW) strcpy_P(buffer, (char*)pgm_read_word(&(string_rc[ROW])))
#define OSD_BATT(ROW) strcpy_P(buffer, (char*)pgm_read_word(&(string_batt[ROW])))
#define OSD_ATT(ROW) strcpy_P(buffer, (char*)pgm_read_word(&(string_att[ROW])))




class TFT:public Adafruit_ST7735 {
public:
	TFT();
	TFT(int8_t cs, int8_t dc, int8_t mosi, int8_t sclk,
	      int8_t rst);
	TFT(int8_t cs, int8_t dc, int8_t rst);
	TFT(SPIClass *spiClass, int8_t cs, int8_t dc, int8_t rst);
	uint16_t color;
	uint8_t FONT_WIDTH_SZ1,FONT_HEIGHT_SZ1;
	enum screen {PLOGO=0,PSYS=1,PHUD=2,PRC=3,PBATT=4,PATT=5};
	screen changeScreen,actualScreen;
	bool iconDone,iconDoneGps;
	int lastRawRc[8];



	void drawtext(const char *text, uint16_t forgcolor ,uint16_t backgcolor ,int x ,int y);
	void drawtext(int16_t  text, uint16_t forgcolor ,uint16_t backgcolor ,int x ,int y);
	void drawtext(uint16_t  text, uint16_t forgcolor ,uint16_t backgcolor ,int x ,int y);
	void drawtext(uint8_t text, uint16_t forgcolor ,uint16_t backgcolor ,int x ,int y);
	void drawtext(uint32_t text, uint16_t forgcolor ,uint16_t backgcolor ,int x ,int y);
	void drawtext(int32_t text, uint16_t forgcolor ,uint16_t backgcolor ,int x ,int y);
	void drawtext(float text, uint16_t forgcolor ,uint16_t backgcolor ,signed char w, unsigned char p,int x ,int y);


	void pageLogo();
	void pageSys(const  MavlinkProcessor::MavlinkTelemetry& mav_telemetry, bool connected,MavlinkProcessor::stream &stream);
	void pageHud(const MavlinkProcessor::MavlinkTelemetry& mav_telemetry, bool connected,MavlinkProcessor::stream &stream);
	void pageRC(const MavlinkProcessor::MavlinkTelemetry& mav_telemetry, bool connected,MavlinkProcessor::stream &stream);
	void pageBatt(const MavlinkProcessor::MavlinkTelemetry& mav_telemetry, bool connected,MavlinkProcessor::stream &stream,float _voltage[]);
	void pageAttitue(const MavlinkProcessor::MavlinkTelemetry& mav_telemetry, bool connected,MavlinkProcessor::stream &stream);

	bool drawIcon(int x,int y,const int icon[][16],uint16_t fgcolor,uint16_t bgcolor=ST7735_BLACK);
	void console(const char* text);
private:
    char buffer[20];
	void RawBar(uint16_t channel,int x , int y,int &temp);
	void checkVoltageMinMax(float _voltage, uint16_t& color);
};

#endif /* MYLIB_TFT_H_ */
