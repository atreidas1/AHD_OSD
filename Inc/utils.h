#ifndef UTILS_H_
#define UTILS_H_
#include <math.h>

#define ToDeg(x) (x*57.272729)
#define GPSCoordToFloat(x) (x/10000000.0)
#define radInDeg 0.01745329252

typedef int32_t FixedPoint1;
typedef int32_t FixedPoint3;
typedef struct {
	int32_t distance;
	int32_t bearing;
} HomeDistAndBearing;
HomeDistAndBearing hdb;

//hh:mm:ss
static inline char* msToHourMinSecStr (uint32_t number, char *buffer) {
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

static inline char* FPToString_N(FixedPoint1 value, uint32_t charsAfterPoint, char *buffer) {
	buffer += 11;
	*--buffer = 0;
	if (value < 0) {
		value = -value;
		do {
			*--buffer = value % 10 + '0';
			value = value / 10;
			charsAfterPoint--;
		} while (charsAfterPoint != 0);
		*--buffer = '.';
		do {
			*--buffer = value % 10 + '0';
			value = value / 10;
		} while (value != 0);
		*--buffer = '-';
	} else {
		do {
			*--buffer = value % 10 + '0';
			value = value / 10;
			charsAfterPoint--;
		} while (charsAfterPoint != 0);
		*--buffer = '.';
		do {
			*--buffer = value % 10 + '0';
			value = value / 10;
		} while (value != 0);
	}
	return buffer;
}

static inline char* FPToString(FixedPoint1 value, uint8_t *buffer) {
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
static inline char* intToString(int32_t value, char *buffer) {
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

/*
You can manually calculate the bearing between two points using a map, a compass, and a protractor.
However, if you know the exact latitudes and longitudes of the points in question, you can use the following formula:

β = atan2(X,Y)
Calculate X and Y as follows:

X = cos θb * sin ∆L
Y = cos θa * sin θb – sin θa * cos θb * cos ∆L
Whereas:

L represents longitude.
θ represents latitude.
β is the bearing.
*/
static inline HomeDistAndBearing* getDistanceBetweenPoints(double latitude1,
		double longitude1, double latitude2, double longitude2) {
	double deltaLon = (longitude2 - longitude1)*radInDeg;
	double rad1 = latitude1 * radInDeg;
	double rad2 = latitude2 * radInDeg;
	double cos1 = cos(rad1);
	double sin1 = sin(rad1);
	double cos2 = cos(rad2);
	double sin2 = sin(rad2);
	double cosDelatLon = cos(deltaLon);

	double X = cos2*sin(deltaLon);
	double Y = cos1*sin2 - sin1*cos2*cosDelatLon;
	double bearing = ToDeg(atan2(X, Y));
	if(bearing < 0) {
		bearing = 360 + bearing;
	}
	hdb.bearing = bearing;
	hdb.distance = 6371000 * acos(sin1 * sin2 + cos1 * cos2 * cosDelatLon);
	return &hdb;
}

#endif /* UTILS_H_ */
