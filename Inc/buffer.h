#ifndef BUFFER_H_
#define BUFFER_H_

#include "font.h"
#include "usart1.h"

#define BUFFER_COLUMNS 52
#define BUFFER_LINES 240

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

void printGrafic_8xN(uint8_t x, uint8_t y, uint8_t *symbol, uint8_t height) {
	for (uint8_t i = 0; i < height; i++) {
		osd_buffer[y +i][x] = *(symbol+i);
	}
}

void printGrafic_16xN(uint8_t x, uint8_t y, uint16_t *symbol, uint8_t height) {
	for (uint8_t i = 0; i < height; i++) {
		*(uint16_t*)&osd_buffer[y +i][x] = *(symbol+i);
	}
}

void printGrafic_32xN(uint8_t x, uint8_t y, uint32_t *symbol, uint8_t height) {
	for (uint8_t i = 0; i < height; i++) {
		*(uint32_t*)&osd_buffer[y +i][x] = *(symbol+i);
	}
}


void printStr(uint8_t *buff, uint8_t x, uint8_t y, uint8_t *string, uint8_t size) {
	for (uint8_t i = 0; i < size; i++) {
		printChar(buff, x + i, y, *(string + i) - 32);
	}
}

void setPixel(uint16_t x, uint16_t y) {
	uint8_t bytePos = x >> 3;
}

void drawCircle(int x0, int y0, int radius) {
	int x = 0;
	int y = radius;
	int delta = 1 - 2 * radius;
	int error = 0;
	while(y >= 0) {
		setPixel(x0 + x, y0 + y);
		setPixel(x0 + x, y0 - y);
		setPixel(x0 - x, y0 + y);
		setPixel(x0 - x, y0 - y);
		error = 2 * (delta + y) - 1;
		if(delta < 0 && error <= 0) {
			++x;
			delta += 2 * x + 1;
			continue;
		}
		error = 2 * (delta - x) - 1;
		if(delta > 0 && error > 0) {
			--y;
			delta += 1 - 2 * y;
			continue;
		}
		++x;
		delta += 2 * (x - y);
		--y;
	}
}

void drawLine(int x1, int y1, int x2, int y2) {
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    setPixel(x2, y2);
    while(x1 != x2 || y1 != y2)
   {
        setPixel(x1, y1);
        int error2 = error * 2;
        if(error2 > -deltaY)
        {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX)
        {
            error += deltaX;
            y1 += signY;
        }
    }

}

#endif /* BUFFER_H_ */
