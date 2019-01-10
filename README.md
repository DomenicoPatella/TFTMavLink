# TFTMavLink
TFT  onboard display for Arducopter/Pixhawk 
Display information with a simplet TFT Display 128x160.  

![diagram](https://github.com/dpsoftware/TFTMavLink/blob/master/doc/images/Diagram.png)

This display is an extension of the onboard display. It's possibile  to show  more information , and could be useful for a more exausistive pre-arm check.

The components required are :
* Display TFT 120x160 
* Arduino Nano 

The mechanis is simple , a Mavlinkprocessor establish a comunication with a FlightController and require the stream messages.
The informations are show on the page for fuctionality. 

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
