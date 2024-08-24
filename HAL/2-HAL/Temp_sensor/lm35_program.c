/***********************************************************************/
/***********************************************************************/
/********************** author     : Abdelhamed Ahmed *********************/
/********************** Layer      : HAL              *********************/
/********************** SWC        : TEMP_SENSOR      *********************/
/********************** version    : 1.00             *********************/
/***********************************************************************/
/***********************************************************************/
#include"STD_TYPEs.h"
#include"ADC_interface.h"
#include"lm35_interface.h"
#include"lm35_config.h"
#include"lm35_private.h"


u8 TempSensor_u8Degree(u8 Digital_Result)
{
  u8 Local_u8Temp;
  u16 Local_u16MilliVolt;
#if Resolution == 256
  Local_u16MilliVolt = ((u32)Digital_Result * AVref_mv) / ADC_RES_8Bit;

#elif Resolution == 1024
  Local_u16MilliVolt = ((u32)Digital_Result * AVref_mv) / ADC_RES_10Bit;

#endif
  Local_u8Temp = Local_u16MilliVolt / TempSensor_Step_mv;
  return Local_u8Temp;
}
