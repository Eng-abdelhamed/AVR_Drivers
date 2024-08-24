/*
 * WDT_program.c
 *
 *  Created on: Aug 24, 2024
 *      Author: abdel
 */

#include"STD_TYPEs.h"
#include"BIT_MATH.h"
#include"WDT_Interface.h"
#include"WDT_Register.h"
#include"WDT_config.h"

void WDT_voidSleep(u8 copy_u8SleepTime)
{
	/*Clear the pre-scalar*/
	WDTCR &= 0b11111000;
	/*Set the pre-scalar*/
	WDTCR |= copy_u8SleepTime;
}


void WDT_voidEnable(void)
{
	/*Enable the watchdog timer*/
    SET_BIT(WDTCR,WDTCR_WDE);
}


void WDT_voidDisable(void)
{
	WDTCR |= 0b00011000;
	WDTCR = 0;
}




