/*******************************************************   ******************/
/*****************************************************   ******************/
/********************** author     : Abdelhamed Ahmed *********************/
/********************** Layer      : MCAL             *********************/
/********************** SWC        : LCD              *********************/
/********************** version    : 1.00             *********************/
/****************************************************   *******************/
/*****************************************************   ******************/
#include "STD_TYPEs.h"
#include "KEYBAD_private.h"
#include "KEYBAD_config.h"
#include "KEYBAD_interface.h"
#include"BIT_MATH.h"
#include "DIO_interface.h"

 u8 KeypadValueChar[KBD_SIZE_ROW][KBD_SIZE_COL]=
 {
                  {'1','2','3','/'}
                 ,{'4','5','6','*'}
                 ,{'7','8','9','-'}
                 ,{'R','0','C','+'}
 };

u8 KBD_u8GetPressedKey()
{
u8 KBD_u8Row_Iterator;
u8 KBD_u8Col_Iterator;
u8 KBD_GetPitState;
u8 KBD_u8POTTONPRESSED = KBD_Unpressed;
u8 static KBD_u8Column_array [KBD_SIZE_COL] = {KBD_COLOUMN_0 ,
		                                       KBD_COLOUMN_1 ,
		                                       KBD_COLOUMN_2 ,
		                                       KBD_COLOUMN_3  };

u8 static KBD_u8Row_array [KBD_SIZE_ROW] = {KBD_ROW_0 ,
		                                    KBD_ROW_1 ,
		                                    KBD_ROW_2 ,
		                                    KBD_ROW_3  };

//u8 static KBD_u8PuttonArray[KBD_SIZE_ROW][KBD_SIZE_COL]=KeypadValueChar;

for(KBD_u8Col_Iterator = 0 ;KBD_u8Col_Iterator < KBD_SIZE_COL ;KBD_u8Col_Iterator++)
{
	/*                      Activate currant column                                    */
	DIO_u8SetPinValue(KBD_PORT , KBD_u8Column_array[KBD_u8Col_Iterator],DIO_u8PIN_LOW);

	for(KBD_u8Row_Iterator = 0 ; KBD_u8Row_Iterator < KBD_SIZE_ROW ; KBD_u8Row_Iterator++)
	{
      if(KBD_u8Row_array[KBD_u8Row_Iterator] == 0)
      {
    	  DIO_u8GetPinValue(KBD_PORT ,KBD_u8Row_array[KBD_u8Row_Iterator],&KBD_GetPitState);
    	  /*                     Check if switch is Pressed Or Not                        */
    	  if(0 == KBD_GetPitState)
    	  {
    		  KBD_u8POTTONPRESSED = KeypadValueChar[KBD_u8Row_Iterator][KBD_u8Col_Iterator];
    		  /*   Busy waiting until the key is released  = polling */
    		  while(DIO_u8PIN_LOW == KBD_GetPitState)
    		  {
    	      DIO_u8GetPinValue(KBD_PORT ,KBD_u8Row_array[KBD_u8Row_Iterator],&KBD_GetPitState);
    		  }
    		  return KBD_u8POTTONPRESSED;
    	  }
      }

	}
	DIO_u8SetPinValue(KBD_PORT , KBD_u8Column_array[KBD_u8Col_Iterator],DIO_u8PIN_HIGH);
}
return KBD_u8POTTONPRESSED;
}
