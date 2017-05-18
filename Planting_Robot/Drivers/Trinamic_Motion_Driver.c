/*
 * Trinamic_Motion_Driver.c
 *
 *  Created on: 18.05.2017
 *      Author: Patrick
 */

#include "Trinamic_Motion_Driver.h"


static void Trinamic_Motion_Task(void *pvParameters) {
	(void)pvParameters; /* parameter not used */

	for(;;) {
		LED2_Neg();
		FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
	}
}

/*
 * Sends a char packet to the Driver
 */
void Trinamic_Motion_sendPacket(unsigned char packet[], int packetlength){
		for(int i=0; i<packetlength; i++){
			CLS1_SendChar(packet[i]);
		}
}

void Trinamic_Motion_Driver_Init(void){
	/* Initialisation of the Trinamic_Motion_Driver Task*/
	if(FRTOS1_xTaskCreate(Trinamic_Motion_Task, (signed portCHAR *)"Trinamic_Motion_Task", configMINIMAL_STACK_SIZE, (void*)NULL, tskIDLE_PRIORITY, (xTaskHandle*)NULL) != pdPASS)
	{
		for(;;){}; /* Out of heap memory? */
	}
}
