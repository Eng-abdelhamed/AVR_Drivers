/***********************************************************************/
/***********************************************************************/
/********************** author     : Abdelhamed Ahmed *********************/
/********************** Layer      : MACL             *********************/
/********************** SWC        : TIMER             *********************/
/********************** version    : 1.00             *********************/
/***********************************************************************/
/***********************************************************************/
#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

/**
 * @brief  initialize  for the Timer0 [normal , ctc , fast pwm , phase correct pwm ].
 * @param  void
 * @return void
 */
void TIMER0_voidInit(void);

/**
 * @brief  Sets the callback function for the Timer0 Compare Match interrupt.
 * @param  CAll_packFunc: Pointer to the callback function.
 * @return u8: Status of the function (OK if successful, NOK if not).
 */
u8 TIMER0_u8SetCallBack(void(*CAll_packFunc)(void));
/**
 * @brief  set the OC0 the compare match value [fast pwm on pin 0c0 ]
 * @param  value range from 0 -> 255
 * @return void
 */
void timer0_voidSetCompareValue(u8 value);

/**
 * @brief  initialize  for the Timer1
 * @param  void
 * @return void
 */

/*******************************************************/


void TIMER1_voidInit(void);




void TIMER1_voidSetICR(u16 copy_u16ICRVAL);



void timer1_voidSetChannelA_CompareMatch(u16 value);



#endif
