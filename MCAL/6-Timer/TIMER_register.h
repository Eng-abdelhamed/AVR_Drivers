/***********************************************************************/
/***********************************************************************/
/********************** author     : Abdelhamed Ahmed *********************/
/********************** Layer      : MACL             *********************/
/********************** SWC        : TIMER             *********************/
/********************** version    : 1.00          *********************/
/***********************************************************************/
/***********************************************************************/
#ifndef TIMER_REGISTER_h
#define TIMER_REGISTER_H

#define TCCR0          *((volatile u8 *)0x53) // timer 0 control register
#define TCCR0_CS00     0                       /*  Pre_scalar 0*/
#define TCCR0_CS01     1                       /*  Pre_scalar 1*/
#define TCCR0_CS02     2                       /*  Pre_scalar 2*/
#define TCCR0_WGRM01   3                       // wave form generation mode bit 1
#define TCCR0_COM00    4                       //control the Output Compare pin (OC0) behavior
#define TCCR0_COM01    5                       //control the Output Compare pin (OC0) behavior
#define TCCR0_WGRM00   6                       // wave form generation mode bit 0

#define




#define OCR0            *((volatile u8 *)0x5C)   // output compare register 0
#define TIMSK           *((volatile u8 *)0x59)   // timer mask
#define TMSK_OCIE0      1                        // output compare 0 intrupt enable
#define

#endif
