/*
 The code has contributions from
 Rolf Blomgren http://diydrones.com/profile/RolfBlomgren; http://diydrones.com/forum/topics/amp-to-frsky-x8r-sport-converter?xg_source=activity&id=705844%3ATopic%3A1539556;
 Pawelky http://www.rcgroups.com/forums/member.php?u=393936; http://www.rcgroups.com/forums/showthread.php?t=2245978
 Paulo Neves  https://www.airborneprojects.com/services

 */

#include "MavlinkProcessor.h"
#include "Arduino.h"
#define MavLinkSerial Serial

/**
 * @brief
 */
MavlinkProcessor::MavlinkProcessor() :
		gathered_telemetry { }, is_connected { false }, buf { 0 }, msg { 0 }, status {
				0 }, msg_count { 0 }, alive_led_pin { 13 }, connection_timer { 0 }, heartbeat_timer {
				millis() } {
	MavLinkSerial.begin(115200);

}

/**
 * @brief
 * @return gathered_telemetry
 */
const MavlinkProcessor::MavlinkTelemetry& MavlinkProcessor::getGatheredTelemetry() const {
	return gathered_telemetry;
}

/**
 * @brief
 * @return heartbeat_timer
 */
const unsigned long& MavlinkProcessor::getLastHeartbeat() const {

	return last_connection;
}

/**
 * @brief
 * @return heartbeat_timer
 */
unsigned long& MavlinkProcessor::getLastComTime() {

	msg_timer = millis() - connection_timer;

	return msg_timer;
}

/**
 *
 */
void MavlinkProcessor::receiveTelemetry() {

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
				connection_timer = millis();
				break;
			case MAVLINK_MSG_ID_SYS_STATUS:   //
				is_connected = true;
				connection_timer = millis();

				gathered_telemetry.battery_voltage =
						mavlink_msg_sys_status_get_voltage_battery(&msg) / 10; //
				gathered_telemetry.battery_current =
						mavlink_msg_sys_status_get_current_battery(&msg) / 10; //
				gathered_telemetry.battery_remaining =
						mavlink_msg_sys_status_get_battery_remaining(&msg);
				mavlink_msg_sys_status_decode(&msg,
						&gathered_telemetry.sys_status);

				break;
			case MAVLINK_MSG_ID_GPS_RAW_INT:   // 24
				is_connected = true;
				connection_timer = millis();
				mavlink_msg_gps_raw_int_decode(&msg,
						&gathered_telemetry.gps_raw);
				if (gathered_telemetry.gps_raw.fix_type != 3) {

					gathered_telemetry.gps_raw.eph = 9999;
					gathered_telemetry.gps_raw.lat = 0L;
					gathered_telemetry.gps_raw.lon = 0L;
					gathered_telemetry.gps_raw.alt = 0L;
					gathered_telemetry.gps_raw.vel = 0L;
				}
				break;
			case MAVLINK_MSG_ID_VFR_HUD:   //  74
				is_connected = true;
				connection_timer = millis();
				mavlink_msg_vfr_hud_decode(&msg, &gathered_telemetry.hud_raw);
				break;
			case MAVLINK_MSG_ID_ATTITUDE:
				is_connected = true;
				connection_timer = millis();
				mavlink_msg_attitude_decode(&msg, &gathered_telemetry.attitude);
				break;

			case MAVLINK_MSG_ID_STATUSTEXT:
				is_connected = true;
				connection_timer = millis();
				mavlink_msg_statustext_decode(&msg,
						&gathered_telemetry.status_text);
				break;
			case MAVLINK_MSG_ID_RC_CHANNELS_RAW:
				is_connected = true;

				connection_timer = millis();
				mavlink_msg_rc_channels_raw_decode(&msg,
						&gathered_telemetry.rc_raw);
				break;
			default:
				break;
			}
		}
	}
}

/**
 *
 */
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

			//ATTITUDE
			mavlink_msg_request_data_stream_pack(0xFF, 0xBE, &msg, 1, 1,
					MAV_DATA_STREAM_EXTRA1, 10, stream_flag.START_ATTITUDE);
			len = mavlink_msg_to_send_buffer(buf, &msg);
			MavLinkSerial.write(buf, len);
			delay(10);

			//VFR_HUD
			mavlink_msg_request_data_stream_pack(0xFF, 0xBE, &msg, 1, 1,
					MAV_DATA_STREAM_EXTRA2, 10, stream_flag.START_VFR);
			len = mavlink_msg_to_send_buffer(buf, &msg);
			MavLinkSerial.write(buf, len);
			delay(10);

			//BATTERY,EFK,ECC
			mavlink_msg_request_data_stream_pack(0xFF, 0xBE, &msg, 1, 1,
					MAV_DATA_STREAM_EXTRA3, 10, stream_flag.START_BATT);
			len = mavlink_msg_to_send_buffer(buf, &msg);
			MavLinkSerial.write(buf, len);

			//RC
			mavlink_msg_request_data_stream_pack(0xFF, 0xBE, &msg, 1, 1,
					MAV_DATA_STREAM_RC_CHANNELS, 9, stream_flag.START_RC);
			len = mavlink_msg_to_send_buffer(buf, &msg);
			MavLinkSerial.write(buf, len);

			digitalWrite(alive_led_pin, LOW);
		}
	}

	if ((millis() - connection_timer) > 5000UL) {
		is_connected = false;
		msg_count = 0;

	}
}

/**
 *
 * @return
 */
bool MavlinkProcessor::isConnected() {
	return is_connected;
}

void MavlinkProcessor::simula() {

	/*
	 gathered_telemetry.hud_raw.heading = rand() / 100;
	 gathered_telemetry.hud_raw.groundspeed = rand() * 0.01;
	 gathered_telemetry.hud_raw.groundspeed = 123.01231243;

	 gathered_telemetry.hud_raw.throttle = rand();
	 gathered_telemetry.hud_raw.alt = rand() * 0.01;
	 gathered_telemetry.hud_raw.climb = rand() * 0.01;
	 is_connected = true;
	 gathered_telemetry.gps_raw.satellites_visible = rand_r(10UL);
	 */
}
