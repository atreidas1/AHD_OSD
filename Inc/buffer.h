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

static inline void printChar(uint8_t x, uint8_t y, uint8_t symbol) {
		uint16_t startIndex = symbol*CHAR_HEIGHT;
		osd_buffer[y][x] = Fixedsys8x15[startIndex];
		osd_buffer[y+1][x] = Fixedsys8x15[startIndex+1];
		osd_buffer[y+2][x] = Fixedsys8x15[startIndex+2];
		osd_buffer[y+3][x] = Fixedsys8x15[startIndex+3];
		osd_buffer[y+4][x] = Fixedsys8x15[startIndex+4];
		osd_buffer[y+5][x] = Fixedsys8x15[startIndex+5];
		osd_buffer[y+6][x] = Fixedsys8x15[startIndex+6];
		osd_buffer[y+7][x] = Fixedsys8x15[startIndex+7];
		osd_buffer[y+8][x] = Fixedsys8x15[startIndex+8];
}

void printGrafic_8xN(uint16_t x, uint16_t y, uint8_t *symbol, uint8_t height) {
	for (uint8_t i = 0; i < height; i++) {
		osd_buffer[y +i][x] = *(symbol+i);
	}
}

void printGrafic_16xN(uint16_t x, uint16_t y, uint16_t *symbol, uint8_t height) {
	for (uint8_t i = 0; i < height; i++) {
		*(uint16_t*)&osd_buffer[y +i][x] = *(symbol+i);
	}
}

void printGrafic_32xN(uint16_t x, uint16_t y, uint32_t *symbol, uint8_t height) {
	for (uint8_t i = 0; i < height; i++) {
		*(uint32_t*)&osd_buffer[y +i][x] = *(symbol+i);
	}
}

static inline void printString(uint8_t x, uint8_t y, char *string) {
	int i = 0;
	while(*string != 0) {
		printChar(x + i, y, *string);
		string++;
		i++;
	}
}

static inline void printStringWithPlaceholder(uint32_t x, uint32_t y, char *string, uint32_t placeHolderSize) {
	uint32_t i = 0;
	uint32_t startIndex = 0;
	while (*string != 0) {
		startIndex = (*string) * CHAR_HEIGHT;
		osd_buffer[y][x] = Fixedsys8x15[startIndex];
		osd_buffer[y + 1][x] = Fixedsys8x15[startIndex + 1];
		osd_buffer[y + 2][x] = Fixedsys8x15[startIndex + 2];
		osd_buffer[y + 3][x] = Fixedsys8x15[startIndex + 3];
		osd_buffer[y + 4][x] = Fixedsys8x15[startIndex + 4];
		osd_buffer[y + 5][x] = Fixedsys8x15[startIndex + 5];
		osd_buffer[y + 6][x] = Fixedsys8x15[startIndex + 6];
		osd_buffer[y + 7][x] = Fixedsys8x15[startIndex + 7];
		osd_buffer[y + 8][x] = Fixedsys8x15[startIndex + 8];
		x++;
		string++;
		i++;
	}
	while (i < placeHolderSize) {
		osd_buffer[y][x] = 0;
		osd_buffer[y + 1][x] = 0;
		osd_buffer[y + 2][x] = 0;
		osd_buffer[y + 3][x] = 0;
		osd_buffer[y + 4][x] = 0;
		osd_buffer[y + 5][x] = 0;
		osd_buffer[y + 6][x] = 0;
		osd_buffer[y + 7][x] = 0;
		osd_buffer[y + 8][x] = 0;
		i++;
		x++;
	}
}

static inline void setPixel(uint32_t x, uint32_t y) {
	osd_buffer[y][x>>3] |= 1 << (x & 0x07);
}

static inline void clearPixel(uint32_t x, uint32_t y) {
	osd_buffer[y][x>>3] &= ~(1 << (x & 0x07));
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

void drawLine(int_fast16_t x1, int_fast16_t y1, int_fast16_t x2, int_fast16_t y2) {
    uint16_t deltaX = utils_abs(x2 - x1);
    uint16_t deltaY = utils_abs(y2 - y1);
    int16_t signX = x1 < x2 ? 1 : -1;
    int16_t signY = y1 < y2 ? 1 : -1;
    int_fast16_t error = deltaX - deltaY;
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
