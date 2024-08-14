/***********************************************************************/
/***********************************************************************/
/********************** author     : Abdelhamed Ahmed *********************/
/********************** Layer      : MACL             *********************/
/********************** SWC        : TIMER             *********************/
/********************** version    : 1.00             *********************/
/***********************************************************************/
/***********************************************************************/
#ifndef TIMER_CONFIG_H
#define TIMER_CONFIG_H

/**
 * Waveform Generation Mode options:
 *         1 - NORMAL
 *         2 - PWM_Phase_Correct
 *         3 - CTC
 *         4 - FAST_PWM
 */
#define Waveform_Generation_Mode  CTC

/**
 * Clock Select options:
 *          1- NO_CLK_SOURCE
 *          2- CLK_NO_PRESCALING
 *          3- CLK_8
 *          4- CLK_64
 *          5- CLK_256
 *          6- CLK_1024
 *          7- EXT_CLK_FALLING_EDGE
 *          8- EXT_CLK_RISING_EDGE
 */
#define CLK_SELECT_BIT            CLK_8

/**
 * Compare match value for 8-bit overflow
 */
#define COMPARE_MATCH_VALUE       250

/**
 * Compare Match Output Mode options:
 *         1 - OC0_DISCONNECT
 *         2 - OC0_TOGGLE
 *         3 - OC0_CLR
 *         4 - OC0_SET
 */
#define COMPARE_MATCH_OUTPUT_MODE    OC0_DISCONNECT

#endif
