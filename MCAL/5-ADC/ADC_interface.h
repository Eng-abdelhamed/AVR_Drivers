/*******************************************************   ******************/
/*****************************************************   ******************/
/********************** author     : Abdelhamed Ahmed *********************/
/********************** Layer      : MCAL             *********************/
/********************** SWC        : ADC              *********************/
/********************** version    : 1.00             *********************/
/****************************************************   *******************/
/*****************************************************   ******************/
#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

typedef struct
{
	u8 Chain_id;
	u16 Channel_size;
	void (*Notify_func_Chain)(void);
	u16 Array_result[8];
}ADC_chain;



void ADC_voidINIT(void);

u16 ADC_u16StratConversionSynch(u8 copy_u8Channel , u16 *copy_pu16_returnState);

u16 ADC_u16StratConversion_ASynch(u8 copy_u8Channel,u16 *copy_pu16_returnState,void(*copy_p_NotifyFunction)(void));

u16 ADC_u16ChainCoversion_Async (ADC_chain *Copy_p_Chain);

#endif
