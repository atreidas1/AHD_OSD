#ifndef OSD_POSITION_H_
#define OSD_POSITION_H_

#include "buffer.h"
#include "mavlink/mavlink.h"



void HOME_DIRECTION(int16_t homeDirect){

	uint32_t heading = 0;

	if (homeDirect >= 0 && homeDirect < 8
			|| homeDirect >= 351 && homeDirect < 0) {
		heading = HOME_DIRECTION_0;
	}
	if (homeDirect >= 8 && homeDirect < 19) {
		heading = HOME_DIRECTION_18;

	}
	if (homeDirect >= 19 && homeDirect < 37) {
		heading = HOME_DIRECTION_36;
	}
	if (homeDirect >= 37 && homeDirect < 55) {
		heading = HOME_DIRECTION_54;
	}
	if (homeDirect >= 55 && homeDirect < 73) {
		heading = HOME_DIRECTION_72;
	}
	if (homeDirect >= 73 && homeDirect < 91) {
		heading = HOME_DIRECTION_90;
	}
	if (homeDirect >= 91 && homeDirect < 109) {
		heading = HOME_DIRECTION_108;
	}
	if (homeDirect >= 109 && homeDirect < 127) {
		heading = HOME_DIRECTION_126;
	}
	if (homeDirect >= 127 && homeDirect < 145) {
		heading = HOME_DIRECTION_144;
	}
	if (homeDirect >= 145 && homeDirect < 163) {
		heading = HOME_DIRECTION_162;
	}
	if (homeDirect >= 163 && homeDirect < 181) {
		heading = HOME_DIRECTION_180;
	}
	if (homeDirect >= 181 && homeDirect < 199) {
		heading = HOME_DIRECTION_198;
	}
	if (homeDirect >= 199 && homeDirect < 217) {
		heading = HOME_DIRECTION_216;
	}
	if (homeDirect >= 217 && homeDirect < 235) {
		heading = HOME_DIRECTION_234;
	}
	if (homeDirect >= 235 && homeDirect < 253) {
		heading = HOME_DIRECTION_252;
	}
	if (homeDirect >= 253 && homeDirect < 271) {
		heading = HOME_DIRECTION_270;
	}
	if (homeDirect >= 271 && homeDirect < 289) {
		heading = HOME_DIRECTION_288;
	}
	if (homeDirect >= 289 && homeDirect < 307) {
		heading = HOME_DIRECTION_306;
	}
	if (homeDirect >= 306 && homeDirect < 325) {
		heading = HOME_DIRECTION_324;
	}
	if (homeDirect >= 325 && homeDirect < 343) {
		heading = HOME_DIRECTION_342;
	}
	printGrafic_16xN(24, 20, &SpecialFonts16x15[heading], 15); //Home direction
}

//Вывод знака ARM/Disarm
void ARM_DISARM(uint8_t ARMED){


	if(ARMED & MAV_MODE_FLAG_SAFETY_ARMED ){
		printStringWithPlaceholder(1, 128, " ", 7); //Затираем DISARM
		printGrafic_16xN(4, 128, &SpecialFonts16x15[ARM], 15);
	}
	else{
		printStringWithPlaceholder(4, 134, " ", 2); //Затираем вторую строку ARM
		printStringWithPlaceholder(2, 128, "DISARM", 6);
	}


}


void GPS(){

printGrafic_8xN(1, 1, &SpecialFonts8x15[LAT], 15); //LAT
printGrafic_8xN(39, 1, &SpecialFonts8x15[LON], 15); //LON
printGrafic_16xN(23, 0, &SpecialFonts16x15[SAT], 15); //SAT


}

void GPS_Fix(uint8_t gps_fix){

	if (gps_fix == 0) {
		printGrafic_16xN(27, 1, &SpecialFonts16x15[NO_GPS], 15); //NO GPS
	}
	if (gps_fix == 1) {
		printGrafic_16xN(27, 1, &SpecialFonts16x15[NO_FIX], 15); //NO Fix
	}
	if (gps_fix == 2) {
		printGrafic_16xN(27, 1, &SpecialFonts16x15[TwoD_FIX], 15); //2D Fix
	}
	if (gps_fix == 3) {
		printGrafic_16xN(27, 1, &SpecialFonts16x15[ThreeD_FIX], 15); //3D Fix
	}

}

void NAVIGATION(){

	//printGrafic_32xN(23, 15, &SpecialFonts32x30[heading], 30); //Home direction
	printGrafic_16xN(1, 22, &SpecialFonts16x15[HOME_DIST_ICON], 15); //HOME Dist
	printGrafic_16xN(1, 37, &SpecialFonts16x15[TRIP], 15); //TRIP
	printGrafic_8xN(8, 60, &SpecialFonts8x105[LEFT_LIMB], 105); //LEFT LIMB
	printGrafic_8xN(42, 60, &SpecialFonts8x105[RIGHT_LIMB], 105); //RIGHT LIMB

	printGrafic_32xN(4, 105, &SpecialFonts32x15[FRAME_SPEED_ONE], 15); //Правая часть рамки скорости
	printGrafic_16xN(2, 105, &SpecialFonts16x15[FRAME_SPEED_TWO], 15); //Лева часть рамки скорости

	printGrafic_32xN(43, 105, &SpecialFonts32x15[FRAME_ALT_ONE], 15); //Левая часть рамки высоты
	printGrafic_16xN(47, 105, &SpecialFonts16x15[FRAME_ALT_TWO], 15); //Правая часть рамки высоты

	printGrafic_16xN(24, 105, &SpecialFonts16x15[CENTER_CURSOR], 15); //CENTR CURSOR

	printGrafic_8xN(1, 104, &SpecialFonts8x15[kmh], 15); //kmh
	printString(49, 108, "m"); //m

	printGrafic_32xN(44, 128, &SpecialFonts32x15[ms_LEFT], 15); // m/s левая часть
	printGrafic_8xN(48, 128, &SpecialFonts8x15[ms_RIGHT], 15); // m/s правая часть

	printGrafic_32xN(44, 82, &SpecialFonts32x15[GLD_DIST_PART_ONE], 15); // GLD DIST левая часть
	printGrafic_8xN(48, 82, &SpecialFonts8x15[GLD_DIST_PART_TWO], 15); // GLD DIST правая часть




}

void ELECTRIC_TIME(){

	printGrafic_16xN(1, 223, &SpecialFonts16x15[FLIGHT_TIME], 15); // FLIGHT TIME
	printString(23, 227, "V");
	printString(30, 227, "A");
	printGrafic_8xN(36, 223, &SpecialFonts8x15[EFF], 15); // EFF


	printGrafic_8xN(42, 223, &SpecialFonts8x15[mah], 15); //mah
}

void OSD_STATIC_IMAGE(){
	GPS();
	NAVIGATION();
	ELECTRIC_TIME();


}



#endif /* OSD_POSITION_H_ */

