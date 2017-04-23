/*
 * LED_Driver.c
 *
 *  Created on: 23.04.2017
 *      Author: Patrick
 */


#include "IR_Sensor_Driver.h"


static void IR_Sensor_Task(void *pvParameters) {
	(void)pvParameters; /* parameter not used */

	uint16_t IR_Value = 0;
	for(;;) {
		(void)AD1_Measure(TRUE);
		(void)AD1_GetValue16(&IR_Value);

		if (IR_Value >= Erkenndistanz){
			LED1_On();
		} else{
			LED1_Off();
		}
		WAIT1_Waitms(100);
	}
}
