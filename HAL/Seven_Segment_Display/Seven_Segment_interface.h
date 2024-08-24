/*
 * Seven_Segment_interface.h
 *
 *  Created on: Aug 20, 2024
 *      Author: abdel
 */

#ifndef SEVEN_SEGMENT_INTERFACE_H_
#define SEVEN_SEGMENT_INTERFACE_H_
#include"Seven_Seg_Config.h"
typedef struct
{
	u8 PORT;
	u8 Type;

}Seven_seg;



void Seven_Seg_Set_Num(Seven_seg *Seven_num , u8 NUM);



#endif /* SEVEN_SEGMENT_INTERFACE_H_ */
