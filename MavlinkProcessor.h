#ifndef MAVLINK_PROCESSOR_H
#define MAVLINK_PROCESSOR_H
#include <GCS_MAVLink.h>


class MavlinkProcessor {
public:
	struct MavlinkTelemetry {

	  //  MAVLINK_MSG_ID_HEARTBEAT
	  uint8_t    base_mode;
	  uint16_t   custom_mode;

	  // Message # 1  MAVLINK_MSG_ID_SYS_STATUS
	  mavlink_sys_status_t sys_status;

	  // MAVLINK_MSG_ID_GPS_RAW_INT
	  //uint8_t    gps_fixtype;                // 0= No GPS, 1 = No Fix, 2 = 2D Fix, 3 = 3D Fix
	  //uint8_t    gps_satellites_visible;     // number of visible satelites
	  //int32_t    gps_latitude;               // 585522540;
	  //int32_t    gps_longitude;              // 162344467;
	  //int32_t    gps_altitude;               // 1000 = 1m
	  //int32_t    gps_speed;                  // in cm/s
	  //uint16_t   gps_hdop;                   // GPS HDOP horizontal dilution of position in cm
	  mavlink_gps_raw_int_t gps_raw;

	  // MAVLINK_MSG_ID_VFR_HUD
	  //float   groundspeed;                // Current ground speed in m/s
	  //uint16_t   heading;                 // Current heading in degrees, in compass units (0..360, 0=north)
	  //uint16_t   throttle;                // Current throttle setting in integer percent, 0 to 100
	  //int32_t    bar_altitude;            // 100 = 1m
	  //float    climb_rate;                // 100= 1m/s
	  mavlink_vfr_hud_t hud_raw;

	  //MAVLINK_MSG_ID_ATTITUDE
	  mavlink_attitude_t attitude;

	  //MAVLINK_MSG_ID_RC_CHANNELS_RAW
	  mavlink_rc_channels_raw_t rc_raw;

	  // MAVLINK_MSG_ID_STATUSTEXT
	  mavlink_statustext_t status_text;

	  // MAVLINK MSG_ID_HWSTATUS
	  mavlink_hwstatus_t hw_status;

	};

	MavlinkTelemetry gathered_telemetry;

	struct stream{
		 uint16_t START_SYS_STATUS,START_ATTITUDE,START_VFR,START_BATT,START_RC ;

	 };

	stream stream_flag;

	unsigned long msg_timer;
	MavlinkProcessor();
	const MavlinkTelemetry& getGatheredTelemetry() const;
	unsigned long& getLastComTime();

	void receiveTelemetry();
	bool isConnected();
private:
	const int START = 1;
	const int MSG_RATE = 10; //Hz

	//MavlinkTelemetry gathered_telemetry;
	uint8_t is_connected;
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];
	mavlink_message_t msg;
	mavlink_status_t status;
	unsigned long msg_count;
	int alive_led_pin;
	unsigned long connection_timer,last_connection;
	unsigned long heartbeat_timer;

	void calculateVoltageAverage(uint16_t value);
	void calculateCurrentAverage(uint16_t value);
	void simula();
	void tryToConnectToAPM();
};
#endif
