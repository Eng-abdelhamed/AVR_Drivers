#include "STD_TYPEs.h"
#include "BIT_MATH.h"
#include "DIO_register.h"
#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_config.h"
#include "Seven_Seg_Config.h"
#include "Seven_Segment_interface.h"

// Array holding the 7-segment display codes for digits 0-9
u8 seven_seg_digits[] = {0x3F, // 0
                         0x06, // 1
                         0x5B, // 2
                         0x4F, // 3
                         0x66, // 4
                         0x6D, // 5
                         0x7D, // 6
                         0x07, // 7
                         0x7F, // 8
                         0x6F  // 9
};

void Seven_Seg_Set_Num(Seven_seg *Seven_num , u8 NUM)
{
	 switch(Seven_num->Type)
	 {
	 case ANODE:
		 DIO_u8SetPortDirection(Seven_num->PORT ,DIO_u8PORT_OUTPUT);
		 DIO_u8SetPortValue(Seven_num->PORT ,(~(seven_seg_digits[NUM])));
	 break;
	 case CATHODE:
		 DIO_u8SetPortDirection(Seven_num->PORT ,DIO_u8PORT_OUTPUT);
		 DIO_u8SetPortValue(Seven_num->PORT ,(seven_seg_digits[NUM]));
	 break;
	 }
}
