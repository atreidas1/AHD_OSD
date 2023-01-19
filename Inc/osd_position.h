#ifndef OSD_POSITION_H_
#define OSD_POSITION_H_

#include "buffer.h"




void GPS(){

printGrafic_8xN(2, 0, &SpecialFonts8x15[LAT], 15); //LAT
printGrafic_8xN(40, 0, &SpecialFonts8x15[LON], 15); //LON
printGrafic_16xN(23, 0, &SpecialFonts16x15[SAT], 15); //SAT

}

void NAVIGATION(){

	printGrafic_32xN(23, 15, &SpecialFonts32x30[HOME_DIRECTION_0], 30); //Home direction
	printGrafic_16xN(2, 30, &SpecialFonts16x15[HOME_DIST_ICON], 15); //HOME Dist
	printGrafic_16xN(2, 45, &SpecialFonts16x15[TRIP], 15); //TRIP
	printGrafic_8xN(8, 60, &SpecialFonts8x105[LEFT_LIMB], 105); //LEFT LIMB
	printGrafic_8xN(42, 60, &SpecialFonts8x105[RIGHT_LIMB], 105); //RIGHT LIMB

	printGrafic_32xN(4, 105, &SpecialFonts32x15[FRAME_SPEED_ONE], 15); //Правая часть рамки скорости
	printGrafic_16xN(2, 105, &SpecialFonts16x15[FRAME_SPEED_TWO], 15); //Лева часть рамки скорости

	printGrafic_32xN(43, 105, &SpecialFonts32x15[FRAME_ALT_ONE], 15); //Левая часть рамки высоты
	printGrafic_16xN(47, 105, &SpecialFonts16x15[FRAME_ALT_TWO], 15); //Правая часть рамки высоты

	printGrafic_16xN(24, 105, &SpecialFonts16x15[CENTER_CURSOR], 15); //CENTR CURSOR

}

void ELECTRIC_TIME(){

	printGrafic_16xN(2, 225, &SpecialFonts16x15[FLIGHT_TIME], 15); // FLIGHT TIME
	printStr(&osd_buffer[0][0], 15, 225, "V", 1);
}
void OSD_STATIC_IMAGE(){
	GPS();
	NAVIGATION();
	ELECTRIC_TIME();
}

#endif /* OSD_POSITION_H_ */

