#include "SoftwareSerial/SoftwareSerial.h"
#include <GCS_MAVLink.h>
#include "Arduino.h"
#include "MavlinkProcessor.h"
#include "MyLib/TFT.h"
#include "MyLib/Resource.h"
#include "Mylib/Battery.h"

#define TFT_CS        10
#define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC         8

// For 1.44" and 1.8" TFT with ST7735 (including HalloWing) use:
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

TFT tft = TFT(TFT_CS, TFT_DC, TFT_RST);

int buttonState = LOW;           // the current reading from the input pin
int lastButtonState = -1;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 100; // the debounce time; increase if the output flickers


int button(int reading) {

	//sample the state of the button - is it pressed or not?
	buttonState = digitalRead(3);

	//filter out any noise by setting a time buffer
	if ((millis() - lastDebounceTime) > debounceDelay) {

		//
		if ((buttonState == HIGH) && (lastButtonState < 0)) {
			lastButtonState = -lastButtonState;
			lastDebounceTime = millis(); //set the current time
			return buttonState;

		}
		if ((buttonState == LOW) && (lastButtonState > 0)) {

			lastButtonState = -lastButtonState;
			lastDebounceTime = millis(); //set the current time
			if (tft.actualScreen < tft.PATT) {
				tft.changeScreen = tft.changeScreen + 1;

			} else {
				tft.changeScreen = tft.PSYS;

			}

			return buttonState;

		}

	}

}



void setup() {

	uint8_t led_pin = 6;

	Serial.begin(57600);

	pinMode(13, OUTPUT);
	pinMode(3, INPUT_PULLUP);
	pinMode(led_pin, OUTPUT);
	analogReference(INTERNAL);


	bool connected;

	MavlinkProcessor mavlink_processor;
	Battery lipo(A0);


	tft.changeScreen = tft.PATT;
	tft.initR(INITR_BLACKTAB);		// Init ST7735S chip, black tab
	tft.fillScreen(ST77XX_BLACK);
	tft.setRotation(1);
	tft.setTextWrap(true);
	tft.pageLogo();

	delay(3000);

	while (1) {
		uint32_t start = micros() / 1000;;
		unsigned long last;

		int btn = button(digitalRead(3));

		mavlink_processor.receiveTelemetry();
		connected = mavlink_processor.isConnected();

		switch (tft.changeScreen) {

		case tft.PSYS:
			if (tft.actualScreen != tft.PSYS) {
				tft.fillScreen(ST77XX_BLACK);
				tft.actualScreen = tft.PSYS;
			}
			break;

		case tft.PHUD:
			if (tft.actualScreen != tft.PHUD) {
				tft.fillScreen(ST77XX_BLACK);
				tft.actualScreen = tft.PHUD;
			}
			break;

		case tft.PRC:
			if (tft.actualScreen != tft.PRC) {
				tft.fillScreen(ST77XX_BLACK);
				tft.actualScreen = tft.PRC;
				for (int var = 0; var < 8; var++) {
					tft.lastRawRc[var]=0;
				}
			}
			break;

		case tft.PBATT:
			if (tft.actualScreen != tft.PBATT) {
				tft.fillScreen(ST77XX_BLACK);
				tft.actualScreen = tft.PBATT;
			}
			break;
		case tft.PATT:
			if (tft.actualScreen != tft.PATT) {
				tft.fillScreen(ST77XX_BLACK);
				tft.actualScreen = tft.PATT;
			}
			break;


		default:
			if (tft.actualScreen != tft.PLOGO) {
				tft.fillScreen(ST77XX_BLACK);
				tft.actualScreen = tft.PLOGO;
			}
		}

		if (tft.actualScreen == tft.PSYS)
			tft.pageSys(mavlink_processor.getGatheredTelemetry(), connected,mavlink_processor.stream_flag);
		if (tft.actualScreen == tft.PHUD)
			tft.pageHud(mavlink_processor.getGatheredTelemetry(), connected,mavlink_processor.stream_flag);
		if (tft.actualScreen == tft.PRC)
			tft.pageRC(mavlink_processor.getGatheredTelemetry(), connected,mavlink_processor.stream_flag);
		if (tft.actualScreen == tft.PBATT){
			lipo.getVoltage();
			tft.pageBatt(mavlink_processor.getGatheredTelemetry(), connected,mavlink_processor.stream_flag,
					lipo.voltage);
		}
		if (tft.actualScreen == tft.PATT){

			tft.pageAttitue(mavlink_processor.getGatheredTelemetry(), connected,mavlink_processor.stream_flag);
		}




		if (serialEventRun)
			serialEventRun();

		int y =112;
		char text[10];

		tft.setCursor(0, y );
		uint32_t end = micros() / 1000 - start;
		//tft.drawtext("Loop [ms]:", ST7735_CYAN,ST7735_BLACK ,0, y);
		//tft.drawtext(end, ST7735_GREEN,ST7735_BLACK ,tft.getCursorX(), tft.getCursorY());
		//tft.drawtext("MavlinkTime [s] :", ST7735_CYAN,ST7735_BLACK ,0, tft.getCursorY()+8);
		//tft.drawtext((float)mavlink_processor.getLastComTime()/1000.0, ST7735_GREEN,ST7735_BLACK ,1,1,tft.getCursorX(), tft.getCursorY());


	}

}

void loop() {

}
