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
tryToConnectToAPM();
	//simula();
	while (MavLinkSerial.available()) {
		uint8_t c = MavLinkSerial.read();
		if (mavlink_parse_char(MAVLINK_COMM_0, c, &msg, &status)) {
			switch (msg.msgid) {

			case MAVLINK_MSG_ID_HEARTBEAT:  // 0
				gathered_telemetry.base_mode =
						mavlink_msg_heartbeat_get_base_mode(&msg);
				gathered_telemetry.custom_mode =
						mavlink_msg_heartbeat_get_custom_mode(&msg);
			.....

				gathered_telemetry.battery_voltage =
						mavlink_msg_sys_status_get_voltage_battery(&msg) / 10; //
				gathered_telemetry.battery_current =
						mavlink_msg_sys_status_get_current_battery(&msg) / 10; //
				gathered_telemetry.battery_remaining =
						mavlink_msg_sys_status_get_battery_remaining(&msg);
				mavlink_msg_sys_status_decode(&msg,
&gathered_telemetry.sys_status);
```

The class TFT  implement the Adafruit library ,and provide  with set of methods to write the data on the display

The informations are showed on the page for fuctionality. 

SYSTEM STATUS | HUD
------------ | -------------
Armed/Disarmed |Heading
GPS Status (Fix,no Fix ,ec..) |Groundspeed
GPS Sat/HDOP |Alt
GPS number  |Climb
Message text | Throttle 

 <img src="https://github.com/dpsoftware/TFTMavLink/blob/master/doc/images/IMG_2.jpg" width="320" height="427">



  <img src="https://github.com/dpsoftware/TFTMavLink/blob/master/doc/images/IMG_3.jpg" width="320" height="427">
  <img src="https://github.com/dpsoftware/TFTMavLink/blob/master/doc/images/IMG_4.jpg" width="320" height="427">
  <img src="https://github.com/dpsoftware/TFTMavLink/blob/master/doc/images/IMG_5.jpg" width="320" height="427">
  <img src="https://github.com/dpsoftware/TFTMavLink/blob/master/doc/images/IMG_6.jpg" width="320" height="427">


![Watch the video](https://github.com/dpsoftware/TFTMavLink/blob/master/doc/images/VID_20190109_001611.mp4?raw=true)
