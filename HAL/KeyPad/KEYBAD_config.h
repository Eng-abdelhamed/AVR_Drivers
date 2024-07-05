 /*******************************************************   ******************/
/*****************************************************   ******************/
/********************** author     : Abdelhamed Ahmed *********************/
/********************** Layer      : MCAL             *********************/
/********************** SWC        : LCD              *********************/
/********************** version    : 1.00             *********************/
/****************************************************   *******************/
/*****************************************************   ******************/
#ifndef KEYBAD_CONFIG_H
#define KEYBAD_CONFIG_H


#define KBD_PORT       DIO_u8PORTD

#define KBD_COLOUMN_0  DIO_u8PIN0
#define KBD_COLOUMN_1  DIO_u8PIN1
#define KBD_COLOUMN_2  DIO_u8PIN2
#define KBD_COLOUMN_3  DIO_u8PIN3

#define KBD_ROW_0      DIO_u8PIN4
#define KBD_ROW_1      DIO_u8PIN5
#define KBD_ROW_2      DIO_u8PIN6
#define KBD_ROW_3      DIO_u8PIN7

#define KBD_Unpressed  0xff

#define KBD_ARR_VALUE  { {1, 2, 3, 4}, \
                         {5, 6, 7, 8}, \
                         {9, 10, 11, '+'}, \
                         {13, 14, 15, 16} }


#endif
