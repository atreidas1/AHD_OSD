#ifndef ARDUPILOT_MODES_H_
#define ARDUPILOT_MODES_H_
/*
 * ArduPilotmodes
 */
static inline char* defineCustomMode(uint32_t code) {
	switch (code) {
		case 0: return "MANUAL";
		case 1: return "CIRCLE";
		case 2: return "STABILIZE";
		case 3: return "TRAINING";
		case 4: return "ACRO";
		case 5: return "FBWA";
		case 6: return "FBWB";
		case 7: return "CRUISE";
		case 8: return "AUTOTUNE";
		case 10: return "AUTO";
		case 11: return "RTL";
		case 12: return "LOITER";
		case 13: return "TAKEOFF";
		case 14: return "AVOID_ADSB";
		case 15: return "GUIDED";
		case 16: return "INIT";
		case 24: return "THERMAL";
		default:
			return "UNKNOWN";
	}
}
#endif /* ARDUPILOT_MODES_H_ */
