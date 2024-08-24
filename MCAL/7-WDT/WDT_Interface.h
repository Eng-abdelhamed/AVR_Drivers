/*
 * WDT_Interface.h
 *
 *  Created on: Aug 24, 2024
 *      Author: abdel
 */

#ifndef WDT_INTERFACE_H_
#define WDT_INTERFACE_H_

#define PRE_Scalar_16ms       0
#define PRE_Scalar_32ms       1
#define PRE_Scalar_65ms       2
#define PRE_Scalar_0sec       3
#define PRE_Scalar_0_5sec     4
#define PRE_Scalar_0_52sec    5
#define PRE_Scalar_1sec       6
#define PRE_Scalar_2sec       7

void WDT_voidSleep(u8 copy_u8SleepTime);


void WDT_voidEnable(void);


void WDT_voidDisable(void);



#endif /* WDT_INTERFACE_H_ */
