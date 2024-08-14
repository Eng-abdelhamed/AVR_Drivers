/*******************************************************   ******************/
/*****************************************************   ******************/
/********************** author     : Abdelhamed Ahmed *********************/
/********************** Layer      : MCAL             *********************/
/********************** SWC        : keybad              *********************/
/********************** version    : 1.00             *********************/
/****************************************************   *******************/
/*****************************************************   ******************/
#include "STD_TYPEs.h"
#include "BIT_MATH.h"
#include "KEYBAD_private.h"
#include "KEYBAD_config.h"
#include "KEYBAD_interface.h"
#include "DIO_interface.h"




u8 KBD_u8GetPressedKey(void)
{
    u8 KBD_u8POTTONPRESSED = KBD_Unpressed;
    u8 KBD_u8Row_Iterator;
    u8 KBD_u8Col_Iterator;
    u8 KBD_GetPitState;

    static u8 KBD_u8Column_array[KBD_SIZE_COL] = { KBD_COLOUMN_0,
                                                   KBD_COLOUMN_1,
                                                   KBD_COLOUMN_2,
                                                   KBD_COLOUMN_3 };

    static u8 KBD_u8Row_array[KBD_SIZE_ROW] = { KBD_ROW_0,
                                                KBD_ROW_1,
                                                KBD_ROW_2,
                                                KBD_ROW_3  };

    static u8 KBD_u8PuttonArray[KBD_SIZE_ROW][KBD_SIZE_COL] = KBD_ARR_VALUE;

    for (KBD_u8Col_Iterator = 0; KBD_u8Col_Iterator < KBD_SIZE_COL; KBD_u8Col_Iterator++)
    {
        /* Activate current column */
        DIO_u8SetPinValue(KBD_PORT, KBD_u8Column_array[KBD_u8Col_Iterator], DIO_u8PIN_LOW);

        for (KBD_u8Row_Iterator = 0; KBD_u8Row_Iterator < KBD_SIZE_ROW; KBD_u8Row_Iterator++)
        {
            DIO_u8GetPinValue(KBD_PORT, KBD_u8Row_array[KBD_u8Row_Iterator], &KBD_GetPitState);

            /* Check if switch is pressed */
            if (DIO_u8PIN_LOW == KBD_GetPitState)
            {
                KBD_u8POTTONPRESSED = KBD_u8PuttonArray[KBD_u8Row_Iterator][KBD_u8Col_Iterator];

                /* Busy wait until the key is released (polling) */
                while (DIO_u8PIN_LOW == KBD_GetPitState)
                {
                    DIO_u8GetPinValue(KBD_PORT, KBD_u8Row_array[KBD_u8Row_Iterator], &KBD_GetPitState);
                }

                /* Add a small delay for debouncing */
               // _delay_ms(20);

                return KBD_u8POTTONPRESSED;
            }
        }

        /* Deactivate current column */
        DIO_u8SetPinValue(KBD_PORT, KBD_u8Column_array[KBD_u8Col_Iterator], DIO_u8PIN_HIGH);
    }

    return KBD_u8POTTONPRESSED;
}

