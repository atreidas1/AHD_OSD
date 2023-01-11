#include "main.h"
#include "system_init.h"
#include "usart1.h"
#include "mavlink/mavlink.h"
#include "tv_generation.h"

uint8_t str[] = "Received message with ID %d, sequence: %d from component %d of system %d\n\0";
uint8_t str_attitude[] = "Attitude{time_boot_ms: %d, roll: %d, pitch: %d}\n\0";
uint8_t str_heartbeat[] = "Heartbeat{custom_mode: %d, type: %d, autopilot: %d, base_mode: %d, system_status: %d, mavlink_version: %d }\n\0";
uint8_t attitudestr[] = "";
uint8_t serialBuffer[100];
uint16_t counter = 0;
uint16_t spiBuff[3] = {43690, 43690, 43690};
uint16_t spiBuff1[3] = {0, 0, 0};

int main(void) {

	ClockInit();
	USART_init();
	TV_generation_start();
	printStr(osd_buffer, 10, 10, "Hello World", 11);

	mavlink_status_t status;
	mavlink_message_t msg;
	int chan = 0;
	while (1) {
		if (USART_available()) {
			uint8_t byte = USART_readByte();
			if (mavlink_frame_char(chan, byte, &msg, &status)!= MAVLINK_FRAMING_INCOMPLETE) {
				sprintf(serialBuffer, str, msg.msgid, msg.seq, msg.compid, msg.sysid);
				USART_print(serialBuffer);
				switch (msg.msgid) {
					case 30:
					{
						mavlink_attitude_t attitude;
						mavlink_msg_attitude_decode(&msg, &attitude);
						sprintf(serialBuffer, str_attitude, attitude.time_boot_ms, (int)attitude.roll, (int)attitude.pitch);
						USART_print(serialBuffer);
					}
						break;
					case MAVLINK_MSG_ID_HEARTBEAT:
					{
						mavlink_heartbeat_t heartbeat;
						mavlink_msg_heartbeat_decode(&msg, &heartbeat);
						sprintf(serialBuffer, str_heartbeat, heartbeat.custom_mode, heartbeat.type, heartbeat.autopilot, heartbeat.base_mode, heartbeat.system_status, heartbeat.mavlink_version);
						USART_print(serialBuffer);
					}
						break;
					default:
						break;
				}
			}
		}
	}
}

