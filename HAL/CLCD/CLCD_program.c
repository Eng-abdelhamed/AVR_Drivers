/***********************************************************************/
/***********************************************************************/
/********************** author     : Abdelhamed Ahmed *********************/
/********************** Layer      : HAL             *********************/
/********************** SWC        : LCD             *********************/
/********************** version    : 1.00          *********************/
/***********************************************************************/
/***********************************************************************/
#include "STD_TYPEs.h"
#include "util/delay.h"
#include "DIO_interface.h"
#include "CLCD_config.h"
#include "CLCD_interface.h"
#include "CLCD_private.h"

/* Send Command to LCD */
void CLCD_voidSendCommand(u8 Copu_u8Command)
{
	/*Set RS pin to low for command */
	DIO_u8SetPinValue  (CLCD_CTRL_PORT , CLCD_RS_PIN , DIO_u8PIN_LOW);

	/*Set RW pin to low for command */
	DIO_u8SetPinValue  (CLCD_CTRL_PORT , CLCD_RW_PIN , DIO_u8PIN_LOW);

	/* SET command Data */
	DIO_u8SetPortValue (CLCD_DATA_PORT , Copu_u8Command);

	/*Send Enable pin to low for command */
	DIO_u8SetPinValue  (CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_HIGH);

	_delay_ms(2);

	DIO_u8SetPinValue  (CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_LOW);
}

/* Send Data to LCD */
void CLCD_voidSendData(u8 Copy_u8Data)
{
	/*Set RS pin to high for data */
	DIO_u8SetPinValue  (CLCD_CTRL_PORT , CLCD_RS_PIN , DIO_u8PIN_HIGH);

	/*Set RW pin to low for data */
	DIO_u8SetPinValue  (CLCD_CTRL_PORT , CLCD_RW_PIN , DIO_u8PIN_LOW);

	/* SET command Data */
	DIO_u8SetPortValue (CLCD_DATA_PORT , Copy_u8Data);

	/*Send Enable pin to low for command */
	DIO_u8SetPinValue  (CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_HIGH);

	_delay_ms(2);

	DIO_u8SetPinValue  (CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_LOW);
}

/* INITALIZE LCD */
void CLCD_voidInitialize(void)
{
	/*wait for more than 30 Ms */
	_delay_ms(40);
	/*Function Set command 2lines , 5*8 font size*/
	CLCD_voidSendCommand(0b00111000);
	/* display on off control  display enable ,disable cursor , no Blink cursor*/
	CLCD_voidSendCommand(0b00001100);

	/* clear display*/
	CLCD_voidSendCommand(1);
}
void CLCD_voidSendString(const char*Copy_pcharString)
{
	u8 Counter  = 0;
	while(Copy_pcharString[Counter]!= '\0')
	{
		CLCD_voidSendData(Copy_pcharString[Counter]);
		Counter++;
	}
}
void CLCD_voidGotoX_Y(u8 Copy_u8XPos,u8 Copy_u8YPos)
{
	u8 Local_u8Address;
	if(Copy_u8XPos == 0)
	{
		/* location is at First line */
		Local_u8Address = Copy_u8YPos ;
	}
	else if(Copy_u8XPos == 1)
	{
		/* location is at Second line */
		Local_u8Address = Copy_u8YPos + 0x40;
	}
	CLCD_voidSendCommand(Local_u8Address + 128);
}

void CLCD_voidWriteSpecialChar(u8*Copy_pu8Array , u8 COpy_u8BlockNumber , u8 Copy_u8Xpos,u8 Copy_u8Ypos)

{
	u8 Local_u8CGRamAddress=0;
	u8 Local_u8Iterator ;
	/*         Calculate CG RAM address           */
	Local_u8CGRamAddress = COpy_u8BlockNumber * 8;
	/*         writing CG RAM address           */
	CLCD_voidSendCommand(COpy_u8BlockNumber + 64);

	for(Local_u8Iterator =0 ;Local_u8Iterator < 8 ;Local_u8Iterator++)
	{
		CLCD_voidSendData(Copy_pu8Array[Local_u8Iterator]);
	}
	/*     Go back to DDRam to display array       */
	CLCD_voidGotoX_Y(  Copy_u8Xpos ,Copy_u8Ypos);

	/* Write the Array in the block number itself  */
	CLCD_voidSendData(COpy_u8BlockNumber);
}
void CLCD_voidWriteNumber(u32 Copy_u64Number) {
	u32 LOC_u64Reversed = 0; // Initialize to 0 for proper reversal

	if (Copy_u64Number == 0) {
		CLCD_voidSendData('0');
		return; // Exit function early if the number is 0
	}

	// Reverse Copy_u64Number
	while (Copy_u64Number != 0)
	{
		LOC_u64Reversed = (LOC_u64Reversed * 10) + (Copy_u64Number % 10);
		Copy_u64Number /= 10;
	}

	// Send reversed number to CLCD
	while (LOC_u64Reversed != 0)
	{
		CLCD_voidSendData((LOC_u64Reversed % 10) + '0');
		LOC_u64Reversed /= 10;
	}
}
void CLCD_voidClearScreen(void)
{

	CLCD_voidSendCommand(0x01);
	_delay_ms(1.53);
}
