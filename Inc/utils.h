#ifndef UTILS_H_
#define UTILS_H_

#define ToDeg(x) (x*57.3)

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
