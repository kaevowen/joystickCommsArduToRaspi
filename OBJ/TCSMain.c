#include <stdio.h>      //printf()
#include <stdlib.h>

#include "DEV_Config.h"
#include "TCS34725.h"

UWORD r,g,b,c;
UWORD cpl,lux,k;

int callTCS(){
	RGB rgb;
	UDOUBLE	RGB888=0;
	UWORD 	RGB565=0;

	if(DEV_ModuleInit() != 0) {
		exit(0);
	}
	
	if(TCS34725_Init() != 0) {
		perror("TCS34725_Init()");
		exit(0);
	}

	TCS34725_SetLight(60);

	rgb = TCS34725_Get_RGBData();
	RGB888 = TCS34725_GetRGB888(rgb);
	RGB565 = TCS34725_GetRGB565(rgb);
	
	printf("Call TCS34725\n");
	printf("RGB888 : R = %d / G = %d / B = %d // ",
			(RGB888>>16), (RGB888>>8), (RGB888) & 0xff);
	printf("RGB888 = 0X%X | RGB565=0X%X | rgb = %x ",
			RGB888, RGB565, rgb.C);

	if ( TCS34725_GetLux_Interrupt(0xff00, 0x00ff) == 1 ) {
		printf("Lux_Interrupt = 1\r\n");
	} else {
		printf("Lux_Interript = 0\r\n");
	}
	
	DEV_ModuleExit();
	return 0;
}


