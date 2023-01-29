#ifndef GRAPHIC_SPEED_H_
#define GRAPHIC_SPEED_H_

#include "buffer.h"

#define PRESCALER_SPEED 15
#define MAX_SPEED 151
#define POSITION_X 9
#define POSITION_Y 162
#define PRES_HOLDER 0x02
#define MAX_PIXEL 150
#define START_Y_POS 60
#define END_Y_POS 163

void GRAPH_GROUND_SPEED(uint16_t speed) {

	uint16_t startFillPos = END_Y_POS - speed * 10 / PRESCALER_SPEED;

	for (uint8_t i = START_Y_POS; i < END_Y_POS; i++) {

		if (i >= startFillPos) {
			osd_buffer[i][POSITION_X] = PRES_HOLDER;
		} else {
			osd_buffer[i][POSITION_X] = 0x00;
		}

	}
}


#endif /* GRAPHIC_SPEED_H_ */
