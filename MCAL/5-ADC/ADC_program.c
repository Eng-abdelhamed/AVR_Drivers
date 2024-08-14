/*************************************************************/
/*************************************************************/
/******************** Author: Abdelhamed Ahmed ****************/
/******************** Layer: MCAL ********************/
/******************** SWC: ADC ********************/
/******************** Version: 1.00 ********************/
/*************************************************************/
/*************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"
#include "ADC_register.h"


// Function pointer to use in ISR
static void(*p_CallBackFun)(void) = 0;
static void(*p_CallBackChainFun)(void) = 0;
// Pointer to store ADC reading
u16 *ADC_reading = 0;
u16 *ADC_Chain_reading = 0;
u16 Chanel_size=0;
u16 Array_data[8];
u8 Channel_id;
u8 Chain_flag = NOT_CHAIN;
u8 chain_index = 0;

// ADC state variable
u8 Adc_Busystate = IDLE;

/**
 * @brief Initialize the ADC
 */
void ADC_voidINIT(void)
{
    // Set voltage reference
#if (VOLT_Refrence == AVCC)
    SET_BIT(ADMUX, ADMUX_REFS0);
    CLR_BIT(ADMUX, ADMUX_REFS1);
#elif (VOLT_Refrence == AREF)
    CLR_BIT(ADMUX, ADMUX_REFS1);
    CLR_BIT(ADMUX, ADMUX_REFS0);
#elif (VOLT_Refrence == Internal)
    SET_BIT(ADMUX, ADMUX_REFS0);
    SET_BIT(ADMUX, ADMUX_REFS1);
#else
    #error "Wrong Voltage Reference Configurations"
#endif

    // Set resolution adjustment
#if (ADC_RESOLUTION == 256)
    SET_BIT(ADMUX, ADMUX_ADLAR);
#elif (ADC_RESOLUTION == 1024)
    CLR_BIT(ADMUX, ADMUX_ADLAR);
#else
    #error "Wrong Resolution Adjustment"
#endif

    // Set prescaler options
    ADCSRA &= PRESCALAR_MASK;  // Clear the last three bits
    ADCSRA |= ADC_PRESCALAR;   // Set the last three bits with the value

    // Enable ADC
    SET_BIT(ADCSRA, ADCSRA_ADEN);  // ADC enable bit

#if (AUTO_TRIGGR == ENABLE && AUTO_TRIG_MODE == FREE_RUNNING)
    ADMUX &= ADMUX_MASK_CLEAR;
    ADMUX |= AUTO_TRIG_CHANNEL;
    // Start first conversion
    SET_BIT(ADCSRA, ADCSRA_ADSC);
    // Set auto trigger enable bit
    SET_BIT(ADCSRA, ADCSRA_ADATE);
    // Set interrupt enable pin (not essential in ADATE)
    SET_BIT(ADCSRA, ADCSRA_ADIE);

    // Set trigger mode at SFIOR Register
    SFIOR &= SFIOR_MASK;
    SFIOR |= AUTO_TRIG_MODE;
#endif
}

/**
 * @brief Start synchronous ADC conversion
 * @param copy_u8Channel ADC channel to convert
 * @param copy_pu16_returnState Pointer to store the ADC result
 * @return u16 Error state
 */
u16 ADC_u16StratConversionSynch(u8 copy_u8Channel, u16 *copy_pu16_returnState)
{
    u8 Local_u8ErrorState = 0;

    if (Adc_Busystate == IDLE)
    {
        u32 local_u32counter = 0;

        // Clear the mux bits in ADMUX register
        ADMUX &= ADMUX_MASK_CLEAR;
        // Set the channel into mux bits
        ADMUX |= copy_u8Channel;

#if (AUTO_TRIGGR == DISABLE)
        // Start conversion
        SET_BIT(ADCSRA, ADCSRA_ADSC);
        // Polling until the flag is set or reaching the timeout
        while (((GET_BIT(ADCSRA, ADCSRA_ADIF)) == 0) && (local_u32counter != ADC_u32Timeout))
        {
            local_u32counter++;
        }
        if (local_u32counter == ADC_u32Timeout)
        {
            // Loop is broken because the timeout is reached
            Local_u8ErrorState = 1;
        }
        else
        {
            // Clear the flag
            SET_BIT(ADCSRA, ADCSRA_ADIF);
#endif

#if (ADC_RESOLUTION == 256)
            *copy_pu16_returnState = ADCH;
            Adc_Busystate = IDLE;

#elif (ADC_RESOLUTION == 1024)
            *copy_pu16_returnState = ADC;
            Adc_Busystate = IDLE;
#endif
        }
    }
    else
    {
        Local_u8ErrorState = BUSY_FUNC;
    }
    // Returning the error state for the user
    return Local_u8ErrorState;
}

