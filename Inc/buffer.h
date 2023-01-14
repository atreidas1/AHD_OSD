#ifndef BUFFER_H_
#define BUFFER_H_

#include "font.h"
#include "usart1.h"

#define BUFFER_COLUMNS 40
#define BUFFER_LINES 100
#define BUFFER_SIZE BUFFER_LINES*BUFFER_COLUMNS
#define BUFFER_WIDTH_IN_BITS 8*BUFFER_COLUMNS

uint8_t osd_buffer[BUFFER_LINES][BUFFER_COLUMNS];

uint8_t debug_buffer[BUFFER_COLUMNS*8 + 2];

void clearScreen(uint8_t *buff) {
	for(uint16_t i = 0; i < BUFFER_SIZE; i++ ) {
		*(buff + i) = 0;
	}
}

void printBuffer(uint8_t *buff) {
	for(uint16_t i = 0; i < BUFFER_LINES; i++) {
		for (uint16_t j = 0; j < BUFFER_COLUMNS; j++) {
			uint8_t val = *(buff + i*BUFFER_COLUMNS + j);
			for(int8_t k = 0; k <= 7; k++) {
				debug_buffer[j*8 + k] = (val>>k) & 1 ? '#' : ' ';
			}
		}
		debug_buffer[BUFFER_COLUMNS*8] = '\n';
		debug_buffer[BUFFER_COLUMNS*8 +1] = '\0';
		USART_print(debug_buffer);
	}
}

void printChar(uint8_t *buff, uint8_t x, uint8_t y, uint8_t symbol) {
	uint16_t startIndex = symbol*15;
	for (uint8_t i = 0; i < CHAR_HEIGHT; i++) {
		*(buff + (y*CHAR_HEIGHT+i)*BUFFER_COLUMNS + x) = Fixedsys8x15[startIndex+i];
	}
}

void printStr(uint8_t *buff, uint8_t x, uint8_t y, uint8_t *string, uint8_t size) {
	for (uint8_t i = 0; i < size; i++) {
		printChar(buff, x + i, y, *(string + i) - 32);
	}
}

#endif /* BUFFER_H_ */
