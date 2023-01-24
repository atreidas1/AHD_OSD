#ifndef OSD_POSITION_H_
#define OSD_POSITION_H_

#include "buffer.h"

uint32_t heading = 0;

void HOME_DIRECTION(){
	if (osd_data.heading >= 0 && osd_data.heading < 11 || osd_data.heading >= 335 && osd_data.heading < 0) {
		heading = HOME_DIRECTION_0;
	}
	if (osd_data.heading >= 11 && osd_data.heading < 22) {
		heading = HOME_DIRECTION_22;

	}
	if (osd_data.heading >= 22 && osd_data.heading < 44) {
		heading = HOME_DIRECTION_45;
	}
	if (osd_data.heading >= 44 && osd_data.heading < 66) {
		heading = HOME_DIRECTION_67;
	}
	if (osd_data.heading >= 66 && osd_data.heading < 89) {
		heading = HOME_DIRECTION_90;
	}
	if (osd_data.heading >= 89 && osd_data.heading < 114) {
		heading = HOME_DIRECTION_115;
	}
	if (osd_data.heading >= 114 && osd_data.heading < 132) {
		heading = HOME_DIRECTION_135;
	}
	if (osd_data.heading >= 132 && osd_data.heading < 155) {
		heading = HOME_DIRECTION_157;
	}
	if (osd_data.heading >= 155 && osd_data.heading < 178) {
		heading = HOME_DIRECTION_180;
	}
	if (osd_data.heading >= 178 && osd_data.heading < 200) {
		heading = HOME_DIRECTION_202;
	}
	if (osd_data.heading >= 200 && osd_data.heading < 223) {
		heading = HOME_DIRECTION_225;
	}
	if (osd_data.heading >= 223 && osd_data.heading < 245) {
		heading = HOME_DIRECTION_247;
	}
	if (osd_data.heading >= 245 && osd_data.heading < 268) {
		heading = HOME_DIRECTION_270;
	}
	if (osd_data.heading >= 268 && osd_data.heading < 290) {
		heading = HOME_DIRECTION_292;
	}
	if (osd_data.heading >= 290 && osd_data.heading < 313) {
		heading = HOME_DIRECTION_315;
	}
	if (osd_data.heading >= 313 && osd_data.heading < 335) {
		heading = HOME_DIRECTION_337;
	}


	printGrafic_32xN(23, 20, &SpecialFonts32x30[heading], 30); //Home direction
}

void ARM_DISARM(){

	if(osd_data.base_mode & MAV_MODE_FLAG_SAFETY_ARMED){
		printGrafic_16xN(4, 128, &SpecialFonts16x15[ARM], 15);
	}
	else{
		printGrafic_16xN(4, 128, &SpecialFonts16x15[DISARM], 15);
	}

}


void GPS(){

printGrafic_8xN(2, 1, &SpecialFonts8x15[LAT], 15); //LAT
printGrafic_8xN(40, 1, &SpecialFonts8x15[LON], 15); //LON
printGrafic_16xN(23, 0, &SpecialFonts16x15[SAT], 15); //SAT

}

void NAVIGATION(){

	//printGrafic_32xN(23, 15, &SpecialFonts32x30[heading], 30); //Home direction
	printGrafic_16xN(2, 30, &SpecialFonts16x15[HOME_DIST_ICON], 15); //HOME Dist
	printGrafic_16xN(2, 45, &SpecialFonts16x15[TRIP], 15); //TRIP
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

}

void ELECTRIC_TIME(){

	printGrafic_16xN(2, 223, &SpecialFonts16x15[FLIGHT_TIME], 15); // FLIGHT TIME
	printString(24, 227, "V");
	printString(32, 227, "A");


	printGrafic_8xN(42, 223, &SpecialFonts8x15[mah], 15); //mah
}

void OSD_STATIC_IMAGE(){
	GPS();
	NAVIGATION();
	ELECTRIC_TIME();

}



#endif /* OSD_POSITION_H_ */

