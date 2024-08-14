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
 * @brief  initialize  for the Timer0 Compare Match interrupt.
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

#endif
