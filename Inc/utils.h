#ifndef UTILS_H_
#define UTILS_H_
#include <math.h>

#define ToDeg(x) (x*57.3)
#define  radInDeg 0.01745329252

typedef int32_t FixedPoint1;
typedef int32_t FixedPoint3;

//hh:mm:ss
static inline uint8_t* msToHourMinSecStr (uint32_t number, uint8_t *buffer) {
	uint32_t hours = 0;
	uint32_t minutes = 0;
	uint32_t seconds = 0;
	number = number/1000;
	seconds = number%60;
	hours = number/3600;
	minutes = (number - hours*3600 - seconds)/60;
	buffer[0] = hours/10 + '0';
	buffer[1] = hours%10 + '0';
	buffer[2] = ':';
	buffer[3] = minutes/10 + '0';
	buffer[4] = minutes%10 + '0';
	buffer[5] = ':';
	buffer[6] = seconds/10 + '0';
	buffer[7] = seconds%10 + '0';
	buffer[8] = 0;

	return buffer;
}

static inline FixedPoint1 toFixedPoint1(float number){
	return number*10;
}

static inline uint8_t* FPToString(FixedPoint1 value, uint8_t *buffer) {
	buffer += 11;
	*--buffer = 0;
	if (value < 0) {
		value *= -1;
		*--buffer = value % 10 + '0';
		value = value / 10;
		*--buffer = '.';
		do {
			*--buffer = value % 10 + '0';
			value = value / 10;
		} while (value != 0);
		*--buffer = '-';
	} else {
		*--buffer = value % 10 + '0';
		value = value / 10;
		*--buffer = '.';
		do {
			*--buffer = value % 10 + '0';
			value = value / 10;
		} while (value != 0);
	}
	return buffer;
}

//322
static inline uint8_t* intToString(int32_t value, uint8_t *buffer) {
	buffer += 11;
	*--buffer = 0;
	if (value < 0) {
		value *= -1;
		do {
			*--buffer = value % 10 + '0';
			value = value / 10;
		} while (value != 0);
		*--buffer = '-';
	} else {
		do {
			*--buffer = value % 10 + '0';
			value = value / 10;
		} while (value != 0);
	}
	return buffer;
}

static inline int32_t utils_abs(int32_t x) {
	return x < 0 ? -x : x;
}


  FixedPoint3 getDistanceBetweenPointsNew(float latitude1, float longitude1, float latitude2, float longitude2) {
	  float theta = longitude1 - longitude2;
	  float rad1 = latitude1 * radInDeg;
	  float rad2 = latitude2 * radInDeg;
	  return 6371000*acos(sin(rad1) * sin(rad2) + cos(rad1) * cos(rad2) * cos(theta * radInDeg));
}

#endif /* UTILS_H_ */
