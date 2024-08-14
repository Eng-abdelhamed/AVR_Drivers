/***********************************************************************/
/***********************************************************************/
/********************** author     : Abdelhamed Ahmed *********************/
/********************** Layer      : MACL             *********************/
/********************** SWC        : TIMER             *********************/
/********************** version    : 1.00             *********************/
/***********************************************************************/
/***********************************************************************/
#ifndef TIMER_PRIVATE_H
#define TIMER_PRIVATE_H

// Waveform Generation Mode options
#define NORMAL                        0
#define PWM_Phase_Correct             1
#define CTC                           2
#define FAST_PWM                      3

// Clock Select options
#define NO_CLK_SOURCE                 0
#define CLK_NO_PRESCALING             1
#define CLK_8                         2
#define CLK_64                        3
#define CLK_256                       4
#define CLK_1024                      5
#define EXT_CLK_FALLING_EDGE          6
#define EXT_CLK_RISING_EDGE           7

// Compare Match Output Mode options
#define OC0_DISCONNECT                0
#define OC0_TOGGLE                    1
#define OC0_CLR                       2
#define OC0_SET                       3

// Masks for register configurations
#define OC0_MASK                      0b11001111
#define PRE_SCALE_MASK                0b11111000
#define Waveform_Generation_Mode_MASK 0b10110111

#endif
