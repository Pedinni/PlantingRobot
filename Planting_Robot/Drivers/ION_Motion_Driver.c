/*
 * ION_Motion_Driver.c
 *
 *  Created on: 23.04.2017
 *      Author: Patrick
 */


#include "ION_Motion_Driver.h"


static void ION_Motion_Task(void *pvParameters) {
  (void)pvParameters; /* parameter not used */

  for(;;) {
	  /*unsigned char* String[5];

	  strcat(&String, 128);
	  strcat(&String, 6);
	  strcat(&String, 80);

	  CLS1_SendStr(&String, CLS1_GetStdio()->stdOut);
	  */

	  unsigned int packet[3];
	  packet[0] = 0x00;		//128
	  packet[1] = 0xFF;		//6
	  packet[2] = 0x00;		//80

	  CLS1_SendNum8u(packet[1], CLS1_GetStdio()->stdOut);				// Adress:	(128)
	  //FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
	  //CLS1_SendNum8u(packet[1], CLS1_GetStdio()->stdOut);				// Command: Drive M1 (6)
	  //FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
	  //CLS1_SendNum8u(packet[2], CLS1_GetStdio()->stdOut);				// Value:	Drive motor 1 forward or reverse. Valid data range is 0 - 127.
	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  			// 			A value of 0 = full speed reverse, 64 = stop and 127 = full speed forward


	  //packet = (unsigned char*)packet;

	  /*
 	 	 strcpy(packet,"128");
	 	 strcpy(packet,"6");
		  strcpy(packet,"80");
	  */
	  //unsigned int crc = crc16(packet, sizeof(packet));

	  //CLS1_SendNum16u(crc, CLS1_GetStdio()->stdOut);		// CRC 2 Byte

	  FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
  	  }
}

//Calculates CRC16 of nBytes of data in byte array message
/*
unsigned int crc16(unsigned char *packet, int nBytes) {
	unsigned int crc;
	for (int byte = 0; byte < nBytes; byte++) {
		crc = crc ^ ((unsigned int)packet[byte] << 8);
		for (unsigned char bit = 0; bit < 8; bit++) {
			if (crc & 0x8000) {
				crc = (crc << 1) ^ 0x1021;
			} else {
				crc = crc << 1;
			}
		}
	}
	return crc;
}
*/

void ION_Motion_Driver_Init(void){
	/* Initialisation of the IR_Sensor_Driver Task*/
	if (FRTOS1_xTaskCreate(
		ION_Motion_Task,  /* pointer to the task */
	    (signed portCHAR *)"ION_Motion_Task", /* task name for kernel awareness debugging */
	    configMINIMAL_STACK_SIZE, /* task stack size */
	    (void*)NULL, /* optional task startup argument */
	    tskIDLE_PRIORITY,  /* initial priority */
	    (xTaskHandle*)NULL /* optional task handle to create */
	) != pdPASS)
	{
		for(;;){}; /* Out of heap memory? */
	}
}
