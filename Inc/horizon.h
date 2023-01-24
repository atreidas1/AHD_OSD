#ifndef HORIZON_H_
#define HORIZON_H_
#include "buffer.h"

#define X_0 200
#define Y_0 113

#define MAX_Y_SHIFT 50

#define PIXELS_PER_PITCH_DEGREE 1

#define MAX_ROL_DEEGREES 45
uint32_t clearIndex = 0;


const int8_t negativeCornerX[] = {48, 38, 28, 18, 48, 38, 28, 18, 48, 38, 28, 18, 48, 38, 28, 18, 48, 38, 28, 18, 48, 38, 28, 18, 48, 38, 28, 18, 48, 38, 28, 18, 48, 38, 28, 18, 47, 38, 28, 18, 47, 37, 28, 18, 47, 37, 27, 18, 47, 37, 27, 18, 47, 37, 27, 18, 47, 37, 27, 17, 46, 37, 27, 17, 46, 37, 27, 17, 46, 36, 27, 17, 46, 36, 27, 17, 45, 36, 26, 17, 45, 36, 26, 17, 45, 35, 26, 17, 45, 35, 26, 17, 44, 35, 26, 17, 44, 35, 26, 16, 44, 34, 25, 16, 43, 34, 25, 16, 43, 34, 25, 16, 42, 34, 25, 16, 42, 33, 24, 16, 42, 33, 24, 16, 41, 33, 24, 15, 41, 32, 24, 15, 40, 32, 23, 15, 40, 32, 23, 15, 39, 31, 23, 15, 39, 31, 23, 15, 38, 30, 22, 14, 38, 30, 22, 14, 37, 30, 22, 14, 37, 29, 21, 14, 36, 29, 21, 14, 36, 28, 21, 13, 35, 28, 20, 13, 35, 27, 20, 13, 34, 27, 20, 13, 33, 26, 19, 13, 33, 26, 19, 12, 32, 25, 19, 12, 31, 25, 18, 12, 31, 24, 18, 12, 30, 24, 18, 11, 30, 23, 17, 11, 29, 23, 17, 11, 28, 22, 16, 11, 28, 22, 16, 10, 27, 21, 16, 10, 26, 21, 15, 10, 25, 20, 15, 10, 25, 20, 14, 9, 24, 19, 14, 9};
const int8_t negativeCornerY[] = {0, 0, 0, 0, 1, 1, 0, 0, 2, 1, 1, 1, 3, 2, 1, 1, 3, 3, 2, 1, 4, 3, 2, 2, 5, 4, 3, 2, 6, 5, 3, 2, 7, 5, 4, 3, 8, 6, 4, 3, 8, 7, 5, 3, 9, 7, 5, 3, 10, 8, 6, 4, 11, 9, 6, 4, 12, 9, 7, 4, 12, 10, 7, 5, 13, 10, 8, 5, 14, 11, 8, 5, 15, 12, 9, 6, 16, 12, 9, 6, 16, 13, 10, 6, 17, 14, 10, 6, 18, 14, 10, 7, 19, 15, 11, 7, 20, 15, 11, 7, 20, 16, 12, 8, 21, 17, 12, 8, 22, 17, 13, 8, 23, 18, 13, 8, 23, 18, 14, 9, 24, 19, 14, 9, 25, 20, 14, 9, 25, 20, 15, 10, 26, 21, 15, 10, 27, 21, 16, 10, 28, 22, 16, 10, 28, 22, 16, 11, 29, 23, 17, 11, 30, 23, 17, 11, 30, 24, 18, 11, 31, 24, 18, 12, 31, 25, 18, 12, 32, 25, 19, 12, 33, 26, 19, 12, 33, 26, 19, 13, 34, 27, 20, 13, 35, 27, 20, 13, 35, 28, 20, 13, 36, 28, 21, 13, 36, 29, 21, 14, 37, 29, 21, 14, 37, 30, 22, 14, 38, 30, 22, 14, 38, 30, 22, 14, 39, 31, 23, 15, 39, 31, 23, 15, 40, 32, 23, 15, 40, 32, 23, 15, 41, 32, 24, 15, 41, 33, 24, 15, 42, 33, 24, 16};

