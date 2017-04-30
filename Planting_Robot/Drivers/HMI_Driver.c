/*
 * HMI_Driver.c
 *
 *  Created on: 30.04.2017
 *      Author: Patrick
 */


#include "HMI_Driver.h"


static void HMI_Task(void *pvParameters) {
	(void)pvParameters; /* parameter not used */
	for(;;) {

		FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
	}
}

void HMI_Driver_Init(void){
	/* Initialisation of the HMI_Driver Task*/
	if (FRTOS1_xTaskCreate(HMI_Task, (signed portCHAR *)"HMI_Task", configMINIMAL_STACK_SIZE, (void*)NULL, tskIDLE_PRIORITY, (xTaskHandle*)NULL) != pdPASS){
	   for(;;){}; /* Out of heap memory? */
	}
}
