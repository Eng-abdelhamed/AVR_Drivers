/***********************************************************************/
/***********************************************************************/
/********************** author     : Abdelhamed Ahmed *********************/
/********************** Layer      : HAL             *********************/
/********************** SWC  :       LED             *********************/
/********************** version    : 1.00             *********************/
/***********************************************************************/
/***********************************************************************/
#include"STD_TYPEs.h"
#include"BIT_MATH.h"
#include"DIO_interface.h"
#include"DIO_config.h"
#include"DIO_register.h"
#include"DIO_private.h"
#include"LED_interface.h"

void LED_ONN(u8 PORT ,u8 PIN_NUM)
{
	DIO_u8SetPinDirection(PORT , PIN_NUM ,DIO_u8PIN_Output);
	DIO_u8SetPinValue(PORT ,PIN_NUM ,DIO_u8PIN_HIGH);
}
void LED_OFF(u8 PORT ,u8 PIN_NUM)
{
	DIO_u8SetPinDirection(PORT , PIN_NUM ,DIO_u8PIN_Output);
    DIO_u8SetPinValue(PORT ,PIN_NUM ,DIO_u8PIN_LOW);
}
void LED_TOGGLE(u8 PORT ,u8 PIN_NUM)
{
	u8 status;
	DIO_u8SetPinDirection(PORT , PIN_NUM ,DIO_u8PIN_Output);
	DIO_u8GetPinValue(PORT,PIN_NUM,&status);
	if(status == DIO_u8PIN_HIGH)
	{
     DIO_u8SetPinValue(PORT ,PIN_NUM ,DIO_u8PIN_LOW);
	}
	else if(status == DIO_u8PIN_LOW)
	{
		DIO_u8SetPinValue(PORT ,PIN_NUM ,DIO_u8PIN_HIGH);
	}
}


