# TFTMavLink
TFT  onboard display for Arducopter/Pixhawk 
Display information with a simplet TFT Display 128x160.  

![diagram](https://github.com/dpsoftware/TFTMavLink/blob/master/doc/images/Diagram.png)

This display is an extension of the onboard display. It's possibile  to show  more information , and could be useful for a more exausistive pre-arm check.

The components required are :
* Display TFT 120x160 
* Arduino Nano 

# How does it work ?
The mechanis is simple , a Mavlinkprocessor establish a comunication with a FlightController and require the stream messages.
```c++
void MavlinkProcessor::tryToConnectToAPM() {
	uint16_t len = 0;
	last_connection = (millis() - heartbeat_timer);
	if (millis() - heartbeat_timer > 1500UL) {
		heartbeat_timer = millis();
		if (true) {    // Start requesting data streams from MavLink
			digitalWrite(alive_led_pin, HIGH);
			//SYS STATUS -GPS
			mavlink_msg_request_data_stream_pack(0xFF, 0xBE, &msg, 1, 1,
					MAV_DATA_STREAM_EXTENDED_STATUS, 10,
					stream_flag.START_SYS_STATUS);
			len = mavlink_msg_to_send_buffer(buf, &msg);
			MavLinkSerial.write(buf, len);
			delay(10);

```
Once the connection is established , the processore read the messages and store the informations on the appropriate structure

```c++
 // MAVLINK_MSG_ID_VFR_HUD
	  //float   groundspeed;                // Current ground speed in m/s
	  //uint16_t   heading;                    // Current heading in degrees, in compass units (0..360, 0=north)
	  //uint16_t   throttle;                   // Current throttle setting in integer percent, 0 to 100
	  //int32_t    bar_altitude;               // 100 = 1m
	  //float    climb_rate;              // 100= 1m/s
	  mavlink_vfr_hud_t hud_raw;

	  //MAVLINK_MSG_ID_ATTITUDE
	  mavlink_attitude_t attitude;

	  // MAVLINK_MSG_ID_MISSION_CURRENT
	  uint16_t   mission_current_seq ;

	  //MAVLINK_MSG_ID_RC_CHANNELS_RAW
mavlink_rc_channels_raw_t rc_raw;
```

The class TFT  implement the Adafruit library ,and provide  with set of methods to write the data on the display
```c++
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
	drawtext(text, ST7735_WHITE, ST7735_BLACK, 72, 24);
	drawtext(mav_telemetry.gps_raw.satellites_visible, ST7735_WHITE,
			ST7735_BLACK, 84, getCursorY() + offsY);
	drawtext(mav_telemetry.gps_raw.eph, ST7735_WHITE, ST7735_BLACK, 84,
			getCursorY() + offsY);
	drawtext((float) mav_telemetry.sys_status.voltage_battery / 1000.0,
			ST7735_WHITE, ST7735_BLACK, 2, 3, 84, getCursorY() + offsY);
	drawtext(mav_telemetry.status_text.text, ST7735_ORANGE, ST7735_BLACK, 0,
			getCursorY() + offsY);

actualScreen = PSYS;
```
The informations are showed on the page for fuctionality. 

SYSTEM STATUS | HUD | RC CHANNEL |  ATTITUDE
------------ | ------| ----|
Armed/Disarmed |Heading | CH1....CH8 bargraph |Roll 
GPS Status (Fix,no Fix ,ec..) |Groundspeed |  RSSI |Pitch
GPS Sat/HDOP |Alt |Yaw
GPS number  |Climb |Rollspeed
Message text | Throttle |Pitchspeed 
             |          | Yawspeed
	     
  <img src="https://github.com/dpsoftware/TFTMavLink/blob/master/doc/images/IMG_2.jpg" width="320" height="427">
  <img src="https://github.com/dpsoftware/TFTMavLink/blob/master/doc/images/IMG_3.jpg" width="320" height="427">
  <img src="https://github.com/dpsoftware/TFTMavLink/blob/master/doc/images/IMG_4.jpg" width="320" height="427">
  <img src="https://github.com/dpsoftware/TFTMavLink/blob/master/doc/images/IMG_5.jpg" width="320" height="427">
  <img src="https://github.com/dpsoftware/TFTMavLink/blob/master/doc/images/IMG_6.jpg" width="320" height="427">


![Watch the video](https://github.com/dpsoftware/TFTMavLink/blob/master/doc/images/VID_20190109_001611.mp4?raw=true)