/**
 * @brief Start asynchronous ADC conversion
 *
 * @param copy_u8Channel ADC channel to convert
 * @param copy_pu16_returnState Pointer to store the ADC result
 * @param copy_p_NotifyFunction Pointer to the callback function
 * @return u16 Error state
 */
u16 ADC_u16StratConversion_ASynch(u8 copy_u8Channel, u16 *copy_pu16_returnState, void(*copy_p_NotifyFunction)(void))
{
    u8 Local_u8ReturnState = 0;

    if (Adc_Busystate == IDLE)
    {
        if (copy_pu16_returnState == 0 || copy_p_NotifyFunction == 0)
        {
            Local_u8ReturnState = 1;
        }
        else
        {
            Adc_Busystate = Busy;
            // Init the reading variable globally
            p_CallBackFun = copy_p_NotifyFunction;
            // Init the callback notify function globally
            ADC_reading = copy_pu16_returnState;

            // Clear the ADMUX first
            ADMUX &= ADMUX_MASK_CLEAR;
            // Then set the ADMUX
            ADMUX |= copy_u8Channel;
            // Start conversion
            SET_BIT(ADCSRA, ADCSRA_ADSC);
            // Enable interrupt
            SET_BIT(ADCSRA, ADCSRA_ADIE);
        }
    }
    else
    {
        Local_u8ReturnState = BUSY_FUNC;
    }

    return Local_u8ReturnState;
}
u16 ADC_u16ChainCoversion_Async(ADC_chain *Copy_p_Chain)
{
	/* indication for the isr to work on CHAIN*/
	Chain_flag = CHAIN;
	u8 Local_u8ReturnState = OK;
	if(Copy_p_Chain->Notify_func_Chain == 0)
	{
		Local_u8ReturnState = NOK;
	}
	else
	{
     /*Initialize the global pointer to function to the struct pointer*/
		p_CallBackChainFun =Copy_p_Chain->Notify_func_Chain;
		/*Initialize the Channel_size  to function to the struct pointer*/
		Chanel_size = Copy_p_Chain->Channel_size;
		/*Initialize the Channel_size  to function to the struct pointer*/
	        for (u16 i = 0; i < Chanel_size; ++i)
	        {
	            Array_data[i] = Copy_p_Chain->Array_result[i];
	        }
		/*Initialize the Channel_size  to function to the struct pointer*/
		Channel_id = Copy_p_Chain->Chain_id;
		/*SET the Channel ADmux*/
		ADMUX &= ADMUX_MASK_CLEAR;
		ADMUX |= Channel_id;
		/*START conversion*/
		SET_BIT(ADCSRA,ADCSRA_ADSC);
		/*set intrupt enable*/
		SET_BIT(ADCSRA,ADCSRA_ADEN);
	}
	return Local_u8ReturnState;
}

/**
 * @brief ADC Conversion Complete ISR
 */
void __vector_16(void) __attribute__((signal));  // ISR
void __vector_16(void)
{
	/* Checking for the flag for the chain or not chain just single conversion Async */
	if(Chain_flag==CHAIN)
	{
		/*the chain end*/
		if(chain_index == Chanel_size )
		{

			/*invoke the call back function to start */
			p_CallBackChainFun();
			/*clear the intrupt pin ENABLE*/
			CLR_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
             #if (ADC_RESOLUTION == 256)
			 Array_data[chain_index] = ADCH;
              #elif (ADC_RESOLUTION == 1024)
			 Array_data[chain_index] = ADC;
              #endif
            /*increment to set the next channel*/
			    ADMUX &= ADMUX_MASK_CLEAR;
			    Channel_id++;
				ADMUX |= Channel_id;
			/*start conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);
			chain_index++;
		}
	}
	else
	{
	    // Read the ADC result
	#if (ADC_RESOLUTION == 256)
	    *ADC_reading = ADCH;
	#elif (ADC_RESOLUTION == 1024)
	    *ADC_reading = ADC;
	#endif

	    Adc_Busystate = IDLE;
	    // Invoke the callback notification
	    p_CallBackFun();
	   /*disable the adc enbale*/
	    CLR_BIT(ADCSRA,ADCSRA_ADIE);
	}

}
