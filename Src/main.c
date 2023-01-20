#include "main.h"
#include "system_init.h"
#include "tv_generation.h"

int main(void) {
	ClockInit();
	USART_init();
	TV_generation_start();
	uint8_t buffer[11];
	uint8_t *ptr;
	for (uint8_t i = 0; i< 11; ++i) {
		buffer[i] = 0;
	}
	uint16_t bench = 0;
	while (1) {
		startTimer();
			//for (int var = 0; var < 10; ++var) {
				drawLine(0, 0, 10, 10);
			//}
		stopTimer();
		bench = TIM2->CNT;
		stopTimer();
	}
}

