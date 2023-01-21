#ifndef UTILS_H_
#define UTILS_H_

#define ToDeg(x) (x*57.3)

typedef int32_t FixedPoint1;

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

static inline uint16_t utils_abs(int16_t x) {
	return x < 0 ? -x : x;
}

#endif /* UTILS_H_ */
