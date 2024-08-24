/*******************************************************   ******************/
/*****************************************************   ******************/
/********************** author     : Abdelhamed Ahmed *********************/
/********************** Layer      : HAL             *********************/
/********************** SWC        : SERVO              *********************/
/********************** version    : 1.00             *********************/
/****************************************************   *******************/
/*****************************************************   ******************/
#include"STD_TYPEs.h"
#include"BIT_MATH.h"
#include"TIMER_interface.h"
#include"TIMER_register.h"
#include"TIMER_config.h"
#include"TIMER_private.h"
#include"SERVO.interface.h"
#include"SERVO_private.h"
#include"SERVO.config.h"

u8 Servo_voidMotor(u8 degree)
{
    if (degree > 180)
    {
        degree = 180;
    }
    else if (degree < 0)
    {
        degree = 0;
    }
    u8 temp = -0.7278 * degree +255;
   return temp;
}

