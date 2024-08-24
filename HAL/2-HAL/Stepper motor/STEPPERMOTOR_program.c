
/*********************************************   **************************/
/******************************************      **************************/
/********************** author     : Abdelhamed Ahmed *********************/
/********************** Layer      : HAL             *********************/
/********************** SWC        : stepperMotor                    *********************/
/********************** version    : 1.00             *********************/
/**********************************************   *************************/
/*********************************************   **************************/

#include "STD_TYPEs.h"
#include "DIO_interface.h"
#include "PORT_interface.h"
#include "STEPPERMOTOR_config.h"
#include "STEPPERMOTOR_private.h"
#include "STEPPERMOTOR_interface.h"
#include "util/delay.h"


void Stepper_voidInit()
{
	/*  select 4 pin as output to control the ULN 2003 */
	DIO_u8SetPinValue(stepper_port,stepper_pin1,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(stepper_port,stepper_pin2,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(stepper_port,stepper_pin3,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(stepper_port,stepper_pin4,DIO_u8PIN_HIGH);
}

void Stepper_voidStepperControl(u8 angle)
{
	u8 NoOf_step;
    u8 NoOf_Iteration;
    NoOf_step = angle / AngelOf_Full ;
    NoOf_Iteration = NoOf_step / 4   ;
    for(u8 i = 0 ; i < NoOf_Iteration ;i++)
    {
    	DIO_u8SetPinValue(stepper_port,stepper_pin1,DIO_u8PIN_LOW);
    	DIO_u8SetPinValue(stepper_port,stepper_pin2,DIO_u8PIN_HIGH);
    	DIO_u8SetPinValue(stepper_port,stepper_pin3,DIO_u8PIN_HIGH);
    	DIO_u8SetPinValue(stepper_port,stepper_pin4,DIO_u8PIN_HIGH);
        _delay_ms(2);
        DIO_u8SetPinValue(stepper_port,stepper_pin1,DIO_u8PIN_HIGH);
        DIO_u8SetPinValue(stepper_port,stepper_pin2,DIO_u8PIN_LOW);
        DIO_u8SetPinValue(stepper_port,stepper_pin3,DIO_u8PIN_HIGH);
        DIO_u8SetPinValue(stepper_port,stepper_pin4,DIO_u8PIN_HIGH);
        _delay_ms(2);
        DIO_u8SetPinValue(stepper_port,stepper_pin1,DIO_u8PIN_HIGH);
        DIO_u8SetPinValue(stepper_port,stepper_pin2,DIO_u8PIN_HIGH);
        DIO_u8SetPinValue(stepper_port,stepper_pin3,DIO_u8PIN_LOW);
        DIO_u8SetPinValue(stepper_port,stepper_pin4,DIO_u8PIN_HIGH);
        _delay_ms(2);
        DIO_u8SetPinValue(stepper_port,stepper_pin1,DIO_u8PIN_HIGH);
        DIO_u8SetPinValue(stepper_port,stepper_pin2,DIO_u8PIN_HIGH);
        DIO_u8SetPinValue(stepper_port,stepper_pin3,DIO_u8PIN_HIGH);
        DIO_u8SetPinValue(stepper_port,stepper_pin4,DIO_u8PIN_LOW);
        _delay_ms(2);
    }







}

