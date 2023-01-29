#ifndef GRAPHIC_CLIMB_H_
#define GRAPHIC_CLIMB_H_

#define POSITION_X 41
#define POSITION_Y 112
#define MAX_PIXEL 150
#define PRES_HOLDER 0x40
#define START_Y_POS 60
#define END_Y_POS 165
#define ZERO_CLIMB_POS_Y 112
#define MAX_VALUE 51

#include "buffer.h"

void GRAPHIC_CLIMB(int16_t climb){


	osd_buffer[ZERO_CLIMB_POS_Y][POSITION_X] = PRES_HOLDER;
	int16_t endFillY = ZERO_CLIMB_POS_Y - climb;

	for (uint8_t i = START_Y_POS; i < END_Y_POS; i++) {

		if (climb > 0) {
			if (i > endFillY && i <= ZERO_CLIMB_POS_Y) {

				osd_buffer[i][POSITION_X] = PRES_HOLDER;
			} else {
				osd_buffer[i][POSITION_X] = 0x00;
			}
		}

		else {
			if (i >= ZERO_CLIMB_POS_Y && i <= endFillY) {

				osd_buffer[i][POSITION_X] = PRES_HOLDER;
			} else {
				osd_buffer[i][POSITION_X] = 0x00;
			}
		}
	}
}


#endif /* GRAPHIC_CLIMB_H_ */
