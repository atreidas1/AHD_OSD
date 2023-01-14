#include "main.h"
#include "system_init.h"
#include "usart1.h"
#include "mavlink/mavlink.h"
#include "tv_generation.h"

uint8_t str[] = "ID %d, seq: %d comp %d sys %d\n\0";
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

	while (1) {
		if (attitudeNeedRead) {
			sprintf(serialBuffer, str_attitude, attitude.time_boot_ms, attitude.roll*10, attitude.pitch*10);
			USART_print(serialBuffer);
			attitudeNeedRead = 0;
		}
	}
}

