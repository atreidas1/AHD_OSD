#include "main.h"
#include "system_init.h"
#include "tv_generation.h"

int main(void) {

	ClockInit();
	USART_init();
	TV_generation_start();

	while (1) {
	}
}

