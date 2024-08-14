/***********************************************************************/
/***********************************************************************/
/********************** author     : Abdelhamed Ahmed *********************/
/********************** Layer      : MACL             *********************/
/********************** SWC        : TIMER             *********************/
/********************** version    : 1.00          *********************/
/***********************************************************************/
/***********************************************************************/
#include"STD_TYPEs.h"
#include"BIT_MATH.h"
#include"TIMER_register.h"
#include"TIMER_config.h"
#include"TIMER_private.h"
#include"TIMER_interface.h"

static void (*callPackFunc)(void) = 0;
void TIMER0_voidInit(void)
{
   /*Initialize the CTC mode condition*/
#if   Waveform_Generation_Mode == NORMAL

	TCCR0 &= Waveform_Generation_Mode_MASK ;
	TCCR0 |= NORMAL;



#elif Waveform_Generation_Mode == CTC
	TCCR0 &= Waveform_Generation_Mode_MASK ;
	TCCR0 |= CTC;

	/*Initialize the OC0 pin mode (DIS,SET,CLR,TOG)*/
   #if Waveform_Generation_Mode == CTC || Waveform_Generation_Mode == NORMAL
	TCCR0 &= OC0_MASK;
	TCCR0 |=OC0_DSCONNECT;
    #endif
	/*Peripheral Interrupt Enable*/
	SET_BIT(TIMSK,TMSK_OCIE0);

	/*Set Compare Match Value To 250*/
	OCR0 = COMPARE_MATCH_VALUE;

	/*PreScalar division  by 8 */  // Important to be last code to start timer
	TCCR0 &= PRE_SCALE_MASK;
	TCCR0 |= CLK_8;
#endif
}

u8  TIMER0_u8SetCallPack(void(*CAll_packFunc)(void))
{
 u8 Local_u8ReturnState = OK;

 if(CAll_packFunc == 0)
 {
	 Local_u8ReturnState = NOK;
 }
 else
 {
	 callPackFunc = CAll_packFunc;
 }
    return Local_u8ReturnState;
}
/*ISR FUNCTION*/
void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{

	callPackFunc();

}



