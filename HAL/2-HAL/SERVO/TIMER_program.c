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
	/*Initialize the  mode condition*/
#if   Waveform_Generation_Mode == NORMAL

	/*Setting the NORMAL mode*/
	CLR_BIT(TCCR0,TCCR0_WGRM01);
	CLR_BIT(TCCR0,TCCR0_WGRM00);

	/*Setting the Output of OC0*/
#if COMPARE_MATCH_OUTPUT_MODE == OC0_DISCONNECT
	CLR_BIT(TCCR0,TCCR0_COM01);
	CLR_BIT(TCCR0,TCCR0_COM00);

#elif COMPARE_MATCH_OUTPUT_MODE ==  OC0_TOGGLE
	SET_BIT(TCCR0,TCCR0_COM00);
	CLR_BIT(TCCR0,TCCR0_COM01);

#elif COMPARE_MATCH_OUTPUT_MODE == OC0_CLR
	SET_BIT(TCCR0,TCCR0_COM01);
	CLR_BIT(TCCR0,TCCR0_COM00);

#elif COMPARE_MATCH_OUTPUT_MODE == OC0_SET
	SET_BIT(TCCR0,TCCR0_COM01);
	SET_BIT(TCCR0,TCCR0_COM00);
#endif

	/*Peripheral Interrupt Enable*/
	SET_BIT(TIMSK,TMSK_OCIE0);

    /*Setting the PreLOad Value */
    TCNT0 = Pre_Load_Value

	/*PreScalar division  by 8 */  // Important to be last code to start timer
	TCCR0 &= PRE_SCALE_MASK;
	TCCR0 |= CLK_SELECT_BIT;

   /***************************************************/
#elif Waveform_Generation_Mode == CTC

	/*Setting the CTC Mode */
	SET_BIT(TCCR0,TCCR0_WGRM01);
	CLR_BIT(TCCR0,TCCR0_WGRM00);

	/*Setting the Output of OC0*/
#if COMPARE_MATCH_OUTPUT_MODE == OC0_DISCONNECT
	CLR_BIT(TCCR0,TCCR0_COM01);
	CLR_BIT(TCCR0,TCCR0_COM00);

#elif COMPARE_MATCH_OUTPUT_MODE ==  OC0_TOGGLE
	SET_BIT(TCCR0,TCCR0_COM00);
	CLR_BIT(TCCR0,TCCR0_COM01);

#elif COMPARE_MATCH_OUTPUT_MODE == OC0_CLR
	SET_BIT(TCCR0,TCCR0_COM01);
	CLR_BIT(TCCR0,TCCR0_COM00);

#elif COMPARE_MATCH_OUTPUT_MODE == OC0_SET
	SET_BIT(TCCR0,TCCR0_COM01);
	SET_BIT(TCCR0,TCCR0_COM00);
#endif

	/*Peripheral Interrupt Enable*/
	SET_BIT(TIMSK,TMSK_OCIE0);

	/*Set Compare Match Value*/
	OCR0 = COMPARE_MATCH_VALUE;

	/*PreScalar division  by 8 */  // Important to be last code to start timer
	TCCR0 &= PRE_SCALE_MASK;
	TCCR0 |= CLK_SELECT_BIT;

/***************************************************/
#elif Waveform_Generation_Mode == FAST_PWM
    /*Setting the FAST PWM Mode*/
	SET_BIT(TCCR0,TCCR0_WGRM01);
	SET_BIT(TCCR0,TCCR0_WGRM00);

  /*Setting the output mode */
#if COMPARE_OUTPUT_FAST_PWM == OC0_DISCONNECT
	CLR_BIT(TCCR0,TCCR0_COM01);
	CLR_BIT(TCCR0,TCCR0_COM00);

#elif COMPARE_OUTPUT_FAST_PWM == CLR_ON_COMP_MATCH_SET_ON_TOP
	SET_BIT(TCCR0,TCCR0_COM01);
	CLR_BIT(TCCR0,TCCR0_COM00);

#elif COMPARE_OUTPUT_FAST_PWM == SET_ON_COMP_MATCH_CLR_ON_TOP
	SET_BIT(TCCR0,TCCR0_COM01);
	SET_BIT(TCCR0,TCCR0_COM00);
#endif

	/*Setting the OCR value for DUTY CYCLE*/
	// OCR0 = COMPARE_MATCH_VALUE;

	/*PreScalar division  by 8 */  // Important to be last code to start timer
	TCCR0 &= PRE_SCALE_MASK;
	TCCR0 |= CLK_SELECT_BIT;


#endif
}


void timer0_voidSetCompareValue(u8 value)
{
	OCR0 = value;
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


void TIMER1_voidInit(void)
{
	/*initilize the non inverting mode */
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);
	/*initialize the fast pwm mode changing the top value*/
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);
	/*SET the Pre-Scalar Value*/
	TCCR1B &= 0b11111000;
	TCCR1B |= 2;        // divide by 8

}

void TIMER1_voidSetICR(u16 copy_u16ICRVAL)
{
	/*Set the icr top value with value*/
	ICR1L = copy_u16ICRVAL;
}

void timer1_voidSetChannelA_CompareMatch(u16 value)
{
	OCR1AL =  value;
}



/*ISR FUNCTION*/
void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{

	callPackFunc();

}