const int8_t positiveCornerX[] = {48, 38, 28, 18, 48, 38, 28, 18, 48, 38, 28, 18, 48, 38, 28, 18, 48, 38, 28, 18, 48, 38, 28, 18, 48, 38, 28, 18, 48, 38, 28, 18, 47, 38, 28, 18, 47, 37, 28, 18, 47, 37, 27, 18, 47, 37, 27, 18, 47, 37, 27, 18, 47, 37, 27, 17, 46, 37, 27, 17, 46, 37, 27, 17, 46, 36, 27, 17, 46, 36, 27, 17, 45, 36, 26, 17, 45, 36, 26, 17, 45, 35, 26, 17, 45, 35, 26, 17, 44, 35, 26, 17, 44, 35, 26, 16, 44, 34, 25, 16, 43, 34, 25, 16, 43, 34, 25, 16, 42, 34, 25, 16, 42, 33, 24, 16, 42, 33, 24, 16, 41, 33, 24, 15, 41, 32, 24, 15, 40, 32, 23, 15, 40, 32, 23, 15, 39, 31, 23, 15, 39, 31, 23, 15, 38, 30, 22, 14, 38, 30, 22, 14, 37, 30, 22, 14, 37, 29, 21, 14, 36, 29, 21, 14, 36, 28, 21, 13, 35, 28, 20, 13, 35, 27, 20, 13, 34, 27, 20, 13, 33, 26, 19, 13, 33, 26, 19, 12, 32, 25, 19, 12, 31, 25, 18, 12, 31, 24, 18, 12, 30, 24, 18, 11, 30, 23, 17, 11, 29, 23, 17, 11, 28, 22, 16, 11, 28, 22, 16, 10, 27, 21, 16, 10, 26, 21, 15, 10, 25, 20, 15, 10, 25, 20, 14, 9, 24, 19, 14, 9};
const int8_t positiveCornerY[] = {-1, -1, 0, 0, -2, -1, -1, -1, -3, -2, -1, -1, -3, -3, -2, -1, -4, -3, -2, -2, -5, -4, -3, -2, -6, -5, -3, -2, -7, -5, -4, -3, -8, -6, -4, -3, -8, -7, -5, -3, -9, -7, -5, -3, -10, -8, -6, -4, -11, -9, -6, -4, -12, -9, -7, -4, -12, -10, -7, -5, -13, -10, -8, -5, -14, -11, -8, -5, -15, -12, -9, -6, -16, -12, -9, -6, -16, -13, -10, -6, -17, -14, -10, -6, -18, -14, -10, -7, -19, -15, -11, -7, -20, -15, -11, -7, -20, -16, -12, -8, -21, -17, -12, -8, -22, -17, -13, -8, -23, -18, -13, -8, -23, -18, -14, -9, -24, -19, -14, -9, -25, -20, -14, -9, -25, -20, -15, -10, -26, -21, -15, -10, -27, -21, -16, -10, -28, -22, -16, -10, -28, -22, -16, -11, -29, -23, -17, -11, -30, -23, -17, -11, -30, -24, -18, -11, -31, -24, -18, -12, -31, -25, -18, -12, -32, -25, -19, -12, -33, -26, -19, -12, -33, -26, -19, -13, -34, -27, -20, -13, -35, -27, -20, -13, -35, -28, -20, -13, -36, -28, -21, -13, -36, -29, -21, -14, -37, -29, -21, -14, -37, -30, -22, -14, -38, -30, -22, -14, -38, -30, -22, -14, -39, -31, -23, -15, -39, -31, -23, -15, -40, -32, -23, -15, -40, -32, -23, -15, -41, -32, -24, -15, -41, -33, -24, -15, -42, -33, -24, -16};

