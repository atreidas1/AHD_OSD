#ifndef OSD_DATA_H_
#define OSD_DATA_H_

typedef struct __osd_data {
	// VFR_HUD ( #74 )
	float airspeed; /*< [m/s] Vehicle speed in form appropriate for vehicle type. For standard aircraft this is typically calibrated airspeed (CAS) or indicated airspeed (IAS) - either of which can be used by a pilot to estimate stall speed.*/
	float groundspeed; /*< [m/s] Current ground speed.*/
	float alt; /*< [m] Current altitude (MSL).*/
	float climb; /*< [m/s] Current climb rate.*/
	int16_t heading; /*< [deg] Current heading in compass units (0-360, 0=north).*/
	uint8_t throttle; /*< [%] Current throttle setting (0 to 100).*/
	// ATTITUDE ( #30 )
	int16_t roll; /*< [deg] Roll angle */
	int16_t pitch; /*< [deg] Pitch angle */
	// RC_CHANNELS_RAW ( #35 )
	uint8_t rssi; /*Receive signal strength indicator in device-dependent units/scale. Values: [0-254], UINT8_MAX: invalid/unknown.*/
	//HEARTBEAT ( #0 )
	uint8_t base_mode; /*MAV_MODE_FLAG	System mode bitmap.*/
	uint32_t custom_mode; /*A bitfield for use for autopilot-specific flags*/
	uint8_t system_status; /*MAV_STATE	System status flag.*/
	//BATTERY_STATUS ( #147 )
	int32_t current_consumed;/*< [mAh] Consumed charge, -1: autopilot does not provide consumption estimate*/
	uint16_t voltage;/*< [mV] Battery voltage*/
	int16_t current_battery; /*< [mA] Battery current, -1: autopilot does not measure the current*/
	//NAV_CONTROLLER_OUTPUT ( #62 )
	int16_t nav_bearing; /*< [deg] Current desired heading*/
	int16_t target_bearing; /*< [deg] Bearing to current waypoint/target*/
    uint16_t wp_dist; /*< [m] Distance to active waypoint*/
    //GPS_RAW_INT ( #24 )
    int32_t lat; /*< [degE7] Latitude (WGS84, EGM96 ellipsoid)*/
    int32_t lon; /*< [degE7] Longitude (WGS84, EGM96 ellipsoid)*/
    uint8_t fix_type; /*<  GPS fix type.*/
    uint8_t satellites_visible; /*<  Number of satellites visible. If unknown, set to UINT8_MAX*/

} Osd_data;

#endif /* OSD_DATA_H_ */
