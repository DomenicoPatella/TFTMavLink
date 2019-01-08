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
	  uint16_t   battery_voltage;            // 1000 = 1V
	  int16_t    battery_current;            //  10 = 1A
	  int8_t     battery_remaining;          // Remaining battery energy: (0%: 0, 100%: 100), -1: autopilot estimate the remaining battery
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


	  // MAVLINK_MSG_ID_SCALED_PRESSURE
	  uint16_t   temperature;

	  // MAVLINK_MSG_ID_NAV_CONTROLLER_OUTPUT
	  uint16_t   wp_dist ;                // meters

	  // MAVLINK_MSG_ID_STATUSTEXT
	  uint16_t   ap_status_severity;
	  mavlink_statustext_t status_text;
	  uint16_t heartbeat_count;


	};
	 MavlinkTelemetry gathered_telemetry;

	struct stream{
		 uint16_t START_SYS_STATUS,START_ATTITUDE,START_VFR,START_BATT,START_RC ;

	 };

	stream stream_flag;

	unsigned long msg_timer;
	MavlinkProcessor();
	const MavlinkTelemetry& getGatheredTelemetry() const;
	const unsigned long& getLastHeartbeat() const;
	unsigned long& getLastComTime();

	void receiveTelemetry();
	bool isConnected();
private:
	const int START = 1;



	const int MSG_RATE = 10; //Hz

	//const uint8_t average_sample_count = 10;

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