static inline void drawHorizon(int32_t rolDegrees, int32_t pitchDegrees) {
	int8_t *xArr;
	int8_t *yArr;
	uint32_t startIndex;
	int32_t y_shift =  pitchDegrees*PIXELS_PER_PITCH_DEGREE;
	if(utils_abs(y_shift) > MAX_Y_SHIFT) {
		y_shift = y_shift < 0 ? -MAX_Y_SHIFT : MAX_Y_SHIFT;
	}
	int32_t y0 = Y_0 + y_shift;

	if(utils_abs(rolDegrees) > MAX_ROL_DEEGREES) {
		rolDegrees = rolDegrees < 0 ? -MAX_ROL_DEEGREES : MAX_ROL_DEEGREES;
	}

	if(rolDegrees < 0) {
		rolDegrees = -rolDegrees;
		xArr = negativeCornerX;
		yArr = negativeCornerY;
		startIndex = (rolDegrees-1)*4;
	} else {
		xArr = positiveCornerX;
		yArr = positiveCornerY;
		startIndex = rolDegrees*4;
	}
//	clearPixel(X_0 + xArr[clearIndex], y0 + yArr[clearIndex]);
//	clearPixel(X_0 - xArr[clearIndex], y0 - yArr[clearIndex]);
//	clearIndex++;
//	clearPixel(X_0 + xArr[clearIndex], y0 + yArr[clearIndex]);
//	clearPixel(X_0 - xArr[clearIndex], y0 - yArr[clearIndex]);
//	clearIndex++;
//	clearPixel(X_0 + xArr[clearIndex], y0 + yArr[clearIndex]);
//	clearPixel(X_0 - xArr[clearIndex], y0 - yArr[clearIndex]);
//	clearIndex++;
//	clearPixel(X_0 + xArr[clearIndex], y0 + yArr[clearIndex]);
//	clearPixel(X_0 - xArr[clearIndex], y0 - yArr[clearIndex]);
//
//	clearIndex = startIndex;
	for(int i = Y_0 - MAX_Y_SHIFT - 35; i <= Y_0 + MAX_Y_SHIFT + 35; i++){
		osd_buffer[i][18] = 0;
		osd_buffer[i][19] = 0;
		osd_buffer[i][20] = 0;
		osd_buffer[i][21] = 0;
		osd_buffer[i][22] = 0;
		osd_buffer[i][23] = 0;

		osd_buffer[i][26] = 0;
		osd_buffer[i][27] = 0;
		osd_buffer[i][28] = 0;
		osd_buffer[i][29] = 0;
		osd_buffer[i][30] = 0;
		osd_buffer[i][31] = 0;
	}

	setPixel(X_0 + xArr[startIndex], y0 + yArr[startIndex]);
	setPixel(X_0 - xArr[startIndex], y0 - yArr[startIndex]);
	setPixel(X_0 + xArr[startIndex] + 1, y0 + yArr[startIndex]);
	setPixel(X_0 - xArr[startIndex] - 1, y0 - yArr[startIndex]);
	startIndex++;
	setPixel(X_0 + xArr[startIndex], y0 + yArr[startIndex]);
	setPixel(X_0 - xArr[startIndex], y0 - yArr[startIndex]);
	setPixel(X_0 + xArr[startIndex] + 1, y0 + yArr[startIndex]);
	setPixel(X_0 - xArr[startIndex] - 1, y0 - yArr[startIndex]);
	startIndex++;
	setPixel(X_0 + xArr[startIndex], y0 + yArr[startIndex]);
	setPixel(X_0 - xArr[startIndex], y0 - yArr[startIndex]);
	setPixel(X_0 + xArr[startIndex] + 1, y0 + yArr[startIndex]);
	setPixel(X_0 - xArr[startIndex] - 1, y0 - yArr[startIndex]);
	startIndex++;
	setPixel(X_0 + xArr[startIndex], y0 + yArr[startIndex]);
	setPixel(X_0 - xArr[startIndex], y0 - yArr[startIndex]);
	setPixel(X_0 + xArr[startIndex] + 1, y0 + yArr[startIndex]);
	setPixel(X_0 - xArr[startIndex] - 1, y0 - yArr[startIndex]);
}

#endif
