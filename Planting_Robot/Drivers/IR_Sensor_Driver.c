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

void IR_Sensor_Driver_Init(void){
	/* Initialisation of the IR_Sensor_Driver Task*/
	if (FRTOS1_xTaskCreate(
	    IR_Sensor_Task,  /* pointer to the task */
	    (signed portCHAR *)"IR_Sensor_Task", /* task name for kernel awareness debugging */
	    configMINIMAL_STACK_SIZE, /* task stack size */
	    (void*)NULL, /* optional task startup argument */
	    tskIDLE_PRIORITY,  /* initial priority */
	    (xTaskHandle*)NULL /* optional task handle to create */
	) != pdPASS)
	{
	   for(;;){}; /* Out of heap memory? */
	}
}
